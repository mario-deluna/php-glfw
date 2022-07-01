<?php

class ExtGenerator
{
    /**
     * @var array<ExtConstant>
     */
    public array $constants = [];

    /**
     * @var array<ExtFunction>
     */
    public array $methods = [];

    private array $funcSignatures = [];

    /**
     * @var array<string, ExtInternalPtrObject>
     */
    public array $IPOs = [];

    /**
     * Map of GLTypes to extension type
     *
     * @var array<string, string>
     */
    private array $glTypeToExtType = 
    [
        // base types
        'int' => ExtType::T_LONG,
        'long' => ExtType::T_LONG,
        'float' => ExtType::T_DOUBLE,
        'float' => ExtType::T_DOUBLE,
        'bool' => ExtType::T_BOOL,
        'void' => ExtType::T_VOID,

        // gl spec
        // as php only supports long, double and bool....
        'GLboolean' => ExtType::T_BOOL,
        'GLbyte' => ExtType::T_LONG,
        'GLubyte' => ExtType::T_LONG,
        'GLshort' => ExtType::T_LONG,
        'GLushort' => ExtType::T_LONG,
        'GLint' => ExtType::T_LONG,
        'GLuint' => ExtType::T_LONG,
        'GLfixed' => ExtType::T_LONG,
        'GLint64' => ExtType::T_LONG,
        'GLuint64' => ExtType::T_LONG,
        'GLsizei' => ExtType::T_LONG,
        'GLenum' => ExtType::T_LONG,
        'GLintptr' => ExtType::T_LONG,
        'GLsizeiptr' => ExtType::T_LONG,
        'GLsync' => ExtType::T_LONG,
        'GLbitfield' => ExtType::T_LONG,
        'GLhalf' => ExtType::T_DOUBLE,
        'GLfloat' => ExtType::T_DOUBLE,
        'GLclampf' => ExtType::T_DOUBLE,
        'GLdouble' => ExtType::T_DOUBLE,
        'GLclampd' => ExtType::T_DOUBLE,
    ];

    /**
     * Adds a constant to the extension
     */
    public function addConstant(ExtConstant $const) : void
    {
        $this->constants[] = $const;
    }

    /**
     * Adds an internal ptr object ot the extension
     */
    public function addIPO(ExtInternalPtrObject $res) : void 
    {
        $this->IPOs[$res->type] = $res;
    }

    /**
     * Maps the given GLType to an extension function type
     */
    private function mapGlTypeToExtType(string $glType) : string
    {
        if (!isset($this->glTypeToExtType[$glType])) {
            throw new Exception("Cannot map GLType {$glType} to extension type..");
        }

        return $this->glTypeToExtType[$glType];
    }

