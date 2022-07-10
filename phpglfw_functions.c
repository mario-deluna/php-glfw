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
 * ----------------------------------------------------------------------------
 * PHPGlfw IPOs 
 * ----------------------------------------------------------------------------
 * IPOs (internal pointer object) is a simple PHP object which is attached to 
 * a resource pointer in the extension like a "GLFWwindow" etc...
 */

void phpglfw_register_ipos(void)
{
    phpglfw_glfwwindow_object_minit_helper(); 
    phpglfw_glfwmonitor_object_minit_helper(); 
    phpglfw_glfwcursor_object_minit_helper(); 
}

/**
 * Class entries
 */
zend_class_entry *phpglfw_glfwwindow_ce; 
zend_class_entry *phpglfw_glfwmonitor_ce; 
zend_class_entry *phpglfw_glfwcursor_ce; 

/**
 * Structs
 */
typedef struct _phpglfw_glfwwindow_object {
    GLFWwindow* glfwwindow;
    zend_object std;
} phpglfw_glfwwindow_object; 

typedef struct _phpglfw_glfwmonitor_object {
    GLFWmonitor* glfwmonitor;
    zend_object std;
} phpglfw_glfwmonitor_object; 

typedef struct _phpglfw_glfwcursor_object {
    GLFWcursor* glfwcursor;
    zend_object std;
} phpglfw_glfwcursor_object; 


/**
 * GLFWwindow aka (GLFWwindow*) 
 * object handlers, initializers, helpers etc..
 */
static zend_object_handlers phpglfw_glfwwindow_object_handlers;
static const zend_function_entry phpglfw_glfwwindow_class_methods[] = {
    ZEND_FE_END
};

static zend_always_inline phpglfw_glfwwindow_object* phpglfw_glfwwindow_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_glfwwindow_object *) ((char *) (obj) - XtOffsetOf(phpglfw_glfwwindow_object, std));
}

static zend_function *phpglfw_glfwwindow_class_constructor(zend_object *object)
{
    zend_throw_error(NULL, "You cannot initialize a GLFWwindow object except through helper functions");
    return NULL;
}

static zend_class_entry *phpglfw_glfwwindow_class_register(void)
{
    zend_class_entry ce, *class_entry;

    INIT_CLASS_ENTRY(ce, "GLFWwindow", phpglfw_glfwwindow_class_methods);
    class_entry = zend_register_internal_class_ex(&ce, NULL);
    class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;

    return class_entry;
}

zend_object *phpglfw_glfwwindow_object_create(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_glfwwindow_object) + zend_object_properties_size(class_type);
    phpglfw_glfwwindow_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_glfwwindow_object_handlers;

    return &intern->std;
}

static void phpglfw_glfwwindow_object_free(zend_object *intern)
{
    phpglfw_glfwwindow_object *obj_ptr = phpglfw_glfwwindow_objectptr_from_zobj_p(intern);
    if (obj_ptr->glfwwindow) {
        glfwDestroyWindow(obj_ptr->glfwwindow); 
    }
    zend_object_std_dtor(intern);
}

void phpglfw_glfwwindow_ptr_assign_to_zval_p(zval *val, GLFWwindow* glfwwindow)
{
    object_init_ex(val, phpglfw_glfwwindow_ce);
    phpglfw_glfwwindow_objectptr_from_zobj_p(Z_OBJ_P(val))->glfwwindow = glfwwindow;
}

void phpglfw_glfwwindow_object_minit_helper(void)
{
    phpglfw_glfwwindow_ce = phpglfw_glfwwindow_class_register();
    phpglfw_glfwwindow_ce->create_object = phpglfw_glfwwindow_object_create;

    memcpy(&phpglfw_glfwwindow_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_glfwwindow_object_handlers.clone_obj = NULL;
    phpglfw_glfwwindow_object_handlers.free_obj = phpglfw_glfwwindow_object_free;
    phpglfw_glfwwindow_object_handlers.get_constructor = phpglfw_glfwwindow_class_constructor;
    phpglfw_glfwwindow_object_handlers.compare = zend_objects_not_comparable;
    phpglfw_glfwwindow_object_handlers.offset = XtOffsetOf(phpglfw_glfwwindow_object, std);
}

GLFWwindow* phpglfw_glfwwindowptr_from_zval_ptr(zval* zp)
{
    return phpglfw_glfwwindow_objectptr_from_zobj_p(Z_OBJ_P(zp))->glfwwindow;
}

/**
 * GLFWmonitor aka (GLFWmonitor*) 
 * object handlers, initializers, helpers etc..
 */
static zend_object_handlers phpglfw_glfwmonitor_object_handlers;
static const zend_function_entry phpglfw_glfwmonitor_class_methods[] = {
    ZEND_FE_END
};

static zend_always_inline phpglfw_glfwmonitor_object* phpglfw_glfwmonitor_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_glfwmonitor_object *) ((char *) (obj) - XtOffsetOf(phpglfw_glfwmonitor_object, std));
}

static zend_function *phpglfw_glfwmonitor_class_constructor(zend_object *object)
{
    zend_throw_error(NULL, "You cannot initialize a GLFWmonitor object except through helper functions");
    return NULL;
}

static zend_class_entry *phpglfw_glfwmonitor_class_register(void)
{
    zend_class_entry ce, *class_entry;

    INIT_CLASS_ENTRY(ce, "GLFWmonitor", phpglfw_glfwmonitor_class_methods);
    class_entry = zend_register_internal_class_ex(&ce, NULL);
    class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;

    return class_entry;
}

zend_object *phpglfw_glfwmonitor_object_create(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_glfwmonitor_object) + zend_object_properties_size(class_type);
    phpglfw_glfwmonitor_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_glfwmonitor_object_handlers;

    return &intern->std;
}

static void phpglfw_glfwmonitor_object_free(zend_object *intern)
{
    phpglfw_glfwmonitor_object *obj_ptr = phpglfw_glfwmonitor_objectptr_from_zobj_p(intern);
    if (obj_ptr->glfwmonitor) {
         
    }
    zend_object_std_dtor(intern);
}

void phpglfw_glfwmonitor_ptr_assign_to_zval_p(zval *val, GLFWmonitor* glfwmonitor)
{
    object_init_ex(val, phpglfw_glfwmonitor_ce);
    phpglfw_glfwmonitor_objectptr_from_zobj_p(Z_OBJ_P(val))->glfwmonitor = glfwmonitor;
}

void phpglfw_glfwmonitor_object_minit_helper(void)
{
    phpglfw_glfwmonitor_ce = phpglfw_glfwmonitor_class_register();
    phpglfw_glfwmonitor_ce->create_object = phpglfw_glfwmonitor_object_create;

    memcpy(&phpglfw_glfwmonitor_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_glfwmonitor_object_handlers.clone_obj = NULL;
    phpglfw_glfwmonitor_object_handlers.free_obj = phpglfw_glfwmonitor_object_free;
    phpglfw_glfwmonitor_object_handlers.get_constructor = phpglfw_glfwmonitor_class_constructor;
    phpglfw_glfwmonitor_object_handlers.compare = zend_objects_not_comparable;
    phpglfw_glfwmonitor_object_handlers.offset = XtOffsetOf(phpglfw_glfwmonitor_object, std);
}

GLFWmonitor* phpglfw_glfwmonitorptr_from_zval_ptr(zval* zp)
{
    return phpglfw_glfwmonitor_objectptr_from_zobj_p(Z_OBJ_P(zp))->glfwmonitor;
}

/**
 * GLFWcursor aka (GLFWcursor*) 
 * object handlers, initializers, helpers etc..
 */
static zend_object_handlers phpglfw_glfwcursor_object_handlers;
static const zend_function_entry phpglfw_glfwcursor_class_methods[] = {
    ZEND_FE_END
};

static zend_always_inline phpglfw_glfwcursor_object* phpglfw_glfwcursor_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_glfwcursor_object *) ((char *) (obj) - XtOffsetOf(phpglfw_glfwcursor_object, std));
}

static zend_function *phpglfw_glfwcursor_class_constructor(zend_object *object)
{
    zend_throw_error(NULL, "You cannot initialize a GLFWcursor object except through helper functions");
    return NULL;
}

static zend_class_entry *phpglfw_glfwcursor_class_register(void)
{
    zend_class_entry ce, *class_entry;

    INIT_CLASS_ENTRY(ce, "GLFWcursor", phpglfw_glfwcursor_class_methods);
    class_entry = zend_register_internal_class_ex(&ce, NULL);
    class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;

    return class_entry;
}

zend_object *phpglfw_glfwcursor_object_create(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_glfwcursor_object) + zend_object_properties_size(class_type);
    phpglfw_glfwcursor_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_glfwcursor_object_handlers;

    return &intern->std;
}

static void phpglfw_glfwcursor_object_free(zend_object *intern)
{
    phpglfw_glfwcursor_object *obj_ptr = phpglfw_glfwcursor_objectptr_from_zobj_p(intern);
    if (obj_ptr->glfwcursor) {
        glfwDestroyCursor(obj_ptr->glfwcursor); 
    }
    zend_object_std_dtor(intern);
}

void phpglfw_glfwcursor_ptr_assign_to_zval_p(zval *val, GLFWcursor* glfwcursor)
{
    object_init_ex(val, phpglfw_glfwcursor_ce);
    phpglfw_glfwcursor_objectptr_from_zobj_p(Z_OBJ_P(val))->glfwcursor = glfwcursor;
}

void phpglfw_glfwcursor_object_minit_helper(void)
{
    phpglfw_glfwcursor_ce = phpglfw_glfwcursor_class_register();
    phpglfw_glfwcursor_ce->create_object = phpglfw_glfwcursor_object_create;

    memcpy(&phpglfw_glfwcursor_object_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_glfwcursor_object_handlers.clone_obj = NULL;
    phpglfw_glfwcursor_object_handlers.free_obj = phpglfw_glfwcursor_object_free;
    phpglfw_glfwcursor_object_handlers.get_constructor = phpglfw_glfwcursor_class_constructor;
    phpglfw_glfwcursor_object_handlers.compare = zend_objects_not_comparable;
    phpglfw_glfwcursor_object_handlers.offset = XtOffsetOf(phpglfw_glfwcursor_object, std);
}

GLFWcursor* phpglfw_glfwcursorptr_from_zval_ptr(zval* zp)
{
    return phpglfw_glfwcursor_objectptr_from_zobj_p(Z_OBJ_P(zp))->glfwcursor;
}


/**
 * ----------------------------------------------------------------------------
 * PHPGlfw Functions 
 * ----------------------------------------------------------------------------
 * All the functions wrapped by the extension.
 */
/**
 * glCullFace
 */ 
PHP_FUNCTION(glCullFace)
{
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &mode) == FAILURE) {
        return;
    }
    glCullFace(mode);
} 

/**
 * glFrontFace
 */ 
PHP_FUNCTION(glFrontFace)
{
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &mode) == FAILURE) {
        return;
    }
    glFrontFace(mode);
} 

/**
 * glHint
 */ 
PHP_FUNCTION(glHint)
{
    zend_long target;
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &mode) == FAILURE) {
        return;
    }
    glHint(target, mode);
} 

/**
 * glLineWidth
 */ 
PHP_FUNCTION(glLineWidth)
{
    double width;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &width) == FAILURE) {
        return;
    }
    glLineWidth(width);
} 

/**
 * glPointSize
 */ 
PHP_FUNCTION(glPointSize)
{
    double size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &size) == FAILURE) {
        return;
    }
    glPointSize(size);
} 

/**
 * glPolygonMode
 */ 
PHP_FUNCTION(glPolygonMode)
{
    zend_long face;
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &face, &mode) == FAILURE) {
        return;
    }
    glPolygonMode(face, mode);
} 

/**
 * glScissor
 */ 
PHP_FUNCTION(glScissor)
{
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &x, &y, &width, &height) == FAILURE) {
        return;
    }
    glScissor(x, y, width, height);
} 

/**
 * glTexParameterf
 */ 
PHP_FUNCTION(glTexParameterf)
{
    zend_long target;
    zend_long pname;
    double param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lld", &target, &pname, &param) == FAILURE) {
        return;
    }
    glTexParameterf(target, pname, param);
} 

/**
 * glTexParameteri
 */ 
PHP_FUNCTION(glTexParameteri)
{
    zend_long target;
    zend_long pname;
    zend_long param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &target, &pname, &param) == FAILURE) {
        return;
    }
    glTexParameteri(target, pname, param);
} 

