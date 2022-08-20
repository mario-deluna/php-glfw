# glStencilOpSeparate
set front and/or back stencil test actions

```php
function glStencilOpSeparate(int $face, int $sfail, int $dpfail, int $dppass) : void
```

arguments

:    1. `int` `$face` Specifies whether front and/or back stencil state is
    updated. Three symbolic constants are valid: <constant>GL_FRONT</constant>,
    <constant>GL_BACK</constant>, and <constant>GL_FRONT_AND_BACK</constant>.
    2. `int` `$sfail` Specifies the action to take when the stencil test fails.
    Eight symbolic constants are accepted: <constant>GL_KEEP</constant>,
    <constant>GL_ZERO</constant>, <constant>GL_REPLACE</constant>,
    <constant>GL_INCR</constant>, <constant>GL_INCR_WRAP</constant>,
    <constant>GL_DECR</constant>, <constant>GL_DECR_WRAP</constant>, and
    <constant>GL_INVERT</constant>. The initial value is
    <constant>GL_KEEP</constant>.
    3. `int` `$dpfail` Specifies the stencil action when the stencil test passes,
    but the depth test fails. dpfail accepts the same symbolic constants as
    sfail. The initial value is <constant>GL_KEEP</constant>.
    4. `int` `$dppass` Specifies the stencil action when both the stencil test
    and the depth test pass, or when the stencil test passes and either there is
    no depth buffer or depth testing is not enabled. dppass accepts the same
    symbolic constants as sfail. The initial value is
    <constant>GL_KEEP</constant>.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.