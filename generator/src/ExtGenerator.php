<?php

class ExtGenerator
{
    /**
     * @var array<ExtConstant>
     */
    public array $constants = [];

    public array $methods = [];

    public array $resources = [];

    /**
     * Adds a constant to the extension
     */
    public function addConstant(ExtConstant $const)
    {
        $this->constants[] = $const;
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

        foreach($spec->functionIterator($api, $version) as $func) 
        {
            $phpfunc = new ExtFunction($func->name);

            if ($func->returnTypeString !== 'void') continue;
            if (count($func->arguments) > 0) continue;
            
            // var_dump($phpfunc,$func);

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
            '__buffer_prefix' => '<?php ' . PHP_EOL
        ]);
    }

    private function buildFunctionsBody()
    {
        $buffer = $this->generateTemplate('phpglfw_functions.c', [
            'functions' => $this->methods,
        ]);
    }

}
