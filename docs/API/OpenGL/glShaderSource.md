# glShaderSource
Replaces the source code in a shader object.

```php
function glShaderSource(int $shader, string $source) : void
```

PHP-GLFW: As with PHP I don't see a reason to split up the shader source to
multiple addresses.
This is why the function in PHP is simplyfied.

arguments

:    1. `int` `$shader` Specifies the handle of the shader object whose source
    code is to be replaced.
    2. `string` `$source` Specifies a string containing the source code to be
    loaded into the shader.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.