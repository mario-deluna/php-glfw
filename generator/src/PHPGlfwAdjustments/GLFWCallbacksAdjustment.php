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
    public static function createCallbackImpl(string $handlerFunc, string $callbackStore, string $glfwFunc) : string
    {
        return <<<EOD

zend_fcall_info fci;
zend_fcall_info_cache fcc;
zval *window_zval;

if (FAILURE == zend_parse_parameters(ZEND_NUM_ARGS(), "Of",  &window_zval, phpglfw_glfwwindow_ce, &fci, &fcc)) {
    RETURN_THROWS();
}

phpglfw_glfwwindow_object *obj_ptr = phpglfw_glfwwindow_objectptr_from_zobj_p(Z_OBJ_P(window_zval));

Z_TRY_ADDREF(fci.function_name);
if (fcc.object) {
    GC_ADDREF(fcc.object);
}

memcpy((void*)&obj_ptr->{$callbackStore}.fci, (void*)&fci, sizeof(zend_fcall_info));
memcpy((void*)&obj_ptr->{$callbackStore}.fci_cache, (void*)&fcc, sizeof(zend_fcall_info_cache));

{$glfwFunc}(obj_ptr->glfwwindow, {$handlerFunc});
EOD;
    }


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

phpglfw_glfwwindow_object *obj_ptr = phpglfw_glfwwindow_objectptr_from_zobj_p(Z_OBJ_P(window_zval));

// copy the function info over to the window object
// obj_ptr->keycallback.fci = fci;
// obj_ptr->keycallback.fci_cache = fcc;

// this fixes a segfault when the callback has a reference over `use()`
// i honestly have no idea why this works, but it does
Z_TRY_ADDREF(fci.function_name);
if (fcc.object) {
    GC_ADDREF(fcc.object);
}

memcpy((void*)&obj_ptr->keycallback.fci, (void*)&fci, sizeof(zend_fcall_info));
memcpy((void*)&obj_ptr->keycallback.fci_cache, (void*)&fcc, sizeof(zend_fcall_info_cache));

