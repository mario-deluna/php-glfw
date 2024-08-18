/**
 * PHP-glfw 
 * 
 * Extension: GL Math
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
#include "phpglfw_vg.h"
#include "phpglfw_texture.h"
#include "phpglfw_math.h"
#include "phpglfw_buffer.h"

#include "phpglfw_arginfo.h"

#include "php.h"
#include "Zend/zend_smart_str.h"
#include "ext/standard/info.h"
#include "ext/standard/php_var.h"

#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl.h"

#define DEFINE_STATIC_VGCOLOR_METHOD(name, r, g, b, a) \
    PHP_METHOD(GL_VectorGraphics_VGColor, name) \
    { \
        object_init_ex(return_value, phpglfw_get_vg_vgcolor_ce()); \
        phpglfw_vgcolor_object *color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(return_value)); \
        color->nvgcolor = nvgRGBAf(r, g, b, a); \
    }

zend_class_entry *phpglfw_vgcontext_ce;
zend_class_entry *phpglfw_vgpaint_ce;
zend_class_entry *phpglfw_vgimage_ce;
zend_class_entry *phpglfw_vgcolor_ce;

zend_class_entry *phpglfw_vgalign_ce;

zend_class_entry *phpglfw_get_vg_vgcontext_ce() {
    return phpglfw_vgcontext_ce;
}

zend_class_entry *phpglfw_get_vg_vgpaint_ce() {
    return phpglfw_vgpaint_ce;
}

zend_class_entry *phpglfw_get_vg_vgimage_ce() {
    return phpglfw_vgimage_ce;
}

zend_class_entry *phpglfw_get_vg_vgcolor_ce() {
    return phpglfw_vgcolor_ce;
}

zend_always_inline phpglfw_vgcontext_object* phpglfw_vgcontext_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_vgcontext_object *) ((char *) (obj) - XtOffsetOf(phpglfw_vgcontext_object, std));
}

zend_always_inline phpglfw_vgpaint_object* phpglfw_vgpaint_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_vgpaint_object *) ((char *) (obj) - XtOffsetOf(phpglfw_vgpaint_object, std));
}

zend_always_inline phpglfw_vgimage_object* phpglfw_vgimage_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_vgimage_object *) ((char *) (obj) - XtOffsetOf(phpglfw_vgimage_object, std));
}

zend_always_inline phpglfw_vgcolor_object* phpglfw_vgcolor_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_vgcolor_object *) ((char *) (obj) - XtOffsetOf(phpglfw_vgcolor_object, std));
}

static zend_object_handlers phpglfw_vgcontext_handlers;
static zend_object_handlers phpglfw_vgpaint_handlers;
static zend_object_handlers phpglfw_vgimage_handlers;
static zend_object_handlers phpglfw_vgcolor_handlers;

/**
 * VGColor
 * 
 * ----------------------------------------------------------------------------
 */
zend_object *phpglfw_vgcolor_create_handler(zend_class_entry *class_type)
{
    phpglfw_vgcolor_object *intern;
    intern = zend_object_alloc(sizeof(phpglfw_vgcolor_object), class_type);

    intern->nvgcolor.rgba[0] = 0.0f;
    intern->nvgcolor.rgba[1] = 0.0f;
    intern->nvgcolor.rgba[2] = 0.0f;
    intern->nvgcolor.rgba[3] = 0.0f;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &phpglfw_vgcolor_handlers;

    return &intern->std;
}

static void phpglfw_vgcolor_free_handler(zend_object *object)
{
    phpglfw_vgcolor_object *intern = phpglfw_vgcolor_objectptr_from_zobj_p(object);

    zend_object_std_dtor(&intern->std);
}

static int phpglfw_vgcolor_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_vgcolor_object *obj_ptr = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(object));

    smart_str buf = {0};
    zval zv;
    php_serialize_data_t serialize_data;

    PHP_VAR_SERIALIZE_INIT(serialize_data);

    ZVAL_DOUBLE(&zv, obj_ptr->nvgcolor.rgba[0]);
    php_var_serialize(&buf, &zv, &serialize_data);
    ZVAL_DOUBLE(&zv, obj_ptr->nvgcolor.rgba[1]);
    php_var_serialize(&buf, &zv, &serialize_data);
    ZVAL_DOUBLE(&zv, obj_ptr->nvgcolor.rgba[2]);
    php_var_serialize(&buf, &zv, &serialize_data);
    ZVAL_DOUBLE(&zv, obj_ptr->nvgcolor.rgba[3]);
    php_var_serialize(&buf, &zv, &serialize_data);

    PHP_VAR_SERIALIZE_DESTROY(serialize_data);
    *buffer = (unsigned char *) estrndup(ZSTR_VAL(buf.s), ZSTR_LEN(buf.s));
    *buf_len = ZSTR_LEN(buf.s);
    zend_string_release_ex(buf.s, 0);

    return SUCCESS;
}