/**
 * glDrawBuffer
 */ 
PHP_FUNCTION(glDrawBuffer)
{
    zend_long buf;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &buf) == FAILURE) {
        return;
    }
    glDrawBuffer(buf);
} 

/**
 * glClear
 */ 
PHP_FUNCTION(glClear)
{
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &mask) == FAILURE) {
        return;
    }
    glClear(mask);
} 

/**
 * glClearColor
 */ 
PHP_FUNCTION(glClearColor)
{
    double red;
    double green;
    double blue;
    double alpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &red, &green, &blue, &alpha) == FAILURE) {
        return;
    }
    glClearColor(red, green, blue, alpha);
} 

/**
 * glClearStencil
 */ 
PHP_FUNCTION(glClearStencil)
{
    zend_long s;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &s) == FAILURE) {
        return;
    }
    glClearStencil(s);
} 

/**
 * glClearDepth
 */ 
PHP_FUNCTION(glClearDepth)
{
    double depth;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &depth) == FAILURE) {
        return;
    }
    glClearDepth(depth);
} 

/**
 * glStencilMask
 */ 
PHP_FUNCTION(glStencilMask)
{
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &mask) == FAILURE) {
        return;
    }
    glStencilMask(mask);
} 

/**
 * glColorMask
 */ 
PHP_FUNCTION(glColorMask)
{
    bool red;
    bool green;
    bool blue;
    bool alpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "bbbb", &red, &green, &blue, &alpha) == FAILURE) {
        return;
    }
    glColorMask(red, green, blue, alpha);
} 

/**
 * glDepthMask
 */ 
PHP_FUNCTION(glDepthMask)
{
    bool flag;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "b", &flag) == FAILURE) {
        return;
    }
    glDepthMask(flag);
} 

/**
 * glDisable
 */ 
PHP_FUNCTION(glDisable)
{
    zend_long cap;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &cap) == FAILURE) {
        return;
    }
    glDisable(cap);
} 

/**
 * glEnable
 */ 
PHP_FUNCTION(glEnable)
{
    zend_long cap;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &cap) == FAILURE) {
        return;
    }
    glEnable(cap);
} 

/**
 * glFinish
 */ 
PHP_FUNCTION(glFinish)
{
    glFinish();
} 

/**
 * glFlush
 */ 
PHP_FUNCTION(glFlush)
{
    glFlush();
} 

/**
 * glBlendFunc
 */ 
PHP_FUNCTION(glBlendFunc)
{
    zend_long sfactor;
    zend_long dfactor;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &sfactor, &dfactor) == FAILURE) {
        return;
    }
    glBlendFunc(sfactor, dfactor);
} 

/**
 * glLogicOp
 */ 
PHP_FUNCTION(glLogicOp)
{
    zend_long opcode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &opcode) == FAILURE) {
        return;
    }
    glLogicOp(opcode);
} 

/**
 * glStencilFunc
 */ 
PHP_FUNCTION(glStencilFunc)
{
    zend_long func;
    zend_long ref;
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &func, &ref, &mask) == FAILURE) {
        return;
    }
    glStencilFunc(func, ref, mask);
} 

/**
 * glStencilOp
 */ 
PHP_FUNCTION(glStencilOp)
{
    zend_long fail;
    zend_long zfail;
    zend_long zpass;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &fail, &zfail, &zpass) == FAILURE) {
        return;
    }
    glStencilOp(fail, zfail, zpass);
} 

/**
 * glDepthFunc
 */ 
PHP_FUNCTION(glDepthFunc)
{
    zend_long func;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &func) == FAILURE) {
        return;
    }
    glDepthFunc(func);
} 

/**
 * glPixelStoref
 */ 
PHP_FUNCTION(glPixelStoref)
{
    zend_long pname;
    double param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &pname, &param) == FAILURE) {
        return;
    }
    glPixelStoref(pname, param);
} 

/**
 * glPixelStorei
 */ 
PHP_FUNCTION(glPixelStorei)
{
    zend_long pname;
    zend_long param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &pname, &param) == FAILURE) {
        return;
    }
    glPixelStorei(pname, param);
} 

/**
 * glReadBuffer
 */ 
PHP_FUNCTION(glReadBuffer)
{
    zend_long src;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &src) == FAILURE) {
        return;
    }
    glReadBuffer(src);
} 

/**
 * glGetError
 */ 
PHP_FUNCTION(glGetError)
{
    RETURN_LONG(glGetError());
} 

/**
 * glIsEnabled
 */ 
PHP_FUNCTION(glIsEnabled)
{
    zend_long cap;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &cap) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsEnabled(cap));
} 

/**
 * glDepthRange
 */ 
PHP_FUNCTION(glDepthRange)
{
    double n;
    double f;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dd", &n, &f) == FAILURE) {
        return;
    }
    glDepthRange(n, f);
} 

/**
 * glViewport
 */ 
PHP_FUNCTION(glViewport)
{
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &x, &y, &width, &height) == FAILURE) {
        return;
    }
    glViewport(x, y, width, height);
} 

/**
 * glDrawArrays
 */ 
PHP_FUNCTION(glDrawArrays)
{
    zend_long mode;
    zend_long first;
    zend_long count;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &mode, &first, &count) == FAILURE) {
        return;
    }
    glDrawArrays(mode, first, count);
} 

/**
 * glPolygonOffset
 */ 
PHP_FUNCTION(glPolygonOffset)
{
    double factor;
    double units;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dd", &factor, &units) == FAILURE) {
        return;
    }
    glPolygonOffset(factor, units);
} 

/**
 * glCopyTexImage1D
 */ 
PHP_FUNCTION(glCopyTexImage1D)
{
    zend_long target;
    zend_long level;
    zend_long internalformat;
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long border;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllllll", &target, &level, &internalformat, &x, &y, &width, &border) == FAILURE) {
        return;
    }
    glCopyTexImage1D(target, level, internalformat, x, y, width, border);
} 

/**
 * glCopyTexImage2D
 */ 
PHP_FUNCTION(glCopyTexImage2D)
{
    zend_long target;
    zend_long level;
    zend_long internalformat;
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;
    zend_long border;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllllll", &target, &level, &internalformat, &x, &y, &width, &height, &border) == FAILURE) {
        return;
    }
    glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
} 

/**
 * glCopyTexSubImage1D
 */ 
PHP_FUNCTION(glCopyTexSubImage1D)
{
    zend_long target;
    zend_long level;
    zend_long xoffset;
    zend_long x;
    zend_long y;
    zend_long width;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllll", &target, &level, &xoffset, &x, &y, &width) == FAILURE) {
        return;
    }
    glCopyTexSubImage1D(target, level, xoffset, x, y, width);
} 

/**
 * glCopyTexSubImage2D
 */ 
PHP_FUNCTION(glCopyTexSubImage2D)
{
    zend_long target;
    zend_long level;
    zend_long xoffset;
    zend_long yoffset;
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllllll", &target, &level, &xoffset, &yoffset, &x, &y, &width, &height) == FAILURE) {
        return;
    }
    glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
} 

/**
 * glBindTexture
 */ 
PHP_FUNCTION(glBindTexture)
{
    zend_long target;
    zend_long texture;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &texture) == FAILURE) {
        return;
    }
    glBindTexture(target, texture);
} 

/**
 * glIsTexture
 */ 
PHP_FUNCTION(glIsTexture)
{
    zend_long texture;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &texture) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsTexture(texture));
} 

/**
 * glCopyTexSubImage3D
 */ 
PHP_FUNCTION(glCopyTexSubImage3D)
{
    zend_long target;
    zend_long level;
    zend_long xoffset;
    zend_long yoffset;
    zend_long zoffset;
    zend_long x;
    zend_long y;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllllllll", &target, &level, &xoffset, &yoffset, &zoffset, &x, &y, &width, &height) == FAILURE) {
        return;
    }
    glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
} 

/**
 * glActiveTexture
 */ 
PHP_FUNCTION(glActiveTexture)
{
    zend_long texture;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &texture) == FAILURE) {
        return;
    }
    glActiveTexture(texture);
} 

/**
 * glSampleCoverage
 */ 
PHP_FUNCTION(glSampleCoverage)
{
    double value;
    bool invert;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "db", &value, &invert) == FAILURE) {
        return;
    }
    glSampleCoverage(value, invert);
} 

/**
 * glBlendFuncSeparate
 */ 
PHP_FUNCTION(glBlendFuncSeparate)
{
    zend_long sfactorRGB;
    zend_long dfactorRGB;
    zend_long sfactorAlpha;
    zend_long dfactorAlpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &sfactorRGB, &dfactorRGB, &sfactorAlpha, &dfactorAlpha) == FAILURE) {
        return;
    }
    glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
} 

/**
 * glPointParameterf
 */ 
PHP_FUNCTION(glPointParameterf)
{
    zend_long pname;
    double param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &pname, &param) == FAILURE) {
        return;
    }
    glPointParameterf(pname, param);
} 

/**
 * glPointParameteri
 */ 
PHP_FUNCTION(glPointParameteri)
{
    zend_long pname;
    zend_long param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &pname, &param) == FAILURE) {
        return;
    }
    glPointParameteri(pname, param);
} 

/**
 * glBlendColor
 */ 
PHP_FUNCTION(glBlendColor)
{
    double red;
    double green;
    double blue;
    double alpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddd", &red, &green, &blue, &alpha) == FAILURE) {
        return;
    }
    glBlendColor(red, green, blue, alpha);
} 

/**
 * glBlendEquation
 */ 
PHP_FUNCTION(glBlendEquation)
{
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &mode) == FAILURE) {
        return;
    }
    glBlendEquation(mode);
} 

/**
 * glIsQuery
 */ 
PHP_FUNCTION(glIsQuery)
{
    zend_long id;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &id) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsQuery(id));
} 

/**
 * glBeginQuery
 */ 
PHP_FUNCTION(glBeginQuery)
{
    zend_long target;
    zend_long id;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &id) == FAILURE) {
        return;
    }
    glBeginQuery(target, id);
} 

/**
 * glEndQuery
 */ 
PHP_FUNCTION(glEndQuery)
{
    zend_long target;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &target) == FAILURE) {
        return;
    }
    glEndQuery(target);
} 

/**
 * glBindBuffer
 */ 
PHP_FUNCTION(glBindBuffer)
{
    zend_long target;
    zend_long buffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &buffer) == FAILURE) {
        return;
    }
    glBindBuffer(target, buffer);
} 

/**
 * glIsBuffer
 */ 
PHP_FUNCTION(glIsBuffer)
{
    zend_long buffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &buffer) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsBuffer(buffer));
} 

/**
 * glUnmapBuffer
 */ 
PHP_FUNCTION(glUnmapBuffer)
{
    zend_long target;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &target) == FAILURE) {
        return;
    }
    RETURN_BOOL(glUnmapBuffer(target));
} 

/**
 * glBlendEquationSeparate
 */ 
PHP_FUNCTION(glBlendEquationSeparate)
{
    zend_long modeRGB;
    zend_long modeAlpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &modeRGB, &modeAlpha) == FAILURE) {
        return;
    }
    glBlendEquationSeparate(modeRGB, modeAlpha);
} 

/**
 * glStencilOpSeparate
 */ 
PHP_FUNCTION(glStencilOpSeparate)
{
    zend_long face;
    zend_long sfail;
    zend_long dpfail;
    zend_long dppass;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &face, &sfail, &dpfail, &dppass) == FAILURE) {
        return;
    }
    glStencilOpSeparate(face, sfail, dpfail, dppass);
} 

/**
 * glStencilFuncSeparate
 */ 
PHP_FUNCTION(glStencilFuncSeparate)
{
    zend_long face;
    zend_long func;
    zend_long ref;
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &face, &func, &ref, &mask) == FAILURE) {
        return;
    }
    glStencilFuncSeparate(face, func, ref, mask);
} 

/**
 * glStencilMaskSeparate
 */ 
PHP_FUNCTION(glStencilMaskSeparate)
{
    zend_long face;
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &face, &mask) == FAILURE) {
        return;
    }
    glStencilMaskSeparate(face, mask);
} 

/**
 * glAttachShader
 */ 
PHP_FUNCTION(glAttachShader)
{
    zend_long program;
    zend_long shader;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &program, &shader) == FAILURE) {
        return;
    }
    glAttachShader(program, shader);
} 

/**
 * glBindAttribLocation
 */ 
