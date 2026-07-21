# Gamepad & Joystick

Some games simply feel better with a controller in hand. GLFW reads gamepads and joysticks through the same window system you already use, and PHP-GLFW exposes their axes and buttons as plain PHP arrays. This page shows how to find a connected controller, read a proper gamepad, fall back to a raw joystick, and load community mappings so more controllers "just work".

You do not need a window open to query controllers, but you do need GLFW initialized, which opening a window does for you. See [Creating a Window](/getting-started/window-creation.html) if you have not yet.

## Finding a controller

Controllers are identified by a joystick id, a slot number from `GLFW_JOYSTICK_1` up to `GLFW_JOYSTICK_16`. Before reading anything, check whether a controller is plugged into a slot with [`glfwJoystickPresent`](/API/GLFW/glfwJoystickPresent.html):

```php
if (glfwJoystickPresent(GLFW_JOYSTICK_1)) {
    echo "controller 1: " . glfwGetJoystickName(GLFW_JOYSTICK_1) . PHP_EOL;
}
```

[`glfwGetJoystickName`](/API/GLFW/glfwGetJoystickName.html) gives you a human-readable name for display. If you want to remember a specific controller across sessions, [`glfwGetJoystickGUID`](/API/GLFW/glfwGetJoystickGUID.html) returns a stable SDL-compatible identifier.

!!! note "There is no connect/disconnect callback"
    PHP-GLFW does not expose a joystick callback, so you cannot be notified the moment a controller is plugged in or unplugged. Instead, poll `glfwJoystickPresent` for the slots you care about, once per frame or every so often, and react when the answer changes.

## Gamepads: the easy path

Most modern controllers (Xbox, PlayStation, and the many that imitate them) have a standard button and stick layout. GLFW recognizes these as **gamepads** and gives them a consistent mapping, so button "A" is always in the same place no matter the brand. Check for a mapping with [`glfwJoystickIsGamepad`](/API/GLFW/glfwJoystickIsGamepad.html):

```php
if (glfwJoystickIsGamepad(GLFW_JOYSTICK_1)) {
    echo "recognized gamepad: " . glfwGetGamepadName(GLFW_JOYSTICK_1) . PHP_EOL;
}
```

Once you know it is a gamepad, read its sticks and triggers with [`glfwGetGamepadAxes`](/API/GLFW/glfwGetGamepadAxes.html) and its buttons with [`glfwGetGamepadButtons`](/API/GLFW/glfwGetGamepadButtons.html). Both return arrays indexed by GLFW's standard constants:

```php
$axes = glfwGetGamepadAxes(GLFW_JOYSTICK_1);
$buttons = glfwGetGamepadButtons(GLFW_JOYSTICK_1);

// steer the ship with the left stick, -1.0 (left/up) to 1.0 (right/down)
$ship->steer($axes[GLFW_GAMEPAD_AXIS_LEFT_X], $axes[GLFW_GAMEPAD_AXIS_LEFT_Y]);

// fire on the A / Cross button
if ($buttons[GLFW_GAMEPAD_BUTTON_A] === GLFW_PRESS) {
    $ship->fire();
}
```

The axes are `GLFW_GAMEPAD_AXIS_LEFT_X`, `GLFW_GAMEPAD_AXIS_LEFT_Y`, `GLFW_GAMEPAD_AXIS_RIGHT_X`, `GLFW_GAMEPAD_AXIS_RIGHT_Y`, `GLFW_GAMEPAD_AXIS_LEFT_TRIGGER`, and `GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER`. Stick axes range from `-1.0` to `1.0`, and the two triggers range from `-1.0` at rest to `1.0` fully pressed.

The buttons cover the whole standard pad: the face buttons `GLFW_GAMEPAD_BUTTON_A`, `_B`, `_X`, `_Y` (with PlayStation aliases `GLFW_GAMEPAD_BUTTON_CROSS`, `_CIRCLE`, `_SQUARE`, `_TRIANGLE`), the bumpers `_LEFT_BUMPER` and `_RIGHT_BUMPER`, `_BACK`, `_START`, `_GUIDE`, the stick clicks `_LEFT_THUMB` and `_RIGHT_THUMB`, and the d-pad `_DPAD_UP`, `_DPAD_RIGHT`, `_DPAD_DOWN`, `_DPAD_LEFT`. Each value is `GLFW_PRESS` or `GLFW_RELEASE`.

!!! tip "Add a dead zone"
    Analog sticks rarely rest at exactly zero. Ignore tiny values so a controller sitting on the desk does not slowly drift your camera: `if (abs($x) < 0.15) $x = 0.0;`

## Raw joysticks: the fallback

Flight sticks, racing wheels, and older or exotic controllers may not have a standard gamepad mapping. For those, read the raw hardware directly. [`glfwGetJoystickAxes`](/API/GLFW/glfwGetJoystickAxes.html) returns every analog axis as an array of floats, and [`glfwGetJoystickButtons`](/API/GLFW/glfwGetJoystickButtons.html) returns every button:

```php
$axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1);
$buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1);

echo "this stick has " . count($axes) . " axes and " . count($buttons) . " buttons" . PHP_EOL;
```

The trade-off is that the layout is device-specific: axis 0 might be steering on one wheel and a throttle on another. Raw joysticks are the right tool when you are building configurable bindings or supporting a device GLFW does not recognize as a gamepad. When a controller *is* a gamepad, prefer the gamepad functions above, since their layout is guaranteed.

## Teaching GLFW new controllers

GLFW ships with mappings for many popular controllers, but new hardware appears all the time. The community maintains a large database of mappings (the SDL GameControllerDB), and you can feed it to GLFW so more controllers are recognized as gamepads. Load the database contents with [`glfwUpdateGamepadMappings`](/API/GLFW/glfwUpdateGamepadMappings.html):

```php
$db = file_get_contents(__DIR__ . '/gamecontrollerdb.txt');
glfwUpdateGamepadMappings($db);
```

Call this once at startup, before you check `glfwJoystickIsGamepad`. Any controller covered by the database will then report as a gamepad and work with `glfwGetGamepadAxes` and `glfwGetGamepadButtons`, no per-device code required.

## Full API Reference

For every controller function and the full list of button and axis constants, see the generated [GLFW function reference](/API/GLFW/), starting with [`glfwJoystickPresent`](/API/GLFW/glfwJoystickPresent.html), [`glfwGetGamepadAxes`](/API/GLFW/glfwGetGamepadAxes.html), and [`glfwGetGamepadButtons`](/API/GLFW/glfwGetGamepadButtons.html).
