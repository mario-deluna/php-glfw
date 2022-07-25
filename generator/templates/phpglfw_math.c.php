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

<?php foreach($objects as $obj) : ?>
zend_class_entry *<?php echo $obj->getClassEntryName(); ?>; 
<?php endforeach; ?>

<?php foreach($objects as $obj) : ?>
/**
 * <?php echo $obj->getFullNamespaceString(); ?> 
 * 
 * ----------------------------------------------------------------------------
 */
typedef struct _<?php echo $obj->getObjectName(); ?> {
    <?php echo $obj->getInternalDataType(); ?> data;
    zend_object std;
} <?php echo $obj->getObjectName(); ?>; 

static zend_object_handlers <?php echo $obj->getHandlersVarName(); ?>;

zend_always_inline <?php echo $obj->getObjectName(); ?>* <?php echo $obj->objectFromZObjFunctionName(); ?>(zend_object* obj)
{
    return (<?php echo $obj->getObjectName(); ?> *) ((char *) (obj) - XtOffsetOf(<?php echo $obj->getObjectName(); ?>, std));
}

/**
 * Creation (<?php echo $obj->getFullNamespaceString(); ?>)
 */
zend_object *<?php echo $obj->getHandlerMethodName('create'); ?>(zend_class_entry *class_type)
{
    size_t block_len = sizeof(<?php echo $obj->getObjectName(); ?>) + zend_object_properties_size(class_type);
    <?php echo $obj->getObjectName(); ?> *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    for(int i=0; i<<?php echo $obj->size; ?>; i++) {
        intern->data[i] = 0.0f;
    }

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &<?php echo $obj->getHandlersVarName(); ?>;

    return &intern->std;
}

static HashTable *<?php echo $obj->getHandlerMethodName('debug_info'); ?>(zend_object *object, int *is_temp)
{
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(<?php echo $obj->size; ?>);
    *is_temp = 1;

<?php foreach($obj->getPropIt() as $i => $name) : ?>
    ZVAL_DOUBLE(&zv, obj_ptr->data[<?php echo $i; ?>]);
    zend_hash_str_update(ht, "<?php echo $name; ?>", sizeof("<?php echo $name; ?>") - 1, &zv);
<?php endforeach; ?> 

    return ht;
}

static zval *<?php echo $obj->getHandlerMethodName('read_prop'); ?>(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) 
{
    zval *retval;
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(object);

	if ((type != BP_VAR_R && type != BP_VAR_IS)) {
		zend_throw_error(NULL, <?php echo $obj->getFullNamespaceCString(); ?>  " properties are virtual and cannot be referenced.");
		retval = &EG( uninitialized_zval );
	} else {

<?php foreach($obj->getPropIt() as $i => $name) : ?>
        <?php echo ($i !== 0 ? 'else ' : '') ?>if (zend_string_equals_literal(member, "<?php echo $name; ?>")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[<?php echo $i; ?>]);
        }
<?php endforeach; ?>
<?php foreach($obj->getAltPropIt() as $i => $name) : ?>
        else if (zend_string_equals_literal(member, "<?php echo $name; ?>")) {
		    ZVAL_DOUBLE(retval, obj_ptr->data[<?php echo $i; ?>]);
        }
<?php endforeach; ?>
        else {
            ZVAL_NULL(retval);
        }
	}

	return retval;
}

static zval *<?php echo $obj->getHandlerMethodName('write_prop'); ?>(zend_object *object, zend_string *member, zval *value, void **cache_slot) 
{
    if (Z_TYPE_P(value) == IS_LONG) {
        convert_to_double(value);
    }
    
    if (Z_TYPE_P(value) != IS_DOUBLE) {
		zend_throw_error(NULL, <?php echo $obj->getFullNamespaceCString(); ?> " properties can only be of type 'float'.");
        return value;
    }
    else {
        <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(object);

<?php foreach($obj->getPropIt() as $i => $name) : ?>
        <?php echo ($i !== 0 ? 'else ' : '') ?>if (zend_string_equals_literal(member, "<?php echo $name; ?>")) {
		    obj_ptr->data[<?php echo $i; ?>] = Z_DVAL_P(value); 
        }
<?php endforeach; ?>
<?php foreach($obj->getAltPropIt() as $i => $name) : ?>
        else if (zend_string_equals_literal(member, "<?php echo $name; ?>")) {
		    obj_ptr->data[<?php echo $i; ?>] = Z_DVAL_P(value); 
        }
<?php endforeach; ?>
        else {
		    zend_throw_error(NULL, <?php echo $obj->getFullNamespaceCString(); ?> " trying to write into a invalid property.");
        }
    }

	return value;
}

