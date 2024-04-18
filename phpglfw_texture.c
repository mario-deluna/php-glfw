/**
 * PHP-glfw 
 * 
 * Extension: GL Textures
 *
 * Copyright (c) 2018-2024 Mario Döring
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "phpglfw_texture.h"
#include "phpglfw_arginfo.h"
#include "phpglfw_buffer.h"

#define STB_IMAGE_IMPLEMENTATION
#define STBI_MALLOC emalloc
#define STBI_REALLOC erealloc
#define STBI_FREE efree
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// we also have the perlin noise functions in here
// they probably should be moved to some utility namespace
#define STB_PERLIN_IMPLEMENTATION
#include <stb_perlin.h>

zend_class_entry *phpglfw_texture2d_ce; 

zend_class_entry *phpglfw_get_texture_texture2d_ce() {
    return phpglfw_texture2d_ce;
}

phpglfw_texture2d_object* phpglfw_texture2d_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_texture2d_object *) ((char *) (obj) - XtOffsetOf(phpglfw_texture2d_object, std));
}

static zend_object_handlers phpglfw_texture2d_handlers;

zend_object *phpglfw_texture2d_create_handler(zend_class_entry *class_type)
{
    phpglfw_texture2d_object *intern = zend_object_alloc(sizeof(phpglfw_texture2d_object), class_type);

	zend_object_std_init(&intern->std, class_type);
	object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_texture2d_handlers;

    ZVAL_UNDEF(&intern->buffer_zval);
    object_init_ex(&intern->buffer_zval, phpglfw_get_buffer_glubyte_ce());

    return &intern->std;
}

static void phpglfw_texture2d_free_handler(zend_object *object)
{
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(object);

    zval_ptr_dtor(&intern->buffer_zval);
    zend_object_std_dtor(&intern->std);
}

static HashTable *phpglfw_texture2d_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(3);
    *is_temp = 1;

    ZVAL_LONG(&zv, intern->width);
    zend_hash_str_update(ht, "width", sizeof("width") - 1, &zv);

    ZVAL_LONG(&zv, intern->height);
    zend_hash_str_update(ht, "height", sizeof("height") - 1, &zv);

    ZVAL_LONG(&zv, intern->channels);
    zend_hash_str_update(ht, "channels", sizeof("channels") - 1, &zv);
 

    return ht;
}

PHP_METHOD(GL_Texture_Texture2D, fromDisk)
{
    const char *path;
    size_t path_size;
    zend_long force_channels = 0;
    bool flip_vertically = 1;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|lb", &path, &path_size, &force_channels, &flip_vertically) == FAILURE) {
        RETURN_THROWS();
    }

    if (force_channels > 4) {
        zend_throw_error(NULL, "Invalid number of channels. Must be between 1 and 4.");
        return;
    }

    object_init_ex(return_value, phpglfw_get_texture_texture2d_ce());
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    phpglfw_buffer_glubyte_object *buffer = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(&intern->buffer_zval));

    stbi_set_flip_vertically_on_load(flip_vertically); 

    unsigned char *data = stbi_load(path, &intern->width, &intern->height, &intern->channels, force_channels);
    size_t buffersize;
    if (data == NULL) {
        zend_throw_error(NULL, "Failed to load image from disk '%s'.", path);
        return;
    }

    // in our case we overwrite the channels with the forced channels
    // because from userland we care about the final resulting buffer
    if (force_channels > 0) {
        intern->channels = force_channels;
    }

    buffersize = intern->width * intern->height * intern->channels;

    // php_printf("%s: %i x %i x %i, (%i)", path, intern->width, intern->height, intern->channels, buffersize);

    // prealloc space
    cvector_reserve(buffer->vec, buffersize);

    // copy the data over to the buffer
    // please if somebody finds a way to avoid this copy, let me know
    memcpy(buffer->vec, data, buffersize * sizeof(unsigned char));
    cvector_set_size(buffer->vec, buffersize);
    // for (size_t i = 0; i < buffersize; i++) {
    //     cvector_push_back(buffer->vec, data[i]);
    // }

    // free the stb allocated memory 
    efree(data);
    // php_printf("buffer cap %i\n", cvector_capacity(buffer->vec));
    // buffer->vec = data;
}

PHP_METHOD(GL_Texture_Texture2D, fromBuffer)
{
    zend_long width, height, channels = 4;
    zval *buffer_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "llO|l", &width, &height, &buffer_zval, phpglfw_get_buffer_glubyte_ce(), &channels) == FAILURE) {
        RETURN_THROWS();
    }

    if (channels > 4 || channels < 1) {
        zend_throw_error(NULL, "Invalid number of channels. Must be between 1 and 4.");
        return;
    }

    // check if the buffer is big enough
    phpglfw_buffer_glubyte_object *buffer = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(buffer_zval));

    if (cvector_size(buffer->vec) < width * height * channels) {
        zend_throw_error(NULL, "Buffer is too small to hold the image data.");
        return;
    }

    object_init_ex(return_value, phpglfw_get_texture_texture2d_ce());
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    ZVAL_COPY(&intern->buffer_zval, buffer_zval);

    intern->width = width;
    intern->height = height;
    intern->channels = channels;
}

PHP_METHOD(GL_Texture_Texture2D, width)
{
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    RETURN_LONG(intern->width);
}

PHP_METHOD(GL_Texture_Texture2D, height)
{
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    RETURN_LONG(intern->height);
}

PHP_METHOD(GL_Texture_Texture2D, channels)
{
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    RETURN_LONG(intern->channels);
}

PHP_METHOD(GL_Texture_Texture2D, buffer)
{
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    // phpglfw_buffer_glubyte_object *buffer = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(&intern->buffer_zval));
    // php_printf("fetching buffer %p\n", &intern->buffer_zval);
    // php_printf("buffer cap %i\n", cvector_capacity(buffer->vec));

    RETURN_ZVAL(&intern->buffer_zval, 1, 0);
}

PHP_METHOD(GL_Texture_Texture2D, writeJPG)
{
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_buffer_glubyte_object *buffer = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(&intern->buffer_zval));
    const char *path;
    size_t path_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &path, &path_size) == FAILURE) {
        RETURN_THROWS();
    }
    stbi_flip_vertically_on_write(1);
    stbi_write_jpg(path, intern->width, intern->height, intern->channels, buffer->vec, 100);
}

PHP_METHOD(GL_Texture_Texture2D, writePNG)
{
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_buffer_glubyte_object *buffer = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(&intern->buffer_zval));
    const char *path;
    size_t path_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &path, &path_size) == FAILURE) {
        RETURN_THROWS();
    }
    stbi_flip_vertically_on_write(1);
    stbi_write_png(path, intern->width, intern->height, intern->channels, buffer->vec, 0);
}

PHP_METHOD(GL_Texture_Texture2D, writeBMP)
{
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_buffer_glubyte_object *buffer = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(&intern->buffer_zval));
    const char *path;
    size_t path_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &path, &path_size) == FAILURE) {
        RETURN_THROWS();
    }
    stbi_flip_vertically_on_write(1);
    stbi_write_bmp(path, intern->width, intern->height, intern->channels, buffer->vec);
}

PHP_METHOD(GL_Texture_Texture2D, writeTGA)
{
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_buffer_glubyte_object *buffer = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(&intern->buffer_zval));
    const char *path;
    size_t path_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &path, &path_size) == FAILURE) {
        RETURN_THROWS();
    }
    stbi_flip_vertically_on_write(1);
    stbi_write_tga(path, intern->width, intern->height, intern->channels, buffer->vec);
}

PHP_METHOD(GL_Noise, perlin)
{
    double x, y, z;
    zend_long x_wrap = 0, y_wrap = 0, z_wrap = 0, seed = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddd|llll", &x, &y, &z, &x_wrap, &y_wrap, &z_wrap, &seed) == FAILURE) {
        RETURN_THROWS();
    }

    float result = stb_perlin_noise3_seed(x, y, z, x_wrap, y_wrap, z_wrap, seed);

    RETURN_DOUBLE(result);
}

PHP_METHOD(GL_Noise, ridge)
{
    double x, y, z;
    double lacunarity = 2.0, gain = 0.5, offset = 1.0;
    zend_long octaves = 6;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddd|dddl", &x, &y, &z, &lacunarity, &gain, &offset, &octaves) == FAILURE) {
        RETURN_THROWS();
    }

    float result = stb_perlin_ridge_noise3(x, y, z, lacunarity, gain, offset, octaves);

    RETURN_DOUBLE(result);
}

PHP_METHOD(GL_Noise, fbm)
{
    double x, y, z;
    double lacunarity = 2.0, gain = 0.5;
    zend_long octaves = 6;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddd|ddl", &x, &y, &z, &lacunarity, &gain, &octaves) == FAILURE) {
        RETURN_THROWS();
    }

    float result = stb_perlin_fbm_noise3(x, y, z, lacunarity, gain, octaves);

    RETURN_DOUBLE(result);
}

PHP_METHOD(GL_Noise, turbulence)
{
    double x, y, z;
    double lacunarity = 2.0, gain = 0.5;
    zend_long octaves = 6;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ddd|ddl", &x, &y, &z, &lacunarity, &gain, &octaves) == FAILURE) {
        RETURN_THROWS();
    }

    float result = stb_perlin_turbulence_noise3(x, y, z, lacunarity, gain, octaves);

    RETURN_DOUBLE(result);
}

PHP_METHOD(GL_Noise, perlinFill2D)
{
    zval *buffer_zval;
    zend_long width, height, wrapX = 0, wrapY = 0, seed = 0;
    double scale, offsetX = 0, offsetY = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Olld|ddlll", &buffer_zval, phpglfw_get_buffer_glfloat_ce(), &width, &height, &scale, &offsetX, &offsetY, &wrapX, &wrapY, &seed) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_buffer_glfloat_object *buffer = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(buffer_zval));

    if (cvector_size(buffer->vec) < width * height) {
        cvector_reserve(buffer->vec, width * height);
        cvector_fill(buffer->vec, width * height, 0.0f);
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double nx = (double) x / width - 0.5;
            double ny = (double) y / height - 0.5;
            float value = stb_perlin_noise3_seed(nx * scale + offsetX, ny * scale + offsetY, 0, wrapX, wrapY, 0, seed);
            buffer->vec[y * width + x] = value;
        }
    }
}

PHP_METHOD(GL_Noise, ridgeFill2D)
{
    zval *buffer_zval;
    zend_long width, height, octaves = 6;
    double scale, offsetX = 0, offsetY = 0, lacunarity = 2.0, gain = 0.5, offset = 1.0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Olld|dddddll", &buffer_zval, phpglfw_get_buffer_glfloat_ce(), &width, &height, &scale, &offsetX, &offsetY, &lacunarity, &gain, &offset, &octaves) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_buffer_glfloat_object *buffer = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(buffer_zval));

    if (cvector_size(buffer->vec) < width * height) {
        cvector_reserve(buffer->vec, width * height);
        cvector_fill(buffer->vec, width * height, 0.0f);
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double nx = (double) x / width - 0.5;
            double ny = (double) y / height - 0.5;
            float value = stb_perlin_ridge_noise3(nx * scale + offsetX, ny * scale + offsetY, 0, lacunarity, gain, offset, octaves);
            buffer->vec[y * width + x] = value;
        }
    }
}

PHP_METHOD(GL_Noise, fbmFill2D)
{
    zval *buffer_zval;
    zend_long width, height, octaves = 6;
    double scale, offsetX = 0, offsetY = 0, lacunarity = 2.0, gain = 0.5;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Olld|ddddl", &buffer_zval, phpglfw_get_buffer_glfloat_ce(), &width, &height, &scale, &offsetX, &offsetY, &lacunarity, &gain, &octaves) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_buffer_glfloat_object *buffer = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(buffer_zval));

    if (cvector_size(buffer->vec) < width * height) {
        cvector_reserve(buffer->vec, width * height);
        cvector_fill(buffer->vec, width * height, 0.0f);
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double nx = (double) x / width - 0.5;
            double ny = (double) y / height - 0.5;
            float value = stb_perlin_fbm_noise3(nx * scale + offsetX, ny * scale + offsetY, 0, lacunarity, gain, octaves);
            buffer->vec[y * width + x] = value;
        }
    }
}

PHP_METHOD(GL_Noise, turbulenceFill2D)
{
    zval *buffer_zval;
    zend_long width, height, octaves = 6;
    double scale, offsetX = 0, offsetY = 0, lacunarity = 2.0, gain = 0.5;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Olld|ddddl", &buffer_zval, phpglfw_get_buffer_glfloat_ce(), &width, &height, &scale, &offsetX, &offsetY, &lacunarity, &gain, &octaves) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_buffer_glfloat_object *buffer = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(buffer_zval));

    if (cvector_size(buffer->vec) < width * height) {
        cvector_reserve(buffer->vec, width * height);
        cvector_fill(buffer->vec, width * height, 0.0f);
    }

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            double nx = (double) x / width - 0.5;
            double ny = (double) y / height - 0.5;
            float value = stb_perlin_turbulence_noise3(nx * scale + offsetX, ny * scale + offsetY, 0, lacunarity, gain, octaves);
            buffer->vec[y * width + x] = value;
        }
    }
}

// basically the same as ridgeFill2D but we use a distance function to create a island shape
PHP_METHOD(GL_Noise, islandFill2D)
{
    zval *buffer_zval;
    zend_long width, height, octaves = 6;
    double scale = 1.0, lacunarity = 2.0, gain = 0.5, islandmix = 0.7, z = 0.0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Oll|dddddl", &buffer_zval, phpglfw_get_buffer_glfloat_ce(), &width, &height, &z, &scale, &islandmix, &lacunarity, &gain, &octaves) == FAILURE) {
        RETURN_THROWS();
    }

    float fscale = scale;
    float fmix = islandmix;

    phpglfw_buffer_glfloat_object *buffer = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(buffer_zval));

    if (cvector_size(buffer->vec) < width * height) {
        cvector_reserve(buffer->vec, width * height);
        cvector_fill(buffer->vec, width * height, 0.0f);
    }

    float cx = width / 2.0;
    float cy = height / 2.0;
    float max_dist = sqrtf(cx * cx + cy * cy);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float dx = cx - x;
            float dy = cy - y;
            float dist = sqrtf(dx * dx + dy * dy);
            float dist_factor = 1.0f - (dist / max_dist);
            dist_factor = powf(dist_factor, fmix);

            double nx = (double)x / width - 0.5;
            double ny = (double)y / height - 0.5;
            float noise = stb_perlin_ridge_noise3(nx * fscale, ny * fscale, z, lacunarity, gain, 1.0, octaves);
            float value = noise * dist_factor;

            buffer->vec[y * width + x] = value;
        }
    }
}


void phpglfw_register_texture_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;
    
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Texture\\Texture2D", class_GL_Texture_Texture2D_methods);
    phpglfw_texture2d_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_texture2d_ce->create_object =  phpglfw_texture2d_create_handler;

    zend_declare_class_constant_long(phpglfw_texture2d_ce, "CHANNEL_R", strlen("CHANNEL_R"), 1);
    zend_declare_class_constant_long(phpglfw_texture2d_ce, "CHANNEL_GRAY", strlen("CHANNEL_GRAY"), 1);
    zend_declare_class_constant_long(phpglfw_texture2d_ce, "CHANNEL_RG", strlen("CHANNEL_RG"), 2);
    zend_declare_class_constant_long(phpglfw_texture2d_ce, "CHANNEL_GRAY_ALPHA", strlen("CHANNEL_GRAY_ALPHA"), 2);
    zend_declare_class_constant_long(phpglfw_texture2d_ce, "CHANNEL_RGB", strlen("CHANNEL_RGB"), 3);
    zend_declare_class_constant_long(phpglfw_texture2d_ce, "CHANNEL_RGBA", strlen("CHANNEL_RGBA"), 4);

    memcpy(&phpglfw_texture2d_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_texture2d_handlers.offset = XtOffsetOf(phpglfw_texture2d_object, std);
    phpglfw_texture2d_handlers.free_obj = phpglfw_texture2d_free_handler;
    phpglfw_texture2d_handlers.get_debug_info = phpglfw_texture2d_debug_info_handler;

    // register a noise class for the perlin noise functions
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Noise", class_GL_Noise_methods);
    zend_register_internal_class(&tmp_ce);
}