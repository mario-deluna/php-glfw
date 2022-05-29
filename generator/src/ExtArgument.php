<?php

/**
 * Base argument
 *
 * ---------------------------------------------------------
 */
abstract class ExtArgument
{
    public static function make(string $name, string $argumentType) : ExtArgument
    {
        switch($argumentType) {
            case ExtType::T_LONG:
                return new ExtLongArgument($name, $argumentType);
            break;
            case ExtType::T_DOUBLE:
                return new ExtDoubleArgument($name, $argumentType);
            break;
            case ExtType::T_BOOL:
                return new ExtBoolArgument($name, $argumentType);
            break;
            case ExtType::T_STRING:
                return new ExtStringArgument($name, $argumentType);
            break;
            default: 
                throw new \Exception("Unsupported argument type {$argumentType}");
        }
    }

    public string $name;

    public string $argumentType;

    public ?string $argumentTypeFrom = null;

    public string $charid;

    public bool $passedByRef = false;

    public bool $shouldDeref = false;

    public function __construct(string $name, string $argumentType)
    {
        $this->name = $name;
        $this->argumentType = $argumentType;
    }

    abstract public function generateVariable() : string;

    public function getVariable() 
    {
        if ($this->passedByRef) {
            return "zval *z_{$this->name};";
        }
        return $this->generateVariable();
    }

    public function getReferences() 
    {
        if ($this->passedByRef) {
            return '&z_' . $this->name;
        }
        return '&' . $this->name;
    }

    public function getCharId() : string 
    {
        if ($this->passedByRef) {
            return 'z';
        }
        return $this->charid;
    }

    public function generateZValConvertion() : string
    {
        return '';
    }

    public function generateDereferencing() : string 
    {
        if (!$this->passedByRef) {
            return '';
        }

        $b = "ZVAL_DEREF(z_{$this->name});";
        $b .= $this->generateZValConvertion();

        return $b;
    }

    public function getCallName()
    {
        if ($this->passedByRef) {
            return "&z_{$this->name}->value";
        }

        if ($this->shouldDeref) {
            return "&" . $this->name;
        }

        return $this->name;
    }
}

/**
 * Argument types
 *
 * ---------------------------------------------------------
 */

/**
 * long arg
 */
class ExtLongArgument extends ExtArgument
{
    public string $charid = 'l';

    public function generateVariable(): string
    {
        return "zend_long {$this->name};";
    }

    public function generateZValConvertion(): string
    {
        return " convert_to_long(z_{$this->name});";
    }

    public function getCallName()
    {
        if ($this->passedByRef) {
            return "({$this->realType} *)" . parent::getCallName();
        }
        return parent::getCallName();
    }
}

/**
 * double arg
 */
class ExtDoubleArgument extends ExtArgument
{
    public string $charid = 'd';

    public function generateVariable(): string
    {
        return "double {$this->name};";
    }

    public function generateZValConvertion(): string
    {
        return " convert_to_double(z_{$this->name});";
    }

    public function getCallName()
    {
        if ($this->passedByRef) {
            return "({$this->realType} *)" . parent::getCallName();
        }
        return parent::getCallName();
    }
}

/**
 * bool arg
 */
class ExtBoolArgument extends ExtArgument
{
    public string $charid = 'b';

    public function generateVariable(): string
    {
        return "bool {$this->name};";
    }
}

/**
 * null arg
 */
class ExtNullArgument extends ExtArgument
{
    public function generateVariable(): string
    {
        return "";
    }

    public function getCallName()
    {
        return "NULL";
    }
}

/**
 * string arg
 */
class ExtStringArgument extends ExtArgument
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

/**
 * resource arg
 */
class ExtResourceArgument extends ExtArgument
{
    public string $charid = 'r';

    public function generateVariable(): string
    {
        return "zval *{$this->name}_resource;";
    }

    public function getReferences()
    {
        return "&{$this->name}_resource";
    }
}


/**
 * hashtable arg
 */
class ExtHashTableArgument extends ExtArgument
{
    public string $charid = 'h';

    public function generateVariable(): string
    {
        return "HashTable *{$this->name}; zval *{$this->name}_data;";
    }
}
