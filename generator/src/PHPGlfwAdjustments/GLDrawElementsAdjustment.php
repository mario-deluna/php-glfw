<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\CEObjectArgument;
use ExtFunction;
use ExtGenerator;
use ExtInternalPtrObject;
use ExtType;

class GLDrawElementsAdjustment implements AdjustmentInterface
{
    /**
     * Receives an instance of the extension generator before being built to 
     * make changes / adjustments for the extension to handle edge cases without 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $func = new class('glDrawElements') extends ExtFunction 
        {    
            public function getFunctionCallCode() : string
            {
                $body = <<<EOD
if (Z_TYPE_P(indices) == IS_LONG) {
    // indices is an offset (for use with element array buffer)
    glDrawElements(mode, count, type, (void*)(uintptr_t)Z_LVAL_P(indices));
} else if (Z_OBJCE_P(indices) == phpglfw_get_buffer_gluint_ce()) {
    // indices is a buffer object containing index data
    phpglfw_buffer_gluint_object *obj_ptr = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(indices));
    glDrawElements(mode, count, type, obj_ptr->vec);
} else if (Z_OBJCE_P(indices) == phpglfw_get_buffer_glushort_ce()) {
    // indices is a buffer object containing index data
    phpglfw_buffer_glushort_object *obj_ptr = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(indices));
    glDrawElements(mode, count, type, obj_ptr->vec);
} else if (Z_OBJCE_P(indices) == phpglfw_get_buffer_glubyte_ce()) {
    // indices is a buffer object containing index data
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(indices));
    glDrawElements(mode, count, type, obj_ptr->vec);
} else {
    zend_throw_error(NULL, "glDrawElements: Invalid indices argument. Must be an integer offset or a UIntBuffer, UShortBuffer, or UByteBuffer object.");
}
EOD;
                return $body;
            }

            public function getPHPStubArgument(ExtArgument $arg, bool $allowDefaultValue = true) : string
            {
                // custom indices argument
                if ($arg->name === 'indices') {
                    return 'int|\\GL\\Buffer\\UIntBuffer|\\GL\\Buffer\\UShortBuffer|\\GL\\Buffer\\UByteBuffer $' . $arg->name;
                }
                
                // forward
                return parent::getPHPStubArgument($arg, $allowDefaultValue);
            }
        };

        $func->comment = <<<EOD
render primitives from array data using element indices

Example: 
```php
// define vertices for a rectangle using two triangles
\$vertices = new GL\Buffer\FloatBuffer([
    // positions     // colors
    0.5,  0.5, 0.0,  1.0, 0.0, 0.0,  // top right
    0.5, -0.5, 0.0,  0.0, 1.0, 0.0,  // bottom right
   -0.5, -0.5, 0.0,  0.0, 0.0, 1.0,  // bottom left
   -0.5,  0.5, 0.0,  1.0, 1.0, 0.0   // top left 
]);

// define indices to form two triangles
\$indices = new GL\Buffer\UIntBuffer([
    0, 1, 3,  // first triangle
    1, 2, 3   // second triangle
]);

glGenVertexArrays(1, \$VAO);
glGenBuffers(1, \$VBO);
glGenBuffers(1, \$EBO);

glBindVertexArray(\$VAO);
glBindBuffer(GL_ARRAY_BUFFER, \$VBO);
glBufferData(GL_ARRAY_BUFFER, \$vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, \$EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, \$indices, GL_STATIC_DRAW);

// ... set up vertex attributes ...

// draw the rectangle using indices
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```

@PHP-GLFW: In the PHP extension this method supports both buffer objects and integer offsets.
When using an Element Array Buffer (bound to GL_ELEMENT_ARRAY_BUFFER), pass an integer offset.
When drawing without binding an element buffer, pass a UIntBuffer, UShortBuffer, or UByteBuffer containing the indices.
EOD;
        
        $func->arguments[] = ExtArgument::make('mode', ExtType::T_LONG);
        $func->arguments[] = ExtArgument::make('count', ExtType::T_LONG);
        $func->arguments[] = ExtArgument::make('type', ExtType::T_LONG);
        
        // create a custom argument that can accept both integer and buffer objects
        $indicesArg = new class('indices', ExtType::T_LONG) extends \ExtArgument {
            public string $charid = 'z';
            public string $variableDeclarationPrefix = 'zval *';
            
            public function getCharId() : string {
                return 'z' . ($this->isOptional() ? '!' : '');
            }
            
            public function getZendParameterParseArguments() : array {
                return ['&' . $this->getInternalVariable()];
            }
            
            public function getUsableVariable() : string {
                return $this->name;
            }
        };
        $func->arguments[] = $indicesArg;

        $func->arguments[0]->comment = 'Specifies what kind of primitives to render. Symbolic constants GL_POINTS, GL_LINE_STRIP, GL_LINE_LOOP, GL_LINES, GL_LINE_STRIP_ADJACENCY, GL_LINES_ADJACENCY, GL_TRIANGLE_STRIP, GL_TRIANGLE_FAN, GL_TRIANGLES, GL_TRIANGLE_STRIP_ADJACENCY, GL_TRIANGLES_ADJACENCY and GL_PATCHES are accepted.';
        $func->arguments[1]->comment = 'Specifies the number of elements to be rendered.';
        $func->arguments[2]->comment = 'Specifies the type of the values in indices. Must be one of GL_UNSIGNED_BYTE, GL_UNSIGNED_SHORT, or GL_UNSIGNED_INT.';
        $func->arguments[3]->comment = 'Specifies a buffer object containing the indices, or an offset into the currently bound element array buffer.';

        // force function to be complete and set return type
        $func->incomplete = false;
        $func->returnType = ExtType::T_VOID;

        // add the function
        $gen->addFunction($func);
    }
}