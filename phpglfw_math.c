/**
 * PHP-glfw 
 * 
 * Extension: GL Math
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
#include "phpglfw_math.h"

#include "phpglfw_arginfo.h"

#include "php.h"
#include "Zend/zend_smart_str.h"
#include "linmath.h"

zend_class_entry *phpglfw_math_vec2_ce; 
zend_class_entry *phpglfw_math_vec3_ce; 
zend_class_entry *phpglfw_math_vec4_ce; 

/**
 * GL\Math\Vec2 
 * 
 * ----------------------------------------------------------------------------
 */
typedef struct _phpglfw_math_vec2_object {
    vec2 data;
    zend_object std;
} phpglfw_math_vec2_object; 

static zend_object_handlers phpglfw_math_vec2_handlers;

zend_always_inline phpglfw_math_vec2_object* phpglfw_math_vec2_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_math_vec2_object *) ((char *) (obj) - XtOffsetOf(phpglfw_math_vec2_object, std));
}

/**
 * Creation (GL\Math\Vec2)
 */
zend_object *phpglfw_math_vec2_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_math_vec2_object) + zend_object_properties_size(class_type);
    phpglfw_math_vec2_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    for(int i=0; i<2; i++) {
        intern->data[i] = 0.0f;
    }

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_math_vec2_handlers;

    return &intern->std;
}

static HashTable *phpglfw_math_vec2_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(2);
    *is_temp = 1;

    ZVAL_DOUBLE(&zv, obj_ptr->data[0]);
    zend_hash_str_update(ht, "x", sizeof("x") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[1]);
    zend_hash_str_update(ht, "y", sizeof("y") - 1, &zv);
 

    return ht;
}

static zval *phpglfw_math_vec2_read_prop_handler(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) 
{
    zval *retval;
    phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(object);

	if ((type != BP_VAR_R && type != BP_VAR_IS)) {
		zend_throw_error(NULL, "GL\\Math\\Vec2"  " properties are virtual and cannot be referenced.");
		retval = &EG( uninitialized_zval );
	} else {

        if (zend_string_equals_literal(member, "x")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "y")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[1]);
        }
        else if (zend_string_equals_literal(member, "r")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "g")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[1]);
        }
        else {
            ZVAL_NULL(retval);
        }
	}

	return retval;
}

static zval *phpglfw_math_vec2_write_prop_handler(zend_object *object, zend_string *member, zval *value, void **cache_slot) 
{
    if (Z_TYPE_P(value) == IS_LONG) {
        convert_to_double(value);
    }
    
    if (Z_TYPE_P(value) != IS_DOUBLE) {
		zend_throw_error(NULL, "GL\\Math\\Vec2" " properties can only be of type 'float'.");
        return value;
    }
    else {
        phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(object);

        if (zend_string_equals_literal(member, "x")) {
		    obj_ptr->data[0] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "y")) {
		    obj_ptr->data[1] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "r")) {
		    obj_ptr->data[0] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "g")) {
		    obj_ptr->data[1] = Z_DVAL_P(value); 
        }
        else {
		    zend_throw_error(NULL, "GL\\Math\\Vec2" " trying to write into a invalid property.");
        }
    }

	return value;
}

