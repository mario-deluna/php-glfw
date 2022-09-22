# glfwGetPrimaryMonitor
Returns the primary monitor.

```php
function glfwGetPrimaryMonitor() : \GLFWmonitor
```

This function returns the primary monitor. This is usually the monitor
where elements like the task bar or global menu bar are located.

returns

:    `\GLFWmonitor` The primary monitor, or `NULL` if no monitors were found
or if an
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