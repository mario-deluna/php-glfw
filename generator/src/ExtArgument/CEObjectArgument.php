<?php

namespace ExtArgument;

use Exception;
use ExtArgument;
use ExtInternalPtrObject;

class CEObjectArgument extends ExtArgument
{
    /**
     * Is the argument passed by referenced?
     */
    public bool $passedByReference = true;

    /**
     * The char used for parsing the arguments with the zend engine
     */
    public string $charid = 'O';

    /**
     * The prefix used for a var declaration
     */
    public string $variableDeclarationPrefix = 'zval *';

    /**
     * Returns a C string that should resolve a class entry pointer
     */
    public function getClassEntryPointer() : string 
    {
        return $this->name . '_ce';
    }

    public function getPHPClassName() : string {
        return ucfirst($this->name);
    }

    /**
     * Returns boolean if the PHP type is of the same size as the internal one
     */
    public function typeIsOfSameInternalSize() : bool
    {
        return true;
    }

    /**
     * The IPO is always the default O, passed by reference does not change the type
     */
    public function getCharId() : string 
    {
        $c = $this->charid;
        if ($this->isOptional()) $c .= '!';

        return $c;
    }

    /**
     * An array of C arguments passed to the "zend_parse_parameters" function. usally just one 
     */
    public function getZendParameterParseArguments() : array
    {
        return [
            '&' . $this->getInternalVariable(),
            $this->getClassEntryPointer(),
        ];
    }

    /**
     * Returns C code to be run after the argument has been assigned to the arguments 
     * local var declaration
     */
    public function getUsePrepCode() : string 
    {
        return '';
    }

    /**
     * Returns the usable C variable contining the arguments value
     */
    public function getUsableVariable() : string
    {
        return $this->name;
    }
}
