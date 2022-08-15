# glTexImage3DMultisample
establish the data storage, format, dimensions, and number of samples of a
multisample texture's image

```php
function glTexImage3DMultisample(int $target, int $samples, int $internalformat, int $width, int $height, int $depth, bool $fixedsamplelocations) : void
```



arguments

:    1. `int` `$target` Specifies the target of the operation. target must be
    <constant>GL_TEXTURE_2D_MULTISAMPLE_ARRAY</constant> or
    <constant>GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY</constant>.
    2. `int` `$samples` The number of samples in the multisample texture's image.
    3. `int` `$internalformat` The internal format to be used to store the
    multisample texture's image. internalformat must specify a color-renderable,
    depth-renderable, or stencil-renderable format.
    4. `int` `$width` The width of the multisample texture's image, in texels.
    5. `int` `$height` The height of the multisample texture's image, in texels.
    6. `int` `$depth` 
    7. `bool` `$fixedsamplelocations` Specifies whether the image will use
    identical sample locations and the same number of samples for all texels in
    the image, and the sample locations will not depend on the internal format or
    size of the image.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.