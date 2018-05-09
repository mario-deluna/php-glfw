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