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

zend_class_entry *phpglfw_math_vec3_ce; 

/**
 * PGL\Math\Vec3
 * 
 * ----------------------------------------------------------------------------
 */
typedef struct _phpglfw_math_vec3_object {
    vec3 vec;
    zend_object std;
} phpglfw_math_vec3_object; 

static zend_object_handlers phpglfw_math_vec3_handlers;

static zend_always_inline phpglfw_math_vec3_object* phpglfw_math_vec3_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_math_vec3_object *) ((char *) (obj) - XtOffsetOf(phpglfw_math_vec3_object, std));
}

zend_object *phpglfw_create_math_vec3_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_math_vec3_object) + zend_object_properties_size(class_type);
    phpglfw_math_vec3_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    intern->vec[0] = 0.0f;
    intern->vec[1] = 0.0f;
    intern->vec[2] = 0.0f;

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

    // ZVAL_STRING(&zv, "Aadas");
    ZVAL_DOUBLE(&zv, obj_ptr->vec[0]);
    zend_hash_str_update(ht, "x", sizeof("x") - 1, &zv);

    ZVAL_DOUBLE(&zv, obj_ptr->vec[1]);
    zend_hash_str_update(ht, "y", sizeof("y") - 1, &zv);

    ZVAL_DOUBLE(&zv, obj_ptr->vec[2]);
    zend_hash_str_update(ht, "z", sizeof("z") - 1, &zv);

    return ht;
}

static zval *phpglfw_math_vec3_read_prop_handler(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) 
{
    zval *retval;
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(object);

	if ((type != BP_VAR_R && type != BP_VAR_IS)) {
		zend_throw_error(NULL, "PHP-GLFW Math\\Vec3 Properties are virtual and cannot be referenced.");
		retval = &EG( uninitialized_zval );
	} else {

        if (zend_string_equals_literal(member, "x")) {
		    ZVAL_DOUBLE(retval, obj_ptr->vec[0]);
        }
        else if (zend_string_equals_literal(member, "y")) {
		    ZVAL_DOUBLE(retval, obj_ptr->vec[1]);
        }
        else if (zend_string_equals_literal(member, "z")) {
		    ZVAL_DOUBLE(retval, obj_ptr->vec[1]);
        }
        else if (zend_string_equals_literal(member, "r")) {
		    ZVAL_DOUBLE(retval, obj_ptr->vec[0]);
        }
        else if (zend_string_equals_literal(member, "g")) {
		    ZVAL_DOUBLE(retval, obj_ptr->vec[1]);
        }
        else if (zend_string_equals_literal(member, "b")) {
		    ZVAL_DOUBLE(retval, obj_ptr->vec[1]);
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
		zend_throw_error(NULL, "PGL\\Math\\Vec3 properties can only be of type 'float'.");
        return value;
    }
    else {
        phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(object);

        if (zend_string_equals_literal(member, "x")) {
		    obj_ptr->vec[0] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "y")) {
		    obj_ptr->vec[1] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "z")) {
		    obj_ptr->vec[2] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "r")) {
		    obj_ptr->vec[0] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "g")) {
		    obj_ptr->vec[1] = Z_DVAL_P(value); 
        }
        else if (zend_string_equals_literal(member, "b")) {
		    obj_ptr->vec[2] = Z_DVAL_P(value); 
        }
    }

	return value;
}

