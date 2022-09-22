# glfwGetWindowOpacity
Returns the opacity of the whole window.

```php
function glfwGetWindowOpacity(\GLFWwindow $window) : float
```

This function returns the opacity of the window, including any decorations.

The opacity (or alpha) value is a positive finite number between zero and
one, where zero is fully transparent and one is fully opaque. If the system
does not support whole window transparency, this function always returns one.

The initial opacity value for newly created windows is one.

arguments

:    1. `\GLFWwindow` `$window` The window to query.

returns

:    `float` The opacity value of the specified window.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```