# glfwGetTime
Returns the GLFW time.

```php
function glfwGetTime() : float
```

This function returns the current GLFW time, in seconds. Unless the time
has been set using [`glfwSetTime`](/API/GLFW/glfwSetTime.html) it measures
time elapsed since GLFW was
initialized.

This function and [`glfwSetTime`](/API/GLFW/glfwSetTime.html) are helper
functions on top of @ref
glfwGetTimerFrequency and
[`glfwGetTimerValue`](/API/GLFW/glfwGetTimerValue.html).

The resolution of the timer is system dependent, but is usually on the order
of a few micro- or nanoseconds. It uses the highest-resolution monotonic
time source on each supported platform.

returns

:    `float` The current time, in seconds, or zero if an
`error` occurred.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```