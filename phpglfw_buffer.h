/**
 * PHP-glfw 
 * 
 * Extension GL buffers
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
#ifndef PHP_GLFW_BUFFER_H
#define PHP_GLFW_BUFFER_H 1

#include "phpglfw_constants.h"
#include "php.h"

#define cvector_clib_malloc emalloc
#define cvector_clib_free efree
#define cvector_clib_calloc ecalloc
#define cvector_clib_realloc erealloc
#define CVECTOR_LOGARITHMIC_GROWTH 1

#include "cvector.h"

/**
 * buffer object structs
 */
typedef struct _phpglfw_buffer_glfloat_object {
    cvector_vector_type(GLfloat) vec;
    zend_object std;
} phpglfw_buffer_glfloat_object; 

typedef struct _phpglfw_buffer_glhalf_object {
    cvector_vector_type(GLhalf) vec;
    zend_object std;
} phpglfw_buffer_glhalf_object; 

typedef struct _phpglfw_buffer_gldouble_object {
    cvector_vector_type(GLdouble) vec;
    zend_object std;
} phpglfw_buffer_gldouble_object; 

typedef struct _phpglfw_buffer_glint_object {
    cvector_vector_type(GLint) vec;
    zend_object std;
} phpglfw_buffer_glint_object; 

typedef struct _phpglfw_buffer_gluint_object {
    cvector_vector_type(GLuint) vec;
    zend_object std;
} phpglfw_buffer_gluint_object; 

typedef struct _phpglfw_buffer_glshort_object {
    cvector_vector_type(GLshort) vec;
    zend_object std;
} phpglfw_buffer_glshort_object; 

typedef struct _phpglfw_buffer_glushort_object {
    cvector_vector_type(GLushort) vec;
    zend_object std;
} phpglfw_buffer_glushort_object; 

typedef struct _phpglfw_buffer_glbyte_object {
    cvector_vector_type(GLbyte) vec;
    zend_object std;
} phpglfw_buffer_glbyte_object; 

typedef struct _phpglfw_buffer_glubyte_object {
    cvector_vector_type(GLubyte) vec;
    zend_object std;
} phpglfw_buffer_glubyte_object; 


/**
 * module init
 */
void phpglfw_register_buffer_module(INIT_FUNC_ARGS);

/**
 * Fetch object helper methods
 */
phpglfw_buffer_glfloat_object* phpglfw_buffer_glfloat_objectptr_from_zobj_p(zend_object* obj);
phpglfw_buffer_glhalf_object* phpglfw_buffer_glhalf_objectptr_from_zobj_p(zend_object* obj);
phpglfw_buffer_gldouble_object* phpglfw_buffer_gldouble_objectptr_from_zobj_p(zend_object* obj);
phpglfw_buffer_glint_object* phpglfw_buffer_glint_objectptr_from_zobj_p(zend_object* obj);
phpglfw_buffer_gluint_object* phpglfw_buffer_gluint_objectptr_from_zobj_p(zend_object* obj);
phpglfw_buffer_glshort_object* phpglfw_buffer_glshort_objectptr_from_zobj_p(zend_object* obj);
phpglfw_buffer_glushort_object* phpglfw_buffer_glushort_objectptr_from_zobj_p(zend_object* obj);
phpglfw_buffer_glbyte_object* phpglfw_buffer_glbyte_objectptr_from_zobj_p(zend_object* obj);
phpglfw_buffer_glubyte_object* phpglfw_buffer_glubyte_objectptr_from_zobj_p(zend_object* obj);

/**
 * Class entry getters
 */
zend_class_entry *phpglfw_get_buffer_interface_ce();
zend_class_entry *phpglfw_get_buffer_glfloat_ce(); 
zend_class_entry *phpglfw_get_buffer_glhalf_ce(); 
zend_class_entry *phpglfw_get_buffer_gldouble_ce(); 
zend_class_entry *phpglfw_get_buffer_glint_ce(); 
zend_class_entry *phpglfw_get_buffer_gluint_ce(); 
zend_class_entry *phpglfw_get_buffer_glshort_ce(); 
zend_class_entry *phpglfw_get_buffer_glushort_ce(); 
zend_class_entry *phpglfw_get_buffer_glbyte_ce(); 
zend_class_entry *phpglfw_get_buffer_glubyte_ce(); 

#endif
