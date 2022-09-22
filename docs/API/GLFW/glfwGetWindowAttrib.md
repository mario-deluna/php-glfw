# glfwGetWindowAttrib
Returns an attribute of the specified window.

```php
function glfwGetWindowAttrib(\GLFWwindow $window, int $attrib) : int
```

This function returns the value of an attribute of the specified window or
its OpenGL or OpenGL ES context.

arguments

:    1. `\GLFWwindow` `$window` The window to query.
    2. `int` `$attrib` The `window attribute` whose value to
    return.

returns

:    `int` The value of the attribute, or zero if an
`error` occurred.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```