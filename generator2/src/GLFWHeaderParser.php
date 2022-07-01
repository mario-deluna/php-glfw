<?php

class GLFWHeaderParser 
{
    private array $glfwTypeToExt = 
    [
        'void' => ExtType::T_VOID,
        'int' => ExtType::T_LONG,
        'long' => ExtType::T_LONG,
        'float' => ExtType::T_DOUBLE,
        'double' => ExtType::T_DOUBLE,
        'char*' => ExtType::T_STRING,
    ];

    private function createIPODefinitions(ExtGenerator $extGen)
    {
        $extGen->addIPO(new class('GLFWwindow', 'GLFWwindow*') extends ExtInternalPtrObject {
            public function getDestructionCall(string $var) : string {
                return "glfwDestroyWindow($var);";
            }
        });

        $extGen->addIPO(new class('GLFWmonitor', 'GLFWmonitor*') extends ExtInternalPtrObject {
            public function getDestructionCall(string $var) : string {
                return "";
            }
        });

        $extGen->addIPO(new class('GLFWcursor', 'GLFWcursor*') extends ExtInternalPtrObject {
            public function getDestructionCall(string $var) : string {
                return "glfwDestroyCursor($var);";
            }
        });
    }

    public function process(string $headerFilePath, ExtGenerator $extGen)
    {
        // first create required resource definitions
        $this->createIPODefinitions($extGen);

        // begin reading the header
        $headerContents = file_get_contents($headerFilePath);
        preg_match_all("/#define (GLFW_[A-Z_]+) +([A-Z0-9x_]+)/", $headerContents, $matches);

        // trim the names & values
        $matches[1] = array_map('trim', $matches[1]);
        $matches[2] = array_map('trim', $matches[2]);

        $foundConstants = array_combine($matches[1], $matches[2]);

        $group = new ExtConstantGroup();
        $group->name = "GLFW Constants";
        $group->desc = "Constants usally defined by the glfw3.h file.";

        foreach($foundConstants as $key => $value)
        {
            $const = new ExtConstant($key, $key, $value);
            $const->isForwardDefinition = true;
            $const->group = $group;
            $const->comment = '=> ' . $value;

            // if (is_numeric($value) || substr($value, 0, 2) === '0x') {
            //     $const->isForwardDefinition = false;
            // } else {
            //     $const->isForwardDefinition = true;
            // }
            
            $extGen->addConstant($const);
        }

        preg_match_all("/GLFWAPI (.*) (glfw.*)\((.*)?\)/", $headerContents, $funcmatches);

        foreach($funcmatches[0] as $k => $fullSig) 
        {
            $funcReturnValue = $funcmatches[1][$k];
            $funcName = $funcmatches[2][$k];
            $funcArgs = $funcmatches[3][$k];

            // flag that turns falls when we could not parse 
            // or convert the function properly
            $isValid = true;

            // split the args
            if ($funcArgs === 'void') {
                $funcArgs = [];
            } else {
                $funcArgs = array_map('trim', explode(',', $funcArgs));
            }

            // parse the arguments (const, type, pointer, name)
            foreach($funcArgs as &$arg) {
                preg_match("/^(const +)?([a-zA-Z]+ ?[\*+]?) ?(.*)/", $arg, $match);
                $arg = array_combine(['full', 'const', 'type', 'name'], str_replace(' ', '', array_map('trim', $match)));
            } 

            // create func def
            $phpfunc = new ExtFunction($funcName);

            // add the arguments 
            foreach($funcArgs as $sourceArg) 
            {
                preg_match("/([a-zA-Z0-9]+)[ +]?(\*+)?/", $sourceArg['type'], $pointerTypeArg);
                $rawArgType = $pointerTypeArg[1] ?? null;
                $argIsPointer = ($pointerTypeArg[2] ?? null) === '*';

                if (strpos($sourceArg['full'], '**') !== false) {
                    if (GEN_VERBOSE) printf("** Args currently not supported. (%s)\n", $sourceArg['full']);
                    $isValid = false;
                    break;
                }
                // if ($funcName === 'glfwGetError') {
                //     var_dump($sourceArg); die;
                // }

                // string workaround
                if ($rawArgType === 'char' && $sourceArg['type'] === 'char*') {
                    $rawArgType = 'char*';
                    $argIsPointer = false;
                }

                // scalar
                if (isset($this->glfwTypeToExt[$rawArgType]) && $rawArgType !== 'void') {
                    $phparg = ExtArgument::make($sourceArg['name'], $this->glfwTypeToExt[$rawArgType]);
                    $phparg->argumentTypeFrom = $sourceArg['type'];
                    $phparg->passedByReference = $argIsPointer;
                    $phpfunc->arguments[] = $phparg;
                }
                // IPO
                elseif (isset($extGen->IPOs[$sourceArg['type']])) {
                    $ipo = $extGen->IPOs[$sourceArg['type']];
                    $phparg = ExtArgument::make($sourceArg['name'], ExtType::T_IPO);
                    $phparg->argInternalPtrObject = $ipo;
                    $phpfunc->arguments[] = $phparg;
                }
                // unmapped
                else {
                    if (GEN_VERBOSE) printf("Argument type %s is not mapped.\n", $sourceArg['type']);
                    $isValid = false;
                }
            }

            // parse return argument
            preg_match("/^(const +)?([a-zA-Z]+ ?\*?\*?)/", $funcReturnValue, $match);
            $funcReturnValue = array_combine(['full', 'const', 'type'], str_replace(' ', '', array_map('trim', $match)));

            // we do not support pointer redirection yet..
            if (strpos($funcReturnValue['full'], '**') !== false) {
                if (GEN_VERBOSE) printf("** Return currently not supported. (%s)\n", $funcReturnValue['full']);
                $isValid = false;
            }

            // scalar type 
            if (isset($this->glfwTypeToExt[$funcReturnValue['type']])) {
                $phpfunc->returnType = $this->glfwTypeToExt[$funcReturnValue['type']];
                $phpfunc->returnTypeFrom = $funcReturnValue['type'];
            }

            // IPO
            elseif (isset($extGen->IPOs[$funcReturnValue['type']])) {
                $ipo = $extGen->IPOs[$funcReturnValue['type']];
                $phpfunc->returnType = ExtFunction::RETURN_IPO;
                $phpfunc->returnTypeFrom = $ipo->type;
                $phpfunc->returnIPO = $ipo;
            }
            // unmapped
            else {
                if (GEN_VERBOSE) printf("Return type '%s' is not wrappable.\n", $funcReturnValue['full']);
                $isValid = false;
            }

            // if ($funcName === 'glfwCreateWindow') {
            //     var_dump($fullSig, $phpfunc); die;
            // }

            // add the function if still valid
            if ($isValid) $extGen->methods[] = $phpfunc;
            else {
                if (GEN_VERBOSE) printf("Skipping function '%s', not wrappable.\n", $funcName);
            }
        }
        // var_dump($funcmatches); die;
    }
}
