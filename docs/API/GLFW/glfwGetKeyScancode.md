# glfwGetKeyScancode
Returns the platform-specific scancode of the specified key.

```php
function glfwGetKeyScancode(int $key) : int
```

This function returns the platform-specific scancode of the specified key.

If the key is `GLFW_KEY_UNKNOWN` or does not exist on the keyboard this
method will return `-1`.

arguments

:    1. `int` `$key` Any `named key`.

returns

:    `int` The platform-specific scancode for the key, or `-1` if an
`error` occurred.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```