/**
 * PHP-glfw 
 * 
 * Extension: GL Buffers
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
#include "phpglfw_buffer.h"

#include "phpglfw.h"
#include "phpglfw_arginfo.h"
#include "phpglfw_math.h"

#include "php.h"
#include "Zend/zend_smart_str.h"
#include "zend_interfaces.h"

#include "linmath.h"
#include "cvector.h"

#define pglmax(a,b) ((a) > (b) ? (a) : (b))
#define pglmin(a,b) ((a) < (b) ? (a) : (b))

zend_class_entry *phpglfw_buffer_interface_ce; 
zend_class_entry *phpglfw_buffer_glfloat_ce; 
zend_class_entry *phpglfw_buffer_glhalf_ce; 
zend_class_entry *phpglfw_buffer_gldouble_ce; 
zend_class_entry *phpglfw_buffer_glint_ce; 
zend_class_entry *phpglfw_buffer_gluint_ce; 
zend_class_entry *phpglfw_buffer_glshort_ce; 
zend_class_entry *phpglfw_buffer_glushort_ce; 
zend_class_entry *phpglfw_buffer_glbyte_ce; 
zend_class_entry *phpglfw_buffer_glubyte_ce; 

zend_class_entry *phpglfw_get_buffer_interface_ce() {
    return phpglfw_buffer_interface_ce;
}

zend_class_entry *phpglfw_get_buffer_glfloat_ce() {
    return phpglfw_buffer_glfloat_ce;
}
zend_class_entry *phpglfw_get_buffer_glhalf_ce() {
    return phpglfw_buffer_glhalf_ce;
}
zend_class_entry *phpglfw_get_buffer_gldouble_ce() {
    return phpglfw_buffer_gldouble_ce;
}
zend_class_entry *phpglfw_get_buffer_glint_ce() {
    return phpglfw_buffer_glint_ce;
}
zend_class_entry *phpglfw_get_buffer_gluint_ce() {
    return phpglfw_buffer_gluint_ce;
}
zend_class_entry *phpglfw_get_buffer_glshort_ce() {
    return phpglfw_buffer_glshort_ce;
}
zend_class_entry *phpglfw_get_buffer_glushort_ce() {
    return phpglfw_buffer_glushort_ce;
}
zend_class_entry *phpglfw_get_buffer_glbyte_ce() {
    return phpglfw_buffer_glbyte_ce;
}
zend_class_entry *phpglfw_get_buffer_glubyte_ce() {
    return phpglfw_buffer_glubyte_ce;
}

phpglfw_buffer_glfloat_object* phpglfw_buffer_glfloat_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_buffer_glfloat_object *) ((char *) (obj) - XtOffsetOf(phpglfw_buffer_glfloat_object, std));
}
phpglfw_buffer_glhalf_object* phpglfw_buffer_glhalf_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_buffer_glhalf_object *) ((char *) (obj) - XtOffsetOf(phpglfw_buffer_glhalf_object, std));
}
phpglfw_buffer_gldouble_object* phpglfw_buffer_gldouble_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_buffer_gldouble_object *) ((char *) (obj) - XtOffsetOf(phpglfw_buffer_gldouble_object, std));
}
phpglfw_buffer_glint_object* phpglfw_buffer_glint_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_buffer_glint_object *) ((char *) (obj) - XtOffsetOf(phpglfw_buffer_glint_object, std));
}
phpglfw_buffer_gluint_object* phpglfw_buffer_gluint_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_buffer_gluint_object *) ((char *) (obj) - XtOffsetOf(phpglfw_buffer_gluint_object, std));
}
phpglfw_buffer_glshort_object* phpglfw_buffer_glshort_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_buffer_glshort_object *) ((char *) (obj) - XtOffsetOf(phpglfw_buffer_glshort_object, std));
}
phpglfw_buffer_glushort_object* phpglfw_buffer_glushort_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_buffer_glushort_object *) ((char *) (obj) - XtOffsetOf(phpglfw_buffer_glushort_object, std));
}
phpglfw_buffer_glbyte_object* phpglfw_buffer_glbyte_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_buffer_glbyte_object *) ((char *) (obj) - XtOffsetOf(phpglfw_buffer_glbyte_object, std));
}
phpglfw_buffer_glubyte_object* phpglfw_buffer_glubyte_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_buffer_glubyte_object *) ((char *) (obj) - XtOffsetOf(phpglfw_buffer_glubyte_object, std));
}

/**
 * GL\Buffer\FloatBuffer 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_buffer_glfloat_handlers;

/**
 * Iterator (GL\Buffer\FloatBuffer )
 */
typedef struct _phpglfw_buffer_glfloat_iterator {
	zend_object_iterator intern;
	size_t index;
	zval current;
} phpglfw_buffer_glfloat_iterator;

static void phpglfw_buffer_glfloat_it_dtor_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glfloat_iterator *I = (phpglfw_buffer_glfloat_iterator*)iter;

	zval_ptr_dtor(&I->intern.data);
    if (!Z_ISUNDEF(I->current)) {
		zval_ptr_dtor(&I->current);
	}
}

static void phpglfw_buffer_glfloat_it_rewind_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glfloat_iterator*)iter)->index = 0;
}

static void phpglfw_buffer_glfloat_it_current_key_handler(zend_object_iterator *iter, zval *key)
{
	ZVAL_LONG(key, ((phpglfw_buffer_glfloat_iterator*)iter)->index);
}

static void phpglfw_buffer_glfloat_it_move_forward_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glfloat_iterator*)iter)->index++;
}

static int phpglfw_buffer_glfloat_it_valid_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glfloat_iterator *iterator = (phpglfw_buffer_glfloat_iterator*)iter;
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	if (iterator->index >= 0 && iterator->index < cvector_size(obj_ptr->vec)) {
		return SUCCESS;
	}

	return FAILURE;
}

static zval *phpglfw_buffer_glfloat_it_current_data_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glfloat_iterator *iterator = (phpglfw_buffer_glfloat_iterator*)iter;
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	ZVAL_DOUBLE(&iterator->current, obj_ptr->vec[iterator->index]);

	return &iterator->current;
}

static const zend_object_iterator_funcs phpglfw_buffer_glfloat_iterator_handlers = {
	phpglfw_buffer_glfloat_it_dtor_handler,
	phpglfw_buffer_glfloat_it_valid_handler,
	phpglfw_buffer_glfloat_it_current_data_handler,
	phpglfw_buffer_glfloat_it_current_key_handler,
	phpglfw_buffer_glfloat_it_move_forward_handler,
	phpglfw_buffer_glfloat_it_rewind_handler,
	NULL,
	NULL,
};

zend_object_iterator *phpglfw_buffer_glfloat_get_iterator_handler(zend_class_entry *ce, zval *object, int by_ref)
{
	phpglfw_buffer_glfloat_iterator *iterator;

	if (by_ref != 0) {
		zend_throw_error(NULL, "GL\\Buffer\\BufferInterface object can not be iterated by reference");
		return NULL;
	}
    
	iterator = emalloc(sizeof(phpglfw_buffer_glfloat_iterator));

	zend_iterator_init((zend_object_iterator*)iterator);

	ZVAL_OBJ_COPY(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &phpglfw_buffer_glfloat_iterator_handlers;
    iterator->index = 0;

	return &iterator->intern;
}

/**
 * Free (GL\Buffer\FloatBuffer )
 */
static void phpglfw_buffer_glfloat_free_handler(zend_object *object)
{
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

/**
 * Creation (GL\Buffer\FloatBuffer )
 */
zend_object *phpglfw_buffer_glfloat_create_handler(zend_class_entry *class_type)
{
    phpglfw_buffer_glfloat_object *intern = zend_object_alloc(sizeof(phpglfw_buffer_glfloat_object), class_type);

    intern->vec = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_buffer_glfloat_handlers;

    return &intern->std;
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
/*
static int phpglfw_buffer_glfloat_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(object));

    size_t item_count = cvector_size(obj_ptr->vec);
    *buf_len = sizeof(size_t) + item_count * sizeof(GLfloat);
    *buffer = emalloc(*buf_len);

    memcpy(*buffer, &item_count, sizeof(size_t));
    memcpy(*buffer + sizeof(size_t), obj_ptr->vec, item_count * sizeof(GLfloat));

    return SUCCESS;
}

int phpglfw_buffer_glfloat_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    const unsigned char *buf_ptr = buf;
    size_t item_count;
    phpglfw_buffer_glfloat_object *obj;

    if (buf_len < sizeof(size_t)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glfloat_object unserialization", 0);
        return FAILURE;
    }

    memcpy(&item_count, buf_ptr, sizeof(size_t));
    buf_ptr += sizeof(size_t);

    if (buf_len < sizeof(size_t) + item_count * sizeof(GLfloat)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glfloat_object unserialization", 0);
        return FAILURE;
    }

    object_init_ex(object, phpglfw_buffer_glfloat_ce);
    obj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(object));
    //obj->vec = emalloc(item_count * sizeof(GLfloat));

    cvector_reserve(obj->vec, item_count);
    cvector_set_size(obj->vec, item_count); 

    // copy the data
    memcpy(obj->vec, buf_ptr, item_count * sizeof(GLfloat));

    return SUCCESS;
}*/

static int phpglfw_buffer_glfloat_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    bool serialize_hex_float = PHPGLFW_G(buffer_serialize_hex_float);
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(object));
    size_t num_elements = cvector_size(obj_ptr->vec);

    // I want the standard serialization format to be human readable and easaly reconstructable
    // which is why I use a simple format of: <num_elements>:<element1> <element2> <element3> ...
    // More efficent serialization formats should be added as seperate, deticated functions
    cvector_vector_type(char) buffer_string = NULL;

    // used to temporarly store the string representation of each element
    // honestly I could not find a proper description of the maximum length of a double represented as 
    // string, after spending an hour down that rabbit hole I decided to just use a buffer of 256 bytes
    char tmp[256]; 

    // reserve some space for the string, its going to be more 
    // at the end but saves the first few reallocs
    cvector_reserve(buffer_string, num_elements * sizeof(GLfloat));

    // write the number of elements
    int offset = sprintf(tmp, "%zu:", num_elements);
    cvector_push_back_array(buffer_string, tmp, offset);

    // write each element
    if (serialize_hex_float) {
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "%a ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }
    } else {
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "%.9g ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }
    }

    // trim away the trailing space
    cvector_pop_back(buffer_string);

    size_t total_size = cvector_size(buffer_string);

    *buffer = (unsigned char *)estrndup(buffer_string, total_size);
    *buf_len = total_size;
    // efree(buf);

    return SUCCESS;
}

static int phpglfw_buffer_glfloat_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    phpglfw_buffer_glfloat_object *obj;

    size_t exp_item_count, item_count;
    char *endptr, *token, *tmp_copy;
    
    // prints the buffer for debugging
    // for (size_t i = 0; i < buf_len; i++) {
    //     printf("%c", buf[i]);
    // }
    // printf("\n");

    // read the number of elements
    exp_item_count = item_count = strtoul((char *)buf, &endptr, 10);
    if (endptr == (char *)buf || *endptr != ':') {
        // Failed to parse the number of elements
        zend_throw_error(NULL, "Invalid format during phpglfw_buffer_glfloat_object unserialization, could not parse the number of elements.");
        return FAILURE;
    }

    // skip the ':'
    endptr++;

    // create a copy of the buffer, we are going to modify it
    // @TODO: when using `strtok` we are modifying the entire buffer,
    // which will cause an issue when we are using the same buffer for multiple elements
    // This copy for sure can be avoided, but im going to tackle that in the future
    tmp_copy = estrndup(endptr, buf_len - (endptr - (char *)buf));

    // make the object
    object_init_ex(object, phpglfw_buffer_glfloat_ce);
    obj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(object));

    cvector_reserve(obj->vec, exp_item_count); 

    // read the elements, check if our endptr is still valid and we have not reached the end of the buffer
    token = strtok(tmp_copy, " ");
    while (token != NULL && item_count > 0) {
                cvector_push_back(obj->vec, atof(token));
                token = strtok(NULL, " ");
        item_count--;
    }

    if (cvector_size(obj->vec) != exp_item_count) {
        zend_throw_error(NULL, "Mismatch in expected item count during phpglfw_buffer_glfloat_object unserialization. Expected: %zu, Found: %zu", exp_item_count, cvector_size(obj->vec));
        return FAILURE;
    }

    return SUCCESS;
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

    for(size_t i = 0; i < pglmin(127, cvector_size(obj_ptr->vec)); i++) {
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

PHP_METHOD(GL_Buffer_FloatBuffer, pushArray)
{
    zval *array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "a", &array) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(array), array) {
        if (Z_TYPE_P(array) != IS_DOUBLE) {
            zend_throw_error(NULL, "Trying to store non float value in a float type buffer.");
            return;
        }

        cvector_push_back(obj_ptr->vec, Z_DVAL_P(array));
    } ZEND_HASH_FOREACH_END();
}


PHP_METHOD(GL_Buffer_FloatBuffer, pushVec2)
{
    zval *vec2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec2, phpglfw_get_math_vec2_ce()) == FAILURE) {
        return;
    }

    phpglfw_math_vec2_object *vec2_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(vec2));

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    for(size_t i = 0; i < 2; i++) {
        cvector_push_back(obj_ptr->vec, vec2_ptr->data[i]);
    }
}

