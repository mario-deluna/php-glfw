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

    private function createResourceDefinitions(ExtGenerator $extGen)
    {
        $extGen->addResource(new class('glfwwindow', 'GLFWwindow*') extends ExtResource {
            public function generateDestroy() : string {
                return "glfwDestroyWindow($this->name);";
            }
        });

        $extGen->addResource(new class('glfwcursor', 'GLFWcursor*') extends ExtResource {
            public function generateDestroy() : string {
                return "glfwDestroyCursor($this->name);";
            }
        });
    }

    public function process(string $headerFilePath, ExtGenerator $extGen)
    {
        // first create required resource definitions
        $this->createResourceDefinitions($extGen);

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
                preg_match("/^(const +)?([a-zA-Z]+ ?\*?) ?(.*)/", $arg, $match);
                $arg = array_combine(['full', 'const', 'type', 'name'], str_replace(' ', '', array_map('trim', $match)));
            } 

            // create func def
            $phpfunc = new ExtFunction($funcName);

            // add the arguments 
            foreach($funcArgs as $sourceArg) 
            {
                if (isset($this->glfwTypeToExt[$sourceArg['type']])) {
                    $phparg = ExtArgument::make($sourceArg['name'], $this->glfwTypeToExt[$sourceArg['type']]);
                    $phparg->argumentTypeFrom = $sourceArg['type'];
                    $phpfunc->arguments[] = $phparg;
                }
                elseif (isset($extGen->resources[$sourceArg['type']])) {
                    $res = $extGen->resources[$sourceArg['type']];
                    var_dump($res, $sourceArg); die;
                    $phparg = ExtArgument::make($sourceArg['name'], $this->glfwTypeToExt[$sourceArg['type']]);
                } else {
                    $isValid = false;
                }
            }

            // parse return argument
            preg_match("/^(const +)?([a-zA-Z]+ ?\*?)/", $funcReturnValue, $match);
            $funcReturnValue = array_combine(['full', 'const', 'type'], str_replace(' ', '', array_map('trim', $match)));

            if (isset($this->glfwTypeToExt[$funcReturnValue['type']])) {
                $phpfunc->returnType = $this->glfwTypeToExt[$funcReturnValue['type']];
                $phpfunc->returnTypeFrom = $funcReturnValue['type'];
            }
            elseif (isset($extGen->resources[$funcReturnValue['type']])) {
                $res = $extGen->resources[$funcReturnValue['type']];
                $phpfunc->returnType = ExtFunction::RETURN_RESOURCE;
                $phpfunc->returnTypeFrom = $res->type;
                $phpfunc->returnResource = $res;
            }
            else {
                $isValid = false;
            }

            if ($funcName === 'glfwCreateWindow') {
                // var_dump($fullSig, $phpfunc); die;
            }

            // add the function if still valid
            if ($isValid) $extGen->methods[] = $phpfunc;
        }

        // var_dump($funcmatches); die;
    }
}
