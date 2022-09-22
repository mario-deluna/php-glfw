# glfwGetWindowPos
Retrieves the position of the content area of the specified window.

```php
function glfwGetWindowPos(\GLFWwindow $window, int &$xpos, int &$ypos) : void
```

This function retrieves the position, in screen coordinates, of the
upper-left corner of the content area of the specified window.

Any or all of the position arguments may be `NULL`. If an error occurs, all
non-`NULL` position arguments will be set to zero.

arguments

:    1. `\GLFWwindow` `$window` The window to query.
    2. `int` `$xpos` Where to store the x-coordinate of the upper-left corner of
    the content area, or `NULL`.
    3. `int` `$ypos` Where to store the y-coordinate of the upper-left corner of
    the content area, or `NULL`.

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