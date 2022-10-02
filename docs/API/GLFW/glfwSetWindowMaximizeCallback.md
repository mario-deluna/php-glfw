# glfwSetWindowMaximizeCallback
This function sets the maximize callback of the specified window, which is
called when the window is maximized or restored.

```php
function glfwSetWindowMaximizeCallback(\GLFWwindow $window, callable $callback) : void
```

Example:
```php
glfwSetWindowMaximizeCallback($window, function($maximized) {
    echo "Window maximized changed to: " . $maximized . PHP_EOL;
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