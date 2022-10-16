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
<?php foreach($objects as $obj) : ?>
zend_class_entry *<?php echo $obj->getClassEntryName(); ?>; 
<?php endforeach; ?>

<?php foreach($objects as $obj) : ?>
zend_class_entry *<?php echo $obj->getClassEntryNameGetter(); ?>() {
    return <?php echo $obj->getClassEntryName(); ?>;
}
<?php endforeach; ?>

<?php foreach($objects as $obj) : ?>
/**
 * <?php echo $obj->getFullNamespaceString(); ?> 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers <?php echo $obj->getHandlersVarName(); ?>;

/**
 * Creation (<?php echo $obj->getFullNamespaceString(); ?>)
 */
zend_object *<?php echo $obj->getHandlerMethodName('create'); ?>(zend_class_entry *class_type)
{
    size_t block_len = sizeof(<?php echo $obj->getObjectName(); ?>) + zend_object_properties_size(class_type);
    <?php echo $obj->getObjectName(); ?> *intern = emalloc(block_len);
    memset(intern, 0, block_len);

<?php if ($obj->isVector()) : ?>
    for(int i=0; i<<?php echo $obj->size; ?>; i++) {
        intern->data[i] = 0.0f;
    }
<?php elseif ($obj->isMatrix()) : ?>
    mat4x4_identity(intern->data);
<?php endif; ?>

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

<?php if ($obj->isVector()) : ?>
<?php foreach($obj->getPropIt() as $i => $name) : ?>
    ZVAL_DOUBLE(&zv, obj_ptr->data[<?php echo $i; ?>]);
    zend_hash_str_update(ht, "<?php echo $name; ?>", sizeof("<?php echo $name; ?>") - 1, &zv);
<?php endforeach; ?> 
<?php elseif ($obj->isMatrix()) : ?>
<?php for($i=0; $i<4; $i++) : ?>
<?php for($y=0; $y<4; $y++) : ?>
    ZVAL_DOUBLE(&zv, obj_ptr->data[<?php echo $i; ?>][<?php echo $y; ?>]);
    zend_hash_index_update(ht, <?php echo ($i * 4) + $y; ?>, &zv);
<?php endfor; ?>
<?php endfor; ?>
<?php endif; ?>

    return ht;
}

zval *<?php echo $obj->getHandlerMethodName('array_get'); ?>(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Math\\<?php echo $obj->name; ?> object");
	}

    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(object);

    if (Z_TYPE_P(offset) == IS_LONG) {
		size_t index = (size_t)Z_LVAL_P(offset);

        if (index < <?php echo $obj->size; ?>) {
<?php if ($obj->isVector()) : ?>
            ZVAL_DOUBLE(rv, obj_ptr->data[index]);
<?php elseif ($obj->isMatrix()) : ?>
            ZVAL_DOUBLE(rv, obj_ptr->data[index / 4][index % 4]);
<?php endif; ?>
        } else {
            ZVAL_NULL(rv);
        }
	} else {
        zend_throw_error(NULL, "Only a int offset '$vec[int]' can be used with the GL\\Math\\<?php echo $obj->name; ?> object");
		ZVAL_NULL(rv);
	}

	return rv;
}

void <?php echo $obj->getHandlerMethodName('array_set'); ?>(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != IS_DOUBLE) {
        zend_throw_error(NULL, "Trying to store non float value in a <?php echo $obj->name; ?>.");
        return;
    }

    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(object);

	if (offset == NULL) {
        zend_throw_error(NULL, "You cannot append values into a <?php echo $obj->name; ?>.");
	} 
    else {
        if (Z_TYPE_P(offset) == IS_LONG) {
            size_t index = (size_t)Z_LVAL_P(offset);

            if (index >= <?php echo $obj->size; ?>) {
                zend_throw_error(NULL, "<?php echo $obj->name; ?> has a fixed space, the given index [%d] is out of bounds...",  (int) index);
            }
<?php if ($obj->isVector()) : ?>
            obj_ptr->data[index] = Z_DVAL_P(value);
<?php elseif($obj->isMatrix()) : ?>
            obj_ptr->data[index / 4][index % 4] = Z_DVAL_P(value);
<?php endif; ?>
        } else {
            zend_throw_error(NULL, "Only a int offset '$vec[int]' can be used with the GL\\Math\\<?php echo $obj->name; ?> object");
        }
    }
}

