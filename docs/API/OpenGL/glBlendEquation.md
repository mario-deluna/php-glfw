# glBlendEquation
specify the equation used for both the RGB blend equation and the Alpha blend
equation

```php
function glBlendEquation(int $mode) : void
```

arguments

:    1. `int` `$mode` specifies how source and destination colors are combined. It
    must be <constant>GL_FUNC_ADD</constant>,
    <constant>GL_FUNC_SUBTRACT</constant>,
    <constant>GL_FUNC_REVERSE_SUBTRACT</constant>, <constant>GL_MIN</constant>,
    <constant>GL_MAX</constant>.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.