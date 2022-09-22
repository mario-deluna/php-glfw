# glfwSwapBuffers
Swaps the front and back buffers of the specified window.

```php
function glfwSwapBuffers(\GLFWwindow $window) : void
```

This function swaps the front and back buffers of the specified window when
rendering with OpenGL or OpenGL ES. If the swap interval is greater than
zero, the GPU driver waits the specified number of screen updates before
swapping the buffers.

The specified window must have an OpenGL or OpenGL ES context. Specifying
a window without a context will generate a `GLFW_NO_WINDOW_CONTEXT`
error.

This function does not apply to Vulkan. If you are rendering with Vulkan,
see `vkQueuePresentKHR` instead.

arguments

:    1. `\GLFWwindow` `$window` The window whose buffers to swap.

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