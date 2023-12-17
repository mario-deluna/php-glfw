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

/**
 * beginFrame
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, beginFrame)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double windowWidth;
    double windowHeight;
    double devicePixelRatio;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddd", &windowWidth, &windowHeight, &devicePixelRatio) == FAILURE) {
        return;
    }
    nvgBeginFrame(intern->nvgctx, windowWidth, windowHeight, devicePixelRatio);
}
/**
 * cancelFrame
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, cancelFrame)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgCancelFrame(intern->nvgctx);
}
/**
 * endFrame
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, endFrame)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgEndFrame(intern->nvgctx);
}
/**
 * globalCompositeOperation
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, globalCompositeOperation)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long op;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &op) == FAILURE) {
        return;
    }
    nvgGlobalCompositeOperation(intern->nvgctx, op);
}
/**
 * globalCompositeBlendFunc
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, globalCompositeBlendFunc)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long sfactor;
    zend_long dfactor;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &sfactor, &dfactor) == FAILURE) {
        return;
    }
    nvgGlobalCompositeBlendFunc(intern->nvgctx, sfactor, dfactor);
}
/**
 * globalCompositeBlendFuncSeparate
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, globalCompositeBlendFuncSeparate)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long srcRGB;
    zend_long dstRGB;
    zend_long srcAlpha;
    zend_long dstAlpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &srcRGB, &dstRGB, &srcAlpha, &dstAlpha) == FAILURE) {
        return;
    }
    nvgGlobalCompositeBlendFuncSeparate(intern->nvgctx, srcRGB, dstRGB, srcAlpha, dstAlpha);
}
/**
 * save
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, save)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgSave(intern->nvgctx);
}
/**
 * restore
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, restore)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgRestore(intern->nvgctx);
}
/**
 * reset
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, reset)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgReset(intern->nvgctx);
}
/**
 * shapeAntiAlias
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, shapeAntiAlias)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long enabled;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &enabled) == FAILURE) {
        return;
    }
    nvgShapeAntiAlias(intern->nvgctx, enabled);
}
/**
 * strokeColor
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, strokeColor)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zval *color_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &color_zval, phpglfw_get_vg_vgcolor_ce()) == FAILURE) {
        return;
    }
    NVGcolor color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(color_zval))->nvgcolor;
    nvgStrokeColor(intern->nvgctx, color);
}
/**
 * strokePaint
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, strokePaint)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zval *paint_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &paint_zval, phpglfw_get_vg_vgpaint_ce()) == FAILURE) {
        return;
    }
    NVGpaint paint = phpglfw_vgpaint_objectptr_from_zobj_p(Z_OBJ_P(paint_zval))->nvgpaint;
    nvgStrokePaint(intern->nvgctx, paint);
}
/**
 * fillColor
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, fillColor)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zval *color_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &color_zval, phpglfw_get_vg_vgcolor_ce()) == FAILURE) {
        return;
    }
    NVGcolor color = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(color_zval))->nvgcolor;
    nvgFillColor(intern->nvgctx, color);
}
/**
 * fillPaint
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, fillPaint)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zval *paint_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &paint_zval, phpglfw_get_vg_vgpaint_ce()) == FAILURE) {
        return;
    }
    NVGpaint paint = phpglfw_vgpaint_objectptr_from_zobj_p(Z_OBJ_P(paint_zval))->nvgpaint;
    nvgFillPaint(intern->nvgctx, paint);
}
/**
 * miterLimit
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, miterLimit)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double limit;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &limit) == FAILURE) {
        return;
    }
    nvgMiterLimit(intern->nvgctx, limit);
}
/**
 * strokeWidth
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, strokeWidth)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &size) == FAILURE) {
        return;
    }
    nvgStrokeWidth(intern->nvgctx, size);
}
/**
 * lineCap
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, lineCap)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long cap;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &cap) == FAILURE) {
        return;
    }
    nvgLineCap(intern->nvgctx, cap);
}
/**
 * lineJoin
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, lineJoin)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long join;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &join) == FAILURE) {
        return;
    }
    nvgLineJoin(intern->nvgctx, join);
}
/**
 * globalAlpha
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, globalAlpha)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double alpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &alpha) == FAILURE) {
        return;
    }
    nvgGlobalAlpha(intern->nvgctx, alpha);
}
/**
 * resetTransform
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, resetTransform)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgResetTransform(intern->nvgctx);
}
/**
 * transform
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, transform)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double a;
    double b;
    double c;
    double d;
    double e;
    double f;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddddd", &a, &b, &c, &d, &e, &f) == FAILURE) {
        return;
    }
    nvgTransform(intern->nvgctx, a, b, c, d, e, f);
}
/**
 * translate
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, translate)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dd", &x, &y) == FAILURE) {
        return;
    }
    nvgTranslate(intern->nvgctx, x, y);
}
/**
 * rotate
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, rotate)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double angle;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &angle) == FAILURE) {
        return;
    }
    nvgRotate(intern->nvgctx, angle);
}
/**
 * skewX
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, skewX)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double angle;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &angle) == FAILURE) {
        return;
    }
    nvgSkewX(intern->nvgctx, angle);
}
/**
 * skewY
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, skewY)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double angle;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &angle) == FAILURE) {
        return;
    }
    nvgSkewY(intern->nvgctx, angle);
}
/**
 * scale
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, scale)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dd", &x, &y) == FAILURE) {
        return;
    }
    nvgScale(intern->nvgctx, x, y);
}
/**
 * currentTransform
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, currentTransform)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zval *buffer_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &buffer_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        return;
    }
    phpglfw_buffer_glfloat_object *buffer = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(buffer_zval));
    // ensure the proper size of the buffer
    cvector_reserve(buffer->vec, 6);
    // nvgCurrentTransform will copy the values into the float*
    nvgCurrentTransform(intern->nvgctx, buffer->vec);
    cvector_set_size(buffer->vec, 6);;
}
/**
 * transformPointCurrent
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, transformPointCurrent)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zval *dstx_zval;
    float dstx_tmp;
    zval *dsty_zval;
    float dsty_tmp;
    double srcx;
    double srcy;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "zzdd", &dstx_zval, &dsty_zval, &srcx, &srcy) == FAILURE) {
        return;
    }
    ZVAL_DEREF(dstx_zval);
    convert_to_double(dstx_zval);
    ZVAL_DEREF(dsty_zval);
    convert_to_double(dsty_zval);
    nvgTransformPointCurrent(intern->nvgctx, &dstx_tmp, &dsty_tmp, srcx, srcy);
    ZVAL_DOUBLE(dstx_zval, dstx_tmp);
    ZVAL_DOUBLE(dsty_zval, dsty_tmp);
}
/**
 * imageSize
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, imageSize)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long image;
    zval *w_zval;
    int w_tmp;
    zval *h_zval;
    int h_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lzz", &image, &w_zval, &h_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(w_zval);
    convert_to_long(w_zval);
    ZVAL_DEREF(h_zval);
    convert_to_long(h_zval);
    nvgImageSize(intern->nvgctx, image, &w_tmp, &h_tmp);
    ZVAL_LONG(w_zval, w_tmp);
    ZVAL_LONG(h_zval, h_tmp);
}
/**
 * deleteImage
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, deleteImage)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long image;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &image) == FAILURE) {
        return;
    }
    nvgDeleteImage(intern->nvgctx, image);
}
/**
 * scissor
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, scissor)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    double w;
    double h;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &x, &y, &w, &h) == FAILURE) {
        return;
    }
    nvgScissor(intern->nvgctx, x, y, w, h);
}
/**
 * intersectScissor
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, intersectScissor)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    double w;
    double h;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &x, &y, &w, &h) == FAILURE) {
        return;
    }
    nvgIntersectScissor(intern->nvgctx, x, y, w, h);
}
/**
 * resetScissor
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, resetScissor)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgResetScissor(intern->nvgctx);
}
/**
 * beginPath
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, beginPath)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgBeginPath(intern->nvgctx);
}
/**
 * moveTo
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, moveTo)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dd", &x, &y) == FAILURE) {
        return;
    }
    nvgMoveTo(intern->nvgctx, x, y);
}
/**
 * lineTo
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, lineTo)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dd", &x, &y) == FAILURE) {
        return;
    }
    nvgLineTo(intern->nvgctx, x, y);
}
/**
 * bezierTo
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, bezierTo)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double c1x;
    double c1y;
    double c2x;
    double c2y;
    double x;
    double y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddddd", &c1x, &c1y, &c2x, &c2y, &x, &y) == FAILURE) {
        return;
    }
    nvgBezierTo(intern->nvgctx, c1x, c1y, c2x, c2y, x, y);
}
/**
 * quadTo
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, quadTo)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double cx;
    double cy;
    double x;
    double y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &cx, &cy, &x, &y) == FAILURE) {
        return;
    }
    nvgQuadTo(intern->nvgctx, cx, cy, x, y);
}
/**
 * arcTo
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, arcTo)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x1;
    double y1;
    double x2;
    double y2;
    double radius;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddddd", &x1, &y1, &x2, &y2, &radius) == FAILURE) {
        return;
    }
    nvgArcTo(intern->nvgctx, x1, y1, x2, y2, radius);
}
/**
 * closePath
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, closePath)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgClosePath(intern->nvgctx);
}
/**
 * pathWinding
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, pathWinding)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long dir;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &dir) == FAILURE) {
        return;
    }
    nvgPathWinding(intern->nvgctx, dir);
}
/**
 * arc
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, arc)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double cx;
    double cy;
    double r;
    double a0;
    double a1;
    zend_long dir;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddddl", &cx, &cy, &r, &a0, &a1, &dir) == FAILURE) {
        return;
    }
    nvgArc(intern->nvgctx, cx, cy, r, a0, a1, dir);
}
/**
 * rect
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, rect)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    double w;
    double h;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &x, &y, &w, &h) == FAILURE) {
        return;
    }
    nvgRect(intern->nvgctx, x, y, w, h);
}
/**
 * roundedRect
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, roundedRect)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    double w;
    double h;
    double r;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddddd", &x, &y, &w, &h, &r) == FAILURE) {
        return;
    }
    nvgRoundedRect(intern->nvgctx, x, y, w, h, r);
}
/**
 * roundedRectVarying
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, roundedRectVarying)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    double w;
    double h;
    double radTopLeft;
    double radTopRight;
    double radBottomRight;
    double radBottomLeft;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddddddd", &x, &y, &w, &h, &radTopLeft, &radTopRight, &radBottomRight, &radBottomLeft) == FAILURE) {
        return;
    }
    nvgRoundedRectVarying(intern->nvgctx, x, y, w, h, radTopLeft, radTopRight, radBottomRight, radBottomLeft);
}
/**
 * ellipse
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, ellipse)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double cx;
    double cy;
    double rx;
    double ry;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &cx, &cy, &rx, &ry) == FAILURE) {
        return;
    }
    nvgEllipse(intern->nvgctx, cx, cy, rx, ry);
}
/**
 * circle
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, circle)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double cx;
    double cy;
    double r;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddd", &cx, &cy, &r) == FAILURE) {
        return;
    }
    nvgCircle(intern->nvgctx, cx, cy, r);
}
/**
 * fill
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, fill)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgFill(intern->nvgctx);
}
/**
 * stroke
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, stroke)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgStroke(intern->nvgctx);
}
/**
 * createFont
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, createFont)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    const char *name;
    size_t name_size;
    const char *filename;
    size_t filename_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ss", &name, &name_size, &filename, &filename_size) == FAILURE) {
        return;
    }
    RETURN_LONG(nvgCreateFont(intern->nvgctx, name, filename));
}
/**
 * createFontAtIndex
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, createFontAtIndex)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    const char *name;
    size_t name_size;
    const char *filename;
    size_t filename_size;
    zend_long fontIndex;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ssl", &name, &name_size, &filename, &filename_size, &fontIndex) == FAILURE) {
        return;
    }
    RETURN_LONG(nvgCreateFontAtIndex(intern->nvgctx, name, filename, fontIndex));
}
/**
 * findFont
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, findFont)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    const char *name;
    size_t name_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &name, &name_size) == FAILURE) {
        return;
    }
    RETURN_LONG(nvgFindFont(intern->nvgctx, name));
}
/**
 * addFallbackFontId
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, addFallbackFontId)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long baseFont;
    zend_long fallbackFont;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &baseFont, &fallbackFont) == FAILURE) {
        return;
    }
    RETURN_LONG(nvgAddFallbackFontId(intern->nvgctx, baseFont, fallbackFont));
}
/**
 * addFallbackFont
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, addFallbackFont)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    const char *baseFont;
    size_t baseFont_size;
    const char *fallbackFont;
    size_t fallbackFont_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ss", &baseFont, &baseFont_size, &fallbackFont, &fallbackFont_size) == FAILURE) {
        return;
    }
    RETURN_LONG(nvgAddFallbackFont(intern->nvgctx, baseFont, fallbackFont));
}
/**
 * resetFallbackFontsId
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, resetFallbackFontsId)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long baseFont;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &baseFont) == FAILURE) {
        return;
    }
    nvgResetFallbackFontsId(intern->nvgctx, baseFont);
}
/**
 * resetFallbackFonts
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, resetFallbackFonts)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    const char *baseFont;
    size_t baseFont_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &baseFont, &baseFont_size) == FAILURE) {
        return;
    }
    nvgResetFallbackFonts(intern->nvgctx, baseFont);
}
/**
 * fontSize
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, fontSize)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &size) == FAILURE) {
        return;
    }
    nvgFontSize(intern->nvgctx, size);
}
/**
 * fontBlur
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, fontBlur)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double blur;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &blur) == FAILURE) {
        return;
    }
    nvgFontBlur(intern->nvgctx, blur);
}
/**
 * textLetterSpacing
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, textLetterSpacing)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double spacing;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &spacing) == FAILURE) {
        return;
    }
    nvgTextLetterSpacing(intern->nvgctx, spacing);
}
/**
 * textLineHeight
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, textLineHeight)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double lineHeight;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &lineHeight) == FAILURE) {
        return;
    }
    nvgTextLineHeight(intern->nvgctx, lineHeight);
}
/**
 * textAlign
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, textAlign)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long align;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &align) == FAILURE) {
        return;
    }
    nvgTextAlign(intern->nvgctx, align);
}
/**
 * fontFaceId
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, fontFaceId)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zend_long font;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &font) == FAILURE) {
        return;
    }
    nvgFontFaceId(intern->nvgctx, font);
}
/**
 * fontFace
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, fontFace)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    const char *font;
    size_t font_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &font, &font_size) == FAILURE) {
        return;
    }
    nvgFontFace(intern->nvgctx, font);
}
/**
 * text
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, text)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    const char *string;
    size_t string_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dds", &x, &y, &string, &string_size) == FAILURE) {
        return;
    }
    RETURN_DOUBLE(nvgText(intern->nvgctx, x, y, string, NULL));
}
/**
 * textBox
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, textBox)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    double breakRowWidth;
    const char *string;
    size_t string_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddds", &x, &y, &breakRowWidth, &string, &string_size) == FAILURE) {
        return;
    }
    nvgTextBox(intern->nvgctx, x, y, breakRowWidth, string, NULL);
}
/**
 * textBounds
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, textBounds)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    const char *string;
    size_t string_size;
    zval *bounds_zval = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dds|O!", &x, &y, &string, &string_size, &bounds_zval, phpglfw_get_math_vec4_ce()) == FAILURE) {
        return;
    }
    phpglfw_math_vec4_object *bounds = NULL;
    if (bounds_zval != NULL) {
        ZVAL_DEREF(bounds_zval);
        // if we got a var but its not an object, we create a new one
        if (Z_TYPE_P(bounds_zval) == IS_OBJECT && Z_OBJCE_P(bounds_zval) == phpglfw_get_math_vec4_ce()) {
            bounds = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(bounds_zval));
        }
        else {
            object_init_ex(bounds_zval, phpglfw_get_math_vec4_ce());
            bounds = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(bounds_zval));
        }
    }
    RETURN_DOUBLE(nvgTextBounds(intern->nvgctx, x, y, string, NULL, bounds->data));
}
/**
 * textBoxBounds
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, textBoxBounds)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    double x;
    double y;
    double breakRowWidth;
    const char *string;
    size_t string_size;
    zval *bounds_zval;
    float bounds_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddsz", &x, &y, &breakRowWidth, &string, &string_size, &bounds_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(bounds_zval);
    convert_to_double(bounds_zval);
    nvgTextBoxBounds(intern->nvgctx, x, y, breakRowWidth, string, NULL, &bounds_tmp);
    ZVAL_DOUBLE(bounds_zval, bounds_tmp);
}
/**
 * textMetrics
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, textMetrics)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    zval *ascender_zval;
    float ascender_tmp;
    zval *descender_zval;
    float descender_tmp;
    zval *lineh_zval;
    float lineh_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "zzz", &ascender_zval, &descender_zval, &lineh_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(ascender_zval);
    convert_to_double(ascender_zval);
    ZVAL_DEREF(descender_zval);
    convert_to_double(descender_zval);
    ZVAL_DEREF(lineh_zval);
    convert_to_double(lineh_zval);
    nvgTextMetrics(intern->nvgctx, &ascender_tmp, &descender_tmp, &lineh_tmp);
    ZVAL_DOUBLE(ascender_zval, ascender_tmp);
    ZVAL_DOUBLE(descender_zval, descender_tmp);
    ZVAL_DOUBLE(lineh_zval, lineh_tmp);
}
/**
 * deleteInternal
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, deleteInternal)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgDeleteInternal(intern->nvgctx);
}
/**
 * debugDumpPathCache
 */ 
PHP_METHOD(GL_VectorGraphics_VGContext, debugDumpPathCache)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    nvgDebugDumpPathCache(intern->nvgctx);
}

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