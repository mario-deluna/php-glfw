<?php

use ExtArgument\{
    LongArgument,
    BoolArgument,
    DoubleArgument,
    StringArgument,
    NullArgument,
    InternalPtrObjectArgument,
    CEObjectArgument,
    FunctionArgument,
    VariadicArgument,
};

/**
 * Function call argument 
 */
abstract class ExtArgument
{
    public static function make(string $name, string $argumentType) : ExtArgument
    {
        switch($argumentType) {
            case ExtType::T_LONG:
                return new LongArgument($name, $argumentType);
            break;
            case ExtType::T_DOUBLE:
                return new DoubleArgument($name, $argumentType);
            break;
            case ExtType::T_BOOL:
                return new BoolArgument($name, $argumentType);
            break;
            case ExtType::T_STRING:
                return new StringArgument($name, $argumentType);
            break;
            case ExtType::T_NULL:
                return new NullArgument($name, $argumentType);
            break;
            case ExtType::T_IPO:
                return new InternalPtrObjectArgument($name, $argumentType);
            break;
            case ExtType::T_CE:
                return new CEObjectArgument($name, $argumentType);
            break;
            case ExtType::T_FUNC:
                return new FunctionArgument($name, $argumentType);
            break;
            case ExtType::T_VARIADIC:
                throw new \Exception("Please construct variadic arguments with 'new VariadicArgument'");
            break;
            default: 
                throw new \Exception("Unsupported argument type {$argumentType}");
        }
    }

    /**
     * The name of the argument, also used in the declation
     */
    public string $name;

    /**
     * A comment describing the argument and its use 
     */
    public ?string $comment = null;

    /**
     * The generator internal type of the argument
     */
    public string $argumentType;

    /**
     * The C type the argument should be cast from
     */
    public ?string $argumentTypeFrom = null;

    /**
     * The char used for parsing the arguments with the zend engine
     * 
     * Z_PARAM_ARRAY()                "a" 
     * Z_PARAM_ARRAY_OR_OBJECT()      "A" 
     * Z_PARAM_BOOL()                 "b" 
     * Z_PARAM_CLASS()                "C" 
     * Z_PARAM_DOUBLE()               "d" 
     * Z_PARAM_FUNC()                 "f" 
     * Z_PARAM_ARRAY_HT()             "h" 
     * Z_PARAM_ARRAY_OR_OBJECT_HT()   "H" 
     * Z_PARAM_LONG()                 "l" 
     * Z_PARAM_STRICT_LONG()          "L" 
     * Z_PARAM_OBJECT()               "o" 
     * Z_PARAM_OBJECT_OF_CLASS()      "O" 
     * Z_PARAM_PATH()                 "p" 
     * Z_PARAM_PATH_STR()             "P" 
     * Z_PARAM_RESOURCE()             "r" 
     * Z_PARAM_STRING()               "s" 
     * Z_PARAM_STR()                  "S" 
     * Z_PARAM_ZVAL()                 "z" 
     * Z_PARAM_VARIADIC()             "+"
     * 
     * @var string
     */
    public string $charid;

    /**
     * The prefix used for a var declaration
     */
    public string $variableDeclarationPrefix;

    /**
     * The C default value for the argument, if null === required value
     */
    public ?string $defaultValue = null;

    /**
     * Is the argument passed by referenced?
     */
    public bool $passedByReference = false;

    /**
     * Is the argument parsed?
     * A not parsed argument won't be parsed from the userland function call
     * but will be present in the generated C function
     */
    public bool $isParsed = true;

    /**
     * Constrcutor
     * @param string $name The name of the argument 
     */
    public function __construct(string $name, string $argumentType)
    {
        $this->name = $name;
        $this->argumentType = $argumentType;
    }

    /**
     * Returns the arguments zval name which is prefixed to avoid collisions.
     */
    public function getZValName() : string
    {
        return $this->name . '_zval';
    }

    /**
     * Returns the arguments temporary var name, used when types don't match and we
     * have to pass a pointer
     */
    public function getTmpVarName() : string
    {
        return $this->name . '_tmp';
    }

    /**
     * Returns the internal type without any pointer or const shenanigans
     */
    public function getPureFromType() : string
    {
        return trim(str_replace('const ', '', $this->argumentTypeFrom ?? ''), ' *');
    }

