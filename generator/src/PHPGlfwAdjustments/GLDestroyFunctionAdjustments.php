<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\VariadicArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLDestroyFunctionAdjustments implements AdjustmentInterface
{
    private function patchResourceDestructionFunction(ExtGenerator $gen, string $functionName) : void
    {
        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionCallCode() : string
            {
                $numVar = $this->arguments[0];
                $variadicVar = $this->arguments[1];

                $numVarName = $numVar->getInternalVariable();
                $variadicVarName = $variadicVar->getInternalVariable();
                $variadicVarNumName = $variadicVar->getInternalVariable() . '_num';

                $variadicVarNameIds = $variadicVar->getInternalVariable() . '_ids';
                

                $buffer = <<<EOD
if ({$numVarName} != {$variadicVarNumName}) {
    zend_throw_error(NULL, "The given number of elements needs to match the actual amount of given variadic vars.");
    return;
}

GLuint *{$variadicVarNameIds} = malloc({$numVarName} * sizeof(GLuint));

zval *data;
for (size_t i = 0; i <  {$variadicVarNumName}; i++) {
    data = &{$variadicVarName}[i];
    convert_to_long(data);
    {$variadicVarNameIds}[i] = Z_LVAL_P(data);
}

{$this->name}({$numVarName}, {$variadicVarNameIds});
EOD;
                return $buffer;
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);
        $func->incomplete = false; // force complete

        // sets the second argument to be variadic
        $func->arguments[1] = new VariadicArgument($func->arguments[1]->name, ExtType::T_LONG);

        $gen->replaceFunctionByName($func);
    }

    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $resourceDestructorFunctions = [];

        // we iterate over all methods to locate functions we deem
        // to be resource creators that follow the same pattern 
        // that allows us to apply our variadic argument modifications
        foreach($gen->methods as $func) 
        {
            // must be 2 args only
            if (count($func->arguments) !== 2) continue;
            
            // first arg must be GLsizei
            if ($func->arguments[0]->argumentTypeFrom !== 'GLsizei') continue;

            // second arg must be GLuint pointer
            if ($func->arguments[1]->argumentTypeFrom !== 'const GLuint *' && $func->arguments[1]->argumentTypeFrom !== 'const GLenum *') continue;

            // the func cannot return anything...
            if ($func->returnType !== ExtFunction::RETURN_VOID) continue;

            $resourceDestructorFunctions[] = $func->name;
        }

        // now patch the matched functions
        foreach($resourceDestructorFunctions as $funcName) {
            $this->patchResourceDestructionFunction($gen, $funcName);
        }
    }
}
