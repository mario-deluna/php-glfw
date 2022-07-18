<?php

class PHPGLFWBuffer
{
    /**
     * Buffer class name
     */
    public string $name;

    /**
     * Buffer class internal type
     */
    public string $type;

    /**
     * The PHP type this buffer maps or translates to 
     */
    public string $phpType;

    /**
     * Constructor
     */
    public function __construct(string $name, string $type, string $phpType) 
    {
        $this->name = $name;
        $this->type = $type;
        $this->phpType = $phpType;
    }

    /**
     * Returns a string used to construct functions names, var names etc.
     */
    public function getInternalNameString() : string
    {
        return strtolower($this->type);
    }
    
    public function getClassEntryName() : string
    {
        return sprintf("phpglfw_buffer_%s_ce", $this->getInternalNameString());
    }
    
    public function getClassEntryNameGetter() : string
    {
        return sprintf("phpglfw_get_buffer_%s_ce", $this->getInternalNameString());
    }

    public function getFullNamespaceString() : string
    {
        return sprintf("GL\\Buffer\\%s", $this->name);
    }

    public function getFullNamespaceCString() : string
    {
        return '"' . trim(var_export($this->getFullNamespaceString(), true), "'") . '"';
    }

    public function getObjectName() : string
    {
        return sprintf("phpglfw_buffer_%s_object", $this->getInternalNameString());
    }

    public function getIteratorObjectName() : string
    {
        return sprintf("phpglfw_buffer_%s_iterator", $this->getInternalNameString());
    }

    public function getIteratorHandlersVarName() : string
    {
        return sprintf("phpglfw_buffer_%s_iterator_handlers", $this->getInternalNameString());
    }

    public function objectFromZObjFunctionName() : string
    {
        return sprintf("phpglfw_buffer_%s_objectptr_from_zobj_p", $this->getInternalNameString());
    }

    public function getHandlersVarName() : string
    {
        return sprintf("phpglfw_buffer_%s_handlers", $this->getInternalNameString());
    }

    public function getHandlerMethodName(string $handler) : string
    {
        return sprintf("phpglfw_buffer_%s_%s_handler", $this->getInternalNameString(), $handler);
    }

    public function getFullNamespaceConstString() : string
    {
        return str_replace("\\", '_', $this->getFullNamespaceString());   
    }

    public function getValueArg() : ExtArgument 
    {
        return ExtArgument::make('value', $this->phpType);
    }

    public function getParseArgumentsChar() : string
    {
        return $this->getValueArg()->getCharId();
    }

    public function getValuePHPType() : string
    {
        return ExtType::getPHPType($this->phpType);
    }
}