static zend_always_inline int phpglfw_math_vec3_do_op_handler_vec_scalar(zend_uchar opcode, phpglfw_math_vec3_object *resobj, phpglfw_math_vec3_object *vecobj, zval *mod)
{
    if (Z_TYPE_P(mod) == IS_LONG) {
        convert_to_double(mod);
    }

    switch (opcode) {
    case ZEND_ADD:
        vec3_s_add(resobj->vec, vecobj->vec, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_SUB:
        vec3_s_sub(resobj->vec, vecobj->vec, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_MUL:
        vec3_s_mul(resobj->vec, vecobj->vec, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_DIV:
        vec3_s_div(resobj->vec, vecobj->vec, Z_DVAL_P(mod));
        return SUCCESS;
    default:
        return FAILURE;
    }
}

static int phpglfw_math_vec3_do_op_handler(zend_uchar opcode, zval *result, zval *op1, zval *op2)
{
    object_init_ex(result, phpglfw_math_vec3_ce);
    phpglfw_math_vec3_object *resobj = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(result));

    // if left and right are both vec3...
    if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == phpglfw_math_vec3_ce &&
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == phpglfw_math_vec3_ce
    ) {
        phpglfw_math_vec3_object *vecobj1 = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(op1));
        phpglfw_math_vec3_object *vecobj2 = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(op2));

        switch (opcode) {
        case ZEND_ADD:
            vec3_add(resobj->vec, vecobj1->vec, vecobj2->vec);
            // resobj->vec[0] = vecobj1->vec[0] + vecobj2->vec[0];
            // resobj->vec[1] = vecobj1->vec[1] + vecobj2->vec[1];
            // resobj->vec[2] = vecobj1->vec[2] + vecobj2->vec[2];
            return SUCCESS;
        case ZEND_SUB:
            vec3_sub(resobj->vec, vecobj1->vec, vecobj2->vec);
            return SUCCESS;
        case ZEND_MUL:
            vec3_mul(resobj->vec, vecobj1->vec, vecobj2->vec);
            return SUCCESS;
        case ZEND_DIV:
            vec3_div(resobj->vec, vecobj1->vec, vecobj2->vec);
            return SUCCESS;
        default:
            return FAILURE;
        }
    }
    // if left is a vec 3 and right a scalar number
    else if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == phpglfw_math_vec3_ce &&
        (Z_TYPE_P(op2) == IS_LONG || Z_TYPE_P(op2) == IS_DOUBLE)
    ) {
        phpglfw_math_vec3_object *vecobj1 = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(op1));
        return phpglfw_math_vec3_do_op_handler_vec_scalar(opcode, resobj, vecobj1, op2);
    }
    // otherway around
    else if (
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == phpglfw_math_vec3_ce &&
        (Z_TYPE_P(op1) == IS_LONG || Z_TYPE_P(op1) == IS_DOUBLE)
    ) {
        phpglfw_math_vec3_object *vecobj1 = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(op2));
        return phpglfw_math_vec3_do_op_handler_vec_scalar(opcode, resobj, vecobj1, op1);
    }
    else {
        return FAILURE;
    }
}

PHP_METHOD(PGL_Math_Vec3, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, "vec3(");

    smart_str_append_double(&my_str, obj_ptr->vec[0], 4, true);
    smart_str_appends(&my_str, ", ");
    smart_str_append_double(&my_str, obj_ptr->vec[1], 4, true);
    smart_str_appends(&my_str, ", ");
    smart_str_append_double(&my_str, obj_ptr->vec[2], 4, true);
    smart_str_appends(&my_str, ")");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(PGL_Math_Vec3, length)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(obj));

    RETURN_DOUBLE(vec3_len(obj_ptr->vec));
}

PHP_METHOD(PGL_Math_Vec3, normalize)
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

    // normalize
    vec3_norm(resobj->vec, obj_ptr->vec);
}

PHP_METHOD(PGL_Math_Vec3, abs)
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

    vec3_abs(resobj->vec, obj_ptr->vec);
}

// const zend_function_entry phpglfw_math_vec3_functions[] = {
// 	PHP_ME(Vec3, __toString, NULL, ZEND_ACC_PUBLIC)
//     PHP_FE_END
// };


void phpglfw_register_math_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;
    INIT_CLASS_ENTRY(tmp_ce, "PGL\\Math\\Vec3", class_PGL_Math_Vec3_methods);
    phpglfw_math_vec3_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_math_vec3_ce->create_object = phpglfw_create_math_vec3_handler;

    memcpy(&phpglfw_math_vec3_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_math_vec3_handlers));
    phpglfw_math_vec3_handlers.get_debug_info = phpglfw_math_vec3_debug_info_handler;
    phpglfw_math_vec3_handlers.read_property = phpglfw_math_vec3_read_prop_handler;
    phpglfw_math_vec3_handlers.write_property = phpglfw_math_vec3_write_prop_handler;
    phpglfw_math_vec3_handlers.do_operation = phpglfw_math_vec3_do_op_handler;
    phpglfw_math_vec3_handlers.offset = XtOffsetOf(phpglfw_math_vec3_object, std);
}
