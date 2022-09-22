# glfwGetWindowFrameSize
Retrieves the size of the frame of the window.

```php
function glfwGetWindowFrameSize(\GLFWwindow $window, int &$left, int &$top, int &$right, int &$bottom) : void
```

This function retrieves the size, in screen coordinates, of each edge of the
frame of the specified window. This size includes the title bar, if the
window has one. The size of the frame may vary depending on the
`window-related hints` used to create it.

Because this function retrieves the size of each window frame edge and not
the offset along a particular coordinate axis, the retrieved values will
always be zero or positive.

Any or all of the size arguments may be `NULL`. If an error occurs, all
non-`NULL` size arguments will be set to zero.

arguments

:    1. `\GLFWwindow` `$window` The window whose frame size to query.
    2. `int` `$left` Where to store the size, in screen coordinates, of the left
    edge of the window frame, or `NULL`.
    3. `int` `$top` Where to store the size, in screen coordinates, of the top
    edge of the window frame, or `NULL`.
    4. `int` `$right` Where to store the size, in screen coordinates, of the
    right edge of the window frame, or `NULL`.
    5. `int` `$bottom` Where to store the size, in screen coordinates, of the
    bottom edge of the window frame, or `NULL`.

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