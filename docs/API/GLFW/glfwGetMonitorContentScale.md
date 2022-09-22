# glfwGetMonitorContentScale
Retrieves the content scale for the specified monitor.

```php
function glfwGetMonitorContentScale(\GLFWmonitor $monitor, float &$xscale, float &$yscale) : void
```

This function retrieves the content scale for the specified monitor. The
content scale is the ratio between the current DPI and the platform's
default DPI. This is especially important for text and any UI elements. If
the pixel dimensions of your UI scaled by this look appropriate on your
machine then it should appear at a reasonable size on other machines
regardless of their DPI and scaling settings. This relies on the system DPI
and scaling settings being somewhat correct.

The content scale may depend on both the monitor resolution and pixel
density and on user settings. It may be very different from the raw DPI
calculated from the physical size and current resolution.

arguments

:    1. `\GLFWmonitor` `$monitor` The monitor to query.
    2. `float` `$xscale` Where to store the x-axis content scale, or `NULL`.
    3. `float` `$yscale` Where to store the y-axis content scale, or `NULL`.

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