# glfwSetDropCallback
This function sets the file drop callback of the specified window, which is
called when one or more dragged files are dropped on the window.

```php
function glfwSetDropCallback(\GLFWwindow $window, callable $callback) : void
```

Example:
```php
glfwSetDropCallback($window, function($paths) {
    echo "Dropped files:" . PHP_EOL;
    foreach ($paths as $path) {
        echo "  " . $path . PHP_EOL;
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