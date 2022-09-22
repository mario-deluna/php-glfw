# glfwGetMonitorPhysicalSize
Returns the physical size of the monitor.

```php
function glfwGetMonitorPhysicalSize(\GLFWmonitor $monitor, int &$widthMM, int &$heightMM) : void
```

This function returns the size, in millimetres, of the display area of the
specified monitor.

Some systems do not provide accurate monitor size information, either
because the monitor
[EDID](https://en.wikipedia.org/wiki/Extended_display_identification_data)
data is incorrect or because the driver does not report it accurately.

Any or all of the size arguments may be `NULL`. If an error occurs, all
non-`NULL` size arguments will be set to zero.

arguments

:    1. `\GLFWmonitor` `$monitor` The monitor to query.
    2. `int` `$widthMM` Where to store the width, in millimetres, of the
    monitor's display area, or `NULL`.
    3. `int` `$heightMM` Where to store the height, in millimetres, of the
    monitor's display area, or `NULL`.

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