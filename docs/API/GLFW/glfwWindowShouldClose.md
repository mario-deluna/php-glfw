# glfwWindowShouldClose
Checks the close flag of the specified window.

```php
function glfwWindowShouldClose(\GLFWwindow $window) : int
```

This function returns the value of the close flag of the specified window.

arguments

:    1. `\GLFWwindow` `$window` The window to query.

returns

:    `int` The value of the close flag.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```