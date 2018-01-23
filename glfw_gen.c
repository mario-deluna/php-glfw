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
/**
 * glfwInit
 * --------------------------------
 */
PHP_FUNCTION(glfwInit)
{

    if (glfwInit()) { RETURN_TRUE; } RETURN_FALSE;
}
 
/**
 * glfwTerminate
 * --------------------------------
 */
PHP_FUNCTION(glfwTerminate)
{

    glfwTerminate();
}
 
/**
 * glfwGetVersion
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetVersion, 0, 0, 1)
    ZEND_ARG_INFO(1, major)
    ZEND_ARG_INFO(1, minor)
    ZEND_ARG_INFO(1, rev)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwGetVersion)
{
    zend_long major;
    zend_long minor;
    zend_long rev;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lll", &major, &minor, &rev) == FAILURE) {
       return;
    }
    glfwGetVersion(major, minor, rev);
}
 
/**
 * glfwGetVersionString
 * --------------------------------
 */
PHP_FUNCTION(glfwGetVersionString)
{

    RETURN_STRING(glfwGetVersionString());
}
 
/**
 * glfwMakeContextCurrent
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwMakeContextCurrent, 0, 0, 1)
    ZEND_ARG_INFO(0, window)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwMakeContextCurrent)
{
    zval *window_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &window_resource) == FAILURE) {
       return;
    }
    GLFWwindow* window = phpglfw_fetch_window(window_resource TSRMLS_CC);
    glfwMakeContextCurrent(window);
}
 
/**
 * glfwGetCurrentContext
 * --------------------------------
 */
PHP_FUNCTION(glfwGetCurrentContext)
{

    GLFWwindow* window = glfwGetCurrentContext();
    if (!window) RETURN_FALSE;
    PHPGLFW_RETURN_RESOURCE(window, phpglfw_window_context);
}
 
/**
 * glfwSwapInterval
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwSwapInterval, 0, 0, 1)
    ZEND_ARG_INFO(0, interval)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwSwapInterval)
{
    zend_long interval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &interval) == FAILURE) {
       return;
    }
    glfwSwapInterval(interval);
}
 
/**
 * glfwExtensionSupported
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwExtensionSupported, 0, 0, 1)
    ZEND_ARG_INFO(0, extension)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwExtensionSupported)
{
    char *extension;
    size_t extension_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &extension, &extension_size) == FAILURE) {
       return;
    }
    if (glfwExtensionSupported(extension)) { RETURN_TRUE; } RETURN_FALSE;
}
 
/**
 * glfwGetProcAddress
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetProcAddress, 0, 0, 1)
    ZEND_ARG_INFO(0, procname)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwGetProcAddress)
{
    char *procname;
    size_t procname_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &procname, &procname_size) == FAILURE) {
       return;
    }
    glfwGetProcAddress(procname);
}
 
/**
 * glfwDefaultWindowHints
 * --------------------------------
 */
PHP_FUNCTION(glfwDefaultWindowHints)
{

    glfwDefaultWindowHints();
}
 
/**
 * glfwWindowHint
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwWindowHint, 0, 0, 1)
    ZEND_ARG_INFO(0, hint)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwWindowHint)
{
    zend_long hint;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &hint, &value) == FAILURE) {
       return;
    }
    glfwWindowHint(hint, value);
}
 
/**
 * glfwDestroyWindow
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwDestroyWindow, 0, 0, 1)
    ZEND_ARG_INFO(0, window)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwDestroyWindow)
{
    zval *window_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &window_resource) == FAILURE) {
       return;
    }
    zend_list_close(Z_RES_P(window_resource));
}
 
/**
 * glfwCreateWindow
 * --------------------------------
 */
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
    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) RETURN_FALSE;
    PHPGLFW_RETURN_RESOURCE(window, phpglfw_window_context);
}
 
/**
 * glfwWindowShouldClose
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwWindowShouldClose, 0, 0, 1)
    ZEND_ARG_INFO(0, window)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwWindowShouldClose)
{
    zval *window_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &window_resource) == FAILURE) {
       return;
    }
    GLFWwindow* window = phpglfw_fetch_window(window_resource TSRMLS_CC);
    if (glfwWindowShouldClose(window)) { RETURN_TRUE; } RETURN_FALSE;
}
 
/**
 * glfwSetWindowShouldClose
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwSetWindowShouldClose, 0, 0, 1)
    ZEND_ARG_INFO(0, window)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwSetWindowShouldClose)
{
    zval *window_resource;
    zend_bool value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rb", &window_resource, &value) == FAILURE) {
       return;
    }
    GLFWwindow* window = phpglfw_fetch_window(window_resource TSRMLS_CC);
    glfwSetWindowShouldClose(window, value);
}
 
/**
 * glfwSwapBuffers
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwSwapBuffers, 0, 0, 1)
    ZEND_ARG_INFO(0, window)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwSwapBuffers)
{
    zval *window_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &window_resource) == FAILURE) {
       return;
    }
    GLFWwindow* window = phpglfw_fetch_window(window_resource TSRMLS_CC);
    glfwSwapBuffers(window);
}
 
/**
 * glfwPollEvents
 * --------------------------------
 */
PHP_FUNCTION(glfwPollEvents)
{

    glfwPollEvents();
}
 
/**
 * glClearColor
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClearColor, 0, 0, 1)
    ZEND_ARG_INFO(0, r)
    ZEND_ARG_INFO(0, g)
    ZEND_ARG_INFO(0, b)
    ZEND_ARG_INFO(0, a)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClearColor)
{
    double r;
    double g;
    double b;
    double a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &r, &g, &b, &a) == FAILURE) {
       return;
    }
    glClearColor(r, g, b, a);
}
 
/**
 * glClear
 * --------------------------------
 */
PHP_FUNCTION(glClear)
{

    glClear(GL_COLOR_BUFFER_BIT);
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
    PHP_FE(glfwGetVersion, arginfo_glfwGetVersion) 
    PHP_FE(glfwGetVersionString, NULL) 
    PHP_FE(glfwMakeContextCurrent, arginfo_glfwMakeContextCurrent) 
    PHP_FE(glfwGetCurrentContext, NULL) 
    PHP_FE(glfwSwapInterval, arginfo_glfwSwapInterval) 
    PHP_FE(glfwExtensionSupported, arginfo_glfwExtensionSupported) 
    PHP_FE(glfwGetProcAddress, arginfo_glfwGetProcAddress) 
    PHP_FE(glfwDefaultWindowHints, NULL) 
    PHP_FE(glfwWindowHint, arginfo_glfwWindowHint) 
    PHP_FE(glfwDestroyWindow, arginfo_glfwDestroyWindow) 
    PHP_FE(glfwCreateWindow, arginfo_glfwCreateWindow) 
    PHP_FE(glfwWindowShouldClose, arginfo_glfwWindowShouldClose) 
    PHP_FE(glfwSetWindowShouldClose, arginfo_glfwSetWindowShouldClose) 
    PHP_FE(glfwSwapBuffers, arginfo_glfwSwapBuffers) 
    PHP_FE(glfwPollEvents, NULL) 
    PHP_FE(glClearColor, arginfo_glClearColor) 
    PHP_FE(glClear, NULL) 
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