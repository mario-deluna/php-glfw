# glfwSetCharCallback
This function sets the character callback of the specified window, which is
called when a Unicode character is input.

```php
function glfwSetCharCallback(\GLFWwindow $window, callable $callback) : void
```

Example:
```php
glfwSetCharCallback($window, function($codepoint) {
    echo "Character: " . mb_chr($codepoint) . PHP_EOL;
});
```

The character callback is intended for Unicode text input. As it deals with
characters, it is keyboard layout dependent, whereas the key callback is not.
Characters do not map 1:1 to physical keys, as a key may produce zero, one or
more characters. If you want to know whether a specific physical key was
pressed or released, see the key callback instead.

The character callback behaves as system text input normally does and will
not be called if modifier keys are held down that would prevent normal text
input on that platform, for example a Super (Command) key on macOS or Alt key
on Windows.

arguments

:    1. `\GLFWwindow` `$window` The window whose callback to set.
    2. `callable` `$callback` 

returns

:    `void` 

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```