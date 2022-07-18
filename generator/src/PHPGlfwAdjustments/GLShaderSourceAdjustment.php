<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLShaderSourceAdjustment implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $func = new class('glShaderSource') extends ExtFunction 
        {    
            public function getFunctionCallCode() : string
            {
                $shaderArg = $this->arguments[0];
                $sourceArg = $this->arguments[1];

                return sprintf('glShaderSource(%s, 1, &%s, NULL);', $shaderArg->getUsableVariable(), $sourceArg->getUsableVariable());
            }
        };

        $func->comment = <<<EOD
Replaces the source code in a shader object.

PHP-GLFW: As with PHP I don't see a reason to split up the shader source to multiple addresses. 
This is why the function in PHP is simplyfied `glShaderSource(int \$shader, string \$soruce)`.

@param int \$shader Specifies the handle of the shader object whose source code is to be replaced.
@param string \$source Specifies a string containing the source code to be loaded into the shader.
EOD;
        $func->arguments[] = ExtArgument::make('shader', ExtType::T_LONG);
        $func->arguments[] = ExtArgument::make('source', ExtType::T_STRING);

        $gen->replaceFunctionByName($func);
    }
}
