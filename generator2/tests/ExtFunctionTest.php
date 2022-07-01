<?php 

namespace Tests;

use ExtArgument;
use ExtFunction;
use ExtInternalPtrObject;
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

        $this->assertEquals('l', $func->getArgumentTypeCharList());

        // two
        $func->arguments = [
            ExtArgument::make('a', ExtType::T_LONG),
            ExtArgument::make('b', ExtType::T_LONG),
        ];

        $this->assertEquals('ll', $func->getArgumentTypeCharList());

        // by ref
        $func->arguments = [
            ExtArgument::make('a', ExtType::T_LONG),
            ExtArgument::make('b', ExtType::T_LONG),
        ];
        $func->arguments[1]->passedByReference = true;

        $this->assertEquals('lz', $func->getArgumentTypeCharList());

        // test optional
        $func->arguments = [
            ExtArgument::make('a', ExtType::T_LONG),
            ExtArgument::make('b', ExtType::T_LONG),
            ExtArgument::make('c', ExtType::T_LONG),
        ];
        $func->arguments[1]->defaultValue = 42;
        $func->arguments[2]->defaultValue = 42;

        $this->assertEquals('l|ll', $func->getArgumentTypeCharList());
    }

    public function testGetArgumentAssignmentList() 
    {
        
        $func = new ExtFunction('test');
        $func->arguments = [
            ExtArgument::make('x', ExtType::T_LONG),
            ExtArgument::make('y', ExtType::T_LONG),
            ExtArgument::make('z', ExtType::T_LONG)
        ];

        $this->assertEquals('&x, &y, &z', $func->getArgumentAssignmentList());

        $func->arguments[1]->passedByReference = true;

        $this->assertEquals('&x, &y_zval, &z', $func->getArgumentAssignmentList());
    }
    
    public function testGetArgumentParseCode() 
    {
        $func = new ExtFunction('test');
        $func->arguments = [
            ExtArgument::make('x', ExtType::T_LONG),
            ExtArgument::make('y', ExtType::T_LONG),
            ExtArgument::make('z', ExtType::T_LONG)
        ];

        $this->assertEquals(<<<EOD
zend_long x;
zend_long y;
zend_long z;

if (zend_parse_parameters(ZEND_NUM_ARGS() , "lll", &x, &y, &z) == FAILURE) {
    return;
}
EOD, $func->getArgumentParseCode());


        $func->arguments[1]->passedByReference = true;

        $this->assertEquals(<<<EOD
zend_long x;
zval *y_zval;
zend_long z;

if (zend_parse_parameters(ZEND_NUM_ARGS() , "lzl", &x, &y_zval, &z) == FAILURE) {
    return;
}

ZVAL_DEREF(y_zval);
convert_to_long(y_zval);
EOD, $func->getArgumentParseCode());
    }

    public function testGetArgumentParseCodeIPO() 
    {
        $func = new ExtFunction('test');
        $func->arguments = [
            ExtArgument::make('window', ExtType::T_IPO),
            ExtArgument::make('device', ExtType::T_IPO),
        ];

        $func->arguments[0]->argInternalPtrObject = new ExtInternalPtrObject('glfwwindow', 'GLFWwindow *');
        $func->arguments[1]->argInternalPtrObject = new ExtInternalPtrObject('device', 'VKDevice *');

        $this->assertEquals(<<<EOD
zval *window_zval;
zval *device_zval;

if (zend_parse_parameters(ZEND_NUM_ARGS() , "OO", &window_zval, phpglfw_glfwwindow_ce, &device_zval, phpglfw_device_ce) == FAILURE) {
    return;
}
GLFWwindow * window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
VKDevice * device = phpglfw_deviceptr_from_zval_ptr(device_zval);
EOD, $func->getArgumentParseCode());
    }

    public function testGetFunctionCallCode() 
    {
        $func = new ExtFunction('test');
        $func->arguments = [
            ExtArgument::make('x', ExtType::T_LONG),
            ExtArgument::make('y', ExtType::T_LONG),
            ExtArgument::make('window', ExtType::T_IPO),
        ];

        $func->arguments[1]->passedByReference = true;

        $this->assertEquals('test(x, Z_LVAL_P(y_zval), window)', $func->getFunctionCallCode());
    
    }

    public function testGetFunctionCommentBlock() 
    {
        $func = new ExtFunction('phpglfwUnitTest');    
        $func->comment = "A simple function to test the comment block here..\nShould work\n   -> on\nmultiple lines";
        $this->assertEquals(<<<EOD
/**
 * phpglfwUnitTest
 * A simple function to test the comment block here..
 * Should work
 *    -> on
 * multiple lines
 */
EOD, $func->getFunctionCommentBlock());
    }

    public function testGetFunctionImplementation() 
    {
        $func = new ExtFunction('test');
        $func->arguments = [
            ExtArgument::make('window', ExtType::T_IPO),
            ExtArgument::make('x', ExtType::T_LONG),
            ExtArgument::make('y', ExtType::T_LONG),
        ];

        $func->arguments[0]->argInternalPtrObject = new ExtInternalPtrObject('glfwwindow', 'GLFWwindow *');

        $func->returnType = ExtFunction::RETURN_LONG;

        $this->assertEquals(<<<EOD
PHP_FUNCTION(test)
{
    zval *window_zval;
    zend_long x;
    zend_long y;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "Oll", &window_zval, phpglfw_glfwwindow_ce, &x, &y) == FAILURE) {
        return;
    }
    GLFWwindow * window = phpglfw_glfwwindowptr_from_zval_ptr(window_zval);
    RETURN_LONG(test(window, x, y));
}
EOD, $func->getFunctionImplementation());
    }
}