PHP_METHOD(GL_Buffer_FloatBuffer, pushVec3)
{
    zval *vec3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec3, phpglfw_get_math_vec3_ce()) == FAILURE) {
        return;
    }

    phpglfw_math_vec3_object *vec3_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(vec3));

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    for(size_t i = 0; i < 3; i++) {
        cvector_push_back(obj_ptr->vec, vec3_ptr->data[i]);
    }
}

PHP_METHOD(GL_Buffer_FloatBuffer, pushVec4)
{
    zval *vec4;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec4, phpglfw_get_math_vec4_ce()) == FAILURE) {
        return;
    }

    phpglfw_math_vec4_object *vec4_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(vec4));

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    for(size_t i = 0; i < 4; i++) {
        cvector_push_back(obj_ptr->vec, vec4_ptr->data[i]);
    }
}

PHP_METHOD(GL_Buffer_FloatBuffer, pushMat4)
{
    zval *mat4;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &mat4, phpglfw_get_math_mat4_ce()) == FAILURE) {
        return;
    }

    phpglfw_math_mat4_object *mat4_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(mat4));

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    for(size_t i = 0; i < 4; i++) {
        for(size_t j = 0; j < 4; j++) {
            cvector_push_back(obj_ptr->vec, mat4_ptr->data[i][j]);
        }
    }
}

PHP_METHOD(GL_Buffer_FloatBuffer, quantizeToUChar)
{
    bool autonormalize = true;
    double upper_bound = 1.0;
    double lower_bound = 0.0;

    if (zend_parse_parameters(ZEND_NUM_ARGS() , "|bdd", &autonormalize, &lower_bound, &upper_bound) == FAILURE) {
        return;
    }

    float min = lower_bound;
    float max = upper_bound;

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // make the return value a ubyte Buffer
    object_init_ex(return_value, phpglfw_get_buffer_glubyte_ce());
    phpglfw_buffer_glubyte_object *res_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    // determine the min and max values if autonormalize is enabled
    if (autonormalize) {
        for(size_t i = 0; i < cvector_size(obj_ptr->vec); i++) {
            min = pglmin(min, obj_ptr->vec[i]);
            max = pglmax(max, obj_ptr->vec[i]);
        }
    }
    
    // ensure buffer has the correct size
    cvector_reserve(res_ptr->vec, cvector_size(obj_ptr->vec));
    cvector_set_size(res_ptr->vec, cvector_size(obj_ptr->vec));

    // quantize the values
    for(size_t i = 0; i < cvector_size(obj_ptr->vec); i++) {
        res_ptr->vec[i] = (GLubyte) (255.0 * (obj_ptr->vec[i] - min) / (max - min));
    }
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

PHP_METHOD(GL_Buffer_FloatBuffer, dump)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_STRINGL((char *)obj_ptr->vec, cvector_size(obj_ptr->vec) * sizeof(GLfloat));
}

PHP_METHOD(GL_Buffer_FloatBuffer, __construct)
{
    HashTable *initaldata = NULL;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h", &initaldata) == FAILURE) {
        return;
    }
    else if (initaldata == NULL) {
        return;
    }
    else if (zend_hash_num_elements(initaldata) == 0) {
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
 * GL\Buffer\HFloatBuffer 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_buffer_glhalf_handlers;

/**
 * Iterator (GL\Buffer\HFloatBuffer )
 */
typedef struct _phpglfw_buffer_glhalf_iterator {
	zend_object_iterator intern;
	size_t index;
	zval current;
} phpglfw_buffer_glhalf_iterator;

static void phpglfw_buffer_glhalf_it_dtor_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glhalf_iterator *I = (phpglfw_buffer_glhalf_iterator*)iter;

	zval_ptr_dtor(&I->intern.data);
    if (!Z_ISUNDEF(I->current)) {
		zval_ptr_dtor(&I->current);
	}
}

static void phpglfw_buffer_glhalf_it_rewind_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glhalf_iterator*)iter)->index = 0;
}

static void phpglfw_buffer_glhalf_it_current_key_handler(zend_object_iterator *iter, zval *key)
{
	ZVAL_LONG(key, ((phpglfw_buffer_glhalf_iterator*)iter)->index);
}

static void phpglfw_buffer_glhalf_it_move_forward_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glhalf_iterator*)iter)->index++;
}

static int phpglfw_buffer_glhalf_it_valid_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glhalf_iterator *iterator = (phpglfw_buffer_glhalf_iterator*)iter;
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	if (iterator->index >= 0 && iterator->index < cvector_size(obj_ptr->vec)) {
		return SUCCESS;
	}

	return FAILURE;
}

static zval *phpglfw_buffer_glhalf_it_current_data_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glhalf_iterator *iterator = (phpglfw_buffer_glhalf_iterator*)iter;
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	ZVAL_LONG(&iterator->current, obj_ptr->vec[iterator->index]);

	return &iterator->current;
}

static const zend_object_iterator_funcs phpglfw_buffer_glhalf_iterator_handlers = {
	phpglfw_buffer_glhalf_it_dtor_handler,
	phpglfw_buffer_glhalf_it_valid_handler,
	phpglfw_buffer_glhalf_it_current_data_handler,
	phpglfw_buffer_glhalf_it_current_key_handler,
	phpglfw_buffer_glhalf_it_move_forward_handler,
	phpglfw_buffer_glhalf_it_rewind_handler,
	NULL,
	NULL,
};

zend_object_iterator *phpglfw_buffer_glhalf_get_iterator_handler(zend_class_entry *ce, zval *object, int by_ref)
{
	phpglfw_buffer_glhalf_iterator *iterator;

	if (by_ref != 0) {
		zend_throw_error(NULL, "GL\\Buffer\\BufferInterface object can not be iterated by reference");
		return NULL;
	}
    
	iterator = emalloc(sizeof(phpglfw_buffer_glhalf_iterator));

	zend_iterator_init((zend_object_iterator*)iterator);

	ZVAL_OBJ_COPY(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &phpglfw_buffer_glhalf_iterator_handlers;
    iterator->index = 0;

	return &iterator->intern;
}

/**
 * Free (GL\Buffer\HFloatBuffer )
 */
static void phpglfw_buffer_glhalf_free_handler(zend_object *object)
{
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

/**
 * Creation (GL\Buffer\HFloatBuffer )
 */
zend_object *phpglfw_buffer_glhalf_create_handler(zend_class_entry *class_type)
{
    phpglfw_buffer_glhalf_object *intern = zend_object_alloc(sizeof(phpglfw_buffer_glhalf_object), class_type);

    intern->vec = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_buffer_glhalf_handlers;

    return &intern->std;
}

zval *phpglfw_buffer_glhalf_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Buffer\\BufferInterface object");
	}

    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(object);

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

void phpglfw_buffer_glhalf_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_LONG) {
        zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
        return;
    }

    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(object);

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
/*
static int phpglfw_buffer_glhalf_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(object));

    size_t item_count = cvector_size(obj_ptr->vec);
    *buf_len = sizeof(size_t) + item_count * sizeof(GLhalf);
    *buffer = emalloc(*buf_len);

    memcpy(*buffer, &item_count, sizeof(size_t));
    memcpy(*buffer + sizeof(size_t), obj_ptr->vec, item_count * sizeof(GLhalf));

    return SUCCESS;
}

int phpglfw_buffer_glhalf_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    const unsigned char *buf_ptr = buf;
    size_t item_count;
    phpglfw_buffer_glhalf_object *obj;

    if (buf_len < sizeof(size_t)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glhalf_object unserialization", 0);
        return FAILURE;
    }

    memcpy(&item_count, buf_ptr, sizeof(size_t));
    buf_ptr += sizeof(size_t);

    if (buf_len < sizeof(size_t) + item_count * sizeof(GLhalf)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glhalf_object unserialization", 0);
        return FAILURE;
    }

    object_init_ex(object, phpglfw_buffer_glhalf_ce);
    obj = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(object));
    //obj->vec = emalloc(item_count * sizeof(GLhalf));

    cvector_reserve(obj->vec, item_count);
    cvector_set_size(obj->vec, item_count); 

    // copy the data
    memcpy(obj->vec, buf_ptr, item_count * sizeof(GLhalf));

    return SUCCESS;
}*/

static int phpglfw_buffer_glhalf_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(object));
    size_t num_elements = cvector_size(obj_ptr->vec);

    // I want the standard serialization format to be human readable and easaly reconstructable
    // which is why I use a simple format of: <num_elements>:<element1> <element2> <element3> ...
    // More efficent serialization formats should be added as seperate, deticated functions
    cvector_vector_type(char) buffer_string = NULL;

    // used to temporarly store the string representation of each element
    // honestly I could not find a proper description of the maximum length of a double represented as 
    // string, after spending an hour down that rabbit hole I decided to just use a buffer of 256 bytes
    char tmp[256]; 

    // reserve some space for the string, its going to be more 
    // at the end but saves the first few reallocs
    cvector_reserve(buffer_string, num_elements * sizeof(GLhalf));

    // write the number of elements
    int offset = sprintf(tmp, "%zu:", num_elements);
    cvector_push_back_array(buffer_string, tmp, offset);

    // write each element
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "%hu ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }

    // trim away the trailing space
    cvector_pop_back(buffer_string);

    size_t total_size = cvector_size(buffer_string);

    *buffer = (unsigned char *)estrndup(buffer_string, total_size);
    *buf_len = total_size;
    // efree(buf);

    return SUCCESS;
}

static int phpglfw_buffer_glhalf_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    phpglfw_buffer_glhalf_object *obj;

    size_t exp_item_count, item_count;
    char *endptr, *token, *tmp_copy;
    
    // prints the buffer for debugging
    // for (size_t i = 0; i < buf_len; i++) {
    //     printf("%c", buf[i]);
    // }
    // printf("\n");

    // read the number of elements
    exp_item_count = item_count = strtoul((char *)buf, &endptr, 10);
    if (endptr == (char *)buf || *endptr != ':') {
        // Failed to parse the number of elements
        zend_throw_error(NULL, "Invalid format during phpglfw_buffer_glhalf_object unserialization, could not parse the number of elements.");
        return FAILURE;
    }

    // skip the ':'
    endptr++;

    // create a copy of the buffer, we are going to modify it
    // @TODO: when using `strtok` we are modifying the entire buffer,
    // which will cause an issue when we are using the same buffer for multiple elements
    // This copy for sure can be avoided, but im going to tackle that in the future
    tmp_copy = estrndup(endptr, buf_len - (endptr - (char *)buf));

    // make the object
    object_init_ex(object, phpglfw_buffer_glhalf_ce);
    obj = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(object));

    cvector_reserve(obj->vec, exp_item_count); 

    // read the elements, check if our endptr is still valid and we have not reached the end of the buffer
    token = strtok(tmp_copy, " ");
    while (token != NULL && item_count > 0) {
                cvector_push_back(obj->vec, strtol(token, NULL, 10));
                token = strtok(NULL, " ");
        item_count--;
    }

    if (cvector_size(obj->vec) != exp_item_count) {
        zend_throw_error(NULL, "Mismatch in expected item count during phpglfw_buffer_glhalf_object unserialization. Expected: %zu, Found: %zu", exp_item_count, cvector_size(obj->vec));
        return FAILURE;
    }

    return SUCCESS;
}

static HashTable *phpglfw_buffer_glhalf_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht, *dataht;

    ht = zend_new_array(2);
    dataht = zend_new_array(127);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

    for(size_t i = 0; i < pglmin(127, cvector_size(obj_ptr->vec)); i++) {
        ZVAL_LONG(&zv, obj_ptr->vec[i]);
        zend_hash_index_update(dataht, i, &zv);
    }


    ZVAL_ARR(&zv, dataht);
    zend_hash_str_update(ht, "data", sizeof("data") - 1, &zv);

    return ht;
}

PHP_METHOD(GL_Buffer_HFloatBuffer, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "GL\\Buffer\\HFloatBuffer" "(");
    smart_str_append_long(&my_str, cvector_size(obj_ptr->vec));
    smart_str_appends(&my_str, " [");
    smart_str_append_long(&my_str, cvector_capacity(obj_ptr->vec));
    smart_str_appends(&my_str, "])");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(GL_Buffer_HFloatBuffer, push)
{
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_push_back(obj_ptr->vec, value);
}

PHP_METHOD(GL_Buffer_HFloatBuffer, pushArray)
{
    zval *array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "a", &array) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(obj));

    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(array), array) {
        if (Z_TYPE_P(array) != IS_LONG) {
            zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
            return;
        }

        cvector_push_back(obj_ptr->vec, Z_LVAL_P(array));
    } ZEND_HASH_FOREACH_END();
}



PHP_METHOD(GL_Buffer_HFloatBuffer, reserve)
{
    zend_long resvering_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &resvering_size) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_reserve(obj_ptr->vec, resvering_size);
}

PHP_METHOD(GL_Buffer_HFloatBuffer, clear)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_free(obj_ptr->vec);
    obj_ptr->vec = NULL;
}

PHP_METHOD(GL_Buffer_HFloatBuffer, fill)
{
    zend_long value;
    zend_long fill_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &fill_size, &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_fill(obj_ptr->vec, fill_size, value);
}

PHP_METHOD(GL_Buffer_HFloatBuffer, size)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_size(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_HFloatBuffer, capacity)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_capacity(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_HFloatBuffer, dump)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_STRINGL((char *)obj_ptr->vec, cvector_size(obj_ptr->vec) * sizeof(GLhalf));
}

