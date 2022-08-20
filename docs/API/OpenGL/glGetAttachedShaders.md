# glGetAttachedShaders
Returns the handles of the shader objects attached to a program object

```php
function glGetAttachedShaders(int $program, int $maxCount, int &$count, int &$shaders) : void
```

arguments

:    1. `int` `$program` Specifies the program object to be queried.
    2. `int` `$maxCount` Specifies the size of the array for storing the returned
    object names.
    3. `int` `$count` Returns the number of names actually returned in shaders.
    4. `int` `$shaders` Specifies an array that is used to return the names of
    attached shader objects.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.