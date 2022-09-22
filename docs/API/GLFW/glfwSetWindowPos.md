# glfwSetWindowPos
Sets the position of the content area of the specified window.

```php
function glfwSetWindowPos(\GLFWwindow $window, int $xpos, int $ypos) : void
```

This function sets the position, in screen coordinates, of the upper-left
corner of the content area of the specified windowed mode window. If the
window is a full screen window, this function does nothing.

__Do not use this function__ to move an already visible window unless you
have very good reasons for doing so, as it will confuse and annoy the user.

The window manager may put limits on what positions are allowed. GLFW
cannot and should not override these limits.

arguments

:    1. `\GLFWwindow` `$window` The window to query.
    2. `int` `$xpos` The x-coordinate of the upper-left corner of the content
    area.
    3. `int` `$ypos` The y-coordinate of the upper-left corner of the content
    area.

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