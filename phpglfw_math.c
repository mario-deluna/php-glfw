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

#if defined(DBL_MANT_DIG) && defined(DBL_MIN_EXP) && !defined(ZEND_DOUBLE_MAX_LENGTH)
#define ZEND_DOUBLE_MAX_LENGTH (3 + DBL_MANT_DIG - DBL_MIN_EXP)
#elif !defined(ZEND_DOUBLE_MAX_LENGTH)
#define ZEND_DOUBLE_MAX_LENGTH 1080
#endif

// becase the method is missing in some builds.. ???
void ZEND_FASTCALL glfw_smart_str_append_double(
		smart_str *str, double num, int precision, bool zero_fraction) {
	char buf[ZEND_DOUBLE_MAX_LENGTH];
#if PHP_API_VERSION <= 20200930
    sprintf(buf, "%.4f", num);
#else
	/* Model snprintf precision behavior. */
	zend_gcvt(num, precision ? precision : 1, '.', 'E', buf);
#endif
	smart_str_appends(str, buf);
	if (zero_fraction && zend_finite(num) && !strchr(buf, '.')) {
		smart_str_appendl(str, ".0", 2);
	}
}

zend_class_entry *phpglfw_glm_ce; 
zend_class_entry *phpglfw_math_vec2_ce; 
zend_class_entry *phpglfw_math_vec3_ce; 
zend_class_entry *phpglfw_math_vec4_ce; 
zend_class_entry *phpglfw_math_quat_ce; 
zend_class_entry *phpglfw_math_mat4_ce; 

zend_class_entry *phpglfw_get_math_vec2_ce() {
    return phpglfw_math_vec2_ce;
}
zend_class_entry *phpglfw_get_math_vec3_ce() {
    return phpglfw_math_vec3_ce;
}
zend_class_entry *phpglfw_get_math_vec4_ce() {
    return phpglfw_math_vec4_ce;
}
zend_class_entry *phpglfw_get_math_quat_ce() {
    return phpglfw_math_quat_ce;
}
zend_class_entry *phpglfw_get_math_mat4_ce() {
    return phpglfw_math_mat4_ce;
}

/**
 * GL\Math\Vec2 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_math_vec2_handlers;

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

zval *phpglfw_math_vec2_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Math\\Vec2 object");
	}

    phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(object);

    if (Z_TYPE_P(offset) == IS_LONG) {
		size_t index = (size_t)Z_LVAL_P(offset);

        if (index < 2) {
            ZVAL_DOUBLE(rv, obj_ptr->data[index]);
        } else {
            ZVAL_NULL(rv);
        }
	} else {
        zend_throw_error(NULL, "Only a int offset '$vec[int]' can be used with the GL\\Math\\Vec2 object");
		ZVAL_NULL(rv);
	}

	return rv;
}

void phpglfw_math_vec2_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_DOUBLE) {
        zend_throw_error(NULL, "Trying to store non float value in a Vec2.");
        return;
    }

    phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(object);

	if (offset == NULL) {
        zend_throw_error(NULL, "You cannot append values into a Vec2.");
	} 
    else {
        if (Z_TYPE_P(offset) == IS_LONG) {
            size_t index = (size_t)Z_LVAL_P(offset);

            if (index >= 2) {
                zend_throw_error(NULL, "Vec2 has a fixed space, the given index [%d] is out of bounds...",  (int) index);
            }
            obj_ptr->data[index] = Z_DVAL_P(value);
        } else {
            zend_throw_error(NULL, "Only a int offset '$vec[int]' can be used with the GL\\Math\\Vec2 object");
        }
    }
}

/**
 * Vector (Vec2) Property READ / WRITE
 * 
 * ----------------------------------------------------------------------------
 */
static zval *phpglfw_math_vec2_read_prop_handler(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) 
{
    phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(object);

	if ((type != BP_VAR_R && type != BP_VAR_IS)) {
		zend_throw_error(NULL, "GL\\Math\\Vec2"  " properties are virtual and cannot be referenced.");
		rv = &EG( uninitialized_zval );
	} else {

        if (zend_string_equals_literal(member, "x")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "y")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[1]);
        }
        else if (zend_string_equals_literal(member, "r")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "g")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[1]);
        }
        else {
            ZVAL_NULL(rv);
        }
	}

	return rv;
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


/**
 * Vector (Vec2) Operation Handler
 * 
 * ----------------------------------------------------------------------------
 */
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

/**
 * Vector operation handler
 */
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
    smart_str_appends(&my_str, "vec2(");

    for (int i = 0; i < 2; i++) {
        glfw_smart_str_append_double(&my_str, obj_ptr->data[i], 4, true);
        if (i < 2 - 1) {
            smart_str_appends(&my_str, ", ");
        }
    }
    smart_str_appends(&my_str, ")");
    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}


/**
 * Vector (Vec2) specific methods
 * 
 * ----------------------------------------------------------------------------
 */
PHP_METHOD(GL_Math_Vec2, copy)
{
    zval *obj;
    obj = getThis();
    phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec2_ce);
    phpglfw_math_vec2_object *resobj = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    // copy data
    for (int i = 0; i < 2; i++) {
        resobj->data[i] = obj_ptr->data[i];
    }
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

    vec2_norm(obj_ptr->data, obj_ptr->data);
}

