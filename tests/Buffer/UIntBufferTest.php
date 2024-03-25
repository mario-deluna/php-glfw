<?php 

namespace GL\Tests\Buffer;

use GL\Buffer\UIntBuffer;

class UIntBufferTest extends BufferTestCase
{
    /**
     * Returns the class name on which the base tests shall be executed on
     */
    protected function getBufferClass() : string
    {
        return UIntBuffer::class;
    }

    /**
     * Returns an array of test data
     */
    protected function getTestData() : array
    {
        // generate some numbers (and 0) in range of the unsigned int type etc..
        return [0, ...range(0, 4294967295, 4294967295 / 85)];
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
        $buffer = new UIntBuffer();
        $buffer->push(42);
        $buffer->push(4294967295);
        $buffer->push(4294967295 + 1);
        $buffer->push(-1);

        $this->assertEquals(42, $buffer[0]);
        $this->assertEquals(4294967295, $buffer[1]);
        $this->assertEquals(0, $buffer[2]);
        $this->assertEquals(4294967295, $buffer[3]);
    }
}