int phpglfw_vgcolor_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    const unsigned char *buf_ptr = buf;
    const unsigned char *buf_end = buf + buf_len;
    zval *zv;
    php_unserialize_data_t unserialize_data;
    
    PHP_VAR_UNSERIALIZE_INIT(unserialize_data);

    object_init_ex(object, phpglfw_vgcolor_ce);
    phpglfw_vgcolor_object *obj = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(object));

    for (int i = 0; i < 4; i++) {
        zv = var_tmp_var(&unserialize_data);
        if (!php_var_unserialize(zv, &buf_ptr, buf_end, &unserialize_data) || Z_TYPE_P(zv) != IS_DOUBLE) {
            zend_throw_error(NULL, "Could not unserialize vector element");
            zend_object_std_dtor(&obj->std);
            efree(obj);
            PHP_VAR_UNSERIALIZE_DESTROY(unserialize_data);
            return FAILURE;
        }
        obj->nvgcolor.rgba[i] = Z_DVAL_P(zv);
    }

    PHP_VAR_UNSERIALIZE_DESTROY(unserialize_data);
    return SUCCESS;
}

static void debug_info_nvgcolor_to_hs(HashTable *ht, NVGcolor *color)
{
    zval zv;

    ZVAL_DOUBLE(&zv, color->r);
    zend_hash_str_update(ht, "r", sizeof("r") - 1, &zv);
    ZVAL_DOUBLE(&zv, color->g);
    zend_hash_str_update(ht, "g", sizeof("g") - 1, &zv);
    ZVAL_DOUBLE(&zv, color->b);
    zend_hash_str_update(ht, "b", sizeof("b") - 1, &zv);
    ZVAL_DOUBLE(&zv, color->a);
    zend_hash_str_update(ht, "a", sizeof("a") - 1, &zv);
}

static HashTable *phpglfw_vgcolor_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_vgcolor_object *obj_ptr = phpglfw_vgcolor_objectptr_from_zobj_p(object);
    HashTable *ht;

    ht = zend_new_array(4);
    *is_temp = 1;

    debug_info_nvgcolor_to_hs(ht, &obj_ptr->nvgcolor);

    return ht;
}

static zval *phpglfw_vgcolor_read_prop_handler(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) 
{
    phpglfw_vgcolor_object *obj_ptr = phpglfw_vgcolor_objectptr_from_zobj_p(object);

	if ((type != BP_VAR_R && type != BP_VAR_IS)) {
		zend_throw_error(NULL, "GL\\VectorGraphics\\VGColor properties are virtual and cannot be referenced.");
		rv = &EG( uninitialized_zval );
	} else {

        if (zend_string_equals_literal(member, "r")) {
		    ZVAL_DOUBLE(rv, obj_ptr->nvgcolor.rgba[0]);
        }
        else if (zend_string_equals_literal(member, "g")) {
		    ZVAL_DOUBLE(rv, obj_ptr->nvgcolor.rgba[1]);
        }
        else if (zend_string_equals_literal(member, "b")) {
		    ZVAL_DOUBLE(rv, obj_ptr->nvgcolor.rgba[2]);
        }
        else if (zend_string_equals_literal(member, "a")) {
		    ZVAL_DOUBLE(rv, obj_ptr->nvgcolor.rgba[3]);
        }
        else {
            ZVAL_NULL(rv);
        }
	}

	return rv;
}

static zval *phpglfw_vgcolor_write_prop_handler(zend_object *object, zend_string *member, zval *value, void **cache_slot) 
{
    if (Z_TYPE_P(value) == IS_LONG) {
        convert_to_double(value);
    }
    
    if (Z_TYPE_P(value) != IS_DOUBLE) {
		zend_throw_error(NULL, "GL\\VectorGraphics\\VGColor properties can only be of type 'float'.");
        return value;
    }
    else {
        phpglfw_vgcolor_object *obj_ptr = phpglfw_vgcolor_objectptr_from_zobj_p(object);

        if (zend_string_equals_literal(member, "r")) {
		    obj_ptr->nvgcolor.rgba[0] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "g")) {
		    obj_ptr->nvgcolor.rgba[1] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "b")) {
		    obj_ptr->nvgcolor.rgba[2] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "a")) {
		    obj_ptr->nvgcolor.rgba[3] = Z_DVAL_P(value); 
        }
        else {
		    zend_throw_error(NULL, "GL\\VectorGraphics\\VGColor trying to write into a invalid property.");
        }
    }

	return value;
}

PHP_METHOD(GL_VectorGraphics_VGColor, __construct)
{
    double r, g, b, a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &r, &g, &b, &a) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgcolor_object *intern = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    intern->nvgcolor = nvgRGBAf(r, g, b, a);
}

PHP_METHOD(GL_VectorGraphics_VGColor, rgb)
{
    double r, g, b;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddd", &r, &g, &b) == FAILURE) {
        RETURN_THROWS();
    }

    object_init_ex(return_value, phpglfw_get_vg_vgcolor_ce());
    phpglfw_vgcolor_object *color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    color->nvgcolor = nvgRGBAf(r, g, b, 1.0f);
}