PHP_FUNCTION(glBindAttribLocation)
{
    zend_long program;
    zend_long index;
    const char *name;
    size_t name_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lls", &program, &index, &name, &name_size) == FAILURE) {
        return;
    }
    glBindAttribLocation(program, index, name);
} 

/**
 * glCompileShader
 */ 
PHP_FUNCTION(glCompileShader)
{
    zend_long shader;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &shader) == FAILURE) {
        return;
    }
    glCompileShader(shader);
} 

/**
 * glCreateProgram
 */ 
PHP_FUNCTION(glCreateProgram)
{
    RETURN_LONG(glCreateProgram());
} 

/**
 * glCreateShader
 */ 
PHP_FUNCTION(glCreateShader)
{
    zend_long type;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &type) == FAILURE) {
        return;
    }
    RETURN_LONG(glCreateShader(type));
} 

/**
 * glDeleteProgram
 */ 
PHP_FUNCTION(glDeleteProgram)
{
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &program) == FAILURE) {
        return;
    }
    glDeleteProgram(program);
} 

/**
 * glDeleteShader
 */ 
PHP_FUNCTION(glDeleteShader)
{
    zend_long shader;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &shader) == FAILURE) {
        return;
    }
    glDeleteShader(shader);
} 

/**
 * glDetachShader
 */ 
PHP_FUNCTION(glDetachShader)
{
    zend_long program;
    zend_long shader;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &program, &shader) == FAILURE) {
        return;
    }
    glDetachShader(program, shader);
} 

/**
 * glDisableVertexAttribArray
 */ 
PHP_FUNCTION(glDisableVertexAttribArray)
{
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &index) == FAILURE) {
        return;
    }
    glDisableVertexAttribArray(index);
} 

/**
 * glEnableVertexAttribArray
 */ 
PHP_FUNCTION(glEnableVertexAttribArray)
{
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &index) == FAILURE) {
        return;
    }
    glEnableVertexAttribArray(index);
} 

/**
 * glGetAttribLocation
 */ 
PHP_FUNCTION(glGetAttribLocation)
{
    zend_long program;
    const char *name;
    size_t name_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ls", &program, &name, &name_size) == FAILURE) {
        return;
    }
    RETURN_LONG(glGetAttribLocation(program, name));
} 

/**
 * glGetUniformLocation
 */ 
PHP_FUNCTION(glGetUniformLocation)
{
    zend_long program;
    const char *name;
    size_t name_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ls", &program, &name, &name_size) == FAILURE) {
        return;
    }
    RETURN_LONG(glGetUniformLocation(program, name));
} 

/**
 * glIsProgram
 */ 
PHP_FUNCTION(glIsProgram)
{
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &program) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsProgram(program));
} 

/**
 * glIsShader
 */ 
PHP_FUNCTION(glIsShader)
{
    zend_long shader;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &shader) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsShader(shader));
} 

/**
 * glLinkProgram
 */ 
PHP_FUNCTION(glLinkProgram)
{
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &program) == FAILURE) {
        return;
    }
    glLinkProgram(program);
} 

/**
 * glUseProgram
 */ 
PHP_FUNCTION(glUseProgram)
{
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &program) == FAILURE) {
        return;
    }
    glUseProgram(program);
} 

/**
 * glUniform1f
 */ 
PHP_FUNCTION(glUniform1f)
{
    zend_long location;
    double v0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &location, &v0) == FAILURE) {
        return;
    }
    glUniform1f(location, v0);
} 

/**
 * glUniform2f
 */ 
PHP_FUNCTION(glUniform2f)
{
    zend_long location;
    double v0;
    double v1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldd", &location, &v0, &v1) == FAILURE) {
        return;
    }
    glUniform2f(location, v0, v1);
} 

/**
 * glUniform3f
 */ 
PHP_FUNCTION(glUniform3f)
{
    zend_long location;
    double v0;
    double v1;
    double v2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lddd", &location, &v0, &v1, &v2) == FAILURE) {
        return;
    }
    glUniform3f(location, v0, v1, v2);
} 

/**
 * glUniform4f
 */ 
PHP_FUNCTION(glUniform4f)
{
    zend_long location;
    double v0;
    double v1;
    double v2;
    double v3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldddd", &location, &v0, &v1, &v2, &v3) == FAILURE) {
        return;
    }
    glUniform4f(location, v0, v1, v2, v3);
} 

/**
 * glUniform1i
 */ 
PHP_FUNCTION(glUniform1i)
{
    zend_long location;
    zend_long v0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &location, &v0) == FAILURE) {
        return;
    }
    glUniform1i(location, v0);
} 

/**
 * glUniform2i
 */ 
PHP_FUNCTION(glUniform2i)
{
    zend_long location;
    zend_long v0;
    zend_long v1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &location, &v0, &v1) == FAILURE) {
        return;
    }
    glUniform2i(location, v0, v1);
} 

/**
 * glUniform3i
 */ 
PHP_FUNCTION(glUniform3i)
{
    zend_long location;
    zend_long v0;
    zend_long v1;
    zend_long v2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &location, &v0, &v1, &v2) == FAILURE) {
        return;
    }
    glUniform3i(location, v0, v1, v2);
} 

/**
 * glUniform4i
 */ 
PHP_FUNCTION(glUniform4i)
{
    zend_long location;
    zend_long v0;
    zend_long v1;
    zend_long v2;
    zend_long v3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &location, &v0, &v1, &v2, &v3) == FAILURE) {
        return;
    }
    glUniform4i(location, v0, v1, v2, v3);
} 

/**
 * glValidateProgram
 */ 
PHP_FUNCTION(glValidateProgram)
{
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &program) == FAILURE) {
        return;
    }
    glValidateProgram(program);
} 

/**
 * glVertexAttrib1d
 */ 
PHP_FUNCTION(glVertexAttrib1d)
{
    zend_long index;
    double x;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &index, &x) == FAILURE) {
        return;
    }
    glVertexAttrib1d(index, x);
} 

/**
 * glVertexAttrib1f
 */ 
PHP_FUNCTION(glVertexAttrib1f)
{
    zend_long index;
    double x;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &index, &x) == FAILURE) {
        return;
    }
    glVertexAttrib1f(index, x);
} 

/**
 * glVertexAttrib1s
 */ 
PHP_FUNCTION(glVertexAttrib1s)
{
    zend_long index;
    zend_long x;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &index, &x) == FAILURE) {
        return;
    }
    glVertexAttrib1s(index, x);
} 

/**
 * glVertexAttrib2d
 */ 
PHP_FUNCTION(glVertexAttrib2d)
{
    zend_long index;
    double x;
    double y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldd", &index, &x, &y) == FAILURE) {
        return;
    }
    glVertexAttrib2d(index, x, y);
} 

/**
 * glVertexAttrib2f
 */ 
PHP_FUNCTION(glVertexAttrib2f)
{
    zend_long index;
    double x;
    double y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldd", &index, &x, &y) == FAILURE) {
        return;
    }
    glVertexAttrib2f(index, x, y);
} 

/**
 * glVertexAttrib2s
 */ 
PHP_FUNCTION(glVertexAttrib2s)
{
    zend_long index;
    zend_long x;
    zend_long y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &index, &x, &y) == FAILURE) {
        return;
    }
    glVertexAttrib2s(index, x, y);
} 

/**
 * glVertexAttrib3d
 */ 
PHP_FUNCTION(glVertexAttrib3d)
{
    zend_long index;
    double x;
    double y;
    double z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lddd", &index, &x, &y, &z) == FAILURE) {
        return;
    }
    glVertexAttrib3d(index, x, y, z);
} 

/**
 * glVertexAttrib3f
 */ 
PHP_FUNCTION(glVertexAttrib3f)
{
    zend_long index;
    double x;
    double y;
    double z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lddd", &index, &x, &y, &z) == FAILURE) {
        return;
    }
    glVertexAttrib3f(index, x, y, z);
} 

/**
 * glVertexAttrib3s
 */ 
PHP_FUNCTION(glVertexAttrib3s)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &index, &x, &y, &z) == FAILURE) {
        return;
    }
    glVertexAttrib3s(index, x, y, z);
} 

/**
 * glVertexAttrib4Nub
 */ 
PHP_FUNCTION(glVertexAttrib4Nub)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    zend_long w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &index, &x, &y, &z, &w) == FAILURE) {
        return;
    }
    glVertexAttrib4Nub(index, x, y, z, w);
} 

/**
 * glVertexAttrib4d
 */ 
PHP_FUNCTION(glVertexAttrib4d)
{
    zend_long index;
    double x;
    double y;
    double z;
    double w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldddd", &index, &x, &y, &z, &w) == FAILURE) {
        return;
    }
    glVertexAttrib4d(index, x, y, z, w);
} 

/**
 * glVertexAttrib4f
 */ 
PHP_FUNCTION(glVertexAttrib4f)
{
    zend_long index;
    double x;
    double y;
    double z;
    double w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldddd", &index, &x, &y, &z, &w) == FAILURE) {
        return;
    }
    glVertexAttrib4f(index, x, y, z, w);
} 

/**
 * glVertexAttrib4s
 */ 
PHP_FUNCTION(glVertexAttrib4s)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    zend_long w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &index, &x, &y, &z, &w) == FAILURE) {
        return;
    }
    glVertexAttrib4s(index, x, y, z, w);
} 

/**
 * glColorMaski
 */ 
PHP_FUNCTION(glColorMaski)
{
    zend_long index;
    bool r;
    bool g;
    bool b;
    bool a;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbbbb", &index, &r, &g, &b, &a) == FAILURE) {
        return;
    }
    glColorMaski(index, r, g, b, a);
} 

/**
 * glEnablei
 */ 
PHP_FUNCTION(glEnablei)
{
    zend_long target;
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &index) == FAILURE) {
        return;
    }
    glEnablei(target, index);
} 

/**
 * glDisablei
 */ 
PHP_FUNCTION(glDisablei)
{
    zend_long target;
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &index) == FAILURE) {
        return;
    }
    glDisablei(target, index);
} 

/**
 * glIsEnabledi
 */ 
PHP_FUNCTION(glIsEnabledi)
{
    zend_long target;
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &index) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsEnabledi(target, index));
} 

/**
 * glBeginTransformFeedback
 */ 
PHP_FUNCTION(glBeginTransformFeedback)
{
    zend_long primitiveMode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &primitiveMode) == FAILURE) {
        return;
    }
    glBeginTransformFeedback(primitiveMode);
} 

/**
 * glEndTransformFeedback
 */ 
PHP_FUNCTION(glEndTransformFeedback)
{
    glEndTransformFeedback();
} 

/**
 * glBindBufferRange
 */ 
PHP_FUNCTION(glBindBufferRange)
{
    zend_long target;
    zend_long index;
    zend_long buffer;
    zend_long offset;
    zend_long size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &target, &index, &buffer, &offset, &size) == FAILURE) {
        return;
    }
    glBindBufferRange(target, index, buffer, offset, size);
} 

/**
 * glBindBufferBase
 */ 
PHP_FUNCTION(glBindBufferBase)
{
    zend_long target;
    zend_long index;
    zend_long buffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &target, &index, &buffer) == FAILURE) {
        return;
    }
    glBindBufferBase(target, index, buffer);
} 

/**
 * glClampColor
 */ 
PHP_FUNCTION(glClampColor)
{
    zend_long target;
    zend_long clamp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &clamp) == FAILURE) {
        return;
    }
    glClampColor(target, clamp);
} 

/**
 * glBeginConditionalRender
 */ 
PHP_FUNCTION(glBeginConditionalRender)
{
    zend_long id;
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &id, &mode) == FAILURE) {
        return;
    }
    glBeginConditionalRender(id, mode);
} 

/**
 * glEndConditionalRender
 */ 
PHP_FUNCTION(glEndConditionalRender)
{
    glEndConditionalRender();
} 

/**
 * glVertexAttribI1i
 */ 
PHP_FUNCTION(glVertexAttribI1i)
{
    zend_long index;
    zend_long x;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &index, &x) == FAILURE) {
        return;
    }
    glVertexAttribI1i(index, x);
} 

/**
 * glVertexAttribI2i
 */ 
PHP_FUNCTION(glVertexAttribI2i)
{
    zend_long index;
    zend_long x;
    zend_long y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &index, &x, &y) == FAILURE) {
        return;
    }
    glVertexAttribI2i(index, x, y);
} 

/**
 * glVertexAttribI3i
 */ 
