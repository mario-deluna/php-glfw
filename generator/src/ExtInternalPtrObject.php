<?php

class ExtInternalPtrObject
{
    /**
     * The name of the pointer object aka the class name it should
     * take inside PHP
     */
    public string $name;

    /**
     * The pointer type this object wraps
     * example:
     *   'GLFWwindow *'
     */
    public string $type;

    /**
     * An array of Zvals that should be added to the object,
     * i use this to store the callback functions for example
     * 
     * @var array
     */
    public array $additionalZvals = [];

    /**
     * Constructor
     */
    public function __construct(string $name, string $type) 
    {
        $this->name = $name;
        $this->type = $type;
    }

    public function getType() : string 
    {
        return $this->type;
    }

    public function getPHPClassName() : string 
    {
        return $this->name;
    }

    /**
     * Basically the extension prefixed name id
     */
    public function getIdentifierName() : string
    {
        return GEN_DECL_PREFIX . strtolower($this->name);
    }

    /**
     * Returns the class entry var
     */
    public function getClassEntryName() : string
    {
        return $this->getIdentifierName() . '_ce';
    }

    /**
     * Returns the name of the pointer holding struct
     */
    public function getObjectStructName() : string
    {
        return $this->getIdentifierName() . '_object';
    }

    public function getObjectHandlersVar() : string
    {
        return $this->getIdentifierName() . '_object_handlers';
    }

    public function getObjectCreateFunctionName() : string
    {
        return $this->getIdentifierName() . '_object_create';
    }

    public function getObjectFreeFunctionName() : string
    {
        return $this->getIdentifierName() . '_object_free';
    }

    public function getClassMethodEntriesVar() : string
    {
        return $this->getIdentifierName() . '_class_methods';
    }

    public function getClassConstructorFunctionName() 
    {
        return $this->getIdentifierName() . '_class_constructor';
    }

    public function getClassRegistrationFunctionName() 
    {
        return $this->getIdentifierName() . '_class_register';
    }

    /**
     * Returns the var inside the object struct holding our resource pointer
     */
    public function getObjectStructPointerVar() : string
    {
        return strtolower($this->name);
    }

    /**
     * Returns the function name for the converter function of internal * <- from <- zval *
     */
    public function getInternalPtrFromZValPtrFunctionName() : string
    {
        return $this->getIdentifierName() . 'ptr_from_zval_ptr';
    }

    public function getObjectStructPtrFromZObjPtrFunctionName() : string 
    {
        return $this->getObjectStructName() . 'ptr_from_zobj_p';
    }
    
    public function getAssignPtrToZvalFunctionName() 
    {
        return $this->getIdentifierName() . '_ptr_assign_to_zval_p';
    }

    public function getObjectMinitHelperFunctionName() 
    {
        return $this->getIdentifierName() . '_object_minit_helper';
    }

    /**
     * Returns C code that declares the given varname of the internal type by resolving a zval potiner
     */
    public function getInternalPtrFromZValDeclarationCode(string $internalVarName, string $zvalVarName, ?string $defaultValue = null) : string 
    {
        if ($defaultValue !== null) {
            $b = $this->type . ' ' . $internalVarName . ' = NULL;' . PHP_EOL;
            $b .= sprintf("if (%s != NULL && Z_TYPE_P(%s) == IS_OBJECT) {\n", $zvalVarName, $zvalVarName);
            $b .= sprintf("    %s = %s(%s);\n}", $internalVarName, $this->getInternalPtrFromZValPtrFunctionName(), $zvalVarName);
            return $b;
        }
        
        return $this->type . ' ' . $internalVarName . ' = ' . $this->getInternalPtrFromZValPtrFunctionName() . '(' . $zvalVarName . ');';
    }

    /**
     * Returns C code to deallocate the resources behind the internal pointer
     */
    public function getDestructionCall(string $var) : string 
    {
        return "efree(" . $var . '); ' . $var . ' = NULL;' . PHP_EOL;
    }
}
