/**
 * PHP-glfw 
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
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <php.h>
#include <zend_API.h>
#include <ext/standard/info.h>

#include "phpglfw.h"
#include "phpglfw_arginfo.h"
#include "phpglfw_constants.h"
#include "phpglfw_functions.h"


zend_module_entry glfw_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_GLFW_EXTNAME,
    ext_functions,
    PHP_MINIT(glfw),
    NULL, // PHP_MSHUTDOWN(glfw),
    NULL,
    NULL,
    PHP_MINFO(glfw),
    PHP_GLFW_VERSION,
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_GLFW
ZEND_GET_MODULE(glfw)
#endif

/**
 * MINIT
 * --------------------------------
 */
PHP_MINIT_FUNCTION(glfw)
{   
    // register constants
    phpglfw_register_constants(INIT_FUNC_ARGS_PASSTHRU);
    phpglfw_register_resource_destructors(INIT_FUNC_ARGS_PASSTHRU);

    return SUCCESS;
}

/**
 * MINFO
 * --------------------------------
 */
PHP_MINFO_FUNCTION(glfw)
{
    php_info_print_table_start();
    php_info_print_table_row(2, "GLFW extension support", "enabled");
    php_info_print_table_row(2, "PHP-GLFW Version", PHP_GLFW_VERSION);
    php_info_print_table_row(2, "PHP-GLFW Compiled API", PHPGLFW_C_PHPGLFW_COMPILED_API);
    php_info_print_table_row(2, "PHP-GLFW Compiled API Version", PHPGLFW_C_PHPGLFW_COMPILED_API_VERSION);
    php_info_print_table_row(2, "GLFW Version", glfwGetVersionString());
    //php_info_print_table_row(2, "OpengGL Version", glGetString(PHPGLFW_C_GL_VERSION));
    php_info_print_table_row(2, "Author", "Mario Döring");
    php_info_print_table_end();

    DISPLAY_INI_ENTRIES();
}

// /**
//  * Register
//  * --------------------------------
//  */
// static zend_function_entry glfw_functions[] = {
// #ifdef PHP_FE_END
//     PHP_FE_END
// #else
//     {NULL, NULL, NULL}
// #endif
// };

// /* {{{ Return cURL version information. */
// PHP_FUNCTION(glGetVersion)
// {
//     RETURN_TRUE;
// }
// /* }}} */
