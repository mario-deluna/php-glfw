# glfwGetVideoModes
Returns the available video modes for the specified monitor.

```php
function glfwGetVideoModes(\GLFWmonitor $monitor) : \GLFWvidmode
```

This function returns an array of all video modes supported by the specified
monitor. The returned array is sorted in ascending order, first by color
bit depth (the sum of all channel depths), then by resolution area (the
product of width and height), then resolution width and finally by refresh
rate.

arguments

:    1. `\GLFWmonitor` `$monitor` The monitor to query.

returns

:    `\GLFWvidmode` An array of video modes, or `NULL` if an
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