/**
 * PHP-glfw 
 * 
 * Extension constants
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
#ifndef PHP_GLFW_CONSTANTS_H
#define PHP_GLFW_CONSTANTS_H 1

#include <zend_API.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void phpglfw_register_constants(INIT_FUNC_ARGS);

<?php foreach($groupedConstants as list($group, $constants)) : //var_dump($group); die; ?>
/**
<?php if ($group->name) : ?> 
 * <?php echo $group->name; ?> 
 * ----------------------------------------------------------------------------
<?php endif; ?>
<?php echo commentifyString($group->desc ?? ''); ?> 
 */
<?php foreach($constants as $const) : //var_dump($const); die; ?>
<?php if ($const->isForwardDefinition) : ?> 
#ifdef <?php echo $const->definition; ?> 
<?php endif; ?>
#define <?php echo $const->internalConstantName(); ?> <?php echo $const->getDefinitionValue(); ?><?php if ($const->comment) : ?> // <?php echo $const->comment; ?> <?php endif; ?> 
<?php if ($const->isForwardDefinition) : ?>
#endif
<?php endif; ?>
<?php endforeach; ?>

<?php endforeach; ?>
#endif
