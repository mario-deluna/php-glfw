<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLGetStringAdjustment implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        foreach(['glGetString', 'glGetStringi'] as $fname) {
            $func = $gen->getFunctionByName($fname);
            $func->returnType = ExtType::T_STRING;
    
            // force complete
            $func->incomplete = false;
        }
    }
}
