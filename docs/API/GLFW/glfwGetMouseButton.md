# glfwGetMouseButton
Returns the last reported state of a mouse button for the specified
window.

```php
function glfwGetMouseButton(\GLFWwindow $window, int $button) : int
```

This function returns the last state reported for the specified mouse button
to the specified window. The returned state is one of `GLFW_PRESS` or
`GLFW_RELEASE`.

If the `GLFW_STICKY_MOUSE_BUTTONS` input mode is enabled, this function
returns `GLFW_PRESS` the first time you call it for a mouse button that was
pressed, even if that mouse button has already been released.

arguments

:    1. `\GLFWwindow` `$window` The desired window.
    2. `int` `$button` The desired `mouse button`.

returns

:    `int` One of `GLFW_PRESS` or `GLFW_RELEASE`.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```