#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_glfw.h"

#include <zend_API.h>
#include <GLFW/glfw3.h>

#define PHPGLFW_WINDOW_NAME "phpglfw window"

int phpglfw_window_context;

#define PHPGLFW_RESOURCE_TYPE zend_resource
#define PHPGLFW_RETURN_RESOURCE(window, context) \
    RETURN_RES(zend_register_resource(window, context))

/**
 * Get GLFW window from resource
 * --------------------------------
 */
static GLFWwindow *phpglfw_fetch_window(zval *resource TSRMLS_DC)
{
    GLFWwindow *window;

    window = (GLFWwindow *)zend_fetch_resource_ex(resource, PHPGLFW_WINDOW_NAME, phpglfw_window_context);

    return window;
}

/**
 * dtor
 * --------------------------------
 */
static void phpglfw_window_dtor(zend_resource *rsrc TSRMLS_DC)
{
    GLFWwindow* window = (void *) rsrc->ptr;

    if (window) {
        glfwDestroyWindow(window);
    }
}

/**
 * --------------------------------
 * Generated methods
 * --------------------------------
 */
<?php foreach($methods as $method) : ?>
<?php echo $method->generate(); ?> 
<?php endforeach; ?>


/**
 * MINIT
 * --------------------------------
 */
PHP_MINIT_FUNCTION(glfw)
{
    phpglfw_window_context = zend_register_list_destructors_ex(phpglfw_window_dtor, NULL, PHPGLFW_WINDOW_NAME, module_number);
<?php foreach($constants as $constant) : ?>
#ifdef <?php echo $constant; ?> 
    REGISTER_LONG_CONSTANT("<?php echo $constant; ?>", <?php echo $constant; ?>, CONST_CS|CONST_PERSISTENT);
#endif
<?php endforeach; ?>
    return SUCCESS;
}

/**
 * Register
 * --------------------------------
 */
static zend_function_entry glfw_functions[] = {
<?php foreach($methods as $method) : ?>
    <?php echo $method->generateFE(); ?> 
<?php endforeach; ?>
#ifdef PHP_FE_END
    PHP_FE_END
#else
    {NULL, NULL, NULL}
#endif
};

zend_module_entry glfw_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_GLFW_EXTNAME,
    glfw_functions,
    PHP_MINIT(glfw),
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_GLFW_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GLFW
ZEND_GET_MODULE(glfw)
#endif