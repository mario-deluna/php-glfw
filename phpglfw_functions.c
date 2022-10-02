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
#include "phpglfw_buffer.h"
#include "phpglfw_math.h"
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
     
    phpglfw_callback poscallback;
    phpglfw_callback sizecallback;
    phpglfw_callback closecallback;
    phpglfw_callback refreshcallback;
    phpglfw_callback focuscallback;
    phpglfw_callback iconifycallback;
    phpglfw_callback maximizecallback;
    phpglfw_callback framebuffersizecallback;
    phpglfw_callback contentcalecallback;
    phpglfw_callback keycallback;
    phpglfw_callback charcallback;
    phpglfw_callback charmodscallback;
    phpglfw_callback mousebuttoncallback;
    phpglfw_callback cursorposcallback;
    phpglfw_callback cursorentercallback;
    phpglfw_callback scrollcallback;
    phpglfw_callback dropcallback;
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

#ifdef ZEND_ACC_NOT_SERIALIZABLE  
    class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;
#else
    class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES;
#endif

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

#ifdef ZEND_ACC_NOT_SERIALIZABLE  
    class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;
#else
    class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES;
#endif

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

#ifdef ZEND_ACC_NOT_SERIALIZABLE  
    class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;
#else
    class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES;
#endif

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
 * PHPGlfw callbacks
 * ----------------------------------------------------------------------------
 * callbacks like GLFWkeyfun etc..
 */
// static zval _phpglfw_callback_keycallback;
// static zval _phpglfw_callback_charcallback;

void phpglfw_init_callbacks(void)
{
//     ZVAL_UNDEF(&_phpglfw_callback_keycallback);
//     ZVAL_UNDEF(&_phpglfw_callback_charcallback);
}

void phpglfw_shutdown_callbacks(void)
{
    // if (Z_TYPE(_phpglfw_callback_keycallback) != IS_UNDEF) {
	// 	zval_ptr_dtor(&_phpglfw_callback_keycallback);
	// 	ZVAL_UNDEF(&_phpglfw_callback_keycallback);
	// }

    // if (Z_TYPE(_phpglfw_callback_charcallback) != IS_UNDEF) {
    //     zval_ptr_dtor(&_phpglfw_callback_charcallback);
    //     ZVAL_UNDEF(&_phpglfw_callback_charcallback);
    // }
}

static void phpglfw_callback_keycallback_handler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // update args of the callback function entry
	zval return_val;
	zval *params = emalloc(4 * sizeof(zval));

	ZVAL_NULL(&return_val);

    ZVAL_LONG(&params[0], key);
    ZVAL_LONG(&params[1], scancode);
    ZVAL_LONG(&params[2], action);
    ZVAL_LONG(&params[3], mods);

    // load the internal obj from the user pointer
    phpglfw_glfwwindow_object* window_obj = (phpglfw_glfwwindow_object*)glfwGetWindowUserPointer(window);

    window_obj->keycallback.fci.params = params;
    window_obj->keycallback.fci.param_count = 4;
    window_obj->keycallback.fci.retval = &return_val;

    zend_call_function(&window_obj->keycallback.fci, &window_obj->keycallback.fci_cache);

	zval_ptr_dtor(&return_val);
    efree(params);
}

static void phpglfw_callback_charcallback_handler(GLFWwindow* window, unsigned int codepoint)
{
    // update args of the callback function entry
    zval return_val;
    zval *params = emalloc(1 * sizeof(zval));

    ZVAL_NULL(&return_val);

    ZVAL_LONG(&params[0], codepoint);

    // load the internal obj from the user pointer
    phpglfw_glfwwindow_object* window_obj = (phpglfw_glfwwindow_object*)glfwGetWindowUserPointer(window);

    window_obj->charcallback.fci.params = params;
    window_obj->charcallback.fci.param_count = 1;
    window_obj->charcallback.fci.retval = &return_val;

    zend_call_function(&window_obj->charcallback.fci, &window_obj->charcallback.fci_cache);

    zval_ptr_dtor(&return_val);
    efree(params);
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
 * glTexParameterfv
 */ 
PHP_FUNCTION(glTexParameterfv)
{
    zend_long target;
    zend_long pname;
    zval *params_zval;
    HashTable *params_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &target, &pname, &params_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &target, &pname, &params_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(params_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glTexParameterfv(target, pname, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(params_zval));
    glTexParameterfv(target, pname, bufferobj->vec);
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
 * glTexParameteriv
 */ 
PHP_FUNCTION(glTexParameteriv)
{
    zend_long target;
    zend_long pname;
    zval *params_zval;
    HashTable *params_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &target, &pname, &params_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &target, &pname, &params_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(params_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glTexParameteriv(target, pname, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(params_zval));
    glTexParameteriv(target, pname, bufferobj->vec);
} 

/**
 * glTexImage2D
 */ 
PHP_FUNCTION(glTexImage2D)
{
    zend_long target;
    zend_long level;
    zend_long internalformat;
    zend_long width;
    zend_long height;
    zend_long border;
    zend_long format;
    zend_long type;
    zval *data_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllllllO", &target, &level, &internalformat, &width, &height, &border, &format, &type, &data_zval, phpglfw_get_buffer_interface_ce()) == FAILURE) {
        return;
    }
    // im still not 100% sure if we should do the validation here, 
    // it will avoid some segfaults but I don't know if it's the best way to do it.
    // on the other hand the performance impact of the validation is going to 
    // so low compared to the other php shenanigans that it probably won't matter. 
    size_t min_buffer_size;
    int numofcom;
    switch (format) {
        case GL_RED:
        case GL_RED_INTEGER:
        case GL_STENCIL_INDEX:
        case GL_DEPTH_COMPONENT:
        numofcom = 1;
        break;
        case GL_RG:
        case GL_RG_INTEGER:
        case GL_DEPTH_STENCIL:
        numofcom = 2;
        break;
        case GL_RGB:
        case GL_RGB_INTEGER:
        case GL_BGR:
        case GL_BGR_INTEGER:
        numofcom = 3;
        break;
        case GL_RGBA:
        case GL_RGBA_INTEGER:
        case GL_BGRA:
        case GL_BGRA_INTEGER:
        numofcom = 4;
        break;
        default:
            zend_throw_error(NULL, "glTexImage2D: invalid format, only GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_DEPTH_COMPONENT, GL_STENCIL_INDEX, GL_DEPTH_STENCIL, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER are supported");
            return;
    }
    // min size is simply width * height * com
    min_buffer_size = width * height * numofcom;
    // check if the given pixel data type is valid and matches 
    // the given buffer object
    zend_class_entry *expected_ce;
    switch (type) {
        case GL_BYTE:
        expected_ce = phpglfw_get_buffer_glbyte_ce();
        break;
        case GL_UNSIGNED_BYTE:
        case GL_UNSIGNED_BYTE_3_3_2:
        case GL_UNSIGNED_BYTE_2_3_3_REV:
        expected_ce = phpglfw_get_buffer_glubyte_ce();
        break;
        case GL_SHORT:
        expected_ce = phpglfw_get_buffer_glshort_ce();
        break;
        case GL_UNSIGNED_SHORT:
        case GL_UNSIGNED_SHORT_5_6_5:
        case GL_UNSIGNED_SHORT_5_6_5_REV:
        case GL_UNSIGNED_SHORT_4_4_4_4:
        case GL_UNSIGNED_SHORT_4_4_4_4_REV:
        case GL_UNSIGNED_SHORT_5_5_5_1:
        case GL_UNSIGNED_SHORT_1_5_5_5_REV:
        expected_ce = phpglfw_get_buffer_glushort_ce();
        break;
        case GL_INT:
        expected_ce = phpglfw_get_buffer_glint_ce();
        break;
        case GL_UNSIGNED_INT:
        case GL_UNSIGNED_INT_8_8_8_8:
        case GL_UNSIGNED_INT_8_8_8_8_REV:
        case GL_UNSIGNED_INT_10_10_10_2:
        case GL_UNSIGNED_INT_2_10_10_10_REV:
        expected_ce = phpglfw_get_buffer_gluint_ce();
        break;
        case GL_FLOAT:
        expected_ce = phpglfw_get_buffer_glfloat_ce();
        break;
        case GL_HALF_FLOAT:
        expected_ce = phpglfw_get_buffer_glhalf_ce();
        break;
    }
    if (Z_OBJCE_P(data_zval) == expected_ce) {
        
        // GLubyte
        if (expected_ce == phpglfw_get_buffer_glubyte_ce()) {
            phpglfw_buffer_glubyte_object *bufferobj = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
            if (cvector_size(bufferobj->vec) < min_buffer_size) {
                zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLubyte)");
                return;
            }
            glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
        }
        // GLbyte
        else if (expected_ce == phpglfw_get_buffer_glbyte_ce()) {
            phpglfw_buffer_glbyte_object *bufferobj = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
            if (cvector_size(bufferobj->vec) < min_buffer_size) {
                zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLbyte)");
                return;
            }
            glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
        }
        // GLshort
        else if (expected_ce == phpglfw_get_buffer_glshort_ce()) {
            phpglfw_buffer_glshort_object *bufferobj = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
            if (cvector_size(bufferobj->vec) < min_buffer_size) {
                zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLshort)");
                return;
            }
            glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
        }
        // GLushort
        else if (expected_ce == phpglfw_get_buffer_glushort_ce()) {
            phpglfw_buffer_glushort_object *bufferobj = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
            if (cvector_size(bufferobj->vec) < min_buffer_size) {
                zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLushort)");
                return;
            }
            glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
        }
        // GLuint
        else if (expected_ce == phpglfw_get_buffer_gluint_ce()) {
            phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
            if (cvector_size(bufferobj->vec) < min_buffer_size) {
                zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLuint)");
                return;
            }
            glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
        }
        // GLint
        else if (expected_ce == phpglfw_get_buffer_glint_ce()) {
            phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
            if (cvector_size(bufferobj->vec) < min_buffer_size) {
                zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLint)");
                return;
            }
            glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
        }
        // GLfloat
        else if (expected_ce == phpglfw_get_buffer_glfloat_ce()) {
            phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
            if (cvector_size(bufferobj->vec) < min_buffer_size) {
                zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLfloat)");
                return;
            }
            glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
        }
        // GLhalf
        else if (expected_ce == phpglfw_get_buffer_glhalf_ce()) {
            phpglfw_buffer_glhalf_object *bufferobj = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
            if (cvector_size(bufferobj->vec) < min_buffer_size) {
                zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLhalf)");
                return;
            }
            glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
        }
        else {
            zend_throw_error(NULL, "glTexImage2D: How in the wold did you get here?");
            return;
        }
        
    } else {
        zend_throw_error(NULL, "glTexImage2D: Invalid buffer object type given. Expected %s, got %s", ZSTR_VAL(expected_ce->name), ZSTR_VAL(Z_OBJCE_P(data_zval)->name));
    };;
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
 * glGetBooleanv
 */ 
PHP_FUNCTION(glGetBooleanv)
{
    zend_long pname;
    zval *data_zval;
    size_t data_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &pname, &data_zval, &data_zval_num) == FAILURE) {
        return;
    }
    if (data_zval_num < 1) {
        zend_throw_error(NULL, "You must at least pass one variable to glGetBooleanv(const, var...)");
        return;
    }
    GLboolean *data_zval_tmp = emalloc(data_zval_num * sizeof(GLboolean));
    glGetBooleanv(pname, data_zval_tmp);
    zval *data;
    for (size_t i = 0; i <  data_zval_num; i++) {
        data = &data_zval[i];
        ZVAL_DEREF(data);
        convert_to_boolean(data);
        ZVAL_BOOL(data, data_zval_tmp[i]);
    }
    efree(data_zval_tmp);;
} 

/**
 * glGetDoublev
 */ 