static zend_always_inline int phpglfw_math_vec2_do_op_scalar_handler(zend_uchar opcode, phpglfw_math_vec2_object *resobj, phpglfw_math_vec2_object *vecobj, zval *mod)
{
    if (Z_TYPE_P(mod) == IS_LONG) {
        convert_to_double(mod);
    }

    switch (opcode) {
    case ZEND_ADD:
        vec2_s_add(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_SUB:
        vec2_s_sub(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_MUL:
        vec2_s_mul(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_DIV:
        vec2_s_div(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    default:
        return FAILURE;
    }
}

static int phpglfw_math_vec2_do_op_handler(zend_uchar opcode, zval *result, zval *op1, zval *op2)
{
    object_init_ex(result, phpglfw_math_vec2_ce);
    phpglfw_math_vec2_object *resobj = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(result));

    // if left and right are both vec...
    if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == phpglfw_math_vec2_ce &&
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == phpglfw_math_vec2_ce    ) {
        phpglfw_math_vec2_object *vecobj1 = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(op1));
        phpglfw_math_vec2_object *vecobj2 = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(op2));

        switch (opcode) {
        case ZEND_ADD:
            vec2_add(resobj->data, vecobj1->data, vecobj2->data);
            // resobj->vec[0] = vecobj1->vec[0] + vecobj2->vec[0];
            // resobj->vec[1] = vecobj1->vec[1] + vecobj2->vec[1];
            // resobj->vec[2] = vecobj1->vec[2] + vecobj2->vec[2];
            return SUCCESS;
        case ZEND_SUB:
            vec2_sub(resobj->data, vecobj1->data, vecobj2->data);
            return SUCCESS;
        case ZEND_MUL:
            vec2_mul(resobj->data, vecobj1->data, vecobj2->data);
            return SUCCESS;
        case ZEND_DIV:
            vec2_div(resobj->data, vecobj1->data, vecobj2->data);
            return SUCCESS;
        default:
            return FAILURE;
        }
    }
    // if left is a vec and right a scalar number
    else if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == phpglfw_math_vec2_ce &&
        (Z_TYPE_P(op2) == IS_LONG || Z_TYPE_P(op2) == IS_DOUBLE)
    ) {
        phpglfw_math_vec2_object *vecobj1 = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(op1));
        return phpglfw_math_vec2_do_op_scalar_handler(opcode, resobj, vecobj1, op2);
    }
    // otherway around
    else if (
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == phpglfw_math_vec2_ce &&
        (Z_TYPE_P(op1) == IS_LONG || Z_TYPE_P(op1) == IS_DOUBLE)
    ) {
        phpglfw_math_vec2_object *vecobj1 = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(op2));
        return phpglfw_math_vec2_do_op_scalar_handler(opcode, resobj, vecobj1, op1);
    }
    else {
        return FAILURE;
    }
}

PHP_METHOD(GL_Math_Vec2, __construct)
{
    zval *obj;
    obj = getThis();
    phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(obj));

    double xval = 0.0;
    double yval = 0.0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|dd", &xval, &yval) == FAILURE) { 
        return;
    }

    if (ZEND_NUM_ARGS() == 0) {
        return;
    }

    // if only one argument is given we initalize all values with it
    else if (ZEND_NUM_ARGS() == 1) {
        obj_ptr->data[0] = xval;
        obj_ptr->data[1] = xval;
        return;
    }

    obj_ptr->data[0] = xval;
    obj_ptr->data[1] = yval;
}

PHP_METHOD(GL_Math_Vec2, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "vec3(");

    // smart_str_append_double(&my_str, obj_ptr->vec[0], 4, true);
    // smart_str_appends(&my_str, ", ");
    // smart_str_append_double(&my_str, obj_ptr->vec[1], 4, true);
    // smart_str_appends(&my_str, ", ");
    // smart_str_append_double(&my_str, obj_ptr->vec[2], 4, true);
    // smart_str_appends(&my_str, ")");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(GL_Math_Vec2, length)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_DOUBLE(vec2_len(obj_ptr->data));
}

PHP_METHOD(GL_Math_Vec2, dot)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, phpglfw_math_vec2_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_vec2_object *leftvec_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec2_object *rightvec_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(rightvec_zval));

    RETURN_DOUBLE(vec2_mul_inner(leftvec_ptr->data, rightvec_ptr->data));
}

PHP_METHOD(GL_Math_Vec2, distance)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, phpglfw_math_vec2_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_vec2_object *leftvec_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec2_object *rightvec_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(rightvec_zval));

    RETURN_DOUBLE(sqrt(vec2_distance_square(leftvec_ptr->data, rightvec_ptr->data)));
}

PHP_METHOD(GL_Math_Vec2, distance2)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, phpglfw_math_vec2_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_vec2_object *leftvec_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec2_object *rightvec_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(rightvec_zval));

    RETURN_DOUBLE(vec2_distance_square(leftvec_ptr->data, rightvec_ptr->data));
}

