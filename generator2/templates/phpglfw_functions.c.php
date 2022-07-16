/**
 * PHP-glfw 
 * 
 * Extension functions
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
#include "phpglfw_functions.h"

#include "php.h"
#include "phpglfw.h"
#include "phpglfw_buffer.h"
#include <zend_API.h>
    
/**
 * ----------------------------------------------------------------------------
 * PHPGlfw IPOs 
 * ----------------------------------------------------------------------------
 * IPOs (internal pointer object) is a simple PHP object which is attached to 
 * a resource pointer in the extension like a "GLFWwindow" etc...
 */

void phpglfw_register_ipos(void)
{
<?php foreach($ipos as $ipo) : ?>
    <?php echo $ipo->getObjectMinitHelperFunctionName(); ?>(); 
<?php endforeach; ?>
}

/**
 * Class entries
 */
<?php foreach($ipos as $ipo) : ?>
zend_class_entry *<?php echo $ipo->getClassEntryName(); ?>; 
<?php endforeach; ?>

/**
 * Structs
 */
<?php foreach($ipos as $ipo) : ?>
typedef struct _<?php echo $ipo->getObjectStructName(); ?> {
    <?php echo $ipo->getType(); ?> <?php echo $ipo->getObjectStructPointerVar(); ?>;
    zend_object std;
} <?php echo $ipo->getObjectStructName(); ?>; 

<?php endforeach; ?>

<?php foreach($ipos as $ipo) : ?>
/**
 * <?php echo $ipo->name; ?> aka (<?php echo $ipo->getType(); ?>) 
 * object handlers, initializers, helpers etc..
 */
static zend_object_handlers <?php echo $ipo->getObjectHandlersVar(); ?>;
static const zend_function_entry <?php echo $ipo->getClassMethodEntriesVar(); ?>[] = {
    ZEND_FE_END
};

static zend_always_inline <?php echo $ipo->getObjectStructName(); ?>* <?php echo $ipo->getObjectStructPtrFromZObjPtrFunctionName(); ?>(zend_object* obj)
{
    return (<?php echo $ipo->getObjectStructName(); ?> *) ((char *) (obj) - XtOffsetOf(<?php echo $ipo->getObjectStructName(); ?>, std));
}

static zend_function *<?php echo $ipo->getClassConstructorFunctionName(); ?>(zend_object *object)
{
    zend_throw_error(NULL, "You cannot initialize a <?php echo $ipo->getPHPClassName(); ?> object except through helper functions");
    return NULL;
}

static zend_class_entry *<?php echo $ipo->getClassRegistrationFunctionName(); ?>(void)
{
    zend_class_entry ce, *class_entry;

    INIT_CLASS_ENTRY(ce, "<?php echo $ipo->getPHPClassName(); ?>", <?php echo $ipo->getClassMethodEntriesVar(); ?>);
    class_entry = zend_register_internal_class_ex(&ce, NULL);

#ifdef ZEND_ACC_NOT_SERIALIZABLE  
    class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES|ZEND_ACC_NOT_SERIALIZABLE;
#else
    class_entry->ce_flags |= ZEND_ACC_FINAL|ZEND_ACC_NO_DYNAMIC_PROPERTIES;
#endif

    return class_entry;
}

zend_object *<?php echo $ipo->getObjectCreateFunctionName(); ?>(zend_class_entry *class_type)
{
    size_t block_len = sizeof(<?php echo $ipo->getObjectStructName(); ?>) + zend_object_properties_size(class_type);
    <?php echo $ipo->getObjectStructName(); ?> *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &<?php echo $ipo->getObjectHandlersVar(); ?>;

    return &intern->std;
}

static void <?php echo $ipo->getObjectFreeFunctionName(); ?>(zend_object *intern)
{
    <?php echo $ipo->getObjectStructName(); ?> *obj_ptr = <?php echo $ipo->getObjectStructPtrFromZObjPtrFunctionName(); ?>(intern);
    if (obj_ptr-><?php echo $ipo->getObjectStructPointerVar(); ?>) {
        <?php echo $ipo->getDestructionCall('obj_ptr->' .  $ipo->getObjectStructPointerVar()); ?> 
    }
    zend_object_std_dtor(intern);
}

void <?php echo $ipo->getAssignPtrToZvalFunctionName(); ?>(zval *val, <?php echo $ipo->getType(); ?> <?php echo $ipo->getObjectStructPointerVar(); ?>)
{
    object_init_ex(val, <?php echo $ipo->getClassEntryName(); ?>);
    <?php echo $ipo->getObjectStructPtrFromZObjPtrFunctionName(); ?>(Z_OBJ_P(val))-><?php echo $ipo->getObjectStructPointerVar(); ?> = <?php echo $ipo->getObjectStructPointerVar(); ?>;
}

void <?php echo $ipo->getObjectMinitHelperFunctionName(); ?>(void)
{
    <?php echo $ipo->getClassEntryName(); ?> = <?php echo $ipo->getClassRegistrationFunctionName(); ?>();
    <?php echo $ipo->getClassEntryName(); ?>->create_object = <?php echo $ipo->getObjectCreateFunctionName(); ?>;

    memcpy(&<?php echo $ipo->getObjectHandlersVar(); ?>, &std_object_handlers, sizeof(zend_object_handlers));
    <?php echo $ipo->getObjectHandlersVar(); ?>.clone_obj = NULL;
    <?php echo $ipo->getObjectHandlersVar(); ?>.free_obj = <?php echo $ipo->getObjectFreeFunctionName(); ?>;
    <?php echo $ipo->getObjectHandlersVar(); ?>.get_constructor = <?php echo $ipo->getClassConstructorFunctionName(); ?>;
    <?php echo $ipo->getObjectHandlersVar(); ?>.compare = zend_objects_not_comparable;
    <?php echo $ipo->getObjectHandlersVar(); ?>.offset = XtOffsetOf(<?php echo $ipo->getObjectStructName(); ?>, std);
}

<?php echo $ipo->getType(); ?> <?php echo $ipo->getInternalPtrFromZValPtrFunctionName(); ?>(zval* zp)
{
    return <?php echo $ipo->getObjectStructPtrFromZObjPtrFunctionName(); ?>(Z_OBJ_P(zp))-><?php echo $ipo->getObjectStructPointerVar(); ?>;
}

<?php endforeach; ?>

/**
 * ----------------------------------------------------------------------------
 * PHPGlfw Functions 
 * ----------------------------------------------------------------------------
 * All the functions wrapped by the extension.
 */
<?php foreach($functions as $func) : ?>
<?php echo $func->getFunctionCommentBlock(); ?> 
<?php echo $func->getFunctionImplementation(); ?> 

<?php endforeach; ?>
