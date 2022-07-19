<?php

// initalize GLFW
if (!glfwInit()) {
    throw new Exception('GLFW could not be initialized!');
}

// prints the GLFW version for the examples sake
echo glfwGetVersionString() . PHP_EOL;

// configure the window
glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

// make sure to set the GLFW context version to the same 
// version the GLFW extension has been compiled with, default 4.1
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// enable forward compatibitly, @see glfw docs for details
// but mostly this fixes an issue many expirence on MacOS
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

// glfwCreateWindow will initalizes a new window in which you can render,
// you can have multiple windows of course.
if (!$window = glfwCreateWindow(800, 800, "PHP GLFW Demo")) {
    throw new Exception('OS Window could not be initialized!');
}

// calling this method will make the given window object 
// the one that is bound to the current GL context. In other words
// all GL commands will be executed in the context of this window
// Special in PHP-GLFW is that this will also initialize glad.
glfwMakeContextCurrent($window);

// setting the swap interval to "1" basically enabled vsync. 
// more correctly it defines how many screen updates to wait for 
// after glfwSwapBuffers has been called 
glfwSwapInterval(1);

// Shader Setup
// ---------------------------------------------------------------------------- 

// create, upload and compile the vertex shader
$vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource($vertexShader, <<< 'GLSL'
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec4 pcolor;

void main()
{
    pcolor = vec4(color, 1.0f);
    gl_Position = vec4(position, 1.0f);
}
GLSL);
glCompileShader($vertexShader);
glGetShaderiv($vertexShader, GL_COMPILE_STATUS, $success);
if (!$success) {
    throw new Exception("Vertex shader could not be compiled.");
}

// create, upload and compile the fragment shader
$fragShader = glCreateShader(GL_FRAGMENT_SHADER);
glShaderSource($fragShader, <<<'GLSL'
#version 330 core
out vec4 fragment_color;
in vec4 pcolor;

void main()
{
    fragment_color = pcolor;
} 
GLSL);
glCompileShader($fragShader);
glGetShaderiv($fragShader, GL_COMPILE_STATUS, $success);
if (!$success) {
    throw new Exception("Fragment shader could not be compiled.");
}

// create a shader programm and link our vertex and framgent shader together
$shaderProgram = glCreateProgram();
glAttachShader($shaderProgram, $vertexShader);
glAttachShader($shaderProgram, $fragShader);
glLinkProgram($shaderProgram);

glGetProgramiv($shaderProgram, GL_LINK_STATUS, $linkSuccess);
if (!$linkSuccess) {
    throw new Exception("Shader program could not be linked.");
}

// free the shders
glDeleteShader($vertexShader);
glDeleteShader($fragShader);

// Buffer and data setup
// ---------------------------------------------------------------------------- 

// create a vertex array (VertextArrayObject -> VAO)
glGenVertexArrays(1, $VAO);

// create a buffer for our vertices (VertextBufferObject -> VBO)
glGenBuffers(1, $VBO);

// bind the buffer to our VAO 
glBindVertexArray($VAO);
glBindBuffer(GL_ARRAY_BUFFER, $VBO);

// declare vertices for a single triangle and the colors for each vertex
$buffer = new \GL\Buffer\FloatBuffer([ 
   // positions     // colors
   0.5, -0.5, 0.0,  1.0, 0.0, 0.0,  // bottom right
  -0.5, -0.5, 0.0,  0.0, 1.0, 0.0,  // bottom let
   0.0,  0.5, 0.0,  0.0, 0.0, 1.0   // top 
]);

// now we can upload our float buffer to the currently bound VBO
glBufferData(GL_ARRAY_BUFFER, $buffer, GL_STATIC_DRAW);

// in the next step we have to define the vertex attributes, in simpler
// words tell openGL how the data we just uploaded should be split and iterated over.

// positions
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 6, 0);
glEnableVertexAttribArray(0);

// colors
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 6, GL_SIZEOF_FLOAT * 3);
glEnableVertexAttribArray(1);

// unbind
glBindBuffer(GL_ARRAY_BUFFER, 0); 
glBindVertexArray(0); 


// Main Loop
// ---------------------------------------------------------------------------- 
// `glfwWindowShouldClose` returns true when the user clicks on the little 
// close button on the window, there probably are other triggers. But in short
// we simply loop forever until the window tells us it wants to close.
while (!glfwWindowShouldClose($window))
{
    // setting the clear color to black and clearing the color buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // use the shader
    glUseProgram($shaderProgram);

    // draw our vertex array
    glBindVertexArray($VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

// stop & cleanup
glDeleteVertexArrays(1, $VAO);
glDeleteBuffers(1, $VBO);

glfwDestroyWindow($window);

glfwTerminate();
