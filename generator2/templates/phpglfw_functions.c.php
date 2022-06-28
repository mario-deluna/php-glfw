/**
 * PHP-glfw 
 * 
 * Extension functions
 *
 * Copyright (c) 2018-2022 Mario Döring
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
#include "phpglfw_functions.h"

#include "php.h"
#include "phpglfw.h"
#include <zend_API.h>

/** 
 * Test
 */
zend_class_entry *phpglfw_window_ce;

typedef struct _phpglfw_window_object {
    GLFWwindow *window;
    zend_object std;
} phpglfw_window_object;

static zend_object_handlers phpglfw_window_object_handlers;

static const zend_function_entry class_GLFWwindow_methods[] = {
    ZEND_FE_END
};

static zend_always_inline phpglfw_window_object* phpglfw_window_from_zobj_p(zend_object* obj)
{
    return (phpglfw_window_object *) ((char *) (obj) - XtOffsetOf(phpglfw_window_object, std));
}

static zend_function *phpglfw_window_object_get_constructor(zend_object *object)
{
    zend_throw_error(NULL, "You cannot initialize a GLFWwindow object except through helper functions");
    return NULL;
}

static zend_class_entry *register_class_GLFWwindow(void)
{
    zend_class_entry ce, *class_entry;

    INIT_CLASS_ENTRY(ce, "GLFWwindow", class_GLFWwindow_methods);
    class_entry = zend_register_internal_class_ex(&ce, NULL);
    class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;

    return class_entry;
}

zend_object *phpglfw_window_object_create(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_window_object) + zend_object_properties_size(class_type);
    phpglfw_window_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_window_object_handlers;

    return &intern->std;
}

static void phpglfw_window_object_free(zend_object *intern)
{
    phpglfw_window_object *obj_ptr = phpglfw_window_from_zobj_p(intern);
    if (obj_ptr->window) {
        glfwDestroyWindow(obj_ptr->window);
    }
    zend_object_std_dtor(intern);
}

void phpglfw_assign_glfwwindowptr_as_extglfwwindow(zval *val, GLFWwindow *window)
{
    object_init_ex(val, phpglfw_window_ce);
    phpglfw_window_from_zobj_p(Z_OBJ_P(val))->window = window;
}

void phpglfw_object_minit_helper(void)
{
    phpglfw_window_ce = register_class_GLFWwindow();
    phpglfw_window_ce->create_object = phpglfw_window_object_create;

    /* setting up the object handlers for the GdImage class */
    memcpy(&phpglfw_window_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_window_object_handlers.clone_obj = NULL;
    phpglfw_window_object_handlers.free_obj = phpglfw_window_object_free;
    phpglfw_window_object_handlers.get_constructor = phpglfw_window_object_get_constructor;
    phpglfw_window_object_handlers.compare = zend_objects_not_comparable;
    phpglfw_window_object_handlers.offset = XtOffsetOf(phpglfw_window_object, std);
}

GLFWwindow * phpglfw_glfwwindowptr_from_zval_p(zval* zp)
{
    return phpglfw_window_from_zobj_p(Z_OBJ_P(zp))->window;
}
/**
 * ----------------------------------------------------------------------------
 * PHPGlfw Resources 
 * ----------------------------------------------------------------------------
 */

<?php foreach ($resources as $resource) : ?>
#define <?php echo $resource->getResourceName(); ?> "<?php echo $resource->name; ?>"
int <?php echo $resource->getContextName(); ?>;
<?php endforeach; ?>

#define PHPGLFW_RESOURCE_TYPE zend_resource
<?php foreach ($resources as $resource) : ?>
#define <?php echo $resource->getReturnResource(); ?>(<?php echo $resource->name; ?>, context) \
    RETURN_RES(zend_register_resource(<?php echo $resource->name; ?>, context))
<?php endforeach; ?>

<?php foreach ($resources as $resource) : ?>
/**
 * Get <?php echo $resource->type; ?> from resource 
 * --------------------------------
 */
static <?php echo $resource->type; ?><?php echo $resource->getFetchMethod(); ?>(zval *resource)
{
    if (Z_TYPE_P(resource) == IS_NULL) {
        return NULL;
    }

    <?php echo $resource->type; ?><?php echo $resource->name; ?>;
    ZEND_ASSERT(Z_TYPE_P(resource) == IS_RESOURCE);
    <?php echo $resource->name; ?> = (<?php echo $resource->type; ?>)zend_fetch_resource(Z_RES_P(resource), <?php echo $resource->getResourceName(); ?>, <?php echo $resource->getContextName(); ?>);

    return <?php echo $resource->name; ?>;
}

/**
 * dtor <?php echo $resource->type; ?> 
 * --------------------------------
 */
static void <?php echo $resource->getDtorMethod(); ?>(PHPGLFW_RESOURCE_TYPE *rsrc)
{
    <?php echo $resource->type; ?><?php echo $resource->name; ?> = (void *) rsrc->ptr;

    if (<?php echo $resource->name; ?>) {
        <?php echo $resource->generateDestroy(); ?> 
    }
}

<?php endforeach; ?>


/**
 * Resources destructors..
 */
void phpglfw_register_resource_destructors(INIT_FUNC_ARGS)
{
<?php foreach ($resources as $resource) : ?>
    <?php echo $resource->getContextName(); ?> = zend_register_list_destructors_ex(<?php echo $resource->getDtorMethod(); ?>, NULL, <?php echo $resource->getResourceName(); ?>, module_number);
<?php endforeach; ?>
}

/**
 * ----------------------------------------------------------------------------
 * PHPGlfw Functions 
 * ----------------------------------------------------------------------------
 */
<?php foreach($functions as $func) : ?>
/**
 * <?php echo $func->name; ?> 
<?php echo commentifyString($func->comment ?? ''); ?> 
 */
<?php echo $func->generateExtImplementation(); ?>

<?php endforeach; ?>
