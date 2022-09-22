# glfwSetInputMode
Sets an input option for the specified window.

```php
function glfwSetInputMode(\GLFWwindow $window, int $mode, int $value) : void
```

This function sets an input mode option for the specified window. The mode
must be one of `GLFW_CURSOR`, `GLFW_STICKY_KEYS`,
`GLFW_STICKY_MOUSE_BUTTONS`, `GLFW_LOCK_KEY_MODS` or
`GLFW_RAW_MOUSE_MOTION`.

If the mode is `GLFW_CURSOR`, the value must be one of the following cursor
modes:
- `GLFW_CURSOR_NORMAL` makes the cursor visible and behaving normally.
- `GLFW_CURSOR_HIDDEN` makes the cursor invisible when it is over the
 content area of the window but does not restrict the cursor from leaving.
- `GLFW_CURSOR_DISABLED` hides and grabs the cursor, providing virtual
 and unlimited cursor movement. This is useful for implementing for
 example 3D camera controls.

If the mode is `GLFW_STICKY_KEYS`, the value must be either `GLFW_TRUE` to
enable sticky keys, or `GLFW_FALSE` to disable it. If sticky keys are
enabled, a key press will ensure that
[`glfwGetKey`](/API/GLFW/glfwGetKey.html) returns `GLFW_PRESS`
the next time it is called even if the key had been released before the
call. This is useful when you are only interested in whether keys have been
pressed but not when or in which order.

If the mode is `GLFW_STICKY_MOUSE_BUTTONS`, the value must be either
`GLFW_TRUE` to enable sticky mouse buttons, or `GLFW_FALSE` to disable it.
If sticky mouse buttons are enabled, a mouse button press will ensure that
[`glfwGetMouseButton`](/API/GLFW/glfwGetMouseButton.html) returns
`GLFW_PRESS` the next time it is called even
if the mouse button had been released before the call. This is useful when
you are only interested in whether mouse buttons have been pressed but not
when or in which order.

If the mode is `GLFW_LOCK_KEY_MODS`, the value must be either `GLFW_TRUE` to
enable lock key modifier bits, or `GLFW_FALSE` to disable them. If enabled,
callbacks that receive modifier bits will also have the @ref
GLFW_MOD_CAPS_LOCK bit set when the event was generated with Caps Lock on,
and the `GLFW_MOD_NUM_LOCK` bit when Num Lock was on.

If the mode is `GLFW_RAW_MOUSE_MOTION`, the value must be either `GLFW_TRUE`
to enable raw (unscaled and unaccelerated) mouse motion when the cursor is
disabled, or `GLFW_FALSE` to disable it. If raw motion is not supported,
attempting to set this will emit `GLFW_PLATFORM_ERROR`. Call @ref
glfwRawMouseMotionSupported to check for support.

arguments

:    1. `\GLFWwindow` `$window` The window whose input mode to set.
    2. `int` `$mode` One of `GLFW_CURSOR`, `GLFW_STICKY_KEYS`,
    `GLFW_STICKY_MOUSE_BUTTONS`, `GLFW_LOCK_KEY_MODS` or
    `GLFW_RAW_MOUSE_MOTION`.
    3. `int` `$value` The new value of the specified input mode.

returns

:    `void` 

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```