PHP_METHOD(GL_Math_Vec2, normalize)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec2_ce);
    phpglfw_math_vec2_object *resobj = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    vec2_norm(resobj->data, obj_ptr->data);
}

PHP_METHOD(GL_Math_Vec2, abs)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec2_ce);
    phpglfw_math_vec2_object *resobj = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    vec2_abs(resobj->data, obj_ptr->data);
}

/**
 * GL\Math\Vec3 
 * 
 * ----------------------------------------------------------------------------
 */
typedef struct _phpglfw_math_vec3_object {
    vec3 data;
    zend_object std;
} phpglfw_math_vec3_object; 

static zend_object_handlers phpglfw_math_vec3_handlers;

zend_always_inline phpglfw_math_vec3_object* phpglfw_math_vec3_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_math_vec3_object *) ((char *) (obj) - XtOffsetOf(phpglfw_math_vec3_object, std));
}

/**
 * Creation (GL\Math\Vec3)
 */
zend_object *phpglfw_math_vec3_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_math_vec3_object) + zend_object_properties_size(class_type);
    phpglfw_math_vec3_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    for(int i=0; i<3; i++) {
        intern->data[i] = 0.0f;
    }

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_math_vec3_handlers;

    return &intern->std;
}

static HashTable *phpglfw_math_vec3_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(3);
    *is_temp = 1;

    ZVAL_DOUBLE(&zv, obj_ptr->data[0]);
    zend_hash_str_update(ht, "x", sizeof("x") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[1]);
    zend_hash_str_update(ht, "y", sizeof("y") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[2]);
    zend_hash_str_update(ht, "z", sizeof("z") - 1, &zv);
 

    return ht;
}

static zval *phpglfw_math_vec3_read_prop_handler(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) 
{
    zval *retval;
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(object);

	if ((type != BP_VAR_R && type != BP_VAR_IS)) {
		zend_throw_error(NULL, "GL\\Math\\Vec3"  " properties are virtual and cannot be referenced.");
		retval = &EG( uninitialized_zval );
	} else {

        if (zend_string_equals_literal(member, "x")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "y")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[1]);
        }
        else if (zend_string_equals_literal(member, "z")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[2]);
        }
        else if (zend_string_equals_literal(member, "r")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "g")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[1]);
        }
        else if (zend_string_equals_literal(member, "b")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[2]);
        }
        else {
            ZVAL_NULL(retval);
        }
	}

	return retval;
}

static zval *phpglfw_math_vec3_write_prop_handler(zend_object *object, zend_string *member, zval *value, void **cache_slot) 
{
    if (Z_TYPE_P(value) == IS_LONG) {
        convert_to_double(value);
    }
    
    if (Z_TYPE_P(value) != IS_DOUBLE) {
		zend_throw_error(NULL, "GL\\Math\\Vec3" " properties can only be of type 'float'.");
        return value;
    }
    else {
        phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(object);

        if (zend_string_equals_literal(member, "x")) {
		    obj_ptr->data[0] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "y")) {
		    obj_ptr->data[1] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "z")) {
		    obj_ptr->data[2] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "r")) {
		    obj_ptr->data[0] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "g")) {
		    obj_ptr->data[1] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "b")) {
		    obj_ptr->data[2] = Z_DVAL_P(value); 
        }
        else {
		    zend_throw_error(NULL, "GL\\Math\\Vec3" " trying to write into a invalid property.");
        }
    }

	return value;
}

