<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\CEObjectArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLTexImage2DAdjustment implements AdjustmentInterface
{
    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $func = new class('glTexImage2D') extends ExtFunction 
        {   
            public function getFunctionCallCode() : string
            {
                // yes i could have written this method less copy pasty but i decided i dont care.
                $body = <<<EOD
// if no data is given, we need to pass a null pointer 
// also the validation is skipped then
if (data_zval == NULL || Z_TYPE_P(data_zval) == IS_NULL) {
    glTexImage2D(target, level, internalformat, width, height, border, format, type, NULL);
    return;
}

// im still not 100% sure if we should do the validation here, 
// it will avoid some segfaults but I don't know if it's the best way to do it.
// on the other hand the performance impact of the validation is going to 
// so low compared to the other php shenanigans that it probably won't matter. 
size_t min_buffer_size;
int numofcom;
switch (format) {
    case GL_RED:
    case GL_RED_INTEGER:
    case GL_STENCIL_INDEX:
    case GL_DEPTH_COMPONENT:
    numofcom = 1;
    break;
    case GL_RG:
    case GL_RG_INTEGER:
    case GL_DEPTH_STENCIL:
    numofcom = 2;
    break;
    case GL_RGB:
    case GL_RGB_INTEGER:
    case GL_BGR:
    case GL_BGR_INTEGER:
    numofcom = 3;
    break;
    case GL_RGBA:
    case GL_RGBA_INTEGER:
    case GL_BGRA:
    case GL_BGRA_INTEGER:
    numofcom = 4;
    break;
    default:
        zend_throw_error(NULL, "glTexImage2D: invalid format, only GL_RED, GL_RG, GL_RGB, GL_BGR, GL_RGBA, GL_BGRA, GL_DEPTH_COMPONENT, GL_STENCIL_INDEX, GL_DEPTH_STENCIL, GL_RED_INTEGER, GL_RG_INTEGER, GL_RGB_INTEGER, GL_BGR_INTEGER, GL_RGBA_INTEGER, GL_BGRA_INTEGER are supported");
        return;
}
// min size is simply width * height * com
min_buffer_size = width * height * numofcom;
// check if the given pixel data type is valid and matches 
// the given buffer object
zend_class_entry *expected_ce;
switch (type) {
    case GL_BYTE:
    expected_ce = phpglfw_get_buffer_glbyte_ce();
    break;
    case GL_UNSIGNED_BYTE:
    case GL_UNSIGNED_BYTE_3_3_2:
    case GL_UNSIGNED_BYTE_2_3_3_REV:
    expected_ce = phpglfw_get_buffer_glubyte_ce();
    break;
    case GL_SHORT:
    expected_ce = phpglfw_get_buffer_glshort_ce();
    break;
    case GL_UNSIGNED_SHORT:
    case GL_UNSIGNED_SHORT_5_6_5:
    case GL_UNSIGNED_SHORT_5_6_5_REV:
    case GL_UNSIGNED_SHORT_4_4_4_4:
    case GL_UNSIGNED_SHORT_4_4_4_4_REV:
    case GL_UNSIGNED_SHORT_5_5_5_1:
    case GL_UNSIGNED_SHORT_1_5_5_5_REV:
    expected_ce = phpglfw_get_buffer_glushort_ce();
    break;
    case GL_INT:
    expected_ce = phpglfw_get_buffer_glint_ce();
    break;
    case GL_UNSIGNED_INT:
    case GL_UNSIGNED_INT_8_8_8_8:
    case GL_UNSIGNED_INT_8_8_8_8_REV:
    case GL_UNSIGNED_INT_10_10_10_2:
    case GL_UNSIGNED_INT_2_10_10_10_REV:
    expected_ce = phpglfw_get_buffer_gluint_ce();
    break;
    case GL_FLOAT:
    expected_ce = phpglfw_get_buffer_glfloat_ce();
    break;
    case GL_HALF_FLOAT:
    expected_ce = phpglfw_get_buffer_glhalf_ce();
    break;
}

if (Z_OBJCE_P(data_zval) == expected_ce) {
    
    // GLubyte
    if (expected_ce == phpglfw_get_buffer_glubyte_ce()) {
        phpglfw_buffer_glubyte_object *bufferobj = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
        if (cvector_size(bufferobj->vec) < min_buffer_size) {
            zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLubyte)");
            return;
        }
        glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
    }
    // GLbyte
    else if (expected_ce == phpglfw_get_buffer_glbyte_ce()) {
        phpglfw_buffer_glbyte_object *bufferobj = phpglfw_buffer_glbyte_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
        if (cvector_size(bufferobj->vec) < min_buffer_size) {
            zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLbyte)");
            return;
        }
        glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
    }
    // GLshort
    else if (expected_ce == phpglfw_get_buffer_glshort_ce()) {
        phpglfw_buffer_glshort_object *bufferobj = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
        if (cvector_size(bufferobj->vec) < min_buffer_size) {
            zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLshort)");
            return;
        }
        glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
    }
    // GLushort
    else if (expected_ce == phpglfw_get_buffer_glushort_ce()) {
        phpglfw_buffer_glushort_object *bufferobj = phpglfw_buffer_glushort_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
        if (cvector_size(bufferobj->vec) < min_buffer_size) {
            zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLushort)");
            return;
        }
        glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
    }
    // GLuint
    else if (expected_ce == phpglfw_get_buffer_gluint_ce()) {
        phpglfw_buffer_gluint_object *bufferobj = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
        if (cvector_size(bufferobj->vec) < min_buffer_size) {
            zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLuint)");
            return;
        }
        glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
    }
    // GLint
    else if (expected_ce == phpglfw_get_buffer_glint_ce()) {
        phpglfw_buffer_glint_object *bufferobj = phpglfw_buffer_glint_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
        if (cvector_size(bufferobj->vec) < min_buffer_size) {
            zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLint)");
            return;
        }
        glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
    }
    // GLfloat
    else if (expected_ce == phpglfw_get_buffer_glfloat_ce()) {
        phpglfw_buffer_glfloat_object *bufferobj = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
        if (cvector_size(bufferobj->vec) < min_buffer_size) {
            zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLfloat)");
            return;
        }
        glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
    }
    // GLhalf
    else if (expected_ce == phpglfw_get_buffer_glhalf_ce()) {
        phpglfw_buffer_glhalf_object *bufferobj = phpglfw_buffer_glhalf_objectptr_from_zobj_p(Z_OBJ_P(data_zval));
        if (cvector_size(bufferobj->vec) < min_buffer_size) {
            zend_throw_error(NULL, "glTexImage2D: The passed buffer is too small for the given width, height and format (GLhalf)");
            return;
        }
        glTexImage2D(target, level, internalformat, width, height, border, format, type, bufferobj->vec);
    }
    else {
        zend_throw_error(NULL, "glTexImage2D: How in the wold did you get here?");
        return;
    }
    
} else {
    zend_throw_error(NULL, "glTexImage2D: Invalid buffer object type given. Expected %s, got %s", ZSTR_VAL(expected_ce->name), ZSTR_VAL(Z_OBJCE_P(data_zval)->name));
};
EOD;
                return $body;
            }
        };

        // copy base function into our new one and replace it in the extension
        $baseFunc = $gen->getFunctionByName('glTexImage2D');
        $func->copyFrom($baseFunc);

        $func->arguments[8] = new class('data', ExtType::T_CE) extends CEObjectArgument {
            /**
             * The char used for parsing the arguments with the zend engine
             */
            public string $charid = 'O!';

            public function getClassEntryPointer() : string {
                return 'phpglfw_get_buffer_interface_ce()';
            }

            public function getPHPClassName() : string {
                return "?\\GL\\Buffer\\BufferInterface";
            }
        };

        // update the comment 
        $func->comment .= <<<EOD

        
Example:

```php
glGenTextures(1, \$texture);
glBindTexture(GL_TEXTURE_2D, \$texture);

// we just create a simple 2x2 texture with 4 channels
\$buffer = new GL\\Buffer\\UByteBuffer([
    255, 0, 0, 255,
    0, 255, 0, 255,
    0, 0, 255, 255,
    255, 255, 255, 255,
]);

glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, \$buffer);
```

@PHP-GLFW: for This function has been modified to accept a `BufferInterface` object instead of a pointer.

Also in this PHP OpenGL extension, the arguments are validated against the passed buffer object. If the buffer object is too small for the given width, height, and format an exception is thrown. This is done to prevent segfaults, this will unfortunately, make the function quite a bit slower. But as uploading textures is anyway a heavy operation the impact should not be noticeable in normal applications.
EOD;
        

        // force complete
        $func->incomplete = false;

        $gen->replaceFunctionByName($func);
    }
}
