# glGetShaderInfoLog
Returns the information log for a shader object

```php
function glGetShaderInfoLog(int $shader, int $bufSize) : string
```

!!! hint "PHP-GLFW Note"

    In the PHP extension this function directly returns the error
    string instead of being passed by reference as an argument.

arguments

:    1. `int` `$shader` Specifies the shader object whose information log is to be
    queried.
    2. `int` `$bufSize` Specifies the size of the character buffer for storing
    the returned information log.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.