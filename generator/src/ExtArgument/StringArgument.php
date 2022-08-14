<?php

namespace ExtArgument;

use ExtArgument;

class StringArgument extends ExtArgument
{
    /**
     * The char used for parsing the arguments with the zend engine
     */
    public string $charid = 's';

    /**
     * Returns boolean if the PHP type is of the same size as the internal one
     */
    public function typeIsOfSameInternalSize() : bool
    {
        return $this->getPureFromType() === 'GLchar' || $this->getPureFromType() === 'char';
    }

    /**
     * Returns a string that contains the declaration of the variable 
     */
    public function getVariableDeclaration() : string
    {
        $b = sprintf("const char *%s;\n", $this->getInternalVariable());
        $b .= sprintf("size_t %s_size;\n", $this->getInternalVariable());

        return $b;
    }

    /**
    * Retruns the code for the zval to be converted to the arguments expected type
    * return null if no conversion is required / possible
    */
    public function getZValConversionCode(string $zvalVar) : ?string 
    {
        return 'convert_to_string(' . $zvalVar . ');';
    }

    /**
    * If the argument is passed as a ZVal the actual value is behind a data structre
    * this method should return the C code to the actual value
    */
    public function getUsableVariableFromZVal(string $zvalVar) : string 
    {
        return 'Z_SVAL_P(' . $zvalVar . ')';
    }

    /**
     * An array of C arguments passed to the "zend_parse_parameters" function. usally just one 
     */
    public function getZendParameterParseArguments() : array
    {
        return [
            '&' . $this->getInternalVariable(),
            '&' . $this->getInternalVariable() . '_size',
        ];
    }
    
    /**
     * Returns the C macro to assign this type of argument to zval
     *     MACRO(zval, value)
     */
    public function getZvalAssignmentMacro() : string
    {
        return 'ZVAL_STRING';
    }
}
