# glfwSetWindowMonitor
Sets the mode, monitor, video mode and placement of a window.

```php
function glfwSetWindowMonitor(\GLFWwindow $window, ?\GLFWmonitor $monitor, int $xpos, int $ypos, int $width, int $height, int $refreshRate) : void
```

This function sets the monitor that the window uses for full screen mode or,
if the monitor is `NULL`, makes it windowed mode.

When setting a monitor, this function updates the width, height and refresh
rate of the desired video mode and switches to the video mode closest to it.
The window position is ignored when setting a monitor.

When the monitor is `NULL`, the position, width and height are used to
place the window content area. The refresh rate is ignored when no monitor
is specified.

If you only wish to update the resolution of a full screen window or the
size of a windowed mode window, see
[`glfwSetWindowSize`](/API/GLFW/glfwSetWindowSize.html).

When a window transitions from full screen to windowed mode, this function
restores any previous window settings such as whether it is decorated,
floating, resizable, has size or aspect ratio limits, etc.

arguments

:    1. `\GLFWwindow` `$window` The window whose monitor, size or video mode to
    set.
    2. `?\GLFWmonitor` `$monitor` The desired monitor, or `NULL` to set windowed
    mode.
    3. `int` `$xpos` The desired x-coordinate of the upper-left corner of the
    content area.
    4. `int` `$ypos` The desired y-coordinate of the upper-left corner of the
    content area.
    5. `int` `$width` The desired with, in screen coordinates, of the content
    area or video mode.
    6. `int` `$height` The desired height, in screen coordinates, of the content
    area or video mode.
    7. `int` `$refreshRate` The desired refresh rate, in Hz, of the video mode,
    or `GLFW_DONT_CARE`.

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