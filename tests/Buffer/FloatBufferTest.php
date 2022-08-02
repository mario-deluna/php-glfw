<?php 

namespace GL\Tests\Buffer;

use GL\Buffer\FloatBuffer;
use GL\Buffer\BufferInterface;
use GL\Math\Mat4;
use GL\Math\Vec2;
use GL\Math\Vec3;
use GL\Math\Vec4;

class FloatBufferTest extends BufferTestCase
{
    /**
     * Returns the class name on which the base tests shall be executed on
     */
    protected function getBufferClass() : string
    {
        return FloatBuffer::class;
    }

    /**
     * Returns an array of test data
     */
    protected function getTestData() : array
    {
        return [
            0.0, 1.1, 2.2, 3.3, 4.4, 5.5,
            6.6, 7.7, 8.8, 9.9, 10.0, 
        ];
    }

    /**
     * Assertion helper to check if two values are equal
     */
    protected function assertEqualBufferValue($expected, $actual)
    {
        $this->assertEqualsWithDelta($expected, $actual, 0.0001);
    }

    public function testPushVec2()
    {
        $buffer = new FloatBuffer();
        $buffer->pushVec2(new Vec2(1.0, 2.0));
        $buffer->pushVec2(new Vec2(3.0, 4.0));
        $buffer->pushVec2(new Vec2(5.0, 6.0));
        $buffer->pushVec2(new Vec2(7.0, 8.0));
        
        for($i = 0; $i < 8; $i++) {
            $this->assertEqualBufferValue($i + 1, $buffer[$i]);
        }   
    }

    public function testPushVec3()
    {
        $buffer = new FloatBuffer();
        $buffer->pushVec3(new Vec3(1.0, 2.0, 3.0));
        $buffer->pushVec3(new Vec3(4.0, 5.0, 6.0));
        $buffer->pushVec3(new Vec3(7.0, 8.0, 9.0));
        $buffer->pushVec3(new Vec3(10.0, 11.0, 12.0));

        for($i = 0; $i < 12; $i++) {
            $this->assertEqualBufferValue($i + 1, $buffer[$i]);
        }
    }

    public function testPushVec4()
    {
        $buffer = new FloatBuffer();
        $buffer->pushVec4(new Vec4(1.0, 2.0, 3.0, 4.0));
        $buffer->pushVec4(new Vec4(5.0, 6.0, 7.0, 8.0));
        $buffer->pushVec4(new Vec4(9.0, 10.0, 11.0, 12.0));
        $buffer->pushVec4(new Vec4(13.0, 14.0, 15.0, 16.0));

        for($i = 0; $i < 16; $i++) {
            $this->assertEqualBufferValue($i + 1, $buffer[$i]);
        }
    }

    public function testPushMat4()
    {
        $buffer = new FloatBuffer();
        $buffer->pushMat4(Mat4::fromArray([
            1.0, 2.0, 3.0, 4.0,
            5.0, 6.0, 7.0, 8.0,
            9.0, 10.0, 11.0, 12.0,
            13.0, 14.0, 15.0, 16.0,
        ]));
        $buffer->pushMat4(Mat4::fromArray([
            17.0, 18.0, 19.0, 20.0,
            21.0, 22.0, 23.0, 24.0,
            25.0, 26.0, 27.0, 28.0,
            29.0, 30.0, 31.0, 32.0,
        ]));
        
        for($i = 0; $i < 32; $i++) {
            $this->assertEqualBufferValue($i + 1, $buffer[$i]);
        }
    }
}