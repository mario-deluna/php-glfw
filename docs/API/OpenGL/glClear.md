# glClear
clear buffers to preset values

```php
function glClear(int $mask) : void
```

arguments

:    1. `int` `$mask` Bitwise OR of masks that indicate the buffers to be cleared.
    The three masks are <constant>GL_COLOR_BUFFER_BIT</constant>,
    <constant>GL_DEPTH_BUFFER_BIT</constant>, and
    <constant>GL_STENCIL_BUFFER_BIT</constant>.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.