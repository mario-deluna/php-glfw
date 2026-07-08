<?php

namespace GL\Tests\VG;

use GL\VectorGraphics\SVGImage;

class SVGImageTest extends \PHPUnit\Framework\TestCase
{
    private function makeImage() : SVGImage
    {
        return SVGImage::fromString('<svg width="100" height="40" xmlns="http://www.w3.org/2000/svg"><rect x="0" y="0" width="100" height="40" fill="#ff0000"/></svg>');
    }

    public function testDimensionsAreReadable() : void
    {
        $svg = $this->makeImage();
        $this->assertEqualsWithDelta(100.0, $svg->width, 0.005);
        $this->assertEqualsWithDelta(40.0, $svg->height, 0.005);
    }

    public function testDimensionsAreSet() : void
    {
        $svg = $this->makeImage();
        $this->assertTrue(isset($svg->width));
        $this->assertTrue(isset($svg->height));
    }

    public function testPropertiesAreDeclared() : void
    {
        $svg = $this->makeImage();
        $reflection = new \ReflectionObject($svg);
        $this->assertTrue($reflection->hasProperty('width'));
        $this->assertTrue($reflection->hasProperty('height'));
        $this->assertTrue($reflection->getProperty('width')->isReadOnly());
    }

    public function testWidthIsReadonly() : void
    {
        $svg = $this->makeImage();
        $this->expectException(\Error::class);
        $svg->width = 5.0;
    }

    public function testFromDiskLoadsFile() : void
    {
        $path = tempnam(sys_get_temp_dir(), 'phpglfw_svg') . '.svg';
        file_put_contents($path, '<svg width="123" height="45" xmlns="http://www.w3.org/2000/svg"><rect x="0" y="0" width="123" height="45" fill="#00ff00"/></svg>');

        try {
            $svg = SVGImage::fromDisk($path);
            $this->assertEqualsWithDelta(123.0, $svg->width, 0.005);
            $this->assertEqualsWithDelta(45.0, $svg->height, 0.005);
        } finally {
            @unlink($path);
        }
    }

    public function testFromDiskThrowsOnMissingFile() : void
    {
        $this->expectException(\Error::class);
        SVGImage::fromDisk(sys_get_temp_dir() . '/phpglfw_does_not_exist_' . uniqid() . '.svg');
    }
}
