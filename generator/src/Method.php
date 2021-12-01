<?php
/**
 * This file contains all classes and methods needed
 * to generate the PHP extensions methods including their 
 * argument info and function entry.
 */

/**
 * Base method objects
 */
class Method 
{
    public $name = null;
    public $returns = 'void';
    public $arguments = [];

    /**
     * Does the method have arguments
     */
    public function hasArguments() {
        return !empty($this->arguments);
    }

    /**
     * Get an array of argument objects
     */
    public function getArguments() : array
    {
        $args = [];

        foreach ($this->arguments as $name => $type) 
        {
            $shouldDeref = false;
            if (substr($type, 0, 1) === '&') {
                $shouldDeref = true;
                $type = substr($type, 1);
            }

            $currArg;

            switch ($type) 
            {
                case 'long': $args[] = $currArg = new LongArgument($name); break;
                case 'float': $args[] = $currArg = new FloatArgument($name); break;
                case 'double': $args[] = $currArg = new DoubleArgument($name); break;
                case 'bool': $args[] = $currArg = new BoolArgument($name); break;
                case 'null': $args[] = $currArg = new NullArgument($name); break;
                case 'string': $args[] = $currArg = new StringArgument($name); break;
                case 'resource': $args[] = $currArg = new ResourceArgument($name); break;
                case 'ht': $args[] = $currArg = new HashTableArgument($name); break;
            }

            $currArg->shouldDeref = $shouldDeref;
        }

        return $args;
    }

    /**
     * Prefix every line of the given text
     *
     * @param string        $test
     * @param string        $prefix
     */
    private function tabulate(string $text, string $prefix = '    ') : string
    {
        $lines = array_filter(explode("\n", $text));
        foreach($lines as &$line) 
        {
            $line = $prefix . $line;
        }

        return implode("\n", $lines);
    }

    /**
     * Generate the argument definition name
     */
    protected function generateArgInfoName(string $name) : string
    {
        return "arginfo_{$name}";
    }

    /**
     * Generate the function entry
     */
    public function generateFE() : string
    {
        $arginfo = 'NULL';
        $arginfo = $this->generateArgInfoName($this->name);

        //return "ZEND_RAW_NAMED_FE({$this->name}, zif_{$this->name}, {$arginfo})";
        return "PHP_FE({$this->name}, {$arginfo})";
    }

    /**
     * Generates the argument info definition
     */
    protected function generateArgInfo() : string
    {
        $arginfo = $this->generateArgInfoName($this->name);

        $b = "ZEND_BEGIN_ARG_INFO_EX({$arginfo}, 0, 0, 1)" . PHP_EOL;
        foreach($this->getArguments() as $argument)
        {
            if ($argument instanceof NullArgument) {
                continue;
            }

            $b .= "    ZEND_ARG_INFO(". (int) $argument->passedByRef .", $argument->name)" . PHP_EOL;
        }

        $b .= "ZEND_END_ARG_INFO()" . PHP_EOL;
        
        return $b;
    }

    protected function generateWindowResourceFetchCode() : string
    {
        return "GLFWwindow* window = phpglfw_fetch_window(window_resource );\n";
    }

    protected function generateArgumentParser() : string
    {
        $b = "";

        $typecharlist = '';
        $referencelist = [];

        $hasWindowArg = false;

        // generate the vars
        foreach($this->getArguments() as $argument)
        {
            // skip null
            if ($argument instanceof NullArgument) {
                continue;
            }

            $typecharlist .= $argument->getCharId();
            $referencelist[] = $argument->getReferences();

            // add the variable
            $b .= $argument->getVariable() . "\n";

            if ($argument instanceof WindowArgument) {
                $hasWindowArg = true;
            }
        }

        // create the parser method
        $b .= PHP_EOL . 'if (zend_parse_parameters(ZEND_NUM_ARGS() , "'.$typecharlist.'", '.implode(', ', $referencelist).') == FAILURE) {' . PHP_EOL;
        $b .= '   return;' . PHP_EOL;
        $b .= "}\n";

        // generate dereferencing and converting
        foreach($this->getArguments() as $argument)
        {
            $b .= $argument->generateDereferencing() . "\n";
        }

        // generate the resource fetchers
        foreach($this->getArguments() as $argument) 
        {
            if (!$argument instanceof ResourceArgument) 
            {
                continue;
            }

            // find the matching resource
            global $resources;

            foreach($resources as $resource) 
            {
                if ($resource->name != $argument->name) {
                    continue;
                }

                $b .= $resource->type . $resource->name . ' = ' . $resource->getFetchMethod() . "(". substr($argument->getReferences(), 1) ." );\n";
            }
        }


        return $b;
    }

    /**
     * Generate the method call
     */
    protected function generateCallReturnVoid(string $call) : string
    {
        return $call . ";\n";
    }

    /**
     * Generate the method call (Bool)
     */
    protected function generateCallReturnBool(string $call) : string
    {
        // Im not sure whats exactly behind the `RETURN_TRUE` and `RETURN_FALSE`
        // so this code is probably stupid and should be return $call..
        return 'if ('. $call .') { RETURN_TRUE; } RETURN_FALSE;';
    }

    /**
     * Generate the method call (String)
     */
    protected function generateCallReturnString(string $call) : string
    {
        return 'RETURN_STRING('. $call .');';
    }

    /**
     * Generate the method call (Int)
     */
    protected function generateCallReturnLong(string $call) : string
    {
        return 'RETURN_LONG('. $call .');';
    }

    /**
     * Generate the method call (Int)
     */
    protected function generateCallReturnDouble(string $call) : string
    {
        return 'RETURN_DOUBLE('. $call .');';
    }

    /**
     * Generate the method call
     */
    protected function generateCall() : string
    {
        $arguments = [];

        foreach($this->getArguments() as $argument) 
        {
            $arguments[] = $argument->getCallName();
        }

        $callCode = $this->name . '('. implode(', ', $arguments) .')';

        // check if there might be a resource we want to return
        global $resources;

        foreach($resources as $resource) {
            if ($resource->name != $this->returns) {
                continue;
            }

            return $resource->type . ' ' . $resource->name . ' = ' . $callCode . ";\n" . Resource::getReturnCall($this->returns) . PHP_EOL;
        }

        $returnCodeGenerator = 'generateCallReturn' . ucfirst($this->returns);

        return $this->{$returnCodeGenerator}($callCode);
    }

    /**
     * Generates the method 
     */
    protected function generateMethod() : string
    {
        // we need to work around the glad defines here
        // this allows us to keep the normal gl functions 
        // inside php without the glad prefix
        $b = "PHP_FUNCTION($this->name)\n{\n";
        //$b = "ZEND_NAMED_FUNCTION(zif_{$this->name})\n{\n";

        if ($this->hasArguments()) {
            $b .= $this->tabulate($this->generateArgumentParser());
        }

        $b .= PHP_EOL;

        $b .= $this->tabulate($this->generateCall());

        $b .= "\n}\n";

        return $b;
    }

    /**
     * Main generator call
     */
    public function generate()
    {
        $c = "/**\n * {$this->name}\n * --------------------------------\n */\n";

        return $c . $this->generateArgInfo() . PHP_EOL . $this->generateMethod();
    }
}
