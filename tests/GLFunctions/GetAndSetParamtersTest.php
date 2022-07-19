<?php 

namespace GL\Tests\GLFunctions;

use GLFWwindow;

/**
 * @group glfwinit
 */
class GetAndSetParamtersTest extends GLFunctionsTestCase
{
    public function testGlGetBooleanv()
    {
        glGetBooleanv(GL_BLEND, $bool);
        $this->assertFalse($bool);
        
        glEnable(GL_BLEND);

        glGetBooleanv(GL_BLEND, $bool);
        $this->assertTrue($bool);

        glDisable(GL_BLEND);

        glGetBooleanv(GL_BLEND, $bool);
        $this->assertFalse($bool);
    }
}