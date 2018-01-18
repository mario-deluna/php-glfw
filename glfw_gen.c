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
PHP_FUNCTION(glfwInit)
{
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "", ) == FAILURE) {
       return;
    }
    
}
 
PHP_FUNCTION(glfwTerminate)
{
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "", ) == FAILURE) {
       return;
    }
    
}
 
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwDestroyWindow, 0, 0, 1)
    ZEND_ARG_INFO(0, window)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwDestroyWindow)
{
    zval *window_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &window_resource) == FAILURE) {
       return;
    }
    
}
 
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwCreateWindow, 0, 0, 1)
    ZEND_ARG_INFO(0, width)
    ZEND_ARG_INFO(0, height)
    ZEND_ARG_INFO(0, title)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwCreateWindow)
{
    zend_long width;
    zend_long height;
    char *title;
    size_t title_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lls", &width, &height, &title, &title_size) == FAILURE) {
       return;
    }
    
}
 


/**
 * MINIT
 * --------------------------------
 */
PHP_MINIT_FUNCTION(glfw)
{
    phpglfw_window_context = zend_register_list_destructors_ex(phpglfw_window_dtor, NULL, PHPGLFW_WINDOW_NAME, module_number);

    return SUCCESS;
}

/**
 * Register
 * --------------------------------
 */
static zend_function_entry glfw_functions[] = {
    PHP_FE(glfwInit, NULL) 
    PHP_FE(glfwTerminate, NULL) 
    PHP_FE(glfwDestroyWindow, arginfo_glfwDestroyWindow) 
    PHP_FE(glfwCreateWindow, arginfo_glfwCreateWindow) 
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