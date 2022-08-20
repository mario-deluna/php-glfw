# glFenceSync
create a new sync object and insert it into the GL command stream

```php
function glFenceSync(int $condition, int $flags) : int
```

arguments

:    1. `int` `$condition` Specifies the condition that must be met to set the
    sync object's state to signaled. condition must be
    <constant>GL_SYNC_GPU_COMMANDS_COMPLETE</constant>.
    2. `int` `$flags` Specifies a bitwise combination of flags controlling the
    behavior of the sync object. No flags are presently defined for this
    operation and flags must be zero. flags is a placeholder for anticipated
    future extensions of fence sync object capabilities.

returns

:    `int` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.