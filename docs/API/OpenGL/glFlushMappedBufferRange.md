# glFlushMappedBufferRange
indicate modifications to a range of a mapped buffer

```php
function glFlushMappedBufferRange(int $target, int $offset, int $length) : void
```

arguments

:    1. `int` `$target` Specifies the target to which the buffer object is bound
    for glFlushMappedBufferRange, which must be one of the buffer binding targets
    in the following table:
    2. `int` `$offset` Specifies the start of the buffer subrange, in basic
    machine units.
    3. `int` `$length` Specifies the length of the buffer subrange, in basic
    machine units.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.