/**
 * PHP-glfw 
 * 
 * Extension: GL Textures
 *
 * Copyright (c) 2018-2023 Mario Döring
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

zend_class_entry *phpglfw_texture2d_ce; 

zend_class_entry *phpglfw_get_texture_texture2d_ce() {
    return phpglfw_texture2d_ce;
}

zend_always_inline phpglfw_texture2d_object* phpglfw_texture2d_objectptr_from_zobj_p(zend_object* obj)
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
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &path, &path_size) == FAILURE) {
        RETURN_THROWS();
    }

    object_init_ex(return_value, phpglfw_get_texture_texture2d_ce());
    phpglfw_texture2d_object *intern = phpglfw_texture2d_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    phpglfw_buffer_glubyte_object *buffer = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(&intern->buffer_zval));

    stbi_set_flip_vertically_on_load(1);

    unsigned char *data = stbi_load(path, &intern->width, &intern->height, &intern->channels, 0);
    size_t buffersize;
    if (data == NULL) {
        zend_throw_error(NULL, "Failed to load image from disk '%s'.", path);
        return;
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
    stbi_write_jpg(path, intern->width, intern->height, intern->channels, buffer->vec, 100);
}

void phpglfw_register_texture_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;
    
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Texture\\Texture2D", class_GL_Texture_Texture2D_methods);
    phpglfw_texture2d_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_texture2d_ce->create_object =  phpglfw_texture2d_create_handler;

    memcpy(&phpglfw_texture2d_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_texture2d_handlers.offset = XtOffsetOf(phpglfw_texture2d_object, std);
    phpglfw_texture2d_handlers.free_obj = phpglfw_texture2d_free_handler;
    phpglfw_texture2d_handlers.get_debug_info = phpglfw_texture2d_debug_info_handler;
}