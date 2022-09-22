# glfwFocusWindow
Brings the specified window to front and sets input focus.

```php
function glfwFocusWindow(\GLFWwindow $window) : void
```

This function brings the specified window to front and sets input focus.
The window should already be visible and not iconified.

By default, both windowed and full screen mode windows are focused when
initially created. Set the `GLFW_FOCUSED` to
disable this behavior.

Also by default, windowed mode windows are focused when shown
with [`glfwShowWindow`](/API/GLFW/glfwShowWindow.html). Set the
`GLFW_FOCUS_ON_SHOW` to disable this behavior.

__Do not use this function__ to steal focus from other applications unless
you are certain that is what the user wants. Focus stealing can be
extremely disruptive.

For a less disruptive way of getting the user's attention, see
`attention requests`.

arguments

:    1. `\GLFWwindow` `$window` The window to give input focus.

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