# Window Events

The window itself is a source of events. The user drags it to another monitor, resizes it, minimizes it, clicks away to another app, or drops a file onto it. GLFW reports all of this through the same callback idiom you use for input, and reacting to it is what makes an application feel native instead of stuck. This page covers the window callbacks you will actually reach for, file drops, and the two ways to pump events.

These callbacks follow the pattern from the [Input & Events overview](../../user-guide/input/overview.md): you register a closure once, and it fires during `glfwPollEvents`. As always, the window handle is not passed to your closure, so capture `$window` with `use` when you need it.

```bash
php examples/08_input_and_events.php
```

## Reacting to resizes

The single most important window callback is the framebuffer size callback, because your OpenGL viewport must match the drawable area or everything stretches. Register [`glfwSetFramebufferSizeCallback`](../../API/GLFW/glfwSetFramebufferSizeCallback.md) and update the viewport whenever the size changes:

```php
glfwSetFramebufferSizeCallback($window, function ($width, $height) {
    glViewport(0, 0, $width, $height); // keep the GL viewport in sync
});
```

!!! warning "Framebuffer size is in pixels, not screen coordinates"
    On high-DPI displays (like a Retina screen) the framebuffer is larger than the window's screen-coordinate size, often twice as many pixels per side. `glViewport` works in pixels, so always drive it from the **framebuffer** size callback, not the window size callback. Use [`glfwSetWindowSizeCallback`](../../API/GLFW/glfwSetWindowSizeCallback.md), whose closure also receives `($width, $height)`, only when you genuinely need screen coordinates, for example to reposition UI measured in points.

If your projection depends on the aspect ratio, this is also where you would recompute it, so the scene never looks squashed after a resize.

## Focus, minimize, and maximize

When the user clicks away to another application, you often want to pause, mute audio, or throttle back to save power. [`glfwSetWindowFocusCallback`](../../API/GLFW/glfwSetWindowFocusCallback.md) tells you, with a closure receiving `($focused)`:

```php
glfwSetWindowFocusCallback($window, function ($focused) use (&$paused) {
    $paused = !$focused; // pause when the window loses focus
});
```

Two related callbacks round this out. [`glfwSetWindowIconifyCallback`](../../API/GLFW/glfwSetWindowIconifyCallback.md) fires with `($iconified)` when the window is minimized to the taskbar or restored, and [`glfwSetWindowMaximizeCallback`](../../API/GLFW/glfwSetWindowMaximizeCallback.md) fires with `($maximized)` when it is maximized or restored. Both are useful for pausing work while the window is not really visible.

## Moving and rescaling

If you need to know where the window sits or when it crosses onto a different monitor, [`glfwSetWindowPosCallback`](../../API/GLFW/glfwSetWindowPosCallback.md) reports `($x, $y)` after every move. And when the window is dragged onto a screen with a different DPI, [`glfwSetWindowContentScaleCallback`](../../API/GLFW/glfwSetWindowContentScaleCallback.md) fires with `($xscale, $yscale)`, which is your cue to rescale fonts and UI so they stay a sensible physical size.

There is also [`glfwSetWindowRefreshCallback`](../../API/GLFW/glfwSetWindowRefreshCallback.md), a zero-argument callback GLFW uses to ask you to redraw, for instance while the user is actively resizing. On modern compositing systems it may fire rarely or never, so treat it as a hint, not your main render trigger.

## Handling the close request

When the user clicks the window's close button, GLFW does not close the window. It sets a flag, which is exactly the flag your loop checks with `glfwWindowShouldClose`. That gives you the chance to intervene, for example to ask "save before quitting?". [`glfwSetWindowCloseCallback`](../../API/GLFW/glfwSetWindowCloseCallback.md) fires (with no arguments) the moment the request comes in:

```php
glfwSetWindowCloseCallback($window, function () use ($window) {
    if ($this->hasUnsavedWork()) {
        glfwSetWindowShouldClose($window, GL_FALSE); // veto the close, keep running
        $this->promptToSave();
    }
});
```

Setting the flag back to `GL_FALSE` cancels the close and keeps your loop going. Conversely, you can request a close yourself from anywhere, such as an Escape key handler, by calling `glfwSetWindowShouldClose($window, GL_TRUE)`.

## Accepting dropped files

Users expect to drag a file onto a window and have it open. GLFW makes this a one-callback affair with [`glfwSetDropCallback`](../../API/GLFW/glfwSetDropCallback.md). Your closure receives `($count, $paths)`, the number of files and an array of their absolute paths:

```php
glfwSetDropCallback($window, function ($count, $paths) {
    for ($i = 0; $i < $count; $i++) {
        echo "opening " . $paths[$i] . PHP_EOL;
        $this->loadModel($paths[$i]);
    }
});
```

This is the natural way to let users load a model, a texture, or a project file, no file dialog required.

## Pumping events: poll vs. wait

None of these callbacks fire on their own. GLFW collects events and dispatches them when you tell it to, and you have two ways to do that.

[`glfwPollEvents`](../../API/GLFW/glfwPollEvents.md) processes whatever has happened and returns immediately. This is what you want for a game or any continuously animating application, where you redraw every frame regardless of input:

```php
while (!glfwWindowShouldClose($window)) {
    glfwPollEvents();      // dispatch callbacks, then keep going
    // ... render every frame ...
    glfwSwapBuffers($window);
}
```

[`glfwWaitEvents`](../../API/GLFW/glfwWaitEvents.md) instead puts your program to sleep until something actually happens, then dispatches it. This is ideal for tools and editors that only need to redraw when the user does something, because it uses almost no CPU while idle:

```php
while (!glfwWindowShouldClose($window)) {
    glfwWaitEvents();      // sleep until the user acts, then wake up
    // ... redraw once in response ...
    glfwSwapBuffers($window);
}
```

If you wait but still need to wake up periodically, [`glfwWaitEventsTimeout`](../../API/GLFW/glfwWaitEventsTimeout.md) sleeps for at most a given number of seconds. And from another part of your program you can nudge a waiting loop awake with [`glfwPostEmptyEvent`](../../API/GLFW/glfwPostEmptyEvent.md), which is handy when a background task finishes and you want to redraw.

## Full API Reference

For every window callback and event function, see the generated GLFW function reference, including [`glfwSetFramebufferSizeCallback`](../../API/GLFW/glfwSetFramebufferSizeCallback.md), [`glfwSetWindowCloseCallback`](../../API/GLFW/glfwSetWindowCloseCallback.md), [`glfwSetDropCallback`](../../API/GLFW/glfwSetDropCallback.md), and [`glfwPollEvents`](../../API/GLFW/glfwPollEvents.md).
