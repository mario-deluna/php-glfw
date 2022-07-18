<?php

namespace ExtArgument;

use ExtArgument;

class DoubleArgument extends ExtArgument
{
    /**
     * The char used for parsing the arguments with the zend engine
     */
    public string $charid = 'd';

    /**
     * The prefix used for a var declaration
     */
    public string $variableDeclarationPrefix = 'double';

    /**
     * Retruns the code for the zval to be converted to the arguments expected type
     * return null if no conversion is required / possible
     */
    public function getZValConversionCode(string $zvalVar) : ?string 
    {
        return 'convert_to_double(' . $zvalVar . ');';
    }

    /**
     * If the argument is passed as a ZVal the actual value is behind a data structre
     * this method should return the C code to the actual value
     */
    public function getUsableVariableFromZVal(string $zvalVar) : string 
    {
        return '&Z_DVAL_P(' . $zvalVar . ')';
    }

    /**
     * Returns the C macro to assign this type of argument to zval
     *     MACRO(zval, value)
     */
    public function getZvalAssignmentMacro() : string
    {
        return 'ZVAL_DOUBLE';
    }

    /**
     * Returns the comparison constant for a zval for this type
     *     IS_LONG
     *     IS_DOUBLE
     */
    public function getZvalTypeComparisonConst() : string
    {
        return 'IS_DOUBLE';
    }


    /**
     * Returns the comparison constant for a zval for this type
     *     Z_LVAL_P
     */
    public function getValueFromZvalPointerConst() : string
    {
        return 'Z_DVAL_P';
    }
}