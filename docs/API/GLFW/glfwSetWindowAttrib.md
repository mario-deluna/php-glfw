# glfwSetWindowAttrib
Sets an attribute of the specified window.

```php
function glfwSetWindowAttrib(\GLFWwindow $window, int $attrib, int $value) : void
```

This function sets the value of an attribute of the specified window.

The supported attributes are `GLFW_DECORATED`,
`GLFW_RESIZABLE`,
`GLFW_FLOATING`,
`GLFW_AUTO_ICONIFY` and
`GLFW_FOCUS_ON_SHOW`.

Some of these attributes are ignored for full screen windows. The new
value will take effect if the window is later made windowed.

Some of these attributes are ignored for windowed mode windows. The new
value will take effect if the window is later made full screen.

arguments

:    1. `\GLFWwindow` `$window` The window to set the attribute for.
    2. `int` `$attrib` A supported window attribute.
    3. `int` `$value` `GLFW_TRUE` or `GLFW_FALSE`.

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