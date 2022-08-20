# glPolygonOffset
set the scale and units used to calculate depth values

```php
function glPolygonOffset(float $factor, float $units) : void
```

arguments

:    1. `float` `$factor` Specifies a scale factor that is used to create a
    variable depth offset for each polygon. The initial value is 0.
    2. `float` `$units` Is multiplied by an implementation-specific value to
    create a constant depth offset. The initial value is 0.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.