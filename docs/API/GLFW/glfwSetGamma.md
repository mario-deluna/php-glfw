# glfwSetGamma
Generates a gamma ramp and sets it for the specified monitor.

```php
function glfwSetGamma(\GLFWmonitor $monitor, float $gamma) : void
```

This function generates an appropriately sized gamma ramp from the specified
exponent and then calls [`glfwSetGammaRamp`](/API/GLFW/glfwSetGammaRamp.html)
with it. The value must be
a finite number greater than zero.

The software controlled gamma ramp is applied _in addition_ to the hardware
gamma correction, which today is usually an approximation of sRGB gamma.
This means that setting a perfectly linear ramp, or gamma 1.0, will produce
the default (usually sRGB-like) behavior.

For gamma correct rendering with OpenGL or OpenGL ES, see the @ref
GLFW_SRGB_CAPABLE hint.

arguments

:    1. `\GLFWmonitor` `$monitor` The monitor whose gamma ramp to set.
    2. `float` `$gamma` The desired exponent.

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