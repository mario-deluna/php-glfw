# glGenerateMipmap
generate mipmaps for a specified texture object

```php
function glGenerateMipmap(int $target) : void
```

arguments

:    1. `int` `$target` Specifies the target to which the texture object is bound
    for glGenerateMipmap. Must be one of <constant>GL_TEXTURE_1D</constant>,
    <constant>GL_TEXTURE_2D</constant>, <constant>GL_TEXTURE_3D</constant>,
    <constant>GL_TEXTURE_1D_ARRAY</constant>,
    <constant>GL_TEXTURE_2D_ARRAY</constant>,
    <constant>GL_TEXTURE_CUBE_MAP</constant>, or
    <constant>GL_TEXTURE_CUBE_MAP_ARRAY</constant>.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.