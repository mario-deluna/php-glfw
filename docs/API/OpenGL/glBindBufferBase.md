# glBindBufferBase
bind a buffer object to an indexed buffer target

```php
function glBindBufferBase(int $target, int $index, int $buffer) : void
```



arguments

:    1. `int` `$target` Specify the target of the bind operation. target must be
    one of <constant>GL_ATOMIC_COUNTER_BUFFER</constant>,
    <constant>GL_TRANSFORM_FEEDBACK_BUFFER</constant>,
    <constant>GL_UNIFORM_BUFFER</constant> or
    <constant>GL_SHADER_STORAGE_BUFFER</constant>.
    2. `int` `$index` Specify the index of the binding point within the array
    specified by target.
    3. `int` `$buffer` The name of a buffer object to bind to the specified
    binding point.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.