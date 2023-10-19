<?php

use ExtArgument\CEObjectArgument;
use ExtArgument\InternalPtrObjectArgument;
use ExtArgument\VariadicArgument;

class ExtFunction
{
    /**
     * PHP Exposed function name
     */
    public string $name;

    /**
     * If true this function is in an incomplete state and should not generate code.
     */
    public bool $incomplete = false;

    /**
     * Internal name, the actual function to be called / forwarded to
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
    public const RETURN_IPO = ExtType::T_IPO;

    /**
     * The original internal return type from the wrapped function
     * @var null|string
     */
    public ?string $returnTypeFrom = null;

    /**
     * The return type of the extension function
     */
    public string $returnType = self::RETURN_VOID;

    /**
     * DocBlock return value comment
     */
    public string $returnComment = '';

    /**
     * The to be returned IPO 
     */
    public ?ExtInternalPtrObject $returnIPO = null;

    /**
     * An array of extension arguments
     * 
     * @var array<ExtArgument>
     */
    public array $arguments = [];

    /**
     * Copy ext function state from the given function
     */
    public function copyFrom(ExtFunction $from) : void
    {
        $this->name = $from->name;
        $this->internalCallFunc = $from->internalCallFunc;
        $this->comment = $from->comment;
        $this->returnTypeFrom = $from->returnTypeFrom;
        $this->returnType = $from->returnType;
        $this->returnIPO = $from->returnIPO;
        $this->arguments = $from->arguments;
    }

    /**
     * Constrctor
     */
    public function __construct(string $name) 
    {
        $this->name = $name;
        $this->internalCallFunc = $name;
    }

    /**
     * Returns the function paramter type list string
     */
    public function getArgumentTypeCharList() : string 
    {
        $b = '';
        $optionalSet = false;
        foreach($this->arguments as $arg) {
            if (!$arg->isParsed) continue;
            if ($arg->isOptional() && $optionalSet === false) {
                $b .= '|';
                $optionalSet = true;
            }
            $b .= $arg->getCharId();
        }
        return $b;
    }

    /**
     * Returns C code for the "zend_parse_parameters" arguments passed based on "getTypeCharList"
     */
    public function getArgumentAssignmentList() : string 
    {
        $args = [];
        foreach($this->arguments as $arg) {
            if (!$arg->isParsed) continue;
            foreach($arg->getZendParameterParseArguments() as $paramArg) {
                $args[] = $paramArg;
            }
        }

        return implode(', ', $args);
    }

    /**
     * Returns the C code responsible for parsing the function arguments into local variables
     */
    public function getArgumentParseCode() : string
    {
        $b = '';

        // define var declaration
        foreach($this->arguments as $arg) {
            if (!$arg->isParsed) continue;
            $b .= $arg->getVariableDeclaration() . PHP_EOL;
        }

        $b .= PHP_EOL . sprintf('if (zend_parse_parameters(ZEND_NUM_ARGS() , "%s", %s) == FAILURE) {', $this->getArgumentTypeCharList(), $this->getArgumentAssignmentList()) . PHP_EOL;
        $b .= '    return;' . PHP_EOL;
        $b .= "}" . PHP_EOL;

        foreach($this->arguments as $arg) {
            if (!$arg->isParsed) continue;
            $b .= $arg->getUsePrepCode() . PHP_EOL;
        }

        return trim($b);
    }

    /**
     * Returns the C code of actually calling the intended function
     */
    public function getFunctionCallCode() : string
    {
        $arguments = [];
        foreach($this->arguments as $arg) {
            $arguments[] = $arg->getUsableVariable();
        }

        return $this->internalCallFunc . '('. implode(', ', $arguments) .')';
    }

    /**
     * Returns the C code for the extension functions return, usally a macro setting "return_value"
     */
    public function getReturnStatement(string $val) : string
    {
        $b = "";

        if ($this->returnType === self::RETURN_VOID) {
            $b .= $val . ';';
        } else {
            switch($this->returnType) {
                case self::RETURN_LONG:
                    $b .= $this->generateExtImplementationReturnLong($val);
                break;
                case self::RETURN_DOUBLE:
                    $b .= $this->generateExtImplementationReturnDouble($val);
                break;
                case self::RETURN_BOOL:
                    $b .= $this->generateExtImplementationReturnBool($val);
                break;
                case self::RETURN_STRING:
                    $b .= $this->generateExtImplementationReturnString($val);
                break;
                case self::RETURN_IPO:
                    $b .= $this->generateExtImplementationReturnIPO($val);
                break;
                default: 
                    throw new \Exception("Unsupported return type {$this->returnType}");
            }
        }

        return trim($b);
    }

