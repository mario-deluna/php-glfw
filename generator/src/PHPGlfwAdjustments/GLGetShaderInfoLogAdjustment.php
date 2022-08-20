<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLGetShaderInfoLogAdjustment implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {   
        foreach(['glGetShaderInfoLog', 'glGetProgramInfoLog'] as $functionName) 
        {
            // instead of hassling with a passed by reference string
            // we simply return the string as in php the string is already a reference
            $func = new class($functionName) extends ExtFunction 
            {   
                public function getFunctionCallCode() : string
                {
                    $targetVarName = $this->arguments[0]->getInternalVariable();
                    $sizeVarName = $this->arguments[1]->getInternalVariable();

                    // i do a probably unessecary copy of the string here 
                    // you can probably directly write into a zval..
                    $b = 'GLint maxlen = 0;' . PHP_EOL;
                    $b .= 'char *buffer;' . PHP_EOL;
                    $b .= sprintf('buffer = emalloc(sizeof(char) * %s);', $sizeVarName) . PHP_EOL;
                    $b .= sprintf('%s(%s, %s, &maxlen, buffer);', $this->name, $targetVarName, $sizeVarName) . PHP_EOL;
                    $b .= sprintf('RETURN_STRINGL(buffer, maxlen);') . PHP_EOL;
                    $b .= 'efree(buffer);' . PHP_EOL;

                    return $b;
                }

                public function getReturnStatement(string $c) : string {
                    return $c;
                }
            };

            $func->copyFrom($gen->getFunctionByName($functionName));

            $func->arguments[1]->comment = "Specifies the size of the character buffer for storing the returned information log.";

            $func->arguments = array_slice($func->arguments, 0, 2);
            $func->returnType = ExtType::T_STRING;
            $func->returnComment = "Returns the information log for the specified object.";
            $func->comment .= PHP_EOL . PHP_EOL . '@PHP-GLFW: In the PHP extension this function directly returns the error string instead of being passed by reference as an argument.';
            
            $func->incomplete = false;
            $gen->replaceFunctionByName($func);
        }
    }
}
