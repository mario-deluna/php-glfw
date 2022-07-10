<?php

use GLSpec\{
    GLConstant,
    GLConstantGroup,
    GLFunction,
    GLFunctionArg,
    GLVersion
};

class GLSpec
{
    /**
     * Spec functions
     * 
     * @var array<GLFunction>
     */
    private array $functions = [];

    /**
     * Spec version
     * 
     * @var array<GLVersion>
     */
    private array $versions = [];

    /**
     * Spec constants
     * 
     * @var array<GLConstant>
     */
    private array $constants = [];

    /**
     * Make a spec function object
     * 
     * @return GLFunction
     */
    public function makeFunction(string $functionName) : GLFunction
    {
        $func = new GLFunction;
        $func->name = $functionName;
        $this->functions[$functionName] = $func;
        return $func;
    }

    /**
     * Make a spec function object
     * 
     * @return GLVersion
     */
    public function makeVersion(string $versionString) : GLVersion
    {
        $version = new GLVersion;
        $version->name = $versionString;
        $this->versions[$versionString] = $version;
        return $version;
    }

    /**
     * Make a spec constant object
     * 
     * @return GLConstant
     */
    public function makeConstant(string $constName, string $stringValue) : GLConstant
    {
        $const = new GLConstant;
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
     * @return Generator<GLFunction>
     */
    public function functionIterator(string $api, string $versionString) : Generator
    {
        $versionInt = GLVersion::versionIntFromString($versionString);

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
        $versionInt = GLVersion::versionIntFromString($versionString);

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
