<?php

class ExtConstantGroup
{
    /**
     * Group name / title
     */
    public ?string $name = null;

    /** 
     * Group description
     */
    public ?string $desc = null;
}

class ExtConstant
{
    /**
     * Constant name
     */
    public string $name;

    /**
     * The constant definition
     */
    public string $definition;

    /**
     * The constant definition final value string
     */
    public string $definitionValueString;

    public const TYPE_PASSTHROUGH = 0;
    public const TYPE_STRING = 1;

    public int $constantCompiledType = 0;

    /**
     * A comment that should be outputted next to the definition
     */
    public ?string $comment = null;

    public bool $isForwardDefinition = false;

    /**
     * The group this constant should belong to 
     */
    public ?ExtConstantGroup $group = null;

    public function __construct(string $name, string $definition, ?string $definitionValueString = null) 
    {
        $this->name = $name;
        $this->definition = $definition;
        $this->definitionValueString = $definitionValueString ?: $definition;
    }

    public function internalConstantName() : string
    {
        return 'PHPGLFW_C_' . $this->name;
    }

    /**
     * Returns the definition value while respecting the type
     * means will return a string type in double quotes..
     */
    public function getDefinitionValue() : string
    {
        if ($this->constantCompiledType === static::TYPE_STRING) {
            return '"'.$this->definition.'"';
        }

        return $this->definition;
    }

    public function getPHPRegisterFunction() : string 
    {
        if ($this->constantCompiledType === static::TYPE_STRING) {
            return 'REGISTER_STRING_CONSTANT';
        }

        return 'REGISTER_LONG_CONSTANT';
    }
}
