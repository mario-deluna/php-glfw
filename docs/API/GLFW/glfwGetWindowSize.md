# glfwGetWindowSize
Retrieves the size of the content area of the specified window.

```php
function glfwGetWindowSize(\GLFWwindow $window, int &$width, int &$height) : void
```

This function retrieves the size, in screen coordinates, of the content area
of the specified window. If you wish to retrieve the size of the
framebuffer of the window in pixels, see
[`glfwGetFramebufferSize`](/API/GLFW/glfwGetFramebufferSize.html).

Any or all of the size arguments may be `NULL`. If an error occurs, all
non-`NULL` size arguments will be set to zero.

arguments

:    1. `\GLFWwindow` `$window` The window whose size to retrieve.
    2. `int` `$width` Where to store the width, in screen coordinates, of the
    content area, or `NULL`.
    3. `int` `$height` Where to store the height, in screen coordinates, of the
    content area, or `NULL`.

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