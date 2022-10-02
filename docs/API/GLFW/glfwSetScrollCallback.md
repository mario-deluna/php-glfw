# glfwSetScrollCallback
This function sets the scroll callback of the specified window, which is
called when a scrolling device is used, such as a mouse wheel or scrolling
area of a touchpad.

```php
function glfwSetScrollCallback(\GLFWwindow $window, callable $callback) : void
```

Example:
```php
glfwSetScrollCallback($window, function($xoffset, $yoffset) {
    echo "Scroll offset: " . $xoffset . ", " . $yoffset . PHP_EOL;
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