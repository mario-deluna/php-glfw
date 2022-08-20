# glCopyTexImage1D
copy pixels into a 1D texture image

```php
function glCopyTexImage1D(int $target, int $level, int $internalformat, int $x, int $y, int $width, int $border) : void
```

arguments

:    1. `int` `$target` Specifies the target texture. Must be
    <constant>GL_TEXTURE_1D</constant>.
    2. `int` `$level` Specifies the level-of-detail number. Level 0 is the base
    image level. Level n is the nth mipmap reduction image.
    3. `int` `$internalformat` Specifies the internal format of the texture. Must
    be one of the following symbolic constants:
    <constant>GL_COMPRESSED_RED</constant>,
    <constant>GL_COMPRESSED_RG</constant>,
    <constant>GL_COMPRESSED_RGB</constant>,
    <constant>GL_COMPRESSED_RGBA</constant>.
    <constant>GL_COMPRESSED_SRGB</constant>,
    <constant>GL_COMPRESSED_SRGB_ALPHA</constant>.
    <constant>GL_DEPTH_COMPONENT</constant>,
    <constant>GL_DEPTH_COMPONENT16</constant>,
    <constant>GL_DEPTH_COMPONENT24</constant>,
    <constant>GL_DEPTH_COMPONENT32</constant>,
    <constant>GL_STENCIL_INDEX8</constant>, <constant>GL_RED</constant>,
    <constant>GL_RG</constant>, <constant>GL_RGB</constant>,
    <constant>GL_R3_G3_B2</constant>, <constant>GL_RGB4</constant>,
    <constant>GL_RGB5</constant>, <constant>GL_RGB8</constant>,
    <constant>GL_RGB10</constant>, <constant>GL_RGB12</constant>,
    <constant>GL_RGB16</constant>, <constant>GL_RGBA</constant>,
    <constant>GL_RGBA2</constant>, <constant>GL_RGBA4</constant>,
    <constant>GL_RGB5_A1</constant>, <constant>GL_RGBA8</constant>,
    <constant>GL_RGB10_A2</constant>, <constant>GL_RGBA12</constant>,
    <constant>GL_RGBA16</constant>, <constant>GL_SRGB</constant>,
    <constant>GL_SRGB8</constant>, <constant>GL_SRGB_ALPHA</constant>, or
    <constant>GL_SRGB8_ALPHA8</constant>.
    4. `int` `$x` Specify the window coordinates of the left corner of the row of
    pixels to be copied.
    5. `int` `$y` 
    6. `int` `$width` Specifies the width of the texture image. The height of the
    texture image is 1.
    7. `int` `$border` Must be 0.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.