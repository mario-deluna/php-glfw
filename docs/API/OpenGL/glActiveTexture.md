# glActiveTexture
select active texture unit

```php
function glActiveTexture(int $texture) : void
```



arguments

:    1. `int` `$texture` Specifies which texture unit to make active. The number
    of texture units is implementation dependent, but must be at least 80.
    texture must be one of <constant>GL_TEXTURE</constant>i, where i ranges from
    zero to the value of <constant>GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS</constant>
    minus one. The initial value is <constant>GL_TEXTURE0</constant>.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.