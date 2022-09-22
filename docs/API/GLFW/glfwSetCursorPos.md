# glfwSetCursorPos
Sets the position of the cursor, relative to the content area of the
window.

```php
function glfwSetCursorPos(\GLFWwindow $window, float $xpos, float $ypos) : void
```

This function sets the position, in screen coordinates, of the cursor
relative to the upper-left corner of the content area of the specified
window. The window must have input focus. If the window does not have
input focus when this function is called, it fails silently.

__Do not use this function__ to implement things like camera controls. GLFW
already provides the `GLFW_CURSOR_DISABLED` cursor mode that hides the
cursor, transparently re-centers it and provides unconstrained cursor
motion. See [`glfwSetInputMode`](/API/GLFW/glfwSetInputMode.html) for more
information.

If the cursor mode is `GLFW_CURSOR_DISABLED` then the cursor position is
unconstrained and limited only by the minimum and maximum values of
a `double`.

arguments

:    1. `\GLFWwindow` `$window` The desired window.
    2. `float` `$xpos` The desired x-coordinate, relative to the left edge of the
    content area.
    3. `float` `$ypos` The desired y-coordinate, relative to the top edge of the
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