PHP_FUNCTION(glVertexAttribI3i)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &index, &x, &y, &z) == FAILURE) {
        return;
    }
    glVertexAttribI3i(index, x, y, z);
} 

/**
 * glVertexAttribI4i
 */ 
PHP_FUNCTION(glVertexAttribI4i)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    zend_long w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &index, &x, &y, &z, &w) == FAILURE) {
        return;
    }
    glVertexAttribI4i(index, x, y, z, w);
} 

/**
 * glVertexAttribI1ui
 */ 
PHP_FUNCTION(glVertexAttribI1ui)
{
    zend_long index;
    zend_long x;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &index, &x) == FAILURE) {
        return;
    }
    glVertexAttribI1ui(index, x);
} 

/**
 * glVertexAttribI2ui
 */ 
PHP_FUNCTION(glVertexAttribI2ui)
{
    zend_long index;
    zend_long x;
    zend_long y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &index, &x, &y) == FAILURE) {
        return;
    }
    glVertexAttribI2ui(index, x, y);
} 

/**
 * glVertexAttribI3ui
 */ 
PHP_FUNCTION(glVertexAttribI3ui)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &index, &x, &y, &z) == FAILURE) {
        return;
    }
    glVertexAttribI3ui(index, x, y, z);
} 

/**
 * glVertexAttribI4ui
 */ 
PHP_FUNCTION(glVertexAttribI4ui)
{
    zend_long index;
    zend_long x;
    zend_long y;
    zend_long z;
    zend_long w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &index, &x, &y, &z, &w) == FAILURE) {
        return;
    }
    glVertexAttribI4ui(index, x, y, z, w);
} 

/**
 * glBindFragDataLocation
 */ 
PHP_FUNCTION(glBindFragDataLocation)
{
    zend_long program;
    zend_long color;
    const char *name;
    size_t name_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lls", &program, &color, &name, &name_size) == FAILURE) {
        return;
    }
    glBindFragDataLocation(program, color, name);
} 

/**
 * glGetFragDataLocation
 */ 
PHP_FUNCTION(glGetFragDataLocation)
{
    zend_long program;
    const char *name;
    size_t name_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ls", &program, &name, &name_size) == FAILURE) {
        return;
    }
    RETURN_LONG(glGetFragDataLocation(program, name));
} 

/**
 * glUniform1ui
 */ 
PHP_FUNCTION(glUniform1ui)
{
    zend_long location;
    zend_long v0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &location, &v0) == FAILURE) {
        return;
    }
    glUniform1ui(location, v0);
} 

/**
 * glUniform2ui
 */ 
PHP_FUNCTION(glUniform2ui)
{
    zend_long location;
    zend_long v0;
    zend_long v1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &location, &v0, &v1) == FAILURE) {
        return;
    }
    glUniform2ui(location, v0, v1);
} 

/**
 * glUniform3ui
 */ 
PHP_FUNCTION(glUniform3ui)
{
    zend_long location;
    zend_long v0;
    zend_long v1;
    zend_long v2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &location, &v0, &v1, &v2) == FAILURE) {
        return;
    }
    glUniform3ui(location, v0, v1, v2);
} 

/**
 * glUniform4ui
 */ 
PHP_FUNCTION(glUniform4ui)
{
    zend_long location;
    zend_long v0;
    zend_long v1;
    zend_long v2;
    zend_long v3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &location, &v0, &v1, &v2, &v3) == FAILURE) {
        return;
    }
    glUniform4ui(location, v0, v1, v2, v3);
} 

/**
 * glClearBufferfi
 */ 
PHP_FUNCTION(glClearBufferfi)
{
    zend_long buffer;
    zend_long drawbuffer;
    double depth;
    zend_long stencil;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lldl", &buffer, &drawbuffer, &depth, &stencil) == FAILURE) {
        return;
    }
    glClearBufferfi(buffer, drawbuffer, depth, stencil);
} 

/**
 * glIsRenderbuffer
 */ 
PHP_FUNCTION(glIsRenderbuffer)
{
    zend_long renderbuffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &renderbuffer) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsRenderbuffer(renderbuffer));
} 

/**
 * glBindRenderbuffer
 */ 
PHP_FUNCTION(glBindRenderbuffer)
{
    zend_long target;
    zend_long renderbuffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &renderbuffer) == FAILURE) {
        return;
    }
    glBindRenderbuffer(target, renderbuffer);
} 

/**
 * glRenderbufferStorage
 */ 
PHP_FUNCTION(glRenderbufferStorage)
{
    zend_long target;
    zend_long internalformat;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &target, &internalformat, &width, &height) == FAILURE) {
        return;
    }
    glRenderbufferStorage(target, internalformat, width, height);
} 

/**
 * glIsFramebuffer
 */ 
PHP_FUNCTION(glIsFramebuffer)
{
    zend_long framebuffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &framebuffer) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsFramebuffer(framebuffer));
} 

/**
 * glBindFramebuffer
 */ 
PHP_FUNCTION(glBindFramebuffer)
{
    zend_long target;
    zend_long framebuffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &framebuffer) == FAILURE) {
        return;
    }
    glBindFramebuffer(target, framebuffer);
} 

/**
 * glCheckFramebufferStatus
 */ 
PHP_FUNCTION(glCheckFramebufferStatus)
{
    zend_long target;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &target) == FAILURE) {
        return;
    }
    RETURN_LONG(glCheckFramebufferStatus(target));
} 

/**
 * glFramebufferTexture1D
 */ 
PHP_FUNCTION(glFramebufferTexture1D)
{
    zend_long target;
    zend_long attachment;
    zend_long textarget;
    zend_long texture;
    zend_long level;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &target, &attachment, &textarget, &texture, &level) == FAILURE) {
        return;
    }
    glFramebufferTexture1D(target, attachment, textarget, texture, level);
} 

/**
 * glFramebufferTexture2D
 */ 
PHP_FUNCTION(glFramebufferTexture2D)
{
    zend_long target;
    zend_long attachment;
    zend_long textarget;
    zend_long texture;
    zend_long level;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &target, &attachment, &textarget, &texture, &level) == FAILURE) {
        return;
    }
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
} 

/**
 * glFramebufferTexture3D
 */ 
PHP_FUNCTION(glFramebufferTexture3D)
{
    zend_long target;
    zend_long attachment;
    zend_long textarget;
    zend_long texture;
    zend_long level;
    zend_long zoffset;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllll", &target, &attachment, &textarget, &texture, &level, &zoffset) == FAILURE) {
        return;
    }
    glFramebufferTexture3D(target, attachment, textarget, texture, level, zoffset);
} 

/**
 * glFramebufferRenderbuffer
 */ 
PHP_FUNCTION(glFramebufferRenderbuffer)
{
    zend_long target;
    zend_long attachment;
    zend_long renderbuffertarget;
    zend_long renderbuffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &target, &attachment, &renderbuffertarget, &renderbuffer) == FAILURE) {
        return;
    }
    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
} 

/**
 * glGenerateMipmap
 */ 
PHP_FUNCTION(glGenerateMipmap)
{
    zend_long target;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &target) == FAILURE) {
        return;
    }
    glGenerateMipmap(target);
} 

/**
 * glBlitFramebuffer
 */ 
PHP_FUNCTION(glBlitFramebuffer)
{
    zend_long srcX0;
    zend_long srcY0;
    zend_long srcX1;
    zend_long srcY1;
    zend_long dstX0;
    zend_long dstY0;
    zend_long dstX1;
    zend_long dstY1;
    zend_long mask;
    zend_long filter;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllllllll", &srcX0, &srcY0, &srcX1, &srcY1, &dstX0, &dstY0, &dstX1, &dstY1, &mask, &filter) == FAILURE) {
        return;
    }
    glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
} 

/**
 * glRenderbufferStorageMultisample
 */ 
PHP_FUNCTION(glRenderbufferStorageMultisample)
{
    zend_long target;
    zend_long samples;
    zend_long internalformat;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &target, &samples, &internalformat, &width, &height) == FAILURE) {
        return;
    }
    glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
} 

/**
 * glFramebufferTextureLayer
 */ 
PHP_FUNCTION(glFramebufferTextureLayer)
{
    zend_long target;
    zend_long attachment;
    zend_long texture;
    zend_long level;
    zend_long layer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &target, &attachment, &texture, &level, &layer) == FAILURE) {
        return;
    }
    glFramebufferTextureLayer(target, attachment, texture, level, layer);
} 

/**
 * glFlushMappedBufferRange
 */ 
PHP_FUNCTION(glFlushMappedBufferRange)
{
    zend_long target;
    zend_long offset;
    zend_long length;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &target, &offset, &length) == FAILURE) {
        return;
    }
    glFlushMappedBufferRange(target, offset, length);
} 

/**
 * glBindVertexArray
 */ 
PHP_FUNCTION(glBindVertexArray)
{
    zend_long array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &array) == FAILURE) {
        return;
    }
    glBindVertexArray(array);
} 

/**
 * glIsVertexArray
 */ 
PHP_FUNCTION(glIsVertexArray)
{
    zend_long array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &array) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsVertexArray(array));
} 

/**
 * glDrawArraysInstanced
 */ 
PHP_FUNCTION(glDrawArraysInstanced)
{
    zend_long mode;
    zend_long first;
    zend_long count;
    zend_long instancecount;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &mode, &first, &count, &instancecount) == FAILURE) {
        return;
    }
    glDrawArraysInstanced(mode, first, count, instancecount);
} 

/**
 * glTexBuffer
 */ 
PHP_FUNCTION(glTexBuffer)
{
    zend_long target;
    zend_long internalformat;
    zend_long buffer;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &target, &internalformat, &buffer) == FAILURE) {
        return;
    }
    glTexBuffer(target, internalformat, buffer);
} 

/**
 * glPrimitiveRestartIndex
 */ 
PHP_FUNCTION(glPrimitiveRestartIndex)
{
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &index) == FAILURE) {
        return;
    }
    glPrimitiveRestartIndex(index);
} 

/**
 * glCopyBufferSubData
 */ 
PHP_FUNCTION(glCopyBufferSubData)
{
    zend_long readTarget;
    zend_long writeTarget;
    zend_long readOffset;
    zend_long writeOffset;
    zend_long size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &readTarget, &writeTarget, &readOffset, &writeOffset, &size) == FAILURE) {
        return;
    }
    glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
} 

/**
 * glGetUniformBlockIndex
 */ 
PHP_FUNCTION(glGetUniformBlockIndex)
{
    zend_long program;
    const char *uniformBlockName;
    size_t uniformBlockName_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ls", &program, &uniformBlockName, &uniformBlockName_size) == FAILURE) {
        return;
    }
    RETURN_LONG(glGetUniformBlockIndex(program, uniformBlockName));
} 

/**
 * glUniformBlockBinding
 */ 
PHP_FUNCTION(glUniformBlockBinding)
{
    zend_long program;
    zend_long uniformBlockIndex;
    zend_long uniformBlockBinding;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &program, &uniformBlockIndex, &uniformBlockBinding) == FAILURE) {
        return;
    }
    glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
} 

/**
 * glProvokingVertex
 */ 
PHP_FUNCTION(glProvokingVertex)
{
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &mode) == FAILURE) {
        return;
    }
    glProvokingVertex(mode);
} 

/**
 * glFenceSync
 */ 
PHP_FUNCTION(glFenceSync)
{
    zend_long condition;
    zend_long flags;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &condition, &flags) == FAILURE) {
        return;
    }
    RETURN_LONG(glFenceSync(condition, flags));
} 

/**
 * glIsSync
 */ 
PHP_FUNCTION(glIsSync)
{
    zend_long sync;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &sync) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsSync(sync));
} 

/**
 * glDeleteSync
 */ 
PHP_FUNCTION(glDeleteSync)
{
    zend_long sync;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &sync) == FAILURE) {
        return;
    }
    glDeleteSync(sync);
} 

/**
 * glClientWaitSync
 */ 
PHP_FUNCTION(glClientWaitSync)
{
    zend_long sync;
    zend_long flags;
    zend_long timeout;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &sync, &flags, &timeout) == FAILURE) {
        return;
    }
    RETURN_LONG(glClientWaitSync(sync, flags, timeout));
} 

/**
 * glWaitSync
 */ 
PHP_FUNCTION(glWaitSync)
{
    zend_long sync;
    zend_long flags;
    zend_long timeout;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &sync, &flags, &timeout) == FAILURE) {
        return;
    }
    glWaitSync(sync, flags, timeout);
} 

/**
 * glFramebufferTexture
 */ 
