<?php

use GL\Buffer\FloatBuffer;

/**
 * To reduce the amount of boilerplate for each example this file contains
 * a collection of helpers / common code that is used by the examples.
 */
class ExampleHelper
{
    const WIN_WIDTH = 800;
    const WIN_HEIGHT = 600;

    /**
     * Initializes GLFW and creates a window.
     */
    public static function begin() : GLFWwindow
    {
        // initalize GLFW
        if (!glfwInit()) {
            throw new Exception('GLFW could not be initialized!');
        }

        // prints the GLFW version for the examples sake
        echo glfwGetVersionString() . PHP_EOL;

        // configure the window
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        // make sure to set the GLFW context version to the same 
        // version the GLFW extension has been compiled with, default 4.1
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // enable forward compatibitly, @see glfw docs for details
        // but mostly this fixes an issue many expirence on MacOS
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        // glfwCreateWindow will initalizes a new window in which you can render,
        // you can have multiple windows of course.
        if (!$window = glfwCreateWindow(self::WIN_WIDTH, self::WIN_HEIGHT, "PHP GLFW Demo")) {
            throw new Exception('OS Window could not be initialized!');
        }

        // calling this method will make the given window object 
        // the one that is bound to the current GL context. In other words
        // all GL commands will be executed in the context of this window
        // Special in PHP-GLFW is that this will also initialize glad.
        glfwMakeContextCurrent($window);

        // setting the swap interval to "1" basically enabled vsync. 
        // more correctly it defines how many screen updates to wait for 
        // after glfwSwapBuffers has been called 
        glfwSwapInterval(1);

        return $window;
    }

    /**
     * Terminates GLFW, destroys the window and frees all resources.
     */
    public static function stop(GLFWwindow $window) : void
    {
        glfwDestroyWindow($window);
        glfwTerminate();
    }

    /**
     * Compiles a basic shader program.
     */
    public static function compileShader(string $vertexShaderSource, string $fragmentShaderSource) : int
    {
        $vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource($vertexShader, $vertexShaderSource);
        glCompileShader($vertexShader);
        glGetShaderiv($vertexShader, GL_COMPILE_STATUS, $success);
        if (!$success) {
            throw new Exception("Vertex shader could not be compiled.");
        }

        // create, upload and compile the fragment shader
        $fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource($fragShader, $fragmentShaderSource);
        glCompileShader($fragShader);
        glGetShaderiv($fragShader, GL_COMPILE_STATUS, $success);
        if (!$success) {
            throw new Exception("Fragment shader could not be compiled.");
        }

        // create a shader programm and link our vertex and framgent shader together
        $shaderProgram = glCreateProgram();
        glAttachShader($shaderProgram, $vertexShader);
        glAttachShader($shaderProgram, $fragShader);
        glLinkProgram($shaderProgram);

        glGetProgramiv($shaderProgram, GL_LINK_STATUS, $linkSuccess);
        if (!$linkSuccess) {
            throw new Exception("Shader program could not be linked.");
        }

        // free the shders
        glDeleteShader($vertexShader);
        glDeleteShader($fragShader);

        return $shaderProgram;
    }

    /**
     * Creates a cube vertex buffer
     * Returns the VBO and VAO
     */
    public static function createCubeVBO()
    {
        $verticies = new FloatBuffer([ 
            -0.5, -0.5, -0.5,  0.0, 0.0,
             0.5, -0.5, -0.5,  1.0, 0.0,
             0.5,  0.5, -0.5,  1.0, 1.0,
             0.5,  0.5, -0.5,  1.0, 1.0,
            -0.5,  0.5, -0.5,  0.0, 1.0,
            -0.5, -0.5, -0.5,  0.0, 0.0,
        
            -0.5, -0.5,  0.5,  0.0, 0.0,
             0.5, -0.5,  0.5,  1.0, 0.0,
             0.5,  0.5,  0.5,  1.0, 1.0,
             0.5,  0.5,  0.5,  1.0, 1.0,
            -0.5,  0.5,  0.5,  0.0, 1.0,
            -0.5, -0.5,  0.5,  0.0, 0.0,
        
            -0.5,  0.5,  0.5,  1.0, 0.0,
            -0.5,  0.5, -0.5,  1.0, 1.0,
            -0.5, -0.5, -0.5,  0.0, 1.0,
            -0.5, -0.5, -0.5,  0.0, 1.0,
            -0.5, -0.5,  0.5,  0.0, 0.0,
            -0.5,  0.5,  0.5,  1.0, 0.0,
        
             0.5,  0.5,  0.5,  1.0, 0.0,
             0.5,  0.5, -0.5,  1.0, 1.0,
             0.5, -0.5, -0.5,  0.0, 1.0,
             0.5, -0.5, -0.5,  0.0, 1.0,
             0.5, -0.5,  0.5,  0.0, 0.0,
             0.5,  0.5,  0.5,  1.0, 0.0,
        
            -0.5, -0.5, -0.5,  0.0, 1.0,
             0.5, -0.5, -0.5,  1.0, 1.0,
             0.5, -0.5,  0.5,  1.0, 0.0,
             0.5, -0.5,  0.5,  1.0, 0.0,
            -0.5, -0.5,  0.5,  0.0, 0.0,
            -0.5, -0.5, -0.5,  0.0, 1.0,
        
            -0.5,  0.5, -0.5,  0.0, 1.0,
             0.5,  0.5, -0.5,  1.0, 1.0,
             0.5,  0.5,  0.5,  1.0, 0.0,
             0.5,  0.5,  0.5,  1.0, 0.0,
            -0.5,  0.5,  0.5,  0.0, 0.0,
            -0.5,  0.5, -0.5,  0.0, 1.0
        ]);
        
        // create a vertex array object and upload the vertices
        glGenVertexArrays(1, $VAO);
        glGenBuffers(1, $VBO);
        
        glBindVertexArray($VAO);
        glBindBuffer(GL_ARRAY_BUFFER, $VBO);
        glBufferData(GL_ARRAY_BUFFER, $verticies, GL_STATIC_DRAW);
        
        // declare the vertex attributes
        // positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 5, 0);
        glEnableVertexAttribArray(0);
        
        // uv
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 5, GL_SIZEOF_FLOAT * 3);
        glEnableVertexAttribArray(1);
        
        // unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 

        return [$VAO, $VBO];
    }
}