PHP_METHOD(GL_Buffer_HFloatBuffer, __construct)
{
    HashTable *initaldata = NULL;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h", &initaldata) == FAILURE) {
        return;
    }
    else if (initaldata == NULL) {
        return;
    }
    else if (zend_hash_num_elements(initaldata) == 0) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glhalf_object *obj_ptr = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(obj));

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
 * GL\Buffer\DoubleBuffer 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_buffer_gldouble_handlers;

/**
 * Iterator (GL\Buffer\DoubleBuffer )
 */
typedef struct _phpglfw_buffer_gldouble_iterator {
	zend_object_iterator intern;
	size_t index;
	zval current;
} phpglfw_buffer_gldouble_iterator;

static void phpglfw_buffer_gldouble_it_dtor_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_gldouble_iterator *I = (phpglfw_buffer_gldouble_iterator*)iter;

	zval_ptr_dtor(&I->intern.data);
    if (!Z_ISUNDEF(I->current)) {
		zval_ptr_dtor(&I->current);
	}
}

static void phpglfw_buffer_gldouble_it_rewind_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_gldouble_iterator*)iter)->index = 0;
}

static void phpglfw_buffer_gldouble_it_current_key_handler(zend_object_iterator *iter, zval *key)
{
	ZVAL_LONG(key, ((phpglfw_buffer_gldouble_iterator*)iter)->index);
}

static void phpglfw_buffer_gldouble_it_move_forward_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_gldouble_iterator*)iter)->index++;
}

static int phpglfw_buffer_gldouble_it_valid_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_gldouble_iterator *iterator = (phpglfw_buffer_gldouble_iterator*)iter;
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	if (iterator->index >= 0 && iterator->index < cvector_size(obj_ptr->vec)) {
		return SUCCESS;
	}

	return FAILURE;
}

static zval *phpglfw_buffer_gldouble_it_current_data_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_gldouble_iterator *iterator = (phpglfw_buffer_gldouble_iterator*)iter;
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	ZVAL_DOUBLE(&iterator->current, obj_ptr->vec[iterator->index]);

	return &iterator->current;
}

static const zend_object_iterator_funcs phpglfw_buffer_gldouble_iterator_handlers = {
	phpglfw_buffer_gldouble_it_dtor_handler,
	phpglfw_buffer_gldouble_it_valid_handler,
	phpglfw_buffer_gldouble_it_current_data_handler,
	phpglfw_buffer_gldouble_it_current_key_handler,
	phpglfw_buffer_gldouble_it_move_forward_handler,
	phpglfw_buffer_gldouble_it_rewind_handler,
	NULL,
	NULL,
};

zend_object_iterator *phpglfw_buffer_gldouble_get_iterator_handler(zend_class_entry *ce, zval *object, int by_ref)
{
	phpglfw_buffer_gldouble_iterator *iterator;

	if (by_ref != 0) {
		zend_throw_error(NULL, "GL\\Buffer\\BufferInterface object can not be iterated by reference");
		return NULL;
	}
    
	iterator = emalloc(sizeof(phpglfw_buffer_gldouble_iterator));

	zend_iterator_init((zend_object_iterator*)iterator);

	ZVAL_OBJ_COPY(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &phpglfw_buffer_gldouble_iterator_handlers;
    iterator->index = 0;

	return &iterator->intern;
}

/**
 * Free (GL\Buffer\DoubleBuffer )
 */
static void phpglfw_buffer_gldouble_free_handler(zend_object *object)
{
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

/**
 * Creation (GL\Buffer\DoubleBuffer )
 */
zend_object *phpglfw_buffer_gldouble_create_handler(zend_class_entry *class_type)
{
    phpglfw_buffer_gldouble_object *intern = zend_object_alloc(sizeof(phpglfw_buffer_gldouble_object), class_type);

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
/*
static int phpglfw_buffer_gldouble_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(object));

    size_t item_count = cvector_size(obj_ptr->vec);
    *buf_len = sizeof(size_t) + item_count * sizeof(GLdouble);
    *buffer = emalloc(*buf_len);

    memcpy(*buffer, &item_count, sizeof(size_t));
    memcpy(*buffer + sizeof(size_t), obj_ptr->vec, item_count * sizeof(GLdouble));

    return SUCCESS;
}

int phpglfw_buffer_gldouble_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    const unsigned char *buf_ptr = buf;
    size_t item_count;
    phpglfw_buffer_gldouble_object *obj;

    if (buf_len < sizeof(size_t)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_gldouble_object unserialization", 0);
        return FAILURE;
    }

    memcpy(&item_count, buf_ptr, sizeof(size_t));
    buf_ptr += sizeof(size_t);

    if (buf_len < sizeof(size_t) + item_count * sizeof(GLdouble)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_gldouble_object unserialization", 0);
        return FAILURE;
    }

    object_init_ex(object, phpglfw_buffer_gldouble_ce);
    obj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(object));
    //obj->vec = emalloc(item_count * sizeof(GLdouble));

    cvector_reserve(obj->vec, item_count);
    cvector_set_size(obj->vec, item_count); 

    // copy the data
    memcpy(obj->vec, buf_ptr, item_count * sizeof(GLdouble));

    return SUCCESS;
}*/

static int phpglfw_buffer_gldouble_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    bool serialize_hex_float = PHPGLFW_G(buffer_serialize_hex_float);
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(object));
    size_t num_elements = cvector_size(obj_ptr->vec);

    // I want the standard serialization format to be human readable and easaly reconstructable
    // which is why I use a simple format of: <num_elements>:<element1> <element2> <element3> ...
    // More efficent serialization formats should be added as seperate, deticated functions
    cvector_vector_type(char) buffer_string = NULL;

    // used to temporarly store the string representation of each element
    // honestly I could not find a proper description of the maximum length of a double represented as 
    // string, after spending an hour down that rabbit hole I decided to just use a buffer of 256 bytes
    char tmp[256]; 

    // reserve some space for the string, its going to be more 
    // at the end but saves the first few reallocs
    cvector_reserve(buffer_string, num_elements * sizeof(GLdouble));

    // write the number of elements
    int offset = sprintf(tmp, "%zu:", num_elements);
    cvector_push_back_array(buffer_string, tmp, offset);

    // write each element
    if (serialize_hex_float) {
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "%a ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }
    } else {
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "%.17g ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }
    }

    // trim away the trailing space
    cvector_pop_back(buffer_string);

    size_t total_size = cvector_size(buffer_string);

    *buffer = (unsigned char *)estrndup(buffer_string, total_size);
    *buf_len = total_size;
    // efree(buf);

    return SUCCESS;
}

static int phpglfw_buffer_gldouble_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    phpglfw_buffer_gldouble_object *obj;

    size_t exp_item_count, item_count;
    char *endptr, *token, *tmp_copy;
    
    // prints the buffer for debugging
    // for (size_t i = 0; i < buf_len; i++) {
    //     printf("%c", buf[i]);
    // }
    // printf("\n");

    // read the number of elements
    exp_item_count = item_count = strtoul((char *)buf, &endptr, 10);
    if (endptr == (char *)buf || *endptr != ':') {
        // Failed to parse the number of elements
        zend_throw_error(NULL, "Invalid format during phpglfw_buffer_gldouble_object unserialization, could not parse the number of elements.");
        return FAILURE;
    }

    // skip the ':'
    endptr++;

    // create a copy of the buffer, we are going to modify it
    // @TODO: when using `strtok` we are modifying the entire buffer,
    // which will cause an issue when we are using the same buffer for multiple elements
    // This copy for sure can be avoided, but im going to tackle that in the future
    tmp_copy = estrndup(endptr, buf_len - (endptr - (char *)buf));

    // make the object
    object_init_ex(object, phpglfw_buffer_gldouble_ce);
    obj = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(object));

    cvector_reserve(obj->vec, exp_item_count); 

    // read the elements, check if our endptr is still valid and we have not reached the end of the buffer
    token = strtok(tmp_copy, " ");
    while (token != NULL && item_count > 0) {
                cvector_push_back(obj->vec, atof(token));
                token = strtok(NULL, " ");
        item_count--;
    }

    if (cvector_size(obj->vec) != exp_item_count) {
        zend_throw_error(NULL, "Mismatch in expected item count during phpglfw_buffer_gldouble_object unserialization. Expected: %zu, Found: %zu", exp_item_count, cvector_size(obj->vec));
        return FAILURE;
    }

    return SUCCESS;
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

    for(size_t i = 0; i < pglmin(127, cvector_size(obj_ptr->vec)); i++) {
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

PHP_METHOD(GL_Buffer_DoubleBuffer, pushArray)
{
    zval *array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "a", &array) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(obj));

    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(array), array) {
        if (Z_TYPE_P(array) != IS_DOUBLE) {
            zend_throw_error(NULL, "Trying to store non float value in a float type buffer.");
            return;
        }

        cvector_push_back(obj_ptr->vec, Z_DVAL_P(array));
    } ZEND_HASH_FOREACH_END();
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

PHP_METHOD(GL_Buffer_DoubleBuffer, dump)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_STRINGL((char *)obj_ptr->vec, cvector_size(obj_ptr->vec) * sizeof(GLdouble));
}

PHP_METHOD(GL_Buffer_DoubleBuffer, __construct)
{
    HashTable *initaldata = NULL;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h", &initaldata) == FAILURE) {
        return;
    }
    else if (initaldata == NULL) {
        return;
    }
    else if (zend_hash_num_elements(initaldata) == 0) {
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

/**
 * Iterator (GL\Buffer\IntBuffer )
 */
typedef struct _phpglfw_buffer_glint_iterator {
	zend_object_iterator intern;
	size_t index;
	zval current;
} phpglfw_buffer_glint_iterator;

static void phpglfw_buffer_glint_it_dtor_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glint_iterator *I = (phpglfw_buffer_glint_iterator*)iter;

	zval_ptr_dtor(&I->intern.data);
    if (!Z_ISUNDEF(I->current)) {
		zval_ptr_dtor(&I->current);
	}
}

static void phpglfw_buffer_glint_it_rewind_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glint_iterator*)iter)->index = 0;
}

static void phpglfw_buffer_glint_it_current_key_handler(zend_object_iterator *iter, zval *key)
{
	ZVAL_LONG(key, ((phpglfw_buffer_glint_iterator*)iter)->index);
}

static void phpglfw_buffer_glint_it_move_forward_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glint_iterator*)iter)->index++;
}

static int phpglfw_buffer_glint_it_valid_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glint_iterator *iterator = (phpglfw_buffer_glint_iterator*)iter;
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	if (iterator->index >= 0 && iterator->index < cvector_size(obj_ptr->vec)) {
		return SUCCESS;
	}

	return FAILURE;
}

static zval *phpglfw_buffer_glint_it_current_data_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glint_iterator *iterator = (phpglfw_buffer_glint_iterator*)iter;
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	ZVAL_LONG(&iterator->current, obj_ptr->vec[iterator->index]);

	return &iterator->current;
}

static const zend_object_iterator_funcs phpglfw_buffer_glint_iterator_handlers = {
	phpglfw_buffer_glint_it_dtor_handler,
	phpglfw_buffer_glint_it_valid_handler,
	phpglfw_buffer_glint_it_current_data_handler,
	phpglfw_buffer_glint_it_current_key_handler,
	phpglfw_buffer_glint_it_move_forward_handler,
	phpglfw_buffer_glint_it_rewind_handler,
	NULL,
	NULL,
};

