<?php

namespace ExtArgument;

use ExtArgument;

class BoolArgument extends ExtArgument
{
    public string $charid = 'b';

    public function generateVariable(): string
    {
        return "bool {$this->name};";
    }
}