<?php 

namespace Tests\ExtArgument;

use ExtArgument;
use ExtType;

class LongArgumentTest extends \PHPUnit\Framework\TestCase
{
    public function testGetVarDeclaration()
    {
        $arg = ExtArgument::make('test1', ExtType::T_LONG);
        $this->assertEquals('zend_long test1;', $arg->getVariableDeclaration());
        $arg->name = 'test2';
        $this->assertEquals('zend_long test2;', $arg->getVariableDeclaration());

        // default value
        $arg->defaultValue = '42';
        $this->assertEquals('zend_long test2 = 42;', $arg->getVariableDeclaration());

        // passed by reference
        $arg->passedByReference = true;
        $this->assertEquals('zval *test2_zval;', $arg->getVariableDeclaration());
    }

    public function testGetUsePrepCode()
    {
        $arg = ExtArgument::make('test1', ExtType::T_LONG);
        $this->assertEquals('', $arg->getUsePrepCode());

        // passed by reference
        $arg->passedByReference = true;
        $this->assertEquals("ZVAL_DEREF(test1_zval);\nconvert_to_long(test1_zval);", $arg->getUsePrepCode());
    }

    public function testGetUsableVariable()
    {
        $arg = ExtArgument::make('test1', ExtType::T_LONG);
        $this->assertEquals('test1', $arg->getUsableVariable());

        // passed by reference
        $arg->passedByReference = true;
        $this->assertEquals('Z_LVAL_P(test1_zval)', $arg->getUsableVariable());
    }
}