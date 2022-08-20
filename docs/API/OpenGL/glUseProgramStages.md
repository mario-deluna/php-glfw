# glUseProgramStages
bind stages of a program object to a program pipeline

```php
function glUseProgramStages(int $pipeline, int $stages, int $program) : void
```

arguments

:    1. `int` `$pipeline` Specifies the program pipeline object to which to bind
    stages from program.
    2. `int` `$stages` Specifies a set of program stages to bind to the program
    pipeline object.
    3. `int` `$program` Specifies the program object containing the shader
    executables to use in pipeline.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.