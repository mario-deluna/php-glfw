<?php 

namespace GL\Tests\Buffer;

use GL\Buffer\UShortBuffer;

class UShortBufferTest extends BufferTestCase
{
    /**
     * Returns the class name on which the base tests shall be executed on
     */
    protected function getBufferClass() : string
    {
        return UShortBuffer::class;
    }

    /**
     * Returns an array of test data
     */
    protected function getTestData() : array
    {
        // generate some numbers in the range of the ushort type
        return [0, ...range(0, 65535, 65535 / 85)];
    }

    /**
     * Assertion helper to check if two values are equal
     */
    protected function assertEqualBufferValue($expected, $actual)
    {
        $this->assertEquals($expected, $actual);
    }

    /**
     * Test to ensure that values above the ushort max wrap around
     */
    public function testUpperBoundOverflow() 
    {
        $buffer = new UShortBuffer();
        $buffer->push(65535);
        $buffer->push(65536);
        $buffer->push(-1);

        $this->assertEquals(65535, $buffer[0]);
        $this->assertEquals(0, $buffer[1]);
        $this->assertEquals(65535, $buffer[2]);
    }
}
