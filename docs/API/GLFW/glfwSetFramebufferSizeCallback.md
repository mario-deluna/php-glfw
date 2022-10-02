# glfwSetFramebufferSizeCallback
This function sets the framebuffer resize callback of the specified window,
which is called when the framebuffer of the specified window is resized.

```php
function glfwSetFramebufferSizeCallback(\GLFWwindow $window, callable $callback) : void
```

This callback is provided for convenience.  The equivalent functionality can
be achieved by registering a window size callback and querying the
framebuffer size within that callback.

Example:
```php
glfwSetFramebufferSizeCallback($window, function($width, $height) {
    echo "Framebuffer size changed to: " . $width . "x" . $height . PHP_EOL;
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