# glfwWindowHint
Sets the specified window hint to the desired value.

```php
function glfwWindowHint(int $hint, int $value) : void
```

This function sets hints for the next call to
[`glfwCreateWindow`](/API/GLFW/glfwCreateWindow.html). The
hints, once set, retain their values until changed by a call to this
function or
[`glfwDefaultWindowHints`](/API/GLFW/glfwDefaultWindowHints.html), or until
the library is terminated.

Only integer value hints can be set with this function. String value hints
are set with [`glfwWindowHintString`](/API/GLFW/glfwWindowHintString.html).

This function does not check whether the specified hint values are valid.
If you set hints to invalid values this will instead be reported by the next
call to [`glfwCreateWindow`](/API/GLFW/glfwCreateWindow.html).

Some hints are platform specific. These may be set on any platform but they
will only affect their specific platform. Other platforms will ignore them.
Setting these hints requires no platform specific headers or functions.

arguments

:    1. `int` `$hint` The `window hint` to set.
    2. `int` `$value` The new value of the window hint.

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