<?php 

namespace GL\Tests\Texture;

use GL\Texture\Texture2D;

class Texture2DTest extends \PHPUnit\Framework\TestCase
{
    public function testFromDisk() : void
    {
        // tests loading the php logo from disk and validatating a hash of the internal data
        $logo = Texture2D::fromDisk(__DIR__ . '/../../examples/phpglfwlogo.png');

        $this->assertEquals(512, $logo->width());
        $this->assertEquals(512, $logo->height());
        $this->assertEquals(3, $logo->channels());

        $buffer = $logo->buffer();
        $samples = [];
        foreach($buffer as $k => $val) {
            if ($k % 128 === 0) {
                $samples[] = $val;
            }
        }

        $this->assertEquals('a0bed380430adca3c3ddaec5e9142516', md5(implode('', $samples)));
    }
}