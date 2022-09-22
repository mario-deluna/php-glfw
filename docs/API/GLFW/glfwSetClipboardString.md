# glfwSetClipboardString
Sets the clipboard to the specified string.

```php
function glfwSetClipboardString(\GLFWwindow $window, string $string) : void
```

This function sets the system clipboard to the specified, UTF-8 encoded
string.

arguments

:    1. `\GLFWwindow` `$window` Deprecated. Any valid window or `NULL`.
    2. `string` `$string` A UTF-8 encoded string.

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