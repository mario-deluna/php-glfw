# glfwDestroyWindow
Destroys the specified window and its context.

```php
function glfwDestroyWindow(\GLFWwindow $window) : void
```

This function destroys the specified window and its context. On calling
this function, no further callbacks will be called for that window.

If the context of the specified window is current on the main thread, it is
detached before being destroyed.

arguments

:    1. `\GLFWwindow` `$window` The window to destroy.

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