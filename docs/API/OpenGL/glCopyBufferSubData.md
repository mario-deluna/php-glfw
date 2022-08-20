# glCopyBufferSubData
copy all or part of the data store of a buffer object to the data store of
another buffer object

```php
function glCopyBufferSubData(int $readTarget, int $writeTarget, int $readOffset, int $writeOffset, int $size) : void
```

arguments

:    1. `int` `$readTarget` Specifies the target to which the source buffer object
    is bound for glCopyBufferSubData
    2. `int` `$writeTarget` Specifies the target to which the destination buffer
    object is bound for glCopyBufferSubData.
    3. `int` `$readOffset` Specifies the offset, in basic machine units, within
    the data store of the source buffer object at which data will be read.
    4. `int` `$writeOffset` Specifies the offset, in basic machine units, within
    the data store of the destination buffer object at which data will be
    written.
    5. `int` `$size` Specifies the size, in basic machine units, of the data to
    be copied from the source buffer object to the destination buffer object.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.