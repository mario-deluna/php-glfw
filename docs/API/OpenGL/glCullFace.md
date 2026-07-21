# glCullFace
specify whether front- or back-facing facets can be culled

```php
function glCullFace(int $mode) : void
```

arguments

:    1. `int` `$mode` Specifies whether front- or back-facing facets are
    candidates for culling. Symbolic constants <constant>GL_FRONT</constant>,
    <constant>GL_BACK</constant>, and <constant>GL_FRONT_AND_BACK</constant> are
    accepted. The initial value is <constant>GL_BACK</constant>.

returns

:    `void` 

---

 

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.