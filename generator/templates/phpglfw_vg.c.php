/**
 * PHP-glfw 
 * 
 * Extension: GL Math
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

zend_class_entry *phpglfw_vgcontext_ce;
zend_class_entry *phpglfw_vgpaint_ce;
zend_class_entry *phpglfw_vgimage_ce;
zend_class_entry *phpglfw_vgcolor_ce;

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

PHP_METHOD(GL_VectorGraphics_VGColor, __construct)
{
    double r, g, b, a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &r, &g, &b, &a) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgcolor_object *intern = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    intern->nvgcolor = nvgRGBAf(r, g, b, a);
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

PHP_METHOD(GL_VectorGraphics_VGContext, __construct)
{
    zval *obj;
    obj = getThis();
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // parse the flags from the constructor
    int flags = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "|l", &flags) == FAILURE) {
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

    // initialize and register the VectorGraphics Color class
    INIT_CLASS_ENTRY(tmp_ce, "GL\\VectorGraphics\\VGColor", class_GL_VectorGraphics_VGColor_methods);
    phpglfw_vgcolor_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_vgcolor_ce->create_object = phpglfw_vgcolor_create_handler;

    memcpy(&phpglfw_vgcolor_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_vgcolor_handlers.offset = XtOffsetOf(phpglfw_vgcolor_object, std);
    phpglfw_vgcolor_handlers.free_obj = phpglfw_vgcolor_free_handler;
    phpglfw_vgcolor_handlers.get_debug_info = phpglfw_vgcolor_debug_info_handler;

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


    // initialize and register the VectorGraphics Paint class
    INIT_CLASS_ENTRY(tmp_ce, "GL\\VectorGraphics\\VGPaint", class_GL_VectorGraphics_VGPaint_methods);
    phpglfw_vgpaint_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_vgpaint_ce->create_object = phpglfw_vgpaint_create_handler;

    memcpy(&phpglfw_vgpaint_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_vgpaint_handlers.offset = XtOffsetOf(phpglfw_vgpaint_object, std);
    phpglfw_vgpaint_handlers.free_obj = phpglfw_vgpaint_free_handler;
    phpglfw_vgpaint_handlers.get_debug_info = phpglfw_vgpaint_debug_info_handler;
}