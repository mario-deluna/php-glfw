<?php 

namespace GLSpec;

class GLVersion
{
    public string $name;

    public string $versionString;

    public string $api;

    public $functions = [];

    public $enums = [];

    public $removedFunctions = [];

    public $removedEnums = [];

    public function versionInt() : int
    {
        return static::versionIntFromString($this->versionString);
    }

    public static function versionIntFromString(string $versionString) : int
    {
        $parts = explode('.', $versionString);
        foreach($parts as &$n) {
            $n = str_pad($n, 2, '0', STR_PAD_LEFT);
        }
        
        return (int) implode('', $parts);
    }
}