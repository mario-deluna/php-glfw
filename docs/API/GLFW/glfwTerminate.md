# glfwTerminate
Terminates the GLFW library.

```php
function glfwTerminate() : void
```

This function destroys all remaining windows and cursors, restores any
modified gamma ramps and frees any other allocated resources. Once this
function is called, you must again call [`glfwInit`](/API/GLFW/glfwInit.html)
successfully before
you will be able to use most GLFW functions.

If GLFW has been successfully initialized, this function should be called
before the application exits. If initialization fails, there is no need to
call this function, as it is called by [`glfwInit`](/API/GLFW/glfwInit.html)
before it returns
failure.

This function has no effect if GLFW is not initialized.

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