PHP_METHOD(GL_Math_Vec2, normalized)
{
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec_zval,  phpglfw_math_vec2_ce) == FAILURE) {
        return;
    }

    object_init_ex(return_value, phpglfw_math_vec2_ce);
    phpglfw_math_vec2_object *res_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    phpglfw_math_vec2_object *in_obj =  phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));

    vec2_norm(res_ptr->data, in_obj->data);
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
static zend_object_handlers phpglfw_math_vec3_handlers;

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

zval *phpglfw_math_vec3_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Math\\Vec3 object");
	}

    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(object);

    if (Z_TYPE_P(offset) == IS_LONG) {
		size_t index = (size_t)Z_LVAL_P(offset);

        if (index < 3) {
            ZVAL_DOUBLE(rv, obj_ptr->data[index]);
        } else {
            ZVAL_NULL(rv);
        }
	} else {
        zend_throw_error(NULL, "Only a int offset '$vec[int]' can be used with the GL\\Math\\Vec3 object");
		ZVAL_NULL(rv);
	}

	return rv;
}

void phpglfw_math_vec3_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_DOUBLE) {
        zend_throw_error(NULL, "Trying to store non float value in a Vec3.");
        return;
    }

    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(object);

	if (offset == NULL) {
        zend_throw_error(NULL, "You cannot append values into a Vec3.");
	} 
    else {
        if (Z_TYPE_P(offset) == IS_LONG) {
            size_t index = (size_t)Z_LVAL_P(offset);

            if (index >= 3) {
                zend_throw_error(NULL, "Vec3 has a fixed space, the given index [%d] is out of bounds...",  (int) index);
            }
            obj_ptr->data[index] = Z_DVAL_P(value);
        } else {
            zend_throw_error(NULL, "Only a int offset '$vec[int]' can be used with the GL\\Math\\Vec3 object");
        }
    }
}

/**
 * Vector (Vec3) Property READ / WRITE
 * 
 * ----------------------------------------------------------------------------
 */
static zval *phpglfw_math_vec3_read_prop_handler(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) 
{
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(object);

	if ((type != BP_VAR_R && type != BP_VAR_IS)) {
		zend_throw_error(NULL, "GL\\Math\\Vec3"  " properties are virtual and cannot be referenced.");
		rv = &EG( uninitialized_zval );
	} else {

        if (zend_string_equals_literal(member, "x")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "y")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[1]);
        }
        else if (zend_string_equals_literal(member, "z")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[2]);
        }
        else if (zend_string_equals_literal(member, "r")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "g")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[1]);
        }
        else if (zend_string_equals_literal(member, "b")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[2]);
        }
        else {
            ZVAL_NULL(rv);
        }
	}

	return rv;
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


/**
 * Vector (Vec3) Operation Handler
 * 
 * ----------------------------------------------------------------------------
 */
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

/**
 * Vector operation handler
 */
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

    for (int i = 0; i < 3; i++) {
        glfw_smart_str_append_double(&my_str, obj_ptr->data[i], 4, true);
        if (i < 3 - 1) {
            smart_str_appends(&my_str, ", ");
        }
    }
    smart_str_appends(&my_str, ")");
    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}


/**
 * Vector (Vec3) specific methods
 * 
 * ----------------------------------------------------------------------------
 */
PHP_METHOD(GL_Math_Vec3, copy)
{
    zval *obj;
    obj = getThis();
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec3_ce);
    phpglfw_math_vec3_object *resobj = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    // copy data
    for (int i = 0; i < 3; i++) {
        resobj->data[i] = obj_ptr->data[i];
    }
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

    vec3_norm(obj_ptr->data, obj_ptr->data);
}

PHP_METHOD(GL_Math_Vec3, normalized)
{
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec_zval,  phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }

    object_init_ex(return_value, phpglfw_math_vec3_ce);
    phpglfw_math_vec3_object *res_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    phpglfw_math_vec3_object *in_obj =  phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));

    vec3_norm(res_ptr->data, in_obj->data);
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

PHP_METHOD(GL_Math_Vec3, cross)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_vec3_object *leftvec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec3_object *rightvec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(rightvec_zval));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec3_ce);
    phpglfw_math_vec3_object *resobj = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    vec3_mul_cross(resobj->data, leftvec_ptr->data, rightvec_ptr->data);
}


/**
 * GL\Math\Vec4 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_math_vec4_handlers;

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

zval *phpglfw_math_vec4_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Math\\Vec4 object");
	}

    phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(object);

    if (Z_TYPE_P(offset) == IS_LONG) {
		size_t index = (size_t)Z_LVAL_P(offset);

        if (index < 4) {
            ZVAL_DOUBLE(rv, obj_ptr->data[index]);
        } else {
            ZVAL_NULL(rv);
        }
	} else {
        zend_throw_error(NULL, "Only a int offset '$vec[int]' can be used with the GL\\Math\\Vec4 object");
		ZVAL_NULL(rv);
	}

	return rv;
}

void phpglfw_math_vec4_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_DOUBLE) {
        zend_throw_error(NULL, "Trying to store non float value in a Vec4.");
        return;
    }

    phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(object);

	if (offset == NULL) {
        zend_throw_error(NULL, "You cannot append values into a Vec4.");
	} 
    else {
        if (Z_TYPE_P(offset) == IS_LONG) {
            size_t index = (size_t)Z_LVAL_P(offset);

            if (index >= 4) {
                zend_throw_error(NULL, "Vec4 has a fixed space, the given index [%d] is out of bounds...",  (int) index);
            }
            obj_ptr->data[index] = Z_DVAL_P(value);
        } else {
            zend_throw_error(NULL, "Only a int offset '$vec[int]' can be used with the GL\\Math\\Vec4 object");
        }
    }
}

/**
 * Vector (Vec4) Property READ / WRITE
 * 
 * ----------------------------------------------------------------------------
 */
