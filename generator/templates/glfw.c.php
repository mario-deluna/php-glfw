#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_glfw.h"
#include "linmath.h"

#include <zend_API.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
static <?php echo $resource->type; ?><?php echo $resource->getFetchMethod(); ?>(zval *resource TSRMLS_DC)
{
    <?php echo $resource->type; ?><?php echo $resource->name; ?>;

    <?php echo $resource->name; ?> = (<?php echo $resource->type; ?>)zend_fetch_resource_ex(resource, <?php echo $resource->getResourceName(); ?>, <?php echo $resource->getContextName(); ?>);

    return <?php echo $resource->name; ?>;
}

/**
 * dtor <?php echo $resource->type; ?>
 * --------------------------------
 */
static void <?php echo $resource->getDtorMethod(); ?>(zend_resource *rsrc TSRMLS_DC)
{
    <?php echo $resource->type; ?><?php echo $resource->name; ?> = (void *) rsrc->ptr;

    if (<?php echo $resource->name; ?>) {
        <?php echo $resource->generateDestroy(); ?>
    }
}

<?php endforeach; ?>

/**
 * --------------------------------
 * Generated methods
 * --------------------------------
 */
<?php foreach($methods as $method) : ?>
<?php echo $method->generate(); ?> 
<?php endforeach; ?>


/**
 * MINIT
 * --------------------------------
 */
PHP_MINIT_FUNCTION(glfw)
{
<?php foreach ($resources as $resource) : ?>
    <?php echo $resource->getContextName(); ?> = zend_register_list_destructors_ex(<?php echo $resource->getDtorMethod(); ?>, NULL, <?php echo $resource->getResourceName(); ?>, module_number);
<?php endforeach; ?>
<?php foreach($constants as $constant) : ?>
#ifdef <?php echo $constant; ?> 
    REGISTER_LONG_CONSTANT("<?php echo $constant; ?>", <?php echo $constant; ?>, CONST_CS|CONST_PERSISTENT);
#endif
<?php endforeach; ?>
    return SUCCESS;
}

/**
 * Register
 * --------------------------------
 */
static zend_function_entry glfw_functions[] = {
<?php foreach($methods as $method) : ?>
    <?php echo $method->generateFE(); ?> 
<?php endforeach; ?>
#ifdef PHP_FE_END
    PHP_FE_END
#else
    {NULL, NULL, NULL}
#endif
};

zend_module_entry glfw_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_GLFW_EXTNAME,
    glfw_functions,
    PHP_MINIT(glfw),
    NULL,
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_GLFW_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GLFW
ZEND_GET_MODULE(glfw)
#endif