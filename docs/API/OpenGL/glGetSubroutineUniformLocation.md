# glGetSubroutineUniformLocation
retrieve the location of a subroutine uniform of a given shader stage within
a program

```php
function glGetSubroutineUniformLocation(int $program, int $shadertype, string $name) : int
```

arguments

:    1. `int` `$program` Specifies the name of the program containing shader
    stage.
    2. `int` `$shadertype` Specifies the shader stage from which to query for
    subroutine uniform index. shadertype must be one of
    <constant>GL_VERTEX_SHADER</constant>,
    <constant>GL_TESS_CONTROL_SHADER</constant>,
    <constant>GL_TESS_EVALUATION_SHADER</constant>,
    <constant>GL_GEOMETRY_SHADER</constant> or
    <constant>GL_FRAGMENT_SHADER</constant>.
    3. `string` `$name` Specifies the name of the subroutine uniform whose index
    to query.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.