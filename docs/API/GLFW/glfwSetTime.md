# glfwSetTime
Sets the GLFW time.

```php
function glfwSetTime(float $time) : void
```

This function sets the current GLFW time, in seconds. The value must be
a positive finite number less than or equal to 18446744073.0, which is
approximately 584.5 years.

This function and [`glfwGetTime`](/API/GLFW/glfwGetTime.html) are helper
functions on top of @ref
glfwGetTimerFrequency and
[`glfwGetTimerValue`](/API/GLFW/glfwGetTimerValue.html).

arguments

:    1. `float` `$time` The new value, in seconds.

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