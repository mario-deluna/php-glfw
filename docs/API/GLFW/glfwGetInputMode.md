# glfwGetInputMode
Returns the value of an input option for the specified window.

```php
function glfwGetInputMode(\GLFWwindow $window, int $mode) : int
```

This function returns the value of an input option for the specified window.
The mode must be one of `GLFW_CURSOR`, `GLFW_STICKY_KEYS`,
`GLFW_STICKY_MOUSE_BUTTONS`, `GLFW_LOCK_KEY_MODS` or
`GLFW_RAW_MOUSE_MOTION`.

arguments

:    1. `\GLFWwindow` `$window` The window to query.
    2. `int` `$mode` One of `GLFW_CURSOR`, `GLFW_STICKY_KEYS`,
    `GLFW_STICKY_MOUSE_BUTTONS`, `GLFW_LOCK_KEY_MODS` or
    `GLFW_RAW_MOUSE_MOTION`.

returns

:    `int` 

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```