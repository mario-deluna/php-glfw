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

static HashTable *phpglfw_buffer_glfloat_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(2);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

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

    smart_str_appends(&my_str, "GL\\Buffer\\FloatBuffer(");
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

static HashTable *phpglfw_buffer_gldouble_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_gldouble_object *obj_ptr = phpglfw_buffer_gldouble_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(2);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

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

    smart_str_appends(&my_str, "GL\\Buffer\\FloatBuffer(");
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

static HashTable *phpglfw_buffer_glint_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(2);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

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

    smart_str_appends(&my_str, "GL\\Buffer\\FloatBuffer(");
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

static HashTable *phpglfw_buffer_glbyte_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_buffer_glbyte_object *obj_ptr = phpglfw_buffer_glbyte_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(2);
    *is_temp = 1;

    ZVAL_LONG(&zv, cvector_capacity(obj_ptr->vec));
    zend_hash_str_update(ht, "capacity", sizeof("capacity") - 1, &zv);
    ZVAL_LONG(&zv, cvector_size(obj_ptr->vec));
    zend_hash_str_update(ht, "size", sizeof("size") - 1, &zv);

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

    smart_str_appends(&my_str, "GL\\Buffer\\FloatBuffer(");
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

zval *phpglfw_buffer_glint_array_get(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
		php_error( E_ERROR, "Cannot apply [] to GL\\Buffer\\BufferInterface object" );
	}

    phpglfw_buffer_glint_object *obj_ptr = phpglfw_buffer_glint_objectptr_from_zobj_p(object);

    if(Z_TYPE_P(offset) == IS_LONG) {
		size_t index = (size_t)Z_LVAL_P(offset);
        ZVAL_LONG(rv, obj_ptr->vec[index]);
	} else {
		php_error( E_ERROR, "Cannot apply [] to GL\\Buffer\\BufferInterface object" );
		ZVAL_NULL(rv);
	}

	return rv;
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

	zend_class_implements(phpglfw_buffer_glfloat_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glfloat_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_buffer_glfloat_handlers));
    phpglfw_buffer_glfloat_handlers.free_obj = phpglfw_buffer_glfloat_free_handler;
    phpglfw_buffer_glfloat_handlers.get_debug_info = phpglfw_buffer_glfloat_debug_info_handler;
    phpglfw_buffer_glfloat_handlers.offset = XtOffsetOf(phpglfw_buffer_glfloat_object, std);

    // float buffer
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\DoubleBuffer", class_GL_Buffer_DoubleBuffer_methods);
    phpglfw_buffer_gldouble_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_gldouble_ce->create_object = phpglfw_buffer_gldouble_create_handler;

	zend_class_implements(phpglfw_buffer_gldouble_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_gldouble_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_buffer_gldouble_handlers));
    phpglfw_buffer_gldouble_handlers.free_obj = phpglfw_buffer_gldouble_free_handler;
    phpglfw_buffer_gldouble_handlers.get_debug_info = phpglfw_buffer_gldouble_debug_info_handler;
    phpglfw_buffer_gldouble_handlers.offset = XtOffsetOf(phpglfw_buffer_gldouble_object, std);

    // float buffer
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\IntBuffer", class_GL_Buffer_IntBuffer_methods);
    phpglfw_buffer_glint_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_glint_ce->create_object = phpglfw_buffer_glint_create_handler;

	zend_class_implements(phpglfw_buffer_glint_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glint_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_buffer_glint_handlers));
    phpglfw_buffer_glint_handlers.free_obj = phpglfw_buffer_glint_free_handler;
    phpglfw_buffer_glint_handlers.get_debug_info = phpglfw_buffer_glint_debug_info_handler;
    phpglfw_buffer_glint_handlers.read_dimension = phpglfw_buffer_glint_array_get;
    phpglfw_buffer_glint_handlers.offset = XtOffsetOf(phpglfw_buffer_glint_object, std);

    // float buffer
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\ByteBuffer", class_GL_Buffer_ByteBuffer_methods);
    phpglfw_buffer_glbyte_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_buffer_glbyte_ce->create_object = phpglfw_buffer_glbyte_create_handler;

	zend_class_implements(phpglfw_buffer_glbyte_ce, 1, phpglfw_buffer_interface_ce);
    memcpy(&phpglfw_buffer_glbyte_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_buffer_glbyte_handlers));
    phpglfw_buffer_glbyte_handlers.free_obj = phpglfw_buffer_glbyte_free_handler;
    phpglfw_buffer_glbyte_handlers.get_debug_info = phpglfw_buffer_glbyte_debug_info_handler;
    phpglfw_buffer_glbyte_handlers.offset = XtOffsetOf(phpglfw_buffer_glbyte_object, std);

}