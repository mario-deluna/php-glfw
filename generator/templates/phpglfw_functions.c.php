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
#include <zend_API.h>

/**
 * ----------------------------------------------------------------------------
 * PHPGlfw Resources 
 * ----------------------------------------------------------------------------
 */

<?php foreach ($resources as $resource) : ?>
#define <?php echo $resource->getResourceName(); ?> "<?php echo $resource->name; ?>"
int <?php echo $resource->getContextName(); ?>;
<?php endforeach; ?>

#define PHPGLFW_RESOURCE_TYPE zend_resource
<?php foreach ($resources as $resource) : ?>
#define <?php echo $resource->getReturnResource(); ?>(<?php echo $resource->name; ?>, context) \
    RETURN_RES(zend_register_resource(<?php echo $resource->name; ?>, context))
<?php endforeach; ?>

<?php foreach ($resources as $resource) : ?>
/**
 * Get <?php echo $resource->type; ?> from resource 
 * --------------------------------
 */
static <?php echo $resource->type; ?><?php echo $resource->getFetchMethod(); ?>(zval *resource)
{
    <?php echo $resource->type; ?><?php echo $resource->name; ?>;
    ZEND_ASSERT(Z_TYPE_P(resource) == IS_RESOURCE);
    <?php echo $resource->name; ?> = (<?php echo $resource->type; ?>)zend_fetch_resource(Z_RES_P(resource), <?php echo $resource->getResourceName(); ?>, <?php echo $resource->getContextName(); ?>);

    return <?php echo $resource->name; ?>;
}

/**
 * dtor <?php echo $resource->type; ?> 
 * --------------------------------
 */
static void <?php echo $resource->getDtorMethod(); ?>(PHPGLFW_RESOURCE_TYPE *rsrc)
{
    <?php echo $resource->type; ?><?php echo $resource->name; ?> = (void *) rsrc->ptr;

    if (<?php echo $resource->name; ?>) {
        <?php echo $resource->generateDestroy(); ?> 
    }
}

<?php endforeach; ?>


/**
 * Resources destructors..
 */
void phpglfw_register_resource_destructors(INIT_FUNC_ARGS)
{
<?php foreach ($resources as $resource) : ?>
    <?php echo $resource->getContextName(); ?> = zend_register_list_destructors_ex(<?php echo $resource->getDtorMethod(); ?>, NULL, <?php echo $resource->getResourceName(); ?>, module_number);
<?php endforeach; ?>
}

/**
 * ----------------------------------------------------------------------------
 * PHPGlfw Functions 
 * ----------------------------------------------------------------------------
 */
<?php foreach($functions as $func) : ?>
/**
 * <?php echo $func->name; ?> 
<?php echo commentifyString($func->comment ?? ''); ?> 
 */
<?php echo $func->generateExtImplementation(); ?>

<?php endforeach; ?>
