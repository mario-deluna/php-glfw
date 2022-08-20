<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\CEObjectArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GlUniformMathObjAdjustment implements AdjustmentInterface
{
    private function createDirectUploadMatrixFunction(ExtGenerator $gen)
    {
        $func = new class('glUniformMatrix4f') extends ExtFunction 
        {   
            public function getFunctionCallCode() : string
            {
                $matarg = $this->arguments[2];
                $matargZval = $matarg->getZValName();

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

    private function createDirectUploadVec2Function(ExtGenerator $gen)
    {
        $func = new class('glUniformVec2f') extends ExtFunction 
        {   
            public function getFunctionCallCode() : string
            {
                $matarg = $this->arguments[1];
                $matargZval = $matarg->getZValName();

                $body = <<<EOD
phpglfw_math_vec2_object *obj_ptr = phpglfw_math_vec2_objectptr_from_zobj_p(Z_OBJ_P({$matargZval}));
glUniform2fv(location, 1, &obj_ptr->data[0]);

EOD;
                return $body;
            }
        };

        $func->arguments[] = ExtArgument::make('location', ExtType::T_LONG);
        $func->arguments[] = new class('vec', ExtType::T_CE) extends CEObjectArgument {
            public function getClassEntryPointer() : string {
                return 'phpglfw_get_math_vec2_ce()';
            }

            public function getPHPClassName() : string {
                return "\\GL\\Math\\Vec2";
            }
        };

        $func->comment = 'Sets a vector (vec2) uniform value to the current shader program.';
        $func->comment .= PHP_EOL . PHP_EOL . '@PHP-GLFW: This method is specifc to the php extension and not part of the original OpenGL API.';

        $func->incomplete = false;
        $gen->replaceFunctionByName($func);
    }


    private function createDirectUploadVec3Function(ExtGenerator $gen)
    {
        $func = new class('glUniformVec3f') extends ExtFunction 
        {   
            public function getFunctionCallCode() : string
            {
                $matarg = $this->arguments[1];
                $matargZval = $matarg->getZValName();

                $body = <<<EOD
phpglfw_math_vec3_object *obj_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P({$matargZval}));
glUniform3fv(location, 1, &obj_ptr->data[0]);

EOD;
                return $body;
            }
        };
        $func->arguments[] = ExtArgument::make('location', ExtType::T_LONG);
        $func->arguments[] = new class('vec', ExtType::T_CE) extends CEObjectArgument {
            public function getClassEntryPointer() : string {
                return 'phpglfw_get_math_vec3_ce()';
            }
            public function getPHPClassName() : string {
                return "\\GL\\Math\\Vec3";
            }
        };
        $func->comment = 'Sets a vector (vec3) uniform value to the current shader program.';
        $func->comment .= PHP_EOL . PHP_EOL . '@PHP-GLFW: This method is specifc to the php extension and not part of the original OpenGL API.';
        $func->incomplete = false;
        $gen->replaceFunctionByName($func);
    }

    private function createDirectUploadVec4Function(ExtGenerator $gen)
    {
        $func = new class('glUniformVec4f') extends ExtFunction 
        {   
            public function getFunctionCallCode() : string
            {
                $matarg = $this->arguments[1];
                $matargZval = $matarg->getZValName();
                $body = <<<EOD
phpglfw_math_vec4_object *obj_ptr = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P({$matargZval}));
glUniform4fv(location, 1, &obj_ptr->data[0]);

EOD;
                return $body;
            }
        };
        $func->arguments[] = ExtArgument::make('location', ExtType::T_LONG);
        $func->arguments[] = new class('vec', ExtType::T_CE) extends CEObjectArgument {
            public function getClassEntryPointer() : string {
                return 'phpglfw_get_math_vec4_ce()';
            }
            public function getPHPClassName() : string {
                return "\\GL\\Math\\Vec4";
            }
        };
        $func->comment = 'Sets a vector (vec4) uniform value to the current shader program.';
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
        $this->createDirectUploadVec2Function($gen);
        $this->createDirectUploadVec3Function($gen);
        $this->createDirectUploadVec4Function($gen);
    }
}
