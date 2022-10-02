# glfwSetCursorPosCallback
This function sets the cursor position callback of the specified window,
which is called when the cursor is moved.

```php
function glfwSetCursorPosCallback(\GLFWwindow $window, callable $callback) : void
```

The callback is provided with the position, in screen coordinates, relative
to the upper-left corner of the client area of the window.

Example:
```php
glfwSetCursorPosCallback($window, function($xpos, $ypos) {
    echo "Cursor position: " . $xpos . ", " . $ypos . PHP_EOL;
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