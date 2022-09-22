# glfwJoystickPresent
Returns whether the specified joystick is present.

```php
function glfwJoystickPresent(int $jid) : int
```

This function returns whether the specified joystick is present.

There is no need to call this function before other functions that accept
a joystick ID, as they all check for presence before performing any other
work.

arguments

:    1. `int` `$jid` The `joystick` to query.

returns

:    `int` `GLFW_TRUE` if the joystick is present, or `GLFW_FALSE`
otherwise.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```