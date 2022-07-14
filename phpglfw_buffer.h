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

typedef struct _phpglfw_buffer_float_object {
    cvector_vector_type(float) vec;
    zend_object std;
} phpglfw_buffer_float_object; 

void phpglfw_register_buffer_module(INIT_FUNC_ARGS);

zend_always_inline phpglfw_buffer_float_object* phpglfw_buffer_float_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_buffer_float_object *) ((char *) (obj) - XtOffsetOf(phpglfw_buffer_float_object, std));
}

zend_class_entry *phpglfw_get_buffer_interface_ce();
zend_class_entry *phpglfw_get_buffer_float_ce();

#endif
