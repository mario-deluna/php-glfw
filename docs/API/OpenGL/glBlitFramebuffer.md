# glBlitFramebuffer
copy a block of pixels from one framebuffer object to another

```php
function glBlitFramebuffer(int $srcX0, int $srcY0, int $srcX1, int $srcY1, int $dstX0, int $dstY0, int $dstX1, int $dstY1, int $mask, int $filter) : void
```



arguments

:    1. `int` `$srcX0` Specify the bounds of the source rectangle within the read
    buffer of the read framebuffer.
    2. `int` `$srcY0` 
    3. `int` `$srcX1` 
    4. `int` `$srcY1` 
    5. `int` `$dstX0` Specify the bounds of the destination rectangle within the
    write buffer of the write framebuffer.
    6. `int` `$dstY0` 
    7. `int` `$dstX1` 
    8. `int` `$dstY1` 
    9. `int` `$mask` The bitwise OR of the flags indicating which buffers are to
    be copied. The allowed flags are <constant>GL_COLOR_BUFFER_BIT</constant>,
    <constant>GL_DEPTH_BUFFER_BIT</constant> and
    <constant>GL_STENCIL_BUFFER_BIT</constant>.
    10. `int` `$filter` Specifies the interpolation to be applied if the image is
    stretched. Must be <constant>GL_NEAREST</constant> or
    <constant>GL_LINEAR</constant>.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.