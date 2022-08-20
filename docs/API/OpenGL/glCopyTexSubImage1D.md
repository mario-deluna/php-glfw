# glCopyTexSubImage1D
copy a one-dimensional texture subimage

```php
function glCopyTexSubImage1D(int $target, int $level, int $xoffset, int $x, int $y, int $width) : void
```

arguments

:    1. `int` `$target` Specifies the target to which the texture object is bound
    for glCopyTexSubImage1D function. Must be <constant>GL_TEXTURE_1D</constant>.
    2. `int` `$level` Specifies the level-of-detail number. Level 0 is the base
    image level. Level n is the nth mipmap reduction image.
    3. `int` `$xoffset` Specifies the texel offset within the texture array.
    4. `int` `$x` Specify the window coordinates of the left corner of the row of
    pixels to be copied.
    5. `int` `$y` 
    6. `int` `$width` Specifies the width of the texture subimage.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.