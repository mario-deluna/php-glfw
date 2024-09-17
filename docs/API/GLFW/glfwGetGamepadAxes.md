# glfwGetGamepadAxes
Returns the state of the specified gamepad's axes.

```php
function glfwGetGamepadAxes(int $joystick) : array
```

If the gamepad is not present, or the given joystick is not a gamepad, this
function will return an empty array.

The returned array is indexed by the GLFW gamepad axis constants:
 - `GLFW_GAMEPAD_AXIS_LEFT_X`
 - `GLFW_GAMEPAD_AXIS_LEFT_Y`
 - `GLFW_GAMEPAD_AXIS_RIGHT_X`
 - `GLFW_GAMEPAD_AXIS_RIGHT_Y`
 - `GLFW_GAMEPAD_AXIS_LEFT_TRIGGER`
 - `GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER`

arguments

:    1. `int` `$joystick` The joystick to query.

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