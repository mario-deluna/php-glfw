<?php 

glfwInit();

echo glfwGetVersionString() . PHP_EOL;

glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
$window = glfwCreateWindow(500, 500, "PHP GLFW Demo");

glfwMakeContextCurrent($window);
glfwSwapInterval(1);

// verticies
$verticies = [ 
	-0.5, -0.5, 0.0,
     0.5, -0.5, 0.0,
     0.0,  0.5, 0.0
];

$VBO; $VAO; 

// buffers
glGenBuffers(1, $VBO);
glBindBuffer(GL_ARRAY_BUFFER, $VBO);
glBufferData(GL_ARRAY_BUFFER, 0, $verticies, GL_STATIC_DRAW);

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