PHP_METHOD(GL_VectorGraphics_VGColor, rgba)
{
    double r, g, b, a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &r, &g, &b, &a) == FAILURE) {
        RETURN_THROWS();
    }

    object_init_ex(return_value, phpglfw_get_vg_vgcolor_ce());
    phpglfw_vgcolor_object *color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    color->nvgcolor = nvgRGBAf(r, g, b, a);
}

PHP_METHOD(GL_VectorGraphics_VGColor, hsl)
{
    double h, s, l;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddd", &h, &s, &l) == FAILURE) {
        RETURN_THROWS();
    }

    object_init_ex(return_value, phpglfw_get_vg_vgcolor_ce());
    phpglfw_vgcolor_object *color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    color->nvgcolor = nvgHSLA(h, s, l, 255);
}

PHP_METHOD(GL_VectorGraphics_VGColor, hsla)
{
    double h, s, l, a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &h, &s, &l, &a) == FAILURE) {
        RETURN_THROWS();
    }

    // nanovg expects the alpha value to be a unsigned char here for some reason
    // it is internally then converted back to a float -,- 
    // i could fix this, but im lazy
    unsigned char alpha = (unsigned char)(a * 255.0f);

    object_init_ex(return_value, phpglfw_get_vg_vgcolor_ce());
    phpglfw_vgcolor_object *color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    color->nvgcolor = nvgHSLA(h, s, l, alpha);
}

PHP_METHOD(GL_VectorGraphics_VGColor, irgb)
{
    zend_long r, g, b;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &r, &g, &b) == FAILURE) {
        RETURN_THROWS();
    }

    object_init_ex(return_value, phpglfw_get_vg_vgcolor_ce());
    phpglfw_vgcolor_object *color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    color->nvgcolor = nvgRGBA(r, g, b, 255);
}

PHP_METHOD(GL_VectorGraphics_VGColor, irgba)
{
    zend_long r, g, b, a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &r, &g, &b, &a) == FAILURE) {
        RETURN_THROWS();
    }

    object_init_ex(return_value, phpglfw_get_vg_vgcolor_ce());
    phpglfw_vgcolor_object *color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    color->nvgcolor = nvgRGBA(r, g, b, a);
}

PHP_METHOD(GL_VectorGraphics_VGColor, hex)
{
    const char *hex;
    size_t hex_len;
    size_t hex_off = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &hex, &hex_len) == FAILURE) {
        RETURN_THROWS();
    }

    // allocate memory for the 8 character hex string (9th is for the null terminator)
    char hex_str[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    // remove the hash if it exists
    if (hex[0] == '#') {
        hex_off = 1;
    }

    // if the hex string is only 3 characters long, we need to expand it
    // Note: I know there is a smarter way to do this, but i had a memory bug
    // this somehow fixed it and i could not be bothered to investigate further
    if (hex_len - hex_off == 3) {
        hex_str[0] = hex[0+hex_off];
        hex_str[1] = hex[0+hex_off];
        hex_str[2] = hex[1+hex_off];
        hex_str[3] = hex[1+hex_off];
        hex_str[4] = hex[2+hex_off];
        hex_str[5] = hex[2+hex_off];
        hex_str[6] = 'f';
        hex_str[7] = 'f';
    }
    // 6 characters long
    else if (hex_len - hex_off == 6) {
        hex_str[0] = hex[0+hex_off];
        hex_str[1] = hex[1+hex_off];
        hex_str[2] = hex[2+hex_off];
        hex_str[3] = hex[3+hex_off];
        hex_str[4] = hex[4+hex_off];
        hex_str[5] = hex[5+hex_off];
        hex_str[6] = 'f';
        hex_str[7] = 'f';
    }
    else if (hex_len - hex_off == 8) {
        hex_str[0] = hex[0+hex_off];
        hex_str[1] = hex[1+hex_off];
        hex_str[2] = hex[2+hex_off];
        hex_str[3] = hex[3+hex_off];
        hex_str[4] = hex[4+hex_off];
        hex_str[5] = hex[5+hex_off];
        hex_str[6] = hex[6+hex_off];
        hex_str[7] = hex[7+hex_off];
    }
    else {
        zend_throw_error(NULL, "Invalid hex string length, must be 3, 6 or 8 characters long.");
        RETURN_THROWS();
    }

    // convert the hex string to a long
    long color = strtol(hex_str, NULL, 16);

    // extract rgba values
    float r = ((color >> 24) & 0xFF) / 255.0f;
    float g = ((color >> 16) & 0xFF) / 255.0f;
    float b = ((color >> 8) & 0xFF) / 255.0f;
    float a = (color & 0xFF) / 255.0f;

    object_init_ex(return_value, phpglfw_get_vg_vgcolor_ce());
    phpglfw_vgcolor_object *vgcolor = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    vgcolor->nvgcolor = nvgRGBAf(r, g, b, a);
}

