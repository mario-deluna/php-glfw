# glBeginQuery
delimit the boundaries of a query object

```php
function glBeginQuery(int $target, int $id) : void
```

arguments

:    1. `int` `$target` Specifies the target type of query object established
    between glBeginQuery and the subsequent  glEndQuery. The symbolic constant
    must be one of <constant>GL_SAMPLES_PASSED</constant>,
    <constant>GL_ANY_SAMPLES_PASSED</constant>,
    <constant>GL_ANY_SAMPLES_PASSED_CONSERVATIVE</constant>,
    <constant>GL_PRIMITIVES_GENERATED</constant>,
    <constant>GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN</constant>, or
    <constant>GL_TIME_ELAPSED</constant>.
    2. `int` `$id` Specifies the name of a query object.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.