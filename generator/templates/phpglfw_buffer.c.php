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
<?php echo $buffer->getObjectName(); ?>* <?php echo $buffer->objectFromZObjFunctionName(); ?>(zend_object* obj)
{
    return (<?php echo $buffer->getObjectName(); ?> *) ((char *) (obj) - XtOffsetOf(<?php echo $buffer->getObjectName(); ?>, std));
}
<?php endforeach; ?>

<?php foreach($buffers as $buffer) : ?>
/**
 * <?php echo $buffer->getFullNamespaceString(); ?> 
 * 
 * ----------------------------------------------------------------------------
 */
static zend_object_handlers <?php echo $buffer->getHandlersVarName(); ?>;

/**
 * Iterator (<?php echo $buffer->getFullNamespaceString(); ?> )
 */
typedef struct _<?php echo $buffer->getIteratorObjectName(); ?> {
	zend_object_iterator intern;
	size_t index;
	zval current;
} <?php echo $buffer->getIteratorObjectName(); ?>;

static void <?php echo $buffer->getHandlerMethodName('it_dtor'); ?>(zend_object_iterator *iter)
{
	<?php echo $buffer->getIteratorObjectName(); ?> *I = (<?php echo $buffer->getIteratorObjectName(); ?>*)iter;

	zval_ptr_dtor(&I->intern.data);
    if (!Z_ISUNDEF(I->current)) {
		zval_ptr_dtor(&I->current);
	}
}

static void <?php echo $buffer->getHandlerMethodName('it_rewind'); ?>(zend_object_iterator *iter)
{
	((<?php echo $buffer->getIteratorObjectName(); ?>*)iter)->index = 0;
}

static void <?php echo $buffer->getHandlerMethodName('it_current_key'); ?>(zend_object_iterator *iter, zval *key)
{
	ZVAL_LONG(key, ((<?php echo $buffer->getIteratorObjectName(); ?>*)iter)->index);
}

static void <?php echo $buffer->getHandlerMethodName('it_move_forward'); ?>(zend_object_iterator *iter)
{
	((<?php echo $buffer->getIteratorObjectName(); ?>*)iter)->index++;
}

static int <?php echo $buffer->getHandlerMethodName('it_valid'); ?>(zend_object_iterator *iter)
{
	<?php echo $buffer->getIteratorObjectName(); ?> *iterator = (<?php echo $buffer->getIteratorObjectName(); ?>*)iter;
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(&iter->data));

	if (iterator->index >= 0 && iterator->index < cvector_size(obj_ptr->vec)) {
		return SUCCESS;
	}

	return FAILURE;
}

static zval *<?php echo $buffer->getHandlerMethodName('it_current_data'); ?>(zend_object_iterator *iter)
{
	<?php echo $buffer->getIteratorObjectName(); ?> *iterator = (<?php echo $buffer->getIteratorObjectName(); ?>*)iter;
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(&iter->data));

	<?php echo $buffer->getValueArg()->getZvalAssignmentMacro(); ?>(&iterator->current, obj_ptr->vec[iterator->index]);

	return &iterator->current;
}

static const zend_object_iterator_funcs <?php echo $buffer->getIteratorHandlersVarName(); ?> = {
	<?php echo $buffer->getHandlerMethodName('it_dtor'); ?>,
	<?php echo $buffer->getHandlerMethodName('it_valid'); ?>,
	<?php echo $buffer->getHandlerMethodName('it_current_data'); ?>,
	<?php echo $buffer->getHandlerMethodName('it_current_key'); ?>,
	<?php echo $buffer->getHandlerMethodName('it_move_forward'); ?>,
	<?php echo $buffer->getHandlerMethodName('it_rewind'); ?>,
	NULL,
	NULL,
};

zend_object_iterator *<?php echo $buffer->getHandlerMethodName('get_iterator'); ?>(zend_class_entry *ce, zval *object, int by_ref)
{
	<?php echo $buffer->getIteratorObjectName(); ?> *iterator;

	if (by_ref != 0) {
		zend_throw_error(NULL, "GL\\Buffer\\BufferInterface object can not be iterated by reference");
		return NULL;
	}
    
	iterator = emalloc(sizeof(<?php echo $buffer->getIteratorObjectName(); ?>));

	zend_iterator_init((zend_object_iterator*)iterator);

	ZVAL_OBJ_COPY(&iterator->intern.data, Z_OBJ_P(object));
	iterator->intern.funcs = &<?php echo $buffer->getIteratorHandlersVarName(); ?>;
    iterator->index = 0;

	return &iterator->intern;
}

/**
 * Free (<?php echo $buffer->getFullNamespaceString(); ?> )
 */
