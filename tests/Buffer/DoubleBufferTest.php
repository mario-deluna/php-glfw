<?php 

namespace GL\Tests\Buffer;

use GL\Buffer\DoubleBuffer;

class DoubleBufferTest extends BufferTestCase
{
    /**
     * Returns the class name on which the base tests shall be executed on
     */
    protected function getBufferClass() : string
    {
        return DoubleBuffer::class;
    }

    /**
     * Returns an array of test data
     */
    protected function getTestData() : array
    {
        return [
            0.0, 1.1, 2.2, 3.3, 4.4, 5.5,
            6.6, 7.7, 8.8, 9.9, 10.0, M_PI
        ];
    }

    /**
     * Assertion helper to check if two values are equal
     */
    protected function assertEqualBufferValue($expected, $actual)
    {
        $this->assertEquals($expected, $actual);
    }
}