    /**
     * Returns the PHP extension function inner C code
     */
    public function getFunctionImplementationBody() : string
    {
        $parsableArguments = array_filter($this->arguments, function($arg) {
            return $arg->isParsed;
        });

        $b = "";
        if (!empty($parsableArguments)) $b .= $this->getArgumentParseCode() . PHP_EOL . PHP_EOL;
        $b .= $this->getReturnStatement($this->getFunctionCallCode());

        // if ($this->name == 'glShaderSource') {
        //     var_dump($this, $b); die;
        // }

        foreach($this->arguments as $arg) {
            if (
                $arg->passedByReference &&
                !$arg->typeIsOfSameInternalSize() && 
                (!$arg instanceof VariadicArgument) &&
                (!$arg instanceof InternalPtrObjectArgument) &&
                (!$arg instanceof CEObjectArgument)
            ) {
                $b .= sprintf("\n%s(%s, %s);", $arg->getZvalAssignmentMacro(), $arg->getZValName(), $arg->getTmpVarName());
            }
        }

        return $b;
    }

    /**
     * Returns the PHP extension function implementation C code
     */
    public function getFunctionImplementation() : string
    {
        return sprintf("PHP_FUNCTION(%s)\n{\n%s\n}", $this->name, tabulate($this->getFunctionImplementationBody()));
    }

    /**
     * Generates a comment block for the current function
     */
    public function getCFunctionCommentBlock() : string
    {
        return commentBlock(trim(sprintf("%s", $this->name)));
    }

    /**
     * Returns the default comment, but allows specific override for the Stubs.
     */
    public function getFunctionPHPComment() : string
    {
        return $this->comment ?: $this->name;
    } 

    /**
     * Generates a comment block for the current function
     */
    public function getFunctionPHPCommentBlock() : string
    {
        $argsBuffer = '';
        foreach($this->arguments as $arg) {
            $argsBuffer .= PHP_EOL . '@param ' . $this->getPHPStubArgument($arg, false) . ' ' . $arg->comment; 
        }

        // add some spaceing if there is content
        if ($argsBuffer) $argsBuffer = PHP_EOL . $argsBuffer . PHP_EOL;

        // retrun tag
        $return = '@return ' . $this->getPHPStubReturn() . ' ' . $this->returnComment;

        return commentBlock(trim(sprintf("%s%s\n%s", $this->getFunctionPHPComment(), $argsBuffer, $return)));
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
     * Generate the method call (Long)
     */
    protected function generateExtImplementationReturnLong(string $call) : string
    {
        return 'RETURN_LONG('. $call .');';
    }

    /**
     * Generate the method call (Double)
     */
    protected function generateExtImplementationReturnDouble(string $call) : string
    {
        return 'RETURN_DOUBLE('. $call .');';
    }

    /**
     * Generate the method call (IPO)
     */
    protected function generateExtImplementationReturnIPO(string $call) : string
    {   
        $b = sprintf("%s %s = %s;\n", $this->returnIPO->getType(), $this->returnIPO->getObjectStructPointerVar(), $call);
        $b .= sprintf("%s(return_value, %s);", $this->returnIPO->getAssignPtrToZvalFunctionName(), $this->returnIPO->getObjectStructPointerVar()); 
        
        return $b;
    }

    private function getPHPStubReturn() : string
    {
        if ($this->returnType === self::RETURN_IPO) {
            return $this->returnIPO->getPHPClassName();
        } else {
            return $this->mapTypeToStubType($this->returnType);
        }
    }

    /**
     * Genreates the PHP stub
     */
    public function getPHPStub() : string
    {
        $stubReturnType = $this->getPHPStubReturn();
        return "function {$this->name}({$this->getPHPStubArguments()}) : {$stubReturnType} {}\n";
    }

    public function getPHPStubArgument(ExtArgument $arg, bool $allowDefaultValue = true) : string
    {
        // IPO argument
        if ($arg->argumentType === ExtType::T_IPO) {
            $buffer = ($arg->isOptional() ? '?' : '') . $arg->argInternalPtrObject->getPHPClassName() . ' ' . '$' . $arg->name;
                
            if ($arg->isOptional() && $allowDefaultValue) {
                $buffer .= ' = ' . $arg->defaultValue;
            }

            return $buffer;
        }
        // class entry argument
        elseif ($arg->argumentType === ExtType::T_CE && $arg instanceof CEObjectArgument) {
            $buffer = ($arg->isOptional() ? '?' : '') . $arg->getPHPClassName() . ' ' . '$' . $arg->name;
                
            if ($arg->isOptional() && $allowDefaultValue) {
                $buffer .= ' = ' . $arg->defaultValue;
            }

           return $buffer;
        } 
        // variadic argument
        elseif ($arg instanceof VariadicArgument) {
            return '?' . $this->mapTypeToStubType($arg->argumentType) . ' ' . ($arg->passedByReference ? '&' : '') . '...$' . $arg->name;
        } else {
            return $this->mapTypeToStubType($arg->argumentType) . ' ' . ($arg->passedByReference ? '&' : '') . '$' . $arg->name;
        }
    }

    public function getPHPStubArguments() : string
    {
        $args = [];
        foreach($this->arguments as $arg) {
            if (!$arg->isParsed) continue;
            $args[] = $this->getPHPStubArgument($arg);
        }

        return implode(', ', $args);
    }

    public function mapTypeToStubType(string $type) : string
    {
        return ExtType::getPHPType($type);
    }
}
