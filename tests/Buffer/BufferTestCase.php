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

    /**
     * Assertion helper to check if two values are equal
     */
    abstract protected function assertEqualBufferValue($expected, $actual);

    public function testConstruct()
    {
        $className = $this->getBufferClass();

        $this->assertInstanceOf($className, new $className());
        $this->assertInstanceOf(BufferInterface::class, new $className());

        // test construct with inital data
        $data = $this->getTestData();
        $buffer = new $className($data);

        for($i=0; $i<count($data); $i++) {
            $this->assertEqualBufferValue($data[$i], $buffer[$i]);
        }
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
            $this->assertEqualBufferValue($data[$i], $buffer[$i]);
        }
    }

    /**
     * The same as testPushAndRead but using the "$buffer[] = 24" syntax
     */
    public function testPushSubscriptAndRead() 
    {
        $className = $this->getBufferClass();
        $buffer = new $className();

        $data = $this->getTestData();
        foreach($data as $v) {
            $buffer[] = $v;
        }

        for($i=0; $i<count($data); $i++) {
            $this->assertEqualBufferValue($data[$i], $buffer[$i]);
        }
    }

    public function testPushArray()
    {
        $className = $this->getBufferClass();
        $buffer = new $className();

        $data = $this->getTestData();
        $buffer->pushArray($data);

        for($i=0; $i<count($data); $i++) {
            $this->assertEqualBufferValue($data[$i], $buffer[$i]);
        }
    }

    public function testReadOutOfBounds()
    {
        $className = $this->getBufferClass();
        $buffer = new $className();

        $buffer->push(42);

        $this->assertEqualBufferValue(42, $buffer[0]);
        $this->assertEquals(null, $buffer[1]);
    }

    public function testReadUnsupportedKey()
    {
        $this->expectError();
        
        $className = $this->getBufferClass();
        $buffer = new $className();
        $buffer['foo'];
    }

    public function testReadWrite()
    {
        $className = $this->getBufferClass();
        $data = $this->getTestData();
        $buffer = new $className($data);

        $this->assertEqualBufferValue($buffer[0], $data[0]);
        $this->assertEqualBufferValue($buffer[1], $data[1]);

        // now swap and check 
        $buffer[1] = $data[0];
        $buffer[0] = $data[1];

        $this->assertEqualBufferValue($buffer[0], $data[1]);
        $this->assertEqualBufferValue($buffer[1], $data[0]);
    }

    public function testClear()
    {
        $className = $this->getBufferClass();
        $buffer = new $className();
        
        $data = $this->getTestData();
        foreach($data as $v) {
            $buffer->push($v);
        }

        $this->assertEquals(count($data), $buffer->size());
        $this->assertEqualBufferValue($data[0], $buffer[0]);

        $buffer->clear();

        $this->assertEquals(0, $buffer->size());
        $this->assertEquals(null, $buffer[0]);

        // vector should still work..
        $buffer->push($data[0]);
        $this->assertEqualBufferValue($data[0], $buffer[0]);
    }

    public function testFill()
    {
        $className = $this->getBufferClass();
        $buffer = new $className();
        $testVal = $this->getTestData()[count($this->getTestData()) - 1];
        
        $buffer->fill(5, $testVal);
        $this->assertEquals(5, $buffer->size());
        for($i = 0; $i < 5; $i++) {
            $this->assertEqualBufferValue($testVal, $buffer[$i]);
        }

        // push another value and ensure the buffer resizes correctly
        $buffer->push(42.0);
        $this->assertEquals(6, $buffer->size());

        // fill again and ensure the new value is still the same
        $buffer->fill(5, $testVal);
        $this->assertEquals(6, $buffer->size());
        $this->assertEqualBufferValue(42.0, $buffer[5]);
    }

    public function testIterator()
    {
        $className = $this->getBufferClass();
        $data = $this->getTestData();
        $buffer = new $className($data);

        $this->assertEquals(count($data), $buffer->size());

        $i = 0;

        foreach($buffer as $key => $value) {
            $this->assertEquals($i, $key);
            $this->assertEqualBufferValue($data[$key], $value);
            $i++;
        }
    }

    public function testSerialisation() 
    {
        $className = $this->getBufferClass();
        $data = $this->getTestData();
        $buffer = new $className($data);

        ini_set('glfw.buffer_serialize_hex_float', false);

        $serialized = serialize($buffer);
        $unserialized = unserialize($serialized);

        $this->assertEquals($buffer->size(), $unserialized->size());

        for($i=0; $i<count($data); $i++) {
            $this->assertEqualBufferValue($data[$i], $unserialized[$i]);
        }

        // test with hex serialization
        ini_set('glfw.buffer_serialize_hex_float', true);

        $serialized = serialize($buffer);
        $unserialized = unserialize($serialized);

        $this->assertEquals($buffer->size(), $unserialized->size());

        for($i=0; $i<count($data); $i++) {
            $this->assertEqualBufferValue($data[$i], $unserialized[$i]);
        }
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