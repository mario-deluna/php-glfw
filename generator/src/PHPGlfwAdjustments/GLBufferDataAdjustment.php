<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\CEObjectArgument;
use ExtFunction;
use ExtGenerator;
use ExtInternalPtrObject;
use ExtType;

class GLBufferDataAdjustment implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $func = new class('glBufferData') extends ExtFunction 
        {    
            public function getFunctionCallCode() : string
            {
                $body = <<<EOD
if (Z_OBJCE_P(buffer_zval) == phpglfw_get_buffer_glfloat_ce()) {
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(buffer_zval));
    glBufferData(target, sizeof(GLfloat) * cvector_size(obj_ptr->vec), obj_ptr->vec, usage);
} else {
    zend_throw_error(NULL, "glBufferData: Invalid or unsupported buffer object given.");
}
EOD;
                return $body;
            }
        };

        $func->comment = <<<EOD
creates and initializes a buffer object's data store

@PHP-GLFW: In the PHP extension this method has different signiture compared to the original. 
Instead of passing byte size and a pointer to the function, in PHP you pass a `GL\\Buffer\\BufferInterface` instance.

Example: 
```php
\$buffer = new GL\Buffer\FloatBuffer([
    // positions     // colors
    0.5, -0.5, 0.0,  1.0, 0.0, 0.0,  // bottom right
   -0.5, -0.5, 0.0,  0.0, 1.0, 0.0,  // bottom let
    0.0,  0.5, 0.0,  0.0, 0.0, 1.0   // top 
]);

glGenVertexArrays(1, \$VAO);
glGenBuffers(1, \$VBO);
glBindVertexArray(\$VAO);
glBindBuffer(GL_ARRAY_BUFFER, \$VBO);
glBufferData(GL_ARRAY_BUFFER, \$buffer, GL_STATIC_DRAW);
```
EOD;
        $func->arguments[] = ExtArgument::make('target', ExtType::T_LONG);

        $bufferArg = new class('buffer', ExtType::T_CE) extends CEObjectArgument {
            public function getClassEntryPointer() : string {
                return 'phpglfw_get_buffer_interface_ce()';
            }

            public function getPHPClassName() : string {
                return "\\GL\\Buffer\\BufferInterface";
            }
        };

        $func->arguments[] = $bufferArg;
        $func->arguments[] = ExtArgument::make('usage', ExtType::T_LONG);

        $func->arguments[0]->comment = 'Specifies the target to which the buffer object is bound for glBufferData.';
        $func->arguments[1]->comment = 'Specifies a buffer object containing the to be uploaded data.';
        $func->arguments[2]->comment = 'Specifies the expected usage pattern of the data store. The symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY, GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW, GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.';

        $gen->replaceFunctionByName($func);
    }
}
