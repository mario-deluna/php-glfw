# glfwSetCursorEnterCallback
This function sets the cursor boundary crossing callback of the specified
window, which is called when the cursor enters or leaves the client area of
the window.

```php
function glfwSetCursorEnterCallback(\GLFWwindow $window, callable $callback) : void
```

Example:
```php
glfwSetCursorEnterCallback($window, function($entered) {
    if ($entered) {
        echo "Cursor entered window" . PHP_EOL;
    } else {
        echo "Cursor left window" . PHP_EOL;
    }
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