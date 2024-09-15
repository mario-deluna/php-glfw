# glfwGetVideoMode
Returns the current mode of the specified monitor.

```php
function glfwGetVideoMode(\GLFWmonitor $monitor) : \GLFWvidmode
```

This function returns the current video mode of the specified monitor. If
you have created a full screen window for that monitor, the return value
will depend on whether that window is iconified.

arguments

:    1. `\GLFWmonitor` `$monitor` The monitor to query.

returns

:    `\GLFWvidmode` The current mode of the monitor, or `NULL` if an
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