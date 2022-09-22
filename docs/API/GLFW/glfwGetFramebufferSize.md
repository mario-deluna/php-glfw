# glfwGetFramebufferSize
Retrieves the size of the framebuffer of the specified window.

```php
function glfwGetFramebufferSize(\GLFWwindow $window, int &$width, int &$height) : void
```

This function retrieves the size, in pixels, of the framebuffer of the
specified window. If you wish to retrieve the size of the window in screen
coordinates, see [`glfwGetWindowSize`](/API/GLFW/glfwGetWindowSize.html).

Any or all of the size arguments may be `NULL`. If an error occurs, all
non-`NULL` size arguments will be set to zero.

arguments

:    1. `\GLFWwindow` `$window` The window whose framebuffer to query.
    2. `int` `$width` Where to store the width, in pixels, of the framebuffer,
    or `NULL`.
    3. `int` `$height` Where to store the height, in pixels, of the framebuffer,
    or `NULL`.

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