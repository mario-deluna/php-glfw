# glBindTransformFeedback
bind a transform feedback object

```php
function glBindTransformFeedback(int $target, int $id) : void
```

arguments

:    1. `int` `$target` Specifies the target to which to bind the transform
    feedback object id. target must be
    <constant>GL_TRANSFORM_FEEDBACK</constant>.
    2. `int` `$id` Specifies the name of a transform feedback object reserved by
    glGenTransformFeedbacks.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.