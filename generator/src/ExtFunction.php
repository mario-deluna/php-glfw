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

    /**
     * What will be returned by the function
     */
    public const RETURN_VOID = ExtType::T_VOID;
    public const RETURN_LONG = ExtType::T_LONG;
    public const RETURN_DOUBLE = ExtType::T_DOUBLE;
    public const RETURN_BOOL = ExtType::T_BOOL;
    public const RETURN_STRING = ExtType::T_STRING;
    public const RETURN_RESOURCE = ExtType::T_RESOURCE;

    public ?string $returnTypeFrom = null;
    public string $returnType = self::RETURN_VOID;
    public ?ExtResource $returnResource = null;

    /**
     * An array of extension arguments
     * 
     * @var array<ExtArgument>
     */
    public array $arguments = [];

    /**
     * Constrctor
     */
    public function __construct(string $name) 
    {
        $this->name = $name;
        $this->internalCallFunc = $name;
    }

    /**
     * Genreates the extension C impl
     */
    public function generateExtImplementation()
    {
        $s = "PHP_FUNCTION({$this->name})\n{\n";

        $b = "";
        $typecharlist = '';
        $referencelist = [];
        $argumentVars = [];

        // if we have arguments...
        if (!empty($this->arguments)) 
        {
            foreach($this->arguments as $argument)
            {
                $typecharlist .= $argument->getCharId();
                $referencelist[] = $argument->getReferences();
                $argumentVars[] = $argument->getCallName();

                // add the variable
                $b .= $argument->getVariable() . "\n";
            }

            // create the parser method
            $b .= PHP_EOL . 'if (zend_parse_parameters(ZEND_NUM_ARGS() , "'.$typecharlist.'", '.implode(', ', $referencelist).') == FAILURE) {' . PHP_EOL;
            $b .= '   return;' . PHP_EOL;
            $b .= "}\n";

            // generate dereferencing and converting
            foreach($this->arguments as $argument)
            {
                $b .= $argument->generateDereferencing() . "\n";
            }
        }

        $call = $this->internalCallFunc . '('. implode(', ', $argumentVars) .')';

        if ($this->returnType === self::RETURN_VOID) {
            $b .= $call . ';';
        } else {
            switch($this->returnType) {
                case self::RETURN_LONG:
                    $b .= $this->generateExtImplementationReturnLong($call);
                break;
                case self::RETURN_DOUBLE:
                    $b .= $this->generateExtImplementationReturnDouble($call);
                break;
                case self::RETURN_BOOL:
                    $b .= $this->generateExtImplementationReturnBool($call);
                break;
                case self::RETURN_STRING:
                    $b .= $this->generateExtImplementationReturnString($call);
                break;
                case self::RETURN_RESOURCE:
                    $b .= $this->generateExtImplementationReturnResource($call);
                break;
                default: 
                    throw new \Exception("Unsupported return type {$this->returnType}");
            }
        }

        $b = tabulate($b);

        return "{$s}{$b}\n}\n";
    }

    /**
     * Generate the method call (Bool)
     */
    protected function generateExtImplementationReturnBool(string $call) : string
    {
        return 'RETURN_BOOL('. $call .');';
    }

    /**
     * Generate the method call (String)
     */
    protected function generateExtImplementationReturnString(string $call) : string
    {
        return 'RETURN_STRING('. $call .');';
    }

    /**
     * Generate the method call (Int)
     */
    protected function generateExtImplementationReturnLong(string $call) : string
    {
        return 'RETURN_LONG('. $call .');';
    }

    /**
     * Generate the method call (Int)
     */
    protected function generateExtImplementationReturnDouble(string $call) : string
    {
        return 'RETURN_DOUBLE('. $call .');';
    }

    /**
     * Generate the method call (Int)
     */
    protected function generateExtImplementationReturnResource(string $call) : string
    {   
        $resource = $this->returnResource;
        $buffer = $this->returnTypeFrom . ' '.$resource->name.' = ' . $call . ';' . PHP_EOL;
        $buffer .= $resource->getReturnResource(). "($resource->name, ".$resource->getContextName().");" . PHP_EOL;
        return $buffer;
    }

    /**
     * Genreates the PHP stub
     */
    public function generateStub()
    {
        $stubReturnType = $this->mapTypeToStubType($this->returnType);

        return "function {$this->name}() : {$stubReturnType} {};\n";
    }

    public function mapTypeToStubType(string $type) : string
    {
        switch($type) {
            case 'long':
            case 'int':
                return 'int';
            break;
            case 'double':
            case 'float':
                return 'float';
            break;
            case 'bool':
                return 'bool';
            break;
            case 'void':
                return 'void';
            break;
            case 'string':
                return 'string';
            break;
            case '@res':
                return 'resource';
            break;
            default: 
                throw new \Exception("Unmappable type {$type}");
        }
    }
}
