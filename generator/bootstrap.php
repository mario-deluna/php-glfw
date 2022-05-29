<?php
define('GEN_PATH_ROOT', __DIR__);
define('GEN_PATH_EXT', GEN_PATH_ROOT . '/..');
define('GEN_PATH_TEMPLATES', GEN_PATH_ROOT . '/templates');
define('GEN_PATH_DATA', GEN_PATH_ROOT . '/data');

/**
 * Just include everything, I don't bother 
 * with an autoloader in this project..
 */
require __DIR__ . '/src/functions.php';
require __DIR__ . '/src/ExtType.php';
require __DIR__ . '/src/GLSpecReader.php';
require __DIR__ . '/src/GLSpec.php';
require __DIR__ . '/src/GLFWHeaderParser.php';
require __DIR__ . '/src/ExtConstant.php';
require __DIR__ . '/src/ExtResource.php';
require __DIR__ . '/src/ExtArgument.php';
require __DIR__ . '/src/ExtFunction.php';
require __DIR__ . '/src/ExtGenerator.php';
require __DIR__ . '/src/Method.php';
require __DIR__ . '/src/Argument.php';
require __DIR__ . '/src/Resource.php';