<?php if ($obj->isVector()) : ?>
static zval *<?php echo $obj->getHandlerMethodName('read_prop'); ?>(zend_object *object, zend_string *member, int type, void **cache_slot, zval *rv) 
{
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(object);

	if ((type != BP_VAR_R && type != BP_VAR_IS)) {
		zend_throw_error(NULL, <?php echo $obj->getFullNamespaceCString(); ?>  " properties are virtual and cannot be referenced.");
		rv = &EG( uninitialized_zval );
	} else {

<?php foreach($obj->getPropIt() as $i => $name) : ?>
        <?php echo ($i !== 0 ? 'else ' : '') ?>if (zend_string_equals_literal(member, "<?php echo $name; ?>")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[<?php echo $i; ?>]);
        }
<?php endforeach; ?>
<?php foreach($obj->getAltPropIt() as $i => $name) : ?>
        else if (zend_string_equals_literal(member, "<?php echo $name; ?>")) {
		    ZVAL_DOUBLE(rv, obj_ptr->data[<?php echo $i; ?>]);
        }
<?php endforeach; ?>
        else {
            ZVAL_NULL(rv);
        }
	}

	return rv;
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

/**
 * Vector operation handler
 */
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

<?php elseif ($obj->isMatrix()) : ?>

/**
 * Matrix operation handler
 */

static int <?php echo $obj->getHandlerMethodName('do_op_ex'); ?>(zend_uchar opcode, zval *result, zval *op1, zval *op2)
{
    object_init_ex(result, <?php echo $obj->getClassEntryName(); ?>);
    <?php echo $obj->getObjectName(); ?> *resobj = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(result));

    // if left and right are both mat...
    if (
        Z_TYPE_P(op1) == IS_OBJECT && Z_OBJCE_P(op1) == <?php echo $obj->getClassEntryName(); ?> &&
        Z_TYPE_P(op2) == IS_OBJECT && Z_OBJCE_P(op2) == <?php echo $obj->getClassEntryName(); ?>
    ) {
        <?php echo $obj->getObjectName(); ?> *matobj1 = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(op1));
        <?php echo $obj->getObjectName(); ?> *matobj2 = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(op2));

        //php_printf("[%p](%f %f [%p] [%i]) * (%f %f [%p] [%i])\n", 
        //    result, matobj1->data[0][0], matobj1->data[0][1], op1, op1->u2.constant_flags,
        //    matobj2->data[0][0], matobj2->data[0][1], op2, op2->u2.constant_flags
        //);

        switch (opcode) {
        case ZEND_ADD:
            <?php echo $obj->getMatFunction('add'); ?>(resobj->data, matobj1->data, matobj2->data);
            return SUCCESS;
        case ZEND_SUB:
            <?php echo $obj->getMatFunction('sub'); ?>(resobj->data, matobj1->data, matobj2->data);
            return SUCCESS;
        case ZEND_MUL:
            <?php echo $obj->getMatFunction('mul'); ?>(resobj->data, matobj1->data, matobj2->data);
            return SUCCESS;
        default:
            return FAILURE;
        }
    }
    else {
        return FAILURE;
    }
}
static int <?php echo $obj->getHandlerMethodName('do_op'); ?>(zend_uchar opcode, zval *result, zval *op1, zval *op2)
{
    zval op1_copy;
    int retval;

    if (result == op1) {
        ZVAL_COPY_VALUE(&op1_copy, op1);
        op1 = &op1_copy;
    }

    retval = <?php echo $obj->getHandlerMethodName('do_op_ex'); ?>(opcode, result, op1, op2);

    if (retval == SUCCESS && op1 == &op1_copy) {
        zval_ptr_dtor(op1);
    }

    return retval;
}

