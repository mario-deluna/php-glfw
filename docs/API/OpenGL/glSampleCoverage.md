# glSampleCoverage
specify multisample coverage parameters

```php
function glSampleCoverage(float $value, bool $invert) : void
```



arguments

:    1. `float` `$value` Specify a single floating-point sample coverage value.
    The value is clamped to the range    0 1  . The initial value is 1.0.
    2. `bool` `$invert` Specify a single boolean value representing if the
    coverage masks should be inverted.  <constant>GL_TRUE</constant> and
    <constant>GL_FALSE</constant> are accepted.  The initial value is
    <constant>GL_FALSE</constant>.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.