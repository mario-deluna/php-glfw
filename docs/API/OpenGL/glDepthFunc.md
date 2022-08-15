# glDepthFunc
specify the value used for depth buffer comparisons

```php
function glDepthFunc(int $func) : void
```



arguments

:    1. `int` `$func` Specifies the depth comparison function. Symbolic constants
    <constant>GL_NEVER</constant>, <constant>GL_LESS</constant>,
    <constant>GL_EQUAL</constant>, <constant>GL_LEQUAL</constant>,
    <constant>GL_GREATER</constant>, <constant>GL_NOTEQUAL</constant>,
    <constant>GL_GEQUAL</constant>, and <constant>GL_ALWAYS</constant> are
    accepted. The initial value is <constant>GL_LESS</constant>.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.