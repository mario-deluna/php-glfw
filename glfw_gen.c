#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_glfw.h"

#include <zend_API.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>


#define PHPGLFW_GLFWWINDOW_NAME "glfwwindow"
int phpglfw_glfwwindow_context;
#define PHPGLFW_GLFWCURSOR_NAME "glfwcursor"
int phpglfw_glfwcursor_context;
#define PHPGLFW_STBIMAGEDATA_NAME "stbimagedata"
int phpglfw_stbimagedata_context;

#define PHPGLFW_RESOURCE_TYPE zend_resource
#define PHPGLFW_RETURN_GLFWWINDOW_RESOURCE(glfwwindow, context) \
    RETURN_RES(zend_register_resource(glfwwindow, context))
#define PHPGLFW_RETURN_GLFWCURSOR_RESOURCE(glfwcursor, context) \
    RETURN_RES(zend_register_resource(glfwcursor, context))
#define PHPGLFW_RETURN_STBIMAGEDATA_RESOURCE(stbimagedata, context) \
    RETURN_RES(zend_register_resource(stbimagedata, context))

/**
 * Get GLFWwindow * from resource
 * --------------------------------
 */
static GLFWwindow *phpglfw_fetch_glfwwindow(zval *resource)
{
    GLFWwindow *glfwwindow;
    ZEND_ASSERT(Z_TYPE_P(resource) == IS_RESOURCE);
    glfwwindow = (GLFWwindow *)zend_fetch_resource(Z_RES_P(resource), PHPGLFW_GLFWWINDOW_NAME, phpglfw_glfwwindow_context);

    return glfwwindow;
}

/**
 * dtor GLFWwindow * * --------------------------------
 */
static void phpglfw_glfwwindow_dtor(zend_resource *rsrc)
{
    GLFWwindow *glfwwindow = (void *) rsrc->ptr;

    if (glfwwindow) {
        glfwDestroyWindow(glfwwindow);    }
}

/**
 * Get GLFWcursor * from resource
 * --------------------------------
 */
static GLFWcursor *phpglfw_fetch_glfwcursor(zval *resource)
{
    GLFWcursor *glfwcursor;
    ZEND_ASSERT(Z_TYPE_P(resource) == IS_RESOURCE);
    glfwcursor = (GLFWcursor *)zend_fetch_resource(Z_RES_P(resource), PHPGLFW_GLFWCURSOR_NAME, phpglfw_glfwcursor_context);

    return glfwcursor;
}

/**
 * dtor GLFWcursor * * --------------------------------
 */
static void phpglfw_glfwcursor_dtor(zend_resource *rsrc)
{
    GLFWcursor *glfwcursor = (void *) rsrc->ptr;

    if (glfwcursor) {
        glfwDestroyCursor(glfwcursor);    }
}

/**
 * Get unsigned char * from resource
 * --------------------------------
 */
static unsigned char *phpglfw_fetch_stbimagedata(zval *resource)
{
    unsigned char *stbimagedata;
    ZEND_ASSERT(Z_TYPE_P(resource) == IS_RESOURCE);
    stbimagedata = (unsigned char *)zend_fetch_resource(Z_RES_P(resource), PHPGLFW_STBIMAGEDATA_NAME, phpglfw_stbimagedata_context);

    return stbimagedata;
}

/**
 * dtor unsigned char * * --------------------------------
 */
static void phpglfw_stbimagedata_dtor(zend_resource *rsrc)
{
    unsigned char *stbimagedata = (void *) rsrc->ptr;

    if (stbimagedata) {
        stbi_image_free(stbimagedata);    }
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
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwInit, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwInit)
{

    if (glfwInit()) { RETURN_TRUE; } RETURN_FALSE;
}
 
