<?php 

namespace GL\Tests\Buffer;

use GL\Buffer\ByteBuffer;

class ByteBufferTest extends BufferTestCase
{
    /**
     * Returns the class name on which the base tests shall be executed on
     */
    protected function getBufferClass() : string
    {
        return ByteBuffer::class;
    }

    /**
     * Returns an array of test data
     */
    protected function getTestData() : array
    {
        return range(-128, 127);
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
        $buffer = new ByteBuffer();
        $buffer->push(16);
        $buffer->push(127);
        $buffer->push(128);
        $buffer->push(-128);
        $buffer->push(-64);


        $this->assertEquals(16, $buffer[0]);
        $this->assertEquals(127, $buffer[1]);
        $this->assertEquals(-128, $buffer[2]);
        $this->assertEquals(-128, $buffer[3]);
        $this->assertEquals(-64, $buffer[4]);
    }
}