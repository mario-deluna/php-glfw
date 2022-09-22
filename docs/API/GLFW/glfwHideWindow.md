# glfwHideWindow
Hides the specified window.

```php
function glfwHideWindow(\GLFWwindow $window) : void
```

This function hides the specified window if it was previously visible. If
the window is already hidden or is in full screen mode, this function does
nothing.

arguments

:    1. `\GLFWwindow` `$window` The window to hide.

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