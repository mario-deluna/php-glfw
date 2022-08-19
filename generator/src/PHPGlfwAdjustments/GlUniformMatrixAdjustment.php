<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\CEObjectArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GlUniformMatrixAdjustment implements AdjustmentInterface
{
    private function createDirectUploadMatrixFunction(ExtGenerator $gen)
    {
        $func = new class('glUniformMatrix4f') extends ExtFunction 
        {   
            public function getFunctionCallCode() : string
            {
                $matarg = $this->arguments[2];
                $matargZval = $matarg->getZValName();
                $matargCe = $matarg->getClassEntryPointer();

                $body = <<<EOD
phpglfw_math_mat4_object *obj_ptr = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P({$matargZval}));
glUniformMatrix4fv(location, 1, transpose, &obj_ptr->data[0][0]);

EOD;
                return $body;
            }
        };

        $func->arguments[] = ExtArgument::make('location', ExtType::T_LONG);
        $func->arguments[] = ExtArgument::make('transpose', ExtType::T_BOOL);

        $func->arguments[] = new class('matrix', ExtType::T_CE) extends CEObjectArgument {
            public function getClassEntryPointer() : string {
                return 'phpglfw_get_math_mat4_ce()';
            }

            public function getPHPClassName() : string {
                return "\\GL\\Math\\Mat4";
            }
        };

        $func->comment = 'Sets a matrix (mat4x4) uniform value to the current shader program.';
        $func->comment .= PHP_EOL . PHP_EOL . '@PHP-GLFW: This method is specifc to the php extension and not part of the original OpenGL API.';

        $func->incomplete = false;
        $gen->replaceFunctionByName($func);
    }

    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $this->createDirectUploadMatrixFunction($gen);

//         $func = new class('glUniformMatrix4fv') extends ExtFunction 
//         {   
//             public function getFunctionCallCode() : string
//             {
//                 $body = <<<EOD
// if (Z_OBJCE_P(buffer_zval) == phpglfw_get_buffer_glfloat_ce()) {
//     phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(buffer_zval));
//     glUniformMatrix4fv(location, count, transpose, obj_ptr->vec);
// } else {
//     zend_throw_error(NULL, "glUniformMatrix4fv: Invalid or unsupported buffer object given.");
// }
// EOD;
//                 return $body;
//             }
//         };

//         // copy base function into our new one and replace it in the extension
//         $baseFunc = $gen->getFunctionByName('glUniformMatrix4fv');
//         $func->copyFrom($baseFunc);

//         $func->arguments[3] = new class('buffer', ExtType::T_CE) extends CEObjectArgument {
//             public function getClassEntryPointer() : string {
//                 return 'phpglfw_get_buffer_interface_ce()';
//             }

//             public function getPHPClassName() : string {
//                 return "\\GL\\Buffer\\BufferInterface";
//             }
//         };

//         // force complete
//         $func->incomplete = false;

//         $gen->replaceFunctionByName($func);
    }
}
