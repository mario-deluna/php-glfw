/**
 * PHP-glfw 
 * 
 * Extension: GL Buffers
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
#include "phpglfw_buffer.h"

#include "phpglfw_arginfo.h"

#include "php.h"
#include "Zend/zend_smart_str.h"
#include "cvector.h"
#include "linmath.h"

zend_class_entry *phpglfw_buffer_float_ce; 

/**
 * PGL\Math\Vec3
 * 
 * ----------------------------------------------------------------------------
 */
typedef struct _phpglfw_buffer_float_object {
    cvector_vector_type(float) vec;
    zend_object std;
} phpglfw_buffer_float_object; 

static zend_object_handlers phpglfw_buffer_float_handlers;

static zend_always_inline phpglfw_buffer_float_object* phpglfw_buffer_float_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_buffer_float_object *) ((char *) (obj) - XtOffsetOf(phpglfw_buffer_float_object, std));
}

static void phpglfw_free_buffer_float_storage_handler(phpglfw_buffer_float_object *intern)
{
    zend_object_std_dtor(&intern->std);
    cvector_free(intern->vec);
    efree(intern);
}

zend_object *phpglfw_create_buffer_float_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_buffer_float_object) + zend_object_properties_size(class_type);
    phpglfw_buffer_float_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    intern->vec = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_buffer_float_handlers;

    return &intern->std;
}

static HashTable *phpglfw_buffer_float_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_float_object *obj_ptr = phpglfw_buffer_float_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(3);
    *is_temp = 1;

    // ZVAL_STRING(&zv, "Aadas");
    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

    // ZVAL_DOUBLE(&zv, obj_ptr->vec[1]);
    // zend_hash_str_update(ht, "y", sizeof("y") - 1, &zv);

    // ZVAL_DOUBLE(&zv, obj_ptr->vec[2]);
    // zend_hash_str_update(ht, "z", sizeof("z") - 1, &zv);

    return ht;
}

PHP_METHOD(PGL_Buffer_FBuffer, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_buffer_float_object *obj_ptr = phpglfw_buffer_float_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "GL\\Buffer\\FBuffer(");
    float *it;
    for (it = cvector_begin(obj_ptr->vec); it != cvector_end(obj_ptr->vec); ++it) {
        smart_str_append_double(&my_str, *it, 4, true);
        smart_str_appends(&my_str, ", ");
    }
    
    // smart_str_append_double(&my_str, obj_ptr->vec[1], 4, true);
    // smart_str_appends(&my_str, ", ");
    // smart_str_append_double(&my_str, obj_ptr->vec[2], 4, true);
    // smart_str_appends(&my_str, ")");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(PGL_Buffer_FBuffer, push)
{
    double value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_float_object *obj_ptr = phpglfw_buffer_float_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_push_back(obj_ptr->vec, value);
}

PHP_METHOD(PGL_Buffer_FBuffer, reserve)
{
    zend_long resvering_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &resvering_size) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_float_object *obj_ptr = phpglfw_buffer_float_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_reserve(obj_ptr->vec, resvering_size);
}


void phpglfw_register_buffer_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;
    INIT_CLASS_ENTRY(tmp_ce, "PGL\\Buffer\\FBuffer", class_PGL_Buffer_FBuffer_methods);
    phpglfw_buffer_float_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_float_ce->create_object = phpglfw_create_buffer_float_handler;

    memcpy(&phpglfw_buffer_float_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_buffer_float_handlers));
    phpglfw_buffer_float_handlers.get_debug_info = phpglfw_buffer_float_debug_info_handler;
    phpglfw_buffer_float_handlers.offset = XtOffsetOf(phpglfw_buffer_float_object, std);
}
