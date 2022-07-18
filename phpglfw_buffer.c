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
#include "zend_interfaces.h"

#include "linmath.h"

#define max(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a > _b ? _a : _b;       \
})

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})

zend_class_entry *phpglfw_buffer_interface_ce; 
zend_class_entry *phpglfw_buffer_glfloat_ce; 
zend_class_entry *phpglfw_buffer_gldouble_ce; 
zend_class_entry *phpglfw_buffer_glint_ce; 
zend_class_entry *phpglfw_buffer_glbyte_ce; 

zend_class_entry *phpglfw_get_buffer_interface_ce() {
    return phpglfw_buffer_interface_ce;
}

zend_class_entry *phpglfw_get_buffer_glfloat_ce() {
    return phpglfw_buffer_glfloat_ce;
}
zend_class_entry *phpglfw_get_buffer_gldouble_ce() {
    return phpglfw_buffer_gldouble_ce;
}
zend_class_entry *phpglfw_get_buffer_glint_ce() {
    return phpglfw_buffer_glint_ce;
}
zend_class_entry *phpglfw_get_buffer_glbyte_ce() {
    return phpglfw_buffer_glbyte_ce;
}

/**
 * GL\Buffer\FloatBuffer 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_buffer_glfloat_handlers;

typedef struct _phpglfw_buffer_glfloat_it {
	zend_object_iterator intern;
	size_t current;
} phpglfw_buffer_glfloat_it;


static void phpglfw_buffer_glfloat_free_handler(zend_object *object)
{
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

zend_object *phpglfw_buffer_glfloat_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_buffer_glfloat_object) + zend_object_properties_size(class_type);
    phpglfw_buffer_glfloat_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    intern->vec = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_buffer_glfloat_handlers;

    return &intern->std;
}

static void phpglfw_buffer_glfloat_it_dtor(zend_object_iterator *iter)
{
	zval_ptr_dtor(&iter->data);
}

static void phpglfw_buffer_glfloat_it_rewind(zend_object_iterator *iter)
{
	((phpglfw_buffer_glfloat_it*)iter)->current = 0;
}

static void phpglfw_buffer_glfloat_it_get_current_key(zend_object_iterator *iter, zval *key)
{
	ZVAL_LONG(key, ((phpglfw_buffer_glfloat_it*)iter)->current);
}

static void phpglfw_buffer_glfloat_it_move_forward(zend_object_iterator *iter)
{
	((phpglfw_buffer_glfloat_it*)iter)->current++;
}

static int phpglfw_buffer_glfloat_it_valid(zend_object_iterator *iter)
{
	phpglfw_buffer_glfloat_it *iterator = (phpglfw_buffer_glfloat_it*)iter;
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	if (iterator->current >= 0 && iterator->current < cvector_size(obj_ptr->vec)) {
		return SUCCESS;
	}

	return FAILURE;
}

static zval *phpglfw_buffer_glfloat_it_get_current_data(zend_object_iterator *iter)
{
	zval zindex, *data;
	phpglfw_buffer_glfloat_it *iterator = (phpglfw_buffer_glfloat_it*)iter;
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	ZVAL_LONG(&zindex, iterator->current);
	ZVAL_DOUBLE(data, obj_ptr->vec[iterator->current]);

	if (data == NULL) {
		data = &EG(uninitialized_zval);
	}
	return data;
}

/* iterator handler table */
static const zend_object_iterator_funcs phpglfw_buffer_glfloat_it_funcs = {
	phpglfw_buffer_glfloat_it_dtor,
	phpglfw_buffer_glfloat_it_valid,
	phpglfw_buffer_glfloat_it_get_current_data,
	phpglfw_buffer_glfloat_it_get_current_key,
	phpglfw_buffer_glfloat_it_move_forward,
	phpglfw_buffer_glfloat_it_rewind,
	NULL,
	NULL,
};