static zend_always_inline int <?php echo $obj->getHandlerMethodName('do_op_scalar'); ?>(zend_uchar opcode, <?php echo $obj->getObjectName(); ?> *resobj, <?php echo $obj->getObjectName(); ?> *vecobj, zval *mod)
{
    if (Z_TYPE_P(mod) == IS_LONG) {
        convert_to_double(mod);
    }

    switch (opcode) {
    case ZEND_ADD:
        <?php echo $obj->getVecFunction('s_add'); ?>(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_SUB:
        <?php echo $obj->getVecFunction('s_sub'); ?>(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_MUL:
        <?php echo $obj->getVecFunction('s_mul'); ?>(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    case ZEND_DIV:
        <?php echo $obj->getVecFunction('s_div'); ?>(resobj->data, vecobj->data, Z_DVAL_P(mod));
        return SUCCESS;
    default:
        return FAILURE;
    }
}

static int <?php echo $obj->getHandlerMethodName('do_op'); ?>(zend_uchar opcode, zval *result, zval *op1, zval *op2)
{
    object_init_ex(result, <?php echo $obj->getClassEntryName(); ?>);
    <?php echo $obj->getObjectName(); ?> *resobj = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(result));

    // if left and right are both vec...
    if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == <?php echo $obj->getClassEntryName(); ?> &&
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == <?php echo $obj->getClassEntryName(); ?>
    ) {
        <?php echo $obj->getObjectName(); ?> *vecobj1 = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(op1));
        <?php echo $obj->getObjectName(); ?> *vecobj2 = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(op2));

        switch (opcode) {
        case ZEND_ADD:
            <?php echo $obj->getVecFunction('add'); ?>(resobj->data, vecobj1->data, vecobj2->data);
            // resobj->vec[0] = vecobj1->vec[0] + vecobj2->vec[0];
            // resobj->vec[1] = vecobj1->vec[1] + vecobj2->vec[1];
            // resobj->vec[2] = vecobj1->vec[2] + vecobj2->vec[2];
            return SUCCESS;
        case ZEND_SUB:
            <?php echo $obj->getVecFunction('sub'); ?>(resobj->data, vecobj1->data, vecobj2->data);
            return SUCCESS;
        case ZEND_MUL:
            <?php echo $obj->getVecFunction('mul'); ?>(resobj->data, vecobj1->data, vecobj2->data);
            return SUCCESS;
        case ZEND_DIV:
            <?php echo $obj->getVecFunction('div'); ?>(resobj->data, vecobj1->data, vecobj2->data);
            return SUCCESS;
        default:
            return FAILURE;
        }
    }
    // if left is a vec and right a scalar number
    else if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == <?php echo $obj->getClassEntryName(); ?> &&
        (Z_TYPE_P(op2) == IS_LONG || Z_TYPE_P(op2) == IS_DOUBLE)
    ) {
        <?php echo $obj->getObjectName(); ?> *vecobj1 = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(op1));
        return <?php echo $obj->getHandlerMethodName('do_op_scalar'); ?>(opcode, resobj, vecobj1, op2);
    }
    // otherway around
    else if (
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == <?php echo $obj->getClassEntryName(); ?> &&
        (Z_TYPE_P(op1) == IS_LONG || Z_TYPE_P(op1) == IS_DOUBLE)
    ) {
        <?php echo $obj->getObjectName(); ?> *vecobj1 = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(op2));
        return <?php echo $obj->getHandlerMethodName('do_op_scalar'); ?>(opcode, resobj, vecobj1, op1);
    }
    else {
        return FAILURE;
    }
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, __construct)
{
    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

<?php echo tabulate($obj->getVectorZendParseParamters()); ?> 
        return;
    }

    if (ZEND_NUM_ARGS() == 0) {
        return;
    }

    // if only one argument is given we initalize all values with it
    else if (ZEND_NUM_ARGS() == 1) {
<?php for($i=0; $i<$obj->size; $i++) : ?>
        obj_ptr->data[<?php echo $i; ?>] = <?php echo $obj->propNameForPos(0); ?>val;
<?php endfor; ?>
        return;
    }