DEFINE_STATIC_VGCOLOR_METHOD(red, 1.0f, 0.0f, 0.0f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(green, 0.0f, 1.0f, 0.0f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(blue, 0.0f, 0.0f, 1.0f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(white, 1.0f, 1.0f, 1.0f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(black, 0.0f, 0.0f, 0.0f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(transparent, 0.0f, 0.0f, 0.0f, 0.0f);
DEFINE_STATIC_VGCOLOR_METHOD(yellow, 1.0f, 1.0f, 0.0f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(cyan, 0.0f, 1.0f, 1.0f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(magenta, 1.0f, 0.0f, 1.0f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(orange, 1.0f, 0.65f, 0.0f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(pink, 0.95f, 0.4f, 0.7f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(purple, 0.5f, 0.0f, 0.5f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(brown, 0.5f, 0.3f, 0.0f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(gray, 0.5f, 0.5f, 0.5f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(darkGray, 0.33f, 0.33f, 0.33f, 1.0f);
DEFINE_STATIC_VGCOLOR_METHOD(lightGray, 0.75f, 0.75f, 0.75f, 1.0f);


PHP_METHOD(GL_VectorGraphics_VGColor, random)
{
    object_init_ex(return_value, phpglfw_get_vg_vgcolor_ce());
    phpglfw_vgcolor_object *color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    color->nvgcolor = nvgRGBAf((float)rand()/RAND_MAX, (float)rand()/RAND_MAX, (float)rand()/RAND_MAX, 1.0f);
}

PHP_METHOD(GL_VectorGraphics_VGColor, randomGray)
{
    object_init_ex(return_value, phpglfw_get_vg_vgcolor_ce());
    phpglfw_vgcolor_object *color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    float grayValue = (float)rand()/RAND_MAX;
    color->nvgcolor = nvgRGBAf(grayValue, grayValue, grayValue, 1.0f);
}

PHP_METHOD(GL_VectorGraphics_VGColor, getHSLA)
{
    phpglfw_vgcolor_object *intern = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_math_vec4_ce());
    phpglfw_math_vec4_object *vec4 = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    nvgColorToHSLA(intern->nvgcolor, &vec4->data[0], &vec4->data[1], &vec4->data[2], &vec4->data[3]);
}

PHP_METHOD(GL_VectorGraphics_VGColor, getHSL)
{
    phpglfw_vgcolor_object *intern = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_math_vec3_ce());
    phpglfw_math_vec3_object *vec3 = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    float throwaway;
    nvgColorToHSLA(intern->nvgcolor, &vec3->data[0], &vec3->data[1], &vec3->data[2], &throwaway);
}

PHP_METHOD(GL_VectorGraphics_VGColor, getVec4)
{
    phpglfw_vgcolor_object *intern = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_math_vec4_ce());
    phpglfw_math_vec4_object *vec4 = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    vec4->data[0] = intern->nvgcolor.r;
    vec4->data[1] = intern->nvgcolor.g;
    vec4->data[2] = intern->nvgcolor.b;
    vec4->data[3] = intern->nvgcolor.a;
}

PHP_METHOD(GL_VectorGraphics_VGColor, getVec3)
{
    phpglfw_vgcolor_object *intern = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_math_vec3_ce());
    phpglfw_math_vec3_object *vec3 = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    vec3->data[0] = intern->nvgcolor.r;
    vec3->data[1] = intern->nvgcolor.g;
    vec3->data[2] = intern->nvgcolor.b;
}


// public function darken(float $amount) : VGColor {}
// public function lighten(float $amount) : VGColor {}
// public function saturate(float $amount) : VGColor {}
// public function desaturate(float $amount) : VGColor {}
// public function invert() : VGColor {}

void adjust_hsl_l(INTERNAL_FUNCTION_PARAMETERS, double amount)
{
    phpglfw_vgcolor_object *intern = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_vg_vgcolor_ce());
    phpglfw_vgcolor_object *color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    float h, s, l, a;
    nvgColorToHSLA(intern->nvgcolor, &h, &s, &l, &a);
    l += amount;

    color->nvgcolor = nvgHSL(h, s, l);
    color->nvgcolor.a = a; // skip the conversion to unsigned char
}

PHP_METHOD(GL_VectorGraphics_VGColor, darken)
{
    double amount;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &amount) == FAILURE) {
        RETURN_THROWS();
    }

    adjust_hsl_l(INTERNAL_FUNCTION_PARAM_PASSTHRU, -amount);
}

PHP_METHOD(GL_VectorGraphics_VGColor, lighten)
{
    double amount;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "d", &amount) == FAILURE) {
        RETURN_THROWS();
    }

    adjust_hsl_l(INTERNAL_FUNCTION_PARAM_PASSTHRU, amount);
}

PHP_METHOD(GL_VectorGraphics_VGColor, invert)
{
    phpglfw_vgcolor_object *intern = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_vg_vgcolor_ce());
    phpglfw_vgcolor_object *color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    color->nvgcolor = nvgRGBAf(1.0f - intern->nvgcolor.r, 1.0f - intern->nvgcolor.g, 1.0f - intern->nvgcolor.b, intern->nvgcolor.a);
}

/**
 * VGPaint 
 * 
 * ----------------------------------------------------------------------------
 */
zend_object *phpglfw_vgpaint_create_handler(zend_class_entry *class_type)
{
    phpglfw_vgpaint_object *intern;
    intern = zend_object_alloc(sizeof(phpglfw_vgpaint_object), class_type);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &phpglfw_vgpaint_handlers;

    return &intern->std;
}

static void phpglfw_vgpaint_free_handler(zend_object *object)
{
    phpglfw_vgpaint_object *intern = phpglfw_vgpaint_objectptr_from_zobj_p(object);

    zend_object_std_dtor(&intern->std);
}

static HashTable *phpglfw_vgpaint_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_vgpaint_object *obj_ptr = phpglfw_vgpaint_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(4);

    ZVAL_DOUBLE(&zv, obj_ptr->nvgpaint.radius);
    zend_hash_str_update(ht, "radius", sizeof("radius") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->nvgpaint.feather);
    zend_hash_str_update(ht, "feather", sizeof("feather") - 1, &zv);

    // create a new array for the inner color
    HashTable *inner_color_ht = zend_new_array(4);
    debug_info_nvgcolor_to_hs(inner_color_ht, &obj_ptr->nvgpaint.innerColor);
    ZVAL_ARR(&zv, inner_color_ht);
    zend_hash_str_update(ht, "innerColor", sizeof("innerColor") - 1, &zv);

    // create a new array for the outer color
    HashTable *outer_color_ht = zend_new_array(4);
    debug_info_nvgcolor_to_hs(outer_color_ht, &obj_ptr->nvgpaint.outerColor);
    ZVAL_ARR(&zv, outer_color_ht);
    zend_hash_str_update(ht, "outerColor", sizeof("outerColor") - 1, &zv);

    // image handle
    ZVAL_LONG(&zv, obj_ptr->nvgpaint.image);
    zend_hash_str_update(ht, "image", sizeof("image") - 1, &zv);

    return ht;
}

/**
 * VGImage
 * 
 * ----------------------------------------------------------------------------
 */
zend_object *phpglfw_vgimage_create_handler(zend_class_entry *class_type)
{
    phpglfw_vgimage_object *intern;
    intern = zend_object_alloc(sizeof(phpglfw_vgimage_object), class_type);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &phpglfw_vgimage_handlers;

    return &intern->std;
}

static void phpglfw_vgimage_free_handler(zend_object *object)
{
    phpglfw_vgimage_object *intern = phpglfw_vgimage_objectptr_from_zobj_p(object);

    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(GL_VectorGraphics_VGImage, makePaint)
{
    double cx, cy, w, h, angle = 0.0, alpha = 1.0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd|dd", &cx, &cy, &w, &h, &angle, &alpha) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgimage_object *intern = phpglfw_vgimage_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_vg_vgpaint_ce());
    phpglfw_vgpaint_object *paint = phpglfw_vgpaint_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    // nvgImagePattern doesnt actually require the nvcontext so we can pass NULL
    paint->nvgpaint = nvgImagePattern(NULL, cx, cy, w, h, angle, intern->nvgimage_handle, alpha);
}

PHP_METHOD(GL_VectorGraphics_VGImage, makePaintCentered)
{
    double cx, cy, w, h, angle = 0.0, alpha = 1.0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd|dd", &cx, &cy, &w, &h, &angle, &alpha) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgimage_object *intern = phpglfw_vgimage_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_vg_vgpaint_ce());
    phpglfw_vgpaint_object *paint = phpglfw_vgpaint_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    paint->nvgpaint = nvgImagePatternCentered(NULL, cx, cy, w, h, angle, intern->nvgimage_handle, alpha);
}

/**
 * VGContext
 * 
 * ----------------------------------------------------------------------------
 */
zend_object *phpglfw_vgcontext_create_handler(zend_class_entry *class_type)
{
    phpglfw_vgcontext_object *intern;
    intern = zend_object_alloc(sizeof(phpglfw_vgcontext_object), class_type);

    intern->nvgctx = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &phpglfw_vgcontext_handlers;

    return &intern->std;
}


static void phpglfw_vgcontext_free_handler(zend_object *object)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(object);

    if (intern->nvgctx != NULL) {
	    nvgDeleteGL3(intern->nvgctx);
        intern->nvgctx = NULL;
    }

    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(GL_VectorGraphics_VGContext, linearGradient)
{
    double sx, sy, ex, ey;
    zval *icol, *ocol;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddddOO", &sx, &sy, &ex, &ey, &icol, phpglfw_get_vg_vgcolor_ce(), &ocol, phpglfw_get_vg_vgcolor_ce()) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgcolor_object *icol_ptr = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(icol));
    phpglfw_vgcolor_object *ocol_ptr = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(ocol));
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_vg_vgpaint_ce());
    phpglfw_vgpaint_object *paint = phpglfw_vgpaint_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    paint->nvgpaint = nvgLinearGradient(intern->nvgctx, sx, sy, ex, ey, icol_ptr->nvgcolor, ocol_ptr->nvgcolor);
}

PHP_METHOD(GL_VectorGraphics_VGContext, boxGradient)
{
    double x, y, w, h, r, f;
    zval *icol, *ocol;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddddddOO", &x, &y, &w, &h, &r, &f, &icol, phpglfw_get_vg_vgcolor_ce(), &ocol, phpglfw_get_vg_vgcolor_ce()) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgcolor_object *icol_ptr = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(icol));
    phpglfw_vgcolor_object *ocol_ptr = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(ocol));
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_vg_vgpaint_ce());
    phpglfw_vgpaint_object *paint = phpglfw_vgpaint_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    paint->nvgpaint = nvgBoxGradient(intern->nvgctx, x, y, w, h, r, f, icol_ptr->nvgcolor, ocol_ptr->nvgcolor);
}

