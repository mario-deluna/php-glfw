<?php 

namespace GL\Tests\Buffer;

use GL\Buffer\IntBuffer;
use GL\Buffer\BufferInterface;

class IntBufferTest extends BufferTestCase
{
    /**
     * Returns the class name on which the base tests shall be executed on
     */
    protected function getBufferClass() : string
    {
        return IntBuffer::class;
    }

    /**
     * Returns an array of test data
     */
    protected function getTestData() : array
    {
        // generate some numbers (and 0) in range of the int type (must be a factor of the range: 15, 17, 51, 85, 255) etc..
        return [0, ...range(-2147483648, 2147483647, 4294967295 / 85)];
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
        $buffer = new IntBuffer();
        $buffer->push(42);
        $buffer->push(2147483647);
        $buffer->push(2147483647 + 1);
        $buffer->push(2147483648 * 2 + 1);

        $this->assertEquals(42, $buffer[0]);
        $this->assertEquals(2147483647, $buffer[1]);
        $this->assertEquals(-2147483648, $buffer[2]);
        $this->assertEquals(1, $buffer[3]);
    }
}