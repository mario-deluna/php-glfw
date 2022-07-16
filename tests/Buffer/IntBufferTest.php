<?php 

namespace GL\Tests\Buffer;

use GL\Buffer\IntBuffer;
use GL\Buffer\BufferInterface;

class IntBufferTest extends \PHPUnit\Framework\TestCase
{
    public function testConstruct()
    {
        $this->assertInstanceOf(IntBuffer::class, new IntBuffer());
        $this->assertInstanceOf(BufferInterface::class, new IntBuffer());
    }

    /**
     * Very basic test to check that we do not leak memory...
     */
    public function testMemoryConsumption() 
    {
        $afterMemory = memory_get_usage(true);
        $finalMemory = memory_get_usage(true);
        $initalMemory = memory_get_usage(true);

        $buffer = new IntBuffer();
        $buffer->reserve(100000000);

        $afterMemory = memory_get_usage(true);

        unset($buffer);

        $finalMemory = memory_get_usage(true);

        $this->assertTrue($afterMemory > $initalMemory);
        $this->assertEquals($initalMemory, $finalMemory);
    }

    public function testToString() 
    {
        $buffer = new IntBuffer();
        $this->assertEquals('GL\Buffer\FloatBuffer(0 [0])', (string) $buffer);

        $buffer->push(42);
        $this->assertEquals('GL\Buffer\FloatBuffer(1 [1])', (string) $buffer);
        $buffer->push(1);
        $buffer->push(2);
        $buffer->push(3);
        $buffer->push(4);
        $this->assertEquals('GL\Buffer\FloatBuffer(5 [8])', (string) $buffer);

        $buffer->reserve(20);

        $this->assertEquals('GL\Buffer\FloatBuffer(5 [20])', (string) $buffer);
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