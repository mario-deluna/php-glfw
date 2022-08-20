# glGetQueryiv
return parameters of a query object target

```php
function glGetQueryiv(int $target, int $pname, int &$params) : void
```

arguments

:    1. `int` `$target` Specifies a query object target. Must be
    <constant>GL_SAMPLES_PASSED</constant>,
    <constant>GL_ANY_SAMPLES_PASSED</constant>,
    <constant>GL_ANY_SAMPLES_PASSED_CONSERVATIVE</constant>
    <constant>GL_PRIMITIVES_GENERATED</constant>,
    <constant>GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN</constant>,
    <constant>GL_TIME_ELAPSED</constant>, or <constant>GL_TIMESTAMP</constant>.
    2. `int` `$pname` Specifies the symbolic name of a query object target
    parameter. Accepted values are <constant>GL_CURRENT_QUERY</constant> or
    <constant>GL_QUERY_COUNTER_BITS</constant>.
    3. `int` `$params` Returns the requested data.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.