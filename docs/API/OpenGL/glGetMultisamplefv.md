# glGetMultisamplefv
retrieve the location of a sample

```php
function glGetMultisamplefv(int $pname, int $index, float &$val) : void
```



arguments

:    1. `int` `$pname` Specifies the sample parameter name. pname must be
    <constant>GL_SAMPLE_POSITION</constant>.
    2. `int` `$index` Specifies the index of the sample whose position to query.
    3. `float` `$val` Specifies the address of an array to receive the position
    of the sample.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.