static zval *phpglfw_math_vec4_read_prop_handler(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) 
{
    phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(object);

	if ((type != BP_VAR_R && type != BP_VAR_IS)) {
		zend_throw_error(NULL, "GL\\Math\\Vec4"  " properties are virtual and cannot be referenced.");
		rv = &EG( uninitialized_zval );
	} else {

        if (zend_string_equals_literal(member, "x")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "y")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[1]);
        }
        else if (zend_string_equals_literal(member, "z")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[2]);
        }
        else if (zend_string_equals_literal(member, "w")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[3]);
        }
        else if (zend_string_equals_literal(member, "r")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "g")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[1]);
        }
        else if (zend_string_equals_literal(member, "b")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[2]);
        }
        else if (zend_string_equals_literal(member, "a")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[3]);
        }
        else {
            ZVAL_NULL(rv);
        }
	}

	return rv;
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


/**
 * Vector (Vec4) Operation Handler
 * 
 * ----------------------------------------------------------------------------
 */
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

/**
 * Vector operation handler
 */
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
    smart_str_appends(&my_str, "vec4(");

    for (int i = 0; i < 4; i++) {
        glfw_smart_str_append_double(&my_str, obj_ptr->data[i], 4, true);
        if (i < 4 - 1) {
            smart_str_appends(&my_str, ", ");
        }
    }
    smart_str_appends(&my_str, ")");
    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}


/**
 * Vector (Vec4) specific methods
 * 
 * ----------------------------------------------------------------------------
 */
PHP_METHOD(GL_Math_Vec4, copy)
{
    zval *obj;
    obj = getThis();
    phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec4_ce);
    phpglfw_math_vec4_object *resobj = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    // copy data
    for (int i = 0; i < 4; i++) {
        resobj->data[i] = obj_ptr->data[i];
    }
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

    vec4_norm(obj_ptr->data, obj_ptr->data);
}

PHP_METHOD(GL_Math_Vec4, normalized)
{
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec_zval,  phpglfw_math_vec4_ce) == FAILURE) {
        return;
    }

    object_init_ex(return_value, phpglfw_math_vec4_ce);
    phpglfw_math_vec4_object *res_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    phpglfw_math_vec4_object *in_obj =  phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));

    vec4_norm(res_ptr->data, in_obj->data);
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



/**
 * GL\Math\Quat 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_math_quat_handlers;

/**
 * Creation (GL\Math\Quat)
 */
zend_object *phpglfw_math_quat_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_math_quat_object) + zend_object_properties_size(class_type);
    phpglfw_math_quat_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);


    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_math_quat_handlers;

    return &intern->std;
}

static HashTable *phpglfw_math_quat_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(4);
    *is_temp = 1;

    ZVAL_DOUBLE(&zv, obj_ptr->data[0]);
    zend_hash_str_update(ht, "w", sizeof("w") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[1]);
    zend_hash_str_update(ht, "x", sizeof("x") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[2]);
    zend_hash_str_update(ht, "y", sizeof("y") - 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[3]);
    zend_hash_str_update(ht, "z", sizeof("z") - 1, &zv);

    return ht;
}

zval *phpglfw_math_quat_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Math\\Quat object");
	}

    phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(object);

    if (Z_TYPE_P(offset) == IS_LONG) {
		size_t index = (size_t)Z_LVAL_P(offset);

        if (index < 4) {
            ZVAL_DOUBLE(rv, obj_ptr->data[index]);
        } else {
            ZVAL_NULL(rv);
        }
	} else {
        zend_throw_error(NULL, "Only a int offset '$vec[int]' can be used with the GL\\Math\\Quat object");
		ZVAL_NULL(rv);
	}

	return rv;
}

void phpglfw_math_quat_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_DOUBLE) {
        zend_throw_error(NULL, "Trying to store non float value in a Quat.");
        return;
    }

    phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(object);

	if (offset == NULL) {
        zend_throw_error(NULL, "You cannot append values into a Quat.");
	} 
    else {
        if (Z_TYPE_P(offset) == IS_LONG) {
            size_t index = (size_t)Z_LVAL_P(offset);

            if (index >= 4) {
                zend_throw_error(NULL, "Quat has a fixed space, the given index [%d] is out of bounds...",  (int) index);
            }
            obj_ptr->data[index] = Z_DVAL_P(value);
        } else {
            zend_throw_error(NULL, "Only a int offset '$vec[int]' can be used with the GL\\Math\\Quat object");
        }
    }
}

/**
 * Quaternion Property READ / WRITE
 * 
 * ----------------------------------------------------------------------------
 */
static zval *phpglfw_math_quat_read_prop_handler(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) 
{
    phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(object);

	if ((type != BP_VAR_R && type != BP_VAR_IS)) {
		zend_throw_error(NULL, "GL\\Math\\Quat"  " properties are virtual and cannot be referenced.");
		rv = &EG( uninitialized_zval );
	} else {

        if (zend_string_equals_literal(member, "w")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[0]);
        }
        else if (zend_string_equals_literal(member, "x")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[1]);
        }
        else if (zend_string_equals_literal(member, "y")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[2]);
        }
        else if (zend_string_equals_literal(member, "z")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[3]);
        }
        else {
            ZVAL_NULL(rv);
        }
	}

	return rv;
}

