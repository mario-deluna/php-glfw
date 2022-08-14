<?php 
namespace GL\Math 
{
 
    class Vec2 {
        public function __construct(?float $x = null, ?float $y = null) {}
        public function length() : float {}
        public function dot(Vec2 $right) : float {}
        public function distance(Vec2 $right) : float {}
        public function distance2(Vec2 $right) : float {}
        public function normalize() : Vec2 {}
        public function abs() : Vec2 {}
        public function __toString() : string {}
    }
 
    class Vec3 {
        public function __construct(?float $x = null, ?float $y = null, ?float $z = null) {}
        public function length() : float {}
        public function dot(Vec3 $right) : float {}
        public function distance(Vec3 $right) : float {}
        public function distance2(Vec3 $right) : float {}
        public function normalize() : Vec3 {}
        public function abs() : Vec3 {}
        public function __toString() : string {}
    }
 
    class Vec4 {
        public function __construct(?float $x = null, ?float $y = null, ?float $z = null, ?float $w = null) {}
        public function length() : float {}
        public function dot(Vec4 $right) : float {}
        public function distance(Vec4 $right) : float {}
        public function distance2(Vec4 $right) : float {}
        public function normalize() : Vec4 {}
        public function abs() : Vec4 {}
        public function __toString() : string {}
    }
 
    class Mat4 {
        public function __construct() {}
        public function length() : float {}
        public function dot(Mat4 $right) : float {}
        public function distance(Mat4 $right) : float {}
        public function distance2(Mat4 $right) : float {}
        public function normalize() : Mat4 {}
        public function abs() : Mat4 {}
        public function __toString() : string {}
    }
};

namespace GL\Buffer 
{   
    interface BufferInterface {
        public function __construct(?array $initalData = null);
        public function clear() : void;
        public function size() : int;
        public function capacity() : int;
        public function reserve(int $size) : void;
    }

    class FloatBuffer implements BufferInterface {

        /**
         * Constructs a new FloatBuffer, internally (GLfloat)
         * 
         * @param null|array<float> $intialData Inital data to be pushed into the buffer.
         */
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}

        /**
         * pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = 3.14`.
         *
         * @param float $value The value to be pushed into the buffer.
         *
         * @return void 
         */
        public function push(float $value) : void {}

        /**
         * Fills the buffer with $count amount of values. The second argument is the value that is filled in.
         *
         * @param int $count The number of elements to fill.
         * @param float $value The value that will be filled in.
         *
         * @return void 
         */
        public function fill(int $count, float $value) : void {}
        
        /**
         * Reserves the $size amount of space. Values are still undefined.
         *
         * @param int $size The number of elements to reserve space for.
         *
         * @return void 
         */
        public function reserve(int $size) : void {}

        /**
         * Will clear the Buffer, internally this will release all allocated data. Meaning any reserved space will be freed.
         *
         * @return void 
         */
        public function clear() : void {}

        /**
         * Returns the actual size / number of elements of the buffer.
         *
         * @return int buffer size in element count (not bytes)
         */
        public function size() : int {}

        /**
         * Returns the current reserved space of the buffer.
         *
         * @return int buffer space in element count (not bytes)
         */
        public function capacity() : int {}
    }

    class HFloatBuffer implements BufferInterface {

        /**
         * Constructs a new HFloatBuffer, internally (GLhalf)
         * 
         * @param null|array<float> $intialData Inital data to be pushed into the buffer.
         */
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}

        /**
         * pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = 3.14`.
         *
         * @param float $value The value to be pushed into the buffer.
         *
         * @return void 
         */
        public function push(float $value) : void {}

        /**
         * Fills the buffer with $count amount of values. The second argument is the value that is filled in.
         *
         * @param int $count The number of elements to fill.
         * @param float $value The value that will be filled in.
         *
         * @return void 
         */
        public function fill(int $count, float $value) : void {}
        
        /**
         * Reserves the $size amount of space. Values are still undefined.
         *
         * @param int $size The number of elements to reserve space for.
         *
         * @return void 
         */
        public function reserve(int $size) : void {}

        /**
         * Will clear the Buffer, internally this will release all allocated data. Meaning any reserved space will be freed.
         *
         * @return void 
         */
        public function clear() : void {}

        /**
         * Returns the actual size / number of elements of the buffer.
         *
         * @return int buffer size in element count (not bytes)
         */
        public function size() : int {}

        /**
         * Returns the current reserved space of the buffer.
         *
         * @return int buffer space in element count (not bytes)
         */
        public function capacity() : int {}
    }

    class DoubleBuffer implements BufferInterface {

        /**
         * Constructs a new DoubleBuffer, internally (GLdouble)
         * 
         * @param null|array<float> $intialData Inital data to be pushed into the buffer.
         */
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}

        /**
         * pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = 3.14`.
         *
         * @param float $value The value to be pushed into the buffer.
         *
         * @return void 
         */
        public function push(float $value) : void {}

        /**
         * Fills the buffer with $count amount of values. The second argument is the value that is filled in.
         *
         * @param int $count The number of elements to fill.
         * @param float $value The value that will be filled in.
         *
         * @return void 
         */
        public function fill(int $count, float $value) : void {}
        
        /**
         * Reserves the $size amount of space. Values are still undefined.
         *
         * @param int $size The number of elements to reserve space for.
         *
         * @return void 
         */
        public function reserve(int $size) : void {}

        /**
         * Will clear the Buffer, internally this will release all allocated data. Meaning any reserved space will be freed.
         *
         * @return void 
         */
        public function clear() : void {}

        /**
         * Returns the actual size / number of elements of the buffer.
         *
         * @return int buffer size in element count (not bytes)
         */
        public function size() : int {}

        /**
         * Returns the current reserved space of the buffer.
         *
         * @return int buffer space in element count (not bytes)
         */
        public function capacity() : int {}
    }

    class IntBuffer implements BufferInterface {

        /**
         * Constructs a new IntBuffer, internally (GLint)
         * 
         * @param null|array<int> $intialData Inital data to be pushed into the buffer.
         */
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}

        /**
         * pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = 123`.
         *
         * @param int $value The value to be pushed into the buffer.
         *
         * @return void 
         */
        public function push(int $value) : void {}

        /**
         * Fills the buffer with $count amount of values. The second argument is the value that is filled in.
         *
         * @param int $count The number of elements to fill.
         * @param int $value The value that will be filled in.
         *
         * @return void 
         */
        public function fill(int $count, int $value) : void {}
        
        /**
         * Reserves the $size amount of space. Values are still undefined.
         *
         * @param int $size The number of elements to reserve space for.
         *
         * @return void 
         */
        public function reserve(int $size) : void {}

        /**
         * Will clear the Buffer, internally this will release all allocated data. Meaning any reserved space will be freed.
         *
         * @return void 
         */
        public function clear() : void {}

        /**
         * Returns the actual size / number of elements of the buffer.
         *
         * @return int buffer size in element count (not bytes)
         */
        public function size() : int {}

        /**
         * Returns the current reserved space of the buffer.
         *
         * @return int buffer space in element count (not bytes)
         */
        public function capacity() : int {}
    }

    class UIntBuffer implements BufferInterface {

        /**
         * Constructs a new UIntBuffer, internally (GLuint)
         * 
         * @param null|array<int> $intialData Inital data to be pushed into the buffer.
         */
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}

        /**
         * pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = 123`.
         *
         * @param int $value The value to be pushed into the buffer.
         *
         * @return void 
         */
        public function push(int $value) : void {}

        /**
         * Fills the buffer with $count amount of values. The second argument is the value that is filled in.
         *
         * @param int $count The number of elements to fill.
         * @param int $value The value that will be filled in.
         *
         * @return void 
         */
        public function fill(int $count, int $value) : void {}
        
        /**
         * Reserves the $size amount of space. Values are still undefined.
         *
         * @param int $size The number of elements to reserve space for.
         *
         * @return void 
         */
        public function reserve(int $size) : void {}

        /**
         * Will clear the Buffer, internally this will release all allocated data. Meaning any reserved space will be freed.
         *
         * @return void 
         */
        public function clear() : void {}

        /**
         * Returns the actual size / number of elements of the buffer.
         *
         * @return int buffer size in element count (not bytes)
         */
        public function size() : int {}

        /**
         * Returns the current reserved space of the buffer.
         *
         * @return int buffer space in element count (not bytes)
         */
        public function capacity() : int {}
    }

    class ShortBuffer implements BufferInterface {

        /**
         * Constructs a new ShortBuffer, internally (GLshort)
         * 
         * @param null|array<int> $intialData Inital data to be pushed into the buffer.
         */
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}

        /**
         * pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = 123`.
         *
         * @param int $value The value to be pushed into the buffer.
         *
         * @return void 
         */
        public function push(int $value) : void {}

        /**
         * Fills the buffer with $count amount of values. The second argument is the value that is filled in.
         *
         * @param int $count The number of elements to fill.
         * @param int $value The value that will be filled in.
         *
         * @return void 
         */
        public function fill(int $count, int $value) : void {}
        
        /**
         * Reserves the $size amount of space. Values are still undefined.
         *
         * @param int $size The number of elements to reserve space for.
         *
         * @return void 
         */
        public function reserve(int $size) : void {}

        /**
         * Will clear the Buffer, internally this will release all allocated data. Meaning any reserved space will be freed.
         *
         * @return void 
         */
        public function clear() : void {}

        /**
         * Returns the actual size / number of elements of the buffer.
         *
         * @return int buffer size in element count (not bytes)
         */
        public function size() : int {}

        /**
         * Returns the current reserved space of the buffer.
         *
         * @return int buffer space in element count (not bytes)
         */
        public function capacity() : int {}
    }

    class UShortBuffer implements BufferInterface {

        /**
         * Constructs a new UShortBuffer, internally (GLushort)
         * 
         * @param null|array<int> $intialData Inital data to be pushed into the buffer.
         */
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}

        /**
         * pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = 123`.
         *
         * @param int $value The value to be pushed into the buffer.
         *
         * @return void 
         */
        public function push(int $value) : void {}

        /**
         * Fills the buffer with $count amount of values. The second argument is the value that is filled in.
         *
         * @param int $count The number of elements to fill.
         * @param int $value The value that will be filled in.
         *
         * @return void 
         */
        public function fill(int $count, int $value) : void {}
        
        /**
         * Reserves the $size amount of space. Values are still undefined.
         *
         * @param int $size The number of elements to reserve space for.
         *
         * @return void 
         */
        public function reserve(int $size) : void {}

        /**
         * Will clear the Buffer, internally this will release all allocated data. Meaning any reserved space will be freed.
         *
         * @return void 
         */
        public function clear() : void {}

        /**
         * Returns the actual size / number of elements of the buffer.
         *
         * @return int buffer size in element count (not bytes)
         */
        public function size() : int {}

        /**
         * Returns the current reserved space of the buffer.
         *
         * @return int buffer space in element count (not bytes)
         */
        public function capacity() : int {}
    }

    class ByteBuffer implements BufferInterface {

        /**
         * Constructs a new ByteBuffer, internally (GLbyte)
         * 
         * @param null|array<int> $intialData Inital data to be pushed into the buffer.
         */
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}

        /**
         * pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = 123`.
         *
         * @param int $value The value to be pushed into the buffer.
         *
         * @return void 
         */
        public function push(int $value) : void {}

        /**
         * Fills the buffer with $count amount of values. The second argument is the value that is filled in.
         *
         * @param int $count The number of elements to fill.
         * @param int $value The value that will be filled in.
         *
         * @return void 
         */
        public function fill(int $count, int $value) : void {}
        
        /**
         * Reserves the $size amount of space. Values are still undefined.
         *
         * @param int $size The number of elements to reserve space for.
         *
         * @return void 
         */
        public function reserve(int $size) : void {}

        /**
         * Will clear the Buffer, internally this will release all allocated data. Meaning any reserved space will be freed.
         *
         * @return void 
         */
        public function clear() : void {}

        /**
         * Returns the actual size / number of elements of the buffer.
         *
         * @return int buffer size in element count (not bytes)
         */
        public function size() : int {}

        /**
         * Returns the current reserved space of the buffer.
         *
         * @return int buffer space in element count (not bytes)
         */
        public function capacity() : int {}
    }

    class UByteBuffer implements BufferInterface {

        /**
         * Constructs a new UByteBuffer, internally (GLubyte)
         * 
         * @param null|array<int> $intialData Inital data to be pushed into the buffer.
         */
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}

        /**
         * pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = 123`.
         *
         * @param int $value The value to be pushed into the buffer.
         *
         * @return void 
         */
        public function push(int $value) : void {}

        /**
         * Fills the buffer with $count amount of values. The second argument is the value that is filled in.
         *
         * @param int $count The number of elements to fill.
         * @param int $value The value that will be filled in.
         *
         * @return void 
         */
        public function fill(int $count, int $value) : void {}
        
        /**
         * Reserves the $size amount of space. Values are still undefined.
         *
         * @param int $size The number of elements to reserve space for.
         *
         * @return void 
         */
        public function reserve(int $size) : void {}

        /**
         * Will clear the Buffer, internally this will release all allocated data. Meaning any reserved space will be freed.
         *
         * @return void 
         */
        public function clear() : void {}

        /**
         * Returns the actual size / number of elements of the buffer.
         *
         * @return int buffer size in element count (not bytes)
         */
        public function size() : int {}

        /**
         * Returns the current reserved space of the buffer.
         *
         * @return int buffer space in element count (not bytes)
         */
        public function capacity() : int {}
    }
};

namespace {
    /**
     * Functions
     * ----------------------------------------------------------------------------
     */
    /**
     * specify whether front- or back-facing facets can be culled
     * 
     * @param int $mode Specifies whether front- or back-facing facets are
     * candidates for culling. Symbolic constants <constant>GL_FRONT</constant>,
     * <constant>GL_BACK</constant>, and <constant>GL_FRONT_AND_BACK</constant> are
     * accepted. The initial value is <constant>GL_BACK</constant>.
     */ 
    function glCullFace(int $mode) : void {};
 
    /**
     * define front- and back-facing polygons
     * 
     * @param int $mode Specifies the orientation of front-facing polygons.
     * <constant>GL_CW</constant> and <constant>GL_CCW</constant> are accepted. The
     * initial value is <constant>GL_CCW</constant>.
     */ 
    function glFrontFace(int $mode) : void {};
 
    /**
     * specify implementation-specific hints
     * 
     * @param int $target Specifies a symbolic constant indicating the behavior to
     * be controlled. <constant>GL_LINE_SMOOTH_HINT</constant>,
     * <constant>GL_POLYGON_SMOOTH_HINT</constant>,
     * <constant>GL_TEXTURE_COMPRESSION_HINT</constant>, and
     * <constant>GL_FRAGMENT_SHADER_DERIVATIVE_HINT</constant> are accepted.
     * @param int $mode Specifies a symbolic constant indicating the desired
     * behavior. <constant>GL_FASTEST</constant>, <constant>GL_NICEST</constant>,
     * and <constant>GL_DONT_CARE</constant> are accepted.
     */ 
    function glHint(int $target, int $mode) : void {};
 
    /**
     * specify the width of rasterized lines
     * 
     * @param float $width Specifies the width of rasterized lines. The initial
     * value is 1.
     */ 
    function glLineWidth(float $width) : void {};
 
    /**
     * specify the diameter of rasterized points
     * 
     * @param float $size Specifies the diameter of rasterized points. The initial
     * value is 1.
     */ 
    function glPointSize(float $size) : void {};
 
    /**
     * select a polygon rasterization mode
     * 
     * @param int $face Specifies the polygons that mode applies to. Must be
     * <constant>GL_FRONT_AND_BACK</constant> for front- and back-facing polygons.
     * @param int $mode Specifies how polygons will be rasterized. Accepted values
     * are <constant>GL_POINT</constant>, <constant>GL_LINE</constant>, and
     * <constant>GL_FILL</constant>. The initial value is
     * <constant>GL_FILL</constant> for both front- and back-facing polygons.
     */ 
    function glPolygonMode(int $face, int $mode) : void {};
 
    /**
     * define the scissor box
     * 
     * @param int $x Specify the lower left corner of the scissor box. Initially (0,
     * 0).
     * @param int $y 
     * @param int $width Specify the width and height of the scissor box. When a GL
     * context is first attached to a window, width and height are set to the
     * dimensions of that window.
     * @param int $height
     */ 
    function glScissor(int $x, int $y, int $width, int $height) : void {};
 
    /**
     * glTexParameterf
     * 
     * @param int $target 
     * @param int $pname 
     * @param float $param
     */ 
    function glTexParameterf(int $target, int $pname, float $param) : void {};
 
    /**
     * glTexParameterfv
     * 
     * @param int $target 
     * @param int $pname 
     * @param \GL\Buffer\FloatBuffer|array $params
     */ 
    function glTexParameterfv(int $target, int $pname, \GL\Buffer\FloatBuffer|array $params) : void {};
 
    /**
     * glTexParameteri
     * 
     * @param int $target 
     * @param int $pname 
     * @param int $param
     */ 
    function glTexParameteri(int $target, int $pname, int $param) : void {};
 
    /**
     * glTexParameteriv
     * 
     * @param int $target 
     * @param int $pname 
     * @param \GL\Buffer\IntBuffer|array $params
     */ 
    function glTexParameteriv(int $target, int $pname, \GL\Buffer\IntBuffer|array $params) : void {};
 
