<?php

namespace ExtArgument;

use Exception;
use ExtArgument;
use ExtInternalPtrObject;

class InternalPtrObjectArgument extends ExtArgument
{
    /**
     * The internal pointer object this argument should point to
     * 
     * @var null|ExtInternalPtrObject
     */
    public ?ExtInternalPtrObject $argInternalPtrObject = null;

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
     * The IPO is always the default O, passed by reference does not change the type
     */
    public function getCharId() : string 
    {
        $c = $this->charid;
        if ($this->isOptional()) $c .= '!';

        return $c;
    }

    /**
     * Simple helper throwing an exception when the IPO is null
     */
    private function requireIPODef()
    {
        if (!$this->argInternalPtrObject) {
            throw new \Exception('Cannot continue with an IPO argument without an IPO assigned.');
        }
    }

    /**
     * An array of C arguments passed to the "zend_parse_parameters" function. usally just one 
     */
    public function getZendParameterParseArguments() : array
    {
        $this->requireIPODef();

        return [
            '&' . $this->getInternalVariable(),
            $this->argInternalPtrObject->getClassEntryName(),
        ];
    }

    /**
     * Returns C code to be run after the argument has been assigned to the arguments 
     * local var declaration
     */
    public function getUsePrepCode() : string 
    {
        return $this->argInternalPtrObject->getInternalPtrFromZValDeclarationCode($this->name, $this->getZValName(), $this->defaultValue);
    }

    /**
     * Returns the usable C variable contining the arguments value
     */
    public function getUsableVariable() : string
    {
        return $this->name;
    }
}