<?php endif; ?>

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, __construct)
{
    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

<?php if ($obj->isVector()) : ?>
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
<?php endif; ?>
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
    smart_str_appends(&my_str, "<?php echo strtolower($obj->name); ?>(");

<?php if ($obj->isVector()) : ?>
    for (int i = 0; i < <?php echo $obj->size; ?>; i++) {
        glfw_smart_str_append_double(&my_str, obj_ptr->data[i], 4, true);
        if (i < <?php echo $obj->size; ?> - 1) {
            smart_str_appends(&my_str, ", ");
        }
    }
<?php elseif ($obj->isMatrix()) : ?>
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
<?php endif; ?>
    smart_str_appends(&my_str, ")");
    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

<?php if ($obj->isVector()) : ?>
PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, copy)
{
    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, <?php echo $obj->getClassEntryName(); ?>);
    <?php echo $obj->getObjectName(); ?> *resobj = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(return_value));

    // copy data
    for (int i = 0; i < <?php echo $obj->size; ?>; i++) {
        resobj->data[i] = obj_ptr->data[i];
    }
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

<?php if ($obj->size === 3) : ?>
PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, cross)
{
    zval *rightvec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &rightvec_zval, <?php echo $obj->getClassEntryName(); ?>) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *leftvec_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));
    <?php echo $obj->getObjectName(); ?> *rightvec_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(rightvec_zval));

    // create new vec
    object_init_ex(return_value, <?php echo $obj->getClassEntryName(); ?>);
    <?php echo $obj->getObjectName(); ?> *resobj = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(return_value));

    <?php echo $obj->getVecFunction('mul_cross'); ?>(resobj->data, leftvec_ptr->data, rightvec_ptr->data);
}
<?php endif; ?>

<?php elseif($obj->isMatrix()) : ?>

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, fromArray)
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

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, row)
{
    zend_long row_index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &row_index) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec4_ce);
    phpglfw_math_vec4_object *resobj = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    for(int i = 0; i < 4; i++) {
        resobj->data[i] = obj_ptr->data[row_index][i];
    }
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, col)
{
    zend_long col_index;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &col_index) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    // create new vec
    object_init_ex(return_value, phpglfw_math_vec4_ce);
    phpglfw_math_vec4_object *resobj = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));

    for(int i = 0; i < 4; i++) {
        resobj->data[i] = obj_ptr->data[i][col_index];
    }
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, setRow)
{
    zend_long row_index;
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &row_index, &vec_zval, phpglfw_math_vec4_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));
    phpglfw_math_vec4_object *vec_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));

    for(int i = 0; i < 4; i++) {
        obj_ptr->data[row_index][i] = vec_ptr->data[i];
    }
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, setCol)
{
    zend_long col_index;
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &col_index, &vec_zval, phpglfw_math_vec4_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));
    phpglfw_math_vec4_object *vec_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));

    for(int i = 0; i < 4; i++) {
        obj_ptr->data[i][col_index] = vec_ptr->data[i];
    }
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, perspective)
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
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    <?php echo $obj->getMatFunction('perspective'); ?>(obj_ptr->data, gl_fov, gl_aspect, gl_near, gl_far);
}


PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, ortho)
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
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    <?php echo $obj->getMatFunction('ortho'); ?>(obj_ptr->data, gl_left, gl_right, gl_bottom, gl_top, gl_near, gl_far);
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, lookAt)
{
    zval *eye_zval;
    zval *center_zval;
    zval *up_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "OOO", &eye_zval, phpglfw_math_vec3_ce, &center_zval, phpglfw_math_vec3_ce, &up_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));
    phpglfw_math_vec3_object *eye_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(eye_zval));
    phpglfw_math_vec3_object *center_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(center_zval));
    phpglfw_math_vec3_object *up_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(up_zval));

    <?php echo $obj->getMatFunction('look_at'); ?>(obj_ptr->data, eye_ptr->data, center_ptr->data, up_ptr->data);
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, transpose)
{
    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    mat4x4 T;
    <?php echo $obj->getMatFunction('transpose'); ?>(T, obj_ptr->data);
    mat4x4_dup(obj_ptr->data, T);
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, inverse)
{
    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    mat4x4 T;
    <?php echo $obj->getMatFunction('invert'); ?>(T, obj_ptr->data);
    mat4x4_dup(obj_ptr->data, T);
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, translate) {
    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }
    phpglfw_math_vec3_object *vec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));
    <?php echo $obj->getMatFunction('translate_in_place'); ?>(obj_ptr->data, vec_ptr->data[0], vec_ptr->data[1], vec_ptr->data[2]);
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, scale)
{
    zval *vec_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));
    phpglfw_math_vec3_object *vec_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));

    <?php echo $obj->getMatFunction('scale_aniso'); ?>(obj_ptr->data, obj_ptr->data, vec_ptr->data[0], vec_ptr->data[1], vec_ptr->data[2]);
}


PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, rotate)
{
    double radians;
    zval *axis_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "dO", &radians, &axis_zval, phpglfw_math_vec3_ce) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    phpglfw_math_vec3_object *axis_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(axis_zval));
    <?php echo $obj->getMatFunction('rotate'); ?>(obj_ptr->data, obj_ptr->data, axis_ptr->data[0], axis_ptr->data[1], axis_ptr->data[2], radians);
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, copy)
{
    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));
    
    // create new mat4
    object_init_ex(return_value, <?php echo $obj->getClassEntryName(); ?>);
    <?php echo $obj->getObjectName(); ?> *res_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(return_value));

    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            res_ptr->data[i][j] = obj_ptr->data[i][j];
        }
    }
}

PHP_METHOD(<?php echo $obj->getFullNamespaceConstString(); ?>, determinant)
{
    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_THROWS();
    }

    zval *obj;
    obj = getThis();
    <?php echo $obj->getObjectName(); ?> *obj_ptr = <?php echo $obj->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    RETURN_DOUBLE(<?php echo $obj->getMatFunction('det'); ?>(obj_ptr->data));
}

<?php endif; ?>

<?php endforeach; ?>

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

<?php foreach($objects as $obj) : ?> 
    INIT_CLASS_ENTRY(tmp_ce, <?php echo $obj->getFullNamespaceCString(); ?>, class_<?php echo $obj->getFullNamespaceConstString(); ?>_methods);
    <?php echo $obj->getClassEntryName(); ?> = zend_register_internal_class(&tmp_ce);
    <?php echo $obj->getClassEntryName(); ?>->create_object = <?php echo $obj->getHandlerMethodName('create'); ?>;

    memcpy(&<?php echo $obj->getHandlersVarName(); ?>, zend_get_std_object_handlers(), sizeof(<?php echo $obj->getHandlersVarName(); ?>));
    <?php echo $obj->getHandlersVarName(); ?>.get_debug_info = <?php echo $obj->getHandlerMethodName('debug_info'); ?>;
    <?php echo $obj->getHandlersVarName(); ?>.read_dimension = <?php echo $obj->getHandlerMethodName('array_get'); ?>;
    <?php echo $obj->getHandlersVarName(); ?>.write_dimension = <?php echo $obj->getHandlerMethodName('array_set'); ?>;

<?php if ($obj->isVector()) : ?>
    <?php echo $obj->getHandlersVarName(); ?>.read_property = <?php echo $obj->getHandlerMethodName('read_prop'); ?>;
    <?php echo $obj->getHandlersVarName(); ?>.write_property = <?php echo $obj->getHandlerMethodName('write_prop'); ?>;
<?php endif; ?>
    <?php echo $obj->getHandlersVarName(); ?>.do_operation = <?php echo $obj->getHandlerMethodName('do_op'); ?>;
    <?php echo $obj->getHandlersVarName(); ?>.offset = XtOffsetOf(<?php echo $obj->getObjectName(); ?>, std);
<?php endforeach; ?>
}