# glfwJoystickIsGamepad
Returns whether the specified joystick has a gamepad mapping.

```php
function glfwJoystickIsGamepad(int $jid) : int
```

This function returns whether the specified joystick is both present and has
a gamepad mapping.

If the specified joystick is present but does not have a gamepad mapping
this function will return `GLFW_FALSE` but will not generate an error. Call
[`glfwJoystickPresent`](/API/GLFW/glfwJoystickPresent.html) to check if a
joystick is present regardless of
whether it has a mapping.

arguments

:    1. `int` `$jid` The `joystick` to query.

returns

:    `int` `GLFW_TRUE` if a joystick is both present and has a gamepad
mapping,
or `GLFW_FALSE` otherwise.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```