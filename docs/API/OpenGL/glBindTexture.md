# glBindTexture
bind a named texture to a texturing target

```php
function glBindTexture(int $target, int $texture) : void
```

arguments

:    1. `int` `$target` Specifies the target to which the texture is bound. Must
    be one of <constant>GL_TEXTURE_1D</constant>,
    <constant>GL_TEXTURE_2D</constant>, <constant>GL_TEXTURE_3D</constant>,
    <constant>GL_TEXTURE_1D_ARRAY</constant>,
    <constant>GL_TEXTURE_2D_ARRAY</constant>,
    <constant>GL_TEXTURE_RECTANGLE</constant>,
    <constant>GL_TEXTURE_CUBE_MAP</constant>,
    <constant>GL_TEXTURE_CUBE_MAP_ARRAY</constant>,
    <constant>GL_TEXTURE_BUFFER</constant>,
    <constant>GL_TEXTURE_2D_MULTISAMPLE</constant> or
    <constant>GL_TEXTURE_2D_MULTISAMPLE_ARRAY</constant>.
    2. `int` `$texture` Specifies the name of a texture.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.