    /**
     * specify a two-dimensional texture image
     * 
     * @param int $target Specifies the target texture. Must be
     * <constant>GL_TEXTURE_2D</constant>, <constant>GL_PROXY_TEXTURE_2D</constant>,
     * <constant>GL_TEXTURE_1D_ARRAY</constant>,
     * <constant>GL_PROXY_TEXTURE_1D_ARRAY</constant>,
     * <constant>GL_TEXTURE_RECTANGLE</constant>,
     * <constant>GL_PROXY_TEXTURE_RECTANGLE</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_POSITIVE_X</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_NEGATIVE_X</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_POSITIVE_Y</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_NEGATIVE_Y</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_POSITIVE_Z</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_NEGATIVE_Z</constant>, or
     * <constant>GL_PROXY_TEXTURE_CUBE_MAP</constant>.
     * @param int $level Specifies the level-of-detail number. Level 0 is the base
     * image level. Level n is the nth mipmap reduction image. If target is
     * <constant>GL_TEXTURE_RECTANGLE</constant> or
     * <constant>GL_PROXY_TEXTURE_RECTANGLE</constant>, level must be 0.
     * @param int $internalformat Specifies the number of color components in the
     * texture. Must be one of base internal formats given in Table 1, one of the
     * sized internal formats given in Table 2, or one of the compressed internal
     * formats given in Table 3, below.
     * @param int $width Specifies the width of the texture image. All
     * implementations support texture images that are at least 1024 texels wide.
     * @param int $height Specifies the height of the texture image, or the number
     * of layers in a texture array, in the case of the
     * <constant>GL_TEXTURE_1D_ARRAY</constant> and
     * <constant>GL_PROXY_TEXTURE_1D_ARRAY</constant> targets. All implementations
     * support 2D texture images that are at least 1024 texels high, and texture
     * arrays that are at least 256 layers deep.
     * @param int $border This value must be 0.
     * @param int $format Specifies the format of the pixel data. The following
     * symbolic values are accepted: <constant>GL_RED</constant>,
     * <constant>GL_RG</constant>, <constant>GL_RGB</constant>,
     * <constant>GL_BGR</constant>, <constant>GL_RGBA</constant>,
     * <constant>GL_BGRA</constant>, <constant>GL_RED_INTEGER</constant>,
     * <constant>GL_RG_INTEGER</constant>, <constant>GL_RGB_INTEGER</constant>,
     * <constant>GL_BGR_INTEGER</constant>, <constant>GL_RGBA_INTEGER</constant>,
     * <constant>GL_BGRA_INTEGER</constant>, <constant>GL_STENCIL_INDEX</constant>,
     * <constant>GL_DEPTH_COMPONENT</constant>,
     * <constant>GL_DEPTH_STENCIL</constant>.
     * @param int $type Specifies the data type of the pixel data. The following
     * symbolic values are accepted: <constant>GL_UNSIGNED_BYTE</constant>,
     * <constant>GL_BYTE</constant>, <constant>GL_UNSIGNED_SHORT</constant>,
     * <constant>GL_SHORT</constant>, <constant>GL_UNSIGNED_INT</constant>,
     * <constant>GL_INT</constant>, <constant>GL_HALF_FLOAT</constant>,
     * <constant>GL_FLOAT</constant>, <constant>GL_UNSIGNED_BYTE_3_3_2</constant>,
     * <constant>GL_UNSIGNED_BYTE_2_3_3_REV</constant>,
     * <constant>GL_UNSIGNED_SHORT_5_6_5</constant>,
     * <constant>GL_UNSIGNED_SHORT_5_6_5_REV</constant>,
     * <constant>GL_UNSIGNED_SHORT_4_4_4_4</constant>,
     * <constant>GL_UNSIGNED_SHORT_4_4_4_4_REV</constant>,
     * <constant>GL_UNSIGNED_SHORT_5_5_5_1</constant>,
     * <constant>GL_UNSIGNED_SHORT_1_5_5_5_REV</constant>,
     * <constant>GL_UNSIGNED_INT_8_8_8_8</constant>,
     * <constant>GL_UNSIGNED_INT_8_8_8_8_REV</constant>,
     * <constant>GL_UNSIGNED_INT_10_10_10_2</constant>, and
     * <constant>GL_UNSIGNED_INT_2_10_10_10_REV</constant>.
     * @param \GL\Buffer\BufferInterface $data
     */ 
    function glTexImage2D(int $target, int $level, int $internalformat, int $width, int $height, int $border, int $format, int $type, \GL\Buffer\BufferInterface $data) : void {};
 
    /**
     * specify which color buffers are to be drawn into
     * 
     * @param int $buf For default framebuffer, the argument specifies up to four
     * color buffers to be drawn into. Symbolic constants
     * <constant>GL_NONE</constant>, <constant>GL_FRONT_LEFT</constant>,
     * <constant>GL_FRONT_RIGHT</constant>, <constant>GL_BACK_LEFT</constant>,
     * <constant>GL_BACK_RIGHT</constant>, <constant>GL_FRONT</constant>,
     * <constant>GL_BACK</constant>, <constant>GL_LEFT</constant>,
     * <constant>GL_RIGHT</constant>, and <constant>GL_FRONT_AND_BACK</constant> are
     * accepted. The initial value is <constant>GL_FRONT</constant> for
     * single-buffered contexts, and <constant>GL_BACK</constant> for
     * double-buffered contexts. For framebuffer objects,
     * <constant>GL_COLOR_ATTACHMENT$m$</constant> and <constant>GL_NONE</constant>
     * enums are accepted, where <constant>$m$</constant> is a value between 0 and
     * <constant>GL_MAX_COLOR_ATTACHMENTS</constant>.
     */ 
    function glDrawBuffer(int $buf) : void {};
 
    /**
     * clear buffers to preset values
     * 
     * @param int $mask Bitwise OR of masks that indicate the buffers to be cleared.
     * The three masks are <constant>GL_COLOR_BUFFER_BIT</constant>,
     * <constant>GL_DEPTH_BUFFER_BIT</constant>, and
     * <constant>GL_STENCIL_BUFFER_BIT</constant>.
     */ 
    function glClear(int $mask) : void {};
 
    /**
     * specify clear values for the color buffers
     * 
     * @param float $red Specify the red, green, blue, and alpha values used when
     * the color buffers are cleared. The initial values are all 0.
     * @param float $green 
     * @param float $blue 
     * @param float $alpha
     */ 
    function glClearColor(float $red, float $green, float $blue, float $alpha) : void {};
 
    /**
     * specify the clear value for the stencil buffer
     * 
     * @param int $s Specifies the index used when the stencil buffer is cleared.
     * The initial value is 0.
     */ 
    function glClearStencil(int $s) : void {};
 
    /**
     * specify the clear value for the depth buffer
     * 
     * @param float $depth Specifies the depth value used when the depth buffer is
     * cleared. The initial value is 1.
     */ 
    function glClearDepth(float $depth) : void {};
 
    /**
     * control the front and back writing of individual bits in the stencil planes
     * 
     * @param int $mask Specifies a bit mask to enable and disable writing of
     * individual bits in the stencil planes. Initially, the mask is all 1's.
     */ 
    function glStencilMask(int $mask) : void {};
 
    /**
     * enable and disable writing of frame buffer color components
     * 
     * @param bool $red Specify whether red, green, blue, and alpha are to be
     * written into the frame buffer. The initial values are all
     * <constant>GL_TRUE</constant>, indicating that the color components are
     * written.
     * @param bool $green 
     * @param bool $blue 
     * @param bool $alpha
     */ 
    function glColorMask(bool $red, bool $green, bool $blue, bool $alpha) : void {};
 
    /**
     * enable or disable writing into the depth buffer
     * 
     * @param bool $flag Specifies whether the depth buffer is enabled for writing.
     * If flag is <constant>GL_FALSE</constant>, depth buffer writing is disabled.
     * Otherwise, it is enabled. Initially, depth buffer writing is enabled.
     */ 
    function glDepthMask(bool $flag) : void {};
 
    /**
     * glDisable
     * 
     * @param int $cap
     */ 
    function glDisable(int $cap) : void {};
 
    /**
     * enable or disable server-side GL capabilities
     * 
     * @param int $cap Specifies a symbolic constant indicating a GL capability.
     */ 
    function glEnable(int $cap) : void {};
 
    /**
     * block until all GL execution is complete
     */ 
    function glFinish() : void {};
 
    /**
     * force execution of GL commands in finite time
     */ 
    function glFlush() : void {};
 
    /**
     * specify pixel arithmetic
     * 
     * @param int $sfactor Specifies how the red, green, blue, and alpha source
     * blending factors are computed. The initial value is
     * <constant>GL_ONE</constant>.
     * @param int $dfactor Specifies how the red, green, blue, and alpha destination
     * blending factors are computed. The following symbolic constants are accepted:
     * <constant>GL_ZERO</constant>, <constant>GL_ONE</constant>,
     * <constant>GL_SRC_COLOR</constant>,
     * <constant>GL_ONE_MINUS_SRC_COLOR</constant>,
     * <constant>GL_DST_COLOR</constant>,
     * <constant>GL_ONE_MINUS_DST_COLOR</constant>,
     * <constant>GL_SRC_ALPHA</constant>,
     * <constant>GL_ONE_MINUS_SRC_ALPHA</constant>,
     * <constant>GL_DST_ALPHA</constant>,
     * <constant>GL_ONE_MINUS_DST_ALPHA</constant>.
     * <constant>GL_CONSTANT_COLOR</constant>,
     * <constant>GL_ONE_MINUS_CONSTANT_COLOR</constant>,
     * <constant>GL_CONSTANT_ALPHA</constant>, and
     * <constant>GL_ONE_MINUS_CONSTANT_ALPHA</constant>. The initial value is
     * <constant>GL_ZERO</constant>.
     */ 
    function glBlendFunc(int $sfactor, int $dfactor) : void {};
 
    /**
     * specify a logical pixel operation for rendering
     * 
     * @param int $opcode Specifies a symbolic constant that selects a logical
     * operation. The following symbols are accepted: <constant>GL_CLEAR</constant>,
     * <constant>GL_SET</constant>, <constant>GL_COPY</constant>,
     * <constant>GL_COPY_INVERTED</constant>, <constant>GL_NOOP</constant>,
     * <constant>GL_INVERT</constant>, <constant>GL_AND</constant>,
     * <constant>GL_NAND</constant>, <constant>GL_OR</constant>,
     * <constant>GL_NOR</constant>, <constant>GL_XOR</constant>,
     * <constant>GL_EQUIV</constant>, <constant>GL_AND_REVERSE</constant>,
     * <constant>GL_AND_INVERTED</constant>, <constant>GL_OR_REVERSE</constant>, and
     * <constant>GL_OR_INVERTED</constant>. The initial value is
     * <constant>GL_COPY</constant>.
     */ 
    function glLogicOp(int $opcode) : void {};
 
    /**
     * set front and back function and reference value for stencil testing
     * 
     * @param int $func Specifies the test function. Eight symbolic constants are
     * valid: <constant>GL_NEVER</constant>, <constant>GL_LESS</constant>,
     * <constant>GL_LEQUAL</constant>, <constant>GL_GREATER</constant>,
     * <constant>GL_GEQUAL</constant>, <constant>GL_EQUAL</constant>,
     * <constant>GL_NOTEQUAL</constant>, and <constant>GL_ALWAYS</constant>. The
     * initial value is <constant>GL_ALWAYS</constant>.
     * @param int $ref Specifies the reference value for the stencil test. ref is
     * clamped to the range    0  2 n  - 1   , where n is the number of bitplanes in
     * the stencil buffer. The initial value is 0.
     * @param int $mask Specifies a mask that is ANDed with both the reference value
     * and the stored stencil value when the test is done. The initial value is all
     * 1's.
     */ 
    function glStencilFunc(int $func, int $ref, int $mask) : void {};
 
    /**
     * set front and back stencil test actions
     * 
     * @param int $fail 
     * @param int $zfail 
     * @param int $zpass
     */ 
    function glStencilOp(int $fail, int $zfail, int $zpass) : void {};
 
    /**
     * specify the value used for depth buffer comparisons
     * 
     * @param int $func Specifies the depth comparison function. Symbolic constants
     * <constant>GL_NEVER</constant>, <constant>GL_LESS</constant>,
     * <constant>GL_EQUAL</constant>, <constant>GL_LEQUAL</constant>,
     * <constant>GL_GREATER</constant>, <constant>GL_NOTEQUAL</constant>,
     * <constant>GL_GEQUAL</constant>, and <constant>GL_ALWAYS</constant> are
     * accepted. The initial value is <constant>GL_LESS</constant>.
     */ 
    function glDepthFunc(int $func) : void {};
 
    /**
     * glPixelStoref
     * 
     * @param int $pname 
     * @param float $param
     */ 
    function glPixelStoref(int $pname, float $param) : void {};
 
    /**
     * glPixelStorei
     * 
     * @param int $pname 
     * @param int $param
     */ 
    function glPixelStorei(int $pname, int $param) : void {};
 
    /**
     * select a color buffer source for pixels
     * 
     * @param int $src
     */ 
    function glReadBuffer(int $src) : void {};
 
    /**
     * glGetBooleanv
     * 
     * @param int $pname 
     * @param ?bool &...$data
     */ 
    function glGetBooleanv(int $pname, ?bool &...$data) : void {};
 
    /**
     * glGetDoublev
     * 
     * @param int $pname 
     * @param ?bool &...$data
     */ 
    function glGetDoublev(int $pname, ?bool &...$data) : void {};
 
    /**
     * return error information
     */ 
    function glGetError() : int {};
 
    /**
     * glGetFloatv
     * 
     * @param int $pname 
     * @param ?bool &...$data
     */ 
    function glGetFloatv(int $pname, ?bool &...$data) : void {};
 
    /**
     * glGetIntegerv
     * 
     * @param int $pname 
     * @param ?bool &...$data
     */ 
    function glGetIntegerv(int $pname, ?bool &...$data) : void {};
 
    /**
     * return a string describing the current GL connection
     * 
     * @param int $name Specifies a symbolic constant, one of
     * <constant>GL_VENDOR</constant>, <constant>GL_RENDERER</constant>,
     * <constant>GL_VERSION</constant>, or
     * <constant>GL_SHADING_LANGUAGE_VERSION</constant>. Additionally, glGetStringi
     * accepts the <constant>GL_EXTENSIONS</constant> token.
     */ 
    function glGetString(int $name) : string {};
 
    /**
     * glGetTexParameterfv
     * 
     * @param int $target 
     * @param int $pname 
     * @param ?bool &...$params
     */ 
    function glGetTexParameterfv(int $target, int $pname, ?bool &...$params) : void {};
 
    /**
     * glGetTexParameteriv
     * 
     * @param int $target 
     * @param int $pname 
     * @param ?bool &...$params
     */ 
    function glGetTexParameteriv(int $target, int $pname, ?bool &...$params) : void {};
 
    /**
     * glGetTexLevelParameterfv
     * 
     * @param int $target 
     * @param int $level 
     * @param int $pname 
     * @param float &$params
     */ 
    function glGetTexLevelParameterfv(int $target, int $level, int $pname, float &$params) : void {};
 
    /**
     * glGetTexLevelParameteriv
     * 
     * @param int $target 
     * @param int $level 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetTexLevelParameteriv(int $target, int $level, int $pname, int &$params) : void {};
 
    /**
     * test whether a capability is enabled
     * 
     * @param int $cap Specifies a symbolic constant indicating a GL capability.
     */ 
    function glIsEnabled(int $cap) : bool {};
 
    /**
     * specify mapping of depth values from normalized device coordinates to window
     * coordinates
     * 
     * @param float $n 
     * @param float $f
     */ 
    function glDepthRange(float $n, float $f) : void {};
 
    /**
     * set the viewport
     * 
     * @param int $x Specify the lower left corner of the viewport rectangle, in
     * pixels. The initial value is (0,0).
     * @param int $y 
     * @param int $width Specify the width and height of the viewport. When a GL
     * context is first attached to a window, width and height are set to the
     * dimensions of that window.
     * @param int $height
     */ 
    function glViewport(int $x, int $y, int $width, int $height) : void {};
 
    /**
     * render primitives from array data
     * 
     * @param int $mode Specifies what kind of primitives to render. Symbolic
     * constants <constant>GL_POINTS</constant>, <constant>GL_LINE_STRIP</constant>,
     * <constant>GL_LINE_LOOP</constant>, <constant>GL_LINES</constant>,
     * <constant>GL_LINE_STRIP_ADJACENCY</constant>,
     * <constant>GL_LINES_ADJACENCY</constant>,
     * <constant>GL_TRIANGLE_STRIP</constant>, <constant>GL_TRIANGLE_FAN</constant>,
     * <constant>GL_TRIANGLES</constant>,
     * <constant>GL_TRIANGLE_STRIP_ADJACENCY</constant>,
     * <constant>GL_TRIANGLES_ADJACENCY</constant> and
     * <constant>GL_PATCHES</constant> are accepted.
     * @param int $first Specifies the starting index in the enabled arrays.
     * @param int $count Specifies the number of indices to be rendered.
     */ 
    function glDrawArrays(int $mode, int $first, int $count) : void {};
 
    /**
     * set the scale and units used to calculate depth values
     * 
     * @param float $factor Specifies a scale factor that is used to create a
     * variable depth offset for each polygon. The initial value is 0.
     * @param float $units Is multiplied by an implementation-specific value to
     * create a constant depth offset. The initial value is 0.
     */ 
    function glPolygonOffset(float $factor, float $units) : void {};
 
    /**
     * copy pixels into a 1D texture image
     * 
     * @param int $target Specifies the target texture. Must be
     * <constant>GL_TEXTURE_1D</constant>.
     * @param int $level Specifies the level-of-detail number. Level 0 is the base
     * image level. Level n is the nth mipmap reduction image.
     * @param int $internalformat Specifies the internal format of the texture. Must
     * be one of the following symbolic constants:
     * <constant>GL_COMPRESSED_RED</constant>,
     * <constant>GL_COMPRESSED_RG</constant>,
     * <constant>GL_COMPRESSED_RGB</constant>,
     * <constant>GL_COMPRESSED_RGBA</constant>.
     * <constant>GL_COMPRESSED_SRGB</constant>,
     * <constant>GL_COMPRESSED_SRGB_ALPHA</constant>.
     * <constant>GL_DEPTH_COMPONENT</constant>,
     * <constant>GL_DEPTH_COMPONENT16</constant>,
     * <constant>GL_DEPTH_COMPONENT24</constant>,
     * <constant>GL_DEPTH_COMPONENT32</constant>,
     * <constant>GL_STENCIL_INDEX8</constant>, <constant>GL_RED</constant>,
     * <constant>GL_RG</constant>, <constant>GL_RGB</constant>,
     * <constant>GL_R3_G3_B2</constant>, <constant>GL_RGB4</constant>,
     * <constant>GL_RGB5</constant>, <constant>GL_RGB8</constant>,
     * <constant>GL_RGB10</constant>, <constant>GL_RGB12</constant>,
     * <constant>GL_RGB16</constant>, <constant>GL_RGBA</constant>,
     * <constant>GL_RGBA2</constant>, <constant>GL_RGBA4</constant>,
     * <constant>GL_RGB5_A1</constant>, <constant>GL_RGBA8</constant>,
     * <constant>GL_RGB10_A2</constant>, <constant>GL_RGBA12</constant>,
     * <constant>GL_RGBA16</constant>, <constant>GL_SRGB</constant>,
     * <constant>GL_SRGB8</constant>, <constant>GL_SRGB_ALPHA</constant>, or
     * <constant>GL_SRGB8_ALPHA8</constant>.
     * @param int $x Specify the window coordinates of the left corner of the row of
     * pixels to be copied.
     * @param int $y 
     * @param int $width Specifies the width of the texture image. The height of the
     * texture image is 1.
     * @param int $border Must be 0.
     */ 
    function glCopyTexImage1D(int $target, int $level, int $internalformat, int $x, int $y, int $width, int $border) : void {};
 
