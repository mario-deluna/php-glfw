# glDrawTransformFeedbackStream
render primitives using a count derived from a specifed stream of a transform
feedback object

```php
function glDrawTransformFeedbackStream(int $mode, int $id, int $stream) : void
```

arguments

:    1. `int` `$mode` Specifies what kind of primitives to render. Symbolic
    constants <constant>GL_POINTS</constant>, <constant>GL_LINE_STRIP</constant>,
    <constant>GL_LINE_LOOP</constant>, <constant>GL_LINES</constant>,
    <constant>GL_LINE_STRIP_ADJACENCY</constant>,
    <constant>GL_LINES_ADJACENCY</constant>,
    <constant>GL_TRIANGLE_STRIP</constant>, <constant>GL_TRIANGLE_FAN</constant>,
    <constant>GL_TRIANGLES</constant>,
    <constant>GL_TRIANGLE_STRIP_ADJACENCY</constant>,
    <constant>GL_TRIANGLES_ADJACENCY</constant>, and
    <constant>GL_PATCHES</constant> are accepted.
    2. `int` `$id` Specifies the name of a transform feedback object from which
    to retrieve a primitive count.
    3. `int` `$stream` Specifies the index of the transform feedback stream from
    which to retrieve a primitive count.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.