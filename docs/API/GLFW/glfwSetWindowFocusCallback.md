# glfwSetWindowFocusCallback
This function sets the focus callback of the specified window, which is
called when the window gains or loses input focus.

```php
function glfwSetWindowFocusCallback(\GLFWwindow $window, callable $callback) : void
```

After the focus callback is called for a window that lost input focus,
synthetic key and mouse button release events will be generated for all such
that had been pressed.  For more information, see glfwSetKeyCallback and
glfwSetMouseButtonCallback.

Example:
```php
glfwSetWindowFocusCallback($window, function($focused) {
    echo "Window focus changed to: " . $focused . PHP_EOL;
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