# glGetShaderPrecisionFormat
retrieve the range and precision for numeric formats supported by the shader
compiler

```php
function glGetShaderPrecisionFormat(int $shadertype, int $precisiontype, int &$range, int &$precision) : void
```

arguments

:    1. `int` `$shadertype` 
    2. `int` `$precisiontype` 
    3. `int` `$range` Specifies the address of array of two integers into which
    encodings of the implementation's numeric range are returned.
    4. `int` `$precision` Specifies the address of an integer into which the
    numeric precision of the implementation is written.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.