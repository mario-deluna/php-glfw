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

    public function testConstructorHex() : void
    {
        $color = VGColor::hex('#FF0000');
        $this->assertEqualsColor(1.0, 0.0, 0.0, 1.0, $color);

        // lowercase
        $color = VGColor::hex('#ff0000');
        $this->assertEqualsColor(1.0, 0.0, 0.0, 1.0, $color);

        // shorthand
        $color = VGColor::hex('#F00');
        $this->assertEqualsColor(1.0, 0.0, 0.0, 1.0, $color);

        // lowercase shorthand
        $color = VGColor::hex('#f00');
        $this->assertEqualsColor(1.0, 0.0, 0.0, 1.0, $color);
    
        // 8 digit
        $color = VGColor::hex('#FF000000');
        $this->assertEqualsColor(1.0, 0.0, 0.0, 0.0, $color);

        // without #
        $color = VGColor::hex('00FF00');
        $this->assertEqualsColor(0.0, 1.0, 0.0, 1.0, $color);

        // lowercase without #
        $color = VGColor::hex('0000ff');
        $this->assertEqualsColor(0.0, 0.0, 1.0, 1.0, $color);
    }

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

    public function testGetHSLA() : void
    {
        $color = VGColor::rgb(1.0, 0.0, 0.0);
        $hsla = $color->getHSLA();

        $this->assertEqualsWithDelta(0.0, $hsla->x, 0.005);
        $this->assertEqualsWithDelta(1.0, $hsla->y, 0.005);
        $this->assertEqualsWithDelta(0.5, $hsla->z, 0.005);
        $this->assertEqualsWithDelta(1.0, $hsla->w, 0.005);        
    }

    public function testGetHSL() : void
    {
        $color = VGColor::rgb(1.0, 0.0, 0.0);
        $hsl = $color->getHSL();

        $this->assertEqualsWithDelta(0.0, $hsl->x, 0.005);
        $this->assertEqualsWithDelta(1.0, $hsl->y, 0.005);
        $this->assertEqualsWithDelta(0.5, $hsl->z, 0.005);
    }

    public function testGetVec4() : void
    {
        $color = VGColor::rgba(0.1, 0.2, 0.3, 0.4);
        $vec4 = $color->getVec4();

        $this->assertEqualsWithDelta(0.1, $vec4->x, 0.005);
        $this->assertEqualsWithDelta(0.2, $vec4->y, 0.005);
        $this->assertEqualsWithDelta(0.3, $vec4->z, 0.005);
        $this->assertEqualsWithDelta(0.4, $vec4->w, 0.005);
    }

    public function testGetVec3() : void
    {
        $color = VGColor::rgb(0.1, 0.2, 0.3);
        $vec3 = $color->getVec3();

        $this->assertEqualsWithDelta(0.1, $vec3->x, 0.005);
        $this->assertEqualsWithDelta(0.2, $vec3->y, 0.005);
        $this->assertEqualsWithDelta(0.3, $vec3->z, 0.005);
    }

    public function testDarken() : void
    {
        $color = VGColor::hsl(0.5, 1.0, 0.5);
        $darker = $color->darken(0.1)->getHSL();

        $this->assertEqualsWithDelta(0.5, $darker->x, 0.005);
        $this->assertEqualsWithDelta(1.0, $darker->y, 0.005);
        $this->assertEqualsWithDelta(0.4, $darker->z, 0.005);
    }

    public function testLighten() : void
    {
        $color = VGColor::hsl(0.5, 1.0, 0.5);
        $lighter = $color->lighten(0.1)->getHSL();

        $this->assertEqualsWithDelta(0.5, $lighter->x, 0.005);
        $this->assertEqualsWithDelta(1.0, $lighter->y, 0.005);
        $this->assertEqualsWithDelta(0.6, $lighter->z, 0.005);
    }

    public function testInvert() : void
    {
        $color = VGColor::rgb(0.1, 0.2, 0.3);
        $inverted = $color->invert()->getVec3();

        $this->assertEqualsWithDelta(0.9, $inverted->x, 0.005);
        $this->assertEqualsWithDelta(0.8, $inverted->y, 0.005);
        $this->assertEqualsWithDelta(0.7, $inverted->z, 0.005);
    }

    public function testSerialize() : void
    {
        $color = VGColor::rgba(0.1, 0.2, 0.3, 0.4);
        $serialized = serialize($color);
        $color2 = unserialize($serialized);
        $this->assertEqualsColor(0.1, 0.2, 0.3, 0.4, $color2);
    }
}