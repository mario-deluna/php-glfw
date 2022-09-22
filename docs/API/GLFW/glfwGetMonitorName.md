# glfwGetMonitorName
Returns the name of the specified monitor.

```php
function glfwGetMonitorName(\GLFWmonitor $monitor) : string
```

This function returns a human-readable name, encoded as UTF-8, of the
specified monitor. The name typically reflects the make and model of the
monitor and is not guaranteed to be unique among the connected monitors.

arguments

:    1. `\GLFWmonitor` `$monitor` The monitor to query.

returns

:    `string` The UTF-8 encoded name of the monitor, or `NULL` if an
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