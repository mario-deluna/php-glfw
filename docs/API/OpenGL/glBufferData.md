# glBufferData
creates and initializes a buffer object's data store

```php
function glBufferData(int $target, \GL\Buffer\BufferInterface $buffer, int $usage) : void
```

!!! hint "PHP-GLFW Note"

    In the PHP extension this method has different signiture compared
    to the original.
    Instead of passing byte size and a pointer to the function, in PHP you pass a
    `GL\Buffer\BufferInterface` instance.

Example:
```php
$buffer = new GL\Buffer\FloatBuffer([
    // positions     // colors
    0.5, -0.5, 0.0,  1.0, 0.0, 0.0,  // bottom right
   -0.5, -0.5, 0.0,  0.0, 1.0, 0.0,  // bottom let
    0.0,  0.5, 0.0,  0.0, 0.0, 1.0   // top
]);

glGenVertexArrays(1, $VAO);
glGenBuffers(1, $VBO);
glBindVertexArray($VAO);
glBindBuffer(GL_ARRAY_BUFFER, $VBO);
glBufferData(GL_ARRAY_BUFFER, $buffer, GL_STATIC_DRAW);
```

arguments

:    1. `int` `$target` Specifies the target to which the buffer object is bound
    for glBufferData.
    2. `\GL\Buffer\BufferInterface` `$buffer` Specifies a buffer object
    containing the to be uploaded data.
    3. `int` `$usage` Specifies the expected usage pattern of the data store. The
    symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY,
    GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW,
    GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.