static zend_always_inline int phpglfw_math_vec3_do_op_scalar_handler(zend_uchar opcode, phpglfw_math_vec3_object *resobj, phpglfw_math_vec3_object *vecobj, zval *mod)
{
    if (Z_TYPE_P(mod) == IS_LONG) {
        convert_to_double(mod);
    }

    switch (opcode) {
    case ZEND_ADD:
        vec3_s_add(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_SUB:
        vec3_s_sub(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_MUL:
        vec3_s_mul(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_DIV:
        vec3_s_div(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    default:
        return FAILURE;
    }
}

static int phpglfw_math_vec3_do_op_handler(zend_uchar opcode, zval *result, zval *op1, zval *op2)
{
    object_init_ex(result, phpglfw_math_vec3_ce);
    phpglfw_math_vec3_object *resobj = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(result));

    // if left and right are both vec...
    if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == phpglfw_math_vec3_ce &&
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == phpglfw_math_vec3_ce    ) {
        phpglfw_math_vec3_object *vecobj1 = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(op1));
        phpglfw_math_vec3_object *vecobj2 = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(op2));

        switch (opcode) {
        case ZEND_ADD:
            vec3_add(resobj->data, vecobj1->data, vecobj2->data);
            // resobj->vec[0] = vecobj1->vec[0] + vecobj2->vec[0];
            // resobj->vec[1] = vecobj1->vec[1] + vecobj2->vec[1];
            // resobj->vec[2] = vecobj1->vec[2] + vecobj2->vec[2];
            return SUCCESS;
        case ZEND_SUB:
            vec3_sub(resobj->data, vecobj1->data, vecobj2->data);
            return SUCCESS;
        case ZEND_MUL:
            vec3_mul(resobj->data, vecobj1->data, vecobj2->data);
            return SUCCESS;
        case ZEND_DIV:
            vec3_div(resobj->data, vecobj1->data, vecobj2->data);
            return SUCCESS;
        default:
            return FAILURE;
        }
    }
    // if left is a vec and right a scalar number
    else if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == phpglfw_math_vec3_ce &&
        (Z_TYPE_P(op2) == IS_LONG || Z_TYPE_P(op2) == IS_DOUBLE)
    ) {
        phpglfw_math_vec3_object *vecobj1 = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(op1));
        return phpglfw_math_vec3_do_op_scalar_handler(opcode, resobj, vecobj1, op2);
    }
    // otherway around
    else if (
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == phpglfw_math_vec3_ce &&
        (Z_TYPE_P(op1) == IS_LONG || Z_TYPE_P(op1) == IS_DOUBLE)
    ) {
        phpglfw_math_vec3_object *vecobj1 = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(op2));
        return phpglfw_math_vec3_do_op_scalar_handler(opcode, resobj, vecobj1, op1);
    }
    else {
        return FAILURE;
    }
}

PHP_METHOD(GL_Math_Vec3, __construct)
{
    zval *obj;
    obj = getThis();
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(obj));

    double xval = 0.0;
    double yval = 0.0;
    double zval = 0.0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|ddd", &xval, &yval, &zval) == FAILURE) { 
        return;
    }

    if (ZEND_NUM_ARGS() == 0) {
        return;
    }

    // if only one argument is given we initalize all values with it
    else if (ZEND_NUM_ARGS() == 1) {
        obj_ptr->data[0] = xval;
        obj_ptr->data[1] = xval;
        obj_ptr->data[2] = xval;
        return;
    }

    obj_ptr->data[0] = xval;
    obj_ptr->data[1] = yval;
    obj_ptr->data[2] = zval;
}

PHP_METHOD(GL_Math_Vec3, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "vec3(");

    // smart_str_append_double(&my_str, obj_ptr->vec[0], 4, true);
    // smart_str_appends(&my_str, ", ");
    // smart_str_append_double(&my_str, obj_ptr->vec[1], 4, true);
    // smart_str_appends(&my_str, ", ");
    // smart_str_append_double(&my_str, obj_ptr->vec[2], 4, true);
    // smart_str_appends(&my_str, ")");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(GL_Math_Vec3, length)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_DOUBLE(vec3_len(obj_ptr->data));
}

PHP_METHOD(GL_Math_Vec3, dot)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_vec3_object *leftvec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec3_object *rightvec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(rightvec_zval));

    RETURN_DOUBLE(vec3_mul_inner(leftvec_ptr->data, rightvec_ptr->data));
}

PHP_METHOD(GL_Math_Vec3, distance)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_vec3_object *leftvec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec3_object *rightvec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(rightvec_zval));

    RETURN_DOUBLE(sqrt(vec3_distance_square(leftvec_ptr->data, rightvec_ptr->data)));
}

