# glfwSetWindowIconifyCallback
This function sets the iconification callback of the specified window, which
is called when the window is iconified or restored.

```php
function glfwSetWindowIconifyCallback(\GLFWwindow $window, callable $callback) : void
```

Example:
```php
glfwSetWindowIconifyCallback($window, function($iconified) {
    echo "Window iconified changed to: " . $iconified . PHP_EOL;
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