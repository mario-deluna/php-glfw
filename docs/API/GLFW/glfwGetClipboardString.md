# glfwGetClipboardString
Returns the contents of the clipboard as a string.

```php
function glfwGetClipboardString(\GLFWwindow $window) : string
```

This function returns the contents of the system clipboard, if it contains
or is convertible to a UTF-8 encoded string. If the clipboard is empty or
if its contents cannot be converted, `NULL` is returned and a @ref
GLFW_FORMAT_UNAVAILABLE error is generated.

arguments

:    1. `\GLFWwindow` `$window` Deprecated. Any valid window or `NULL`.

returns

:    `string` The contents of the clipboard as a UTF-8 encoded string, or
`NULL`
if an `error` occurred.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```