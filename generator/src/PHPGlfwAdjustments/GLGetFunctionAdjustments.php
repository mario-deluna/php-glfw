<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\VariadicArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLGetFunctionAdjustments implements AdjustmentInterface
{
    
    private function patchGetArrayFunc(ExtGenerator $gen, $functionName, $internalType, $convertFunc, $assignMacro) : void
    {
        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionCallCode() : string
            {
                list($internalType, $convertFunc, $assignMacro) = $this->tmpData;

                $pnameVar = $this->arguments[0];
                $variadicVar = $this->arguments[1];

                $pnameVarName = $pnameVar->getInternalVariable();
                $variadicVarName = $variadicVar->getInternalVariable();
                $variadicVarNumName = $variadicVar->getInternalVariable() . '_num';

                $variadicVarNameTmpParams = $variadicVar->getInternalVariable() . '_tmp';
                
                $buffer = <<<EOD

                
if ({$variadicVarNumName} < 1) {
    zend_throw_error(NULL, "You must at least pass one variable to {$this->name}(const, var...)");
    return;
}

{$internalType} *{$variadicVarNameTmpParams} = emalloc({$variadicVarNumName} * sizeof({$internalType}));
{$this->name}({$pnameVarName}, {$variadicVarNameTmpParams});

zval *data;
for (size_t i = 0; i <  {$variadicVarNumName}; i++) {
    data = &{$variadicVarName}[i];
    ZVAL_DEREF(data);
    {$convertFunc}(data);
    {$assignMacro}(data, {$variadicVarNameTmpParams}[i]);
}

efree({$variadicVarNameTmpParams});
EOD;
                return $buffer;
            }
        };

        $func->tmpData = [$internalType, $convertFunc, $assignMacro];

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        // set the second argument to variadic bool 
        $func->arguments[1] = new VariadicArgument($func->arguments[1]->name, ExtType::T_BOOL);
        $func->arguments[1]->passedByReference = true;

        $gen->replaceFunctionByName($func);
    }

    private function patchTargetGetArrayFunc(ExtGenerator $gen, $functionName, $internalType, $convertFunc, $assignMacro) : void
    {
        $func = new class($functionName) extends ExtFunction 
        {
            public function getFunctionCallCode() : string
            {
                list($internalType, $convertFunc, $assignMacro) = $this->tmpData;

                $targetVar = $this->arguments[0];
                $pnameVar = $this->arguments[1];
                $variadicVar = $this->arguments[2];

                $targetVarName = $targetVar->getInternalVariable();
                $pnameVarName = $pnameVar->getInternalVariable();
                $variadicVarName = $variadicVar->getInternalVariable();
                $variadicVarNumName = $variadicVar->getInternalVariable() . '_num';

                $variadicVarNameTmpParams = $variadicVar->getInternalVariable() . '_tmp';
                
                $buffer = <<<EOD

                
if ({$variadicVarNumName} < 1) {
    zend_throw_error(NULL, "You must at least pass one variable to {$this->name}(const, var...)");
    return;
}

{$internalType} *{$variadicVarNameTmpParams} = emalloc({$variadicVarNumName} * sizeof({$internalType}));
{$this->name}({$targetVarName}, {$pnameVarName}, {$variadicVarNameTmpParams});

zval *data;
for (size_t i = 0; i <  {$variadicVarNumName}; i++) {
    data = &{$variadicVarName}[i];
    ZVAL_DEREF(data);
    {$convertFunc}(data);
    {$assignMacro}(data, {$variadicVarNameTmpParams}[i]);
}
efree({$variadicVarNameTmpParams});
EOD;
                return $buffer;
            }
        };

        $func->tmpData = [$internalType, $convertFunc, $assignMacro];

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName($functionName);
        $func->copyFrom($baseFunc);

        // set the second argument to variadic bool 
        $func->arguments[2] = new VariadicArgument($func->arguments[2]->name, ExtType::T_BOOL);
        $func->arguments[2]->passedByReference = true;

        $gen->replaceFunctionByName($func);
    }

    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        // base
        $this->patchGetArrayFunc($gen, 'glGetBooleanv', 'GLboolean', 'convert_to_boolean', 'ZVAL_BOOL');
        $this->patchGetArrayFunc($gen, 'glGetDoublev', 'GLdouble', 'convert_to_double', 'ZVAL_DOUBLE');
        $this->patchGetArrayFunc($gen, 'glGetFloatv', 'GLfloat', 'convert_to_double', 'ZVAL_DOUBLE');
        $this->patchGetArrayFunc($gen, 'glGetIntegerv', 'GLint', 'convert_to_long', 'ZVAL_LONG');

        // base with index offset
        $this->patchTargetGetArrayFunc($gen, 'glGetBooleani_v', 'GLboolean', 'convert_to_boolean', 'ZVAL_BOOL');
        $this->patchTargetGetArrayFunc($gen, 'glGetDoublei_v', 'GLdouble', 'convert_to_double', 'ZVAL_DOUBLE');
        $this->patchTargetGetArrayFunc($gen, 'glGetFloati_v', 'GLfloat', 'convert_to_double', 'ZVAL_DOUBLE');
        $this->patchTargetGetArrayFunc($gen, 'glGetIntegeri_v', 'GLint', 'convert_to_long', 'ZVAL_LONG');

        // texture 
        $this->patchTargetGetArrayFunc($gen, 'glGetTexParameterfv', 'GLfloat', 'convert_to_double', 'ZVAL_DOUBLE');
        $this->patchTargetGetArrayFunc($gen, 'glGetTexParameteriv', 'GLint', 'convert_to_long', 'ZVAL_LONG');
        $this->patchTargetGetArrayFunc($gen, 'glGetTexParameterIiv', 'GLint', 'convert_to_long', 'ZVAL_LONG');
        $this->patchTargetGetArrayFunc($gen, 'glGetTexParameterIuiv', 'GLuint', 'convert_to_long', 'ZVAL_LONG');
    }
}
