# glCopyTexSubImage3D
copy a three-dimensional texture subimage

```php
function glCopyTexSubImage3D(int $target, int $level, int $xoffset, int $yoffset, int $zoffset, int $x, int $y, int $width, int $height) : void
```

arguments

:    1. `int` `$target` Specifies the target to which the texture object is bound
    for glCopyTexSubImage3D function. Must be <constant>GL_TEXTURE_3D</constant>,
    <constant>GL_TEXTURE_2D_ARRAY</constant> or
    <constant>GL_TEXTURE_CUBE_MAP_ARRAY</constant>.
    2. `int` `$level` Specifies the level-of-detail number. Level 0 is the base
    image level. Level n is the nth mipmap reduction image.
    3. `int` `$xoffset` Specifies a texel offset in the x direction within the
    texture array.
    4. `int` `$yoffset` Specifies a texel offset in the y direction within the
    texture array.
    5. `int` `$zoffset` Specifies a texel offset in the z direction within the
    texture array.
    6. `int` `$x` Specify the window coordinates of the lower left corner of the
    rectangular region of pixels to be copied.
    7. `int` `$y` 
    8. `int` `$width` Specifies the width of the texture subimage.
    9. `int` `$height` Specifies the height of the texture subimage.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.