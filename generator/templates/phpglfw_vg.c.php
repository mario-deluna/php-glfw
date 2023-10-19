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
zend_class_entry *phpglfw_vgpaint_ce;
zend_class_entry *phpglfw_vgcolor_ce;

zend_class_entry *phpglfw_get_vg_vgcontext_ce() {
    return phpglfw_vgcontext_ce;
}

zend_class_entry *phpglfw_get_vg_vgpaint_ce() {
    return phpglfw_vgpaint_ce;
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

zend_always_inline phpglfw_vgcolor_object* phpglfw_vgcolor_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_vgcolor_object *) ((char *) (obj) - XtOffsetOf(phpglfw_vgcolor_object, std));
}

static zend_object_handlers phpglfw_vgcontext_handlers;
static zend_object_handlers phpglfw_vgpaint_handlers;
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

static HashTable *phpglfw_vgcolor_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_vgcolor_object *obj_ptr = phpglfw_vgcolor_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(4);
    *is_temp = 1;

    ZVAL_DOUBLE(&zv, obj_ptr->nvgcolor.r);
    zend_hash_str_update(ht, "r", sizeof("r") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->nvgcolor.g);
    zend_hash_str_update(ht, "g", sizeof("g") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->nvgcolor.b);
    zend_hash_str_update(ht, "b", sizeof("b") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->nvgcolor.a);
    zend_hash_str_update(ht, "a", sizeof("a") - 1, &zv);

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

PHP_METHOD(GL_VectorGraphics_VGContext, __construct)
{
    zval *obj;
    obj = getThis();
    phpglfw_vgcontext_object *intern = phpglfw_vgcontext_objectptr_from_zobj_p(Z_OBJ_P(obj));
    intern->nvgctx = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
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

    // initialize and register the VectorGraphics Color class
    INIT_CLASS_ENTRY(tmp_ce, "GL\\VectorGraphics\\VGColor", class_GL_VectorGraphics_VGColor_methods);
    phpglfw_vgcolor_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_vgcolor_ce->create_object = phpglfw_vgcolor_create_handler;

    memcpy(&phpglfw_vgcolor_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_vgcolor_handlers.offset = XtOffsetOf(phpglfw_vgcolor_object, std);
    phpglfw_vgcolor_handlers.free_obj = phpglfw_vgcolor_free_handler;
    phpglfw_vgcolor_handlers.get_debug_info = phpglfw_vgcolor_debug_info_handler;
}