<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\VariadicArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLFWDestroyFunctionAdjustment implements AdjustmentInterface
{
    private function patchResourceDestructionFunction(ExtGenerator $gen, string $functionName) : void
    {
        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionCallCode() : string
            {
                $arg = $this->arguments[0];
                $ipo = $arg->argInternalPtrObject;
                
                $buffer = <<<EOD
{$ipo->getObjectStructName()} *obj_ptr = {$ipo->getObjectStructPtrFromZObjPtrFunctionName()}(Z_OBJ_P({$arg->getZValName()}));
{$this->name}(obj_ptr->{$ipo->getObjectStructPointerVar()});
obj_ptr->{$ipo->getObjectStructPointerVar()} = NULL;
ZVAL_DEREF({$arg->getZValName()});
ZVAL_NULL({$arg->getZValName()});
EOD;

                return $buffer;
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        // the to be destructed resource need to be passed by ref 
        // so we can null it
        $func->arguments[0]->passedByReference = true;    

        $gen->replaceFunctionByName($func);
    }

    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $resourceDestructionFunction = $gen->findFunctionNamesMatching("/glfwDestroy.*/");

        foreach($resourceDestructionFunction as $funcName) {
            $this->patchResourceDestructionFunction($gen, $funcName);
        }
    }
}
