# glfwSetWindowSize
Sets the size of the content area of the specified window.

```php
function glfwSetWindowSize(\GLFWwindow $window, int $width, int $height) : void
```

This function sets the size, in screen coordinates, of the content area of
the specified window.

For full screen windows, this function updates the resolution of its desired
video mode and switches to the video mode closest to it, without affecting
the window's context. As the context is unaffected, the bit depths of the
framebuffer remain unchanged.

If you wish to update the refresh rate of the desired video mode in addition
to its resolution, see
[`glfwSetWindowMonitor`](/API/GLFW/glfwSetWindowMonitor.html).

The window manager may put limits on what sizes are allowed. GLFW cannot
and should not override these limits.

arguments

:    1. `\GLFWwindow` `$window` The window to resize.
    2. `int` `$width` The desired width, in screen coordinates, of the window
    content area.
    3. `int` `$height` The desired height, in screen coordinates, of the window
    content area.

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