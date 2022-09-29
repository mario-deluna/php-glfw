<?php 

namespace PHPGlfwAdjustments;

use ExtFunction;
use ExtGenerator;

class GLFWSwapBuffersAdjustment implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        /**
         * There is a BUG in GLFW under MacOS, as updating 
         * to the newest GLFW version did not work, i decided to include
         * the workaround directly in PHP-GLFW so that PHP users don't have 
         * to worry about it. https://github.com/glfw/glfw/issues/1334
         */
        $func = new class('glfwSwapBuffers') extends ExtFunction 
        {    
            public function getFunctionImplementationBody() : string
            {
                $b = parent::getFunctionImplementationBody() . PHP_EOL . PHP_EOL;

                $b .= <<<EOD
#ifdef __APPLE__
    static bool macMovedToFix1334 = false;
    if (!macMovedToFix1334) {
        int x, y;
        glfwGetWindowPos(window, &x, &y);
        glfwSetWindowPos(window, ++x, y);
        macMovedToFix1334 = true;
    }
#endif
EOD;
                return $b;
            }
        };
        
        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName('glfwSwapBuffers');
        $func->copyFrom($baseFunc);
        $gen->replaceFunctionByName($func);
    }
}
