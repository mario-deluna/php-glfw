# glBlendFunc
specify pixel arithmetic

```php
function glBlendFunc(int $sfactor, int $dfactor) : void
```

arguments

:    1. `int` `$sfactor` Specifies how the red, green, blue, and alpha source
    blending factors are computed. The initial value is
    <constant>GL_ONE</constant>.
    2. `int` `$dfactor` Specifies how the red, green, blue, and alpha destination
    blending factors are computed. The following symbolic constants are accepted:
    <constant>GL_ZERO</constant>, <constant>GL_ONE</constant>,
    <constant>GL_SRC_COLOR</constant>,
    <constant>GL_ONE_MINUS_SRC_COLOR</constant>,
    <constant>GL_DST_COLOR</constant>,
    <constant>GL_ONE_MINUS_DST_COLOR</constant>,
    <constant>GL_SRC_ALPHA</constant>,
    <constant>GL_ONE_MINUS_SRC_ALPHA</constant>,
    <constant>GL_DST_ALPHA</constant>,
    <constant>GL_ONE_MINUS_DST_ALPHA</constant>.
    <constant>GL_CONSTANT_COLOR</constant>,
    <constant>GL_ONE_MINUS_CONSTANT_COLOR</constant>,
    <constant>GL_CONSTANT_ALPHA</constant>, and
    <constant>GL_ONE_MINUS_CONSTANT_ALPHA</constant>. The initial value is
    <constant>GL_ZERO</constant>.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.