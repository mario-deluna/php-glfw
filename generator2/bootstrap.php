<?php
/**
 * Some general paths
 */
define('GEN_PATH_ROOT', __DIR__);
define('GEN_PATH_EXT', GEN_PATH_ROOT . '/..');
define('GEN_PATH_TEMPLATES', GEN_PATH_ROOT . '/templates');
define('GEN_PATH_DATA', GEN_PATH_ROOT . '/data');
define('GEN_DECL_PREFIX', 'phpglfw_');
define('GEN_VERBOSE', true);

/**
 * Autoloader
 */
require __DIR__ . '/vendor/autoload.php';
require __DIR__ . '/src/functions.php';