zend_object_iterator *phpglfw_buffer_glint_get_iterator_handler(zend_class_entry *ce, zval *object, int by_ref)
{
	phpglfw_buffer_glint_iterator *iterator;

	if (by_ref != 0) {
		zend_throw_error(NULL, "GL\\Buffer\\BufferInterface object can not be iterated by reference");
		return NULL;
	}
    
	iterator = emalloc(sizeof(phpglfw_buffer_glint_iterator));

	zend_iterator_init((zend_object_iterator*)iterator);

	ZVAL_OBJ_COPY(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &phpglfw_buffer_glint_iterator_handlers;
    iterator->index = 0;

	return &iterator->intern;
}

/**
 * Free (GL\Buffer\IntBuffer )
 */
static void phpglfw_buffer_glint_free_handler(zend_object *object)
{
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

/**
 * Creation (GL\Buffer\IntBuffer )
 */
zend_object *phpglfw_buffer_glint_create_handler(zend_class_entry *class_type)
{
    phpglfw_buffer_glint_object *intern = zend_object_alloc(sizeof(phpglfw_buffer_glint_object), class_type);

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
/*
static int phpglfw_buffer_glint_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(object));

    size_t item_count = cvector_size(obj_ptr->vec);
    *buf_len = sizeof(size_t) + item_count * sizeof(GLint);
    *buffer = emalloc(*buf_len);

    memcpy(*buffer, &item_count, sizeof(size_t));
    memcpy(*buffer + sizeof(size_t), obj_ptr->vec, item_count * sizeof(GLint));

    return SUCCESS;
}

int phpglfw_buffer_glint_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    const unsigned char *buf_ptr = buf;
    size_t item_count;
    phpglfw_buffer_glint_object *obj;

    if (buf_len < sizeof(size_t)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glint_object unserialization", 0);
        return FAILURE;
    }

    memcpy(&item_count, buf_ptr, sizeof(size_t));
    buf_ptr += sizeof(size_t);

    if (buf_len < sizeof(size_t) + item_count * sizeof(GLint)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glint_object unserialization", 0);
        return FAILURE;
    }

    object_init_ex(object, phpglfw_buffer_glint_ce);
    obj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(object));
    //obj->vec = emalloc(item_count * sizeof(GLint));

    cvector_reserve(obj->vec, item_count);
    cvector_set_size(obj->vec, item_count); 

    // copy the data
    memcpy(obj->vec, buf_ptr, item_count * sizeof(GLint));

    return SUCCESS;
}*/

static int phpglfw_buffer_glint_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(object));
    size_t num_elements = cvector_size(obj_ptr->vec);

    // I want the standard serialization format to be human readable and easaly reconstructable
    // which is why I use a simple format of: <num_elements>:<element1> <element2> <element3> ...
    // More efficent serialization formats should be added as seperate, deticated functions
    cvector_vector_type(char) buffer_string = NULL;

    // used to temporarly store the string representation of each element
    // honestly I could not find a proper description of the maximum length of a double represented as 
    // string, after spending an hour down that rabbit hole I decided to just use a buffer of 256 bytes
    char tmp[256]; 

    // reserve some space for the string, its going to be more 
    // at the end but saves the first few reallocs
    cvector_reserve(buffer_string, num_elements * sizeof(GLint));

    // write the number of elements
    int offset = sprintf(tmp, "%zu:", num_elements);
    cvector_push_back_array(buffer_string, tmp, offset);

    // write each element
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "%d ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }

    // trim away the trailing space
    cvector_pop_back(buffer_string);

    size_t total_size = cvector_size(buffer_string);

    *buffer = (unsigned char *)estrndup(buffer_string, total_size);
    *buf_len = total_size;
    // efree(buf);

    return SUCCESS;
}

static int phpglfw_buffer_glint_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    phpglfw_buffer_glint_object *obj;

    size_t exp_item_count, item_count;
    char *endptr, *token, *tmp_copy;
    
    // prints the buffer for debugging
    // for (size_t i = 0; i < buf_len; i++) {
    //     printf("%c", buf[i]);
    // }
    // printf("\n");

    // read the number of elements
    exp_item_count = item_count = strtoul((char *)buf, &endptr, 10);
    if (endptr == (char *)buf || *endptr != ':') {
        // Failed to parse the number of elements
        zend_throw_error(NULL, "Invalid format during phpglfw_buffer_glint_object unserialization, could not parse the number of elements.");
        return FAILURE;
    }

    // skip the ':'
    endptr++;

    // create a copy of the buffer, we are going to modify it
    // @TODO: when using `strtok` we are modifying the entire buffer,
    // which will cause an issue when we are using the same buffer for multiple elements
    // This copy for sure can be avoided, but im going to tackle that in the future
    tmp_copy = estrndup(endptr, buf_len - (endptr - (char *)buf));

    // make the object
    object_init_ex(object, phpglfw_buffer_glint_ce);
    obj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(object));

    cvector_reserve(obj->vec, exp_item_count); 

    // read the elements, check if our endptr is still valid and we have not reached the end of the buffer
    token = strtok(tmp_copy, " ");
    while (token != NULL && item_count > 0) {
                cvector_push_back(obj->vec, strtol(token, NULL, 10));
                token = strtok(NULL, " ");
        item_count--;
    }

    if (cvector_size(obj->vec) != exp_item_count) {
        zend_throw_error(NULL, "Mismatch in expected item count during phpglfw_buffer_glint_object unserialization. Expected: %zu, Found: %zu", exp_item_count, cvector_size(obj->vec));
        return FAILURE;
    }

    return SUCCESS;
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

    for(size_t i = 0; i < pglmin(127, cvector_size(obj_ptr->vec)); i++) {
        ZVAL_LONG(&zv, obj_ptr->vec[i]);
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

PHP_METHOD(GL_Buffer_IntBuffer, pushArray)
{
    zval *array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "a", &array) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(array), array) {
        if (Z_TYPE_P(array) != IS_LONG) {
            zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
            return;
        }

        cvector_push_back(obj_ptr->vec, Z_LVAL_P(array));
    } ZEND_HASH_FOREACH_END();
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

PHP_METHOD(GL_Buffer_IntBuffer, dump)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_STRINGL((char *)obj_ptr->vec, cvector_size(obj_ptr->vec) * sizeof(GLint));
}

PHP_METHOD(GL_Buffer_IntBuffer, __construct)
{
    HashTable *initaldata = NULL;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h", &initaldata) == FAILURE) {
        return;
    }
    else if (initaldata == NULL) {
        return;
    }
    else if (zend_hash_num_elements(initaldata) == 0) {
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
 * GL\Buffer\UIntBuffer 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_buffer_gluint_handlers;

/**
 * Iterator (GL\Buffer\UIntBuffer )
 */
typedef struct _phpglfw_buffer_gluint_iterator {
	zend_object_iterator intern;
	size_t index;
	zval current;
} phpglfw_buffer_gluint_iterator;

static void phpglfw_buffer_gluint_it_dtor_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_gluint_iterator *I = (phpglfw_buffer_gluint_iterator*)iter;

	zval_ptr_dtor(&I->intern.data);
    if (!Z_ISUNDEF(I->current)) {
		zval_ptr_dtor(&I->current);
	}
}

static void phpglfw_buffer_gluint_it_rewind_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_gluint_iterator*)iter)->index = 0;
}

static void phpglfw_buffer_gluint_it_current_key_handler(zend_object_iterator *iter, zval *key)
{
	ZVAL_LONG(key, ((phpglfw_buffer_gluint_iterator*)iter)->index);
}

static void phpglfw_buffer_gluint_it_move_forward_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_gluint_iterator*)iter)->index++;
}

static int phpglfw_buffer_gluint_it_valid_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_gluint_iterator *iterator = (phpglfw_buffer_gluint_iterator*)iter;
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	if (iterator->index >= 0 && iterator->index < cvector_size(obj_ptr->vec)) {
		return SUCCESS;
	}

	return FAILURE;
}

static zval *phpglfw_buffer_gluint_it_current_data_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_gluint_iterator *iterator = (phpglfw_buffer_gluint_iterator*)iter;
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	ZVAL_LONG(&iterator->current, obj_ptr->vec[iterator->index]);

	return &iterator->current;
}

static const zend_object_iterator_funcs phpglfw_buffer_gluint_iterator_handlers = {
	phpglfw_buffer_gluint_it_dtor_handler,
	phpglfw_buffer_gluint_it_valid_handler,
	phpglfw_buffer_gluint_it_current_data_handler,
	phpglfw_buffer_gluint_it_current_key_handler,
	phpglfw_buffer_gluint_it_move_forward_handler,
	phpglfw_buffer_gluint_it_rewind_handler,
	NULL,
	NULL,
};

zend_object_iterator *phpglfw_buffer_gluint_get_iterator_handler(zend_class_entry *ce, zval *object, int by_ref)
{
	phpglfw_buffer_gluint_iterator *iterator;

	if (by_ref != 0) {
		zend_throw_error(NULL, "GL\\Buffer\\BufferInterface object can not be iterated by reference");
		return NULL;
	}
    
	iterator = emalloc(sizeof(phpglfw_buffer_gluint_iterator));

	zend_iterator_init((zend_object_iterator*)iterator);

	ZVAL_OBJ_COPY(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &phpglfw_buffer_gluint_iterator_handlers;
    iterator->index = 0;

	return &iterator->intern;
}

/**
 * Free (GL\Buffer\UIntBuffer )
 */
static void phpglfw_buffer_gluint_free_handler(zend_object *object)
{
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

/**
 * Creation (GL\Buffer\UIntBuffer )
 */
zend_object *phpglfw_buffer_gluint_create_handler(zend_class_entry *class_type)
{
    phpglfw_buffer_gluint_object *intern = zend_object_alloc(sizeof(phpglfw_buffer_gluint_object), class_type);

    intern->vec = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_buffer_gluint_handlers;

    return &intern->std;
}

zval *phpglfw_buffer_gluint_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Buffer\\BufferInterface object");
	}

    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(object);

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

void phpglfw_buffer_gluint_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_LONG) {
        zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
        return;
    }

    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(object);

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
/*
static int phpglfw_buffer_gluint_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(object));

    size_t item_count = cvector_size(obj_ptr->vec);
    *buf_len = sizeof(size_t) + item_count * sizeof(GLuint);
    *buffer = emalloc(*buf_len);

    memcpy(*buffer, &item_count, sizeof(size_t));
    memcpy(*buffer + sizeof(size_t), obj_ptr->vec, item_count * sizeof(GLuint));

    return SUCCESS;
}

int phpglfw_buffer_gluint_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    const unsigned char *buf_ptr = buf;
    size_t item_count;
    phpglfw_buffer_gluint_object *obj;

    if (buf_len < sizeof(size_t)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_gluint_object unserialization", 0);
        return FAILURE;
    }

    memcpy(&item_count, buf_ptr, sizeof(size_t));
    buf_ptr += sizeof(size_t);

    if (buf_len < sizeof(size_t) + item_count * sizeof(GLuint)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_gluint_object unserialization", 0);
        return FAILURE;
    }

    object_init_ex(object, phpglfw_buffer_gluint_ce);
    obj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(object));
    //obj->vec = emalloc(item_count * sizeof(GLuint));

    cvector_reserve(obj->vec, item_count);
    cvector_set_size(obj->vec, item_count); 

    // copy the data
    memcpy(obj->vec, buf_ptr, item_count * sizeof(GLuint));

    return SUCCESS;
}*/

static int phpglfw_buffer_gluint_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(object));
    size_t num_elements = cvector_size(obj_ptr->vec);

    // I want the standard serialization format to be human readable and easaly reconstructable
    // which is why I use a simple format of: <num_elements>:<element1> <element2> <element3> ...
    // More efficent serialization formats should be added as seperate, deticated functions
    cvector_vector_type(char) buffer_string = NULL;

    // used to temporarly store the string representation of each element
    // honestly I could not find a proper description of the maximum length of a double represented as 
    // string, after spending an hour down that rabbit hole I decided to just use a buffer of 256 bytes
    char tmp[256]; 

    // reserve some space for the string, its going to be more 
    // at the end but saves the first few reallocs
    cvector_reserve(buffer_string, num_elements * sizeof(GLuint));

    // write the number of elements
    int offset = sprintf(tmp, "%zu:", num_elements);
    cvector_push_back_array(buffer_string, tmp, offset);

    // write each element
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "%u ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }

    // trim away the trailing space
    cvector_pop_back(buffer_string);

    size_t total_size = cvector_size(buffer_string);

    *buffer = (unsigned char *)estrndup(buffer_string, total_size);
    *buf_len = total_size;
    // efree(buf);

    return SUCCESS;
}

static int phpglfw_buffer_gluint_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    phpglfw_buffer_gluint_object *obj;

    size_t exp_item_count, item_count;
    char *endptr, *token, *tmp_copy;
    
    // prints the buffer for debugging
    // for (size_t i = 0; i < buf_len; i++) {
    //     printf("%c", buf[i]);
    // }
    // printf("\n");

    // read the number of elements
    exp_item_count = item_count = strtoul((char *)buf, &endptr, 10);
    if (endptr == (char *)buf || *endptr != ':') {
        // Failed to parse the number of elements
        zend_throw_error(NULL, "Invalid format during phpglfw_buffer_gluint_object unserialization, could not parse the number of elements.");
        return FAILURE;
    }

    // skip the ':'
    endptr++;

    // create a copy of the buffer, we are going to modify it
    // @TODO: when using `strtok` we are modifying the entire buffer,
    // which will cause an issue when we are using the same buffer for multiple elements
    // This copy for sure can be avoided, but im going to tackle that in the future
    tmp_copy = estrndup(endptr, buf_len - (endptr - (char *)buf));

    // make the object
    object_init_ex(object, phpglfw_buffer_gluint_ce);
    obj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(object));

    cvector_reserve(obj->vec, exp_item_count); 

    // read the elements, check if our endptr is still valid and we have not reached the end of the buffer
    token = strtok(tmp_copy, " ");
    while (token != NULL && item_count > 0) {
                cvector_push_back(obj->vec, strtol(token, NULL, 10));
                token = strtok(NULL, " ");
        item_count--;
    }

    if (cvector_size(obj->vec) != exp_item_count) {
        zend_throw_error(NULL, "Mismatch in expected item count during phpglfw_buffer_gluint_object unserialization. Expected: %zu, Found: %zu", exp_item_count, cvector_size(obj->vec));
        return FAILURE;
    }

    return SUCCESS;
}

static HashTable *phpglfw_buffer_gluint_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht, *dataht;

    ht = zend_new_array(2);
    dataht = zend_new_array(127);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

    for(size_t i = 0; i < pglmin(127, cvector_size(obj_ptr->vec)); i++) {
        ZVAL_LONG(&zv, obj_ptr->vec[i]);
        zend_hash_index_update(dataht, i, &zv);
    }


    ZVAL_ARR(&zv, dataht);
    zend_hash_str_update(ht, "data", sizeof("data") - 1, &zv);

    return ht;
}

PHP_METHOD(GL_Buffer_UIntBuffer, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "GL\\Buffer\\UIntBuffer" "(");
    smart_str_append_long(&my_str, cvector_size(obj_ptr->vec));
    smart_str_appends(&my_str, " [");
    smart_str_append_long(&my_str, cvector_capacity(obj_ptr->vec));
    smart_str_appends(&my_str, "])");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(GL_Buffer_UIntBuffer, push)
{
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_push_back(obj_ptr->vec, value);
}

