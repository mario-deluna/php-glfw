# glfwGetKey
Returns the last reported state of a keyboard key for the specified
window.

```php
function glfwGetKey(\GLFWwindow $window, int $key) : int
```

This function returns the last state reported for the specified key to the
specified window. The returned state is one of `GLFW_PRESS` or
`GLFW_RELEASE`. The higher-level action `GLFW_REPEAT` is only reported to
the key callback.

If the `GLFW_STICKY_KEYS` input mode is enabled, this function returns
`GLFW_PRESS` the first time you call it for a key that was pressed, even if
that key has already been released.

The key functions deal with physical keys, with `key tokens`
named after their use on the standard US keyboard layout. If you want to
input text, use the Unicode character callback instead.

The `modifier key bit masks` are not key tokens and cannot be
used with this function.

__Do not use this function__ to implement `text input`.

arguments

:    1. `\GLFWwindow` `$window` The desired window.
    2. `int` `$key` The desired `keyboard key`. `GLFW_KEY_UNKNOWN` is
    not a valid key for this function.

returns

:    `int` One of `GLFW_PRESS` or `GLFW_RELEASE`.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```