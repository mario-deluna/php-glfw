# glfwRequestWindowAttention
Requests user attention to the specified window.

```php
function glfwRequestWindowAttention(\GLFWwindow $window) : void
```

This function requests user attention to the specified window. On
platforms where this is not supported, attention is requested to the
application as a whole.

Once the user has given attention, usually by focusing the window or
application, the system will end the request automatically.

arguments

:    1. `\GLFWwindow` `$window` The window to request attention to.

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