PHP_METHOD(GL_Buffer_UIntBuffer, pushArray)
{
    zval *array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "a", &array) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(array), array) {
        if (Z_TYPE_P(array) != IS_LONG) {
            zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
            return;
        }

        cvector_push_back(obj_ptr->vec, Z_LVAL_P(array));
    } ZEND_HASH_FOREACH_END();
}



PHP_METHOD(GL_Buffer_UIntBuffer, reserve)
{
    zend_long resvering_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &resvering_size) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_reserve(obj_ptr->vec, resvering_size);
}

PHP_METHOD(GL_Buffer_UIntBuffer, clear)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_free(obj_ptr->vec);
    obj_ptr->vec = NULL;
}

PHP_METHOD(GL_Buffer_UIntBuffer, fill)
{
    zend_long value;
    zend_long fill_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &fill_size, &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_fill(obj_ptr->vec, fill_size, value);
}

PHP_METHOD(GL_Buffer_UIntBuffer, size)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_size(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_UIntBuffer, capacity)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_capacity(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_UIntBuffer, dump)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_STRINGL((char *)obj_ptr->vec, cvector_size(obj_ptr->vec) * sizeof(GLuint));
}

PHP_METHOD(GL_Buffer_UIntBuffer, __construct)
{
    HashTable *initaldata = NULL;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h", &initaldata) == FAILURE) {
        return;
    }
    else if (initaldata == NULL) {
        return;
    }
    else if (zend_hash_num_elements(initaldata) == 0) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(obj));

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
 * GL\Buffer\ShortBuffer 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_buffer_glshort_handlers;

/**
 * Iterator (GL\Buffer\ShortBuffer )
 */
typedef struct _phpglfw_buffer_glshort_iterator {
	zend_object_iterator intern;
	size_t index;
	zval current;
} phpglfw_buffer_glshort_iterator;

static void phpglfw_buffer_glshort_it_dtor_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glshort_iterator *I = (phpglfw_buffer_glshort_iterator*)iter;

	zval_ptr_dtor(&I->intern.data);
    if (!Z_ISUNDEF(I->current)) {
		zval_ptr_dtor(&I->current);
	}
}

static void phpglfw_buffer_glshort_it_rewind_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glshort_iterator*)iter)->index = 0;
}

static void phpglfw_buffer_glshort_it_current_key_handler(zend_object_iterator *iter, zval *key)
{
	ZVAL_LONG(key, ((phpglfw_buffer_glshort_iterator*)iter)->index);
}

static void phpglfw_buffer_glshort_it_move_forward_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glshort_iterator*)iter)->index++;
}

static int phpglfw_buffer_glshort_it_valid_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glshort_iterator *iterator = (phpglfw_buffer_glshort_iterator*)iter;
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	if (iterator->index >= 0 && iterator->index < cvector_size(obj_ptr->vec)) {
		return SUCCESS;
	}

	return FAILURE;
}

static zval *phpglfw_buffer_glshort_it_current_data_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glshort_iterator *iterator = (phpglfw_buffer_glshort_iterator*)iter;
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	ZVAL_LONG(&iterator->current, obj_ptr->vec[iterator->index]);

	return &iterator->current;
}

static const zend_object_iterator_funcs phpglfw_buffer_glshort_iterator_handlers = {
	phpglfw_buffer_glshort_it_dtor_handler,
	phpglfw_buffer_glshort_it_valid_handler,
	phpglfw_buffer_glshort_it_current_data_handler,
	phpglfw_buffer_glshort_it_current_key_handler,
	phpglfw_buffer_glshort_it_move_forward_handler,
	phpglfw_buffer_glshort_it_rewind_handler,
	NULL,
	NULL,
};

zend_object_iterator *phpglfw_buffer_glshort_get_iterator_handler(zend_class_entry *ce, zval *object, int by_ref)
{
	phpglfw_buffer_glshort_iterator *iterator;

	if (by_ref != 0) {
		zend_throw_error(NULL, "GL\\Buffer\\BufferInterface object can not be iterated by reference");
		return NULL;
	}
    
	iterator = emalloc(sizeof(phpglfw_buffer_glshort_iterator));

	zend_iterator_init((zend_object_iterator*)iterator);

	ZVAL_OBJ_COPY(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &phpglfw_buffer_glshort_iterator_handlers;
    iterator->index = 0;

	return &iterator->intern;
}

/**
 * Free (GL\Buffer\ShortBuffer )
 */
static void phpglfw_buffer_glshort_free_handler(zend_object *object)
{
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

/**
 * Creation (GL\Buffer\ShortBuffer )
 */
zend_object *phpglfw_buffer_glshort_create_handler(zend_class_entry *class_type)
{
    phpglfw_buffer_glshort_object *intern = zend_object_alloc(sizeof(phpglfw_buffer_glshort_object), class_type);

    intern->vec = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_buffer_glshort_handlers;

    return &intern->std;
}

zval *phpglfw_buffer_glshort_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Buffer\\BufferInterface object");
	}

    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(object);

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

void phpglfw_buffer_glshort_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_LONG) {
        zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
        return;
    }

    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(object);

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
/*
static int phpglfw_buffer_glshort_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(object));

    size_t item_count = cvector_size(obj_ptr->vec);
    *buf_len = sizeof(size_t) + item_count * sizeof(GLshort);
    *buffer = emalloc(*buf_len);

    memcpy(*buffer, &item_count, sizeof(size_t));
    memcpy(*buffer + sizeof(size_t), obj_ptr->vec, item_count * sizeof(GLshort));

    return SUCCESS;
}

int phpglfw_buffer_glshort_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    const unsigned char *buf_ptr = buf;
    size_t item_count;
    phpglfw_buffer_glshort_object *obj;

    if (buf_len < sizeof(size_t)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glshort_object unserialization", 0);
        return FAILURE;
    }

    memcpy(&item_count, buf_ptr, sizeof(size_t));
    buf_ptr += sizeof(size_t);

    if (buf_len < sizeof(size_t) + item_count * sizeof(GLshort)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glshort_object unserialization", 0);
        return FAILURE;
    }

    object_init_ex(object, phpglfw_buffer_glshort_ce);
    obj = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(object));
    //obj->vec = emalloc(item_count * sizeof(GLshort));

    cvector_reserve(obj->vec, item_count);
    cvector_set_size(obj->vec, item_count); 

    // copy the data
    memcpy(obj->vec, buf_ptr, item_count * sizeof(GLshort));

    return SUCCESS;
}*/

static int phpglfw_buffer_glshort_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(object));
    size_t num_elements = cvector_size(obj_ptr->vec);

    // I want the standard serialization format to be human readable and easaly reconstructable
    // which is why I use a simple format of: <num_elements>:<element1> <element2> <element3> ...
    // More efficent serialization formats should be added as seperate, deticated functions
    cvector_vector_type(char) buffer_string = NULL;

    // used to temporarly store the string representation of each element
    // honestly I could not find a proper description of the maximum length of a double represented as 
    // string, after spending an hour down that rabbit hole I decided to just use a buffer of 256 bytes
    char tmp[256]; 

    // reserve some space for the string, its going to be more 
    // at the end but saves the first few reallocs
    cvector_reserve(buffer_string, num_elements * sizeof(GLshort));

    // write the number of elements
    int offset = sprintf(tmp, "%zu:", num_elements);
    cvector_push_back_array(buffer_string, tmp, offset);

    // write each element
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "%hd ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }

    // trim away the trailing space
    cvector_pop_back(buffer_string);

    size_t total_size = cvector_size(buffer_string);

    *buffer = (unsigned char *)estrndup(buffer_string, total_size);
    *buf_len = total_size;
    // efree(buf);

    return SUCCESS;
}

static int phpglfw_buffer_glshort_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    phpglfw_buffer_glshort_object *obj;

    size_t exp_item_count, item_count;
    char *endptr, *token, *tmp_copy;
    
    // prints the buffer for debugging
    // for (size_t i = 0; i < buf_len; i++) {
    //     printf("%c", buf[i]);
    // }
    // printf("\n");

    // read the number of elements
    exp_item_count = item_count = strtoul((char *)buf, &endptr, 10);
    if (endptr == (char *)buf || *endptr != ':') {
        // Failed to parse the number of elements
        zend_throw_error(NULL, "Invalid format during phpglfw_buffer_glshort_object unserialization, could not parse the number of elements.");
        return FAILURE;
    }

    // skip the ':'
    endptr++;

    // create a copy of the buffer, we are going to modify it
    // @TODO: when using `strtok` we are modifying the entire buffer,
    // which will cause an issue when we are using the same buffer for multiple elements
    // This copy for sure can be avoided, but im going to tackle that in the future
    tmp_copy = estrndup(endptr, buf_len - (endptr - (char *)buf));

    // make the object
    object_init_ex(object, phpglfw_buffer_glshort_ce);
    obj = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(object));

    cvector_reserve(obj->vec, exp_item_count); 

    // read the elements, check if our endptr is still valid and we have not reached the end of the buffer
    token = strtok(tmp_copy, " ");
    while (token != NULL && item_count > 0) {
                cvector_push_back(obj->vec, strtol(token, NULL, 10));
                token = strtok(NULL, " ");
        item_count--;
    }

    if (cvector_size(obj->vec) != exp_item_count) {
        zend_throw_error(NULL, "Mismatch in expected item count during phpglfw_buffer_glshort_object unserialization. Expected: %zu, Found: %zu", exp_item_count, cvector_size(obj->vec));
        return FAILURE;
    }

    return SUCCESS;
}

static HashTable *phpglfw_buffer_glshort_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht, *dataht;

    ht = zend_new_array(2);
    dataht = zend_new_array(127);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

    for(size_t i = 0; i < pglmin(127, cvector_size(obj_ptr->vec)); i++) {
        ZVAL_LONG(&zv, obj_ptr->vec[i]);
        zend_hash_index_update(dataht, i, &zv);
    }


    ZVAL_ARR(&zv, dataht);
    zend_hash_str_update(ht, "data", sizeof("data") - 1, &zv);

    return ht;
}

PHP_METHOD(GL_Buffer_ShortBuffer, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "GL\\Buffer\\ShortBuffer" "(");
    smart_str_append_long(&my_str, cvector_size(obj_ptr->vec));
    smart_str_appends(&my_str, " [");
    smart_str_append_long(&my_str, cvector_capacity(obj_ptr->vec));
    smart_str_appends(&my_str, "])");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(GL_Buffer_ShortBuffer, push)
{
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_push_back(obj_ptr->vec, value);
}

PHP_METHOD(GL_Buffer_ShortBuffer, pushArray)
{
    zval *array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "a", &array) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(array), array) {
        if (Z_TYPE_P(array) != IS_LONG) {
            zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
            return;
        }

        cvector_push_back(obj_ptr->vec, Z_LVAL_P(array));
    } ZEND_HASH_FOREACH_END();
}



PHP_METHOD(GL_Buffer_ShortBuffer, reserve)
{
    zend_long resvering_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &resvering_size) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_reserve(obj_ptr->vec, resvering_size);
}

PHP_METHOD(GL_Buffer_ShortBuffer, clear)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_free(obj_ptr->vec);
    obj_ptr->vec = NULL;
}

PHP_METHOD(GL_Buffer_ShortBuffer, fill)
{
    zend_long value;
    zend_long fill_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &fill_size, &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_fill(obj_ptr->vec, fill_size, value);
}

PHP_METHOD(GL_Buffer_ShortBuffer, size)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_size(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_ShortBuffer, capacity)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_capacity(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_ShortBuffer, dump)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_STRINGL((char *)obj_ptr->vec, cvector_size(obj_ptr->vec) * sizeof(GLshort));
}

PHP_METHOD(GL_Buffer_ShortBuffer, __construct)
{
    HashTable *initaldata = NULL;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h", &initaldata) == FAILURE) {
        return;
    }
    else if (initaldata == NULL) {
        return;
    }
    else if (zend_hash_num_elements(initaldata) == 0) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(obj));

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
 * GL\Buffer\UShortBuffer 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_buffer_glushort_handlers;

/**
 * Iterator (GL\Buffer\UShortBuffer )
 */
typedef struct _phpglfw_buffer_glushort_iterator {
	zend_object_iterator intern;
	size_t index;
	zval current;
} phpglfw_buffer_glushort_iterator;

static void phpglfw_buffer_glushort_it_dtor_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glushort_iterator *I = (phpglfw_buffer_glushort_iterator*)iter;

	zval_ptr_dtor(&I->intern.data);
    if (!Z_ISUNDEF(I->current)) {
		zval_ptr_dtor(&I->current);
	}
}

static void phpglfw_buffer_glushort_it_rewind_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glushort_iterator*)iter)->index = 0;
}

static void phpglfw_buffer_glushort_it_current_key_handler(zend_object_iterator *iter, zval *key)
{
	ZVAL_LONG(key, ((phpglfw_buffer_glushort_iterator*)iter)->index);
}

static void phpglfw_buffer_glushort_it_move_forward_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glushort_iterator*)iter)->index++;
}

static int phpglfw_buffer_glushort_it_valid_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glushort_iterator *iterator = (phpglfw_buffer_glushort_iterator*)iter;
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	if (iterator->index >= 0 && iterator->index < cvector_size(obj_ptr->vec)) {
		return SUCCESS;
	}

	return FAILURE;
}