    /**
     * Returns a string that contains the declaration of the variable 
     */
    public function getVariableDeclaration() : string
    {
        // reference values are passed as zval's which have
        // to be dereferencd later
        if ($this->passedByReference) {
            $b = 'zval *' . $this->getZValName() . '';
            if ($this->isOptional()) {
                $b .= ' = ' . $this->getDefaultValue();
            }
            
            $b .= ';' . PHP_EOL;

            // if the size don't match also declare a temp var
            if (!$this->typeIsOfSameInternalSize()) {
                $b .= $this->getPureFromType() . ' ' . $this->getTmpVarName() . ';';
            }

            return $b;
        }

        if (!isset($this->variableDeclarationPrefix)) {
            throw new Exception(sprintf("The current argument %s type does not define the variableDeclarationPrefix property..", get_class($this)));
        }

        $b = $this->variableDeclarationPrefix . ' ' . $this->getInternalVariable();

        if ($this->isOptional()) {
            $b .= ' = ' . $this->getDefaultValue();
        }

        return $b . ';';
    }

    /**
     * Returns the to be used char ID for the zend paramter parsing
     */
    public function getCharId() : string 
    {
        if ($this->passedByReference) {
            return 'z';
        }

        return $this->charid;
    }

    /**
     * Returns the arguments default value as a string containing the default in C
     * return null if the value is required.
     */
    public function getDefaultValue() : ?string
    {
        return $this->defaultValue;
    }

    /**
     * Returns bool if the argument is optional
     */
    public function isOptional() : bool
    {
        return $this->getDefaultValue() !== null;
    }

    /**
     * Retruns the code for the zval to be converted to the arguments expected type
     * return null if no conversion is required / possible
     */
    public function getZValConversionCode(string $zvalVar) : ?string 
    {
        return null;
    }

    /**
     * Returns C code to be run after the argument has been assigned to the arguments 
     * local var declaration
     */
    public function getUsePrepCode() : string 
    {
        $b = '';

        // if the argument is passed by reference
        // we have to dereference the zval and ensure its the correct type 
        if ($this->passedByReference) {
            $b .= 'ZVAL_DEREF('. $this->getZValName() .');' . PHP_EOL;
            if ($conv = $this->getZValConversionCode($this->getZValName())) {
                $b .= $conv;
            }
        }

        return $b;
    }

    /**
     * Returns the variable to hold the actual argument, this usally is simply
     * the name but can be the zval when passed by reference
     */
    public function getInternalVariable() : string
    {
        if ($this->passedByReference) {
            return $this->getZValName();
        }

        return $this->name;
    }


    /**
     * Returns boolean if the PHP type is of the same size as the internal one
     */
    public function typeIsOfSameInternalSize() : bool
    {
        return false;
    }

    /**
     * If the argument is passed as a ZVal the actual value is behind a data structre
     * this method should return the C code to the actual value
     */
    public function getUsableVariableFromZVal(string $zvalVar) : string 
    {
        throw new Exception(sprintf('The argument type "%s" does not support beeing used directly as zval.', get_class($this)));  
    }

    /**
     * Returns the usable C variable contining the arguments value
     */
    public function getUsableVariable() : string
    {
        if ($this->passedByReference) {
            if (!$this->typeIsOfSameInternalSize()) {
                return '&' . $this->getTmpVarName();
            }

            return $this->getUsableVariableFromZVal($this->getZValName());
        }
        
        return $this->name;
    }

    /**
     * An array of C arguments passed to the "zend_parse_parameters" function. usally just one 
     */
    public function getZendParameterParseArguments() : array
    {
        return [
            '&' . $this->getInternalVariable(),
        ];
    }

    /**
     * Returns the C macro to assign this type of argument to zval
     *     MACRO(zval, value)
     */
    public function getZvalAssignmentMacro() : string
    {
        throw new Exception(sprintf('The argument type "%s" does not support beeing assigned to zval.', get_class($this)));  
    }

    /**
     * Returns the comparison constant for a zval for this type
     *     IS_LONG
     *     IS_DOUBLE
     */
    public function getZvalTypeComparisonConst() : string
    {
        throw new Exception(sprintf('The argument type "%s" does not support zval comparison.', get_class($this)));  
    }


    /**
     * Returns the comparison constant for a zval for this type
     *     Z_LVAL_P
     */
    public function getValueFromZvalPointerConst() : string
    {
        throw new Exception(sprintf('The argument type "%s" does not support getting a value from.', get_class($this)));  
    }

    /**
     * Returns the comparison constant for a zval for this type
     *     RETURN_LONG
     */
    public function getReturnValueAssignment() : string
    {
        throw new Exception(sprintf('The argument type "%s" does not support a return value cast', get_class($this)));  
    }
}