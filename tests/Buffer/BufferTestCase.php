<?php 

namespace GL\Tests\Buffer;

use GL\Buffer\BufferInterface;

abstract class BufferTestCase extends \PHPUnit\Framework\TestCase
{
    /**
     * Returns the class name on which the base tests shall be executed on
     */
    abstract protected function getBufferClass() : string;

    /**
     * Returns an array of test data
     */
    abstract protected function getTestData() : array;

    public function testConstruct()
    {
        $className = $this->getBufferClass();

        $this->assertInstanceOf($className, new $className());
        $this->assertInstanceOf(BufferInterface::class, new $className());
    }

    /**
     * Very basic test to check that we do not leak memory...
     */
    public function testMemoryConsumption() 
    {
        $className = $this->getBufferClass();

        $afterMemory = memory_get_usage(true);
        $finalMemory = memory_get_usage(true);
        $initalMemory = memory_get_usage(true);

        $buffer = new $className();
        $buffer->reserve(10000000);

        $afterMemory = memory_get_usage(true);

        unset($buffer);

        $finalMemory = memory_get_usage(true);

        $this->assertTrue($afterMemory > $initalMemory);
        $this->assertEquals($initalMemory, $finalMemory);
    }

    public function testPushAndRead() 
    {
        $className = $this->getBufferClass();
        $buffer = new $className();

        $data = $this->getTestData();
        foreach($data as $v) {
            $buffer->push($v);
        }

        for($i=0; $i<count($data); $i++) {
            if (is_float($data[$i])) {
                // because of type conversions we expect some rounding offset
                $this->assertEqualsWithDelta($data[$i], $buffer[$i], 0.0001);
            } else {
                $this->assertEquals($data[$i], $buffer[$i]);
            }
        }
    }

    public function testReadOutOfBounds()
    {
        $className = $this->getBufferClass();
        $buffer = new $className();

        $buffer->push(42);

        $this->assertEquals(42, $buffer[0]);
        $this->assertEquals(null, $buffer[1]);
    }

    public function testReadUnsupportedKey()
    {
        $this->expectError();
        
        $className = $this->getBufferClass();
        $buffer = new $className();
        $buffer['foo'];
    }

    public function testToString() 
    {
        $className = $this->getBufferClass();
        $buffer = new $className();

        $this->assertEquals($className . '(0 [0])', (string) $buffer);

        $buffer->push(42);
        $this->assertEquals($className . '(1 [1])', (string) $buffer);
        $buffer->push(1);
        $buffer->push(2);
        $buffer->push(3);
        $buffer->push(4);
        $this->assertEquals($className . '(5 [8])', (string) $buffer);

        $buffer->reserve(20);

        $this->assertEquals($className . '(5 [20])', (string) $buffer);
    }
}