<?php

namespace ExtArgument;

use ExtArgument;

class NullArgument extends ExtArgument
{
    /**
     * The C default value for the argument, if null === required value
     */
    public ?string $defaultValue = 'NULL';
}