PHP_FUNCTION(glGetDoublev)
{
    zend_long pname;
    zval *data_zval;
    size_t data_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &pname, &data_zval, &data_zval_num) == FAILURE) {
        return;
    }
    if (data_zval_num < 1) {
        zend_throw_error(NULL, "You must at least pass one variable to glGetDoublev(const, var...)");
        return;
    }
    GLdouble *data_zval_tmp = emalloc(data_zval_num * sizeof(GLdouble));
    glGetDoublev(pname, data_zval_tmp);
    zval *data;
    for (size_t i = 0; i <  data_zval_num; i++) {
        data = &data_zval[i];
        ZVAL_DEREF(data);
        convert_to_double(data);
        ZVAL_DOUBLE(data, data_zval_tmp[i]);
    }
    efree(data_zval_tmp);;
} 

/**
 * glGetError
 */ 
PHP_FUNCTION(glGetError)
{
    RETURN_LONG(glGetError());
} 

/**
 * glGetFloatv
 */ 
PHP_FUNCTION(glGetFloatv)
{
    zend_long pname;
    zval *data_zval;
    size_t data_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &pname, &data_zval, &data_zval_num) == FAILURE) {
        return;
    }
    if (data_zval_num < 1) {
        zend_throw_error(NULL, "You must at least pass one variable to glGetFloatv(const, var...)");
        return;
    }
    GLfloat *data_zval_tmp = emalloc(data_zval_num * sizeof(GLfloat));
    glGetFloatv(pname, data_zval_tmp);
    zval *data;
    for (size_t i = 0; i <  data_zval_num; i++) {
        data = &data_zval[i];
        ZVAL_DEREF(data);
        convert_to_double(data);
        ZVAL_DOUBLE(data, data_zval_tmp[i]);
    }
    efree(data_zval_tmp);;
} 

/**
 * glGetIntegerv
 */ 
PHP_FUNCTION(glGetIntegerv)
{
    zend_long pname;
    zval *data_zval;
    size_t data_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &pname, &data_zval, &data_zval_num) == FAILURE) {
        return;
    }
    if (data_zval_num < 1) {
        zend_throw_error(NULL, "You must at least pass one variable to glGetIntegerv(const, var...)");
        return;
    }
    GLint *data_zval_tmp = emalloc(data_zval_num * sizeof(GLint));
    glGetIntegerv(pname, data_zval_tmp);
    zval *data;
    for (size_t i = 0; i <  data_zval_num; i++) {
        data = &data_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        ZVAL_LONG(data, data_zval_tmp[i]);
    }
    efree(data_zval_tmp);;
} 

/**
 * glGetString
 */ 
PHP_FUNCTION(glGetString)
{
    zend_long name;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &name) == FAILURE) {
        return;
    }
    RETURN_STRING(glGetString(name));
} 

/**
 * glGetTexParameterfv
 */ 
PHP_FUNCTION(glGetTexParameterfv)
{
    zend_long target;
    zend_long pname;
    zval *params_zval;
    size_t params_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll+", &target, &pname, &params_zval, &params_zval_num) == FAILURE) {
        return;
    }
    if (params_zval_num < 1) {
        zend_throw_error(NULL, "You must at least pass one variable to glGetTexParameterfv(const, var...)");
        return;
    }
    GLfloat *params_zval_tmp = emalloc(params_zval_num * sizeof(GLfloat));
    glGetTexParameterfv(target, pname, params_zval_tmp);
    zval *data;
    for (size_t i = 0; i <  params_zval_num; i++) {
        data = &params_zval[i];
        ZVAL_DEREF(data);
        convert_to_double(data);
        ZVAL_DOUBLE(data, params_zval_tmp[i]);
    }
    efree(params_zval_tmp);;
} 

/**
 * glGetTexParameteriv
 */ 
PHP_FUNCTION(glGetTexParameteriv)
{
    zend_long target;
    zend_long pname;
    zval *params_zval;
    size_t params_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll+", &target, &pname, &params_zval, &params_zval_num) == FAILURE) {
        return;
    }
    if (params_zval_num < 1) {
        zend_throw_error(NULL, "You must at least pass one variable to glGetTexParameteriv(const, var...)");
        return;
    }
    GLint *params_zval_tmp = emalloc(params_zval_num * sizeof(GLint));
    glGetTexParameteriv(target, pname, params_zval_tmp);
    zval *data;
    for (size_t i = 0; i <  params_zval_num; i++) {
        data = &params_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        ZVAL_LONG(data, params_zval_tmp[i]);
    }
    efree(params_zval_tmp);;
} 

/**
 * glGetTexLevelParameterfv
 */ 
PHP_FUNCTION(glGetTexLevelParameterfv)
{
    zend_long target;
    zend_long level;
    zend_long pname;
    zval *params_zval;
    GLfloat params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllz", &target, &level, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_double(params_zval);
    glGetTexLevelParameterfv(target, level, pname, &params_tmp);
    ZVAL_DOUBLE(params_zval, params_tmp);
} 

/**
 * glGetTexLevelParameteriv
 */ 
PHP_FUNCTION(glGetTexLevelParameteriv)
{
    zend_long target;
    zend_long level;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllz", &target, &level, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetTexLevelParameteriv(target, level, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glDeleteTextures
 */ 
PHP_FUNCTION(glDeleteTextures)
{
    zend_long n;
    zval *textures;
    size_t textures_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &textures, &textures_num) == FAILURE) {
        return;
    }
    if (n != textures_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *textures_ids = malloc(n * sizeof(GLuint));
    zval *data;
    for (size_t i = 0; i <  textures_num; i++) {
        data = &textures[i];
        convert_to_long(data);
        textures_ids[i] = Z_LVAL_P(data);
    }
    glDeleteTextures(n, textures_ids);;
} 

/**
 * glGenTextures
 */ 
