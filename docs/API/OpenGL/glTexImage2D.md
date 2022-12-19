# glTexImage2D
specify a two-dimensional texture image

```php
function glTexImage2D(int $target, int $level, int $internalformat, int $width, int $height, int $border, int $format, int $type, ?\GL\Buffer\BufferInterface $data) : void
```

!!! hint "PHP-GLFW Note"

    for This function has been modified to accept a `BufferInterface`
    object instead of a pointer.
    Also in this PHP OpenGL extension, the arguments are validated against the
    passed buffer object. If the buffer object is too small for the given width,
    height, and format an exception is thrown. This is done to prevent segfaults,
    this will unfortunately, make the function quite a bit slower. But as
    uploading textures is anyway a heavy operation the impact should not be
    noticeable in normal applications.

Example:

```php
glGenTextures(1, $texture);
glBindTexture(GL_TEXTURE_2D, $texture);

// we just create a simple 2x2 texture with 4 channels
$buffer = new GL\Buffer\UByteBuffer([
    255, 0, 0, 255,
    0, 255, 0, 255,
    0, 0, 255, 255,
    255, 255, 255, 255,
]);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE,
$buffer);
```

arguments

:    1. `int` `$target` Specifies the target texture. Must be
    <constant>GL_TEXTURE_2D</constant>, <constant>GL_PROXY_TEXTURE_2D</constant>,
    <constant>GL_TEXTURE_1D_ARRAY</constant>,
    <constant>GL_PROXY_TEXTURE_1D_ARRAY</constant>,
    <constant>GL_TEXTURE_RECTANGLE</constant>,
    <constant>GL_PROXY_TEXTURE_RECTANGLE</constant>,
    <constant>GL_TEXTURE_CUBE_MAP_POSITIVE_X</constant>,
    <constant>GL_TEXTURE_CUBE_MAP_NEGATIVE_X</constant>,
    <constant>GL_TEXTURE_CUBE_MAP_POSITIVE_Y</constant>,
    <constant>GL_TEXTURE_CUBE_MAP_NEGATIVE_Y</constant>,
    <constant>GL_TEXTURE_CUBE_MAP_POSITIVE_Z</constant>,
    <constant>GL_TEXTURE_CUBE_MAP_NEGATIVE_Z</constant>, or
    <constant>GL_PROXY_TEXTURE_CUBE_MAP</constant>.
    2. `int` `$level` Specifies the level-of-detail number. Level 0 is the base
    image level. Level n is the nth mipmap reduction image. If target is
    <constant>GL_TEXTURE_RECTANGLE</constant> or
    <constant>GL_PROXY_TEXTURE_RECTANGLE</constant>, level must be 0.
    3. `int` `$internalformat` Specifies the number of color components in the
    texture. Must be one of base internal formats given in Table 1, one of the
    sized internal formats given in Table 2, or one of the compressed internal
    formats given in Table 3, below.
    4. `int` `$width` Specifies the width of the texture image. All
    implementations support texture images that are at least 1024 texels wide.
    5. `int` `$height` Specifies the height of the texture image, or the number
    of layers in a texture array, in the case of the
    <constant>GL_TEXTURE_1D_ARRAY</constant> and
    <constant>GL_PROXY_TEXTURE_1D_ARRAY</constant> targets. All implementations
    support 2D texture images that are at least 1024 texels high, and texture
    arrays that are at least 256 layers deep.
    6. `int` `$border` This value must be 0.
    7. `int` `$format` Specifies the format of the pixel data. The following
    symbolic values are accepted: <constant>GL_RED</constant>,
    <constant>GL_RG</constant>, <constant>GL_RGB</constant>,
    <constant>GL_BGR</constant>, <constant>GL_RGBA</constant>,
    <constant>GL_BGRA</constant>, <constant>GL_RED_INTEGER</constant>,
    <constant>GL_RG_INTEGER</constant>, <constant>GL_RGB_INTEGER</constant>,
    <constant>GL_BGR_INTEGER</constant>, <constant>GL_RGBA_INTEGER</constant>,
    <constant>GL_BGRA_INTEGER</constant>, <constant>GL_STENCIL_INDEX</constant>,
    <constant>GL_DEPTH_COMPONENT</constant>,
    <constant>GL_DEPTH_STENCIL</constant>.
    8. `int` `$type` Specifies the data type of the pixel data. The following
    symbolic values are accepted: <constant>GL_UNSIGNED_BYTE</constant>,
    <constant>GL_BYTE</constant>, <constant>GL_UNSIGNED_SHORT</constant>,
    <constant>GL_SHORT</constant>, <constant>GL_UNSIGNED_INT</constant>,
    <constant>GL_INT</constant>, <constant>GL_HALF_FLOAT</constant>,
    <constant>GL_FLOAT</constant>, <constant>GL_UNSIGNED_BYTE_3_3_2</constant>,
    <constant>GL_UNSIGNED_BYTE_2_3_3_REV</constant>,
    <constant>GL_UNSIGNED_SHORT_5_6_5</constant>,
    <constant>GL_UNSIGNED_SHORT_5_6_5_REV</constant>,
    <constant>GL_UNSIGNED_SHORT_4_4_4_4</constant>,
    <constant>GL_UNSIGNED_SHORT_4_4_4_4_REV</constant>,
    <constant>GL_UNSIGNED_SHORT_5_5_5_1</constant>,
    <constant>GL_UNSIGNED_SHORT_1_5_5_5_REV</constant>,
    <constant>GL_UNSIGNED_INT_8_8_8_8</constant>,
    <constant>GL_UNSIGNED_INT_8_8_8_8_REV</constant>,
    <constant>GL_UNSIGNED_INT_10_10_10_2</constant>, and
    <constant>GL_UNSIGNED_INT_2_10_10_10_REV</constant>.
    9. `?\GL\Buffer\BufferInterface` `$data` 

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.