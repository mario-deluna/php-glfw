<?php 

namespace PHPGlfwAdjustments;

use ExtFunction;
use ExtGenerator;

class GLFWGladLoader implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        /**
         * In PHPGlfw we automatically load GL function pointers over glad 
         * as soon as we have an active context. We could expose this call to the user 
         * but I decided to hide this part of the implemenation in glfwMakeContextCurrent
         */
        $func = new class('glfwMakeContextCurrent') extends ExtFunction 
        {    
            public function getFunctionImplementationBody() : string
            {
                $b = parent::getFunctionImplementationBody() . PHP_EOL . PHP_EOL;

                $b .= "if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {" . PHP_EOL;
                $b .= "    zend_error(E_ERROR, \"glad failed loading the GL loader...\");" . PHP_EOL;
                $b .= "}";

                return $b;
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName('glfwMakeContextCurrent');
        $func->copyFrom($baseFunc);
        $gen->replaceFunctionByName($func);
    }
}
