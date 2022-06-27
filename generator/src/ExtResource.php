<?php

class ExtResource
{
    /**
     * Resource name
     */
    public string $name;

    /**
     * Resource Type
     */
    public string $type = 'Unknown *';

    /**
     * Constructor
     */
    public function __construct(string $name, string $type) 
    {
        $this->name = $name;
        $this->type = $type;
    }

    public function getUName() : string {
        return strtoupper($this->name);
    }

    public function getReturnResource() : string {
        return 'PHPGLFW_RETURN_'.$this->getUName().'_RESOURCE';
    }

    public function getResourceName() : string {
        return 'PHPGLFW_'. $this->getUName() .'_NAME';
    }

    public function getContextName() : string {
        return 'phpglfw_' . $this->name . '_context';
    }

    public function getFetchMethod() : string {
        return 'phpglfw_fetch_' . $this->name;
    }

    public function getDtorMethod() : string {
        return 'phpglfw_dtor_'. $this->name;
    }

    public function generateDestroy() : string {
        return "free(" . $this->name . '); ' . $this->name . ' = NULL;' . PHP_EOL;
    }
}
