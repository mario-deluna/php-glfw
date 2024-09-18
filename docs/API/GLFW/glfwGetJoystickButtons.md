# glfwGetJoystickButtons
Returns the state of all buttons of the specified joystick.

```php
function glfwGetJoystickButtons(int $jid) : array
```

This function returns the state of all buttons of the specified joystick.
Each element in the array is either `GLFW_PRESS` or `GLFW_RELEASE`.

For backward compatibility with earlier versions that did not have @ref
glfwGetJoystickHats, the button array also includes all hats, each
represented as four buttons. The hats are in the same order as returned by
__glfwGetJoystickHats__ and are in the order _up_, _right_, _down_ and
_left_. To disable these extra buttons, set the @ref
GLFW_JOYSTICK_HAT_BUTTONS init hint before initialization.

If the specified joystick is not present this function will return `NULL`
but will not generate an error. This can be used instead of first calling
[`glfwJoystickPresent`](/API/GLFW/glfwJoystickPresent.html).

arguments

:    1. `int` `$jid` The `joystick` to query.

returns

:    `array` 

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```