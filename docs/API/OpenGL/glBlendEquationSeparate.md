# glBlendEquationSeparate
set the RGB blend equation and the alpha blend equation separately

```php
function glBlendEquationSeparate(int $modeRGB, int $modeAlpha) : void
```



arguments

:    1. `int` `$modeRGB` specifies the RGB blend equation, how the red, green, and
    blue components of the source and destination colors are combined. It must be
    <constant>GL_FUNC_ADD</constant>, <constant>GL_FUNC_SUBTRACT</constant>,
    <constant>GL_FUNC_REVERSE_SUBTRACT</constant>, <constant>GL_MIN</constant>,
    <constant>GL_MAX</constant>.
    2. `int` `$modeAlpha` specifies the alpha blend equation, how the alpha
    component of the source and destination colors are combined. It must be
    <constant>GL_FUNC_ADD</constant>, <constant>GL_FUNC_SUBTRACT</constant>,
    <constant>GL_FUNC_REVERSE_SUBTRACT</constant>, <constant>GL_MIN</constant>,
    <constant>GL_MAX</constant>.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.