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

    public function testPushString()
    {
        $buffer = new UByteBuffer();
        $buffer->pushString('Hello World!');

        $this->assertEquals(72, $buffer[0]);
        $this->assertEquals(101, $buffer[1]);
        $this->assertEquals(108, $buffer[2]);
        $this->assertEquals(108, $buffer[3]);
        $this->assertEquals(111, $buffer[4]);
        $this->assertEquals(32, $buffer[5]);
        $this->assertEquals(87, $buffer[6]);
        $this->assertEquals(111, $buffer[7]);
        $this->assertEquals(114, $buffer[8]);
        $this->assertEquals(108, $buffer[9]);
        $this->assertEquals(100, $buffer[10]);
        $this->assertEquals(33, $buffer[11]);
    }

    public function testAppendStringData()
    {
        $buffer1 = new UByteBuffer();
        $buffer1->pushString('Hello ');
        
        $buffer2 = new UByteBuffer();
        $buffer2->pushString('World!');

        $buffer1->append($buffer2);

        $this->assertEquals(12, $buffer1->size());
        
        $result = '';
        for($i = 0; $i < $buffer1->size(); $i++) {
            $result .= chr($buffer1[$i]);
        }
        $this->assertEquals('Hello World!', $result);
    }
}