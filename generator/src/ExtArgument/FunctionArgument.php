<?php

namespace ExtArgument;

use ExtArgument;

class FunctionArgument extends ExtArgument
{
    /**
     * The char used for parsing the arguments with the zend engine
     */
    public string $charid = 'f';

    /**
     * Returns boolean if the PHP type is of the same size as the internal one
     */
    public function typeIsOfSameInternalSize() : bool
    {
        return true;
    }
}
