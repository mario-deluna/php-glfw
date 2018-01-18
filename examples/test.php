<?php 

glfwInit();

$window = glfwCreateWindow(500, 500, "PHP GLFW");

sleep(1);
echo "running";
sleep(1);
echo "running";
sleep(1);
echo "running";
sleep(1);

glfwDestroyWindow($window);

#glfwTerminate();