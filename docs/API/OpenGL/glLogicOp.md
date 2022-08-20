# glLogicOp
specify a logical pixel operation for rendering

```php
function glLogicOp(int $opcode) : void
```

arguments

:    1. `int` `$opcode` Specifies a symbolic constant that selects a logical
    operation. The following symbols are accepted: <constant>GL_CLEAR</constant>,
    <constant>GL_SET</constant>, <constant>GL_COPY</constant>,
    <constant>GL_COPY_INVERTED</constant>, <constant>GL_NOOP</constant>,
    <constant>GL_INVERT</constant>, <constant>GL_AND</constant>,
    <constant>GL_NAND</constant>, <constant>GL_OR</constant>,
    <constant>GL_NOR</constant>, <constant>GL_XOR</constant>,
    <constant>GL_EQUIV</constant>, <constant>GL_AND_REVERSE</constant>,
    <constant>GL_AND_INVERTED</constant>, <constant>GL_OR_REVERSE</constant>, and
    <constant>GL_OR_INVERTED</constant>. The initial value is
    <constant>GL_COPY</constant>.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.