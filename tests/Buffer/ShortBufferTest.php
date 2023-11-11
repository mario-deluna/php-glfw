<?php 

namespace GL\Tests\Buffer;

use GL\Buffer\ShortBuffer;

class ShortBufferTest extends BufferTestCase
{
    /**
     * Returns the class name on which the base tests shall be executed on
     */
    protected function getBufferClass() : string
    {
        return ShortBuffer::class;
    }

    /**
     * Returns an array of test data
     */
    protected function getTestData() : array
    {
        // generate some numbers (and 0) in range of the short type (must be a factor of the range) etc..
        return [0, ...range(-32768, 32767, 65535 / 85)];
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
        $buffer = new ShortBuffer();
        $buffer->push(42);
        $buffer->push(32767);
        $buffer->push(32767 + 1);
        $buffer->push(32768 * 2 + 1);

        $this->assertEquals(42, $buffer[0]);
        $this->assertEquals(32767, $buffer[1]);
        $this->assertEquals(-32768, $buffer[2]);
        $this->assertEquals(1, $buffer[3]);
    }
}