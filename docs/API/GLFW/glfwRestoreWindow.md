# glfwRestoreWindow
Restores the specified window.

```php
function glfwRestoreWindow(\GLFWwindow $window) : void
```

This function restores the specified window if it was previously iconified
(minimized) or maximized. If the window is already restored, this function
does nothing.

If the specified window is a full screen window, the resolution chosen for
the window is restored on the selected monitor.

arguments

:    1. `\GLFWwindow` `$window` The window to restore.

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