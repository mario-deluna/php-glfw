<?php

class ExtGenerator
{
    public array $constants = [];

    public array $methods = [];

    public array $resources = [];

    function import(GLSpec $spec, string $api, string $version)
    {
        foreach($spec->functionIterator($api, $version) as $func) 
        {
            $phpfunc = new Method();
            $phpfunc->name = $func->name;

            $this->methods[] = $phpfunc;
        }
    } 
}

