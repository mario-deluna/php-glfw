<?php

// initalize GLFW
glfwInit();

// prints the GLFW version for the examples sake
echo glfwGetVersionString() . PHP_EOL;

// configure the window
glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

// make sure to set the GLFW context version to the same 
// version the GLFW extension has been compiled with, default 4.1
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// fix for macos "el capitan"
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

// glfwCreateWindow will initalizes a new window in which you can render,
// you can have multiple windows of course.
if (!$window = glfwCreateWindow(800, 800, "PHP GLFW Demo")) {
    die('Could not create window.');
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

/**
 * Shader Setup
 */
// Vertext shader
$vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource($vertexShader, "
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
glShaderSource($fragShader, "
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
glGenBuffers(2, $VBO, $VBO2);

var_dump($VBO, $VBO2);

die;

glBindVertexArray($VAO);

glBindBuffer(GL_ARRAY_BUFFER, $VBO);

$buffer = new \PGL\Buffer\FBuffer();
foreach($verticies as $v) {
    $buffer->push($v);
}

glBufferData(GL_ARRAY_BUFFER, $buffer, GL_STATIC_DRAW);

// positions
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 6, 0);
glEnableVertexAttribArray(0);

// colors
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 6, GL_SIZEOF_FLOAT * 3);
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
