# glfwWaitEvents
Waits until events are queued and processes them.

```php
function glfwWaitEvents() : void
```

This function puts the calling thread to sleep until at least one event is
available in the event queue. Once one or more events are available,
it behaves exactly like [`glfwPollEvents`](/API/GLFW/glfwPollEvents.html),
i.e. the events in the queue
are processed and the function then returns immediately. Processing events
will cause the window and input callbacks associated with those events to be
called.

Since not all events are associated with callbacks, this function may return
without a callback having been called even if you are monitoring all
callbacks.

On some platforms, a window move, resize or menu operation will cause event
processing to block. This is due to how event processing is designed on
those platforms. You can use the
`window refresh callback` to redraw the contents of
your window when necessary during such operations.

Do not assume that callbacks you set will _only_ be called in response to
event processing functions like this one. While it is necessary to poll for
events, window systems that require GLFW to register callbacks of its own
can pass events to GLFW in response to many window system function calls.
GLFW will pass those events on to the application callbacks before
returning.

Event processing is not required for joystick input to work.

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