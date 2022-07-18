<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLVertexAttribPointerAdjustment implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $func = new class('glVertexAttribPointer') extends ExtFunction 
        {    
            // public function getFunctionImplementationBody() : string
            // {
            //     return 'a';
            // }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName('glVertexAttribPointer');
        $func->copyFrom($baseFunc);

        // set the 5th argument which is the offset pointer 
        // manually, in the extension we accept another int instead
        $func->arguments[] = ExtArgument::make('offset', ExtType::T_LONG);

        // force complete
        $func->incomplete = false;

        $gen->replaceFunctionByName($func);
    }
}
