<?php 

glfwInit();

echo glfwGetVersionString() . PHP_EOL;

// configure the window
glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// fix for macOs
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

// create the window
if (!$window = glfwCreateWindow(500, 500, "PHP GLFW Demo")) {
	die('Could not create window.');
}

// setup the window
glfwMakeContextCurrent($window);
glfwSwapInterval(1);

// verticies
$verticies = [ 
	-0.5, -0.5, 0.0,
     0.5, -0.5, 0.0,
     0.0,  0.5, 0.0
];

// setup the shaders
$vertexShader = glCreateShader(GL_VERTEX_SHADER);
glShaderSource($vertexShader, 1, "
#version 330 core
layout (location = 0) in vec3 aPos;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
");
glCompileShader($vertexShader);
glGetShaderiv($vertexShader, GL_COMPILE_STATUS, $success);

var_dump($success); die;
//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);

$VBO; $VAO; 

// buffers
glGenBuffers(1, $VBO);
glBindBuffer(GL_ARRAY_BUFFER, $VBO);
glBufferDataFloat(GL_ARRAY_BUFFER, $verticies, GL_STATIC_DRAW);

$i = 0;

while (!glfwWindowShouldClose($window))
{
	$i++;

    glClearColor(sin($i / 200), sin($i / 100), sin($i / 500), 1.0);      
	glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers($window);
    glfwPollEvents();
}

glfwDestroyWindow($window);

glfwTerminate();