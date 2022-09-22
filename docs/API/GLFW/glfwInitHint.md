# glfwInitHint
Sets the specified init hint to the desired value.

```php
function glfwInitHint(int $hint, int $value) : void
```

This function sets hints for the next initialization of GLFW.

The values you set hints to are never reset by GLFW, but they only take
effect during initialization. Once GLFW has been initialized, any values
you set will be ignored until the library is terminated and initialized
again.

Some hints are platform specific. These may be set on any platform but they
will only affect their specific platform. Other platforms will ignore them.
Setting these hints requires no platform specific headers or functions.

arguments

:    1. `int` `$hint` The `init hint` to set.
    2. `int` `$value` The new value of the init hint.

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