# glfwSetWindowRefreshCallback
This function sets the refresh callback of the specified window, which is
called when the client area of the window needs to be redrawn, for example if
the window has been exposed after having been covered by another window.

```php
function glfwSetWindowRefreshCallback(\GLFWwindow $window, callable $callback) : void
```

On compositing window systems such as Aero, Compiz, Aqua or Wayland, where
the window contents are saved off-screen, this callback may be called only
very infrequently or never at all.

Example:
```php
glfwSetWindowRefreshCallback($window, function() {
    echo "Window needs to be redrawn" . PHP_EOL;
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