# glfwGetGamepadButtons
Returns the state of the specified gamepad's buttons.

```php
function glfwGetGamepadButtons(int $joystick) : array
```

If the gamepad is not present, or the given joystick is not a gamepad, this
function will return an empty array.

The returned array is indexed by the GLFW gamepad button constants:
 - `GLFW_GAMEPAD_BUTTON_A`
 - `GLFW_GAMEPAD_BUTTON_B`
 - `GLFW_GAMEPAD_BUTTON_X`
 - `GLFW_GAMEPAD_BUTTON_Y`
 - `GLFW_GAMEPAD_BUTTON_LEFT_BUMPER`
 - `GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER`
 - `GLFW_GAMEPAD_BUTTON_BACK`
 - `GLFW_GAMEPAD_BUTTON_START`
 - `GLFW_GAMEPAD_BUTTON_GUIDE`
 - `GLFW_GAMEPAD_BUTTON_LEFT_THUMB`
 - `GLFW_GAMEPAD_BUTTON_RIGHT_THUMB`
 - `GLFW_GAMEPAD_BUTTON_DPAD_UP`
 - `GLFW_GAMEPAD_BUTTON_DPAD_RIGHT`
 - `GLFW_GAMEPAD_BUTTON_DPAD_DOWN`
 - `GLFW_GAMEPAD_BUTTON_DPAD_LEFT`

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