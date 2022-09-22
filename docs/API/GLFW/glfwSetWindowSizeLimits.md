# glfwSetWindowSizeLimits
Sets the size limits of the specified window.

```php
function glfwSetWindowSizeLimits(\GLFWwindow $window, int $minwidth, int $minheight, int $maxwidth, int $maxheight) : void
```

This function sets the size limits of the content area of the specified
window. If the window is full screen, the size limits only take effect
once it is made windowed. If the window is not resizable, this function
does nothing.

The size limits are applied immediately to a windowed mode window and may
cause it to be resized.

The maximum dimensions must be greater than or equal to the minimum
dimensions and all must be greater than or equal to zero.

arguments

:    1. `\GLFWwindow` `$window` The window to set limits for.
    2. `int` `$minwidth` The minimum width, in screen coordinates, of the content
    area, or `GLFW_DONT_CARE`.
    3. `int` `$minheight` The minimum height, in screen coordinates, of the
    content area, or `GLFW_DONT_CARE`.
    4. `int` `$maxwidth` The maximum width, in screen coordinates, of the content
    area, or `GLFW_DONT_CARE`.
    5. `int` `$maxheight` The maximum height, in screen coordinates, of the
    content area, or `GLFW_DONT_CARE`.

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