PHP_METHOD(GL_Math_Vec3, distance2)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_vec3_object *leftvec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec3_object *rightvec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(rightvec_zval));

    RETURN_DOUBLE(vec3_distance_square(leftvec_ptr->data, rightvec_ptr->data));
}

PHP_METHOD(GL_Math_Vec3, normalize)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec3_ce);
    phpglfw_math_vec3_object *resobj = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    vec3_norm(resobj->data, obj_ptr->data);
}

PHP_METHOD(GL_Math_Vec3, abs)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec3_ce);
    phpglfw_math_vec3_object *resobj = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    vec3_abs(resobj->data, obj_ptr->data);
}

/**
 * GL\Math\Vec4 
 * 
 * ----------------------------------------------------------------------------
 */
typedef struct _phpglfw_math_vec4_object {
    vec4 data;
    zend_object std;
} phpglfw_math_vec4_object; 

static zend_object_handlers phpglfw_math_vec4_handlers;

zend_always_inline phpglfw_math_vec4_object* phpglfw_math_vec4_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_math_vec4_object *) ((char *) (obj) - XtOffsetOf(phpglfw_math_vec4_object, std));
}

/**
 * Creation (GL\Math\Vec4)
 */
zend_object *phpglfw_math_vec4_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_math_vec4_object) + zend_object_properties_size(class_type);
    phpglfw_math_vec4_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    for(int i=0; i<4; i++) {
        intern->data[i] = 0.0f;
    }

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_math_vec4_handlers;

    return &intern->std;
}

static HashTable *phpglfw_math_vec4_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(4);
    *is_temp = 1;

    ZVAL_DOUBLE(&zv, obj_ptr->data[0]);
    zend_hash_str_update(ht, "x", sizeof("x") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[1]);
    zend_hash_str_update(ht, "y", sizeof("y") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[2]);
    zend_hash_str_update(ht, "z", sizeof("z") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[3]);
    zend_hash_str_update(ht, "w", sizeof("w") - 1, &zv);
 

    return ht;
}

static zval *phpglfw_math_vec4_read_prop_handler(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) 
{
    zval *retval;
    phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(object);

	if ((type != BP_VAR_R && type != BP_VAR_IS)) {
		zend_throw_error(NULL, "GL\\Math\\Vec4"  " properties are virtual and cannot be referenced.");
		retval = &EG( uninitialized_zval );
	} else {

        if (zend_string_equals_literal(member, "x")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "y")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[1]);
        }
        else if (zend_string_equals_literal(member, "z")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[2]);
        }
        else if (zend_string_equals_literal(member, "w")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[3]);
        }
        else if (zend_string_equals_literal(member, "r")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "g")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[1]);
        }
        else if (zend_string_equals_literal(member, "b")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[2]);
        }
        else if (zend_string_equals_literal(member, "a")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[3]);
        }
        else {
            ZVAL_NULL(retval);
        }
	}

	return retval;
}

static zval *phpglfw_math_vec4_write_prop_handler(zend_object *object, zend_string *member, zval *value, void **cache_slot) 
{
    if (Z_TYPE_P(value) == IS_LONG) {
        convert_to_double(value);
    }
    
    if (Z_TYPE_P(value) != IS_DOUBLE) {
		zend_throw_error(NULL, "GL\\Math\\Vec4" " properties can only be of type 'float'.");
        return value;
    }
    else {
        phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(object);

        if (zend_string_equals_literal(member, "x")) {
		    obj_ptr->data[0] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "y")) {
		    obj_ptr->data[1] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "z")) {
		    obj_ptr->data[2] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "w")) {
		    obj_ptr->data[3] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "r")) {
		    obj_ptr->data[0] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "g")) {
		    obj_ptr->data[1] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "b")) {
		    obj_ptr->data[2] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "a")) {
		    obj_ptr->data[3] = Z_DVAL_P(value); 
        }
        else {
		    zend_throw_error(NULL, "GL\\Math\\Vec4" " trying to write into a invalid property.");
        }
    }

	return value;
}