static void <?php echo $buffer->getHandlerMethodName('free'); ?>(zend_object *object)
{
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(object);
    cvector_free(obj_ptr->vec);
    zend_object_std_dtor(&obj_ptr->std);
}

/**
 * Creation (<?php echo $buffer->getFullNamespaceString(); ?> )
 */
zend_object *<?php echo $buffer->getHandlerMethodName('create'); ?>(zend_class_entry *class_type)
{
    <?php echo $buffer->getObjectName(); ?> *intern = zend_object_alloc(sizeof(<?php echo $buffer->getObjectName(); ?>), class_type);

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

void <?php echo $buffer->getHandlerMethodName('array_set'); ?>(zend_object *object, zval *offset, zval *value)
{
    if (Z_TYPE_P(value) != <?php echo $buffer->getValueArg()->getZvalTypeComparisonConst(); ?>) {
        zend_throw_error(NULL, "Trying to store non <?php echo $buffer->getValuePHPType(); ?> value in a <?php echo $buffer->getValuePHPType(); ?> type buffer.");
        return;
    }

    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(object);

    // if offset is not given ($buff[] = 3.14)  
	if (offset == NULL) {
        cvector_push_back(obj_ptr->vec, <?php echo $buffer->getValueArg()->getValueFromZvalPointerConst(); ?>(value));
	} 
    else {
        if (Z_TYPE_P(offset) == IS_LONG) {
            size_t index = (size_t)Z_LVAL_P(offset);

            if (index >= cvector_size(obj_ptr->vec)) {
                zend_throw_error(NULL, "Cannot modify unallocated buffer space, the element at index [%d] does not exist. Use `push` or `fill` to allocate the requested spaces.",  (int) index);
            }

            obj_ptr->vec[index] = <?php echo $buffer->getValueArg()->getValueFromZvalPointerConst(); ?>(value);
        } else {
            zend_throw_error(NULL, "Only a int offset '$buffer[int]' can be used with the GL\\Buffer\\BufferInterface object");
        }
    }
}
/*
static int <?php echo $buffer->getHandlerMethodName('serialize'); ?>(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(object));

    size_t item_count = cvector_size(obj_ptr->vec);
    *buf_len = sizeof(size_t) + item_count * sizeof(<?php echo $buffer->type; ?>);
    *buffer = emalloc(*buf_len);

    memcpy(*buffer, &item_count, sizeof(size_t));
    memcpy(*buffer + sizeof(size_t), obj_ptr->vec, item_count * sizeof(<?php echo $buffer->type; ?>));

    return SUCCESS;
}

int <?php echo $buffer->getHandlerMethodName('unserialize'); ?>(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    const unsigned char *buf_ptr = buf;
    size_t item_count;
    <?php echo $buffer->getObjectName(); ?> *obj;

    if (buf_len < sizeof(size_t)) {
        zend_throw_error(NULL, "Buffer underflow during <?php echo $buffer->getObjectName(); ?> unserialization", 0);
        return FAILURE;
    }

    memcpy(&item_count, buf_ptr, sizeof(size_t));
    buf_ptr += sizeof(size_t);

    if (buf_len < sizeof(size_t) + item_count * sizeof(<?php echo $buffer->type; ?>)) {
        zend_throw_error(NULL, "Buffer underflow during <?php echo $buffer->getObjectName(); ?> unserialization", 0);
        return FAILURE;
    }

    object_init_ex(object, <?php echo $buffer->getClassEntryName(); ?>);
    obj = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(object));
    //obj->vec = emalloc(item_count * sizeof(<?php echo $buffer->type; ?>));

    cvector_reserve(obj->vec, item_count);
    cvector_set_size(obj->vec, item_count); 

    // copy the data
    memcpy(obj->vec, buf_ptr, item_count * sizeof(<?php echo $buffer->type; ?>));

    return SUCCESS;
}*/

static int <?php echo $buffer->getHandlerMethodName('serialize'); ?>(zval *object, unsigned char **buffer, size_t *buf_len, zend_serialize_data *data)
{
<?php if (!$buffer->isPrintfSameInHex()) : ?>
    bool serialize_hex_float = PHPGLFW_G(buffer_serialize_hex_float);
<?php endif; ?>
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(object));
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
    cvector_reserve(buffer_string, num_elements * sizeof(<?php echo $buffer->type; ?>));

    // write the number of elements
    int offset = sprintf(tmp, "%zu:", num_elements);
    cvector_push_back_array(buffer_string, tmp, offset);

    // write each element
<?php if (!$buffer->isPrintfSameInHex()) : ?>
    if (serialize_hex_float) {
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "<?php echo $buffer->getPrintfHexFormat(); ?> ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }
    } else {
<?php endif; ?>
        for (size_t i = 0; i < num_elements; i++) {
            offset = sprintf(tmp, "<?php echo $buffer->getPrintfFormat(); ?> ", obj_ptr->vec[i]);
            cvector_push_back_array(buffer_string, tmp, offset);
        }
<?php if (!$buffer->isPrintfSameInHex()) : ?>
    }
<?php endif; ?>

    // trim away the trailing space
    cvector_pop_back(buffer_string);

    size_t total_size = cvector_size(buffer_string);

    *buffer = (unsigned char *)estrndup(buffer_string, total_size);
    *buf_len = total_size;
    // efree(buf);

    return SUCCESS;
}

