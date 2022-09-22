# glfwGetKeyName
Returns the layout-specific name of the specified printable key.

```php
function glfwGetKeyName(int $key, int $scancode) : string
```

This function returns the name of the specified printable key, encoded as
UTF-8. This is typically the character that key would produce without any
modifier keys, intended for displaying key bindings to the user. For dead
keys, it is typically the diacritic it would add to a character.

__Do not use this function__ for `text input`. You will
break text input for many languages even if it happens to work for yours.

If the key is `GLFW_KEY_UNKNOWN`, the scancode is used to identify the key,
otherwise the scancode is ignored. If you specify a non-printable key, or
`GLFW_KEY_UNKNOWN` and a scancode that maps to a non-printable key, this
function returns `NULL` but does not emit an error.

This behavior allows you to always pass in the arguments in the
`key callback` without modification.

The printable keys are:
- `GLFW_KEY_APOSTROPHE`
- `GLFW_KEY_COMMA`
- `GLFW_KEY_MINUS`
- `GLFW_KEY_PERIOD`
- `GLFW_KEY_SLASH`
- `GLFW_KEY_SEMICOLON`
- `GLFW_KEY_EQUAL`
- `GLFW_KEY_LEFT_BRACKET`
- `GLFW_KEY_RIGHT_BRACKET`
- `GLFW_KEY_BACKSLASH`
- `GLFW_KEY_WORLD_1`
- `GLFW_KEY_WORLD_2`
- `GLFW_KEY_0` to `GLFW_KEY_9`
- `GLFW_KEY_A` to `GLFW_KEY_Z`
- `GLFW_KEY_KP_0` to `GLFW_KEY_KP_9`
- `GLFW_KEY_KP_DECIMAL`
- `GLFW_KEY_KP_DIVIDE`
- `GLFW_KEY_KP_MULTIPLY`
- `GLFW_KEY_KP_SUBTRACT`
- `GLFW_KEY_KP_ADD`
- `GLFW_KEY_KP_EQUAL`

Names for printable keys depend on keyboard layout, while names for
non-printable keys are the same across layouts but depend on the application
language and should be localized along with other user interface text.

arguments

:    1. `int` `$key` The key to query, or `GLFW_KEY_UNKNOWN`.
    2. `int` `$scancode` The scancode of the key to query.

returns

:    `string` The UTF-8 encoded, layout-specific name of the key, or `NULL`.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```