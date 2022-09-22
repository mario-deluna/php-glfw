# glfwGetCursorPos
Retrieves the position of the cursor relative to the content area of
the window.

```php
function glfwGetCursorPos(\GLFWwindow $window, float &$xpos, float &$ypos) : void
```

This function returns the position of the cursor, in screen coordinates,
relative to the upper-left corner of the content area of the specified
window.

If the cursor is disabled (with `GLFW_CURSOR_DISABLED`) then the cursor
position is unbounded and limited only by the minimum and maximum values of
a `double`.

The coordinate can be converted to their integer equivalents with the
`floor` function. Casting directly to an integer type works for positive
coordinates, but fails for negative ones.

Any or all of the position arguments may be `NULL`. If an error occurs, all
non-`NULL` position arguments will be set to zero.

arguments

:    1. `\GLFWwindow` `$window` The desired window.
    2. `float` `$xpos` Where to store the cursor x-coordinate, relative to the
    left edge of the content area, or `NULL`.
    3. `float` `$ypos` Where to store the cursor y-coordinate, relative to the
    to
    top edge of the content area, or `NULL`.

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