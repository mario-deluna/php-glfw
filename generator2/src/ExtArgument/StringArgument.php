<?php

namespace ExtArgument;

use ExtArgument;

class StringArgument extends ExtArgument
{
    public string $charid = 's';

    public function generateVariable(): string
    {
        return "const char *{$this->name};\nsize_t {$this->name}_size;";
    }

    public function getReferences()
    {
        return '&' . $this->name . ', &' . $this->name . '_size';
    }
}
