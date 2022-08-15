<?php 

namespace GL\Tests\Texture;

use GL\Texture\Texture2D;

class Texture2DTest extends \PHPUnit\Framework\TestCase
{
    public function testFromDisk() : void
    {
        // tests loading the php logo from disk and validatating a hash of the internal data
        $logo = Texture2D::fromDisk(__DIR__ . '/../../examples/phplogo.png');

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

        $this->assertEquals('410ab0a97d06be141419ae4e4695a536', md5(implode('', $samples)));
    }
}