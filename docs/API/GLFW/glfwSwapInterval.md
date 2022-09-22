# glfwSwapInterval
Sets the swap interval for the current context.

```php
function glfwSwapInterval(int $interval) : void
```

This function sets the swap interval for the current OpenGL or OpenGL ES
context, i.e. the number of screen updates to wait from the time @ref
glfwSwapBuffers was called before swapping the buffers and returning. This
is sometimes called _vertical synchronization_, _vertical retrace
synchronization_ or just _vsync_.

A context that supports either of the `WGL_EXT_swap_control_tear` and
`GLX_EXT_swap_control_tear` extensions also accepts _negative_ swap
intervals, which allows the driver to swap immediately even if a frame
arrives a little bit late. You can check for these extensions with @ref
glfwExtensionSupported.

A context must be current on the calling thread. Calling this function
without a current context will cause a `GLFW_NO_CURRENT_CONTEXT` error.

This function does not apply to Vulkan. If you are rendering with Vulkan,
see the present mode of your swapchain instead.

arguments

:    1. `int` `$interval` The minimum number of screen updates to wait for
    until the buffers are swapped by
    [`glfwSwapBuffers`](/API/GLFW/glfwSwapBuffers.html).

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