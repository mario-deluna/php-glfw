# glUniformBlockBinding
assign a binding point to an active uniform block

```php
function glUniformBlockBinding(int $program, int $uniformBlockIndex, int $uniformBlockBinding) : void
```

arguments

:    1. `int` `$program` The name of a program object containing the active
    uniform block whose binding to assign.
    2. `int` `$uniformBlockIndex` The index of the active uniform block within
    program whose binding to assign.
    3. `int` `$uniformBlockBinding` Specifies the binding point to which to bind
    the uniform block with index uniformBlockIndex within program.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.