/**
 * glfwTerminate
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwTerminate, 0, 0, 1)
ZEND_END_ARG_INFO()

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
    zval *z_major;
    zval *z_minor;
    zval *z_rev;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "zzz", &z_major, &z_minor, &z_rev) == FAILURE) {
       return;
    }
    ZVAL_DEREF(z_major); convert_to_long(z_major);
    ZVAL_DEREF(z_minor); convert_to_long(z_minor);
    ZVAL_DEREF(z_rev); convert_to_long(z_rev);
    glfwGetVersion((int *)&z_major->value, (int *)&z_minor->value, (int *)&z_rev->value);
}
 
/**
 * glfwGetVersionString
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetVersionString, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwGetVersionString)
{

    RETURN_STRING(glfwGetVersionString());
}
 
/**
 * glfwMakeContextCurrent
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwMakeContextCurrent, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwMakeContextCurrent)
{
    zval *glfwwindow_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "r", &glfwwindow_resource) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource );
    glfwMakeContextCurrent(glfwwindow);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    zend_error(E_ERROR, "Could not load glad.");
    }
}
 
/**
 * glfwGetCurrentContext
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetCurrentContext, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwGetCurrentContext)
{

    GLFWwindow* glfwwindow = glfwGetCurrentContext();
    if (!glfwwindow) RETURN_FALSE;
    PHPGLFW_RETURN_GLFWWINDOW_RESOURCE(glfwwindow, phpglfw_glfwwindow_context);
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
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &interval) == FAILURE) {
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
    const char *extension;
    size_t extension_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &extension, &extension_size) == FAILURE) {
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
    const char *procname;
    size_t procname_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &procname, &procname_size) == FAILURE) {
       return;
    }
    glfwGetProcAddress(procname);
}
 
/**
 * glfwDefaultWindowHints
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwDefaultWindowHints, 0, 0, 1)
ZEND_END_ARG_INFO()

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
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &hint, &value) == FAILURE) {
       return;
    }
    glfwWindowHint(hint, value);
}
 
/**
 * glfwDestroyWindow
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwDestroyWindow, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwDestroyWindow)
{
    zval *glfwwindow_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "r", &glfwwindow_resource) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource );
    zend_list_close(Z_RES_P(glfwwindow_resource));
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
    const char *title;
    size_t title_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lls", &width, &height, &title, &title_size) == FAILURE) {
       return;
    }
    GLFWwindow* glfwwindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!glfwwindow) RETURN_FALSE;
    PHPGLFW_RETURN_GLFWWINDOW_RESOURCE(glfwwindow, phpglfw_glfwwindow_context);
}
 
/**
 * glfwWindowShouldClose
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwWindowShouldClose, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwWindowShouldClose)
{
    zval *glfwwindow_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "r", &glfwwindow_resource) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource );
    if (glfwWindowShouldClose(glfwwindow)) { RETURN_TRUE; } RETURN_FALSE;
}
 
/**
 * glfwSetWindowShouldClose
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwSetWindowShouldClose, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwSetWindowShouldClose)
{
    zval *glfwwindow_resource;
    zend_bool value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "rb", &glfwwindow_resource, &value) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource );
    glfwSetWindowShouldClose(glfwwindow, value);
}
 
/**
 * glfwSwapBuffers
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwSwapBuffers, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwSwapBuffers)
{
    zval *glfwwindow_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "r", &glfwwindow_resource) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource );
    glfwSwapBuffers(glfwwindow);
}
 
/**
 * glfwPollEvents
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwPollEvents, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwPollEvents)
{

    glfwPollEvents();
}
 
/**
 * glfwGetTime
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetTime, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwGetTime)
{

    RETURN_DOUBLE(glfwGetTime());
}
 
/**
 * glfwCreateStandardCursor
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwCreateStandardCursor, 0, 0, 1)
    ZEND_ARG_INFO(0, shape)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwCreateStandardCursor)
{
    zend_long shape;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &shape) == FAILURE) {
       return;
    }
    GLFWcursor * glfwcursor = glfwCreateStandardCursor(shape);
    PHPGLFW_RETURN_GLFWCURSOR_RESOURCE(glfwcursor, phpglfw_glfwcursor_context);
}
 
/**
 * glfwDestroyCursor
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwDestroyCursor, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwcursor)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwDestroyCursor)
{
    zval *glfwcursor_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "r", &glfwcursor_resource) == FAILURE) {
       return;
    }
    GLFWcursor *glfwcursor = phpglfw_fetch_glfwcursor(glfwcursor_resource );
    zend_list_close(Z_RES_P(glfwcursor_resource));
}
 
/**
 * glfwGetClipboardString
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetClipboardString, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwGetClipboardString)
{
    zval *glfwwindow_resource;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "r", &glfwwindow_resource) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource );
    RETURN_STRING(glfwGetClipboardString(glfwwindow));
}
 
/**
 * glfwGetCursorPos
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetCursorPos, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
    ZEND_ARG_INFO(1, xpos)
    ZEND_ARG_INFO(1, ypos)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwGetCursorPos)
{
    zval *glfwwindow_resource;
    zval *z_xpos;
    zval *z_ypos;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "rzz", &glfwwindow_resource, &z_xpos, &z_ypos) == FAILURE) {
       return;
    }
    ZVAL_DEREF(z_xpos); convert_to_double(z_xpos);
    ZVAL_DEREF(z_ypos); convert_to_double(z_ypos);
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource );
    glfwGetCursorPos(glfwwindow, (double *)&z_xpos->value, (double *)&z_ypos->value);
}
 
/**
 * glfwGetKey
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetKey, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwGetKey)
{
    zval *glfwwindow_resource;
    zend_long key;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "rl", &glfwwindow_resource, &key) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource );
    RETURN_LONG(glfwGetKey(glfwwindow, key));
}
 
/**
 * glfwGetMouseButton
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwGetMouseButton, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
    ZEND_ARG_INFO(0, key)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwGetMouseButton)
{
    zval *glfwwindow_resource;
    zend_long key;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "rl", &glfwwindow_resource, &key) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource );
    RETURN_LONG(glfwGetMouseButton(glfwwindow, key));
}
 
/**
 * glfwSetInputMode
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwSetInputMode, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
    ZEND_ARG_INFO(0, param)
    ZEND_ARG_INFO(0, value)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwSetInputMode)
{
    zval *glfwwindow_resource;
    zend_long param;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "rll", &glfwwindow_resource, &param, &value) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource );
    glfwSetInputMode(glfwwindow, param, value);
}
 
/**
 * glfwSetCursorPosCallback
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glfwSetCursorPosCallback, 0, 0, 1)
    ZEND_ARG_INFO(0, glfwwindow)
    ZEND_ARG_INFO(0, param)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glfwSetCursorPosCallback)
{
    zval *glfwwindow_resource;
    zend_long param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "rl", &glfwwindow_resource, &param) == FAILURE) {
       return;
    }
    GLFWwindow *glfwwindow = phpglfw_fetch_glfwwindow(glfwwindow_resource );
    glfwSetCursorPosCallback(glfwwindow, param);
}
 
/**
 * glCullFace
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCullFace, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCullFace)
{

    glCullFace();
}
 
/**
 * glFrontFace
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFrontFace, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFrontFace)
{

    glFrontFace();
}
 
/**
 * glHint
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glHint, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glHint)
{

    glHint();
}
 
/**
 * glLineWidth
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLineWidth, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLineWidth)
{

    glLineWidth();
}
 
/**
 * glPointSize
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPointSize, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPointSize)
{

    glPointSize();
}
 
/**
 * glPolygonMode
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPolygonMode, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPolygonMode)
{

    glPolygonMode();
}
 
/**
 * glScissor
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glScissor, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glScissor)
{

    glScissor();
}
 
/**
 * glTexParameterf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexParameterf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexParameterf)
{

    glTexParameterf();
}
 
/**
 * glTexParameterfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexParameterfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexParameterfv)
{

    glTexParameterfv();
}
 
/**
 * glTexParameteri
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexParameteri, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexParameteri)
{

    glTexParameteri();
}
 
/**
 * glTexParameteriv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexParameteriv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexParameteriv)
{

    glTexParameteriv();
}
 
/**
 * glTexImage1D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexImage1D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexImage1D)
{

    glTexImage1D();
}
 
/**
 * glTexImage2D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexImage2D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexImage2D)
{

    glTexImage2D();
}
 
/**
 * glDrawBuffer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDrawBuffer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDrawBuffer)
{

    glDrawBuffer();
}
 
/**
 * glClear
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClear, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClear)
{

    glClear();
}
 
/**
 * glClearColor
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClearColor, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClearColor)
{

    glClearColor();
}
 
/**
 * glClearStencil
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClearStencil, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClearStencil)
{

    glClearStencil();
}
 
/**
 * glClearDepth
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClearDepth, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClearDepth)
{

    glClearDepth();
}
 
/**
 * glStencilMask
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glStencilMask, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glStencilMask)
{

    glStencilMask();
}
 
/**
 * glColorMask
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColorMask, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColorMask)
{

    glColorMask();
}
 
/**
 * glDepthMask
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDepthMask, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDepthMask)
{

    glDepthMask();
}
 
/**
 * glDisable
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDisable, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDisable)
{

    glDisable();
}
 
/**
 * glEnable
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEnable, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEnable)
{

    glEnable();
}
 
/**
 * glFinish
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFinish, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFinish)
{

    glFinish();
}
 
/**
 * glFlush
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFlush, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFlush)
{

    glFlush();
}
 
/**
 * glBlendFunc
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBlendFunc, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBlendFunc)
{

    glBlendFunc();
}
 
/**
 * glLogicOp
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLogicOp, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLogicOp)
{

    glLogicOp();
}
 
/**
 * glStencilFunc
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glStencilFunc, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glStencilFunc)
{

    glStencilFunc();
}
 
/**
 * glStencilOp
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glStencilOp, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glStencilOp)
{

    glStencilOp();
}
 
/**
 * glDepthFunc
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDepthFunc, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDepthFunc)
{

    glDepthFunc();
}
 
/**
 * glPixelStoref
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPixelStoref, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPixelStoref)
{

    glPixelStoref();
}
 
/**
 * glPixelStorei
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPixelStorei, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPixelStorei)
{

    glPixelStorei();
}
 
/**
 * glReadBuffer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glReadBuffer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glReadBuffer)
{

    glReadBuffer();
}
 
/**
 * glReadPixels
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glReadPixels, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glReadPixels)
{

    glReadPixels();
}
 
/**
 * glGetBooleanv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetBooleanv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetBooleanv)
{

    glGetBooleanv();
}
 
/**
 * glGetDoublev
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetDoublev, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetDoublev)
{

    glGetDoublev();
}
 
/**
 * glGetError
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetError, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetError)
{

    glGetError();
}
 
/**
 * glGetFloatv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetFloatv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetFloatv)
{

    glGetFloatv();
}
 
/**
 * glGetIntegerv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetIntegerv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetIntegerv)
{

    glGetIntegerv();
}
 
/**
 * glGetString
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetString, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetString)
{

    glGetString();
}
 
/**
 * glGetTexImage
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTexImage, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTexImage)
{

    glGetTexImage();
}
 
/**
 * glGetTexParameterfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTexParameterfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTexParameterfv)
{

    glGetTexParameterfv();
}
 
/**
 * glGetTexParameteriv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTexParameteriv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTexParameteriv)
{

    glGetTexParameteriv();
}
 
/**
 * glGetTexLevelParameterfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTexLevelParameterfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTexLevelParameterfv)
{

    glGetTexLevelParameterfv();
}
 
/**
 * glGetTexLevelParameteriv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTexLevelParameteriv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTexLevelParameteriv)
{

    glGetTexLevelParameteriv();
}
 
/**
 * glIsEnabled
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIsEnabled, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIsEnabled)
{

    glIsEnabled();
}
 
/**
 * glDepthRange
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDepthRange, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDepthRange)
{

    glDepthRange();
}
 
/**
 * glViewport
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glViewport, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glViewport)
{

    glViewport();
}
 
/**
 * glNewList
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glNewList, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glNewList)
{

    glNewList();
}
 
/**
 * glEndList
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEndList, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEndList)
{

    glEndList();
}
 
/**
 * glCallList
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCallList, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCallList)
{

    glCallList();
}
 
/**
 * glCallLists
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCallLists, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCallLists)
{

    glCallLists();
}
 
/**
 * glDeleteLists
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDeleteLists, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDeleteLists)
{

    glDeleteLists();
}
 
/**
 * glGenLists
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGenLists, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGenLists)
{

    glGenLists();
}
 
/**
 * glListBase
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glListBase, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glListBase)
{

    glListBase();
}
 
/**
 * glBegin
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBegin, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBegin)
{

    glBegin();
}
 
/**
 * glBitmap
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBitmap, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBitmap)
{

    glBitmap();
}
 
/**
 * glColor3b
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3b, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3b)
{

    glColor3b();
}
 
/**
 * glColor3bv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3bv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3bv)
{

    glColor3bv();
}
 
/**
 * glColor3d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3d)
{

    glColor3d();
}
 
/**
 * glColor3dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3dv)
{

    glColor3dv();
}
 
/**
 * glColor3f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3f)
{

    glColor3f();
}
 
/**
 * glColor3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3fv)
{

    glColor3fv();
}
 
/**
 * glColor3i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3i)
{

    glColor3i();
}
 
/**
 * glColor3iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3iv)
{

    glColor3iv();
}
 
/**
 * glColor3s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3s)
{

    glColor3s();
}
 
/**
 * glColor3sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3sv)
{

    glColor3sv();
}
 
/**
 * glColor3ub
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3ub, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3ub)
{

    glColor3ub();
}
 
/**
 * glColor3ubv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3ubv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3ubv)
{

    glColor3ubv();
}
 
/**
 * glColor3ui
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3ui, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3ui)
{

    glColor3ui();
}
 
/**
 * glColor3uiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3uiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3uiv)
{

    glColor3uiv();
}
 
/**
 * glColor3us
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3us, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3us)
{

    glColor3us();
}
 
/**
 * glColor3usv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor3usv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor3usv)
{

    glColor3usv();
}
 
/**
 * glColor4b
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4b, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4b)
{

    glColor4b();
}
 
/**
 * glColor4bv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4bv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4bv)
{

    glColor4bv();
}
 
/**
 * glColor4d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4d)
{

    glColor4d();
}
 
/**
 * glColor4dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4dv)
{

    glColor4dv();
}
 
/**
 * glColor4f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4f)
{

    glColor4f();
}
 
/**
 * glColor4fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4fv)
{

    glColor4fv();
}
 
/**
 * glColor4i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4i)
{

    glColor4i();
}
 
/**
 * glColor4iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4iv)
{

    glColor4iv();
}
 
/**
 * glColor4s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4s)
{

    glColor4s();
}
 
/**
 * glColor4sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4sv)
{

    glColor4sv();
}
 
/**
 * glColor4ub
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4ub, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4ub)
{

    glColor4ub();
}
 
/**
 * glColor4ubv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4ubv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4ubv)
{

    glColor4ubv();
}
 
/**
 * glColor4ui
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4ui, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4ui)
{

    glColor4ui();
}
 
/**
 * glColor4uiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4uiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4uiv)
{

    glColor4uiv();
}
 
/**
 * glColor4us
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4us, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4us)
{

    glColor4us();
}
 
/**
 * glColor4usv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColor4usv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColor4usv)
{

    glColor4usv();
}
 
/**
 * glEdgeFlag
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEdgeFlag, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEdgeFlag)
{

    glEdgeFlag();
}
 
/**
 * glEdgeFlagv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEdgeFlagv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEdgeFlagv)
{

    glEdgeFlagv();
}
 
/**
 * glEnd
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEnd, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEnd)
{

    glEnd();
}
 
/**
 * glIndexd
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIndexd, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIndexd)
{

    glIndexd();
}
 
/**
 * glIndexdv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIndexdv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIndexdv)
{

    glIndexdv();
}
 
/**
 * glIndexf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIndexf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIndexf)
{

    glIndexf();
}
 
/**
 * glIndexfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIndexfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIndexfv)
{

    glIndexfv();
}
 
/**
 * glIndexi
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIndexi, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIndexi)
{

    glIndexi();
}
 
/**
 * glIndexiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIndexiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIndexiv)
{

    glIndexiv();
}
 
/**
 * glIndexs
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIndexs, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIndexs)
{

    glIndexs();
}
 
/**
 * glIndexsv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIndexsv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIndexsv)
{

    glIndexsv();
}
 
/**
 * glNormal3b
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glNormal3b, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glNormal3b)
{

    glNormal3b();
}
 
/**
 * glNormal3bv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glNormal3bv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glNormal3bv)
{

    glNormal3bv();
}
 
/**
 * glNormal3d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glNormal3d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glNormal3d)
{

    glNormal3d();
}
 
/**
 * glNormal3dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glNormal3dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glNormal3dv)
{

    glNormal3dv();
}
 
/**
 * glNormal3f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glNormal3f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glNormal3f)
{

    glNormal3f();
}
 
/**
 * glNormal3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glNormal3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glNormal3fv)
{

    glNormal3fv();
}
 
/**
 * glNormal3i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glNormal3i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glNormal3i)
{

    glNormal3i();
}
 
/**
 * glNormal3iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glNormal3iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glNormal3iv)
{

    glNormal3iv();
}
 
/**
 * glNormal3s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glNormal3s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glNormal3s)
{

    glNormal3s();
}
 
/**
 * glNormal3sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glNormal3sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glNormal3sv)
{

    glNormal3sv();
}
 
/**
 * glRasterPos2d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos2d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos2d)
{

    glRasterPos2d();
}
 
/**
 * glRasterPos2dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos2dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos2dv)
{

    glRasterPos2dv();
}
 
/**
 * glRasterPos2f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos2f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos2f)
{

    glRasterPos2f();
}
 
/**
 * glRasterPos2fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos2fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos2fv)
{

    glRasterPos2fv();
}
 
/**
 * glRasterPos2i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos2i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos2i)
{

    glRasterPos2i();
}
 
/**
 * glRasterPos2iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos2iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos2iv)
{

    glRasterPos2iv();
}
 
/**
 * glRasterPos2s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos2s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos2s)
{

    glRasterPos2s();
}
 
/**
 * glRasterPos2sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos2sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos2sv)
{

    glRasterPos2sv();
}
 
/**
 * glRasterPos3d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos3d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos3d)
{

    glRasterPos3d();
}
 
/**
 * glRasterPos3dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos3dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos3dv)
{

    glRasterPos3dv();
}
 
/**
 * glRasterPos3f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos3f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos3f)
{

    glRasterPos3f();
}
 
/**
 * glRasterPos3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos3fv)
{

    glRasterPos3fv();
}
 
/**
 * glRasterPos3i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos3i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos3i)
{

    glRasterPos3i();
}
 
/**
 * glRasterPos3iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos3iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos3iv)
{

    glRasterPos3iv();
}
 
/**
 * glRasterPos3s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos3s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos3s)
{

    glRasterPos3s();
}
 
/**
 * glRasterPos3sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos3sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos3sv)
{

    glRasterPos3sv();
}
 
/**
 * glRasterPos4d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos4d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos4d)
{

    glRasterPos4d();
}
 
/**
 * glRasterPos4dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos4dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos4dv)
{

    glRasterPos4dv();
}
 
/**
 * glRasterPos4f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos4f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos4f)
{

    glRasterPos4f();
}
 
/**
 * glRasterPos4fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos4fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos4fv)
{

    glRasterPos4fv();
}
 
/**
 * glRasterPos4i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos4i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos4i)
{

    glRasterPos4i();
}
 
/**
 * glRasterPos4iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos4iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos4iv)
{

    glRasterPos4iv();
}
 
/**
 * glRasterPos4s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos4s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos4s)
{

    glRasterPos4s();
}
 
/**
 * glRasterPos4sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRasterPos4sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRasterPos4sv)
{

    glRasterPos4sv();
}
 
/**
 * glRectd
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRectd, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRectd)
{

    glRectd();
}
 
/**
 * glRectdv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRectdv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRectdv)
{

    glRectdv();
}
 
/**
 * glRectf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRectf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRectf)
{

    glRectf();
}
 
/**
 * glRectfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRectfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRectfv)
{

    glRectfv();
}
 
/**
 * glRecti
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRecti, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRecti)
{

    glRecti();
}
 
/**
 * glRectiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRectiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRectiv)
{

    glRectiv();
}
 
/**
 * glRects
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRects, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRects)
{

    glRects();
}
 
/**
 * glRectsv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRectsv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRectsv)
{

    glRectsv();
}
 
/**
 * glTexCoord1d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord1d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord1d)
{

    glTexCoord1d();
}
 
/**
 * glTexCoord1dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord1dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord1dv)
{

    glTexCoord1dv();
}
 
/**
 * glTexCoord1f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord1f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord1f)
{

    glTexCoord1f();
}
 
/**
 * glTexCoord1fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord1fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord1fv)
{

    glTexCoord1fv();
}
 
/**
 * glTexCoord1i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord1i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord1i)
{

    glTexCoord1i();
}
 
/**
 * glTexCoord1iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord1iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord1iv)
{

    glTexCoord1iv();
}
 
/**
 * glTexCoord1s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord1s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord1s)
{

    glTexCoord1s();
}
 
/**
 * glTexCoord1sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord1sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord1sv)
{

    glTexCoord1sv();
}
 
/**
 * glTexCoord2d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord2d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord2d)
{

    glTexCoord2d();
}
 
/**
 * glTexCoord2dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord2dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord2dv)
{

    glTexCoord2dv();
}
 
/**
 * glTexCoord2f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord2f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord2f)
{

    glTexCoord2f();
}
 
/**
 * glTexCoord2fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord2fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord2fv)
{

    glTexCoord2fv();
}
 
/**
 * glTexCoord2i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord2i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord2i)
{

    glTexCoord2i();
}
 
/**
 * glTexCoord2iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord2iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord2iv)
{

    glTexCoord2iv();
}
 
/**
 * glTexCoord2s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord2s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord2s)
{

    glTexCoord2s();
}
 
/**
 * glTexCoord2sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord2sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord2sv)
{

    glTexCoord2sv();
}
 
/**
 * glTexCoord3d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord3d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord3d)
{

    glTexCoord3d();
}
 
/**
 * glTexCoord3dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord3dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord3dv)
{

    glTexCoord3dv();
}
 
/**
 * glTexCoord3f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord3f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord3f)
{

    glTexCoord3f();
}
 
/**
 * glTexCoord3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord3fv)
{

    glTexCoord3fv();
}
 
/**
 * glTexCoord3i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord3i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord3i)
{

    glTexCoord3i();
}
 
/**
 * glTexCoord3iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord3iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord3iv)
{

    glTexCoord3iv();
}
 
/**
 * glTexCoord3s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord3s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord3s)
{

    glTexCoord3s();
}
 
/**
 * glTexCoord3sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord3sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord3sv)
{

    glTexCoord3sv();
}
 
/**
 * glTexCoord4d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord4d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord4d)
{

    glTexCoord4d();
}
 
/**
 * glTexCoord4dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord4dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord4dv)
{

    glTexCoord4dv();
}
 
/**
 * glTexCoord4f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord4f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord4f)
{

    glTexCoord4f();
}
 
/**
 * glTexCoord4fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord4fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord4fv)
{

    glTexCoord4fv();
}
 
/**
 * glTexCoord4i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord4i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord4i)
{

    glTexCoord4i();
}
 
/**
 * glTexCoord4iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord4iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord4iv)
{

    glTexCoord4iv();
}
 
/**
 * glTexCoord4s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord4s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord4s)
{

    glTexCoord4s();
}
 
/**
 * glTexCoord4sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoord4sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoord4sv)
{

    glTexCoord4sv();
}
 
/**
 * glVertex2d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex2d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex2d)
{

    glVertex2d();
}
 
/**
 * glVertex2dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex2dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex2dv)
{

    glVertex2dv();
}
 
/**
 * glVertex2f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex2f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex2f)
{

    glVertex2f();
}
 
/**
 * glVertex2fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex2fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex2fv)
{

    glVertex2fv();
}
 
/**
 * glVertex2i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex2i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex2i)
{

    glVertex2i();
}
 
/**
 * glVertex2iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex2iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex2iv)
{

    glVertex2iv();
}
 
/**
 * glVertex2s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex2s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex2s)
{

    glVertex2s();
}
 
/**
 * glVertex2sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex2sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex2sv)
{

    glVertex2sv();
}
 
/**
 * glVertex3d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex3d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex3d)
{

    glVertex3d();
}
 
/**
 * glVertex3dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex3dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex3dv)
{

    glVertex3dv();
}
 
/**
 * glVertex3f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex3f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex3f)
{

    glVertex3f();
}
 
/**
 * glVertex3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex3fv)
{

    glVertex3fv();
}
 
/**
 * glVertex3i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex3i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex3i)
{

    glVertex3i();
}
 
/**
 * glVertex3iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex3iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex3iv)
{

    glVertex3iv();
}
 
/**
 * glVertex3s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex3s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex3s)
{

    glVertex3s();
}
 
/**
 * glVertex3sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex3sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex3sv)
{

    glVertex3sv();
}
 
/**
 * glVertex4d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex4d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex4d)
{

    glVertex4d();
}
 
/**
 * glVertex4dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex4dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex4dv)
{

    glVertex4dv();
}
 
/**
 * glVertex4f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex4f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex4f)
{

    glVertex4f();
}
 
/**
 * glVertex4fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex4fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex4fv)
{

    glVertex4fv();
}
 
/**
 * glVertex4i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex4i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex4i)
{

    glVertex4i();
}
 
/**
 * glVertex4iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex4iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex4iv)
{

    glVertex4iv();
}
 
/**
 * glVertex4s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex4s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex4s)
{

    glVertex4s();
}
 
/**
 * glVertex4sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertex4sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertex4sv)
{

    glVertex4sv();
}
 
/**
 * glClipPlane
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClipPlane, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClipPlane)
{

    glClipPlane();
}
 
/**
 * glColorMaterial
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColorMaterial, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColorMaterial)
{

    glColorMaterial();
}
 
/**
 * glFogf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFogf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFogf)
{

    glFogf();
}
 
/**
 * glFogfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFogfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFogfv)
{

    glFogfv();
}
 
/**
 * glFogi
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFogi, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFogi)
{

    glFogi();
}
 
/**
 * glFogiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFogiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFogiv)
{

    glFogiv();
}
 
/**
 * glLightf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLightf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLightf)
{

    glLightf();
}
 
/**
 * glLightfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLightfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLightfv)
{

    glLightfv();
}
 
/**
 * glLighti
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLighti, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLighti)
{

    glLighti();
}
 
/**
 * glLightiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLightiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLightiv)
{

    glLightiv();
}
 
/**
 * glLightModelf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLightModelf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLightModelf)
{

    glLightModelf();
}
 
/**
 * glLightModelfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLightModelfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLightModelfv)
{

    glLightModelfv();
}
 
/**
 * glLightModeli
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLightModeli, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLightModeli)
{

    glLightModeli();
}
 
/**
 * glLightModeliv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLightModeliv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLightModeliv)
{

    glLightModeliv();
}
 
/**
 * glLineStipple
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLineStipple, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLineStipple)
{

    glLineStipple();
}
 
/**
 * glMaterialf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMaterialf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMaterialf)
{

    glMaterialf();
}
 
/**
 * glMaterialfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMaterialfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMaterialfv)
{

    glMaterialfv();
}
 
/**
 * glMateriali
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMateriali, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMateriali)
{

    glMateriali();
}
 
/**
 * glMaterialiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMaterialiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMaterialiv)
{

    glMaterialiv();
}
 
/**
 * glPolygonStipple
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPolygonStipple, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPolygonStipple)
{

    glPolygonStipple();
}
 
/**
 * glShadeModel
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glShadeModel, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glShadeModel)
{

    glShadeModel();
}
 
/**
 * glTexEnvf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexEnvf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexEnvf)
{

    glTexEnvf();
}
 
/**
 * glTexEnvfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexEnvfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexEnvfv)
{

    glTexEnvfv();
}
 
/**
 * glTexEnvi
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexEnvi, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexEnvi)
{

    glTexEnvi();
}
 
/**
 * glTexEnviv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexEnviv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexEnviv)
{

    glTexEnviv();
}
 
/**
 * glTexGend
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexGend, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexGend)
{

    glTexGend();
}
 
/**
 * glTexGendv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexGendv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexGendv)
{

    glTexGendv();
}
 
/**
 * glTexGenf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexGenf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexGenf)
{

    glTexGenf();
}
 
/**
 * glTexGenfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexGenfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexGenfv)
{

    glTexGenfv();
}
 
/**
 * glTexGeni
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexGeni, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexGeni)
{

    glTexGeni();
}
 
/**
 * glTexGeniv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexGeniv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexGeniv)
{

    glTexGeniv();
}
 
/**
 * glFeedbackBuffer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFeedbackBuffer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFeedbackBuffer)
{

    glFeedbackBuffer();
}
 
/**
 * glSelectBuffer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSelectBuffer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSelectBuffer)
{

    glSelectBuffer();
}
 
/**
 * glRenderMode
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRenderMode, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRenderMode)
{

    glRenderMode();
}
 
/**
 * glInitNames
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glInitNames, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glInitNames)
{

    glInitNames();
}
 
/**
 * glLoadName
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLoadName, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLoadName)
{

    glLoadName();
}
 
/**
 * glPassThrough
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPassThrough, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPassThrough)
{

    glPassThrough();
}
 
/**
 * glPopName
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPopName, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPopName)
{

    glPopName();
}
 
/**
 * glPushName
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPushName, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPushName)
{

    glPushName();
}
 
/**
 * glClearAccum
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClearAccum, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClearAccum)
{

    glClearAccum();
}
 
/**
 * glClearIndex
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClearIndex, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClearIndex)
{

    glClearIndex();
}
 
/**
 * glIndexMask
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIndexMask, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIndexMask)
{

    glIndexMask();
}
 
/**
 * glAccum
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glAccum, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glAccum)
{

    glAccum();
}
 
/**
 * glPopAttrib
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPopAttrib, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPopAttrib)
{

    glPopAttrib();
}
 
/**
 * glPushAttrib
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPushAttrib, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPushAttrib)
{

    glPushAttrib();
}
 
/**
 * glMap1d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMap1d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMap1d)
{

    glMap1d();
}
 
/**
 * glMap1f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMap1f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMap1f)
{

    glMap1f();
}
 
/**
 * glMap2d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMap2d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMap2d)
{

    glMap2d();
}
 
/**
 * glMap2f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMap2f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMap2f)
{

    glMap2f();
}
 
/**
 * glMapGrid1d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMapGrid1d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMapGrid1d)
{

    glMapGrid1d();
}
 
/**
 * glMapGrid1f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMapGrid1f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMapGrid1f)
{

    glMapGrid1f();
}
 
/**
 * glMapGrid2d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMapGrid2d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMapGrid2d)
{

    glMapGrid2d();
}
 
/**
 * glMapGrid2f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMapGrid2f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMapGrid2f)
{

    glMapGrid2f();
}
 
/**
 * glEvalCoord1d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEvalCoord1d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEvalCoord1d)
{

    glEvalCoord1d();
}
 
/**
 * glEvalCoord1dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEvalCoord1dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEvalCoord1dv)
{

    glEvalCoord1dv();
}
 
/**
 * glEvalCoord1f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEvalCoord1f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEvalCoord1f)
{

    glEvalCoord1f();
}
 
/**
 * glEvalCoord1fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEvalCoord1fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEvalCoord1fv)
{

    glEvalCoord1fv();
}
 
/**
 * glEvalCoord2d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEvalCoord2d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEvalCoord2d)
{

    glEvalCoord2d();
}
 
/**
 * glEvalCoord2dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEvalCoord2dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEvalCoord2dv)
{

    glEvalCoord2dv();
}
 
/**
 * glEvalCoord2f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEvalCoord2f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEvalCoord2f)
{

    glEvalCoord2f();
}
 
/**
 * glEvalCoord2fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEvalCoord2fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEvalCoord2fv)
{

    glEvalCoord2fv();
}
 
/**
 * glEvalMesh1
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEvalMesh1, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEvalMesh1)
{

    glEvalMesh1();
}
 
/**
 * glEvalPoint1
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEvalPoint1, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEvalPoint1)
{

    glEvalPoint1();
}
 
/**
 * glEvalMesh2
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEvalMesh2, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEvalMesh2)
{

    glEvalMesh2();
}
 
/**
 * glEvalPoint2
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEvalPoint2, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEvalPoint2)
{

    glEvalPoint2();
}
 
/**
 * glAlphaFunc
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glAlphaFunc, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glAlphaFunc)
{

    glAlphaFunc();
}
 
/**
 * glPixelZoom
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPixelZoom, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPixelZoom)
{

    glPixelZoom();
}
 
/**
 * glPixelTransferf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPixelTransferf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPixelTransferf)
{

    glPixelTransferf();
}
 
/**
 * glPixelTransferi
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPixelTransferi, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPixelTransferi)
{

    glPixelTransferi();
}
 
/**
 * glPixelMapfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPixelMapfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPixelMapfv)
{

    glPixelMapfv();
}
 
/**
 * glPixelMapuiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPixelMapuiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPixelMapuiv)
{

    glPixelMapuiv();
}
 
/**
 * glPixelMapusv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPixelMapusv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPixelMapusv)
{

    glPixelMapusv();
}
 
/**
 * glCopyPixels
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCopyPixels, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCopyPixels)
{

    glCopyPixels();
}
 
/**
 * glDrawPixels
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDrawPixels, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDrawPixels)
{

    glDrawPixels();
}
 
/**
 * glGetClipPlane
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetClipPlane, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetClipPlane)
{

    glGetClipPlane();
}
 
/**
 * glGetLightfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetLightfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetLightfv)
{

    glGetLightfv();
}
 
/**
 * glGetLightiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetLightiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetLightiv)
{

    glGetLightiv();
}
 
/**
 * glGetMapdv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetMapdv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetMapdv)
{

    glGetMapdv();
}
 
/**
 * glGetMapfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetMapfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetMapfv)
{

    glGetMapfv();
}
 
/**
 * glGetMapiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetMapiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetMapiv)
{

    glGetMapiv();
}
 
/**
 * glGetMaterialfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetMaterialfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetMaterialfv)
{

    glGetMaterialfv();
}
 
/**
 * glGetMaterialiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetMaterialiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetMaterialiv)
{

    glGetMaterialiv();
}
 
/**
 * glGetPixelMapfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetPixelMapfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetPixelMapfv)
{

    glGetPixelMapfv();
}
 
/**
 * glGetPixelMapuiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetPixelMapuiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetPixelMapuiv)
{

    glGetPixelMapuiv();
}
 
/**
 * glGetPixelMapusv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetPixelMapusv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetPixelMapusv)
{

    glGetPixelMapusv();
}
 
/**
 * glGetPolygonStipple
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetPolygonStipple, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetPolygonStipple)
{

    glGetPolygonStipple();
}
 
/**
 * glGetTexEnvfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTexEnvfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTexEnvfv)
{

    glGetTexEnvfv();
}
 
/**
 * glGetTexEnviv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTexEnviv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTexEnviv)
{

    glGetTexEnviv();
}
 
/**
 * glGetTexGendv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTexGendv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTexGendv)
{

    glGetTexGendv();
}
 
/**
 * glGetTexGenfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTexGenfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTexGenfv)
{

    glGetTexGenfv();
}
 
/**
 * glGetTexGeniv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTexGeniv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTexGeniv)
{

    glGetTexGeniv();
}
 
/**
 * glIsList
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIsList, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIsList)
{

    glIsList();
}
 
/**
 * glFrustum
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFrustum, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFrustum)
{

    glFrustum();
}
 
/**
 * glLoadIdentity
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLoadIdentity, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLoadIdentity)
{

    glLoadIdentity();
}
 
/**
 * glLoadMatrixf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLoadMatrixf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLoadMatrixf)
{

    glLoadMatrixf();
}
 
/**
 * glLoadMatrixd
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLoadMatrixd, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLoadMatrixd)
{

    glLoadMatrixd();
}
 
/**
 * glMatrixMode
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMatrixMode, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMatrixMode)
{

    glMatrixMode();
}
 
/**
 * glMultMatrixf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultMatrixf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultMatrixf)
{

    glMultMatrixf();
}
 
/**
 * glMultMatrixd
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultMatrixd, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultMatrixd)
{

    glMultMatrixd();
}
 
/**
 * glOrtho
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glOrtho, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glOrtho)
{

    glOrtho();
}
 
/**
 * glPopMatrix
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPopMatrix, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPopMatrix)
{

    glPopMatrix();
}
 
/**
 * glPushMatrix
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPushMatrix, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPushMatrix)
{

    glPushMatrix();
}
 
/**
 * glRotated
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRotated, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRotated)
{

    glRotated();
}
 
/**
 * glRotatef
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glRotatef, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glRotatef)
{

    glRotatef();
}
 
/**
 * glScaled
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glScaled, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glScaled)
{

    glScaled();
}
 
/**
 * glScalef
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glScalef, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glScalef)
{

    glScalef();
}
 
/**
 * glTranslated
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTranslated, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTranslated)
{

    glTranslated();
}
 
/**
 * glTranslatef
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTranslatef, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTranslatef)
{

    glTranslatef();
}
 
/**
 * glDrawArrays
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDrawArrays, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDrawArrays)
{

    glDrawArrays();
}
 
/**
 * glDrawElements
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDrawElements, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDrawElements)
{

    glDrawElements();
}
 
/**
 * glGetPointerv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetPointerv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetPointerv)
{

    glGetPointerv();
}
 
/**
 * glPolygonOffset
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPolygonOffset, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPolygonOffset)
{

    glPolygonOffset();
}
 
/**
 * glCopyTexImage1D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCopyTexImage1D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCopyTexImage1D)
{

    glCopyTexImage1D();
}
 
/**
 * glCopyTexImage2D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCopyTexImage2D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCopyTexImage2D)
{

    glCopyTexImage2D();
}
 
/**
 * glCopyTexSubImage1D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCopyTexSubImage1D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCopyTexSubImage1D)
{

    glCopyTexSubImage1D();
}
 
/**
 * glCopyTexSubImage2D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCopyTexSubImage2D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCopyTexSubImage2D)
{

    glCopyTexSubImage2D();
}
 
/**
 * glTexSubImage1D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexSubImage1D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexSubImage1D)
{

    glTexSubImage1D();
}
 
/**
 * glTexSubImage2D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexSubImage2D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexSubImage2D)
{

    glTexSubImage2D();
}
 
/**
 * glBindTexture
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBindTexture, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBindTexture)
{

    glBindTexture();
}
 
/**
 * glDeleteTextures
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDeleteTextures, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDeleteTextures)
{

    glDeleteTextures();
}
 
/**
 * glGenTextures
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGenTextures, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGenTextures)
{

    glGenTextures();
}
 
/**
 * glIsTexture
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIsTexture, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIsTexture)
{

    glIsTexture();
}
 
/**
 * glArrayElement
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glArrayElement, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glArrayElement)
{

    glArrayElement();
}
 
/**
 * glColorPointer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColorPointer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColorPointer)
{

    glColorPointer();
}
 
/**
 * glDisableClientState
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDisableClientState, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDisableClientState)
{

    glDisableClientState();
}
 
/**
 * glEdgeFlagPointer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEdgeFlagPointer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEdgeFlagPointer)
{

    glEdgeFlagPointer();
}
 
/**
 * glEnableClientState
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEnableClientState, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEnableClientState)
{

    glEnableClientState();
}
 
/**
 * glIndexPointer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIndexPointer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIndexPointer)
{

    glIndexPointer();
}
 
/**
 * glInterleavedArrays
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glInterleavedArrays, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glInterleavedArrays)
{

    glInterleavedArrays();
}
 
/**
 * glNormalPointer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glNormalPointer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glNormalPointer)
{

    glNormalPointer();
}
 
/**
 * glTexCoordPointer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexCoordPointer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexCoordPointer)
{

    glTexCoordPointer();
}
 
/**
 * glVertexPointer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexPointer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexPointer)
{

    glVertexPointer();
}
 
/**
 * glAreTexturesResident
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glAreTexturesResident, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glAreTexturesResident)
{

    glAreTexturesResident();
}
 
/**
 * glPrioritizeTextures
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPrioritizeTextures, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPrioritizeTextures)
{

    glPrioritizeTextures();
}
 
/**
 * glIndexub
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIndexub, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIndexub)
{

    glIndexub();
}
 
/**
 * glIndexubv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIndexubv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIndexubv)
{

    glIndexubv();
}
 
/**
 * glPopClientAttrib
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPopClientAttrib, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPopClientAttrib)
{

    glPopClientAttrib();
}
 
/**
 * glPushClientAttrib
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPushClientAttrib, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPushClientAttrib)
{

    glPushClientAttrib();
}
 
/**
 * glDrawRangeElements
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDrawRangeElements, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDrawRangeElements)
{

    glDrawRangeElements();
}
 
/**
 * glTexImage3D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexImage3D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexImage3D)
{

    glTexImage3D();
}
 
/**
 * glTexSubImage3D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexSubImage3D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexSubImage3D)
{

    glTexSubImage3D();
}
 
/**
 * glCopyTexSubImage3D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCopyTexSubImage3D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCopyTexSubImage3D)
{

    glCopyTexSubImage3D();
}
 
/**
 * glActiveTexture
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glActiveTexture, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glActiveTexture)
{

    glActiveTexture();
}
 
/**
 * glSampleCoverage
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSampleCoverage, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSampleCoverage)
{

    glSampleCoverage();
}
 
/**
 * glCompressedTexImage3D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCompressedTexImage3D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCompressedTexImage3D)
{

    glCompressedTexImage3D();
}
 
/**
 * glCompressedTexImage2D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCompressedTexImage2D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCompressedTexImage2D)
{

    glCompressedTexImage2D();
}
 
/**
 * glCompressedTexImage1D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCompressedTexImage1D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCompressedTexImage1D)
{

    glCompressedTexImage1D();
}
 
/**
 * glCompressedTexSubImage3D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCompressedTexSubImage3D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCompressedTexSubImage3D)
{

    glCompressedTexSubImage3D();
}
 
/**
 * glCompressedTexSubImage2D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCompressedTexSubImage2D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCompressedTexSubImage2D)
{

    glCompressedTexSubImage2D();
}
 
/**
 * glCompressedTexSubImage1D
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCompressedTexSubImage1D, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCompressedTexSubImage1D)
{

    glCompressedTexSubImage1D();
}
 
/**
 * glGetCompressedTexImage
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetCompressedTexImage, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetCompressedTexImage)
{

    glGetCompressedTexImage();
}
 
/**
 * glClientActiveTexture
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClientActiveTexture, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClientActiveTexture)
{

    glClientActiveTexture();
}
 
/**
 * glMultiTexCoord1d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord1d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord1d)
{

    glMultiTexCoord1d();
}
 
/**
 * glMultiTexCoord1dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord1dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord1dv)
{

    glMultiTexCoord1dv();
}
 
/**
 * glMultiTexCoord1f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord1f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord1f)
{

    glMultiTexCoord1f();
}
 
/**
 * glMultiTexCoord1fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord1fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord1fv)
{

    glMultiTexCoord1fv();
}
 
/**
 * glMultiTexCoord1i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord1i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord1i)
{

    glMultiTexCoord1i();
}
 
/**
 * glMultiTexCoord1iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord1iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord1iv)
{

    glMultiTexCoord1iv();
}
 
/**
 * glMultiTexCoord1s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord1s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord1s)
{

    glMultiTexCoord1s();
}
 
/**
 * glMultiTexCoord1sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord1sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord1sv)
{

    glMultiTexCoord1sv();
}
 
/**
 * glMultiTexCoord2d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord2d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord2d)
{

    glMultiTexCoord2d();
}
 
/**
 * glMultiTexCoord2dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord2dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord2dv)
{

    glMultiTexCoord2dv();
}
 
/**
 * glMultiTexCoord2f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord2f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord2f)
{

    glMultiTexCoord2f();
}
 
/**
 * glMultiTexCoord2fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord2fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord2fv)
{

    glMultiTexCoord2fv();
}
 
/**
 * glMultiTexCoord2i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord2i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord2i)
{

    glMultiTexCoord2i();
}
 
/**
 * glMultiTexCoord2iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord2iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord2iv)
{

    glMultiTexCoord2iv();
}
 
/**
 * glMultiTexCoord2s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord2s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord2s)
{

    glMultiTexCoord2s();
}
 
/**
 * glMultiTexCoord2sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord2sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord2sv)
{

    glMultiTexCoord2sv();
}
 
/**
 * glMultiTexCoord3d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord3d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord3d)
{

    glMultiTexCoord3d();
}
 
/**
 * glMultiTexCoord3dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord3dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord3dv)
{

    glMultiTexCoord3dv();
}
 
/**
 * glMultiTexCoord3f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord3f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord3f)
{

    glMultiTexCoord3f();
}
 
/**
 * glMultiTexCoord3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord3fv)
{

    glMultiTexCoord3fv();
}
 
/**
 * glMultiTexCoord3i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord3i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord3i)
{

    glMultiTexCoord3i();
}
 
/**
 * glMultiTexCoord3iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord3iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord3iv)
{

    glMultiTexCoord3iv();
}
 
/**
 * glMultiTexCoord3s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord3s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord3s)
{

    glMultiTexCoord3s();
}
 
/**
 * glMultiTexCoord3sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord3sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord3sv)
{

    glMultiTexCoord3sv();
}
 
/**
 * glMultiTexCoord4d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord4d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord4d)
{

    glMultiTexCoord4d();
}
 
/**
 * glMultiTexCoord4dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord4dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord4dv)
{

    glMultiTexCoord4dv();
}
 
/**
 * glMultiTexCoord4f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord4f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord4f)
{

    glMultiTexCoord4f();
}
 
/**
 * glMultiTexCoord4fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord4fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord4fv)
{

    glMultiTexCoord4fv();
}
 
/**
 * glMultiTexCoord4i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord4i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord4i)
{

    glMultiTexCoord4i();
}
 
/**
 * glMultiTexCoord4iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord4iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord4iv)
{

    glMultiTexCoord4iv();
}
 
/**
 * glMultiTexCoord4s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord4s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord4s)
{

    glMultiTexCoord4s();
}
 
/**
 * glMultiTexCoord4sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiTexCoord4sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiTexCoord4sv)
{

    glMultiTexCoord4sv();
}
 
/**
 * glLoadTransposeMatrixf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLoadTransposeMatrixf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLoadTransposeMatrixf)
{

    glLoadTransposeMatrixf();
}
 
/**
 * glLoadTransposeMatrixd
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLoadTransposeMatrixd, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLoadTransposeMatrixd)
{

    glLoadTransposeMatrixd();
}
 
/**
 * glMultTransposeMatrixf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultTransposeMatrixf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultTransposeMatrixf)
{

    glMultTransposeMatrixf();
}
 
/**
 * glMultTransposeMatrixd
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultTransposeMatrixd, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultTransposeMatrixd)
{

    glMultTransposeMatrixd();
}
 
/**
 * glBlendFuncSeparate
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBlendFuncSeparate, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBlendFuncSeparate)
{

    glBlendFuncSeparate();
}
 
/**
 * glMultiDrawArrays
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiDrawArrays, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiDrawArrays)
{

    glMultiDrawArrays();
}
 
/**
 * glMultiDrawElements
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMultiDrawElements, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMultiDrawElements)
{

    glMultiDrawElements();
}
 
/**
 * glPointParameterf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPointParameterf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPointParameterf)
{

    glPointParameterf();
}
 
/**
 * glPointParameterfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPointParameterfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPointParameterfv)
{

    glPointParameterfv();
}
 
/**
 * glPointParameteri
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPointParameteri, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPointParameteri)
{

    glPointParameteri();
}
 
/**
 * glPointParameteriv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPointParameteriv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPointParameteriv)
{

    glPointParameteriv();
}
 
/**
 * glFogCoordf
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFogCoordf, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFogCoordf)
{

    glFogCoordf();
}
 
/**
 * glFogCoordfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFogCoordfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFogCoordfv)
{

    glFogCoordfv();
}
 
/**
 * glFogCoordd
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFogCoordd, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFogCoordd)
{

    glFogCoordd();
}
 
/**
 * glFogCoorddv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFogCoorddv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFogCoorddv)
{

    glFogCoorddv();
}
 
/**
 * glFogCoordPointer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glFogCoordPointer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glFogCoordPointer)
{

    glFogCoordPointer();
}
 
/**
 * glSecondaryColor3b
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3b, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3b)
{

    glSecondaryColor3b();
}
 
/**
 * glSecondaryColor3bv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3bv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3bv)
{

    glSecondaryColor3bv();
}
 
/**
 * glSecondaryColor3d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3d)
{

    glSecondaryColor3d();
}
 
/**
 * glSecondaryColor3dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3dv)
{

    glSecondaryColor3dv();
}
 
/**
 * glSecondaryColor3f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3f)
{

    glSecondaryColor3f();
}
 
/**
 * glSecondaryColor3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3fv)
{

    glSecondaryColor3fv();
}
 
/**
 * glSecondaryColor3i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3i)
{

    glSecondaryColor3i();
}
 
/**
 * glSecondaryColor3iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3iv)
{

    glSecondaryColor3iv();
}
 
/**
 * glSecondaryColor3s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3s)
{

    glSecondaryColor3s();
}
 
/**
 * glSecondaryColor3sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3sv)
{

    glSecondaryColor3sv();
}
 
/**
 * glSecondaryColor3ub
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3ub, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3ub)
{

    glSecondaryColor3ub();
}
 
/**
 * glSecondaryColor3ubv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3ubv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3ubv)
{

    glSecondaryColor3ubv();
}
 
/**
 * glSecondaryColor3ui
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3ui, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3ui)
{

    glSecondaryColor3ui();
}
 
/**
 * glSecondaryColor3uiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3uiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3uiv)
{

    glSecondaryColor3uiv();
}
 
/**
 * glSecondaryColor3us
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3us, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3us)
{

    glSecondaryColor3us();
}
 
/**
 * glSecondaryColor3usv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColor3usv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColor3usv)
{

    glSecondaryColor3usv();
}
 
/**
 * glSecondaryColorPointer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glSecondaryColorPointer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glSecondaryColorPointer)
{

    glSecondaryColorPointer();
}
 
/**
 * glWindowPos2d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos2d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos2d)
{

    glWindowPos2d();
}
 
/**
 * glWindowPos2dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos2dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos2dv)
{

    glWindowPos2dv();
}
 
/**
 * glWindowPos2f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos2f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos2f)
{

    glWindowPos2f();
}
 
/**
 * glWindowPos2fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos2fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos2fv)
{

    glWindowPos2fv();
}
 
/**
 * glWindowPos2i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos2i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos2i)
{

    glWindowPos2i();
}
 
/**
 * glWindowPos2iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos2iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos2iv)
{

    glWindowPos2iv();
}
 
/**
 * glWindowPos2s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos2s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos2s)
{

    glWindowPos2s();
}
 
/**
 * glWindowPos2sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos2sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos2sv)
{

    glWindowPos2sv();
}
 
/**
 * glWindowPos3d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos3d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos3d)
{

    glWindowPos3d();
}
 
/**
 * glWindowPos3dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos3dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos3dv)
{

    glWindowPos3dv();
}
 
/**
 * glWindowPos3f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos3f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos3f)
{

    glWindowPos3f();
}
 
/**
 * glWindowPos3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos3fv)
{

    glWindowPos3fv();
}
 
/**
 * glWindowPos3i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos3i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos3i)
{

    glWindowPos3i();
}
 
/**
 * glWindowPos3iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos3iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos3iv)
{

    glWindowPos3iv();
}
 
/**
 * glWindowPos3s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos3s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos3s)
{

    glWindowPos3s();
}
 
/**
 * glWindowPos3sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glWindowPos3sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glWindowPos3sv)
{

    glWindowPos3sv();
}
 
/**
 * glGenQueries
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGenQueries, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGenQueries)
{

    glGenQueries();
}
 
/**
 * glDeleteQueries
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDeleteQueries, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDeleteQueries)
{

    glDeleteQueries();
}
 
/**
 * glIsQuery
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIsQuery, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIsQuery)
{

    glIsQuery();
}
 
/**
 * glBeginQuery
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBeginQuery, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBeginQuery)
{

    glBeginQuery();
}
 
/**
 * glEndQuery
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEndQuery, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEndQuery)
{

    glEndQuery();
}
 
/**
 * glGetQueryiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetQueryiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetQueryiv)
{

    glGetQueryiv();
}
 
/**
 * glGetQueryObjectiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetQueryObjectiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetQueryObjectiv)
{

    glGetQueryObjectiv();
}
 
/**
 * glGetQueryObjectuiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetQueryObjectuiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetQueryObjectuiv)
{

    glGetQueryObjectuiv();
}
 
/**
 * glBindBuffer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBindBuffer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBindBuffer)
{

    glBindBuffer();
}
 
/**
 * glDeleteBuffers
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDeleteBuffers, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDeleteBuffers)
{

    glDeleteBuffers();
}
 
/**
 * glGenBuffers
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGenBuffers, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGenBuffers)
{

    glGenBuffers();
}
 
/**
 * glIsBuffer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIsBuffer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIsBuffer)
{

    glIsBuffer();
}
 
/**
 * glBufferData
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBufferData, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBufferData)
{

    glBufferData();
}
 
/**
 * glBufferSubData
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBufferSubData, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBufferSubData)
{

    glBufferSubData();
}
 
/**
 * glGetBufferSubData
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetBufferSubData, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetBufferSubData)
{

    glGetBufferSubData();
}
 
/**
 * glMapBuffer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glMapBuffer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glMapBuffer)
{

    glMapBuffer();
}
 
/**
 * glUnmapBuffer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUnmapBuffer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUnmapBuffer)
{

    glUnmapBuffer();
}
 
/**
 * glGetBufferParameteriv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetBufferParameteriv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetBufferParameteriv)
{

    glGetBufferParameteriv();
}
 
/**
 * glGetBufferPointerv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetBufferPointerv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetBufferPointerv)
{

    glGetBufferPointerv();
}
 
/**
 * glBlendEquationSeparate
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBlendEquationSeparate, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBlendEquationSeparate)
{

    glBlendEquationSeparate();
}
 
/**
 * glDrawBuffers
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDrawBuffers, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDrawBuffers)
{

    glDrawBuffers();
}
 
/**
 * glStencilOpSeparate
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glStencilOpSeparate, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glStencilOpSeparate)
{

    glStencilOpSeparate();
}
 
/**
 * glStencilFuncSeparate
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glStencilFuncSeparate, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glStencilFuncSeparate)
{

    glStencilFuncSeparate();
}
 
/**
 * glStencilMaskSeparate
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glStencilMaskSeparate, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glStencilMaskSeparate)
{

    glStencilMaskSeparate();
}
 
/**
 * glAttachShader
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glAttachShader, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glAttachShader)
{

    glAttachShader();
}
 
/**
 * glBindAttribLocation
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBindAttribLocation, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBindAttribLocation)
{

    glBindAttribLocation();
}
 
/**
 * glCompileShader
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCompileShader, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCompileShader)
{

    glCompileShader();
}
 
/**
 * glCreateProgram
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCreateProgram, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCreateProgram)
{

    glCreateProgram();
}
 
/**
 * glCreateShader
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glCreateShader, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glCreateShader)
{

    glCreateShader();
}
 
/**
 * glDeleteProgram
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDeleteProgram, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDeleteProgram)
{

    glDeleteProgram();
}
 
/**
 * glDeleteShader
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDeleteShader, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDeleteShader)
{

    glDeleteShader();
}
 
/**
 * glDetachShader
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDetachShader, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDetachShader)
{

    glDetachShader();
}
 
/**
 * glDisableVertexAttribArray
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDisableVertexAttribArray, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDisableVertexAttribArray)
{

    glDisableVertexAttribArray();
}
 
/**
 * glEnableVertexAttribArray
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEnableVertexAttribArray, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEnableVertexAttribArray)
{

    glEnableVertexAttribArray();
}
 
/**
 * glGetActiveAttrib
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetActiveAttrib, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetActiveAttrib)
{

    glGetActiveAttrib();
}
 
/**
 * glGetActiveUniform
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetActiveUniform, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetActiveUniform)
{

    glGetActiveUniform();
}
 
/**
 * glGetAttachedShaders
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetAttachedShaders, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetAttachedShaders)
{

    glGetAttachedShaders();
}
 
/**
 * glGetAttribLocation
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetAttribLocation, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetAttribLocation)
{

    glGetAttribLocation();
}
 
/**
 * glGetProgramiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetProgramiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetProgramiv)
{

    glGetProgramiv();
}
 
/**
 * glGetProgramInfoLog
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetProgramInfoLog, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetProgramInfoLog)
{

    glGetProgramInfoLog();
}
 
/**
 * glGetShaderiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetShaderiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetShaderiv)
{

    glGetShaderiv();
}
 
/**
 * glGetShaderInfoLog
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetShaderInfoLog, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetShaderInfoLog)
{

    glGetShaderInfoLog();
}
 
/**
 * glGetShaderSource
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetShaderSource, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetShaderSource)
{

    glGetShaderSource();
}
 
/**
 * glGetUniformLocation
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetUniformLocation, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetUniformLocation)
{

    glGetUniformLocation();
}
 
/**
 * glGetUniformfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetUniformfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetUniformfv)
{

    glGetUniformfv();
}
 
/**
 * glGetUniformiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetUniformiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetUniformiv)
{

    glGetUniformiv();
}
 
/**
 * glGetVertexAttribdv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetVertexAttribdv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetVertexAttribdv)
{

    glGetVertexAttribdv();
}
 
/**
 * glGetVertexAttribfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetVertexAttribfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetVertexAttribfv)
{

    glGetVertexAttribfv();
}
 
/**
 * glGetVertexAttribiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetVertexAttribiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetVertexAttribiv)
{

    glGetVertexAttribiv();
}
 
/**
 * glGetVertexAttribPointerv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetVertexAttribPointerv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetVertexAttribPointerv)
{

    glGetVertexAttribPointerv();
}
 
/**
 * glIsProgram
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIsProgram, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIsProgram)
{

    glIsProgram();
}
 
/**
 * glIsShader
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIsShader, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIsShader)
{

    glIsShader();
}
 
/**
 * glLinkProgram
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glLinkProgram, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glLinkProgram)
{

    glLinkProgram();
}
 
/**
 * glShaderSource
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glShaderSource, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glShaderSource)
{

    glShaderSource();
}
 
/**
 * glUseProgram
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUseProgram, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUseProgram)
{

    glUseProgram();
}
 
/**
 * glUniform1f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform1f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform1f)
{

    glUniform1f();
}
 
/**
 * glUniform2f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform2f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform2f)
{

    glUniform2f();
}
 
/**
 * glUniform3f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform3f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform3f)
{

    glUniform3f();
}
 
/**
 * glUniform4f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform4f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform4f)
{

    glUniform4f();
}
 
/**
 * glUniform1i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform1i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform1i)
{

    glUniform1i();
}
 
/**
 * glUniform2i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform2i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform2i)
{

    glUniform2i();
}
 
/**
 * glUniform3i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform3i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform3i)
{

    glUniform3i();
}
 
/**
 * glUniform4i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform4i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform4i)
{

    glUniform4i();
}
 
/**
 * glUniform1fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform1fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform1fv)
{

    glUniform1fv();
}
 
/**
 * glUniform2fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform2fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform2fv)
{

    glUniform2fv();
}
 
/**
 * glUniform3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform3fv)
{

    glUniform3fv();
}
 
/**
 * glUniform4fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform4fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform4fv)
{

    glUniform4fv();
}
 
/**
 * glUniform1iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform1iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform1iv)
{

    glUniform1iv();
}
 
/**
 * glUniform2iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform2iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform2iv)
{

    glUniform2iv();
}
 
/**
 * glUniform3iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform3iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform3iv)
{

    glUniform3iv();
}
 
/**
 * glUniform4iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform4iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform4iv)
{

    glUniform4iv();
}
 
/**
 * glUniformMatrix2fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniformMatrix2fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniformMatrix2fv)
{

    glUniformMatrix2fv();
}
 
/**
 * glUniformMatrix3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniformMatrix3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniformMatrix3fv)
{

    glUniformMatrix3fv();
}
 
/**
 * glUniformMatrix4fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniformMatrix4fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniformMatrix4fv)
{

    glUniformMatrix4fv();
}
 
/**
 * glValidateProgram
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glValidateProgram, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glValidateProgram)
{

    glValidateProgram();
}
 
/**
 * glVertexAttrib1d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib1d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib1d)
{

    glVertexAttrib1d();
}
 
/**
 * glVertexAttrib1dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib1dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib1dv)
{

    glVertexAttrib1dv();
}
 
/**
 * glVertexAttrib1f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib1f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib1f)
{

    glVertexAttrib1f();
}
 
/**
 * glVertexAttrib1fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib1fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib1fv)
{

    glVertexAttrib1fv();
}
 
/**
 * glVertexAttrib1s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib1s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib1s)
{

    glVertexAttrib1s();
}
 
/**
 * glVertexAttrib1sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib1sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib1sv)
{

    glVertexAttrib1sv();
}
 
/**
 * glVertexAttrib2d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib2d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib2d)
{

    glVertexAttrib2d();
}
 
/**
 * glVertexAttrib2dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib2dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib2dv)
{

    glVertexAttrib2dv();
}
 
/**
 * glVertexAttrib2f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib2f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib2f)
{

    glVertexAttrib2f();
}
 
/**
 * glVertexAttrib2fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib2fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib2fv)
{

    glVertexAttrib2fv();
}
 
/**
 * glVertexAttrib2s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib2s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib2s)
{

    glVertexAttrib2s();
}
 
/**
 * glVertexAttrib2sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib2sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib2sv)
{

    glVertexAttrib2sv();
}
 
/**
 * glVertexAttrib3d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib3d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib3d)
{

    glVertexAttrib3d();
}
 
/**
 * glVertexAttrib3dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib3dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib3dv)
{

    glVertexAttrib3dv();
}
 
/**
 * glVertexAttrib3f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib3f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib3f)
{

    glVertexAttrib3f();
}
 
/**
 * glVertexAttrib3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib3fv)
{

    glVertexAttrib3fv();
}
 
/**
 * glVertexAttrib3s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib3s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib3s)
{

    glVertexAttrib3s();
}
 
/**
 * glVertexAttrib3sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib3sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib3sv)
{

    glVertexAttrib3sv();
}
 
/**
 * glVertexAttrib4Nbv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4Nbv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4Nbv)
{

    glVertexAttrib4Nbv();
}
 
/**
 * glVertexAttrib4Niv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4Niv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4Niv)
{

    glVertexAttrib4Niv();
}
 
/**
 * glVertexAttrib4Nsv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4Nsv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4Nsv)
{

    glVertexAttrib4Nsv();
}
 
/**
 * glVertexAttrib4Nub
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4Nub, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4Nub)
{

    glVertexAttrib4Nub();
}
 
/**
 * glVertexAttrib4Nubv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4Nubv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4Nubv)
{

    glVertexAttrib4Nubv();
}
 
/**
 * glVertexAttrib4Nuiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4Nuiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4Nuiv)
{

    glVertexAttrib4Nuiv();
}
 
/**
 * glVertexAttrib4Nusv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4Nusv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4Nusv)
{

    glVertexAttrib4Nusv();
}
 
/**
 * glVertexAttrib4bv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4bv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4bv)
{

    glVertexAttrib4bv();
}
 
/**
 * glVertexAttrib4d
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4d, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4d)
{

    glVertexAttrib4d();
}
 
/**
 * glVertexAttrib4dv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4dv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4dv)
{

    glVertexAttrib4dv();
}
 
/**
 * glVertexAttrib4f
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4f, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4f)
{

    glVertexAttrib4f();
}
 
/**
 * glVertexAttrib4fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4fv)
{

    glVertexAttrib4fv();
}
 
/**
 * glVertexAttrib4iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4iv)
{

    glVertexAttrib4iv();
}
 
/**
 * glVertexAttrib4s
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4s, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4s)
{

    glVertexAttrib4s();
}
 
/**
 * glVertexAttrib4sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4sv)
{

    glVertexAttrib4sv();
}
 
/**
 * glVertexAttrib4ubv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4ubv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4ubv)
{

    glVertexAttrib4ubv();
}
 
/**
 * glVertexAttrib4uiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4uiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4uiv)
{

    glVertexAttrib4uiv();
}
 
/**
 * glVertexAttrib4usv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttrib4usv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttrib4usv)
{

    glVertexAttrib4usv();
}
 
/**
 * glVertexAttribPointer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribPointer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribPointer)
{

    glVertexAttribPointer();
}
 
/**
 * glUniformMatrix2x3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniformMatrix2x3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniformMatrix2x3fv)
{

    glUniformMatrix2x3fv();
}
 
/**
 * glUniformMatrix3x2fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniformMatrix3x2fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniformMatrix3x2fv)
{

    glUniformMatrix3x2fv();
}
 
/**
 * glUniformMatrix2x4fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniformMatrix2x4fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniformMatrix2x4fv)
{

    glUniformMatrix2x4fv();
}
 
/**
 * glUniformMatrix4x2fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniformMatrix4x2fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniformMatrix4x2fv)
{

    glUniformMatrix4x2fv();
}
 
/**
 * glUniformMatrix3x4fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniformMatrix3x4fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniformMatrix3x4fv)
{

    glUniformMatrix3x4fv();
}
 
/**
 * glUniformMatrix4x3fv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniformMatrix4x3fv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniformMatrix4x3fv)
{

    glUniformMatrix4x3fv();
}
 
/**
 * glColorMaski
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glColorMaski, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glColorMaski)
{

    glColorMaski();
}
 
/**
 * glGetBooleani_v
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetBooleani_v, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetBooleani_v)
{

    glGetBooleani_v();
}
 
/**
 * glGetIntegeri_v
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetIntegeri_v, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetIntegeri_v)
{

    glGetIntegeri_v();
}
 
/**
 * glEnablei
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEnablei, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEnablei)
{

    glEnablei();
}
 
/**
 * glDisablei
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDisablei, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDisablei)
{

    glDisablei();
}
 
/**
 * glIsEnabledi
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glIsEnabledi, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glIsEnabledi)
{

    glIsEnabledi();
}
 
/**
 * glBeginTransformFeedback
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBeginTransformFeedback, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBeginTransformFeedback)
{

    glBeginTransformFeedback();
}
 
/**
 * glEndTransformFeedback
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEndTransformFeedback, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEndTransformFeedback)
{

    glEndTransformFeedback();
}
 
/**
 * glBindBufferRange
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBindBufferRange, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBindBufferRange)
{

    glBindBufferRange();
}
 
/**
 * glBindBufferBase
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBindBufferBase, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBindBufferBase)
{

    glBindBufferBase();
}
 
/**
 * glTransformFeedbackVaryings
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTransformFeedbackVaryings, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTransformFeedbackVaryings)
{

    glTransformFeedbackVaryings();
}
 
/**
 * glGetTransformFeedbackVarying
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTransformFeedbackVarying, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTransformFeedbackVarying)
{

    glGetTransformFeedbackVarying();
}
 
/**
 * glClampColor
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClampColor, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClampColor)
{

    glClampColor();
}
 
/**
 * glBeginConditionalRender
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBeginConditionalRender, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBeginConditionalRender)
{

    glBeginConditionalRender();
}
 
/**
 * glEndConditionalRender
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glEndConditionalRender, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glEndConditionalRender)
{

    glEndConditionalRender();
}
 
/**
 * glVertexAttribIPointer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribIPointer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribIPointer)
{

    glVertexAttribIPointer();
}
 
/**
 * glGetVertexAttribIiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetVertexAttribIiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetVertexAttribIiv)
{

    glGetVertexAttribIiv();
}
 
/**
 * glGetVertexAttribIuiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetVertexAttribIuiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetVertexAttribIuiv)
{

    glGetVertexAttribIuiv();
}
 
/**
 * glVertexAttribI1i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI1i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI1i)
{

    glVertexAttribI1i();
}
 
/**
 * glVertexAttribI2i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI2i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI2i)
{

    glVertexAttribI2i();
}
 
/**
 * glVertexAttribI3i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI3i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI3i)
{

    glVertexAttribI3i();
}
 
/**
 * glVertexAttribI4i
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI4i, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI4i)
{

    glVertexAttribI4i();
}
 
/**
 * glVertexAttribI1ui
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI1ui, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI1ui)
{

    glVertexAttribI1ui();
}
 
/**
 * glVertexAttribI2ui
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI2ui, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI2ui)
{

    glVertexAttribI2ui();
}
 
/**
 * glVertexAttribI3ui
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI3ui, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI3ui)
{

    glVertexAttribI3ui();
}
 
/**
 * glVertexAttribI4ui
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI4ui, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI4ui)
{

    glVertexAttribI4ui();
}
 
/**
 * glVertexAttribI1iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI1iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI1iv)
{

    glVertexAttribI1iv();
}
 
/**
 * glVertexAttribI2iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI2iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI2iv)
{

    glVertexAttribI2iv();
}
 
/**
 * glVertexAttribI3iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI3iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI3iv)
{

    glVertexAttribI3iv();
}
 
/**
 * glVertexAttribI4iv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI4iv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI4iv)
{

    glVertexAttribI4iv();
}
 
/**
 * glVertexAttribI1uiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI1uiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI1uiv)
{

    glVertexAttribI1uiv();
}
 
/**
 * glVertexAttribI2uiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI2uiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI2uiv)
{

    glVertexAttribI2uiv();
}
 
/**
 * glVertexAttribI3uiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI3uiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI3uiv)
{

    glVertexAttribI3uiv();
}
 
/**
 * glVertexAttribI4uiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI4uiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI4uiv)
{

    glVertexAttribI4uiv();
}
 
/**
 * glVertexAttribI4bv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI4bv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI4bv)
{

    glVertexAttribI4bv();
}
 
/**
 * glVertexAttribI4sv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI4sv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI4sv)
{

    glVertexAttribI4sv();
}
 
/**
 * glVertexAttribI4ubv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI4ubv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI4ubv)
{

    glVertexAttribI4ubv();
}
 
/**
 * glVertexAttribI4usv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glVertexAttribI4usv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glVertexAttribI4usv)
{

    glVertexAttribI4usv();
}
 
/**
 * glGetUniformuiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetUniformuiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetUniformuiv)
{

    glGetUniformuiv();
}
 
/**
 * glBindFragDataLocation
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glBindFragDataLocation, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glBindFragDataLocation)
{

    glBindFragDataLocation();
}
 
/**
 * glGetFragDataLocation
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetFragDataLocation, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetFragDataLocation)
{

    glGetFragDataLocation();
}
 
/**
 * glUniform1ui
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform1ui, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform1ui)
{

    glUniform1ui();
}
 
/**
 * glUniform2ui
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform2ui, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform2ui)
{

    glUniform2ui();
}
 
/**
 * glUniform3ui
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform3ui, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform3ui)
{

    glUniform3ui();
}
 
/**
 * glUniform4ui
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform4ui, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform4ui)
{

    glUniform4ui();
}
 
/**
 * glUniform1uiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform1uiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform1uiv)
{

    glUniform1uiv();
}
 
/**
 * glUniform2uiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform2uiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform2uiv)
{

    glUniform2uiv();
}
 
/**
 * glUniform3uiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform3uiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform3uiv)
{

    glUniform3uiv();
}
 
/**
 * glUniform4uiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glUniform4uiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glUniform4uiv)
{

    glUniform4uiv();
}
 
/**
 * glTexParameterIiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexParameterIiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexParameterIiv)
{

    glTexParameterIiv();
}
 
/**
 * glTexParameterIuiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexParameterIuiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexParameterIuiv)
{

    glTexParameterIuiv();
}
 
/**
 * glGetTexParameterIiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTexParameterIiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTexParameterIiv)
{

    glGetTexParameterIiv();
}
 
/**
 * glGetTexParameterIuiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetTexParameterIuiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetTexParameterIuiv)
{

    glGetTexParameterIuiv();
}
 
/**
 * glClearBufferiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClearBufferiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClearBufferiv)
{

    glClearBufferiv();
}
 
/**
 * glClearBufferuiv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClearBufferuiv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClearBufferuiv)
{

    glClearBufferuiv();
}
 
/**
 * glClearBufferfv
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClearBufferfv, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClearBufferfv)
{

    glClearBufferfv();
}
 
/**
 * glClearBufferfi
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glClearBufferfi, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glClearBufferfi)
{

    glClearBufferfi();
}
 
/**
 * glGetStringi
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glGetStringi, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glGetStringi)
{

    glGetStringi();
}
 
/**
 * glDrawArraysInstanced
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDrawArraysInstanced, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDrawArraysInstanced)
{

    glDrawArraysInstanced();
}
 
/**
 * glDrawElementsInstanced
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glDrawElementsInstanced, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glDrawElementsInstanced)
{

    glDrawElementsInstanced();
}
 
/**
 * glTexBuffer
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glTexBuffer, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glTexBuffer)
{

    glTexBuffer();
}
 
/**
 * glPrimitiveRestartIndex
 * --------------------------------
 */