static zval *phpglfw_math_quat_write_prop_handler(zend_object *object, zend_string *member, zval *value, void **cache_slot) 
{
    if (Z_TYPE_P(value) == IS_LONG) {
        convert_to_double(value);
    }
    
    if (Z_TYPE_P(value) != IS_DOUBLE) {
		zend_throw_error(NULL, "GL\\Math\\Quat" " properties can only be of type 'float'.");
        return value;
    }
    else {
        phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(object);

        if (zend_string_equals_literal(member, "w")) {
		    obj_ptr->data[0] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "x")) {
		    obj_ptr->data[1] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "y")) {
		    obj_ptr->data[2] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "z")) {
		    obj_ptr->data[3] = Z_DVAL_P(value); 
        }
        else {
		    zend_throw_error(NULL, "GL\\Math\\Quat" " trying to write into a invalid property.");
        }
    }

	return value;
}



/**
 * Quat Operation Handler
 * 
 * ----------------------------------------------------------------------------
 */
static int phpglfw_math_quat_do_op_handler(zend_uchar opcode, zval *result, zval *op1, zval *op2)
{
    object_init_ex(result, phpglfw_math_quat_ce);
    phpglfw_math_quat_object *resobj = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(result));

    // if left and right are both quat...
    if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == phpglfw_math_quat_ce &&
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == phpglfw_math_quat_ce    ) {
        phpglfw_math_quat_object *quatobj1 = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(op1));
        phpglfw_math_quat_object *quatobj2 = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(op2));

        switch (opcode) {
        case ZEND_ADD:
            quat_add(resobj->data, quatobj1->data, quatobj2->data);
            return SUCCESS;
        case ZEND_SUB:
            quat_sub(resobj->data, quatobj1->data, quatobj2->data);
            return SUCCESS;
        case ZEND_MUL:
            quat_mul(resobj->data, quatobj1->data, quatobj2->data);
            return SUCCESS;
        default:
            return FAILURE;
        }
    }
    // left is quat, right is scalar
    else if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == phpglfw_math_quat_ce &&
        (Z_TYPE_P(op2) == IS_LONG || Z_TYPE_P(op2) == IS_DOUBLE)
    ) {
        phpglfw_math_quat_object *quatobj1 = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(op1));

        // get scalar value
        if (Z_TYPE_P(op2) == IS_LONG) {
            convert_to_double(op2);
        }

        switch (opcode) {
        case ZEND_MUL:
            quat_mul_scalar(resobj->data, quatobj1->data, Z_DVAL_P(op2));
            return SUCCESS;
        case ZEND_DIV:
            quat_div_scalar(resobj->data, quatobj1->data, Z_DVAL_P(op2));
            return SUCCESS;
        default:
            return FAILURE;
        }
    }
    return FAILURE;
}


PHP_METHOD(GL_Math_Quat, __construct)
{
    zval *obj;
    obj = getThis();
    phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    double wval = 1.0f;
    double xval = 0.0f;
    double yval = 0.0f;
    double zval = 0.0f;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|dddd", &wval, &xval, &yval, &zval) == FAILURE) {
        return;
    }

    if (ZEND_NUM_ARGS() == 0) {
        obj_ptr->data[0] = 1.0f;
        obj_ptr->data[1] = 0.0f;
        obj_ptr->data[2] = 0.0f;
        obj_ptr->data[3] = 0.0f;
        return;
    }

    obj_ptr->data[0] = wval;
    obj_ptr->data[1] = xval;
    obj_ptr->data[2] = yval;
    obj_ptr->data[3] = zval;
}

PHP_METHOD(GL_Math_Quat, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};
    smart_str_appends(&my_str, "quat(");

    smart_str_appends(&my_str, "w: ");
    glfw_smart_str_append_double(&my_str, obj_ptr->data[0], 4, true);
    smart_str_appends(&my_str, ", x: ");
    glfw_smart_str_append_double(&my_str, obj_ptr->data[1], 4, true);
    smart_str_appends(&my_str, ", y: ");
    glfw_smart_str_append_double(&my_str, obj_ptr->data[2], 4, true);
    smart_str_appends(&my_str, ", z: ");
    glfw_smart_str_append_double(&my_str, obj_ptr->data[3], 4, true);
    smart_str_appends(&my_str, ")");
    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}


/**
 * Quaternion specific methods
 * 
 * ----------------------------------------------------------------------------
 */
PHP_METHOD(GL_Math_Quat, copy)
{
    zval *obj;
    obj = getThis();
    phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    // create new quat
    object_init_ex(return_value, phpglfw_math_quat_ce);
    phpglfw_math_quat_object *res_ptr = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    for(int i = 0; i < 4; i++) {
        res_ptr->data[i] = obj_ptr->data[i];
    }
}

PHP_METHOD(GL_Math_Quat, fromMat4)
{
    zval *mat_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &mat_zval, phpglfw_math_mat4_ce) == FAILURE) {
        return;
    }

    // create new quat
    object_init_ex(return_value, phpglfw_math_quat_ce);
    phpglfw_math_quat_object *res_ptr = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    phpglfw_math_mat4_object *mat_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(mat_zval));
    quat_from_mat4x4(res_ptr->data, mat_ptr->data);
}

PHP_METHOD(GL_Math_Quat, normalize)
{
    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_THROWS();
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    quat_norm(obj_ptr->data, obj_ptr->data);
}

