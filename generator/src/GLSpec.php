<?php

class GLSpecFunctionArg
{
    public string $name;

    public string $typeString;

    public ?string $class;

    public ?string $group;
}

class GLSpecFunction
{
    public string $name;

    public ?string $class;

    public ?string $group;

    public string $returnTypeString;

    public array $arguments = [];

    public function makeArg() : GLSpecFunctionArg
    {
        $arg = new GLSpecFunctionArg;
        $this->arguments[] = $arg;
        return $arg;
    }
}

class GLSpecVersion
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

class GLSpecConstantGroup
{
    public ?string $group = null;
    public ?string $vendor = null;
    public ?string $comment = null;
}

class GLSpecConstant
{
    public string $name;
    public string $stringVal;
    public ?int $intVal = null;
    public array $groups = [];
    public ?string $comment = null;
    public ?GLSpecConstantGroup $constGroup = null;

    public function setStringValue(string $stringValue) : void
    {
        $this->stringVal = $stringValue;
        if (substr($this->stringVal, 0, 2) === '0x') {
            $this->intVal = (int) hexdec(substr($this->stringVal, 2));
        } elseif (is_numeric($this->stringVal)) {
            $this->intVal = (int) $this->stringVal;
        }
    }
}

class GLSpec
{
    /**
     * Spec functions
     * 
     * @var array<GLSpecFunction>
     */
    private array $functions = [];

    /**
     * Spec version
     * 
     * @var array<GLSpecVersion>
     */
    private array $versions = [];

    /**
     * Spec constants
     * 
     * @var array<GLSpecConstant>
     */
    private array $constants = [];

    /**
     * Make a spec function object
     * 
     * @return GLSpecFunction
     */
    public function makeFunction(string $functionName) : GLSpecFunction
    {
        $func = new GLSpecFunction;
        $func->name = $functionName;
        $this->functions[$functionName] = $func;
        return $func;
    }

    /**
     * Make a spec function object
     * 
     * @return GLSpecVersion
     */
    public function makeVersion(string $versionString) : GLSpecVersion
    {
        $version = new GLSpecVersion;
        $version->name = $versionString;
        $this->versions[$versionString] = $version;
        return $version;
    }

    /**
     * Make a spec constant object
     * 
     * @return GLSpecConstant
     */
    public function makeConstant(string $constName, string $stringValue) : GLSpecConstant
    {
        $const = new GLSpecConstant;
        $const->name = $constName;
        $const->setStringValue($stringValue);
        $this->constants[$constName] = $const;
        return $const;
    }

    /**
     * Iterates over all function definitions in the given API and version
     * 
     * @param string            $api
     * @param string            $versionString
     * @return Generator
     */
    public function functionIterator(string $api, string $versionString) : Generator
    {
        $versionInt = GLSpecVersion::versionIntFromString($versionString);

        $removedFunctions = [];

        foreach($this->versions as $version) {
            if ($version->api === $api) {
                if ($version->versionInt() <= $versionInt) {
                    $removedFunctions = array_merge($removedFunctions, $version->removedFunctions);
                }
            }
        }

        foreach($this->versions as $version) {
            if ($version->api === $api) {
                if ($version->versionInt() <= $versionInt) {
                    foreach($version->functions as $func) {
                        if (isset($this->functions[$func]) && (!in_array($func, $removedFunctions))) {
                            yield $this->functions[$func];
                        }
                    }
                }
            }
        }
    }

    /**
     * Iterates over all constant definitions in the given API and version
     * 
     * @param string            $api
     * @param string            $versionString
     * @return Generator
     */
    public function constantIterator(string $api, string $versionString) : Generator
    {
        $versionInt = GLSpecVersion::versionIntFromString($versionString);

        foreach($this->versions as $version) {
            if ($version->api === $api) {
                if ($version->versionInt() <= $versionInt) {
                    foreach($version->enums as $constName) {
                        if (isset($this->constants[$constName])) {
                            yield $this->constants[$constName];
                        }
                    }
                }
            }
        }
    }
}
