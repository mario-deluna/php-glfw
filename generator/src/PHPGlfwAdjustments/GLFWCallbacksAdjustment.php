<?php 

namespace PHPGlfwAdjustments;

use Exception;
use ExtArgument;
use ExtArgument\VariadicArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLFWCallbacksAdjustment implements AdjustmentInterface
{

    /**
     * GLFW Key Callback 
     * 
     * ------------------------------------------------------------------------------------------------------
     */
    private function patchGlfwSetKeyCallback(ExtGenerator $gen) : void
    {
        $functionName = 'glfwSetKeyCallback';

        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionImplementationBody(): string
            {

                $buffer = <<<EOD
zend_fcall_info fci;
zend_fcall_info_cache fcc;
zval *window_zval;

if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "Of",  &window_zval, phpglfw_glfwwindow_ce, &fci, &fcc)) {
    RETURN_THROWS();
}

if (Z_TYPE(_phpglfw_callback_keycallback) != IS_UNDEF) {
    zval_ptr_dtor(&_phpglfw_callback_keycallback);
}

GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);

ZVAL_COPY(&_phpglfw_callback_keycallback, &fci.function_name);

glfwSetKeyCallback(window, phpglfw_callback_keycallback_handler);
EOD;
                return $buffer;
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        $func->arguments[1] = ExtArgument::make('callback', ExtType::T_FUNC);

        $func->comment = <<<EOD
This function sets the key callback of the specified window, which is called when a key is pressed, repeated or released.

Example: 
```php
glfwSetKeyCallback(\$window, function(\$key, \$scancode, \$action, \$mods) use(\$window) {
	if (\$key == GLFW_KEY_ESCAPE && \$action == GLFW_PRESS) {
		glfwSetWindowShouldClose(\$window, GL_TRUE);
	}
});
```

The key functions deal with physical keys, with layout independent key tokens named after their values in the standard US keyboard layout. If you want to input text, use the character callback instead.

When a window loses input focus, it will generate synthetic key release events for all pressed keys. You can tell these events from user-generated events by the fact that the synthetic ones are generated after the focus loss event has been processed, i.e. after the window focus callback has been called.

The scancode of a key is specific to that platform or sometimes even to that machine. Scancodes are intended to allow users to bind keys that don't have a GLFW key token. Such keys have key set to GLFW_KEY_UNKNOWN, their state is not saved and so it cannot be queried with glfwGetKey.

Sometimes GLFW needs to generate synthetic key events, in which case the scancode may be zero.
EOD;

        $gen->replaceFunctionByName($func);
    }

    /**
     * GLFW CHAR Callback 
     * 
     * ------------------------------------------------------------------------------------------------------
     */
    private function patchGlfwSetCharCallback(ExtGenerator $gen) : void
    {
        $functionName = 'glfwSetCharCallback';

        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionImplementationBody(): string
            {

                $buffer = <<<EOD
zend_fcall_info fci;
zend_fcall_info_cache fcc;
zval *window_zval;

if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "Of",  &window_zval, phpglfw_glfwwindow_ce, &fci, &fcc)) {
    RETURN_THROWS();
}

if (Z_TYPE(_phpglfw_callback_charcallback) != IS_UNDEF) {
    zval_ptr_dtor(&_phpglfw_callback_charcallback);
}

GLFWwindow* window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);

ZVAL_COPY(&_phpglfw_callback_charcallback, &fci.function_name);

glfwSetCharCallback(window, phpglfw_callback_charcallback_handler);
EOD;
                return $buffer;
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        $func->arguments[1] = ExtArgument::make('callback', ExtType::T_FUNC);

        $func->comment = <<<EOD
This function sets the character callback of the specified window, which is called when a Unicode character is input.

Example:
```php
glfwSetCharCallback(\$window, function(\$codepoint) {
    echo "Character: " . mb_chr(\$codepoint) . PHP_EOL;
});
```

The character callback is intended for Unicode text input. As it deals with characters, it is keyboard layout dependent, whereas the key callback is not. Characters do not map 1:1 to physical keys, as a key may produce zero, one or more characters. If you want to know whether a specific physical key was pressed or released, see the key callback instead.

The character callback behaves as system text input normally does and will not be called if modifier keys are held down that would prevent normal text input on that platform, for example a Super (Command) key on macOS or Alt key on Windows.

EOD;
        // var_dump($func); die;

        $gen->replaceFunctionByName($func);
    }

    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $this->patchGlfwSetKeyCallback($gen);
        $this->patchGlfwSetCharCallback($gen);
    }
}