PHP_METHOD(GL_Math_Quat, normalized)
{
    zval *quat_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &quat_zval,  phpglfw_math_quat_ce) == FAILURE) {
        return;
    }

    object_init_ex(return_value, phpglfw_math_quat_ce);
    phpglfw_math_quat_object *res_ptr = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    phpglfw_math_quat_object *in_obj =  phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(quat_zval));

    quat_norm(res_ptr->data, in_obj->data);
}

PHP_METHOD(GL_Math_Quat, length)
{
    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_THROWS();
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_DOUBLE(quat_len(obj_ptr->data));
}

PHP_METHOD(GL_Math_Quat, eulerAngles)
{
    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_THROWS();
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // construct a new Vec3 object to be returned
    object_init_ex(return_value, phpglfw_math_vec3_ce);
    phpglfw_math_vec3_object *vec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    quat_euler_angles(vec_ptr->data, obj_ptr->data);
}

PHP_METHOD(GL_Math_Quat, rotate)
{
    double radians;
    zval *axis_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dO", &radians, &axis_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    phpglfw_math_vec3_object *axis_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(axis_zval));

    quat temp;
    temp[0] = obj_ptr->data[0];
    temp[1] = obj_ptr->data[1];
    temp[2] = obj_ptr->data[2];
    temp[3] = obj_ptr->data[3];
    quat_rotate_by(obj_ptr->data, temp, radians, axis_ptr->data);
    //quat_rotate(obj_ptr->data, radians, axis_ptr->data);
}

PHP_METHOD(GL_Math_Quat, mat4)
{
    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_THROWS();
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_quat_object *obj_ptr = phpglfw_math_quat_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // construct a new Mat4 object to be returned
    object_init_ex(return_value, phpglfw_math_mat4_ce);
    phpglfw_math_mat4_object *mat_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    mat4x4_from_quat(mat_ptr->data, obj_ptr->data);
}


/**
 * GL\Math\Mat4 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers phpglfw_math_mat4_handlers;

/**
 * Creation (GL\Math\Mat4)
 */
zend_object *phpglfw_math_mat4_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_math_mat4_object) + zend_object_properties_size(class_type);
    phpglfw_math_mat4_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    mat4x4_identity(intern->data);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_math_mat4_handlers;

    return &intern->std;
}

static HashTable *phpglfw_math_mat4_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(16);
    *is_temp = 1;

    ZVAL_DOUBLE(&zv, obj_ptr->data[0][0]);
    zend_hash_index_update(ht, 0, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[0][1]);
    zend_hash_index_update(ht, 1, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[0][2]);
    zend_hash_index_update(ht, 2, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[0][3]);
    zend_hash_index_update(ht, 3, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[1][0]);
    zend_hash_index_update(ht, 4, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[1][1]);
    zend_hash_index_update(ht, 5, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[1][2]);
    zend_hash_index_update(ht, 6, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[1][3]);
    zend_hash_index_update(ht, 7, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[2][0]);
    zend_hash_index_update(ht, 8, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[2][1]);
    zend_hash_index_update(ht, 9, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[2][2]);
    zend_hash_index_update(ht, 10, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[2][3]);
    zend_hash_index_update(ht, 11, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[3][0]);
    zend_hash_index_update(ht, 12, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[3][1]);
    zend_hash_index_update(ht, 13, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[3][2]);
    zend_hash_index_update(ht, 14, &zv);
    ZVAL_DOUBLE(&zv, obj_ptr->data[3][3]);
    zend_hash_index_update(ht, 15, &zv);

    return ht;
}

zval *phpglfw_math_mat4_array_get_handler(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Math\\Mat4 object");
	}

    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(object);

    if (Z_TYPE_P(offset) == IS_LONG) {
		size_t index = (size_t)Z_LVAL_P(offset);

        if (index < 16) {
            ZVAL_DOUBLE(rv, obj_ptr->data[index / 4][index % 4]);
        } else {
            ZVAL_NULL(rv);
        }
	} else {
        zend_throw_error(NULL, "Only a int offset '$vec[int]' can be used with the GL\\Math\\Mat4 object");
		ZVAL_NULL(rv);
	}

	return rv;
}

void phpglfw_math_mat4_array_set_handler(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_DOUBLE) {
        zend_throw_error(NULL, "Trying to store non float value in a Mat4.");
        return;
    }

    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(object);

	if (offset == NULL) {
        zend_throw_error(NULL, "You cannot append values into a Mat4.");
	} 
    else {
        if (Z_TYPE_P(offset) == IS_LONG) {
            size_t index = (size_t)Z_LVAL_P(offset);

            if (index >= 16) {
                zend_throw_error(NULL, "Mat4 has a fixed space, the given index [%d] is out of bounds...",  (int) index);
            }
            obj_ptr->data[index / 4][index % 4] = Z_DVAL_P(value);
        } else {
            zend_throw_error(NULL, "Only a int offset '$vec[int]' can be used with the GL\\Math\\Mat4 object");
        }
    }
}



/**
 * Matrix Operation Handler
 * 
 * ----------------------------------------------------------------------------
 */
