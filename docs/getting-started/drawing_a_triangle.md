# Drawing a triangle

Now things start to get a bit more interesting and we are going to draw our first triangle. We will use the same window from the previous example, so make sure you have that running.

<figure markdown>
  ![Trinagle drawn in OpenGL with PHP. (PHP-GLFW)](./drawing_a_triangle-01.png){ width="400" }
  <figcaption>Trinagle drawn in OpenGL with PHP</figcaption>
</figure>

!!! note "Full Source"

    This getting started tutorial is based on the examples provided with PHP-GLFW.<br> You can check out the complete source code here: [01_triangle.php](https://github.com/mario-deluna/php-glfw/blob/master/examples/01_triangle.php)


## Why a triangle?

Why draw a triangle? Well, it's the simplest geometry you can draw and it's a good starting point to get familiar with the rendering pipeline.
I honestly was kinda blown away when I realized that every object/model/mesh could be represented as a collection of triangles. (That sentence is going to make a few math people mad) but let me explain.

A square is made up of two triangles. A cube is made up of six squares, and so on. So if you can draw a triangle, you can draw anything. (Well, almost anything...)

![PHP-GLFW](./../docs-assets/php-glfw/getting_started/triangles.png){ width="100%"}

My next level drawing skills besides, lets talk about the rendering pipeline.

## The rendering pipeline

The rendering pipeline simplified, is a series of steps that are executed to transform a 3D model into a 2D image that can be displayed on the screen. The OpenGL pipeline in this example is divided into two parts, the vertex processing and fragment processing. There are many more steps/stages which we will not cover here to keep things simple. (If you are interested, you can read more about it [here](https://www.khronos.org/opengl/wiki/Rendering_Pipeline_Overview))

Each of these steps/stages is performed by a shader, a small program executed on the GPU. The vertex shader is executed for each vertex (point) in the your geometry, and the fragment shader is executed for each pixel on the screen.

![PHP-GLFW](./../docs-assets/php-glfw/getting_started/basic_pipeline.png){ width="100%"}

Some of these shaders can be programmed by the user. The GPU driver handles others. Shaders are written in a language called GLSL, which is a C-like language with some extensions to make it easier to write shaders.

In PHP-GLFW (PHP OpenGL) you still write your shaders in GLSL. We could have written a transpiler of some sort to convert PHP to GLSL, but that would have been a lot of work and would have made the library a lot more complex, and I also believe it would ultimately defeat the purpose. 

## Vertex arrays (VAO and VBO)

In order to draw a triangle, we need to define the vertices that make up the triangle. A vertex array is not necessarily just an array of vertex positions. It can also contain other information such as color, texture coordinates, normals, etc. 

Note the vertex array object (_VAO_) does not directly store the vertices. It holds the state of the vertex array. For example, the _VAO_ stores the vertex attribute configuration, which tells the GPU how to interpret the vertex data. The actual vertex data is stored in the vertex buffer object (_VBO_), which is really just a blob of data.

```php
// create a vertex array (VertextArrayObject -> VAO)
glGenVertexArrays(1, $VAO);

// create a buffer for our vertices (VertextBufferObject -> VBO)
glGenBuffers(1, $VBO);

// bind the buffer to our VAO 
glBindVertexArray($VAO);
glBindBuffer(GL_ARRAY_BUFFER, $VBO);
```

So what is happing here? We are creating a vertex array object (_VAO_) using the [`glGenVertexArrays`](./../API/OpenGL/glGenVertexArrays.md) function. We are also creating a buffer for our vertices using the [`glGenBuffers`](./../API/OpenGL/glGenBuffers.md) function. Using the [`glBindVertexArray`](./../API/OpenGL/glBindVertexArray.md) and [`glBindBuffer`](./../API/OpenGL/glBindBuffer.md) functions we are binding the buffer (_VBO_) and our vertex array object (_VAO_) to the current context.

### Uploading the vertex data

PHP-GLFW provides a few helper classes to make it easier to upload data to the GPU. PHP unfortunately, doest really have built in tools to work with "real" arrays of data (like C/C++). So this extension comes with custom buffer classes that can be used to upload data to the GPU "directly".

So lets declare our triange vertices and upload them to the GPU using [`glBufferData`](./../API/OpenGL/glBufferData.md).

```{ .php .annotate }
$buffer = new \GL\Buffer\FloatBuffer([ # (1)!
   // positions     // colors
   0.5, -0.5, 0.0,  1.0, 0.0, 0.0,  // bottom right
  -0.5, -0.5, 0.0,  0.0, 1.0, 0.0,  // bottom let
   0.0,  0.5, 0.0,  0.0, 0.0, 1.0   // top 
]);

glBufferData(GL_ARRAY_BUFFER, $buffer, GL_STATIC_DRAW);
```

1.  The [FloatBuffer](./../API/Buffer/FloatBuffer.html) class is just one of many buffer helpers.
    Also available are:
    - [ByteBuffer](./../API/Buffer/ByteBuffer.html)
    - [UByteBuffer](./../API/Buffer/UByteBuffer.html)
    - [ShortBuffer](./../API/Buffer/ShortBuffer.html)
    - [UShortBuffer](./../API/Buffer/UShortBuffer.html)
    - [IntBuffer](./../API/Buffer/IntBuffer.html)
    - [UIntBuffer](./../API/Buffer/UIntBuffer.html)
    - [FloatBuffer](./../API/Buffer/FloatBuffer.html)
    - [HFloatBuffer](./../API/Buffer/HFloatBuffer.html)
    - [DoubleBuffer](./../API/Buffer/DoubleBuffer.html)


But what does the data actually mean? If not clear from the code here a visual representation of the data.

![PHP-GLFW](./../docs-assets/php-glfw/getting_started/colors_and_attributes.png){ width="100%"}

### Vertex attribute pointers

We now know how that buffer data is to be interpreted, but we still need to tell the GPU how to interpret the data. We do this by setting the vertex attribute pointers using the [`glVertexAttribPointer`](./../API/OpenGL/glVertexAttribPointer.md) function.

А vertex attribute pointer consists of 3 central values to allow the GPU to iterate over your vertex data. Lets assume a type uniform vertex buffer for now:

- `size` - The number of components per vertex attribute
- `stride` - The offset between consecutive vertex attributes
- `offset` - The offset of the first component of the vertex attribute


![PHP-GLFW](./../docs-assets/php-glfw/getting_started/vertex_attributes.png){ width="100%"}

Now in practive the [`glVertexAttribPointer`](./../API/OpenGL/glVertexAttribPointer.md) function is delcered like this:

```php
function glVertexAttribPointer(
  int $index,      // Specifies the index of the generic vertex attribute to be modified.
  int $size,       // Specifies the number of components
  int $type,       // Specifies the data type of each component
  bool $normalized,// Specifies whether fixed-point data values should be normalized
  int $stride,     // Specifies the byte offset between consecutive generic vertex attributes
  int $offset      // Specifies a offset of the first component of the first generic vertex attribute 
) : void
```

In case of our trinagle we have 6 components per vertex. The first 3 components are the position of the vertex and the last 3 components are the color of the vertex.

```php
// positions
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 6, 0);
glEnableVertexAttribArray(0);

// colors
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 6, GL_SIZEOF_FLOAT * 3);
glEnableVertexAttribArray(1);
```

`$stride` and `$offset` expects the number of bytes. PHP-GLFW exposes the size of the data types as constants. For example `GL_SIZEOF_FLOAT` is the size of a float in bytes. So you can simply multiply the number of components by the size of the data type to get the stride.

I know you probably did not expect a simple triangle to be so complicated. But this is the bare minimum you need to know to get started with OpenGL. In the next section we will look at the shaders.

## Shaders

As we already touch on in [the rendering pipeline](#the-rendering-pipeline), we need to cover two shading stages to render a triangle. The vertex shader and the fragment shader. The vertex shader is responsible for transforming the vertices into clip space. The fragment shader is responsible for calculating the color of each pixel.



**TO BE CONTINUED**

## Additional resources 

 1. [https://www.khronos.org/opengl/wiki/Vertex_Specification](https://www.khronos.org/opengl/wiki/Vertex_Specification)
 2. [http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/](http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/)
 3. [https://learnopengl.com/Getting-started/Hello-Triangle](https://learnopengl.com/Getting-started/Hello-Triangle)