PHP_FUNCTION(glFramebufferTexture)
{
    zend_long target;
    zend_long attachment;
    zend_long texture;
    zend_long level;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &target, &attachment, &texture, &level) == FAILURE) {
        return;
    }
    glFramebufferTexture(target, attachment, texture, level);
} 

/**
 * glTexImage2DMultisample
 */ 
PHP_FUNCTION(glTexImage2DMultisample)
{
    zend_long target;
    zend_long samples;
    zend_long internalformat;
    zend_long width;
    zend_long height;
    bool fixedsamplelocations;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllllb", &target, &samples, &internalformat, &width, &height, &fixedsamplelocations) == FAILURE) {
        return;
    }
    glTexImage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
} 

/**
 * glTexImage3DMultisample
 */ 
PHP_FUNCTION(glTexImage3DMultisample)
{
    zend_long target;
    zend_long samples;
    zend_long internalformat;
    zend_long width;
    zend_long height;
    zend_long depth;
    bool fixedsamplelocations;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllllb", &target, &samples, &internalformat, &width, &height, &depth, &fixedsamplelocations) == FAILURE) {
        return;
    }
    glTexImage3DMultisample(target, samples, internalformat, width, height, depth, fixedsamplelocations);
} 

/**
 * glSampleMaski
 */ 
PHP_FUNCTION(glSampleMaski)
{
    zend_long maskNumber;
    zend_long mask;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &maskNumber, &mask) == FAILURE) {
        return;
    }
    glSampleMaski(maskNumber, mask);
} 

/**
 * glBindFragDataLocationIndexed
 */ 
PHP_FUNCTION(glBindFragDataLocationIndexed)
{
    zend_long program;
    zend_long colorNumber;
    zend_long index;
    const char *name;
    size_t name_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llls", &program, &colorNumber, &index, &name, &name_size) == FAILURE) {
        return;
    }
    glBindFragDataLocationIndexed(program, colorNumber, index, name);
} 

/**
 * glGetFragDataIndex
 */ 
PHP_FUNCTION(glGetFragDataIndex)
{
    zend_long program;
    const char *name;
    size_t name_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ls", &program, &name, &name_size) == FAILURE) {
        return;
    }
    RETURN_LONG(glGetFragDataIndex(program, name));
} 

/**
 * glIsSampler
 */ 
PHP_FUNCTION(glIsSampler)
{
    zend_long sampler;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &sampler) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsSampler(sampler));
} 

/**
 * glBindSampler
 */ 
PHP_FUNCTION(glBindSampler)
{
    zend_long unit;
    zend_long sampler;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &unit, &sampler) == FAILURE) {
        return;
    }
    glBindSampler(unit, sampler);
} 

/**
 * glSamplerParameteri
 */ 
PHP_FUNCTION(glSamplerParameteri)
{
    zend_long sampler;
    zend_long pname;
    zend_long param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &sampler, &pname, &param) == FAILURE) {
        return;
    }
    glSamplerParameteri(sampler, pname, param);
} 

/**
 * glSamplerParameterf
 */ 
PHP_FUNCTION(glSamplerParameterf)
{
    zend_long sampler;
    zend_long pname;
    double param;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lld", &sampler, &pname, &param) == FAILURE) {
        return;
    }
    glSamplerParameterf(sampler, pname, param);
} 

/**
 * glQueryCounter
 */ 
PHP_FUNCTION(glQueryCounter)
{
    zend_long id;
    zend_long target;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &id, &target) == FAILURE) {
        return;
    }
    glQueryCounter(id, target);
} 

/**
 * glVertexAttribDivisor
 */ 
PHP_FUNCTION(glVertexAttribDivisor)
{
    zend_long index;
    zend_long divisor;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &index, &divisor) == FAILURE) {
        return;
    }
    glVertexAttribDivisor(index, divisor);
} 

/**
 * glVertexAttribP1ui
 */ 
PHP_FUNCTION(glVertexAttribP1ui)
{
    zend_long index;
    zend_long type;
    bool normalized;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbl", &index, &type, &normalized, &value) == FAILURE) {
        return;
    }
    glVertexAttribP1ui(index, type, normalized, value);
} 

/**
 * glVertexAttribP2ui
 */ 
PHP_FUNCTION(glVertexAttribP2ui)
{
    zend_long index;
    zend_long type;
    bool normalized;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbl", &index, &type, &normalized, &value) == FAILURE) {
        return;
    }
    glVertexAttribP2ui(index, type, normalized, value);
} 

/**
 * glVertexAttribP3ui
 */ 
PHP_FUNCTION(glVertexAttribP3ui)
{
    zend_long index;
    zend_long type;
    bool normalized;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbl", &index, &type, &normalized, &value) == FAILURE) {
        return;
    }
    glVertexAttribP3ui(index, type, normalized, value);
} 

/**
 * glVertexAttribP4ui
 */ 
PHP_FUNCTION(glVertexAttribP4ui)
{
    zend_long index;
    zend_long type;
    bool normalized;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbl", &index, &type, &normalized, &value) == FAILURE) {
        return;
    }
    glVertexAttribP4ui(index, type, normalized, value);
} 

/**
 * glVertexP2ui
 */ 
PHP_FUNCTION(glVertexP2ui)
{
    zend_long type;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &type, &value) == FAILURE) {
        return;
    }
    glVertexP2ui(type, value);
} 

/**
 * glVertexP3ui
 */ 
PHP_FUNCTION(glVertexP3ui)
{
    zend_long type;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &type, &value) == FAILURE) {
        return;
    }
    glVertexP3ui(type, value);
} 

/**
 * glVertexP4ui
 */ 
PHP_FUNCTION(glVertexP4ui)
{
    zend_long type;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &type, &value) == FAILURE) {
        return;
    }
    glVertexP4ui(type, value);
} 

/**
 * glTexCoordP1ui
 */ 
PHP_FUNCTION(glTexCoordP1ui)
{
    zend_long type;
    zend_long coords;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &type, &coords) == FAILURE) {
        return;
    }
    glTexCoordP1ui(type, coords);
} 

/**
 * glTexCoordP2ui
 */ 
PHP_FUNCTION(glTexCoordP2ui)
{
    zend_long type;
    zend_long coords;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &type, &coords) == FAILURE) {
        return;
    }
    glTexCoordP2ui(type, coords);
} 

/**
 * glTexCoordP3ui
 */ 
PHP_FUNCTION(glTexCoordP3ui)
{
    zend_long type;
    zend_long coords;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &type, &coords) == FAILURE) {
        return;
    }
    glTexCoordP3ui(type, coords);
} 

/**
 * glTexCoordP4ui
 */ 
PHP_FUNCTION(glTexCoordP4ui)
{
    zend_long type;
    zend_long coords;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &type, &coords) == FAILURE) {
        return;
    }
    glTexCoordP4ui(type, coords);
} 

/**
 * glMultiTexCoordP1ui
 */ 
PHP_FUNCTION(glMultiTexCoordP1ui)
{
    zend_long texture;
    zend_long type;
    zend_long coords;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &texture, &type, &coords) == FAILURE) {
        return;
    }
    glMultiTexCoordP1ui(texture, type, coords);
} 

/**
 * glMultiTexCoordP2ui
 */ 
PHP_FUNCTION(glMultiTexCoordP2ui)
{
    zend_long texture;
    zend_long type;
    zend_long coords;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &texture, &type, &coords) == FAILURE) {
        return;
    }
    glMultiTexCoordP2ui(texture, type, coords);
} 

/**
 * glMultiTexCoordP3ui
 */ 
PHP_FUNCTION(glMultiTexCoordP3ui)
{
    zend_long texture;
    zend_long type;
    zend_long coords;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &texture, &type, &coords) == FAILURE) {
        return;
    }
    glMultiTexCoordP3ui(texture, type, coords);
} 

/**
 * glMultiTexCoordP4ui
 */ 
PHP_FUNCTION(glMultiTexCoordP4ui)
{
    zend_long texture;
    zend_long type;
    zend_long coords;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &texture, &type, &coords) == FAILURE) {
        return;
    }
    glMultiTexCoordP4ui(texture, type, coords);
} 

/**
 * glNormalP3ui
 */ 
PHP_FUNCTION(glNormalP3ui)
{
    zend_long type;
    zend_long coords;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &type, &coords) == FAILURE) {
        return;
    }
    glNormalP3ui(type, coords);
} 

/**
 * glColorP3ui
 */ 
PHP_FUNCTION(glColorP3ui)
{
    zend_long type;
    zend_long color;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &type, &color) == FAILURE) {
        return;
    }
    glColorP3ui(type, color);
} 

/**
 * glColorP4ui
 */ 
PHP_FUNCTION(glColorP4ui)
{
    zend_long type;
    zend_long color;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &type, &color) == FAILURE) {
        return;
    }
    glColorP4ui(type, color);
} 

/**
 * glSecondaryColorP3ui
 */ 
PHP_FUNCTION(glSecondaryColorP3ui)
{
    zend_long type;
    zend_long color;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &type, &color) == FAILURE) {
        return;
    }
    glSecondaryColorP3ui(type, color);
} 

/**
 * glMinSampleShading
 */ 
PHP_FUNCTION(glMinSampleShading)
{
    double value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &value) == FAILURE) {
        return;
    }
    glMinSampleShading(value);
} 

/**
 * glBlendEquationi
 */ 
PHP_FUNCTION(glBlendEquationi)
{
    zend_long buf;
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &buf, &mode) == FAILURE) {
        return;
    }
    glBlendEquationi(buf, mode);
} 

/**
 * glBlendEquationSeparatei
 */ 
PHP_FUNCTION(glBlendEquationSeparatei)
{
    zend_long buf;
    zend_long modeRGB;
    zend_long modeAlpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &buf, &modeRGB, &modeAlpha) == FAILURE) {
        return;
    }
    glBlendEquationSeparatei(buf, modeRGB, modeAlpha);
} 

/**
 * glBlendFunci
 */ 
PHP_FUNCTION(glBlendFunci)
{
    zend_long buf;
    zend_long src;
    zend_long dst;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &buf, &src, &dst) == FAILURE) {
        return;
    }
    glBlendFunci(buf, src, dst);
} 

/**
 * glBlendFuncSeparatei
 */ 
PHP_FUNCTION(glBlendFuncSeparatei)
{
    zend_long buf;
    zend_long srcRGB;
    zend_long dstRGB;
    zend_long srcAlpha;
    zend_long dstAlpha;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &buf, &srcRGB, &dstRGB, &srcAlpha, &dstAlpha) == FAILURE) {
        return;
    }
    glBlendFuncSeparatei(buf, srcRGB, dstRGB, srcAlpha, dstAlpha);
} 

/**
 * glUniform1d
 */ 
PHP_FUNCTION(glUniform1d)
{
    zend_long location;
    double x;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &location, &x) == FAILURE) {
        return;
    }
    glUniform1d(location, x);
} 

/**
 * glUniform2d
 */ 
PHP_FUNCTION(glUniform2d)
{
    zend_long location;
    double x;
    double y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldd", &location, &x, &y) == FAILURE) {
        return;
    }
    glUniform2d(location, x, y);
} 

/**
 * glUniform3d
 */ 
PHP_FUNCTION(glUniform3d)
{
    zend_long location;
    double x;
    double y;
    double z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lddd", &location, &x, &y, &z) == FAILURE) {
        return;
    }
    glUniform3d(location, x, y, z);
} 

/**
 * glUniform4d
 */ 
PHP_FUNCTION(glUniform4d)
{
    zend_long location;
    double x;
    double y;
    double z;
    double w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldddd", &location, &x, &y, &z, &w) == FAILURE) {
        return;
    }
    glUniform4d(location, x, y, z, w);
} 

/**
 * glGetSubroutineUniformLocation
 */ 
PHP_FUNCTION(glGetSubroutineUniformLocation)
{
    zend_long program;
    zend_long shadertype;
    const char *name;
    size_t name_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lls", &program, &shadertype, &name, &name_size) == FAILURE) {
        return;
    }
    RETURN_LONG(glGetSubroutineUniformLocation(program, shadertype, name));
} 

/**
 * glGetSubroutineIndex
 */ 
PHP_FUNCTION(glGetSubroutineIndex)
{
    zend_long program;
    zend_long shadertype;
    const char *name;
    size_t name_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lls", &program, &shadertype, &name, &name_size) == FAILURE) {
        return;
    }
    RETURN_LONG(glGetSubroutineIndex(program, shadertype, name));
} 

