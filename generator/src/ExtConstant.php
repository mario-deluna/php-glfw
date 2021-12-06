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
}
