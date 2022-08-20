# glRenderbufferStorage
establish data storage, format and dimensions of a
    renderbuffer object's image

```php
function glRenderbufferStorage(int $target, int $internalformat, int $width, int $height) : void
```

arguments

:    1. `int` `$target` Specifies a binding target of the allocation for
    glRenderbufferStorage function. Must be <constant>GL_RENDERBUFFER</constant>.
    2. `int` `$internalformat` Specifies the internal format to use for the
    renderbuffer object's image.
    3. `int` `$width` Specifies the width of the renderbuffer, in pixels.
    4. `int` `$height` Specifies the height of the renderbuffer, in pixels.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.