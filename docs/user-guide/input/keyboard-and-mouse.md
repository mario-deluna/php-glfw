# Keyboard & Mouse

The keyboard and mouse are where most interaction lives. This page walks through reading keys, receiving typed text, tracking mouse buttons and cursor position, handling the scroll wheel, grabbing the cursor for camera control, swapping cursor shapes, and touching the system clipboard.

Everything here assumes you have a `$window` from [Creating a Window](../../getting-started/window-creation.md), and it helps to have read the [Input & Events overview](../../user-guide/input/overview.md) first, since the callback idiom and the `GLFW_PRESS` / `GLFW_MOD_*` vocabulary are explained there. To see it all running at once:

```bash
php examples/08_input_and_events.php
```

## Reading the keyboard

For keys you care about continuously, such as movement, poll their state each frame with [`glfwGetKey`](../../API/GLFW/glfwGetKey.md). It returns `GLFW_PRESS` or `GLFW_RELEASE`:

```php
if (glfwGetKey($window, GLFW_KEY_W) === GLFW_PRESS) {
    $ship->moveForward();
}
if (glfwGetKey($window, GLFW_KEY_LEFT_SHIFT) === GLFW_PRESS) {
    $ship->boost();
}
```

Keys are named after their physical position on a US keyboard layout, so `GLFW_KEY_W` is always the key where W sits, regardless of the user's language layout. That is exactly what you want for movement bindings. There is a token for every key: letters (`GLFW_KEY_A`), digits (`GLFW_KEY_0`), function keys (`GLFW_KEY_F1`), the arrows (`GLFW_KEY_UP`), and named keys like `GLFW_KEY_ESCAPE`, `GLFW_KEY_ENTER`, `GLFW_KEY_SPACE`, and `GLFW_KEY_TAB`.

For discrete key events, such as a menu shortcut or a single jump, register a callback with [`glfwSetKeyCallback`](../../API/GLFW/glfwSetKeyCallback.md). Your closure receives `($key, $scancode, $action, $mods)`:

```php
glfwSetKeyCallback($window, function ($key, $scancode, $action, $mods) use ($window) {
    if ($key === GLFW_KEY_ESCAPE && $action === GLFW_PRESS) {
        glfwSetWindowShouldClose($window, GL_TRUE); // close on Escape
    }

    if ($key === GLFW_KEY_S && $action === GLFW_PRESS && ($mods & GLFW_MOD_CONTROL)) {
        $this->save(); // Ctrl+S
    }
});
```

The `$action` is `GLFW_PRESS`, `GLFW_RELEASE`, or `GLFW_REPEAT`. Checking for `GLFW_PRESS` means your handler fires once when the key goes down, not every frame it is held.

!!! warning "Physical keys are not text"
    `glfwGetKey` and the key callback deal with physical keys, not characters. `GLFW_KEY_A` is the position of the A key, not the letter the user typed (that depends on their layout, Shift, and dead keys). Never build text input by concatenating key names. For text, use the character callback below.

## Receiving typed text

When you want the actual characters a user types, into a search box or a chat line, listen for [`glfwSetCharCallback`](../../API/GLFW/glfwSetCharCallback.md). It fires once per Unicode codepoint and already accounts for layout, Shift, and dead keys. Your closure receives a single `($codepoint)`, an integer you turn into a string with `mb_chr`:

```php
$typed = '';

glfwSetCharCallback($window, function ($codepoint) use (&$typed) {
    $typed .= mb_chr($codepoint); // appends the real character, "A", "ä", "文", ...
});
```

!!! tip "You need the mbstring extension"
    `mb_chr` lives in PHP's `mbstring` extension, so make sure it is loaded before you decode codepoints. The bundled example guards this with `extension_loaded('mbstring')` at startup.

If you also need to know which modifiers were held while the character was produced, use [`glfwSetCharModsCallback`](../../API/GLFW/glfwSetCharModsCallback.md) instead, whose closure receives `($codepoint, $mods)`. For ordinary text entry, the plain character callback is what you want.

## Mouse buttons

Just like keys, mouse buttons can be polled or delivered by callback. To ask about a button right now, use [`glfwGetMouseButton`](../../API/GLFW/glfwGetMouseButton.md):

```php
if (glfwGetMouseButton($window, GLFW_MOUSE_BUTTON_LEFT) === GLFW_PRESS) {
    $ship->fire();
}
```

For click events, register [`glfwSetMouseButtonCallback`](../../API/GLFW/glfwSetMouseButtonCallback.md). The closure receives `($button, $action, $mods)`:

```php
glfwSetMouseButtonCallback($window, function ($button, $action, $mods) {
    if ($button === GLFW_MOUSE_BUTTON_RIGHT && $action === GLFW_PRESS) {
        echo "context menu" . PHP_EOL;
    }
});
```

The common buttons have friendly names, `GLFW_MOUSE_BUTTON_LEFT`, `GLFW_MOUSE_BUTTON_RIGHT`, and `GLFW_MOUSE_BUTTON_MIDDLE`, and the rest are numbered `GLFW_MOUSE_BUTTON_1` through `GLFW_MOUSE_BUTTON_8` for mice with extra buttons.

## Where the cursor is

To read the cursor position, call [`glfwGetCursorPos`](../../API/GLFW/glfwGetCursorPos.md). It does not return the coordinates, it writes them into two variables you pass **by reference**:

```php
$mouseX = 0.0;
$mouseY = 0.0;
glfwGetCursorPos($window, $mouseX, $mouseY);
// $mouseX and $mouseY now hold the position, in screen coordinates,
// measured from the top-left of the window's content area
```

