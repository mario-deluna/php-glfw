# glQueryCounter
record the GL time into a query object after all previous commands have
reached the GL server but have not yet necessarily executed.

```php
function glQueryCounter(int $id, int $target) : void
```



arguments

:    1. `int` `$id` Specify the name of a query object into which to record the GL
    time.
    2. `int` `$target` Specify the counter to query. target must be
    <constant>GL_TIMESTAMP</constant>.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.