static int phpglfw_math_mat4_do_op_ex_handler(zend_uchar opcode, zval *result, zval *op1, zval *op2)
{
    object_init_ex(result, phpglfw_math_mat4_ce);
    phpglfw_math_mat4_object *resobj = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(result));

    // if left and right are both mat...
    if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == phpglfw_math_mat4_ce &&
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == phpglfw_math_mat4_ce    ) {
        phpglfw_math_mat4_object *matobj1 = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(op1));
        phpglfw_math_mat4_object *matobj2 = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(op2));

        //php_printf("[%p](%f %f [%p] [%i]) * (%f %f [%p] [%i])\n", 
        //    result, matobj1->data[0][0], matobj1->data[0][1], op1, op1->u2.constant_flags,
        //    matobj2->data[0][0], matobj2->data[0][1], op2, op2->u2.constant_flags
        //);

        switch (opcode) {
        case ZEND_ADD:
            mat4x4_add(resobj->data, matobj1->data, matobj2->data);
            return SUCCESS;
        case ZEND_SUB:
            mat4x4_sub(resobj->data, matobj1->data, matobj2->data);
            return SUCCESS;
        case ZEND_MUL:
            mat4x4_mul(resobj->data, matobj1->data, matobj2->data);
            return SUCCESS;
        default:
            return FAILURE;
        }
    }
    else {
        return FAILURE;
    }
}
static int phpglfw_math_mat4_do_op_handler(zend_uchar opcode, zval *result, zval *op1, zval *op2)
{
    zval op1_copy;
    int retval;

    if (result == op1) {
        ZVAL_COPY_VALUE(&op1_copy, op1);
        op1 = &op1_copy;
    }

    retval = phpglfw_math_mat4_do_op_ex_handler(opcode, result, op1, op2);

    if (retval == SUCCESS && op1 == &op1_copy) {
        zval_ptr_dtor(op1);
    }

    return retval;
}


PHP_METHOD(GL_Math_Mat4, __construct)
{
    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));

}

PHP_METHOD(GL_Math_Mat4, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};
    smart_str_appends(&my_str, "mat4(");

    smart_str_appends(&my_str, "\n");
    for (int i = 0; i < 4; i++) {
        smart_str_appends(&my_str, "    ");
        for(int y = 0; y < 4; y++) {
            glfw_smart_str_append_double(&my_str, obj_ptr->data[i][y], 4, true);
            if (y < 3) {
                smart_str_appends(&my_str, ", ");
            } else {
                smart_str_appends(&my_str, "\n");
            }
        }
    }
    smart_str_appends(&my_str, ")");
    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}


/**
 * Matrix specific methods
 * 
 * ----------------------------------------------------------------------------
 */
PHP_METHOD(GL_Math_Mat4, fromArray)
{
    HashTable *initaldata = NULL;
    zval *data;
	zend_ulong num_key;
	zend_string *str_key;
    
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "h", &initaldata) == FAILURE) {
        return;
    }
    else if (zend_hash_num_elements(initaldata) != 16) {
        zend_throw_error(NULL, "When constructing a matrix from an array, the array must have 16 elements");
        return;
    }

    object_init_ex(return_value, phpglfw_math_mat4_ce);
    phpglfw_math_mat4_object *resobj = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    ZEND_HASH_FOREACH_KEY_VAL(initaldata, num_key, str_key, data)
    {
        if (num_key < 0 || num_key > 15) {
            zend_throw_error(NULL, "When constructing a matrix from an array, the array keys must be integers between 0 and 15");
            return;
        }

        if (Z_TYPE_P(data) == IS_DOUBLE) {
            resobj->data[num_key / 4][num_key % 4] = Z_DVAL_P(data);
        }  else {
            zend_throw_error(NULL, "When constructing a matrix from an array, the array must contain only doubles");
            return;
        }
    } ZEND_HASH_FOREACH_END();
}

PHP_METHOD(GL_Math_Mat4, row)
{
    zend_long row_index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &row_index) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec4_ce);
    phpglfw_math_vec4_object *resobj = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    for(int i = 0; i < 4; i++) {
        resobj->data[i] = obj_ptr->data[row_index][i];
    }
}

PHP_METHOD(GL_Math_Mat4, col)
{
    zend_long col_index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &col_index) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec4_ce);
    phpglfw_math_vec4_object *resobj = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    for(int i = 0; i < 4; i++) {
        resobj->data[i] = obj_ptr->data[i][col_index];
    }
}

PHP_METHOD(GL_Math_Mat4, setRow)
{
    zend_long row_index;
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &row_index, &vec_zval, phpglfw_math_vec4_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec4_object *vec_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));

    for(int i = 0; i < 4; i++) {
        obj_ptr->data[row_index][i] = vec_ptr->data[i];
    }
}

PHP_METHOD(GL_Math_Mat4, setCol)
{
    zend_long col_index;
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &col_index, &vec_zval, phpglfw_math_vec4_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec4_object *vec_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));

    for(int i = 0; i < 4; i++) {
        obj_ptr->data[i][col_index] = vec_ptr->data[i];
    }
}

PHP_METHOD(GL_Math_Mat4, perspective)
{
    // prefix with gl_ because windows has one of those
    // globally defined as a macro. It took my hours to figure this out 
    // because all i got was "syntax error ','"... -.-
    double gl_fov;
    double gl_aspect;
    double gl_near;
    double gl_far;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "dddd", &gl_fov, &gl_aspect, &gl_near, &gl_far) == FAILURE) {
        RETURN_THROWS();
    }
    
    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    mat4x4_perspective(obj_ptr->data, gl_fov, gl_aspect, gl_near, gl_far);
}


PHP_METHOD(GL_Math_Mat4, ortho)
{
    double gl_left;
    double gl_right;
    double gl_bottom;
    double gl_top;
    double gl_near;
    double gl_far;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dddddd", &gl_left, &gl_right, &gl_bottom, &gl_top, &gl_near, &gl_far) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    mat4x4_ortho(obj_ptr->data, gl_left, gl_right, gl_bottom, gl_top, gl_near, gl_far);
}