PHP_METHOD(GL_VectorGraphics_VGContext, radialGradient)
{
    double cx, cy, inr, outr;
    zval *icol, *ocol;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddddOO", &cx, &cy, &inr, &outr, &icol, phpglfw_get_vg_vgcolor_ce(), &ocol, phpglfw_get_vg_vgcolor_ce()) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgcolor_object *icol_ptr = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(icol));
    phpglfw_vgcolor_object *ocol_ptr = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(ocol));
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_vg_vgpaint_ce());
    phpglfw_vgpaint_object *paint = phpglfw_vgpaint_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    paint->nvgpaint = nvgRadialGradient(intern->nvgctx, cx, cy, inr, outr, icol_ptr->nvgcolor, ocol_ptr->nvgcolor);
}

PHP_METHOD(GL_VectorGraphics_VGContext, imageFromTexture)
{
    zval *texture;
    zend_long repeat = PHPGLFW_VG_REPEAT_NONE;
    zend_long filter = PHPGLFW_VG_FILTER_LINEAR;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O|ll", &texture, phpglfw_get_texture_texture2d_ce(), &repeat, &filter) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_texture2d_object *texture_ptr = phpglfw_texture2d_objectptr_from_zobj_p(Z_OBJ_P(texture));
    phpglfw_buffer_glubyte_object *buffer = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(&texture_ptr->buffer_zval));
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_vg_vgimage_ce());
    phpglfw_vgimage_object *image = phpglfw_vgimage_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    
    // ensure the texture has 4 channels
    if (texture_ptr->channels != 4) {
        zend_throw_error(NULL, "The texture for the VGImage must have 4 channels");
    }

    // build the NVGimageFlags
    int image_flags = 0;
    if (repeat == PHPGLFW_VG_REPEAT_X) {
        image_flags |= NVG_IMAGE_REPEATX;
    } else if (repeat == PHPGLFW_VG_REPEAT_Y) {
        image_flags |= NVG_IMAGE_REPEATY;
    } else if (repeat == PHPGLFW_VG_REPEAT_XY) {
        image_flags |= NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY;
    }

    // apply nearest filtering (default is linear)
    if (filter == PHPGLFW_VG_FILTER_NEAREST) {
        image_flags |= NVG_IMAGE_NEAREST;
    }

    image->nvgimage_handle = nvgCreateImageRGBA(intern->nvgctx, texture_ptr->width, texture_ptr->height, image_flags, buffer->vec);
}