<?php for($i=0; $i<$obj->size; $i++) : ?>
    obj_ptr->data[<?php echo $i; ?>] = <?php echo $obj->propNameForPos($i); ?>val;
<?php endfor; ?>
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

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

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, length)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    RETURN_DOUBLE(<?php echo $obj->getVecFunction('len'); ?>(obj_ptr->data));
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, dot)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, <?php echo $obj->getClassEntryName(); ?>) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *leftvec_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));
    <?php echo $obj->getObjectName(); ?> *rightvec_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(rightvec_zval));

    RETURN_DOUBLE(<?php echo $obj->getVecFunction('mul_inner'); ?>(leftvec_ptr->data, rightvec_ptr->data));
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, distance)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, <?php echo $obj->getClassEntryName(); ?>) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *leftvec_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));
    <?php echo $obj->getObjectName(); ?> *rightvec_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(rightvec_zval));

    RETURN_DOUBLE(sqrt(<?php echo $obj->getVecFunction('distance_square'); ?>(leftvec_ptr->data, rightvec_ptr->data)));
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, distance2)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, <?php echo $obj->getClassEntryName(); ?>) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *leftvec_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));
    <?php echo $obj->getObjectName(); ?> *rightvec_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(rightvec_zval));

    RETURN_DOUBLE(<?php echo $obj->getVecFunction('distance_square'); ?>(leftvec_ptr->data, rightvec_ptr->data));
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, normalize)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, <?php echo $obj->getClassEntryName(); ?>);
    <?php echo $obj->getObjectName(); ?> *resobj = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(return_value));

    <?php echo $obj->getVecFunction('norm'); ?>(resobj->data, obj_ptr->data);
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, abs)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, <?php echo $obj->getClassEntryName(); ?>);
    <?php echo $obj->getObjectName(); ?> *resobj = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(return_value));

    <?php echo $obj->getVecFunction('abs'); ?>(resobj->data, obj_ptr->data);
}

<?php endforeach; ?>

void phpglfw_register_math_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;

<?php foreach($objects as $obj) : ?> 
    INIT_CLASS_ENTRY(tmp_ce, <?php echo $obj->getFullNamespaceCString(); ?>, class_<?php echo $obj->getFullNamespaceConstString(); ?>_methods);
    <?php echo $obj->getClassEntryName(); ?> = zend_register_internal_class(&tmp_ce);
    <?php echo $obj->getClassEntryName(); ?>->create_object = <?php echo $obj->getHandlerMethodName('create'); ?>;

    memcpy(&<?php echo $obj->getHandlersVarName(); ?>, zend_get_std_object_handlers(), sizeof(<?php echo $obj->getHandlersVarName(); ?>));
    <?php echo $obj->getHandlersVarName(); ?>.get_debug_info = <?php echo $obj->getHandlerMethodName('debug_info'); ?>;
    <?php echo $obj->getHandlersVarName(); ?>.read_property = <?php echo $obj->getHandlerMethodName('read_prop'); ?>;
    <?php echo $obj->getHandlersVarName(); ?>.write_property = <?php echo $obj->getHandlerMethodName('write_prop'); ?>;
    <?php echo $obj->getHandlersVarName(); ?>.do_operation = <?php echo $obj->getHandlerMethodName('do_op'); ?>;
    <?php echo $obj->getHandlersVarName(); ?>.offset = XtOffsetOf(<?php echo $obj->getObjectName(); ?>, std);
<?php endforeach; ?>
}