    /**
     * copy pixels into a 2D texture image
     * 
     * @param int $target Specifies the target texture. Must be
     * <constant>GL_TEXTURE_2D</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_POSITIVE_X</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_NEGATIVE_X</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_POSITIVE_Y</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_NEGATIVE_Y</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_POSITIVE_Z</constant>, or
     * <constant>GL_TEXTURE_CUBE_MAP_NEGATIVE_Z</constant>.
     * @param int $level Specifies the level-of-detail number. Level 0 is the base
     * image level. Level n is the nth mipmap reduction image.
     * @param int $internalformat Specifies the internal format of the texture. Must
     * be one of the following symbolic constants:
     * <constant>GL_COMPRESSED_RED</constant>,
     * <constant>GL_COMPRESSED_RG</constant>,
     * <constant>GL_COMPRESSED_RGB</constant>,
     * <constant>GL_COMPRESSED_RGBA</constant>.
     * <constant>GL_COMPRESSED_SRGB</constant>,
     * <constant>GL_COMPRESSED_SRGB_ALPHA</constant>.
     * <constant>GL_DEPTH_COMPONENT</constant>,
     * <constant>GL_DEPTH_COMPONENT16</constant>,
     * <constant>GL_DEPTH_COMPONENT24</constant>,
     * <constant>GL_DEPTH_COMPONENT32</constant>,
     * <constant>GL_STENCIL_INDEX8</constant>, <constant>GL_RED</constant>,
     * <constant>GL_RG</constant>, <constant>GL_RGB</constant>,
     * <constant>GL_R3_G3_B2</constant>, <constant>GL_RGB4</constant>,
     * <constant>GL_RGB5</constant>, <constant>GL_RGB8</constant>,
     * <constant>GL_RGB10</constant>, <constant>GL_RGB12</constant>,
     * <constant>GL_RGB16</constant>, <constant>GL_RGBA</constant>,
     * <constant>GL_RGBA2</constant>, <constant>GL_RGBA4</constant>,
     * <constant>GL_RGB5_A1</constant>, <constant>GL_RGBA8</constant>,
     * <constant>GL_RGB10_A2</constant>, <constant>GL_RGBA12</constant>,
     * <constant>GL_RGBA16</constant>, <constant>GL_SRGB</constant>,
     * <constant>GL_SRGB8</constant>, <constant>GL_SRGB_ALPHA</constant>, or
     * <constant>GL_SRGB8_ALPHA8</constant>.
     * @param int $x Specify the window coordinates of the lower left corner of the
     * rectangular region of pixels to be copied.
     * @param int $y 
     * @param int $width Specifies the width of the texture image.
     * @param int $height Specifies the height of the texture image.
     * @param int $border Must be 0.
     */ 
    function glCopyTexImage2D(int $target, int $level, int $internalformat, int $x, int $y, int $width, int $height, int $border) : void {};
 
    /**
     * copy a one-dimensional texture subimage
     * 
     * @param int $target Specifies the target to which the texture object is bound
     * for glCopyTexSubImage1D function. Must be <constant>GL_TEXTURE_1D</constant>.
     * @param int $level Specifies the level-of-detail number. Level 0 is the base
     * image level. Level n is the nth mipmap reduction image.
     * @param int $xoffset Specifies the texel offset within the texture array.
     * @param int $x Specify the window coordinates of the left corner of the row of
     * pixels to be copied.
     * @param int $y 
     * @param int $width Specifies the width of the texture subimage.
     */ 
    function glCopyTexSubImage1D(int $target, int $level, int $xoffset, int $x, int $y, int $width) : void {};
 
    /**
     * copy a two-dimensional texture subimage
     * 
     * @param int $target Specifies the target to which the texture object is bound
     * for glCopyTexSubImage2D function. Must be
     * <constant>GL_TEXTURE_1D_ARRAY</constant>, <constant>GL_TEXTURE_2D</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_POSITIVE_X</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_NEGATIVE_X</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_POSITIVE_Y</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_NEGATIVE_Y</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_POSITIVE_Z</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_NEGATIVE_Z</constant>, or
     * <constant>GL_TEXTURE_RECTANGLE</constant>.
     * @param int $level Specifies the level-of-detail number. Level 0 is the base
     * image level. Level n is the nth mipmap reduction image.
     * @param int $xoffset Specifies a texel offset in the x direction within the
     * texture array.
     * @param int $yoffset Specifies a texel offset in the y direction within the
     * texture array.
     * @param int $x Specify the window coordinates of the lower left corner of the
     * rectangular region of pixels to be copied.
     * @param int $y 
     * @param int $width Specifies the width of the texture subimage.
     * @param int $height Specifies the height of the texture subimage.
     */ 
    function glCopyTexSubImage2D(int $target, int $level, int $xoffset, int $yoffset, int $x, int $y, int $width, int $height) : void {};
 
    /**
     * bind a named texture to a texturing target
     * 
     * @param int $target Specifies the target to which the texture is bound. Must
     * be one of <constant>GL_TEXTURE_1D</constant>,
     * <constant>GL_TEXTURE_2D</constant>, <constant>GL_TEXTURE_3D</constant>,
     * <constant>GL_TEXTURE_1D_ARRAY</constant>,
     * <constant>GL_TEXTURE_2D_ARRAY</constant>,
     * <constant>GL_TEXTURE_RECTANGLE</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP_ARRAY</constant>,
     * <constant>GL_TEXTURE_BUFFER</constant>,
     * <constant>GL_TEXTURE_2D_MULTISAMPLE</constant> or
     * <constant>GL_TEXTURE_2D_MULTISAMPLE_ARRAY</constant>.
     * @param int $texture Specifies the name of a texture.
     */ 
    function glBindTexture(int $target, int $texture) : void {};
 
    /**
     * delete named textures
     * 
     * @param int $n Specifies the number of textures to be deleted.
     * @param ?int ...$textures
     */ 
    function glDeleteTextures(int $n, ?int ...$textures) : void {};
 
    /**
     * generate texture names
     * 
     * @param int $n Specifies the number of texture names to be generated.
     * @param ?int &...$textures
     */ 
    function glGenTextures(int $n, ?int &...$textures) : void {};
 
    /**
     * determine if a name corresponds to a texture
     * 
     * @param int $texture Specifies a value that may be the name of a texture.
     */ 
    function glIsTexture(int $texture) : bool {};
 
    /**
     * copy a three-dimensional texture subimage
     * 
     * @param int $target Specifies the target to which the texture object is bound
     * for glCopyTexSubImage3D function. Must be <constant>GL_TEXTURE_3D</constant>,
     * <constant>GL_TEXTURE_2D_ARRAY</constant> or
     * <constant>GL_TEXTURE_CUBE_MAP_ARRAY</constant>.
     * @param int $level Specifies the level-of-detail number. Level 0 is the base
     * image level. Level n is the nth mipmap reduction image.
     * @param int $xoffset Specifies a texel offset in the x direction within the
     * texture array.
     * @param int $yoffset Specifies a texel offset in the y direction within the
     * texture array.
     * @param int $zoffset Specifies a texel offset in the z direction within the
     * texture array.
     * @param int $x Specify the window coordinates of the lower left corner of the
     * rectangular region of pixels to be copied.
     * @param int $y 
     * @param int $width Specifies the width of the texture subimage.
     * @param int $height Specifies the height of the texture subimage.
     */ 
    function glCopyTexSubImage3D(int $target, int $level, int $xoffset, int $yoffset, int $zoffset, int $x, int $y, int $width, int $height) : void {};
 
    /**
     * select active texture unit
     * 
     * @param int $texture Specifies which texture unit to make active. The number
     * of texture units is implementation dependent, but must be at least 80.
     * texture must be one of <constant>GL_TEXTURE</constant>i, where i ranges from
     * zero to the value of <constant>GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS</constant>
     * minus one. The initial value is <constant>GL_TEXTURE0</constant>.
     */ 
    function glActiveTexture(int $texture) : void {};
 
    /**
     * specify multisample coverage parameters
     * 
     * @param float $value Specify a single floating-point sample coverage value. 
     * The value is clamped to the range    0 1  . The initial value is 1.0.
     * @param bool $invert Specify a single boolean value representing if the
     * coverage masks should be inverted.  <constant>GL_TRUE</constant> and
     * <constant>GL_FALSE</constant> are accepted.  The initial value is
     * <constant>GL_FALSE</constant>.
     */ 
    function glSampleCoverage(float $value, bool $invert) : void {};
 
    /**
     * specify pixel arithmetic for RGB and alpha components separately
     * 
     * @param int $sfactorRGB 
     * @param int $dfactorRGB 
     * @param int $sfactorAlpha 
     * @param int $dfactorAlpha
     */ 
    function glBlendFuncSeparate(int $sfactorRGB, int $dfactorRGB, int $sfactorAlpha, int $dfactorAlpha) : void {};
 
    /**
     * glPointParameterf
     * 
     * @param int $pname 
     * @param float $param
     */ 
    function glPointParameterf(int $pname, float $param) : void {};
 
    /**
     * glPointParameterfv
     * 
     * @param int $pname 
     * @param \GL\Buffer\FloatBuffer|array $params
     */ 
    function glPointParameterfv(int $pname, \GL\Buffer\FloatBuffer|array $params) : void {};
 
    /**
     * glPointParameteri
     * 
     * @param int $pname 
     * @param int $param
     */ 
    function glPointParameteri(int $pname, int $param) : void {};
 
    /**
     * glPointParameteriv
     * 
     * @param int $pname 
     * @param \GL\Buffer\IntBuffer|array $params
     */ 
    function glPointParameteriv(int $pname, \GL\Buffer\IntBuffer|array $params) : void {};
 
    /**
     * set the blend color
     * 
     * @param float $red specify the components of
     * <constant>GL_BLEND_COLOR</constant>
     * @param float $green 
     * @param float $blue 
     * @param float $alpha
     */ 
    function glBlendColor(float $red, float $green, float $blue, float $alpha) : void {};
 
    /**
     * specify the equation used for both the RGB blend equation and the Alpha blend
     * equation
     * 
     * @param int $mode specifies how source and destination colors are combined. It
     * must be <constant>GL_FUNC_ADD</constant>,
     * <constant>GL_FUNC_SUBTRACT</constant>,
     * <constant>GL_FUNC_REVERSE_SUBTRACT</constant>, <constant>GL_MIN</constant>,
     * <constant>GL_MAX</constant>.
     */ 
    function glBlendEquation(int $mode) : void {};
 
    /**
     * generate query object names
     * 
     * @param int $n Specifies the number of query object names to be generated.
     * @param ?int &...$ids
     */ 
    function glGenQueries(int $n, ?int &...$ids) : void {};
 
    /**
     * delete named query objects
     * 
     * @param int $n Specifies the number of query objects to be deleted.
     * @param ?int ...$ids
     */ 
    function glDeleteQueries(int $n, ?int ...$ids) : void {};
 
    /**
     * determine if a name corresponds to a query object
     * 
     * @param int $id Specifies a value that may be the name of a query object.
     */ 
    function glIsQuery(int $id) : bool {};
 
    /**
     * delimit the boundaries of a query object
     * 
     * @param int $target Specifies the target type of query object established
     * between glBeginQuery and the subsequent  glEndQuery. The symbolic constant
     * must be one of <constant>GL_SAMPLES_PASSED</constant>,
     * <constant>GL_ANY_SAMPLES_PASSED</constant>,
     * <constant>GL_ANY_SAMPLES_PASSED_CONSERVATIVE</constant>,
     * <constant>GL_PRIMITIVES_GENERATED</constant>,
     * <constant>GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN</constant>, or
     * <constant>GL_TIME_ELAPSED</constant>.
     * @param int $id Specifies the name of a query object.
     */ 
    function glBeginQuery(int $target, int $id) : void {};
 
    /**
     * glEndQuery
     * 
     * @param int $target
     */ 
    function glEndQuery(int $target) : void {};
 
    /**
     * return parameters of a query object target
     * 
     * @param int $target Specifies a query object target. Must be
     * <constant>GL_SAMPLES_PASSED</constant>,
     * <constant>GL_ANY_SAMPLES_PASSED</constant>,
     * <constant>GL_ANY_SAMPLES_PASSED_CONSERVATIVE</constant>
     * <constant>GL_PRIMITIVES_GENERATED</constant>,
     * <constant>GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN</constant>,
     * <constant>GL_TIME_ELAPSED</constant>, or <constant>GL_TIMESTAMP</constant>.
     * @param int $pname Specifies the symbolic name of a query object target
     * parameter. Accepted values are <constant>GL_CURRENT_QUERY</constant> or
     * <constant>GL_QUERY_COUNTER_BITS</constant>.
     * @param int &$params Returns the requested data.
     */ 
    function glGetQueryiv(int $target, int $pname, int &$params) : void {};
 
    /**
     * glGetQueryObjectiv
     * 
     * @param int $id 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetQueryObjectiv(int $id, int $pname, int &$params) : void {};
 
    /**
     * glGetQueryObjectuiv
     * 
     * @param int $id 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetQueryObjectuiv(int $id, int $pname, int &$params) : void {};
 
    /**
     * bind a named buffer object
     * 
     * @param int $target Specifies the target to which the buffer object is bound,
     * which must be one of the buffer binding targets in the following table:
     * @param int $buffer Specifies the name of a buffer object.
     */ 
    function glBindBuffer(int $target, int $buffer) : void {};
 
    /**
     * delete named buffer objects
     * 
     * @param int $n Specifies the number of buffer objects to be deleted.
     * @param ?int ...$buffers
     */ 
    function glDeleteBuffers(int $n, ?int ...$buffers) : void {};
 
    /**
     * generate buffer object names
     * 
     * @param int $n Specifies the number of buffer object names to be generated.
     * @param ?int &...$buffers
     */ 
    function glGenBuffers(int $n, ?int &...$buffers) : void {};
 
    /**
     * determine if a name corresponds to a buffer object
     * 
     * @param int $buffer Specifies a value that may be the name of a buffer object.
     */ 
    function glIsBuffer(int $buffer) : bool {};
 
    /**
     * release the mapping of a buffer object's data store into the client's address
     * space
     * 
     * @param int $target Specifies the target to which the buffer object is bound
     * for glUnmapBuffer, which must be one of the buffer binding targets in the
     * following table:
     */ 
    function glUnmapBuffer(int $target) : bool {};
 
    /**
     * return parameters of a buffer object
     * 
     * @param int $target Specifies the target to which the buffer object is bound
     * for glGetBufferParameteriv and glGetBufferParameteri64v. Must be one of the
     * buffer binding targets in the following table:
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetBufferParameteriv(int $target, int $pname, int &$params) : void {};
 
    /**
     * set the RGB blend equation and the alpha blend equation separately
     * 
     * @param int $modeRGB specifies the RGB blend equation, how the red, green, and
     * blue components of the source and destination colors are combined. It must be
     * <constant>GL_FUNC_ADD</constant>, <constant>GL_FUNC_SUBTRACT</constant>,
     * <constant>GL_FUNC_REVERSE_SUBTRACT</constant>, <constant>GL_MIN</constant>,
     * <constant>GL_MAX</constant>.
     * @param int $modeAlpha specifies the alpha blend equation, how the alpha
     * component of the source and destination colors are combined. It must be
     * <constant>GL_FUNC_ADD</constant>, <constant>GL_FUNC_SUBTRACT</constant>,
     * <constant>GL_FUNC_REVERSE_SUBTRACT</constant>, <constant>GL_MIN</constant>,
     * <constant>GL_MAX</constant>.
     */ 
    function glBlendEquationSeparate(int $modeRGB, int $modeAlpha) : void {};
 
    /**
     * set front and/or back stencil test actions
     * 
     * @param int $face Specifies whether front and/or back stencil state is
     * updated. Three symbolic constants are valid: <constant>GL_FRONT</constant>,
     * <constant>GL_BACK</constant>, and <constant>GL_FRONT_AND_BACK</constant>.
     * @param int $sfail Specifies the action to take when the stencil test fails.
     * Eight symbolic constants are accepted: <constant>GL_KEEP</constant>,
     * <constant>GL_ZERO</constant>, <constant>GL_REPLACE</constant>,
     * <constant>GL_INCR</constant>, <constant>GL_INCR_WRAP</constant>,
     * <constant>GL_DECR</constant>, <constant>GL_DECR_WRAP</constant>, and
     * <constant>GL_INVERT</constant>. The initial value is
     * <constant>GL_KEEP</constant>.
     * @param int $dpfail Specifies the stencil action when the stencil test passes,
     * but the depth test fails. dpfail accepts the same symbolic constants as
     * sfail. The initial value is <constant>GL_KEEP</constant>.
     * @param int $dppass Specifies the stencil action when both the stencil test
     * and the depth test pass, or when the stencil test passes and either there is
     * no depth buffer or depth testing is not enabled. dppass accepts the same
     * symbolic constants as sfail. The initial value is
     * <constant>GL_KEEP</constant>.
     */ 
    function glStencilOpSeparate(int $face, int $sfail, int $dpfail, int $dppass) : void {};
 
    /**
     * set front and/or back function and reference value for stencil testing
     * 
     * @param int $face Specifies whether front and/or back stencil state is
     * updated. Three symbolic constants are valid: <constant>GL_FRONT</constant>,
     * <constant>GL_BACK</constant>, and <constant>GL_FRONT_AND_BACK</constant>.
     * @param int $func Specifies the test function. Eight symbolic constants are
     * valid: <constant>GL_NEVER</constant>, <constant>GL_LESS</constant>,
     * <constant>GL_LEQUAL</constant>, <constant>GL_GREATER</constant>,
     * <constant>GL_GEQUAL</constant>, <constant>GL_EQUAL</constant>,
     * <constant>GL_NOTEQUAL</constant>, and <constant>GL_ALWAYS</constant>. The
     * initial value is <constant>GL_ALWAYS</constant>.
     * @param int $ref Specifies the reference value for the stencil test. ref is
     * clamped to the range    0  2 n  - 1   , where n is the number of bitplanes in
     * the stencil buffer. The initial value is 0.
     * @param int $mask Specifies a mask that is ANDed with both the reference value
     * and the stored stencil value when the test is done. The initial value is all
     * 1's.
     */ 
    function glStencilFuncSeparate(int $face, int $func, int $ref, int $mask) : void {};
 
    /**
     * control the front and/or back writing of individual bits in the stencil
     * planes
     * 
     * @param int $face Specifies whether the front and/or back stencil writemask is
     * updated. Three symbolic constants are valid: <constant>GL_FRONT</constant>,
     * <constant>GL_BACK</constant>, and <constant>GL_FRONT_AND_BACK</constant>.
     * @param int $mask Specifies a bit mask to enable and disable writing of
     * individual bits in the stencil planes. Initially, the mask is all 1's.
     */ 
    function glStencilMaskSeparate(int $face, int $mask) : void {};
 
    /**
     * Attaches a shader object to a program object
     * 
     * @param int $program Specifies the program object to which a shader object
     * will be attached.
     * @param int $shader Specifies the shader object that is to be attached.
     */ 
    function glAttachShader(int $program, int $shader) : void {};
 
    /**
     * Associates a generic vertex attribute index with a named attribute variable
     * 
     * @param int $program Specifies the handle of the program object in which the
     * association is to be made.
     * @param int $index Specifies the index of the generic vertex attribute to be
     * bound.
     * @param string $name Specifies a null terminated string containing the name of
     * the vertex shader attribute variable to which index is to be bound.
     */ 
    function glBindAttribLocation(int $program, int $index, string $name) : void {};
 
    /**
     * Compiles a shader object
     * 
     * @param int $shader Specifies the shader object to be compiled.
     */ 
    function glCompileShader(int $shader) : void {};
 
