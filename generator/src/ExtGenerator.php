<?php

use PHPGlfwAdjustments\AdjustmentInterface;

use PhpParser\Node;
use PhpParser\Node\Stmt\ClassMethod;
use PhpParser\NodeTraverser;
use PhpParser\NodeVisitorAbstract;
use PhpParser\ParserFactory;
use PhpParser\Node\Stmt\Function_;
use PhpParser\NodeVisitor\NameResolver;
use PhpParser\NodeVisitor\ParentConnectingVisitor;

class ExtGenerator
{
    /**
     * @var array<string, ExtConstant>
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
     * Array of PHPGLFW buffers to be generated
     */
    public array $phpglfwBuffers = [];

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
     * Instance of the doc parser 
     */
    private ?ExtDocParser $docParser = null;

    /**
     * Adds a constant to the extension
     */
    public function addConstant(ExtConstant $const) : void
    {
        $this->constants[$const->name] = $const;
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
     * Find a extension function instance by name
     */
    public function getFunctionByName(string $functionName) : ?ExtFunction
    {
        foreach($this->methods as $func) {
            if ($func->name === $functionName) {
                return $func;
            }
        }

        return null;
    }

    /**
     * Returns an array of function which name matches the given regex
     * 
     * @return array<ExtFunction>
     */
    public function findFunctionsMatching(string $regex) : array
    {
        $matches = [];

        foreach($this->methods as $func) {
            if (preg_match($regex, $func->name)) {
                $matches[] = $func;
            }
        }

        return $matches;
    }

    /**
     * Returns an array of function names matching the given regex
     * 
     * @return array<string>
     */
    public function findFunctionNamesMatching(string $regex) : array
    {
        return array_column($this->findFunctionsMatching($regex), 'name');
    }

    /**
     * Find a extension function instance by name and replace it.
     * If the function does not already exists it will simply be added.
     */
    public function replaceFunctionByName(ExtFunction $replacement) : void
    {
        foreach($this->methods as $k => $func) {
            if ($func->name === $replacement->name) {
                $this->methods[$k] = $replacement;
                return;
            }
        }

        // just add it if not replacable
        $this->methods[] = $replacement;
    }

    /**
     * Import the given GLSpec into the extension generator
     * 
     * @param GLSpec            $spec
     * @param string            $api
     * @param string            $version
     * @param array<string>     $ignoredFunctions an array of function names to be ignored during import
     */
    function import(GLSpec $spec, string $api, string $version, array $ignoredFunctions = [])
    {
        // add custom constants for the build API + version 
        $glfwExtCG = new ExtConstantGroup();
        $glfwExtCG->name = "PHPGlfw Extension";

        $apiConst = new ExtConstant("PHPGLFW_COMPILED_API", $api, var_export($api, true));
        $apiConst->isForwardDefinition = false;
        $apiConst->constantCompiledType = ExtConstant::TYPE_STRING;
        $apiConst->group = $glfwExtCG;
        $this->addConstant($apiConst);

        $apiVersionConst = new ExtConstant("PHPGLFW_COMPILED_API_VERSION", $version, var_export($version, true));
        $apiVersionConst->isForwardDefinition = false;
        $apiVersionConst->constantCompiledType = ExtConstant::TYPE_STRING;
        $apiVersionConst->group = $glfwExtCG;
        $this->addConstant($apiVersionConst);

        foreach([
            'GLbyte' => ['BYTE', 1],
            'GLubyte' => ['UNSIGNED_BYTE', 1],
            'GLshort' => ['SHORT', 2],
            'GLushort' => ['UNSIGNED_SHORT', 2],
            'GLint' => ['INT', 4],
            'GLuint' => ['UNSIGNED_INT', 4],
            'GLfloat' => ['FLOAT', 4],
            'GLhalf' => ['HALF_FLOAT', 2],
            'GLdouble' => ['DOUBLE', 8],
        ] as $type => [$name, $nb]) {
            // size of varios data typey
            $glSizeofType = new ExtConstant("GL_SIZEOF_" . $name, 'sizeof('. $type .')', $nb);
            $glSizeofType->isForwardDefinition = false;
            $glSizeofType->constantCompiledType = ExtConstant::TYPE_PASSTHROUGH;
            $glSizeofType->group = $glfwExtCG;
            $this->addConstant($glSizeofType);
        }

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

        // return;
        foreach($spec->functionIterator($api, $version) as $func) 
        {
            // skip ignored functions
            if (in_array($func->name, $ignoredFunctions)) {
                continue;
            }

            // if ($func->name === 'glGetString') {
            //     var_dump($func); die;
            // }

            $phpfunc = new ExtFunction($func->name);
            $phpfunc->incomplete = false;
            $phpfunc->comment = $func->commentSummary;

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
            if (!isset($this->glTypeToExtType[$func->returnTypeString])) {
                if (GEN_VERBOSE) printf("Unmapped return type '%s' in function (%s)\n", $func->returnTypeString, $func->name);
                $phpfunc->incomplete = true;
            }

            // skip pointer return types
            if ($func->isPointerReturn()) {
                if (GEN_VERBOSE) printf("Pointer return type in function (%s)\n", $func->name);
                $phpfunc->incomplete = true;
            }

            // skip functions with unmapped arguments
            foreach($func->arguments as $argument) 
            {
                $phparg = null;

                // direct map
                if (isset($this->glTypeToExtType[$argument->typeString]) && $argument->isPointer() === false) 
                {
                    $phparg = ExtArgument::make($argument->name, $this->glTypeToExtType[$argument->typeString]);
                    if ($argument->typeString != $phparg->argumentType) {
                        $phparg->argumentTypeFrom = $argument->fullTypeString;
                    }

                    $phpfunc->arguments[] = $phparg;
                }
                // pointer but and not const we assume to be passed by ref in the ext
                elseif (isset($this->glTypeToExtType[$argument->typeString]) && $argument->isPointer() === true && $argument->isConst() === false) 
                {
                    $phparg = ExtArgument::make($argument->name, $this->glTypeToExtType[$argument->typeString]);
                    $phparg->passedByReference = true;
                    if ($argument->typeString != $phparg->argumentType) {
                        $phparg->argumentTypeFrom = $argument->fullTypeString;
                    }

                    $phpfunc->arguments[] = $phparg;
                }
                // pointer and const..
                elseif (isset($this->glTypeToExtType[$argument->typeString]) && $argument->isPointer() === true && $argument->isConst() === true) 
                {
                    $phparg = ExtArgument::make($argument->name, $this->glTypeToExtType[$argument->typeString]);
                    if ($argument->typeString != $phparg->argumentType) {
                        $phparg->argumentTypeFrom = $argument->fullTypeString;
                    }

                    $phpfunc->arguments[] = $phparg;
                    $phpfunc->incomplete = true;
                }
                // we simply assume all "const GLchar pointers" to be strings 
                elseif ($argument->typeString === 'GLchar' && $argument->isPointer() && $argument->isConst()) 
                {
                    $phparg = ExtArgument::make($argument->name, ExtType::T_STRING);
                    $phparg->argumentTypeFrom = $argument->typeString;

                    $phpfunc->arguments[] = $phparg;
                }
                // otherwise unmappable
                else {
                    if (GEN_VERBOSE) printf("Unmapped argument type '%s' (%s), in function (%s)\n", $argument->fullTypeString, $argument->typeString, $func->name);
                    $phpfunc->incomplete = true;
                    continue 1;
                }
                
                // add reference page comment
                $phparg->comment = $argument->comment;
            }

            //  assign return type
            if ($this->glTypeToExtType[$func->returnTypeString]) {
                $phpfunc->returnType = $this->mapGlTypeToExtType($func->returnTypeString);
            }
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
    private function generateTemplate(string $templateName, array $params, bool $writefile = true) : string
    {
        $buffer = $this->renderTemplate($templateName, $params);

        if (isset($params['__buffer_prefix'])) {
            $buffer = $params['__buffer_prefix'] . $buffer;
        }

        if ($writefile) file_put_contents(GEN_PATH_EXT . '/' . $templateName, $buffer);

        return $buffer;
    }

    /**
     * Adjust the current generator based on the given adjustments
     * 
     * @param class-string<AdjustmentInterface>          $adjustmentClass
     */
    public function adjust(string $adjustmentClass) : void
    {
        $adjustment = new $adjustmentClass;
        $adjustment->handle($this);
    }

    /**
     * Returns an array of all functions in this extension that are not marked incomplete
     * 
     * @return array<ExtFunction>
     */
    public function getCompleteFunctions() : array
    {
        return array_filter($this->methods, function($f) {
            return !$f->incomplete;
        });
    }

    /**
     * Returns math objects
     * 
     * @return array<PHPGLFWMathObj>
     */
    private function getMathObjects() : array
    {
        $mobjarr = [];
        $mobjarr[] = new PHPGLFWMathObj('Vec2', 2);
        $mobjarr[] = new PHPGLFWMathObj('Vec3', 3);
        $mobjarr[] = new PHPGLFWMathObj('Vec4', 4);

        $mobjarr[] = new PHPGLFWMathObj('Quat', 4);

        $mobjarr[] = new PHPGLFWMathObj('Mat4', 16);

        return $mobjarr;
    }

    /**
     * Generates the extension files at the given path
     * 
     * @param string            $path
     */
    public function build(string $path) : void
    {
        $this->buildConstantsHeader();
        $this->buildConstantsBody();
        $this->buildFunctionsHeader();
        $this->buildFunctionsBody();
        $this->buildGLBufferHeaderAndBody();
        $this->buildGLMathHeaderAndBody();
        $this->buildStubs();

        // docs 
        $this->docParser = new ExtDocParser;
        $this->buildDocsBuffer();
        $this->buildDocsMath();
        $this->buildDocsOpenGL();
        $this->buildDocsGLFW();
        $this->buildDocsCommon();

        // copy stubs if directory exists (this is rather specific to my setup)
        // cp phpglfw.stub.php ../../phpgl/ide-stubs/src/phpglfw.php
        if (file_exists(__DIR__ . '/../../../../phpgl/ide-stubs/src/phpglfw.php')) {
            copy(__DIR__ . '/../../stubs/phpglfw.php', __DIR__ . '/../../../../phpgl/ide-stubs/src/phpglfw.php');
        }

        foreach($this->methods as $func) {
            if ($func->incomplete) {
                echo "Icomplete function: " . $func->name . "\n";
            }
        }
    }

    /**
     * Build the "phpglfw_constants" header file
     */
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

        $this->generateTemplate('phpglfw_constants.h', [
            'groupedConstants' => $groupedConstants
        ]);
    }

    /**
     * Build the "phpglfw_constants" body file
     */
    private function buildConstantsBody()
    {
        $buffer = $this->generateTemplate('phpglfw_constants.c', [
            'constants' => $this->constants,
        ]);
    }

    /**
     * Build the "phpglfw_functions" header file
     */
    private function buildFunctionsHeader() : void
    {
        $this->generateTemplate('phpglfw_functions.h', [
            'functions' => $this->getCompleteFunctions(),
            'ipos' => $this->IPOs,
        ]);
    }

    /**
     * Build the "phpglfw_functions" body file
     */
    private function buildFunctionsBody() : void
    {
        $this->generateTemplate('phpglfw_functions.c', [
            'functions' => $this->getCompleteFunctions(),
            'ipos' => $this->IPOs,
        ]);
    }

    /**
     * Builds the "phpglfw_buffer" files
     */
    private function buildGLBufferHeaderAndBody() : void
    {
        $this->generateTemplate('phpglfw_buffer.h', [
            'buffers' => $this->phpglfwBuffers,
        ]);
        $this->generateTemplate('phpglfw_buffer.c', [
            'buffers' => $this->phpglfwBuffers,
        ]);
    }


    /**
     * Builds the "phpglfw_math" files
     */
    private function buildGLMathHeaderAndBody() : void
    {
        $mobjarr = $this->getMathObjects();

        $this->generateTemplate('phpglfw_math.h', [
            'objects' => $mobjarr,
        ]);
        $this->generateTemplate('phpglfw_math.c', [
            'objects' => $mobjarr,
        ]);
    }

    /**
     * Builds the PHP Stubs file
     */
    private function buildStubs() : void
    {   
        $mobjarr = $this->getMathObjects();

        // build the extension stub file
        // used for autogenerating the arginfo.h header and class entries
        $this->generateTemplate('phpglfw.stub.php', [
            'mathObjects' => $mobjarr,
            'buffers' => $this->phpglfwBuffers,
            'constants' => $this->constants,
            'functions' => $this->getCompleteFunctions(),
            '__buffer_prefix' => '<?php ' . PHP_EOL
        ]);

        // build the IDE stubs file
        // IDE stubs contian comments and meta information for the user
        // the extension stubs are only used for building the extension
        file_put_contents(GEN_PATH_EXT . '/stubs/phpglfw.php', $this->generateTemplate('stubs/phpglfw.php', [
            'mathObjects' => $mobjarr,
            'buffers' => $this->phpglfwBuffers,
            'constants' => $this->constants,
            'functions' => $this->getCompleteFunctions(),
            '__buffer_prefix' => '<?php ' . PHP_EOL
        ], false));
    }

    /**
     * Builds the Docs / Buffer
     */
    private function buildDocsBuffer() : void
    {
        foreach($this->phpglfwBuffers as $buffer) {
            file_put_contents(GEN_PATH_EXT . '/docs/API/Buffer/' . $buffer->name . '.md', $this->generateTemplate('docs/buffer.md', [
                'buffer' => $buffer,
                'docParser' => $this->docParser,
            ], false));
        }
    }

    /**
     * Builds the Docs / Math
     */
    private function buildDocsMath() : void
    {
        $mobjarr = $this->getMathObjects();

        foreach($mobjarr as $mobj) {
            if ($mobj->isVector()) {
                file_put_contents(GEN_PATH_EXT . '/docs/API/Math/' . $mobj->name . '.md', $this->generateTemplate('docs/math_vec.md', [
                    'docParser' => $this->docParser,
                    'vec' => $mobj,
                ], false));
            }
        }
    }

    /**
     * Builds the Docs / Buffer
     */
    private function buildDocsOpenGL() : void
    {
        foreach($this->getCompleteFunctions() as $func) {

            if (substr($func->name, 0, 2) !== 'gl' || substr($func->name, 0, 4) === 'glfw') continue;

            $path = GEN_PATH_EXT . '/docs/API/OpenGL/' . $func->name . '.md';

            file_put_contents($path, $this->generateTemplate('docs/opengl_func.md', [
                'func' => $func,
                'docParser' => $this->docParser,
            ], false));
        }
    }

    /**
     * Builds the Docs / Buffer
     */
    private function buildDocsGLFW() : void
    {
        foreach($this->getCompleteFunctions() as $func) {

            if (substr($func->name, 0, 4) !== 'glfw') continue;

            $path = GEN_PATH_EXT . '/docs/API/GLFW/' . $func->name . '.md';

            file_put_contents($path, $this->generateTemplate('docs/glfw_func.md', [
                'func' => $func,
                'docParser' => $this->docParser,
            ], false));
        }
    }

    private function buildMarkdownDocsFile(string $templateName, string $targetPath)
    {
        $path = GEN_PATH_EXT . '/docs/' . $targetPath;

        file_put_contents($path, $this->generateTemplate('docs/' . $templateName, [
            'docParser' => $this->docParser,
        ], false));
    }

    /**
     * Builds the Docs / Buffer
     */
    private function buildDocsCommon() : void
    {
        // geometry
        $this->buildMarkdownDocsFile('geo_objfileparser.md', 'API/Geometry/ObjFileParser.md');   
        // texture
        $this->buildMarkdownDocsFile('texture_texture2d.md', 'API/Texture/Texture2D.md');   
    }
}
