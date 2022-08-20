# glBeginConditionalRender
start conditional rendering

```php
function glBeginConditionalRender(int $id, int $mode) : void
```

arguments

:    1. `int` `$id` Specifies the name of an occlusion query object whose results
    are used to determine if the rendering commands are discarded.
    2. `int` `$mode` Specifies how glBeginConditionalRender interprets the
    results of the occlusion query.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.