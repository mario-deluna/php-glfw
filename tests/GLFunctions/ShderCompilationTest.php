<?php 

namespace GL\Tests\GLFunctions;

use GLFWwindow;
use SebastianBergmann\RecursionContext\InvalidArgumentException;
use PHPUnit\Framework\ExpectationFailedException;

/**
 * @group glfwinit
 */
class ShderCompilationTest extends GLFunctionsTestCase
{
    public function testShaderCompilation()
    {
        $vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource($vertexShader, "
        #version 400
        void main() {
            gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
        }");
        glCompileShader($vertexShader);
        glGetShaderiv($vertexShader, GL_COMPILE_STATUS, $success);
        $this->assertEquals(1, $success);
        glDeleteShader($vertexShader);
    }

    public function testReadingErrors()
    {
        $vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource($vertexShader, "
        #version 400
        void main() {
            gl_Position = vec4(0.0, 0.0, 0.0, 1.0).x;
        }");
        glCompileShader($vertexShader);
        glGetShaderiv($vertexShader, GL_COMPILE_STATUS, $success);
        $this->assertEquals(0, $success);

        // read lenght
	    glGetShaderiv($vertexShader, GL_INFO_LOG_LENGTH, $maxLength);
        $log = glGetShaderInfoLog($vertexShader, $maxLength);

        // check for the expected error
        $this->assertStringContainsString("0:4", $log);

        glDeleteShader($vertexShader);
    }

    public function testCompileAndLink()
    {
        $vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource($vertexShader, "
        #version 400
        void main() {
            gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
        }");
        glCompileShader($vertexShader);
        glGetShaderiv($vertexShader, GL_COMPILE_STATUS, $success);

        $this->assertEquals(1, $success);

        $fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource($fragmentShader, "
        #version 330 core
        out vec4 fragment_color;
        void main() {
            fragment_color = vec4(1.0, 1.0, 1.0, 1.0);
        }");
        glCompileShader($fragmentShader);
        glGetShaderiv($fragmentShader, GL_COMPILE_STATUS, $success);

        $this->assertEquals(1, $success);

        $shaderProgram = glCreateProgram();
        glAttachShader($shaderProgram, $vertexShader);
        glAttachShader($shaderProgram, $fragmentShader);
        glLinkProgram($shaderProgram);
        glGetProgramiv($shaderProgram, GL_LINK_STATUS, $linkSuccess)
        ;
        $this->assertEquals(1, $linkSuccess);

        glDeleteProgram($shaderProgram);
        glDeleteShader($vertexShader);
        glDeleteShader($fragmentShader);
    }
}