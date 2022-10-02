# glfwSetWindowContentScaleCallback
This function sets the window content scale callback of the specified window,
which is called when the content scale of the specified window changes.

```php
function glfwSetWindowContentScaleCallback(\GLFWwindow $window, callable $callback) : void
```

This callback is provided for convenience.  The equivalent functionality can
be achieved by registering a window size callback and querying the content
scale within that callback.

Example:
```php
glfwSetWindowContentScaleCallback($window, function($xscale, $yscale) {
    echo "Window content scale changed to: " . $xscale . "x" . $yscale .
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