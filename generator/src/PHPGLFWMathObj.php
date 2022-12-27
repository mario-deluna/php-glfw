<?php

class PHPGLFWMathObj
{
    /**
     * Math class name
     */
    public string $name;

    /**
     * Number of components of this class
     */
    public int $size;

    /**
     * Constructor
     */
    public function __construct(string $name, int $size) 
    {
        $this->name = $name;
        $this->size = $size;
    }

    private array $propNames = ['x', 'y', 'z', 'w'];
    private array $altPropNames = ['r', 'g', 'b', 'a'];

    public function isVector() : bool {
        return substr($this->name, 0, 3) === 'Vec';
    }
    public function isMatrix() : bool {
        return substr($this->name, 0, 3) === 'Mat';
    }
    public function isQuat() : bool {
        return $this->name === 'Quat';
    }

    public function propNameForPos(int $p) : string {
        return $this->propNames[$p];
    }

    public function altPropNameForPos(int $p) : string {
        return $this->altPropNames[$p];
    }

    public function getPropIt() 
    {
        for ($i = 0; $i<$this->size; $i++) {
            yield $i => $this->propNameForPos($i);
        }
    }

    public function getAltPropIt() 
    {
        for ($i = 0; $i<$this->size; $i++) {
            yield $i => $this->altPropNameForPos($i);
        }
    }

    /**
     * Returns a string used to construct functions names, var names etc.
     */
    public function getInternalNameString() : string
    {
        return strtolower($this->name);
    }   

    /**
     * Returns the internal data type of the object (vec3, mat4) etc..
     */
    public function getInternalDataType() : string 
    {
        if ($this->isMatrix()) {
            return 'mat4x4';
        }

        return strtolower($this->name);
    }
    
    public function getClassEntryName() : string
    {
        return sprintf("phpglfw_math_%s_ce", $this->getInternalNameString());
    }

    public function getVecFunction(string $func) : string
    {
        return sprintf("vec%d_%s", $this->size, $func);
    }

    public function getMatFunction(string $func) : string
    {
        return sprintf("mat4x4_%s", $func);
    }

    public function getQuatFunction(string $func) : string
    {
        return sprintf("quat_%s", $func);
    }
    
    public function getClassEntryNameGetter() : string
    {
        return sprintf("phpglfw_get_math_%s_ce", $this->getInternalNameString());
    }

    public function getFullNamespaceString() : string
    {
        return sprintf("GL\\Math\\%s", $this->name);
    }

    public function getFullNamespaceCString() : string
    {
        return '"' . trim(var_export($this->getFullNamespaceString(), true), "'") . '"';
    }

    public function getObjectName() : string
    {
        return sprintf("phpglfw_math_%s_object", $this->getInternalNameString());
    }

    public function objectFromZObjFunctionName() : string
    {
        return sprintf("phpglfw_math_%s_objectptr_from_zobj_p", $this->getInternalNameString());
    }

    public function getHandlersVarName() : string
    {
        return sprintf("phpglfw_math_%s_handlers", $this->getInternalNameString());
    }

    public function getHandlerMethodName(string $handler) : string
    {
        return sprintf("phpglfw_math_%s_%s_handler", $this->getInternalNameString(), $handler);
    }

    public function getFullNamespaceConstString() : string
    {
        return str_replace("\\", '_', $this->getFullNamespaceString());   
    }

    public function getPhpArgs() : string
    {
        if ($this->isMatrix()) {
            return '';
        }

        $args = [];

        for($i=0; $i<$this->size; $i++) {
            $args[] = '?float $' . $this->propNameForPos($i) . ' = null';
        }
        
        return implode(', ', $args);
    }

    public function getVectorZendParseParamters() : string
    {
        $b = '';
        $args = [];

        for($i=0; $i<$this->size; $i++) {
            $var = $this->propNameForPos($i) . 'val';
            $b .= 'double ' . $var . ' = 0.0;' . PHP_EOL;
            $args[] = '&' . $var;
        }
        
        $b .= PHP_EOL;

        $argsstring = str_repeat('d', $this->size);
        $argsstring = substr_replace($argsstring, '|', 0, 0);
    
        $b .= sprintf('if (zend_parse_parameters(ZEND_NUM_ARGS(), "%s", %s) == FAILURE) {', $argsstring, implode(', ', $args));

        return $b;
    }
}
