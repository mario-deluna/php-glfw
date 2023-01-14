<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\CEObjectArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLReadPixelsAdjustment implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $func = new class('glReadPixels') extends ExtFunction 
        {    
            public function getFunctionCallCode() : string
            {
                $body = <<<EOD
if (Z_OBJCE_P(pixels_zval) == phpglfw_get_buffer_glubyte_ce()) {
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(pixels_zval));
    cvector_reserve(obj_ptr->vec, width * height * 4);
    glReadPixels(x, y, width, height, format, type, obj_ptr->vec);
    cvector_set_size(obj_ptr->vec, width * height * 4);
} else {
    zend_throw_error(NULL, "glReadPixels: Invalid or unsupported buffer object given.");
}
EOD;
                return $body;
            }
        };

        $func->arguments[] = ExtArgument::make('x', ExtType::T_LONG);
        $func->arguments[] = ExtArgument::make('y', ExtType::T_LONG);
        $func->arguments[] = ExtArgument::make('width', ExtType::T_LONG);
        $func->arguments[] = ExtArgument::make('height', ExtType::T_LONG);
        $func->arguments[] = ExtArgument::make('format', ExtType::T_LONG);
        $func->arguments[] = ExtArgument::make('type', ExtType::T_LONG);
        $bufferArg = new class('pixels', ExtType::T_CE) extends CEObjectArgument {
            public function getClassEntryPointer() : string {
                return 'phpglfw_get_buffer_interface_ce()';
            }

            public function getPHPClassName() : string {
                return "\\GL\\Buffer\\BufferInterface";
            }
        };
        $func->arguments[] = $bufferArg;

        $gen->replaceFunctionByName($func);
    }
}
