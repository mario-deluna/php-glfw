# glHint
specify implementation-specific hints

```php
function glHint(int $target, int $mode) : void
```

arguments

:    1. `int` `$target` Specifies a symbolic constant indicating the behavior to
    be controlled. <constant>GL_LINE_SMOOTH_HINT</constant>,
    <constant>GL_POLYGON_SMOOTH_HINT</constant>,
    <constant>GL_TEXTURE_COMPRESSION_HINT</constant>, and
    <constant>GL_FRAGMENT_SHADER_DERIVATIVE_HINT</constant> are accepted.
    2. `int` `$mode` Specifies a symbolic constant indicating the desired
    behavior. <constant>GL_FASTEST</constant>, <constant>GL_NICEST</constant>,
    and <constant>GL_DONT_CARE</constant> are accepted.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.