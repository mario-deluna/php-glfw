# glfwSetWindowCloseCallback
This function sets the close callback of the specified window, which is
called when the user attempts to close the window, for example by clicking
the close widget in the title bar.

```php
function glfwSetWindowCloseCallback(\GLFWwindow $window, callable $callback) : void
```

The close flag is set before this callback is called, but you can modify it
at any time with glfwSetWindowShouldClose.

The close callback is not triggered by glfwDestroyWindow.

Example:
```php
glfwSetWindowCloseCallback($window, function() {
    echo "Window close requested" . PHP_EOL;
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