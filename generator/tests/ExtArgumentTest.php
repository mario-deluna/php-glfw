<?php 

namespace Tests;

use ExtArgument;
use ExtArgument\NullArgument;
use ExtType;

class ExtArgumentTest extends \PHPUnit\Framework\TestCase
{
    public function testMake()
    {
        $this->assertInstanceOf(NullArgument::class, ExtArgument::make('test', ExtType::T_NULL));
    }
}