/**
 * glPatchParameteri
 */ 
PHP_FUNCTION(glPatchParameteri)
{
    zend_long pname;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &pname, &value) == FAILURE) {
        return;
    }
    glPatchParameteri(pname, value);
} 

/**
 * glBindTransformFeedback
 */ 
PHP_FUNCTION(glBindTransformFeedback)
{
    zend_long target;
    zend_long id;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &id) == FAILURE) {
        return;
    }
    glBindTransformFeedback(target, id);
} 

/**
 * glIsTransformFeedback
 */ 
PHP_FUNCTION(glIsTransformFeedback)
{
    zend_long id;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &id) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsTransformFeedback(id));
} 

/**
 * glPauseTransformFeedback
 */ 
PHP_FUNCTION(glPauseTransformFeedback)
{
    glPauseTransformFeedback();
} 

/**
 * glResumeTransformFeedback
 */ 
PHP_FUNCTION(glResumeTransformFeedback)
{
    glResumeTransformFeedback();
} 

/**
 * glDrawTransformFeedback
 */ 
PHP_FUNCTION(glDrawTransformFeedback)
{
    zend_long mode;
    zend_long id;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &mode, &id) == FAILURE) {
        return;
    }
    glDrawTransformFeedback(mode, id);
} 

/**
 * glDrawTransformFeedbackStream
 */ 
PHP_FUNCTION(glDrawTransformFeedbackStream)
{
    zend_long mode;
    zend_long id;
    zend_long stream;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &mode, &id, &stream) == FAILURE) {
        return;
    }
    glDrawTransformFeedbackStream(mode, id, stream);
} 

/**
 * glBeginQueryIndexed
 */ 
PHP_FUNCTION(glBeginQueryIndexed)
{
    zend_long target;
    zend_long index;
    zend_long id;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &target, &index, &id) == FAILURE) {
        return;
    }
    glBeginQueryIndexed(target, index, id);
} 

/**
 * glEndQueryIndexed
 */ 
PHP_FUNCTION(glEndQueryIndexed)
{
    zend_long target;
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &target, &index) == FAILURE) {
        return;
    }
    glEndQueryIndexed(target, index);
} 

/**
 * glReleaseShaderCompiler
 */ 
PHP_FUNCTION(glReleaseShaderCompiler)
{
    glReleaseShaderCompiler();
} 

/**
 * glDepthRangef
 */ 
PHP_FUNCTION(glDepthRangef)
{
    double n;
    double f;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dd", &n, &f) == FAILURE) {
        return;
    }
    glDepthRangef(n, f);
} 

/**
 * glClearDepthf
 */ 
PHP_FUNCTION(glClearDepthf)
{
    double d;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &d) == FAILURE) {
        return;
    }
    glClearDepthf(d);
} 

/**
 * glProgramParameteri
 */ 
PHP_FUNCTION(glProgramParameteri)
{
    zend_long program;
    zend_long pname;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &program, &pname, &value) == FAILURE) {
        return;
    }
    glProgramParameteri(program, pname, value);
} 

/**
 * glUseProgramStages
 */ 
PHP_FUNCTION(glUseProgramStages)
{
    zend_long pipeline;
    zend_long stages;
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &pipeline, &stages, &program) == FAILURE) {
        return;
    }
    glUseProgramStages(pipeline, stages, program);
} 

/**
 * glActiveShaderProgram
 */ 
PHP_FUNCTION(glActiveShaderProgram)
{
    zend_long pipeline;
    zend_long program;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &pipeline, &program) == FAILURE) {
        return;
    }
    glActiveShaderProgram(pipeline, program);
} 

/**
 * glBindProgramPipeline
 */ 
PHP_FUNCTION(glBindProgramPipeline)
{
    zend_long pipeline;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &pipeline) == FAILURE) {
        return;
    }
    glBindProgramPipeline(pipeline);
} 

/**
 * glIsProgramPipeline
 */ 
PHP_FUNCTION(glIsProgramPipeline)
{
    zend_long pipeline;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &pipeline) == FAILURE) {
        return;
    }
    RETURN_BOOL(glIsProgramPipeline(pipeline));
} 

/**
 * glProgramUniform1i
 */ 
PHP_FUNCTION(glProgramUniform1i)
{
    zend_long program;
    zend_long location;
    zend_long v0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &program, &location, &v0) == FAILURE) {
        return;
    }
    glProgramUniform1i(program, location, v0);
} 

/**
 * glProgramUniform1f
 */ 
PHP_FUNCTION(glProgramUniform1f)
{
    zend_long program;
    zend_long location;
    double v0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lld", &program, &location, &v0) == FAILURE) {
        return;
    }
    glProgramUniform1f(program, location, v0);
} 

/**
 * glProgramUniform1d
 */ 
PHP_FUNCTION(glProgramUniform1d)
{
    zend_long program;
    zend_long location;
    double v0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lld", &program, &location, &v0) == FAILURE) {
        return;
    }
    glProgramUniform1d(program, location, v0);
} 

/**
 * glProgramUniform1ui
 */ 
PHP_FUNCTION(glProgramUniform1ui)
{
    zend_long program;
    zend_long location;
    zend_long v0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &program, &location, &v0) == FAILURE) {
        return;
    }
    glProgramUniform1ui(program, location, v0);
} 

/**
 * glProgramUniform2i
 */ 
PHP_FUNCTION(glProgramUniform2i)
{
    zend_long program;
    zend_long location;
    zend_long v0;
    zend_long v1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &program, &location, &v0, &v1) == FAILURE) {
        return;
    }
    glProgramUniform2i(program, location, v0, v1);
} 

/**
 * glProgramUniform2f
 */ 
PHP_FUNCTION(glProgramUniform2f)
{
    zend_long program;
    zend_long location;
    double v0;
    double v1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lldd", &program, &location, &v0, &v1) == FAILURE) {
        return;
    }
    glProgramUniform2f(program, location, v0, v1);
} 

/**
 * glProgramUniform2d
 */ 
PHP_FUNCTION(glProgramUniform2d)
{
    zend_long program;
    zend_long location;
    double v0;
    double v1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lldd", &program, &location, &v0, &v1) == FAILURE) {
        return;
    }
    glProgramUniform2d(program, location, v0, v1);
} 

/**
 * glProgramUniform2ui
 */ 
PHP_FUNCTION(glProgramUniform2ui)
{
    zend_long program;
    zend_long location;
    zend_long v0;
    zend_long v1;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llll", &program, &location, &v0, &v1) == FAILURE) {
        return;
    }
    glProgramUniform2ui(program, location, v0, v1);
} 

/**
 * glProgramUniform3i
 */ 
PHP_FUNCTION(glProgramUniform3i)
{
    zend_long program;
    zend_long location;
    zend_long v0;
    zend_long v1;
    zend_long v2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &program, &location, &v0, &v1, &v2) == FAILURE) {
        return;
    }
    glProgramUniform3i(program, location, v0, v1, v2);
} 

/**
 * glProgramUniform3f
 */ 
PHP_FUNCTION(glProgramUniform3f)
{
    zend_long program;
    zend_long location;
    double v0;
    double v1;
    double v2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llddd", &program, &location, &v0, &v1, &v2) == FAILURE) {
        return;
    }
    glProgramUniform3f(program, location, v0, v1, v2);
} 

/**
 * glProgramUniform3d
 */ 
PHP_FUNCTION(glProgramUniform3d)
{
    zend_long program;
    zend_long location;
    double v0;
    double v1;
    double v2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llddd", &program, &location, &v0, &v1, &v2) == FAILURE) {
        return;
    }
    glProgramUniform3d(program, location, v0, v1, v2);
} 

/**
 * glProgramUniform3ui
 */ 
PHP_FUNCTION(glProgramUniform3ui)
{
    zend_long program;
    zend_long location;
    zend_long v0;
    zend_long v1;
    zend_long v2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &program, &location, &v0, &v1, &v2) == FAILURE) {
        return;
    }
    glProgramUniform3ui(program, location, v0, v1, v2);
} 

/**
 * glProgramUniform4i
 */ 
PHP_FUNCTION(glProgramUniform4i)
{
    zend_long program;
    zend_long location;
    zend_long v0;
    zend_long v1;
    zend_long v2;
    zend_long v3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllll", &program, &location, &v0, &v1, &v2, &v3) == FAILURE) {
        return;
    }
    glProgramUniform4i(program, location, v0, v1, v2, v3);
} 

/**
 * glProgramUniform4f
 */ 
PHP_FUNCTION(glProgramUniform4f)
{
    zend_long program;
    zend_long location;
    double v0;
    double v1;
    double v2;
    double v3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lldddd", &program, &location, &v0, &v1, &v2, &v3) == FAILURE) {
        return;
    }
    glProgramUniform4f(program, location, v0, v1, v2, v3);
} 

/**
 * glProgramUniform4d
 */ 
PHP_FUNCTION(glProgramUniform4d)
{
    zend_long program;
    zend_long location;
    double v0;
    double v1;
    double v2;
    double v3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lldddd", &program, &location, &v0, &v1, &v2, &v3) == FAILURE) {
        return;
    }
    glProgramUniform4d(program, location, v0, v1, v2, v3);
} 

/**
 * glProgramUniform4ui
 */ 
PHP_FUNCTION(glProgramUniform4ui)
{
    zend_long program;
    zend_long location;
    zend_long v0;
    zend_long v1;
    zend_long v2;
    zend_long v3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllll", &program, &location, &v0, &v1, &v2, &v3) == FAILURE) {
        return;
    }
    glProgramUniform4ui(program, location, v0, v1, v2, v3);
} 

/**
 * glValidateProgramPipeline
 */ 
PHP_FUNCTION(glValidateProgramPipeline)
{
    zend_long pipeline;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &pipeline) == FAILURE) {
        return;
    }
    glValidateProgramPipeline(pipeline);
} 

/**
 * glVertexAttribL1d
 */ 
PHP_FUNCTION(glVertexAttribL1d)
{
    zend_long index;
    double x;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &index, &x) == FAILURE) {
        return;
    }
    glVertexAttribL1d(index, x);
} 

/**
 * glVertexAttribL2d
 */ 
PHP_FUNCTION(glVertexAttribL2d)
{
    zend_long index;
    double x;
    double y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldd", &index, &x, &y) == FAILURE) {
        return;
    }
    glVertexAttribL2d(index, x, y);
} 

/**
 * glVertexAttribL3d
 */ 
PHP_FUNCTION(glVertexAttribL3d)
{
    zend_long index;
    double x;
    double y;
    double z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lddd", &index, &x, &y, &z) == FAILURE) {
        return;
    }
    glVertexAttribL3d(index, x, y, z);
} 

/**
 * glVertexAttribL4d
 */ 
PHP_FUNCTION(glVertexAttribL4d)
{
    zend_long index;
    double x;
    double y;
    double z;
    double w;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldddd", &index, &x, &y, &z, &w) == FAILURE) {
        return;
    }
    glVertexAttribL4d(index, x, y, z, w);
} 

/**
 * glViewportIndexedf
 */ 
PHP_FUNCTION(glViewportIndexedf)
{
    zend_long index;
    double x;
    double y;
    double w;
    double h;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldddd", &index, &x, &y, &w, &h) == FAILURE) {
        return;
    }
    glViewportIndexedf(index, x, y, w, h);
} 

/**
 * glScissorIndexed
 */ 
PHP_FUNCTION(glScissorIndexed)
{
    zend_long index;
    zend_long left;
    zend_long bottom;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllll", &index, &left, &bottom, &width, &height) == FAILURE) {
        return;
    }
    glScissorIndexed(index, left, bottom, width, height);
} 

/**
 * glDepthRangeIndexed
 */ 
PHP_FUNCTION(glDepthRangeIndexed)
{
    zend_long index;
    double n;
    double f;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ldd", &index, &n, &f) == FAILURE) {
        return;
    }
    glDepthRangeIndexed(index, n, f);
} 

/**
 * glfwInit
 */ 
PHP_FUNCTION(glfwInit)
{
    RETURN_LONG(glfwInit());
} 

/**
 * glfwTerminate
 */ 
PHP_FUNCTION(glfwTerminate)
{
    glfwTerminate();
} 

/**
 * glfwInitHint
 */ 
PHP_FUNCTION(glfwInitHint)
{
    zend_long hint;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &hint, &value) == FAILURE) {
        return;
    }
    glfwInitHint(hint, value);
} 

