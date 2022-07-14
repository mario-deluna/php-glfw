<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\VariadicArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLGenFunctionAdjustments implements AdjustmentInterface
{
    private function patchResourceCreationFunction(ExtGenerator $gen, string $functionName) : void
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
        $resourceGeneratorFunctions = [];

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
            if ($func->arguments[1]->argumentTypeFrom !== 'GLuint *') continue;

            // the func cannot return anything...
            if ($func->returnType !== ExtFunction::RETURN_VOID) continue;

            $resourceGeneratorFunctions[] = $func->name;
        }

        // now patch the matched functions
        foreach($resourceGeneratorFunctions as $funcName) {
            $this->patchResourceCreationFunction($gen, $funcName);
        }

        // PHP_FUNCTION(glGenBuffers)
        // {
        //     zend_long n;
        //     zval *buffers_zval;
        //     uint32_t n_given_buffers = 0;
        //     if (zend_parse_parameters(ZEND_NUM_ARGS() , "l+", &n, &buffers_zval, &n_given_buffers) == FAILURE) {
        //         return;
        //     }
        
            // if (n_given_buffers != n) {
            //     zend_throw_error(NULL, "The given number of generated buffers needs to match the amount of giving buffer object vars.");
            //     return;
            // }
        
            // GLuint *buffer_ids = malloc(n * sizeof(GLuint));
            // glGenBuffers(n, buffer_ids);
        
            // zval *data;
            // for (uint32_t i = 0; i < n_given_buffers; i++) {
            //     data = &buffers_zval[i];
            //     ZVAL_DEREF(data);
            //     convert_to_long(data);
            //     Z_LVAL_P(data) = buffer_ids[i];
            // }
        // }
        
    }
}