    /**
     * Creates a program object
     */ 
    function glCreateProgram() : int {};
 
    /**
     * Creates a shader object
     * 
     * @param int $type
     */ 
    function glCreateShader(int $type) : int {};
 
    /**
     * Deletes a program object
     * 
     * @param int $program Specifies the program object to be deleted.
     */ 
    function glDeleteProgram(int $program) : void {};
 
    /**
     * Deletes a shader object
     * 
     * @param int $shader Specifies the shader object to be deleted.
     */ 
    function glDeleteShader(int $shader) : void {};
 
    /**
     * Detaches a shader object from a program object to which it is attached
     * 
     * @param int $program Specifies the program object from which to detach the
     * shader object.
     * @param int $shader Specifies the shader object to be detached.
     */ 
    function glDetachShader(int $program, int $shader) : void {};
 
    /**
     * glDisableVertexAttribArray
     * 
     * @param int $index
     */ 
    function glDisableVertexAttribArray(int $index) : void {};
 
    /**
     * Enable or disable a generic vertex attribute
     *     array
     * 
     * @param int $index Specifies the index of the generic vertex attribute to be
     * enabled or disabled.
     */ 
    function glEnableVertexAttribArray(int $index) : void {};
 
    /**
     * Returns the handles of the shader objects attached to a program object
     * 
     * @param int $program Specifies the program object to be queried.
     * @param int $maxCount Specifies the size of the array for storing the returned
     * object names.
     * @param int &$count Returns the number of names actually returned in shaders.
     * @param int &$shaders Specifies an array that is used to return the names of
     * attached shader objects.
     */ 
    function glGetAttachedShaders(int $program, int $maxCount, int &$count, int &$shaders) : void {};
 
    /**
     * Returns the location of an attribute variable
     * 
     * @param int $program Specifies the program object to be queried.
     * @param string $name Points to a null terminated string containing the name of
     * the attribute variable whose location is to be queried.
     */ 
    function glGetAttribLocation(int $program, string $name) : int {};
 
    /**
     * glGetProgramiv
     * 
     * @param int $program 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetProgramiv(int $program, int $pname, int &$params) : void {};
 
    /**
     * glGetShaderiv
     * 
     * @param int $shader 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetShaderiv(int $shader, int $pname, int &$params) : void {};
 
    /**
     * Returns the information log for a shader object
     * 
     * @PHP-GLFW: In the PHP extension this function directly returns the error
     * string instead of being passed by reference as an argument.
     * 
     * @param int $shader Specifies the shader object whose information log is to be
     * queried.
     * @param int $bufSize Specifies the size of the character buffer for storing
     * the returned information log.
     */ 
    function glGetShaderInfoLog(int $shader, int $bufSize) : string {};
 
    /**
     * Returns the location of a uniform variable
     * 
     * @param int $program Specifies the program object to be queried.
     * @param string $name Points to a null terminated string containing the name of
     * the uniform variable whose location is to be queried.
     */ 
    function glGetUniformLocation(int $program, string $name) : int {};
 
    /**
     * glGetUniformfv
     * 
     * @param int $program 
     * @param int $location 
     * @param float &$params
     */ 
    function glGetUniformfv(int $program, int $location, float &$params) : void {};
 
    /**
     * glGetUniformiv
     * 
     * @param int $program 
     * @param int $location 
     * @param int &$params
     */ 
    function glGetUniformiv(int $program, int $location, int &$params) : void {};
 
    /**
     * glGetVertexAttribdv
     * 
     * @param int $index 
     * @param int $pname 
     * @param float &$params
     */ 
    function glGetVertexAttribdv(int $index, int $pname, float &$params) : void {};
 
    /**
     * glGetVertexAttribfv
     * 
     * @param int $index 
     * @param int $pname 
     * @param float &$params
     */ 
    function glGetVertexAttribfv(int $index, int $pname, float &$params) : void {};
 
    /**
     * glGetVertexAttribiv
     * 
     * @param int $index 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetVertexAttribiv(int $index, int $pname, int &$params) : void {};
 
    /**
     * Determines if a name corresponds to a program object
     * 
     * @param int $program Specifies a potential program object.
     */ 
    function glIsProgram(int $program) : bool {};
 
    /**
     * Determines if a name corresponds to a shader object
     * 
     * @param int $shader Specifies a potential shader object.
     */ 
    function glIsShader(int $shader) : bool {};
 
    /**
     * Links a program object
     * 
     * @param int $program Specifies the handle of the program object to be linked.
     */ 
    function glLinkProgram(int $program) : void {};
 
    /**
     * Installs a program object as part of current rendering state
     * 
     * @param int $program Specifies the handle of the program object whose
     * executables are to be used as part of current rendering state.
     */ 
    function glUseProgram(int $program) : void {};
 
    /**
     * glUniform1f
     * 
     * @param int $location 
     * @param float $v0
     */ 
    function glUniform1f(int $location, float $v0) : void {};
 
    /**
     * glUniform2f
     * 
     * @param int $location 
     * @param float $v0 
     * @param float $v1
     */ 
    function glUniform2f(int $location, float $v0, float $v1) : void {};
 
    /**
     * glUniform3f
     * 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * @param float $v2
     */ 
    function glUniform3f(int $location, float $v0, float $v1, float $v2) : void {};
 
    /**
     * glUniform4f
     * 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * @param float $v2 
     * @param float $v3
     */ 
    function glUniform4f(int $location, float $v0, float $v1, float $v2, float $v3) : void {};
 
    /**
     * glUniform1i
     * 
     * @param int $location 
     * @param int $v0
     */ 
    function glUniform1i(int $location, int $v0) : void {};
 
    /**
     * glUniform2i
     * 
     * @param int $location 
     * @param int $v0 
     * @param int $v1
     */ 
    function glUniform2i(int $location, int $v0, int $v1) : void {};
 
    /**
     * glUniform3i
     * 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2
     */ 
    function glUniform3i(int $location, int $v0, int $v1, int $v2) : void {};
 
    /**
     * glUniform4i
     * 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2 
     * @param int $v3
     */ 
    function glUniform4i(int $location, int $v0, int $v1, int $v2, int $v3) : void {};
 