/**
 * glfwGetVersion
 */ 
PHP_FUNCTION(glfwGetVersion)
{
    zval *major_zval;
    zval *minor_zval;
    zval *rev_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "zzz", &major_zval, &minor_zval, &rev_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(major_zval);
    convert_to_long(major_zval);
    ZVAL_DEREF(minor_zval);
    convert_to_long(minor_zval);
    ZVAL_DEREF(rev_zval);
    convert_to_long(rev_zval);
    glfwGetVersion(&Z_LVAL_P(major_zval), &Z_LVAL_P(minor_zval), &Z_LVAL_P(rev_zval));
} 

/**
 * glfwGetVersionString
 */ 
PHP_FUNCTION(glfwGetVersionString)
{
    RETURN_STRING(glfwGetVersionString());
} 

/**
 * glfwGetPrimaryMonitor
 */ 
PHP_FUNCTION(glfwGetPrimaryMonitor)
{
    GLFWmonitor* glfwmonitor = glfwGetPrimaryMonitor();
    phpglfw_glfwmonitor_ptr_assign_to_zval_p(return_value, glfwmonitor);
} 

/**
 * glfwGetMonitorPos
 */ 
PHP_FUNCTION(glfwGetMonitorPos)
{
    zval *monitor_zval;
    zval *xpos_zval;
    zval *ypos_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &monitor_zval, phpglfw_glfwmonitor_ce, &xpos_zval, &ypos_zval) == FAILURE) {
        return;
    }
    GLFWmonitor* monitor = phpglfw_glfwmonitorptr_from_zval_ptr(monitor_zval);
    ZVAL_DEREF(xpos_zval);
    convert_to_long(xpos_zval);
    ZVAL_DEREF(ypos_zval);
    convert_to_long(ypos_zval);
    glfwGetMonitorPos(monitor, &Z_LVAL_P(xpos_zval), &Z_LVAL_P(ypos_zval));
} 

/**
 * glfwGetMonitorWorkarea
 */ 
PHP_FUNCTION(glfwGetMonitorWorkarea)
{
    zval *monitor_zval;
    zval *xpos_zval;
    zval *ypos_zval;
    zval *width_zval;
    zval *height_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozzzz", &monitor_zval, phpglfw_glfwmonitor_ce, &xpos_zval, &ypos_zval, &width_zval, &height_zval) == FAILURE) {
        return;
    }
    GLFWmonitor* monitor = phpglfw_glfwmonitorptr_from_zval_ptr(monitor_zval);
    ZVAL_DEREF(xpos_zval);
    convert_to_long(xpos_zval);
    ZVAL_DEREF(ypos_zval);
    convert_to_long(ypos_zval);
    ZVAL_DEREF(width_zval);
    convert_to_long(width_zval);
    ZVAL_DEREF(height_zval);
    convert_to_long(height_zval);
    glfwGetMonitorWorkarea(monitor, &Z_LVAL_P(xpos_zval), &Z_LVAL_P(ypos_zval), &Z_LVAL_P(width_zval), &Z_LVAL_P(height_zval));
} 

/**
 * glfwGetMonitorPhysicalSize
 */ 
PHP_FUNCTION(glfwGetMonitorPhysicalSize)
{
    zval *monitor_zval;
    zval *widthMM_zval;
    zval *heightMM_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &monitor_zval, phpglfw_glfwmonitor_ce, &widthMM_zval, &heightMM_zval) == FAILURE) {
        return;
    }
    GLFWmonitor* monitor = phpglfw_glfwmonitorptr_from_zval_ptr(monitor_zval);
    ZVAL_DEREF(widthMM_zval);
    convert_to_long(widthMM_zval);
    ZVAL_DEREF(heightMM_zval);
    convert_to_long(heightMM_zval);
    glfwGetMonitorPhysicalSize(monitor, &Z_LVAL_P(widthMM_zval), &Z_LVAL_P(heightMM_zval));
} 

/**
 * glfwGetMonitorContentScale
 */ 
PHP_FUNCTION(glfwGetMonitorContentScale)
{
    zval *monitor_zval;
    zval *xscale_zval;
    zval *yscale_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &monitor_zval, phpglfw_glfwmonitor_ce, &xscale_zval, &yscale_zval) == FAILURE) {
        return;
    }
    GLFWmonitor* monitor = phpglfw_glfwmonitorptr_from_zval_ptr(monitor_zval);
    ZVAL_DEREF(xscale_zval);
    convert_to_double(xscale_zval);
    ZVAL_DEREF(yscale_zval);
    convert_to_double(yscale_zval);
    glfwGetMonitorContentScale(monitor, &Z_DVAL_P(xscale_zval), &Z_DVAL_P(yscale_zval));
} 

/**
 * glfwGetMonitorName
 */ 
PHP_FUNCTION(glfwGetMonitorName)
{
    zval *monitor_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &monitor_zval, phpglfw_glfwmonitor_ce) == FAILURE) {
        return;
    }
    GLFWmonitor* monitor = phpglfw_glfwmonitorptr_from_zval_ptr(monitor_zval);
    RETURN_STRING(glfwGetMonitorName(monitor));
} 

/**
 * glfwSetGamma
 */ 
PHP_FUNCTION(glfwSetGamma)
{
    zval *monitor_zval;
    double gamma;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Od", &monitor_zval, phpglfw_glfwmonitor_ce, &gamma) == FAILURE) {
        return;
    }
    GLFWmonitor* monitor = phpglfw_glfwmonitorptr_from_zval_ptr(monitor_zval);
    glfwSetGamma(monitor, gamma);
} 

/**
 * glfwDefaultWindowHints
 */ 
PHP_FUNCTION(glfwDefaultWindowHints)
{
    glfwDefaultWindowHints();
} 

/**
 * glfwWindowHint
 */ 
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
 * glfwWindowHintString
 */ 
PHP_FUNCTION(glfwWindowHintString)
{
    zend_long hint;
    const char *value;
    size_t value_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ls", &hint, &value, &value_size) == FAILURE) {
        return;
    }
    glfwWindowHintString(hint, value);
} 

/**
 * glfwCreateWindow
 */ 
PHP_FUNCTION(glfwCreateWindow)
{
    zend_long width;
    zend_long height;
    const char *title;
    size_t title_size;
    zval *monitor_zval = NULL;
    zval *share_zval = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lls|O!O!", &width, &height, &title, &title_size, &monitor_zval, phpglfw_glfwmonitor_ce, &share_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWmonitor* monitor = NULL;
    if (monitor_zval != NULL && Z_TYPE_P(monitor_zval) == IS_OBJECT) {
        monitor = phpglfw_glfwmonitorptr_from_zval_ptr(monitor_zval);
    }
    GLFWwindow* share = NULL;
    if (share_zval != NULL && Z_TYPE_P(share_zval) == IS_OBJECT) {
        share = phpglfw_glfwwindowptr_from_zval_ptr(share_zval);
    }
    GLFWwindow* glfwwindow = glfwCreateWindow(width, height, title, monitor, share);
    phpglfw_glfwwindow_ptr_assign_to_zval_p(return_value, glfwwindow);
} 

/**
 * glfwDestroyWindow
 */ 
PHP_FUNCTION(glfwDestroyWindow)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwDestroyWindow(window);
} 

/**
 * glfwWindowShouldClose
 */ 
PHP_FUNCTION(glfwWindowShouldClose)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    RETURN_LONG(glfwWindowShouldClose(window));
} 

/**
 * glfwSetWindowShouldClose
 */ 
PHP_FUNCTION(glfwSetWindowShouldClose)
{
    zval *window_zval;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ol", &window_zval, phpglfw_glfwwindow_ce, &value) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwSetWindowShouldClose(window, value);
} 

/**
 * glfwSetWindowTitle
 */ 
PHP_FUNCTION(glfwSetWindowTitle)
{
    zval *window_zval;
    const char *title;
    size_t title_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Os", &window_zval, phpglfw_glfwwindow_ce, &title, &title_size) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwSetWindowTitle(window, title);
} 

/**
 * glfwGetWindowPos
 */ 
PHP_FUNCTION(glfwGetWindowPos)
{
    zval *window_zval;
    zval *xpos_zval;
    zval *ypos_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &window_zval, phpglfw_glfwwindow_ce, &xpos_zval, &ypos_zval) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    ZVAL_DEREF(xpos_zval);
    convert_to_long(xpos_zval);
    ZVAL_DEREF(ypos_zval);
    convert_to_long(ypos_zval);
    glfwGetWindowPos(window, &Z_LVAL_P(xpos_zval), &Z_LVAL_P(ypos_zval));
} 

/**
 * glfwSetWindowPos
 */ 
PHP_FUNCTION(glfwSetWindowPos)
{
    zval *window_zval;
    zend_long xpos;
    zend_long ypos;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Oll", &window_zval, phpglfw_glfwwindow_ce, &xpos, &ypos) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwSetWindowPos(window, xpos, ypos);
} 

/**
 * glfwGetWindowSize
 */ 
PHP_FUNCTION(glfwGetWindowSize)
{
    zval *window_zval;
    zval *width_zval;
    zval *height_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &window_zval, phpglfw_glfwwindow_ce, &width_zval, &height_zval) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    ZVAL_DEREF(width_zval);
    convert_to_long(width_zval);
    ZVAL_DEREF(height_zval);
    convert_to_long(height_zval);
    glfwGetWindowSize(window, &Z_LVAL_P(width_zval), &Z_LVAL_P(height_zval));
} 

/**
 * glfwSetWindowSizeLimits
 */ 
PHP_FUNCTION(glfwSetWindowSizeLimits)
{
    zval *window_zval;
    zend_long minwidth;
    zend_long minheight;
    zend_long maxwidth;
    zend_long maxheight;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ollll", &window_zval, phpglfw_glfwwindow_ce, &minwidth, &minheight, &maxwidth, &maxheight) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwSetWindowSizeLimits(window, minwidth, minheight, maxwidth, maxheight);
} 

/**
 * glfwSetWindowAspectRatio
 */ 
PHP_FUNCTION(glfwSetWindowAspectRatio)
{
    zval *window_zval;
    zend_long numer;
    zend_long denom;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Oll", &window_zval, phpglfw_glfwwindow_ce, &numer, &denom) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwSetWindowAspectRatio(window, numer, denom);
} 

/**
 * glfwSetWindowSize
 */ 
PHP_FUNCTION(glfwSetWindowSize)
{
    zval *window_zval;
    zend_long width;
    zend_long height;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Oll", &window_zval, phpglfw_glfwwindow_ce, &width, &height) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwSetWindowSize(window, width, height);
} 

/**
 * glfwGetFramebufferSize
 */ 
PHP_FUNCTION(glfwGetFramebufferSize)
{
    zval *window_zval;
    zval *width_zval;
    zval *height_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &window_zval, phpglfw_glfwwindow_ce, &width_zval, &height_zval) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    ZVAL_DEREF(width_zval);
    convert_to_long(width_zval);
    ZVAL_DEREF(height_zval);
    convert_to_long(height_zval);
    glfwGetFramebufferSize(window, &Z_LVAL_P(width_zval), &Z_LVAL_P(height_zval));
} 

/**
 * glfwGetWindowFrameSize
 */ 
PHP_FUNCTION(glfwGetWindowFrameSize)
{
    zval *window_zval;
    zval *left_zval;
    zval *top_zval;
    zval *right_zval;
    zval *bottom_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozzzz", &window_zval, phpglfw_glfwwindow_ce, &left_zval, &top_zval, &right_zval, &bottom_zval) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    ZVAL_DEREF(left_zval);
    convert_to_long(left_zval);
    ZVAL_DEREF(top_zval);
    convert_to_long(top_zval);
    ZVAL_DEREF(right_zval);
    convert_to_long(right_zval);
    ZVAL_DEREF(bottom_zval);
    convert_to_long(bottom_zval);
    glfwGetWindowFrameSize(window, &Z_LVAL_P(left_zval), &Z_LVAL_P(top_zval), &Z_LVAL_P(right_zval), &Z_LVAL_P(bottom_zval));
} 

/**
 * glfwGetWindowContentScale
 */ 
PHP_FUNCTION(glfwGetWindowContentScale)
{
    zval *window_zval;
    zval *xscale_zval;
    zval *yscale_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &window_zval, phpglfw_glfwwindow_ce, &xscale_zval, &yscale_zval) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    ZVAL_DEREF(xscale_zval);
    convert_to_double(xscale_zval);
    ZVAL_DEREF(yscale_zval);
    convert_to_double(yscale_zval);
    glfwGetWindowContentScale(window, &Z_DVAL_P(xscale_zval), &Z_DVAL_P(yscale_zval));
} 

