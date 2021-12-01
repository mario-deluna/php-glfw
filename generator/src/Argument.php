<?php 

/**
 * Base argument
 */
abstract class Argument 
{
    public $name;
    public $charid;
    public $passedByRef = false;
    public $realType = 'void';
    public $shouldDeref = false;
    
    public function __construct(string $name) 
    { 
        if ($name[0] === '&') {
            $this->passedByRef = true;
            $name = substr($name, 1);
        }

        if (strpos($name, ':') !== false) {
            list($name, $this->realType) = explode(':', $name);
        }

        $this->name = $name; 
    }

    abstract public function generateVariable() : string;

    public function getVariable() {
        if ($this->passedByRef) {
            return "zval *z_{$this->name};";
        }
        return $this->generateVariable();
    }

    public function getReferences() {
        if ($this->passedByRef) {
            return '&z_' . $this->name;
        }
        return '&' . $this->name;
    }

    public function getCharId() : string {
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
 */
class LongArgument extends Argument {
    public $charid = 'l';
    public function generateVariable() : string {
        return "zend_long {$this->name};";
    }
    public function generateZValConvertion() : string {
        return " convert_to_long(z_{$this->name});";
    }
    public function getCallName() {
        if ($this->passedByRef) {
            return "({$this->realType} *)" . parent::getCallName();
        }
        return parent::getCallName();
    }
}
class DoubleArgument extends Argument {
    public $charid = 'd';
    public function generateVariable() : string {
        return "double {$this->name};";
    }
    public function generateZValConvertion() : string {
        return " convert_to_double(z_{$this->name});";
    }
    public function getCallName() {
        if ($this->passedByRef) {
            return "({$this->realType} *)" . parent::getCallName();
        }
        return parent::getCallName();
    }
}
class BoolArgument extends Argument {
    public $charid = 'b';
    public function generateVariable() : string {
        return "zend_bool {$this->name};";
    }
}
class NullArgument extends Argument {
    public function generateVariable() : string {
        return "";
    }
    public function getCallName() {
        return "NULL";
    }
}
class StringArgument extends Argument {
    public $charid = 's';
    public function generateVariable() : string {
        return "const char *{$this->name};\nsize_t {$this->name}_size;";
    }
    public function getReferences() {
        return '&' . $this->name . ', &' . $this->name . '_size';
    }
}
class ResourceArgument extends Argument {
    public $charid = 'r';
    public function generateVariable() : string {
        return "zval *{$this->name}_resource;";
    }
    public function getReferences() {
        return "&{$this->name}_resource";
    }
}
class HashTableArgument extends Argument {
    public $charid = 'h';
    public function generateVariable() : string {
        return "HashTable *{$this->name}; zval *{$this->name}_data;";
    }
}
