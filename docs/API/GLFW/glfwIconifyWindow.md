# glfwIconifyWindow
Iconifies the specified window.

```php
function glfwIconifyWindow(\GLFWwindow $window) : void
```

This function iconifies (minimizes) the specified window if it was
previously restored. If the window is already iconified, this function does
nothing.

If the specified window is a full screen window, GLFW restores the original
video mode of the monitor. The window's desired video mode is set again
when the window is restored.

arguments

:    1. `\GLFWwindow` `$window` The window to iconify.

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