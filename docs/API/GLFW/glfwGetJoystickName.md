# glfwGetJoystickName
Returns the name of the specified joystick.

```php
function glfwGetJoystickName(int $jid) : string
```

This function returns the name, encoded as UTF-8, of the specified joystick.
The returned string is allocated and freed by GLFW. You should not free it
yourself.

If the specified joystick is not present this function will return `NULL`
but will not generate an error. This can be used instead of first calling
[`glfwJoystickPresent`](/API/GLFW/glfwJoystickPresent.html).

arguments

:    1. `int` `$jid` The `joystick` to query.

returns

:    `string` The UTF-8 encoded name of the joystick, or `NULL` if the
joystick
is not present or an `error` occurred.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```