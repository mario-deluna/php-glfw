# glfwCreateStandardCursor
Creates a cursor with a standard shape.

```php
function glfwCreateStandardCursor(int $shape) : \GLFWcursor
```

Returns a cursor with a `standard shape`, that can be set for
a window with [`glfwSetCursor`](/API/GLFW/glfwSetCursor.html).

arguments

:    1. `int` `$shape` One of the `standard shapes`.

returns

:    `\GLFWcursor` A new cursor ready to use or `NULL` if an
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