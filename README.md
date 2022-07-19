# PHP-GLFW

A fully-featured OpenGL and GLFW extension for PHP. Batteries included (Math Functions, Texture Loaders, etc..)

PHP-GLFW allows you to create 2D and 3D desktop applications in PHP. Bringing a whole different set of tools into the PHP world for real-time applications or simple rendering services. 

## 💡 Things to know when you start

PHP-GLFW tries to keep the core OpenGL / GLFW API as close to the original as possible and only do modifications to the API when necessary. This results in some functions being quite wired from a PHP point of view. Naming scheme:

| prefix | module   | desc                                                                                                                    |
|--------|----------|-------------------------------------------------------------------------------------------------------------------------|
| `gl`     | OpenGL   | Core OpenGL functions.<br> Examples: glClearColor, glEnable, glActiveTexture etc.                               |
| `glfw`   | GLFW     | GLFW library functions, everything to interact with the OS window, input.<br> Examples: glfwCreateWindow, glfwGetCursorPos, glfwSwapBuffers |
| `GL\`    | PHP-GLFW | Classes and functions in this namespace are custom to the extension, and are not default to OpenGL.<br> Examples: `GL\Buffer\FloatBuffer`, `GL\Math\Vec3` etc.. |


## ❓❓❓

<p align="center">
 <img src="https://media.giphy.com/media/lzQHOFIV9Cj5whBcOF/giphy.gif"/>
</p>

> Keep in mind this is a **gif** in reality this runs smoothly at 60fps.

## Notes / Disclaimer

Nobody asked for a library like this, and still, I delivered. Please don't spend a tremendous amount of time writing a "real game" in PHP with this. Just because its possible does not mean it is a good idea. I have no idea how you would ship/distribute such a game. Therefore this library hopefully serves an educational purpose for people who want to get into graphics programming and mainly work with PHP.

I am very far from being an expert with the Zend engine and the PHP internals. So there are pieces in this code that will make you want to pull out your hair from your head. My focus was to make this thing work at any cost, bugs, performance and memory leaks or even safe type conversions can be fixed later. (Or maybe never because again this is not supposed to create production applications with.) Many methods introduce a hell lot of overhead when it comes to copying or type conversations (I would love to buy you a beer here in Zürich if you can help me make this somehow efficient.).

Also, keep in mind I did not spend time making this failsafe in any way. When you pass unexpected types / values, you might end up with a segmentation fault.

I can't point this out enough this library is far from stable, and should **only** be used in _"just for fun"_ or _"because I can"_ and general _experimental_ type of projects. At least in its current state, who knows what the future brings.
 

## Installation

> Note: I only tested this extension on MacOS.

Make sure to install glfw3. 

```
$ brew install glfw3 
```

Clone the repository.

```
$ git clone https://github.com/mario-deluna/php-glfw/ && cd php-glfw
```

Now you should be able to build the extension:

```
$ phpize
$ ./configure --enable-glfw
$ make && make install
```

Don't forget to link the extension, by appending the following lines to your `php.ini`.

```
[glfw]
extension=glfw.so
```

## Example (Triangle)

Drawing the classic colored triangle. You can run this example: `php ./examples/triangle.php`

<img width="912" alt="screen shot 2018-05-09 at 20 32 01" src="https://user-images.githubusercontent.com/956212/39832883-c78e1606-53c8-11e8-9dcd-6f3015ca11d3.png">

**Code:**

```php
<?php

// initalize GLFW
glfwInit();
echo glfwGetVersionString() . PHP_EOL;

// configure the window
glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// fix for "el capitan"
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

// create the window
if (!$window = glfwCreateWindow(800, 800, "PHP GLFW Demo")) {
    die('Could not create window.');
}

// setup the window
glfwMakeContextCurrent($window);
glfwSwapInterval(1);

/**
 * Shader Setup
 */