PHP_METHOD(GL_VectorGraphics_VGContext, imageFromHandle)
{
    zend_long texture, w, h;
    zend_long repeat = PHPGLFW_VG_REPEAT_NONE;
    zend_long filter = PHPGLFW_VG_FILTER_LINEAR;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll|ll", &texture, &w, &h, &repeat, &filter) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_vg_vgimage_ce());
    phpglfw_vgimage_object *image = phpglfw_vgimage_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    // build the NVGimageFlags
    int image_flags = 0;
    if (repeat == PHPGLFW_VG_REPEAT_X) {
        image_flags |= NVG_IMAGE_REPEATX;
    } else if (repeat == PHPGLFW_VG_REPEAT_Y) {
        image_flags |= NVG_IMAGE_REPEATY;
    } else if (repeat == PHPGLFW_VG_REPEAT_XY) {
        image_flags |= NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY;
    }

    // apply nearest filtering (default is linear)
    if (filter == PHPGLFW_VG_FILTER_NEAREST) {
        image_flags |= NVG_IMAGE_NEAREST;
    }

    image->nvgimage_handle = nvglCreateImageFromHandleGL3(intern->nvgctx, texture, w, h, image_flags);
}

PHP_METHOD(GL_VectorGraphics_VGContext, __construct)
{
    zval *obj;
    obj = getThis();
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // parse the flags from the constructor
    zend_long flags = 0;
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "|l", &flags) == FAILURE) {
		RETURN_THROWS();
	}

    // quick sanity check for the flags
    if (flags > (NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG)) {
        zend_throw_error(NULL, "Invalid flags for VGContext, must be a combination of VGContext::ANTIALIAS, VGContext::STENCIL_STROKES and VGContext::DEBUG");
        return;
    }

    intern->nvgctx = nvgCreateGL3(flags);
}

<?php foreach($ctxfunctions as $func): ?>
<?php echo $func->getCFunctionCommentBlock(); ?> 
PHP_METHOD(GL_VectorGraphics_VGContext, <?php echo $func->name; ?>)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

<?php echo tabulate($func->getFunctionImplementationBody()); ?>

}
<?php endforeach; ?>

