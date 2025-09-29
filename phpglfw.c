/**
 * PHP-glfw 
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
#include "phpglfw_math.h"
#include "phpglfw_buffer.h"
#include "phpglfw_texture.h"
#include "phpglfw_objparser.h"
#include "phpglfw_voxparser.h"
#include "phpglfw_vg.h"
#include "phpglfw_audio.h"

ZEND_DECLARE_MODULE_GLOBALS(glfw)

zend_module_entry glfw_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_GLFW_EXTNAME,
    ext_functions,
    PHP_MINIT(glfw),
    PHP_MSHUTDOWN(glfw),
    NULL,
    NULL,
    PHP_MINFO(glfw),
    PHP_GLFW_VERSION,
	PHP_MODULE_GLOBALS(glfw),
	NULL,
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};

#ifdef COMPILE_DL_GLFW
ZEND_GET_MODULE(glfw)
#endif

/* {{{ PHP_INI */
PHP_INI_BEGIN()
    STD_PHP_INI_BOOLEAN("glfw.buffer_serialize_hex_float", "0", PHP_INI_ALL, OnUpdateBool, buffer_serialize_hex_float, zend_glfw_globals, glfw_globals)
PHP_INI_END()
/* }}} */

/**
 * MINIT
 * --------------------------------
 */
PHP_MINIT_FUNCTION(glfw)
{   
    REGISTER_INI_ENTRIES();

    // register constants
    phpglfw_register_constants(INIT_FUNC_ARGS_PASSTHRU);

    // callbacks
    phpglfw_init_callbacks();

    // register IPOs
    phpglfw_register_ipos();

    // math module
    phpglfw_register_math_module(INIT_FUNC_ARGS_PASSTHRU);

    // buffer module
    phpglfw_register_buffer_module(INIT_FUNC_ARGS_PASSTHRU);

    // texture module
    phpglfw_register_texture_module(INIT_FUNC_ARGS_PASSTHRU);

    // object parser module
    phpglfw_register_objparser_module(INIT_FUNC_ARGS_PASSTHRU);

    // voxel parser module
    phpglfw_register_voxparser_module(INIT_FUNC_ARGS_PASSTHRU);

    // vg module
    phpglfw_register_vg_module(INIT_FUNC_ARGS_PASSTHRU);

    // audio module
    phpglfw_register_audio_module(INIT_FUNC_ARGS_PASSTHRU);

    return SUCCESS;
}

/**
 * MSHUTDOWN
 * --------------------------------
 */
PHP_MSHUTDOWN_FUNCTION(glfw)
{   
    // destruct registered callbacks
    phpglfw_shutdown_callbacks();

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
