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

    private array $arguments = [];

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

    public function functionIterator(string $api, string $versionString)
    {
        $versionInt = GLSpecVersion::versionIntFromString($versionString);

        foreach($this->versions as $version) {
            if ($version->api === $api) {
                if ($version->versionInt() <= $versionInt) {
                    foreach($version->functions as $func) {
                        if (isset($this->functions[$func])) {
                            yield $this->functions[$func];
                        }
                    }
                }
            }
        }
    }
}