glfwSetKeyCallback(obj_ptr->glfwwindow, phpglfw_callback_keycallback_handler);
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
                return GLFWCallbacksAdjustment::createCallbackImpl('phpglfw_callback_charcallback_handler', 'charcallback', 'glfwSetCharCallback');
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
        $gen->replaceFunctionByName($func);
    }

    /**
     * GLFW Window position Callback 
     * 
     * ------------------------------------------------------------------------------------------------------
     */
    private function patchGlfwSetWindowPosCallback(ExtGenerator $gen) : void
    {
        $functionName = 'glfwSetWindowPosCallback';

        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionImplementationBody(): string
            {
                return GLFWCallbacksAdjustment::createCallbackImpl('phpglfw_callback_windowposcallback_handler', 'windowposcallback', 'glfwSetWindowPosCallback');
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        $func->arguments[1] = ExtArgument::make('callback', ExtType::T_FUNC);

        $func->comment = <<<EOD
This function sets the position callback of the specified window, which is called when the window is moved.

The callback is provided with the screen position of the upper-left corner of the client area of the window.

Example:
```php
glfwSetWindowPosCallback(\$window, function(\$x, \$y) {
    echo "Window moved to: " . \$x . ", " . \$y . PHP_EOL;
});
```

EOD;
        $gen->replaceFunctionByName($func);
    }

    /**
     * GLFW Window size Callback 
     * 
     * ------------------------------------------------------------------------------------------------------
     */
    private function patchGlfwSetWindowSizeCallback(ExtGenerator $gen) : void
    {
        $functionName = 'glfwSetWindowSizeCallback';

        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionImplementationBody(): string
            {
                return GLFWCallbacksAdjustment::createCallbackImpl('phpglfw_callback_windowsizecallback_handler', 'windowsizecallback', 'glfwSetWindowSizeCallback');
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        $func->arguments[1] = ExtArgument::make('callback', ExtType::T_FUNC);

        $func->comment = <<<EOD
This function sets the size callback of the specified window, which is called when the window is resized.

The callback is provided with the size, in screen coordinates, of the client area of the window.

Example:
```php
glfwSetWindowSizeCallback(\$window, function(\$width, \$height) {
    echo "Window resized to: " . \$width . "x" . \$height . PHP_EOL;
});
```

EOD;
        $gen->replaceFunctionByName($func);
    }

    /**
     * GLFW Window close Callback 
     * 
     * ------------------------------------------------------------------------------------------------------
     */
    private function patchGlfwSetWindowCloseCallback(ExtGenerator $gen) : void
    {
        $functionName = 'glfwSetWindowCloseCallback';

        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionImplementationBody(): string
            {
                return GLFWCallbacksAdjustment::createCallbackImpl('phpglfw_callback_windowclosecallback_handler', 'windowclosecallback', 'glfwSetWindowCloseCallback');
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        $func->arguments[1] = ExtArgument::make('callback', ExtType::T_FUNC);

        $func->comment = <<<EOD
This function sets the close callback of the specified window, which is called when the user attempts to close the window, for example by clicking the close widget in the title bar.

The close flag is set before this callback is called, but you can modify it at any time with glfwSetWindowShouldClose.

The close callback is not triggered by glfwDestroyWindow.

Example:
```php
glfwSetWindowCloseCallback(\$window, function() {
    echo "Window close requested" . PHP_EOL;
});
```

EOD;
        $gen->replaceFunctionByName($func);
    }

    /**
     * GLFW Window refresh Callback 
     * 
     * ------------------------------------------------------------------------------------------------------
     */
    private function patchGlfwSetWindowRefreshCallback(ExtGenerator $gen) : void
    {
        $functionName = 'glfwSetWindowRefreshCallback';

        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionImplementationBody(): string
            {
                return GLFWCallbacksAdjustment::createCallbackImpl('phpglfw_callback_windowrefreshcallback_handler', 'windowrefreshcallback', 'glfwSetWindowRefreshCallback');
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        $func->arguments[1] = ExtArgument::make('callback', ExtType::T_FUNC);

        $func->comment = <<<EOD
This function sets the refresh callback of the specified window, which is called when the client area of the window needs to be redrawn, for example if the window has been exposed after having been covered by another window.

On compositing window systems such as Aero, Compiz, Aqua or Wayland, where the window contents are saved off-screen, this callback may be called only very infrequently or never at all.

Example:
```php
glfwSetWindowRefreshCallback(\$window, function() {
    echo "Window needs to be redrawn" . PHP_EOL;
});
```

EOD;
        $gen->replaceFunctionByName($func);
    }

    /**
     * GLFW Window focus Callback 
     * 
     * ------------------------------------------------------------------------------------------------------
     */
    private function patchGlfwSetWindowFocusCallback(ExtGenerator $gen) : void
    {
        $functionName = 'glfwSetWindowFocusCallback';

        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionImplementationBody(): string
            {
                return GLFWCallbacksAdjustment::createCallbackImpl('phpglfw_callback_windowfocuscallback_handler', 'windowfocuscallback', 'glfwSetWindowFocusCallback');
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        $func->arguments[1] = ExtArgument::make('callback', ExtType::T_FUNC);

        $func->comment = <<<EOD
This function sets the focus callback of the specified window, which is called when the window gains or loses input focus.

After the focus callback is called for a window that lost input focus, synthetic key and mouse button release events will be generated for all such that had been pressed.  For more information, see glfwSetKeyCallback and glfwSetMouseButtonCallback.

Example:
```php
glfwSetWindowFocusCallback(\$window, function(\$focused) {
    echo "Window focus changed to: " . \$focused . PHP_EOL;
});
```

EOD;
        $gen->replaceFunctionByName($func);
    }

    /**
     * GLFW Window iconify Callback 
     * 
     * ------------------------------------------------------------------------------------------------------
     */
    private function patchGlfwSetWindowIconifyCallback(ExtGenerator $gen) : void
    {
        $functionName = 'glfwSetWindowIconifyCallback';

        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionImplementationBody(): string
            {
                return GLFWCallbacksAdjustment::createCallbackImpl('phpglfw_callback_windowiconifycallback_handler', 'windowiconifycallback', 'glfwSetWindowIconifyCallback');
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        $func->arguments[1] = ExtArgument::make('callback', ExtType::T_FUNC);

        $func->comment = <<<EOD
This function sets the iconification callback of the specified window, which is called when the window is iconified or restored.

Example:
```php
glfwSetWindowIconifyCallback(\$window, function(\$iconified) {
    echo "Window iconified changed to: " . \$iconified . PHP_EOL;
});
```

EOD;
        $gen->replaceFunctionByName($func);
    }

    /**
     * GLFW Window maximize Callback 
     * 
     * ------------------------------------------------------------------------------------------------------
     */
    private function patchGlfwSetWindowMaximizeCallback(ExtGenerator $gen) : void
    {
        $functionName = 'glfwSetWindowMaximizeCallback';

        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionImplementationBody(): string
            {
                return GLFWCallbacksAdjustment::createCallbackImpl('phpglfw_callback_windowmaximizecallback_handler', 'windowmaximizecallback', 'glfwSetWindowMaximizeCallback');
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        $func->arguments[1] = ExtArgument::make('callback', ExtType::T_FUNC);

        $func->comment = <<<EOD
This function sets the maximize callback of the specified window, which is called when the window is maximized or restored.

Example:
```php
glfwSetWindowMaximizeCallback(\$window, function(\$maximized) {
    echo "Window maximized changed to: " . \$maximized . PHP_EOL;
});
```

EOD;
        $gen->replaceFunctionByName($func);
    }

    /**
     * GLFW Window framebuffer resize Callback 
     * 
     * ------------------------------------------------------------------------------------------------------
     */
    private function patchGlfwSetFramebufferSizeCallback(ExtGenerator $gen) : void
    {
        $functionName = 'glfwSetFramebufferSizeCallback';

        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionImplementationBody(): string
            {
                return GLFWCallbacksAdjustment::createCallbackImpl('phpglfw_callback_windowframebuffersizecallback_handler', 'windowframebuffersizecallback', 'glfwSetFramebufferSizeCallback');
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        $func->arguments[1] = ExtArgument::make('callback', ExtType::T_FUNC);

        $func->comment = <<<EOD
This function sets the framebuffer resize callback of the specified window, which is called when the framebuffer of the specified window is resized.

This callback is provided for convenience.  The equivalent functionality can be achieved by registering a window size callback and querying the framebuffer size within that callback.

Example:
```php
glfwSetFramebufferSizeCallback(\$window, function(\$width, \$height) {
    echo "Framebuffer size changed to: " . \$width . "x" . \$height . PHP_EOL;
});
```

EOD;
        $gen->replaceFunctionByName($func);
    }

    /**
     * GLFW Window content scale Callback 
     * 
     * ------------------------------------------------------------------------------------------------------
     */
    private function patchGlfwSetWindowContentScaleCallback(ExtGenerator $gen) : void
    {
        $functionName = 'glfwSetWindowContentScaleCallback';

        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionImplementationBody(): string
            {
                return GLFWCallbacksAdjustment::createCallbackImpl('phpglfw_callback_windowcontentscalecallback_handler', 'windowcontentscalecallback', 'glfwSetWindowContentScaleCallback');
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        $func->arguments[1] = ExtArgument::make('callback', ExtType::T_FUNC);

        $func->comment = <<<EOD
This function sets the window content scale callback of the specified window, which is called when the content scale of the specified window changes.

This callback is provided for convenience.  The equivalent functionality can be achieved by registering a window size callback and querying the content scale within that callback.

Example:
```php
glfwSetWindowContentScaleCallback(\$window, function(\$xscale, \$yscale) {
    echo "Window content scale changed to: " . \$xscale . "x" . \$yscale . PHP_EOL;
});
```

EOD;
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
        $this->patchGlfwSetWindowPosCallback($gen);
        $this->patchGlfwSetWindowSizeCallback($gen);
        $this->patchGlfwSetWindowCloseCallback($gen);
        $this->patchGlfwSetWindowRefreshCallback($gen);
        $this->patchGlfwSetWindowFocusCallback($gen);
        $this->patchGlfwSetWindowIconifyCallback($gen);
        $this->patchGlfwSetWindowMaximizeCallback($gen);
        $this->patchGlfwSetFramebufferSizeCallback($gen);
        $this->patchGlfwSetWindowContentScaleCallback($gen);


    }
}
