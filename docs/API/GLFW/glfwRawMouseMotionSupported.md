# glfwRawMouseMotionSupported
Returns whether raw mouse motion is supported.

```php
function glfwRawMouseMotionSupported() : int
```

This function returns whether raw mouse motion is supported on the current
system. This status does not change after GLFW has been initialized so you
only need to check this once. If you attempt to enable raw motion on
a system that does not support it, `GLFW_PLATFORM_ERROR` will be emitted.

Raw mouse motion is closer to the actual motion of the mouse across
a surface. It is not affected by the scaling and acceleration applied to
the motion of the desktop cursor. That processing is suitable for a cursor
while raw motion is better for controlling for example a 3D camera. Because
of this, raw mouse motion is only provided when the cursor is disabled.

returns

:    `int` `GLFW_TRUE` if raw mouse motion is supported on the current
machine,
or `GLFW_FALSE` otherwise.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```