static zval *phpglfw_buffer_glushort_it_current_data_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glushort_iterator *iterator = (phpglfw_buffer_glushort_iterator*)iter;
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	ZVAL_LONG(&iterator->current, obj_ptr->vec[iterator->index]);

	return &iterator->current;
}

static const zend_object_iterator_funcs phpglfw_buffer_glushort_iterator_handlers = {
	phpglfw_buffer_glushort_it_dtor_handler,
	phpglfw_buffer_glushort_it_valid_handler,
	phpglfw_buffer_glushort_it_current_data_handler,
	phpglfw_buffer_glushort_it_current_key_handler,
	phpglfw_buffer_glushort_it_move_forward_handler,
	phpglfw_buffer_glushort_it_rewind_handler,
	NULL,
	NULL,
};

zend_object_iterator *phpglfw_buffer_glushort_get_iterator_handler(zend_class_entry *ce, zval *object, int by_ref)
{
	phpglfw_buffer_glushort_iterator *iterator;

	if (by_ref != 0) {
		zend_throw_error(NULL, "GL\\Buffer\\BufferInterface object can not be iterated by reference");
		return NULL;
	}
    
	iterator = emalloc(sizeof(phpglfw_buffer_glushort_iterator));

	zend_iterator_init((zend_object_iterator*)iterator);

	ZVAL_OBJ_COPY(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &phpglfw_buffer_glushort_iterator_handlers;
    iterator->index = 0;

	return &iterator->intern;
}

/**
 * Free (GL\Buffer\UShortBuffer )
 */
static void phpglfw_buffer_glushort_free_handler(zend_object *object)
{
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

/**
 * Creation (GL\Buffer\UShortBuffer )
 */
zend_object *phpglfw_buffer_glushort_create_handler(zend_class_entry *class_type)
{
    phpglfw_buffer_glushort_object *intern = zend_object_alloc(sizeof(phpglfw_buffer_glushort_object), class_type);

    intern->vec = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_buffer_glushort_handlers;

    return &intern->std;
}

zval *phpglfw_buffer_glushort_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Buffer\\BufferInterface object");
	}

    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(object);

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

void phpglfw_buffer_glushort_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_LONG) {
        zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
        return;
    }

    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(object);

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
/*
static int phpglfw_buffer_glushort_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(object));

    size_t item_count = cvector_size(obj_ptr->vec);
    *buf_len = sizeof(size_t) + item_count * sizeof(GLushort);
    *buffer = emalloc(*buf_len);

    memcpy(*buffer, &item_count, sizeof(size_t));
    memcpy(*buffer + sizeof(size_t), obj_ptr->vec, item_count * sizeof(GLushort));

    return SUCCESS;
}

int phpglfw_buffer_glushort_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    const unsigned char *buf_ptr = buf;
    size_t item_count;
    phpglfw_buffer_glushort_object *obj;

    if (buf_len < sizeof(size_t)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glushort_object unserialization", 0);
        return FAILURE;
    }

    memcpy(&item_count, buf_ptr, sizeof(size_t));
    buf_ptr += sizeof(size_t);

    if (buf_len < sizeof(size_t) + item_count * sizeof(GLushort)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glushort_object unserialization", 0);
        return FAILURE;
    }

    object_init_ex(object, phpglfw_buffer_glushort_ce);
    obj = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(object));
    //obj->vec = emalloc(item_count * sizeof(GLushort));

    cvector_reserve(obj->vec, item_count);
    cvector_set_size(obj->vec, item_count); 

    // copy the data
    memcpy(obj->vec, buf_ptr, item_count * sizeof(GLushort));

    return SUCCESS;
}*/

static int phpglfw_buffer_glushort_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(object));
    size_t num_elements = cvector_size(obj_ptr->vec);

    // I want the standard serialization format to be human readable and easaly reconstructable
    // which is why I use a simple format of: <num_elements>:<element1> <element2> <element3> ...
    // More efficent serialization formats should be added as seperate, deticated functions
    cvector_vector_type(char) buffer_string = NULL;

    // used to temporarly store the string representation of each element
    // honestly I could not find a proper description of the maximum length of a double represented as 
    // string, after spending an hour down that rabbit hole I decided to just use a buffer of 256 bytes
    char tmp[256]; 

    // reserve some space for the string, its going to be more 
    // at the end but saves the first few reallocs
    cvector_reserve(buffer_string, num_elements * sizeof(GLushort));

    // write the number of elements
    int offset = sprintf(tmp, "%zu:", num_elements);
    cvector_push_back_array(buffer_string, tmp, offset);

    // write each element
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "%hu ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }

    // trim away the trailing space
    cvector_pop_back(buffer_string);

    size_t total_size = cvector_size(buffer_string);

    *buffer = (unsigned char *)estrndup(buffer_string, total_size);
    *buf_len = total_size;
    // efree(buf);

    return SUCCESS;
}

static int phpglfw_buffer_glushort_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    phpglfw_buffer_glushort_object *obj;

    size_t exp_item_count, item_count;
    char *endptr, *token, *tmp_copy;
    
    // prints the buffer for debugging
    // for (size_t i = 0; i < buf_len; i++) {
    //     printf("%c", buf[i]);
    // }
    // printf("\n");

    // read the number of elements
    exp_item_count = item_count = strtoul((char *)buf, &endptr, 10);
    if (endptr == (char *)buf || *endptr != ':') {
        // Failed to parse the number of elements
        zend_throw_error(NULL, "Invalid format during phpglfw_buffer_glushort_object unserialization, could not parse the number of elements.");
        return FAILURE;
    }

    // skip the ':'
    endptr++;

    // create a copy of the buffer, we are going to modify it
    // @TODO: when using `strtok` we are modifying the entire buffer,
    // which will cause an issue when we are using the same buffer for multiple elements
    // This copy for sure can be avoided, but im going to tackle that in the future
    tmp_copy = estrndup(endptr, buf_len - (endptr - (char *)buf));

    // make the object
    object_init_ex(object, phpglfw_buffer_glushort_ce);
    obj = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(object));

    cvector_reserve(obj->vec, exp_item_count); 

    // read the elements, check if our endptr is still valid and we have not reached the end of the buffer
    token = strtok(tmp_copy, " ");
    while (token != NULL && item_count > 0) {
                cvector_push_back(obj->vec, strtol(token, NULL, 10));
                token = strtok(NULL, " ");
        item_count--;
    }

    if (cvector_size(obj->vec) != exp_item_count) {
        zend_throw_error(NULL, "Mismatch in expected item count during phpglfw_buffer_glushort_object unserialization. Expected: %zu, Found: %zu", exp_item_count, cvector_size(obj->vec));
        return FAILURE;
    }

    return SUCCESS;
}

static HashTable *phpglfw_buffer_glushort_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht, *dataht;

    ht = zend_new_array(2);
    dataht = zend_new_array(127);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

    for(size_t i = 0; i < pglmin(127, cvector_size(obj_ptr->vec)); i++) {
        ZVAL_LONG(&zv, obj_ptr->vec[i]);
        zend_hash_index_update(dataht, i, &zv);
    }


    ZVAL_ARR(&zv, dataht);
    zend_hash_str_update(ht, "data", sizeof("data") - 1, &zv);

    return ht;
}

PHP_METHOD(GL_Buffer_UShortBuffer, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "GL\\Buffer\\UShortBuffer" "(");
    smart_str_append_long(&my_str, cvector_size(obj_ptr->vec));
    smart_str_appends(&my_str, " [");
    smart_str_append_long(&my_str, cvector_capacity(obj_ptr->vec));
    smart_str_appends(&my_str, "])");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(GL_Buffer_UShortBuffer, push)
{
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_push_back(obj_ptr->vec, value);
}

PHP_METHOD(GL_Buffer_UShortBuffer, pushArray)
{
    zval *array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "a", &array) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(array), array) {
        if (Z_TYPE_P(array) != IS_LONG) {
            zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
            return;
        }

        cvector_push_back(obj_ptr->vec, Z_LVAL_P(array));
    } ZEND_HASH_FOREACH_END();
}



PHP_METHOD(GL_Buffer_UShortBuffer, reserve)
{
    zend_long resvering_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &resvering_size) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_reserve(obj_ptr->vec, resvering_size);
}

PHP_METHOD(GL_Buffer_UShortBuffer, clear)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_free(obj_ptr->vec);
    obj_ptr->vec = NULL;
}

PHP_METHOD(GL_Buffer_UShortBuffer, fill)
{
    zend_long value;
    zend_long fill_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &fill_size, &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_fill(obj_ptr->vec, fill_size, value);
}

PHP_METHOD(GL_Buffer_UShortBuffer, size)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_size(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_UShortBuffer, capacity)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_capacity(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_UShortBuffer, dump)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_STRINGL((char *)obj_ptr->vec, cvector_size(obj_ptr->vec) * sizeof(GLushort));
}

PHP_METHOD(GL_Buffer_UShortBuffer, __construct)
{
    HashTable *initaldata = NULL;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h", &initaldata) == FAILURE) {
        return;
    }
    else if (initaldata == NULL) {
        return;
    }
    else if (zend_hash_num_elements(initaldata) == 0) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(obj));

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

/**
 * Iterator (GL\Buffer\ByteBuffer )
 */
typedef struct _phpglfw_buffer_glbyte_iterator {
	zend_object_iterator intern;
	size_t index;
	zval current;
} phpglfw_buffer_glbyte_iterator;

static void phpglfw_buffer_glbyte_it_dtor_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glbyte_iterator *I = (phpglfw_buffer_glbyte_iterator*)iter;

	zval_ptr_dtor(&I->intern.data);
    if (!Z_ISUNDEF(I->current)) {
		zval_ptr_dtor(&I->current);
	}
}

static void phpglfw_buffer_glbyte_it_rewind_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glbyte_iterator*)iter)->index = 0;
}

static void phpglfw_buffer_glbyte_it_current_key_handler(zend_object_iterator *iter, zval *key)
{
	ZVAL_LONG(key, ((phpglfw_buffer_glbyte_iterator*)iter)->index);
}

static void phpglfw_buffer_glbyte_it_move_forward_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glbyte_iterator*)iter)->index++;
}

static int phpglfw_buffer_glbyte_it_valid_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glbyte_iterator *iterator = (phpglfw_buffer_glbyte_iterator*)iter;
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	if (iterator->index >= 0 && iterator->index < cvector_size(obj_ptr->vec)) {
		return SUCCESS;
	}

	return FAILURE;
}

static zval *phpglfw_buffer_glbyte_it_current_data_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glbyte_iterator *iterator = (phpglfw_buffer_glbyte_iterator*)iter;
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	ZVAL_LONG(&iterator->current, obj_ptr->vec[iterator->index]);

	return &iterator->current;
}

static const zend_object_iterator_funcs phpglfw_buffer_glbyte_iterator_handlers = {
	phpglfw_buffer_glbyte_it_dtor_handler,
	phpglfw_buffer_glbyte_it_valid_handler,
	phpglfw_buffer_glbyte_it_current_data_handler,
	phpglfw_buffer_glbyte_it_current_key_handler,
	phpglfw_buffer_glbyte_it_move_forward_handler,
	phpglfw_buffer_glbyte_it_rewind_handler,
	NULL,
	NULL,
};

