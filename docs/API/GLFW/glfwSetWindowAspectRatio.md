# glfwSetWindowAspectRatio
Sets the aspect ratio of the specified window.

```php
function glfwSetWindowAspectRatio(\GLFWwindow $window, int $numer, int $denom) : void
```

This function sets the required aspect ratio of the content area of the
specified window. If the window is full screen, the aspect ratio only takes
effect once it is made windowed. If the window is not resizable, this
function does nothing.

The aspect ratio is specified as a numerator and a denominator and both
values must be greater than zero. For example, the common 16:9 aspect ratio
is specified as 16 and 9, respectively.

If the numerator and denominator is set to `GLFW_DONT_CARE` then the aspect
ratio limit is disabled.

The aspect ratio is applied immediately to a windowed mode window and may
cause it to be resized.

arguments

:    1. `\GLFWwindow` `$window` The window to set limits for.
    2. `int` `$numer` The numerator of the desired aspect ratio, or
    `GLFW_DONT_CARE`.
    3. `int` `$denom` The denominator of the desired aspect ratio, or
    `GLFW_DONT_CARE`.

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