# glDrawArraysInstanced
draw multiple instances of a range of elements

```php
function glDrawArraysInstanced(int $mode, int $first, int $count, int $instancecount) : void
```



arguments

:    1. `int` `$mode` Specifies what kind of primitives to render. Symbolic
    constants <constant>GL_POINTS</constant>, <constant>GL_LINE_STRIP</constant>,
    <constant>GL_LINE_LOOP</constant>, <constant>GL_LINES</constant>,
    <constant>GL_TRIANGLE_STRIP</constant>, <constant>GL_TRIANGLE_FAN</constant>,
    <constant>GL_TRIANGLES</constant> <constant>GL_LINES_ADJACENCY</constant>,
    <constant>GL_LINE_STRIP_ADJACENCY</constant>,
    <constant>GL_TRIANGLES_ADJACENCY</constant>,
    <constant>GL_TRIANGLE_STRIP_ADJACENCY</constant> and
    <constant>GL_PATCHES</constant> are accepted.
    2. `int` `$first` Specifies the starting index in the enabled arrays.
    3. `int` `$count` Specifies the number of indices to be rendered.
    4. `int` `$instancecount` Specifies the number of instances of the specified
    range of indices to be rendered.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.