zend_object_iterator *phpglfw_buffer_glbyte_get_iterator_handler(zend_class_entry *ce, zval *object, int by_ref)
{
	phpglfw_buffer_glbyte_iterator *iterator;

	if (by_ref != 0) {
		zend_throw_error(NULL, "GL\\Buffer\\BufferInterface object can not be iterated by reference");
		return NULL;
	}
    
	iterator = emalloc(sizeof(phpglfw_buffer_glbyte_iterator));

	zend_iterator_init((zend_object_iterator*)iterator);

	ZVAL_OBJ_COPY(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &phpglfw_buffer_glbyte_iterator_handlers;
    iterator->index = 0;

	return &iterator->intern;
}

/**
 * Free (GL\Buffer\ByteBuffer )
 */
static void phpglfw_buffer_glbyte_free_handler(zend_object *object)
{
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

/**
 * Creation (GL\Buffer\ByteBuffer )
 */
zend_object *phpglfw_buffer_glbyte_create_handler(zend_class_entry *class_type)
{
    phpglfw_buffer_glbyte_object *intern = zend_object_alloc(sizeof(phpglfw_buffer_glbyte_object), class_type);

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
/*
static int phpglfw_buffer_glbyte_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(object));

    size_t item_count = cvector_size(obj_ptr->vec);
    *buf_len = sizeof(size_t) + item_count * sizeof(GLbyte);
    *buffer = emalloc(*buf_len);

    memcpy(*buffer, &item_count, sizeof(size_t));
    memcpy(*buffer + sizeof(size_t), obj_ptr->vec, item_count * sizeof(GLbyte));

    return SUCCESS;
}

int phpglfw_buffer_glbyte_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    const unsigned char *buf_ptr = buf;
    size_t item_count;
    phpglfw_buffer_glbyte_object *obj;

    if (buf_len < sizeof(size_t)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glbyte_object unserialization", 0);
        return FAILURE;
    }

    memcpy(&item_count, buf_ptr, sizeof(size_t));
    buf_ptr += sizeof(size_t);

    if (buf_len < sizeof(size_t) + item_count * sizeof(GLbyte)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glbyte_object unserialization", 0);
        return FAILURE;
    }

    object_init_ex(object, phpglfw_buffer_glbyte_ce);
    obj = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(object));
    //obj->vec = emalloc(item_count * sizeof(GLbyte));

    cvector_reserve(obj->vec, item_count);
    cvector_set_size(obj->vec, item_count); 

    // copy the data
    memcpy(obj->vec, buf_ptr, item_count * sizeof(GLbyte));

    return SUCCESS;
}*/

static int phpglfw_buffer_glbyte_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(object));
    size_t num_elements = cvector_size(obj_ptr->vec);

    // I want the standard serialization format to be human readable and easaly reconstructable
    // which is why I use a simple format of: <num_elements>:<element1> <element2> <element3> ...
    // More efficent serialization formats should be added as seperate, deticated functions
    cvector_vector_type(char) buffer_string = NULL;

    // used to temporarly store the string representation of each element
    // honestly I could not find a proper description of the maximum length of a double represented as 
    // string, after spending an hour down that rabbit hole I decided to just use a buffer of 256 bytes
    char tmp[256]; 

    // reserve some space for the string, its going to be more 
    // at the end but saves the first few reallocs
    cvector_reserve(buffer_string, num_elements * sizeof(GLbyte));

    // write the number of elements
    int offset = sprintf(tmp, "%zu:", num_elements);
    cvector_push_back_array(buffer_string, tmp, offset);

    // write each element
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "%hhd ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }

    // trim away the trailing space
    cvector_pop_back(buffer_string);

    size_t total_size = cvector_size(buffer_string);

    *buffer = (unsigned char *)estrndup(buffer_string, total_size);
    *buf_len = total_size;
    // efree(buf);

    return SUCCESS;
}

static int phpglfw_buffer_glbyte_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    phpglfw_buffer_glbyte_object *obj;

    size_t exp_item_count, item_count;
    char *endptr, *token, *tmp_copy;
    
    // prints the buffer for debugging
    // for (size_t i = 0; i < buf_len; i++) {
    //     printf("%c", buf[i]);
    // }
    // printf("\n");

    // read the number of elements
    exp_item_count = item_count = strtoul((char *)buf, &endptr, 10);
    if (endptr == (char *)buf || *endptr != ':') {
        // Failed to parse the number of elements
        zend_throw_error(NULL, "Invalid format during phpglfw_buffer_glbyte_object unserialization, could not parse the number of elements.");
        return FAILURE;
    }

    // skip the ':'
    endptr++;

    // create a copy of the buffer, we are going to modify it
    // @TODO: when using `strtok` we are modifying the entire buffer,
    // which will cause an issue when we are using the same buffer for multiple elements
    // This copy for sure can be avoided, but im going to tackle that in the future
    tmp_copy = estrndup(endptr, buf_len - (endptr - (char *)buf));

    // make the object
    object_init_ex(object, phpglfw_buffer_glbyte_ce);
    obj = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(object));

    cvector_reserve(obj->vec, exp_item_count); 

    // read the elements, check if our endptr is still valid and we have not reached the end of the buffer
    token = strtok(tmp_copy, " ");
    while (token != NULL && item_count > 0) {
                cvector_push_back(obj->vec, strtol(token, NULL, 10));
                token = strtok(NULL, " ");
        item_count--;
    }

    if (cvector_size(obj->vec) != exp_item_count) {
        zend_throw_error(NULL, "Mismatch in expected item count during phpglfw_buffer_glbyte_object unserialization. Expected: %zu, Found: %zu", exp_item_count, cvector_size(obj->vec));
        return FAILURE;
    }

    return SUCCESS;
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

    for(size_t i = 0; i < pglmin(127, cvector_size(obj_ptr->vec)); i++) {
        ZVAL_LONG(&zv, obj_ptr->vec[i]);
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

PHP_METHOD(GL_Buffer_ByteBuffer, pushArray)
{
    zval *array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "a", &array) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(array), array) {
        if (Z_TYPE_P(array) != IS_LONG) {
            zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
            return;
        }

        cvector_push_back(obj_ptr->vec, Z_LVAL_P(array));
    } ZEND_HASH_FOREACH_END();
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

PHP_METHOD(GL_Buffer_ByteBuffer, dump)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_STRINGL((char *)obj_ptr->vec, cvector_size(obj_ptr->vec) * sizeof(GLbyte));
}

PHP_METHOD(GL_Buffer_ByteBuffer, __construct)
{
    HashTable *initaldata = NULL;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h", &initaldata) == FAILURE) {
        return;
    }
    else if (initaldata == NULL) {
        return;
    }
    else if (zend_hash_num_elements(initaldata) == 0) {
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

/**
 * GL\Buffer\UByteBuffer 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_buffer_glubyte_handlers;

/**
 * Iterator (GL\Buffer\UByteBuffer )
 */
typedef struct _phpglfw_buffer_glubyte_iterator {
	zend_object_iterator intern;
	size_t index;
	zval current;
} phpglfw_buffer_glubyte_iterator;

static void phpglfw_buffer_glubyte_it_dtor_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glubyte_iterator *I = (phpglfw_buffer_glubyte_iterator*)iter;

	zval_ptr_dtor(&I->intern.data);
    if (!Z_ISUNDEF(I->current)) {
		zval_ptr_dtor(&I->current);
	}
}

static void phpglfw_buffer_glubyte_it_rewind_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glubyte_iterator*)iter)->index = 0;
}

static void phpglfw_buffer_glubyte_it_current_key_handler(zend_object_iterator *iter, zval *key)
{
	ZVAL_LONG(key, ((phpglfw_buffer_glubyte_iterator*)iter)->index);
}

static void phpglfw_buffer_glubyte_it_move_forward_handler(zend_object_iterator *iter)
{
	((phpglfw_buffer_glubyte_iterator*)iter)->index++;
}

static int phpglfw_buffer_glubyte_it_valid_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glubyte_iterator *iterator = (phpglfw_buffer_glubyte_iterator*)iter;
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	if (iterator->index >= 0 && iterator->index < cvector_size(obj_ptr->vec)) {
		return SUCCESS;
	}

	return FAILURE;
}

static zval *phpglfw_buffer_glubyte_it_current_data_handler(zend_object_iterator *iter)
{
	phpglfw_buffer_glubyte_iterator *iterator = (phpglfw_buffer_glubyte_iterator*)iter;
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(&iter->data));

	ZVAL_LONG(&iterator->current, obj_ptr->vec[iterator->index]);

	return &iterator->current;
}

static const zend_object_iterator_funcs phpglfw_buffer_glubyte_iterator_handlers = {
	phpglfw_buffer_glubyte_it_dtor_handler,
	phpglfw_buffer_glubyte_it_valid_handler,
	phpglfw_buffer_glubyte_it_current_data_handler,
	phpglfw_buffer_glubyte_it_current_key_handler,
	phpglfw_buffer_glubyte_it_move_forward_handler,
	phpglfw_buffer_glubyte_it_rewind_handler,
	NULL,
	NULL,
};

zend_object_iterator *phpglfw_buffer_glubyte_get_iterator_handler(zend_class_entry *ce, zval *object, int by_ref)
{
	phpglfw_buffer_glubyte_iterator *iterator;

	if (by_ref != 0) {
		zend_throw_error(NULL, "GL\\Buffer\\BufferInterface object can not be iterated by reference");
		return NULL;
	}
    
	iterator = emalloc(sizeof(phpglfw_buffer_glubyte_iterator));

	zend_iterator_init((zend_object_iterator*)iterator);

	ZVAL_OBJ_COPY(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &phpglfw_buffer_glubyte_iterator_handlers;
    iterator->index = 0;

	return &iterator->intern;
}

/**
 * Free (GL\Buffer\UByteBuffer )
 */
static void phpglfw_buffer_glubyte_free_handler(zend_object *object)
{
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

/**
 * Creation (GL\Buffer\UByteBuffer )
 */
zend_object *phpglfw_buffer_glubyte_create_handler(zend_class_entry *class_type)
{
    phpglfw_buffer_glubyte_object *intern = zend_object_alloc(sizeof(phpglfw_buffer_glubyte_object), class_type);

    intern->vec = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_buffer_glubyte_handlers;

    return &intern->std;
}

zval *phpglfw_buffer_glubyte_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Buffer\\BufferInterface object");
	}

    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(object);

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

void phpglfw_buffer_glubyte_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_LONG) {
        zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
        return;
    }

    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(object);

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
/*
static int phpglfw_buffer_glubyte_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(object));

    size_t item_count = cvector_size(obj_ptr->vec);
    *buf_len = sizeof(size_t) + item_count * sizeof(GLubyte);
    *buffer = emalloc(*buf_len);

    memcpy(*buffer, &item_count, sizeof(size_t));
    memcpy(*buffer + sizeof(size_t), obj_ptr->vec, item_count * sizeof(GLubyte));

    return SUCCESS;
}

int phpglfw_buffer_glubyte_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    const unsigned char *buf_ptr = buf;
    size_t item_count;
    phpglfw_buffer_glubyte_object *obj;

    if (buf_len < sizeof(size_t)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glubyte_object unserialization", 0);
        return FAILURE;
    }

    memcpy(&item_count, buf_ptr, sizeof(size_t));
    buf_ptr += sizeof(size_t);

    if (buf_len < sizeof(size_t) + item_count * sizeof(GLubyte)) {
        zend_throw_error(NULL, "Buffer underflow during phpglfw_buffer_glubyte_object unserialization", 0);
        return FAILURE;
    }

    object_init_ex(object, phpglfw_buffer_glubyte_ce);
    obj = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(object));
    //obj->vec = emalloc(item_count * sizeof(GLubyte));

    cvector_reserve(obj->vec, item_count);
    cvector_set_size(obj->vec, item_count); 

    // copy the data
    memcpy(obj->vec, buf_ptr, item_count * sizeof(GLubyte));

    return SUCCESS;
}*/

static int phpglfw_buffer_glubyte_serialize_handler(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(object));
    size_t num_elements = cvector_size(obj_ptr->vec);

    // I want the standard serialization format to be human readable and easaly reconstructable
    // which is why I use a simple format of: <num_elements>:<element1> <element2> <element3> ...
    // More efficent serialization formats should be added as seperate, deticated functions
    cvector_vector_type(char) buffer_string = NULL;

    // used to temporarly store the string representation of each element
    // honestly I could not find a proper description of the maximum length of a double represented as 
    // string, after spending an hour down that rabbit hole I decided to just use a buffer of 256 bytes
    char tmp[256]; 

    // reserve some space for the string, its going to be more 
    // at the end but saves the first few reallocs
    cvector_reserve(buffer_string, num_elements * sizeof(GLubyte));

    // write the number of elements
    int offset = sprintf(tmp, "%zu:", num_elements);
    cvector_push_back_array(buffer_string, tmp, offset);

    // write each element
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "%hhu ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }

    // trim away the trailing space
    cvector_pop_back(buffer_string);

    size_t total_size = cvector_size(buffer_string);

    *buffer = (unsigned char *)estrndup(buffer_string, total_size);
    *buf_len = total_size;
    // efree(buf);

    return SUCCESS;
}

static int phpglfw_buffer_glubyte_unserialize_handler(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    phpglfw_buffer_glubyte_object *obj;

    size_t exp_item_count, item_count;
    char *endptr, *token, *tmp_copy;
    
    // prints the buffer for debugging
    // for (size_t i = 0; i < buf_len; i++) {
    //     printf("%c", buf[i]);
    // }
    // printf("\n");

    // read the number of elements
    exp_item_count = item_count = strtoul((char *)buf, &endptr, 10);
    if (endptr == (char *)buf || *endptr != ':') {
        // Failed to parse the number of elements
        zend_throw_error(NULL, "Invalid format during phpglfw_buffer_glubyte_object unserialization, could not parse the number of elements.");
        return FAILURE;
    }

    // skip the ':'
    endptr++;

    // create a copy of the buffer, we are going to modify it
    // @TODO: when using `strtok` we are modifying the entire buffer,
    // which will cause an issue when we are using the same buffer for multiple elements
    // This copy for sure can be avoided, but im going to tackle that in the future
    tmp_copy = estrndup(endptr, buf_len - (endptr - (char *)buf));

    // make the object
    object_init_ex(object, phpglfw_buffer_glubyte_ce);
    obj = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(object));

    cvector_reserve(obj->vec, exp_item_count); 

    // read the elements, check if our endptr is still valid and we have not reached the end of the buffer
    token = strtok(tmp_copy, " ");
    while (token != NULL && item_count > 0) {
                cvector_push_back(obj->vec, strtol(token, NULL, 10));
                token = strtok(NULL, " ");
        item_count--;
    }

    if (cvector_size(obj->vec) != exp_item_count) {
        zend_throw_error(NULL, "Mismatch in expected item count during phpglfw_buffer_glubyte_object unserialization. Expected: %zu, Found: %zu", exp_item_count, cvector_size(obj->vec));
        return FAILURE;
    }

    return SUCCESS;
}

static HashTable *phpglfw_buffer_glubyte_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht, *dataht;

    ht = zend_new_array(2);
    dataht = zend_new_array(127);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

    for(size_t i = 0; i < pglmin(127, cvector_size(obj_ptr->vec)); i++) {
        ZVAL_LONG(&zv, obj_ptr->vec[i]);
        zend_hash_index_update(dataht, i, &zv);
    }


    ZVAL_ARR(&zv, dataht);
    zend_hash_str_update(ht, "data", sizeof("data") - 1, &zv);

    return ht;
}

