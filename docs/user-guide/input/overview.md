# Input & Events

A window that cannot hear the user is just a picture. The moment you want the player to steer a ship, the moment you want a click to select something, or the moment you want the viewport to follow a resize, you need input. GLFW hands you every keyboard, mouse, gamepad, and window event the operating system produces, and PHP-GLFW exposes all of it through plain PHP functions and closures.

This section is the narrative companion to the API reference. It teaches the two ways to read input, the callback idiom that ties everything together, and then splits into focused pages:

- [Keyboard & Mouse](/user-guide/input/keyboard-and-mouse.html) covers keys, text input, mouse buttons, cursor position and modes, scrolling, cursors, and the clipboard.
- [Gamepad & Joystick](/user-guide/input/gamepad-and-joystick.html) covers controllers, axes, buttons, and gamepad mappings.
- [Window Events](/user-guide/input/window-events.html) covers resize, focus, close, file drops, and how to pump events.

Every function shown here runs against a live window. If you have not opened one yet, start with [Creating a Window](/getting-started/window-creation.html). You can also run the example this whole section is built on:

```bash
php examples/08_input_and_events.php
```

## Two ways to read input: polling and callbacks

GLFW lets you ask about input in two styles, and you will use both.

**Polling** means you ask "what is the state right now?" every frame, inside your render loop. This is perfect for continuous things: a key held down to move forward, the current mouse position for a camera.

```php
while (!glfwWindowShouldClose($window)) {
    glfwPollEvents();

    if (glfwGetKey($window, GLFW_KEY_W) === GLFW_PRESS) {
        $shipSpeed += 0.1; // W is held this frame, keep accelerating
    }

    // ... render ...
    glfwSwapBuffers($window);
}
```

**Callbacks** mean you hand GLFW a function once, and it calls you back the instant something discrete happens: a key was pressed, a character was typed, a file was dropped. This is perfect for events you must not miss and do not want to sample: typing into a text field, a single click, a window resize.

```php
glfwSetKeyCallback($window, function ($key, $scancode, $action, $mods) {
    if ($key === GLFW_KEY_SPACE && $action === GLFW_PRESS) {
        echo "fire!" . PHP_EOL; // fires once per press, never missed
    }
});
```

As a rule of thumb: poll for state that matters continuously (movement, held keys, cursor position), and use callbacks for discrete events (text, clicks, resizes, drops). Nothing stops you from mixing them in the same application.

## The callback idiom

Every event callback follows the exact same shape, so once you learn one you know them all:

```php
glfwSet<Something>Callback($window, callable $callback);
```

You pass your window and a PHP callable, almost always an inline closure. There are two things worth internalizing up front.

**Your closure receives only the event payload, not the window.** In C, GLFW passes the window handle as the first argument to every callback. PHP-GLFW drops it, because you already have the window in scope. So a key callback receives `($key, $scancode, $action, $mods)`, a scroll callback receives `($xoffset, $yoffset)`, and so on. Each page lists the exact arguments for its events.

**When you need the window inside the callback, capture it with `use`.** This is the one habit to build. To close the window when Escape is pressed, capture `$window`:

```php
glfwSetKeyCallback($window, function ($key, $scancode, $action, $mods) use ($window) {
    if ($key === GLFW_KEY_ESCAPE && $action === GLFW_PRESS) {
        glfwSetWindowShouldClose($window, GL_TRUE);
    }
});
```

!!! tip "When do callbacks actually run?"
    Your closures do not fire the instant the user acts. GLFW queues events and dispatches them all when you call [`glfwPollEvents`](/API/GLFW/glfwPollEvents.html) (or [`glfwWaitEvents`](/API/GLFW/glfwWaitEvents.html)), which you do once per frame. This keeps input synchronized with your render loop, so you never have a callback firing in the middle of drawing. See [Window Events](/user-guide/input/window-events.html) for the difference between polling and waiting.

## Actions and modifier keys

Two small vocabularies show up across almost every input event, so it is worth meeting them once here.

Key and button events report an **action**, one of three constants:

| Constant | Meaning |
|----------|---------|
| `GLFW_PRESS` | the key or button just went down |
| `GLFW_RELEASE` | it just came up |
| `GLFW_REPEAT` | the key is being held and the OS is auto-repeating it |

`GLFW_REPEAT` is only ever delivered to callbacks, never returned by `glfwGetKey`, which knows only pressed or released.

Many events also carry a **mods** value: a bitmask of the modifier keys held at that moment. Test it with a bitwise `&`:

```php
glfwSetMouseButtonCallback($window, function ($button, $action, $mods) {
    if ($button === GLFW_MOUSE_BUTTON_LEFT && $action === GLFW_PRESS) {
        if ($mods & GLFW_MOD_SHIFT) {
            echo "shift-click, add to selection" . PHP_EOL;
        } else {
            echo "plain click, replace selection" . PHP_EOL;
        }
    }
});
```

The modifier bits are `GLFW_MOD_SHIFT`, `GLFW_MOD_CONTROL`, `GLFW_MOD_ALT`, `GLFW_MOD_SUPER` (the Command or Windows key), and, when you opt in with `GLFW_LOCK_KEY_MODS`, `GLFW_MOD_CAPS_LOCK` and `GLFW_MOD_NUM_LOCK`.

## Where to go next

- Want to read the keyboard, mouse, and scroll wheel, or grab the cursor for a 3D camera? Head to [Keyboard & Mouse](/user-guide/input/keyboard-and-mouse.html).
- Wiring up a controller? See [Gamepad & Joystick](/user-guide/input/gamepad-and-joystick.html).
- Need to react to resizes, focus loss, file drops, or build an event-driven app that sleeps until the user acts? See [Window Events](/user-guide/input/window-events.html).
