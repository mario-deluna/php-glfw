# glWaitSync
instruct the GL server to block until the specified sync object becomes
signaled

```php
function glWaitSync(int $sync, int $flags, int $timeout) : void
```

arguments

:    1. `int` `$sync` Specifies the sync object whose status to wait on.
    2. `int` `$flags` A bitfield controlling the command flushing behavior. flags
    may be zero.
    3. `int` `$timeout` Specifies the timeout that the server should wait before
    continuing. timeout must be <constant>GL_TIMEOUT_IGNORED</constant>.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.