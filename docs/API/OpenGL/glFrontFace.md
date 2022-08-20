# glFrontFace
define front- and back-facing polygons

```php
function glFrontFace(int $mode) : void
```

arguments

:    1. `int` `$mode` Specifies the orientation of front-facing polygons.
    <constant>GL_CW</constant> and <constant>GL_CCW</constant> are accepted. The
    initial value is <constant>GL_CCW</constant>.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.