PHP_METHOD(GL_Buffer_UByteBuffer, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "GL\\Buffer\\UByteBuffer" "(");
    smart_str_append_long(&my_str, cvector_size(obj_ptr->vec));
    smart_str_appends(&my_str, " [");
    smart_str_append_long(&my_str, cvector_capacity(obj_ptr->vec));
    smart_str_appends(&my_str, "])");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(GL_Buffer_UByteBuffer, push)
{
    zend_long value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_push_back(obj_ptr->vec, value);
}

PHP_METHOD(GL_Buffer_UByteBuffer, pushArray)
{
    zval *array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "a", &array) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(array), array) {
        if (Z_TYPE_P(array) != IS_LONG) {
            zend_throw_error(NULL, "Trying to store non int value in a int type buffer.");
            return;
        }

        cvector_push_back(obj_ptr->vec, Z_LVAL_P(array));
    } ZEND_HASH_FOREACH_END();
}


PHP_METHOD(GL_Buffer_UByteBuffer, pushString)
{
    char *string;
    size_t string_len;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &string, &string_len) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_push_back_array(obj_ptr->vec, string, string_len);
}



PHP_METHOD(GL_Buffer_UByteBuffer, reserve)
{
    zend_long resvering_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &resvering_size) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    cvector_reserve(obj_ptr->vec, resvering_size);
}

PHP_METHOD(GL_Buffer_UByteBuffer, clear)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_free(obj_ptr->vec);
    obj_ptr->vec = NULL;
}

PHP_METHOD(GL_Buffer_UByteBuffer, fill)
{
    zend_long value;
    zend_long fill_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ll", &fill_size, &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    cvector_fill(obj_ptr->vec, fill_size, value);
}

PHP_METHOD(GL_Buffer_UByteBuffer, size)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_size(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_UByteBuffer, capacity)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_LONG(cvector_capacity(obj_ptr->vec));
}

PHP_METHOD(GL_Buffer_UByteBuffer, dump)
{
    zval *obj;
    obj = getThis();
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_STRINGL((char *)obj_ptr->vec, cvector_size(obj_ptr->vec) * sizeof(GLubyte));
}

PHP_METHOD(GL_Buffer_UByteBuffer, __construct)
{
    HashTable *initaldata = NULL;
    zval *data;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|h", &initaldata) == FAILURE) {
        return;
    }
    else if (initaldata == NULL) {
        return;
    }
    else if (zend_hash_num_elements(initaldata) == 0) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(obj));

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
    
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\FloatBuffer", class_GL_Buffer_FloatBuffer_methods);
    phpglfw_buffer_glfloat_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_glfloat_ce->create_object = phpglfw_buffer_glfloat_create_handler;
    phpglfw_buffer_glfloat_ce->serialize = phpglfw_buffer_glfloat_serialize_handler;
    phpglfw_buffer_glfloat_ce->unserialize = phpglfw_buffer_glfloat_unserialize_handler;
    phpglfw_buffer_glfloat_ce->get_iterator = phpglfw_buffer_glfloat_get_iterator_handler;

	zend_class_implements(phpglfw_buffer_glfloat_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glfloat_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_buffer_glfloat_handlers.offset = XtOffsetOf(phpglfw_buffer_glfloat_object, std);
    
    phpglfw_buffer_glfloat_handlers.free_obj = phpglfw_buffer_glfloat_free_handler;
    phpglfw_buffer_glfloat_handlers.read_dimension = phpglfw_buffer_glfloat_array_get_handler;
    phpglfw_buffer_glfloat_handlers.write_dimension = phpglfw_buffer_glfloat_array_set_handler;
    phpglfw_buffer_glfloat_handlers.get_debug_info = phpglfw_buffer_glfloat_debug_info_handler;
    
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\HFloatBuffer", class_GL_Buffer_HFloatBuffer_methods);
    phpglfw_buffer_glhalf_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_glhalf_ce->create_object = phpglfw_buffer_glhalf_create_handler;
    phpglfw_buffer_glhalf_ce->serialize = phpglfw_buffer_glhalf_serialize_handler;
    phpglfw_buffer_glhalf_ce->unserialize = phpglfw_buffer_glhalf_unserialize_handler;
    phpglfw_buffer_glhalf_ce->get_iterator = phpglfw_buffer_glhalf_get_iterator_handler;

	zend_class_implements(phpglfw_buffer_glhalf_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glhalf_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_buffer_glhalf_handlers.offset = XtOffsetOf(phpglfw_buffer_glhalf_object, std);
    
    phpglfw_buffer_glhalf_handlers.free_obj = phpglfw_buffer_glhalf_free_handler;
    phpglfw_buffer_glhalf_handlers.read_dimension = phpglfw_buffer_glhalf_array_get_handler;
    phpglfw_buffer_glhalf_handlers.write_dimension = phpglfw_buffer_glhalf_array_set_handler;
    phpglfw_buffer_glhalf_handlers.get_debug_info = phpglfw_buffer_glhalf_debug_info_handler;
    
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\DoubleBuffer", class_GL_Buffer_DoubleBuffer_methods);
    phpglfw_buffer_gldouble_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_gldouble_ce->create_object = phpglfw_buffer_gldouble_create_handler;
    phpglfw_buffer_gldouble_ce->serialize = phpglfw_buffer_gldouble_serialize_handler;
    phpglfw_buffer_gldouble_ce->unserialize = phpglfw_buffer_gldouble_unserialize_handler;
    phpglfw_buffer_gldouble_ce->get_iterator = phpglfw_buffer_gldouble_get_iterator_handler;

	zend_class_implements(phpglfw_buffer_gldouble_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_gldouble_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_buffer_gldouble_handlers.offset = XtOffsetOf(phpglfw_buffer_gldouble_object, std);
    
    phpglfw_buffer_gldouble_handlers.free_obj = phpglfw_buffer_gldouble_free_handler;
    phpglfw_buffer_gldouble_handlers.read_dimension = phpglfw_buffer_gldouble_array_get_handler;
    phpglfw_buffer_gldouble_handlers.write_dimension = phpglfw_buffer_gldouble_array_set_handler;
    phpglfw_buffer_gldouble_handlers.get_debug_info = phpglfw_buffer_gldouble_debug_info_handler;
    
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\IntBuffer", class_GL_Buffer_IntBuffer_methods);
    phpglfw_buffer_glint_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_glint_ce->create_object = phpglfw_buffer_glint_create_handler;
    phpglfw_buffer_glint_ce->serialize = phpglfw_buffer_glint_serialize_handler;
    phpglfw_buffer_glint_ce->unserialize = phpglfw_buffer_glint_unserialize_handler;
    phpglfw_buffer_glint_ce->get_iterator = phpglfw_buffer_glint_get_iterator_handler;

	zend_class_implements(phpglfw_buffer_glint_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glint_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_buffer_glint_handlers.offset = XtOffsetOf(phpglfw_buffer_glint_object, std);
    
    phpglfw_buffer_glint_handlers.free_obj = phpglfw_buffer_glint_free_handler;
    phpglfw_buffer_glint_handlers.read_dimension = phpglfw_buffer_glint_array_get_handler;
    phpglfw_buffer_glint_handlers.write_dimension = phpglfw_buffer_glint_array_set_handler;
    phpglfw_buffer_glint_handlers.get_debug_info = phpglfw_buffer_glint_debug_info_handler;
    
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\UIntBuffer", class_GL_Buffer_UIntBuffer_methods);
    phpglfw_buffer_gluint_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_gluint_ce->create_object = phpglfw_buffer_gluint_create_handler;
    phpglfw_buffer_gluint_ce->serialize = phpglfw_buffer_gluint_serialize_handler;
    phpglfw_buffer_gluint_ce->unserialize = phpglfw_buffer_gluint_unserialize_handler;
    phpglfw_buffer_gluint_ce->get_iterator = phpglfw_buffer_gluint_get_iterator_handler;

	zend_class_implements(phpglfw_buffer_gluint_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_gluint_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_buffer_gluint_handlers.offset = XtOffsetOf(phpglfw_buffer_gluint_object, std);
    
    phpglfw_buffer_gluint_handlers.free_obj = phpglfw_buffer_gluint_free_handler;
    phpglfw_buffer_gluint_handlers.read_dimension = phpglfw_buffer_gluint_array_get_handler;
    phpglfw_buffer_gluint_handlers.write_dimension = phpglfw_buffer_gluint_array_set_handler;
    phpglfw_buffer_gluint_handlers.get_debug_info = phpglfw_buffer_gluint_debug_info_handler;
    
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\ShortBuffer", class_GL_Buffer_ShortBuffer_methods);
    phpglfw_buffer_glshort_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_glshort_ce->create_object = phpglfw_buffer_glshort_create_handler;
    phpglfw_buffer_glshort_ce->serialize = phpglfw_buffer_glshort_serialize_handler;
    phpglfw_buffer_glshort_ce->unserialize = phpglfw_buffer_glshort_unserialize_handler;
    phpglfw_buffer_glshort_ce->get_iterator = phpglfw_buffer_glshort_get_iterator_handler;

	zend_class_implements(phpglfw_buffer_glshort_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glshort_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_buffer_glshort_handlers.offset = XtOffsetOf(phpglfw_buffer_glshort_object, std);
    
    phpglfw_buffer_glshort_handlers.free_obj = phpglfw_buffer_glshort_free_handler;
    phpglfw_buffer_glshort_handlers.read_dimension = phpglfw_buffer_glshort_array_get_handler;
    phpglfw_buffer_glshort_handlers.write_dimension = phpglfw_buffer_glshort_array_set_handler;
    phpglfw_buffer_glshort_handlers.get_debug_info = phpglfw_buffer_glshort_debug_info_handler;
    
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\UShortBuffer", class_GL_Buffer_UShortBuffer_methods);
    phpglfw_buffer_glushort_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_glushort_ce->create_object = phpglfw_buffer_glushort_create_handler;
    phpglfw_buffer_glushort_ce->serialize = phpglfw_buffer_glushort_serialize_handler;
    phpglfw_buffer_glushort_ce->unserialize = phpglfw_buffer_glushort_unserialize_handler;
    phpglfw_buffer_glushort_ce->get_iterator = phpglfw_buffer_glushort_get_iterator_handler;

	zend_class_implements(phpglfw_buffer_glushort_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glushort_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_buffer_glushort_handlers.offset = XtOffsetOf(phpglfw_buffer_glushort_object, std);
    
    phpglfw_buffer_glushort_handlers.free_obj = phpglfw_buffer_glushort_free_handler;
    phpglfw_buffer_glushort_handlers.read_dimension = phpglfw_buffer_glushort_array_get_handler;
    phpglfw_buffer_glushort_handlers.write_dimension = phpglfw_buffer_glushort_array_set_handler;
    phpglfw_buffer_glushort_handlers.get_debug_info = phpglfw_buffer_glushort_debug_info_handler;
    
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\ByteBuffer", class_GL_Buffer_ByteBuffer_methods);
    phpglfw_buffer_glbyte_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_glbyte_ce->create_object = phpglfw_buffer_glbyte_create_handler;
    phpglfw_buffer_glbyte_ce->serialize = phpglfw_buffer_glbyte_serialize_handler;
    phpglfw_buffer_glbyte_ce->unserialize = phpglfw_buffer_glbyte_unserialize_handler;
    phpglfw_buffer_glbyte_ce->get_iterator = phpglfw_buffer_glbyte_get_iterator_handler;

	zend_class_implements(phpglfw_buffer_glbyte_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glbyte_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_buffer_glbyte_handlers.offset = XtOffsetOf(phpglfw_buffer_glbyte_object, std);
    
    phpglfw_buffer_glbyte_handlers.free_obj = phpglfw_buffer_glbyte_free_handler;
    phpglfw_buffer_glbyte_handlers.read_dimension = phpglfw_buffer_glbyte_array_get_handler;
    phpglfw_buffer_glbyte_handlers.write_dimension = phpglfw_buffer_glbyte_array_set_handler;
    phpglfw_buffer_glbyte_handlers.get_debug_info = phpglfw_buffer_glbyte_debug_info_handler;
    
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\UByteBuffer", class_GL_Buffer_UByteBuffer_methods);
    phpglfw_buffer_glubyte_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_glubyte_ce->create_object = phpglfw_buffer_glubyte_create_handler;
    phpglfw_buffer_glubyte_ce->serialize = phpglfw_buffer_glubyte_serialize_handler;
    phpglfw_buffer_glubyte_ce->unserialize = phpglfw_buffer_glubyte_unserialize_handler;
    phpglfw_buffer_glubyte_ce->get_iterator = phpglfw_buffer_glubyte_get_iterator_handler;

	zend_class_implements(phpglfw_buffer_glubyte_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glubyte_handlers, &std_object_handlers, sizeof(zend_object_handlers));
    phpglfw_buffer_glubyte_handlers.offset = XtOffsetOf(phpglfw_buffer_glubyte_object, std);
    
    phpglfw_buffer_glubyte_handlers.free_obj = phpglfw_buffer_glubyte_free_handler;
    phpglfw_buffer_glubyte_handlers.read_dimension = phpglfw_buffer_glubyte_array_get_handler;
    phpglfw_buffer_glubyte_handlers.write_dimension = phpglfw_buffer_glubyte_array_set_handler;
    phpglfw_buffer_glubyte_handlers.get_debug_info = phpglfw_buffer_glubyte_debug_info_handler;
    
}