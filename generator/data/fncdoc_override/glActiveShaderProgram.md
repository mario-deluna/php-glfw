The `glActiveShaderProgram` function is used to set the active program object for a program pipeline object. This function takes two integer arguments `$pipeline` and `$program`. The pipeline parameter specifies the program pipeline object, and the program parameter specifies the linked program to be the active program. 

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

Note that before calling `glActiveShaderProgram`, you should first create a program object, attach shaders to it, link the program, and then create a program pipeline object with  [`glGenProgramPipelines`](./glGenProgramPipelines.md). Also, make sure that the program object referred to by `$program` has been successfully linked. If not, `GL_INVALID_OPERATION` will be generated.