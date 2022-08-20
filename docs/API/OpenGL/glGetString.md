# glGetString
return a string describing the current GL connection

```php
function glGetString(int $name) : string
```

arguments

:    1. `int` `$name` Specifies a symbolic constant, one of
    <constant>GL_VENDOR</constant>, <constant>GL_RENDERER</constant>,
    <constant>GL_VERSION</constant>, or
    <constant>GL_SHADING_LANGUAGE_VERSION</constant>. Additionally, glGetStringi
    accepts the <constant>GL_EXTENSIONS</constant> token.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.