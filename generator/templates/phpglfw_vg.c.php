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

#include "phpglfw_arginfo.h"

#include "php.h"
#include "Zend/zend_smart_str.h"
#include "ext/standard/info.h"
#include "ext/standard/php_var.h"

#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl.h"

zend_class_entry *phpglfw_vgcontext_ce;

zend_class_entry *phpglfw_get_vg_vgcontext_ce() {
    return phpglfw_vgcontext_ce;
}

zend_always_inline phpglfw_vgcontext_object* phpglfw_vgcontext_res_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_vgcontext_object *) ((char *) (obj) - XtOffsetOf(phpglfw_vgcontext_object, std));
}

static zend_object_handlers phpglfw_vgcontext_res_handlers;

zend_object *phpglfw_vgcontext_res_create_handler(zend_class_entry *class_type)
{
    phpglfw_vgcontext_object *intern;
    intern = zend_object_alloc(sizeof(phpglfw_vgcontext_object), class_type);

    intern->nvgctx = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &phpglfw_vgcontext_res_handlers;

    return &intern->std;
}

static void phpglfw_vgcontext_res_free_handler(zend_object *object)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_res_objectptr_from_zobj_p(object);

    if (intern->nvgctx != NULL) {
	    nvgDeleteGL3(intern->nvgctx);
        intern->nvgctx = NULL;
    }

    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(GL_VectorGraphics_VGContext, __construct)
{
    zval *obj;
    obj = getThis();
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_res_objectptr_from_zobj_p(Z_OBJ_P(obj));
    intern->nvgctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
}

PHP_METHOD(GL_VectorGraphics_VGContext, beginFrame)
{
    zval *obj;
    obj = getThis();
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_res_objectptr_from_zobj_p(Z_OBJ_P(obj));
    nvgBeginFrame(intern->nvgctx, 1280, 720, 1.0f);
}

PHP_METHOD(GL_VectorGraphics_VGContext, endFrame)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_res_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    nvgEndFrame(intern->nvgctx);
}

PHP_METHOD(GL_VectorGraphics_VGContext, beginPath)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_res_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    nvgBeginPath(intern->nvgctx);
}

PHP_METHOD(GL_VectorGraphics_VGContext, rect)
{
    double x, y, w, h;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &x, &y, &w, &h) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_res_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    nvgRect(intern->nvgctx, x, y, w, h);
}

PHP_METHOD(GL_VectorGraphics_VGContext, fillColor)
{
    zend_long r, g, b, a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &r, &g, &b, &a) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_res_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    nvgFillColor(intern->nvgctx, nvgRGBA(r, g, b, a));
}

PHP_METHOD(GL_VectorGraphics_VGContext, fill)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_res_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    nvgFill(intern->nvgctx);
}

PHP_METHOD(GL_VectorGraphics_VGContext, strokeColor)
{
    zend_long r, g, b, a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &r, &g, &b, &a) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_res_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    nvgStrokeColor(intern->nvgctx, nvgRGBA(r, g, b, a));
}

PHP_METHOD(GL_VectorGraphics_VGContext, stroke)
{
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_res_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    nvgStroke(intern->nvgctx);
}


void phpglfw_register_vg_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;
    
    // initialize and register the VectorGraphics Context class
    INIT_CLASS_ENTRY(tmp_ce, "GL\\VectorGraphics\\VGContext", class_GL_VectorGraphics_VGContext_methods);
    phpglfw_vgcontext_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_vgcontext_ce->create_object = phpglfw_vgcontext_res_create_handler;

    memcpy(&phpglfw_vgcontext_res_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_vgcontext_res_handlers.offset = XtOffsetOf(phpglfw_vgcontext_object, std);
    phpglfw_vgcontext_res_handlers.free_obj = phpglfw_vgcontext_res_free_handler;
}