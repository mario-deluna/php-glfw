<?php 

namespace GLSpec;

class GLFunctionArg
{
    public string $name;

    public string $typeString;
    
    public string $fullTypeString;

    public ?string $class;

    public ?string $group;

    public function isPointer() : bool
    {
        return substr_count($this->fullTypeString, '*') === 1;
    }

    public function isConst() : bool
    {
        return strpos($this->fullTypeString, 'const') !== false;
    }
}