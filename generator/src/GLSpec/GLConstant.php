<?php 

namespace GLSpec;

class GLConstant
{
    public string $name;
    public string $stringVal;
    public ?int $intVal = null;
    public array $groups = [];
    public ?string $comment = null;
    public ?GLConstantGroup $constGroup = null;

    public function setStringValue(string $stringValue) : void
    {
        $this->stringVal = $stringValue;
        if (substr($this->stringVal, 0, 2) === '0x') {
            $this->intVal = (int) hexdec(substr($this->stringVal, 2));
        } elseif (is_numeric($this->stringVal)) {
            $this->intVal = (int) $this->stringVal;
        }
    }
}