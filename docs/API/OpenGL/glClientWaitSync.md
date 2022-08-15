# glClientWaitSync
block and wait for a sync object to become signaled

```php
function glClientWaitSync(int $sync, int $flags, int $timeout) : int
```



arguments

:    1. `int` `$sync` The sync object whose status to wait on.
    2. `int` `$flags` A bitfield controlling the command flushing behavior. flags
    may be <constant>GL_SYNC_FLUSH_COMMANDS_BIT</constant>.
    3. `int` `$timeout` The timeout, specified in nanoseconds, for which the
    implementation should wait for sync to become signaled.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.