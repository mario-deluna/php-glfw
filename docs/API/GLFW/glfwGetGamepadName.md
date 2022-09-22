# glfwGetGamepadName
Returns the human-readable gamepad name for the specified joystick.

```php
function glfwGetGamepadName(int $jid) : string
```

This function returns the human-readable name of the gamepad from the
gamepad mapping assigned to the specified joystick.

If the specified joystick is not present or does not have a gamepad mapping
this function will return `NULL` but will not generate an error. Call
[`glfwJoystickPresent`](/API/GLFW/glfwJoystickPresent.html) to check whether
it is present regardless of
whether it has a mapping.

arguments

:    1. `int` `$jid` The `joystick` to query.

returns

:    `string` The UTF-8 encoded name of the gamepad, or `NULL` if the
joystick is not present, does not have a mapping or an
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