zend_object_iterator *phpglfw_buffer_glfloat_get_iterator_handler(zend_class_entry *ce, zval *object, int by_ref)
{
	phpglfw_buffer_glfloat_it *iterator;

	if (by_ref) {
		zend_throw_error(NULL, "An iterator cannot be used with foreach by reference");
		return NULL;
	}

	iterator = emalloc(sizeof(phpglfw_buffer_glfloat_it));

	zend_iterator_init((zend_object_iterator*)iterator);

	ZVAL_OBJ_COPY(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &phpglfw_buffer_glfloat_it_funcs;

	return &iterator->intern;
}

zval *phpglfw_buffer_glfloat_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Buffer\\BufferInterface object");
	}

    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(object);

    if (Z_TYPE_P(offset) == IS_LONG) {
		size_t index = (size_t)Z_LVAL_P(offset);

        if (index < cvector_size(obj_ptr->vec)) {
            ZVAL_DOUBLE(rv, obj_ptr->vec[index]);
        } else {
            ZVAL_NULL(rv);
        }
	} else {
        zend_throw_error(NULL, "Only a int offset '$buffer[int]' can be used with the GL\\Buffer\\BufferInterface object");
		ZVAL_NULL(rv);
	}

	return rv;
}

void phpglfw_buffer_glfloat_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_DOUBLE) {
        zend_throw_error(NULL, "Trying to store non float value in a float type buffer.");
        return;
    }

    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(object);

    // if offset is not given ($buff[] = 3.14)  
	if (offset == NULL) {
        cvector_push_back(obj_ptr->vec, Z_DVAL_P(value));
	} 
    else {
        if (Z_TYPE_P(offset) == IS_LONG) {
            size_t index = (size_t)Z_LVAL_P(offset);

            if (index >= cvector_size(obj_ptr->vec)) {
                zend_throw_error(NULL, "Cannot modify unallocated buffer space, the element at index [%d] does not exist. Use `push` or `fill` to allocate the requested spaces.",  (int) index);
            }

            obj_ptr->vec[index] = Z_DVAL_P(value);
        } else {
            zend_throw_error(NULL, "Only a int offset '$buffer[int]' can be used with the GL\\Buffer\\BufferInterface object");
        }
    }
}

static HashTable *phpglfw_buffer_glfloat_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht, *dataht;

    ht = zend_new_array(2);
    dataht = zend_new_array(127);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

    for(size_t i = 0; i < min(127, cvector_size(obj_ptr->vec)); i++) {
        ZVAL_DOUBLE(&zv, obj_ptr->vec[i]);
        zend_hash_index_update(dataht, i, &zv);
    }


    ZVAL_ARR(&zv, dataht);
    zend_hash_str_update(ht, "data", sizeof("data") - 1, &zv);

    return ht;
}

PHP_METHOD(GL_Buffer_FloatBuffer, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "GL\\Buffer\\FloatBuffer" "(");
    smart_str_append_long(&my_str, cvector_size(obj_ptr->vec));
    smart_str_appends(&my_str, " [");
    smart_str_append_long(&my_str, cvector_capacity(obj_ptr->vec));
    smart_str_appends(&my_str, "])");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(GL_Buffer_FloatBuffer, push)
{
    double value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_push_back(obj_ptr->vec, value);
}

PHP_METHOD(GL_Buffer_FloatBuffer, reserve)
{
    zend_long resvering_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &resvering_size) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_reserve(obj_ptr->vec, resvering_size);
}

PHP_METHOD(GL_Buffer_FloatBuffer, clear)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_free(obj_ptr->vec);
    obj_ptr->vec = NULL;
}

PHP_METHOD(GL_Buffer_FloatBuffer, fill)
{
    double value;
    zend_long fill_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &fill_size, &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_fill(obj_ptr->vec, fill_size, value);
}

PHP_METHOD(GL_Buffer_FloatBuffer, size)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_size(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_FloatBuffer, capacity)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_capacity(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_FloatBuffer, __construct)
{
    HashTable *initaldata;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h!", &initaldata) == FAILURE) {
        return;
    }
    if (initaldata == NULL) {
        return;
    }
    if (zend_hash_num_elements(initaldata) == 0) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // reserve the space
    cvector_reserve(obj_ptr->vec, zend_hash_num_elements(initaldata));

    ZEND_HASH_FOREACH_VAL(initaldata, data)
        if (Z_TYPE_P(data) == IS_DOUBLE) {
            cvector_push_back(obj_ptr->vec, Z_DVAL_P(data));
        } else {
            zend_throw_error(NULL, "All elements of the inital data array has to be of type: float");
        }
    ZEND_HASH_FOREACH_END();
}

