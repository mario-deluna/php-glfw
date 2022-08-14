<?php

namespace ExtArgument;

use Exception;
use ExtArgument;
use ExtInternalPtrObject;

class VariadicArgument extends ExtArgument
{
    /**
     * The char used for parsing the arguments with the zend engine
     */
    public string $charid = '+';

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
     * Returns a string that contains the declaration of the variable 
     */
    public function getVariableDeclaration() : string
    {
        $b = sprintf("zval *%s;\n", $this->getInternalVariable());
        $b .= sprintf("size_t %s_num = 0;\n", $this->getInternalVariable());

        return $b;
    }

    /**
     * An array of C arguments passed to the "zend_parse_parameters" function. usally just one 
     */
    public function getZendParameterParseArguments() : array
    {
        return [
            '&' . $this->getInternalVariable(),
            sprintf("&%s_num", $this->getInternalVariable()),
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
