<?php

namespace ExtArgument;

use ExtArgument;

class DoubleArgument extends ExtArgument
{
    public string $charid = 'd';

    public function generateVariable(): string
    {
        return "double {$this->name};";
    }

    public function generateZValConvertion(): string
    {
        return " convert_to_double(z_{$this->name});";
    }

    public function getCallName()
    {
        if ($this->passedByRef) {
            return "({$this->realType} *)" . parent::getCallName();
        }
        return parent::getCallName();
    }
}