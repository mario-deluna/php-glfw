<?php

use ExtArgument\CEObjectArgument;

class NVGParser 
{
    /**
     * An array of function names to be always excluded 
     * 
     * @var array<string>
     */
    private array $excludedFunctions = 
    [
        'nvgCreateImage',
    ];

    private array $nvgTypeToExt = 
    [
        'void' => ExtType::T_VOID,
        'int' => ExtType::T_LONG,
        'long' => ExtType::T_LONG,
        'float' => ExtType::T_DOUBLE,
        'double' => ExtType::T_DOUBLE,
    ];

    private function createIPODefinitions(ExtGenerator $extGen)
    {
    }

    public function process(string $headerFilePath, ExtGenerator $extGen)
    {
        // first create required resource definitions
        $this->createIPODefinitions($extGen);

        $headerFile = file_get_contents($headerFilePath);

        preg_match_all('/(int|float|void) (nvg.*)\((.*)\);/', $headerFile, $sigs);

        foreach($sigs[0] as $k => $funcSig) 
        {
            $returnType = $sigs[1][$k];
            $funcName = $sigs[2][$k];
            $params = $sigs[3][$k];

            if (in_array($funcName, $this->excludedFunctions)) {
                continue;
            }

            $phpfunc = new ExtFunction($funcName);
            $phpfunc->name = lcfirst(substr($funcName, 3)); // remove nvg prefix

            if (!isset($this->nvgTypeToExt[$returnType])) {
                $phpfunc->incomplete = true;
            } else {
                $phpfunc->returnType = $this->nvgTypeToExt[$returnType];
            }

            $funcArgs = array_map('trim', explode(',', $params));
            // parse the arguments (const, type, pointer, name)
            foreach($funcArgs as &$arg) {
                preg_match("/^(const +)?([a-zA-Z]+ ?[\*+]?) ?(.*)/", $arg, $match);
                $sourceArg = array_combine(['full', 'const', 'type', 'name'], str_replace(' ', '', array_map('trim', $match)));

                preg_match("/([a-zA-Z0-9]+)[ +]?(\*+)?/", $sourceArg['type'], $pointerTypeArg);
                $rawArgType = $pointerTypeArg[1] ?? null;
                $argIsPointer = ($pointerTypeArg[2] ?? null) === '*';

                if (strpos($sourceArg['full'], '**') !== false) {
                    if (GEN_VERBOSE) printf("** Args currently not supported. (%s)\n", $sourceArg['full']);
                    $phpfunc->incomplete = true;
                    break;
                }

                $isConstCharPtr = $sourceArg['const'] === 'const' && $rawArgType === 'char' && $argIsPointer;

                if (isset($this->nvgTypeToExt[$rawArgType]) && $rawArgType !== 'void') {
                    $phparg = ExtArgument::make($sourceArg['name'], $this->nvgTypeToExt[$rawArgType]);
                    $phparg->argumentTypeFrom = $sourceArg['type'];
                    $phparg->passedByReference = $argIsPointer;
                    $phparg->comment = $paramDesc[$sourceArg['name']] ?? null;
                    $phpfunc->arguments[] = $phparg;
                }
                elseif ($rawArgType === 'NVGcontext') {
                    $phparg = ExtArgument::make('intern->nvgctx', ExtType::T_IPO);
                    $phparg->argumentTypeFrom = $sourceArg['type'];
                    $phparg->passedByReference = $argIsPointer;
                    $phparg->isParsed = false;
                    $phpfunc->arguments[] = $phparg;
                }
                elseif ($rawArgType === 'NVGcolor') {
                    $phparg = new class($sourceArg['name'], ExtType::T_CE) extends CEObjectArgument {
                        public function getClassEntryPointer() : string {
                            return 'phpglfw_get_vg_vgcolor_ce()';
                        }

                        public function getUsePrepCode() : string 
                        {
                            return 'NVGcolor ' .$this->getUsableVariable(). ' = phpglfw_vgcolor_objectptr_from_zobj_p(Z_OBJ_P(color_zval))->nvgcolor;';
                        }
            
                        public function getPHPClassName() : string {
                            return "\\GL\\VectorGraphics\\VGColor";
                        }
                    };
                    $phpfunc->arguments[] = $phparg;
                }
                elseif ($rawArgType === 'NVGpaint') {
                    $phparg = new class($sourceArg['name'], ExtType::T_CE) extends CEObjectArgument {
                        public function getClassEntryPointer() : string {
                            return 'phpglfw_get_vg_vgpaint_ce()';
                        }

                        public function getUsePrepCode() : string 
                        {
                            return 'NVGpaint ' .$this->getUsableVariable(). ' = phpglfw_vgpaint_objectptr_from_zobj_p(Z_OBJ_P(paint_zval))->nvgpaint;';
                        }
            
                        public function getPHPClassName() : string {
                            return "\\GL\\VectorGraphics\\VGPaint";
                        }
                    };
                    $phpfunc->arguments[] = $phparg;
                }
                // for nanoVB we consider const char* always as a string
                elseif ($isConstCharPtr) {
                    $phparg = ExtArgument::make($sourceArg['name'], ExtType::T_STRING);
                    $phparg->argumentTypeFrom = $sourceArg['type'];
                    $phparg->passedByReference = false;
                    $phparg->comment = $paramDesc[$sourceArg['name']] ?? null;

                    // now in PHP-glfw we do not support "end" strings so we discard 
                    // any string arguments called "end"
                    if ($sourceArg['name'] === 'end') {
                        $phparg->isParsed = false;
                        $phparg->name = 'NULL'; // we use the name as the argument identifier in the generated function call
                    }

                    $phpfunc->arguments[] = $phparg;
                }
                else {
                    $phpfunc->incomplete = true;
                }
            }

            // if the first argument is a NVGcontext we consider a context function
            // that should be binded onto the VGContext class
            if (isset($phpfunc->arguments[0]) && $phpfunc->arguments[0]->argumentTypeFrom === 'NVGcontext*') {
                if ($phpfunc->incomplete) {
                    if (GEN_VERBOSE) printf("Skipping incomplete function %s\n", $phpfunc->internalCallFunc);
                    continue;
                }
                $extGen->vgContextFunctions[] = $phpfunc;
            }

            // check for a doc override file
            $docOverridePath = GEN_PATH_DATA . '/fncdoc_override/vg/' . $phpfunc->name . '.md';
            if (file_exists($docOverridePath)) {
                $phpfunc->comment = file_get_contents($docOverridePath);

                @list($comm, $args) = explode('---', $phpfunc->comment, 2);

                $phpfunc->comment = trim($comm);
                 // parse @return from the comment
                if (preg_match('/@return\s+(.+)/', $args ?? '', $matches)) {
                    $phpfunc->returnComment = trim($matches[1]);
                    // remove the @return line from the comment
                    $args = preg_replace('/@return\s+.+/s', '', $args);
                }

                $args = "\n" . trim($args ?? '') . "\n";
                $args = array_filter(array_map('trim', explode("\n$", $args)));

                $mappedArgs = [];
                foreach($args as $argLine) {
                    // till the first space is the argument name
                    $argName = substr($argLine, 0, strpos($argLine, ' '));
                    $argDesc = trim(substr($argLine, strlen($argName)));

                    $mappedArgs[$argName] = $argDesc;
                }

                // now replace the argument comments
                foreach($phpfunc->arguments as $parg) {
                    if (isset($mappedArgs[$parg->name])) {
                        $parg->comment = $mappedArgs[$parg->name];
                    }
                }
            }
        }
    }
}
