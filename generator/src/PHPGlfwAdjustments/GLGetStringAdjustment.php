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

            $func = new class($fname) extends ExtFunction 
            {    
                public function getFunctionImplementationBody() : string
                {
                    $buffer = $this->getArgumentParseCode() . PHP_EOL . PHP_EOL;
                    $funcCallCode = $this->getFunctionCallCode();

                    $buffer .= <<<CODE
                    const char *result = (const char *)$funcCallCode;

                    if (result) {
                        RETURN_STRING(result);
                    } else {
                        RETURN_NULL();
                    }
                    CODE;

                    return $buffer;
                }
            };

            $orig = $gen->getFunctionByName($fname);

            // copy arguments
            $func->arguments = $orig->arguments;
            $func->comment = $orig->comment;

            $func->returnType = ExtType::T_STRING;
            $func->incomplete = false;

            $gen->replaceFunctionByName($func);
        }
    }
}
