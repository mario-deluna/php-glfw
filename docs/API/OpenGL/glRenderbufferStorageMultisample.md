# glRenderbufferStorageMultisample
establish data storage, format, dimensions and sample count of
    a renderbuffer object's image

```php
function glRenderbufferStorageMultisample(int $target, int $samples, int $internalformat, int $width, int $height) : void
```



arguments

:    1. `int` `$target` Specifies a binding target of the allocation for
    glRenderbufferStorageMultisample function. Must be
    <constant>GL_RENDERBUFFER</constant>.
    2. `int` `$samples` Specifies the number of samples to be used for the
    renderbuffer object's storage.
    3. `int` `$internalformat` Specifies the internal format to use for the
    renderbuffer object's image.
    4. `int` `$width` Specifies the width of the renderbuffer, in pixels.
    5. `int` `$height` Specifies the height of the renderbuffer, in pixels.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.