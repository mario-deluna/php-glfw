# glfwMakeContextCurrent
Makes the context of the specified window current for the calling
thread.

```php
function glfwMakeContextCurrent(\GLFWwindow $window) : void
```

This function makes the OpenGL or OpenGL ES context of the specified window
current on the calling thread. A context must only be made current on
a single thread at a time and each thread can have only a single current
context at a time.

When moving a context between threads, you must make it non-current on the
old thread before making it current on the new one.

By default, making a context non-current implicitly forces a pipeline flush.
On machines that support `GL_KHR_context_flush_control`, you can control
whether a context performs this flush by setting the
`GLFW_CONTEXT_RELEASE_BEHAVIOR`
hint.

The specified window must have an OpenGL or OpenGL ES context. Specifying
a window without a context will generate a `GLFW_NO_WINDOW_CONTEXT`
error.

arguments

:    1. `\GLFWwindow` `$window` The window whose context to make current, or `NULL`
    to
    detach the current context.

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