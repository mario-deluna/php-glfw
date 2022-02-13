<?php

class ExtFunction
{
    /**
     * PHP Exposed function name
     */
    public string $name;

    /**
     * Internal name to be called
     */
    public ?string $internalCallFunc = null;

    /**
     * A comment that should be outputted next to the definition
     */
    public ?string $comment = null;

    public function __construct(string $name) 
    {
        $this->name = $name;
        $this->internalCallFunc = $name;
    }
}
