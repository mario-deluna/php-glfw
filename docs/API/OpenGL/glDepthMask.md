# glDepthMask
enable or disable writing into the depth buffer

```php
function glDepthMask(bool $flag) : void
```

arguments

:    1. `bool` `$flag` Specifies whether the depth buffer is enabled for writing.
    If flag is <constant>GL_FALSE</constant>, depth buffer writing is disabled.
    Otherwise, it is enabled. Initially, depth buffer writing is enabled.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.