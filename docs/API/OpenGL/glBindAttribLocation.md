# glBindAttribLocation
Associates a generic vertex attribute index with a named attribute variable

```php
function glBindAttribLocation(int $program, int $index, string $name) : void
```

arguments

:    1. `int` `$program` Specifies the handle of the program object in which the
    association is to be made.
    2. `int` `$index` Specifies the index of the generic vertex attribute to be
    bound.
    3. `string` `$name` Specifies a null terminated string containing the name of
    the vertex shader attribute variable to which index is to be bound.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.