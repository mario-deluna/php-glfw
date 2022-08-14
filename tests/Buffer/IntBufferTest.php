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
        return [
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
        ];
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