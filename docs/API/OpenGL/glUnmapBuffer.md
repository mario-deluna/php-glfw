# glUnmapBuffer
release the mapping of a buffer object's data store into the client's address
space

```php
function glUnmapBuffer(int $target) : bool
```



arguments

:    1. `int` `$target` Specifies the target to which the buffer object is bound
    for glUnmapBuffer, which must be one of the buffer binding targets in the
    following table:



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.