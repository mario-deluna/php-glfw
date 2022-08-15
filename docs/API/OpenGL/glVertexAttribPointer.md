# glVertexAttribPointer
define an array of generic vertex attribute data

```php
function glVertexAttribPointer(int $index, int $size, int $type, bool $normalized, int $stride, int $offset) : void
```



arguments

:    1. `int` `$index` Specifies the index of the generic vertex attribute to be
    modified.
    2. `int` `$size` Specifies the number of components per generic vertex
    attribute. Must be 1, 2, 3, 4. Additionally, the symbolic constant
    <constant>GL_BGRA</constant> is accepted by glVertexAttribPointer. The
    initial value is 4.
    3. `int` `$type` Specifies the data type of each component in the array. The
    symbolic constants <constant>GL_BYTE</constant>,
    <constant>GL_UNSIGNED_BYTE</constant>, <constant>GL_SHORT</constant>,
    <constant>GL_UNSIGNED_SHORT</constant>, <constant>GL_INT</constant>, and
    <constant>GL_UNSIGNED_INT</constant> are accepted by glVertexAttribPointer
    and glVertexAttribIPointer. Additionally <constant>GL_HALF_FLOAT</constant>,
    <constant>GL_FLOAT</constant>, <constant>GL_DOUBLE</constant>,
    <constant>GL_FIXED</constant>, <constant>GL_INT_2_10_10_10_REV</constant>,
    <constant>GL_UNSIGNED_INT_2_10_10_10_REV</constant> and
    <constant>GL_UNSIGNED_INT_10F_11F_11F_REV</constant> are accepted by
    glVertexAttribPointer. <constant>GL_DOUBLE</constant> is also accepted by
    glVertexAttribLPointer and is the only token accepted by the type parameter
    for that function. The initial value is <constant>GL_FLOAT</constant>.
    4. `bool` `$normalized` For glVertexAttribPointer, specifies whether
    fixed-point data values should be normalized (<constant>GL_TRUE</constant>)
    or converted directly as fixed-point values (<constant>GL_FALSE</constant>)
    when they are accessed.
    5. `int` `$stride` Specifies the byte offset between consecutive generic
    vertex attributes. If stride is 0, the generic vertex attributes are
    understood to be tightly packed in the array. The initial value is 0.
    6. `int` `$offset` 



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.