If you would rather be notified only when the cursor moves, use [`glfwSetCursorPosCallback`](../../API/GLFW/glfwSetCursorPosCallback.md), whose closure receives `($xpos, $ypos)`. And to know when the cursor crosses your window's edge, [`glfwSetCursorEnterCallback`](../../API/GLFW/glfwSetCursorEnterCallback.md) gives you `($entered)`, which is truthy on the way in and falsy on the way out:

```php
glfwSetCursorEnterCallback($window, function ($entered) {
    echo $entered ? "cursor entered" . PHP_EOL : "cursor left" . PHP_EOL;
});
```

## The scroll wheel

Scrolling, whether from a wheel or a trackpad gesture, arrives through [`glfwSetScrollCallback`](../../API/GLFW/glfwSetScrollCallback.md). The closure receives `($xoffset, $yoffset)`, and most of the time you care about `$yoffset`:

```php
glfwSetScrollCallback($window, function ($xoffset, $yoffset) use (&$cameraZoom) {
    $cameraZoom -= $yoffset * 0.1; // scroll up to zoom in
});
```

## Cursor modes: hiding and grabbing the cursor

For a first-person camera you do not want a visible cursor drifting to the edge of the screen and stopping. You want to capture it, so the mouse can turn the camera forever in any direction. That is what input modes are for. Set them with [`glfwSetInputMode`](../../API/GLFW/glfwSetInputMode.md) and the `GLFW_CURSOR` mode:

```php
// hide and lock the cursor to the window, virtual movement is unlimited
glfwSetInputMode($window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
```

The three cursor modes are:

| Value | Effect |
|-------|--------|
| `GLFW_CURSOR_NORMAL` | the ordinary visible cursor (the default) |
| `GLFW_CURSOR_HIDDEN` | invisible while over the window, but not locked |
| `GLFW_CURSOR_DISABLED` | hidden and locked to the window, movement is unbounded, ideal for 3D cameras |

With the cursor disabled, read motion through the cursor-position callback as usual, and treat the deltas between frames as how far to rotate the camera. To hand control back to the user, for example when they open a menu, set the mode back to `GLFW_CURSOR_NORMAL`.

You can query the current mode at any time with [`glfwGetInputMode`](../../API/GLFW/glfwGetInputMode.md).

### Raw mouse motion

When the cursor is disabled, you usually want raw, unaccelerated motion so the camera is not affected by the operating system's mouse acceleration curve. Enable it with the `GLFW_RAW_MOUSE_MOTION` mode, but only after checking that the platform supports it:

```php
if (glfwRawMouseMotionSupported()) {
    glfwSetInputMode($window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
}
```

!!! warning "Check support first"
    Raw motion is only available while the cursor is disabled, and enabling it on a platform that does not support it raises a `GLFW_PLATFORM_ERROR`. Always guard the call with [`glfwRawMouseMotionSupported`](../../API/GLFW/glfwRawMouseMotionSupported.md). Support does not change while your program runs, so a single check at startup is enough.

### Sticky input

If your loop runs slowly and you worry about missing a very quick tap, turn on sticky mode. With `GLFW_STICKY_KEYS` (or `GLFW_STICKY_MOUSE_BUTTONS`), a press is remembered until the next time you poll it, so a key that was pressed and released between two frames still reads as `GLFW_PRESS` once:

```php
glfwSetInputMode($window, GLFW_STICKY_KEYS, GLFW_TRUE);
```

## Cursor shapes

You can swap the cursor image to hint at what is interactive: a hand over a link, an I-beam over text, a crosshair over a target. Create one of the standard shapes with [`glfwCreateStandardCursor`](../../API/GLFW/glfwCreateStandardCursor.md) and apply it with [`glfwSetCursor`](../../API/GLFW/glfwSetCursor.md):

```php
$hand = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
glfwSetCursor($window, $hand); // show the hand cursor

// ... later, back to the default arrow ...
glfwSetCursor($window, null);

// when you are done with it entirely
glfwDestroyCursor($hand);
```

The available shapes are `GLFW_ARROW_CURSOR`, `GLFW_IBEAM_CURSOR`, `GLFW_CROSSHAIR_CURSOR`, `GLFW_HAND_CURSOR`, `GLFW_HRESIZE_CURSOR`, and `GLFW_VRESIZE_CURSOR`. Passing `null` to `glfwSetCursor` restores the default arrow, and [`glfwDestroyCursor`](../../API/GLFW/glfwDestroyCursor.md) frees a cursor you no longer need.

!!! note
    PHP-GLFW ships the standard system cursors only. Building a cursor from your own image (`glfwCreateCursor` in the C API) is not currently exposed.

## The clipboard

Copy and paste go through a pair of functions. Put text on the system clipboard with [`glfwSetClipboardString`](../../API/GLFW/glfwSetClipboardString.md), and read it back with [`glfwGetClipboardString`](../../API/GLFW/glfwGetClipboardString.md):

```php
// copy
glfwSetClipboardString($window, "shared from my app");

// paste
$fromClipboard = glfwGetClipboardString($window);
```

Both work with UTF-8 strings. `glfwGetClipboardString` returns `null` when the clipboard is empty or holds something that is not text, so check before using the result.

## Full API Reference

For the exhaustive list of every function, argument, and constant, browse the generated GLFW function reference. The key input entry points are [`glfwGetKey`](../../API/GLFW/glfwGetKey.md), [`glfwSetKeyCallback`](../../API/GLFW/glfwSetKeyCallback.md), [`glfwSetCharCallback`](../../API/GLFW/glfwSetCharCallback.md), [`glfwGetCursorPos`](../../API/GLFW/glfwGetCursorPos.md), [`glfwSetInputMode`](../../API/GLFW/glfwSetInputMode.md), and [`glfwSetScrollCallback`](../../API/GLFW/glfwSetScrollCallback.md).
