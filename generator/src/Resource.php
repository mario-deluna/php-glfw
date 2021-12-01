<?php

/**
 * Resources
 */
abstract class Resource
{
    public static function getReturnCall(string $for) 
    {
        global $resources;

        foreach($resources as $resource) {
            if ($resource->name != $for) {
                continue;
            }

            return $resource->getReturnResource(). "($resource->name, ".$resource->getContextName().");" . PHP_EOL;
        }
    }

    public $type = 'Unknown *';
    public $name = "resource";

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
        return 'phpglfw_'. $this->name .'_dtor';
    }

    public function generateDestroy() : string {
        return "free(" . $this->name . '); ' . $this->name . ' = NULL;' . PHP_EOL;
    }
}
