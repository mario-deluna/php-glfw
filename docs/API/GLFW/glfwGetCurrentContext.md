# glfwGetCurrentContext
Returns the window whose context is current on the calling thread.

```php
function glfwGetCurrentContext() : \GLFWwindow
```

This function returns the window whose OpenGL or OpenGL ES context is
current on the calling thread.

returns

:    `\GLFWwindow` The window whose context is current, or `NULL` if no
window's
context is current.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```