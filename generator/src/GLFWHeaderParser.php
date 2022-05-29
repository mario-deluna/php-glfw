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
    ];

    private function createResourceDefinitions(ExtGenerator $extGen)
    {
        $extGen->resources[] = new ExtResource('GLFWwindow');
        $extGen->resources[] = new ExtResource('GLFWcursor');
    }

    public function process(string $headerFilePath, ExtGenerator $extGen)
    {
        // first create required resource definitions

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

            if (!isset($this->glfwTypeToExt[$funcReturnValue])) continue;

            if ($funcArgs !== 'void') continue;

            $phpfunc = new ExtFunction($funcName);
            $phpfunc->returnType = $this->glfwTypeToExt[$funcReturnValue];

            $extGen->methods[] = $phpfunc;

            // var_dump($funcReturnValue, $funcName, $funcArgs); die;
        }

        // var_dump($funcmatches); die;
    }
}
