<?php 

namespace GLSpec;

class GLFunction
{
    public string $name;

    public ?string $class;

    public ?string $group;

    public string $returnTypeString;

    public string $fullReturnTypeString;

    public array $arguments = [];

    public string $commentSummary = '';

    public function isPointerReturn() : bool
    {
        return strpos($this->fullReturnTypeString, '*') !== false;
    }

    public function makeArg() : GLFunctionArg
    {
        $arg = new GLFunctionArg;
        $this->arguments[] = $arg;
        return $arg;
    }
}