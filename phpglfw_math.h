/**
 * PHP-glfw 
 * 
 * Extension constants
 *
 * Copyright (c) 2018-2024 Mario Döring
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
#ifndef PHP_GLFW_MATH_H
#define PHP_GLFW_MATH_H 1

#include "phpglfw_constants.h"
#include "linmath.h"

/**
 * object structs
 */
typedef struct _phpglfw_math_vec2_object {
    vec2 data;
    zend_object std;
} phpglfw_math_vec2_object; 

typedef struct _phpglfw_math_vec3_object {
    vec3 data;
    zend_object std;
} phpglfw_math_vec3_object; 

typedef struct _phpglfw_math_vec4_object {
    vec4 data;
    zend_object std;
} phpglfw_math_vec4_object; 

typedef struct _phpglfw_math_quat_object {
    quat data;
    zend_object std;
} phpglfw_math_quat_object; 

typedef struct _phpglfw_math_mat4_object {
    mat4x4 data;
    zend_object std;
} phpglfw_math_mat4_object; 


void phpglfw_register_math_module(INIT_FUNC_ARGS);

/**
 * Fetch object helper methods
 */
zend_always_inline phpglfw_math_vec2_object* phpglfw_math_vec2_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_math_vec2_object *) ((char *) (obj) - XtOffsetOf(phpglfw_math_vec2_object, std));
}

zend_always_inline phpglfw_math_vec3_object* phpglfw_math_vec3_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_math_vec3_object *) ((char *) (obj) - XtOffsetOf(phpglfw_math_vec3_object, std));
}

zend_always_inline phpglfw_math_vec4_object* phpglfw_math_vec4_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_math_vec4_object *) ((char *) (obj) - XtOffsetOf(phpglfw_math_vec4_object, std));
}

zend_always_inline phpglfw_math_quat_object* phpglfw_math_quat_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_math_quat_object *) ((char *) (obj) - XtOffsetOf(phpglfw_math_quat_object, std));
}

zend_always_inline phpglfw_math_mat4_object* phpglfw_math_mat4_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_math_mat4_object *) ((char *) (obj) - XtOffsetOf(phpglfw_math_mat4_object, std));
}


/**
 * Class entry getters
 */
zend_class_entry *phpglfw_get_math_vec2_ce(); 
zend_class_entry *phpglfw_get_math_vec3_ce(); 
zend_class_entry *phpglfw_get_math_vec4_ce(); 
zend_class_entry *phpglfw_get_math_quat_ce(); 
zend_class_entry *phpglfw_get_math_mat4_ce(); 

#endif
