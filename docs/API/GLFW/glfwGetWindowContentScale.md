# glfwGetWindowContentScale
Retrieves the content scale for the specified window.

```php
function glfwGetWindowContentScale(\GLFWwindow $window, float &$xscale, float &$yscale) : void
```

This function retrieves the content scale for the specified window. The
content scale is the ratio between the current DPI and the platform's
default DPI. This is especially important for text and any UI elements. If
the pixel dimensions of your UI scaled by this look appropriate on your
machine then it should appear at a reasonable size on other machines
regardless of their DPI and scaling settings. This relies on the system DPI
and scaling settings being somewhat correct.

On systems where each monitors can have its own content scale, the window
content scale will depend on which monitor the system considers the window
to be on.

arguments

:    1. `\GLFWwindow` `$window` The window to query.
    2. `float` `$xscale` Where to store the x-axis content scale, or `NULL`.
    3. `float` `$yscale` Where to store the y-axis content scale, or `NULL`.

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