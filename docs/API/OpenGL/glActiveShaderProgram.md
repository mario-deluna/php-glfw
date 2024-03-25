# glActiveShaderProgram
The `glActiveShaderProgram` function is used to set the active program object
for a program pipeline object. This function takes two integer arguments
`$pipeline` and `$program`. The pipeline parameter specifies the program
pipeline object, and the program parameter specifies the linked program to be
the active program.

```php
function glActiveShaderProgram(int $pipeline, int $program) : void
```

Here is an example usage of `glActiveShaderProgram`:

```php
$program = glCreateProgram();
glAttachShader($program, $vertexShader);
glAttachShader($program, $fragmentShader);
glLinkProgram($program);

$pipeline = glGenProgramPipelines();
glUseProgramStages($pipeline, GL_VERTEX_SHADER_BIT, $program);
glActiveShaderProgram($pipeline, $program);
```

Note that before calling `glActiveShaderProgram`, you should first create a
program object, attach shaders to it, link the program, and then create a
program pipeline object with
[`glGenProgramPipelines`](./glGenProgramPipelines.md). Also, make sure that
the program object referred to by `$program` has been successfully linked. If
not, `GL_INVALID_OPERATION` will be generated.

arguments

:    1. `int` `$pipeline` Specifies the program pipeline object to set the active
    program object for.
    2. `int` `$program` Specifies the program object to set as the active program
    pipeline object pipeline.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.