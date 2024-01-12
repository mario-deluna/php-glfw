<?php 

namespace GL\Tests\VG;

use GL\VectorGraphics\VGColor;

class VGColorTest extends \PHPUnit\Framework\TestCase
{
    private function assertEqualsColor($x, $y, $z, $a, VGColor $color)
    {
        $this->assertEqualsWithDelta($x, $color->r, 0.005);
        $this->assertEqualsWithDelta($y, $color->g, 0.005);
        $this->assertEqualsWithDelta($z, $color->b, 0.005);
        $this->assertEqualsWithDelta($a, $color->a, 0.005);
    }

    public function testReadAndWriteProperties() : void
    {
        $color = new VGColor(0.1, 0.2, 0.3, 0.4);
        $this->assertEqualsColor(0.1, 0.2, 0.3, 0.4, $color);

        $color->r = 0.5;
        $color->g = 0.6;
        $color->b = 0.7;
        $color->a = 0.8;
        $this->assertEqualsColor(0.5, 0.6, 0.7, 0.8, $color);
    }

    public function testConstructorRGB() : void
    {
        $color = VGColor::rgb(0.1, 0.2, 0.3);
        $this->assertEqualsColor(0.1, 0.2, 0.3, 1.0, $color);
    }

    public function testConstructorRGBA() : void
    {
        $color = VGColor::rgba(0.1, 0.2, 0.3, 0.4);
        $this->assertEqualsColor(0.1, 0.2, 0.3, 0.4, $color);
    }

    // public function testConstructorHex() : void
    // {
    //     $color = VGColor::hex(0x123456);
    //     $this->assertEqualsColor(0.07, 0.20, 0.34, 1.0, $color);
    // }

    public function testConstructorIRGB() : void
    {
        $color = VGColor::irgb(10, 20, 30);
        $this->assertEqualsColor(0.039, 0.078, 0.117, 1.0, $color);
    }

    public function testConstructorIRGBA() : void
    {
        $color = VGColor::irgba(10, 20, 30, 40);
        $this->assertEqualsColor(0.039, 0.078, 0.117, 0.157, $color);
    }

    public function testConstructorHSL() : void
    {
        $color = VGColor::hsl(0, 1.0, 0.5);
        $this->assertEqualsColor(1.0, 0.0, 0.0, 1.0, $color);
    }

    public function testConstructorHSLA() : void
    {
        $color = VGColor::hsla(0, 1.0, 0.5, 0.4);
        $this->assertEqualsColor(1.0, 0.0, 0.0, 0.4, $color);
    }

    
}