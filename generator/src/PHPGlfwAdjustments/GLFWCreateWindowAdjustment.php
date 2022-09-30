<?php 

namespace PHPGlfwAdjustments;

use ExtFunction;
use ExtGenerator;

class GLFWCreateWindowAdjustment implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        /**
         * We bind the window and input callbacks to our internal window object
         * and forward events to the their hold zvals if they are set.
         */
        $func = new class('glfwCreateWindow') extends ExtFunction 
        {    
            public function getFunctionImplementationBody() : string
            {
                $b = parent::getFunctionImplementationBody() . PHP_EOL . PHP_EOL;

                $b .= <<<EOD
// ensure user pointer is our internal window object
zval *windowzval_userptr = NULL;
ZVAL_COPY(windowzval_userptr, return_value);
glfwSetWindowUserPointer(glfwwindow, windowzval_userptr);
EOD;
                return $b;
            }
        };
        
        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName('glfwCreateWindow');
        $func->copyFrom($baseFunc);
        $gen->replaceFunctionByName($func);
    }
}
