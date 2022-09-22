# glfwGetWindowMonitor
Returns the monitor that the window uses for full screen mode.

```php
function glfwGetWindowMonitor(\GLFWwindow $window) : \GLFWmonitor
```

This function returns the handle of the monitor that the specified window is
in full screen on.

arguments

:    1. `\GLFWwindow` `$window` The window to query.

returns

:    `\GLFWmonitor` The monitor, or `NULL` if the window is in windowed mode
or an
`error` occurred.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```