static zend_always_inline int phpglfw_math_vec4_do_op_scalar_handler(zend_uchar opcode, phpglfw_math_vec4_object *resobj, phpglfw_math_vec4_object *vecobj, zval *mod)
{
    if (Z_TYPE_P(mod) == IS_LONG) {
        convert_to_double(mod);
    }

    switch (opcode) {
    case ZEND_ADD:
        vec4_s_add(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_SUB:
        vec4_s_sub(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_MUL:
        vec4_s_mul(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_DIV:
        vec4_s_div(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    default:
        return FAILURE;
    }
}

static int phpglfw_math_vec4_do_op_handler(zend_uchar opcode, zval *result, zval *op1, zval *op2)
{
    object_init_ex(result, phpglfw_math_vec4_ce);
    phpglfw_math_vec4_object *resobj = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(result));

    // if left and right are both vec...
    if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == phpglfw_math_vec4_ce &&
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == phpglfw_math_vec4_ce    ) {
        phpglfw_math_vec4_object *vecobj1 = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(op1));
        phpglfw_math_vec4_object *vecobj2 = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(op2));

        switch (opcode) {
        case ZEND_ADD:
            vec4_add(resobj->data, vecobj1->data, vecobj2->data);
            // resobj->vec[0] = vecobj1->vec[0] + vecobj2->vec[0];
            // resobj->vec[1] = vecobj1->vec[1] + vecobj2->vec[1];
            // resobj->vec[2] = vecobj1->vec[2] + vecobj2->vec[2];
            return SUCCESS;
        case ZEND_SUB:
            vec4_sub(resobj->data, vecobj1->data, vecobj2->data);
            return SUCCESS;
        case ZEND_MUL:
            vec4_mul(resobj->data, vecobj1->data, vecobj2->data);
            return SUCCESS;
        case ZEND_DIV:
            vec4_div(resobj->data, vecobj1->data, vecobj2->data);
            return SUCCESS;
        default:
            return FAILURE;
        }
    }
    // if left is a vec and right a scalar number
    else if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == phpglfw_math_vec4_ce &&
        (Z_TYPE_P(op2) == IS_LONG || Z_TYPE_P(op2) == IS_DOUBLE)
    ) {
        phpglfw_math_vec4_object *vecobj1 = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(op1));
        return phpglfw_math_vec4_do_op_scalar_handler(opcode, resobj, vecobj1, op2);
    }
    // otherway around
    else if (
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == phpglfw_math_vec4_ce &&
        (Z_TYPE_P(op1) == IS_LONG || Z_TYPE_P(op1) == IS_DOUBLE)
    ) {
        phpglfw_math_vec4_object *vecobj1 = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(op2));
        return phpglfw_math_vec4_do_op_scalar_handler(opcode, resobj, vecobj1, op1);
    }
    else {
        return FAILURE;
    }
}

PHP_METHOD(GL_Math_Vec4, __construct)
{
    zval *obj;
    obj = getThis();
    phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    double xval = 0.0;
    double yval = 0.0;
    double zval = 0.0;
    double wval = 0.0;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|dddd", &xval, &yval, &zval, &wval) == FAILURE) { 
        return;
    }

    if (ZEND_NUM_ARGS() == 0) {
        return;
    }

    // if only one argument is given we initalize all values with it
    else if (ZEND_NUM_ARGS() == 1) {
        obj_ptr->data[0] = xval;
        obj_ptr->data[1] = xval;
        obj_ptr->data[2] = xval;
        obj_ptr->data[3] = xval;
        return;
    }

    obj_ptr->data[0] = xval;
    obj_ptr->data[1] = yval;
    obj_ptr->data[2] = zval;
    obj_ptr->data[3] = wval;
}

PHP_METHOD(GL_Math_Vec4, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "vec3(");

    // smart_str_append_double(&my_str, obj_ptr->vec[0], 4, true);
    // smart_str_appends(&my_str, ", ");
    // smart_str_append_double(&my_str, obj_ptr->vec[1], 4, true);
    // smart_str_appends(&my_str, ", ");
    // smart_str_append_double(&my_str, obj_ptr->vec[2], 4, true);
    // smart_str_appends(&my_str, ")");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(GL_Math_Vec4, length)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_DOUBLE(vec4_len(obj_ptr->data));
}