PHP_METHOD(GL_Math_Mat4, lookAt)
{
    zval *eye_zval;
    zval *center_zval;
    zval *up_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "OOO", &eye_zval, phpglfw_math_vec3_ce, &center_zval, phpglfw_math_vec3_ce, &up_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec3_object *eye_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(eye_zval));
    phpglfw_math_vec3_object *center_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(center_zval));
    phpglfw_math_vec3_object *up_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(up_zval));

    mat4x4_look_at(obj_ptr->data, eye_ptr->data, center_ptr->data, up_ptr->data);
}

PHP_METHOD(GL_Math_Mat4, transpose)
{
    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    mat4x4 T;
    mat4x4_transpose(T, obj_ptr->data);
    mat4x4_dup(obj_ptr->data, T);
}

PHP_METHOD(GL_Math_Mat4, inverse)
{
    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    mat4x4 T;
    mat4x4_invert(T, obj_ptr->data);
    mat4x4_dup(obj_ptr->data, T);
}

PHP_METHOD(GL_Math_Mat4, translate) {
    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }
    phpglfw_math_vec3_object *vec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));
    mat4x4_translate_in_place(obj_ptr->data, vec_ptr->data[0], vec_ptr->data[1], vec_ptr->data[2]);
}

PHP_METHOD(GL_Math_Mat4, scale)
{
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));
    phpglfw_math_vec3_object *vec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));

    mat4x4_scale_aniso(obj_ptr->data, obj_ptr->data, vec_ptr->data[0], vec_ptr->data[1], vec_ptr->data[2]);
}


PHP_METHOD(GL_Math_Mat4, rotate)
{
    double radians;
    zval *axis_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dO", &radians, &axis_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    phpglfw_math_vec3_object *axis_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(axis_zval));
    mat4x4_rotate(obj_ptr->data, obj_ptr->data, axis_ptr->data[0], axis_ptr->data[1], axis_ptr->data[2], radians);
}

PHP_METHOD(GL_Math_Mat4, copy)
{
    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));
    
    // create new mat4
    object_init_ex(return_value, phpglfw_math_mat4_ce);
    phpglfw_math_mat4_object *res_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            res_ptr->data[i][j] = obj_ptr->data[i][j];
        }
    }
}

PHP_METHOD(GL_Math_Mat4, determinant)
{
    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_THROWS();
    }

    zval *obj;
    obj = getThis();
    phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_DOUBLE(mat4x4_det(obj_ptr->data));
}



/**
 * GLM static functions 
 * This class holds a collection of common funtions, constructors and
 * alternative copy based math functions.
 */

PHP_METHOD(GL_Math_GLM, radians)
{
    double angle;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &angle) == FAILURE) {
        RETURN_THROWS();
    }
    RETURN_DOUBLE(angle * M_PI / 180.0);
}

PHP_METHOD(GL_Math_GLM, angle)
{
    double radians;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &radians) == FAILURE) {
        RETURN_THROWS();
    }
    RETURN_DOUBLE(radians * 180.0 / M_PI);
}

PHP_METHOD(GL_Math_GLM, triangleNormal)
{
    zval *v0_zval, *v1_zval, *v2_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "OOO", &v0_zval, phpglfw_math_vec3_ce, &v1_zval, phpglfw_math_vec3_ce, &v2_zval, phpglfw_math_vec3_ce) == FAILURE) {
        RETURN_THROWS();
    }
    phpglfw_math_vec3_object *v0_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(v0_zval));
    phpglfw_math_vec3_object *v1_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(v1_zval));
    phpglfw_math_vec3_object *v2_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(v2_zval));

    // calc normal from v0, v1, v2
    vec3 dir, t1, t2;
    vec3_sub(t1, v1_ptr->data, v0_ptr->data);
    vec3_sub(t2, v2_ptr->data, v0_ptr->data);
    vec3_mul_cross(dir, t1, t2);
    vec3_s_div(dir, dir, vec3_len(dir));
    vec3_norm(dir, dir);

    // create new vec3
    object_init_ex(return_value, phpglfw_math_vec3_ce);
    phpglfw_math_vec3_object *res_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    res_ptr->data[0] = dir[0];
    res_ptr->data[1] = dir[1];
    res_ptr->data[2] = dir[2];
}

PHP_METHOD(GL_Math_GLM, normalize)
{
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "o", &vec_zval) == SUCCESS) {
        if (instanceof_function(Z_OBJCE_P(vec_zval), phpglfw_math_vec4_ce)) {
            object_init_ex(return_value, phpglfw_math_vec4_ce);
            phpglfw_math_vec4_object *return_obj = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));
            phpglfw_math_vec4_object *in_obj = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));
            vec4_norm(return_obj->data, in_obj->data);
        } 
        else if (instanceof_function(Z_OBJCE_P(vec_zval), phpglfw_math_vec3_ce)) {
            object_init_ex(return_value, phpglfw_math_vec3_ce);
            phpglfw_math_vec3_object *return_obj = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));
            phpglfw_math_vec3_object *in_obj = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));
            vec3_norm(return_obj->data, in_obj->data);
        } 
        else if (instanceof_function(Z_OBJCE_P(vec_zval), phpglfw_math_vec2_ce)) {
            object_init_ex(return_value, phpglfw_math_vec2_ce);
            phpglfw_math_vec2_object *return_obj = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(return_value));
            phpglfw_math_vec2_object *in_obj = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));
            vec2_norm(return_obj->data, in_obj->data);
        } 
        else {
            zend_throw_error(NULL, "Invalid argument type, expected Vec4, Vec3 or Vec2, got %s", ZSTR_VAL(Z_OBJCE_P(vec_zval)->name));
        }
    } else {
        RETURN_THROWS();
    }
}


