# glfwPostEmptyEvent
Posts an empty event to the event queue.

```php
function glfwPostEmptyEvent() : void
```

This function posts an empty event from the current thread to the event
queue, causing [`glfwWaitEvents`](/API/GLFW/glfwWaitEvents.html) or
[`glfwWaitEventsTimeout`](/API/GLFW/glfwWaitEventsTimeout.html) to return.

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