<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtArgument\CEObjectArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLReadPixelsAdjustment implements AdjustmentInterface
{
    private function patchGlReadPixels(ExtGenerator $gen) : void
    {
        $func = new class('glReadPixels') extends ExtFunction 
        {    
            public function getFunctionCallCode() : string
            {
                $body = <<<EOD
uint32_t channels_count = 0;
switch (format) {
    case GL_RED:
    case GL_GREEN:
    case GL_BLUE:
    case GL_ALPHA:
    case GL_DEPTH_COMPONENT:
    case GL_STENCIL_INDEX:
        channels_count = 1;
        break;
    case GL_RG:
        channels_count = 2;
        break;
    case GL_RGB:
        channels_count = 3;
        break;
    case GL_RGBA:
        channels_count = 4;
        break;
    default:
        zend_throw_error(NULL, "glReadPixels: Invalid format given.");
        return;
}

if (Z_OBJCE_P(pixels_zval) == phpglfw_get_buffer_glubyte_ce()) {
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(pixels_zval));
    cvector_reserve(obj_ptr->vec, width * height * channels_count);
    glReadPixels(x, y, width, height, format, type, obj_ptr->vec);
    cvector_set_size(obj_ptr->vec, width * height * channels_count);
} else if (Z_OBJCE_P(pixels_zval) == phpglfw_get_buffer_glfloat_ce()) {
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(pixels_zval));
    cvector_reserve(obj_ptr->vec, width * height * channels_count);
    glReadPixels(x, y, width, height, format, type, obj_ptr->vec);
    cvector_set_size(obj_ptr->vec, width * height * channels_count);
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

    private function patchGlGetTexImage(ExtGenerator $gen) : void
    {
        $func = new class('glGetTexImage') extends ExtFunction 
        {    
            public function getFunctionCallCode() : string
            {
                $body = <<<EOD
uint32_t channels_count = 0;
switch (format) {
    case GL_RED:
    case GL_GREEN:
    case GL_BLUE:
    case GL_ALPHA:
    case GL_DEPTH_COMPONENT:
    case GL_STENCIL_INDEX:
        channels_count = 1;
        break;
    case GL_RG:
        channels_count = 2;
        break;
    case GL_RGB:
        channels_count = 3;
        break;
    case GL_RGBA:
        channels_count = 4;
        break;
    default:
        zend_throw_error(NULL, "glGetTexImage: Invalid format given.");
        return;
}

// fetch the width and height of the texture
GLint width, height;
glGetTexLevelParameteriv(target, level, GL_TEXTURE_WIDTH, &width);
glGetTexLevelParameteriv(target, level, GL_TEXTURE_HEIGHT, &height);

if (
    Z_OBJCE_P(pixels_zval) == phpglfw_get_buffer_glubyte_ce() && (
        type == GL_UNSIGNED_BYTE ||
        type == GL_UNSIGNED_BYTE_3_3_2 ||
        type == GL_UNSIGNED_BYTE_2_3_3_REV
    )) {
    phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(pixels_zval));
    cvector_reserve(obj_ptr->vec, width * height * channels_count);
    glGetTexImage(target, level, format, type, obj_ptr->vec);
    cvector_set_size(obj_ptr->vec, width * height * channels_count);
} else if (Z_OBJCE_P(pixels_zval) == phpglfw_get_buffer_glfloat_ce() && type == GL_FLOAT) {
    phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(pixels_zval));
    cvector_reserve(obj_ptr->vec, width * height * channels_count);
    glGetTexImage(target, level, format, type, obj_ptr->vec);
    cvector_set_size(obj_ptr->vec, width * height * channels_count);
} else {
    zend_throw_error(NULL, "glGetTexImage: Invalid or unsupported buffer object given and or data type given.");
}
EOD;
                return $body;
            }
        };

        $func->arguments[] = ExtArgument::make('target', ExtType::T_LONG);
        $func->arguments[] = ExtArgument::make('level', ExtType::T_LONG);
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

    /**
     * Recieves an instance of the extension generator before beeing built to 
     * make changes / adjustments for the extension to handle edge cases whithout 
     * adding a million ifs into the parser code.
     */
    public function handle(ExtGenerator $gen) : void
    {
        $this->patchGLReadPixels($gen);
        $this->patchGLGetTexImage($gen);
    }
}