static int <?php echo $buffer->getHandlerMethodName('unserialize'); ?>(zval *object, zend_class_entry *ce, const unsigned char *buf, size_t buf_len, zend_unserialize_data *data)
{
    <?php echo $buffer->getObjectName(); ?> *obj;

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
        zend_throw_error(NULL, "Invalid format during <?php echo $buffer->getObjectName(); ?> unserialization, could not parse the number of elements.");
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
    object_init_ex(object, <?php echo $buffer->getClassEntryName(); ?>);
    obj = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(object));

    cvector_reserve(obj->vec, exp_item_count); 

    // read the elements, check if our endptr is still valid and we have not reached the end of the buffer
    token = strtok(tmp_copy, " ");
    while (token != NULL && item_count > 0) {
        <?php if ($buffer->type == "GLfloat" || $buffer->type == "GLdouble"): ?>
        cvector_push_back(obj->vec, atof(token));
        <?php elseif ($buffer->type == "GLint" || $buffer->type == "GLuint" || $buffer->type == "GLshort" || $buffer->type == "GLushort" || $buffer->type == "GLhalf" || $buffer->type == "GLbyte" || $buffer->type == "GLubyte"): ?>
        cvector_push_back(obj->vec, strtol(token, NULL, 10));
        <?php else: ?>
        zend_throw_error(NULL, "Unknown buffer type for deserialization.");
        return FAILURE;
        <?php endif; ?>
        token = strtok(NULL, " ");
        item_count--;
    }

    if (cvector_size(obj->vec) != exp_item_count) {
        zend_throw_error(NULL, "Mismatch in expected item count during <?php echo $buffer->getObjectName(); ?> unserialization. Expected: %zu, Found: %zu", exp_item_count, cvector_size(obj->vec));
        return FAILURE;
    }

    return SUCCESS;
}

static HashTable *<?php echo $buffer->getHandlerMethodName('debug_info'); ?>(zend_object *object, int *is_temp)
{
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(object);
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
        <?php echo $buffer->getValueArg()->getZvalAssignmentMacro(); ?>(&zv, obj_ptr->vec[i]);
        zend_hash_index_update(dataht, i, &zv);
    }


    ZVAL_ARR(&zv, dataht);
    zend_hash_str_update(ht, "data", sizeof("data") - 1, &zv);

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

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, pushArray)
{
    zval *array;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "a", &array) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    ZEND_HASH_FOREACH_VAL(Z_ARRVAL_P(array), array) {
        if (Z_TYPE_P(array) != <?php echo $buffer->getValueArg()->getZvalTypeComparisonConst(); ?>) {
            zend_throw_error(NULL, "Trying to store non <?php echo $buffer->getValuePHPType(); ?> value in a <?php echo $buffer->getValuePHPType(); ?> type buffer.");
            return;
        }

        cvector_push_back(obj_ptr->vec, <?php echo $buffer->getValueArg()->getValueFromZvalPointerConst(); ?>(array));
    } ZEND_HASH_FOREACH_END();
}

<?php if ($buffer->name == 'FloatBuffer') : ?>
PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, pushVec2)
{
    zval *vec2;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec2, phpglfw_get_math_vec2_ce()) == FAILURE) {
        return;
    }

    phpglfw_math_vec2_object *vec2_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P(vec2));

    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    for(size_t i = 0; i < 2; i++) {
        cvector_push_back(obj_ptr->vec, vec2_ptr->data[i]);
    }
}

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, pushVec3)
{
    zval *vec3;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec3, phpglfw_get_math_vec3_ce()) == FAILURE) {
        return;
    }

    phpglfw_math_vec3_object *vec3_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(vec3));

    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    for(size_t i = 0; i < 3; i++) {
        cvector_push_back(obj_ptr->vec, vec3_ptr->data[i]);
    }
}

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, pushVec4)
{
    zval *vec4;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &vec4, phpglfw_get_math_vec4_ce()) == FAILURE) {
        return;
    }

    phpglfw_math_vec4_object *vec4_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(vec4));

    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    for(size_t i = 0; i < 4; i++) {
        cvector_push_back(obj_ptr->vec, vec4_ptr->data[i]);
    }
}

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, pushMat4)
{
    zval *mat4;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &mat4, phpglfw_get_math_mat4_ce()) == FAILURE) {
        return;
    }

    phpglfw_math_mat4_object *mat4_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(mat4));

    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    for(size_t i = 0; i < 4; i++) {
        for(size_t j = 0; j < 4; j++) {
            cvector_push_back(obj_ptr->vec, mat4_ptr->data[i][j]);
        }
    }
}

