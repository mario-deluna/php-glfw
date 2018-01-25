<?php 

glfwInit();

echo glfwGetVersionString() . PHP_EOL;

glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
$window = glfwCreateWindow(500, 500, "PHP GLFW Demo");

glfwMakeContextCurrent($window);
glfwSwapInterval(1);

// verticies
$verticies = [ 
	-0.6, -0.4, 1.0, 0.0, 0.0,
    0.6, -0.4, 0.0, 1.0, 0.0,
    0.0, 0.6, 0.0, 0.0, 1.0,
];

// buffers
glGenBuffers(1, $vb);
glBindBuffer(GL_ARRAY_BUFFER, $vb);
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