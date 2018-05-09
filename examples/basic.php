<?php require 'vendor/autoload.php';

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
if (!$window = glfwCreateWindow(600, 600, "PHP GLFW Demo")) {
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

out vec3 pcolor;

void main()
{
	gl_Position = vec4(position, 1.0f);
	pcolor = position;
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

in vec3 pcolor;

uniform float time;

float cvalue(float speed, float m)
{
	return ((cos(time / speed) + 1) / 2) * m;
}

float svalue(float speed, float m)
{
	return ((sin(time / speed) + 1) / 2) * m;
}

void main()
{
	vec2 resolution = vec2(600 + cvalue(5.0f, 400.0f), 600 + cvalue(5.0f, 400.0f));

	vec3 colorA = vec3(cvalue(5.0f, 1.0f), svalue(2.0f, 1.0f), svalue(10.0f, 1.0f));
	vec3 colorB = vec3(svalue(7.0f, 1.0f), svalue(8.0f, 1.0f), cvalue(5.0f, 1.0f));

	float mixv = distance(
		gl_FragCoord.xy / resolution.xy, 
		vec2(cos(time) + 1, sin(time) + 1)
	);
	vec3 color = mix(colorA, colorB, mixv);

	fragment_color = vec4(color, 1.0f);
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
$VBO; $VAO; $EBO; 

// verticies
$verticies = [ 
	 1.0,  1.0, 0.0,
     1.0, -1.0, 0.0,
    -1.0, -1.0, 0.0,
    -1.0,  1.0, 0.0,
];

$indicies = [
	0, 1, 3, // first triangle
    1, 2, 3  // second triangle
];

glGenVertexArrays(1, $VAO);
glGenBuffers(1, $VBO);
glGenBuffers(1, $EBO);

glBindVertexArray($VAO);

glBindBuffer(GL_ARRAY_BUFFER, $VBO);
glBufferDataFloat(GL_ARRAY_BUFFER, $verticies, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, $EBO);
glBufferDataInt(GL_ELEMENT_ARRAY_BUFFER, $indicies, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3, 0);
glEnableVertexAttribArray(0);

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

	// forward the time to the shader
	glUniform1f(glGetUniformLocation($shaderProgram, "time"), glfwGetTime());

	// draw our vertex array
	glBindVertexArray($VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	// swap
    glfwSwapBuffers($window);
    glfwPollEvents();
}

// stop & cleanup
glDeleteVertexArrays(1, $VAO);
glDeleteBuffers(1, $VBO);
glDeleteBuffers(1, $EBO);

glfwDestroyWindow($window);

glfwTerminate();