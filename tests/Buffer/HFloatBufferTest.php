<?php 

namespace GL\Tests\Buffer;

use GL\Buffer\HFloatBuffer;

class HFloatBufferTest extends UShortBufferTest
{
    /**
     * Returns the class name on which the base tests shall be executed on
     */
    protected function getBufferClass() : string
    {
        return HFloatBuffer::class;
    }
}