# glfwSetWindowSizeCallback
This function sets the size callback of the specified window, which is called
when the window is resized.

```php
function glfwSetWindowSizeCallback(\GLFWwindow $window, callable $callback) : void
```

The callback is provided with the size, in screen coordinates, of the client
area of the window.

Example:
```php
glfwSetWindowSizeCallback($window, function($width, $height) {
    echo "Window resized to: " . $width . "x" . $height . PHP_EOL;
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