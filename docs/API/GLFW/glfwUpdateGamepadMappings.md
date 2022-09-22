# glfwUpdateGamepadMappings
Adds the specified SDL_GameControllerDB gamepad mappings.

```php
function glfwUpdateGamepadMappings(string $string) : int
```

This function parses the specified ASCII encoded string and updates the
internal list with any gamepad mappings it finds. This string may
contain either a single gamepad mapping or many mappings separated by
newlines. The parser supports the full format of the `gamecontrollerdb.txt`
source file including empty lines and comments.

See `gamepad_mapping` for a description of the format.

If there is already a gamepad mapping for a given GUID in the internal list,
it will be replaced by the one passed to this function. If the library is
terminated and re-initialized the internal list will revert to the built-in
default.

arguments

:    1. `string` `$string` The string containing the gamepad mappings.

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