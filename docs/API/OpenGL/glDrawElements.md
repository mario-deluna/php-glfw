# glDrawElements
render primitives from array data using element indices

```php
function glDrawElements(int $mode, int $count, int $type, int|\GL\Buffer\UIntBuffer|\GL\Buffer\UShortBuffer|\GL\Buffer\UByteBuffer $indices) : void
```

!!! hint "PHP-GLFW Note"

    In the PHP extension this method supports both buffer objects and
    integer offsets.
    When using an Element Array Buffer (bound to GL_ELEMENT_ARRAY_BUFFER), pass
    an integer offset.
    When drawing without binding an element buffer, pass a UIntBuffer,
    UShortBuffer, or UByteBuffer containing the indices.

Example:
```php
// define vertices for a rectangle using two triangles
$vertices = new GL\Buffer\FloatBuffer([
    // positions     // colors
    0.5,  0.5, 0.0,  1.0, 0.0, 0.0,  // top right
    0.5, -0.5, 0.0,  0.0, 1.0, 0.0,  // bottom right
   -0.5, -0.5, 0.0,  0.0, 0.0, 1.0,  // bottom left
   -0.5,  0.5, 0.0,  1.0, 1.0, 0.0   // top left
]);

// define indices to form two triangles
$indices = new GL\Buffer\UIntBuffer([
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
]);

glGenVertexArrays(1, $VAO);
glGenBuffers(1, $VBO);
glGenBuffers(1, $EBO);

glBindVertexArray($VAO);
glBindBuffer(GL_ARRAY_BUFFER, $VBO);
glBufferData(GL_ARRAY_BUFFER, $vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, $EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, $indices, GL_STATIC_DRAW);

// ... set up vertex attributes ...

// draw the rectangle using indices
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

arguments

:    1. `int` `$mode` Specifies what kind of primitives to render. Symbolic
    constants GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES,
    GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP,
    GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY,
    GL_TRIANGLES_ADJACENCY and GL_PATCHES are accepted.
    2. `int` `$count` Specifies the number of elements to be rendered.
    3. `int` `$type` Specifies the type of the values in indices. Must be one of
    GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.
    4. `int|\GL\Buffer\UIntBuffer|\GL\Buffer\UShortBuffer|\GL\Buffer\UByteBuffer` `$indices` Specifies a buffer object containing the indices, or an offset into
    the currently bound element array buffer.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.