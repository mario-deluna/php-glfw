# glfwInit
Initializes the GLFW library.

```php
function glfwInit() : int
```

This function initializes the GLFW library. Before most GLFW functions can
be used, GLFW must be initialized, and before an application terminates GLFW
should be terminated in order to free any resources allocated during or
after initialization.

If this function fails, it calls
[`glfwTerminate`](/API/GLFW/glfwTerminate.html) before returning. If it
succeeds, you should call [`glfwTerminate`](/API/GLFW/glfwTerminate.html)
before the application exits.

Additional calls to this function after successful initialization but before
termination will return `GLFW_TRUE` immediately.

returns

:    `int` `GLFW_TRUE` if successful, or `GLFW_FALSE` if an
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