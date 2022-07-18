<?php 

namespace GL\Tests\Buffer;

use GL\Buffer\FloatBuffer;
use GL\Buffer\BufferInterface;

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
}