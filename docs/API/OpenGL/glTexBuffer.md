# glTexBuffer
attach a buffer object's data store to a buffer texture object

```php
function glTexBuffer(int $target, int $internalformat, int $buffer) : void
```

arguments

:    1. `int` `$target` Specifies the target to which the texture is bound for
    glTexBuffer. Must be <constant>GL_TEXTURE_BUFFER</constant>.
    2. `int` `$internalformat` Specifies the internal format of the data in the
    store belonging to buffer.
    3. `int` `$buffer` Specifies the name of the buffer object whose storage to
    attach to the active buffer texture.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.