ZEND_BEGIN_ARG_INFO_EX(arginfo_glPrimitiveRestartIndex, 0, 0, 1)
ZEND_END_ARG_INFO()

PHP_FUNCTION(glPrimitiveRestartIndex)
{

    glPrimitiveRestartIndex();
}
 


/**
 * MINIT
 * --------------------------------
 */
PHP_MINIT_FUNCTION(glfw)
{
    phpglfw_glfwwindow_context = zend_register_list_destructors_ex(phpglfw_glfwwindow_dtor, NULL, PHPGLFW_GLFWWINDOW_NAME, module_number);
    phpglfw_glfwcursor_context = zend_register_list_destructors_ex(phpglfw_glfwcursor_dtor, NULL, PHPGLFW_GLFWCURSOR_NAME, module_number);
    phpglfw_stbimagedata_context = zend_register_list_destructors_ex(phpglfw_stbimagedata_dtor, NULL, PHPGLFW_STBIMAGEDATA_NAME, module_number);
#ifdef GLFW_TRUE 
    REGISTER_LONG_CONSTANT("GLFW_TRUE", GLFW_TRUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_FALSE 
    REGISTER_LONG_CONSTANT("GLFW_FALSE", GLFW_FALSE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_DONT_CARE 
    REGISTER_LONG_CONSTANT("GLFW_DONT_CARE", GLFW_DONT_CARE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_RELEASE 
    REGISTER_LONG_CONSTANT("GLFW_RELEASE", GLFW_RELEASE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_PRESS 
    REGISTER_LONG_CONSTANT("GLFW_PRESS", GLFW_PRESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_REPEAT 
    REGISTER_LONG_CONSTANT("GLFW_REPEAT", GLFW_REPEAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_CENTERED 
    REGISTER_LONG_CONSTANT("GLFW_HAT_CENTERED", GLFW_HAT_CENTERED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_UP 
    REGISTER_LONG_CONSTANT("GLFW_HAT_UP", GLFW_HAT_UP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_RIGHT 
    REGISTER_LONG_CONSTANT("GLFW_HAT_RIGHT", GLFW_HAT_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_DOWN 
    REGISTER_LONG_CONSTANT("GLFW_HAT_DOWN", GLFW_HAT_DOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_LEFT 
    REGISTER_LONG_CONSTANT("GLFW_HAT_LEFT", GLFW_HAT_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_RIGHT_UP 
    REGISTER_LONG_CONSTANT("GLFW_HAT_RIGHT_UP", GLFW_HAT_RIGHT_UP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_RIGHT_DOWN 
    REGISTER_LONG_CONSTANT("GLFW_HAT_RIGHT_DOWN", GLFW_HAT_RIGHT_DOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_LEFT_UP 
    REGISTER_LONG_CONSTANT("GLFW_HAT_LEFT_UP", GLFW_HAT_LEFT_UP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAT_LEFT_DOWN 
    REGISTER_LONG_CONSTANT("GLFW_HAT_LEFT_DOWN", GLFW_HAT_LEFT_DOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_UNKNOWN 
    REGISTER_LONG_CONSTANT("GLFW_KEY_UNKNOWN", GLFW_KEY_UNKNOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_SPACE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_SPACE", GLFW_KEY_SPACE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_APOSTROPHE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_APOSTROPHE", GLFW_KEY_APOSTROPHE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_COMMA 
    REGISTER_LONG_CONSTANT("GLFW_KEY_COMMA", GLFW_KEY_COMMA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_MINUS 
    REGISTER_LONG_CONSTANT("GLFW_KEY_MINUS", GLFW_KEY_MINUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_PERIOD 
    REGISTER_LONG_CONSTANT("GLFW_KEY_PERIOD", GLFW_KEY_PERIOD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_SLASH 
    REGISTER_LONG_CONSTANT("GLFW_KEY_SLASH", GLFW_KEY_SLASH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_0 
    REGISTER_LONG_CONSTANT("GLFW_KEY_0", GLFW_KEY_0, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_1 
    REGISTER_LONG_CONSTANT("GLFW_KEY_1", GLFW_KEY_1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_2 
    REGISTER_LONG_CONSTANT("GLFW_KEY_2", GLFW_KEY_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_3 
    REGISTER_LONG_CONSTANT("GLFW_KEY_3", GLFW_KEY_3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_4 
    REGISTER_LONG_CONSTANT("GLFW_KEY_4", GLFW_KEY_4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_5 
    REGISTER_LONG_CONSTANT("GLFW_KEY_5", GLFW_KEY_5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_6 
    REGISTER_LONG_CONSTANT("GLFW_KEY_6", GLFW_KEY_6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_7 
    REGISTER_LONG_CONSTANT("GLFW_KEY_7", GLFW_KEY_7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_8 
    REGISTER_LONG_CONSTANT("GLFW_KEY_8", GLFW_KEY_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_9 
    REGISTER_LONG_CONSTANT("GLFW_KEY_9", GLFW_KEY_9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_SEMICOLON 
    REGISTER_LONG_CONSTANT("GLFW_KEY_SEMICOLON", GLFW_KEY_SEMICOLON, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_EQUAL 
    REGISTER_LONG_CONSTANT("GLFW_KEY_EQUAL", GLFW_KEY_EQUAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_A 
    REGISTER_LONG_CONSTANT("GLFW_KEY_A", GLFW_KEY_A, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_B 
    REGISTER_LONG_CONSTANT("GLFW_KEY_B", GLFW_KEY_B, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_C 
    REGISTER_LONG_CONSTANT("GLFW_KEY_C", GLFW_KEY_C, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_D 
    REGISTER_LONG_CONSTANT("GLFW_KEY_D", GLFW_KEY_D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_E 
    REGISTER_LONG_CONSTANT("GLFW_KEY_E", GLFW_KEY_E, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F", GLFW_KEY_F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_G 
    REGISTER_LONG_CONSTANT("GLFW_KEY_G", GLFW_KEY_G, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_H 
    REGISTER_LONG_CONSTANT("GLFW_KEY_H", GLFW_KEY_H, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_I 
    REGISTER_LONG_CONSTANT("GLFW_KEY_I", GLFW_KEY_I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_J 
    REGISTER_LONG_CONSTANT("GLFW_KEY_J", GLFW_KEY_J, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_K 
    REGISTER_LONG_CONSTANT("GLFW_KEY_K", GLFW_KEY_K, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_L 
    REGISTER_LONG_CONSTANT("GLFW_KEY_L", GLFW_KEY_L, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_M 
    REGISTER_LONG_CONSTANT("GLFW_KEY_M", GLFW_KEY_M, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_N 
    REGISTER_LONG_CONSTANT("GLFW_KEY_N", GLFW_KEY_N, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_O 
    REGISTER_LONG_CONSTANT("GLFW_KEY_O", GLFW_KEY_O, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_P 
    REGISTER_LONG_CONSTANT("GLFW_KEY_P", GLFW_KEY_P, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_Q 
    REGISTER_LONG_CONSTANT("GLFW_KEY_Q", GLFW_KEY_Q, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_R 
    REGISTER_LONG_CONSTANT("GLFW_KEY_R", GLFW_KEY_R, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_S 
    REGISTER_LONG_CONSTANT("GLFW_KEY_S", GLFW_KEY_S, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_T 
    REGISTER_LONG_CONSTANT("GLFW_KEY_T", GLFW_KEY_T, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_U 
    REGISTER_LONG_CONSTANT("GLFW_KEY_U", GLFW_KEY_U, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_V 
    REGISTER_LONG_CONSTANT("GLFW_KEY_V", GLFW_KEY_V, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_W 
    REGISTER_LONG_CONSTANT("GLFW_KEY_W", GLFW_KEY_W, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_X 
    REGISTER_LONG_CONSTANT("GLFW_KEY_X", GLFW_KEY_X, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_Y 
    REGISTER_LONG_CONSTANT("GLFW_KEY_Y", GLFW_KEY_Y, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_Z 
    REGISTER_LONG_CONSTANT("GLFW_KEY_Z", GLFW_KEY_Z, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LEFT_BRACKET 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LEFT_BRACKET", GLFW_KEY_LEFT_BRACKET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_BACKSLASH 
    REGISTER_LONG_CONSTANT("GLFW_KEY_BACKSLASH", GLFW_KEY_BACKSLASH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_RIGHT_BRACKET 
    REGISTER_LONG_CONSTANT("GLFW_KEY_RIGHT_BRACKET", GLFW_KEY_RIGHT_BRACKET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_GRAVE_ACCENT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_GRAVE_ACCENT", GLFW_KEY_GRAVE_ACCENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_WORLD_1 
    REGISTER_LONG_CONSTANT("GLFW_KEY_WORLD_1", GLFW_KEY_WORLD_1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_WORLD_2 
    REGISTER_LONG_CONSTANT("GLFW_KEY_WORLD_2", GLFW_KEY_WORLD_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_ESCAPE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_ESCAPE", GLFW_KEY_ESCAPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_ENTER 
    REGISTER_LONG_CONSTANT("GLFW_KEY_ENTER", GLFW_KEY_ENTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_TAB 
    REGISTER_LONG_CONSTANT("GLFW_KEY_TAB", GLFW_KEY_TAB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_BACKSPACE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_BACKSPACE", GLFW_KEY_BACKSPACE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_INSERT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_INSERT", GLFW_KEY_INSERT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_DELETE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_DELETE", GLFW_KEY_DELETE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_RIGHT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_RIGHT", GLFW_KEY_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LEFT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LEFT", GLFW_KEY_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_DOWN 
    REGISTER_LONG_CONSTANT("GLFW_KEY_DOWN", GLFW_KEY_DOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_UP 
    REGISTER_LONG_CONSTANT("GLFW_KEY_UP", GLFW_KEY_UP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_PAGE_UP 
    REGISTER_LONG_CONSTANT("GLFW_KEY_PAGE_UP", GLFW_KEY_PAGE_UP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_PAGE_DOWN 
    REGISTER_LONG_CONSTANT("GLFW_KEY_PAGE_DOWN", GLFW_KEY_PAGE_DOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_HOME 
    REGISTER_LONG_CONSTANT("GLFW_KEY_HOME", GLFW_KEY_HOME, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_END 
    REGISTER_LONG_CONSTANT("GLFW_KEY_END", GLFW_KEY_END, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_CAPS_LOCK 
    REGISTER_LONG_CONSTANT("GLFW_KEY_CAPS_LOCK", GLFW_KEY_CAPS_LOCK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_SCROLL_LOCK 
    REGISTER_LONG_CONSTANT("GLFW_KEY_SCROLL_LOCK", GLFW_KEY_SCROLL_LOCK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_NUM_LOCK 
    REGISTER_LONG_CONSTANT("GLFW_KEY_NUM_LOCK", GLFW_KEY_NUM_LOCK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_PRINT_SCREEN 
    REGISTER_LONG_CONSTANT("GLFW_KEY_PRINT_SCREEN", GLFW_KEY_PRINT_SCREEN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_PAUSE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_PAUSE", GLFW_KEY_PAUSE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F1 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F1", GLFW_KEY_F1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F2 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F2", GLFW_KEY_F2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F3 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F3", GLFW_KEY_F3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F4 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F4", GLFW_KEY_F4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F5 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F5", GLFW_KEY_F5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F6 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F6", GLFW_KEY_F6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F7 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F7", GLFW_KEY_F7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F8 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F8", GLFW_KEY_F8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F9 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F9", GLFW_KEY_F9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F10 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F10", GLFW_KEY_F10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F11 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F11", GLFW_KEY_F11, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F12 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F12", GLFW_KEY_F12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F13 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F13", GLFW_KEY_F13, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F14 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F14", GLFW_KEY_F14, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F15 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F15", GLFW_KEY_F15, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F16 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F16", GLFW_KEY_F16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F17 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F17", GLFW_KEY_F17, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F18 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F18", GLFW_KEY_F18, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F19 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F19", GLFW_KEY_F19, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F20 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F20", GLFW_KEY_F20, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F21 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F21", GLFW_KEY_F21, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F22 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F22", GLFW_KEY_F22, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F23 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F23", GLFW_KEY_F23, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F24 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F24", GLFW_KEY_F24, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_F25 
    REGISTER_LONG_CONSTANT("GLFW_KEY_F25", GLFW_KEY_F25, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_0 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_0", GLFW_KEY_KP_0, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_1 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_1", GLFW_KEY_KP_1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_2 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_2", GLFW_KEY_KP_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_3 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_3", GLFW_KEY_KP_3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_4 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_4", GLFW_KEY_KP_4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_5 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_5", GLFW_KEY_KP_5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_6 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_6", GLFW_KEY_KP_6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_7 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_7", GLFW_KEY_KP_7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_8 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_8", GLFW_KEY_KP_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_9 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_9", GLFW_KEY_KP_9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_DECIMAL 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_DECIMAL", GLFW_KEY_KP_DECIMAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_DIVIDE 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_DIVIDE", GLFW_KEY_KP_DIVIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_MULTIPLY 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_MULTIPLY", GLFW_KEY_KP_MULTIPLY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_SUBTRACT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_SUBTRACT", GLFW_KEY_KP_SUBTRACT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_ADD 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_ADD", GLFW_KEY_KP_ADD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_ENTER 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_ENTER", GLFW_KEY_KP_ENTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_KP_EQUAL 
    REGISTER_LONG_CONSTANT("GLFW_KEY_KP_EQUAL", GLFW_KEY_KP_EQUAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LEFT_SHIFT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LEFT_SHIFT", GLFW_KEY_LEFT_SHIFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LEFT_CONTROL 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LEFT_CONTROL", GLFW_KEY_LEFT_CONTROL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LEFT_ALT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LEFT_ALT", GLFW_KEY_LEFT_ALT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LEFT_SUPER 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LEFT_SUPER", GLFW_KEY_LEFT_SUPER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_RIGHT_SHIFT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_RIGHT_SHIFT", GLFW_KEY_RIGHT_SHIFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_RIGHT_CONTROL 
    REGISTER_LONG_CONSTANT("GLFW_KEY_RIGHT_CONTROL", GLFW_KEY_RIGHT_CONTROL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_RIGHT_ALT 
    REGISTER_LONG_CONSTANT("GLFW_KEY_RIGHT_ALT", GLFW_KEY_RIGHT_ALT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_RIGHT_SUPER 
    REGISTER_LONG_CONSTANT("GLFW_KEY_RIGHT_SUPER", GLFW_KEY_RIGHT_SUPER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_MENU 
    REGISTER_LONG_CONSTANT("GLFW_KEY_MENU", GLFW_KEY_MENU, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_KEY_LAST 
    REGISTER_LONG_CONSTANT("GLFW_KEY_LAST", GLFW_KEY_LAST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOD_SHIFT 
    REGISTER_LONG_CONSTANT("GLFW_MOD_SHIFT", GLFW_MOD_SHIFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOD_CONTROL 
    REGISTER_LONG_CONSTANT("GLFW_MOD_CONTROL", GLFW_MOD_CONTROL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOD_ALT 
    REGISTER_LONG_CONSTANT("GLFW_MOD_ALT", GLFW_MOD_ALT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOD_SUPER 
    REGISTER_LONG_CONSTANT("GLFW_MOD_SUPER", GLFW_MOD_SUPER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_1 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_1", GLFW_MOUSE_BUTTON_1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_2 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_2", GLFW_MOUSE_BUTTON_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_3 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_3", GLFW_MOUSE_BUTTON_3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_4 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_4", GLFW_MOUSE_BUTTON_4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_5 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_5", GLFW_MOUSE_BUTTON_5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_6 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_6", GLFW_MOUSE_BUTTON_6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_7 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_7", GLFW_MOUSE_BUTTON_7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_8 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_8", GLFW_MOUSE_BUTTON_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_LAST 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_LAST", GLFW_MOUSE_BUTTON_LAST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_LEFT 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_LEFT", GLFW_MOUSE_BUTTON_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_RIGHT 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_RIGHT", GLFW_MOUSE_BUTTON_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MOUSE_BUTTON_MIDDLE 
    REGISTER_LONG_CONSTANT("GLFW_MOUSE_BUTTON_MIDDLE", GLFW_MOUSE_BUTTON_MIDDLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_1 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_1", GLFW_JOYSTICK_1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_2 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_2", GLFW_JOYSTICK_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_3 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_3", GLFW_JOYSTICK_3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_4 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_4", GLFW_JOYSTICK_4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_5 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_5", GLFW_JOYSTICK_5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_6 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_6", GLFW_JOYSTICK_6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_7 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_7", GLFW_JOYSTICK_7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_8 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_8", GLFW_JOYSTICK_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_9 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_9", GLFW_JOYSTICK_9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_10 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_10", GLFW_JOYSTICK_10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_11 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_11", GLFW_JOYSTICK_11, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_12 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_12", GLFW_JOYSTICK_12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_13 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_13", GLFW_JOYSTICK_13, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_14 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_14", GLFW_JOYSTICK_14, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_15 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_15", GLFW_JOYSTICK_15, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_16 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_16", GLFW_JOYSTICK_16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_LAST 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_LAST", GLFW_JOYSTICK_LAST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_A 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_A", GLFW_GAMEPAD_BUTTON_A, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_B 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_B", GLFW_GAMEPAD_BUTTON_B, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_X 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_X", GLFW_GAMEPAD_BUTTON_X, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_Y 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_Y", GLFW_GAMEPAD_BUTTON_Y, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_LEFT_BUMPER 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_LEFT_BUMPER", GLFW_GAMEPAD_BUTTON_LEFT_BUMPER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER", GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_BACK 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_BACK", GLFW_GAMEPAD_BUTTON_BACK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_START 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_START", GLFW_GAMEPAD_BUTTON_START, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_GUIDE 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_GUIDE", GLFW_GAMEPAD_BUTTON_GUIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_LEFT_THUMB 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_LEFT_THUMB", GLFW_GAMEPAD_BUTTON_LEFT_THUMB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_RIGHT_THUMB 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_RIGHT_THUMB", GLFW_GAMEPAD_BUTTON_RIGHT_THUMB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_DPAD_UP 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_DPAD_UP", GLFW_GAMEPAD_BUTTON_DPAD_UP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_DPAD_RIGHT 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_DPAD_RIGHT", GLFW_GAMEPAD_BUTTON_DPAD_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_DPAD_DOWN 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_DPAD_DOWN", GLFW_GAMEPAD_BUTTON_DPAD_DOWN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_DPAD_LEFT 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_DPAD_LEFT", GLFW_GAMEPAD_BUTTON_DPAD_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_LAST 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_LAST", GLFW_GAMEPAD_BUTTON_LAST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_CROSS 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_CROSS", GLFW_GAMEPAD_BUTTON_CROSS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_CIRCLE 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_CIRCLE", GLFW_GAMEPAD_BUTTON_CIRCLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_SQUARE 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_SQUARE", GLFW_GAMEPAD_BUTTON_SQUARE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_BUTTON_TRIANGLE 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_BUTTON_TRIANGLE", GLFW_GAMEPAD_BUTTON_TRIANGLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_LEFT_X 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_LEFT_X", GLFW_GAMEPAD_AXIS_LEFT_X, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_LEFT_Y 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_LEFT_Y", GLFW_GAMEPAD_AXIS_LEFT_Y, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_RIGHT_X 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_RIGHT_X", GLFW_GAMEPAD_AXIS_RIGHT_X, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_RIGHT_Y 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_RIGHT_Y", GLFW_GAMEPAD_AXIS_RIGHT_Y, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_LEFT_TRIGGER 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_LEFT_TRIGGER", GLFW_GAMEPAD_AXIS_LEFT_TRIGGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER", GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GAMEPAD_AXIS_LAST 
    REGISTER_LONG_CONSTANT("GLFW_GAMEPAD_AXIS_LAST", GLFW_GAMEPAD_AXIS_LAST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NO_ERROR 
    REGISTER_LONG_CONSTANT("GLFW_NO_ERROR", GLFW_NO_ERROR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NOT_INITIALIZED 
    REGISTER_LONG_CONSTANT("GLFW_NOT_INITIALIZED", GLFW_NOT_INITIALIZED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NO_CURRENT_CONTEXT 
    REGISTER_LONG_CONSTANT("GLFW_NO_CURRENT_CONTEXT", GLFW_NO_CURRENT_CONTEXT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_INVALID_ENUM 
    REGISTER_LONG_CONSTANT("GLFW_INVALID_ENUM", GLFW_INVALID_ENUM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_INVALID_VALUE 
    REGISTER_LONG_CONSTANT("GLFW_INVALID_VALUE", GLFW_INVALID_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OUT_OF_MEMORY 
    REGISTER_LONG_CONSTANT("GLFW_OUT_OF_MEMORY", GLFW_OUT_OF_MEMORY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_API_UNAVAILABLE 
    REGISTER_LONG_CONSTANT("GLFW_API_UNAVAILABLE", GLFW_API_UNAVAILABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_VERSION_UNAVAILABLE 
    REGISTER_LONG_CONSTANT("GLFW_VERSION_UNAVAILABLE", GLFW_VERSION_UNAVAILABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_PLATFORM_ERROR 
    REGISTER_LONG_CONSTANT("GLFW_PLATFORM_ERROR", GLFW_PLATFORM_ERROR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_FORMAT_UNAVAILABLE 
    REGISTER_LONG_CONSTANT("GLFW_FORMAT_UNAVAILABLE", GLFW_FORMAT_UNAVAILABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NO_WINDOW_CONTEXT 
    REGISTER_LONG_CONSTANT("GLFW_NO_WINDOW_CONTEXT", GLFW_NO_WINDOW_CONTEXT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_FOCUSED 
    REGISTER_LONG_CONSTANT("GLFW_FOCUSED", GLFW_FOCUSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ICONIFIED 
    REGISTER_LONG_CONSTANT("GLFW_ICONIFIED", GLFW_ICONIFIED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_RESIZABLE 
    REGISTER_LONG_CONSTANT("GLFW_RESIZABLE", GLFW_RESIZABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_VISIBLE 
    REGISTER_LONG_CONSTANT("GLFW_VISIBLE", GLFW_VISIBLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_DECORATED 
    REGISTER_LONG_CONSTANT("GLFW_DECORATED", GLFW_DECORATED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_AUTO_ICONIFY 
    REGISTER_LONG_CONSTANT("GLFW_AUTO_ICONIFY", GLFW_AUTO_ICONIFY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_FLOATING 
    REGISTER_LONG_CONSTANT("GLFW_FLOATING", GLFW_FLOATING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_MAXIMIZED 
    REGISTER_LONG_CONSTANT("GLFW_MAXIMIZED", GLFW_MAXIMIZED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CENTER_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_CENTER_CURSOR", GLFW_CENTER_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_RED_BITS 
    REGISTER_LONG_CONSTANT("GLFW_RED_BITS", GLFW_RED_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_GREEN_BITS 
    REGISTER_LONG_CONSTANT("GLFW_GREEN_BITS", GLFW_GREEN_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_BLUE_BITS 
    REGISTER_LONG_CONSTANT("GLFW_BLUE_BITS", GLFW_BLUE_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ALPHA_BITS 
    REGISTER_LONG_CONSTANT("GLFW_ALPHA_BITS", GLFW_ALPHA_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_DEPTH_BITS 
    REGISTER_LONG_CONSTANT("GLFW_DEPTH_BITS", GLFW_DEPTH_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_STENCIL_BITS 
    REGISTER_LONG_CONSTANT("GLFW_STENCIL_BITS", GLFW_STENCIL_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ACCUM_RED_BITS 
    REGISTER_LONG_CONSTANT("GLFW_ACCUM_RED_BITS", GLFW_ACCUM_RED_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ACCUM_GREEN_BITS 
    REGISTER_LONG_CONSTANT("GLFW_ACCUM_GREEN_BITS", GLFW_ACCUM_GREEN_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ACCUM_BLUE_BITS 
    REGISTER_LONG_CONSTANT("GLFW_ACCUM_BLUE_BITS", GLFW_ACCUM_BLUE_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ACCUM_ALPHA_BITS 
    REGISTER_LONG_CONSTANT("GLFW_ACCUM_ALPHA_BITS", GLFW_ACCUM_ALPHA_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_AUX_BUFFERS 
    REGISTER_LONG_CONSTANT("GLFW_AUX_BUFFERS", GLFW_AUX_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_STEREO 
    REGISTER_LONG_CONSTANT("GLFW_STEREO", GLFW_STEREO, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_SAMPLES 
    REGISTER_LONG_CONSTANT("GLFW_SAMPLES", GLFW_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_SRGB_CAPABLE 
    REGISTER_LONG_CONSTANT("GLFW_SRGB_CAPABLE", GLFW_SRGB_CAPABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_REFRESH_RATE 
    REGISTER_LONG_CONSTANT("GLFW_REFRESH_RATE", GLFW_REFRESH_RATE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_DOUBLEBUFFER 
    REGISTER_LONG_CONSTANT("GLFW_DOUBLEBUFFER", GLFW_DOUBLEBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CLIENT_API 
    REGISTER_LONG_CONSTANT("GLFW_CLIENT_API", GLFW_CLIENT_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_VERSION_MAJOR 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_VERSION_MAJOR", GLFW_CONTEXT_VERSION_MAJOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_VERSION_MINOR 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_VERSION_MINOR", GLFW_CONTEXT_VERSION_MINOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_REVISION 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_REVISION", GLFW_CONTEXT_REVISION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_ROBUSTNESS 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_ROBUSTNESS", GLFW_CONTEXT_ROBUSTNESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_FORWARD_COMPAT 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_FORWARD_COMPAT", GLFW_OPENGL_FORWARD_COMPAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_DEBUG_CONTEXT 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_DEBUG_CONTEXT", GLFW_OPENGL_DEBUG_CONTEXT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_PROFILE 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_PROFILE", GLFW_OPENGL_PROFILE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_RELEASE_BEHAVIOR 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_RELEASE_BEHAVIOR", GLFW_CONTEXT_RELEASE_BEHAVIOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_NO_ERROR 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_NO_ERROR", GLFW_CONTEXT_NO_ERROR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONTEXT_CREATION_API 
    REGISTER_LONG_CONSTANT("GLFW_CONTEXT_CREATION_API", GLFW_CONTEXT_CREATION_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_COCOA_RETINA_FRAMEBUFFER 
    REGISTER_LONG_CONSTANT("GLFW_COCOA_RETINA_FRAMEBUFFER", GLFW_COCOA_RETINA_FRAMEBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_COCOA_FRAME_AUTOSAVE 
    REGISTER_LONG_CONSTANT("GLFW_COCOA_FRAME_AUTOSAVE", GLFW_COCOA_FRAME_AUTOSAVE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_COCOA_GRAPHICS_SWITCHING 
    REGISTER_LONG_CONSTANT("GLFW_COCOA_GRAPHICS_SWITCHING", GLFW_COCOA_GRAPHICS_SWITCHING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NO_API 
    REGISTER_LONG_CONSTANT("GLFW_NO_API", GLFW_NO_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_API 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_API", GLFW_OPENGL_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_ES_API 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_ES_API", GLFW_OPENGL_ES_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NO_ROBUSTNESS 
    REGISTER_LONG_CONSTANT("GLFW_NO_ROBUSTNESS", GLFW_NO_ROBUSTNESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NO_RESET_NOTIFICATION 
    REGISTER_LONG_CONSTANT("GLFW_NO_RESET_NOTIFICATION", GLFW_NO_RESET_NOTIFICATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_LOSE_CONTEXT_ON_RESET 
    REGISTER_LONG_CONSTANT("GLFW_LOSE_CONTEXT_ON_RESET", GLFW_LOSE_CONTEXT_ON_RESET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_ANY_PROFILE 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_ANY_PROFILE", GLFW_OPENGL_ANY_PROFILE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_CORE_PROFILE 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_CORE_PROFILE", GLFW_OPENGL_CORE_PROFILE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OPENGL_COMPAT_PROFILE 
    REGISTER_LONG_CONSTANT("GLFW_OPENGL_COMPAT_PROFILE", GLFW_OPENGL_COMPAT_PROFILE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_CURSOR", GLFW_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_STICKY_KEYS 
    REGISTER_LONG_CONSTANT("GLFW_STICKY_KEYS", GLFW_STICKY_KEYS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_STICKY_MOUSE_BUTTONS 
    REGISTER_LONG_CONSTANT("GLFW_STICKY_MOUSE_BUTTONS", GLFW_STICKY_MOUSE_BUTTONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CURSOR_NORMAL 
    REGISTER_LONG_CONSTANT("GLFW_CURSOR_NORMAL", GLFW_CURSOR_NORMAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CURSOR_HIDDEN 
    REGISTER_LONG_CONSTANT("GLFW_CURSOR_HIDDEN", GLFW_CURSOR_HIDDEN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CURSOR_DISABLED 
    REGISTER_LONG_CONSTANT("GLFW_CURSOR_DISABLED", GLFW_CURSOR_DISABLED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ANY_RELEASE_BEHAVIOR 
    REGISTER_LONG_CONSTANT("GLFW_ANY_RELEASE_BEHAVIOR", GLFW_ANY_RELEASE_BEHAVIOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_RELEASE_BEHAVIOR_FLUSH 
    REGISTER_LONG_CONSTANT("GLFW_RELEASE_BEHAVIOR_FLUSH", GLFW_RELEASE_BEHAVIOR_FLUSH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_RELEASE_BEHAVIOR_NONE 
    REGISTER_LONG_CONSTANT("GLFW_RELEASE_BEHAVIOR_NONE", GLFW_RELEASE_BEHAVIOR_NONE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_NATIVE_CONTEXT_API 
    REGISTER_LONG_CONSTANT("GLFW_NATIVE_CONTEXT_API", GLFW_NATIVE_CONTEXT_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_EGL_CONTEXT_API 
    REGISTER_LONG_CONSTANT("GLFW_EGL_CONTEXT_API", GLFW_EGL_CONTEXT_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_OSMESA_CONTEXT_API 
    REGISTER_LONG_CONSTANT("GLFW_OSMESA_CONTEXT_API", GLFW_OSMESA_CONTEXT_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_ARROW_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_ARROW_CURSOR", GLFW_ARROW_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_IBEAM_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_IBEAM_CURSOR", GLFW_IBEAM_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CROSSHAIR_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_CROSSHAIR_CURSOR", GLFW_CROSSHAIR_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HAND_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_HAND_CURSOR", GLFW_HAND_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_HRESIZE_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_HRESIZE_CURSOR", GLFW_HRESIZE_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_VRESIZE_CURSOR 
    REGISTER_LONG_CONSTANT("GLFW_VRESIZE_CURSOR", GLFW_VRESIZE_CURSOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_CONNECTED 
    REGISTER_LONG_CONSTANT("GLFW_CONNECTED", GLFW_CONNECTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_DISCONNECTED 
    REGISTER_LONG_CONSTANT("GLFW_DISCONNECTED", GLFW_DISCONNECTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_JOYSTICK_HAT_BUTTONS 
    REGISTER_LONG_CONSTANT("GLFW_JOYSTICK_HAT_BUTTONS", GLFW_JOYSTICK_HAT_BUTTONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_COCOA_CHDIR_RESOURCES 
    REGISTER_LONG_CONSTANT("GLFW_COCOA_CHDIR_RESOURCES", GLFW_COCOA_CHDIR_RESOURCES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_COCOA_MENUBAR 
    REGISTER_LONG_CONSTANT("GLFW_COCOA_MENUBAR", GLFW_COCOA_MENUBAR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_X11_WM_CLASS_NAME 
    REGISTER_LONG_CONSTANT("GLFW_X11_WM_CLASS_NAME", GLFW_X11_WM_CLASS_NAME, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GLFW_X11_WM_CLASS_CLASS 
    REGISTER_LONG_CONSTANT("GLFW_X11_WM_CLASS_CLASS", GLFW_X11_WM_CLASS_CLASS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_BUFFER_BIT 
    REGISTER_LONG_CONSTANT("GL_DEPTH_BUFFER_BIT", GL_DEPTH_BUFFER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BUFFER_BIT 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BUFFER_BIT", GL_STENCIL_BUFFER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_BUFFER_BIT 
    REGISTER_LONG_CONSTANT("GL_COLOR_BUFFER_BIT", GL_COLOR_BUFFER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FALSE 
    REGISTER_LONG_CONSTANT("GL_FALSE", GL_FALSE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRUE 
    REGISTER_LONG_CONSTANT("GL_TRUE", GL_TRUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINTS 
    REGISTER_LONG_CONSTANT("GL_POINTS", GL_POINTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINES 
    REGISTER_LONG_CONSTANT("GL_LINES", GL_LINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_LOOP 
    REGISTER_LONG_CONSTANT("GL_LINE_LOOP", GL_LINE_LOOP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_STRIP 
    REGISTER_LONG_CONSTANT("GL_LINE_STRIP", GL_LINE_STRIP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRIANGLES 
    REGISTER_LONG_CONSTANT("GL_TRIANGLES", GL_TRIANGLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRIANGLE_STRIP 
    REGISTER_LONG_CONSTANT("GL_TRIANGLE_STRIP", GL_TRIANGLE_STRIP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRIANGLE_FAN 
    REGISTER_LONG_CONSTANT("GL_TRIANGLE_FAN", GL_TRIANGLE_FAN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NEVER 
    REGISTER_LONG_CONSTANT("GL_NEVER", GL_NEVER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LESS 
    REGISTER_LONG_CONSTANT("GL_LESS", GL_LESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_EQUAL 
    REGISTER_LONG_CONSTANT("GL_EQUAL", GL_EQUAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LEQUAL 
    REGISTER_LONG_CONSTANT("GL_LEQUAL", GL_LEQUAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GREATER 
    REGISTER_LONG_CONSTANT("GL_GREATER", GL_GREATER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NOTEQUAL 
    REGISTER_LONG_CONSTANT("GL_NOTEQUAL", GL_NOTEQUAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEQUAL 
    REGISTER_LONG_CONSTANT("GL_GEQUAL", GL_GEQUAL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ALWAYS 
    REGISTER_LONG_CONSTANT("GL_ALWAYS", GL_ALWAYS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ZERO 
    REGISTER_LONG_CONSTANT("GL_ZERO", GL_ZERO, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE 
    REGISTER_LONG_CONSTANT("GL_ONE", GL_ONE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRC_COLOR 
    REGISTER_LONG_CONSTANT("GL_SRC_COLOR", GL_SRC_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_SRC_COLOR 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_SRC_COLOR", GL_ONE_MINUS_SRC_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRC_ALPHA 
    REGISTER_LONG_CONSTANT("GL_SRC_ALPHA", GL_SRC_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_SRC_ALPHA 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_SRC_ALPHA", GL_ONE_MINUS_SRC_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DST_ALPHA 
    REGISTER_LONG_CONSTANT("GL_DST_ALPHA", GL_DST_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_DST_ALPHA 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_DST_ALPHA", GL_ONE_MINUS_DST_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DST_COLOR 
    REGISTER_LONG_CONSTANT("GL_DST_COLOR", GL_DST_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_DST_COLOR 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_DST_COLOR", GL_ONE_MINUS_DST_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRC_ALPHA_SATURATE 
    REGISTER_LONG_CONSTANT("GL_SRC_ALPHA_SATURATE", GL_SRC_ALPHA_SATURATE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NONE 
    REGISTER_LONG_CONSTANT("GL_NONE", GL_NONE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRONT_LEFT 
    REGISTER_LONG_CONSTANT("GL_FRONT_LEFT", GL_FRONT_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRONT_RIGHT 
    REGISTER_LONG_CONSTANT("GL_FRONT_RIGHT", GL_FRONT_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BACK_LEFT 
    REGISTER_LONG_CONSTANT("GL_BACK_LEFT", GL_BACK_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BACK_RIGHT 
    REGISTER_LONG_CONSTANT("GL_BACK_RIGHT", GL_BACK_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRONT 
    REGISTER_LONG_CONSTANT("GL_FRONT", GL_FRONT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BACK 
    REGISTER_LONG_CONSTANT("GL_BACK", GL_BACK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LEFT 
    REGISTER_LONG_CONSTANT("GL_LEFT", GL_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RIGHT 
    REGISTER_LONG_CONSTANT("GL_RIGHT", GL_RIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRONT_AND_BACK 
    REGISTER_LONG_CONSTANT("GL_FRONT_AND_BACK", GL_FRONT_AND_BACK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NO_ERROR 
    REGISTER_LONG_CONSTANT("GL_NO_ERROR", GL_NO_ERROR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INVALID_ENUM 
    REGISTER_LONG_CONSTANT("GL_INVALID_ENUM", GL_INVALID_ENUM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INVALID_VALUE 
    REGISTER_LONG_CONSTANT("GL_INVALID_VALUE", GL_INVALID_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INVALID_OPERATION 
    REGISTER_LONG_CONSTANT("GL_INVALID_OPERATION", GL_INVALID_OPERATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_OUT_OF_MEMORY 
    REGISTER_LONG_CONSTANT("GL_OUT_OF_MEMORY", GL_OUT_OF_MEMORY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CW 
    REGISTER_LONG_CONSTANT("GL_CW", GL_CW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CCW 
    REGISTER_LONG_CONSTANT("GL_CCW", GL_CCW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINT_SIZE 
    REGISTER_LONG_CONSTANT("GL_POINT_SIZE", GL_POINT_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINT_SIZE_RANGE 
    REGISTER_LONG_CONSTANT("GL_POINT_SIZE_RANGE", GL_POINT_SIZE_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINT_SIZE_GRANULARITY 
    REGISTER_LONG_CONSTANT("GL_POINT_SIZE_GRANULARITY", GL_POINT_SIZE_GRANULARITY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_SMOOTH 
    REGISTER_LONG_CONSTANT("GL_LINE_SMOOTH", GL_LINE_SMOOTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_WIDTH 
    REGISTER_LONG_CONSTANT("GL_LINE_WIDTH", GL_LINE_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_WIDTH_RANGE 
    REGISTER_LONG_CONSTANT("GL_LINE_WIDTH_RANGE", GL_LINE_WIDTH_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_WIDTH_GRANULARITY 
    REGISTER_LONG_CONSTANT("GL_LINE_WIDTH_GRANULARITY", GL_LINE_WIDTH_GRANULARITY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_MODE 
    REGISTER_LONG_CONSTANT("GL_POLYGON_MODE", GL_POLYGON_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_SMOOTH 
    REGISTER_LONG_CONSTANT("GL_POLYGON_SMOOTH", GL_POLYGON_SMOOTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CULL_FACE 
    REGISTER_LONG_CONSTANT("GL_CULL_FACE", GL_CULL_FACE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CULL_FACE_MODE 
    REGISTER_LONG_CONSTANT("GL_CULL_FACE_MODE", GL_CULL_FACE_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRONT_FACE 
    REGISTER_LONG_CONSTANT("GL_FRONT_FACE", GL_FRONT_FACE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_RANGE 
    REGISTER_LONG_CONSTANT("GL_DEPTH_RANGE", GL_DEPTH_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_TEST 
    REGISTER_LONG_CONSTANT("GL_DEPTH_TEST", GL_DEPTH_TEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_WRITEMASK 
    REGISTER_LONG_CONSTANT("GL_DEPTH_WRITEMASK", GL_DEPTH_WRITEMASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_CLEAR_VALUE 
    REGISTER_LONG_CONSTANT("GL_DEPTH_CLEAR_VALUE", GL_DEPTH_CLEAR_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_FUNC 
    REGISTER_LONG_CONSTANT("GL_DEPTH_FUNC", GL_DEPTH_FUNC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_TEST 
    REGISTER_LONG_CONSTANT("GL_STENCIL_TEST", GL_STENCIL_TEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_CLEAR_VALUE 
    REGISTER_LONG_CONSTANT("GL_STENCIL_CLEAR_VALUE", GL_STENCIL_CLEAR_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_FUNC 
    REGISTER_LONG_CONSTANT("GL_STENCIL_FUNC", GL_STENCIL_FUNC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_VALUE_MASK 
    REGISTER_LONG_CONSTANT("GL_STENCIL_VALUE_MASK", GL_STENCIL_VALUE_MASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_FAIL 
    REGISTER_LONG_CONSTANT("GL_STENCIL_FAIL", GL_STENCIL_FAIL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_PASS_DEPTH_FAIL 
    REGISTER_LONG_CONSTANT("GL_STENCIL_PASS_DEPTH_FAIL", GL_STENCIL_PASS_DEPTH_FAIL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_PASS_DEPTH_PASS 
    REGISTER_LONG_CONSTANT("GL_STENCIL_PASS_DEPTH_PASS", GL_STENCIL_PASS_DEPTH_PASS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_REF 
    REGISTER_LONG_CONSTANT("GL_STENCIL_REF", GL_STENCIL_REF, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_WRITEMASK 
    REGISTER_LONG_CONSTANT("GL_STENCIL_WRITEMASK", GL_STENCIL_WRITEMASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEWPORT 
    REGISTER_LONG_CONSTANT("GL_VIEWPORT", GL_VIEWPORT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DITHER 
    REGISTER_LONG_CONSTANT("GL_DITHER", GL_DITHER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_DST 
    REGISTER_LONG_CONSTANT("GL_BLEND_DST", GL_BLEND_DST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_SRC 
    REGISTER_LONG_CONSTANT("GL_BLEND_SRC", GL_BLEND_SRC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND 
    REGISTER_LONG_CONSTANT("GL_BLEND", GL_BLEND, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOGIC_OP_MODE 
    REGISTER_LONG_CONSTANT("GL_LOGIC_OP_MODE", GL_LOGIC_OP_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER", GL_DRAW_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_BUFFER 
    REGISTER_LONG_CONSTANT("GL_READ_BUFFER", GL_READ_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SCISSOR_BOX 
    REGISTER_LONG_CONSTANT("GL_SCISSOR_BOX", GL_SCISSOR_BOX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SCISSOR_TEST 
    REGISTER_LONG_CONSTANT("GL_SCISSOR_TEST", GL_SCISSOR_TEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_CLEAR_VALUE 
    REGISTER_LONG_CONSTANT("GL_COLOR_CLEAR_VALUE", GL_COLOR_CLEAR_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_WRITEMASK 
    REGISTER_LONG_CONSTANT("GL_COLOR_WRITEMASK", GL_COLOR_WRITEMASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLEBUFFER 
    REGISTER_LONG_CONSTANT("GL_DOUBLEBUFFER", GL_DOUBLEBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STEREO 
    REGISTER_LONG_CONSTANT("GL_STEREO", GL_STEREO, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_SMOOTH_HINT 
    REGISTER_LONG_CONSTANT("GL_LINE_SMOOTH_HINT", GL_LINE_SMOOTH_HINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_SMOOTH_HINT 
    REGISTER_LONG_CONSTANT("GL_POLYGON_SMOOTH_HINT", GL_POLYGON_SMOOTH_HINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_SWAP_BYTES 
    REGISTER_LONG_CONSTANT("GL_UNPACK_SWAP_BYTES", GL_UNPACK_SWAP_BYTES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_LSB_FIRST 
    REGISTER_LONG_CONSTANT("GL_UNPACK_LSB_FIRST", GL_UNPACK_LSB_FIRST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_ROW_LENGTH 
    REGISTER_LONG_CONSTANT("GL_UNPACK_ROW_LENGTH", GL_UNPACK_ROW_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_SKIP_ROWS 
    REGISTER_LONG_CONSTANT("GL_UNPACK_SKIP_ROWS", GL_UNPACK_SKIP_ROWS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_SKIP_PIXELS 
    REGISTER_LONG_CONSTANT("GL_UNPACK_SKIP_PIXELS", GL_UNPACK_SKIP_PIXELS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_ALIGNMENT 
    REGISTER_LONG_CONSTANT("GL_UNPACK_ALIGNMENT", GL_UNPACK_ALIGNMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_SWAP_BYTES 
    REGISTER_LONG_CONSTANT("GL_PACK_SWAP_BYTES", GL_PACK_SWAP_BYTES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_LSB_FIRST 
    REGISTER_LONG_CONSTANT("GL_PACK_LSB_FIRST", GL_PACK_LSB_FIRST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_ROW_LENGTH 
    REGISTER_LONG_CONSTANT("GL_PACK_ROW_LENGTH", GL_PACK_ROW_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_SKIP_ROWS 
    REGISTER_LONG_CONSTANT("GL_PACK_SKIP_ROWS", GL_PACK_SKIP_ROWS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_SKIP_PIXELS 
    REGISTER_LONG_CONSTANT("GL_PACK_SKIP_PIXELS", GL_PACK_SKIP_PIXELS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_ALIGNMENT 
    REGISTER_LONG_CONSTANT("GL_PACK_ALIGNMENT", GL_PACK_ALIGNMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TEXTURE_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_TEXTURE_SIZE", GL_MAX_TEXTURE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VIEWPORT_DIMS 
    REGISTER_LONG_CONSTANT("GL_MAX_VIEWPORT_DIMS", GL_MAX_VIEWPORT_DIMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SUBPIXEL_BITS 
    REGISTER_LONG_CONSTANT("GL_SUBPIXEL_BITS", GL_SUBPIXEL_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_1D 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_1D", GL_TEXTURE_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_2D 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_2D", GL_TEXTURE_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_WIDTH 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_WIDTH", GL_TEXTURE_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_HEIGHT", GL_TEXTURE_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BORDER_COLOR 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BORDER_COLOR", GL_TEXTURE_BORDER_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DONT_CARE 
    REGISTER_LONG_CONSTANT("GL_DONT_CARE", GL_DONT_CARE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FASTEST 
    REGISTER_LONG_CONSTANT("GL_FASTEST", GL_FASTEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NICEST 
    REGISTER_LONG_CONSTANT("GL_NICEST", GL_NICEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BYTE 
    REGISTER_LONG_CONSTANT("GL_BYTE", GL_BYTE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_BYTE 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_BYTE", GL_UNSIGNED_BYTE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHORT 
    REGISTER_LONG_CONSTANT("GL_SHORT", GL_SHORT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT", GL_UNSIGNED_SHORT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT 
    REGISTER_LONG_CONSTANT("GL_INT", GL_INT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT", GL_UNSIGNED_INT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT 
    REGISTER_LONG_CONSTANT("GL_FLOAT", GL_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLEAR 
    REGISTER_LONG_CONSTANT("GL_CLEAR", GL_CLEAR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_AND 
    REGISTER_LONG_CONSTANT("GL_AND", GL_AND, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_AND_REVERSE 
    REGISTER_LONG_CONSTANT("GL_AND_REVERSE", GL_AND_REVERSE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COPY 
    REGISTER_LONG_CONSTANT("GL_COPY", GL_COPY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_AND_INVERTED 
    REGISTER_LONG_CONSTANT("GL_AND_INVERTED", GL_AND_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NOOP 
    REGISTER_LONG_CONSTANT("GL_NOOP", GL_NOOP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_XOR 
    REGISTER_LONG_CONSTANT("GL_XOR", GL_XOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_OR 
    REGISTER_LONG_CONSTANT("GL_OR", GL_OR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NOR 
    REGISTER_LONG_CONSTANT("GL_NOR", GL_NOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_EQUIV 
    REGISTER_LONG_CONSTANT("GL_EQUIV", GL_EQUIV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INVERT 
    REGISTER_LONG_CONSTANT("GL_INVERT", GL_INVERT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_OR_REVERSE 
    REGISTER_LONG_CONSTANT("GL_OR_REVERSE", GL_OR_REVERSE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COPY_INVERTED 
    REGISTER_LONG_CONSTANT("GL_COPY_INVERTED", GL_COPY_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_OR_INVERTED 
    REGISTER_LONG_CONSTANT("GL_OR_INVERTED", GL_OR_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NAND 
    REGISTER_LONG_CONSTANT("GL_NAND", GL_NAND, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SET 
    REGISTER_LONG_CONSTANT("GL_SET", GL_SET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE", GL_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR 
    REGISTER_LONG_CONSTANT("GL_COLOR", GL_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH 
    REGISTER_LONG_CONSTANT("GL_DEPTH", GL_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL 
    REGISTER_LONG_CONSTANT("GL_STENCIL", GL_STENCIL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_INDEX 
    REGISTER_LONG_CONSTANT("GL_STENCIL_INDEX", GL_STENCIL_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_COMPONENT 
    REGISTER_LONG_CONSTANT("GL_DEPTH_COMPONENT", GL_DEPTH_COMPONENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RED 
    REGISTER_LONG_CONSTANT("GL_RED", GL_RED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GREEN 
    REGISTER_LONG_CONSTANT("GL_GREEN", GL_GREEN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLUE 
    REGISTER_LONG_CONSTANT("GL_BLUE", GL_BLUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ALPHA 
    REGISTER_LONG_CONSTANT("GL_ALPHA", GL_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB 
    REGISTER_LONG_CONSTANT("GL_RGB", GL_RGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA 
    REGISTER_LONG_CONSTANT("GL_RGBA", GL_RGBA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINT 
    REGISTER_LONG_CONSTANT("GL_POINT", GL_POINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE 
    REGISTER_LONG_CONSTANT("GL_LINE", GL_LINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FILL 
    REGISTER_LONG_CONSTANT("GL_FILL", GL_FILL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_KEEP 
    REGISTER_LONG_CONSTANT("GL_KEEP", GL_KEEP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REPLACE 
    REGISTER_LONG_CONSTANT("GL_REPLACE", GL_REPLACE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INCR 
    REGISTER_LONG_CONSTANT("GL_INCR", GL_INCR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DECR 
    REGISTER_LONG_CONSTANT("GL_DECR", GL_DECR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VENDOR 
    REGISTER_LONG_CONSTANT("GL_VENDOR", GL_VENDOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERER 
    REGISTER_LONG_CONSTANT("GL_RENDERER", GL_RENDERER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERSION 
    REGISTER_LONG_CONSTANT("GL_VERSION", GL_VERSION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_EXTENSIONS 
    REGISTER_LONG_CONSTANT("GL_EXTENSIONS", GL_EXTENSIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NEAREST 
    REGISTER_LONG_CONSTANT("GL_NEAREST", GL_NEAREST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINEAR 
    REGISTER_LONG_CONSTANT("GL_LINEAR", GL_LINEAR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NEAREST_MIPMAP_NEAREST 
    REGISTER_LONG_CONSTANT("GL_NEAREST_MIPMAP_NEAREST", GL_NEAREST_MIPMAP_NEAREST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINEAR_MIPMAP_NEAREST 
    REGISTER_LONG_CONSTANT("GL_LINEAR_MIPMAP_NEAREST", GL_LINEAR_MIPMAP_NEAREST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NEAREST_MIPMAP_LINEAR 
    REGISTER_LONG_CONSTANT("GL_NEAREST_MIPMAP_LINEAR", GL_NEAREST_MIPMAP_LINEAR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINEAR_MIPMAP_LINEAR 
    REGISTER_LONG_CONSTANT("GL_LINEAR_MIPMAP_LINEAR", GL_LINEAR_MIPMAP_LINEAR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_MAG_FILTER 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_MAG_FILTER", GL_TEXTURE_MAG_FILTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_MIN_FILTER 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_MIN_FILTER", GL_TEXTURE_MIN_FILTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_WRAP_S 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_WRAP_S", GL_TEXTURE_WRAP_S, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_WRAP_T 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_WRAP_T", GL_TEXTURE_WRAP_T, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REPEAT 
    REGISTER_LONG_CONSTANT("GL_REPEAT", GL_REPEAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_LOGIC_OP 
    REGISTER_LONG_CONSTANT("GL_COLOR_LOGIC_OP", GL_COLOR_LOGIC_OP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_OFFSET_UNITS 
    REGISTER_LONG_CONSTANT("GL_POLYGON_OFFSET_UNITS", GL_POLYGON_OFFSET_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_OFFSET_POINT 
    REGISTER_LONG_CONSTANT("GL_POLYGON_OFFSET_POINT", GL_POLYGON_OFFSET_POINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_OFFSET_LINE 
    REGISTER_LONG_CONSTANT("GL_POLYGON_OFFSET_LINE", GL_POLYGON_OFFSET_LINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_OFFSET_FILL 
    REGISTER_LONG_CONSTANT("GL_POLYGON_OFFSET_FILL", GL_POLYGON_OFFSET_FILL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_OFFSET_FACTOR 
    REGISTER_LONG_CONSTANT("GL_POLYGON_OFFSET_FACTOR", GL_POLYGON_OFFSET_FACTOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_1D 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_1D", GL_TEXTURE_BINDING_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_2D 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_2D", GL_TEXTURE_BINDING_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_INTERNAL_FORMAT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_INTERNAL_FORMAT", GL_TEXTURE_INTERNAL_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_RED_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_RED_SIZE", GL_TEXTURE_RED_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_GREEN_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_GREEN_SIZE", GL_TEXTURE_GREEN_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BLUE_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BLUE_SIZE", GL_TEXTURE_BLUE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_ALPHA_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_ALPHA_SIZE", GL_TEXTURE_ALPHA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE 
    REGISTER_LONG_CONSTANT("GL_DOUBLE", GL_DOUBLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_1D 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_1D", GL_PROXY_TEXTURE_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_2D 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_2D", GL_PROXY_TEXTURE_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R3_G3_B2 
    REGISTER_LONG_CONSTANT("GL_R3_G3_B2", GL_R3_G3_B2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB4 
    REGISTER_LONG_CONSTANT("GL_RGB4", GL_RGB4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB5 
    REGISTER_LONG_CONSTANT("GL_RGB5", GL_RGB5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB8 
    REGISTER_LONG_CONSTANT("GL_RGB8", GL_RGB8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB10 
    REGISTER_LONG_CONSTANT("GL_RGB10", GL_RGB10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB12 
    REGISTER_LONG_CONSTANT("GL_RGB12", GL_RGB12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB16 
    REGISTER_LONG_CONSTANT("GL_RGB16", GL_RGB16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA2 
    REGISTER_LONG_CONSTANT("GL_RGBA2", GL_RGBA2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA4 
    REGISTER_LONG_CONSTANT("GL_RGBA4", GL_RGBA4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB5_A1 
    REGISTER_LONG_CONSTANT("GL_RGB5_A1", GL_RGB5_A1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA8 
    REGISTER_LONG_CONSTANT("GL_RGBA8", GL_RGBA8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB10_A2 
    REGISTER_LONG_CONSTANT("GL_RGB10_A2", GL_RGB10_A2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA12 
    REGISTER_LONG_CONSTANT("GL_RGBA12", GL_RGBA12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA16 
    REGISTER_LONG_CONSTANT("GL_RGBA16", GL_RGBA16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_BYTE_3_3_2 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_BYTE_3_3_2", GL_UNSIGNED_BYTE_3_3_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT_4_4_4_4 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT_4_4_4_4", GL_UNSIGNED_SHORT_4_4_4_4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT_5_5_5_1 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT_5_5_5_1", GL_UNSIGNED_SHORT_5_5_5_1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_8_8_8_8 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_8_8_8_8", GL_UNSIGNED_INT_8_8_8_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_10_10_10_2 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_10_10_10_2", GL_UNSIGNED_INT_10_10_10_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_3D 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_3D", GL_TEXTURE_BINDING_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_SKIP_IMAGES 
    REGISTER_LONG_CONSTANT("GL_PACK_SKIP_IMAGES", GL_PACK_SKIP_IMAGES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_IMAGE_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_PACK_IMAGE_HEIGHT", GL_PACK_IMAGE_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_SKIP_IMAGES 
    REGISTER_LONG_CONSTANT("GL_UNPACK_SKIP_IMAGES", GL_UNPACK_SKIP_IMAGES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_IMAGE_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_UNPACK_IMAGE_HEIGHT", GL_UNPACK_IMAGE_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_3D 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_3D", GL_TEXTURE_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_3D 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_3D", GL_PROXY_TEXTURE_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_DEPTH 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_DEPTH", GL_TEXTURE_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_WRAP_R 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_WRAP_R", GL_TEXTURE_WRAP_R, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_3D_TEXTURE_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_3D_TEXTURE_SIZE", GL_MAX_3D_TEXTURE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_BYTE_2_3_3_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_BYTE_2_3_3_REV", GL_UNSIGNED_BYTE_2_3_3_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT_5_6_5 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT_5_6_5", GL_UNSIGNED_SHORT_5_6_5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT_5_6_5_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT_5_6_5_REV", GL_UNSIGNED_SHORT_5_6_5_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT_4_4_4_4_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT_4_4_4_4_REV", GL_UNSIGNED_SHORT_4_4_4_4_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_SHORT_1_5_5_5_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_SHORT_1_5_5_5_REV", GL_UNSIGNED_SHORT_1_5_5_5_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_8_8_8_8_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_8_8_8_8_REV", GL_UNSIGNED_INT_8_8_8_8_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_2_10_10_10_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_2_10_10_10_REV", GL_UNSIGNED_INT_2_10_10_10_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BGR 
    REGISTER_LONG_CONSTANT("GL_BGR", GL_BGR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BGRA 
    REGISTER_LONG_CONSTANT("GL_BGRA", GL_BGRA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_ELEMENTS_VERTICES 
    REGISTER_LONG_CONSTANT("GL_MAX_ELEMENTS_VERTICES", GL_MAX_ELEMENTS_VERTICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_ELEMENTS_INDICES 
    REGISTER_LONG_CONSTANT("GL_MAX_ELEMENTS_INDICES", GL_MAX_ELEMENTS_INDICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLAMP_TO_EDGE 
    REGISTER_LONG_CONSTANT("GL_CLAMP_TO_EDGE", GL_CLAMP_TO_EDGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_MIN_LOD 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_MIN_LOD", GL_TEXTURE_MIN_LOD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_MAX_LOD 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_MAX_LOD", GL_TEXTURE_MAX_LOD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BASE_LEVEL 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BASE_LEVEL", GL_TEXTURE_BASE_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_MAX_LEVEL 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_MAX_LEVEL", GL_TEXTURE_MAX_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SMOOTH_POINT_SIZE_RANGE 
    REGISTER_LONG_CONSTANT("GL_SMOOTH_POINT_SIZE_RANGE", GL_SMOOTH_POINT_SIZE_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SMOOTH_POINT_SIZE_GRANULARITY 
    REGISTER_LONG_CONSTANT("GL_SMOOTH_POINT_SIZE_GRANULARITY", GL_SMOOTH_POINT_SIZE_GRANULARITY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SMOOTH_LINE_WIDTH_RANGE 
    REGISTER_LONG_CONSTANT("GL_SMOOTH_LINE_WIDTH_RANGE", GL_SMOOTH_LINE_WIDTH_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SMOOTH_LINE_WIDTH_GRANULARITY 
    REGISTER_LONG_CONSTANT("GL_SMOOTH_LINE_WIDTH_GRANULARITY", GL_SMOOTH_LINE_WIDTH_GRANULARITY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ALIASED_LINE_WIDTH_RANGE 
    REGISTER_LONG_CONSTANT("GL_ALIASED_LINE_WIDTH_RANGE", GL_ALIASED_LINE_WIDTH_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE0 
    REGISTER_LONG_CONSTANT("GL_TEXTURE0", GL_TEXTURE0, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE1 
    REGISTER_LONG_CONSTANT("GL_TEXTURE1", GL_TEXTURE1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE2 
    REGISTER_LONG_CONSTANT("GL_TEXTURE2", GL_TEXTURE2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE3 
    REGISTER_LONG_CONSTANT("GL_TEXTURE3", GL_TEXTURE3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE4 
    REGISTER_LONG_CONSTANT("GL_TEXTURE4", GL_TEXTURE4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE5 
    REGISTER_LONG_CONSTANT("GL_TEXTURE5", GL_TEXTURE5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE6 
    REGISTER_LONG_CONSTANT("GL_TEXTURE6", GL_TEXTURE6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE7 
    REGISTER_LONG_CONSTANT("GL_TEXTURE7", GL_TEXTURE7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE8 
    REGISTER_LONG_CONSTANT("GL_TEXTURE8", GL_TEXTURE8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE9 
    REGISTER_LONG_CONSTANT("GL_TEXTURE9", GL_TEXTURE9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE10 
    REGISTER_LONG_CONSTANT("GL_TEXTURE10", GL_TEXTURE10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE11 
    REGISTER_LONG_CONSTANT("GL_TEXTURE11", GL_TEXTURE11, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE12 
    REGISTER_LONG_CONSTANT("GL_TEXTURE12", GL_TEXTURE12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE13 
    REGISTER_LONG_CONSTANT("GL_TEXTURE13", GL_TEXTURE13, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE14 
    REGISTER_LONG_CONSTANT("GL_TEXTURE14", GL_TEXTURE14, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE15 
    REGISTER_LONG_CONSTANT("GL_TEXTURE15", GL_TEXTURE15, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE16 
    REGISTER_LONG_CONSTANT("GL_TEXTURE16", GL_TEXTURE16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE17 
    REGISTER_LONG_CONSTANT("GL_TEXTURE17", GL_TEXTURE17, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE18 
    REGISTER_LONG_CONSTANT("GL_TEXTURE18", GL_TEXTURE18, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE19 
    REGISTER_LONG_CONSTANT("GL_TEXTURE19", GL_TEXTURE19, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE20 
    REGISTER_LONG_CONSTANT("GL_TEXTURE20", GL_TEXTURE20, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE21 
    REGISTER_LONG_CONSTANT("GL_TEXTURE21", GL_TEXTURE21, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE22 
    REGISTER_LONG_CONSTANT("GL_TEXTURE22", GL_TEXTURE22, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE23 
    REGISTER_LONG_CONSTANT("GL_TEXTURE23", GL_TEXTURE23, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE24 
    REGISTER_LONG_CONSTANT("GL_TEXTURE24", GL_TEXTURE24, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE25 
    REGISTER_LONG_CONSTANT("GL_TEXTURE25", GL_TEXTURE25, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE26 
    REGISTER_LONG_CONSTANT("GL_TEXTURE26", GL_TEXTURE26, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE27 
    REGISTER_LONG_CONSTANT("GL_TEXTURE27", GL_TEXTURE27, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE28 
    REGISTER_LONG_CONSTANT("GL_TEXTURE28", GL_TEXTURE28, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE29 
    REGISTER_LONG_CONSTANT("GL_TEXTURE29", GL_TEXTURE29, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE30 
    REGISTER_LONG_CONSTANT("GL_TEXTURE30", GL_TEXTURE30, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE31 
    REGISTER_LONG_CONSTANT("GL_TEXTURE31", GL_TEXTURE31, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_TEXTURE", GL_ACTIVE_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_MULTISAMPLE", GL_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_ALPHA_TO_COVERAGE 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_ALPHA_TO_COVERAGE", GL_SAMPLE_ALPHA_TO_COVERAGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_ALPHA_TO_ONE 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_ALPHA_TO_ONE", GL_SAMPLE_ALPHA_TO_ONE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_COVERAGE 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_COVERAGE", GL_SAMPLE_COVERAGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_BUFFERS", GL_SAMPLE_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_SAMPLES", GL_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_COVERAGE_VALUE 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_COVERAGE_VALUE", GL_SAMPLE_COVERAGE_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_COVERAGE_INVERT 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_COVERAGE_INVERT", GL_SAMPLE_COVERAGE_INVERT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP", GL_TEXTURE_CUBE_MAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_CUBE_MAP 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_CUBE_MAP", GL_TEXTURE_BINDING_CUBE_MAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_POSITIVE_X 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_POSITIVE_X", GL_TEXTURE_CUBE_MAP_POSITIVE_X, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_NEGATIVE_X 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_NEGATIVE_X", GL_TEXTURE_CUBE_MAP_NEGATIVE_X, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_POSITIVE_Y 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_POSITIVE_Y", GL_TEXTURE_CUBE_MAP_POSITIVE_Y, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_NEGATIVE_Y", GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_POSITIVE_Z 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_POSITIVE_Z", GL_TEXTURE_CUBE_MAP_POSITIVE_Z, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_NEGATIVE_Z", GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_CUBE_MAP 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_CUBE_MAP", GL_PROXY_TEXTURE_CUBE_MAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_CUBE_MAP_TEXTURE_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_CUBE_MAP_TEXTURE_SIZE", GL_MAX_CUBE_MAP_TEXTURE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGB 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGB", GL_COMPRESSED_RGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGBA 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGBA", GL_COMPRESSED_RGBA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPRESSION_HINT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPRESSION_HINT", GL_TEXTURE_COMPRESSION_HINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPRESSED_IMAGE_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPRESSED_IMAGE_SIZE", GL_TEXTURE_COMPRESSED_IMAGE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPRESSED 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPRESSED", GL_TEXTURE_COMPRESSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_COMPRESSED_TEXTURE_FORMATS 
    REGISTER_LONG_CONSTANT("GL_NUM_COMPRESSED_TEXTURE_FORMATS", GL_NUM_COMPRESSED_TEXTURE_FORMATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_TEXTURE_FORMATS 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_TEXTURE_FORMATS", GL_COMPRESSED_TEXTURE_FORMATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLAMP_TO_BORDER 
    REGISTER_LONG_CONSTANT("GL_CLAMP_TO_BORDER", GL_CLAMP_TO_BORDER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_DST_RGB 
    REGISTER_LONG_CONSTANT("GL_BLEND_DST_RGB", GL_BLEND_DST_RGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_SRC_RGB 
    REGISTER_LONG_CONSTANT("GL_BLEND_SRC_RGB", GL_BLEND_SRC_RGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_DST_ALPHA 
    REGISTER_LONG_CONSTANT("GL_BLEND_DST_ALPHA", GL_BLEND_DST_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_SRC_ALPHA 
    REGISTER_LONG_CONSTANT("GL_BLEND_SRC_ALPHA", GL_BLEND_SRC_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINT_FADE_THRESHOLD_SIZE 
    REGISTER_LONG_CONSTANT("GL_POINT_FADE_THRESHOLD_SIZE", GL_POINT_FADE_THRESHOLD_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_COMPONENT16 
    REGISTER_LONG_CONSTANT("GL_DEPTH_COMPONENT16", GL_DEPTH_COMPONENT16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_COMPONENT24 
    REGISTER_LONG_CONSTANT("GL_DEPTH_COMPONENT24", GL_DEPTH_COMPONENT24, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_COMPONENT32 
    REGISTER_LONG_CONSTANT("GL_DEPTH_COMPONENT32", GL_DEPTH_COMPONENT32, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIRRORED_REPEAT 
    REGISTER_LONG_CONSTANT("GL_MIRRORED_REPEAT", GL_MIRRORED_REPEAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TEXTURE_LOD_BIAS 
    REGISTER_LONG_CONSTANT("GL_MAX_TEXTURE_LOD_BIAS", GL_MAX_TEXTURE_LOD_BIAS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_LOD_BIAS 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_LOD_BIAS", GL_TEXTURE_LOD_BIAS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INCR_WRAP 
    REGISTER_LONG_CONSTANT("GL_INCR_WRAP", GL_INCR_WRAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DECR_WRAP 
    REGISTER_LONG_CONSTANT("GL_DECR_WRAP", GL_DECR_WRAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_DEPTH_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_DEPTH_SIZE", GL_TEXTURE_DEPTH_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPARE_MODE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPARE_MODE", GL_TEXTURE_COMPARE_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPARE_FUNC 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPARE_FUNC", GL_TEXTURE_COMPARE_FUNC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FUNC_ADD 
    REGISTER_LONG_CONSTANT("GL_FUNC_ADD", GL_FUNC_ADD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FUNC_SUBTRACT 
    REGISTER_LONG_CONSTANT("GL_FUNC_SUBTRACT", GL_FUNC_SUBTRACT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FUNC_REVERSE_SUBTRACT 
    REGISTER_LONG_CONSTANT("GL_FUNC_REVERSE_SUBTRACT", GL_FUNC_REVERSE_SUBTRACT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIN 
    REGISTER_LONG_CONSTANT("GL_MIN", GL_MIN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX 
    REGISTER_LONG_CONSTANT("GL_MAX", GL_MAX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONSTANT_COLOR 
    REGISTER_LONG_CONSTANT("GL_CONSTANT_COLOR", GL_CONSTANT_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_CONSTANT_COLOR 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_CONSTANT_COLOR", GL_ONE_MINUS_CONSTANT_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONSTANT_ALPHA 
    REGISTER_LONG_CONSTANT("GL_CONSTANT_ALPHA", GL_CONSTANT_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_CONSTANT_ALPHA 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_CONSTANT_ALPHA", GL_ONE_MINUS_CONSTANT_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_BUFFER_SIZE", GL_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_USAGE 
    REGISTER_LONG_CONSTANT("GL_BUFFER_USAGE", GL_BUFFER_USAGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_COUNTER_BITS 
    REGISTER_LONG_CONSTANT("GL_QUERY_COUNTER_BITS", GL_QUERY_COUNTER_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CURRENT_QUERY 
    REGISTER_LONG_CONSTANT("GL_CURRENT_QUERY", GL_CURRENT_QUERY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_RESULT 
    REGISTER_LONG_CONSTANT("GL_QUERY_RESULT", GL_QUERY_RESULT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_RESULT_AVAILABLE 
    REGISTER_LONG_CONSTANT("GL_QUERY_RESULT_AVAILABLE", GL_QUERY_RESULT_AVAILABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ARRAY_BUFFER 
    REGISTER_LONG_CONSTANT("GL_ARRAY_BUFFER", GL_ARRAY_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ELEMENT_ARRAY_BUFFER 
    REGISTER_LONG_CONSTANT("GL_ELEMENT_ARRAY_BUFFER", GL_ELEMENT_ARRAY_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ARRAY_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_ARRAY_BUFFER_BINDING", GL_ARRAY_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ELEMENT_ARRAY_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_ELEMENT_ARRAY_BUFFER_BINDING", GL_ELEMENT_ARRAY_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING", GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_ONLY 
    REGISTER_LONG_CONSTANT("GL_READ_ONLY", GL_READ_ONLY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_WRITE_ONLY 
    REGISTER_LONG_CONSTANT("GL_WRITE_ONLY", GL_WRITE_ONLY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_WRITE 
    REGISTER_LONG_CONSTANT("GL_READ_WRITE", GL_READ_WRITE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_ACCESS 
    REGISTER_LONG_CONSTANT("GL_BUFFER_ACCESS", GL_BUFFER_ACCESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_MAPPED 
    REGISTER_LONG_CONSTANT("GL_BUFFER_MAPPED", GL_BUFFER_MAPPED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_MAP_POINTER 
    REGISTER_LONG_CONSTANT("GL_BUFFER_MAP_POINTER", GL_BUFFER_MAP_POINTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STREAM_DRAW 
    REGISTER_LONG_CONSTANT("GL_STREAM_DRAW", GL_STREAM_DRAW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STREAM_READ 
    REGISTER_LONG_CONSTANT("GL_STREAM_READ", GL_STREAM_READ, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STREAM_COPY 
    REGISTER_LONG_CONSTANT("GL_STREAM_COPY", GL_STREAM_COPY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STATIC_DRAW 
    REGISTER_LONG_CONSTANT("GL_STATIC_DRAW", GL_STATIC_DRAW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STATIC_READ 
    REGISTER_LONG_CONSTANT("GL_STATIC_READ", GL_STATIC_READ, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STATIC_COPY 
    REGISTER_LONG_CONSTANT("GL_STATIC_COPY", GL_STATIC_COPY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DYNAMIC_DRAW 
    REGISTER_LONG_CONSTANT("GL_DYNAMIC_DRAW", GL_DYNAMIC_DRAW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DYNAMIC_READ 
    REGISTER_LONG_CONSTANT("GL_DYNAMIC_READ", GL_DYNAMIC_READ, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DYNAMIC_COPY 
    REGISTER_LONG_CONSTANT("GL_DYNAMIC_COPY", GL_DYNAMIC_COPY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLES_PASSED 
    REGISTER_LONG_CONSTANT("GL_SAMPLES_PASSED", GL_SAMPLES_PASSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRC1_ALPHA 
    REGISTER_LONG_CONSTANT("GL_SRC1_ALPHA", GL_SRC1_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_EQUATION_RGB 
    REGISTER_LONG_CONSTANT("GL_BLEND_EQUATION_RGB", GL_BLEND_EQUATION_RGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_ENABLED 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_ENABLED", GL_VERTEX_ATTRIB_ARRAY_ENABLED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_SIZE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_SIZE", GL_VERTEX_ATTRIB_ARRAY_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_STRIDE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_STRIDE", GL_VERTEX_ATTRIB_ARRAY_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_TYPE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_TYPE", GL_VERTEX_ATTRIB_ARRAY_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CURRENT_VERTEX_ATTRIB 
    REGISTER_LONG_CONSTANT("GL_CURRENT_VERTEX_ATTRIB", GL_CURRENT_VERTEX_ATTRIB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_PROGRAM_POINT_SIZE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_PROGRAM_POINT_SIZE", GL_VERTEX_PROGRAM_POINT_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_POINTER 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_POINTER", GL_VERTEX_ATTRIB_ARRAY_POINTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_FUNC 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_FUNC", GL_STENCIL_BACK_FUNC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_FAIL 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_FAIL", GL_STENCIL_BACK_FAIL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_PASS_DEPTH_FAIL 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_PASS_DEPTH_FAIL", GL_STENCIL_BACK_PASS_DEPTH_FAIL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_PASS_DEPTH_PASS 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_PASS_DEPTH_PASS", GL_STENCIL_BACK_PASS_DEPTH_PASS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DRAW_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_DRAW_BUFFERS", GL_MAX_DRAW_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER0 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER0", GL_DRAW_BUFFER0, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER1 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER1", GL_DRAW_BUFFER1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER2 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER2", GL_DRAW_BUFFER2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER3 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER3", GL_DRAW_BUFFER3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER4 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER4", GL_DRAW_BUFFER4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER5 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER5", GL_DRAW_BUFFER5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER6 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER6", GL_DRAW_BUFFER6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER7 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER7", GL_DRAW_BUFFER7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER8 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER8", GL_DRAW_BUFFER8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER9 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER9", GL_DRAW_BUFFER9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER10 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER10", GL_DRAW_BUFFER10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER11 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER11", GL_DRAW_BUFFER11, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER12 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER12", GL_DRAW_BUFFER12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER13 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER13", GL_DRAW_BUFFER13, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER14 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER14", GL_DRAW_BUFFER14, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_BUFFER15 
    REGISTER_LONG_CONSTANT("GL_DRAW_BUFFER15", GL_DRAW_BUFFER15, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLEND_EQUATION_ALPHA 
    REGISTER_LONG_CONSTANT("GL_BLEND_EQUATION_ALPHA", GL_BLEND_EQUATION_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_ATTRIBS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_ATTRIBS", GL_MAX_VERTEX_ATTRIBS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_NORMALIZED", GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_TEXTURE_IMAGE_UNITS", GL_MAX_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_SHADER 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_SHADER", GL_FRAGMENT_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_SHADER 
    REGISTER_LONG_CONSTANT("GL_VERTEX_SHADER", GL_VERTEX_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_UNIFORM_COMPONENTS", GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_UNIFORM_COMPONENTS", GL_MAX_VERTEX_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VARYING_FLOATS 
    REGISTER_LONG_CONSTANT("GL_MAX_VARYING_FLOATS", GL_MAX_VARYING_FLOATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS", GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS", GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_TYPE 
    REGISTER_LONG_CONSTANT("GL_SHADER_TYPE", GL_SHADER_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_VEC2 
    REGISTER_LONG_CONSTANT("GL_FLOAT_VEC2", GL_FLOAT_VEC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_VEC3 
    REGISTER_LONG_CONSTANT("GL_FLOAT_VEC3", GL_FLOAT_VEC3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_VEC4 
    REGISTER_LONG_CONSTANT("GL_FLOAT_VEC4", GL_FLOAT_VEC4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_VEC2 
    REGISTER_LONG_CONSTANT("GL_INT_VEC2", GL_INT_VEC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_VEC3 
    REGISTER_LONG_CONSTANT("GL_INT_VEC3", GL_INT_VEC3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_VEC4 
    REGISTER_LONG_CONSTANT("GL_INT_VEC4", GL_INT_VEC4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BOOL 
    REGISTER_LONG_CONSTANT("GL_BOOL", GL_BOOL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BOOL_VEC2 
    REGISTER_LONG_CONSTANT("GL_BOOL_VEC2", GL_BOOL_VEC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BOOL_VEC3 
    REGISTER_LONG_CONSTANT("GL_BOOL_VEC3", GL_BOOL_VEC3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BOOL_VEC4 
    REGISTER_LONG_CONSTANT("GL_BOOL_VEC4", GL_BOOL_VEC4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT2 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT2", GL_FLOAT_MAT2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT3 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT3", GL_FLOAT_MAT3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT4 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT4", GL_FLOAT_MAT4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_1D 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_1D", GL_SAMPLER_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D", GL_SAMPLER_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_3D 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_3D", GL_SAMPLER_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_CUBE 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_CUBE", GL_SAMPLER_CUBE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_1D_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_1D_SHADOW", GL_SAMPLER_1D_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_SHADOW", GL_SAMPLER_2D_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DELETE_STATUS 
    REGISTER_LONG_CONSTANT("GL_DELETE_STATUS", GL_DELETE_STATUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPILE_STATUS 
    REGISTER_LONG_CONSTANT("GL_COMPILE_STATUS", GL_COMPILE_STATUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINK_STATUS 
    REGISTER_LONG_CONSTANT("GL_LINK_STATUS", GL_LINK_STATUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VALIDATE_STATUS 
    REGISTER_LONG_CONSTANT("GL_VALIDATE_STATUS", GL_VALIDATE_STATUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INFO_LOG_LENGTH 
    REGISTER_LONG_CONSTANT("GL_INFO_LOG_LENGTH", GL_INFO_LOG_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATTACHED_SHADERS 
    REGISTER_LONG_CONSTANT("GL_ATTACHED_SHADERS", GL_ATTACHED_SHADERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_UNIFORMS", GL_ACTIVE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_UNIFORM_MAX_LENGTH 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_UNIFORM_MAX_LENGTH", GL_ACTIVE_UNIFORM_MAX_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_SOURCE_LENGTH 
    REGISTER_LONG_CONSTANT("GL_SHADER_SOURCE_LENGTH", GL_SHADER_SOURCE_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_ATTRIBUTES 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_ATTRIBUTES", GL_ACTIVE_ATTRIBUTES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_ATTRIBUTE_MAX_LENGTH 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_ATTRIBUTE_MAX_LENGTH", GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_SHADER_DERIVATIVE_HINT 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_SHADER_DERIVATIVE_HINT", GL_FRAGMENT_SHADER_DERIVATIVE_HINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADING_LANGUAGE_VERSION 
    REGISTER_LONG_CONSTANT("GL_SHADING_LANGUAGE_VERSION", GL_SHADING_LANGUAGE_VERSION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CURRENT_PROGRAM 
    REGISTER_LONG_CONSTANT("GL_CURRENT_PROGRAM", GL_CURRENT_PROGRAM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POINT_SPRITE_COORD_ORIGIN 
    REGISTER_LONG_CONSTANT("GL_POINT_SPRITE_COORD_ORIGIN", GL_POINT_SPRITE_COORD_ORIGIN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOWER_LEFT 
    REGISTER_LONG_CONSTANT("GL_LOWER_LEFT", GL_LOWER_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UPPER_LEFT 
    REGISTER_LONG_CONSTANT("GL_UPPER_LEFT", GL_UPPER_LEFT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_REF 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_REF", GL_STENCIL_BACK_REF, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_VALUE_MASK 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_VALUE_MASK", GL_STENCIL_BACK_VALUE_MASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_BACK_WRITEMASK 
    REGISTER_LONG_CONSTANT("GL_STENCIL_BACK_WRITEMASK", GL_STENCIL_BACK_WRITEMASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PIXEL_PACK_BUFFER 
    REGISTER_LONG_CONSTANT("GL_PIXEL_PACK_BUFFER", GL_PIXEL_PACK_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PIXEL_UNPACK_BUFFER 
    REGISTER_LONG_CONSTANT("GL_PIXEL_UNPACK_BUFFER", GL_PIXEL_UNPACK_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PIXEL_PACK_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_PIXEL_PACK_BUFFER_BINDING", GL_PIXEL_PACK_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PIXEL_UNPACK_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_PIXEL_UNPACK_BUFFER_BINDING", GL_PIXEL_UNPACK_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT2x3 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT2x3", GL_FLOAT_MAT2x3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT2x4 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT2x4", GL_FLOAT_MAT2x4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT3x2 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT3x2", GL_FLOAT_MAT3x2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT3x4 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT3x4", GL_FLOAT_MAT3x4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT4x2 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT4x2", GL_FLOAT_MAT4x2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_MAT4x3 
    REGISTER_LONG_CONSTANT("GL_FLOAT_MAT4x3", GL_FLOAT_MAT4x3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRGB 
    REGISTER_LONG_CONSTANT("GL_SRGB", GL_SRGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRGB8 
    REGISTER_LONG_CONSTANT("GL_SRGB8", GL_SRGB8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRGB_ALPHA 
    REGISTER_LONG_CONSTANT("GL_SRGB_ALPHA", GL_SRGB_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRGB8_ALPHA8 
    REGISTER_LONG_CONSTANT("GL_SRGB8_ALPHA8", GL_SRGB8_ALPHA8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SRGB 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SRGB", GL_COMPRESSED_SRGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SRGB_ALPHA 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SRGB_ALPHA", GL_COMPRESSED_SRGB_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPARE_REF_TO_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_COMPARE_REF_TO_TEXTURE", GL_COMPARE_REF_TO_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE0 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE0", GL_CLIP_DISTANCE0, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE1 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE1", GL_CLIP_DISTANCE1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE2 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE2", GL_CLIP_DISTANCE2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE3 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE3", GL_CLIP_DISTANCE3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE4 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE4", GL_CLIP_DISTANCE4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE5 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE5", GL_CLIP_DISTANCE5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE6 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE6", GL_CLIP_DISTANCE6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DISTANCE7 
    REGISTER_LONG_CONSTANT("GL_CLIP_DISTANCE7", GL_CLIP_DISTANCE7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_CLIP_DISTANCES 
    REGISTER_LONG_CONSTANT("GL_MAX_CLIP_DISTANCES", GL_MAX_CLIP_DISTANCES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAJOR_VERSION 
    REGISTER_LONG_CONSTANT("GL_MAJOR_VERSION", GL_MAJOR_VERSION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MINOR_VERSION 
    REGISTER_LONG_CONSTANT("GL_MINOR_VERSION", GL_MINOR_VERSION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_EXTENSIONS 
    REGISTER_LONG_CONSTANT("GL_NUM_EXTENSIONS", GL_NUM_EXTENSIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_FLAGS 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_FLAGS", GL_CONTEXT_FLAGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RED 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RED", GL_COMPRESSED_RED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RG 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RG", GL_COMPRESSED_RG, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT", GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA32F 
    REGISTER_LONG_CONSTANT("GL_RGBA32F", GL_RGBA32F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB32F 
    REGISTER_LONG_CONSTANT("GL_RGB32F", GL_RGB32F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA16F 
    REGISTER_LONG_CONSTANT("GL_RGBA16F", GL_RGBA16F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB16F 
    REGISTER_LONG_CONSTANT("GL_RGB16F", GL_RGB16F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_INTEGER 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_INTEGER", GL_VERTEX_ATTRIB_ARRAY_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_ARRAY_TEXTURE_LAYERS 
    REGISTER_LONG_CONSTANT("GL_MAX_ARRAY_TEXTURE_LAYERS", GL_MAX_ARRAY_TEXTURE_LAYERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIN_PROGRAM_TEXEL_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MIN_PROGRAM_TEXEL_OFFSET", GL_MIN_PROGRAM_TEXEL_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_PROGRAM_TEXEL_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MAX_PROGRAM_TEXEL_OFFSET", GL_MAX_PROGRAM_TEXEL_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLAMP_READ_COLOR 
    REGISTER_LONG_CONSTANT("GL_CLAMP_READ_COLOR", GL_CLAMP_READ_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FIXED_ONLY 
    REGISTER_LONG_CONSTANT("GL_FIXED_ONLY", GL_FIXED_ONLY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VARYING_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_VARYING_COMPONENTS", GL_MAX_VARYING_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_1D_ARRAY", GL_TEXTURE_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_1D_ARRAY", GL_PROXY_TEXTURE_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_2D_ARRAY", GL_TEXTURE_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_2D_ARRAY", GL_PROXY_TEXTURE_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_1D_ARRAY", GL_TEXTURE_BINDING_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_2D_ARRAY", GL_TEXTURE_BINDING_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R11F_G11F_B10F 
    REGISTER_LONG_CONSTANT("GL_R11F_G11F_B10F", GL_R11F_G11F_B10F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_10F_11F_11F_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_10F_11F_11F_REV", GL_UNSIGNED_INT_10F_11F_11F_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB9_E5 
    REGISTER_LONG_CONSTANT("GL_RGB9_E5", GL_RGB9_E5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_5_9_9_9_REV 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_5_9_9_9_REV", GL_UNSIGNED_INT_5_9_9_9_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SHARED_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SHARED_SIZE", GL_TEXTURE_SHARED_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH", GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_MODE 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_MODE", GL_TRANSFORM_FEEDBACK_BUFFER_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS", GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_VARYINGS 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_VARYINGS", GL_TRANSFORM_FEEDBACK_VARYINGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_START 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_START", GL_TRANSFORM_FEEDBACK_BUFFER_START, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_SIZE", GL_TRANSFORM_FEEDBACK_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PRIMITIVES_GENERATED 
    REGISTER_LONG_CONSTANT("GL_PRIMITIVES_GENERATED", GL_PRIMITIVES_GENERATED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN", GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RASTERIZER_DISCARD 
    REGISTER_LONG_CONSTANT("GL_RASTERIZER_DISCARD", GL_RASTERIZER_DISCARD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS", GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 
    REGISTER_LONG_CONSTANT("GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS", GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERLEAVED_ATTRIBS 
    REGISTER_LONG_CONSTANT("GL_INTERLEAVED_ATTRIBS", GL_INTERLEAVED_ATTRIBS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SEPARATE_ATTRIBS 
    REGISTER_LONG_CONSTANT("GL_SEPARATE_ATTRIBS", GL_SEPARATE_ATTRIBS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER", GL_TRANSFORM_FEEDBACK_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_BINDING", GL_TRANSFORM_FEEDBACK_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA32UI 
    REGISTER_LONG_CONSTANT("GL_RGBA32UI", GL_RGBA32UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB32UI 
    REGISTER_LONG_CONSTANT("GL_RGB32UI", GL_RGB32UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA16UI 
    REGISTER_LONG_CONSTANT("GL_RGBA16UI", GL_RGBA16UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB16UI 
    REGISTER_LONG_CONSTANT("GL_RGB16UI", GL_RGB16UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA8UI 
    REGISTER_LONG_CONSTANT("GL_RGBA8UI", GL_RGBA8UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB8UI 
    REGISTER_LONG_CONSTANT("GL_RGB8UI", GL_RGB8UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA32I 
    REGISTER_LONG_CONSTANT("GL_RGBA32I", GL_RGBA32I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB32I 
    REGISTER_LONG_CONSTANT("GL_RGB32I", GL_RGB32I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA16I 
    REGISTER_LONG_CONSTANT("GL_RGBA16I", GL_RGBA16I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB16I 
    REGISTER_LONG_CONSTANT("GL_RGB16I", GL_RGB16I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA8I 
    REGISTER_LONG_CONSTANT("GL_RGBA8I", GL_RGBA8I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB8I 
    REGISTER_LONG_CONSTANT("GL_RGB8I", GL_RGB8I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RED_INTEGER 
    REGISTER_LONG_CONSTANT("GL_RED_INTEGER", GL_RED_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GREEN_INTEGER 
    REGISTER_LONG_CONSTANT("GL_GREEN_INTEGER", GL_GREEN_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLUE_INTEGER 
    REGISTER_LONG_CONSTANT("GL_BLUE_INTEGER", GL_BLUE_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB_INTEGER 
    REGISTER_LONG_CONSTANT("GL_RGB_INTEGER", GL_RGB_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA_INTEGER 
    REGISTER_LONG_CONSTANT("GL_RGBA_INTEGER", GL_RGBA_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BGR_INTEGER 
    REGISTER_LONG_CONSTANT("GL_BGR_INTEGER", GL_BGR_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BGRA_INTEGER 
    REGISTER_LONG_CONSTANT("GL_BGRA_INTEGER", GL_BGRA_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_1D_ARRAY", GL_SAMPLER_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_ARRAY", GL_SAMPLER_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_1D_ARRAY_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_1D_ARRAY_SHADOW", GL_SAMPLER_1D_ARRAY_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_ARRAY_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_ARRAY_SHADOW", GL_SAMPLER_2D_ARRAY_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_CUBE_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_CUBE_SHADOW", GL_SAMPLER_CUBE_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_VEC2 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_VEC2", GL_UNSIGNED_INT_VEC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_VEC3 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_VEC3", GL_UNSIGNED_INT_VEC3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_VEC4 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_VEC4", GL_UNSIGNED_INT_VEC4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_1D 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_1D", GL_INT_SAMPLER_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_2D 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_2D", GL_INT_SAMPLER_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_3D 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_3D", GL_INT_SAMPLER_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_CUBE 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_CUBE", GL_INT_SAMPLER_CUBE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_1D_ARRAY", GL_INT_SAMPLER_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_2D_ARRAY", GL_INT_SAMPLER_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_1D 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_1D", GL_UNSIGNED_INT_SAMPLER_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_2D 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_2D", GL_UNSIGNED_INT_SAMPLER_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_3D 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_3D", GL_UNSIGNED_INT_SAMPLER_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_CUBE 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_CUBE", GL_UNSIGNED_INT_SAMPLER_CUBE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_1D_ARRAY", GL_UNSIGNED_INT_SAMPLER_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_2D_ARRAY", GL_UNSIGNED_INT_SAMPLER_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_WAIT 
    REGISTER_LONG_CONSTANT("GL_QUERY_WAIT", GL_QUERY_WAIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_NO_WAIT 
    REGISTER_LONG_CONSTANT("GL_QUERY_NO_WAIT", GL_QUERY_NO_WAIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BY_REGION_WAIT 
    REGISTER_LONG_CONSTANT("GL_QUERY_BY_REGION_WAIT", GL_QUERY_BY_REGION_WAIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BY_REGION_NO_WAIT 
    REGISTER_LONG_CONSTANT("GL_QUERY_BY_REGION_NO_WAIT", GL_QUERY_BY_REGION_NO_WAIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_ACCESS_FLAGS 
    REGISTER_LONG_CONSTANT("GL_BUFFER_ACCESS_FLAGS", GL_BUFFER_ACCESS_FLAGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_MAP_LENGTH 
    REGISTER_LONG_CONSTANT("GL_BUFFER_MAP_LENGTH", GL_BUFFER_MAP_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_MAP_OFFSET 
    REGISTER_LONG_CONSTANT("GL_BUFFER_MAP_OFFSET", GL_BUFFER_MAP_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_COMPONENT32F 
    REGISTER_LONG_CONSTANT("GL_DEPTH_COMPONENT32F", GL_DEPTH_COMPONENT32F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH32F_STENCIL8 
    REGISTER_LONG_CONSTANT("GL_DEPTH32F_STENCIL8", GL_DEPTH32F_STENCIL8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FLOAT_32_UNSIGNED_INT_24_8_REV 
    REGISTER_LONG_CONSTANT("GL_FLOAT_32_UNSIGNED_INT_24_8_REV", GL_FLOAT_32_UNSIGNED_INT_24_8_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INVALID_FRAMEBUFFER_OPERATION 
    REGISTER_LONG_CONSTANT("GL_INVALID_FRAMEBUFFER_OPERATION", GL_INVALID_FRAMEBUFFER_OPERATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING", GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE", GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE", GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE", GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE", GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE", GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE", GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE", GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_DEFAULT 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_DEFAULT", GL_FRAMEBUFFER_DEFAULT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_UNDEFINED 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_UNDEFINED", GL_FRAMEBUFFER_UNDEFINED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_STENCIL_ATTACHMENT 
    REGISTER_LONG_CONSTANT("GL_DEPTH_STENCIL_ATTACHMENT", GL_DEPTH_STENCIL_ATTACHMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_RENDERBUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_RENDERBUFFER_SIZE", GL_MAX_RENDERBUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_STENCIL 
    REGISTER_LONG_CONSTANT("GL_DEPTH_STENCIL", GL_DEPTH_STENCIL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_24_8 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_24_8", GL_UNSIGNED_INT_24_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH24_STENCIL8 
    REGISTER_LONG_CONSTANT("GL_DEPTH24_STENCIL8", GL_DEPTH24_STENCIL8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_STENCIL_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_STENCIL_SIZE", GL_TEXTURE_STENCIL_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_RED_TYPE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_RED_TYPE", GL_TEXTURE_RED_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_GREEN_TYPE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_GREEN_TYPE", GL_TEXTURE_GREEN_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BLUE_TYPE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BLUE_TYPE", GL_TEXTURE_BLUE_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_ALPHA_TYPE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_ALPHA_TYPE", GL_TEXTURE_ALPHA_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_DEPTH_TYPE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_DEPTH_TYPE", GL_TEXTURE_DEPTH_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_NORMALIZED 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_NORMALIZED", GL_UNSIGNED_NORMALIZED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_BINDING", GL_FRAMEBUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_FRAMEBUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_DRAW_FRAMEBUFFER_BINDING", GL_DRAW_FRAMEBUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_BINDING", GL_RENDERBUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_FRAMEBUFFER 
    REGISTER_LONG_CONSTANT("GL_READ_FRAMEBUFFER", GL_READ_FRAMEBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_FRAMEBUFFER 
    REGISTER_LONG_CONSTANT("GL_DRAW_FRAMEBUFFER", GL_DRAW_FRAMEBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_FRAMEBUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_READ_FRAMEBUFFER_BINDING", GL_READ_FRAMEBUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_SAMPLES", GL_RENDERBUFFER_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE", GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME", GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL", GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE", GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER", GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_COMPLETE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_COMPLETE", GL_FRAMEBUFFER_COMPLETE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT", GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT", GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER", GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER", GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_UNSUPPORTED 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_UNSUPPORTED", GL_FRAMEBUFFER_UNSUPPORTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COLOR_ATTACHMENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COLOR_ATTACHMENTS", GL_MAX_COLOR_ATTACHMENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT0 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT0", GL_COLOR_ATTACHMENT0, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT1 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT1", GL_COLOR_ATTACHMENT1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT2 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT2", GL_COLOR_ATTACHMENT2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT3 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT3", GL_COLOR_ATTACHMENT3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT4 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT4", GL_COLOR_ATTACHMENT4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT5 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT5", GL_COLOR_ATTACHMENT5, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT6 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT6", GL_COLOR_ATTACHMENT6, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT7 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT7", GL_COLOR_ATTACHMENT7, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT8 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT8", GL_COLOR_ATTACHMENT8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT9 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT9", GL_COLOR_ATTACHMENT9, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT10 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT10", GL_COLOR_ATTACHMENT10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT11 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT11", GL_COLOR_ATTACHMENT11, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT12 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT12", GL_COLOR_ATTACHMENT12, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT13 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT13", GL_COLOR_ATTACHMENT13, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT14 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT14", GL_COLOR_ATTACHMENT14, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT15 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT15", GL_COLOR_ATTACHMENT15, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT16 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT16", GL_COLOR_ATTACHMENT16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT17 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT17", GL_COLOR_ATTACHMENT17, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT18 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT18", GL_COLOR_ATTACHMENT18, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT19 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT19", GL_COLOR_ATTACHMENT19, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT20 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT20", GL_COLOR_ATTACHMENT20, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT21 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT21", GL_COLOR_ATTACHMENT21, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT22 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT22", GL_COLOR_ATTACHMENT22, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT23 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT23", GL_COLOR_ATTACHMENT23, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT24 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT24", GL_COLOR_ATTACHMENT24, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT25 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT25", GL_COLOR_ATTACHMENT25, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT26 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT26", GL_COLOR_ATTACHMENT26, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT27 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT27", GL_COLOR_ATTACHMENT27, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT28 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT28", GL_COLOR_ATTACHMENT28, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT29 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT29", GL_COLOR_ATTACHMENT29, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT30 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT30", GL_COLOR_ATTACHMENT30, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ATTACHMENT31 
    REGISTER_LONG_CONSTANT("GL_COLOR_ATTACHMENT31", GL_COLOR_ATTACHMENT31, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_ATTACHMENT 
    REGISTER_LONG_CONSTANT("GL_DEPTH_ATTACHMENT", GL_DEPTH_ATTACHMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_ATTACHMENT 
    REGISTER_LONG_CONSTANT("GL_STENCIL_ATTACHMENT", GL_STENCIL_ATTACHMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER", GL_FRAMEBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER", GL_RENDERBUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_WIDTH 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_WIDTH", GL_RENDERBUFFER_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_HEIGHT", GL_RENDERBUFFER_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_INTERNAL_FORMAT 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_INTERNAL_FORMAT", GL_RENDERBUFFER_INTERNAL_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_INDEX1 
    REGISTER_LONG_CONSTANT("GL_STENCIL_INDEX1", GL_STENCIL_INDEX1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_INDEX4 
    REGISTER_LONG_CONSTANT("GL_STENCIL_INDEX4", GL_STENCIL_INDEX4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_INDEX8 
    REGISTER_LONG_CONSTANT("GL_STENCIL_INDEX8", GL_STENCIL_INDEX8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_INDEX16 
    REGISTER_LONG_CONSTANT("GL_STENCIL_INDEX16", GL_STENCIL_INDEX16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_RED_SIZE 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_RED_SIZE", GL_RENDERBUFFER_RED_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_GREEN_SIZE 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_GREEN_SIZE", GL_RENDERBUFFER_GREEN_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_BLUE_SIZE 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_BLUE_SIZE", GL_RENDERBUFFER_BLUE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_ALPHA_SIZE 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_ALPHA_SIZE", GL_RENDERBUFFER_ALPHA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_DEPTH_SIZE 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_DEPTH_SIZE", GL_RENDERBUFFER_DEPTH_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RENDERBUFFER_STENCIL_SIZE 
    REGISTER_LONG_CONSTANT("GL_RENDERBUFFER_STENCIL_SIZE", GL_RENDERBUFFER_STENCIL_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE", GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_MAX_SAMPLES", GL_MAX_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INDEX 
    REGISTER_LONG_CONSTANT("GL_INDEX", GL_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_SRGB 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_SRGB", GL_FRAMEBUFFER_SRGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_HALF_FLOAT 
    REGISTER_LONG_CONSTANT("GL_HALF_FLOAT", GL_HALF_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_READ_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_READ_BIT", GL_MAP_READ_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_WRITE_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_WRITE_BIT", GL_MAP_WRITE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_INVALIDATE_RANGE_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_INVALIDATE_RANGE_BIT", GL_MAP_INVALIDATE_RANGE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_INVALIDATE_BUFFER_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_INVALIDATE_BUFFER_BIT", GL_MAP_INVALIDATE_BUFFER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_FLUSH_EXPLICIT_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_FLUSH_EXPLICIT_BIT", GL_MAP_FLUSH_EXPLICIT_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_UNSYNCHRONIZED_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_UNSYNCHRONIZED_BIT", GL_MAP_UNSYNCHRONIZED_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RED_RGTC1 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RED_RGTC1", GL_COMPRESSED_RED_RGTC1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SIGNED_RED_RGTC1 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SIGNED_RED_RGTC1", GL_COMPRESSED_SIGNED_RED_RGTC1, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RG_RGTC2 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RG_RGTC2", GL_COMPRESSED_RG_RGTC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SIGNED_RG_RGTC2 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SIGNED_RG_RGTC2", GL_COMPRESSED_SIGNED_RG_RGTC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG 
    REGISTER_LONG_CONSTANT("GL_RG", GL_RG, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG_INTEGER 
    REGISTER_LONG_CONSTANT("GL_RG_INTEGER", GL_RG_INTEGER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R8 
    REGISTER_LONG_CONSTANT("GL_R8", GL_R8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R16 
    REGISTER_LONG_CONSTANT("GL_R16", GL_R16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG8 
    REGISTER_LONG_CONSTANT("GL_RG8", GL_RG8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG16 
    REGISTER_LONG_CONSTANT("GL_RG16", GL_RG16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R16F 
    REGISTER_LONG_CONSTANT("GL_R16F", GL_R16F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R32F 
    REGISTER_LONG_CONSTANT("GL_R32F", GL_R32F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG16F 
    REGISTER_LONG_CONSTANT("GL_RG16F", GL_RG16F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG32F 
    REGISTER_LONG_CONSTANT("GL_RG32F", GL_RG32F, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R8I 
    REGISTER_LONG_CONSTANT("GL_R8I", GL_R8I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R8UI 
    REGISTER_LONG_CONSTANT("GL_R8UI", GL_R8UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R16I 
    REGISTER_LONG_CONSTANT("GL_R16I", GL_R16I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R16UI 
    REGISTER_LONG_CONSTANT("GL_R16UI", GL_R16UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R32I 
    REGISTER_LONG_CONSTANT("GL_R32I", GL_R32I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R32UI 
    REGISTER_LONG_CONSTANT("GL_R32UI", GL_R32UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG8I 
    REGISTER_LONG_CONSTANT("GL_RG8I", GL_RG8I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG8UI 
    REGISTER_LONG_CONSTANT("GL_RG8UI", GL_RG8UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG16I 
    REGISTER_LONG_CONSTANT("GL_RG16I", GL_RG16I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG16UI 
    REGISTER_LONG_CONSTANT("GL_RG16UI", GL_RG16UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG32I 
    REGISTER_LONG_CONSTANT("GL_RG32I", GL_RG32I, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG32UI 
    REGISTER_LONG_CONSTANT("GL_RG32UI", GL_RG32UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ARRAY_BINDING 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ARRAY_BINDING", GL_VERTEX_ARRAY_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_RECT 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_RECT", GL_SAMPLER_2D_RECT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_RECT_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_RECT_SHADOW", GL_SAMPLER_2D_RECT_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_BUFFER 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_BUFFER", GL_SAMPLER_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_2D_RECT 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_2D_RECT", GL_INT_SAMPLER_2D_RECT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_BUFFER 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_BUFFER", GL_INT_SAMPLER_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_2D_RECT 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_2D_RECT", GL_UNSIGNED_INT_SAMPLER_2D_RECT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_BUFFER 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_BUFFER", GL_UNSIGNED_INT_SAMPLER_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BUFFER 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BUFFER", GL_TEXTURE_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TEXTURE_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_TEXTURE_BUFFER_SIZE", GL_MAX_TEXTURE_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_BUFFER 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_BUFFER", GL_TEXTURE_BINDING_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BUFFER_DATA_STORE_BINDING 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BUFFER_DATA_STORE_BINDING", GL_TEXTURE_BUFFER_DATA_STORE_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_RECTANGLE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_RECTANGLE", GL_TEXTURE_RECTANGLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_RECTANGLE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_RECTANGLE", GL_TEXTURE_BINDING_RECTANGLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_RECTANGLE 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_RECTANGLE", GL_PROXY_TEXTURE_RECTANGLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_RECTANGLE_TEXTURE_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_RECTANGLE_TEXTURE_SIZE", GL_MAX_RECTANGLE_TEXTURE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R8_SNORM 
    REGISTER_LONG_CONSTANT("GL_R8_SNORM", GL_R8_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG8_SNORM 
    REGISTER_LONG_CONSTANT("GL_RG8_SNORM", GL_RG8_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB8_SNORM 
    REGISTER_LONG_CONSTANT("GL_RGB8_SNORM", GL_RGB8_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA8_SNORM 
    REGISTER_LONG_CONSTANT("GL_RGBA8_SNORM", GL_RGBA8_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_R16_SNORM 
    REGISTER_LONG_CONSTANT("GL_R16_SNORM", GL_R16_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RG16_SNORM 
    REGISTER_LONG_CONSTANT("GL_RG16_SNORM", GL_RG16_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB16_SNORM 
    REGISTER_LONG_CONSTANT("GL_RGB16_SNORM", GL_RGB16_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGBA16_SNORM 
    REGISTER_LONG_CONSTANT("GL_RGBA16_SNORM", GL_RGBA16_SNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SIGNED_NORMALIZED 
    REGISTER_LONG_CONSTANT("GL_SIGNED_NORMALIZED", GL_SIGNED_NORMALIZED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PRIMITIVE_RESTART 
    REGISTER_LONG_CONSTANT("GL_PRIMITIVE_RESTART", GL_PRIMITIVE_RESTART, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PRIMITIVE_RESTART_INDEX 
    REGISTER_LONG_CONSTANT("GL_PRIMITIVE_RESTART_INDEX", GL_PRIMITIVE_RESTART_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COPY_READ_BUFFER 
    REGISTER_LONG_CONSTANT("GL_COPY_READ_BUFFER", GL_COPY_READ_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COPY_WRITE_BUFFER 
    REGISTER_LONG_CONSTANT("GL_COPY_WRITE_BUFFER", GL_COPY_WRITE_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BUFFER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BUFFER", GL_UNIFORM_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BUFFER_BINDING", GL_UNIFORM_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BUFFER_START 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BUFFER_START", GL_UNIFORM_BUFFER_START, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BUFFER_SIZE", GL_UNIFORM_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_UNIFORM_BLOCKS", GL_MAX_VERTEX_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_UNIFORM_BLOCKS", GL_MAX_GEOMETRY_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_UNIFORM_BLOCKS", GL_MAX_FRAGMENT_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_UNIFORM_BLOCKS", GL_MAX_COMBINED_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_UNIFORM_BUFFER_BINDINGS 
    REGISTER_LONG_CONSTANT("GL_MAX_UNIFORM_BUFFER_BINDINGS", GL_MAX_UNIFORM_BUFFER_BINDINGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_UNIFORM_BLOCK_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_UNIFORM_BLOCK_SIZE", GL_MAX_UNIFORM_BLOCK_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS", GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS", GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS", GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT", GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH", GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_UNIFORM_BLOCKS", GL_ACTIVE_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_TYPE 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_TYPE", GL_UNIFORM_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_SIZE 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_SIZE", GL_UNIFORM_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_NAME_LENGTH 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_NAME_LENGTH", GL_UNIFORM_NAME_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_INDEX 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_INDEX", GL_UNIFORM_BLOCK_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_OFFSET 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_OFFSET", GL_UNIFORM_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_ARRAY_STRIDE 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_ARRAY_STRIDE", GL_UNIFORM_ARRAY_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_MATRIX_STRIDE 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_MATRIX_STRIDE", GL_UNIFORM_MATRIX_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_IS_ROW_MAJOR 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_IS_ROW_MAJOR", GL_UNIFORM_IS_ROW_MAJOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_BINDING 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_BINDING", GL_UNIFORM_BLOCK_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_DATA_SIZE 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_DATA_SIZE", GL_UNIFORM_BLOCK_DATA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_NAME_LENGTH 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_NAME_LENGTH", GL_UNIFORM_BLOCK_NAME_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS", GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES", GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER", GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER", GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER", GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INVALID_INDEX 
    REGISTER_LONG_CONSTANT("GL_INVALID_INDEX", GL_INVALID_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_CORE_PROFILE_BIT 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_CORE_PROFILE_BIT", GL_CONTEXT_CORE_PROFILE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_COMPATIBILITY_PROFILE_BIT", GL_CONTEXT_COMPATIBILITY_PROFILE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINES_ADJACENCY 
    REGISTER_LONG_CONSTANT("GL_LINES_ADJACENCY", GL_LINES_ADJACENCY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LINE_STRIP_ADJACENCY 
    REGISTER_LONG_CONSTANT("GL_LINE_STRIP_ADJACENCY", GL_LINE_STRIP_ADJACENCY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRIANGLES_ADJACENCY 
    REGISTER_LONG_CONSTANT("GL_TRIANGLES_ADJACENCY", GL_TRIANGLES_ADJACENCY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRIANGLE_STRIP_ADJACENCY 
    REGISTER_LONG_CONSTANT("GL_TRIANGLE_STRIP_ADJACENCY", GL_TRIANGLE_STRIP_ADJACENCY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_POINT_SIZE 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_POINT_SIZE", GL_PROGRAM_POINT_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS", GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_ATTACHMENT_LAYERED 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_ATTACHMENT_LAYERED", GL_FRAMEBUFFER_ATTACHMENT_LAYERED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS", GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_SHADER 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_SHADER", GL_GEOMETRY_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_VERTICES_OUT 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_VERTICES_OUT", GL_GEOMETRY_VERTICES_OUT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_INPUT_TYPE 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_INPUT_TYPE", GL_GEOMETRY_INPUT_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_OUTPUT_TYPE 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_OUTPUT_TYPE", GL_GEOMETRY_OUTPUT_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_UNIFORM_COMPONENTS", GL_MAX_GEOMETRY_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_OUTPUT_VERTICES 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_OUTPUT_VERTICES", GL_MAX_GEOMETRY_OUTPUT_VERTICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS", GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_OUTPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_OUTPUT_COMPONENTS", GL_MAX_VERTEX_OUTPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_INPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_INPUT_COMPONENTS", GL_MAX_GEOMETRY_INPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_OUTPUT_COMPONENTS", GL_MAX_GEOMETRY_OUTPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_INPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_INPUT_COMPONENTS", GL_MAX_FRAGMENT_INPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_PROFILE_MASK 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_PROFILE_MASK", GL_CONTEXT_PROFILE_MASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_CLAMP 
    REGISTER_LONG_CONSTANT("GL_DEPTH_CLAMP", GL_DEPTH_CLAMP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION 
    REGISTER_LONG_CONSTANT("GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION", GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FIRST_VERTEX_CONVENTION 
    REGISTER_LONG_CONSTANT("GL_FIRST_VERTEX_CONVENTION", GL_FIRST_VERTEX_CONVENTION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LAST_VERTEX_CONVENTION 
    REGISTER_LONG_CONSTANT("GL_LAST_VERTEX_CONVENTION", GL_LAST_VERTEX_CONVENTION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROVOKING_VERTEX 
    REGISTER_LONG_CONSTANT("GL_PROVOKING_VERTEX", GL_PROVOKING_VERTEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_SEAMLESS 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_SEAMLESS", GL_TEXTURE_CUBE_MAP_SEAMLESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SERVER_WAIT_TIMEOUT 
    REGISTER_LONG_CONSTANT("GL_MAX_SERVER_WAIT_TIMEOUT", GL_MAX_SERVER_WAIT_TIMEOUT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_OBJECT_TYPE 
    REGISTER_LONG_CONSTANT("GL_OBJECT_TYPE", GL_OBJECT_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SYNC_CONDITION 
    REGISTER_LONG_CONSTANT("GL_SYNC_CONDITION", GL_SYNC_CONDITION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SYNC_STATUS 
    REGISTER_LONG_CONSTANT("GL_SYNC_STATUS", GL_SYNC_STATUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SYNC_FLAGS 
    REGISTER_LONG_CONSTANT("GL_SYNC_FLAGS", GL_SYNC_FLAGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SYNC_FENCE 
    REGISTER_LONG_CONSTANT("GL_SYNC_FENCE", GL_SYNC_FENCE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SYNC_GPU_COMMANDS_COMPLETE 
    REGISTER_LONG_CONSTANT("GL_SYNC_GPU_COMMANDS_COMPLETE", GL_SYNC_GPU_COMMANDS_COMPLETE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNALED 
    REGISTER_LONG_CONSTANT("GL_UNSIGNALED", GL_UNSIGNALED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SIGNALED 
    REGISTER_LONG_CONSTANT("GL_SIGNALED", GL_SIGNALED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ALREADY_SIGNALED 
    REGISTER_LONG_CONSTANT("GL_ALREADY_SIGNALED", GL_ALREADY_SIGNALED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TIMEOUT_EXPIRED 
    REGISTER_LONG_CONSTANT("GL_TIMEOUT_EXPIRED", GL_TIMEOUT_EXPIRED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONDITION_SATISFIED 
    REGISTER_LONG_CONSTANT("GL_CONDITION_SATISFIED", GL_CONDITION_SATISFIED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_WAIT_FAILED 
    REGISTER_LONG_CONSTANT("GL_WAIT_FAILED", GL_WAIT_FAILED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TIMEOUT_IGNORED 
    REGISTER_LONG_CONSTANT("GL_TIMEOUT_IGNORED", GL_TIMEOUT_IGNORED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SYNC_FLUSH_COMMANDS_BIT 
    REGISTER_LONG_CONSTANT("GL_SYNC_FLUSH_COMMANDS_BIT", GL_SYNC_FLUSH_COMMANDS_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_POSITION 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_POSITION", GL_SAMPLE_POSITION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_MASK 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_MASK", GL_SAMPLE_MASK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_MASK_VALUE 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_MASK_VALUE", GL_SAMPLE_MASK_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SAMPLE_MASK_WORDS 
    REGISTER_LONG_CONSTANT("GL_MAX_SAMPLE_MASK_WORDS", GL_MAX_SAMPLE_MASK_WORDS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_2D_MULTISAMPLE", GL_TEXTURE_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_2D_MULTISAMPLE", GL_PROXY_TEXTURE_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_2D_MULTISAMPLE_ARRAY", GL_TEXTURE_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY", GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_2D_MULTISAMPLE", GL_TEXTURE_BINDING_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY", GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SAMPLES", GL_TEXTURE_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_FIXED_SAMPLE_LOCATIONS 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_FIXED_SAMPLE_LOCATIONS", GL_TEXTURE_FIXED_SAMPLE_LOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_MULTISAMPLE", GL_SAMPLER_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_2D_MULTISAMPLE", GL_INT_SAMPLER_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE", GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_2D_MULTISAMPLE_ARRAY", GL_SAMPLER_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY", GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY", GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COLOR_TEXTURE_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_MAX_COLOR_TEXTURE_SAMPLES", GL_MAX_COLOR_TEXTURE_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DEPTH_TEXTURE_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_MAX_DEPTH_TEXTURE_SAMPLES", GL_MAX_DEPTH_TEXTURE_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_INTEGER_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_MAX_INTEGER_SAMPLES", GL_MAX_INTEGER_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_DIVISOR 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_DIVISOR", GL_VERTEX_ATTRIB_ARRAY_DIVISOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRC1_COLOR 
    REGISTER_LONG_CONSTANT("GL_SRC1_COLOR", GL_SRC1_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_SRC1_COLOR 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_SRC1_COLOR", GL_ONE_MINUS_SRC1_COLOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ONE_MINUS_SRC1_ALPHA 
    REGISTER_LONG_CONSTANT("GL_ONE_MINUS_SRC1_ALPHA", GL_ONE_MINUS_SRC1_ALPHA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DUAL_SOURCE_DRAW_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_DUAL_SOURCE_DRAW_BUFFERS", GL_MAX_DUAL_SOURCE_DRAW_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ANY_SAMPLES_PASSED 
    REGISTER_LONG_CONSTANT("GL_ANY_SAMPLES_PASSED", GL_ANY_SAMPLES_PASSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_BINDING 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_BINDING", GL_SAMPLER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB10_A2UI 
    REGISTER_LONG_CONSTANT("GL_RGB10_A2UI", GL_RGB10_A2UI, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SWIZZLE_R 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SWIZZLE_R", GL_TEXTURE_SWIZZLE_R, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SWIZZLE_G 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SWIZZLE_G", GL_TEXTURE_SWIZZLE_G, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SWIZZLE_B 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SWIZZLE_B", GL_TEXTURE_SWIZZLE_B, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SWIZZLE_A 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SWIZZLE_A", GL_TEXTURE_SWIZZLE_A, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SWIZZLE_RGBA 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SWIZZLE_RGBA", GL_TEXTURE_SWIZZLE_RGBA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TIME_ELAPSED 
    REGISTER_LONG_CONSTANT("GL_TIME_ELAPSED", GL_TIME_ELAPSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TIMESTAMP 
    REGISTER_LONG_CONSTANT("GL_TIMESTAMP", GL_TIMESTAMP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_2_10_10_10_REV 
    REGISTER_LONG_CONSTANT("GL_INT_2_10_10_10_REV", GL_INT_2_10_10_10_REV, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLE_SHADING 
    REGISTER_LONG_CONSTANT("GL_SAMPLE_SHADING", GL_SAMPLE_SHADING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIN_SAMPLE_SHADING_VALUE 
    REGISTER_LONG_CONSTANT("GL_MIN_SAMPLE_SHADING_VALUE", GL_MIN_SAMPLE_SHADING_VALUE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET", GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET", GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_CUBE_MAP_ARRAY", GL_TEXTURE_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BINDING_CUBE_MAP_ARRAY", GL_TEXTURE_BINDING_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROXY_TEXTURE_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_PROXY_TEXTURE_CUBE_MAP_ARRAY", GL_PROXY_TEXTURE_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_CUBE_MAP_ARRAY", GL_SAMPLER_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW 
    REGISTER_LONG_CONSTANT("GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW", GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_SAMPLER_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_SAMPLER_CUBE_MAP_ARRAY", GL_INT_SAMPLER_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY", GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_INDIRECT_BUFFER 
    REGISTER_LONG_CONSTANT("GL_DRAW_INDIRECT_BUFFER", GL_DRAW_INDIRECT_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DRAW_INDIRECT_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_DRAW_INDIRECT_BUFFER_BINDING", GL_DRAW_INDIRECT_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_SHADER_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_SHADER_INVOCATIONS", GL_GEOMETRY_SHADER_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_SHADER_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_SHADER_INVOCATIONS", GL_MAX_GEOMETRY_SHADER_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIN_FRAGMENT_INTERPOLATION_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MIN_FRAGMENT_INTERPOLATION_OFFSET", GL_MIN_FRAGMENT_INTERPOLATION_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_INTERPOLATION_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_INTERPOLATION_OFFSET", GL_MAX_FRAGMENT_INTERPOLATION_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_INTERPOLATION_OFFSET_BITS 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_INTERPOLATION_OFFSET_BITS", GL_FRAGMENT_INTERPOLATION_OFFSET_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_STREAMS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_STREAMS", GL_MAX_VERTEX_STREAMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_VEC2 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_VEC2", GL_DOUBLE_VEC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_VEC3 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_VEC3", GL_DOUBLE_VEC3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_VEC4 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_VEC4", GL_DOUBLE_VEC4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT2 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT2", GL_DOUBLE_MAT2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT3 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT3", GL_DOUBLE_MAT3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT4 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT4", GL_DOUBLE_MAT4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT2x3 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT2x3", GL_DOUBLE_MAT2x3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT2x4 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT2x4", GL_DOUBLE_MAT2x4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT3x2 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT3x2", GL_DOUBLE_MAT3x2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT3x4 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT3x4", GL_DOUBLE_MAT3x4, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT4x2 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT4x2", GL_DOUBLE_MAT4x2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DOUBLE_MAT4x3 
    REGISTER_LONG_CONSTANT("GL_DOUBLE_MAT4x3", GL_DOUBLE_MAT4x3, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_SUBROUTINES 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_SUBROUTINES", GL_ACTIVE_SUBROUTINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_SUBROUTINE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_SUBROUTINE_UNIFORMS", GL_ACTIVE_SUBROUTINE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS", GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_SUBROUTINE_MAX_LENGTH 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_SUBROUTINE_MAX_LENGTH", GL_ACTIVE_SUBROUTINE_MAX_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH", GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SUBROUTINES 
    REGISTER_LONG_CONSTANT("GL_MAX_SUBROUTINES", GL_MAX_SUBROUTINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS 
    REGISTER_LONG_CONSTANT("GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS", GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_COMPATIBLE_SUBROUTINES 
    REGISTER_LONG_CONSTANT("GL_NUM_COMPATIBLE_SUBROUTINES", GL_NUM_COMPATIBLE_SUBROUTINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPATIBLE_SUBROUTINES 
    REGISTER_LONG_CONSTANT("GL_COMPATIBLE_SUBROUTINES", GL_COMPATIBLE_SUBROUTINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PATCHES 
    REGISTER_LONG_CONSTANT("GL_PATCHES", GL_PATCHES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PATCH_VERTICES 
    REGISTER_LONG_CONSTANT("GL_PATCH_VERTICES", GL_PATCH_VERTICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PATCH_DEFAULT_INNER_LEVEL 
    REGISTER_LONG_CONSTANT("GL_PATCH_DEFAULT_INNER_LEVEL", GL_PATCH_DEFAULT_INNER_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PATCH_DEFAULT_OUTER_LEVEL 
    REGISTER_LONG_CONSTANT("GL_PATCH_DEFAULT_OUTER_LEVEL", GL_PATCH_DEFAULT_OUTER_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_OUTPUT_VERTICES 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_OUTPUT_VERTICES", GL_TESS_CONTROL_OUTPUT_VERTICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_GEN_MODE 
    REGISTER_LONG_CONSTANT("GL_TESS_GEN_MODE", GL_TESS_GEN_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_GEN_SPACING 
    REGISTER_LONG_CONSTANT("GL_TESS_GEN_SPACING", GL_TESS_GEN_SPACING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_GEN_VERTEX_ORDER 
    REGISTER_LONG_CONSTANT("GL_TESS_GEN_VERTEX_ORDER", GL_TESS_GEN_VERTEX_ORDER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_GEN_POINT_MODE 
    REGISTER_LONG_CONSTANT("GL_TESS_GEN_POINT_MODE", GL_TESS_GEN_POINT_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ISOLINES 
    REGISTER_LONG_CONSTANT("GL_ISOLINES", GL_ISOLINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRACTIONAL_ODD 
    REGISTER_LONG_CONSTANT("GL_FRACTIONAL_ODD", GL_FRACTIONAL_ODD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRACTIONAL_EVEN 
    REGISTER_LONG_CONSTANT("GL_FRACTIONAL_EVEN", GL_FRACTIONAL_EVEN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_PATCH_VERTICES 
    REGISTER_LONG_CONSTANT("GL_MAX_PATCH_VERTICES", GL_MAX_PATCH_VERTICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_GEN_LEVEL 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_GEN_LEVEL", GL_MAX_TESS_GEN_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS", GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS", GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS", GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS", GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS", GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_PATCH_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_PATCH_COMPONENTS", GL_MAX_TESS_PATCH_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS", GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS", GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS", GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS", GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_INPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_INPUT_COMPONENTS", GL_MAX_TESS_CONTROL_INPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS", GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS", GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS", GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER", GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER", GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_EVALUATION_SHADER 
    REGISTER_LONG_CONSTANT("GL_TESS_EVALUATION_SHADER", GL_TESS_EVALUATION_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_SHADER 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_SHADER", GL_TESS_CONTROL_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK", GL_TRANSFORM_FEEDBACK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED", GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE", GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BINDING 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BINDING", GL_TRANSFORM_FEEDBACK_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TRANSFORM_FEEDBACK_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_TRANSFORM_FEEDBACK_BUFFERS", GL_MAX_TRANSFORM_FEEDBACK_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FIXED 
    REGISTER_LONG_CONSTANT("GL_FIXED", GL_FIXED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMPLEMENTATION_COLOR_READ_TYPE 
    REGISTER_LONG_CONSTANT("GL_IMPLEMENTATION_COLOR_READ_TYPE", GL_IMPLEMENTATION_COLOR_READ_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMPLEMENTATION_COLOR_READ_FORMAT 
    REGISTER_LONG_CONSTANT("GL_IMPLEMENTATION_COLOR_READ_FORMAT", GL_IMPLEMENTATION_COLOR_READ_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOW_FLOAT 
    REGISTER_LONG_CONSTANT("GL_LOW_FLOAT", GL_LOW_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MEDIUM_FLOAT 
    REGISTER_LONG_CONSTANT("GL_MEDIUM_FLOAT", GL_MEDIUM_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_HIGH_FLOAT 
    REGISTER_LONG_CONSTANT("GL_HIGH_FLOAT", GL_HIGH_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOW_INT 
    REGISTER_LONG_CONSTANT("GL_LOW_INT", GL_LOW_INT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MEDIUM_INT 
    REGISTER_LONG_CONSTANT("GL_MEDIUM_INT", GL_MEDIUM_INT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_HIGH_INT 
    REGISTER_LONG_CONSTANT("GL_HIGH_INT", GL_HIGH_INT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_COMPILER 
    REGISTER_LONG_CONSTANT("GL_SHADER_COMPILER", GL_SHADER_COMPILER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_BINARY_FORMATS 
    REGISTER_LONG_CONSTANT("GL_SHADER_BINARY_FORMATS", GL_SHADER_BINARY_FORMATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_SHADER_BINARY_FORMATS 
    REGISTER_LONG_CONSTANT("GL_NUM_SHADER_BINARY_FORMATS", GL_NUM_SHADER_BINARY_FORMATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_UNIFORM_VECTORS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_UNIFORM_VECTORS", GL_MAX_VERTEX_UNIFORM_VECTORS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VARYING_VECTORS 
    REGISTER_LONG_CONSTANT("GL_MAX_VARYING_VECTORS", GL_MAX_VARYING_VECTORS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_UNIFORM_VECTORS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_UNIFORM_VECTORS", GL_MAX_FRAGMENT_UNIFORM_VECTORS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RGB565 
    REGISTER_LONG_CONSTANT("GL_RGB565", GL_RGB565, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_BINARY_RETRIEVABLE_HINT 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_BINARY_RETRIEVABLE_HINT", GL_PROGRAM_BINARY_RETRIEVABLE_HINT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_BINARY_LENGTH 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_BINARY_LENGTH", GL_PROGRAM_BINARY_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_PROGRAM_BINARY_FORMATS 
    REGISTER_LONG_CONSTANT("GL_NUM_PROGRAM_BINARY_FORMATS", GL_NUM_PROGRAM_BINARY_FORMATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_BINARY_FORMATS 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_BINARY_FORMATS", GL_PROGRAM_BINARY_FORMATS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_SHADER_BIT 
    REGISTER_LONG_CONSTANT("GL_VERTEX_SHADER_BIT", GL_VERTEX_SHADER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_SHADER_BIT 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_SHADER_BIT", GL_FRAGMENT_SHADER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_SHADER_BIT 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_SHADER_BIT", GL_GEOMETRY_SHADER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_SHADER_BIT 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_SHADER_BIT", GL_TESS_CONTROL_SHADER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_EVALUATION_SHADER_BIT 
    REGISTER_LONG_CONSTANT("GL_TESS_EVALUATION_SHADER_BIT", GL_TESS_EVALUATION_SHADER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ALL_SHADER_BITS 
    REGISTER_LONG_CONSTANT("GL_ALL_SHADER_BITS", GL_ALL_SHADER_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_SEPARABLE 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_SEPARABLE", GL_PROGRAM_SEPARABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_PROGRAM 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_PROGRAM", GL_ACTIVE_PROGRAM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_PIPELINE_BINDING 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_PIPELINE_BINDING", GL_PROGRAM_PIPELINE_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VIEWPORTS 
    REGISTER_LONG_CONSTANT("GL_MAX_VIEWPORTS", GL_MAX_VIEWPORTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEWPORT_SUBPIXEL_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEWPORT_SUBPIXEL_BITS", GL_VIEWPORT_SUBPIXEL_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEWPORT_BOUNDS_RANGE 
    REGISTER_LONG_CONSTANT("GL_VIEWPORT_BOUNDS_RANGE", GL_VIEWPORT_BOUNDS_RANGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LAYER_PROVOKING_VERTEX 
    REGISTER_LONG_CONSTANT("GL_LAYER_PROVOKING_VERTEX", GL_LAYER_PROVOKING_VERTEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEWPORT_INDEX_PROVOKING_VERTEX 
    REGISTER_LONG_CONSTANT("GL_VIEWPORT_INDEX_PROVOKING_VERTEX", GL_VIEWPORT_INDEX_PROVOKING_VERTEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNDEFINED_VERTEX 
    REGISTER_LONG_CONSTANT("GL_UNDEFINED_VERTEX", GL_UNDEFINED_VERTEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COPY_READ_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_COPY_READ_BUFFER_BINDING", GL_COPY_READ_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COPY_WRITE_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_COPY_WRITE_BUFFER_BINDING", GL_COPY_WRITE_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_ACTIVE 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_ACTIVE", GL_TRANSFORM_FEEDBACK_ACTIVE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_PAUSED 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_PAUSED", GL_TRANSFORM_FEEDBACK_PAUSED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_COMPRESSED_BLOCK_WIDTH 
    REGISTER_LONG_CONSTANT("GL_UNPACK_COMPRESSED_BLOCK_WIDTH", GL_UNPACK_COMPRESSED_BLOCK_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_COMPRESSED_BLOCK_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_UNPACK_COMPRESSED_BLOCK_HEIGHT", GL_UNPACK_COMPRESSED_BLOCK_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_COMPRESSED_BLOCK_DEPTH 
    REGISTER_LONG_CONSTANT("GL_UNPACK_COMPRESSED_BLOCK_DEPTH", GL_UNPACK_COMPRESSED_BLOCK_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNPACK_COMPRESSED_BLOCK_SIZE 
    REGISTER_LONG_CONSTANT("GL_UNPACK_COMPRESSED_BLOCK_SIZE", GL_UNPACK_COMPRESSED_BLOCK_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_COMPRESSED_BLOCK_WIDTH 
    REGISTER_LONG_CONSTANT("GL_PACK_COMPRESSED_BLOCK_WIDTH", GL_PACK_COMPRESSED_BLOCK_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_COMPRESSED_BLOCK_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_PACK_COMPRESSED_BLOCK_HEIGHT", GL_PACK_COMPRESSED_BLOCK_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_COMPRESSED_BLOCK_DEPTH 
    REGISTER_LONG_CONSTANT("GL_PACK_COMPRESSED_BLOCK_DEPTH", GL_PACK_COMPRESSED_BLOCK_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PACK_COMPRESSED_BLOCK_SIZE 
    REGISTER_LONG_CONSTANT("GL_PACK_COMPRESSED_BLOCK_SIZE", GL_PACK_COMPRESSED_BLOCK_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_SAMPLE_COUNTS 
    REGISTER_LONG_CONSTANT("GL_NUM_SAMPLE_COUNTS", GL_NUM_SAMPLE_COUNTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIN_MAP_BUFFER_ALIGNMENT 
    REGISTER_LONG_CONSTANT("GL_MIN_MAP_BUFFER_ALIGNMENT", GL_MIN_MAP_BUFFER_ALIGNMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER", GL_ATOMIC_COUNTER_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_BINDING", GL_ATOMIC_COUNTER_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_START 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_START", GL_ATOMIC_COUNTER_BUFFER_START, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_SIZE", GL_ATOMIC_COUNTER_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE", GL_ATOMIC_COUNTER_BUFFER_DATA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS", GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES", GL_ATOMIC_COUNTER_BUFFER_ACTIVE_ATOMIC_COUNTER_INDICES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER", GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_VERTEX_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER", GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_CONTROL_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER", GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_TESS_EVALUATION_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER", GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_GEOMETRY_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER", GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_FRAGMENT_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS", GL_MAX_VERTEX_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS", GL_MAX_TESS_CONTROL_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS", GL_MAX_TESS_EVALUATION_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS", GL_MAX_GEOMETRY_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS", GL_MAX_FRAGMENT_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS", GL_MAX_COMBINED_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_ATOMIC_COUNTERS", GL_MAX_VERTEX_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS", GL_MAX_TESS_CONTROL_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS", GL_MAX_TESS_EVALUATION_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_ATOMIC_COUNTERS", GL_MAX_GEOMETRY_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_ATOMIC_COUNTERS", GL_MAX_FRAGMENT_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_ATOMIC_COUNTERS", GL_MAX_COMBINED_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE", GL_MAX_ATOMIC_COUNTER_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS 
    REGISTER_LONG_CONSTANT("GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS", GL_MAX_ATOMIC_COUNTER_BUFFER_BINDINGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_ATOMIC_COUNTER_BUFFERS", GL_ACTIVE_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX", GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_ATOMIC_COUNTER 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_ATOMIC_COUNTER", GL_UNSIGNED_INT_ATOMIC_COUNTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT", GL_VERTEX_ATTRIB_ARRAY_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ELEMENT_ARRAY_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_ELEMENT_ARRAY_BARRIER_BIT", GL_ELEMENT_ARRAY_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BARRIER_BIT", GL_UNIFORM_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_FETCH_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_FETCH_BARRIER_BIT", GL_TEXTURE_FETCH_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_IMAGE_ACCESS_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_SHADER_IMAGE_ACCESS_BARRIER_BIT", GL_SHADER_IMAGE_ACCESS_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMMAND_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_COMMAND_BARRIER_BIT", GL_COMMAND_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PIXEL_BUFFER_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_PIXEL_BUFFER_BARRIER_BIT", GL_PIXEL_BUFFER_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_UPDATE_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_UPDATE_BARRIER_BIT", GL_TEXTURE_UPDATE_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_UPDATE_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_BUFFER_UPDATE_BARRIER_BIT", GL_BUFFER_UPDATE_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_BARRIER_BIT", GL_FRAMEBUFFER_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BARRIER_BIT", GL_TRANSFORM_FEEDBACK_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BARRIER_BIT", GL_ATOMIC_COUNTER_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ALL_BARRIER_BITS 
    REGISTER_LONG_CONSTANT("GL_ALL_BARRIER_BITS", GL_ALL_BARRIER_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_IMAGE_UNITS", GL_MAX_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS", GL_MAX_COMBINED_IMAGE_UNITS_AND_FRAGMENT_OUTPUTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BINDING_NAME 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BINDING_NAME", GL_IMAGE_BINDING_NAME, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BINDING_LEVEL 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BINDING_LEVEL", GL_IMAGE_BINDING_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BINDING_LAYERED 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BINDING_LAYERED", GL_IMAGE_BINDING_LAYERED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BINDING_LAYER 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BINDING_LAYER", GL_IMAGE_BINDING_LAYER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BINDING_ACCESS 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BINDING_ACCESS", GL_IMAGE_BINDING_ACCESS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_1D 
    REGISTER_LONG_CONSTANT("GL_IMAGE_1D", GL_IMAGE_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_2D 
    REGISTER_LONG_CONSTANT("GL_IMAGE_2D", GL_IMAGE_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_3D 
    REGISTER_LONG_CONSTANT("GL_IMAGE_3D", GL_IMAGE_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_2D_RECT 
    REGISTER_LONG_CONSTANT("GL_IMAGE_2D_RECT", GL_IMAGE_2D_RECT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CUBE 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CUBE", GL_IMAGE_CUBE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BUFFER 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BUFFER", GL_IMAGE_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_IMAGE_1D_ARRAY", GL_IMAGE_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_IMAGE_2D_ARRAY", GL_IMAGE_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CUBE_MAP_ARRAY", GL_IMAGE_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_IMAGE_2D_MULTISAMPLE", GL_IMAGE_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_IMAGE_2D_MULTISAMPLE_ARRAY", GL_IMAGE_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_1D 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_1D", GL_INT_IMAGE_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_2D 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_2D", GL_INT_IMAGE_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_3D 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_3D", GL_INT_IMAGE_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_2D_RECT 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_2D_RECT", GL_INT_IMAGE_2D_RECT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_CUBE 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_CUBE", GL_INT_IMAGE_CUBE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_BUFFER 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_BUFFER", GL_INT_IMAGE_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_1D_ARRAY", GL_INT_IMAGE_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_2D_ARRAY", GL_INT_IMAGE_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_CUBE_MAP_ARRAY", GL_INT_IMAGE_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_2D_MULTISAMPLE", GL_INT_IMAGE_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY", GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_1D 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_1D", GL_UNSIGNED_INT_IMAGE_1D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_2D 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_2D", GL_UNSIGNED_INT_IMAGE_2D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_3D 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_3D", GL_UNSIGNED_INT_IMAGE_3D, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_2D_RECT 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_2D_RECT", GL_UNSIGNED_INT_IMAGE_2D_RECT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_CUBE 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_CUBE", GL_UNSIGNED_INT_IMAGE_CUBE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_BUFFER 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_BUFFER", GL_UNSIGNED_INT_IMAGE_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_1D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_1D_ARRAY", GL_UNSIGNED_INT_IMAGE_1D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_2D_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_2D_ARRAY", GL_UNSIGNED_INT_IMAGE_2D_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY", GL_UNSIGNED_INT_IMAGE_CUBE_MAP_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE", GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY 
    REGISTER_LONG_CONSTANT("GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY", GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_IMAGE_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_MAX_IMAGE_SAMPLES", GL_MAX_IMAGE_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_BINDING_FORMAT 
    REGISTER_LONG_CONSTANT("GL_IMAGE_BINDING_FORMAT", GL_IMAGE_BINDING_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_FORMAT_COMPATIBILITY_TYPE 
    REGISTER_LONG_CONSTANT("GL_IMAGE_FORMAT_COMPATIBILITY_TYPE", GL_IMAGE_FORMAT_COMPATIBILITY_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE 
    REGISTER_LONG_CONSTANT("GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE", GL_IMAGE_FORMAT_COMPATIBILITY_BY_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS 
    REGISTER_LONG_CONSTANT("GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS", GL_IMAGE_FORMAT_COMPATIBILITY_BY_CLASS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_IMAGE_UNIFORMS", GL_MAX_VERTEX_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS", GL_MAX_TESS_CONTROL_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS", GL_MAX_TESS_EVALUATION_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_IMAGE_UNIFORMS", GL_MAX_GEOMETRY_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_IMAGE_UNIFORMS", GL_MAX_FRAGMENT_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_IMAGE_UNIFORMS", GL_MAX_COMBINED_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGBA_BPTC_UNORM 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGBA_BPTC_UNORM", GL_COMPRESSED_RGBA_BPTC_UNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM", GL_COMPRESSED_SRGB_ALPHA_BPTC_UNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT", GL_COMPRESSED_RGB_BPTC_SIGNED_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT", GL_COMPRESSED_RGB_BPTC_UNSIGNED_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_IMMUTABLE_FORMAT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_IMMUTABLE_FORMAT", GL_TEXTURE_IMMUTABLE_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_SHADING_LANGUAGE_VERSIONS 
    REGISTER_LONG_CONSTANT("GL_NUM_SHADING_LANGUAGE_VERSIONS", GL_NUM_SHADING_LANGUAGE_VERSIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_ARRAY_LONG 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_ARRAY_LONG", GL_VERTEX_ATTRIB_ARRAY_LONG, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGB8_ETC2 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGB8_ETC2", GL_COMPRESSED_RGB8_ETC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SRGB8_ETC2 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SRGB8_ETC2", GL_COMPRESSED_SRGB8_ETC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2", GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2", GL_COMPRESSED_SRGB8_PUNCHTHROUGH_ALPHA1_ETC2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RGBA8_ETC2_EAC 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RGBA8_ETC2_EAC", GL_COMPRESSED_RGBA8_ETC2_EAC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC", GL_COMPRESSED_SRGB8_ALPHA8_ETC2_EAC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_R11_EAC 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_R11_EAC", GL_COMPRESSED_R11_EAC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SIGNED_R11_EAC 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SIGNED_R11_EAC", GL_COMPRESSED_SIGNED_R11_EAC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_RG11_EAC 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_RG11_EAC", GL_COMPRESSED_RG11_EAC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPRESSED_SIGNED_RG11_EAC 
    REGISTER_LONG_CONSTANT("GL_COMPRESSED_SIGNED_RG11_EAC", GL_COMPRESSED_SIGNED_RG11_EAC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PRIMITIVE_RESTART_FIXED_INDEX 
    REGISTER_LONG_CONSTANT("GL_PRIMITIVE_RESTART_FIXED_INDEX", GL_PRIMITIVE_RESTART_FIXED_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ANY_SAMPLES_PASSED_CONSERVATIVE 
    REGISTER_LONG_CONSTANT("GL_ANY_SAMPLES_PASSED_CONSERVATIVE", GL_ANY_SAMPLES_PASSED_CONSERVATIVE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_ELEMENT_INDEX 
    REGISTER_LONG_CONSTANT("GL_MAX_ELEMENT_INDEX", GL_MAX_ELEMENT_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_SHADER 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_SHADER", GL_COMPUTE_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_UNIFORM_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_UNIFORM_BLOCKS", GL_MAX_COMPUTE_UNIFORM_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS", GL_MAX_COMPUTE_TEXTURE_IMAGE_UNITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_IMAGE_UNIFORMS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_IMAGE_UNIFORMS", GL_MAX_COMPUTE_IMAGE_UNIFORMS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_SHARED_MEMORY_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_SHARED_MEMORY_SIZE", GL_MAX_COMPUTE_SHARED_MEMORY_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_UNIFORM_COMPONENTS", GL_MAX_COMPUTE_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS", GL_MAX_COMPUTE_ATOMIC_COUNTER_BUFFERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_ATOMIC_COUNTERS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_ATOMIC_COUNTERS", GL_MAX_COMPUTE_ATOMIC_COUNTERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS", GL_MAX_COMBINED_COMPUTE_UNIFORM_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS", GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_WORK_GROUP_COUNT 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_WORK_GROUP_COUNT", GL_MAX_COMPUTE_WORK_GROUP_COUNT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_WORK_GROUP_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_WORK_GROUP_SIZE", GL_MAX_COMPUTE_WORK_GROUP_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_WORK_GROUP_SIZE 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_WORK_GROUP_SIZE", GL_COMPUTE_WORK_GROUP_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER", GL_UNIFORM_BLOCK_REFERENCED_BY_COMPUTE_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER", GL_ATOMIC_COUNTER_BUFFER_REFERENCED_BY_COMPUTE_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DISPATCH_INDIRECT_BUFFER 
    REGISTER_LONG_CONSTANT("GL_DISPATCH_INDIRECT_BUFFER", GL_DISPATCH_INDIRECT_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DISPATCH_INDIRECT_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_DISPATCH_INDIRECT_BUFFER_BINDING", GL_DISPATCH_INDIRECT_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_SHADER_BIT 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_SHADER_BIT", GL_COMPUTE_SHADER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_OUTPUT_SYNCHRONOUS 
    REGISTER_LONG_CONSTANT("GL_DEBUG_OUTPUT_SYNCHRONOUS", GL_DEBUG_OUTPUT_SYNCHRONOUS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 
    REGISTER_LONG_CONSTANT("GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH", GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_CALLBACK_FUNCTION 
    REGISTER_LONG_CONSTANT("GL_DEBUG_CALLBACK_FUNCTION", GL_DEBUG_CALLBACK_FUNCTION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_CALLBACK_USER_PARAM 
    REGISTER_LONG_CONSTANT("GL_DEBUG_CALLBACK_USER_PARAM", GL_DEBUG_CALLBACK_USER_PARAM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SOURCE_API 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SOURCE_API", GL_DEBUG_SOURCE_API, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SOURCE_WINDOW_SYSTEM 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SOURCE_WINDOW_SYSTEM", GL_DEBUG_SOURCE_WINDOW_SYSTEM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SOURCE_SHADER_COMPILER 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SOURCE_SHADER_COMPILER", GL_DEBUG_SOURCE_SHADER_COMPILER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SOURCE_THIRD_PARTY 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SOURCE_THIRD_PARTY", GL_DEBUG_SOURCE_THIRD_PARTY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SOURCE_APPLICATION 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SOURCE_APPLICATION", GL_DEBUG_SOURCE_APPLICATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SOURCE_OTHER 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SOURCE_OTHER", GL_DEBUG_SOURCE_OTHER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_ERROR 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_ERROR", GL_DEBUG_TYPE_ERROR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR", GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR", GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_PORTABILITY 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_PORTABILITY", GL_DEBUG_TYPE_PORTABILITY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_PERFORMANCE 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_PERFORMANCE", GL_DEBUG_TYPE_PERFORMANCE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_OTHER 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_OTHER", GL_DEBUG_TYPE_OTHER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DEBUG_MESSAGE_LENGTH 
    REGISTER_LONG_CONSTANT("GL_MAX_DEBUG_MESSAGE_LENGTH", GL_MAX_DEBUG_MESSAGE_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DEBUG_LOGGED_MESSAGES 
    REGISTER_LONG_CONSTANT("GL_MAX_DEBUG_LOGGED_MESSAGES", GL_MAX_DEBUG_LOGGED_MESSAGES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_LOGGED_MESSAGES 
    REGISTER_LONG_CONSTANT("GL_DEBUG_LOGGED_MESSAGES", GL_DEBUG_LOGGED_MESSAGES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SEVERITY_HIGH 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SEVERITY_HIGH", GL_DEBUG_SEVERITY_HIGH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SEVERITY_MEDIUM 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SEVERITY_MEDIUM", GL_DEBUG_SEVERITY_MEDIUM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SEVERITY_LOW 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SEVERITY_LOW", GL_DEBUG_SEVERITY_LOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_MARKER 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_MARKER", GL_DEBUG_TYPE_MARKER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_PUSH_GROUP 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_PUSH_GROUP", GL_DEBUG_TYPE_PUSH_GROUP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_TYPE_POP_GROUP 
    REGISTER_LONG_CONSTANT("GL_DEBUG_TYPE_POP_GROUP", GL_DEBUG_TYPE_POP_GROUP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_SEVERITY_NOTIFICATION 
    REGISTER_LONG_CONSTANT("GL_DEBUG_SEVERITY_NOTIFICATION", GL_DEBUG_SEVERITY_NOTIFICATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DEBUG_GROUP_STACK_DEPTH 
    REGISTER_LONG_CONSTANT("GL_MAX_DEBUG_GROUP_STACK_DEPTH", GL_MAX_DEBUG_GROUP_STACK_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_GROUP_STACK_DEPTH 
    REGISTER_LONG_CONSTANT("GL_DEBUG_GROUP_STACK_DEPTH", GL_DEBUG_GROUP_STACK_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER 
    REGISTER_LONG_CONSTANT("GL_BUFFER", GL_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER 
    REGISTER_LONG_CONSTANT("GL_SHADER", GL_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM 
    REGISTER_LONG_CONSTANT("GL_PROGRAM", GL_PROGRAM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY 
    REGISTER_LONG_CONSTANT("GL_QUERY", GL_QUERY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_PIPELINE 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_PIPELINE", GL_PROGRAM_PIPELINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SAMPLER 
    REGISTER_LONG_CONSTANT("GL_SAMPLER", GL_SAMPLER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_LABEL_LENGTH 
    REGISTER_LONG_CONSTANT("GL_MAX_LABEL_LENGTH", GL_MAX_LABEL_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEBUG_OUTPUT 
    REGISTER_LONG_CONSTANT("GL_DEBUG_OUTPUT", GL_DEBUG_OUTPUT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_FLAG_DEBUG_BIT 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_FLAG_DEBUG_BIT", GL_CONTEXT_FLAG_DEBUG_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_UNIFORM_LOCATIONS 
    REGISTER_LONG_CONSTANT("GL_MAX_UNIFORM_LOCATIONS", GL_MAX_UNIFORM_LOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_DEFAULT_WIDTH 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_DEFAULT_WIDTH", GL_FRAMEBUFFER_DEFAULT_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_DEFAULT_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_DEFAULT_HEIGHT", GL_FRAMEBUFFER_DEFAULT_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_DEFAULT_LAYERS 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_DEFAULT_LAYERS", GL_FRAMEBUFFER_DEFAULT_LAYERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_DEFAULT_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_DEFAULT_SAMPLES", GL_FRAMEBUFFER_DEFAULT_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS", GL_FRAMEBUFFER_DEFAULT_FIXED_SAMPLE_LOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAMEBUFFER_WIDTH 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAMEBUFFER_WIDTH", GL_MAX_FRAMEBUFFER_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAMEBUFFER_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAMEBUFFER_HEIGHT", GL_MAX_FRAMEBUFFER_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAMEBUFFER_LAYERS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAMEBUFFER_LAYERS", GL_MAX_FRAMEBUFFER_LAYERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAMEBUFFER_SAMPLES 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAMEBUFFER_SAMPLES", GL_MAX_FRAMEBUFFER_SAMPLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_SUPPORTED 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_SUPPORTED", GL_INTERNALFORMAT_SUPPORTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_PREFERRED 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_PREFERRED", GL_INTERNALFORMAT_PREFERRED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_RED_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_RED_SIZE", GL_INTERNALFORMAT_RED_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_GREEN_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_GREEN_SIZE", GL_INTERNALFORMAT_GREEN_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_BLUE_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_BLUE_SIZE", GL_INTERNALFORMAT_BLUE_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_ALPHA_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_ALPHA_SIZE", GL_INTERNALFORMAT_ALPHA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_DEPTH_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_DEPTH_SIZE", GL_INTERNALFORMAT_DEPTH_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_STENCIL_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_STENCIL_SIZE", GL_INTERNALFORMAT_STENCIL_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_SHARED_SIZE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_SHARED_SIZE", GL_INTERNALFORMAT_SHARED_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_RED_TYPE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_RED_TYPE", GL_INTERNALFORMAT_RED_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_GREEN_TYPE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_GREEN_TYPE", GL_INTERNALFORMAT_GREEN_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_BLUE_TYPE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_BLUE_TYPE", GL_INTERNALFORMAT_BLUE_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_ALPHA_TYPE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_ALPHA_TYPE", GL_INTERNALFORMAT_ALPHA_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_DEPTH_TYPE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_DEPTH_TYPE", GL_INTERNALFORMAT_DEPTH_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INTERNALFORMAT_STENCIL_TYPE 
    REGISTER_LONG_CONSTANT("GL_INTERNALFORMAT_STENCIL_TYPE", GL_INTERNALFORMAT_STENCIL_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_WIDTH 
    REGISTER_LONG_CONSTANT("GL_MAX_WIDTH", GL_MAX_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_MAX_HEIGHT", GL_MAX_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_DEPTH 
    REGISTER_LONG_CONSTANT("GL_MAX_DEPTH", GL_MAX_DEPTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_LAYERS 
    REGISTER_LONG_CONSTANT("GL_MAX_LAYERS", GL_MAX_LAYERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_DIMENSIONS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_DIMENSIONS", GL_MAX_COMBINED_DIMENSIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_COLOR_COMPONENTS", GL_COLOR_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_DEPTH_COMPONENTS", GL_DEPTH_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_COMPONENTS 
    REGISTER_LONG_CONSTANT("GL_STENCIL_COMPONENTS", GL_STENCIL_COMPONENTS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_RENDERABLE 
    REGISTER_LONG_CONSTANT("GL_COLOR_RENDERABLE", GL_COLOR_RENDERABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_RENDERABLE 
    REGISTER_LONG_CONSTANT("GL_DEPTH_RENDERABLE", GL_DEPTH_RENDERABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_STENCIL_RENDERABLE 
    REGISTER_LONG_CONSTANT("GL_STENCIL_RENDERABLE", GL_STENCIL_RENDERABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_RENDERABLE 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_RENDERABLE", GL_FRAMEBUFFER_RENDERABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_RENDERABLE_LAYERED 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_RENDERABLE_LAYERED", GL_FRAMEBUFFER_RENDERABLE_LAYERED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAMEBUFFER_BLEND 
    REGISTER_LONG_CONSTANT("GL_FRAMEBUFFER_BLEND", GL_FRAMEBUFFER_BLEND, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_PIXELS 
    REGISTER_LONG_CONSTANT("GL_READ_PIXELS", GL_READ_PIXELS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_PIXELS_FORMAT 
    REGISTER_LONG_CONSTANT("GL_READ_PIXELS_FORMAT", GL_READ_PIXELS_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_READ_PIXELS_TYPE 
    REGISTER_LONG_CONSTANT("GL_READ_PIXELS_TYPE", GL_READ_PIXELS_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_IMAGE_FORMAT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_IMAGE_FORMAT", GL_TEXTURE_IMAGE_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_IMAGE_TYPE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_IMAGE_TYPE", GL_TEXTURE_IMAGE_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GET_TEXTURE_IMAGE_FORMAT 
    REGISTER_LONG_CONSTANT("GL_GET_TEXTURE_IMAGE_FORMAT", GL_GET_TEXTURE_IMAGE_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GET_TEXTURE_IMAGE_TYPE 
    REGISTER_LONG_CONSTANT("GL_GET_TEXTURE_IMAGE_TYPE", GL_GET_TEXTURE_IMAGE_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIPMAP 
    REGISTER_LONG_CONSTANT("GL_MIPMAP", GL_MIPMAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MANUAL_GENERATE_MIPMAP 
    REGISTER_LONG_CONSTANT("GL_MANUAL_GENERATE_MIPMAP", GL_MANUAL_GENERATE_MIPMAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_AUTO_GENERATE_MIPMAP 
    REGISTER_LONG_CONSTANT("GL_AUTO_GENERATE_MIPMAP", GL_AUTO_GENERATE_MIPMAP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COLOR_ENCODING 
    REGISTER_LONG_CONSTANT("GL_COLOR_ENCODING", GL_COLOR_ENCODING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRGB_READ 
    REGISTER_LONG_CONSTANT("GL_SRGB_READ", GL_SRGB_READ, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SRGB_WRITE 
    REGISTER_LONG_CONSTANT("GL_SRGB_WRITE", GL_SRGB_WRITE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FILTER 
    REGISTER_LONG_CONSTANT("GL_FILTER", GL_FILTER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_TEXTURE", GL_VERTEX_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_TEXTURE", GL_TESS_CONTROL_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_EVALUATION_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_TESS_EVALUATION_TEXTURE", GL_TESS_EVALUATION_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_TEXTURE", GL_GEOMETRY_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_TEXTURE", GL_FRAGMENT_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_TEXTURE", GL_COMPUTE_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_SHADOW 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_SHADOW", GL_TEXTURE_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_GATHER 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_GATHER", GL_TEXTURE_GATHER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_GATHER_SHADOW 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_GATHER_SHADOW", GL_TEXTURE_GATHER_SHADOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_IMAGE_LOAD 
    REGISTER_LONG_CONSTANT("GL_SHADER_IMAGE_LOAD", GL_SHADER_IMAGE_LOAD, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_IMAGE_STORE 
    REGISTER_LONG_CONSTANT("GL_SHADER_IMAGE_STORE", GL_SHADER_IMAGE_STORE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_IMAGE_ATOMIC 
    REGISTER_LONG_CONSTANT("GL_SHADER_IMAGE_ATOMIC", GL_SHADER_IMAGE_ATOMIC, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_TEXEL_SIZE 
    REGISTER_LONG_CONSTANT("GL_IMAGE_TEXEL_SIZE", GL_IMAGE_TEXEL_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_COMPATIBILITY_CLASS 
    REGISTER_LONG_CONSTANT("GL_IMAGE_COMPATIBILITY_CLASS", GL_IMAGE_COMPATIBILITY_CLASS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_PIXEL_FORMAT 
    REGISTER_LONG_CONSTANT("GL_IMAGE_PIXEL_FORMAT", GL_IMAGE_PIXEL_FORMAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_PIXEL_TYPE 
    REGISTER_LONG_CONSTANT("GL_IMAGE_PIXEL_TYPE", GL_IMAGE_PIXEL_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST 
    REGISTER_LONG_CONSTANT("GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST", GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_TEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST 
    REGISTER_LONG_CONSTANT("GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST", GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_TEST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE 
    REGISTER_LONG_CONSTANT("GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE", GL_SIMULTANEOUS_TEXTURE_AND_DEPTH_WRITE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE 
    REGISTER_LONG_CONSTANT("GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE", GL_SIMULTANEOUS_TEXTURE_AND_STENCIL_WRITE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPRESSED_BLOCK_WIDTH 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPRESSED_BLOCK_WIDTH", GL_TEXTURE_COMPRESSED_BLOCK_WIDTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT", GL_TEXTURE_COMPRESSED_BLOCK_HEIGHT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_COMPRESSED_BLOCK_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_COMPRESSED_BLOCK_SIZE", GL_TEXTURE_COMPRESSED_BLOCK_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLEAR_BUFFER 
    REGISTER_LONG_CONSTANT("GL_CLEAR_BUFFER", GL_CLEAR_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_VIEW 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_VIEW", GL_TEXTURE_VIEW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_COMPATIBILITY_CLASS 
    REGISTER_LONG_CONSTANT("GL_VIEW_COMPATIBILITY_CLASS", GL_VIEW_COMPATIBILITY_CLASS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FULL_SUPPORT 
    REGISTER_LONG_CONSTANT("GL_FULL_SUPPORT", GL_FULL_SUPPORT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CAVEAT_SUPPORT 
    REGISTER_LONG_CONSTANT("GL_CAVEAT_SUPPORT", GL_CAVEAT_SUPPORT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_4_X_32 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_4_X_32", GL_IMAGE_CLASS_4_X_32, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_2_X_32 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_2_X_32", GL_IMAGE_CLASS_2_X_32, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_1_X_32 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_1_X_32", GL_IMAGE_CLASS_1_X_32, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_4_X_16 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_4_X_16", GL_IMAGE_CLASS_4_X_16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_2_X_16 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_2_X_16", GL_IMAGE_CLASS_2_X_16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_1_X_16 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_1_X_16", GL_IMAGE_CLASS_1_X_16, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_4_X_8 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_4_X_8", GL_IMAGE_CLASS_4_X_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_2_X_8 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_2_X_8", GL_IMAGE_CLASS_2_X_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_1_X_8 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_1_X_8", GL_IMAGE_CLASS_1_X_8, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_11_11_10 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_11_11_10", GL_IMAGE_CLASS_11_11_10, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IMAGE_CLASS_10_10_10_2 
    REGISTER_LONG_CONSTANT("GL_IMAGE_CLASS_10_10_10_2", GL_IMAGE_CLASS_10_10_10_2, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_128_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_128_BITS", GL_VIEW_CLASS_128_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_96_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_96_BITS", GL_VIEW_CLASS_96_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_64_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_64_BITS", GL_VIEW_CLASS_64_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_48_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_48_BITS", GL_VIEW_CLASS_48_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_32_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_32_BITS", GL_VIEW_CLASS_32_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_24_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_24_BITS", GL_VIEW_CLASS_24_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_16_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_16_BITS", GL_VIEW_CLASS_16_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_8_BITS 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_8_BITS", GL_VIEW_CLASS_8_BITS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_S3TC_DXT1_RGB 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_S3TC_DXT1_RGB", GL_VIEW_CLASS_S3TC_DXT1_RGB, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_S3TC_DXT1_RGBA 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_S3TC_DXT1_RGBA", GL_VIEW_CLASS_S3TC_DXT1_RGBA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_S3TC_DXT3_RGBA 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_S3TC_DXT3_RGBA", GL_VIEW_CLASS_S3TC_DXT3_RGBA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_S3TC_DXT5_RGBA 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_S3TC_DXT5_RGBA", GL_VIEW_CLASS_S3TC_DXT5_RGBA, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_RGTC1_RED 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_RGTC1_RED", GL_VIEW_CLASS_RGTC1_RED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_RGTC2_RG 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_RGTC2_RG", GL_VIEW_CLASS_RGTC2_RG, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_BPTC_UNORM 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_BPTC_UNORM", GL_VIEW_CLASS_BPTC_UNORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VIEW_CLASS_BPTC_FLOAT 
    REGISTER_LONG_CONSTANT("GL_VIEW_CLASS_BPTC_FLOAT", GL_VIEW_CLASS_BPTC_FLOAT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_UNIFORM", GL_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNIFORM_BLOCK 
    REGISTER_LONG_CONSTANT("GL_UNIFORM_BLOCK", GL_UNIFORM_BLOCK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_INPUT 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_INPUT", GL_PROGRAM_INPUT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PROGRAM_OUTPUT 
    REGISTER_LONG_CONSTANT("GL_PROGRAM_OUTPUT", GL_PROGRAM_OUTPUT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_VARIABLE 
    REGISTER_LONG_CONSTANT("GL_BUFFER_VARIABLE", GL_BUFFER_VARIABLE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BLOCK 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BLOCK", GL_SHADER_STORAGE_BLOCK, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_SUBROUTINE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_SUBROUTINE", GL_VERTEX_SUBROUTINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_SUBROUTINE 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_SUBROUTINE", GL_TESS_CONTROL_SUBROUTINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_EVALUATION_SUBROUTINE 
    REGISTER_LONG_CONSTANT("GL_TESS_EVALUATION_SUBROUTINE", GL_TESS_EVALUATION_SUBROUTINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_SUBROUTINE 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_SUBROUTINE", GL_GEOMETRY_SUBROUTINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_SUBROUTINE 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_SUBROUTINE", GL_FRAGMENT_SUBROUTINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_SUBROUTINE 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_SUBROUTINE", GL_COMPUTE_SUBROUTINE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_SUBROUTINE_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_VERTEX_SUBROUTINE_UNIFORM", GL_VERTEX_SUBROUTINE_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_SUBROUTINE_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_SUBROUTINE_UNIFORM", GL_TESS_CONTROL_SUBROUTINE_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_EVALUATION_SUBROUTINE_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_TESS_EVALUATION_SUBROUTINE_UNIFORM", GL_TESS_EVALUATION_SUBROUTINE_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_SUBROUTINE_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_SUBROUTINE_UNIFORM", GL_GEOMETRY_SUBROUTINE_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_SUBROUTINE_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_SUBROUTINE_UNIFORM", GL_FRAGMENT_SUBROUTINE_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_SUBROUTINE_UNIFORM 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_SUBROUTINE_UNIFORM", GL_COMPUTE_SUBROUTINE_UNIFORM, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_VARYING 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_VARYING", GL_TRANSFORM_FEEDBACK_VARYING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_RESOURCES 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_RESOURCES", GL_ACTIVE_RESOURCES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_NAME_LENGTH 
    REGISTER_LONG_CONSTANT("GL_MAX_NAME_LENGTH", GL_MAX_NAME_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_NUM_ACTIVE_VARIABLES 
    REGISTER_LONG_CONSTANT("GL_MAX_NUM_ACTIVE_VARIABLES", GL_MAX_NUM_ACTIVE_VARIABLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_NUM_COMPATIBLE_SUBROUTINES 
    REGISTER_LONG_CONSTANT("GL_MAX_NUM_COMPATIBLE_SUBROUTINES", GL_MAX_NUM_COMPATIBLE_SUBROUTINES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NAME_LENGTH 
    REGISTER_LONG_CONSTANT("GL_NAME_LENGTH", GL_NAME_LENGTH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TYPE 
    REGISTER_LONG_CONSTANT("GL_TYPE", GL_TYPE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ARRAY_SIZE 
    REGISTER_LONG_CONSTANT("GL_ARRAY_SIZE", GL_ARRAY_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_OFFSET 
    REGISTER_LONG_CONSTANT("GL_OFFSET", GL_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BLOCK_INDEX 
    REGISTER_LONG_CONSTANT("GL_BLOCK_INDEX", GL_BLOCK_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ARRAY_STRIDE 
    REGISTER_LONG_CONSTANT("GL_ARRAY_STRIDE", GL_ARRAY_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MATRIX_STRIDE 
    REGISTER_LONG_CONSTANT("GL_MATRIX_STRIDE", GL_MATRIX_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IS_ROW_MAJOR 
    REGISTER_LONG_CONSTANT("GL_IS_ROW_MAJOR", GL_IS_ROW_MAJOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ATOMIC_COUNTER_BUFFER_INDEX 
    REGISTER_LONG_CONSTANT("GL_ATOMIC_COUNTER_BUFFER_INDEX", GL_ATOMIC_COUNTER_BUFFER_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_BUFFER_BINDING", GL_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_DATA_SIZE 
    REGISTER_LONG_CONSTANT("GL_BUFFER_DATA_SIZE", GL_BUFFER_DATA_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_ACTIVE_VARIABLES 
    REGISTER_LONG_CONSTANT("GL_NUM_ACTIVE_VARIABLES", GL_NUM_ACTIVE_VARIABLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ACTIVE_VARIABLES 
    REGISTER_LONG_CONSTANT("GL_ACTIVE_VARIABLES", GL_ACTIVE_VARIABLES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REFERENCED_BY_VERTEX_SHADER 
    REGISTER_LONG_CONSTANT("GL_REFERENCED_BY_VERTEX_SHADER", GL_REFERENCED_BY_VERTEX_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REFERENCED_BY_TESS_CONTROL_SHADER 
    REGISTER_LONG_CONSTANT("GL_REFERENCED_BY_TESS_CONTROL_SHADER", GL_REFERENCED_BY_TESS_CONTROL_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REFERENCED_BY_TESS_EVALUATION_SHADER 
    REGISTER_LONG_CONSTANT("GL_REFERENCED_BY_TESS_EVALUATION_SHADER", GL_REFERENCED_BY_TESS_EVALUATION_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REFERENCED_BY_GEOMETRY_SHADER 
    REGISTER_LONG_CONSTANT("GL_REFERENCED_BY_GEOMETRY_SHADER", GL_REFERENCED_BY_GEOMETRY_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REFERENCED_BY_FRAGMENT_SHADER 
    REGISTER_LONG_CONSTANT("GL_REFERENCED_BY_FRAGMENT_SHADER", GL_REFERENCED_BY_FRAGMENT_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_REFERENCED_BY_COMPUTE_SHADER 
    REGISTER_LONG_CONSTANT("GL_REFERENCED_BY_COMPUTE_SHADER", GL_REFERENCED_BY_COMPUTE_SHADER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TOP_LEVEL_ARRAY_SIZE 
    REGISTER_LONG_CONSTANT("GL_TOP_LEVEL_ARRAY_SIZE", GL_TOP_LEVEL_ARRAY_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TOP_LEVEL_ARRAY_STRIDE 
    REGISTER_LONG_CONSTANT("GL_TOP_LEVEL_ARRAY_STRIDE", GL_TOP_LEVEL_ARRAY_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOCATION 
    REGISTER_LONG_CONSTANT("GL_LOCATION", GL_LOCATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOCATION_INDEX 
    REGISTER_LONG_CONSTANT("GL_LOCATION_INDEX", GL_LOCATION_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_IS_PER_PATCH 
    REGISTER_LONG_CONSTANT("GL_IS_PER_PATCH", GL_IS_PER_PATCH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BUFFER 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BUFFER", GL_SHADER_STORAGE_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BUFFER_BINDING", GL_SHADER_STORAGE_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BUFFER_START 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BUFFER_START", GL_SHADER_STORAGE_BUFFER_START, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BUFFER_SIZE", GL_SHADER_STORAGE_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS", GL_MAX_VERTEX_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS", GL_MAX_GEOMETRY_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS", GL_MAX_TESS_CONTROL_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS", GL_MAX_TESS_EVALUATION_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS", GL_MAX_FRAGMENT_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS", GL_MAX_COMPUTE_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS", GL_MAX_COMBINED_SHADER_STORAGE_BLOCKS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS 
    REGISTER_LONG_CONSTANT("GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS", GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_SHADER_STORAGE_BLOCK_SIZE 
    REGISTER_LONG_CONSTANT("GL_MAX_SHADER_STORAGE_BLOCK_SIZE", GL_MAX_SHADER_STORAGE_BLOCK_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT", GL_SHADER_STORAGE_BUFFER_OFFSET_ALIGNMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_STORAGE_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_SHADER_STORAGE_BARRIER_BIT", GL_SHADER_STORAGE_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES", GL_MAX_COMBINED_SHADER_OUTPUT_RESOURCES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DEPTH_STENCIL_TEXTURE_MODE 
    REGISTER_LONG_CONSTANT("GL_DEPTH_STENCIL_TEXTURE_MODE", GL_DEPTH_STENCIL_TEXTURE_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BUFFER_OFFSET 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BUFFER_OFFSET", GL_TEXTURE_BUFFER_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BUFFER_SIZE 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BUFFER_SIZE", GL_TEXTURE_BUFFER_SIZE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT", GL_TEXTURE_BUFFER_OFFSET_ALIGNMENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_VIEW_MIN_LEVEL 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_VIEW_MIN_LEVEL", GL_TEXTURE_VIEW_MIN_LEVEL, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_VIEW_NUM_LEVELS 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_VIEW_NUM_LEVELS", GL_TEXTURE_VIEW_NUM_LEVELS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_VIEW_MIN_LAYER 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_VIEW_MIN_LAYER", GL_TEXTURE_VIEW_MIN_LAYER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_VIEW_NUM_LAYERS 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_VIEW_NUM_LAYERS", GL_TEXTURE_VIEW_NUM_LAYERS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_IMMUTABLE_LEVELS 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_IMMUTABLE_LEVELS", GL_TEXTURE_IMMUTABLE_LEVELS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_BINDING 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_BINDING", GL_VERTEX_ATTRIB_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_ATTRIB_RELATIVE_OFFSET 
    REGISTER_LONG_CONSTANT("GL_VERTEX_ATTRIB_RELATIVE_OFFSET", GL_VERTEX_ATTRIB_RELATIVE_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_BINDING_DIVISOR 
    REGISTER_LONG_CONSTANT("GL_VERTEX_BINDING_DIVISOR", GL_VERTEX_BINDING_DIVISOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_BINDING_OFFSET 
    REGISTER_LONG_CONSTANT("GL_VERTEX_BINDING_OFFSET", GL_VERTEX_BINDING_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_BINDING_STRIDE 
    REGISTER_LONG_CONSTANT("GL_VERTEX_BINDING_STRIDE", GL_VERTEX_BINDING_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET", GL_MAX_VERTEX_ATTRIB_RELATIVE_OFFSET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_ATTRIB_BINDINGS 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_ATTRIB_BINDINGS", GL_MAX_VERTEX_ATTRIB_BINDINGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_BINDING_BUFFER 
    REGISTER_LONG_CONSTANT("GL_VERTEX_BINDING_BUFFER", GL_VERTEX_BINDING_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DISPLAY_LIST 
    REGISTER_LONG_CONSTANT("GL_DISPLAY_LIST", GL_DISPLAY_LIST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_VERTEX_ATTRIB_STRIDE 
    REGISTER_LONG_CONSTANT("GL_MAX_VERTEX_ATTRIB_STRIDE", GL_MAX_VERTEX_ATTRIB_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED 
    REGISTER_LONG_CONSTANT("GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED", GL_PRIMITIVE_RESTART_FOR_PATCHES_SUPPORTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_BUFFER_BINDING", GL_TEXTURE_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_PERSISTENT_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_PERSISTENT_BIT", GL_MAP_PERSISTENT_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAP_COHERENT_BIT 
    REGISTER_LONG_CONSTANT("GL_MAP_COHERENT_BIT", GL_MAP_COHERENT_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_DYNAMIC_STORAGE_BIT 
    REGISTER_LONG_CONSTANT("GL_DYNAMIC_STORAGE_BIT", GL_DYNAMIC_STORAGE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIENT_STORAGE_BIT 
    REGISTER_LONG_CONSTANT("GL_CLIENT_STORAGE_BIT", GL_CLIENT_STORAGE_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT", GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_IMMUTABLE_STORAGE 
    REGISTER_LONG_CONSTANT("GL_BUFFER_IMMUTABLE_STORAGE", GL_BUFFER_IMMUTABLE_STORAGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_BUFFER_STORAGE_FLAGS 
    REGISTER_LONG_CONSTANT("GL_BUFFER_STORAGE_FLAGS", GL_BUFFER_STORAGE_FLAGS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLEAR_TEXTURE 
    REGISTER_LONG_CONSTANT("GL_CLEAR_TEXTURE", GL_CLEAR_TEXTURE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOCATION_COMPONENT 
    REGISTER_LONG_CONSTANT("GL_LOCATION_COMPONENT", GL_LOCATION_COMPONENT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_INDEX 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_INDEX", GL_TRANSFORM_FEEDBACK_BUFFER_INDEX, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE", GL_TRANSFORM_FEEDBACK_BUFFER_STRIDE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BUFFER 
    REGISTER_LONG_CONSTANT("GL_QUERY_BUFFER", GL_QUERY_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BUFFER_BARRIER_BIT 
    REGISTER_LONG_CONSTANT("GL_QUERY_BUFFER_BARRIER_BIT", GL_QUERY_BUFFER_BARRIER_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_QUERY_BUFFER_BINDING", GL_QUERY_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_RESULT_NO_WAIT 
    REGISTER_LONG_CONSTANT("GL_QUERY_RESULT_NO_WAIT", GL_QUERY_RESULT_NO_WAIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MIRROR_CLAMP_TO_EDGE 
    REGISTER_LONG_CONSTANT("GL_MIRROR_CLAMP_TO_EDGE", GL_MIRROR_CLAMP_TO_EDGE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_LOST 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_LOST", GL_CONTEXT_LOST, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NEGATIVE_ONE_TO_ONE 
    REGISTER_LONG_CONSTANT("GL_NEGATIVE_ONE_TO_ONE", GL_NEGATIVE_ONE_TO_ONE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_ZERO_TO_ONE 
    REGISTER_LONG_CONSTANT("GL_ZERO_TO_ONE", GL_ZERO_TO_ONE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_ORIGIN 
    REGISTER_LONG_CONSTANT("GL_CLIP_ORIGIN", GL_CLIP_ORIGIN, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIP_DEPTH_MODE 
    REGISTER_LONG_CONSTANT("GL_CLIP_DEPTH_MODE", GL_CLIP_DEPTH_MODE, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_WAIT_INVERTED 
    REGISTER_LONG_CONSTANT("GL_QUERY_WAIT_INVERTED", GL_QUERY_WAIT_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_NO_WAIT_INVERTED 
    REGISTER_LONG_CONSTANT("GL_QUERY_NO_WAIT_INVERTED", GL_QUERY_NO_WAIT_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BY_REGION_WAIT_INVERTED 
    REGISTER_LONG_CONSTANT("GL_QUERY_BY_REGION_WAIT_INVERTED", GL_QUERY_BY_REGION_WAIT_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_BY_REGION_NO_WAIT_INVERTED 
    REGISTER_LONG_CONSTANT("GL_QUERY_BY_REGION_NO_WAIT_INVERTED", GL_QUERY_BY_REGION_NO_WAIT_INVERTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_CULL_DISTANCES 
    REGISTER_LONG_CONSTANT("GL_MAX_CULL_DISTANCES", GL_MAX_CULL_DISTANCES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES 
    REGISTER_LONG_CONSTANT("GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES", GL_MAX_COMBINED_CLIP_AND_CULL_DISTANCES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_TARGET 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_TARGET", GL_TEXTURE_TARGET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_QUERY_TARGET 
    REGISTER_LONG_CONSTANT("GL_QUERY_TARGET", GL_QUERY_TARGET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GUILTY_CONTEXT_RESET 
    REGISTER_LONG_CONSTANT("GL_GUILTY_CONTEXT_RESET", GL_GUILTY_CONTEXT_RESET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_INNOCENT_CONTEXT_RESET 
    REGISTER_LONG_CONSTANT("GL_INNOCENT_CONTEXT_RESET", GL_INNOCENT_CONTEXT_RESET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_UNKNOWN_CONTEXT_RESET 
    REGISTER_LONG_CONSTANT("GL_UNKNOWN_CONTEXT_RESET", GL_UNKNOWN_CONTEXT_RESET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_RESET_NOTIFICATION_STRATEGY 
    REGISTER_LONG_CONSTANT("GL_RESET_NOTIFICATION_STRATEGY", GL_RESET_NOTIFICATION_STRATEGY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_LOSE_CONTEXT_ON_RESET 
    REGISTER_LONG_CONSTANT("GL_LOSE_CONTEXT_ON_RESET", GL_LOSE_CONTEXT_ON_RESET, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NO_RESET_NOTIFICATION 
    REGISTER_LONG_CONSTANT("GL_NO_RESET_NOTIFICATION", GL_NO_RESET_NOTIFICATION, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT", GL_CONTEXT_FLAG_ROBUST_ACCESS_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_RELEASE_BEHAVIOR 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_RELEASE_BEHAVIOR", GL_CONTEXT_RELEASE_BEHAVIOR, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH", GL_CONTEXT_RELEASE_BEHAVIOR_FLUSH, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SHADER_BINARY_FORMAT_SPIR_V 
    REGISTER_LONG_CONSTANT("GL_SHADER_BINARY_FORMAT_SPIR_V", GL_SHADER_BINARY_FORMAT_SPIR_V, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SPIR_V_BINARY 
    REGISTER_LONG_CONSTANT("GL_SPIR_V_BINARY", GL_SPIR_V_BINARY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PARAMETER_BUFFER 
    REGISTER_LONG_CONSTANT("GL_PARAMETER_BUFFER", GL_PARAMETER_BUFFER, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PARAMETER_BUFFER_BINDING 
    REGISTER_LONG_CONSTANT("GL_PARAMETER_BUFFER_BINDING", GL_PARAMETER_BUFFER_BINDING, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CONTEXT_FLAG_NO_ERROR_BIT 
    REGISTER_LONG_CONSTANT("GL_CONTEXT_FLAG_NO_ERROR_BIT", GL_CONTEXT_FLAG_NO_ERROR_BIT, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTICES_SUBMITTED 
    REGISTER_LONG_CONSTANT("GL_VERTICES_SUBMITTED", GL_VERTICES_SUBMITTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_PRIMITIVES_SUBMITTED 
    REGISTER_LONG_CONSTANT("GL_PRIMITIVES_SUBMITTED", GL_PRIMITIVES_SUBMITTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_VERTEX_SHADER_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_VERTEX_SHADER_INVOCATIONS", GL_VERTEX_SHADER_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_CONTROL_SHADER_PATCHES 
    REGISTER_LONG_CONSTANT("GL_TESS_CONTROL_SHADER_PATCHES", GL_TESS_CONTROL_SHADER_PATCHES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TESS_EVALUATION_SHADER_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_TESS_EVALUATION_SHADER_INVOCATIONS", GL_TESS_EVALUATION_SHADER_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED 
    REGISTER_LONG_CONSTANT("GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED", GL_GEOMETRY_SHADER_PRIMITIVES_EMITTED, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_FRAGMENT_SHADER_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_FRAGMENT_SHADER_INVOCATIONS", GL_FRAGMENT_SHADER_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_COMPUTE_SHADER_INVOCATIONS 
    REGISTER_LONG_CONSTANT("GL_COMPUTE_SHADER_INVOCATIONS", GL_COMPUTE_SHADER_INVOCATIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIPPING_INPUT_PRIMITIVES 
    REGISTER_LONG_CONSTANT("GL_CLIPPING_INPUT_PRIMITIVES", GL_CLIPPING_INPUT_PRIMITIVES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_CLIPPING_OUTPUT_PRIMITIVES 
    REGISTER_LONG_CONSTANT("GL_CLIPPING_OUTPUT_PRIMITIVES", GL_CLIPPING_OUTPUT_PRIMITIVES, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_POLYGON_OFFSET_CLAMP 
    REGISTER_LONG_CONSTANT("GL_POLYGON_OFFSET_CLAMP", GL_POLYGON_OFFSET_CLAMP, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_SPIR_V_EXTENSIONS 
    REGISTER_LONG_CONSTANT("GL_SPIR_V_EXTENSIONS", GL_SPIR_V_EXTENSIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_NUM_SPIR_V_EXTENSIONS 
    REGISTER_LONG_CONSTANT("GL_NUM_SPIR_V_EXTENSIONS", GL_NUM_SPIR_V_EXTENSIONS, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TEXTURE_MAX_ANISOTROPY 
    REGISTER_LONG_CONSTANT("GL_TEXTURE_MAX_ANISOTROPY", GL_TEXTURE_MAX_ANISOTROPY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_MAX_TEXTURE_MAX_ANISOTROPY 
    REGISTER_LONG_CONSTANT("GL_MAX_TEXTURE_MAX_ANISOTROPY", GL_MAX_TEXTURE_MAX_ANISOTROPY, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_OVERFLOW 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_OVERFLOW", GL_TRANSFORM_FEEDBACK_OVERFLOW, CONST_CS|CONST_PERSISTENT);
#endif
#ifdef GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW 
    REGISTER_LONG_CONSTANT("GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW", GL_TRANSFORM_FEEDBACK_STREAM_OVERFLOW, CONST_CS|CONST_PERSISTENT);
#endif
    return SUCCESS;
}

/**
 * Register
 * --------------------------------
 */
static zend_function_entry glfw_functions[] = {
    PHP_FE(glfwInit, arginfo_glfwInit) 
    PHP_FE(glfwTerminate, arginfo_glfwTerminate) 
    PHP_FE(glfwGetVersion, arginfo_glfwGetVersion) 
    PHP_FE(glfwGetVersionString, arginfo_glfwGetVersionString) 
    PHP_FE(glfwMakeContextCurrent, arginfo_glfwMakeContextCurrent) 
    PHP_FE(glfwGetCurrentContext, arginfo_glfwGetCurrentContext) 
    PHP_FE(glfwSwapInterval, arginfo_glfwSwapInterval) 
    PHP_FE(glfwExtensionSupported, arginfo_glfwExtensionSupported) 
    PHP_FE(glfwGetProcAddress, arginfo_glfwGetProcAddress) 
    PHP_FE(glfwDefaultWindowHints, arginfo_glfwDefaultWindowHints) 
    PHP_FE(glfwWindowHint, arginfo_glfwWindowHint) 
    PHP_FE(glfwDestroyWindow, arginfo_glfwDestroyWindow) 
    PHP_FE(glfwCreateWindow, arginfo_glfwCreateWindow) 
    PHP_FE(glfwWindowShouldClose, arginfo_glfwWindowShouldClose) 
    PHP_FE(glfwSetWindowShouldClose, arginfo_glfwSetWindowShouldClose) 
    PHP_FE(glfwSwapBuffers, arginfo_glfwSwapBuffers) 
    PHP_FE(glfwPollEvents, arginfo_glfwPollEvents) 
    PHP_FE(glfwGetTime, arginfo_glfwGetTime) 
    PHP_FE(glfwCreateStandardCursor, arginfo_glfwCreateStandardCursor) 
    PHP_FE(glfwDestroyCursor, arginfo_glfwDestroyCursor) 
    PHP_FE(glfwGetClipboardString, arginfo_glfwGetClipboardString) 
    PHP_FE(glfwGetCursorPos, arginfo_glfwGetCursorPos) 
    PHP_FE(glfwGetKey, arginfo_glfwGetKey) 
    PHP_FE(glfwGetMouseButton, arginfo_glfwGetMouseButton) 
    PHP_FE(glfwSetInputMode, arginfo_glfwSetInputMode) 
    PHP_FE(glfwSetCursorPosCallback, arginfo_glfwSetCursorPosCallback) 
    PHP_FE(glCullFace, arginfo_glCullFace) 
    PHP_FE(glFrontFace, arginfo_glFrontFace) 
    PHP_FE(glHint, arginfo_glHint) 
    PHP_FE(glLineWidth, arginfo_glLineWidth) 
    PHP_FE(glPointSize, arginfo_glPointSize) 
    PHP_FE(glPolygonMode, arginfo_glPolygonMode) 
    PHP_FE(glScissor, arginfo_glScissor) 
    PHP_FE(glTexParameterf, arginfo_glTexParameterf) 
    PHP_FE(glTexParameterfv, arginfo_glTexParameterfv) 
    PHP_FE(glTexParameteri, arginfo_glTexParameteri) 
    PHP_FE(glTexParameteriv, arginfo_glTexParameteriv) 
    PHP_FE(glTexImage1D, arginfo_glTexImage1D) 
    PHP_FE(glTexImage2D, arginfo_glTexImage2D) 
    PHP_FE(glDrawBuffer, arginfo_glDrawBuffer) 
    PHP_FE(glClear, arginfo_glClear) 
    PHP_FE(glClearColor, arginfo_glClearColor) 
    PHP_FE(glClearStencil, arginfo_glClearStencil) 
    PHP_FE(glClearDepth, arginfo_glClearDepth) 
    PHP_FE(glStencilMask, arginfo_glStencilMask) 
    PHP_FE(glColorMask, arginfo_glColorMask) 
    PHP_FE(glDepthMask, arginfo_glDepthMask) 
    PHP_FE(glDisable, arginfo_glDisable) 
    PHP_FE(glEnable, arginfo_glEnable) 
    PHP_FE(glFinish, arginfo_glFinish) 
    PHP_FE(glFlush, arginfo_glFlush) 
    PHP_FE(glBlendFunc, arginfo_glBlendFunc) 
    PHP_FE(glLogicOp, arginfo_glLogicOp) 
    PHP_FE(glStencilFunc, arginfo_glStencilFunc) 
    PHP_FE(glStencilOp, arginfo_glStencilOp) 
    PHP_FE(glDepthFunc, arginfo_glDepthFunc) 
    PHP_FE(glPixelStoref, arginfo_glPixelStoref) 
    PHP_FE(glPixelStorei, arginfo_glPixelStorei) 
    PHP_FE(glReadBuffer, arginfo_glReadBuffer) 
    PHP_FE(glReadPixels, arginfo_glReadPixels) 
    PHP_FE(glGetBooleanv, arginfo_glGetBooleanv) 
    PHP_FE(glGetDoublev, arginfo_glGetDoublev) 
    PHP_FE(glGetError, arginfo_glGetError) 
    PHP_FE(glGetFloatv, arginfo_glGetFloatv) 
    PHP_FE(glGetIntegerv, arginfo_glGetIntegerv) 
    PHP_FE(glGetString, arginfo_glGetString) 
    PHP_FE(glGetTexImage, arginfo_glGetTexImage) 
    PHP_FE(glGetTexParameterfv, arginfo_glGetTexParameterfv) 
    PHP_FE(glGetTexParameteriv, arginfo_glGetTexParameteriv) 
    PHP_FE(glGetTexLevelParameterfv, arginfo_glGetTexLevelParameterfv) 
    PHP_FE(glGetTexLevelParameteriv, arginfo_glGetTexLevelParameteriv) 
    PHP_FE(glIsEnabled, arginfo_glIsEnabled) 
    PHP_FE(glDepthRange, arginfo_glDepthRange) 
    PHP_FE(glViewport, arginfo_glViewport) 
    PHP_FE(glNewList, arginfo_glNewList) 
    PHP_FE(glEndList, arginfo_glEndList) 
    PHP_FE(glCallList, arginfo_glCallList) 
    PHP_FE(glCallLists, arginfo_glCallLists) 
    PHP_FE(glDeleteLists, arginfo_glDeleteLists) 
    PHP_FE(glGenLists, arginfo_glGenLists) 
    PHP_FE(glListBase, arginfo_glListBase) 
    PHP_FE(glBegin, arginfo_glBegin) 
    PHP_FE(glBitmap, arginfo_glBitmap) 
    PHP_FE(glColor3b, arginfo_glColor3b) 
    PHP_FE(glColor3bv, arginfo_glColor3bv) 
    PHP_FE(glColor3d, arginfo_glColor3d) 
    PHP_FE(glColor3dv, arginfo_glColor3dv) 
    PHP_FE(glColor3f, arginfo_glColor3f) 
    PHP_FE(glColor3fv, arginfo_glColor3fv) 
    PHP_FE(glColor3i, arginfo_glColor3i) 
    PHP_FE(glColor3iv, arginfo_glColor3iv) 
    PHP_FE(glColor3s, arginfo_glColor3s) 
    PHP_FE(glColor3sv, arginfo_glColor3sv) 
    PHP_FE(glColor3ub, arginfo_glColor3ub) 
    PHP_FE(glColor3ubv, arginfo_glColor3ubv) 
    PHP_FE(glColor3ui, arginfo_glColor3ui) 
    PHP_FE(glColor3uiv, arginfo_glColor3uiv) 
    PHP_FE(glColor3us, arginfo_glColor3us) 
    PHP_FE(glColor3usv, arginfo_glColor3usv) 
    PHP_FE(glColor4b, arginfo_glColor4b) 
    PHP_FE(glColor4bv, arginfo_glColor4bv) 
    PHP_FE(glColor4d, arginfo_glColor4d) 
    PHP_FE(glColor4dv, arginfo_glColor4dv) 
    PHP_FE(glColor4f, arginfo_glColor4f) 
    PHP_FE(glColor4fv, arginfo_glColor4fv) 
    PHP_FE(glColor4i, arginfo_glColor4i) 
    PHP_FE(glColor4iv, arginfo_glColor4iv) 
    PHP_FE(glColor4s, arginfo_glColor4s) 
    PHP_FE(glColor4sv, arginfo_glColor4sv) 
    PHP_FE(glColor4ub, arginfo_glColor4ub) 
    PHP_FE(glColor4ubv, arginfo_glColor4ubv) 
    PHP_FE(glColor4ui, arginfo_glColor4ui) 
    PHP_FE(glColor4uiv, arginfo_glColor4uiv) 
    PHP_FE(glColor4us, arginfo_glColor4us) 
    PHP_FE(glColor4usv, arginfo_glColor4usv) 
    PHP_FE(glEdgeFlag, arginfo_glEdgeFlag) 
    PHP_FE(glEdgeFlagv, arginfo_glEdgeFlagv) 
    PHP_FE(glEnd, arginfo_glEnd) 
    PHP_FE(glIndexd, arginfo_glIndexd) 
    PHP_FE(glIndexdv, arginfo_glIndexdv) 
    PHP_FE(glIndexf, arginfo_glIndexf) 
    PHP_FE(glIndexfv, arginfo_glIndexfv) 
    PHP_FE(glIndexi, arginfo_glIndexi) 
    PHP_FE(glIndexiv, arginfo_glIndexiv) 
    PHP_FE(glIndexs, arginfo_glIndexs) 
    PHP_FE(glIndexsv, arginfo_glIndexsv) 
    PHP_FE(glNormal3b, arginfo_glNormal3b) 
    PHP_FE(glNormal3bv, arginfo_glNormal3bv) 
    PHP_FE(glNormal3d, arginfo_glNormal3d) 
    PHP_FE(glNormal3dv, arginfo_glNormal3dv) 
    PHP_FE(glNormal3f, arginfo_glNormal3f) 
    PHP_FE(glNormal3fv, arginfo_glNormal3fv) 
    PHP_FE(glNormal3i, arginfo_glNormal3i) 
    PHP_FE(glNormal3iv, arginfo_glNormal3iv) 
    PHP_FE(glNormal3s, arginfo_glNormal3s) 
    PHP_FE(glNormal3sv, arginfo_glNormal3sv) 
    PHP_FE(glRasterPos2d, arginfo_glRasterPos2d) 
    PHP_FE(glRasterPos2dv, arginfo_glRasterPos2dv) 
    PHP_FE(glRasterPos2f, arginfo_glRasterPos2f) 
    PHP_FE(glRasterPos2fv, arginfo_glRasterPos2fv) 
    PHP_FE(glRasterPos2i, arginfo_glRasterPos2i) 
    PHP_FE(glRasterPos2iv, arginfo_glRasterPos2iv) 
    PHP_FE(glRasterPos2s, arginfo_glRasterPos2s) 
    PHP_FE(glRasterPos2sv, arginfo_glRasterPos2sv) 
    PHP_FE(glRasterPos3d, arginfo_glRasterPos3d) 
    PHP_FE(glRasterPos3dv, arginfo_glRasterPos3dv) 
    PHP_FE(glRasterPos3f, arginfo_glRasterPos3f) 
    PHP_FE(glRasterPos3fv, arginfo_glRasterPos3fv) 
    PHP_FE(glRasterPos3i, arginfo_glRasterPos3i) 
    PHP_FE(glRasterPos3iv, arginfo_glRasterPos3iv) 
    PHP_FE(glRasterPos3s, arginfo_glRasterPos3s) 
    PHP_FE(glRasterPos3sv, arginfo_glRasterPos3sv) 
    PHP_FE(glRasterPos4d, arginfo_glRasterPos4d) 
    PHP_FE(glRasterPos4dv, arginfo_glRasterPos4dv) 
    PHP_FE(glRasterPos4f, arginfo_glRasterPos4f) 
    PHP_FE(glRasterPos4fv, arginfo_glRasterPos4fv) 
    PHP_FE(glRasterPos4i, arginfo_glRasterPos4i) 
    PHP_FE(glRasterPos4iv, arginfo_glRasterPos4iv) 
    PHP_FE(glRasterPos4s, arginfo_glRasterPos4s) 
    PHP_FE(glRasterPos4sv, arginfo_glRasterPos4sv) 
    PHP_FE(glRectd, arginfo_glRectd) 
    PHP_FE(glRectdv, arginfo_glRectdv) 
    PHP_FE(glRectf, arginfo_glRectf) 
    PHP_FE(glRectfv, arginfo_glRectfv) 
    PHP_FE(glRecti, arginfo_glRecti) 
    PHP_FE(glRectiv, arginfo_glRectiv) 
    PHP_FE(glRects, arginfo_glRects) 
    PHP_FE(glRectsv, arginfo_glRectsv) 
    PHP_FE(glTexCoord1d, arginfo_glTexCoord1d) 
    PHP_FE(glTexCoord1dv, arginfo_glTexCoord1dv) 
    PHP_FE(glTexCoord1f, arginfo_glTexCoord1f) 
    PHP_FE(glTexCoord1fv, arginfo_glTexCoord1fv) 
    PHP_FE(glTexCoord1i, arginfo_glTexCoord1i) 
    PHP_FE(glTexCoord1iv, arginfo_glTexCoord1iv) 
    PHP_FE(glTexCoord1s, arginfo_glTexCoord1s) 
    PHP_FE(glTexCoord1sv, arginfo_glTexCoord1sv) 
    PHP_FE(glTexCoord2d, arginfo_glTexCoord2d) 
    PHP_FE(glTexCoord2dv, arginfo_glTexCoord2dv) 
    PHP_FE(glTexCoord2f, arginfo_glTexCoord2f) 
    PHP_FE(glTexCoord2fv, arginfo_glTexCoord2fv) 
    PHP_FE(glTexCoord2i, arginfo_glTexCoord2i) 
    PHP_FE(glTexCoord2iv, arginfo_glTexCoord2iv) 
    PHP_FE(glTexCoord2s, arginfo_glTexCoord2s) 
    PHP_FE(glTexCoord2sv, arginfo_glTexCoord2sv) 
    PHP_FE(glTexCoord3d, arginfo_glTexCoord3d) 
    PHP_FE(glTexCoord3dv, arginfo_glTexCoord3dv) 
    PHP_FE(glTexCoord3f, arginfo_glTexCoord3f) 
    PHP_FE(glTexCoord3fv, arginfo_glTexCoord3fv) 
    PHP_FE(glTexCoord3i, arginfo_glTexCoord3i) 
    PHP_FE(glTexCoord3iv, arginfo_glTexCoord3iv) 
    PHP_FE(glTexCoord3s, arginfo_glTexCoord3s) 
    PHP_FE(glTexCoord3sv, arginfo_glTexCoord3sv) 
    PHP_FE(glTexCoord4d, arginfo_glTexCoord4d) 
    PHP_FE(glTexCoord4dv, arginfo_glTexCoord4dv) 
    PHP_FE(glTexCoord4f, arginfo_glTexCoord4f) 
    PHP_FE(glTexCoord4fv, arginfo_glTexCoord4fv) 
    PHP_FE(glTexCoord4i, arginfo_glTexCoord4i) 
    PHP_FE(glTexCoord4iv, arginfo_glTexCoord4iv) 
    PHP_FE(glTexCoord4s, arginfo_glTexCoord4s) 
    PHP_FE(glTexCoord4sv, arginfo_glTexCoord4sv) 
    PHP_FE(glVertex2d, arginfo_glVertex2d) 
    PHP_FE(glVertex2dv, arginfo_glVertex2dv) 
    PHP_FE(glVertex2f, arginfo_glVertex2f) 
    PHP_FE(glVertex2fv, arginfo_glVertex2fv) 
    PHP_FE(glVertex2i, arginfo_glVertex2i) 
    PHP_FE(glVertex2iv, arginfo_glVertex2iv) 
    PHP_FE(glVertex2s, arginfo_glVertex2s) 
    PHP_FE(glVertex2sv, arginfo_glVertex2sv) 
    PHP_FE(glVertex3d, arginfo_glVertex3d) 
    PHP_FE(glVertex3dv, arginfo_glVertex3dv) 
    PHP_FE(glVertex3f, arginfo_glVertex3f) 
    PHP_FE(glVertex3fv, arginfo_glVertex3fv) 
    PHP_FE(glVertex3i, arginfo_glVertex3i) 
    PHP_FE(glVertex3iv, arginfo_glVertex3iv) 
    PHP_FE(glVertex3s, arginfo_glVertex3s) 
    PHP_FE(glVertex3sv, arginfo_glVertex3sv) 
    PHP_FE(glVertex4d, arginfo_glVertex4d) 
    PHP_FE(glVertex4dv, arginfo_glVertex4dv) 
    PHP_FE(glVertex4f, arginfo_glVertex4f) 
    PHP_FE(glVertex4fv, arginfo_glVertex4fv) 
    PHP_FE(glVertex4i, arginfo_glVertex4i) 
    PHP_FE(glVertex4iv, arginfo_glVertex4iv) 
    PHP_FE(glVertex4s, arginfo_glVertex4s) 
    PHP_FE(glVertex4sv, arginfo_glVertex4sv) 
    PHP_FE(glClipPlane, arginfo_glClipPlane) 
    PHP_FE(glColorMaterial, arginfo_glColorMaterial) 
    PHP_FE(glFogf, arginfo_glFogf) 
    PHP_FE(glFogfv, arginfo_glFogfv) 
    PHP_FE(glFogi, arginfo_glFogi) 
    PHP_FE(glFogiv, arginfo_glFogiv) 
    PHP_FE(glLightf, arginfo_glLightf) 
    PHP_FE(glLightfv, arginfo_glLightfv) 
    PHP_FE(glLighti, arginfo_glLighti) 
    PHP_FE(glLightiv, arginfo_glLightiv) 
    PHP_FE(glLightModelf, arginfo_glLightModelf) 
    PHP_FE(glLightModelfv, arginfo_glLightModelfv) 
    PHP_FE(glLightModeli, arginfo_glLightModeli) 
    PHP_FE(glLightModeliv, arginfo_glLightModeliv) 
    PHP_FE(glLineStipple, arginfo_glLineStipple) 
    PHP_FE(glMaterialf, arginfo_glMaterialf) 
    PHP_FE(glMaterialfv, arginfo_glMaterialfv) 
    PHP_FE(glMateriali, arginfo_glMateriali) 
    PHP_FE(glMaterialiv, arginfo_glMaterialiv) 
    PHP_FE(glPolygonStipple, arginfo_glPolygonStipple) 
    PHP_FE(glShadeModel, arginfo_glShadeModel) 
    PHP_FE(glTexEnvf, arginfo_glTexEnvf) 
    PHP_FE(glTexEnvfv, arginfo_glTexEnvfv) 
    PHP_FE(glTexEnvi, arginfo_glTexEnvi) 
    PHP_FE(glTexEnviv, arginfo_glTexEnviv) 
    PHP_FE(glTexGend, arginfo_glTexGend) 
    PHP_FE(glTexGendv, arginfo_glTexGendv) 
    PHP_FE(glTexGenf, arginfo_glTexGenf) 
    PHP_FE(glTexGenfv, arginfo_glTexGenfv) 
    PHP_FE(glTexGeni, arginfo_glTexGeni) 
    PHP_FE(glTexGeniv, arginfo_glTexGeniv) 
    PHP_FE(glFeedbackBuffer, arginfo_glFeedbackBuffer) 
    PHP_FE(glSelectBuffer, arginfo_glSelectBuffer) 
    PHP_FE(glRenderMode, arginfo_glRenderMode) 
    PHP_FE(glInitNames, arginfo_glInitNames) 
    PHP_FE(glLoadName, arginfo_glLoadName) 
    PHP_FE(glPassThrough, arginfo_glPassThrough) 
    PHP_FE(glPopName, arginfo_glPopName) 
    PHP_FE(glPushName, arginfo_glPushName) 
    PHP_FE(glClearAccum, arginfo_glClearAccum) 
    PHP_FE(glClearIndex, arginfo_glClearIndex) 
    PHP_FE(glIndexMask, arginfo_glIndexMask) 
    PHP_FE(glAccum, arginfo_glAccum) 
    PHP_FE(glPopAttrib, arginfo_glPopAttrib) 
    PHP_FE(glPushAttrib, arginfo_glPushAttrib) 
    PHP_FE(glMap1d, arginfo_glMap1d) 
    PHP_FE(glMap1f, arginfo_glMap1f) 
    PHP_FE(glMap2d, arginfo_glMap2d) 
    PHP_FE(glMap2f, arginfo_glMap2f) 
    PHP_FE(glMapGrid1d, arginfo_glMapGrid1d) 
    PHP_FE(glMapGrid1f, arginfo_glMapGrid1f) 
    PHP_FE(glMapGrid2d, arginfo_glMapGrid2d) 
    PHP_FE(glMapGrid2f, arginfo_glMapGrid2f) 
    PHP_FE(glEvalCoord1d, arginfo_glEvalCoord1d) 
    PHP_FE(glEvalCoord1dv, arginfo_glEvalCoord1dv) 
    PHP_FE(glEvalCoord1f, arginfo_glEvalCoord1f) 
    PHP_FE(glEvalCoord1fv, arginfo_glEvalCoord1fv) 
    PHP_FE(glEvalCoord2d, arginfo_glEvalCoord2d) 
    PHP_FE(glEvalCoord2dv, arginfo_glEvalCoord2dv) 
    PHP_FE(glEvalCoord2f, arginfo_glEvalCoord2f) 
    PHP_FE(glEvalCoord2fv, arginfo_glEvalCoord2fv) 
    PHP_FE(glEvalMesh1, arginfo_glEvalMesh1) 
    PHP_FE(glEvalPoint1, arginfo_glEvalPoint1) 
    PHP_FE(glEvalMesh2, arginfo_glEvalMesh2) 
    PHP_FE(glEvalPoint2, arginfo_glEvalPoint2) 
    PHP_FE(glAlphaFunc, arginfo_glAlphaFunc) 
    PHP_FE(glPixelZoom, arginfo_glPixelZoom) 
    PHP_FE(glPixelTransferf, arginfo_glPixelTransferf) 
    PHP_FE(glPixelTransferi, arginfo_glPixelTransferi) 
    PHP_FE(glPixelMapfv, arginfo_glPixelMapfv) 
    PHP_FE(glPixelMapuiv, arginfo_glPixelMapuiv) 
    PHP_FE(glPixelMapusv, arginfo_glPixelMapusv) 
    PHP_FE(glCopyPixels, arginfo_glCopyPixels) 
    PHP_FE(glDrawPixels, arginfo_glDrawPixels) 
    PHP_FE(glGetClipPlane, arginfo_glGetClipPlane) 
    PHP_FE(glGetLightfv, arginfo_glGetLightfv) 
    PHP_FE(glGetLightiv, arginfo_glGetLightiv) 
    PHP_FE(glGetMapdv, arginfo_glGetMapdv) 
    PHP_FE(glGetMapfv, arginfo_glGetMapfv) 
    PHP_FE(glGetMapiv, arginfo_glGetMapiv) 
    PHP_FE(glGetMaterialfv, arginfo_glGetMaterialfv) 
    PHP_FE(glGetMaterialiv, arginfo_glGetMaterialiv) 
    PHP_FE(glGetPixelMapfv, arginfo_glGetPixelMapfv) 
    PHP_FE(glGetPixelMapuiv, arginfo_glGetPixelMapuiv) 
    PHP_FE(glGetPixelMapusv, arginfo_glGetPixelMapusv) 
    PHP_FE(glGetPolygonStipple, arginfo_glGetPolygonStipple) 
    PHP_FE(glGetTexEnvfv, arginfo_glGetTexEnvfv) 
    PHP_FE(glGetTexEnviv, arginfo_glGetTexEnviv) 
    PHP_FE(glGetTexGendv, arginfo_glGetTexGendv) 
    PHP_FE(glGetTexGenfv, arginfo_glGetTexGenfv) 
    PHP_FE(glGetTexGeniv, arginfo_glGetTexGeniv) 
    PHP_FE(glIsList, arginfo_glIsList) 
    PHP_FE(glFrustum, arginfo_glFrustum) 
    PHP_FE(glLoadIdentity, arginfo_glLoadIdentity) 
    PHP_FE(glLoadMatrixf, arginfo_glLoadMatrixf) 
    PHP_FE(glLoadMatrixd, arginfo_glLoadMatrixd) 
    PHP_FE(glMatrixMode, arginfo_glMatrixMode) 
    PHP_FE(glMultMatrixf, arginfo_glMultMatrixf) 
    PHP_FE(glMultMatrixd, arginfo_glMultMatrixd) 
    PHP_FE(glOrtho, arginfo_glOrtho) 
    PHP_FE(glPopMatrix, arginfo_glPopMatrix) 
    PHP_FE(glPushMatrix, arginfo_glPushMatrix) 
    PHP_FE(glRotated, arginfo_glRotated) 
    PHP_FE(glRotatef, arginfo_glRotatef) 
    PHP_FE(glScaled, arginfo_glScaled) 
    PHP_FE(glScalef, arginfo_glScalef) 
    PHP_FE(glTranslated, arginfo_glTranslated) 
    PHP_FE(glTranslatef, arginfo_glTranslatef) 
    PHP_FE(glDrawArrays, arginfo_glDrawArrays) 
    PHP_FE(glDrawElements, arginfo_glDrawElements) 
    PHP_FE(glGetPointerv, arginfo_glGetPointerv) 
    PHP_FE(glPolygonOffset, arginfo_glPolygonOffset) 
    PHP_FE(glCopyTexImage1D, arginfo_glCopyTexImage1D) 
    PHP_FE(glCopyTexImage2D, arginfo_glCopyTexImage2D) 
    PHP_FE(glCopyTexSubImage1D, arginfo_glCopyTexSubImage1D) 
    PHP_FE(glCopyTexSubImage2D, arginfo_glCopyTexSubImage2D) 
    PHP_FE(glTexSubImage1D, arginfo_glTexSubImage1D) 
    PHP_FE(glTexSubImage2D, arginfo_glTexSubImage2D) 
    PHP_FE(glBindTexture, arginfo_glBindTexture) 
    PHP_FE(glDeleteTextures, arginfo_glDeleteTextures) 
    PHP_FE(glGenTextures, arginfo_glGenTextures) 
    PHP_FE(glIsTexture, arginfo_glIsTexture) 
    PHP_FE(glArrayElement, arginfo_glArrayElement) 
    PHP_FE(glColorPointer, arginfo_glColorPointer) 
    PHP_FE(glDisableClientState, arginfo_glDisableClientState) 
    PHP_FE(glEdgeFlagPointer, arginfo_glEdgeFlagPointer) 
    PHP_FE(glEnableClientState, arginfo_glEnableClientState) 
    PHP_FE(glIndexPointer, arginfo_glIndexPointer) 
    PHP_FE(glInterleavedArrays, arginfo_glInterleavedArrays) 
    PHP_FE(glNormalPointer, arginfo_glNormalPointer) 
    PHP_FE(glTexCoordPointer, arginfo_glTexCoordPointer) 
    PHP_FE(glVertexPointer, arginfo_glVertexPointer) 
    PHP_FE(glAreTexturesResident, arginfo_glAreTexturesResident) 
    PHP_FE(glPrioritizeTextures, arginfo_glPrioritizeTextures) 
    PHP_FE(glIndexub, arginfo_glIndexub) 
    PHP_FE(glIndexubv, arginfo_glIndexubv) 
    PHP_FE(glPopClientAttrib, arginfo_glPopClientAttrib) 
    PHP_FE(glPushClientAttrib, arginfo_glPushClientAttrib) 
    PHP_FE(glDrawRangeElements, arginfo_glDrawRangeElements) 
    PHP_FE(glTexImage3D, arginfo_glTexImage3D) 
    PHP_FE(glTexSubImage3D, arginfo_glTexSubImage3D) 
    PHP_FE(glCopyTexSubImage3D, arginfo_glCopyTexSubImage3D) 
    PHP_FE(glActiveTexture, arginfo_glActiveTexture) 
    PHP_FE(glSampleCoverage, arginfo_glSampleCoverage) 
    PHP_FE(glCompressedTexImage3D, arginfo_glCompressedTexImage3D) 
    PHP_FE(glCompressedTexImage2D, arginfo_glCompressedTexImage2D) 
    PHP_FE(glCompressedTexImage1D, arginfo_glCompressedTexImage1D) 
    PHP_FE(glCompressedTexSubImage3D, arginfo_glCompressedTexSubImage3D) 
    PHP_FE(glCompressedTexSubImage2D, arginfo_glCompressedTexSubImage2D) 
    PHP_FE(glCompressedTexSubImage1D, arginfo_glCompressedTexSubImage1D) 
    PHP_FE(glGetCompressedTexImage, arginfo_glGetCompressedTexImage) 
    PHP_FE(glClientActiveTexture, arginfo_glClientActiveTexture) 
    PHP_FE(glMultiTexCoord1d, arginfo_glMultiTexCoord1d) 
    PHP_FE(glMultiTexCoord1dv, arginfo_glMultiTexCoord1dv) 
    PHP_FE(glMultiTexCoord1f, arginfo_glMultiTexCoord1f) 
    PHP_FE(glMultiTexCoord1fv, arginfo_glMultiTexCoord1fv) 
    PHP_FE(glMultiTexCoord1i, arginfo_glMultiTexCoord1i) 
    PHP_FE(glMultiTexCoord1iv, arginfo_glMultiTexCoord1iv) 
    PHP_FE(glMultiTexCoord1s, arginfo_glMultiTexCoord1s) 
    PHP_FE(glMultiTexCoord1sv, arginfo_glMultiTexCoord1sv) 
    PHP_FE(glMultiTexCoord2d, arginfo_glMultiTexCoord2d) 
    PHP_FE(glMultiTexCoord2dv, arginfo_glMultiTexCoord2dv) 
    PHP_FE(glMultiTexCoord2f, arginfo_glMultiTexCoord2f) 
    PHP_FE(glMultiTexCoord2fv, arginfo_glMultiTexCoord2fv) 
    PHP_FE(glMultiTexCoord2i, arginfo_glMultiTexCoord2i) 
    PHP_FE(glMultiTexCoord2iv, arginfo_glMultiTexCoord2iv) 
    PHP_FE(glMultiTexCoord2s, arginfo_glMultiTexCoord2s) 
    PHP_FE(glMultiTexCoord2sv, arginfo_glMultiTexCoord2sv) 
    PHP_FE(glMultiTexCoord3d, arginfo_glMultiTexCoord3d) 
    PHP_FE(glMultiTexCoord3dv, arginfo_glMultiTexCoord3dv) 
    PHP_FE(glMultiTexCoord3f, arginfo_glMultiTexCoord3f) 
    PHP_FE(glMultiTexCoord3fv, arginfo_glMultiTexCoord3fv) 
    PHP_FE(glMultiTexCoord3i, arginfo_glMultiTexCoord3i) 
    PHP_FE(glMultiTexCoord3iv, arginfo_glMultiTexCoord3iv) 
    PHP_FE(glMultiTexCoord3s, arginfo_glMultiTexCoord3s) 
    PHP_FE(glMultiTexCoord3sv, arginfo_glMultiTexCoord3sv) 
    PHP_FE(glMultiTexCoord4d, arginfo_glMultiTexCoord4d) 
    PHP_FE(glMultiTexCoord4dv, arginfo_glMultiTexCoord4dv) 
    PHP_FE(glMultiTexCoord4f, arginfo_glMultiTexCoord4f) 
    PHP_FE(glMultiTexCoord4fv, arginfo_glMultiTexCoord4fv) 
    PHP_FE(glMultiTexCoord4i, arginfo_glMultiTexCoord4i) 
    PHP_FE(glMultiTexCoord4iv, arginfo_glMultiTexCoord4iv) 
    PHP_FE(glMultiTexCoord4s, arginfo_glMultiTexCoord4s) 
    PHP_FE(glMultiTexCoord4sv, arginfo_glMultiTexCoord4sv) 
    PHP_FE(glLoadTransposeMatrixf, arginfo_glLoadTransposeMatrixf) 
    PHP_FE(glLoadTransposeMatrixd, arginfo_glLoadTransposeMatrixd) 
    PHP_FE(glMultTransposeMatrixf, arginfo_glMultTransposeMatrixf) 
    PHP_FE(glMultTransposeMatrixd, arginfo_glMultTransposeMatrixd) 
    PHP_FE(glBlendFuncSeparate, arginfo_glBlendFuncSeparate) 
    PHP_FE(glMultiDrawArrays, arginfo_glMultiDrawArrays) 
    PHP_FE(glMultiDrawElements, arginfo_glMultiDrawElements) 
    PHP_FE(glPointParameterf, arginfo_glPointParameterf) 
    PHP_FE(glPointParameterfv, arginfo_glPointParameterfv) 
    PHP_FE(glPointParameteri, arginfo_glPointParameteri) 
    PHP_FE(glPointParameteriv, arginfo_glPointParameteriv) 
    PHP_FE(glFogCoordf, arginfo_glFogCoordf) 
    PHP_FE(glFogCoordfv, arginfo_glFogCoordfv) 
    PHP_FE(glFogCoordd, arginfo_glFogCoordd) 
    PHP_FE(glFogCoorddv, arginfo_glFogCoorddv) 
    PHP_FE(glFogCoordPointer, arginfo_glFogCoordPointer) 
    PHP_FE(glSecondaryColor3b, arginfo_glSecondaryColor3b) 
    PHP_FE(glSecondaryColor3bv, arginfo_glSecondaryColor3bv) 
    PHP_FE(glSecondaryColor3d, arginfo_glSecondaryColor3d) 
    PHP_FE(glSecondaryColor3dv, arginfo_glSecondaryColor3dv) 
    PHP_FE(glSecondaryColor3f, arginfo_glSecondaryColor3f) 
    PHP_FE(glSecondaryColor3fv, arginfo_glSecondaryColor3fv) 
    PHP_FE(glSecondaryColor3i, arginfo_glSecondaryColor3i) 
    PHP_FE(glSecondaryColor3iv, arginfo_glSecondaryColor3iv) 
    PHP_FE(glSecondaryColor3s, arginfo_glSecondaryColor3s) 
    PHP_FE(glSecondaryColor3sv, arginfo_glSecondaryColor3sv) 
    PHP_FE(glSecondaryColor3ub, arginfo_glSecondaryColor3ub) 
    PHP_FE(glSecondaryColor3ubv, arginfo_glSecondaryColor3ubv) 
    PHP_FE(glSecondaryColor3ui, arginfo_glSecondaryColor3ui) 
    PHP_FE(glSecondaryColor3uiv, arginfo_glSecondaryColor3uiv) 
    PHP_FE(glSecondaryColor3us, arginfo_glSecondaryColor3us) 
    PHP_FE(glSecondaryColor3usv, arginfo_glSecondaryColor3usv) 
    PHP_FE(glSecondaryColorPointer, arginfo_glSecondaryColorPointer) 
    PHP_FE(glWindowPos2d, arginfo_glWindowPos2d) 
    PHP_FE(glWindowPos2dv, arginfo_glWindowPos2dv) 
    PHP_FE(glWindowPos2f, arginfo_glWindowPos2f) 
    PHP_FE(glWindowPos2fv, arginfo_glWindowPos2fv) 
    PHP_FE(glWindowPos2i, arginfo_glWindowPos2i) 
    PHP_FE(glWindowPos2iv, arginfo_glWindowPos2iv) 
    PHP_FE(glWindowPos2s, arginfo_glWindowPos2s) 
    PHP_FE(glWindowPos2sv, arginfo_glWindowPos2sv) 
    PHP_FE(glWindowPos3d, arginfo_glWindowPos3d) 
    PHP_FE(glWindowPos3dv, arginfo_glWindowPos3dv) 
    PHP_FE(glWindowPos3f, arginfo_glWindowPos3f) 
    PHP_FE(glWindowPos3fv, arginfo_glWindowPos3fv) 
    PHP_FE(glWindowPos3i, arginfo_glWindowPos3i) 
    PHP_FE(glWindowPos3iv, arginfo_glWindowPos3iv) 
    PHP_FE(glWindowPos3s, arginfo_glWindowPos3s) 
    PHP_FE(glWindowPos3sv, arginfo_glWindowPos3sv) 
    PHP_FE(glGenQueries, arginfo_glGenQueries) 
    PHP_FE(glDeleteQueries, arginfo_glDeleteQueries) 
    PHP_FE(glIsQuery, arginfo_glIsQuery) 
    PHP_FE(glBeginQuery, arginfo_glBeginQuery) 
    PHP_FE(glEndQuery, arginfo_glEndQuery) 
    PHP_FE(glGetQueryiv, arginfo_glGetQueryiv) 
    PHP_FE(glGetQueryObjectiv, arginfo_glGetQueryObjectiv) 
    PHP_FE(glGetQueryObjectuiv, arginfo_glGetQueryObjectuiv) 
    PHP_FE(glBindBuffer, arginfo_glBindBuffer) 
    PHP_FE(glDeleteBuffers, arginfo_glDeleteBuffers) 
    PHP_FE(glGenBuffers, arginfo_glGenBuffers) 
    PHP_FE(glIsBuffer, arginfo_glIsBuffer) 
    PHP_FE(glBufferData, arginfo_glBufferData) 
    PHP_FE(glBufferSubData, arginfo_glBufferSubData) 
    PHP_FE(glGetBufferSubData, arginfo_glGetBufferSubData) 
    PHP_FE(glMapBuffer, arginfo_glMapBuffer) 
    PHP_FE(glUnmapBuffer, arginfo_glUnmapBuffer) 
    PHP_FE(glGetBufferParameteriv, arginfo_glGetBufferParameteriv) 
    PHP_FE(glGetBufferPointerv, arginfo_glGetBufferPointerv) 
    PHP_FE(glBlendEquationSeparate, arginfo_glBlendEquationSeparate) 
    PHP_FE(glDrawBuffers, arginfo_glDrawBuffers) 
    PHP_FE(glStencilOpSeparate, arginfo_glStencilOpSeparate) 
    PHP_FE(glStencilFuncSeparate, arginfo_glStencilFuncSeparate) 
    PHP_FE(glStencilMaskSeparate, arginfo_glStencilMaskSeparate) 
    PHP_FE(glAttachShader, arginfo_glAttachShader) 
    PHP_FE(glBindAttribLocation, arginfo_glBindAttribLocation) 
    PHP_FE(glCompileShader, arginfo_glCompileShader) 
    PHP_FE(glCreateProgram, arginfo_glCreateProgram) 
    PHP_FE(glCreateShader, arginfo_glCreateShader) 
    PHP_FE(glDeleteProgram, arginfo_glDeleteProgram) 
    PHP_FE(glDeleteShader, arginfo_glDeleteShader) 
    PHP_FE(glDetachShader, arginfo_glDetachShader) 
    PHP_FE(glDisableVertexAttribArray, arginfo_glDisableVertexAttribArray) 
    PHP_FE(glEnableVertexAttribArray, arginfo_glEnableVertexAttribArray) 
    PHP_FE(glGetActiveAttrib, arginfo_glGetActiveAttrib) 
    PHP_FE(glGetActiveUniform, arginfo_glGetActiveUniform) 
    PHP_FE(glGetAttachedShaders, arginfo_glGetAttachedShaders) 
    PHP_FE(glGetAttribLocation, arginfo_glGetAttribLocation) 
    PHP_FE(glGetProgramiv, arginfo_glGetProgramiv) 
    PHP_FE(glGetProgramInfoLog, arginfo_glGetProgramInfoLog) 
    PHP_FE(glGetShaderiv, arginfo_glGetShaderiv) 
    PHP_FE(glGetShaderInfoLog, arginfo_glGetShaderInfoLog) 
    PHP_FE(glGetShaderSource, arginfo_glGetShaderSource) 
    PHP_FE(glGetUniformLocation, arginfo_glGetUniformLocation) 
    PHP_FE(glGetUniformfv, arginfo_glGetUniformfv) 
    PHP_FE(glGetUniformiv, arginfo_glGetUniformiv) 
    PHP_FE(glGetVertexAttribdv, arginfo_glGetVertexAttribdv) 
    PHP_FE(glGetVertexAttribfv, arginfo_glGetVertexAttribfv) 
    PHP_FE(glGetVertexAttribiv, arginfo_glGetVertexAttribiv) 
    PHP_FE(glGetVertexAttribPointerv, arginfo_glGetVertexAttribPointerv) 
    PHP_FE(glIsProgram, arginfo_glIsProgram) 
    PHP_FE(glIsShader, arginfo_glIsShader) 
    PHP_FE(glLinkProgram, arginfo_glLinkProgram) 
    PHP_FE(glShaderSource, arginfo_glShaderSource) 
    PHP_FE(glUseProgram, arginfo_glUseProgram) 
    PHP_FE(glUniform1f, arginfo_glUniform1f) 
    PHP_FE(glUniform2f, arginfo_glUniform2f) 
    PHP_FE(glUniform3f, arginfo_glUniform3f) 
    PHP_FE(glUniform4f, arginfo_glUniform4f) 
    PHP_FE(glUniform1i, arginfo_glUniform1i) 
    PHP_FE(glUniform2i, arginfo_glUniform2i) 
    PHP_FE(glUniform3i, arginfo_glUniform3i) 
    PHP_FE(glUniform4i, arginfo_glUniform4i) 
    PHP_FE(glUniform1fv, arginfo_glUniform1fv) 
    PHP_FE(glUniform2fv, arginfo_glUniform2fv) 
    PHP_FE(glUniform3fv, arginfo_glUniform3fv) 
    PHP_FE(glUniform4fv, arginfo_glUniform4fv) 
    PHP_FE(glUniform1iv, arginfo_glUniform1iv) 
    PHP_FE(glUniform2iv, arginfo_glUniform2iv) 
    PHP_FE(glUniform3iv, arginfo_glUniform3iv) 
    PHP_FE(glUniform4iv, arginfo_glUniform4iv) 
    PHP_FE(glUniformMatrix2fv, arginfo_glUniformMatrix2fv) 
    PHP_FE(glUniformMatrix3fv, arginfo_glUniformMatrix3fv) 
    PHP_FE(glUniformMatrix4fv, arginfo_glUniformMatrix4fv) 
    PHP_FE(glValidateProgram, arginfo_glValidateProgram) 
    PHP_FE(glVertexAttrib1d, arginfo_glVertexAttrib1d) 
    PHP_FE(glVertexAttrib1dv, arginfo_glVertexAttrib1dv) 
    PHP_FE(glVertexAttrib1f, arginfo_glVertexAttrib1f) 
    PHP_FE(glVertexAttrib1fv, arginfo_glVertexAttrib1fv) 
    PHP_FE(glVertexAttrib1s, arginfo_glVertexAttrib1s) 
    PHP_FE(glVertexAttrib1sv, arginfo_glVertexAttrib1sv) 
    PHP_FE(glVertexAttrib2d, arginfo_glVertexAttrib2d) 
    PHP_FE(glVertexAttrib2dv, arginfo_glVertexAttrib2dv) 
    PHP_FE(glVertexAttrib2f, arginfo_glVertexAttrib2f) 
    PHP_FE(glVertexAttrib2fv, arginfo_glVertexAttrib2fv) 
    PHP_FE(glVertexAttrib2s, arginfo_glVertexAttrib2s) 
    PHP_FE(glVertexAttrib2sv, arginfo_glVertexAttrib2sv) 
    PHP_FE(glVertexAttrib3d, arginfo_glVertexAttrib3d) 
    PHP_FE(glVertexAttrib3dv, arginfo_glVertexAttrib3dv) 
    PHP_FE(glVertexAttrib3f, arginfo_glVertexAttrib3f) 
    PHP_FE(glVertexAttrib3fv, arginfo_glVertexAttrib3fv) 
    PHP_FE(glVertexAttrib3s, arginfo_glVertexAttrib3s) 
    PHP_FE(glVertexAttrib3sv, arginfo_glVertexAttrib3sv) 
    PHP_FE(glVertexAttrib4Nbv, arginfo_glVertexAttrib4Nbv) 
    PHP_FE(glVertexAttrib4Niv, arginfo_glVertexAttrib4Niv) 
    PHP_FE(glVertexAttrib4Nsv, arginfo_glVertexAttrib4Nsv) 
    PHP_FE(glVertexAttrib4Nub, arginfo_glVertexAttrib4Nub) 
    PHP_FE(glVertexAttrib4Nubv, arginfo_glVertexAttrib4Nubv) 
    PHP_FE(glVertexAttrib4Nuiv, arginfo_glVertexAttrib4Nuiv) 
    PHP_FE(glVertexAttrib4Nusv, arginfo_glVertexAttrib4Nusv) 
    PHP_FE(glVertexAttrib4bv, arginfo_glVertexAttrib4bv) 
    PHP_FE(glVertexAttrib4d, arginfo_glVertexAttrib4d) 
    PHP_FE(glVertexAttrib4dv, arginfo_glVertexAttrib4dv) 
    PHP_FE(glVertexAttrib4f, arginfo_glVertexAttrib4f) 
    PHP_FE(glVertexAttrib4fv, arginfo_glVertexAttrib4fv) 
    PHP_FE(glVertexAttrib4iv, arginfo_glVertexAttrib4iv) 
    PHP_FE(glVertexAttrib4s, arginfo_glVertexAttrib4s) 
    PHP_FE(glVertexAttrib4sv, arginfo_glVertexAttrib4sv) 
    PHP_FE(glVertexAttrib4ubv, arginfo_glVertexAttrib4ubv) 
    PHP_FE(glVertexAttrib4uiv, arginfo_glVertexAttrib4uiv) 
    PHP_FE(glVertexAttrib4usv, arginfo_glVertexAttrib4usv) 
    PHP_FE(glVertexAttribPointer, arginfo_glVertexAttribPointer) 
    PHP_FE(glUniformMatrix2x3fv, arginfo_glUniformMatrix2x3fv) 
    PHP_FE(glUniformMatrix3x2fv, arginfo_glUniformMatrix3x2fv) 
    PHP_FE(glUniformMatrix2x4fv, arginfo_glUniformMatrix2x4fv) 
    PHP_FE(glUniformMatrix4x2fv, arginfo_glUniformMatrix4x2fv) 
    PHP_FE(glUniformMatrix3x4fv, arginfo_glUniformMatrix3x4fv) 
    PHP_FE(glUniformMatrix4x3fv, arginfo_glUniformMatrix4x3fv) 
    PHP_FE(glColorMaski, arginfo_glColorMaski) 
    PHP_FE(glGetBooleani_v, arginfo_glGetBooleani_v) 
    PHP_FE(glGetIntegeri_v, arginfo_glGetIntegeri_v) 
    PHP_FE(glEnablei, arginfo_glEnablei) 
    PHP_FE(glDisablei, arginfo_glDisablei) 
    PHP_FE(glIsEnabledi, arginfo_glIsEnabledi) 
    PHP_FE(glBeginTransformFeedback, arginfo_glBeginTransformFeedback) 
    PHP_FE(glEndTransformFeedback, arginfo_glEndTransformFeedback) 
    PHP_FE(glBindBufferRange, arginfo_glBindBufferRange) 
    PHP_FE(glBindBufferBase, arginfo_glBindBufferBase) 
    PHP_FE(glTransformFeedbackVaryings, arginfo_glTransformFeedbackVaryings) 
    PHP_FE(glGetTransformFeedbackVarying, arginfo_glGetTransformFeedbackVarying) 
    PHP_FE(glClampColor, arginfo_glClampColor) 
    PHP_FE(glBeginConditionalRender, arginfo_glBeginConditionalRender) 
    PHP_FE(glEndConditionalRender, arginfo_glEndConditionalRender) 
    PHP_FE(glVertexAttribIPointer, arginfo_glVertexAttribIPointer) 
    PHP_FE(glGetVertexAttribIiv, arginfo_glGetVertexAttribIiv) 
    PHP_FE(glGetVertexAttribIuiv, arginfo_glGetVertexAttribIuiv) 
    PHP_FE(glVertexAttribI1i, arginfo_glVertexAttribI1i) 
    PHP_FE(glVertexAttribI2i, arginfo_glVertexAttribI2i) 
    PHP_FE(glVertexAttribI3i, arginfo_glVertexAttribI3i) 
    PHP_FE(glVertexAttribI4i, arginfo_glVertexAttribI4i) 
    PHP_FE(glVertexAttribI1ui, arginfo_glVertexAttribI1ui) 
    PHP_FE(glVertexAttribI2ui, arginfo_glVertexAttribI2ui) 
    PHP_FE(glVertexAttribI3ui, arginfo_glVertexAttribI3ui) 
    PHP_FE(glVertexAttribI4ui, arginfo_glVertexAttribI4ui) 
    PHP_FE(glVertexAttribI1iv, arginfo_glVertexAttribI1iv) 
    PHP_FE(glVertexAttribI2iv, arginfo_glVertexAttribI2iv) 
    PHP_FE(glVertexAttribI3iv, arginfo_glVertexAttribI3iv) 
    PHP_FE(glVertexAttribI4iv, arginfo_glVertexAttribI4iv) 
    PHP_FE(glVertexAttribI1uiv, arginfo_glVertexAttribI1uiv) 
    PHP_FE(glVertexAttribI2uiv, arginfo_glVertexAttribI2uiv) 
    PHP_FE(glVertexAttribI3uiv, arginfo_glVertexAttribI3uiv) 
    PHP_FE(glVertexAttribI4uiv, arginfo_glVertexAttribI4uiv) 
    PHP_FE(glVertexAttribI4bv, arginfo_glVertexAttribI4bv) 
    PHP_FE(glVertexAttribI4sv, arginfo_glVertexAttribI4sv) 
    PHP_FE(glVertexAttribI4ubv, arginfo_glVertexAttribI4ubv) 
    PHP_FE(glVertexAttribI4usv, arginfo_glVertexAttribI4usv) 
    PHP_FE(glGetUniformuiv, arginfo_glGetUniformuiv) 
    PHP_FE(glBindFragDataLocation, arginfo_glBindFragDataLocation) 
    PHP_FE(glGetFragDataLocation, arginfo_glGetFragDataLocation) 
    PHP_FE(glUniform1ui, arginfo_glUniform1ui) 
    PHP_FE(glUniform2ui, arginfo_glUniform2ui) 
    PHP_FE(glUniform3ui, arginfo_glUniform3ui) 
    PHP_FE(glUniform4ui, arginfo_glUniform4ui) 
    PHP_FE(glUniform1uiv, arginfo_glUniform1uiv) 
    PHP_FE(glUniform2uiv, arginfo_glUniform2uiv) 
    PHP_FE(glUniform3uiv, arginfo_glUniform3uiv) 
    PHP_FE(glUniform4uiv, arginfo_glUniform4uiv) 
    PHP_FE(glTexParameterIiv, arginfo_glTexParameterIiv) 
    PHP_FE(glTexParameterIuiv, arginfo_glTexParameterIuiv) 
    PHP_FE(glGetTexParameterIiv, arginfo_glGetTexParameterIiv) 
    PHP_FE(glGetTexParameterIuiv, arginfo_glGetTexParameterIuiv) 
    PHP_FE(glClearBufferiv, arginfo_glClearBufferiv) 
    PHP_FE(glClearBufferuiv, arginfo_glClearBufferuiv) 
    PHP_FE(glClearBufferfv, arginfo_glClearBufferfv) 
    PHP_FE(glClearBufferfi, arginfo_glClearBufferfi) 
    PHP_FE(glGetStringi, arginfo_glGetStringi) 
    PHP_FE(glDrawArraysInstanced, arginfo_glDrawArraysInstanced) 
    PHP_FE(glDrawElementsInstanced, arginfo_glDrawElementsInstanced) 
    PHP_FE(glTexBuffer, arginfo_glTexBuffer) 
    PHP_FE(glPrimitiveRestartIndex, arginfo_glPrimitiveRestartIndex) 
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
