# glfwSetCursor
Sets the cursor for the window.

```php
function glfwSetCursor(\GLFWwindow $window, \GLFWcursor $cursor) : void
```

This function sets the cursor image to be used when the cursor is over the
content area of the specified window. The set cursor will only be visible
when the `cursor mode` of the window is
`GLFW_CURSOR_NORMAL`.

On some platforms, the set cursor may not be visible unless the window also
has input focus.

arguments

:    1. `\GLFWwindow` `$window` The window to set the cursor for.
    2. `\GLFWcursor` `$cursor` The cursor to set, or `NULL` to switch back to the
    default
    arrow cursor.

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