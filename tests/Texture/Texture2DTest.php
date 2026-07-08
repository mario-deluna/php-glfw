<?php 

namespace GL\Tests\Texture;

use GL\Buffer\FloatBuffer;
use GL\Buffer\UByteBuffer;
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
        $this->assertFalse($logo->isHDR());

        $buffer = $logo->buffer();
        $this->assertInstanceOf(UByteBuffer::class, $buffer);

        $samples = [];
        foreach($buffer as $k => $val) {
            if ($k % 128 === 0) {
                $samples[] = $val;
            }
        }

        $this->assertEquals('a0bed380430adca3c3ddaec5e9142516', md5(implode('', $samples)));
    }

    public function testFromBufferHDRAndWriteHDR() : void
    {
        $width = 8;
        $height = 8;
        $channels = 3;

        // we just generate a float buffer to use as our HDR data
        $buffer = new FloatBuffer();
        for ($y = 0; $y < $height; $y++) {
            for ($x = 0; $x < $width; $x++) {
                $r = ($x / $width) * 2.0;  // 0.0 -> 2.0
                $g = ($y / $height) * 2.0; // 0.0 -> 2.0
                $b = 0.5;
                $buffer->push($r);
                $buffer->push($g);
                $buffer->push($b);
            }
        }

        // create texture from our HDR buffer
        $texture = Texture2D::fromBufferHDR($width, $height, $buffer, $channels);

        $this->assertEquals($width, $texture->width());
        $this->assertEquals($height, $texture->height());
        $this->assertEquals($channels, $texture->channels());
        $this->assertTrue($texture->isHDR());
        $this->assertInstanceOf(FloatBuffer::class, $texture->buffer());

        // write to HDR file
        $tempFile = sys_get_temp_dir() . '/phpglfw_test_' . uniqid() . '.hdr';
        $texture->writeHDR($tempFile);

        $this->assertFileExists($tempFile);

        // load it back
        $loadedTexture = Texture2D::fromDisk($tempFile);

        $this->assertEquals($width, $loadedTexture->width());
        $this->assertEquals($height, $loadedTexture->height());
        $this->assertEquals($channels, $loadedTexture->channels());
        $this->assertTrue($loadedTexture->isHDR());

        $loadedBuffer = $loadedTexture->buffer();
        $this->assertInstanceOf(FloatBuffer::class, $loadedBuffer);

        // size must match
        $this->assertEquals($buffer->size(), $loadedBuffer->size());

        $tolerance = 0.01; // we allow some tolarance due to file encoding, honestly i did not check the HDR spec...
        for ($i = 0; $i < $buffer->size(); $i++) {
            $this->assertEqualsWithDelta($buffer[$i], $loadedBuffer[$i], $tolerance);
        }


        unlink($tempFile);
    }

    public function testHDRTextureCannotWriteLDRFormats() : void
    {
        $buffer = new FloatBuffer([1.69, 4.2, 0.69, 4.20, 0.0, 3.14]);
        $texture = Texture2D::fromBufferHDR(2, 1, $buffer, 3);

        $this->expectException(\Error::class);
        $texture->writePNG(sys_get_temp_dir() . '/test.png');
    }

    public function testLDRTextureCannotWriteHDR() : void
    {
        $buffer = new UByteBuffer([1, 2, 3, 4, 5, 6]);
        $texture = Texture2D::fromBuffer(2, 1, $buffer, 3);

        $this->expectException(\Error::class);
        $texture->writeHDR(sys_get_temp_dir() . '/test.hdr');
    }
}