PHP_METHOD(GL_VectorGraphics_VGContext, fillColori)
{
    zend_long r, g, b, a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &r, &g, &b, &a) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    nvgFillColor(intern->nvgctx, nvgRGBA(r, g, b, a));
}

PHP_METHOD(GL_VectorGraphics_VGContext, strokeColori)
{
    zend_long r, g, b, a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &r, &g, &b, &a) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    nvgStrokeColor(intern->nvgctx, nvgRGBA(r, g, b, a));
}

PHP_METHOD(GL_VectorGraphics_VGContext, fillColorVec4)
{
    zval *vec4;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec4, phpglfw_get_math_vec4_ce()) == FAILURE) {
        return;
    }

    phpglfw_math_vec4_object *vec4_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(vec4));
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgFillColor(intern->nvgctx, nvgRGBAf(vec4_ptr->data[0], vec4_ptr->data[1], vec4_ptr->data[2], vec4_ptr->data[3]));
}

PHP_METHOD(GL_VectorGraphics_VGContext, strokeColorVec4)
{
    zval *vec4;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec4, phpglfw_get_math_vec4_ce()) == FAILURE) {
        return;
    }

    phpglfw_math_vec4_object *vec4_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(vec4));
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgStrokeColor(intern->nvgctx, nvgRGBAf(vec4_ptr->data[0], vec4_ptr->data[1], vec4_ptr->data[2], vec4_ptr->data[3]));
}

PHP_METHOD(GL_VectorGraphics_VGContext, transformVec2)
{
    zval *vec2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec2, phpglfw_get_math_vec2_ce()) == FAILURE) {
        return;
    }

    phpglfw_math_vec2_object *vec2_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(vec2));
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    // construct a new vec2 object
    object_init_ex(return_value, phpglfw_get_math_vec2_ce());
    phpglfw_math_vec2_object *new_vec2_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    
    nvgTransformPointCurrent(intern->nvgctx, &new_vec2_ptr->data[0], &new_vec2_ptr->data[1], vec2_ptr->data[0], vec2_ptr->data[1]);
}

PHP_METHOD(GL_VectorGraphics_VGContext, transformPoint)
{
    double x, y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dd", &x, &y) == FAILURE) {
        return;
    }

    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    // construct a new vec2 object
    object_init_ex(return_value, phpglfw_get_math_vec2_ce());
    phpglfw_math_vec2_object *new_vec2_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    
    nvgTransformPointCurrent(intern->nvgctx, &new_vec2_ptr->data[0], &new_vec2_ptr->data[1], x, y);
}

