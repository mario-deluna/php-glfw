<?php 

namespace PHPGlfwAdjustments;

use ExtArgument\CEObjectArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class NVGTextBoundsAdjustment implements AdjustmentInterface
{
    private function fixTextBound(ExtGenerator $gen) : void
    {
        $func = new class('textBounds') extends ExtFunction 
        {    
            // public function getFunctionCallCode() : string
            // {
            //     return <<<EOD
            //     object_init_ex(return_value, phpglfw_math_vec4_ce);
            //     phpglfw_math_vec4_object *bounds = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));
            
            //     EOD;
            // }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getVGContextFunctionByName('textBounds');
        $func->copyFrom($baseFunc);

        // find the bounds argument index
        $boundsArgIndex = -1;
        foreach($func->arguments as $index => $arg) {
            if ($arg->name === 'bounds') {
                $boundsArgIndex = $index;
                break;
            }
        }

        // add min & max arguments
        $func->arguments[$boundsArgIndex] = new class('bounds', ExtType::T_CE) extends CEObjectArgument {
            public function getClassEntryPointer() : string {
                return 'phpglfw_get_math_vec4_ce()';
            }

            public function getPHPClassName() : string {
                return "\\GL\\Math\\Vec4";
            }

            public function getUsePrepCode() : string {
                return <<<EOD
                phpglfw_math_vec4_object *bounds = NULL;

                if ({$this->getZValName()} != NULL) {
                    ZVAL_DEREF({$this->getZValName()});

                    // if we got a var but its not an object, we create a new one
                    if (Z_TYPE_P({$this->getZValName()}) == IS_OBJECT && Z_OBJCE_P({$this->getZValName()}) == phpglfw_get_math_vec4_ce()) {
                        bounds = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P({$this->getZValName()}));
                    }
                    else {
                        object_init_ex({$this->getZValName()}, phpglfw_get_math_vec4_ce());
                        bounds = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P({$this->getZValName()}));
                    }
                }
                EOD;
            }

            public function getUsableVariable(): string
            {
                return 'bounds->data';
            }
        };
        $func->arguments[$boundsArgIndex]->defaultValue = 'NULL';
        $func->arguments[$boundsArgIndex]->explicitPassedByReference = true;

        // copy comment from base function
        $func->arguments[$boundsArgIndex]->comment = $baseFunc->arguments[$boundsArgIndex]->comment;

        // force complete
        $func->incomplete = false;

        $gen->replaceVGContextFunctionByName($func);
    }

    private function fixTextBoxBound(ExtGenerator $gen) : void
    {
        $func = new class('textBoxBounds') extends ExtFunction 
        {
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getVGContextFunctionByName('textBoxBounds');
        $func->copyFrom($baseFunc);

        // find the bounds argument index
        $boundsArgIndex = -1;
        foreach($func->arguments as $index => $arg) {
            if ($arg->name === 'bounds') {
                $boundsArgIndex = $index;
                break;
            }
        }


        // add min & max arguments
        $func->arguments[$boundsArgIndex] = new class('bounds', ExtType::T_CE) extends CEObjectArgument {
            public function getClassEntryPointer() : string {
                return 'phpglfw_get_math_vec4_ce()';
            }

            public function getPHPClassName() : string {
                return "\\GL\\Math\\Vec4";
            }

            public function getUsePrepCode() : string {
                return <<<EOD
                phpglfw_math_vec4_object *bounds = NULL;

                if ({$this->getZValName()} != NULL) {
                    ZVAL_DEREF({$this->getZValName()});

                    // if we got a var but its not an object, we create a new one
                    if (Z_TYPE_P({$this->getZValName()}) == IS_OBJECT && Z_OBJCE_P({$this->getZValName()}) == phpglfw_get_math_vec4_ce()) {
                        bounds = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P({$this->getZValName()}));
                    }
                    else {
                        object_init_ex({$this->getZValName()}, phpglfw_get_math_vec4_ce());
                        bounds = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P({$this->getZValName()}));
                    }
                }
                EOD;
            }

            public function getUsableVariable(): string
            {
                return 'bounds->data';
            }
        };
        $func->arguments[$boundsArgIndex]->defaultValue = 'NULL';
        $func->arguments[$boundsArgIndex]->explicitPassedByReference = true;

        // copy comment from base function
        $func->arguments[$boundsArgIndex]->comment = $baseFunc->arguments[$boundsArgIndex]->comment;

        // force complete
        $func->incomplete = false;

        $gen->replaceVGContextFunctionByName($func);
    }

    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $this->fixTextBound($gen);
        $this->fixTextBoxBound($gen);
    }
}
