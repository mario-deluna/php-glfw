<?php 

namespace GL\Tests\Buffer;

use GL\Buffer\UByteBuffer;

class UByteBufferTest extends BufferTestCase
{
    /**
     * Returns the class name on which the base tests shall be executed on
     */
    protected function getBufferClass() : string
    {
        return UByteBuffer::class;
    }

    /**
     * Returns an array of test data
     */
    protected function getTestData() : array
    {
        return range(0, 255);
    }

    /**
     * Assertion helper to check if two values are equal
     */
    protected function assertEqualBufferValue($expected, $actual)
    {
        $this->assertEquals($expected, $actual);
    }

    public function testOverflow() 
    {
        $buffer = new UByteBuffer();
        $buffer->push(16);
        $buffer->push(128);
        $buffer->push(255);
        $buffer->push(256);

        $this->assertEquals(16, $buffer[0]);
        $this->assertEquals(128, $buffer[1]);
        $this->assertEquals(255, $buffer[2]);
        $this->assertEquals(0, $buffer[3]);
    }
}