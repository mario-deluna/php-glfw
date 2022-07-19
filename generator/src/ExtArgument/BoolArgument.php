<?php

namespace ExtArgument;

use ExtArgument;

class BoolArgument extends ExtArgument
{
    /**
     * The char used for parsing the arguments with the zend engine
     */
    public string $charid = 'b';

    /**
     * The prefix used for a var declaration
     */
    public string $variableDeclarationPrefix = 'bool';

    /**
     * Retruns the code for the zval to be converted to the arguments expected type
     * return null if no conversion is required / possible
     */
    public function getZValConversionCode(string $zvalVar) : ?string 
    {
        return 'convert_to_boolean(' . $zvalVar . ');';
    }

    /**
     * If the argument is passed as a ZVal the actual value is behind a data structre
     * this method should return the C code to the actual value
     */
    public function getUsableVariableFromZVal(string $zvalVar) : string 
    {
        return '('. $this->argumentTypeFrom .' *) &Z_LVAL_P(' . $zvalVar . ')';
    }

    /**
     * Returns the C macro to assign this type of argument to zval
     *     MACRO(zval, value)
     */
    public function getZvalAssignmentMacro() : string
    {
        return 'ZVAL_BOOL';
    }
}