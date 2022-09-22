# glfwSetWindowOpacity
Sets the opacity of the whole window.

```php
function glfwSetWindowOpacity(\GLFWwindow $window, float $opacity) : void
```

This function sets the opacity of the window, including any decorations.

The opacity (or alpha) value is a positive finite number between zero and
one, where zero is fully transparent and one is fully opaque.

The initial opacity value for newly created windows is one.

A window created with framebuffer transparency may not use whole window
transparency. The results of doing this are undefined.

arguments

:    1. `\GLFWwindow` `$window` The window to set the opacity for.
    2. `float` `$opacity` The desired opacity of the specified window.

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