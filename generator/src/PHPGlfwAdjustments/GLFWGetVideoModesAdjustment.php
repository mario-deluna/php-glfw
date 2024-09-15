<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\VariadicArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLFWGetVideoModesAdjustment implements AdjustmentInterface
{
    public function handle(ExtGenerator $gen) : void
    {
        /**
         * The function signiture as follows:
         * const GLFWvidmode * glfwGetVideoModes(GLFWmonitor *monitor, int *count)
         * 
         * This obviously doesn't work well in php so we create a PHP array and return an array of videomode objects
         */
        $func = new class('glfwGetVideoModes') extends ExtFunction 
        {    
            public function getFunctionImplementationBody() : string
            {
                return <<<EOD
                zval *monitor_zval;
                if (zend_parse_parameters(ZEND_NUM_ARGS(), "O", &monitor_zval, phpglfw_glfwmonitor_ce) == FAILURE) {
                    return;
                }
                GLFWmonitor* monitor = phpglfw_glfwmonitorptr_from_zval_ptr(monitor_zval);
                
                int count;
                const GLFWvidmode* modes = glfwGetVideoModes(monitor, &count);
                
                array_init(return_value);
                
                for (int i = 0; i < count; i++) {
                    zval mode_zval;
                    phpglfw_glfwvidmode_ptr_assign_to_zval_p(&mode_zval, &modes[i]);
                    add_next_index_zval(return_value, &mode_zval);
                }
                EOD;
            }
        };
        
        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName('glfwGetVideoModes');
        $func->copyFrom($baseFunc);
        unset($func->arguments[1]);
        
        $gen->replaceFunctionByName($func);
    }
}
