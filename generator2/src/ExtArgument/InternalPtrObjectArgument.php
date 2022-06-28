<?php

namespace ExtArgument;

use ExtArgument;

class InternalPtrObjectArgument extends ExtArgument
{
    public string $charid = 'r';

    public function generateVariable(): string
    {
        return "zval *{$this->name}_resource;";
    }

    public function getReferences()
    {
        return "&{$this->name}_resource";
    }

    public function generateDereferencing() : string 
    {
        return $this->argumentResource->getFetchCall($this->name, $this->name . '_resource');
    }
}