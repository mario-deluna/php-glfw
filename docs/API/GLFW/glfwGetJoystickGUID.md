# glfwGetJoystickGUID
Returns the SDL compatible GUID of the specified joystick.

```php
function glfwGetJoystickGUID(int $jid) : string
```

This function returns the SDL compatible GUID, as a UTF-8 encoded
hexadecimal string, of the specified joystick. The returned string is
allocated and freed by GLFW. You should not free it yourself.

The GUID is what connects a joystick to a gamepad mapping. A connected
joystick will always have a GUID even if there is no gamepad mapping
assigned to it.

If the specified joystick is not present this function will return `NULL`
but will not generate an error. This can be used instead of first calling
[`glfwJoystickPresent`](/API/GLFW/glfwJoystickPresent.html).

The GUID uses the format introduced in SDL 2.0.5. This GUID tries to
uniquely identify the make and model of a joystick but does not identify
a specific unit, e.g. all wired Xbox 360 controllers will have the same
GUID on that platform. The GUID for a unit may vary between platforms
depending on what hardware information the platform specific APIs provide.

arguments

:    1. `int` `$jid` The `joystick` to query.

returns

:    `string` The UTF-8 encoded GUID of the joystick, or `NULL` if the
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