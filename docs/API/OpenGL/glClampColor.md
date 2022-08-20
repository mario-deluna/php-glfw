# glClampColor
specify whether data read via glReadPixels should be clamped

```php
function glClampColor(int $target, int $clamp) : void
```

arguments

:    1. `int` `$target` Target for color clamping. target must be
    <constant>GL_CLAMP_READ_COLOR</constant>.
    2. `int` `$clamp` Specifies whether to apply color clamping. clamp must be
    <constant>GL_TRUE</constant> or <constant>GL_FALSE</constant>.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.