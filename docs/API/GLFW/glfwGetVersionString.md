# glfwGetVersionString
Returns a string describing the compile-time configuration.

```php
function glfwGetVersionString() : string
```

This function returns the compile-time generated
`version string` of the GLFW library binary. It
describes the version, platform, compiler and any platform-specific
compile-time options. It should not be confused with the OpenGL or OpenGL
ES version string, queried with `glGetString`.

__Do not use the version string__ to parse the GLFW library version. The
[`glfwGetVersion`](/API/GLFW/glfwGetVersion.html) function provides the
version of the running library
binary in numerical format.

returns

:    `string` The ASCII encoded GLFW version string.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```