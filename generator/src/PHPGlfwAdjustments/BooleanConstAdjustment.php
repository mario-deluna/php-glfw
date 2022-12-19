<?php 

namespace PHPGlfwAdjustments;

use ExtGenerator;

class BooleanConstAdjustment implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        foreach($gen->constants as $const) 
        {
            // hard replace the value of GL_TRUE and GL_FALSE to a boolean
            if ($const->name === 'GL_TRUE' || $const->name === 'GLFW_TRUE') {
                $const->isForwardDefinition = false;
                $const->definition = 'true';
                $const->definitionValueString = 'true';
            } else if ($const->name === 'GL_FALSE' || $const->name === 'GLFW_FALSE') {
                $const->isForwardDefinition = false;
                $const->definition = 'false';
                $const->definitionValueString = 'false';
            }
        }
        
    }
}