void phpglfw_register_vg_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;
    
    // initialize and register the VectorGraphics Context class
    INIT_CLASS_ENTRY(tmp_ce, "GL\\VectorGraphics\\VGContext", class_GL_VectorGraphics_VGContext_methods);
    phpglfw_vgcontext_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_vgcontext_ce->create_object = phpglfw_vgcontext_create_handler;

    memcpy(&phpglfw_vgcontext_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_vgcontext_handlers.offset = XtOffsetOf(phpglfw_vgcontext_object, std);
    phpglfw_vgcontext_handlers.free_obj = phpglfw_vgcontext_free_handler;

    // register the VGContext constants
    zend_declare_class_constant_long(phpglfw_vgcontext_ce, "ANTIALIAS", strlen("ANTIALIAS"), NVG_ANTIALIAS);
    zend_declare_class_constant_long(phpglfw_vgcontext_ce, "STENCIL_STROKES", strlen("STENCIL_STROKES"), NVG_STENCIL_STROKES);
    zend_declare_class_constant_long(phpglfw_vgcontext_ce, "DEBUG", strlen("DEBUG"), NVG_DEBUG);

    // CCW and CW
    zend_declare_class_constant_long(phpglfw_vgcontext_ce, "CCW", strlen("CCW"), PHPGLFW_VG_CCW);
    zend_declare_class_constant_long(phpglfw_vgcontext_ce, "CW", strlen("CW"), PHPGLFW_VG_CW);

    // Solidity
    zend_declare_class_constant_long(phpglfw_vgcontext_ce, "SOLID", strlen("SOLID"), PHPGLFW_VG_SOLID);
    zend_declare_class_constant_long(phpglfw_vgcontext_ce, "HOLE", strlen("HOLE"), PHPGLFW_VG_HOLE);

    // LineCap
    zend_declare_class_constant_long(phpglfw_vgcontext_ce, "LINECAP_BUTT", strlen("LINECAP_BUTT"), PHPGLFW_VG_BUTT);
    zend_declare_class_constant_long(phpglfw_vgcontext_ce, "LINECAP_ROUND", strlen("LINECAP_ROUND"), PHPGLFW_VG_ROUND);
    zend_declare_class_constant_long(phpglfw_vgcontext_ce, "LINECAP_SQUARE", strlen("LINECAP_SQUARE"), PHPGLFW_VG_SQUARE);
    zend_declare_class_constant_long(phpglfw_vgcontext_ce, "LINEJOIN_BEVEL", strlen("LINEJOIN_BEVEL"), PHPGLFW_VG_BEVEL);
    zend_declare_class_constant_long(phpglfw_vgcontext_ce, "LINEJOIN_MITER", strlen("LINEJOIN_MITER"), PHPGLFW_VG_MITER);

    // initialize and register the VectorGraphics Color class
    INIT_CLASS_ENTRY(tmp_ce, "GL\\VectorGraphics\\VGColor", class_GL_VectorGraphics_VGColor_methods);
    phpglfw_vgcolor_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_vgcolor_ce->create_object = phpglfw_vgcolor_create_handler;
    phpglfw_vgcolor_ce->serialize = phpglfw_vgcolor_serialize_handler;
    phpglfw_vgcolor_ce->unserialize = phpglfw_vgcolor_unserialize_handler;

    memcpy(&phpglfw_vgcolor_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_vgcolor_handlers.offset = XtOffsetOf(phpglfw_vgcolor_object, std);
    phpglfw_vgcolor_handlers.free_obj = phpglfw_vgcolor_free_handler;
    phpglfw_vgcolor_handlers.get_debug_info = phpglfw_vgcolor_debug_info_handler;
    phpglfw_vgcolor_handlers.read_property = phpglfw_vgcolor_read_prop_handler;
    phpglfw_vgcolor_handlers.write_property = phpglfw_vgcolor_write_prop_handler;

    // initialize and register the VectorGraphics Image class
    INIT_CLASS_ENTRY(tmp_ce, "GL\\VectorGraphics\\VGImage", class_GL_VectorGraphics_VGImage_methods);
    phpglfw_vgimage_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_vgimage_ce->create_object = phpglfw_vgimage_create_handler;

    memcpy(&phpglfw_vgimage_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_vgimage_handlers.offset = XtOffsetOf(phpglfw_vgimage_object, std);
    phpglfw_vgimage_handlers.free_obj = phpglfw_vgimage_free_handler;

    zend_declare_class_constant_long(phpglfw_vgimage_ce, "REPEAT_NONE", strlen("REPEAT_NONE"), PHPGLFW_VG_REPEAT_NONE);
    zend_declare_class_constant_long(phpglfw_vgimage_ce, "REPEAT_X", strlen("REPEAT_X"), PHPGLFW_VG_REPEAT_X);
    zend_declare_class_constant_long(phpglfw_vgimage_ce, "REPEAT_Y", strlen("REPEAT_Y"), PHPGLFW_VG_REPEAT_Y);
    zend_declare_class_constant_long(phpglfw_vgimage_ce, "REPEAT_XY", strlen("REPEAT_XY"), PHPGLFW_VG_REPEAT_XY);

    zend_declare_class_constant_long(phpglfw_vgimage_ce, "FILTER_LINEAR", strlen("FILTER_LINEAR"), PHPGLFW_VG_FILTER_LINEAR);
    zend_declare_class_constant_long(phpglfw_vgimage_ce, "FILTER_NEAREST", strlen("FILTER_NEAREST"), PHPGLFW_VG_FILTER_NEAREST);

    // register a VGAlign class
    INIT_CLASS_ENTRY(tmp_ce, "GL\\VectorGraphics\\VGAlign", NULL);
    phpglfw_vgalign_ce = zend_register_internal_class(&tmp_ce);

    zend_declare_class_constant_long(phpglfw_vgalign_ce, "LEFT", strlen("LEFT"), NVG_ALIGN_LEFT);
    zend_declare_class_constant_long(phpglfw_vgalign_ce, "CENTER", strlen("CENTER"), NVG_ALIGN_CENTER);
    zend_declare_class_constant_long(phpglfw_vgalign_ce, "RIGHT", strlen("RIGHT"), NVG_ALIGN_RIGHT);

    zend_declare_class_constant_long(phpglfw_vgalign_ce, "TOP", strlen("TOP"), NVG_ALIGN_TOP);
    zend_declare_class_constant_long(phpglfw_vgalign_ce, "MIDDLE", strlen("MIDDLE"), NVG_ALIGN_MIDDLE);
    zend_declare_class_constant_long(phpglfw_vgalign_ce, "BOTTOM", strlen("BOTTOM"), NVG_ALIGN_BOTTOM);
    zend_declare_class_constant_long(phpglfw_vgalign_ce, "BASELINE", strlen("BASELINE"), NVG_ALIGN_BASELINE);


    // initialize and register the VectorGraphics Paint class
    INIT_CLASS_ENTRY(tmp_ce, "GL\\VectorGraphics\\VGPaint", class_GL_VectorGraphics_VGPaint_methods);
    phpglfw_vgpaint_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_vgpaint_ce->create_object = phpglfw_vgpaint_create_handler;

    memcpy(&phpglfw_vgpaint_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_vgpaint_handlers.offset = XtOffsetOf(phpglfw_vgpaint_object, std);
    phpglfw_vgpaint_handlers.free_obj = phpglfw_vgpaint_free_handler;
    phpglfw_vgpaint_handlers.get_debug_info = phpglfw_vgpaint_debug_info_handler;
}