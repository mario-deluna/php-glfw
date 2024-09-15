<?php 

namespace PHPGlfwAdjustments;

use ExtGenerator;

class GLFWSetWindowMonitorAdjustment implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $setMonitorFunc = $gen->getFunctionByName('glfwSetWindowMonitor');

        // monitor needs to be optional (nullable) if you want to force back 
        // windowed mode
        $setMonitorFunc->arguments[1]->isNullable = true;
    }
}