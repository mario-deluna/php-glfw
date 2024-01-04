/**
 * PHP-glfw 
 * 
 * Extension constants
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
#ifndef PHP_GLFW_MATH_H
#define PHP_GLFW_MATH_H 1

#include "phpglfw_constants.h"
#include "linmath.h"

/**
 * object structs
 */
<?php foreach($objects as $obj) : ?>
typedef struct _<?php echo $obj->getObjectName(); ?> {
    <?php echo $obj->getInternalDataType(); ?> data;
    zend_object std;
} <?php echo $obj->getObjectName(); ?>; 

<?php endforeach; ?>

void phpglfw_register_math_module(INIT_FUNC_ARGS);

/**
 * Fetch object helper methods
 */
<?php foreach($objects as $obj) : ?>
zend_always_inline <?php echo $obj->getObjectName(); ?>* <?php echo $obj->objectFromZObjFunctionName(); ?>(zend_object* obj)
{
    return (<?php echo $obj->getObjectName(); ?> *) ((char *) (obj) - XtOffsetOf(<?php echo $obj->getObjectName(); ?>, std));
}

<?php endforeach; ?>

/**
 * Class entry getters
 */
<?php foreach($objects as $obj) : ?>
zend_class_entry *<?php echo $obj->getClassEntryNameGetter(); ?>(); 
<?php endforeach; ?>

#endif