PHP_FUNCTION(glGenTextures)
{
    zend_long n;
    zval *textures_zval;
    size_t textures_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &textures_zval, &textures_zval_num) == FAILURE) {
        return;
    }
    if (n != textures_zval_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *textures_zval_ids = malloc(n * sizeof(GLuint));
    glGenTextures(n, textures_zval_ids);
    zval *data;
    for (size_t i = 0; i <  textures_zval_num; i++) {
        data = &textures_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        Z_LVAL_P(data) = textures_zval_ids[i];
    };
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
 * glPointParameterfv
 */ 
PHP_FUNCTION(glPointParameterfv)
{
    zend_long pname;
    zval *params_zval;
    HashTable *params_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &pname, &params_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &pname, &params_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(params_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glPointParameterfv(pname, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(params_zval));
    glPointParameterfv(pname, bufferobj->vec);
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
 * glPointParameteriv
 */ 
PHP_FUNCTION(glPointParameteriv)
{
    zend_long pname;
    zval *params_zval;
    HashTable *params_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &pname, &params_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &pname, &params_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(params_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glPointParameteriv(pname, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(params_zval));
    glPointParameteriv(pname, bufferobj->vec);
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
 * glGenQueries
 */ 
PHP_FUNCTION(glGenQueries)
{
    zend_long n;
    zval *ids_zval;
    size_t ids_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &ids_zval, &ids_zval_num) == FAILURE) {
        return;
    }
    if (n != ids_zval_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *ids_zval_ids = malloc(n * sizeof(GLuint));
    glGenQueries(n, ids_zval_ids);
    zval *data;
    for (size_t i = 0; i <  ids_zval_num; i++) {
        data = &ids_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        Z_LVAL_P(data) = ids_zval_ids[i];
    };
} 

/**
 * glDeleteQueries
 */ 
PHP_FUNCTION(glDeleteQueries)
{
    zend_long n;
    zval *ids;
    size_t ids_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &ids, &ids_num) == FAILURE) {
        return;
    }
    if (n != ids_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *ids_ids = malloc(n * sizeof(GLuint));
    zval *data;
    for (size_t i = 0; i <  ids_num; i++) {
        data = &ids[i];
        convert_to_long(data);
        ids_ids[i] = Z_LVAL_P(data);
    }
    glDeleteQueries(n, ids_ids);;
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
 * glGetQueryiv
 */ 
PHP_FUNCTION(glGetQueryiv)
{
    zend_long target;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &target, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetQueryiv(target, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
} 

/**
 * glGetQueryObjectiv
 */ 
PHP_FUNCTION(glGetQueryObjectiv)
{
    zend_long id;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &id, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetQueryObjectiv(id, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
} 

/**
 * glGetQueryObjectuiv
 */ 
PHP_FUNCTION(glGetQueryObjectuiv)
{
    zend_long id;
    zend_long pname;
    zval *params_zval;
    GLuint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &id, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetQueryObjectuiv(id, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glDeleteBuffers
 */ 
PHP_FUNCTION(glDeleteBuffers)
{
    zend_long n;
    zval *buffers;
    size_t buffers_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &buffers, &buffers_num) == FAILURE) {
        return;
    }
    if (n != buffers_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *buffers_ids = malloc(n * sizeof(GLuint));
    zval *data;
    for (size_t i = 0; i <  buffers_num; i++) {
        data = &buffers[i];
        convert_to_long(data);
        buffers_ids[i] = Z_LVAL_P(data);
    }
    glDeleteBuffers(n, buffers_ids);;
} 

/**
 * glGenBuffers
 */ 
PHP_FUNCTION(glGenBuffers)
{
    zend_long n;
    zval *buffers_zval;
    size_t buffers_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &buffers_zval, &buffers_zval_num) == FAILURE) {
        return;
    }
    if (n != buffers_zval_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *buffers_zval_ids = malloc(n * sizeof(GLuint));
    glGenBuffers(n, buffers_zval_ids);
    zval *data;
    for (size_t i = 0; i <  buffers_zval_num; i++) {
        data = &buffers_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        Z_LVAL_P(data) = buffers_zval_ids[i];
    };
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
 * glGetBufferParameteriv
 */ 
PHP_FUNCTION(glGetBufferParameteriv)
{
    zend_long target;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &target, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetBufferParameteriv(target, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glGetAttachedShaders
 */ 
PHP_FUNCTION(glGetAttachedShaders)
{
    zend_long program;
    zend_long maxCount;
    zval *count_zval;
    GLsizei count_tmp;
    zval *shaders_zval;
    GLuint shaders_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llzz", &program, &maxCount, &count_zval, &shaders_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(count_zval);
    convert_to_long(count_zval);
    ZVAL_DEREF(shaders_zval);
    convert_to_long(shaders_zval);
    glGetAttachedShaders(program, maxCount, &count_tmp, &shaders_tmp);
    ZVAL_LONG(count_zval, count_tmp);
    ZVAL_LONG(shaders_zval, shaders_tmp);
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
 * glGetProgramiv
 */ 
PHP_FUNCTION(glGetProgramiv)
{
    zend_long program;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &program, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetProgramiv(program, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
} 

/**
 * glGetProgramInfoLog
 */ 
PHP_FUNCTION(glGetProgramInfoLog)
{
    zend_long program;
    zend_long bufSize;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &program, &bufSize) == FAILURE) {
        return;
    }
    GLint maxlen = 0;
    char *buffer;
    buffer = emalloc(sizeof(char) * bufSize);
    glGetProgramInfoLog(program, bufSize, &maxlen, buffer);
    RETURN_STRINGL(buffer, maxlen);
    efree(buffer);
} 

/**
 * glGetShaderiv
 */ 
PHP_FUNCTION(glGetShaderiv)
{
    zend_long shader;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &shader, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetShaderiv(shader, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
} 

/**
 * glGetShaderInfoLog
 */ 
PHP_FUNCTION(glGetShaderInfoLog)
{
    zend_long shader;
    zend_long bufSize;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &shader, &bufSize) == FAILURE) {
        return;
    }
    GLint maxlen = 0;
    char *buffer;
    buffer = emalloc(sizeof(char) * bufSize);
    glGetShaderInfoLog(shader, bufSize, &maxlen, buffer);
    RETURN_STRINGL(buffer, maxlen);
    efree(buffer);
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
 * glGetUniformfv
 */ 
PHP_FUNCTION(glGetUniformfv)
{
    zend_long program;
    zend_long location;
    zval *params_zval;
    GLfloat params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &program, &location, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_double(params_zval);
    glGetUniformfv(program, location, &params_tmp);
    ZVAL_DOUBLE(params_zval, params_tmp);
} 

/**
 * glGetUniformiv
 */ 
PHP_FUNCTION(glGetUniformiv)
{
    zend_long program;
    zend_long location;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &program, &location, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetUniformiv(program, location, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
} 

/**
 * glGetVertexAttribdv
 */ 
PHP_FUNCTION(glGetVertexAttribdv)
{
    zend_long index;
    zend_long pname;
    zval *params_zval;
    GLdouble params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &index, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_double(params_zval);
    glGetVertexAttribdv(index, pname, &params_tmp);
    ZVAL_DOUBLE(params_zval, params_tmp);
} 

/**
 * glGetVertexAttribfv
 */ 
PHP_FUNCTION(glGetVertexAttribfv)
{
    zend_long index;
    zend_long pname;
    zval *params_zval;
    GLfloat params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &index, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_double(params_zval);
    glGetVertexAttribfv(index, pname, &params_tmp);
    ZVAL_DOUBLE(params_zval, params_tmp);
} 

/**
 * glGetVertexAttribiv
 */ 
PHP_FUNCTION(glGetVertexAttribiv)
{
    zend_long index;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &index, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetVertexAttribiv(index, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glUniform1fv
 */ 
PHP_FUNCTION(glUniform1fv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniform1fv(location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniform1fv(location, cvector_size(bufferobj->vec), bufferobj->vec);
} 

/**
 * glUniform2fv
 */ 
PHP_FUNCTION(glUniform2fv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 2 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniform2fv, the number of values must be dividable by 2.");
            return;
        }
        glUniform2fv(location, cvector_size(tmpvec) / 2, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 2 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniform2fv, the number of values must be dividable by 2.");
        return;
    }
    glUniform2fv(location, cvector_size(bufferobj->vec) / 2, bufferobj->vec);
} 

/**
 * glUniform3fv
 */ 
PHP_FUNCTION(glUniform3fv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 3 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniform3fv, the number of values must be dividable by 3.");
            return;
        }
        glUniform3fv(location, cvector_size(tmpvec) / 3, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 3 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniform3fv, the number of values must be dividable by 3.");
        return;
    }
    glUniform3fv(location, cvector_size(bufferobj->vec) / 3, bufferobj->vec);
} 

/**
 * glUniform4fv
 */ 
PHP_FUNCTION(glUniform4fv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 4 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniform4fv, the number of values must be dividable by 4.");
            return;
        }
        glUniform4fv(location, cvector_size(tmpvec) / 4, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 4 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniform4fv, the number of values must be dividable by 4.");
        return;
    }
    glUniform4fv(location, cvector_size(bufferobj->vec) / 4, bufferobj->vec);
} 

/**
 * glUniform1iv
 */ 
PHP_FUNCTION(glUniform1iv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glUniform1iv(location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniform1iv(location, cvector_size(bufferobj->vec), bufferobj->vec);
} 

/**
 * glUniform2iv
 */ 
PHP_FUNCTION(glUniform2iv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 2 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniform2iv, the number of values must be dividable by 2.");
            return;
        }
        glUniform2iv(location, cvector_size(tmpvec) / 2, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 2 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniform2iv, the number of values must be dividable by 2.");
        return;
    }
    glUniform2iv(location, cvector_size(bufferobj->vec) / 2, bufferobj->vec);
} 

/**
 * glUniform3iv
 */ 
PHP_FUNCTION(glUniform3iv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 3 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniform3iv, the number of values must be dividable by 3.");
            return;
        }
        glUniform3iv(location, cvector_size(tmpvec) / 3, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 3 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniform3iv, the number of values must be dividable by 3.");
        return;
    }
    glUniform3iv(location, cvector_size(bufferobj->vec) / 3, bufferobj->vec);
} 

/**
 * glUniform4iv
 */ 
PHP_FUNCTION(glUniform4iv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 4 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniform4iv, the number of values must be dividable by 4.");
            return;
        }
        glUniform4iv(location, cvector_size(tmpvec) / 4, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 4 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniform4iv, the number of values must be dividable by 4.");
        return;
    }
    glUniform4iv(location, cvector_size(bufferobj->vec) / 4, bufferobj->vec);
} 

/**
 * glUniformMatrix2fv
 */ 
PHP_FUNCTION(glUniformMatrix2fv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 4 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniformMatrix2fv, the number of values must be dividable by 4.");
            return;
        }
        glUniformMatrix2fv(location, cvector_size(tmpvec) / 4, transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 4 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniformMatrix2fv, the number of values must be dividable by 4.");
        return;
    }
    glUniformMatrix2fv(location, cvector_size(bufferobj->vec) / 4, transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix3fv
 */ 
PHP_FUNCTION(glUniformMatrix3fv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 9 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniformMatrix3fv, the number of values must be dividable by 9.");
            return;
        }
        glUniformMatrix3fv(location, cvector_size(tmpvec) / 9, transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 9 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniformMatrix3fv, the number of values must be dividable by 9.");
        return;
    }
    glUniformMatrix3fv(location, cvector_size(bufferobj->vec) / 9, transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix4fv
 */ 
PHP_FUNCTION(glUniformMatrix4fv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 16 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniformMatrix4fv, the number of values must be dividable by 16.");
            return;
        }
        glUniformMatrix4fv(location, cvector_size(tmpvec) / 16, transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 16 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniformMatrix4fv, the number of values must be dividable by 16.");
        return;
    }
    glUniformMatrix4fv(location, cvector_size(bufferobj->vec) / 16, transpose, bufferobj->vec);
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
 * glVertexAttrib1dv
 */ 
PHP_FUNCTION(glVertexAttrib1dv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib1dv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib1dv(index, bufferobj->vec);
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
 * glVertexAttrib1fv
 */ 
PHP_FUNCTION(glVertexAttrib1fv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib1fv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib1fv(index, bufferobj->vec);
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
 * glVertexAttrib1sv
 */ 
PHP_FUNCTION(glVertexAttrib1sv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glshort_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLshort) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib1sv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glshort_object *bufferobj = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib1sv(index, bufferobj->vec);
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
 * glVertexAttrib2dv
 */ 
PHP_FUNCTION(glVertexAttrib2dv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib2dv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib2dv(index, bufferobj->vec);
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
 * glVertexAttrib2fv
 */ 
PHP_FUNCTION(glVertexAttrib2fv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib2fv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib2fv(index, bufferobj->vec);
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
 * glVertexAttrib2sv
 */ 
PHP_FUNCTION(glVertexAttrib2sv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glshort_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLshort) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib2sv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glshort_object *bufferobj = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib2sv(index, bufferobj->vec);
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
 * glVertexAttrib3dv
 */ 
PHP_FUNCTION(glVertexAttrib3dv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib3dv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib3dv(index, bufferobj->vec);
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
 * glVertexAttrib3fv
 */ 
PHP_FUNCTION(glVertexAttrib3fv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib3fv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib3fv(index, bufferobj->vec);
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
 * glVertexAttrib3sv
 */ 
PHP_FUNCTION(glVertexAttrib3sv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glshort_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLshort) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib3sv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glshort_object *bufferobj = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib3sv(index, bufferobj->vec);
} 

/**
 * glVertexAttrib4Nbv
 */ 
PHP_FUNCTION(glVertexAttrib4Nbv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glbyte_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLbyte) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4Nbv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glbyte_object *bufferobj = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4Nbv(index, bufferobj->vec);
} 

/**
 * glVertexAttrib4Niv
 */ 
PHP_FUNCTION(glVertexAttrib4Niv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4Niv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4Niv(index, bufferobj->vec);
} 

/**
 * glVertexAttrib4Nsv
 */ 
PHP_FUNCTION(glVertexAttrib4Nsv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glshort_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLshort) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4Nsv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glshort_object *bufferobj = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4Nsv(index, bufferobj->vec);
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
 * glVertexAttrib4Nubv
 */ 
PHP_FUNCTION(glVertexAttrib4Nubv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glubyte_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLubyte) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4Nubv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glubyte_object *bufferobj = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4Nubv(index, bufferobj->vec);
} 

/**
 * glVertexAttrib4Nuiv
 */ 
PHP_FUNCTION(glVertexAttrib4Nuiv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4Nuiv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4Nuiv(index, bufferobj->vec);
} 

/**
 * glVertexAttrib4Nusv
 */ 
PHP_FUNCTION(glVertexAttrib4Nusv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glushort_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLushort) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4Nusv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glushort_object *bufferobj = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4Nusv(index, bufferobj->vec);
} 

/**
 * glVertexAttrib4bv
 */ 
PHP_FUNCTION(glVertexAttrib4bv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glbyte_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLbyte) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4bv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glbyte_object *bufferobj = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4bv(index, bufferobj->vec);
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
 * glVertexAttrib4dv
 */ 
PHP_FUNCTION(glVertexAttrib4dv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4dv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4dv(index, bufferobj->vec);
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
 * glVertexAttrib4fv
 */ 
PHP_FUNCTION(glVertexAttrib4fv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4fv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4fv(index, bufferobj->vec);
} 

/**
 * glVertexAttrib4iv
 */ 
PHP_FUNCTION(glVertexAttrib4iv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4iv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4iv(index, bufferobj->vec);
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
 * glVertexAttrib4sv
 */ 
PHP_FUNCTION(glVertexAttrib4sv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glshort_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLshort) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4sv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glshort_object *bufferobj = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4sv(index, bufferobj->vec);
} 

/**
 * glVertexAttrib4ubv
 */ 
PHP_FUNCTION(glVertexAttrib4ubv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glubyte_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLubyte) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4ubv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glubyte_object *bufferobj = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4ubv(index, bufferobj->vec);
} 

/**
 * glVertexAttrib4uiv
 */ 
PHP_FUNCTION(glVertexAttrib4uiv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4uiv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4uiv(index, bufferobj->vec);
} 

/**
 * glVertexAttrib4usv
 */ 
PHP_FUNCTION(glVertexAttrib4usv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glushort_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLushort) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttrib4usv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glushort_object *bufferobj = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttrib4usv(index, bufferobj->vec);
} 

/**
 * glVertexAttribPointer
 */ 
PHP_FUNCTION(glVertexAttribPointer)
{
    zend_long index;
    zend_long size;
    zend_long type;
    bool normalized;
    zend_long stride;
    zend_long offset;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllbll", &index, &size, &type, &normalized, &stride, &offset) == FAILURE) {
        return;
    }
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
} 

/**
 * glUniformMatrix2x3fv
 */ 
PHP_FUNCTION(glUniformMatrix2x3fv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 6 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniformMatrix2x3fv, the number of values must be dividable by 6.");
            return;
        }
        glUniformMatrix2x3fv(location, cvector_size(tmpvec) / 6, transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 6 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniformMatrix2x3fv, the number of values must be dividable by 6.");
        return;
    }
    glUniformMatrix2x3fv(location, cvector_size(bufferobj->vec) / 6, transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix3x2fv
 */ 
PHP_FUNCTION(glUniformMatrix3x2fv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 6 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniformMatrix3x2fv, the number of values must be dividable by 6.");
            return;
        }
        glUniformMatrix3x2fv(location, cvector_size(tmpvec) / 6, transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 6 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniformMatrix3x2fv, the number of values must be dividable by 6.");
        return;
    }
    glUniformMatrix3x2fv(location, cvector_size(bufferobj->vec) / 6, transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix2x4fv
 */ 
PHP_FUNCTION(glUniformMatrix2x4fv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 8 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniformMatrix2x4fv, the number of values must be dividable by 8.");
            return;
        }
        glUniformMatrix2x4fv(location, cvector_size(tmpvec) / 8, transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 8 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniformMatrix2x4fv, the number of values must be dividable by 8.");
        return;
    }
    glUniformMatrix2x4fv(location, cvector_size(bufferobj->vec) / 8, transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix4x2fv
 */ 
PHP_FUNCTION(glUniformMatrix4x2fv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 8 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniformMatrix4x2fv, the number of values must be dividable by 8.");
            return;
        }
        glUniformMatrix4x2fv(location, cvector_size(tmpvec) / 8, transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 8 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniformMatrix4x2fv, the number of values must be dividable by 8.");
        return;
    }
    glUniformMatrix4x2fv(location, cvector_size(bufferobj->vec) / 8, transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix3x4fv
 */ 
PHP_FUNCTION(glUniformMatrix3x4fv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 12 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniformMatrix3x4fv, the number of values must be dividable by 12.");
            return;
        }
        glUniformMatrix3x4fv(location, cvector_size(tmpvec) / 12, transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 12 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniformMatrix3x4fv, the number of values must be dividable by 12.");
        return;
    }
    glUniformMatrix3x4fv(location, cvector_size(bufferobj->vec) / 12, transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix4x3fv
 */ 
PHP_FUNCTION(glUniformMatrix4x3fv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 12 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniformMatrix4x3fv, the number of values must be dividable by 12.");
            return;
        }
        glUniformMatrix4x3fv(location, cvector_size(tmpvec) / 12, transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 12 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniformMatrix4x3fv, the number of values must be dividable by 12.");
        return;
    }
    glUniformMatrix4x3fv(location, cvector_size(bufferobj->vec) / 12, transpose, bufferobj->vec);
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
 * glGetBooleani_v
 */ 
PHP_FUNCTION(glGetBooleani_v)
{
    zend_long target;
    zend_long index;
    zval *data_zval;
    size_t data_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll+", &target, &index, &data_zval, &data_zval_num) == FAILURE) {
        return;
    }
    if (data_zval_num < 1) {
        zend_throw_error(NULL, "You must at least pass one variable to glGetBooleani_v(const, var...)");
        return;
    }
    GLboolean *data_zval_tmp = emalloc(data_zval_num * sizeof(GLboolean));
    glGetBooleani_v(target, index, data_zval_tmp);
    zval *data;
    for (size_t i = 0; i <  data_zval_num; i++) {
        data = &data_zval[i];
        ZVAL_DEREF(data);
        convert_to_boolean(data);
        ZVAL_BOOL(data, data_zval_tmp[i]);
    }
    efree(data_zval_tmp);;
} 

/**
 * glGetIntegeri_v
 */ 
PHP_FUNCTION(glGetIntegeri_v)
{
    zend_long target;
    zend_long index;
    zval *data_zval;
    size_t data_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll+", &target, &index, &data_zval, &data_zval_num) == FAILURE) {
        return;
    }
    if (data_zval_num < 1) {
        zend_throw_error(NULL, "You must at least pass one variable to glGetIntegeri_v(const, var...)");
        return;
    }
    GLint *data_zval_tmp = emalloc(data_zval_num * sizeof(GLint));
    glGetIntegeri_v(target, index, data_zval_tmp);
    zval *data;
    for (size_t i = 0; i <  data_zval_num; i++) {
        data = &data_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        ZVAL_LONG(data, data_zval_tmp[i]);
    }
    efree(data_zval_tmp);;
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
 * glGetVertexAttribIiv
 */ 
PHP_FUNCTION(glGetVertexAttribIiv)
{
    zend_long index;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &index, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetVertexAttribIiv(index, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
} 

/**
 * glGetVertexAttribIuiv
 */ 
PHP_FUNCTION(glGetVertexAttribIuiv)
{
    zend_long index;
    zend_long pname;
    zval *params_zval;
    GLuint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &index, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetVertexAttribIuiv(index, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glVertexAttribI1iv
 */ 
PHP_FUNCTION(glVertexAttribI1iv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribI1iv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribI1iv(index, bufferobj->vec);
} 

/**
 * glVertexAttribI2iv
 */ 
PHP_FUNCTION(glVertexAttribI2iv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribI2iv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribI2iv(index, bufferobj->vec);
} 

/**
 * glVertexAttribI3iv
 */ 
PHP_FUNCTION(glVertexAttribI3iv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribI3iv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribI3iv(index, bufferobj->vec);
} 

/**
 * glVertexAttribI4iv
 */ 
PHP_FUNCTION(glVertexAttribI4iv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribI4iv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribI4iv(index, bufferobj->vec);
} 

/**
 * glVertexAttribI1uiv
 */ 
PHP_FUNCTION(glVertexAttribI1uiv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribI1uiv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribI1uiv(index, bufferobj->vec);
} 

/**
 * glVertexAttribI2uiv
 */ 
PHP_FUNCTION(glVertexAttribI2uiv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribI2uiv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribI2uiv(index, bufferobj->vec);
} 

/**
 * glVertexAttribI3uiv
 */ 
PHP_FUNCTION(glVertexAttribI3uiv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribI3uiv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribI3uiv(index, bufferobj->vec);
} 

/**
 * glVertexAttribI4uiv
 */ 
PHP_FUNCTION(glVertexAttribI4uiv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribI4uiv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribI4uiv(index, bufferobj->vec);
} 

/**
 * glVertexAttribI4bv
 */ 
PHP_FUNCTION(glVertexAttribI4bv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glbyte_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLbyte) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribI4bv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glbyte_object *bufferobj = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribI4bv(index, bufferobj->vec);
} 

/**
 * glVertexAttribI4sv
 */ 
PHP_FUNCTION(glVertexAttribI4sv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glshort_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLshort) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribI4sv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glshort_object *bufferobj = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribI4sv(index, bufferobj->vec);
} 

/**
 * glVertexAttribI4ubv
 */ 
PHP_FUNCTION(glVertexAttribI4ubv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glubyte_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLubyte) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribI4ubv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glubyte_object *bufferobj = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribI4ubv(index, bufferobj->vec);
} 

/**
 * glVertexAttribI4usv
 */ 
PHP_FUNCTION(glVertexAttribI4usv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glushort_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLushort) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribI4usv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glushort_object *bufferobj = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribI4usv(index, bufferobj->vec);
} 

/**
 * glGetUniformuiv
 */ 
PHP_FUNCTION(glGetUniformuiv)
{
    zend_long program;
    zend_long location;
    zval *params_zval;
    GLuint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &program, &location, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetUniformuiv(program, location, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glUniform1uiv
 */ 
PHP_FUNCTION(glUniform1uiv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glUniform1uiv(location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniform1uiv(location, cvector_size(bufferobj->vec), bufferobj->vec);
} 

/**
 * glUniform2uiv
 */ 
PHP_FUNCTION(glUniform2uiv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 2 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniform2uiv, the number of values must be dividable by 2.");
            return;
        }
        glUniform2uiv(location, cvector_size(tmpvec) / 2, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 2 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniform2uiv, the number of values must be dividable by 2.");
        return;
    }
    glUniform2uiv(location, cvector_size(bufferobj->vec) / 2, bufferobj->vec);
} 

/**
 * glUniform3uiv
 */ 
PHP_FUNCTION(glUniform3uiv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 3 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniform3uiv, the number of values must be dividable by 3.");
            return;
        }
        glUniform3uiv(location, cvector_size(tmpvec) / 3, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 3 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniform3uiv, the number of values must be dividable by 3.");
        return;
    }
    glUniform3uiv(location, cvector_size(bufferobj->vec) / 3, bufferobj->vec);
} 

/**
 * glUniform4uiv
 */ 
PHP_FUNCTION(glUniform4uiv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        if (cvector_size(tmpvec) % 4 != 0) {
            zend_throw_error(NULL, "Invalid data size for glUniform4uiv, the number of values must be dividable by 4.");
            return;
        }
        glUniform4uiv(location, cvector_size(tmpvec) / 4, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    if (cvector_size(bufferobj->vec) % 4 != 0) {
        zend_throw_error(NULL, "Invalid data size for glUniform4uiv, the number of values must be dividable by 4.");
        return;
    }
    glUniform4uiv(location, cvector_size(bufferobj->vec) / 4, bufferobj->vec);
} 

/**
 * glTexParameterIiv
 */ 
PHP_FUNCTION(glTexParameterIiv)
{
    zend_long target;
    zend_long pname;
    zval *params_zval;
    HashTable *params_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &target, &pname, &params_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &target, &pname, &params_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(params_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glTexParameterIiv(target, pname, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(params_zval));
    glTexParameterIiv(target, pname, bufferobj->vec);
} 

/**
 * glTexParameterIuiv
 */ 
PHP_FUNCTION(glTexParameterIuiv)
{
    zend_long target;
    zend_long pname;
    zval *params_zval;
    HashTable *params_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &target, &pname, &params_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &target, &pname, &params_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(params_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glTexParameterIuiv(target, pname, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(params_zval));
    glTexParameterIuiv(target, pname, bufferobj->vec);
} 

/**
 * glGetTexParameterIiv
 */ 
PHP_FUNCTION(glGetTexParameterIiv)
{
    zend_long target;
    zend_long pname;
    zval *params_zval;
    size_t params_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll+", &target, &pname, &params_zval, &params_zval_num) == FAILURE) {
        return;
    }
    if (params_zval_num < 1) {
        zend_throw_error(NULL, "You must at least pass one variable to glGetTexParameterIiv(const, var...)");
        return;
    }
    GLint *params_zval_tmp = emalloc(params_zval_num * sizeof(GLint));
    glGetTexParameterIiv(target, pname, params_zval_tmp);
    zval *data;
    for (size_t i = 0; i <  params_zval_num; i++) {
        data = &params_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        ZVAL_LONG(data, params_zval_tmp[i]);
    }
    efree(params_zval_tmp);;
} 

/**
 * glGetTexParameterIuiv
 */ 
PHP_FUNCTION(glGetTexParameterIuiv)
{
    zend_long target;
    zend_long pname;
    zval *params_zval;
    size_t params_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll+", &target, &pname, &params_zval, &params_zval_num) == FAILURE) {
        return;
    }
    if (params_zval_num < 1) {
        zend_throw_error(NULL, "You must at least pass one variable to glGetTexParameterIuiv(const, var...)");
        return;
    }
    GLuint *params_zval_tmp = emalloc(params_zval_num * sizeof(GLuint));
    glGetTexParameterIuiv(target, pname, params_zval_tmp);
    zval *data;
    for (size_t i = 0; i <  params_zval_num; i++) {
        data = &params_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        ZVAL_LONG(data, params_zval_tmp[i]);
    }
    efree(params_zval_tmp);;
} 

/**
 * glClearBufferiv
 */ 
PHP_FUNCTION(glClearBufferiv)
{
    zend_long buffer;
    zend_long drawbuffer;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &buffer, &drawbuffer, &value_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &buffer, &drawbuffer, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glClearBufferiv(buffer, drawbuffer, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glClearBufferiv(buffer, drawbuffer, bufferobj->vec);
} 

/**
 * glClearBufferuiv
 */ 
PHP_FUNCTION(glClearBufferuiv)
{
    zend_long buffer;
    zend_long drawbuffer;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &buffer, &drawbuffer, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &buffer, &drawbuffer, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glClearBufferuiv(buffer, drawbuffer, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glClearBufferuiv(buffer, drawbuffer, bufferobj->vec);
} 

/**
 * glClearBufferfv
 */ 
PHP_FUNCTION(glClearBufferfv)
{
    zend_long buffer;
    zend_long drawbuffer;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &buffer, &drawbuffer, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &buffer, &drawbuffer, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glClearBufferfv(buffer, drawbuffer, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glClearBufferfv(buffer, drawbuffer, bufferobj->vec);
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
 * glGetStringi
 */ 
PHP_FUNCTION(glGetStringi)
{
    zend_long name;
    zend_long index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &name, &index) == FAILURE) {
        return;
    }
    RETURN_STRING(glGetStringi(name, index));
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
 * glDeleteRenderbuffers
 */ 
PHP_FUNCTION(glDeleteRenderbuffers)
{
    zend_long n;
    zval *renderbuffers;
    size_t renderbuffers_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &renderbuffers, &renderbuffers_num) == FAILURE) {
        return;
    }
    if (n != renderbuffers_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *renderbuffers_ids = malloc(n * sizeof(GLuint));
    zval *data;
    for (size_t i = 0; i <  renderbuffers_num; i++) {
        data = &renderbuffers[i];
        convert_to_long(data);
        renderbuffers_ids[i] = Z_LVAL_P(data);
    }
    glDeleteRenderbuffers(n, renderbuffers_ids);;
} 

/**
 * glGenRenderbuffers
 */ 
PHP_FUNCTION(glGenRenderbuffers)
{
    zend_long n;
    zval *renderbuffers_zval;
    size_t renderbuffers_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &renderbuffers_zval, &renderbuffers_zval_num) == FAILURE) {
        return;
    }
    if (n != renderbuffers_zval_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *renderbuffers_zval_ids = malloc(n * sizeof(GLuint));
    glGenRenderbuffers(n, renderbuffers_zval_ids);
    zval *data;
    for (size_t i = 0; i <  renderbuffers_zval_num; i++) {
        data = &renderbuffers_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        Z_LVAL_P(data) = renderbuffers_zval_ids[i];
    };
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
 * glGetRenderbufferParameteriv
 */ 
PHP_FUNCTION(glGetRenderbufferParameteriv)
{
    zend_long target;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &target, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetRenderbufferParameteriv(target, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glDeleteFramebuffers
 */ 
PHP_FUNCTION(glDeleteFramebuffers)
{
    zend_long n;
    zval *framebuffers;
    size_t framebuffers_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &framebuffers, &framebuffers_num) == FAILURE) {
        return;
    }
    if (n != framebuffers_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *framebuffers_ids = malloc(n * sizeof(GLuint));
    zval *data;
    for (size_t i = 0; i <  framebuffers_num; i++) {
        data = &framebuffers[i];
        convert_to_long(data);
        framebuffers_ids[i] = Z_LVAL_P(data);
    }
    glDeleteFramebuffers(n, framebuffers_ids);;
} 

/**
 * glGenFramebuffers
 */ 
PHP_FUNCTION(glGenFramebuffers)
{
    zend_long n;
    zval *framebuffers_zval;
    size_t framebuffers_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &framebuffers_zval, &framebuffers_zval_num) == FAILURE) {
        return;
    }
    if (n != framebuffers_zval_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *framebuffers_zval_ids = malloc(n * sizeof(GLuint));
    glGenFramebuffers(n, framebuffers_zval_ids);
    zval *data;
    for (size_t i = 0; i <  framebuffers_zval_num; i++) {
        data = &framebuffers_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        Z_LVAL_P(data) = framebuffers_zval_ids[i];
    };
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
 * glGetFramebufferAttachmentParameteriv
 */ 
PHP_FUNCTION(glGetFramebufferAttachmentParameteriv)
{
    zend_long target;
    zend_long attachment;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllz", &target, &attachment, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetFramebufferAttachmentParameteriv(target, attachment, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glDeleteVertexArrays
 */ 
PHP_FUNCTION(glDeleteVertexArrays)
{
    zend_long n;
    zval *arrays;
    size_t arrays_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &arrays, &arrays_num) == FAILURE) {
        return;
    }
    if (n != arrays_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *arrays_ids = malloc(n * sizeof(GLuint));
    zval *data;
    for (size_t i = 0; i <  arrays_num; i++) {
        data = &arrays[i];
        convert_to_long(data);
        arrays_ids[i] = Z_LVAL_P(data);
    }
    glDeleteVertexArrays(n, arrays_ids);;
} 

/**
 * glGenVertexArrays
 */ 
PHP_FUNCTION(glGenVertexArrays)
{
    zend_long n;
    zval *arrays_zval;
    size_t arrays_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &arrays_zval, &arrays_zval_num) == FAILURE) {
        return;
    }
    if (n != arrays_zval_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *arrays_zval_ids = malloc(n * sizeof(GLuint));
    glGenVertexArrays(n, arrays_zval_ids);
    zval *data;
    for (size_t i = 0; i <  arrays_zval_num; i++) {
        data = &arrays_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        Z_LVAL_P(data) = arrays_zval_ids[i];
    };
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
 * glGetActiveUniformBlockiv
 */ 
PHP_FUNCTION(glGetActiveUniformBlockiv)
{
    zend_long program;
    zend_long uniformBlockIndex;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllz", &program, &uniformBlockIndex, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glGetInteger64v
 */ 
PHP_FUNCTION(glGetInteger64v)
{
    zend_long pname;
    zval *data_zval;
    GLint64 data_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lz", &pname, &data_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(data_zval);
    convert_to_long(data_zval);
    glGetInteger64v(pname, &data_tmp);
    ZVAL_LONG(data_zval, data_tmp);
} 

/**
 * glGetInteger64i_v
 */ 
PHP_FUNCTION(glGetInteger64i_v)
{
    zend_long target;
    zend_long index;
    zval *data_zval;
    GLint64 data_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &target, &index, &data_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(data_zval);
    convert_to_long(data_zval);
    glGetInteger64i_v(target, index, &data_tmp);
    ZVAL_LONG(data_zval, data_tmp);
} 

/**
 * glGetBufferParameteri64v
 */ 
PHP_FUNCTION(glGetBufferParameteri64v)
{
    zend_long target;
    zend_long pname;
    zval *params_zval;
    GLint64 params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &target, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetBufferParameteri64v(target, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glGetMultisamplefv
 */ 
PHP_FUNCTION(glGetMultisamplefv)
{
    zend_long pname;
    zend_long index;
    zval *val_zval;
    GLfloat val_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &pname, &index, &val_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(val_zval);
    convert_to_double(val_zval);
    glGetMultisamplefv(pname, index, &val_tmp);
    ZVAL_DOUBLE(val_zval, val_tmp);
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
 * glGenSamplers
 */ 
PHP_FUNCTION(glGenSamplers)
{
    zend_long count;
    zval *samplers_zval;
    size_t samplers_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &count, &samplers_zval, &samplers_zval_num) == FAILURE) {
        return;
    }
    if (count != samplers_zval_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *samplers_zval_ids = malloc(count * sizeof(GLuint));
    glGenSamplers(count, samplers_zval_ids);
    zval *data;
    for (size_t i = 0; i <  samplers_zval_num; i++) {
        data = &samplers_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        Z_LVAL_P(data) = samplers_zval_ids[i];
    };
} 

/**
 * glDeleteSamplers
 */ 
PHP_FUNCTION(glDeleteSamplers)
{
    zend_long count;
    zval *samplers;
    size_t samplers_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &count, &samplers, &samplers_num) == FAILURE) {
        return;
    }
    if (count != samplers_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *samplers_ids = malloc(count * sizeof(GLuint));
    zval *data;
    for (size_t i = 0; i <  samplers_num; i++) {
        data = &samplers[i];
        convert_to_long(data);
        samplers_ids[i] = Z_LVAL_P(data);
    }
    glDeleteSamplers(count, samplers_ids);;
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
 * glSamplerParameteriv
 */ 
PHP_FUNCTION(glSamplerParameteriv)
{
    zend_long sampler;
    zend_long pname;
    zval *param_zval;
    HashTable *param_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &sampler, &pname, &param_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &sampler, &pname, &param_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(param_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glSamplerParameteriv(sampler, pname, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(param_zval));
    glSamplerParameteriv(sampler, pname, bufferobj->vec);
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
 * glSamplerParameterfv
 */ 
PHP_FUNCTION(glSamplerParameterfv)
{
    zend_long sampler;
    zend_long pname;
    zval *param_zval;
    HashTable *param_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &sampler, &pname, &param_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &sampler, &pname, &param_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(param_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glSamplerParameterfv(sampler, pname, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(param_zval));
    glSamplerParameterfv(sampler, pname, bufferobj->vec);
} 

/**
 * glSamplerParameterIiv
 */ 
PHP_FUNCTION(glSamplerParameterIiv)
{
    zend_long sampler;
    zend_long pname;
    zval *param_zval;
    HashTable *param_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &sampler, &pname, &param_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &sampler, &pname, &param_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(param_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glSamplerParameterIiv(sampler, pname, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(param_zval));
    glSamplerParameterIiv(sampler, pname, bufferobj->vec);
} 

/**
 * glSamplerParameterIuiv
 */ 
PHP_FUNCTION(glSamplerParameterIuiv)
{
    zend_long sampler;
    zend_long pname;
    zval *param_zval;
    HashTable *param_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &sampler, &pname, &param_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &sampler, &pname, &param_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(param_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glSamplerParameterIuiv(sampler, pname, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(param_zval));
    glSamplerParameterIuiv(sampler, pname, bufferobj->vec);
} 

/**
 * glGetSamplerParameteriv
 */ 
PHP_FUNCTION(glGetSamplerParameteriv)
{
    zend_long sampler;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &sampler, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetSamplerParameteriv(sampler, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
} 

/**
 * glGetSamplerParameterIiv
 */ 
PHP_FUNCTION(glGetSamplerParameterIiv)
{
    zend_long sampler;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &sampler, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetSamplerParameterIiv(sampler, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
} 

/**
 * glGetSamplerParameterfv
 */ 
PHP_FUNCTION(glGetSamplerParameterfv)
{
    zend_long sampler;
    zend_long pname;
    zval *params_zval;
    GLfloat params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &sampler, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_double(params_zval);
    glGetSamplerParameterfv(sampler, pname, &params_tmp);
    ZVAL_DOUBLE(params_zval, params_tmp);
} 

/**
 * glGetSamplerParameterIuiv
 */ 
PHP_FUNCTION(glGetSamplerParameterIuiv)
{
    zend_long sampler;
    zend_long pname;
    zval *params_zval;
    GLuint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &sampler, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetSamplerParameterIuiv(sampler, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glGetQueryObjecti64v
 */ 
PHP_FUNCTION(glGetQueryObjecti64v)
{
    zend_long id;
    zend_long pname;
    zval *params_zval;
    GLint64 params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &id, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetQueryObjecti64v(id, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
} 

/**
 * glGetQueryObjectui64v
 */ 
PHP_FUNCTION(glGetQueryObjectui64v)
{
    zend_long id;
    zend_long pname;
    zval *params_zval;
    GLuint64 params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &id, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetQueryObjectui64v(id, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glVertexAttribP1uiv
 */ 
PHP_FUNCTION(glVertexAttribP1uiv)
{
    zend_long index;
    zend_long type;
    bool normalized;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &index, &type, &normalized, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &index, &type, &normalized, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribP1uiv(index, type, normalized, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glVertexAttribP1uiv(index, type, normalized, bufferobj->vec);
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
 * glVertexAttribP2uiv
 */ 
PHP_FUNCTION(glVertexAttribP2uiv)
{
    zend_long index;
    zend_long type;
    bool normalized;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &index, &type, &normalized, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &index, &type, &normalized, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribP2uiv(index, type, normalized, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glVertexAttribP2uiv(index, type, normalized, bufferobj->vec);
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
 * glVertexAttribP3uiv
 */ 
PHP_FUNCTION(glVertexAttribP3uiv)
{
    zend_long index;
    zend_long type;
    bool normalized;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &index, &type, &normalized, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &index, &type, &normalized, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribP3uiv(index, type, normalized, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glVertexAttribP3uiv(index, type, normalized, bufferobj->vec);
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
 * glVertexAttribP4uiv
 */ 
PHP_FUNCTION(glVertexAttribP4uiv)
{
    zend_long index;
    zend_long type;
    bool normalized;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &index, &type, &normalized, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &index, &type, &normalized, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribP4uiv(index, type, normalized, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glVertexAttribP4uiv(index, type, normalized, bufferobj->vec);
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
 * glVertexP2uiv
 */ 
PHP_FUNCTION(glVertexP2uiv)
{
    zend_long type;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &type, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &type, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexP2uiv(type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glVertexP2uiv(type, bufferobj->vec);
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
 * glVertexP3uiv
 */ 
PHP_FUNCTION(glVertexP3uiv)
{
    zend_long type;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &type, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &type, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexP3uiv(type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glVertexP3uiv(type, bufferobj->vec);
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
 * glVertexP4uiv
 */ 
PHP_FUNCTION(glVertexP4uiv)
{
    zend_long type;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &type, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &type, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glVertexP4uiv(type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glVertexP4uiv(type, bufferobj->vec);
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
 * glTexCoordP1uiv
 */ 
PHP_FUNCTION(glTexCoordP1uiv)
{
    zend_long type;
    zval *coords_zval;
    HashTable *coords_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &type, &coords_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &type, &coords_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(coords_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glTexCoordP1uiv(type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(coords_zval));
    glTexCoordP1uiv(type, bufferobj->vec);
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
 * glTexCoordP2uiv
 */ 
PHP_FUNCTION(glTexCoordP2uiv)
{
    zend_long type;
    zval *coords_zval;
    HashTable *coords_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &type, &coords_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &type, &coords_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(coords_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glTexCoordP2uiv(type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(coords_zval));
    glTexCoordP2uiv(type, bufferobj->vec);
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
 * glTexCoordP3uiv
 */ 
PHP_FUNCTION(glTexCoordP3uiv)
{
    zend_long type;
    zval *coords_zval;
    HashTable *coords_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &type, &coords_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &type, &coords_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(coords_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glTexCoordP3uiv(type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(coords_zval));
    glTexCoordP3uiv(type, bufferobj->vec);
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
 * glTexCoordP4uiv
 */ 
PHP_FUNCTION(glTexCoordP4uiv)
{
    zend_long type;
    zval *coords_zval;
    HashTable *coords_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &type, &coords_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &type, &coords_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(coords_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glTexCoordP4uiv(type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(coords_zval));
    glTexCoordP4uiv(type, bufferobj->vec);
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
 * glMultiTexCoordP1uiv
 */ 
PHP_FUNCTION(glMultiTexCoordP1uiv)
{
    zend_long texture;
    zend_long type;
    zval *coords_zval;
    HashTable *coords_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &texture, &type, &coords_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &texture, &type, &coords_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(coords_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glMultiTexCoordP1uiv(texture, type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(coords_zval));
    glMultiTexCoordP1uiv(texture, type, bufferobj->vec);
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
 * glMultiTexCoordP2uiv
 */ 
PHP_FUNCTION(glMultiTexCoordP2uiv)
{
    zend_long texture;
    zend_long type;
    zval *coords_zval;
    HashTable *coords_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &texture, &type, &coords_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &texture, &type, &coords_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(coords_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glMultiTexCoordP2uiv(texture, type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(coords_zval));
    glMultiTexCoordP2uiv(texture, type, bufferobj->vec);
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
 * glMultiTexCoordP3uiv
 */ 
PHP_FUNCTION(glMultiTexCoordP3uiv)
{
    zend_long texture;
    zend_long type;
    zval *coords_zval;
    HashTable *coords_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &texture, &type, &coords_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &texture, &type, &coords_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(coords_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glMultiTexCoordP3uiv(texture, type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(coords_zval));
    glMultiTexCoordP3uiv(texture, type, bufferobj->vec);
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
 * glMultiTexCoordP4uiv
 */ 
PHP_FUNCTION(glMultiTexCoordP4uiv)
{
    zend_long texture;
    zend_long type;
    zval *coords_zval;
    HashTable *coords_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &texture, &type, &coords_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &texture, &type, &coords_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(coords_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glMultiTexCoordP4uiv(texture, type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(coords_zval));
    glMultiTexCoordP4uiv(texture, type, bufferobj->vec);
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
 * glNormalP3uiv
 */ 
PHP_FUNCTION(glNormalP3uiv)
{
    zend_long type;
    zval *coords_zval;
    HashTable *coords_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &type, &coords_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &type, &coords_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(coords_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glNormalP3uiv(type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(coords_zval));
    glNormalP3uiv(type, bufferobj->vec);
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
 * glColorP3uiv
 */ 
PHP_FUNCTION(glColorP3uiv)
{
    zend_long type;
    zval *color_zval;
    HashTable *color_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &type, &color_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &type, &color_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(color_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glColorP3uiv(type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(color_zval));
    glColorP3uiv(type, bufferobj->vec);
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
 * glColorP4uiv
 */ 
PHP_FUNCTION(glColorP4uiv)
{
    zend_long type;
    zval *color_zval;
    HashTable *color_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &type, &color_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &type, &color_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(color_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glColorP4uiv(type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(color_zval));
    glColorP4uiv(type, bufferobj->vec);
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
 * glSecondaryColorP3uiv
 */ 
PHP_FUNCTION(glSecondaryColorP3uiv)
{
    zend_long type;
    zval *color_zval;
    HashTable *color_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &type, &color_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &type, &color_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(color_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glSecondaryColorP3uiv(type, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(color_zval));
    glSecondaryColorP3uiv(type, bufferobj->vec);
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
 * glUniform1dv
 */ 
PHP_FUNCTION(glUniform1dv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniform1dv(location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniform1dv(location, cvector_size(bufferobj->vec), bufferobj->vec);
} 

/**
 * glUniform2dv
 */ 
PHP_FUNCTION(glUniform2dv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniform2dv(location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniform2dv(location, cvector_size(bufferobj->vec), bufferobj->vec);
} 

/**
 * glUniform3dv
 */ 
PHP_FUNCTION(glUniform3dv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniform3dv(location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniform3dv(location, cvector_size(bufferobj->vec), bufferobj->vec);
} 

/**
 * glUniform4dv
 */ 
PHP_FUNCTION(glUniform4dv)
{
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniform4dv(location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniform4dv(location, cvector_size(bufferobj->vec), bufferobj->vec);
} 

/**
 * glUniformMatrix2dv
 */ 
PHP_FUNCTION(glUniformMatrix2dv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniformMatrix2dv(location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniformMatrix2dv(location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix3dv
 */ 
PHP_FUNCTION(glUniformMatrix3dv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniformMatrix3dv(location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniformMatrix3dv(location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix4dv
 */ 
PHP_FUNCTION(glUniformMatrix4dv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniformMatrix4dv(location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniformMatrix4dv(location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix2x3dv
 */ 
PHP_FUNCTION(glUniformMatrix2x3dv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniformMatrix2x3dv(location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniformMatrix2x3dv(location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix2x4dv
 */ 
PHP_FUNCTION(glUniformMatrix2x4dv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniformMatrix2x4dv(location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniformMatrix2x4dv(location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix3x2dv
 */ 
PHP_FUNCTION(glUniformMatrix3x2dv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniformMatrix3x2dv(location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniformMatrix3x2dv(location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix3x4dv
 */ 
PHP_FUNCTION(glUniformMatrix3x4dv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniformMatrix3x4dv(location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniformMatrix3x4dv(location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix4x2dv
 */ 
PHP_FUNCTION(glUniformMatrix4x2dv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniformMatrix4x2dv(location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniformMatrix4x2dv(location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glUniformMatrix4x3dv
 */ 
PHP_FUNCTION(glUniformMatrix4x3dv)
{
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbh", &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glUniformMatrix4x3dv(location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glUniformMatrix4x3dv(location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glGetUniformdv
 */ 
PHP_FUNCTION(glGetUniformdv)
{
    zend_long program;
    zend_long location;
    zval *params_zval;
    GLdouble params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &program, &location, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_double(params_zval);
    glGetUniformdv(program, location, &params_tmp);
    ZVAL_DOUBLE(params_zval, params_tmp);
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
 * glGetActiveSubroutineUniformiv
 */ 
PHP_FUNCTION(glGetActiveSubroutineUniformiv)
{
    zend_long program;
    zend_long shadertype;
    zend_long index;
    zend_long pname;
    zval *values_zval;
    GLint values_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llllz", &program, &shadertype, &index, &pname, &values_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(values_zval);
    convert_to_long(values_zval);
    glGetActiveSubroutineUniformiv(program, shadertype, index, pname, &values_tmp);
    ZVAL_LONG(values_zval, values_tmp);
} 

/**
 * glUniformSubroutinesuiv
 */ 
PHP_FUNCTION(glUniformSubroutinesuiv)
{
    zend_long shadertype;
    zval *indices_zval;
    HashTable *indices_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &shadertype, &indices_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &shadertype, &indices_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(indices_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glUniformSubroutinesuiv(shadertype, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(indices_zval));
    glUniformSubroutinesuiv(shadertype, cvector_size(bufferobj->vec), bufferobj->vec);
} 

/**
 * glGetUniformSubroutineuiv
 */ 
PHP_FUNCTION(glGetUniformSubroutineuiv)
{
    zend_long shadertype;
    zend_long location;
    zval *params_zval;
    GLuint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &shadertype, &location, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetUniformSubroutineuiv(shadertype, location, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
} 

/**
 * glGetProgramStageiv
 */ 
PHP_FUNCTION(glGetProgramStageiv)
{
    zend_long program;
    zend_long shadertype;
    zend_long pname;
    zval *values_zval;
    GLint values_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllz", &program, &shadertype, &pname, &values_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(values_zval);
    convert_to_long(values_zval);
    glGetProgramStageiv(program, shadertype, pname, &values_tmp);
    ZVAL_LONG(values_zval, values_tmp);
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
 * glPatchParameterfv
 */ 
PHP_FUNCTION(glPatchParameterfv)
{
    zend_long pname;
    zval *values_zval;
    HashTable *values_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &pname, &values_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &pname, &values_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(values_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glPatchParameterfv(pname, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(values_zval));
    glPatchParameterfv(pname, bufferobj->vec);
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
 * glDeleteTransformFeedbacks
 */ 
PHP_FUNCTION(glDeleteTransformFeedbacks)
{
    zend_long n;
    zval *ids;
    size_t ids_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &ids, &ids_num) == FAILURE) {
        return;
    }
    if (n != ids_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *ids_ids = malloc(n * sizeof(GLuint));
    zval *data;
    for (size_t i = 0; i <  ids_num; i++) {
        data = &ids[i];
        convert_to_long(data);
        ids_ids[i] = Z_LVAL_P(data);
    }
    glDeleteTransformFeedbacks(n, ids_ids);;
} 

/**
 * glGenTransformFeedbacks
 */ 
PHP_FUNCTION(glGenTransformFeedbacks)
{
    zend_long n;
    zval *ids_zval;
    size_t ids_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &ids_zval, &ids_zval_num) == FAILURE) {
        return;
    }
    if (n != ids_zval_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *ids_zval_ids = malloc(n * sizeof(GLuint));
    glGenTransformFeedbacks(n, ids_zval_ids);
    zval *data;
    for (size_t i = 0; i <  ids_zval_num; i++) {
        data = &ids_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        Z_LVAL_P(data) = ids_zval_ids[i];
    };
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
 * glGetQueryIndexediv
 */ 
PHP_FUNCTION(glGetQueryIndexediv)
{
    zend_long target;
    zend_long index;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lllz", &target, &index, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetQueryIndexediv(target, index, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
} 

/**
 * glReleaseShaderCompiler
 */ 
PHP_FUNCTION(glReleaseShaderCompiler)
{
    glReleaseShaderCompiler();
} 

/**
 * glGetShaderPrecisionFormat
 */ 
PHP_FUNCTION(glGetShaderPrecisionFormat)
{
    zend_long shadertype;
    zend_long precisiontype;
    zval *range_zval;
    GLint range_tmp;
    zval *precision_zval;
    GLint precision_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llzz", &shadertype, &precisiontype, &range_zval, &precision_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(range_zval);
    convert_to_long(range_zval);
    ZVAL_DEREF(precision_zval);
    convert_to_long(precision_zval);
    glGetShaderPrecisionFormat(shadertype, precisiontype, &range_tmp, &precision_tmp);
    ZVAL_LONG(range_zval, range_tmp);
    ZVAL_LONG(precision_zval, precision_tmp);
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
 * glDeleteProgramPipelines
 */ 
PHP_FUNCTION(glDeleteProgramPipelines)
{
    zend_long n;
    zval *pipelines;
    size_t pipelines_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &pipelines, &pipelines_num) == FAILURE) {
        return;
    }
    if (n != pipelines_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *pipelines_ids = malloc(n * sizeof(GLuint));
    zval *data;
    for (size_t i = 0; i <  pipelines_num; i++) {
        data = &pipelines[i];
        convert_to_long(data);
        pipelines_ids[i] = Z_LVAL_P(data);
    }
    glDeleteProgramPipelines(n, pipelines_ids);;
} 

/**
 * glGenProgramPipelines
 */ 
PHP_FUNCTION(glGenProgramPipelines)
{
    zend_long n;
    zval *pipelines_zval;
    size_t pipelines_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &pipelines_zval, &pipelines_zval_num) == FAILURE) {
        return;
    }
    if (n != pipelines_zval_num) {
        zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
        return;
    }
    GLuint *pipelines_zval_ids = malloc(n * sizeof(GLuint));
    glGenProgramPipelines(n, pipelines_zval_ids);
    zval *data;
    for (size_t i = 0; i <  pipelines_zval_num; i++) {
        data = &pipelines_zval[i];
        ZVAL_DEREF(data);
        convert_to_long(data);
        Z_LVAL_P(data) = pipelines_zval_ids[i];
    };
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
 * glGetProgramPipelineiv
 */ 
PHP_FUNCTION(glGetProgramPipelineiv)
{
    zend_long pipeline;
    zend_long pname;
    zval *params_zval;
    GLint params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &pipeline, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_long(params_zval);
    glGetProgramPipelineiv(pipeline, pname, &params_tmp);
    ZVAL_LONG(params_zval, params_tmp);
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
 * glProgramUniform1iv
 */ 
PHP_FUNCTION(glProgramUniform1iv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform1iv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform1iv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform1fv
 */ 
PHP_FUNCTION(glProgramUniform1fv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform1fv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform1fv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform1dv
 */ 
PHP_FUNCTION(glProgramUniform1dv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform1dv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform1dv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform1uiv
 */ 
PHP_FUNCTION(glProgramUniform1uiv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform1uiv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform1uiv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform2iv
 */ 
PHP_FUNCTION(glProgramUniform2iv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform2iv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform2iv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform2fv
 */ 
PHP_FUNCTION(glProgramUniform2fv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform2fv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform2fv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform2dv
 */ 
PHP_FUNCTION(glProgramUniform2dv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform2dv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform2dv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform2uiv
 */ 
PHP_FUNCTION(glProgramUniform2uiv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform2uiv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform2uiv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform3iv
 */ 
PHP_FUNCTION(glProgramUniform3iv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform3iv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform3iv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform3fv
 */ 
PHP_FUNCTION(glProgramUniform3fv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform3fv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform3fv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform3dv
 */ 
PHP_FUNCTION(glProgramUniform3dv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform3dv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform3dv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform3uiv
 */ 
PHP_FUNCTION(glProgramUniform3uiv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform3uiv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform3uiv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform4iv
 */ 
PHP_FUNCTION(glProgramUniform4iv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform4iv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform4iv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform4fv
 */ 
PHP_FUNCTION(glProgramUniform4fv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform4fv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform4fv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform4dv
 */ 
PHP_FUNCTION(glProgramUniform4dv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform4dv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform4dv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glProgramUniform4uiv
 */ 
PHP_FUNCTION(glProgramUniform4uiv)
{
    zend_long program;
    zend_long location;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llO", &program, &location, &value_zval, phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llh", &program, &location, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLuint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniform4uiv(program, location, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniform4uiv(program, location, cvector_size(bufferobj->vec), bufferobj->vec);
} 

/**
 * glProgramUniformMatrix2fv
 */ 
PHP_FUNCTION(glProgramUniformMatrix2fv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix2fv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix2fv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix3fv
 */ 
PHP_FUNCTION(glProgramUniformMatrix3fv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix3fv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix3fv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix4fv
 */ 
PHP_FUNCTION(glProgramUniformMatrix4fv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix4fv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix4fv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix2dv
 */ 
PHP_FUNCTION(glProgramUniformMatrix2dv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix2dv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix2dv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix3dv
 */ 
PHP_FUNCTION(glProgramUniformMatrix3dv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix3dv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix3dv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix4dv
 */ 
PHP_FUNCTION(glProgramUniformMatrix4dv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix4dv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix4dv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix2x3fv
 */ 
PHP_FUNCTION(glProgramUniformMatrix2x3fv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix2x3fv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix2x3fv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix3x2fv
 */ 
PHP_FUNCTION(glProgramUniformMatrix3x2fv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix3x2fv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix3x2fv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix2x4fv
 */ 
PHP_FUNCTION(glProgramUniformMatrix2x4fv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix2x4fv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix2x4fv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix4x2fv
 */ 
PHP_FUNCTION(glProgramUniformMatrix4x2fv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix4x2fv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix4x2fv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix3x4fv
 */ 
PHP_FUNCTION(glProgramUniformMatrix3x4fv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix3x4fv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix3x4fv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix4x3fv
 */ 
PHP_FUNCTION(glProgramUniformMatrix4x3fv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix4x3fv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix4x3fv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix2x3dv
 */ 
PHP_FUNCTION(glProgramUniformMatrix2x3dv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix2x3dv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix2x3dv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix3x2dv
 */ 
PHP_FUNCTION(glProgramUniformMatrix3x2dv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix3x2dv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix3x2dv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix2x4dv
 */ 
PHP_FUNCTION(glProgramUniformMatrix2x4dv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix2x4dv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix2x4dv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix4x2dv
 */ 
PHP_FUNCTION(glProgramUniformMatrix4x2dv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix4x2dv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix4x2dv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix3x4dv
 */ 
PHP_FUNCTION(glProgramUniformMatrix3x4dv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix3x4dv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix3x4dv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
} 

/**
 * glProgramUniformMatrix4x3dv
 */ 
PHP_FUNCTION(glProgramUniformMatrix4x3dv)
{
    zend_long program;
    zend_long location;
    bool transpose;
    zval *value_zval;
    HashTable *value_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbO", &program, &location, &transpose, &value_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "llbh", &program, &location, &transpose, &value_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(value_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glProgramUniformMatrix4x3dv(program, location, cvector_size(tmpvec), transpose, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(value_zval));
    glProgramUniformMatrix4x3dv(program, location, cvector_size(bufferobj->vec), transpose, bufferobj->vec);
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
 * glVertexAttribL1dv
 */ 
PHP_FUNCTION(glVertexAttribL1dv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribL1dv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribL1dv(index, bufferobj->vec);
} 

/**
 * glVertexAttribL2dv
 */ 
PHP_FUNCTION(glVertexAttribL2dv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribL2dv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribL2dv(index, bufferobj->vec);
} 

/**
 * glVertexAttribL3dv
 */ 
PHP_FUNCTION(glVertexAttribL3dv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribL3dv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribL3dv(index, bufferobj->vec);
} 

/**
 * glVertexAttribL4dv
 */ 
PHP_FUNCTION(glVertexAttribL4dv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glVertexAttribL4dv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glVertexAttribL4dv(index, bufferobj->vec);
} 

/**
 * glGetVertexAttribLdv
 */ 
PHP_FUNCTION(glGetVertexAttribLdv)
{
    zend_long index;
    zend_long pname;
    zval *params_zval;
    GLdouble params_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "llz", &index, &pname, &params_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(params_zval);
    convert_to_double(params_zval);
    glGetVertexAttribLdv(index, pname, &params_tmp);
    ZVAL_DOUBLE(params_zval, params_tmp);
} 

/**
 * glViewportArrayv
 */ 
PHP_FUNCTION(glViewportArrayv)
{
    zend_long first;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &first, &v_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &first, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glViewportArrayv(first, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glViewportArrayv(first, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glViewportIndexedfv
 */ 
PHP_FUNCTION(glViewportIndexedfv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glfloat_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLfloat) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glViewportIndexedfv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glViewportIndexedfv(index, bufferobj->vec);
} 

/**
 * glScissorArrayv
 */ 
PHP_FUNCTION(glScissorArrayv)
{
    zend_long first;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &first, &v_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &first, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glScissorArrayv(first, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glScissorArrayv(first, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glScissorIndexedv
 */ 
PHP_FUNCTION(glScissorIndexedv)
{
    zend_long index;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &index, &v_zval, phpglfw_get_buffer_glint_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &index, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLint) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_LONG) {
                cvector_push_back(tmpvec, Z_LVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: int");
            }
        ZEND_HASH_FOREACH_END();
        glScissorIndexedv(index, tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glScissorIndexedv(index, bufferobj->vec);
} 

/**
 * glDepthRangeArrayv
 */ 
PHP_FUNCTION(glDepthRangeArrayv)
{
    zend_long first;
    zval *v_zval;
    HashTable *v_ht = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &first, &v_zval, phpglfw_get_buffer_gldouble_ce()) == FAILURE) {
        if (zend_parse_parameters(ZEND_NUM_ARGS() , "lh", &first, &v_ht) == FAILURE) {
            return;
        }
        
        zval *data;
        cvector_vector_type(GLdouble) tmpvec = NULL;
        ZEND_HASH_FOREACH_VAL(v_ht, data)
            if (Z_TYPE_P(data) == IS_DOUBLE) {
                cvector_push_back(tmpvec, Z_DVAL_P(data));
            } else {
                zend_throw_error(NULL, "All elements of the given array have to be of type: float");
            }
        ZEND_HASH_FOREACH_END();
        glDepthRangeArrayv(first, cvector_size(tmpvec), tmpvec);
        cvector_free(tmpvec);
        return;
    }
    phpglfw_buffer_gldouble_object *bufferobj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(v_zval));
    glDepthRangeArrayv(first, cvector_size(bufferobj->vec), bufferobj->vec);
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
 * glGetFloati_v
 */ 
PHP_FUNCTION(glGetFloati_v)
{
    zend_long target;
    zend_long index;
    zval *data_zval;
    size_t data_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll+", &target, &index, &data_zval, &data_zval_num) == FAILURE) {
        return;
    }
    if (data_zval_num < 1) {
        zend_throw_error(NULL, "You must at least pass one variable to glGetFloati_v(const, var...)");
        return;
    }
    GLfloat *data_zval_tmp = emalloc(data_zval_num * sizeof(GLfloat));
    glGetFloati_v(target, index, data_zval_tmp);
    zval *data;
    for (size_t i = 0; i <  data_zval_num; i++) {
        data = &data_zval[i];
        ZVAL_DEREF(data);
        convert_to_double(data);
        ZVAL_DOUBLE(data, data_zval_tmp[i]);
    }
    efree(data_zval_tmp);;
} 

/**
 * glGetDoublei_v
 */ 
PHP_FUNCTION(glGetDoublei_v)
{
    zend_long target;
    zend_long index;
    zval *data_zval;
    size_t data_zval_num = 0;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll+", &target, &index, &data_zval, &data_zval_num) == FAILURE) {
        return;
    }
    if (data_zval_num < 1) {
        zend_throw_error(NULL, "You must at least pass one variable to glGetDoublei_v(const, var...)");
        return;
    }
    GLdouble *data_zval_tmp = emalloc(data_zval_num * sizeof(GLdouble));
    glGetDoublei_v(target, index, data_zval_tmp);
    zval *data;
    for (size_t i = 0; i <  data_zval_num; i++) {
        data = &data_zval[i];
        ZVAL_DEREF(data);
        convert_to_double(data);
        ZVAL_DOUBLE(data, data_zval_tmp[i]);
    }
    efree(data_zval_tmp);;
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
    int major_tmp;
    zval *minor_zval;
    int minor_tmp;
    zval *rev_zval;
    int rev_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "zzz", &major_zval, &minor_zval, &rev_zval) == FAILURE) {
        return;
    }
    ZVAL_DEREF(major_zval);
    convert_to_long(major_zval);
    ZVAL_DEREF(minor_zval);
    convert_to_long(minor_zval);
    ZVAL_DEREF(rev_zval);
    convert_to_long(rev_zval);
    glfwGetVersion(&major_tmp, &minor_tmp, &rev_tmp);
    ZVAL_LONG(major_zval, major_tmp);
    ZVAL_LONG(minor_zval, minor_tmp);
    ZVAL_LONG(rev_zval, rev_tmp);
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
    int xpos_tmp;
    zval *ypos_zval;
    int ypos_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &monitor_zval, phpglfw_glfwmonitor_ce, &xpos_zval, &ypos_zval) == FAILURE) {
        return;
    }
    GLFWmonitor* monitor = phpglfw_glfwmonitorptr_from_zval_ptr(monitor_zval);
    ZVAL_DEREF(xpos_zval);
    convert_to_long(xpos_zval);
    ZVAL_DEREF(ypos_zval);
    convert_to_long(ypos_zval);
    glfwGetMonitorPos(monitor, &xpos_tmp, &ypos_tmp);
    ZVAL_LONG(xpos_zval, xpos_tmp);
    ZVAL_LONG(ypos_zval, ypos_tmp);
} 

/**
 * glfwGetMonitorWorkarea
 */ 
PHP_FUNCTION(glfwGetMonitorWorkarea)
{
    zval *monitor_zval;
    zval *xpos_zval;
    int xpos_tmp;
    zval *ypos_zval;
    int ypos_tmp;
    zval *width_zval;
    int width_tmp;
    zval *height_zval;
    int height_tmp;
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
    glfwGetMonitorWorkarea(monitor, &xpos_tmp, &ypos_tmp, &width_tmp, &height_tmp);
    ZVAL_LONG(xpos_zval, xpos_tmp);
    ZVAL_LONG(ypos_zval, ypos_tmp);
    ZVAL_LONG(width_zval, width_tmp);
    ZVAL_LONG(height_zval, height_tmp);
} 

/**
 * glfwGetMonitorPhysicalSize
 */ 
PHP_FUNCTION(glfwGetMonitorPhysicalSize)
{
    zval *monitor_zval;
    zval *widthMM_zval;
    int widthMM_tmp;
    zval *heightMM_zval;
    int heightMM_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &monitor_zval, phpglfw_glfwmonitor_ce, &widthMM_zval, &heightMM_zval) == FAILURE) {
        return;
    }
    GLFWmonitor* monitor = phpglfw_glfwmonitorptr_from_zval_ptr(monitor_zval);
    ZVAL_DEREF(widthMM_zval);
    convert_to_long(widthMM_zval);
    ZVAL_DEREF(heightMM_zval);
    convert_to_long(heightMM_zval);
    glfwGetMonitorPhysicalSize(monitor, &widthMM_tmp, &heightMM_tmp);
    ZVAL_LONG(widthMM_zval, widthMM_tmp);
    ZVAL_LONG(heightMM_zval, heightMM_tmp);
} 

/**
 * glfwGetMonitorContentScale
 */ 
PHP_FUNCTION(glfwGetMonitorContentScale)
{
    zval *monitor_zval;
    zval *xscale_zval;
    float xscale_tmp;
    zval *yscale_zval;
    float yscale_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &monitor_zval, phpglfw_glfwmonitor_ce, &xscale_zval, &yscale_zval) == FAILURE) {
        return;
    }
    GLFWmonitor* monitor = phpglfw_glfwmonitorptr_from_zval_ptr(monitor_zval);
    ZVAL_DEREF(xscale_zval);
    convert_to_double(xscale_zval);
    ZVAL_DEREF(yscale_zval);
    convert_to_double(yscale_zval);
    glfwGetMonitorContentScale(monitor, &xscale_tmp, &yscale_tmp);
    ZVAL_DOUBLE(xscale_zval, xscale_tmp);
    ZVAL_DOUBLE(yscale_zval, yscale_tmp);
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
    // fetch the internal object
    phpglfw_glfwwindow_object *intern = phpglfw_glfwwindow_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    // ensure user pointer is our internal window object
    glfwSetWindowUserPointer(glfwwindow, intern);
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
    phpglfw_glfwwindow_object *obj_ptr = phpglfw_glfwwindow_objectptr_from_zobj_p(Z_OBJ_P(window_zval));
    glfwDestroyWindow(obj_ptr->glfwwindow);
    obj_ptr->glfwwindow = NULL;
    ZVAL_DEREF(window_zval);
    ZVAL_NULL(window_zval);;
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
    int xpos_tmp;
    zval *ypos_zval;
    int ypos_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &window_zval, phpglfw_glfwwindow_ce, &xpos_zval, &ypos_zval) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    ZVAL_DEREF(xpos_zval);
    convert_to_long(xpos_zval);
    ZVAL_DEREF(ypos_zval);
    convert_to_long(ypos_zval);
    glfwGetWindowPos(window, &xpos_tmp, &ypos_tmp);
    ZVAL_LONG(xpos_zval, xpos_tmp);
    ZVAL_LONG(ypos_zval, ypos_tmp);
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
    int width_tmp;
    zval *height_zval;
    int height_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &window_zval, phpglfw_glfwwindow_ce, &width_zval, &height_zval) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    ZVAL_DEREF(width_zval);
    convert_to_long(width_zval);
    ZVAL_DEREF(height_zval);
    convert_to_long(height_zval);
    glfwGetWindowSize(window, &width_tmp, &height_tmp);
    ZVAL_LONG(width_zval, width_tmp);
    ZVAL_LONG(height_zval, height_tmp);
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
    int width_tmp;
    zval *height_zval;
    int height_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &window_zval, phpglfw_glfwwindow_ce, &width_zval, &height_zval) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    ZVAL_DEREF(width_zval);
    convert_to_long(width_zval);
    ZVAL_DEREF(height_zval);
    convert_to_long(height_zval);
    glfwGetFramebufferSize(window, &width_tmp, &height_tmp);
    ZVAL_LONG(width_zval, width_tmp);
    ZVAL_LONG(height_zval, height_tmp);
} 

/**
 * glfwGetWindowFrameSize
 */ 
PHP_FUNCTION(glfwGetWindowFrameSize)
{
    zval *window_zval;
    zval *left_zval;
    int left_tmp;
    zval *top_zval;
    int top_tmp;
    zval *right_zval;
    int right_tmp;
    zval *bottom_zval;
    int bottom_tmp;
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
    glfwGetWindowFrameSize(window, &left_tmp, &top_tmp, &right_tmp, &bottom_tmp);
    ZVAL_LONG(left_zval, left_tmp);
    ZVAL_LONG(top_zval, top_tmp);
    ZVAL_LONG(right_zval, right_tmp);
    ZVAL_LONG(bottom_zval, bottom_tmp);
} 

/**
 * glfwGetWindowContentScale
 */ 
PHP_FUNCTION(glfwGetWindowContentScale)
{
    zval *window_zval;
    zval *xscale_zval;
    float xscale_tmp;
    zval *yscale_zval;
    float yscale_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &window_zval, phpglfw_glfwwindow_ce, &xscale_zval, &yscale_zval) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    ZVAL_DEREF(xscale_zval);
    convert_to_double(xscale_zval);
    ZVAL_DEREF(yscale_zval);
    convert_to_double(yscale_zval);
    glfwGetWindowContentScale(window, &xscale_tmp, &yscale_tmp);
    ZVAL_DOUBLE(xscale_zval, xscale_tmp);
    ZVAL_DOUBLE(yscale_zval, yscale_tmp);
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
    double xpos_tmp;
    zval *ypos_zval;
    double ypos_tmp;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Ozz", &window_zval, phpglfw_glfwwindow_ce, &xpos_zval, &ypos_zval) == FAILURE) {
        return;
    }
    GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    ZVAL_DEREF(xpos_zval);
    convert_to_double(xpos_zval);
    ZVAL_DEREF(ypos_zval);
    convert_to_double(ypos_zval);
    glfwGetCursorPos(window, &xpos_tmp, &ypos_tmp);
    ZVAL_DOUBLE(xpos_zval, xpos_tmp);
    ZVAL_DOUBLE(ypos_zval, ypos_tmp);
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
    phpglfw_glfwcursor_object *obj_ptr = phpglfw_glfwcursor_objectptr_from_zobj_p(Z_OBJ_P(cursor_zval));
    glfwDestroyCursor(obj_ptr->glfwcursor);
    obj_ptr->glfwcursor = NULL;
    ZVAL_DEREF(cursor_zval);
    ZVAL_NULL(cursor_zval);;
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
 * glfwSetKeyCallback
 */ 
PHP_FUNCTION(glfwSetKeyCallback)
{
    zend_fcall_info fci;
    zend_fcall_info_cache fcc;
    zval *window_zval;
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "Of",  &window_zval, phpglfw_glfwwindow_ce, &fci, &fcc)) {
        RETURN_THROWS();
    }
    phpglfw_glfwwindow_object *obj_ptr = phpglfw_glfwwindow_objectptr_from_zobj_p(Z_OBJ_P(window_zval));
    // copy the function info over to the window object
    // obj_ptr->keycallback.fci = fci;
    // obj_ptr->keycallback.fci_cache = fcc;
    // this fixes a segfault when the callback has a reference over `use()`
    // i honestly have no idea why this works, but it does
    Z_TRY_ADDREF(fci.function_name);
    if (fcc.object) {
        GC_ADDREF(fcc.object);
    }
    memcpy((void*)&obj_ptr->keycallback.fci, (void*)&fci, sizeof(zend_fcall_info));
    memcpy((void*)&obj_ptr->keycallback.fci_cache, (void*)&fcc, sizeof(zend_fcall_info_cache));
    glfwSetKeyCallback(obj_ptr->glfwwindow, phpglfw_callback_keycallback_handler);
} 

/**
 * glfwSetCharCallback
 */ 
PHP_FUNCTION(glfwSetCharCallback)
{
    zend_fcall_info fci;
    zend_fcall_info_cache fcc;
    zval *window_zval;
    if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "Of",  &window_zval, phpglfw_glfwwindow_ce, &fci, &fcc)) {
        RETURN_THROWS();
    }
    phpglfw_glfwwindow_object *obj_ptr = phpglfw_glfwwindow_objectptr_from_zobj_p(Z_OBJ_P(window_zval));
    Z_TRY_ADDREF(fci.function_name);
    if (fcc.object) {
        GC_ADDREF(fcc.object);
    }
    memcpy((void*)&obj_ptr->charcallback.fci, (void*)&fci, sizeof(zend_fcall_info));
    memcpy((void*)&obj_ptr->charcallback.fci_cache, (void*)&fcc, sizeof(zend_fcall_info_cache));
    glfwSetCharCallback(obj_ptr->glfwwindow, phpglfw_callback_charcallback_handler);
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
    #ifdef __APPLE__
        static bool macMovedToFix1334 = false;
        if (!macMovedToFix1334) {
            int x, y;
            glfwGetWindowPos(window, &x, &y);
            glfwSetWindowPos(window, ++x, y);
            macMovedToFix1334 = true;
        }
    #endif
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

/**
 * glBufferData
 */ 
PHP_FUNCTION(glBufferData)
{
    zend_long target;
    zval *buffer_zval;
    zend_long usage;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lOl", &target, &buffer_zval, phpglfw_get_buffer_interface_ce(), &usage) == FAILURE) {
        return;
    }
    if (Z_OBJCE_P(buffer_zval) == phpglfw_get_buffer_glfloat_ce()) {
        phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(buffer_zval));
        glBufferData(target, sizeof(GLfloat) * cvector_size(obj_ptr->vec), obj_ptr->vec, usage);
    } else {
        zend_throw_error(NULL, "glBufferData: Invalid or unsupported buffer object given.");
    };
} 

/**
 * glUniformMatrix4f
 */ 
PHP_FUNCTION(glUniformMatrix4f)
{
    zend_long location;
    bool transpose;
    zval *matrix_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lbO", &location, &transpose, &matrix_zval, phpglfw_get_math_mat4_ce()) == FAILURE) {
        return;
    }
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(matrix_zval));
    glUniformMatrix4fv(location, 1, transpose, &obj_ptr->data[0][0]);
    ;
} 

/**
 * glUniformVec2f
 */ 
PHP_FUNCTION(glUniformVec2f)
{
    zend_long location;
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &vec_zval, phpglfw_get_math_vec2_ce()) == FAILURE) {
        return;
    }
    phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));
    glUniform2fv(location, 1, &obj_ptr->data[0]);
    ;
} 

/**
 * glUniformVec3f
 */ 
PHP_FUNCTION(glUniformVec3f)
{
    zend_long location;
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &vec_zval, phpglfw_get_math_vec3_ce()) == FAILURE) {
        return;
    }
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));
    glUniform3fv(location, 1, &obj_ptr->data[0]);
    ;
} 

/**
 * glUniformVec4f
 */ 
PHP_FUNCTION(glUniformVec4f)
{
    zend_long location;
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &location, &vec_zval, phpglfw_get_math_vec4_ce()) == FAILURE) {
        return;
    }
    phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));
    glUniform4fv(location, 1, &obj_ptr->data[0]);
    ;
} 

