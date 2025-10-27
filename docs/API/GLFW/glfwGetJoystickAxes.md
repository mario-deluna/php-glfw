# glfwGetJoystickAxes
Returns the values of all axes of the specified joystick.

```php
function glfwGetJoystickAxes(int $jid) : array
```

This function returns the values of all axes of the specified joystick.
Each element in the array is a value between -1.0 and 1.0.

If the specified joystick is not present this function will return `NULL`
but will not generate an error. This can be used instead of first calling
[`glfwJoystickPresent`](/API/GLFW/glfwJoystickPresent.html).

arguments

:    1. `int` `$jid` The `joystick` to query.

returns

:    `array` An array of axis values, or `NULL` if the joystick is not
present or
an `error` occurred.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```