// Vertext shader
$vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource($vertexShader, 1, "
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec4 pcolor;

void main()
{
    pcolor = vec4(color, 1.0f);
    gl_Position = vec4(position, 1.0f);
}
");
glCompileShader($vertexShader);
glGetShaderiv($vertexShader, GL_COMPILE_STATUS, $success);

if (!$success) {
    die("Vertex shader could not be compiled.");
}

// fragment shaders
$fragShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource($fragShader, 1, "
#version 330 core
out vec4 fragment_color;
in vec4 pcolor;

void main()
{
    fragment_color = pcolor;
} 
");
glCompileShader($fragShader);
glGetShaderiv($fragShader, GL_COMPILE_STATUS, $success);

if (!$success) {
    die("Fragment shader could not be compiled.");
}

// link the shaders
$shaderProgram = glCreateProgram();
glAttachShader($shaderProgram, $vertexShader);
glAttachShader($shaderProgram, $fragShader);
glLinkProgram($shaderProgram);

glGetProgramiv($shaderProgram, GL_LINK_STATUS, $linkSuccess);

if (!$linkSuccess) {
    die("Shader program could not be linked.");
}

// free the shders
glDeleteShader($vertexShader);
glDeleteShader($fragShader);

/**
 * Vertex creation
 */
// Buffers
$VBO; $VAO; 

// verticies
$verticies = [ 
     // positions      // colors
    0.5, -0.5, 0.0,  1.0, 0.0, 0.0,  // bottom right
   -0.5, -0.5, 0.0,  0.0, 1.0, 0.0,  // bottom let
    0.0,  0.5, 0.0,  0.0, 0.0, 1.0   // top 
];

glGenVertexArrays(1, $VAO);
glGenBuffers(1, $VBO);

glBindVertexArray($VAO);

glBindBuffer(GL_ARRAY_BUFFER, $VBO);
glBufferDataFloat(GL_ARRAY_BUFFER, $verticies, GL_STATIC_DRAW);

// positions
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6, 0);
glEnableVertexAttribArray(0);

// colors
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6, 3);
glEnableVertexAttribArray(1);

// unbind
glBindBuffer(GL_ARRAY_BUFFER, 0); 
glBindVertexArray(0); 

/**
 * Main loop
 */
while (!glfwWindowShouldClose($window))
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // use the shader
    glUseProgram($shaderProgram);

    // draw our vertex array
    glBindVertexArray($VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // swap
    glfwSwapBuffers($window);
    glfwPollEvents();
}

// stop & cleanup
glDeleteVertexArrays(1, $VAO);
glDeleteBuffers(1, $VBO);

glfwDestroyWindow($window);

glfwTerminate();
```

## Whats inside?

This extension does not only deliver glfw and OpenGL bindings, but it also comes with `stb_image` to make getting started easy.

## API Differences

I have tried to keep the API as similar as possible to the original C API of glfw and OpenGL, but I had to change some things to make this work quickly with PHP. 

### GLFW 

#### glfwMakeContextCurrent

This method will automatically load the **glad** function pointers.

### OpenGL

#### glShaderSource

The last argument the `length` has been removed from the `glShaderSource` function. When you want to add multiple, simply use null termination, or just call the method multiple times.

#### glBufferData

The `glBufferData` method has been disabled and is replaced with multiple type specific buffer methods:
 
 * glBufferDataFloat
 * glBufferDataDouble
 * glBufferDataInt
 * glBufferDataLong

Also, you do not need to pass in the size of your data this is solved by the type-specific methods itself.

```php
glBufferDataFloat(GL_ARRAY_BUFFER, [1.0, 0.5, 0.0], GL_STATIC_DRAW);
``` 

#### glVertexAttribPointer

In phpglfw, the `stride` (byte offset) and `pointer` offset of the vertex attributes is a pure number representing the count and not the size of the data. The size is then determined by the given type.

So this attribute pointer in C:

```c
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
```

Would be written in php be:

```php
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5, 3);
```
