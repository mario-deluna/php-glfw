<?php

class ExtFunction
{
    /**
     * Constant name
     */
    public string $name;

    /**
     * A comment that should be outputted next to the definition
     */
    public ?string $comment = null;

    public function __construct(string $name) 
    {
        $this->name = $name;
    }
}
