# glfwShowWindow
Makes the specified window visible.

```php
function glfwShowWindow(\GLFWwindow $window) : void
```

This function makes the specified window visible if it was previously
hidden. If the window is already visible or is in full screen mode, this
function does nothing.

By default, windowed mode windows are focused when shown
Set the `GLFW_FOCUS_ON_SHOW` window hint
to change this behavior for all newly created windows, or change the
behavior for an existing window with
[`glfwSetWindowAttrib`](/API/GLFW/glfwSetWindowAttrib.html).

arguments

:    1. `\GLFWwindow` `$window` The window to make visible.

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