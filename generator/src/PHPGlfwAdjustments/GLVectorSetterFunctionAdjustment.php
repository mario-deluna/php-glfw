<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\VariadicArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLVectorSetterFunctionAdjustment implements AdjustmentInterface
{
    private function patchVectorSetterFunction(ExtGenerator $gen, string $functionName) : void
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
{$this->name}({$numVarName}, {$variadicVarNameIds});

zval *data;
for (size_t i = 0; i <  {$variadicVarNumName}; i++) {
    data = &{$variadicVarName}[i];
    ZVAL_DEREF(data);
    convert_to_long(data);
    Z_LVAL_P(data) = {$variadicVarNameIds}[i];
}
EOD;
                return $buffer;
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);
        var_dump($func); die;

        // set the 5th argument which is the offset pointer 
        // manually, in the extension we accept another int instead
        $func->arguments[1] = new VariadicArgument($func->arguments[1]->name, ExtType::T_LONG);
        $func->arguments[1]->passedByReference = true;

        $gen->replaceFunctionByName($func);
    }

    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $vectorSetterFunctions = [];

        // we iterate over all methods to locate functions 
        // that follow the expected pattern of settings a vector of data
        foreach($gen->methods as $func) 
        {
            // last character of the function name must be a 'v'
            if (substr($func->name, -1) !== 'v') {
                continue;
            }
            // function should be incomplete
            if (!$func->incomplete) continue;

            // the func cannot return anything...
            if ($func->returnType !== ExtFunction::RETURN_VOID) continue;

            // last argument must be a pointer
            $lastArg = $func->arguments[count($func->arguments) - 1];
            if (strpos($lastArg->argumentTypeFrom, '*') === false) continue;

            // argument should also be const..
            if (strpos($lastArg->argumentTypeFrom, 'const') === false) continue;

            $vectorSetterFunctions[] = $func->name;
        }

        // now patch the matched functions
        foreach($vectorSetterFunctions as $funcName) {
            $this->patchVectorSetterFunction($gen, $funcName);
        }
    }
}
