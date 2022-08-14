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
        $this->assertStringContainsString("Incompatible types (vec4 and float)", $log);

        glDeleteShader($vertexShader);
    }
}