PHP_METHOD(GL_Math_Vec4, dot)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, phpglfw_math_vec4_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_vec4_object *leftvec_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec4_object *rightvec_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(rightvec_zval));

    RETURN_DOUBLE(vec4_mul_inner(leftvec_ptr->data, rightvec_ptr->data));
}

PHP_METHOD(GL_Math_Vec4, distance)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, phpglfw_math_vec4_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_vec4_object *leftvec_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec4_object *rightvec_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(rightvec_zval));

    RETURN_DOUBLE(sqrt(vec4_distance_square(leftvec_ptr->data, rightvec_ptr->data)));
}

PHP_METHOD(GL_Math_Vec4, distance2)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, phpglfw_math_vec4_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_vec4_object *leftvec_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec4_object *rightvec_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(rightvec_zval));

    RETURN_DOUBLE(vec4_distance_square(leftvec_ptr->data, rightvec_ptr->data));
}

PHP_METHOD(GL_Math_Vec4, normalize)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec4_ce);
    phpglfw_math_vec4_object *resobj = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    vec4_norm(resobj->data, obj_ptr->data);
}

PHP_METHOD(GL_Math_Vec4, abs)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec4_ce);
    phpglfw_math_vec4_object *resobj = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    vec4_abs(resobj->data, obj_ptr->data);
}


void phpglfw_register_math_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;

 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Math\\Vec2", class_GL_Math_Vec2_methods);
    phpglfw_math_vec2_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_math_vec2_ce->create_object = phpglfw_math_vec2_create_handler;

    memcpy(&phpglfw_math_vec2_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_math_vec2_handlers));
    phpglfw_math_vec2_handlers.get_debug_info = phpglfw_math_vec2_debug_info_handler;
    phpglfw_math_vec2_handlers.read_property = phpglfw_math_vec2_read_prop_handler;
    phpglfw_math_vec2_handlers.write_property = phpglfw_math_vec2_write_prop_handler;
    phpglfw_math_vec2_handlers.do_operation = phpglfw_math_vec2_do_op_handler;
    phpglfw_math_vec2_handlers.offset = XtOffsetOf(phpglfw_math_vec2_object, std);
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Math\\Vec3", class_GL_Math_Vec3_methods);
    phpglfw_math_vec3_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_math_vec3_ce->create_object = phpglfw_math_vec3_create_handler;

    memcpy(&phpglfw_math_vec3_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_math_vec3_handlers));
    phpglfw_math_vec3_handlers.get_debug_info = phpglfw_math_vec3_debug_info_handler;
    phpglfw_math_vec3_handlers.read_property = phpglfw_math_vec3_read_prop_handler;
    phpglfw_math_vec3_handlers.write_property = phpglfw_math_vec3_write_prop_handler;
    phpglfw_math_vec3_handlers.do_operation = phpglfw_math_vec3_do_op_handler;
    phpglfw_math_vec3_handlers.offset = XtOffsetOf(phpglfw_math_vec3_object, std);
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Math\\Vec4", class_GL_Math_Vec4_methods);
    phpglfw_math_vec4_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_math_vec4_ce->create_object = phpglfw_math_vec4_create_handler;

    memcpy(&phpglfw_math_vec4_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_math_vec4_handlers));
    phpglfw_math_vec4_handlers.get_debug_info = phpglfw_math_vec4_debug_info_handler;
    phpglfw_math_vec4_handlers.read_property = phpglfw_math_vec4_read_prop_handler;
    phpglfw_math_vec4_handlers.write_property = phpglfw_math_vec4_write_prop_handler;
    phpglfw_math_vec4_handlers.do_operation = phpglfw_math_vec4_do_op_handler;
    phpglfw_math_vec4_handlers.offset = XtOffsetOf(phpglfw_math_vec4_object, std);
}
