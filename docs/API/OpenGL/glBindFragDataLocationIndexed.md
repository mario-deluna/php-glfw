# glBindFragDataLocationIndexed
bind a user-defined varying out variable to a fragment shader color number
and index

```php
function glBindFragDataLocationIndexed(int $program, int $colorNumber, int $index, string $name) : void
```

arguments

:    1. `int` `$program` The name of the program containing varying out variable
    whose binding to modify
    2. `int` `$colorNumber` The color number to bind the user-defined varying out
    variable to
    3. `int` `$index` The index of the color input to bind the user-defined
    varying out variable to
    4. `string` `$name` The name of the user-defined varying out variable whose
    binding to modify

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.