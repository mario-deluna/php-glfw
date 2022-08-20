# glGetSynciv
query the properties of a sync object

```php
function glGetSynciv(int $sync, int $pname, int $count, int &$length, int &$values) : void
```

arguments

:    1. `int` `$sync` Specifies the sync object whose properties to query.
    2. `int` `$pname` Specifies the parameter whose value to retrieve from the
    sync object specified in sync.
    3. `int` `$count` 
    4. `int` `$length` Specifies the address of an variable to receive the
    number of integers placed in values.
    5. `int` `$values` Specifies the address of an array to receive the values
    of the queried parameter.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.