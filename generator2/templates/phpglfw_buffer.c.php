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
<?php foreach($buffers as $buffer) : ?>
zend_class_entry *<?php echo $buffer->getClassEntryName(); ?>; 
<?php endforeach; ?>

zend_class_entry *phpglfw_get_buffer_interface_ce() {
    return phpglfw_buffer_interface_ce;
}

<?php foreach($buffers as $buffer) : ?>
zend_class_entry *<?php echo $buffer->getClassEntryNameGetter(); ?>() {
    return <?php echo $buffer->getClassEntryName(); ?>;
}
<?php endforeach; ?>

<?php foreach($buffers as $buffer) : ?>
/**
 * <?php echo $buffer->getFullNamespaceString(); ?> 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers <?php echo $buffer->getHandlersVarName(); ?>;

static void <?php echo $buffer->getHandlerMethodName('free'); ?>(zend_object *object)
{
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

zend_object *<?php echo $buffer->getHandlerMethodName('create'); ?>(zend_class_entry *class_type)
{
    size_t block_len = sizeof(<?php echo $buffer->getObjectName(); ?>) + zend_object_properties_size(class_type);
    <?php echo $buffer->getObjectName(); ?> *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    intern->vec = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &<?php echo $buffer->getHandlersVarName(); ?>;

    return &intern->std;
}

zval *<?php echo $buffer->getHandlerMethodName('array_get'); ?>(zend_object *object, zval *offset, int type, zval *rv)
{
	if(offset == NULL) {
        zend_throw_error(NULL, "Cannot apply [] to GL\\Buffer\\BufferInterface object");
	}

    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(object);

    if (Z_TYPE_P(offset) == IS_LONG) {
		size_t index = (size_t)Z_LVAL_P(offset);

        if (index < cvector_size(obj_ptr->vec)) {
            <?php echo $buffer->getValueArg()->getZvalAssignmentMacro(); ?>(rv, obj_ptr->vec[index]);
        } else {
            ZVAL_NULL(rv);
        }
	} else {
        zend_throw_error(NULL, "Only a int offset '$buffer[int]' can be used with the GL\\Buffer\\BufferInterface object");
		ZVAL_NULL(rv);
	}

	return rv;
}

static HashTable *<?php echo $buffer->getHandlerMethodName('debug_info'); ?>(zend_object *object, int *is_temp)
{
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(object);
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

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, __toString)
{
	if (zend_parse_parameters_none() == FAILURE) {
		RETURN_THROWS();
	}

    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    smart_str my_str = {0};

    smart_str_appends(&my_str, <?php echo $buffer->getFullNamespaceCString(); ?> "(");
    smart_str_append_long(&my_str, cvector_size(obj_ptr->vec));
    smart_str_appends(&my_str, " [");
    smart_str_append_long(&my_str, cvector_capacity(obj_ptr->vec));
    smart_str_appends(&my_str, "])");

    smart_str_0(&my_str);

    RETURN_STRINGL(ZSTR_VAL(my_str.s), ZSTR_LEN(my_str.s));

    smart_str_free(&my_str);
}

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, push)
{
    <?php echo $buffer->getValueArg()->variableDeclarationPrefix; ?> value;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "<?php echo $buffer->getParseArgumentsChar(); ?>", &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    cvector_push_back(obj_ptr->vec, value);
}

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, reserve)
{
    zend_long resvering_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &resvering_size) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    cvector_reserve(obj_ptr->vec, resvering_size);
}

<?php endforeach; ?>

void phpglfw_register_buffer_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;

    // interface
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\BufferInterface", class_GL_Buffer_BufferInterface_methods);
    phpglfw_buffer_interface_ce = zend_register_internal_interface(&tmp_ce);
    
<?php foreach($buffers as $buffer) : ?>
    // float buffer
    INIT_CLASS_ENTRY(tmp_ce, <?php echo $buffer->getFullNamespaceCString(); ?>, class_<?php echo $buffer->getFullNamespaceConstString(); ?>_methods);
    <?php echo $buffer->getClassEntryName(); ?> = zend_register_internal_class(&tmp_ce);
    <?php echo $buffer->getClassEntryName(); ?>->create_object = <?php echo $buffer->getHandlerMethodName('create'); ?>;

	zend_class_implements(<?php echo $buffer->getClassEntryName(); ?>, 1, phpglfw_buffer_interface_ce);
    memcpy(&<?php echo $buffer->getHandlersVarName(); ?>, zend_get_std_object_handlers(), sizeof(<?php echo $buffer->getHandlersVarName(); ?>));
    <?php echo $buffer->getHandlersVarName(); ?>.free_obj = <?php echo $buffer->getHandlerMethodName('free'); ?>;
    <?php echo $buffer->getHandlersVarName(); ?>.read_dimension = <?php echo $buffer->getHandlerMethodName('array_get'); ?>;
    <?php echo $buffer->getHandlersVarName(); ?>.get_debug_info = <?php echo $buffer->getHandlerMethodName('debug_info'); ?>;
    <?php echo $buffer->getHandlersVarName(); ?>.offset = XtOffsetOf(<?php echo $buffer->getObjectName(); ?>, std);

<?php endforeach; ?>
}