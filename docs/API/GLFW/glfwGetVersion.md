# glfwGetVersion
Retrieves the version of the GLFW library.

```php
function glfwGetVersion(int &$major, int &$minor, int &$rev) : void
```

This function retrieves the major, minor and revision numbers of the GLFW
library. It is intended for when you are using GLFW as a shared library and
want to ensure that you are using the minimum required version.

Any or all of the version arguments may be `NULL`.

arguments

:    1. `int` `$major` Where to store the major version number, or `NULL`.
    2. `int` `$minor` Where to store the minor version number, or `NULL`.
    3. `int` `$rev` Where to store the revision number, or `NULL`.

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