/**
 * glfwGetWindowOpacity
 */ 
PHP_FUNCTION(glfwGetWindowOpacity)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    RETURN_DOUBLE(glfwGetWindowOpacity(window));
} 

/**
 * glfwSetWindowOpacity
 */ 
PHP_FUNCTION(glfwSetWindowOpacity)
{
    zval *window_zval;
    double opacity;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Od", &window_zval, phpglfw_glfwwindow_ce, &opacity) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwSetWindowOpacity(window, opacity);
} 

/**
 * glfwIconifyWindow
 */ 
PHP_FUNCTION(glfwIconifyWindow)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwIconifyWindow(window);
} 

/**
 * glfwRestoreWindow
 */ 
PHP_FUNCTION(glfwRestoreWindow)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwRestoreWindow(window);
} 

/**
 * glfwMaximizeWindow
 */ 
PHP_FUNCTION(glfwMaximizeWindow)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwMaximizeWindow(window);
} 

/**
 * glfwShowWindow
 */ 
PHP_FUNCTION(glfwShowWindow)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwShowWindow(window);
} 

/**
 * glfwHideWindow
 */ 
PHP_FUNCTION(glfwHideWindow)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwHideWindow(window);
} 

/**
 * glfwFocusWindow
 */ 
PHP_FUNCTION(glfwFocusWindow)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwFocusWindow(window);
} 

/**
 * glfwRequestWindowAttention
 */ 
PHP_FUNCTION(glfwRequestWindowAttention)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwRequestWindowAttention(window);
} 

/**
 * glfwGetWindowMonitor
 */ 
PHP_FUNCTION(glfwGetWindowMonitor)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    GLFWmonitor* glfwmonitor = glfwGetWindowMonitor(window);
    phpglfw_glfwmonitor_ptr_assign_to_zval_p(return_value, glfwmonitor);
} 

/**
 * glfwSetWindowMonitor
 */ 
PHP_FUNCTION(glfwSetWindowMonitor)
{
    zval *window_zval;
    zval *monitor_zval;
    zend_long xpos;
    zend_long ypos;
    zend_long width;
    zend_long height;
    zend_long refreshRate;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "OOlllll", &window_zval, phpglfw_glfwwindow_ce, &monitor_zval, phpglfw_glfwmonitor_ce, &xpos, &ypos, &width, &height, &refreshRate) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    GLFWmonitor* monitor = phpglfw_glfwmonitorptr_from_zval_ptr(monitor_zval);
    glfwSetWindowMonitor(window, monitor, xpos, ypos, width, height, refreshRate);
} 

/**
 * glfwGetWindowAttrib
 */ 
PHP_FUNCTION(glfwGetWindowAttrib)
{
    zval *window_zval;
    zend_long attrib;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ol", &window_zval, phpglfw_glfwwindow_ce, &attrib) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    RETURN_LONG(glfwGetWindowAttrib(window, attrib));
} 

/**
 * glfwSetWindowAttrib
 */ 
PHP_FUNCTION(glfwSetWindowAttrib)
{
    zval *window_zval;
    zend_long attrib;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Oll", &window_zval, phpglfw_glfwwindow_ce, &attrib, &value) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwSetWindowAttrib(window, attrib, value);
} 

/**
 * glfwPollEvents
 */ 
PHP_FUNCTION(glfwPollEvents)
{
    glfwPollEvents();
} 

/**
 * glfwWaitEvents
 */ 
PHP_FUNCTION(glfwWaitEvents)
{
    glfwWaitEvents();
} 

/**
 * glfwWaitEventsTimeout
 */ 
PHP_FUNCTION(glfwWaitEventsTimeout)
{
    double timeout;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &timeout) == FAILURE) {
        return;
    }
    glfwWaitEventsTimeout(timeout);
} 

/**
 * glfwPostEmptyEvent
 */ 
PHP_FUNCTION(glfwPostEmptyEvent)
{
    glfwPostEmptyEvent();
} 

/**
 * glfwGetInputMode
 */ 
PHP_FUNCTION(glfwGetInputMode)
{
    zval *window_zval;
    zend_long mode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ol", &window_zval, phpglfw_glfwwindow_ce, &mode) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    RETURN_LONG(glfwGetInputMode(window, mode));
} 

/**
 * glfwSetInputMode
 */ 
PHP_FUNCTION(glfwSetInputMode)
{
    zval *window_zval;
    zend_long mode;
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Oll", &window_zval, phpglfw_glfwwindow_ce, &mode, &value) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwSetInputMode(window, mode, value);
} 

/**
 * glfwRawMouseMotionSupported
 */ 
PHP_FUNCTION(glfwRawMouseMotionSupported)
{
    RETURN_LONG(glfwRawMouseMotionSupported());
} 

/**
 * glfwGetKeyName
 */ 
PHP_FUNCTION(glfwGetKeyName)
{
    zend_long key;
    zend_long scancode;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &key, &scancode) == FAILURE) {
        return;
    }
    RETURN_STRING(glfwGetKeyName(key, scancode));
} 

/**
 * glfwGetKeyScancode
 */ 
PHP_FUNCTION(glfwGetKeyScancode)
{
    zend_long key;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &key) == FAILURE) {
        return;
    }
    RETURN_LONG(glfwGetKeyScancode(key));
} 

/**
 * glfwGetKey
 */ 
PHP_FUNCTION(glfwGetKey)
{
    zval *window_zval;
    zend_long key;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ol", &window_zval, phpglfw_glfwwindow_ce, &key) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    RETURN_LONG(glfwGetKey(window, key));
} 

/**
 * glfwGetMouseButton
 */ 
PHP_FUNCTION(glfwGetMouseButton)
{
    zval *window_zval;
    zend_long button;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ol", &window_zval, phpglfw_glfwwindow_ce, &button) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    RETURN_LONG(glfwGetMouseButton(window, button));
} 

/**
 * glfwGetCursorPos
 */ 
PHP_FUNCTION(glfwGetCursorPos)
{
    zval *window_zval;
    zval *xpos_zval;
    zval *ypos_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &window_zval, phpglfw_glfwwindow_ce, &xpos_zval, &ypos_zval) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    ZVAL_DEREF(xpos_zval);
    convert_to_double(xpos_zval);
    ZVAL_DEREF(ypos_zval);
    convert_to_double(ypos_zval);
    glfwGetCursorPos(window, &Z_DVAL_P(xpos_zval), &Z_DVAL_P(ypos_zval));
} 

/**
 * glfwSetCursorPos
 */ 
PHP_FUNCTION(glfwSetCursorPos)
{
    zval *window_zval;
    double xpos;
    double ypos;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Odd", &window_zval, phpglfw_glfwwindow_ce, &xpos, &ypos) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwSetCursorPos(window, xpos, ypos);
} 

/**
 * glfwCreateStandardCursor
 */ 
PHP_FUNCTION(glfwCreateStandardCursor)
{
    zend_long shape;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &shape) == FAILURE) {
        return;
    }
    GLFWcursor* glfwcursor = glfwCreateStandardCursor(shape);
    phpglfw_glfwcursor_ptr_assign_to_zval_p(return_value, glfwcursor);
} 

/**
 * glfwDestroyCursor
 */ 
PHP_FUNCTION(glfwDestroyCursor)
{
    zval *cursor_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &cursor_zval, phpglfw_glfwcursor_ce) == FAILURE) {
        return;
    }
    GLFWcursor* cursor = phpglfw_glfwcursorptr_from_zval_ptr(cursor_zval);
    glfwDestroyCursor(cursor);
} 

/**
 * glfwSetCursor
 */ 
PHP_FUNCTION(glfwSetCursor)
{
    zval *window_zval;
    zval *cursor_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "OO", &window_zval, phpglfw_glfwwindow_ce, &cursor_zval, phpglfw_glfwcursor_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    GLFWcursor* cursor = phpglfw_glfwcursorptr_from_zval_ptr(cursor_zval);
    glfwSetCursor(window, cursor);
} 

/**
 * glfwJoystickPresent
 */ 
PHP_FUNCTION(glfwJoystickPresent)
{
    zend_long jid;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &jid) == FAILURE) {
        return;
    }
    RETURN_LONG(glfwJoystickPresent(jid));
} 

/**
 * glfwGetJoystickName
 */ 
PHP_FUNCTION(glfwGetJoystickName)
{
    zend_long jid;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &jid) == FAILURE) {
        return;
    }
    RETURN_STRING(glfwGetJoystickName(jid));
} 

/**
 * glfwGetJoystickGUID
 */ 
PHP_FUNCTION(glfwGetJoystickGUID)
{
    zend_long jid;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &jid) == FAILURE) {
        return;
    }
    RETURN_STRING(glfwGetJoystickGUID(jid));
} 

/**
 * glfwJoystickIsGamepad
 */ 
PHP_FUNCTION(glfwJoystickIsGamepad)
{
    zend_long jid;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &jid) == FAILURE) {
        return;
    }
    RETURN_LONG(glfwJoystickIsGamepad(jid));
} 

/**
 * glfwUpdateGamepadMappings
 */ 
PHP_FUNCTION(glfwUpdateGamepadMappings)
{
    const char *string;
    size_t string_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &string, &string_size) == FAILURE) {
        return;
    }
    RETURN_LONG(glfwUpdateGamepadMappings(string));
} 

/**
 * glfwGetGamepadName
 */ 
PHP_FUNCTION(glfwGetGamepadName)
{
    zend_long jid;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &jid) == FAILURE) {
        return;
    }
    RETURN_STRING(glfwGetGamepadName(jid));
} 

/**
 * glfwSetClipboardString
 */ 
PHP_FUNCTION(glfwSetClipboardString)
{
    zval *window_zval;
    const char *string;
    size_t string_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Os", &window_zval, phpglfw_glfwwindow_ce, &string, &string_size) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwSetClipboardString(window, string);
} 

/**
 * glfwGetClipboardString
 */ 
PHP_FUNCTION(glfwGetClipboardString)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    RETURN_STRING(glfwGetClipboardString(window));
} 

/**
 * glfwGetTime
 */ 
PHP_FUNCTION(glfwGetTime)
{
    RETURN_DOUBLE(glfwGetTime());
} 

/**
 * glfwSetTime
 */ 
PHP_FUNCTION(glfwSetTime)
{
    double time;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &time) == FAILURE) {
        return;
    }
    glfwSetTime(time);
} 

/**
 * glfwMakeContextCurrent
 */ 
PHP_FUNCTION(glfwMakeContextCurrent)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        zend_error(E_ERROR, "glad failed loading the GL loader...");
    }
} 

/**
 * glfwGetCurrentContext
 */ 
PHP_FUNCTION(glfwGetCurrentContext)
{
    GLFWwindow* glfwwindow = glfwGetCurrentContext();
    phpglfw_glfwwindow_ptr_assign_to_zval_p(return_value, glfwwindow);
} 

/**
 * glfwSwapBuffers
 */ 
PHP_FUNCTION(glfwSwapBuffers)
{
    zval *window_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &window_zval, phpglfw_glfwwindow_ce) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    glfwSwapBuffers(window);
} 

/**
 * glfwSwapInterval
 */ 
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
 */ 
PHP_FUNCTION(glfwExtensionSupported)
{
    const char *extension;
    size_t extension_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &extension, &extension_size) == FAILURE) {
        return;
    }
    RETURN_LONG(glfwExtensionSupported(extension));
} 

/**
 * glfwVulkanSupported
 */ 
PHP_FUNCTION(glfwVulkanSupported)
{
    RETURN_LONG(glfwVulkanSupported());
} 

/**
 * glShaderSource
 * Replaces the source code in a shader object.
 * 
 * PHP-GLFW: As with PHP I don't see a reason to split up the shader source to
 * multiple addresses. 
 * This is why the function in PHP is simplyfied `glShaderSource(int $shader,
 * string $soruce)`.
 * 
 * @param int $shader Specifies the handle of the shader object whose source
 * code is to be replaced.
 * @param string $source Specifies a string containing the source code to be
 * loaded into the shader.
 */ 
PHP_FUNCTION(glShaderSource)
{
    zend_long shader;
    const char *source;
    size_t source_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ls", &shader, &source, &source_size) == FAILURE) {
        return;
    }
    glShaderSource(shader, 1, &source, NULL);;
} 

