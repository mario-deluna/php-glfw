<?php 

namespace PHPGlfwAdjustments;

use ExtGenerator;

class GLFWOptionalArgsAdjustments implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $createWinFunc = $gen->getFunctionByName('glfwCreateWindow');
        $createWinFunc->arguments[3]->defaultValue = 'NULL';
        $createWinFunc->arguments[4]->defaultValue = 'NULL';

        // var_dump($createWinFunc);
    }
}