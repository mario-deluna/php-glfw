<?php 

namespace GL\Tests\GLFunctions;

use GLFWwindow;

abstract class GLFunctionsTestCase extends \PHPUnit\Framework\TestCase
{
    protected GLFWwindow $window;

    protected function setUp() : void
    {
        glfwInit();

        // configure the window
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        // offscreen
        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // fix for macOs
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        // create the window
        $windowWidth = 480;
        $windowHeight = 360;
        if (!$this->window = glfwCreateWindow($windowWidth, $windowHeight, "PHPUnit Offscreen")) {
            throw new \Exception("Could not open window...");
        }

        // setup the window
        glfwMakeContextCurrent($this->window);
    }

    protected function tearDown() : void
    {
        glfwDestroyWindow($this->window);
        glfwTerminate();
    }
}