<?php

class GLFWHeaderParser 
{
    public function process(string $headerFilePath, ExtGenerator $extGen)
    {
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
    }
}
