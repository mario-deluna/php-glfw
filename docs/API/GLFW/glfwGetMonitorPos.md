# glfwGetMonitorPos
Returns the position of the monitor's viewport on the virtual screen.

```php
function glfwGetMonitorPos(\GLFWmonitor $monitor, int &$xpos, int &$ypos) : void
```

This function returns the position, in screen coordinates, of the upper-left
corner of the specified monitor.

Any or all of the position arguments may be `NULL`. If an error occurs, all
non-`NULL` position arguments will be set to zero.

arguments

:    1. `\GLFWmonitor` `$monitor` The monitor to query.
    2. `int` `$xpos` Where to store the monitor x-coordinate, or `NULL`.
    3. `int` `$ypos` Where to store the monitor y-coordinate, or `NULL`.

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