<?php 

namespace GL\Tests\GLFunctions;

use GLFWwindow;

abstract class GLFunctionsTestCase extends \PHPUnit\Framework\TestCase
{
    protected bool $glfwInitialized = false;
    protected ?GLFWwindow $window = null;

    protected const TEST_VIEW_WIDTH = 480;
    protected const TEST_VIEW_HEIGHT = 360;

    protected function setUp() : void
    {
        if (!$this->glfwInitialized) 
        {
            $this->glfwInitialized = true;

            if (!glfwInit()) {
                throw new \Exception("Could not initalize glfw...");
            }
    
            // configure the window
            glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
            // offscreen
            glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
            glfwWindowHint(GLFW_COCOA_MENUBAR, GLFW_FALSE);
            glfwWindowHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
    
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
            // fix for macOs
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        }
        
        if (!$this->window) {
             // create the window
            $windowWidth = self::TEST_VIEW_WIDTH;
            $windowHeight = self::TEST_VIEW_HEIGHT;
            if (!$this->window = glfwCreateWindow($windowWidth, $windowHeight, "PHPUnit Offscreen")) {
                throw new \Exception("Could not open window...");
            }

            // setup the window
            glfwMakeContextCurrent($this->window);
        }
    }

    protected function tearDown() : void
    {
        if ($this->window) glfwDestroyWindow($this->window);
    }
}