    /**
     * Import the given GLSpec into the extension generator
     * 
     * @param GLSpec            $spec
     * @param string            $api
     * @param string            $version
     */
    function import(GLSpec $spec, string $api, string $version)
    {
        // add custom constants for the build API + version 
        $glfwExtCG = new ExtConstantGroup();
        $glfwExtCG->name = "PHPGlfw Extension";

        $apiConst = new ExtConstant("PHPGLFW_COMPILED_API", $api);
        $apiConst->isForwardDefinition = false;
        $apiConst->constantCompiledType = ExtConstant::TYPE_STRING;
        $apiConst->group = $glfwExtCG;
        $this->addConstant($apiConst);

        $apiVersionConst = new ExtConstant("PHPGLFW_COMPILED_API_VERSION", $version);
        $apiVersionConst->isForwardDefinition = false;
        $apiVersionConst->constantCompiledType = ExtConstant::TYPE_STRING;
        $apiVersionConst->group = $glfwExtCG;
        $this->addConstant($apiVersionConst);

        // group the GL constants
        $groupedConstants = [];
        foreach($spec->constantIterator($api, $version) as $const) 
        {
            $gid = spl_object_id($const->constGroup);
            if (!isset($groupedConstants[$gid])) {
                $groupedConstants[$gid] = [];
            }

            $groupedConstants[$gid][] = $const;
        }

        // build the constants
        foreach ($groupedConstants as $glConstants) 
        {
            $glGroup = $glConstants[0]->constGroup;

            $extGroup = new ExtConstantGroup();
            $extGroup->name = $glGroup->group;
            $extGroup->desc = implode("\n", array_filter([
                $glGroup->vendor ? ('@vendor ' . $glGroup->vendor) : null,
                $glGroup->comment
            ]));

            foreach($glConstants as $const) {
                // in the case of GL, we use the GL lib definition 
                // and output the value as comment. This results in the 
                // name and definition beeing the same
                $extConst = new ExtConstant($const->name, $const->name, $const->stringVal);
                $extConst->comment = '=> ' . $const->stringVal;
                $extConst->isForwardDefinition = true;
                $extConst->group = $extGroup;
                $this->addConstant($extConst);
            }
        }

        return;
        foreach($spec->functionIterator($api, $version) as $func) 
        {
            $phpfunc = new ExtFunction($func->name);

            $sig = $func->name . '(' . implode(',', array_column($func->arguments, 'name')) . ')';

            // skip duplicated signitures 
            // @todo: figure out why they exist in the first place..
            if (isset($this->funcSignatures[$sig])) {
                continue;
            }
            $this->funcSignatures[$sig] = true;
            
            // if ($func->name === 'glfwCreateWindow') {
            //     var_dump($func, $sig); die;
            // }

            // skip unmapped return types
            if (!isset($this->glTypeToExtType[$func->returnTypeString])) continue;

            // skip pointer return types
            if ($func->isPointerReturn()) continue;

            // skip functions with unmapped arguments
            foreach($func->arguments as $argument) {

                // skip currently unsupported functions
                if (!isset($this->glTypeToExtType[$argument->typeString])) {
                    continue 2;
                }

                if ($argument->isPointer()) continue 2;

                $phparg = ExtArgument::make($argument->name, $this->glTypeToExtType[$argument->typeString]);
                if ($argument->typeString != $phparg->argumentType) {
                    $phparg->argumentTypeFrom = $argument->typeString;
                }
                $phpfunc->arguments[] = $phparg;
            }

            //  assign return type
            $phpfunc->returnType = $this->mapGlTypeToExtType($func->returnTypeString);
            $phpfunc->returnTypeFrom = ($phpfunc->returnType != $func->returnTypeString) ? $func->returnTypeString : null;

            $this->methods[] = $phpfunc;
        }
    }

    /**
     * Renders a template into a string
     */
    private function renderTemplate(string $templateName, array $params) : string
    {
        $templateFullPath = GEN_PATH_TEMPLATES . '/' . $templateName . '.php';
        $templateResultBuffer = "";

        extract($params, EXTR_SKIP);

        ob_start();
        require $templateFullPath;
        $templateResultBuffer = ob_get_clean();

        return $templateResultBuffer;
    }

    /**
     * Same as "renderTemplate" but stores the file directly
     */
    private function generateTemplate(string $templateName, array $params) : string
    {
        $buffer = $this->renderTemplate($templateName, $params);

        if (isset($params['__buffer_prefix'])) {
            $buffer = $params['__buffer_prefix'] . $buffer;
        }

        file_put_contents(GEN_PATH_EXT . '/' . $templateName, $buffer);
        return $buffer;
    }

    /**
     * Generates the extension files at the given path
     * 
     * @param string            $path
     */
    public function build(string $path)
    {
        $this->buildConstantsHeader();
        $this->buildConstantsBody();
        $this->buildFunctionsBody();
        $this->buildStubs();
    }

    private function buildConstantsHeader()
    {
        $groupedConstants = [];
        foreach($this->constants as $const) 
        {
            $gid = spl_object_id($const->group);
            if (!isset($groupedConstants[$gid])) {
                $groupedConstants[$gid] = [$const->group, []];
            }

            $groupedConstants[$gid][1][] = $const;
        }

        $buffer = $this->generateTemplate('phpglfw_constants.h', [
            'groupedConstants' => $groupedConstants
        ]);
    }

    private function buildConstantsBody()
    {
        $buffer = $this->generateTemplate('phpglfw_constants.c', [
            'constants' => $this->constants,
        ]);
    }

    private function buildStubs()
    {
        $buffer = $this->generateTemplate('phpglfw.stub.php', [
            'constants' => $this->constants,
            'functions' => $this->methods,
            '__buffer_prefix' => '<?php ' . PHP_EOL
        ]);
    }

    private function buildFunctionsBody()
    {
        $buffer = $this->generateTemplate('phpglfw_functions.c', [
            'functions' => $this->methods,
            'ipos' => $this->IPOs,
            // 'resources' => $this->resources,
        ]);
    }

}
