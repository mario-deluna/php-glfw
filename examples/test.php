<?php 

glfwInit();

echo glfwGetVersionString();

$window = glfwCreateWindow(500, 500, "PHP GLFW");

glfwMakeContextCurrent($window);
glfwSwapInterval(1);

$i = 0;

var_dump($window);

while (!glfwWindowShouldClose($window))
{
	$i++;

    glClearColor(sin($i / 200), sin($i / 100), sin($i / 500), 1.0);      
	glClear();
    glfwSwapBuffers($window);
    glfwPollEvents();
}

glfwDestroyWindow($window);

glfwTerminate();