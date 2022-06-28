<?php 

namespace Tests;

use ExtArgument;
use ExtFunction;
use ExtType;

class ExtFunctionTest extends \PHPUnit\Framework\TestCase
{
    public function testConstruct()
    {
        $this->assertInstanceOf(ExtFunction::class, new ExtFunction('test'));
    }

    public function testGetTypeCharList()
    {
        // single long
        $func = new ExtFunction('test');
        $func->arguments = [
            ExtArgument::make('a', ExtType::T_LONG)
        ];

        $this->assertEquals('l', $func->getTypeCharList());

        // two
        $func->arguments = [
            ExtArgument::make('a', ExtType::T_LONG),
            ExtArgument::make('b', ExtType::T_LONG),
        ];

        $this->assertEquals('ll', $func->getTypeCharList());

        // by ref
        $func->arguments = [
            ExtArgument::make('a', ExtType::T_LONG),
            ExtArgument::make('b', ExtType::T_LONG),
        ];
        $func->arguments[1]->passedByReference = true;

        $this->assertEquals('lz', $func->getTypeCharList());
    }
}