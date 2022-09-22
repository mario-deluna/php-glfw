# glfwDestroyCursor
Destroys a cursor.

```php
function glfwDestroyCursor(\GLFWcursor $cursor) : void
```

This function destroys a cursor previously created with @ref
glfwCreateCursor. Any remaining cursors will be destroyed by @ref
glfwTerminate.

If the specified cursor is current for any window, that window will be
reverted to the default cursor. This does not affect the cursor mode.

arguments

:    1. `\GLFWcursor` `$cursor` The cursor object to destroy.

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