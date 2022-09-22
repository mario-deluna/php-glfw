# glfwPollEvents
Processes all pending events.

```php
function glfwPollEvents() : void
```

This function processes only those events that are already in the event
queue and then returns immediately. Processing events will cause the window
and input callbacks associated with those events to be called.

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