<?php 

namespace GL\Tests\GLFunctions;

use GLFWwindow;
use SebastianBergmann\RecursionContext\InvalidArgumentException;
use PHPUnit\Framework\ExpectationFailedException;

/**
 * @group glfwinit
 */
class GetAndSetParamtersTest extends GLFunctionsTestCase
{
    public function testGlEnableDisable()
    {   
        // just test a few common states with 
        // both glIsEnabled and glGetBooleanv
        foreach([
            GL_BLEND,
            GL_CULL_FACE,
            GL_DEPTH_TEST,
            GL_SCISSOR_TEST,
            GL_STENCIL_TEST
        ] as $const) {

            // intial state is disabled
            glGetBooleanv($const, $bool);
            $this->assertFalse($bool);
            $this->assertFalse(glIsEnabled($const));
            
            glEnable($const);
    
            glGetBooleanv($const, $bool);
            $this->assertTrue($bool);
            $this->assertTrue(glIsEnabled($const));
    
            glDisable($const);
    
            glGetBooleanv($const, $bool);
            $this->assertFalse($bool);
            $this->assertFalse(glIsEnabled($const));
        }
    }

    public function testGlGetDouble()
    {   
        // test by reading and writing the clear color
        glGetDoublev(GL_COLOR_CLEAR_VALUE, $red, $green, $blue, $alpha);

        $this->assertEqualsWithDelta(0.0, $red, 0.0001);
        $this->assertEqualsWithDelta(0.0, $green, 0.0001);
        $this->assertEqualsWithDelta(0.0, $blue, 0.0001);
        $this->assertEqualsWithDelta(0.0, $alpha, 0.0001);


        glClearColor(0.1, 0.2, 0.3, 0.4);
        glGetDoublev(GL_COLOR_CLEAR_VALUE, $red, $green, $blue, $alpha);

        $this->assertEqualsWithDelta(0.1, $red, 0.0001);
        $this->assertEqualsWithDelta(0.2, $green, 0.0001);
        $this->assertEqualsWithDelta(0.3, $blue, 0.0001);
        $this->assertEqualsWithDelta(0.4, $alpha, 0.0001);
    }

    /**
     * The same as testGlGetDouble but for glGetFloat
     */
    public function testGlGetFloat()
    {   
        // test by reading and writing the clear color
        glGetFloatv(GL_COLOR_CLEAR_VALUE, $red, $green, $blue, $alpha);

        $this->assertEqualsWithDelta(0.0, $red, 0.0001);
        $this->assertEqualsWithDelta(0.0, $green, 0.0001);
        $this->assertEqualsWithDelta(0.0, $blue, 0.0001);
        $this->assertEqualsWithDelta(0.0, $alpha, 0.0001);


        glClearColor(0.1, 0.2, 0.3, 0.4);
        glGetFloatv(GL_COLOR_CLEAR_VALUE, $red, $green, $blue, $alpha);

        $this->assertEqualsWithDelta(0.1, $red, 0.0001);
        $this->assertEqualsWithDelta(0.2, $green, 0.0001);
        $this->assertEqualsWithDelta(0.3, $blue, 0.0001);
        $this->assertEqualsWithDelta(0.4, $alpha, 0.0001);
    }

    public function testGlGetInteger()
    {  
        // try to read max vertex attribs to test glGetIntegerv
        // opengl promises us minium of 16 
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, $max);
        $this->assertGreaterThanOrEqual(16, $max);

        // read the viewport and change it
        glViewport(10, 20, 30, 40);
        glGetIntegerv(GL_VIEWPORT, $x, $y, $width, $height);
        $this->assertEquals(10, $x);
        $this->assertEquals(20, $y);
        $this->assertEquals(30, $width);
        $this->assertEquals(40, $height);

        // reset the viewport
        glViewport(0, 0, self::TEST_VIEW_WIDTH, self::TEST_VIEW_HEIGHT);
        // unesseary to test the viewport again, but it's a good test
        glGetIntegerv(GL_VIEWPORT, $x, $y, $width, $height);
        $this->assertEquals(0, $x);
        $this->assertEquals(0, $y);
        $this->assertEquals(self::TEST_VIEW_WIDTH, $width); 
        $this->assertEquals(self::TEST_VIEW_HEIGHT, $height);
    }

    public function testGlGetIntegeri_v()
    {  
        // in this test we also utilize the viewport to test glGetIntegeri_v
        glViewportIndexedf(0, 0, 0, self::TEST_VIEW_WIDTH, self::TEST_VIEW_HEIGHT);
        glViewportIndexedf(1, 50, 50, self::TEST_VIEW_WIDTH, self::TEST_VIEW_HEIGHT);
        glViewportIndexedf(2, 100, 100, 100, 100);

        glGetIntegeri_v(GL_VIEWPORT, 0, $x, $y, $width, $height);
        $this->assertEquals(0, $x);
        $this->assertEquals(0, $y);
        $this->assertEquals(self::TEST_VIEW_WIDTH, $width);
        $this->assertEquals(self::TEST_VIEW_HEIGHT, $height);

        glGetIntegeri_v(GL_VIEWPORT, 1, $x, $y, $width, $height);
        $this->assertEquals(50, $x);
        $this->assertEquals(50, $y);
        $this->assertEquals(self::TEST_VIEW_WIDTH, $width);
        $this->assertEquals(self::TEST_VIEW_HEIGHT, $height);

        glGetIntegeri_v(GL_VIEWPORT, 2, $x, $y, $width, $height);
        $this->assertEquals(100, $x);
        $this->assertEquals(100, $y);
        $this->assertEquals(100, $width);
        $this->assertEquals(100, $height);
    }

    public function testGlGetString()
    {
        $version = glGetString(GL_VERSION);
        $this->assertGreaterThan(1, strlen($version));
        
        $numOfExtensions = 0;
        glGetIntegerv(GL_NUM_EXTENSIONS, $numOfExtensions);

        // should be at least 1
        $this->assertGreaterThan(0, $numOfExtensions);

        // fetch the extension names
        for($i = 0; $i < $numOfExtensions; $i++) {
            $ext = glGetStringi(GL_EXTENSIONS, $i);
            // should be at least 1 char long
            $this->assertGreaterThan(0, strlen($ext));
        }
    }
}