# glStencilFunc
set front and back function and reference value for stencil testing

```php
function glStencilFunc(int $func, int $ref, int $mask) : void
```

arguments

:    1. `int` `$func` Specifies the test function. Eight symbolic constants are
    valid: <constant>GL_NEVER</constant>, <constant>GL_LESS</constant>,
    <constant>GL_LEQUAL</constant>, <constant>GL_GREATER</constant>,
    <constant>GL_GEQUAL</constant>, <constant>GL_EQUAL</constant>,
    <constant>GL_NOTEQUAL</constant>, and <constant>GL_ALWAYS</constant>. The
    initial value is <constant>GL_ALWAYS</constant>.
    2. `int` `$ref` Specifies the reference value for the stencil test. ref is
    clamped to the range    0  2 n  - 1   , where n is the number of bitplanes in
    the stencil buffer. The initial value is 0.
    3. `int` `$mask` Specifies a mask that is ANDed with both the reference value
    and the stored stencil value when the test is done. The initial value is all
    1's.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.