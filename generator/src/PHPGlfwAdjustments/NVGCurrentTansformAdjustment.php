<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\CEObjectArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class NVGCurrentTansformAdjustment implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $func = new class('currentTransform') extends ExtFunction 
        {    
            public function getFunctionCallCode() : string
            {
                return <<<EOD
                phpglfw_buffer_glfloat_object *buffer = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(buffer_zval));

                // ensure the proper size of the buffer
                cvector_reserve(buffer->vec, 6);
            
                // nvgCurrentTransform will copy the values into the float*
                nvgCurrentTransform(intern->nvgctx, buffer->vec);
                cvector_set_size(buffer->vec, 6);
                EOD;
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getVGContextFunctionByName('currentTransform');
        $func->copyFrom($baseFunc);

        $bufferArg = new class('buffer', ExtType::T_CE) extends CEObjectArgument {
            public function getClassEntryPointer() : string {
                return 'phpglfw_get_buffer_glfloat_ce()';
            }

            public function getPHPClassName() : string {
                return "\\GL\\Buffer\\FloatBuffer";
            }
        };

        $func->arguments[1] = $bufferArg;

        // force complete
        $func->incomplete = false;

        $gen->replaceVGContextFunctionByName($func);
    }
}
