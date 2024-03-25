# glActiveTexture
The `glActiveTexture` function is used in OpenGL to select an active texture
unit. This function takes an integer argument `$texture`, which specifies
which texture unit to make active. The number of texture units is
implementation dependent, but must be at least 80. The parameter `$texture`
must be one of `GL_TEXTUREi`, where `i` ranges from zero to the value of
`GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS` minus one. The initial value is
`GL_TEXTURE0`.

```php
function glActiveTexture(int $texture) : void
```

Here is an example usage of `glActiveTexture`:

```php
glActiveTexture(GL_TEXTURE0); // Make texture unit 0 active
glActiveTexture(GL_TEXTURE1); // Make texture unit 1 active
```

Note that you should always check the value of
`GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS` to ensure that your program is
compatible with the current OpenGL implementation.

arguments

:    1. `int` `$texture` Specifies which texture unit to make active. The number
    of texture units is implementation dependent, but must be at least 80.
    texture must be one of <constant>GL_TEXTURE</constant>i, where i ranges from
    zero to the value of <constant>GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS</constant>
    minus one. The initial value is <constant>GL_TEXTURE0</constant>.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.