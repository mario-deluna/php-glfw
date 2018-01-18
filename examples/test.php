<?php 

glfwInit();

$window = glfwCreateWindow(500, 500, "PHP GLFW");

glfwMakeContextCurrent($window);

while (!glfwWindowShouldClose($window))
{
    // glfwSwapBuffers(window);
    glfwPollEvents();
}

glfwDestroyWindow($window);

glfwTerminate();