    /**
     * glUniform1fv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glUniform1fv(int $location, int $count, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniform2fv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glUniform2fv(int $location, int $count, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniform3fv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glUniform3fv(int $location, int $count, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniform4fv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glUniform4fv(int $location, int $count, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniform1iv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\IntBuffer|array $value
     */ 
    function glUniform1iv(int $location, int $count, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glUniform2iv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\IntBuffer|array $value
     */ 
    function glUniform2iv(int $location, int $count, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glUniform3iv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\IntBuffer|array $value
     */ 
    function glUniform3iv(int $location, int $count, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glUniform4iv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\IntBuffer|array $value
     */ 
    function glUniform4iv(int $location, int $count, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix2fv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glUniformMatrix2fv(int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix3fv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glUniformMatrix3fv(int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix4fv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\BufferInterface $buffer
     */ 
    function glUniformMatrix4fv(int $location, int $count, bool $transpose, \GL\Buffer\BufferInterface $buffer) : void {};
 
    /**
     * Validates a program object
     * 
     * @param int $program Specifies the handle of the program object to be
     * validated.
     */ 
    function glValidateProgram(int $program) : void {};
 
    /**
     * glVertexAttrib1d
     * 
     * @param int $index 
     * @param float $x
     */ 
    function glVertexAttrib1d(int $index, float $x) : void {};
 
    /**
     * glVertexAttrib1dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v
     */ 
    function glVertexAttrib1dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib1f
     * 
     * @param int $index 
     * @param float $x
     */ 
    function glVertexAttrib1f(int $index, float $x) : void {};
 
    /**
     * glVertexAttrib1fv
     * 
     * @param int $index 
     * @param \GL\Buffer\FloatBuffer|array $v
     */ 
    function glVertexAttrib1fv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib1s
     * 
     * @param int $index 
     * @param int $x
     */ 
    function glVertexAttrib1s(int $index, int $x) : void {};
 
    /**
     * glVertexAttrib1sv
     * 
     * @param int $index 
     * @param \GL\Buffer\ShortBuffer|array $v
     */ 
    function glVertexAttrib1sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib2d
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y
     */ 
    function glVertexAttrib2d(int $index, float $x, float $y) : void {};
 
    /**
     * glVertexAttrib2dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v
     */ 
    function glVertexAttrib2dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib2f
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y
     */ 
    function glVertexAttrib2f(int $index, float $x, float $y) : void {};
 
    /**
     * glVertexAttrib2fv
     * 
     * @param int $index 
     * @param \GL\Buffer\FloatBuffer|array $v
     */ 
    function glVertexAttrib2fv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib2s
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y
     */ 
    function glVertexAttrib2s(int $index, int $x, int $y) : void {};
 
    /**
     * glVertexAttrib2sv
     * 
     * @param int $index 
     * @param \GL\Buffer\ShortBuffer|array $v
     */ 
    function glVertexAttrib2sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib3d
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * @param float $z
     */ 
    function glVertexAttrib3d(int $index, float $x, float $y, float $z) : void {};
 
    /**
     * glVertexAttrib3dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v
     */ 
    function glVertexAttrib3dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib3f
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * @param float $z
     */ 
    function glVertexAttrib3f(int $index, float $x, float $y, float $z) : void {};
 
    /**
     * glVertexAttrib3fv
     * 
     * @param int $index 
     * @param \GL\Buffer\FloatBuffer|array $v
     */ 
    function glVertexAttrib3fv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib3s
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * @param int $z
     */ 
    function glVertexAttrib3s(int $index, int $x, int $y, int $z) : void {};
 
    /**
     * glVertexAttrib3sv
     * 
     * @param int $index 
     * @param \GL\Buffer\ShortBuffer|array $v
     */ 
    function glVertexAttrib3sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4Nbv
     * 
     * @param int $index 
     * @param \GL\Buffer\ByteBuffer|array $v
     */ 
    function glVertexAttrib4Nbv(int $index, \GL\Buffer\ByteBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4Niv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v
     */ 
    function glVertexAttrib4Niv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4Nsv
     * 
     * @param int $index 
     * @param \GL\Buffer\ShortBuffer|array $v
     */ 
    function glVertexAttrib4Nsv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4Nub
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * @param int $z 
     * @param int $w
     */ 
    function glVertexAttrib4Nub(int $index, int $x, int $y, int $z, int $w) : void {};
 
    /**
     * glVertexAttrib4Nubv
     * 
     * @param int $index 
     * @param \GL\Buffer\UbyteBuffer|array $v
     */ 
    function glVertexAttrib4Nubv(int $index, \GL\Buffer\UbyteBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4Nuiv
     * 
     * @param int $index 
     * @param \GL\Buffer\UIntBuffer|array $v
     */ 
    function glVertexAttrib4Nuiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4Nusv
     * 
     * @param int $index 
     * @param \GL\Buffer\UShortBuffer|array $v
     */ 
    function glVertexAttrib4Nusv(int $index, \GL\Buffer\UShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4bv
     * 
     * @param int $index 
     * @param \GL\Buffer\ByteBuffer|array $v
     */ 
    function glVertexAttrib4bv(int $index, \GL\Buffer\ByteBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4d
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * @param float $z 
     * @param float $w
     */ 
    function glVertexAttrib4d(int $index, float $x, float $y, float $z, float $w) : void {};
 
    /**
     * glVertexAttrib4dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v
     */ 
    function glVertexAttrib4dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4f
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * @param float $z 
     * @param float $w
     */ 
    function glVertexAttrib4f(int $index, float $x, float $y, float $z, float $w) : void {};
 
    /**
     * glVertexAttrib4fv
     * 
     * @param int $index 
     * @param \GL\Buffer\FloatBuffer|array $v
     */ 
    function glVertexAttrib4fv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4iv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v
     */ 
    function glVertexAttrib4iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4s
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * @param int $z 
     * @param int $w
     */ 
    function glVertexAttrib4s(int $index, int $x, int $y, int $z, int $w) : void {};
 
    /**
     * glVertexAttrib4sv
     * 
     * @param int $index 
     * @param \GL\Buffer\ShortBuffer|array $v
     */ 
    function glVertexAttrib4sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4ubv
     * 
     * @param int $index 
     * @param \GL\Buffer\UbyteBuffer|array $v
     */ 
    function glVertexAttrib4ubv(int $index, \GL\Buffer\UbyteBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4uiv
     * 
     * @param int $index 
     * @param \GL\Buffer\UIntBuffer|array $v
     */ 
    function glVertexAttrib4uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4usv
     * 
     * @param int $index 
     * @param \GL\Buffer\UShortBuffer|array $v
     */ 
    function glVertexAttrib4usv(int $index, \GL\Buffer\UShortBuffer|array $v) : void {};
 
    /**
     * define an array of generic vertex attribute data
     * 
     * @param int $index Specifies the index of the generic vertex attribute to be
     * modified.
     * @param int $size Specifies the number of components per generic vertex
     * attribute. Must be 1, 2, 3, 4. Additionally, the symbolic constant
     * <constant>GL_BGRA</constant> is accepted by glVertexAttribPointer. The
     * initial value is 4.
     * @param int $type Specifies the data type of each component in the array. The
     * symbolic constants <constant>GL_BYTE</constant>,
     * <constant>GL_UNSIGNED_BYTE</constant>, <constant>GL_SHORT</constant>,
     * <constant>GL_UNSIGNED_SHORT</constant>, <constant>GL_INT</constant>, and
     * <constant>GL_UNSIGNED_INT</constant> are accepted by glVertexAttribPointer
     * and glVertexAttribIPointer. Additionally <constant>GL_HALF_FLOAT</constant>,
     * <constant>GL_FLOAT</constant>, <constant>GL_DOUBLE</constant>,
     * <constant>GL_FIXED</constant>, <constant>GL_INT_2_10_10_10_REV</constant>,
     * <constant>GL_UNSIGNED_INT_2_10_10_10_REV</constant> and
     * <constant>GL_UNSIGNED_INT_10F_11F_11F_REV</constant> are accepted by
     * glVertexAttribPointer. <constant>GL_DOUBLE</constant> is also accepted by
     * glVertexAttribLPointer and is the only token accepted by the type parameter
     * for that function. The initial value is <constant>GL_FLOAT</constant>.
     * @param bool $normalized For glVertexAttribPointer, specifies whether
     * fixed-point data values should be normalized (<constant>GL_TRUE</constant>)
     * or converted directly as fixed-point values (<constant>GL_FALSE</constant>)
     * when they are accessed.
     * @param int $stride Specifies the byte offset between consecutive generic
     * vertex attributes. If stride is 0, the generic vertex attributes are
     * understood to be tightly packed in the array. The initial value is 0.
     * @param int $offset
     */ 
    function glVertexAttribPointer(int $index, int $size, int $type, bool $normalized, int $stride, int $offset) : void {};
 
    /**
     * glUniformMatrix2x3fv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glUniformMatrix2x3fv(int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix3x2fv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glUniformMatrix3x2fv(int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix2x4fv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glUniformMatrix2x4fv(int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix4x2fv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glUniformMatrix4x2fv(int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix3x4fv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glUniformMatrix3x4fv(int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix4x3fv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glUniformMatrix4x3fv(int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glColorMaski
     * 
     * @param int $index 
     * @param bool $r 
     * @param bool $g 
     * @param bool $b 
     * @param bool $a
     */ 
    function glColorMaski(int $index, bool $r, bool $g, bool $b, bool $a) : void {};
 
    /**
     * glGetBooleani_v
     * 
     * @param int $target 
     * @param int $index 
     * @param ?bool &...$data
     */ 
    function glGetBooleani_v(int $target, int $index, ?bool &...$data) : void {};
 
    /**
     * glGetIntegeri_v
     * 
     * @param int $target 
     * @param int $index 
     * @param ?bool &...$data
     */ 
    function glGetIntegeri_v(int $target, int $index, ?bool &...$data) : void {};
 
    /**
     * glEnablei
     * 
     * @param int $target 
     * @param int $index
     */ 
    function glEnablei(int $target, int $index) : void {};
 
    /**
     * glDisablei
     * 
     * @param int $target 
     * @param int $index
     */ 
    function glDisablei(int $target, int $index) : void {};
 
    /**
     * glIsEnabledi
     * 
     * @param int $target 
     * @param int $index
     */ 
    function glIsEnabledi(int $target, int $index) : bool {};
 
    /**
     * start transform feedback operation
     * 
     * @param int $primitiveMode Specify the output type of the primitives that will
     * be recorded into the buffer objects that are bound for transform feedback.
     */ 
    function glBeginTransformFeedback(int $primitiveMode) : void {};
 
    /**
     * glEndTransformFeedback
     */ 
    function glEndTransformFeedback() : void {};
 
    /**
     * bind a range within a buffer object to an indexed buffer target
     * 
     * @param int $target Specify the target of the bind operation. target must be
     * one of <constant>GL_ATOMIC_COUNTER_BUFFER</constant>,
     * <constant>GL_TRANSFORM_FEEDBACK_BUFFER</constant>,
     * <constant>GL_UNIFORM_BUFFER</constant>, or
     * <constant>GL_SHADER_STORAGE_BUFFER</constant>.
     * @param int $index Specify the index of the binding point within the array
     * specified by target.
     * @param int $buffer The name of a buffer object to bind to the specified
     * binding point.
     * @param int $offset The starting offset in basic machine units into the buffer
     * object buffer.
     * @param int $size The amount of data in machine units that can be read from
     * the buffer object while used as an indexed target.
     */ 
    function glBindBufferRange(int $target, int $index, int $buffer, int $offset, int $size) : void {};
 
    /**
     * bind a buffer object to an indexed buffer target
     * 
     * @param int $target Specify the target of the bind operation. target must be
     * one of <constant>GL_ATOMIC_COUNTER_BUFFER</constant>,
     * <constant>GL_TRANSFORM_FEEDBACK_BUFFER</constant>,
     * <constant>GL_UNIFORM_BUFFER</constant> or
     * <constant>GL_SHADER_STORAGE_BUFFER</constant>.
     * @param int $index Specify the index of the binding point within the array
     * specified by target.
     * @param int $buffer The name of a buffer object to bind to the specified
     * binding point.
     */ 
    function glBindBufferBase(int $target, int $index, int $buffer) : void {};
 
    /**
     * specify whether data read via glReadPixels should be clamped
     * 
     * @param int $target Target for color clamping. target must be
     * <constant>GL_CLAMP_READ_COLOR</constant>.
     * @param int $clamp Specifies whether to apply color clamping. clamp must be
     * <constant>GL_TRUE</constant> or <constant>GL_FALSE</constant>.
     */ 
    function glClampColor(int $target, int $clamp) : void {};
 
    /**
     * start conditional rendering
     * 
     * @param int $id Specifies the name of an occlusion query object whose results
     * are used to determine if the rendering commands are discarded.
     * @param int $mode Specifies how glBeginConditionalRender interprets the
     * results of the occlusion query.
     */ 
    function glBeginConditionalRender(int $id, int $mode) : void {};
 
    /**
     * glEndConditionalRender
     */ 
    function glEndConditionalRender() : void {};
 
    /**
     * glGetVertexAttribIiv
     * 
     * @param int $index 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetVertexAttribIiv(int $index, int $pname, int &$params) : void {};
 
    /**
     * glGetVertexAttribIuiv
     * 
     * @param int $index 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetVertexAttribIuiv(int $index, int $pname, int &$params) : void {};
 
    /**
     * glVertexAttribI1i
     * 
     * @param int $index 
     * @param int $x
     */ 
    function glVertexAttribI1i(int $index, int $x) : void {};
 
    /**
     * glVertexAttribI2i
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y
     */ 
    function glVertexAttribI2i(int $index, int $x, int $y) : void {};
 
    /**
     * glVertexAttribI3i
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * @param int $z
     */ 
    function glVertexAttribI3i(int $index, int $x, int $y, int $z) : void {};
 
    /**
     * glVertexAttribI4i
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * @param int $z 
     * @param int $w
     */ 
    function glVertexAttribI4i(int $index, int $x, int $y, int $z, int $w) : void {};
 
    /**
     * glVertexAttribI1ui
     * 
     * @param int $index 
     * @param int $x
     */ 
    function glVertexAttribI1ui(int $index, int $x) : void {};
 
    /**
     * glVertexAttribI2ui
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y
     */ 
    function glVertexAttribI2ui(int $index, int $x, int $y) : void {};
 
    /**
     * glVertexAttribI3ui
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * @param int $z
     */ 
    function glVertexAttribI3ui(int $index, int $x, int $y, int $z) : void {};
 
    /**
     * glVertexAttribI4ui
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * @param int $z 
     * @param int $w
     */ 
    function glVertexAttribI4ui(int $index, int $x, int $y, int $z, int $w) : void {};
 
    /**
     * glVertexAttribI1iv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v
     */ 
    function glVertexAttribI1iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI2iv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v
     */ 
    function glVertexAttribI2iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI3iv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v
     */ 
    function glVertexAttribI3iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI4iv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v
     */ 
    function glVertexAttribI4iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI1uiv
     * 
     * @param int $index 
     * @param \GL\Buffer\UIntBuffer|array $v
     */ 
    function glVertexAttribI1uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI2uiv
     * 
     * @param int $index 
     * @param \GL\Buffer\UIntBuffer|array $v
     */ 
    function glVertexAttribI2uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI3uiv
     * 
     * @param int $index 
     * @param \GL\Buffer\UIntBuffer|array $v
     */ 
    function glVertexAttribI3uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI4uiv
     * 
     * @param int $index 
     * @param \GL\Buffer\UIntBuffer|array $v
     */ 
    function glVertexAttribI4uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI4bv
     * 
     * @param int $index 
     * @param \GL\Buffer\ByteBuffer|array $v
     */ 
    function glVertexAttribI4bv(int $index, \GL\Buffer\ByteBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI4sv
     * 
     * @param int $index 
     * @param \GL\Buffer\ShortBuffer|array $v
     */ 
    function glVertexAttribI4sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI4ubv
     * 
     * @param int $index 
     * @param \GL\Buffer\UbyteBuffer|array $v
     */ 
    function glVertexAttribI4ubv(int $index, \GL\Buffer\UbyteBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI4usv
     * 
     * @param int $index 
     * @param \GL\Buffer\UShortBuffer|array $v
     */ 
    function glVertexAttribI4usv(int $index, \GL\Buffer\UShortBuffer|array $v) : void {};
 
    /**
     * glGetUniformuiv
     * 
     * @param int $program 
     * @param int $location 
     * @param int &$params
     */ 
    function glGetUniformuiv(int $program, int $location, int &$params) : void {};
 
    /**
     * bind a user-defined varying out variable to a fragment shader color number
     * 
     * @param int $program The name of the program containing varying out variable
     * whose binding to modify
     * @param int $color 
     * @param string $name The name of the user-defined varying out variable whose
     * binding to modify
     */ 
    function glBindFragDataLocation(int $program, int $color, string $name) : void {};
 
    /**
     * query the bindings of color numbers to user-defined varying out variables
     * 
     * @param int $program The name of the program containing varying out variable
     * whose binding to query
     * @param string $name The name of the user-defined varying out variable whose
     * binding to query
     */ 
    function glGetFragDataLocation(int $program, string $name) : int {};
 
    /**
     * glUniform1ui
     * 
     * @param int $location 
     * @param int $v0
     */ 
    function glUniform1ui(int $location, int $v0) : void {};
 
    /**
     * glUniform2ui
     * 
     * @param int $location 
     * @param int $v0 
     * @param int $v1
     */ 
    function glUniform2ui(int $location, int $v0, int $v1) : void {};
 
    /**
     * glUniform3ui
     * 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2
     */ 
    function glUniform3ui(int $location, int $v0, int $v1, int $v2) : void {};
 
    /**
     * glUniform4ui
     * 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2 
     * @param int $v3
     */ 
    function glUniform4ui(int $location, int $v0, int $v1, int $v2, int $v3) : void {};
 
    /**
     * glUniform1uiv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glUniform1uiv(int $location, int $count, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glUniform2uiv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glUniform2uiv(int $location, int $count, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glUniform3uiv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glUniform3uiv(int $location, int $count, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glUniform4uiv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glUniform4uiv(int $location, int $count, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glTexParameterIiv
     * 
     * @param int $target 
     * @param int $pname 
     * @param \GL\Buffer\IntBuffer|array $params
     */ 
    function glTexParameterIiv(int $target, int $pname, \GL\Buffer\IntBuffer|array $params) : void {};
 
    /**
     * glTexParameterIuiv
     * 
     * @param int $target 
     * @param int $pname 
     * @param \GL\Buffer\UIntBuffer|array $params
     */ 
    function glTexParameterIuiv(int $target, int $pname, \GL\Buffer\UIntBuffer|array $params) : void {};
 
    /**
     * glGetTexParameterIiv
     * 
     * @param int $target 
     * @param int $pname 
     * @param ?bool &...$params
     */ 
    function glGetTexParameterIiv(int $target, int $pname, ?bool &...$params) : void {};
 
    /**
     * glGetTexParameterIuiv
     * 
     * @param int $target 
     * @param int $pname 
     * @param ?bool &...$params
     */ 
    function glGetTexParameterIuiv(int $target, int $pname, ?bool &...$params) : void {};
 
    /**
     * glClearBufferiv
     * 
     * @param int $buffer 
     * @param int $drawbuffer 
     * @param \GL\Buffer\IntBuffer|array $value
     */ 
    function glClearBufferiv(int $buffer, int $drawbuffer, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glClearBufferuiv
     * 
     * @param int $buffer 
     * @param int $drawbuffer 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glClearBufferuiv(int $buffer, int $drawbuffer, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glClearBufferfv
     * 
     * @param int $buffer 
     * @param int $drawbuffer 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glClearBufferfv(int $buffer, int $drawbuffer, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glClearBufferfi
     * 
     * @param int $buffer 
     * @param int $drawbuffer 
     * @param float $depth 
     * @param int $stencil
     */ 
    function glClearBufferfi(int $buffer, int $drawbuffer, float $depth, int $stencil) : void {};
 
    /**
     * glGetStringi
     * 
     * @param int $name 
     * @param int $index
     */ 
    function glGetStringi(int $name, int $index) : string {};
 
    /**
     * determine if a name corresponds to a renderbuffer object
     * 
     * @param int $renderbuffer Specifies a value that may be the name of a
     * renderbuffer object.
     */ 
    function glIsRenderbuffer(int $renderbuffer) : bool {};
 
    /**
     * bind a renderbuffer to a renderbuffer target
     * 
     * @param int $target Specifies the renderbuffer target of the binding
     * operation. target must be <constant>GL_RENDERBUFFER</constant>.
     * @param int $renderbuffer Specifies the name of the renderbuffer object to
     * bind.
     */ 
    function glBindRenderbuffer(int $target, int $renderbuffer) : void {};
 
    /**
     * delete renderbuffer objects
     * 
     * @param int $n Specifies the number of renderbuffer objects to be deleted.
     * @param ?int ...$renderbuffers
     */ 
    function glDeleteRenderbuffers(int $n, ?int ...$renderbuffers) : void {};
 
    /**
     * generate renderbuffer object names
     * 
     * @param int $n Specifies the number of renderbuffer object names to generate.
     * @param ?int &...$renderbuffers
     */ 
    function glGenRenderbuffers(int $n, ?int &...$renderbuffers) : void {};
 
    /**
     * establish data storage, format and dimensions of a
     *     renderbuffer object's image
     * 
     * @param int $target Specifies a binding target of the allocation for
     * glRenderbufferStorage function. Must be <constant>GL_RENDERBUFFER</constant>.
     * @param int $internalformat Specifies the internal format to use for the
     * renderbuffer object's image.
     * @param int $width Specifies the width of the renderbuffer, in pixels.
     * @param int $height Specifies the height of the renderbuffer, in pixels.
     */ 
    function glRenderbufferStorage(int $target, int $internalformat, int $width, int $height) : void {};
 
    /**
     * glGetRenderbufferParameteriv
     * 
     * @param int $target 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetRenderbufferParameteriv(int $target, int $pname, int &$params) : void {};
 
    /**
     * determine if a name corresponds to a framebuffer object
     * 
     * @param int $framebuffer Specifies a value that may be the name of a
     * framebuffer object.
     */ 
    function glIsFramebuffer(int $framebuffer) : bool {};
 
    /**
     * bind a framebuffer to a framebuffer target
     * 
     * @param int $target Specifies the framebuffer target of the binding operation.
     * @param int $framebuffer Specifies the name of the framebuffer object to bind.
     */ 
    function glBindFramebuffer(int $target, int $framebuffer) : void {};
 
    /**
     * delete framebuffer objects
     * 
     * @param int $n Specifies the number of framebuffer objects to be deleted.
     * @param ?int ...$framebuffers
     */ 
    function glDeleteFramebuffers(int $n, ?int ...$framebuffers) : void {};
 
    /**
     * generate framebuffer object names
     * 
     * @param int $n Specifies the number of framebuffer object names to generate.
     * @param ?int &...$framebuffers
     */ 
    function glGenFramebuffers(int $n, ?int &...$framebuffers) : void {};
 
    /**
     * check the completeness status of a framebuffer
     * 
     * @param int $target Specify the target to which the framebuffer is bound for
     * glCheckFramebufferStatus, and the target against which framebuffer
     * completeness of framebuffer is checked for glCheckNamedFramebufferStatus.
     */ 
    function glCheckFramebufferStatus(int $target) : int {};
 
    /**
     * glFramebufferTexture1D
     * 
     * @param int $target 
     * @param int $attachment 
     * @param int $textarget 
     * @param int $texture 
     * @param int $level
     */ 
    function glFramebufferTexture1D(int $target, int $attachment, int $textarget, int $texture, int $level) : void {};
 
    /**
     * glFramebufferTexture2D
     * 
     * @param int $target 
     * @param int $attachment 
     * @param int $textarget 
     * @param int $texture 
     * @param int $level
     */ 
    function glFramebufferTexture2D(int $target, int $attachment, int $textarget, int $texture, int $level) : void {};
 
    /**
     * glFramebufferTexture3D
     * 
     * @param int $target 
     * @param int $attachment 
     * @param int $textarget 
     * @param int $texture 
     * @param int $level 
     * @param int $zoffset
     */ 
    function glFramebufferTexture3D(int $target, int $attachment, int $textarget, int $texture, int $level, int $zoffset) : void {};
 
    /**
     * attach a renderbuffer as a logical buffer of a framebuffer object
     * 
     * @param int $target Specifies the target to which the framebuffer is bound for
     * glFramebufferRenderbuffer.
     * @param int $attachment Specifies the attachment point of the framebuffer.
     * @param int $renderbuffertarget Specifies the renderbuffer target. Must be
     * <constant>GL_RENDERBUFFER</constant>.
     * @param int $renderbuffer Specifies the name of an existing renderbuffer
     * object of type renderbuffertarget to attach.
     */ 
    function glFramebufferRenderbuffer(int $target, int $attachment, int $renderbuffertarget, int $renderbuffer) : void {};
 
    /**
     * retrieve information about attachments of a framebuffer object
     * 
     * @param int $target Specifies the target to which the framebuffer object is
     * bound for glGetFramebufferAttachmentParameteriv.
     * @param int $attachment Specifies the attachment of the framebuffer object to
     * query.
     * @param int $pname Specifies the parameter of attachment to query.
     * @param int &$params Returns the value of parameter pname for attachment.
     */ 
    function glGetFramebufferAttachmentParameteriv(int $target, int $attachment, int $pname, int &$params) : void {};
 
    /**
     * generate mipmaps for a specified texture object
     * 
     * @param int $target Specifies the target to which the texture object is bound
     * for glGenerateMipmap. Must be one of <constant>GL_TEXTURE_1D</constant>,
     * <constant>GL_TEXTURE_2D</constant>, <constant>GL_TEXTURE_3D</constant>,
     * <constant>GL_TEXTURE_1D_ARRAY</constant>,
     * <constant>GL_TEXTURE_2D_ARRAY</constant>,
     * <constant>GL_TEXTURE_CUBE_MAP</constant>, or
     * <constant>GL_TEXTURE_CUBE_MAP_ARRAY</constant>.
     */ 
    function glGenerateMipmap(int $target) : void {};
 
    /**
     * copy a block of pixels from one framebuffer object to another
     * 
     * @param int $srcX0 Specify the bounds of the source rectangle within the read
     * buffer of the read framebuffer.
     * @param int $srcY0 
     * @param int $srcX1 
     * @param int $srcY1 
     * @param int $dstX0 Specify the bounds of the destination rectangle within the
     * write buffer of the write framebuffer.
     * @param int $dstY0 
     * @param int $dstX1 
     * @param int $dstY1 
     * @param int $mask The bitwise OR of the flags indicating which buffers are to
     * be copied. The allowed flags are <constant>GL_COLOR_BUFFER_BIT</constant>,
     * <constant>GL_DEPTH_BUFFER_BIT</constant> and
     * <constant>GL_STENCIL_BUFFER_BIT</constant>.
     * @param int $filter Specifies the interpolation to be applied if the image is
     * stretched. Must be <constant>GL_NEAREST</constant> or
     * <constant>GL_LINEAR</constant>.
     */ 
    function glBlitFramebuffer(int $srcX0, int $srcY0, int $srcX1, int $srcY1, int $dstX0, int $dstY0, int $dstX1, int $dstY1, int $mask, int $filter) : void {};
 
    /**
     * establish data storage, format, dimensions and sample count of
     *     a renderbuffer object's image
     * 
     * @param int $target Specifies a binding target of the allocation for
     * glRenderbufferStorageMultisample function. Must be
     * <constant>GL_RENDERBUFFER</constant>.
     * @param int $samples Specifies the number of samples to be used for the
     * renderbuffer object's storage.
     * @param int $internalformat Specifies the internal format to use for the
     * renderbuffer object's image.
     * @param int $width Specifies the width of the renderbuffer, in pixels.
     * @param int $height Specifies the height of the renderbuffer, in pixels.
     */ 
    function glRenderbufferStorageMultisample(int $target, int $samples, int $internalformat, int $width, int $height) : void {};
 
    /**
     * attach a single layer of a texture object as a logical buffer of a
     * framebuffer object
     * 
     * @param int $target Specifies the target to which the framebuffer is bound for
     * glFramebufferTextureLayer.
     * @param int $attachment Specifies the attachment point of the framebuffer.
     * @param int $texture Specifies the name of an existing texture object to
     * attach.
     * @param int $level Specifies the mipmap level of the texture object to attach.
     * @param int $layer Specifies the layer of the texture object to attach.
     */ 
    function glFramebufferTextureLayer(int $target, int $attachment, int $texture, int $level, int $layer) : void {};
 
    /**
     * indicate modifications to a range of a mapped buffer
     * 
     * @param int $target Specifies the target to which the buffer object is bound
     * for glFlushMappedBufferRange, which must be one of the buffer binding targets
     * in the following table:
     * @param int $offset Specifies the start of the buffer subrange, in basic
     * machine units.
     * @param int $length Specifies the length of the buffer subrange, in basic
     * machine units.
     */ 
    function glFlushMappedBufferRange(int $target, int $offset, int $length) : void {};
 
    /**
     * bind a vertex array object
     * 
     * @param int $array Specifies the name of the vertex array to bind.
     */ 
    function glBindVertexArray(int $array) : void {};
 
    /**
     * delete vertex array objects
     * 
     * @param int $n Specifies the number of vertex array objects to be deleted.
     * @param ?int ...$arrays
     */ 
    function glDeleteVertexArrays(int $n, ?int ...$arrays) : void {};
 
    /**
     * generate vertex array object names
     * 
     * @param int $n Specifies the number of vertex array object names to generate.
     * @param ?int &...$arrays
     */ 
    function glGenVertexArrays(int $n, ?int &...$arrays) : void {};
 
    /**
     * determine if a name corresponds to a vertex array object
     * 
     * @param int $array Specifies a value that may be the name of a vertex array
     * object.
     */ 
    function glIsVertexArray(int $array) : bool {};
 
    /**
     * draw multiple instances of a range of elements
     * 
     * @param int $mode Specifies what kind of primitives to render. Symbolic
     * constants <constant>GL_POINTS</constant>, <constant>GL_LINE_STRIP</constant>,
     * <constant>GL_LINE_LOOP</constant>, <constant>GL_LINES</constant>,
     * <constant>GL_TRIANGLE_STRIP</constant>, <constant>GL_TRIANGLE_FAN</constant>,
     * <constant>GL_TRIANGLES</constant> <constant>GL_LINES_ADJACENCY</constant>,
     * <constant>GL_LINE_STRIP_ADJACENCY</constant>,
     * <constant>GL_TRIANGLES_ADJACENCY</constant>,
     * <constant>GL_TRIANGLE_STRIP_ADJACENCY</constant> and
     * <constant>GL_PATCHES</constant> are accepted.
     * @param int $first Specifies the starting index in the enabled arrays.
     * @param int $count Specifies the number of indices to be rendered.
     * @param int $instancecount Specifies the number of instances of the specified
     * range of indices to be rendered.
     */ 
    function glDrawArraysInstanced(int $mode, int $first, int $count, int $instancecount) : void {};
 
    /**
     * attach a buffer object's data store to a buffer texture object
     * 
     * @param int $target Specifies the target to which the texture is bound for
     * glTexBuffer. Must be <constant>GL_TEXTURE_BUFFER</constant>.
     * @param int $internalformat Specifies the internal format of the data in the
     * store belonging to buffer.
     * @param int $buffer Specifies the name of the buffer object whose storage to
     * attach to the active buffer texture.
     */ 
    function glTexBuffer(int $target, int $internalformat, int $buffer) : void {};
 
    /**
     * specify the primitive restart index
     * 
     * @param int $index Specifies the value to be interpreted as the primitive
     * restart index.
     */ 
    function glPrimitiveRestartIndex(int $index) : void {};
 
    /**
     * copy all or part of the data store of a buffer object to the data store of
     * another buffer object
     * 
     * @param int $readTarget Specifies the target to which the source buffer object
     * is bound for glCopyBufferSubData
     * @param int $writeTarget Specifies the target to which the destination buffer
     * object is bound for glCopyBufferSubData.
     * @param int $readOffset Specifies the offset, in basic machine units, within
     * the data store of the source buffer object at which data will be read.
     * @param int $writeOffset Specifies the offset, in basic machine units, within
     * the data store of the destination buffer object at which data will be
     * written.
     * @param int $size Specifies the size, in basic machine units, of the data to
     * be copied from the source buffer object to the destination buffer object.
     */ 
    function glCopyBufferSubData(int $readTarget, int $writeTarget, int $readOffset, int $writeOffset, int $size) : void {};
 
    /**
     * retrieve the index of a named uniform block
     * 
     * @param int $program Specifies the name of a program containing the uniform
     * block.
     * @param string $uniformBlockName Specifies the address an array of characters
     * to containing the name of the uniform block whose index to retrieve.
     */ 
    function glGetUniformBlockIndex(int $program, string $uniformBlockName) : int {};
 
    /**
     * glGetActiveUniformBlockiv
     * 
     * @param int $program 
     * @param int $uniformBlockIndex 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetActiveUniformBlockiv(int $program, int $uniformBlockIndex, int $pname, int &$params) : void {};
 
    /**
     * assign a binding point to an active uniform block
     * 
     * @param int $program The name of a program object containing the active
     * uniform block whose binding to assign.
     * @param int $uniformBlockIndex The index of the active uniform block within
     * program whose binding to assign.
     * @param int $uniformBlockBinding Specifies the binding point to which to bind
     * the uniform block with index uniformBlockIndex within program.
     */ 
    function glUniformBlockBinding(int $program, int $uniformBlockIndex, int $uniformBlockBinding) : void {};
 
    /**
     * specifiy the vertex to be used as the source of data for flat shaded varyings
     * 
     * @param int $mode
     */ 
    function glProvokingVertex(int $mode) : void {};
 
    /**
     * create a new sync object and insert it into the GL command stream
     * 
     * @param int $condition Specifies the condition that must be met to set the
     * sync object's state to signaled. condition must be
     * <constant>GL_SYNC_GPU_COMMANDS_COMPLETE</constant>.
     * @param int $flags Specifies a bitwise combination of flags controlling the
     * behavior of the sync object. No flags are presently defined for this
     * operation and flags must be zero. flags is a placeholder for anticipated
     * future extensions of fence sync object capabilities.
     */ 
    function glFenceSync(int $condition, int $flags) : int {};
 
    /**
     * determine if a name corresponds to a sync object
     * 
     * @param int $sync Specifies a value that may be the name of a sync object.
     */ 
    function glIsSync(int $sync) : bool {};
 
    /**
     * delete a sync object
     * 
     * @param int $sync The sync object to be deleted.
     */ 
    function glDeleteSync(int $sync) : void {};
 
    /**
     * block and wait for a sync object to become signaled
     * 
     * @param int $sync The sync object whose status to wait on.
     * @param int $flags A bitfield controlling the command flushing behavior. flags
     * may be <constant>GL_SYNC_FLUSH_COMMANDS_BIT</constant>.
     * @param int $timeout The timeout, specified in nanoseconds, for which the
     * implementation should wait for sync to become signaled.
     */ 
    function glClientWaitSync(int $sync, int $flags, int $timeout) : int {};
 
    /**
     * instruct the GL server to block until the specified sync object becomes
     * signaled
     * 
     * @param int $sync Specifies the sync object whose status to wait on.
     * @param int $flags A bitfield controlling the command flushing behavior. flags
     * may be zero.
     * @param int $timeout Specifies the timeout that the server should wait before
     * continuing. timeout must be <constant>GL_TIMEOUT_IGNORED</constant>.
     */ 
    function glWaitSync(int $sync, int $flags, int $timeout) : void {};
 
    /**
     * glGetInteger64v
     * 
     * @param int $pname 
     * @param int &$data
     */ 
    function glGetInteger64v(int $pname, int &$data) : void {};
 
    /**
     * query the properties of a sync object
     * 
     * @param int $sync Specifies the sync object whose properties to query.
     * @param int $pname Specifies the parameter whose value to retrieve from the
     * sync object specified in sync.
     * @param int $count 
     * @param int &$length Specifies the address of an variable to receive the
     * number of integers placed in values.
     * @param int &$values Specifies the address of an array to receive the values
     * of the queried parameter.
     */ 
    function glGetSynciv(int $sync, int $pname, int $count, int &$length, int &$values) : void {};
 
    /**
     * glGetInteger64i_v
     * 
     * @param int $target 
     * @param int $index 
     * @param int &$data
     */ 
    function glGetInteger64i_v(int $target, int $index, int &$data) : void {};
 
    /**
     * glGetBufferParameteri64v
     * 
     * @param int $target 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetBufferParameteri64v(int $target, int $pname, int &$params) : void {};
 
    /**
     * attach a level of a texture object as a logical buffer of a framebuffer
     * object
     * 
     * @param int $target Specifies the target to which the framebuffer is bound for
     * all commands except glNamedFramebufferTexture.
     * @param int $attachment Specifies the attachment point of the framebuffer.
     * @param int $texture Specifies the name of an existing texture object to
     * attach.
     * @param int $level Specifies the mipmap level of the texture object to attach.
     */ 
    function glFramebufferTexture(int $target, int $attachment, int $texture, int $level) : void {};
 
    /**
     * establish the data storage, format, dimensions, and number of samples of a
     * multisample texture's image
     * 
     * @param int $target Specifies the target of the operation. target must be
     * <constant>GL_TEXTURE_2D_MULTISAMPLE</constant> or
     * <constant>GL_PROXY_TEXTURE_2D_MULTISAMPLE</constant>.
     * @param int $samples The number of samples in the multisample texture's image.
     * @param int $internalformat The internal format to be used to store the
     * multisample texture's image. internalformat must specify a color-renderable,
     * depth-renderable, or stencil-renderable format.
     * @param int $width The width of the multisample texture's image, in texels.
     * @param int $height The height of the multisample texture's image, in texels.
     * @param bool $fixedsamplelocations Specifies whether the image will use
     * identical sample locations and the same number of samples for all texels in
     * the image, and the sample locations will not depend on the internal format or
     * size of the image.
     */ 
    function glTexImage2DMultisample(int $target, int $samples, int $internalformat, int $width, int $height, bool $fixedsamplelocations) : void {};
 
    /**
     * establish the data storage, format, dimensions, and number of samples of a
     * multisample texture's image
     * 
     * @param int $target Specifies the target of the operation. target must be
     * <constant>GL_TEXTURE_2D_MULTISAMPLE_ARRAY</constant> or
     * <constant>GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY</constant>.
     * @param int $samples The number of samples in the multisample texture's image.
     * @param int $internalformat The internal format to be used to store the
     * multisample texture's image. internalformat must specify a color-renderable,
     * depth-renderable, or stencil-renderable format.
     * @param int $width The width of the multisample texture's image, in texels.
     * @param int $height The height of the multisample texture's image, in texels.
     * @param int $depth 
     * @param bool $fixedsamplelocations Specifies whether the image will use
     * identical sample locations and the same number of samples for all texels in
     * the image, and the sample locations will not depend on the internal format or
     * size of the image.
     */ 
    function glTexImage3DMultisample(int $target, int $samples, int $internalformat, int $width, int $height, int $depth, bool $fixedsamplelocations) : void {};
 
    /**
     * retrieve the location of a sample
     * 
     * @param int $pname Specifies the sample parameter name. pname must be
     * <constant>GL_SAMPLE_POSITION</constant>.
     * @param int $index Specifies the index of the sample whose position to query.
     * @param float &$val Specifies the address of an array to receive the position
     * of the sample.
     */ 
    function glGetMultisamplefv(int $pname, int $index, float &$val) : void {};
 
    /**
     * set the value of a sub-word of the sample mask
     * 
     * @param int $maskNumber Specifies which 32-bit sub-word of the sample mask to
     * update.
     * @param int $mask Specifies the new value of the mask sub-word.
     */ 
    function glSampleMaski(int $maskNumber, int $mask) : void {};
 
    /**
     * bind a user-defined varying out variable to a fragment shader color number
     * and index
     * 
     * @param int $program The name of the program containing varying out variable
     * whose binding to modify
     * @param int $colorNumber The color number to bind the user-defined varying out
     * variable to
     * @param int $index The index of the color input to bind the user-defined
     * varying out variable to
     * @param string $name The name of the user-defined varying out variable whose
     * binding to modify
     */ 
    function glBindFragDataLocationIndexed(int $program, int $colorNumber, int $index, string $name) : void {};
 
    /**
     * query the bindings of color indices to user-defined varying out variables
     * 
     * @param int $program The name of the program containing varying out variable
     * whose binding to query
     * @param string $name The name of the user-defined varying out variable whose
     * index to query
     */ 
    function glGetFragDataIndex(int $program, string $name) : int {};
 
    /**
     * generate sampler object names
     * 
     * @param int $count 
     * @param ?int &...$samplers
     */ 
    function glGenSamplers(int $count, ?int &...$samplers) : void {};
 
    /**
     * delete named sampler objects
     * 
     * @param int $count 
     * @param ?int ...$samplers
     */ 
    function glDeleteSamplers(int $count, ?int ...$samplers) : void {};
 
    /**
     * determine if a name corresponds to a sampler object
     * 
     * @param int $sampler
     */ 
    function glIsSampler(int $sampler) : bool {};
 
    /**
     * bind a named sampler to a texturing target
     * 
     * @param int $unit Specifies the index of the texture unit to which the sampler
     * is bound.
     * @param int $sampler Specifies the name of a sampler.
     */ 
    function glBindSampler(int $unit, int $sampler) : void {};
 
    /**
     * glSamplerParameteri
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param int $param
     */ 
    function glSamplerParameteri(int $sampler, int $pname, int $param) : void {};
 
    /**
     * glSamplerParameteriv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param \GL\Buffer\IntBuffer|array $param
     */ 
    function glSamplerParameteriv(int $sampler, int $pname, \GL\Buffer\IntBuffer|array $param) : void {};
 
    /**
     * glSamplerParameterf
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param float $param
     */ 
    function glSamplerParameterf(int $sampler, int $pname, float $param) : void {};
 
    /**
     * glSamplerParameterfv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param \GL\Buffer\FloatBuffer|array $param
     */ 
    function glSamplerParameterfv(int $sampler, int $pname, \GL\Buffer\FloatBuffer|array $param) : void {};
 
    /**
     * glSamplerParameterIiv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param \GL\Buffer\IntBuffer|array $param
     */ 
    function glSamplerParameterIiv(int $sampler, int $pname, \GL\Buffer\IntBuffer|array $param) : void {};
 
    /**
     * glSamplerParameterIuiv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param \GL\Buffer\UIntBuffer|array $param
     */ 
    function glSamplerParameterIuiv(int $sampler, int $pname, \GL\Buffer\UIntBuffer|array $param) : void {};
 
    /**
     * glGetSamplerParameteriv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetSamplerParameteriv(int $sampler, int $pname, int &$params) : void {};
 
    /**
     * glGetSamplerParameterIiv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetSamplerParameterIiv(int $sampler, int $pname, int &$params) : void {};
 
    /**
     * glGetSamplerParameterfv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param float &$params
     */ 
    function glGetSamplerParameterfv(int $sampler, int $pname, float &$params) : void {};
 
    /**
     * glGetSamplerParameterIuiv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetSamplerParameterIuiv(int $sampler, int $pname, int &$params) : void {};
 
    /**
     * record the GL time into a query object after all previous commands have
     * reached the GL server but have not yet necessarily executed.
     * 
     * @param int $id Specify the name of a query object into which to record the GL
     * time.
     * @param int $target Specify the counter to query. target must be
     * <constant>GL_TIMESTAMP</constant>.
     */ 
    function glQueryCounter(int $id, int $target) : void {};
 
    /**
     * glGetQueryObjecti64v
     * 
     * @param int $id 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetQueryObjecti64v(int $id, int $pname, int &$params) : void {};
 
    /**
     * glGetQueryObjectui64v
     * 
     * @param int $id 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetQueryObjectui64v(int $id, int $pname, int &$params) : void {};
 
    /**
     * modify the rate at which generic vertex attributes advance during instanced
     * rendering
     * 
     * @param int $index Specify the index of the generic vertex attribute.
     * @param int $divisor Specify the number of instances that will pass between
     * updates of the generic attribute at slot index.
     */ 
    function glVertexAttribDivisor(int $index, int $divisor) : void {};
 
    /**
     * glVertexAttribP1ui
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param int $value
     */ 
    function glVertexAttribP1ui(int $index, int $type, bool $normalized, int $value) : void {};
 
    /**
     * glVertexAttribP1uiv
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glVertexAttribP1uiv(int $index, int $type, bool $normalized, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glVertexAttribP2ui
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param int $value
     */ 
    function glVertexAttribP2ui(int $index, int $type, bool $normalized, int $value) : void {};
 
    /**
     * glVertexAttribP2uiv
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glVertexAttribP2uiv(int $index, int $type, bool $normalized, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glVertexAttribP3ui
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param int $value
     */ 
    function glVertexAttribP3ui(int $index, int $type, bool $normalized, int $value) : void {};
 
    /**
     * glVertexAttribP3uiv
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glVertexAttribP3uiv(int $index, int $type, bool $normalized, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glVertexAttribP4ui
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param int $value
     */ 
    function glVertexAttribP4ui(int $index, int $type, bool $normalized, int $value) : void {};
 
    /**
     * glVertexAttribP4uiv
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glVertexAttribP4uiv(int $index, int $type, bool $normalized, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glVertexP2ui
     * 
     * @param int $type 
     * @param int $value
     */ 
    function glVertexP2ui(int $type, int $value) : void {};
 
    /**
     * glVertexP2uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glVertexP2uiv(int $type, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glVertexP3ui
     * 
     * @param int $type 
     * @param int $value
     */ 
    function glVertexP3ui(int $type, int $value) : void {};
 
    /**
     * glVertexP3uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glVertexP3uiv(int $type, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glVertexP4ui
     * 
     * @param int $type 
     * @param int $value
     */ 
    function glVertexP4ui(int $type, int $value) : void {};
 
    /**
     * glVertexP4uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glVertexP4uiv(int $type, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glTexCoordP1ui
     * 
     * @param int $type 
     * @param int $coords
     */ 
    function glTexCoordP1ui(int $type, int $coords) : void {};
 
    /**
     * glTexCoordP1uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords
     */ 
    function glTexCoordP1uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glTexCoordP2ui
     * 
     * @param int $type 
     * @param int $coords
     */ 
    function glTexCoordP2ui(int $type, int $coords) : void {};
 
    /**
     * glTexCoordP2uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords
     */ 
    function glTexCoordP2uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glTexCoordP3ui
     * 
     * @param int $type 
     * @param int $coords
     */ 
    function glTexCoordP3ui(int $type, int $coords) : void {};
 
    /**
     * glTexCoordP3uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords
     */ 
    function glTexCoordP3uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glTexCoordP4ui
     * 
     * @param int $type 
     * @param int $coords
     */ 
    function glTexCoordP4ui(int $type, int $coords) : void {};
 
    /**
     * glTexCoordP4uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords
     */ 
    function glTexCoordP4uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glMultiTexCoordP1ui
     * 
     * @param int $texture 
     * @param int $type 
     * @param int $coords
     */ 
    function glMultiTexCoordP1ui(int $texture, int $type, int $coords) : void {};
 
    /**
     * glMultiTexCoordP1uiv
     * 
     * @param int $texture 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords
     */ 
    function glMultiTexCoordP1uiv(int $texture, int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glMultiTexCoordP2ui
     * 
     * @param int $texture 
     * @param int $type 
     * @param int $coords
     */ 
    function glMultiTexCoordP2ui(int $texture, int $type, int $coords) : void {};
 
    /**
     * glMultiTexCoordP2uiv
     * 
     * @param int $texture 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords
     */ 
    function glMultiTexCoordP2uiv(int $texture, int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glMultiTexCoordP3ui
     * 
     * @param int $texture 
     * @param int $type 
     * @param int $coords
     */ 
    function glMultiTexCoordP3ui(int $texture, int $type, int $coords) : void {};
 
    /**
     * glMultiTexCoordP3uiv
     * 
     * @param int $texture 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords
     */ 
    function glMultiTexCoordP3uiv(int $texture, int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glMultiTexCoordP4ui
     * 
     * @param int $texture 
     * @param int $type 
     * @param int $coords
     */ 
    function glMultiTexCoordP4ui(int $texture, int $type, int $coords) : void {};
 
    /**
     * glMultiTexCoordP4uiv
     * 
     * @param int $texture 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords
     */ 
    function glMultiTexCoordP4uiv(int $texture, int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glNormalP3ui
     * 
     * @param int $type 
     * @param int $coords
     */ 
    function glNormalP3ui(int $type, int $coords) : void {};
 
    /**
     * glNormalP3uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords
     */ 
    function glNormalP3uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glColorP3ui
     * 
     * @param int $type 
     * @param int $color
     */ 
    function glColorP3ui(int $type, int $color) : void {};
 
    /**
     * glColorP3uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $color
     */ 
    function glColorP3uiv(int $type, \GL\Buffer\UIntBuffer|array $color) : void {};
 
    /**
     * glColorP4ui
     * 
     * @param int $type 
     * @param int $color
     */ 
    function glColorP4ui(int $type, int $color) : void {};
 
    /**
     * glColorP4uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $color
     */ 
    function glColorP4uiv(int $type, \GL\Buffer\UIntBuffer|array $color) : void {};
 
    /**
     * glSecondaryColorP3ui
     * 
     * @param int $type 
     * @param int $color
     */ 
    function glSecondaryColorP3ui(int $type, int $color) : void {};
 
    /**
     * glSecondaryColorP3uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $color
     */ 
    function glSecondaryColorP3uiv(int $type, \GL\Buffer\UIntBuffer|array $color) : void {};
 
    /**
     * specifies minimum rate at which sample shading takes place
     * 
     * @param float $value Specifies the rate at which samples are shaded within
     * each covered pixel.
     */ 
    function glMinSampleShading(float $value) : void {};
 
    /**
     * glBlendEquationi
     * 
     * @param int $buf 
     * @param int $mode
     */ 
    function glBlendEquationi(int $buf, int $mode) : void {};
 
    /**
     * glBlendEquationSeparatei
     * 
     * @param int $buf 
     * @param int $modeRGB 
     * @param int $modeAlpha
     */ 
    function glBlendEquationSeparatei(int $buf, int $modeRGB, int $modeAlpha) : void {};
 
    /**
     * glBlendFunci
     * 
     * @param int $buf 
     * @param int $src 
     * @param int $dst
     */ 
    function glBlendFunci(int $buf, int $src, int $dst) : void {};
 
    /**
     * glBlendFuncSeparatei
     * 
     * @param int $buf 
     * @param int $srcRGB 
     * @param int $dstRGB 
     * @param int $srcAlpha 
     * @param int $dstAlpha
     */ 
    function glBlendFuncSeparatei(int $buf, int $srcRGB, int $dstRGB, int $srcAlpha, int $dstAlpha) : void {};
 
    /**
     * glUniform1d
     * 
     * @param int $location 
     * @param float $x
     */ 
    function glUniform1d(int $location, float $x) : void {};
 
    /**
     * glUniform2d
     * 
     * @param int $location 
     * @param float $x 
     * @param float $y
     */ 
    function glUniform2d(int $location, float $x, float $y) : void {};
 
    /**
     * glUniform3d
     * 
     * @param int $location 
     * @param float $x 
     * @param float $y 
     * @param float $z
     */ 
    function glUniform3d(int $location, float $x, float $y, float $z) : void {};
 
    /**
     * glUniform4d
     * 
     * @param int $location 
     * @param float $x 
     * @param float $y 
     * @param float $z 
     * @param float $w
     */ 
    function glUniform4d(int $location, float $x, float $y, float $z, float $w) : void {};
 
    /**
     * glUniform1dv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniform1dv(int $location, int $count, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniform2dv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniform2dv(int $location, int $count, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniform3dv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniform3dv(int $location, int $count, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniform4dv
     * 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniform4dv(int $location, int $count, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix2dv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniformMatrix2dv(int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix3dv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniformMatrix3dv(int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix4dv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniformMatrix4dv(int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix2x3dv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniformMatrix2x3dv(int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix2x4dv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniformMatrix2x4dv(int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix3x2dv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniformMatrix3x2dv(int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix3x4dv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniformMatrix3x4dv(int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix4x2dv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniformMatrix4x2dv(int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix4x3dv
     * 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glUniformMatrix4x3dv(int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glGetUniformdv
     * 
     * @param int $program 
     * @param int $location 
     * @param float &$params
     */ 
    function glGetUniformdv(int $program, int $location, float &$params) : void {};
 
    /**
     * retrieve the location of a subroutine uniform of a given shader stage within
     * a program
     * 
     * @param int $program Specifies the name of the program containing shader
     * stage.
     * @param int $shadertype Specifies the shader stage from which to query for
     * subroutine uniform index. shadertype must be one of
     * <constant>GL_VERTEX_SHADER</constant>,
     * <constant>GL_TESS_CONTROL_SHADER</constant>,
     * <constant>GL_TESS_EVALUATION_SHADER</constant>,
     * <constant>GL_GEOMETRY_SHADER</constant> or
     * <constant>GL_FRAGMENT_SHADER</constant>.
     * @param string $name Specifies the name of the subroutine uniform whose index
     * to query.
     */ 
    function glGetSubroutineUniformLocation(int $program, int $shadertype, string $name) : int {};
 
    /**
     * retrieve the index of a subroutine uniform of a given shader stage within a
     * program
     * 
     * @param int $program Specifies the name of the program containing shader
     * stage.
     * @param int $shadertype Specifies the shader stage from which to query for
     * subroutine uniform index. shadertype must be one of
     * <constant>GL_VERTEX_SHADER</constant>,
     * <constant>GL_TESS_CONTROL_SHADER</constant>,
     * <constant>GL_TESS_EVALUATION_SHADER</constant>,
     * <constant>GL_GEOMETRY_SHADER</constant> or
     * <constant>GL_FRAGMENT_SHADER</constant>.
     * @param string $name Specifies the name of the subroutine uniform whose index
     * to query.
     */ 
    function glGetSubroutineIndex(int $program, int $shadertype, string $name) : int {};
 
    /**
     * glGetActiveSubroutineUniformiv
     * 
     * @param int $program 
     * @param int $shadertype 
     * @param int $index 
     * @param int $pname 
     * @param int &$values
     */ 
    function glGetActiveSubroutineUniformiv(int $program, int $shadertype, int $index, int $pname, int &$values) : void {};
 
    /**
     * glUniformSubroutinesuiv
     * 
     * @param int $shadertype 
     * @param int $count 
     * @param \GL\Buffer\UIntBuffer|array $indices
     */ 
    function glUniformSubroutinesuiv(int $shadertype, int $count, \GL\Buffer\UIntBuffer|array $indices) : void {};
 
    /**
     * glGetUniformSubroutineuiv
     * 
     * @param int $shadertype 
     * @param int $location 
     * @param int &$params
     */ 
    function glGetUniformSubroutineuiv(int $shadertype, int $location, int &$params) : void {};
 
    /**
     * glGetProgramStageiv
     * 
     * @param int $program 
     * @param int $shadertype 
     * @param int $pname 
     * @param int &$values
     */ 
    function glGetProgramStageiv(int $program, int $shadertype, int $pname, int &$values) : void {};
 
    /**
     * glPatchParameteri
     * 
     * @param int $pname 
     * @param int $value
     */ 
    function glPatchParameteri(int $pname, int $value) : void {};
 
    /**
     * glPatchParameterfv
     * 
     * @param int $pname 
     * @param \GL\Buffer\FloatBuffer|array $values
     */ 
    function glPatchParameterfv(int $pname, \GL\Buffer\FloatBuffer|array $values) : void {};
 
    /**
     * bind a transform feedback object
     * 
     * @param int $target Specifies the target to which to bind the transform
     * feedback object id. target must be
     * <constant>GL_TRANSFORM_FEEDBACK</constant>.
     * @param int $id Specifies the name of a transform feedback object reserved by
     * glGenTransformFeedbacks.
     */ 
    function glBindTransformFeedback(int $target, int $id) : void {};
 
    /**
     * delete transform feedback objects
     * 
     * @param int $n Specifies the number of transform feedback objects to delete.
     * @param ?int ...$ids
     */ 
    function glDeleteTransformFeedbacks(int $n, ?int ...$ids) : void {};
 
    /**
     * reserve transform feedback object names
     * 
     * @param int $n Specifies the number of transform feedback object names to
     * reserve.
     * @param ?int &...$ids
     */ 
    function glGenTransformFeedbacks(int $n, ?int &...$ids) : void {};
 
    /**
     * determine if a name corresponds to a transform feedback object
     * 
     * @param int $id Specifies a value that may be the name of a transform feedback
     * object.
     */ 
    function glIsTransformFeedback(int $id) : bool {};
 
    /**
     * pause transform feedback operations
     */ 
    function glPauseTransformFeedback() : void {};
 
    /**
     * resume transform feedback operations
     */ 
    function glResumeTransformFeedback() : void {};
 
    /**
     * render primitives using a count derived from a transform feedback object
     * 
     * @param int $mode Specifies what kind of primitives to render. Symbolic
     * constants <constant>GL_POINTS</constant>, <constant>GL_LINE_STRIP</constant>,
     * <constant>GL_LINE_LOOP</constant>, <constant>GL_LINES</constant>,
     * <constant>GL_LINE_STRIP_ADJACENCY</constant>,
     * <constant>GL_LINES_ADJACENCY</constant>,
     * <constant>GL_TRIANGLE_STRIP</constant>, <constant>GL_TRIANGLE_FAN</constant>,
     * <constant>GL_TRIANGLES</constant>,
     * <constant>GL_TRIANGLE_STRIP_ADJACENCY</constant>,
     * <constant>GL_TRIANGLES_ADJACENCY</constant>, and
     * <constant>GL_PATCHES</constant> are accepted.
     * @param int $id Specifies the name of a transform feedback object from which
     * to retrieve a primitive count.
     */ 
    function glDrawTransformFeedback(int $mode, int $id) : void {};
 
    /**
     * render primitives using a count derived from a specifed stream of a transform
     * feedback object
     * 
     * @param int $mode Specifies what kind of primitives to render. Symbolic
     * constants <constant>GL_POINTS</constant>, <constant>GL_LINE_STRIP</constant>,
     * <constant>GL_LINE_LOOP</constant>, <constant>GL_LINES</constant>,
     * <constant>GL_LINE_STRIP_ADJACENCY</constant>,
     * <constant>GL_LINES_ADJACENCY</constant>,
     * <constant>GL_TRIANGLE_STRIP</constant>, <constant>GL_TRIANGLE_FAN</constant>,
     * <constant>GL_TRIANGLES</constant>,
     * <constant>GL_TRIANGLE_STRIP_ADJACENCY</constant>,
     * <constant>GL_TRIANGLES_ADJACENCY</constant>, and
     * <constant>GL_PATCHES</constant> are accepted.
     * @param int $id Specifies the name of a transform feedback object from which
     * to retrieve a primitive count.
     * @param int $stream Specifies the index of the transform feedback stream from
     * which to retrieve a primitive count.
     */ 
    function glDrawTransformFeedbackStream(int $mode, int $id, int $stream) : void {};
 
    /**
     * glBeginQueryIndexed
     * 
     * @param int $target 
     * @param int $index 
     * @param int $id
     */ 
    function glBeginQueryIndexed(int $target, int $index, int $id) : void {};
 
    /**
     * glEndQueryIndexed
     * 
     * @param int $target 
     * @param int $index
     */ 
    function glEndQueryIndexed(int $target, int $index) : void {};
 
    /**
     * return parameters of an indexed query object target
     * 
     * @param int $target Specifies a query object target. Must be
     * <constant>GL_SAMPLES_PASSED</constant>,
     * <constant>GL_ANY_SAMPLES_PASSED</constant>,
     * <constant>GL_ANY_SAMPLES_PASSED_CONSERVATIVE</constant>
     * <constant>GL_PRIMITIVES_GENERATED</constant>,
     * <constant>GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN</constant>,
     * <constant>GL_TIME_ELAPSED</constant>, or <constant>GL_TIMESTAMP</constant>.
     * @param int $index Specifies the index of the query object target.
     * @param int $pname Specifies the symbolic name of a query object target
     * parameter. Accepted values are <constant>GL_CURRENT_QUERY</constant> or
     * <constant>GL_QUERY_COUNTER_BITS</constant>.
     * @param int &$params Returns the requested data.
     */ 
    function glGetQueryIndexediv(int $target, int $index, int $pname, int &$params) : void {};
 
    /**
     * release resources consumed by the implementation's shader compiler
     */ 
    function glReleaseShaderCompiler() : void {};
 
    /**
     * retrieve the range and precision for numeric formats supported by the shader
     * compiler
     * 
     * @param int $shadertype 
     * @param int $precisiontype 
     * @param int &$range Specifies the address of array of two integers into which
     * encodings of the implementation's numeric range are returned.
     * @param int &$precision Specifies the address of an integer into which the
     * numeric precision of the implementation is written.
     */ 
    function glGetShaderPrecisionFormat(int $shadertype, int $precisiontype, int &$range, int &$precision) : void {};
 
    /**
     * glDepthRangef
     * 
     * @param float $n 
     * @param float $f
     */ 
    function glDepthRangef(float $n, float $f) : void {};
 
    /**
     * glClearDepthf
     * 
     * @param float $d
     */ 
    function glClearDepthf(float $d) : void {};
 
    /**
     * glProgramParameteri
     * 
     * @param int $program 
     * @param int $pname 
     * @param int $value
     */ 
    function glProgramParameteri(int $program, int $pname, int $value) : void {};
 
    /**
     * bind stages of a program object to a program pipeline
     * 
     * @param int $pipeline Specifies the program pipeline object to which to bind
     * stages from program.
     * @param int $stages Specifies a set of program stages to bind to the program
     * pipeline object.
     * @param int $program Specifies the program object containing the shader
     * executables to use in pipeline.
     */ 
    function glUseProgramStages(int $pipeline, int $stages, int $program) : void {};
 
    /**
     * set the active program object for a program pipeline object
     * 
     * @param int $pipeline Specifies the program pipeline object to set the active
     * program object for.
     * @param int $program Specifies the program object to set as the active program
     * pipeline object pipeline.
     */ 
    function glActiveShaderProgram(int $pipeline, int $program) : void {};
 
    /**
     * bind a program pipeline to the current context
     * 
     * @param int $pipeline Specifies the name of the pipeline object to bind to the
     * context.
     */ 
    function glBindProgramPipeline(int $pipeline) : void {};
 
    /**
     * delete program pipeline objects
     * 
     * @param int $n Specifies the number of program pipeline objects to delete.
     * @param ?int ...$pipelines
     */ 
    function glDeleteProgramPipelines(int $n, ?int ...$pipelines) : void {};
 
    /**
     * reserve program pipeline object names
     * 
     * @param int $n Specifies the number of program pipeline object names to
     * reserve.
     * @param ?int &...$pipelines
     */ 
    function glGenProgramPipelines(int $n, ?int &...$pipelines) : void {};
 
    /**
     * determine if a name corresponds to a program pipeline object
     * 
     * @param int $pipeline Specifies a value that may be the name of a program
     * pipeline object.
     */ 
    function glIsProgramPipeline(int $pipeline) : bool {};
 
    /**
     * glGetProgramPipelineiv
     * 
     * @param int $pipeline 
     * @param int $pname 
     * @param int &$params
     */ 
    function glGetProgramPipelineiv(int $pipeline, int $pname, int &$params) : void {};
 
    /**
     * glProgramUniform1i
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0
     */ 
    function glProgramUniform1i(int $program, int $location, int $v0) : void {};
 
    /**
     * glProgramUniform1iv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\IntBuffer|array $value
     */ 
    function glProgramUniform1iv(int $program, int $location, int $count, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform1f
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0
     */ 
    function glProgramUniform1f(int $program, int $location, float $v0) : void {};
 
    /**
     * glProgramUniform1fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniform1fv(int $program, int $location, int $count, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniform1d
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0
     */ 
    function glProgramUniform1d(int $program, int $location, float $v0) : void {};
 
    /**
     * glProgramUniform1dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniform1dv(int $program, int $location, int $count, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniform1ui
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0
     */ 
    function glProgramUniform1ui(int $program, int $location, int $v0) : void {};
 
    /**
     * glProgramUniform1uiv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glProgramUniform1uiv(int $program, int $location, int $count, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform2i
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * @param int $v1
     */ 
    function glProgramUniform2i(int $program, int $location, int $v0, int $v1) : void {};
 
    /**
     * glProgramUniform2iv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\IntBuffer|array $value
     */ 
    function glProgramUniform2iv(int $program, int $location, int $count, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform2f
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * @param float $v1
     */ 
    function glProgramUniform2f(int $program, int $location, float $v0, float $v1) : void {};
 
    /**
     * glProgramUniform2fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniform2fv(int $program, int $location, int $count, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniform2d
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * @param float $v1
     */ 
    function glProgramUniform2d(int $program, int $location, float $v0, float $v1) : void {};
 
    /**
     * glProgramUniform2dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniform2dv(int $program, int $location, int $count, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniform2ui
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * @param int $v1
     */ 
    function glProgramUniform2ui(int $program, int $location, int $v0, int $v1) : void {};
 
    /**
     * glProgramUniform2uiv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glProgramUniform2uiv(int $program, int $location, int $count, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform3i
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2
     */ 
    function glProgramUniform3i(int $program, int $location, int $v0, int $v1, int $v2) : void {};
 
    /**
     * glProgramUniform3iv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\IntBuffer|array $value
     */ 
    function glProgramUniform3iv(int $program, int $location, int $count, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform3f
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * @param float $v2
     */ 
    function glProgramUniform3f(int $program, int $location, float $v0, float $v1, float $v2) : void {};
 
    /**
     * glProgramUniform3fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniform3fv(int $program, int $location, int $count, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniform3d
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * @param float $v2
     */ 
    function glProgramUniform3d(int $program, int $location, float $v0, float $v1, float $v2) : void {};
 
    /**
     * glProgramUniform3dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniform3dv(int $program, int $location, int $count, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniform3ui
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2
     */ 
    function glProgramUniform3ui(int $program, int $location, int $v0, int $v1, int $v2) : void {};
 
    /**
     * glProgramUniform3uiv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glProgramUniform3uiv(int $program, int $location, int $count, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform4i
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2 
     * @param int $v3
     */ 
    function glProgramUniform4i(int $program, int $location, int $v0, int $v1, int $v2, int $v3) : void {};
 
    /**
     * glProgramUniform4iv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\IntBuffer|array $value
     */ 
    function glProgramUniform4iv(int $program, int $location, int $count, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform4f
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * @param float $v2 
     * @param float $v3
     */ 
    function glProgramUniform4f(int $program, int $location, float $v0, float $v1, float $v2, float $v3) : void {};
 
    /**
     * glProgramUniform4fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniform4fv(int $program, int $location, int $count, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniform4d
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * @param float $v2 
     * @param float $v3
     */ 
    function glProgramUniform4d(int $program, int $location, float $v0, float $v1, float $v2, float $v3) : void {};
 
    /**
     * glProgramUniform4dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniform4dv(int $program, int $location, int $count, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniform4ui
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2 
     * @param int $v3
     */ 
    function glProgramUniform4ui(int $program, int $location, int $v0, int $v1, int $v2, int $v3) : void {};
 
    /**
     * glProgramUniform4uiv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param \GL\Buffer\UIntBuffer|array $value
     */ 
    function glProgramUniform4uiv(int $program, int $location, int $count, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix2fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniformMatrix2fv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix3fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniformMatrix3fv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix4fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniformMatrix4fv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix2dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniformMatrix2dv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix3dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniformMatrix3dv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix4dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniformMatrix4dv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix2x3fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniformMatrix2x3fv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix3x2fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniformMatrix3x2fv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix2x4fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniformMatrix2x4fv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix4x2fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniformMatrix4x2fv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix3x4fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniformMatrix3x4fv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix4x3fv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value
     */ 
    function glProgramUniformMatrix4x3fv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix2x3dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniformMatrix2x3dv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix3x2dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniformMatrix3x2dv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix2x4dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniformMatrix2x4dv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix4x2dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniformMatrix4x2dv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix3x4dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniformMatrix3x4dv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix4x3dv
     * 
     * @param int $program 
     * @param int $location 
     * @param int $count 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value
     */ 
    function glProgramUniformMatrix4x3dv(int $program, int $location, int $count, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * validate a program pipeline object against current GL state
     * 
     * @param int $pipeline Specifies the name of a program pipeline object to
     * validate.
     */ 
    function glValidateProgramPipeline(int $pipeline) : void {};
 
    /**
     * glVertexAttribL1d
     * 
     * @param int $index 
     * @param float $x
     */ 
    function glVertexAttribL1d(int $index, float $x) : void {};
 
    /**
     * glVertexAttribL2d
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y
     */ 
    function glVertexAttribL2d(int $index, float $x, float $y) : void {};
 
    /**
     * glVertexAttribL3d
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * @param float $z
     */ 
    function glVertexAttribL3d(int $index, float $x, float $y, float $z) : void {};
 
    /**
     * glVertexAttribL4d
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * @param float $z 
     * @param float $w
     */ 
    function glVertexAttribL4d(int $index, float $x, float $y, float $z, float $w) : void {};
 
    /**
     * glVertexAttribL1dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v
     */ 
    function glVertexAttribL1dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttribL2dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v
     */ 
    function glVertexAttribL2dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttribL3dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v
     */ 
    function glVertexAttribL3dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttribL4dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v
     */ 
    function glVertexAttribL4dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glGetVertexAttribLdv
     * 
     * @param int $index 
     * @param int $pname 
     * @param float &$params
     */ 
    function glGetVertexAttribLdv(int $index, int $pname, float &$params) : void {};
 
    /**
     * glViewportArrayv
     * 
     * @param int $first 
     * @param int $count 
     * @param \GL\Buffer\FloatBuffer|array $v
     */ 
    function glViewportArrayv(int $first, int $count, \GL\Buffer\FloatBuffer|array $v) : void {};
 
    /**
     * glViewportIndexedf
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * @param float $w 
     * @param float $h
     */ 
    function glViewportIndexedf(int $index, float $x, float $y, float $w, float $h) : void {};
 
    /**
     * glViewportIndexedfv
     * 
     * @param int $index 
     * @param \GL\Buffer\FloatBuffer|array $v
     */ 
    function glViewportIndexedfv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {};
 
    /**
     * glScissorArrayv
     * 
     * @param int $first 
     * @param int $count 
     * @param \GL\Buffer\IntBuffer|array $v
     */ 
    function glScissorArrayv(int $first, int $count, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * define the scissor box for a specific viewport
     * 
     * @param int $index Specifies the index of the viewport whose scissor box to
     * modify.
     * @param int $left Specify the coordinate of the bottom left corner of the
     * scissor box, in pixels.
     * @param int $bottom 
     * @param int $width Specify ths dimensions of the scissor box, in pixels.
     * @param int $height
     */ 
    function glScissorIndexed(int $index, int $left, int $bottom, int $width, int $height) : void {};
 
    /**
     * glScissorIndexedv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v
     */ 
    function glScissorIndexedv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glDepthRangeArrayv
     * 
     * @param int $first 
     * @param int $count 
     * @param \GL\Buffer\DoubleBuffer|array $v
     */ 
    function glDepthRangeArrayv(int $first, int $count, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * specify mapping of depth values from normalized device coordinates to window
     * coordinates for a specified viewport
     * 
     * @param int $index Specifies the index of the viewport whose depth range to
     * update.
     * @param float $n 
     * @param float $f
     */ 
    function glDepthRangeIndexed(int $index, float $n, float $f) : void {};
 
    /**
     * glGetFloati_v
     * 
     * @param int $target 
     * @param int $index 
     * @param ?bool &...$data
     */ 
    function glGetFloati_v(int $target, int $index, ?bool &...$data) : void {};
 
    /**
     * glGetDoublei_v
     * 
     * @param int $target 
     * @param int $index 
     * @param ?bool &...$data
     */ 
    function glGetDoublei_v(int $target, int $index, ?bool &...$data) : void {};
 
    /**
     * glfwInit
     */ 
    function glfwInit() : int {};
 
    /**
     * glfwTerminate
     */ 
    function glfwTerminate() : void {};
 
    /**
     * glfwInitHint
     * 
     * @param int $hint 
     * @param int $value
     */ 
    function glfwInitHint(int $hint, int $value) : void {};
 
    /**
     * glfwGetVersion
     * 
     * @param int &$major 
     * @param int &$minor 
     * @param int &$rev
     */ 
    function glfwGetVersion(int &$major, int &$minor, int &$rev) : void {};
 
    /**
     * glfwGetVersionString
     */ 
    function glfwGetVersionString() : string {};
 
    /**
     * glfwGetPrimaryMonitor
     */ 
    function glfwGetPrimaryMonitor() : GLFWmonitor {};
 
    /**
     * glfwGetMonitorPos
     * 
     * @param GLFWmonitor $monitor 
     * @param int &$xpos 
     * @param int &$ypos
     */ 
    function glfwGetMonitorPos(GLFWmonitor $monitor, int &$xpos, int &$ypos) : void {};
 
    /**
     * glfwGetMonitorWorkarea
     * 
     * @param GLFWmonitor $monitor 
     * @param int &$xpos 
     * @param int &$ypos 
     * @param int &$width 
     * @param int &$height
     */ 
    function glfwGetMonitorWorkarea(GLFWmonitor $monitor, int &$xpos, int &$ypos, int &$width, int &$height) : void {};
 
    /**
     * glfwGetMonitorPhysicalSize
     * 
     * @param GLFWmonitor $monitor 
     * @param int &$widthMM 
     * @param int &$heightMM
     */ 
    function glfwGetMonitorPhysicalSize(GLFWmonitor $monitor, int &$widthMM, int &$heightMM) : void {};
 
    /**
     * glfwGetMonitorContentScale
     * 
     * @param GLFWmonitor $monitor 
     * @param float &$xscale 
     * @param float &$yscale
     */ 
    function glfwGetMonitorContentScale(GLFWmonitor $monitor, float &$xscale, float &$yscale) : void {};
 
    /**
     * glfwGetMonitorName
     * 
     * @param GLFWmonitor $monitor
     */ 
    function glfwGetMonitorName(GLFWmonitor $monitor) : string {};
 
    /**
     * glfwSetGamma
     * 
     * @param GLFWmonitor $monitor 
     * @param float $gamma
     */ 
    function glfwSetGamma(GLFWmonitor $monitor, float $gamma) : void {};
 
    /**
     * glfwDefaultWindowHints
     */ 
    function glfwDefaultWindowHints() : void {};
 
    /**
     * glfwWindowHint
     * 
     * @param int $hint 
     * @param int $value
     */ 
    function glfwWindowHint(int $hint, int $value) : void {};
 
    /**
     * glfwWindowHintString
     * 
     * @param int $hint 
     * @param string $value
     */ 
    function glfwWindowHintString(int $hint, string $value) : void {};
 
    /**
     * glfwCreateWindow
     * 
     * @param int $width 
     * @param int $height 
     * @param string $title 
     * @param ?GLFWmonitor $monitor 
     * @param ?GLFWwindow $share
     */ 
    function glfwCreateWindow(int $width, int $height, string $title, ?GLFWmonitor $monitor = NULL, ?GLFWwindow $share = NULL) : GLFWwindow {};
 
    /**
     * glfwDestroyWindow
     * 
     * @param GLFWwindow $window
     */ 
    function glfwDestroyWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwWindowShouldClose
     * 
     * @param GLFWwindow $window
     */ 
    function glfwWindowShouldClose(GLFWwindow $window) : int {};
 
    /**
     * glfwSetWindowShouldClose
     * 
     * @param GLFWwindow $window 
     * @param int $value
     */ 
    function glfwSetWindowShouldClose(GLFWwindow $window, int $value) : void {};
 
    /**
     * glfwSetWindowTitle
     * 
     * @param GLFWwindow $window 
     * @param string $title
     */ 
    function glfwSetWindowTitle(GLFWwindow $window, string $title) : void {};
 
    /**
     * glfwGetWindowPos
     * 
     * @param GLFWwindow $window 
     * @param int &$xpos 
     * @param int &$ypos
     */ 
    function glfwGetWindowPos(GLFWwindow $window, int &$xpos, int &$ypos) : void {};
 
    /**
     * glfwSetWindowPos
     * 
     * @param GLFWwindow $window 
     * @param int $xpos 
     * @param int $ypos
     */ 
    function glfwSetWindowPos(GLFWwindow $window, int $xpos, int $ypos) : void {};
 
    /**
     * glfwGetWindowSize
     * 
     * @param GLFWwindow $window 
     * @param int &$width 
     * @param int &$height
     */ 
    function glfwGetWindowSize(GLFWwindow $window, int &$width, int &$height) : void {};
 
    /**
     * glfwSetWindowSizeLimits
     * 
     * @param GLFWwindow $window 
     * @param int $minwidth 
     * @param int $minheight 
     * @param int $maxwidth 
     * @param int $maxheight
     */ 
    function glfwSetWindowSizeLimits(GLFWwindow $window, int $minwidth, int $minheight, int $maxwidth, int $maxheight) : void {};
 
    /**
     * glfwSetWindowAspectRatio
     * 
     * @param GLFWwindow $window 
     * @param int $numer 
     * @param int $denom
     */ 
    function glfwSetWindowAspectRatio(GLFWwindow $window, int $numer, int $denom) : void {};
 
    /**
     * glfwSetWindowSize
     * 
     * @param GLFWwindow $window 
     * @param int $width 
     * @param int $height
     */ 
    function glfwSetWindowSize(GLFWwindow $window, int $width, int $height) : void {};
 
    /**
     * glfwGetFramebufferSize
     * 
     * @param GLFWwindow $window 
     * @param int &$width 
     * @param int &$height
     */ 
    function glfwGetFramebufferSize(GLFWwindow $window, int &$width, int &$height) : void {};
 
    /**
     * glfwGetWindowFrameSize
     * 
     * @param GLFWwindow $window 
     * @param int &$left 
     * @param int &$top 
     * @param int &$right 
     * @param int &$bottom
     */ 
    function glfwGetWindowFrameSize(GLFWwindow $window, int &$left, int &$top, int &$right, int &$bottom) : void {};
 
    /**
     * glfwGetWindowContentScale
     * 
     * @param GLFWwindow $window 
     * @param float &$xscale 
     * @param float &$yscale
     */ 
    function glfwGetWindowContentScale(GLFWwindow $window, float &$xscale, float &$yscale) : void {};
 
    /**
     * glfwGetWindowOpacity
     * 
     * @param GLFWwindow $window
     */ 
    function glfwGetWindowOpacity(GLFWwindow $window) : float {};
 
    /**
     * glfwSetWindowOpacity
     * 
     * @param GLFWwindow $window 
     * @param float $opacity
     */ 
    function glfwSetWindowOpacity(GLFWwindow $window, float $opacity) : void {};
 
    /**
     * glfwIconifyWindow
     * 
     * @param GLFWwindow $window
     */ 
    function glfwIconifyWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwRestoreWindow
     * 
     * @param GLFWwindow $window
     */ 
    function glfwRestoreWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwMaximizeWindow
     * 
     * @param GLFWwindow $window
     */ 
    function glfwMaximizeWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwShowWindow
     * 
     * @param GLFWwindow $window
     */ 
    function glfwShowWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwHideWindow
     * 
     * @param GLFWwindow $window
     */ 
    function glfwHideWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwFocusWindow
     * 
     * @param GLFWwindow $window
     */ 
    function glfwFocusWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwRequestWindowAttention
     * 
     * @param GLFWwindow $window
     */ 
    function glfwRequestWindowAttention(GLFWwindow $window) : void {};
 
    /**
     * glfwGetWindowMonitor
     * 
     * @param GLFWwindow $window
     */ 
    function glfwGetWindowMonitor(GLFWwindow $window) : GLFWmonitor {};
 
    /**
     * glfwSetWindowMonitor
     * 
     * @param GLFWwindow $window 
     * @param GLFWmonitor $monitor 
     * @param int $xpos 
     * @param int $ypos 
     * @param int $width 
     * @param int $height 
     * @param int $refreshRate
     */ 
    function glfwSetWindowMonitor(GLFWwindow $window, GLFWmonitor $monitor, int $xpos, int $ypos, int $width, int $height, int $refreshRate) : void {};
 
    /**
     * glfwGetWindowAttrib
     * 
     * @param GLFWwindow $window 
     * @param int $attrib
     */ 
    function glfwGetWindowAttrib(GLFWwindow $window, int $attrib) : int {};
 
    /**
     * glfwSetWindowAttrib
     * 
     * @param GLFWwindow $window 
     * @param int $attrib 
     * @param int $value
     */ 
    function glfwSetWindowAttrib(GLFWwindow $window, int $attrib, int $value) : void {};
 
    /**
     * glfwPollEvents
     */ 
    function glfwPollEvents() : void {};
 
    /**
     * glfwWaitEvents
     */ 
    function glfwWaitEvents() : void {};
 
    /**
     * glfwWaitEventsTimeout
     * 
     * @param float $timeout
     */ 
    function glfwWaitEventsTimeout(float $timeout) : void {};
 
    /**
     * glfwPostEmptyEvent
     */ 
    function glfwPostEmptyEvent() : void {};
 
    /**
     * glfwGetInputMode
     * 
     * @param GLFWwindow $window 
     * @param int $mode
     */ 
    function glfwGetInputMode(GLFWwindow $window, int $mode) : int {};
 
    /**
     * glfwSetInputMode
     * 
     * @param GLFWwindow $window 
     * @param int $mode 
     * @param int $value
     */ 
    function glfwSetInputMode(GLFWwindow $window, int $mode, int $value) : void {};
 
    /**
     * glfwRawMouseMotionSupported
     */ 
    function glfwRawMouseMotionSupported() : int {};
 
    /**
     * glfwGetKeyName
     * 
     * @param int $key 
     * @param int $scancode
     */ 
    function glfwGetKeyName(int $key, int $scancode) : string {};
 
    /**
     * glfwGetKeyScancode
     * 
     * @param int $key
     */ 
    function glfwGetKeyScancode(int $key) : int {};
 
    /**
     * glfwGetKey
     * 
     * @param GLFWwindow $window 
     * @param int $key
     */ 
    function glfwGetKey(GLFWwindow $window, int $key) : int {};
 
    /**
     * glfwGetMouseButton
     * 
     * @param GLFWwindow $window 
     * @param int $button
     */ 
    function glfwGetMouseButton(GLFWwindow $window, int $button) : int {};
 
    /**
     * glfwGetCursorPos
     * 
     * @param GLFWwindow $window 
     * @param float &$xpos 
     * @param float &$ypos
     */ 
    function glfwGetCursorPos(GLFWwindow $window, float &$xpos, float &$ypos) : void {};
 
    /**
     * glfwSetCursorPos
     * 
     * @param GLFWwindow $window 
     * @param float $xpos 
     * @param float $ypos
     */ 
    function glfwSetCursorPos(GLFWwindow $window, float $xpos, float $ypos) : void {};
 
    /**
     * glfwCreateStandardCursor
     * 
     * @param int $shape
     */ 
    function glfwCreateStandardCursor(int $shape) : GLFWcursor {};
 
    /**
     * glfwDestroyCursor
     * 
     * @param GLFWcursor $cursor
     */ 
    function glfwDestroyCursor(GLFWcursor $cursor) : void {};
 
    /**
     * glfwSetCursor
     * 
     * @param GLFWwindow $window 
     * @param GLFWcursor $cursor
     */ 
    function glfwSetCursor(GLFWwindow $window, GLFWcursor $cursor) : void {};
 
    /**
     * glfwJoystickPresent
     * 
     * @param int $jid
     */ 
    function glfwJoystickPresent(int $jid) : int {};
 
    /**
     * glfwGetJoystickName
     * 
     * @param int $jid
     */ 
    function glfwGetJoystickName(int $jid) : string {};
 
    /**
     * glfwGetJoystickGUID
     * 
     * @param int $jid
     */ 
    function glfwGetJoystickGUID(int $jid) : string {};
 
    /**
     * glfwJoystickIsGamepad
     * 
     * @param int $jid
     */ 
    function glfwJoystickIsGamepad(int $jid) : int {};
 
    /**
     * glfwUpdateGamepadMappings
     * 
     * @param string $string
     */ 
    function glfwUpdateGamepadMappings(string $string) : int {};
 
    /**
     * glfwGetGamepadName
     * 
     * @param int $jid
     */ 
    function glfwGetGamepadName(int $jid) : string {};
 
    /**
     * glfwSetClipboardString
     * 
     * @param GLFWwindow $window 
     * @param string $string
     */ 
    function glfwSetClipboardString(GLFWwindow $window, string $string) : void {};
 
    /**
     * glfwGetClipboardString
     * 
     * @param GLFWwindow $window
     */ 
    function glfwGetClipboardString(GLFWwindow $window) : string {};
 
    /**
     * glfwGetTime
     */ 
    function glfwGetTime() : float {};
 
    /**
     * glfwSetTime
     * 
     * @param float $time
     */ 
    function glfwSetTime(float $time) : void {};
 
    /**
     * glfwMakeContextCurrent
     * 
     * @param GLFWwindow $window
     */ 
    function glfwMakeContextCurrent(GLFWwindow $window) : void {};
 
    /**
     * glfwGetCurrentContext
     */ 
    function glfwGetCurrentContext() : GLFWwindow {};
 
    /**
     * glfwSwapBuffers
     * 
     * @param GLFWwindow $window
     */ 
    function glfwSwapBuffers(GLFWwindow $window) : void {};
 
    /**
     * glfwSwapInterval
     * 
     * @param int $interval
     */ 
    function glfwSwapInterval(int $interval) : void {};
 
    /**
     * glfwExtensionSupported
     * 
     * @param string $extension
     */ 
    function glfwExtensionSupported(string $extension) : int {};
 
    /**
     * glfwVulkanSupported
     */ 
    function glfwVulkanSupported() : int {};
 
    /**
     * Replaces the source code in a shader object.
     * 
     * PHP-GLFW: As with PHP I don't see a reason to split up the shader source to
     * multiple addresses. 
     * This is why the function in PHP is simplyfied.
     * 
     * @param int $shader Specifies the handle of the shader object whose source
     * code is to be replaced.
     * @param string $source Specifies a string containing the source code to be
     * loaded into the shader.
     */ 
    function glShaderSource(int $shader, string $source) : void {};
 
    /**
     * creates and initializes a buffer object's data store
     * 
     * PHP-GLFW: In the PHP extension this method has different signiture compared
     * to the original. 
     * Instead of passing byte size and a pointer to the function, in PHP you pass a
     * `GL\Buffer\BufferInterface` instance.
     * 
     * Example: 
     * ```php
     * $buffer = new GL\Buffer\FloatBuffer([
     *     // positions     // colors
     *     0.5, -0.5, 0.0,  1.0, 0.0, 0.0,  // bottom right
     *    -0.5, -0.5, 0.0,  0.0, 1.0, 0.0,  // bottom let
     *     0.0,  0.5, 0.0,  0.0, 0.0, 1.0   // top 
     * ]);
     * 
     * glGenVertexArrays(1, $VAO);
     * glGenBuffers(1, $VBO);
     * glBindVertexArray($VAO);
     * glBindBuffer(GL_ARRAY_BUFFER, $VBO);
     * glBufferData(GL_ARRAY_BUFFER, $buffer, GL_STATIC_DRAW);
     * ```
     * 
     * @param int $target Specifies the target to which the buffer object is bound
     * for glBufferData.
     * @param \GL\Buffer\BufferInterface $buffer Specifies a buffer object
     * containing the to be uploaded data.
     * @param int $usage Specifies the expected usage pattern of the data store. The
     * symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY,
     * GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW,
     * GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
     */ 
    function glBufferData(int $target, \GL\Buffer\BufferInterface $buffer, int $usage) : void {};
 
    /**
     * glUniformMatrix4f
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Math\Mat4 $matrix
     */ 
    function glUniformMatrix4f(int $location, bool $transpose, \GL\Math\Mat4 $matrix) : void {};
 
 
}