/**
 * GL\Buffer\DoubleBuffer 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_buffer_gldouble_handlers;

static void phpglfw_buffer_gldouble_free_handler(zend_object *object)
{
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

zend_object *phpglfw_buffer_gldouble_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_buffer_gldouble_object) + zend_object_properties_size(class_type);
    phpglfw_buffer_gldouble_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    intern->vec = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_buffer_gldouble_handlers;

    return &intern->std;
}

zval *phpglfw_buffer_gldouble_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Buffer\\BufferInterface object");
	}

    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(object);

    if (Z_TYPE_P(offset) == IS_LONG) {
		size_t index = (size_t)Z_LVAL_P(offset);

        if (index < cvector_size(obj_ptr->vec)) {
            ZVAL_DOUBLE(rv, obj_ptr->vec[index]);
        } else {
            ZVAL_NULL(rv);
        }
	} else {
        zend_throw_error(NULL, "Only a int offset '$buffer[int]' can be used with the GL\\Buffer\\BufferInterface object");
		ZVAL_NULL(rv);
	}

	return rv;
}

void phpglfw_buffer_gldouble_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_DOUBLE) {
        zend_throw_error(NULL, "Trying to store non float value in a float type buffer.");
        return;
    }

    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(object);

    // if offset is not given ($buff[] = 3.14)  
	if (offset == NULL) {
        cvector_push_back(obj_ptr->vec, Z_DVAL_P(value));
	} 
    else {
        if (Z_TYPE_P(offset) == IS_LONG) {
            size_t index = (size_t)Z_LVAL_P(offset);

            if (index >= cvector_size(obj_ptr->vec)) {
                zend_throw_error(NULL, "Cannot modify unallocated buffer space, the element at index [%d] does not exist. Use `push` or `fill` to allocate the requested spaces.",  (int) index);
            }

            obj_ptr->vec[index] = Z_DVAL_P(value);
        } else {
            zend_throw_error(NULL, "Only a int offset '$buffer[int]' can be used with the GL\\Buffer\\BufferInterface object");
        }
    }
}

static HashTable *phpglfw_buffer_gldouble_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht, *dataht;

    ht = zend_new_array(2);
    dataht = zend_new_array(127);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

    for(size_t i = 0; i < min(127, cvector_size(obj_ptr->vec)); i++) {
        ZVAL_DOUBLE(&zv, obj_ptr->vec[i]);
        zend_hash_index_update(dataht, i, &zv);
    }


    ZVAL_ARR(&zv, dataht);
    zend_hash_str_update(ht, "data", sizeof("data") - 1, &zv);

    return ht;
}

PHP_METHOD(GL_Buffer_DoubleBuffer, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "GL\\Buffer\\DoubleBuffer" "(");
    smart_str_append_long(&my_str, cvector_size(obj_ptr->vec));
    smart_str_appends(&my_str, " [");
    smart_str_append_long(&my_str, cvector_capacity(obj_ptr->vec));
    smart_str_appends(&my_str, "])");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(GL_Buffer_DoubleBuffer, push)
{
    double value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_push_back(obj_ptr->vec, value);
}

PHP_METHOD(GL_Buffer_DoubleBuffer, reserve)
{
    zend_long resvering_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &resvering_size) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_reserve(obj_ptr->vec, resvering_size);
}

PHP_METHOD(GL_Buffer_DoubleBuffer, clear)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_free(obj_ptr->vec);
    obj_ptr->vec = NULL;
}

PHP_METHOD(GL_Buffer_DoubleBuffer, fill)
{
    double value;
    zend_long fill_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ld", &fill_size, &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_fill(obj_ptr->vec, fill_size, value);
}

PHP_METHOD(GL_Buffer_DoubleBuffer, size)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_size(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_DoubleBuffer, capacity)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_capacity(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_DoubleBuffer, __construct)
{
    HashTable *initaldata;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h!", &initaldata) == FAILURE) {
        return;
    }
    if (initaldata == NULL) {
        return;
    }
    if (zend_hash_num_elements(initaldata) == 0) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // reserve the space
    cvector_reserve(obj_ptr->vec, zend_hash_num_elements(initaldata));

    ZEND_HASH_FOREACH_VAL(initaldata, data)
        if (Z_TYPE_P(data) == IS_DOUBLE) {
            cvector_push_back(obj_ptr->vec, Z_DVAL_P(data));
        } else {
            zend_throw_error(NULL, "All elements of the inital data array has to be of type: float");
        }
    ZEND_HASH_FOREACH_END();
}

/**
 * GL\Buffer\IntBuffer 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_buffer_glint_handlers;

static void phpglfw_buffer_glint_free_handler(zend_object *object)
{
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

zend_object *phpglfw_buffer_glint_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_buffer_glint_object) + zend_object_properties_size(class_type);
    phpglfw_buffer_glint_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    intern->vec = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_buffer_glint_handlers;

    return &intern->std;
}

zval *phpglfw_buffer_glint_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Buffer\\BufferInterface object");
	}

    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(object);

    if (Z_TYPE_P(offset) == IS_LONG) {
		size_t index = (size_t)Z_LVAL_P(offset);

        if (index < cvector_size(obj_ptr->vec)) {
            ZVAL_LONG(rv, obj_ptr->vec[index]);
        } else {
            ZVAL_NULL(rv);
        }
	} else {
        zend_throw_error(NULL, "Only a int offset '$buffer[int]' can be used with the GL\\Buffer\\BufferInterface object");
		ZVAL_NULL(rv);
	}

	return rv;
}

void phpglfw_buffer_glint_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_LONG) {
        zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
        return;
    }

    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(object);

    // if offset is not given ($buff[] = 3.14)  
	if (offset == NULL) {
        cvector_push_back(obj_ptr->vec, Z_LVAL_P(value));
	} 
    else {
        if (Z_TYPE_P(offset) == IS_LONG) {
            size_t index = (size_t)Z_LVAL_P(offset);

            if (index >= cvector_size(obj_ptr->vec)) {
                zend_throw_error(NULL, "Cannot modify unallocated buffer space, the element at index [%d] does not exist. Use `push` or `fill` to allocate the requested spaces.",  (int) index);
            }

            obj_ptr->vec[index] = Z_LVAL_P(value);
        } else {
            zend_throw_error(NULL, "Only a int offset '$buffer[int]' can be used with the GL\\Buffer\\BufferInterface object");
        }
    }
}

static HashTable *phpglfw_buffer_glint_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht, *dataht;

    ht = zend_new_array(2);
    dataht = zend_new_array(127);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

    for(size_t i = 0; i < min(127, cvector_size(obj_ptr->vec)); i++) {
        ZVAL_DOUBLE(&zv, obj_ptr->vec[i]);
        zend_hash_index_update(dataht, i, &zv);
    }


    ZVAL_ARR(&zv, dataht);
    zend_hash_str_update(ht, "data", sizeof("data") - 1, &zv);

    return ht;
}

PHP_METHOD(GL_Buffer_IntBuffer, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "GL\\Buffer\\IntBuffer" "(");
    smart_str_append_long(&my_str, cvector_size(obj_ptr->vec));
    smart_str_appends(&my_str, " [");
    smart_str_append_long(&my_str, cvector_capacity(obj_ptr->vec));
    smart_str_appends(&my_str, "])");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(GL_Buffer_IntBuffer, push)
{
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_push_back(obj_ptr->vec, value);
}

PHP_METHOD(GL_Buffer_IntBuffer, reserve)
{
    zend_long resvering_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &resvering_size) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_reserve(obj_ptr->vec, resvering_size);
}

PHP_METHOD(GL_Buffer_IntBuffer, clear)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_free(obj_ptr->vec);
    obj_ptr->vec = NULL;
}

PHP_METHOD(GL_Buffer_IntBuffer, fill)
{
    zend_long value;
    zend_long fill_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &fill_size, &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_fill(obj_ptr->vec, fill_size, value);
}

PHP_METHOD(GL_Buffer_IntBuffer, size)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_size(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_IntBuffer, capacity)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_capacity(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_IntBuffer, __construct)
{
    HashTable *initaldata;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h!", &initaldata) == FAILURE) {
        return;
    }
    if (initaldata == NULL) {
        return;
    }
    if (zend_hash_num_elements(initaldata) == 0) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // reserve the space
    cvector_reserve(obj_ptr->vec, zend_hash_num_elements(initaldata));

    ZEND_HASH_FOREACH_VAL(initaldata, data)
        if (Z_TYPE_P(data) == IS_LONG) {
            cvector_push_back(obj_ptr->vec, Z_LVAL_P(data));
        } else {
            zend_throw_error(NULL, "All elements of the inital data array has to be of type: int");
        }
    ZEND_HASH_FOREACH_END();
}

/**
 * GL\Buffer\ByteBuffer 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_buffer_glbyte_handlers;

static void phpglfw_buffer_glbyte_free_handler(zend_object *object)
{
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

zend_object *phpglfw_buffer_glbyte_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_buffer_glbyte_object) + zend_object_properties_size(class_type);
    phpglfw_buffer_glbyte_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    intern->vec = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_buffer_glbyte_handlers;

    return &intern->std;
}

zval *phpglfw_buffer_glbyte_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Buffer\\BufferInterface object");
	}

    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(object);

    if (Z_TYPE_P(offset) == IS_LONG) {
		size_t index = (size_t)Z_LVAL_P(offset);

        if (index < cvector_size(obj_ptr->vec)) {
            ZVAL_LONG(rv, obj_ptr->vec[index]);
        } else {
            ZVAL_NULL(rv);
        }
	} else {
        zend_throw_error(NULL, "Only a int offset '$buffer[int]' can be used with the GL\\Buffer\\BufferInterface object");
		ZVAL_NULL(rv);
	}

	return rv;
}

void phpglfw_buffer_glbyte_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_LONG) {
        zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
        return;
    }

    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(object);

    // if offset is not given ($buff[] = 3.14)  
	if (offset == NULL) {
        cvector_push_back(obj_ptr->vec, Z_LVAL_P(value));
	} 
    else {
        if (Z_TYPE_P(offset) == IS_LONG) {
            size_t index = (size_t)Z_LVAL_P(offset);

            if (index >= cvector_size(obj_ptr->vec)) {
                zend_throw_error(NULL, "Cannot modify unallocated buffer space, the element at index [%d] does not exist. Use `push` or `fill` to allocate the requested spaces.",  (int) index);
            }

            obj_ptr->vec[index] = Z_LVAL_P(value);
        } else {
            zend_throw_error(NULL, "Only a int offset '$buffer[int]' can be used with the GL\\Buffer\\BufferInterface object");
        }
    }
}

static HashTable *phpglfw_buffer_glbyte_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht, *dataht;

    ht = zend_new_array(2);
    dataht = zend_new_array(127);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

    for(size_t i = 0; i < min(127, cvector_size(obj_ptr->vec)); i++) {
        ZVAL_DOUBLE(&zv, obj_ptr->vec[i]);
        zend_hash_index_update(dataht, i, &zv);
    }


    ZVAL_ARR(&zv, dataht);
    zend_hash_str_update(ht, "data", sizeof("data") - 1, &zv);

    return ht;
}

PHP_METHOD(GL_Buffer_ByteBuffer, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "GL\\Buffer\\ByteBuffer" "(");
    smart_str_append_long(&my_str, cvector_size(obj_ptr->vec));
    smart_str_appends(&my_str, " [");
    smart_str_append_long(&my_str, cvector_capacity(obj_ptr->vec));
    smart_str_appends(&my_str, "])");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(GL_Buffer_ByteBuffer, push)
{
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_push_back(obj_ptr->vec, value);
}

PHP_METHOD(GL_Buffer_ByteBuffer, reserve)
{
    zend_long resvering_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &resvering_size) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_reserve(obj_ptr->vec, resvering_size);
}

PHP_METHOD(GL_Buffer_ByteBuffer, clear)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_free(obj_ptr->vec);
    obj_ptr->vec = NULL;
}

PHP_METHOD(GL_Buffer_ByteBuffer, fill)
{
    zend_long value;
    zend_long fill_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &fill_size, &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_fill(obj_ptr->vec, fill_size, value);
}

PHP_METHOD(GL_Buffer_ByteBuffer, size)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_size(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_ByteBuffer, capacity)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_capacity(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_ByteBuffer, __construct)
{
    HashTable *initaldata;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h!", &initaldata) == FAILURE) {
        return;
    }
    if (initaldata == NULL) {
        return;
    }
    if (zend_hash_num_elements(initaldata) == 0) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // reserve the space
    cvector_reserve(obj_ptr->vec, zend_hash_num_elements(initaldata));

    ZEND_HASH_FOREACH_VAL(initaldata, data)
        if (Z_TYPE_P(data) == IS_LONG) {
            cvector_push_back(obj_ptr->vec, Z_LVAL_P(data));
        } else {
            zend_throw_error(NULL, "All elements of the inital data array has to be of type: int");
        }
    ZEND_HASH_FOREACH_END();
}


void phpglfw_register_buffer_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;

    // interface
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\BufferInterface", class_GL_Buffer_BufferInterface_methods);
    phpglfw_buffer_interface_ce = zend_register_internal_interface(&tmp_ce);
    
    // float buffer
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\FloatBuffer", class_GL_Buffer_FloatBuffer_methods);
    phpglfw_buffer_glfloat_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_glfloat_ce->create_object = phpglfw_buffer_glfloat_create_handler;
    phpglfw_buffer_glfloat_ce->get_iterator = phpglfw_buffer_glfloat_get_iterator_handler;

	zend_class_implements(phpglfw_buffer_glfloat_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glfloat_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_buffer_glfloat_handlers));
    phpglfw_buffer_glfloat_handlers.free_obj = phpglfw_buffer_glfloat_free_handler;
    phpglfw_buffer_glfloat_handlers.read_dimension = phpglfw_buffer_glfloat_array_get_handler;
    phpglfw_buffer_glfloat_handlers.write_dimension = phpglfw_buffer_glfloat_array_set_handler;
    phpglfw_buffer_glfloat_handlers.get_debug_info = phpglfw_buffer_glfloat_debug_info_handler;
    phpglfw_buffer_glfloat_handlers.offset = XtOffsetOf(phpglfw_buffer_glfloat_object, std);

    // float buffer
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\DoubleBuffer", class_GL_Buffer_DoubleBuffer_methods);
    phpglfw_buffer_gldouble_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_gldouble_ce->create_object = phpglfw_buffer_gldouble_create_handler;

	zend_class_implements(phpglfw_buffer_gldouble_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_gldouble_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_buffer_gldouble_handlers));
    phpglfw_buffer_gldouble_handlers.free_obj = phpglfw_buffer_gldouble_free_handler;
    phpglfw_buffer_gldouble_handlers.read_dimension = phpglfw_buffer_gldouble_array_get_handler;
    phpglfw_buffer_gldouble_handlers.write_dimension = phpglfw_buffer_gldouble_array_set_handler;
    phpglfw_buffer_gldouble_handlers.get_debug_info = phpglfw_buffer_gldouble_debug_info_handler;
    phpglfw_buffer_gldouble_handlers.offset = XtOffsetOf(phpglfw_buffer_gldouble_object, std);

    // float buffer
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\IntBuffer", class_GL_Buffer_IntBuffer_methods);
    phpglfw_buffer_glint_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_glint_ce->create_object = phpglfw_buffer_glint_create_handler;

	zend_class_implements(phpglfw_buffer_glint_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glint_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_buffer_glint_handlers));
    phpglfw_buffer_glint_handlers.free_obj = phpglfw_buffer_glint_free_handler;
    phpglfw_buffer_glint_handlers.read_dimension = phpglfw_buffer_glint_array_get_handler;
    phpglfw_buffer_glint_handlers.write_dimension = phpglfw_buffer_glint_array_set_handler;
    phpglfw_buffer_glint_handlers.get_debug_info = phpglfw_buffer_glint_debug_info_handler;
    phpglfw_buffer_glint_handlers.offset = XtOffsetOf(phpglfw_buffer_glint_object, std);

    // float buffer
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\ByteBuffer", class_GL_Buffer_ByteBuffer_methods);
    phpglfw_buffer_glbyte_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_glbyte_ce->create_object = phpglfw_buffer_glbyte_create_handler;

	zend_class_implements(phpglfw_buffer_glbyte_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glbyte_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_buffer_glbyte_handlers));
    phpglfw_buffer_glbyte_handlers.free_obj = phpglfw_buffer_glbyte_free_handler;
    phpglfw_buffer_glbyte_handlers.read_dimension = phpglfw_buffer_glbyte_array_get_handler;
    phpglfw_buffer_glbyte_handlers.write_dimension = phpglfw_buffer_glbyte_array_set_handler;
    phpglfw_buffer_glbyte_handlers.get_debug_info = phpglfw_buffer_glbyte_debug_info_handler;
    phpglfw_buffer_glbyte_handlers.offset = XtOffsetOf(phpglfw_buffer_glbyte_object, std);

}