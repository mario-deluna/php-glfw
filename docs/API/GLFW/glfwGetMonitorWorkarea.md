# glfwGetMonitorWorkarea
Retrieves the work area of the monitor.

```php
function glfwGetMonitorWorkarea(\GLFWmonitor $monitor, int &$xpos, int &$ypos, int &$width, int &$height) : void
```

This function returns the position, in screen coordinates, of the upper-left
corner of the work area of the specified monitor along with the work area
size in screen coordinates. The work area is defined as the area of the
monitor not occluded by the operating system task bar where present. If no
task bar exists then the work area is the monitor resolution in screen
coordinates.

Any or all of the position and size arguments may be `NULL`. If an error
occurs, all non-`NULL` position and size arguments will be set to zero.

arguments

:    1. `\GLFWmonitor` `$monitor` The monitor to query.
    2. `int` `$xpos` Where to store the monitor x-coordinate, or `NULL`.
    3. `int` `$ypos` Where to store the monitor y-coordinate, or `NULL`.
    4. `int` `$width` Where to store the monitor width, or `NULL`.
    5. `int` `$height` Where to store the monitor height, or `NULL`.

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