<?php endif; ?>


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

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, clear)
{
    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));
    
    cvector_free(obj_ptr->vec);
    obj_ptr->vec = NULL;
}

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, fill)
{
    <?php echo $buffer->getValueArg()->variableDeclarationPrefix; ?> value;
    zend_long fill_size;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l<?php echo $buffer->getParseArgumentsChar(); ?>", &fill_size, &value) == FAILURE) {
        return;
    }

    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));
    
    cvector_fill(obj_ptr->vec, fill_size, value);
}

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, size)
{
    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    RETURN_LONG(cvector_size(obj_ptr->vec));
}

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, capacity)
{
    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    RETURN_LONG(cvector_capacity(obj_ptr->vec));
}

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, dump)
{
    zval *obj;
    obj = getThis();
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    RETURN_STRINGL((char *)obj_ptr->vec, cvector_size(obj_ptr->vec) * sizeof(<?php echo $buffer->type; ?>));
}

PHP_METHOD(<?php echo $buffer->getFullNamespaceConstString(); ?>, __construct)
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
    <?php echo $buffer->getObjectName(); ?> *obj_ptr = <?php echo $buffer->objectFromZObjFunctionName(); ?>(Z_OBJ_P(obj));

    // reserve the space
    cvector_reserve(obj_ptr->vec, zend_hash_num_elements(initaldata));

    ZEND_HASH_FOREACH_VAL(initaldata, data)
        if (Z_TYPE_P(data) == <?php echo $buffer->getValueArg()->getZvalTypeComparisonConst(); ?>) {
            cvector_push_back(obj_ptr->vec, <?php echo $buffer->getValueArg()->getValueFromZvalPointerConst(); ?>(data));
        } else {
            zend_throw_error(NULL, "All elements of the inital data array has to be of type: <?php echo $buffer->getValuePHPType(); ?>");
        }
    ZEND_HASH_FOREACH_END();
}

<?php endforeach; ?>

void phpglfw_register_buffer_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;

    // interface
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Buffer\\BufferInterface", class_GL_Buffer_BufferInterface_methods);
    phpglfw_buffer_interface_ce = zend_register_internal_interface(&tmp_ce);
    
<?php foreach($buffers as $buffer) : ?> 
    INIT_CLASS_ENTRY(tmp_ce, <?php echo $buffer->getFullNamespaceCString(); ?>, class_<?php echo $buffer->getFullNamespaceConstString(); ?>_methods);
    <?php echo $buffer->getClassEntryName(); ?> = zend_register_internal_class(&tmp_ce);
    <?php echo $buffer->getClassEntryName(); ?>->create_object = <?php echo $buffer->getHandlerMethodName('create'); ?>;
    <?php echo $buffer->getClassEntryName(); ?>->serialize = <?php echo $buffer->getHandlerMethodName('serialize'); ?>;
    <?php echo $buffer->getClassEntryName(); ?>->unserialize = <?php echo $buffer->getHandlerMethodName('unserialize'); ?>;
    <?php echo $buffer->getClassEntryName(); ?>->get_iterator = <?php echo $buffer->getHandlerMethodName('get_iterator'); ?>;

	zend_class_implements(<?php echo $buffer->getClassEntryName(); ?>, 1, phpglfw_buffer_interface_ce);
    memcpy(&<?php echo $buffer->getHandlersVarName(); ?>, &std_object_handlers, sizeof(zend_object_handlers));
    <?php echo $buffer->getHandlersVarName(); ?>.offset = XtOffsetOf(<?php echo $buffer->getObjectName(); ?>, std);
    
    <?php echo $buffer->getHandlersVarName(); ?>.free_obj = <?php echo $buffer->getHandlerMethodName('free'); ?>;
    <?php echo $buffer->getHandlersVarName(); ?>.read_dimension = <?php echo $buffer->getHandlerMethodName('array_get'); ?>;
    <?php echo $buffer->getHandlersVarName(); ?>.write_dimension = <?php echo $buffer->getHandlerMethodName('array_set'); ?>;
    <?php echo $buffer->getHandlersVarName(); ?>.get_debug_info = <?php echo $buffer->getHandlerMethodName('debug_info'); ?>;
    
<?php endforeach; ?>
}