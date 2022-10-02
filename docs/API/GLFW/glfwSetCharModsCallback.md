# glfwSetCharModsCallback
This function sets the character with modifiers callback of the specified
window, which is called when a Unicode character is input regardless of what
modifier keys are used.

```php
function glfwSetCharModsCallback(\GLFWwindow $window, callable $callback) : void
```

The character with modifiers callback is intended for implementing custom
Unicode character input. For regular Unicode text input, see the character
callback.

Example:
```php
glfwSetCharModsCallback($window, function($codepoint, $mods) {
    echo "Character: " . mb_chr($codepoint) . ' with mods: ' . $mods .
PHP_EOL;
});
```

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