void phpglfw_register_math_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;

    INIT_CLASS_ENTRY(tmp_ce, "GL\\Math\\GLM", class_GL_Math_GLM_methods);
    phpglfw_glm_ce = zend_register_internal_class(&tmp_ce);

 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Math\\Vec2", class_GL_Math_Vec2_methods);
    phpglfw_math_vec2_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_math_vec2_ce->create_object = phpglfw_math_vec2_create_handler;

    memcpy(&phpglfw_math_vec2_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_math_vec2_handlers));
    phpglfw_math_vec2_handlers.get_debug_info = phpglfw_math_vec2_debug_info_handler;
    phpglfw_math_vec2_handlers.read_dimension = phpglfw_math_vec2_array_get_handler;
    phpglfw_math_vec2_handlers.write_dimension = phpglfw_math_vec2_array_set_handler;

    phpglfw_math_vec2_handlers.read_property = phpglfw_math_vec2_read_prop_handler;
    phpglfw_math_vec2_handlers.write_property = phpglfw_math_vec2_write_prop_handler;
    phpglfw_math_vec2_handlers.do_operation = phpglfw_math_vec2_do_op_handler;
    phpglfw_math_vec2_handlers.offset = XtOffsetOf(phpglfw_math_vec2_object, std);
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Math\\Vec3", class_GL_Math_Vec3_methods);
    phpglfw_math_vec3_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_math_vec3_ce->create_object = phpglfw_math_vec3_create_handler;

    memcpy(&phpglfw_math_vec3_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_math_vec3_handlers));
    phpglfw_math_vec3_handlers.get_debug_info = phpglfw_math_vec3_debug_info_handler;
    phpglfw_math_vec3_handlers.read_dimension = phpglfw_math_vec3_array_get_handler;
    phpglfw_math_vec3_handlers.write_dimension = phpglfw_math_vec3_array_set_handler;

    phpglfw_math_vec3_handlers.read_property = phpglfw_math_vec3_read_prop_handler;
    phpglfw_math_vec3_handlers.write_property = phpglfw_math_vec3_write_prop_handler;
    phpglfw_math_vec3_handlers.do_operation = phpglfw_math_vec3_do_op_handler;
    phpglfw_math_vec3_handlers.offset = XtOffsetOf(phpglfw_math_vec3_object, std);
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Math\\Vec4", class_GL_Math_Vec4_methods);
    phpglfw_math_vec4_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_math_vec4_ce->create_object = phpglfw_math_vec4_create_handler;

    memcpy(&phpglfw_math_vec4_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_math_vec4_handlers));
    phpglfw_math_vec4_handlers.get_debug_info = phpglfw_math_vec4_debug_info_handler;
    phpglfw_math_vec4_handlers.read_dimension = phpglfw_math_vec4_array_get_handler;
    phpglfw_math_vec4_handlers.write_dimension = phpglfw_math_vec4_array_set_handler;

    phpglfw_math_vec4_handlers.read_property = phpglfw_math_vec4_read_prop_handler;
    phpglfw_math_vec4_handlers.write_property = phpglfw_math_vec4_write_prop_handler;
    phpglfw_math_vec4_handlers.do_operation = phpglfw_math_vec4_do_op_handler;
    phpglfw_math_vec4_handlers.offset = XtOffsetOf(phpglfw_math_vec4_object, std);
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Math\\Quat", class_GL_Math_Quat_methods);
    phpglfw_math_quat_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_math_quat_ce->create_object = phpglfw_math_quat_create_handler;

    memcpy(&phpglfw_math_quat_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_math_quat_handlers));
    phpglfw_math_quat_handlers.get_debug_info = phpglfw_math_quat_debug_info_handler;
    phpglfw_math_quat_handlers.read_dimension = phpglfw_math_quat_array_get_handler;
    phpglfw_math_quat_handlers.write_dimension = phpglfw_math_quat_array_set_handler;

    phpglfw_math_quat_handlers.read_property = phpglfw_math_quat_read_prop_handler;
    phpglfw_math_quat_handlers.write_property = phpglfw_math_quat_write_prop_handler;
    phpglfw_math_quat_handlers.do_operation = phpglfw_math_quat_do_op_handler;
    phpglfw_math_quat_handlers.offset = XtOffsetOf(phpglfw_math_quat_object, std);
 
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Math\\Mat4", class_GL_Math_Mat4_methods);
    phpglfw_math_mat4_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_math_mat4_ce->create_object = phpglfw_math_mat4_create_handler;

    memcpy(&phpglfw_math_mat4_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_math_mat4_handlers));
    phpglfw_math_mat4_handlers.get_debug_info = phpglfw_math_mat4_debug_info_handler;
    phpglfw_math_mat4_handlers.read_dimension = phpglfw_math_mat4_array_get_handler;
    phpglfw_math_mat4_handlers.write_dimension = phpglfw_math_mat4_array_set_handler;

    phpglfw_math_mat4_handlers.do_operation = phpglfw_math_mat4_do_op_handler;
    phpglfw_math_mat4_handlers.offset = XtOffsetOf(phpglfw_math_mat4_object, std);
}