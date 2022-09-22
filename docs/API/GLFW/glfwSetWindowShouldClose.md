# glfwSetWindowShouldClose
Sets the close flag of the specified window.

```php
function glfwSetWindowShouldClose(\GLFWwindow $window, int $value) : void
```

This function sets the value of the close flag of the specified window.
This can be used to override the user's attempt to close the window, or
to signal that it should be closed.

arguments

:    1. `\GLFWwindow` `$window` The window whose flag to change.
    2. `int` `$value` The new value.

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