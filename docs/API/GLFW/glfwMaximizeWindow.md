# glfwMaximizeWindow
Maximizes the specified window.

```php
function glfwMaximizeWindow(\GLFWwindow $window) : void
```

This function maximizes the specified window if it was previously not
maximized. If the window is already maximized, this function does nothing.

If the specified window is a full screen window, this function does nothing.

arguments

:    1. `\GLFWwindow` `$window` The window to maximize.

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