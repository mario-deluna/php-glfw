<?php 
namespace 
{
    /**
     * GLFW Window resource 
     * This class is used to store the GLFW window resource in PHP.
     */
    class GLFWwindow {}

    /**
     * GLFW Monitor resource
     * This class is used to store the GLFW monitor resource in PHP.
     */
    class GLFWmonitor {}

    /**
     * GLFW Cursor resource
     * This class is used to store the GLFW cursor resource in PHP.
     */
    class GLFWcursor {}

    /**
     * GLFW image resource
     * This class is used to store the GLFW image resource in PHP.
     */
    class GLFWimage {}

    /**
     * GLFW video mode resource
     * This class is used to store the GLFW video mode resource in PHP.
     */
    class GLFWvidmode {}

    /**
     * GLFW gamma ramp resource
     * This class is used to store the GLFW gamma ramp resource in PHP.
     */
    class GLFWgammaramp {}

    /**
     * GLFW Gamepad state resource
     * This class is used to store the GLFW gamepad state resource in PHP.
     */
    class GLFWgamepadstate {}
}

namespace GL\Math 
{
     
    class Vec2 
    {
        /**
         * Virtual property for "x" (0)
         */
        public float $x;

        /**
         * Virtual property for "y" (1)
         */
        public float $y;

        /**
         * Virtual property for "r" (0)
         */
        public float $r;

        /**
         * Virtual property for "g" (1)
         */
        public float $g;

        
        /**
         * Constructor
         */
        public function __construct(?float $x = null, ?float $y = null) {}

        /**
         * Returns the length of the vector
         * 
         * @return float
         */
        public function length() : float {}
        
        /**
         * Returns the dot product of this vector and another
         * 
         * @return float
         */
        public function dot(Vec2 $right) : float {}

        /**
         * Returns the distance between this vector and another
         * 
         * @return float
         */
        public function distance(Vec2 $right) : float {}

        /**
         * Returns squared distance between this vector and another
         * 
         * @return float
         */
        public function distance2(Vec2 $right) : float {}

        /**
         * Returns a normalized version of this vector
         */
        public function normalize() : Vec2 {}

        /**
         * Creates a new Vec2 where each component is x if x >= 0; otherwise, -x
         */
        public function abs() : Vec2 {}
        public function __toString() : string {}
    }
 
    class Vec3 
    {
        /**
         * Virtual property for "x" (0)
         */
        public float $x;

        /**
         * Virtual property for "y" (1)
         */
        public float $y;

        /**
         * Virtual property for "z" (2)
         */
        public float $z;

        /**
         * Virtual property for "r" (0)
         */
        public float $r;

        /**
         * Virtual property for "g" (1)
         */
        public float $g;

        /**
         * Virtual property for "b" (2)
         */
        public float $b;

        
        /**
         * Constructor
         */
        public function __construct(?float $x = null, ?float $y = null, ?float $z = null) {}

        /**
         * Returns the length of the vector
         * 
         * @return float
         */
        public function length() : float {}
        
        /**
         * Returns the dot product of this vector and another
         * 
         * @return float
         */
        public function dot(Vec3 $right) : float {}

        /**
         * Returns the distance between this vector and another
         * 
         * @return float
         */
        public function distance(Vec3 $right) : float {}

        /**
         * Returns squared distance between this vector and another
         * 
         * @return float
         */
        public function distance2(Vec3 $right) : float {}

        /**
         * Returns a normalized version of this vector
         */
        public function normalize() : Vec3 {}

        /**
         * Creates a new Vec3 where each component is x if x >= 0; otherwise, -x
         */
        public function abs() : Vec3 {}
        public function __toString() : string {}
    }
 
    class Vec4 
    {
        /**
         * Virtual property for "x" (0)
         */
        public float $x;

        /**
         * Virtual property for "y" (1)
         */
        public float $y;

        /**
         * Virtual property for "z" (2)
         */
        public float $z;

        /**
         * Virtual property for "w" (3)
         */
        public float $w;

        /**
         * Virtual property for "r" (0)
         */
        public float $r;

        /**
         * Virtual property for "g" (1)
         */
        public float $g;

        /**
         * Virtual property for "b" (2)
         */
        public float $b;

        /**
         * Virtual property for "a" (3)
         */
        public float $a;

        
        /**
         * Constructor
         */
        public function __construct(?float $x = null, ?float $y = null, ?float $z = null, ?float $w = null) {}

        /**
         * Returns the length of the vector
         * 
         * @return float
         */
        public function length() : float {}
        
        /**
         * Returns the dot product of this vector and another
         * 
         * @return float
         */
        public function dot(Vec4 $right) : float {}

        /**
         * Returns the distance between this vector and another
         * 
         * @return float
         */
        public function distance(Vec4 $right) : float {}

        /**
         * Returns squared distance between this vector and another
         * 
         * @return float
         */
        public function distance2(Vec4 $right) : float {}

        /**
         * Returns a normalized version of this vector
         */
        public function normalize() : Vec4 {}

        /**
         * Creates a new Vec4 where each component is x if x >= 0; otherwise, -x
         */
        public function abs() : Vec4 {}
        public function __toString() : string {}
    }
 
    class Mat4 
    {
        
        /**
         * Constructor
         */
        public function __construct() {}


        /**
         * Constructs and returns a new matrix based on the given array of values
         */
        public static function fromArray(array $values) : Mat4 {}

        /**
         * Creates and returns a copy of the current matrix
         */
        public function copy() : Mat4 {}
        public function row(int $index) : Vec4 {}
        public function setRow(int $index, Vec4 $row) : void {}
        public function col(int $index) : Vec4 {}
        public function setCol(int $index, Vec4 $col) : void {}
        public function lookAt(Vec3 $eye, Vec3 $center, Vec3 $up) : void {}
        public function perspective(float $fov, float $aspect, float $near, float $far) : void {}
        public function ortho(float $left, float $right, float $bottom, float $top, float $near, float $far) : void {}
        public function transpose() : void {}
        public function inverse() : void {}
        public function scale(Vec3 $scale) : void {}
        public function translate(Vec3 $scale) : void {}
        public function rotate(float $angle, Vec3 $axis) : void {}
        public function determinant() : float {}
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
         * pushes an array of values into the buffer. This works the same as when you pass inital data to the constructor.
         *
         * @param array<float> $values The values to be pushed into the buffer.
         *
         * @return void
         */
        public function pushArray(array $values) : void {}

        /**
         * Pushes the values of a Vec2 object into the buffer
         */
        public function pushVec2(\GL\Math\Vec2 $vec) : void {}

        /**
         * Pushes the values of a Vec3 object into the buffer
         */
        public function pushVec3(\GL\Math\Vec3 $vec) : void {}
        
        /**
         * Pushes the values of a Vec4 object into the buffer
         */
        public function pushVec4(\GL\Math\Vec4 $vec) : void {}
        
        /**
         * Pushes the values of a Mat4 (16) object into the buffer
         */
        public function pushMat4(\GL\Math\Mat4 $matrix) : void {}

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
         * pushes an array of values into the buffer. This works the same as when you pass inital data to the constructor.
         *
         * @param array<float> $values The values to be pushed into the buffer.
         *
         * @return void
         */
        public function pushArray(array $values) : void {}


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
         * pushes an array of values into the buffer. This works the same as when you pass inital data to the constructor.
         *
         * @param array<float> $values The values to be pushed into the buffer.
         *
         * @return void
         */
        public function pushArray(array $values) : void {}


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
         * pushes an array of values into the buffer. This works the same as when you pass inital data to the constructor.
         *
         * @param array<int> $values The values to be pushed into the buffer.
         *
         * @return void
         */
        public function pushArray(array $values) : void {}


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
         * pushes an array of values into the buffer. This works the same as when you pass inital data to the constructor.
         *
         * @param array<int> $values The values to be pushed into the buffer.
         *
         * @return void
         */
        public function pushArray(array $values) : void {}


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
         * pushes an array of values into the buffer. This works the same as when you pass inital data to the constructor.
         *
         * @param array<int> $values The values to be pushed into the buffer.
         *
         * @return void
         */
        public function pushArray(array $values) : void {}


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
         * pushes an array of values into the buffer. This works the same as when you pass inital data to the constructor.
         *
         * @param array<int> $values The values to be pushed into the buffer.
         *
         * @return void
         */
        public function pushArray(array $values) : void {}


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
         * pushes an array of values into the buffer. This works the same as when you pass inital data to the constructor.
         *
         * @param array<int> $values The values to be pushed into the buffer.
         *
         * @return void
         */
        public function pushArray(array $values) : void {}


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
         * pushes an array of values into the buffer. This works the same as when you pass inital data to the constructor.
         *
         * @param array<int> $values The values to be pushed into the buffer.
         *
         * @return void
         */
        public function pushArray(array $values) : void {}


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

namespace GL\Geometry\ObjFileParser
{
    /**
     * A mesh in the ObjFileParser is simply a collection of vertices with a material and optional indices.
     */
    class Mesh 
    {
        /**
         * The material of the mesh (can be null)
         * 
         * @var \GL\Geometry\ObjFileParser\Material|null
         */
        public readonly ?Material $material;

        /**
         * A float buffer containing vertex data of the mesh.
         * The layout of the data is not fixed but rather requested by the user.
         *
         * @var \GL\Buffer\FloatBuffer
         */
        public readonly FloatBuffer $vertices;

        /**
         * A unsigned int buffer containing indices of the mesh. (optional)
         *
         * @var \GL\Buffer\UIntBuffer|null
         */
        public readonly ?UIntBuffer $indices; 
    }

    class Material
    {
        /**
         * The name of the material 
         */
        public readonly string $name;

        /**
         * The ambient color of the material
         * this usally controls the color of the object in the shadow or when a light is not directly hitting the object.
         *
         * @var \GL\Math\Vec3 $ambient
         */
        public readonly \GL\Math\Vec3 $ambient;

        /**
         * The diffuse color of the material
         * this usally controls the color of the object when a light is directly hitting the object.
         * This property is often also used for albedo or base color.
         *
         * @var \GL\Math\Vec3 $diffuse
         */
        public readonly \GL\Math\Vec3 $diffuse;

        /**
         * The specular color of the material
         * This property is often also used for reflection color, shininess or highlights color.
         *
         * @var \GL\Math\Vec3 $specular
         */
        public readonly \GL\Math\Vec3 $specular;

        /**
         * The emmisive color of the material
         * This property is often also used for illumination, self glow or light emission.
         * 
         * @var \GL\Math\Vec3 $emmisive
         */
        public readonly \GL\Math\Vec3 $emmisive;

        /**
         * The transmittance of the material
         * This property is often also used for transparency or refraction color.
         * 
         * @var \GL\Math\Vec3 $transmittance
         */
        public readonly \GL\Math\Vec3 $transmittance;

        /**
         * The transmission filter color property of the Material
         *
         * @var \GL\Math\Vec3 $transmissionFilter
         */
        public readonly \GL\Math\Vec3 $transmissionFilter;

        /**
         * The shininess of the material
         * This property is often also used for glossiness or specular power.
         *
         * @var float $shininess
         */
        public readonly float $shininess;

        /**
         * The index of refraction of the materials
         *
         * @var float $indexOfRefraction
         */        
        public readonly float $indexOfRefraction;

        /**
         * The dissolve of the material
         * This property is often also used for opacity or transparency.
         *
         * @var float $dissolve
         */
        public readonly float $dissolve;

        /**
         * The illumination model of the material
         * from the obj file specification:
         *
         *  0. Color on and Ambient off
         *  1. Color on and Ambient on
         *  2. Highlight on
         *  3. Reflection on and Ray trace on
         *  4. Transparency: Glass on, Reflection: Ray trace on
         *  5. Reflection: Fresnel on and Ray trace on
         *  6. Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
         *  7. Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
         *  8. Reflection on and Ray trace off
         *  9. Transparency: Glass on, Reflection: Ray trace off
         *  10. Casts shadows onto invisible surfaces
         *
         * @var int $illuminationModel
         */
        public readonly int $illuminationModel;

        /**
         * Parser materials should not be constructed from user land.
         * calling this method will throw an exception.
         */
        public function __construct() {}
    }

    /**
     * An ObjFileParser/Group is a submesh of the object, in obj. files marked as "g" or "o". (Group or Object)
     */
    class Group
    {
        /**
         * The name of the group or object
         * 
         * @var string $name|null
         */
        public readonly ?string $name;

        /**
         * The number of faces in the group
         * 
         * @var int $faceCount
         */
        public readonly int $faceCount;

        /**
         * The offset of the first face in the resource object
         *
         * @var int $faceOffset
         */
        public readonly int $faceOffset;

        /**
         * The offset of the first index in the resource object
         *
         * @var int $indexOffset
         */
        public readonly int $indexOffset;

        /**
         * Parser groups should not be constructed from user land.
         * calling this method will throw an exception.
         */
        public function __construct() {}
    }

    /**
     * Texture object just holds the path to a texture file.
     */
    class Texture
    {
        public function __construct() {}
    }

    /**
     * Holder of internal data structres used by the ObjFileParser
     * This object has no direct use for the end user.
     */
    class Resource {}
}

namespace GL\Geometry
{
    /**
     * The Obj File Parser is a simple parser for the Wavefront .obj file format.
     * It is not a full implementation of the specification but rather a simple parser that can be used to load simple models.
     * 
     * **IMPORTANT: We ONLY support triangulated meshes!**
     */
    class ObjFileParser
    {   
        /**
         * An array of material objects parsed from the file.
         * 
         * @var array<\GL\Geometry\ObjFileParser\Material>
         */
        public readonly array $materials;

        /**
         * An array objects parsed from the file. (marked as "o")
         *
         * @var array<\GL\Geometry\ObjFileParser\Group>
         */
        public readonly array $groups;

        /**
         * An array groups parsed from the file. (marked as "g")
         *
         * @var array<\GL\Geometry\ObjFileParser\Group>
         */
        public readonly array $objects;

        /**
         * Parses on `.obj` (Wavefront object) file and makes the parsed data available.
         *  
         * IMPORTANT: This obj. file parser does ONLY support triangulated meshes!
         *
         * @param string $file The path to the obj file to parse.
         */
        public function __construct(string $file) {}

        /**
         * Returns a FloatBuffer object containing the requested vertex data for the given group.
         * If no group is given the entire object is returned.
         * 
         * The layout of the buffer is specifed as a string, where each character represents a vertex attribute.
         * The following characters are supported:
         *
         *  * `p` - position
         *  * `n` - normal 
         *  * `N` - generated normal (estimated for each face)
         *  * `c` - texture coordinate
         *  * `t` - tangent (estimated for each face)
         *  * `b` - bitangent (estimated for each face)
         * 
         * You can use combine those characters to specify the layout of the buffer.
         * 
         * Example: 
         * Layout: `pnc`
         * Will generate the following buffer layout:
         * ```
         * [position.x, position.y, position.z, normal.x, normal.y, normal.z, textureCoordinate.x, textureCoordinate.y, ...]
         * ```
         * @param string $layout The layout of the buffer.
         * @param \GL\Geometry\ObjFileParser\Group|null $group The group to get the vertex data for.
         * 
         * @return \GL\Math\FloatBuffer The generated vertex data buffer
         */
        public function getVertices(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : \GL\Buffer\FloatBuffer {}

        public function getIndexedVertices(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : \GL\Geometry\ObjFileParser\Mesh {}

        /**
         * 
         * @return array<\GL\Geometry\ObjFileParser\Mesh>
         */
        public function getMeshes(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : array {}

        public function getIndexedMeshes(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : array {}
    }
}

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
     * 
     * @return void
     */ 
    function glCullFace(int $mode) : void {};
 
    /**
     * define front- and back-facing polygons
     * 
     * @param int $mode Specifies the orientation of front-facing polygons.
     * <constant>GL_CW</constant> and <constant>GL_CCW</constant> are accepted. The
     * initial value is <constant>GL_CCW</constant>.
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glHint(int $target, int $mode) : void {};
 
    /**
     * specify the width of rasterized lines
     * 
     * @param float $width Specifies the width of rasterized lines. The initial
     * value is 1.
     * 
     * @return void
     */ 
    function glLineWidth(float $width) : void {};
 
    /**
     * specify the diameter of rasterized points
     * 
     * @param float $size Specifies the diameter of rasterized points. The initial
     * value is 1.
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glScissor(int $x, int $y, int $width, int $height) : void {};
 
    /**
     * glTexParameterf
     * 
     * @param int $target 
     * @param int $pname 
     * @param float $param 
     * 
     * @return void
     */ 
    function glTexParameterf(int $target, int $pname, float $param) : void {};
 
    /**
     * glTexParameterfv
     * 
     * @param int $target 
     * @param int $pname 
     * @param \GL\Buffer\FloatBuffer|array $params 
     * 
     * @return void
     */ 
    function glTexParameterfv(int $target, int $pname, \GL\Buffer\FloatBuffer|array $params) : void {};
 
    /**
     * glTexParameteri
     * 
     * @param int $target 
     * @param int $pname 
     * @param int $param 
     * 
     * @return void
     */ 
    function glTexParameteri(int $target, int $pname, int $param) : void {};
 
    /**
     * glTexParameteriv
     * 
     * @param int $target 
     * @param int $pname 
     * @param \GL\Buffer\IntBuffer|array $params 
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glDrawBuffer(int $buf) : void {};
 
    /**
     * clear buffers to preset values
     * 
     * @param int $mask Bitwise OR of masks that indicate the buffers to be cleared.
     * The three masks are <constant>GL_COLOR_BUFFER_BIT</constant>,
     * <constant>GL_DEPTH_BUFFER_BIT</constant>, and
     * <constant>GL_STENCIL_BUFFER_BIT</constant>.
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glClearColor(float $red, float $green, float $blue, float $alpha) : void {};
 
    /**
     * specify the clear value for the stencil buffer
     * 
     * @param int $s Specifies the index used when the stencil buffer is cleared.
     * The initial value is 0.
     * 
     * @return void
     */ 
    function glClearStencil(int $s) : void {};
 
    /**
     * specify the clear value for the depth buffer
     * 
     * @param float $depth Specifies the depth value used when the depth buffer is
     * cleared. The initial value is 1.
     * 
     * @return void
     */ 
    function glClearDepth(float $depth) : void {};
 
    /**
     * control the front and back writing of individual bits in the stencil planes
     * 
     * @param int $mask Specifies a bit mask to enable and disable writing of
     * individual bits in the stencil planes. Initially, the mask is all 1's.
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glColorMask(bool $red, bool $green, bool $blue, bool $alpha) : void {};
 
    /**
     * enable or disable writing into the depth buffer
     * 
     * @param bool $flag Specifies whether the depth buffer is enabled for writing.
     * If flag is <constant>GL_FALSE</constant>, depth buffer writing is disabled.
     * Otherwise, it is enabled. Initially, depth buffer writing is enabled.
     * 
     * @return void
     */ 
    function glDepthMask(bool $flag) : void {};
 
    /**
     * glDisable
     * 
     * @param int $cap 
     * 
     * @return void
     */ 
    function glDisable(int $cap) : void {};
 
    /**
     * enable or disable server-side GL capabilities
     * 
     * @param int $cap Specifies a symbolic constant indicating a GL capability.
     * 
     * @return void
     */ 
    function glEnable(int $cap) : void {};
 
    /**
     * block until all GL execution is complete
     * @return void
     */ 
    function glFinish() : void {};
 
    /**
     * force execution of GL commands in finite time
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glStencilFunc(int $func, int $ref, int $mask) : void {};
 
    /**
     * set front and back stencil test actions
     * 
     * @param int $fail 
     * @param int $zfail 
     * @param int $zpass 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glDepthFunc(int $func) : void {};
 
    /**
     * glPixelStoref
     * 
     * @param int $pname 
     * @param float $param 
     * 
     * @return void
     */ 
    function glPixelStoref(int $pname, float $param) : void {};
 
    /**
     * glPixelStorei
     * 
     * @param int $pname 
     * @param int $param 
     * 
     * @return void
     */ 
    function glPixelStorei(int $pname, int $param) : void {};
 
    /**
     * select a color buffer source for pixels
     * 
     * @param int $src 
     * 
     * @return void
     */ 
    function glReadBuffer(int $src) : void {};
 
    /**
     * glGetBooleanv
     * 
     * @param int $pname 
     * @param ?bool &...$data 
     * 
     * @return void
     */ 
    function glGetBooleanv(int $pname, ?bool &...$data) : void {};
 
    /**
     * glGetDoublev
     * 
     * @param int $pname 
     * @param ?bool &...$data 
     * 
     * @return void
     */ 
    function glGetDoublev(int $pname, ?bool &...$data) : void {};
 
    /**
     * return error information
     * @return int
     */ 
    function glGetError() : int {};
 
    /**
     * glGetFloatv
     * 
     * @param int $pname 
     * @param ?bool &...$data 
     * 
     * @return void
     */ 
    function glGetFloatv(int $pname, ?bool &...$data) : void {};
 
    /**
     * glGetIntegerv
     * 
     * @param int $pname 
     * @param ?bool &...$data 
     * 
     * @return void
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
     * 
     * @return string
     */ 
    function glGetString(int $name) : string {};
 
    /**
     * glGetTexParameterfv
     * 
     * @param int $target 
     * @param int $pname 
     * @param ?bool &...$params 
     * 
     * @return void
     */ 
    function glGetTexParameterfv(int $target, int $pname, ?bool &...$params) : void {};
 
    /**
     * glGetTexParameteriv
     * 
     * @param int $target 
     * @param int $pname 
     * @param ?bool &...$params 
     * 
     * @return void
     */ 
    function glGetTexParameteriv(int $target, int $pname, ?bool &...$params) : void {};
 
    /**
     * glGetTexLevelParameterfv
     * 
     * @param int $target 
     * @param int $level 
     * @param int $pname 
     * @param float &$params 
     * 
     * @return void
     */ 
    function glGetTexLevelParameterfv(int $target, int $level, int $pname, float &$params) : void {};
 
    /**
     * glGetTexLevelParameteriv
     * 
     * @param int $target 
     * @param int $level 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetTexLevelParameteriv(int $target, int $level, int $pname, int &$params) : void {};
 
    /**
     * test whether a capability is enabled
     * 
     * @param int $cap Specifies a symbolic constant indicating a GL capability.
     * 
     * @return bool
     */ 
    function glIsEnabled(int $cap) : bool {};
 
    /**
     * specify mapping of depth values from normalized device coordinates to window
     * coordinates
     * 
     * @param float $n 
     * @param float $f 
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glDrawArrays(int $mode, int $first, int $count) : void {};
 
    /**
     * set the scale and units used to calculate depth values
     * 
     * @param float $factor Specifies a scale factor that is used to create a
     * variable depth offset for each polygon. The initial value is 0.
     * @param float $units Is multiplied by an implementation-specific value to
     * create a constant depth offset. The initial value is 0.
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glBindTexture(int $target, int $texture) : void {};
 
    /**
     * delete named textures
     * 
     * @param int $n Specifies the number of textures to be deleted.
     * @param ?int ...$textures 
     * 
     * @return void
     */ 
    function glDeleteTextures(int $n, ?int ...$textures) : void {};
 
    /**
     * generate texture names
     * 
     * @param int $n Specifies the number of texture names to be generated.
     * @param ?int &...$textures 
     * 
     * @return void
     */ 
    function glGenTextures(int $n, ?int &...$textures) : void {};
 
    /**
     * determine if a name corresponds to a texture
     * 
     * @param int $texture Specifies a value that may be the name of a texture.
     * 
     * @return bool
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glSampleCoverage(float $value, bool $invert) : void {};
 
    /**
     * specify pixel arithmetic for RGB and alpha components separately
     * 
     * @param int $sfactorRGB 
     * @param int $dfactorRGB 
     * @param int $sfactorAlpha 
     * @param int $dfactorAlpha 
     * 
     * @return void
     */ 
    function glBlendFuncSeparate(int $sfactorRGB, int $dfactorRGB, int $sfactorAlpha, int $dfactorAlpha) : void {};
 
    /**
     * glPointParameterf
     * 
     * @param int $pname 
     * @param float $param 
     * 
     * @return void
     */ 
    function glPointParameterf(int $pname, float $param) : void {};
 
    /**
     * glPointParameterfv
     * 
     * @param int $pname 
     * @param \GL\Buffer\FloatBuffer|array $params 
     * 
     * @return void
     */ 
    function glPointParameterfv(int $pname, \GL\Buffer\FloatBuffer|array $params) : void {};
 
    /**
     * glPointParameteri
     * 
     * @param int $pname 
     * @param int $param 
     * 
     * @return void
     */ 
    function glPointParameteri(int $pname, int $param) : void {};
 
    /**
     * glPointParameteriv
     * 
     * @param int $pname 
     * @param \GL\Buffer\IntBuffer|array $params 
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glBlendEquation(int $mode) : void {};
 
    /**
     * generate query object names
     * 
     * @param int $n Specifies the number of query object names to be generated.
     * @param ?int &...$ids 
     * 
     * @return void
     */ 
    function glGenQueries(int $n, ?int &...$ids) : void {};
 
    /**
     * delete named query objects
     * 
     * @param int $n Specifies the number of query objects to be deleted.
     * @param ?int ...$ids 
     * 
     * @return void
     */ 
    function glDeleteQueries(int $n, ?int ...$ids) : void {};
 
    /**
     * determine if a name corresponds to a query object
     * 
     * @param int $id Specifies a value that may be the name of a query object.
     * 
     * @return bool
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
     * 
     * @return void
     */ 
    function glBeginQuery(int $target, int $id) : void {};
 
    /**
     * glEndQuery
     * 
     * @param int $target 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glGetQueryiv(int $target, int $pname, int &$params) : void {};
 
    /**
     * glGetQueryObjectiv
     * 
     * @param int $id 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetQueryObjectiv(int $id, int $pname, int &$params) : void {};
 
    /**
     * glGetQueryObjectuiv
     * 
     * @param int $id 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetQueryObjectuiv(int $id, int $pname, int &$params) : void {};
 
    /**
     * bind a named buffer object
     * 
     * @param int $target Specifies the target to which the buffer object is bound,
     * which must be one of the buffer binding targets in the following table:
     * @param int $buffer Specifies the name of a buffer object.
     * 
     * @return void
     */ 
    function glBindBuffer(int $target, int $buffer) : void {};
 
    /**
     * delete named buffer objects
     * 
     * @param int $n Specifies the number of buffer objects to be deleted.
     * @param ?int ...$buffers 
     * 
     * @return void
     */ 
    function glDeleteBuffers(int $n, ?int ...$buffers) : void {};
 
    /**
     * generate buffer object names
     * 
     * @param int $n Specifies the number of buffer object names to be generated.
     * @param ?int &...$buffers 
     * 
     * @return void
     */ 
    function glGenBuffers(int $n, ?int &...$buffers) : void {};
 
    /**
     * determine if a name corresponds to a buffer object
     * 
     * @param int $buffer Specifies a value that may be the name of a buffer object.
     * 
     * @return bool
     */ 
    function glIsBuffer(int $buffer) : bool {};
 
    /**
     * release the mapping of a buffer object's data store into the client's address
     * space
     * 
     * @param int $target Specifies the target to which the buffer object is bound
     * for glUnmapBuffer, which must be one of the buffer binding targets in the
     * following table:
     * 
     * @return bool
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glStencilMaskSeparate(int $face, int $mask) : void {};
 
    /**
     * Attaches a shader object to a program object
     * 
     * @param int $program Specifies the program object to which a shader object
     * will be attached.
     * @param int $shader Specifies the shader object that is to be attached.
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glBindAttribLocation(int $program, int $index, string $name) : void {};
 
    /**
     * Compiles a shader object
     * 
     * @param int $shader Specifies the shader object to be compiled.
     * 
     * @return void
     */ 
    function glCompileShader(int $shader) : void {};
 
    /**
     * Creates a program object
     * @return int
     */ 
    function glCreateProgram() : int {};
 
    /**
     * Creates a shader object
     * 
     * @param int $type 
     * 
     * @return int
     */ 
    function glCreateShader(int $type) : int {};
 
    /**
     * Deletes a program object
     * 
     * @param int $program Specifies the program object to be deleted.
     * 
     * @return void
     */ 
    function glDeleteProgram(int $program) : void {};
 
    /**
     * Deletes a shader object
     * 
     * @param int $shader Specifies the shader object to be deleted.
     * 
     * @return void
     */ 
    function glDeleteShader(int $shader) : void {};
 
    /**
     * Detaches a shader object from a program object to which it is attached
     * 
     * @param int $program Specifies the program object from which to detach the
     * shader object.
     * @param int $shader Specifies the shader object to be detached.
     * 
     * @return void
     */ 
    function glDetachShader(int $program, int $shader) : void {};
 
    /**
     * glDisableVertexAttribArray
     * 
     * @param int $index 
     * 
     * @return void
     */ 
    function glDisableVertexAttribArray(int $index) : void {};
 
    /**
     * Enable or disable a generic vertex attribute
     *     array
     * 
     * @param int $index Specifies the index of the generic vertex attribute to be
     * enabled or disabled.
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glGetAttachedShaders(int $program, int $maxCount, int &$count, int &$shaders) : void {};
 
    /**
     * Returns the location of an attribute variable
     * 
     * @param int $program Specifies the program object to be queried.
     * @param string $name Points to a null terminated string containing the name of
     * the attribute variable whose location is to be queried.
     * 
     * @return int
     */ 
    function glGetAttribLocation(int $program, string $name) : int {};
 
    /**
     * glGetProgramiv
     * 
     * @param int $program 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetProgramiv(int $program, int $pname, int &$params) : void {};
 
    /**
     * Returns the information log for a program object
     * 
     * @PHP-GLFW: In the PHP extension this function directly returns the error
     * string instead of being passed by reference as an argument.
     * 
     * @param int $program Specifies the program object whose information log is to
     * be queried.
     * @param int $bufSize Specifies the size of the character buffer for storing
     * the returned information log.
     * 
     * @return string Returns the information log for the specified object.
     */ 
    function glGetProgramInfoLog(int $program, int $bufSize) : string {};
 
    /**
     * glGetShaderiv
     * 
     * @param int $shader 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
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
     * 
     * @return string Returns the information log for the specified object.
     */ 
    function glGetShaderInfoLog(int $shader, int $bufSize) : string {};
 
    /**
     * Returns the location of a uniform variable
     * 
     * @param int $program Specifies the program object to be queried.
     * @param string $name Points to a null terminated string containing the name of
     * the uniform variable whose location is to be queried.
     * 
     * @return int
     */ 
    function glGetUniformLocation(int $program, string $name) : int {};
 
    /**
     * glGetUniformfv
     * 
     * @param int $program 
     * @param int $location 
     * @param float &$params 
     * 
     * @return void
     */ 
    function glGetUniformfv(int $program, int $location, float &$params) : void {};
 
    /**
     * glGetUniformiv
     * 
     * @param int $program 
     * @param int $location 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetUniformiv(int $program, int $location, int &$params) : void {};
 
    /**
     * glGetVertexAttribdv
     * 
     * @param int $index 
     * @param int $pname 
     * @param float &$params 
     * 
     * @return void
     */ 
    function glGetVertexAttribdv(int $index, int $pname, float &$params) : void {};
 
    /**
     * glGetVertexAttribfv
     * 
     * @param int $index 
     * @param int $pname 
     * @param float &$params 
     * 
     * @return void
     */ 
    function glGetVertexAttribfv(int $index, int $pname, float &$params) : void {};
 
    /**
     * glGetVertexAttribiv
     * 
     * @param int $index 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetVertexAttribiv(int $index, int $pname, int &$params) : void {};
 
    /**
     * Determines if a name corresponds to a program object
     * 
     * @param int $program Specifies a potential program object.
     * 
     * @return bool
     */ 
    function glIsProgram(int $program) : bool {};
 
    /**
     * Determines if a name corresponds to a shader object
     * 
     * @param int $shader Specifies a potential shader object.
     * 
     * @return bool
     */ 
    function glIsShader(int $shader) : bool {};
 
    /**
     * Links a program object
     * 
     * @param int $program Specifies the handle of the program object to be linked.
     * 
     * @return void
     */ 
    function glLinkProgram(int $program) : void {};
 
    /**
     * Installs a program object as part of current rendering state
     * 
     * @param int $program Specifies the handle of the program object whose
     * executables are to be used as part of current rendering state.
     * 
     * @return void
     */ 
    function glUseProgram(int $program) : void {};
 
    /**
     * glUniform1f
     * 
     * @param int $location 
     * @param float $v0 
     * 
     * @return void
     */ 
    function glUniform1f(int $location, float $v0) : void {};
 
    /**
     * glUniform2f
     * 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * 
     * @return void
     */ 
    function glUniform2f(int $location, float $v0, float $v1) : void {};
 
    /**
     * glUniform3f
     * 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * @param float $v2 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glUniform4f(int $location, float $v0, float $v1, float $v2, float $v3) : void {};
 
    /**
     * glUniform1i
     * 
     * @param int $location 
     * @param int $v0 
     * 
     * @return void
     */ 
    function glUniform1i(int $location, int $v0) : void {};
 
    /**
     * glUniform2i
     * 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * 
     * @return void
     */ 
    function glUniform2i(int $location, int $v0, int $v1) : void {};
 
    /**
     * glUniform3i
     * 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glUniform4i(int $location, int $v0, int $v1, int $v2, int $v3) : void {};
 
    /**
     * glUniform1fv
     * 
     * @param int $location 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform1fv(int $location, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniform2fv
     * 
     * @param int $location 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform2fv(int $location, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniform3fv
     * 
     * @param int $location 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform3fv(int $location, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniform4fv
     * 
     * @param int $location 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform4fv(int $location, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniform1iv
     * 
     * @param int $location 
     * @param \GL\Buffer\IntBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform1iv(int $location, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glUniform2iv
     * 
     * @param int $location 
     * @param \GL\Buffer\IntBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform2iv(int $location, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glUniform3iv
     * 
     * @param int $location 
     * @param \GL\Buffer\IntBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform3iv(int $location, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glUniform4iv
     * 
     * @param int $location 
     * @param \GL\Buffer\IntBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform4iv(int $location, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix2fv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix2fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix3fv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix3fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix4fv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix4fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * Validates a program object
     * 
     * @param int $program Specifies the handle of the program object to be
     * validated.
     * 
     * @return void
     */ 
    function glValidateProgram(int $program) : void {};
 
    /**
     * glVertexAttrib1d
     * 
     * @param int $index 
     * @param float $x 
     * 
     * @return void
     */ 
    function glVertexAttrib1d(int $index, float $x) : void {};
 
    /**
     * glVertexAttrib1dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib1dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib1f
     * 
     * @param int $index 
     * @param float $x 
     * 
     * @return void
     */ 
    function glVertexAttrib1f(int $index, float $x) : void {};
 
    /**
     * glVertexAttrib1fv
     * 
     * @param int $index 
     * @param \GL\Buffer\FloatBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib1fv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib1s
     * 
     * @param int $index 
     * @param int $x 
     * 
     * @return void
     */ 
    function glVertexAttrib1s(int $index, int $x) : void {};
 
    /**
     * glVertexAttrib1sv
     * 
     * @param int $index 
     * @param \GL\Buffer\ShortBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib1sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib2d
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * 
     * @return void
     */ 
    function glVertexAttrib2d(int $index, float $x, float $y) : void {};
 
    /**
     * glVertexAttrib2dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib2dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib2f
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * 
     * @return void
     */ 
    function glVertexAttrib2f(int $index, float $x, float $y) : void {};
 
    /**
     * glVertexAttrib2fv
     * 
     * @param int $index 
     * @param \GL\Buffer\FloatBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib2fv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib2s
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * 
     * @return void
     */ 
    function glVertexAttrib2s(int $index, int $x, int $y) : void {};
 
    /**
     * glVertexAttrib2sv
     * 
     * @param int $index 
     * @param \GL\Buffer\ShortBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib2sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib3d
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * @param float $z 
     * 
     * @return void
     */ 
    function glVertexAttrib3d(int $index, float $x, float $y, float $z) : void {};
 
    /**
     * glVertexAttrib3dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib3dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib3f
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * @param float $z 
     * 
     * @return void
     */ 
    function glVertexAttrib3f(int $index, float $x, float $y, float $z) : void {};
 
    /**
     * glVertexAttrib3fv
     * 
     * @param int $index 
     * @param \GL\Buffer\FloatBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib3fv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib3s
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * @param int $z 
     * 
     * @return void
     */ 
    function glVertexAttrib3s(int $index, int $x, int $y, int $z) : void {};
 
    /**
     * glVertexAttrib3sv
     * 
     * @param int $index 
     * @param \GL\Buffer\ShortBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib3sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4Nbv
     * 
     * @param int $index 
     * @param \GL\Buffer\ByteBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib4Nbv(int $index, \GL\Buffer\ByteBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4Niv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib4Niv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4Nsv
     * 
     * @param int $index 
     * @param \GL\Buffer\ShortBuffer|array $v 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glVertexAttrib4Nub(int $index, int $x, int $y, int $z, int $w) : void {};
 
    /**
     * glVertexAttrib4Nubv
     * 
     * @param int $index 
     * @param \GL\Buffer\UbyteBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib4Nubv(int $index, \GL\Buffer\UbyteBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4Nuiv
     * 
     * @param int $index 
     * @param \GL\Buffer\UIntBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib4Nuiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4Nusv
     * 
     * @param int $index 
     * @param \GL\Buffer\UShortBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib4Nusv(int $index, \GL\Buffer\UShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4bv
     * 
     * @param int $index 
     * @param \GL\Buffer\ByteBuffer|array $v 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glVertexAttrib4d(int $index, float $x, float $y, float $z, float $w) : void {};
 
    /**
     * glVertexAttrib4dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glVertexAttrib4f(int $index, float $x, float $y, float $z, float $w) : void {};
 
    /**
     * glVertexAttrib4fv
     * 
     * @param int $index 
     * @param \GL\Buffer\FloatBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib4fv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4iv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glVertexAttrib4s(int $index, int $x, int $y, int $z, int $w) : void {};
 
    /**
     * glVertexAttrib4sv
     * 
     * @param int $index 
     * @param \GL\Buffer\ShortBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib4sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4ubv
     * 
     * @param int $index 
     * @param \GL\Buffer\UbyteBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib4ubv(int $index, \GL\Buffer\UbyteBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4uiv
     * 
     * @param int $index 
     * @param \GL\Buffer\UIntBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttrib4uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {};
 
    /**
     * glVertexAttrib4usv
     * 
     * @param int $index 
     * @param \GL\Buffer\UShortBuffer|array $v 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glVertexAttribPointer(int $index, int $size, int $type, bool $normalized, int $stride, int $offset) : void {};
 
    /**
     * glUniformMatrix2x3fv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix2x3fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix3x2fv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix3x2fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix2x4fv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix2x4fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix4x2fv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix4x2fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix3x4fv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix3x4fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix4x3fv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix4x3fv(int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glColorMaski
     * 
     * @param int $index 
     * @param bool $r 
     * @param bool $g 
     * @param bool $b 
     * @param bool $a 
     * 
     * @return void
     */ 
    function glColorMaski(int $index, bool $r, bool $g, bool $b, bool $a) : void {};
 
    /**
     * glGetBooleani_v
     * 
     * @param int $target 
     * @param int $index 
     * @param ?bool &...$data 
     * 
     * @return void
     */ 
    function glGetBooleani_v(int $target, int $index, ?bool &...$data) : void {};
 
    /**
     * glGetIntegeri_v
     * 
     * @param int $target 
     * @param int $index 
     * @param ?bool &...$data 
     * 
     * @return void
     */ 
    function glGetIntegeri_v(int $target, int $index, ?bool &...$data) : void {};
 
    /**
     * glEnablei
     * 
     * @param int $target 
     * @param int $index 
     * 
     * @return void
     */ 
    function glEnablei(int $target, int $index) : void {};
 
    /**
     * glDisablei
     * 
     * @param int $target 
     * @param int $index 
     * 
     * @return void
     */ 
    function glDisablei(int $target, int $index) : void {};
 
    /**
     * glIsEnabledi
     * 
     * @param int $target 
     * @param int $index 
     * 
     * @return bool
     */ 
    function glIsEnabledi(int $target, int $index) : bool {};
 
    /**
     * start transform feedback operation
     * 
     * @param int $primitiveMode Specify the output type of the primitives that will
     * be recorded into the buffer objects that are bound for transform feedback.
     * 
     * @return void
     */ 
    function glBeginTransformFeedback(int $primitiveMode) : void {};
 
    /**
     * glEndTransformFeedback
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glBindBufferBase(int $target, int $index, int $buffer) : void {};
 
    /**
     * specify whether data read via glReadPixels should be clamped
     * 
     * @param int $target Target for color clamping. target must be
     * <constant>GL_CLAMP_READ_COLOR</constant>.
     * @param int $clamp Specifies whether to apply color clamping. clamp must be
     * <constant>GL_TRUE</constant> or <constant>GL_FALSE</constant>.
     * 
     * @return void
     */ 
    function glClampColor(int $target, int $clamp) : void {};
 
    /**
     * start conditional rendering
     * 
     * @param int $id Specifies the name of an occlusion query object whose results
     * are used to determine if the rendering commands are discarded.
     * @param int $mode Specifies how glBeginConditionalRender interprets the
     * results of the occlusion query.
     * 
     * @return void
     */ 
    function glBeginConditionalRender(int $id, int $mode) : void {};
 
    /**
     * glEndConditionalRender
     * @return void
     */ 
    function glEndConditionalRender() : void {};
 
    /**
     * glGetVertexAttribIiv
     * 
     * @param int $index 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetVertexAttribIiv(int $index, int $pname, int &$params) : void {};
 
    /**
     * glGetVertexAttribIuiv
     * 
     * @param int $index 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetVertexAttribIuiv(int $index, int $pname, int &$params) : void {};
 
    /**
     * glVertexAttribI1i
     * 
     * @param int $index 
     * @param int $x 
     * 
     * @return void
     */ 
    function glVertexAttribI1i(int $index, int $x) : void {};
 
    /**
     * glVertexAttribI2i
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * 
     * @return void
     */ 
    function glVertexAttribI2i(int $index, int $x, int $y) : void {};
 
    /**
     * glVertexAttribI3i
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * @param int $z 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glVertexAttribI4i(int $index, int $x, int $y, int $z, int $w) : void {};
 
    /**
     * glVertexAttribI1ui
     * 
     * @param int $index 
     * @param int $x 
     * 
     * @return void
     */ 
    function glVertexAttribI1ui(int $index, int $x) : void {};
 
    /**
     * glVertexAttribI2ui
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * 
     * @return void
     */ 
    function glVertexAttribI2ui(int $index, int $x, int $y) : void {};
 
    /**
     * glVertexAttribI3ui
     * 
     * @param int $index 
     * @param int $x 
     * @param int $y 
     * @param int $z 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glVertexAttribI4ui(int $index, int $x, int $y, int $z, int $w) : void {};
 
    /**
     * glVertexAttribI1iv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribI1iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI2iv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribI2iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI3iv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribI3iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI4iv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribI4iv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI1uiv
     * 
     * @param int $index 
     * @param \GL\Buffer\UIntBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribI1uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI2uiv
     * 
     * @param int $index 
     * @param \GL\Buffer\UIntBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribI2uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI3uiv
     * 
     * @param int $index 
     * @param \GL\Buffer\UIntBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribI3uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI4uiv
     * 
     * @param int $index 
     * @param \GL\Buffer\UIntBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribI4uiv(int $index, \GL\Buffer\UIntBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI4bv
     * 
     * @param int $index 
     * @param \GL\Buffer\ByteBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribI4bv(int $index, \GL\Buffer\ByteBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI4sv
     * 
     * @param int $index 
     * @param \GL\Buffer\ShortBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribI4sv(int $index, \GL\Buffer\ShortBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI4ubv
     * 
     * @param int $index 
     * @param \GL\Buffer\UbyteBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribI4ubv(int $index, \GL\Buffer\UbyteBuffer|array $v) : void {};
 
    /**
     * glVertexAttribI4usv
     * 
     * @param int $index 
     * @param \GL\Buffer\UShortBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribI4usv(int $index, \GL\Buffer\UShortBuffer|array $v) : void {};
 
    /**
     * glGetUniformuiv
     * 
     * @param int $program 
     * @param int $location 
     * @param int &$params 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glBindFragDataLocation(int $program, int $color, string $name) : void {};
 
    /**
     * query the bindings of color numbers to user-defined varying out variables
     * 
     * @param int $program The name of the program containing varying out variable
     * whose binding to query
     * @param string $name The name of the user-defined varying out variable whose
     * binding to query
     * 
     * @return int
     */ 
    function glGetFragDataLocation(int $program, string $name) : int {};
 
    /**
     * glUniform1ui
     * 
     * @param int $location 
     * @param int $v0 
     * 
     * @return void
     */ 
    function glUniform1ui(int $location, int $v0) : void {};
 
    /**
     * glUniform2ui
     * 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * 
     * @return void
     */ 
    function glUniform2ui(int $location, int $v0, int $v1) : void {};
 
    /**
     * glUniform3ui
     * 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glUniform4ui(int $location, int $v0, int $v1, int $v2, int $v3) : void {};
 
    /**
     * glUniform1uiv
     * 
     * @param int $location 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform1uiv(int $location, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glUniform2uiv
     * 
     * @param int $location 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform2uiv(int $location, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glUniform3uiv
     * 
     * @param int $location 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform3uiv(int $location, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glUniform4uiv
     * 
     * @param int $location 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform4uiv(int $location, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glTexParameterIiv
     * 
     * @param int $target 
     * @param int $pname 
     * @param \GL\Buffer\IntBuffer|array $params 
     * 
     * @return void
     */ 
    function glTexParameterIiv(int $target, int $pname, \GL\Buffer\IntBuffer|array $params) : void {};
 
    /**
     * glTexParameterIuiv
     * 
     * @param int $target 
     * @param int $pname 
     * @param \GL\Buffer\UIntBuffer|array $params 
     * 
     * @return void
     */ 
    function glTexParameterIuiv(int $target, int $pname, \GL\Buffer\UIntBuffer|array $params) : void {};
 
    /**
     * glGetTexParameterIiv
     * 
     * @param int $target 
     * @param int $pname 
     * @param ?bool &...$params 
     * 
     * @return void
     */ 
    function glGetTexParameterIiv(int $target, int $pname, ?bool &...$params) : void {};
 
    /**
     * glGetTexParameterIuiv
     * 
     * @param int $target 
     * @param int $pname 
     * @param ?bool &...$params 
     * 
     * @return void
     */ 
    function glGetTexParameterIuiv(int $target, int $pname, ?bool &...$params) : void {};
 
    /**
     * glClearBufferiv
     * 
     * @param int $buffer 
     * @param int $drawbuffer 
     * @param \GL\Buffer\IntBuffer|array $value 
     * 
     * @return void
     */ 
    function glClearBufferiv(int $buffer, int $drawbuffer, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glClearBufferuiv
     * 
     * @param int $buffer 
     * @param int $drawbuffer 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glClearBufferuiv(int $buffer, int $drawbuffer, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glClearBufferfv
     * 
     * @param int $buffer 
     * @param int $drawbuffer 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glClearBufferfv(int $buffer, int $drawbuffer, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glClearBufferfi
     * 
     * @param int $buffer 
     * @param int $drawbuffer 
     * @param float $depth 
     * @param int $stencil 
     * 
     * @return void
     */ 
    function glClearBufferfi(int $buffer, int $drawbuffer, float $depth, int $stencil) : void {};
 
    /**
     * glGetStringi
     * 
     * @param int $name 
     * @param int $index 
     * 
     * @return string
     */ 
    function glGetStringi(int $name, int $index) : string {};
 
    /**
     * determine if a name corresponds to a renderbuffer object
     * 
     * @param int $renderbuffer Specifies a value that may be the name of a
     * renderbuffer object.
     * 
     * @return bool
     */ 
    function glIsRenderbuffer(int $renderbuffer) : bool {};
 
    /**
     * bind a renderbuffer to a renderbuffer target
     * 
     * @param int $target Specifies the renderbuffer target of the binding
     * operation. target must be <constant>GL_RENDERBUFFER</constant>.
     * @param int $renderbuffer Specifies the name of the renderbuffer object to
     * bind.
     * 
     * @return void
     */ 
    function glBindRenderbuffer(int $target, int $renderbuffer) : void {};
 
    /**
     * delete renderbuffer objects
     * 
     * @param int $n Specifies the number of renderbuffer objects to be deleted.
     * @param ?int ...$renderbuffers 
     * 
     * @return void
     */ 
    function glDeleteRenderbuffers(int $n, ?int ...$renderbuffers) : void {};
 
    /**
     * generate renderbuffer object names
     * 
     * @param int $n Specifies the number of renderbuffer object names to generate.
     * @param ?int &...$renderbuffers 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glRenderbufferStorage(int $target, int $internalformat, int $width, int $height) : void {};
 
    /**
     * glGetRenderbufferParameteriv
     * 
     * @param int $target 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetRenderbufferParameteriv(int $target, int $pname, int &$params) : void {};
 
    /**
     * determine if a name corresponds to a framebuffer object
     * 
     * @param int $framebuffer Specifies a value that may be the name of a
     * framebuffer object.
     * 
     * @return bool
     */ 
    function glIsFramebuffer(int $framebuffer) : bool {};
 
    /**
     * bind a framebuffer to a framebuffer target
     * 
     * @param int $target Specifies the framebuffer target of the binding operation.
     * @param int $framebuffer Specifies the name of the framebuffer object to bind.
     * 
     * @return void
     */ 
    function glBindFramebuffer(int $target, int $framebuffer) : void {};
 
    /**
     * delete framebuffer objects
     * 
     * @param int $n Specifies the number of framebuffer objects to be deleted.
     * @param ?int ...$framebuffers 
     * 
     * @return void
     */ 
    function glDeleteFramebuffers(int $n, ?int ...$framebuffers) : void {};
 
    /**
     * generate framebuffer object names
     * 
     * @param int $n Specifies the number of framebuffer object names to generate.
     * @param ?int &...$framebuffers 
     * 
     * @return void
     */ 
    function glGenFramebuffers(int $n, ?int &...$framebuffers) : void {};
 
    /**
     * check the completeness status of a framebuffer
     * 
     * @param int $target Specify the target to which the framebuffer is bound for
     * glCheckFramebufferStatus, and the target against which framebuffer
     * completeness of framebuffer is checked for glCheckNamedFramebufferStatus.
     * 
     * @return int
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glFlushMappedBufferRange(int $target, int $offset, int $length) : void {};
 
    /**
     * bind a vertex array object
     * 
     * @param int $array Specifies the name of the vertex array to bind.
     * 
     * @return void
     */ 
    function glBindVertexArray(int $array) : void {};
 
    /**
     * delete vertex array objects
     * 
     * @param int $n Specifies the number of vertex array objects to be deleted.
     * @param ?int ...$arrays 
     * 
     * @return void
     */ 
    function glDeleteVertexArrays(int $n, ?int ...$arrays) : void {};
 
    /**
     * generate vertex array object names
     * 
     * @param int $n Specifies the number of vertex array object names to generate.
     * @param ?int &...$arrays 
     * 
     * @return void
     */ 
    function glGenVertexArrays(int $n, ?int &...$arrays) : void {};
 
    /**
     * determine if a name corresponds to a vertex array object
     * 
     * @param int $array Specifies a value that may be the name of a vertex array
     * object.
     * 
     * @return bool
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glTexBuffer(int $target, int $internalformat, int $buffer) : void {};
 
    /**
     * specify the primitive restart index
     * 
     * @param int $index Specifies the value to be interpreted as the primitive
     * restart index.
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glCopyBufferSubData(int $readTarget, int $writeTarget, int $readOffset, int $writeOffset, int $size) : void {};
 
    /**
     * retrieve the index of a named uniform block
     * 
     * @param int $program Specifies the name of a program containing the uniform
     * block.
     * @param string $uniformBlockName Specifies the address an array of characters
     * to containing the name of the uniform block whose index to retrieve.
     * 
     * @return int
     */ 
    function glGetUniformBlockIndex(int $program, string $uniformBlockName) : int {};
 
    /**
     * glGetActiveUniformBlockiv
     * 
     * @param int $program 
     * @param int $uniformBlockIndex 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glUniformBlockBinding(int $program, int $uniformBlockIndex, int $uniformBlockBinding) : void {};
 
    /**
     * specifiy the vertex to be used as the source of data for flat shaded varyings
     * 
     * @param int $mode 
     * 
     * @return void
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
     * 
     * @return int
     */ 
    function glFenceSync(int $condition, int $flags) : int {};
 
    /**
     * determine if a name corresponds to a sync object
     * 
     * @param int $sync Specifies a value that may be the name of a sync object.
     * 
     * @return bool
     */ 
    function glIsSync(int $sync) : bool {};
 
    /**
     * delete a sync object
     * 
     * @param int $sync The sync object to be deleted.
     * 
     * @return void
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
     * 
     * @return int
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
     * 
     * @return void
     */ 
    function glWaitSync(int $sync, int $flags, int $timeout) : void {};
 
    /**
     * glGetInteger64v
     * 
     * @param int $pname 
     * @param int &$data 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glGetSynciv(int $sync, int $pname, int $count, int &$length, int &$values) : void {};
 
    /**
     * glGetInteger64i_v
     * 
     * @param int $target 
     * @param int $index 
     * @param int &$data 
     * 
     * @return void
     */ 
    function glGetInteger64i_v(int $target, int $index, int &$data) : void {};
 
    /**
     * glGetBufferParameteri64v
     * 
     * @param int $target 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glGetMultisamplefv(int $pname, int $index, float &$val) : void {};
 
    /**
     * set the value of a sub-word of the sample mask
     * 
     * @param int $maskNumber Specifies which 32-bit sub-word of the sample mask to
     * update.
     * @param int $mask Specifies the new value of the mask sub-word.
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glBindFragDataLocationIndexed(int $program, int $colorNumber, int $index, string $name) : void {};
 
    /**
     * query the bindings of color indices to user-defined varying out variables
     * 
     * @param int $program The name of the program containing varying out variable
     * whose binding to query
     * @param string $name The name of the user-defined varying out variable whose
     * index to query
     * 
     * @return int
     */ 
    function glGetFragDataIndex(int $program, string $name) : int {};
 
    /**
     * generate sampler object names
     * 
     * @param int $count 
     * @param ?int &...$samplers 
     * 
     * @return void
     */ 
    function glGenSamplers(int $count, ?int &...$samplers) : void {};
 
    /**
     * delete named sampler objects
     * 
     * @param int $count 
     * @param ?int ...$samplers 
     * 
     * @return void
     */ 
    function glDeleteSamplers(int $count, ?int ...$samplers) : void {};
 
    /**
     * determine if a name corresponds to a sampler object
     * 
     * @param int $sampler 
     * 
     * @return bool
     */ 
    function glIsSampler(int $sampler) : bool {};
 
    /**
     * bind a named sampler to a texturing target
     * 
     * @param int $unit Specifies the index of the texture unit to which the sampler
     * is bound.
     * @param int $sampler Specifies the name of a sampler.
     * 
     * @return void
     */ 
    function glBindSampler(int $unit, int $sampler) : void {};
 
    /**
     * glSamplerParameteri
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param int $param 
     * 
     * @return void
     */ 
    function glSamplerParameteri(int $sampler, int $pname, int $param) : void {};
 
    /**
     * glSamplerParameteriv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param \GL\Buffer\IntBuffer|array $param 
     * 
     * @return void
     */ 
    function glSamplerParameteriv(int $sampler, int $pname, \GL\Buffer\IntBuffer|array $param) : void {};
 
    /**
     * glSamplerParameterf
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param float $param 
     * 
     * @return void
     */ 
    function glSamplerParameterf(int $sampler, int $pname, float $param) : void {};
 
    /**
     * glSamplerParameterfv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param \GL\Buffer\FloatBuffer|array $param 
     * 
     * @return void
     */ 
    function glSamplerParameterfv(int $sampler, int $pname, \GL\Buffer\FloatBuffer|array $param) : void {};
 
    /**
     * glSamplerParameterIiv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param \GL\Buffer\IntBuffer|array $param 
     * 
     * @return void
     */ 
    function glSamplerParameterIiv(int $sampler, int $pname, \GL\Buffer\IntBuffer|array $param) : void {};
 
    /**
     * glSamplerParameterIuiv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param \GL\Buffer\UIntBuffer|array $param 
     * 
     * @return void
     */ 
    function glSamplerParameterIuiv(int $sampler, int $pname, \GL\Buffer\UIntBuffer|array $param) : void {};
 
    /**
     * glGetSamplerParameteriv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetSamplerParameteriv(int $sampler, int $pname, int &$params) : void {};
 
    /**
     * glGetSamplerParameterIiv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetSamplerParameterIiv(int $sampler, int $pname, int &$params) : void {};
 
    /**
     * glGetSamplerParameterfv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param float &$params 
     * 
     * @return void
     */ 
    function glGetSamplerParameterfv(int $sampler, int $pname, float &$params) : void {};
 
    /**
     * glGetSamplerParameterIuiv
     * 
     * @param int $sampler 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glQueryCounter(int $id, int $target) : void {};
 
    /**
     * glGetQueryObjecti64v
     * 
     * @param int $id 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetQueryObjecti64v(int $id, int $pname, int &$params) : void {};
 
    /**
     * glGetQueryObjectui64v
     * 
     * @param int $id 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetQueryObjectui64v(int $id, int $pname, int &$params) : void {};
 
    /**
     * modify the rate at which generic vertex attributes advance during instanced
     * rendering
     * 
     * @param int $index Specify the index of the generic vertex attribute.
     * @param int $divisor Specify the number of instances that will pass between
     * updates of the generic attribute at slot index.
     * 
     * @return void
     */ 
    function glVertexAttribDivisor(int $index, int $divisor) : void {};
 
    /**
     * glVertexAttribP1ui
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param int $value 
     * 
     * @return void
     */ 
    function glVertexAttribP1ui(int $index, int $type, bool $normalized, int $value) : void {};
 
    /**
     * glVertexAttribP1uiv
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glVertexAttribP1uiv(int $index, int $type, bool $normalized, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glVertexAttribP2ui
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param int $value 
     * 
     * @return void
     */ 
    function glVertexAttribP2ui(int $index, int $type, bool $normalized, int $value) : void {};
 
    /**
     * glVertexAttribP2uiv
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glVertexAttribP2uiv(int $index, int $type, bool $normalized, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glVertexAttribP3ui
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param int $value 
     * 
     * @return void
     */ 
    function glVertexAttribP3ui(int $index, int $type, bool $normalized, int $value) : void {};
 
    /**
     * glVertexAttribP3uiv
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glVertexAttribP3uiv(int $index, int $type, bool $normalized, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glVertexAttribP4ui
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param int $value 
     * 
     * @return void
     */ 
    function glVertexAttribP4ui(int $index, int $type, bool $normalized, int $value) : void {};
 
    /**
     * glVertexAttribP4uiv
     * 
     * @param int $index 
     * @param int $type 
     * @param bool $normalized 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glVertexAttribP4uiv(int $index, int $type, bool $normalized, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glVertexP2ui
     * 
     * @param int $type 
     * @param int $value 
     * 
     * @return void
     */ 
    function glVertexP2ui(int $type, int $value) : void {};
 
    /**
     * glVertexP2uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glVertexP2uiv(int $type, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glVertexP3ui
     * 
     * @param int $type 
     * @param int $value 
     * 
     * @return void
     */ 
    function glVertexP3ui(int $type, int $value) : void {};
 
    /**
     * glVertexP3uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glVertexP3uiv(int $type, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glVertexP4ui
     * 
     * @param int $type 
     * @param int $value 
     * 
     * @return void
     */ 
    function glVertexP4ui(int $type, int $value) : void {};
 
    /**
     * glVertexP4uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glVertexP4uiv(int $type, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glTexCoordP1ui
     * 
     * @param int $type 
     * @param int $coords 
     * 
     * @return void
     */ 
    function glTexCoordP1ui(int $type, int $coords) : void {};
 
    /**
     * glTexCoordP1uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords 
     * 
     * @return void
     */ 
    function glTexCoordP1uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glTexCoordP2ui
     * 
     * @param int $type 
     * @param int $coords 
     * 
     * @return void
     */ 
    function glTexCoordP2ui(int $type, int $coords) : void {};
 
    /**
     * glTexCoordP2uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords 
     * 
     * @return void
     */ 
    function glTexCoordP2uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glTexCoordP3ui
     * 
     * @param int $type 
     * @param int $coords 
     * 
     * @return void
     */ 
    function glTexCoordP3ui(int $type, int $coords) : void {};
 
    /**
     * glTexCoordP3uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords 
     * 
     * @return void
     */ 
    function glTexCoordP3uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glTexCoordP4ui
     * 
     * @param int $type 
     * @param int $coords 
     * 
     * @return void
     */ 
    function glTexCoordP4ui(int $type, int $coords) : void {};
 
    /**
     * glTexCoordP4uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords 
     * 
     * @return void
     */ 
    function glTexCoordP4uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glMultiTexCoordP1ui
     * 
     * @param int $texture 
     * @param int $type 
     * @param int $coords 
     * 
     * @return void
     */ 
    function glMultiTexCoordP1ui(int $texture, int $type, int $coords) : void {};
 
    /**
     * glMultiTexCoordP1uiv
     * 
     * @param int $texture 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords 
     * 
     * @return void
     */ 
    function glMultiTexCoordP1uiv(int $texture, int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glMultiTexCoordP2ui
     * 
     * @param int $texture 
     * @param int $type 
     * @param int $coords 
     * 
     * @return void
     */ 
    function glMultiTexCoordP2ui(int $texture, int $type, int $coords) : void {};
 
    /**
     * glMultiTexCoordP2uiv
     * 
     * @param int $texture 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords 
     * 
     * @return void
     */ 
    function glMultiTexCoordP2uiv(int $texture, int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glMultiTexCoordP3ui
     * 
     * @param int $texture 
     * @param int $type 
     * @param int $coords 
     * 
     * @return void
     */ 
    function glMultiTexCoordP3ui(int $texture, int $type, int $coords) : void {};
 
    /**
     * glMultiTexCoordP3uiv
     * 
     * @param int $texture 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords 
     * 
     * @return void
     */ 
    function glMultiTexCoordP3uiv(int $texture, int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glMultiTexCoordP4ui
     * 
     * @param int $texture 
     * @param int $type 
     * @param int $coords 
     * 
     * @return void
     */ 
    function glMultiTexCoordP4ui(int $texture, int $type, int $coords) : void {};
 
    /**
     * glMultiTexCoordP4uiv
     * 
     * @param int $texture 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords 
     * 
     * @return void
     */ 
    function glMultiTexCoordP4uiv(int $texture, int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glNormalP3ui
     * 
     * @param int $type 
     * @param int $coords 
     * 
     * @return void
     */ 
    function glNormalP3ui(int $type, int $coords) : void {};
 
    /**
     * glNormalP3uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $coords 
     * 
     * @return void
     */ 
    function glNormalP3uiv(int $type, \GL\Buffer\UIntBuffer|array $coords) : void {};
 
    /**
     * glColorP3ui
     * 
     * @param int $type 
     * @param int $color 
     * 
     * @return void
     */ 
    function glColorP3ui(int $type, int $color) : void {};
 
    /**
     * glColorP3uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $color 
     * 
     * @return void
     */ 
    function glColorP3uiv(int $type, \GL\Buffer\UIntBuffer|array $color) : void {};
 
    /**
     * glColorP4ui
     * 
     * @param int $type 
     * @param int $color 
     * 
     * @return void
     */ 
    function glColorP4ui(int $type, int $color) : void {};
 
    /**
     * glColorP4uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $color 
     * 
     * @return void
     */ 
    function glColorP4uiv(int $type, \GL\Buffer\UIntBuffer|array $color) : void {};
 
    /**
     * glSecondaryColorP3ui
     * 
     * @param int $type 
     * @param int $color 
     * 
     * @return void
     */ 
    function glSecondaryColorP3ui(int $type, int $color) : void {};
 
    /**
     * glSecondaryColorP3uiv
     * 
     * @param int $type 
     * @param \GL\Buffer\UIntBuffer|array $color 
     * 
     * @return void
     */ 
    function glSecondaryColorP3uiv(int $type, \GL\Buffer\UIntBuffer|array $color) : void {};
 
    /**
     * specifies minimum rate at which sample shading takes place
     * 
     * @param float $value Specifies the rate at which samples are shaded within
     * each covered pixel.
     * 
     * @return void
     */ 
    function glMinSampleShading(float $value) : void {};
 
    /**
     * glBlendEquationi
     * 
     * @param int $buf 
     * @param int $mode 
     * 
     * @return void
     */ 
    function glBlendEquationi(int $buf, int $mode) : void {};
 
    /**
     * glBlendEquationSeparatei
     * 
     * @param int $buf 
     * @param int $modeRGB 
     * @param int $modeAlpha 
     * 
     * @return void
     */ 
    function glBlendEquationSeparatei(int $buf, int $modeRGB, int $modeAlpha) : void {};
 
    /**
     * glBlendFunci
     * 
     * @param int $buf 
     * @param int $src 
     * @param int $dst 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glBlendFuncSeparatei(int $buf, int $srcRGB, int $dstRGB, int $srcAlpha, int $dstAlpha) : void {};
 
    /**
     * glUniform1d
     * 
     * @param int $location 
     * @param float $x 
     * 
     * @return void
     */ 
    function glUniform1d(int $location, float $x) : void {};
 
    /**
     * glUniform2d
     * 
     * @param int $location 
     * @param float $x 
     * @param float $y 
     * 
     * @return void
     */ 
    function glUniform2d(int $location, float $x, float $y) : void {};
 
    /**
     * glUniform3d
     * 
     * @param int $location 
     * @param float $x 
     * @param float $y 
     * @param float $z 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glUniform4d(int $location, float $x, float $y, float $z, float $w) : void {};
 
    /**
     * glUniform1dv
     * 
     * @param int $location 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform1dv(int $location, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniform2dv
     * 
     * @param int $location 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform2dv(int $location, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniform3dv
     * 
     * @param int $location 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform3dv(int $location, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniform4dv
     * 
     * @param int $location 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniform4dv(int $location, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix2dv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix2dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix3dv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix3dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix4dv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix4dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix2x3dv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix2x3dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix2x4dv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix2x4dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix3x2dv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix3x2dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix3x4dv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix3x4dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix4x2dv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix4x2dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glUniformMatrix4x3dv
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glUniformMatrix4x3dv(int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glGetUniformdv
     * 
     * @param int $program 
     * @param int $location 
     * @param float &$params 
     * 
     * @return void
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
     * 
     * @return int
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
     * 
     * @return int
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
     * 
     * @return void
     */ 
    function glGetActiveSubroutineUniformiv(int $program, int $shadertype, int $index, int $pname, int &$values) : void {};
 
    /**
     * glUniformSubroutinesuiv
     * 
     * @param int $shadertype 
     * @param \GL\Buffer\UIntBuffer|array $indices 
     * 
     * @return void
     */ 
    function glUniformSubroutinesuiv(int $shadertype, \GL\Buffer\UIntBuffer|array $indices) : void {};
 
    /**
     * glGetUniformSubroutineuiv
     * 
     * @param int $shadertype 
     * @param int $location 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetUniformSubroutineuiv(int $shadertype, int $location, int &$params) : void {};
 
    /**
     * glGetProgramStageiv
     * 
     * @param int $program 
     * @param int $shadertype 
     * @param int $pname 
     * @param int &$values 
     * 
     * @return void
     */ 
    function glGetProgramStageiv(int $program, int $shadertype, int $pname, int &$values) : void {};
 
    /**
     * glPatchParameteri
     * 
     * @param int $pname 
     * @param int $value 
     * 
     * @return void
     */ 
    function glPatchParameteri(int $pname, int $value) : void {};
 
    /**
     * glPatchParameterfv
     * 
     * @param int $pname 
     * @param \GL\Buffer\FloatBuffer|array $values 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glBindTransformFeedback(int $target, int $id) : void {};
 
    /**
     * delete transform feedback objects
     * 
     * @param int $n Specifies the number of transform feedback objects to delete.
     * @param ?int ...$ids 
     * 
     * @return void
     */ 
    function glDeleteTransformFeedbacks(int $n, ?int ...$ids) : void {};
 
    /**
     * reserve transform feedback object names
     * 
     * @param int $n Specifies the number of transform feedback object names to
     * reserve.
     * @param ?int &...$ids 
     * 
     * @return void
     */ 
    function glGenTransformFeedbacks(int $n, ?int &...$ids) : void {};
 
    /**
     * determine if a name corresponds to a transform feedback object
     * 
     * @param int $id Specifies a value that may be the name of a transform feedback
     * object.
     * 
     * @return bool
     */ 
    function glIsTransformFeedback(int $id) : bool {};
 
    /**
     * pause transform feedback operations
     * @return void
     */ 
    function glPauseTransformFeedback() : void {};
 
    /**
     * resume transform feedback operations
     * @return void
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
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glDrawTransformFeedbackStream(int $mode, int $id, int $stream) : void {};
 
    /**
     * glBeginQueryIndexed
     * 
     * @param int $target 
     * @param int $index 
     * @param int $id 
     * 
     * @return void
     */ 
    function glBeginQueryIndexed(int $target, int $index, int $id) : void {};
 
    /**
     * glEndQueryIndexed
     * 
     * @param int $target 
     * @param int $index 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glGetQueryIndexediv(int $target, int $index, int $pname, int &$params) : void {};
 
    /**
     * release resources consumed by the implementation's shader compiler
     * @return void
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
     * 
     * @return void
     */ 
    function glGetShaderPrecisionFormat(int $shadertype, int $precisiontype, int &$range, int &$precision) : void {};
 
    /**
     * glDepthRangef
     * 
     * @param float $n 
     * @param float $f 
     * 
     * @return void
     */ 
    function glDepthRangef(float $n, float $f) : void {};
 
    /**
     * glClearDepthf
     * 
     * @param float $d 
     * 
     * @return void
     */ 
    function glClearDepthf(float $d) : void {};
 
    /**
     * glProgramParameteri
     * 
     * @param int $program 
     * @param int $pname 
     * @param int $value 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glUseProgramStages(int $pipeline, int $stages, int $program) : void {};
 
    /**
     * set the active program object for a program pipeline object
     * 
     * @param int $pipeline Specifies the program pipeline object to set the active
     * program object for.
     * @param int $program Specifies the program object to set as the active program
     * pipeline object pipeline.
     * 
     * @return void
     */ 
    function glActiveShaderProgram(int $pipeline, int $program) : void {};
 
    /**
     * bind a program pipeline to the current context
     * 
     * @param int $pipeline Specifies the name of the pipeline object to bind to the
     * context.
     * 
     * @return void
     */ 
    function glBindProgramPipeline(int $pipeline) : void {};
 
    /**
     * delete program pipeline objects
     * 
     * @param int $n Specifies the number of program pipeline objects to delete.
     * @param ?int ...$pipelines 
     * 
     * @return void
     */ 
    function glDeleteProgramPipelines(int $n, ?int ...$pipelines) : void {};
 
    /**
     * reserve program pipeline object names
     * 
     * @param int $n Specifies the number of program pipeline object names to
     * reserve.
     * @param ?int &...$pipelines 
     * 
     * @return void
     */ 
    function glGenProgramPipelines(int $n, ?int &...$pipelines) : void {};
 
    /**
     * determine if a name corresponds to a program pipeline object
     * 
     * @param int $pipeline Specifies a value that may be the name of a program
     * pipeline object.
     * 
     * @return bool
     */ 
    function glIsProgramPipeline(int $pipeline) : bool {};
 
    /**
     * glGetProgramPipelineiv
     * 
     * @param int $pipeline 
     * @param int $pname 
     * @param int &$params 
     * 
     * @return void
     */ 
    function glGetProgramPipelineiv(int $pipeline, int $pname, int &$params) : void {};
 
    /**
     * glProgramUniform1i
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * 
     * @return void
     */ 
    function glProgramUniform1i(int $program, int $location, int $v0) : void {};
 
    /**
     * glProgramUniform1iv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\IntBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform1iv(int $program, int $location, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform1f
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * 
     * @return void
     */ 
    function glProgramUniform1f(int $program, int $location, float $v0) : void {};
 
    /**
     * glProgramUniform1fv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform1fv(int $program, int $location, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniform1d
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * 
     * @return void
     */ 
    function glProgramUniform1d(int $program, int $location, float $v0) : void {};
 
    /**
     * glProgramUniform1dv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform1dv(int $program, int $location, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniform1ui
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * 
     * @return void
     */ 
    function glProgramUniform1ui(int $program, int $location, int $v0) : void {};
 
    /**
     * glProgramUniform1uiv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform1uiv(int $program, int $location, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform2i
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * 
     * @return void
     */ 
    function glProgramUniform2i(int $program, int $location, int $v0, int $v1) : void {};
 
    /**
     * glProgramUniform2iv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\IntBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform2iv(int $program, int $location, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform2f
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * 
     * @return void
     */ 
    function glProgramUniform2f(int $program, int $location, float $v0, float $v1) : void {};
 
    /**
     * glProgramUniform2fv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform2fv(int $program, int $location, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniform2d
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * 
     * @return void
     */ 
    function glProgramUniform2d(int $program, int $location, float $v0, float $v1) : void {};
 
    /**
     * glProgramUniform2dv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform2dv(int $program, int $location, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniform2ui
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * 
     * @return void
     */ 
    function glProgramUniform2ui(int $program, int $location, int $v0, int $v1) : void {};
 
    /**
     * glProgramUniform2uiv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform2uiv(int $program, int $location, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform3i
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2 
     * 
     * @return void
     */ 
    function glProgramUniform3i(int $program, int $location, int $v0, int $v1, int $v2) : void {};
 
    /**
     * glProgramUniform3iv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\IntBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform3iv(int $program, int $location, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform3f
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * @param float $v2 
     * 
     * @return void
     */ 
    function glProgramUniform3f(int $program, int $location, float $v0, float $v1, float $v2) : void {};
 
    /**
     * glProgramUniform3fv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform3fv(int $program, int $location, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniform3d
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * @param float $v2 
     * 
     * @return void
     */ 
    function glProgramUniform3d(int $program, int $location, float $v0, float $v1, float $v2) : void {};
 
    /**
     * glProgramUniform3dv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform3dv(int $program, int $location, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniform3ui
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2 
     * 
     * @return void
     */ 
    function glProgramUniform3ui(int $program, int $location, int $v0, int $v1, int $v2) : void {};
 
    /**
     * glProgramUniform3uiv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform3uiv(int $program, int $location, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform4i
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2 
     * @param int $v3 
     * 
     * @return void
     */ 
    function glProgramUniform4i(int $program, int $location, int $v0, int $v1, int $v2, int $v3) : void {};
 
    /**
     * glProgramUniform4iv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\IntBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform4iv(int $program, int $location, \GL\Buffer\IntBuffer|array $value) : void {};
 
    /**
     * glProgramUniform4f
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * @param float $v2 
     * @param float $v3 
     * 
     * @return void
     */ 
    function glProgramUniform4f(int $program, int $location, float $v0, float $v1, float $v2, float $v3) : void {};
 
    /**
     * glProgramUniform4fv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform4fv(int $program, int $location, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniform4d
     * 
     * @param int $program 
     * @param int $location 
     * @param float $v0 
     * @param float $v1 
     * @param float $v2 
     * @param float $v3 
     * 
     * @return void
     */ 
    function glProgramUniform4d(int $program, int $location, float $v0, float $v1, float $v2, float $v3) : void {};
 
    /**
     * glProgramUniform4dv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform4dv(int $program, int $location, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniform4ui
     * 
     * @param int $program 
     * @param int $location 
     * @param int $v0 
     * @param int $v1 
     * @param int $v2 
     * @param int $v3 
     * 
     * @return void
     */ 
    function glProgramUniform4ui(int $program, int $location, int $v0, int $v1, int $v2, int $v3) : void {};
 
    /**
     * glProgramUniform4uiv
     * 
     * @param int $program 
     * @param int $location 
     * @param \GL\Buffer\UIntBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniform4uiv(int $program, int $location, \GL\Buffer\UIntBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix2fv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix2fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix3fv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix3fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix4fv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix4fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix2dv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix2dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix3dv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix3dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix4dv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix4dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix2x3fv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix2x3fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix3x2fv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix3x2fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix2x4fv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix2x4fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix4x2fv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix4x2fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix3x4fv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix3x4fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix4x3fv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\FloatBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix4x3fv(int $program, int $location, bool $transpose, \GL\Buffer\FloatBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix2x3dv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix2x3dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix3x2dv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix3x2dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix2x4dv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix2x4dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix4x2dv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix4x2dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix3x4dv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix3x4dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * glProgramUniformMatrix4x3dv
     * 
     * @param int $program 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Buffer\DoubleBuffer|array $value 
     * 
     * @return void
     */ 
    function glProgramUniformMatrix4x3dv(int $program, int $location, bool $transpose, \GL\Buffer\DoubleBuffer|array $value) : void {};
 
    /**
     * validate a program pipeline object against current GL state
     * 
     * @param int $pipeline Specifies the name of a program pipeline object to
     * validate.
     * 
     * @return void
     */ 
    function glValidateProgramPipeline(int $pipeline) : void {};
 
    /**
     * glVertexAttribL1d
     * 
     * @param int $index 
     * @param float $x 
     * 
     * @return void
     */ 
    function glVertexAttribL1d(int $index, float $x) : void {};
 
    /**
     * glVertexAttribL2d
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * 
     * @return void
     */ 
    function glVertexAttribL2d(int $index, float $x, float $y) : void {};
 
    /**
     * glVertexAttribL3d
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * @param float $z 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glVertexAttribL4d(int $index, float $x, float $y, float $z, float $w) : void {};
 
    /**
     * glVertexAttribL1dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribL1dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttribL2dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribL2dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttribL3dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribL3dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glVertexAttribL4dv
     * 
     * @param int $index 
     * @param \GL\Buffer\DoubleBuffer|array $v 
     * 
     * @return void
     */ 
    function glVertexAttribL4dv(int $index, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * glGetVertexAttribLdv
     * 
     * @param int $index 
     * @param int $pname 
     * @param float &$params 
     * 
     * @return void
     */ 
    function glGetVertexAttribLdv(int $index, int $pname, float &$params) : void {};
 
    /**
     * glViewportArrayv
     * 
     * @param int $first 
     * @param \GL\Buffer\FloatBuffer|array $v 
     * 
     * @return void
     */ 
    function glViewportArrayv(int $first, \GL\Buffer\FloatBuffer|array $v) : void {};
 
    /**
     * glViewportIndexedf
     * 
     * @param int $index 
     * @param float $x 
     * @param float $y 
     * @param float $w 
     * @param float $h 
     * 
     * @return void
     */ 
    function glViewportIndexedf(int $index, float $x, float $y, float $w, float $h) : void {};
 
    /**
     * glViewportIndexedfv
     * 
     * @param int $index 
     * @param \GL\Buffer\FloatBuffer|array $v 
     * 
     * @return void
     */ 
    function glViewportIndexedfv(int $index, \GL\Buffer\FloatBuffer|array $v) : void {};
 
    /**
     * glScissorArrayv
     * 
     * @param int $first 
     * @param \GL\Buffer\IntBuffer|array $v 
     * 
     * @return void
     */ 
    function glScissorArrayv(int $first, \GL\Buffer\IntBuffer|array $v) : void {};
 
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
     * 
     * @return void
     */ 
    function glScissorIndexed(int $index, int $left, int $bottom, int $width, int $height) : void {};
 
    /**
     * glScissorIndexedv
     * 
     * @param int $index 
     * @param \GL\Buffer\IntBuffer|array $v 
     * 
     * @return void
     */ 
    function glScissorIndexedv(int $index, \GL\Buffer\IntBuffer|array $v) : void {};
 
    /**
     * glDepthRangeArrayv
     * 
     * @param int $first 
     * @param \GL\Buffer\DoubleBuffer|array $v 
     * 
     * @return void
     */ 
    function glDepthRangeArrayv(int $first, \GL\Buffer\DoubleBuffer|array $v) : void {};
 
    /**
     * specify mapping of depth values from normalized device coordinates to window
     * coordinates for a specified viewport
     * 
     * @param int $index Specifies the index of the viewport whose depth range to
     * update.
     * @param float $n 
     * @param float $f 
     * 
     * @return void
     */ 
    function glDepthRangeIndexed(int $index, float $n, float $f) : void {};
 
    /**
     * glGetFloati_v
     * 
     * @param int $target 
     * @param int $index 
     * @param ?bool &...$data 
     * 
     * @return void
     */ 
    function glGetFloati_v(int $target, int $index, ?bool &...$data) : void {};
 
    /**
     * glGetDoublei_v
     * 
     * @param int $target 
     * @param int $index 
     * @param ?bool &...$data 
     * 
     * @return void
     */ 
    function glGetDoublei_v(int $target, int $index, ?bool &...$data) : void {};
 
    /**
     * glfwInit
     * @return int
     */ 
    function glfwInit() : int {};
 
    /**
     * glfwTerminate
     * @return void
     */ 
    function glfwTerminate() : void {};
 
    /**
     * glfwInitHint
     * 
     * @param int $hint 
     * @param int $value 
     * 
     * @return void
     */ 
    function glfwInitHint(int $hint, int $value) : void {};
 
    /**
     * glfwGetVersion
     * 
     * @param int &$major 
     * @param int &$minor 
     * @param int &$rev 
     * 
     * @return void
     */ 
    function glfwGetVersion(int &$major, int &$minor, int &$rev) : void {};
 
    /**
     * glfwGetVersionString
     * @return string
     */ 
    function glfwGetVersionString() : string {};
 
    /**
     * glfwGetPrimaryMonitor
     * @return GLFWmonitor
     */ 
    function glfwGetPrimaryMonitor() : GLFWmonitor {};
 
    /**
     * glfwGetMonitorPos
     * 
     * @param GLFWmonitor $monitor 
     * @param int &$xpos 
     * @param int &$ypos 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glfwGetMonitorWorkarea(GLFWmonitor $monitor, int &$xpos, int &$ypos, int &$width, int &$height) : void {};
 
    /**
     * glfwGetMonitorPhysicalSize
     * 
     * @param GLFWmonitor $monitor 
     * @param int &$widthMM 
     * @param int &$heightMM 
     * 
     * @return void
     */ 
    function glfwGetMonitorPhysicalSize(GLFWmonitor $monitor, int &$widthMM, int &$heightMM) : void {};
 
    /**
     * glfwGetMonitorContentScale
     * 
     * @param GLFWmonitor $monitor 
     * @param float &$xscale 
     * @param float &$yscale 
     * 
     * @return void
     */ 
    function glfwGetMonitorContentScale(GLFWmonitor $monitor, float &$xscale, float &$yscale) : void {};
 
    /**
     * glfwGetMonitorName
     * 
     * @param GLFWmonitor $monitor 
     * 
     * @return string
     */ 
    function glfwGetMonitorName(GLFWmonitor $monitor) : string {};
 
    /**
     * glfwSetGamma
     * 
     * @param GLFWmonitor $monitor 
     * @param float $gamma 
     * 
     * @return void
     */ 
    function glfwSetGamma(GLFWmonitor $monitor, float $gamma) : void {};
 
    /**
     * glfwDefaultWindowHints
     * @return void
     */ 
    function glfwDefaultWindowHints() : void {};
 
    /**
     * glfwWindowHint
     * 
     * @param int $hint 
     * @param int $value 
     * 
     * @return void
     */ 
    function glfwWindowHint(int $hint, int $value) : void {};
 
    /**
     * glfwWindowHintString
     * 
     * @param int $hint 
     * @param string $value 
     * 
     * @return void
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
     * 
     * @return GLFWwindow
     */ 
    function glfwCreateWindow(int $width, int $height, string $title, ?GLFWmonitor $monitor = NULL, ?GLFWwindow $share = NULL) : GLFWwindow {};
 
    /**
     * glfwDestroyWindow
     * 
     * @param GLFWwindow $window 
     * 
     * @return void
     */ 
    function glfwDestroyWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwWindowShouldClose
     * 
     * @param GLFWwindow $window 
     * 
     * @return int
     */ 
    function glfwWindowShouldClose(GLFWwindow $window) : int {};
 
    /**
     * glfwSetWindowShouldClose
     * 
     * @param GLFWwindow $window 
     * @param int $value 
     * 
     * @return void
     */ 
    function glfwSetWindowShouldClose(GLFWwindow $window, int $value) : void {};
 
    /**
     * glfwSetWindowTitle
     * 
     * @param GLFWwindow $window 
     * @param string $title 
     * 
     * @return void
     */ 
    function glfwSetWindowTitle(GLFWwindow $window, string $title) : void {};
 
    /**
     * glfwGetWindowPos
     * 
     * @param GLFWwindow $window 
     * @param int &$xpos 
     * @param int &$ypos 
     * 
     * @return void
     */ 
    function glfwGetWindowPos(GLFWwindow $window, int &$xpos, int &$ypos) : void {};
 
    /**
     * glfwSetWindowPos
     * 
     * @param GLFWwindow $window 
     * @param int $xpos 
     * @param int $ypos 
     * 
     * @return void
     */ 
    function glfwSetWindowPos(GLFWwindow $window, int $xpos, int $ypos) : void {};
 
    /**
     * glfwGetWindowSize
     * 
     * @param GLFWwindow $window 
     * @param int &$width 
     * @param int &$height 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glfwSetWindowSizeLimits(GLFWwindow $window, int $minwidth, int $minheight, int $maxwidth, int $maxheight) : void {};
 
    /**
     * glfwSetWindowAspectRatio
     * 
     * @param GLFWwindow $window 
     * @param int $numer 
     * @param int $denom 
     * 
     * @return void
     */ 
    function glfwSetWindowAspectRatio(GLFWwindow $window, int $numer, int $denom) : void {};
 
    /**
     * glfwSetWindowSize
     * 
     * @param GLFWwindow $window 
     * @param int $width 
     * @param int $height 
     * 
     * @return void
     */ 
    function glfwSetWindowSize(GLFWwindow $window, int $width, int $height) : void {};
 
    /**
     * glfwGetFramebufferSize
     * 
     * @param GLFWwindow $window 
     * @param int &$width 
     * @param int &$height 
     * 
     * @return void
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
     * 
     * @return void
     */ 
    function glfwGetWindowFrameSize(GLFWwindow $window, int &$left, int &$top, int &$right, int &$bottom) : void {};
 
    /**
     * glfwGetWindowContentScale
     * 
     * @param GLFWwindow $window 
     * @param float &$xscale 
     * @param float &$yscale 
     * 
     * @return void
     */ 
    function glfwGetWindowContentScale(GLFWwindow $window, float &$xscale, float &$yscale) : void {};
 
    /**
     * glfwGetWindowOpacity
     * 
     * @param GLFWwindow $window 
     * 
     * @return float
     */ 
    function glfwGetWindowOpacity(GLFWwindow $window) : float {};
 
    /**
     * glfwSetWindowOpacity
     * 
     * @param GLFWwindow $window 
     * @param float $opacity 
     * 
     * @return void
     */ 
    function glfwSetWindowOpacity(GLFWwindow $window, float $opacity) : void {};
 
    /**
     * glfwIconifyWindow
     * 
     * @param GLFWwindow $window 
     * 
     * @return void
     */ 
    function glfwIconifyWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwRestoreWindow
     * 
     * @param GLFWwindow $window 
     * 
     * @return void
     */ 
    function glfwRestoreWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwMaximizeWindow
     * 
     * @param GLFWwindow $window 
     * 
     * @return void
     */ 
    function glfwMaximizeWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwShowWindow
     * 
     * @param GLFWwindow $window 
     * 
     * @return void
     */ 
    function glfwShowWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwHideWindow
     * 
     * @param GLFWwindow $window 
     * 
     * @return void
     */ 
    function glfwHideWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwFocusWindow
     * 
     * @param GLFWwindow $window 
     * 
     * @return void
     */ 
    function glfwFocusWindow(GLFWwindow $window) : void {};
 
    /**
     * glfwRequestWindowAttention
     * 
     * @param GLFWwindow $window 
     * 
     * @return void
     */ 
    function glfwRequestWindowAttention(GLFWwindow $window) : void {};
 
    /**
     * glfwGetWindowMonitor
     * 
     * @param GLFWwindow $window 
     * 
     * @return GLFWmonitor
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
     * 
     * @return void
     */ 
    function glfwSetWindowMonitor(GLFWwindow $window, GLFWmonitor $monitor, int $xpos, int $ypos, int $width, int $height, int $refreshRate) : void {};
 
    /**
     * glfwGetWindowAttrib
     * 
     * @param GLFWwindow $window 
     * @param int $attrib 
     * 
     * @return int
     */ 
    function glfwGetWindowAttrib(GLFWwindow $window, int $attrib) : int {};
 
    /**
     * glfwSetWindowAttrib
     * 
     * @param GLFWwindow $window 
     * @param int $attrib 
     * @param int $value 
     * 
     * @return void
     */ 
    function glfwSetWindowAttrib(GLFWwindow $window, int $attrib, int $value) : void {};
 
    /**
     * glfwPollEvents
     * @return void
     */ 
    function glfwPollEvents() : void {};
 
    /**
     * glfwWaitEvents
     * @return void
     */ 
    function glfwWaitEvents() : void {};
 
    /**
     * glfwWaitEventsTimeout
     * 
     * @param float $timeout 
     * 
     * @return void
     */ 
    function glfwWaitEventsTimeout(float $timeout) : void {};
 
    /**
     * glfwPostEmptyEvent
     * @return void
     */ 
    function glfwPostEmptyEvent() : void {};
 
    /**
     * glfwGetInputMode
     * 
     * @param GLFWwindow $window 
     * @param int $mode 
     * 
     * @return int
     */ 
    function glfwGetInputMode(GLFWwindow $window, int $mode) : int {};
 
    /**
     * glfwSetInputMode
     * 
     * @param GLFWwindow $window 
     * @param int $mode 
     * @param int $value 
     * 
     * @return void
     */ 
    function glfwSetInputMode(GLFWwindow $window, int $mode, int $value) : void {};
 
    /**
     * glfwRawMouseMotionSupported
     * @return int
     */ 
    function glfwRawMouseMotionSupported() : int {};
 
    /**
     * glfwGetKeyName
     * 
     * @param int $key 
     * @param int $scancode 
     * 
     * @return string
     */ 
    function glfwGetKeyName(int $key, int $scancode) : string {};
 
    /**
     * glfwGetKeyScancode
     * 
     * @param int $key 
     * 
     * @return int
     */ 
    function glfwGetKeyScancode(int $key) : int {};
 
    /**
     * glfwGetKey
     * 
     * @param GLFWwindow $window 
     * @param int $key 
     * 
     * @return int
     */ 
    function glfwGetKey(GLFWwindow $window, int $key) : int {};
 
    /**
     * glfwGetMouseButton
     * 
     * @param GLFWwindow $window 
     * @param int $button 
     * 
     * @return int
     */ 
    function glfwGetMouseButton(GLFWwindow $window, int $button) : int {};
 
    /**
     * glfwGetCursorPos
     * 
     * @param GLFWwindow $window 
     * @param float &$xpos 
     * @param float &$ypos 
     * 
     * @return void
     */ 
    function glfwGetCursorPos(GLFWwindow $window, float &$xpos, float &$ypos) : void {};
 
    /**
     * glfwSetCursorPos
     * 
     * @param GLFWwindow $window 
     * @param float $xpos 
     * @param float $ypos 
     * 
     * @return void
     */ 
    function glfwSetCursorPos(GLFWwindow $window, float $xpos, float $ypos) : void {};
 
    /**
     * glfwCreateStandardCursor
     * 
     * @param int $shape 
     * 
     * @return GLFWcursor
     */ 
    function glfwCreateStandardCursor(int $shape) : GLFWcursor {};
 
    /**
     * glfwDestroyCursor
     * 
     * @param GLFWcursor $cursor 
     * 
     * @return void
     */ 
    function glfwDestroyCursor(GLFWcursor $cursor) : void {};
 
    /**
     * glfwSetCursor
     * 
     * @param GLFWwindow $window 
     * @param GLFWcursor $cursor 
     * 
     * @return void
     */ 
    function glfwSetCursor(GLFWwindow $window, GLFWcursor $cursor) : void {};
 
    /**
     * This function sets the key callback of the specified window, which is called
     * when a key is pressed, repeated or released.
     * 
     * Example: 
     * ```php
     * glfwSetKeyCallback($window, function($key, $scancode, $action, $mods)
     * use($window) {
     * 	if ($key == GLFW_KEY_ESCAPE && $action == GLFW_PRESS) {
     * 		glfwSetWindowShouldClose($window, GL_TRUE);
     * 	}
     * });
     * ```
     * 
     * The key functions deal with physical keys, with layout independent key tokens
     * named after their values in the standard US keyboard layout. If you want to
     * input text, use the character callback instead.
     * 
     * When a window loses input focus, it will generate synthetic key release
     * events for all pressed keys. You can tell these events from user-generated
     * events by the fact that the synthetic ones are generated after the focus loss
     * event has been processed, i.e. after the window focus callback has been
     * called.
     * 
     * The scancode of a key is specific to that platform or sometimes even to that
     * machine. Scancodes are intended to allow users to bind keys that don't have a
     * GLFW key token. Such keys have key set to GLFW_KEY_UNKNOWN, their state is
     * not saved and so it cannot be queried with glfwGetKey.
     * 
     * Sometimes GLFW needs to generate synthetic key events, in which case the
     * scancode may be zero.
     * 
     * @param GLFWwindow $window 
     * @param callable $callback 
     * 
     * @return void
     */ 
    function glfwSetKeyCallback(GLFWwindow $window, callable $callback) : void {};
 
    /**
     * This function sets the character callback of the specified window, which is
     * called when a Unicode character is input.
     * 
     * Example:
     * ```php
     * glfwSetCharCallback($window, function($codepoint) {
     *     echo "Character: " . mb_chr($codepoint) . PHP_EOL;
     * });
     * ```
     * 
     * The character callback is intended for Unicode text input. As it deals with
     * characters, it is keyboard layout dependent, whereas the key callback is not.
     * Characters do not map 1:1 to physical keys, as a key may produce zero, one or
     * more characters. If you want to know whether a specific physical key was
     * pressed or released, see the key callback instead.
     * 
     * The character callback behaves as system text input normally does and will
     * not be called if modifier keys are held down that would prevent normal text
     * input on that platform, for example a Super (Command) key on macOS or Alt key
     * on Windows.
     * 
     * 
     * @param GLFWwindow $window 
     * @param callable $callback 
     * 
     * @return void
     */ 
    function glfwSetCharCallback(GLFWwindow $window, callable $callback) : void {};
 
    /**
     * glfwJoystickPresent
     * 
     * @param int $jid 
     * 
     * @return int
     */ 
    function glfwJoystickPresent(int $jid) : int {};
 
    /**
     * glfwGetJoystickName
     * 
     * @param int $jid 
     * 
     * @return string
     */ 
    function glfwGetJoystickName(int $jid) : string {};
 
    /**
     * glfwGetJoystickGUID
     * 
     * @param int $jid 
     * 
     * @return string
     */ 
    function glfwGetJoystickGUID(int $jid) : string {};
 
    /**
     * glfwJoystickIsGamepad
     * 
     * @param int $jid 
     * 
     * @return int
     */ 
    function glfwJoystickIsGamepad(int $jid) : int {};
 
    /**
     * glfwUpdateGamepadMappings
     * 
     * @param string $string 
     * 
     * @return int
     */ 
    function glfwUpdateGamepadMappings(string $string) : int {};
 
    /**
     * glfwGetGamepadName
     * 
     * @param int $jid 
     * 
     * @return string
     */ 
    function glfwGetGamepadName(int $jid) : string {};
 
    /**
     * glfwSetClipboardString
     * 
     * @param GLFWwindow $window 
     * @param string $string 
     * 
     * @return void
     */ 
    function glfwSetClipboardString(GLFWwindow $window, string $string) : void {};
 
    /**
     * glfwGetClipboardString
     * 
     * @param GLFWwindow $window 
     * 
     * @return string
     */ 
    function glfwGetClipboardString(GLFWwindow $window) : string {};
 
    /**
     * glfwGetTime
     * @return float
     */ 
    function glfwGetTime() : float {};
 
    /**
     * glfwSetTime
     * 
     * @param float $time 
     * 
     * @return void
     */ 
    function glfwSetTime(float $time) : void {};
 
    /**
     * glfwMakeContextCurrent
     * 
     * @param GLFWwindow $window 
     * 
     * @return void
     */ 
    function glfwMakeContextCurrent(GLFWwindow $window) : void {};
 
    /**
     * glfwGetCurrentContext
     * @return GLFWwindow
     */ 
    function glfwGetCurrentContext() : GLFWwindow {};
 
    /**
     * glfwSwapBuffers
     * 
     * @param GLFWwindow $window 
     * 
     * @return void
     */ 
    function glfwSwapBuffers(GLFWwindow $window) : void {};
 
    /**
     * glfwSwapInterval
     * 
     * @param int $interval 
     * 
     * @return void
     */ 
    function glfwSwapInterval(int $interval) : void {};
 
    /**
     * glfwExtensionSupported
     * 
     * @param string $extension 
     * 
     * @return int
     */ 
    function glfwExtensionSupported(string $extension) : int {};
 
    /**
     * glfwVulkanSupported
     * @return int
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
     * 
     * @return void
     */ 
    function glShaderSource(int $shader, string $source) : void {};
 
    /**
     * creates and initializes a buffer object's data store
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
     * @PHP-GLFW: In the PHP extension this method has different signiture compared
     * to the original. 
     * Instead of passing byte size and a pointer to the function, in PHP you pass a
     * `GL\Buffer\BufferInterface` instance.
     * 
     * @param int $target Specifies the target to which the buffer object is bound
     * for glBufferData.
     * @param \GL\Buffer\BufferInterface $buffer Specifies a buffer object
     * containing the to be uploaded data.
     * @param int $usage Specifies the expected usage pattern of the data store. The
     * symbolic constant must be GL_STREAM_DRAW, GL_STREAM_READ, GL_STREAM_COPY,
     * GL_STATIC_DRAW, GL_STATIC_READ, GL_STATIC_COPY, GL_DYNAMIC_DRAW,
     * GL_DYNAMIC_READ, or GL_DYNAMIC_COPY.
     * 
     * @return void
     */ 
    function glBufferData(int $target, \GL\Buffer\BufferInterface $buffer, int $usage) : void {};
 
    /**
     * Sets a matrix (mat4x4) uniform value to the current shader program.
     * 
     * @PHP-GLFW: This method is specifc to the php extension and not part of the
     * original OpenGL API.
     * 
     * @param int $location 
     * @param bool $transpose 
     * @param \GL\Math\Mat4 $matrix 
     * 
     * @return void
     */ 
    function glUniformMatrix4f(int $location, bool $transpose, \GL\Math\Mat4 $matrix) : void {};
 
    /**
     * Sets a vector (vec2) uniform value to the current shader program.
     * 
     * @PHP-GLFW: This method is specifc to the php extension and not part of the
     * original OpenGL API.
     * 
     * @param int $location 
     * @param \GL\Math\Vec2 $vec 
     * 
     * @return void
     */ 
    function glUniformVec2f(int $location, \GL\Math\Vec2 $vec) : void {};
 
    /**
     * Sets a vector (vec3) uniform value to the current shader program.
     * 
     * @PHP-GLFW: This method is specifc to the php extension and not part of the
     * original OpenGL API.
     * 
     * @param int $location 
     * @param \GL\Math\Vec3 $vec 
     * 
     * @return void
     */ 
    function glUniformVec3f(int $location, \GL\Math\Vec3 $vec) : void {};
 
    /**
     * Sets a vector (vec4) uniform value to the current shader program.
     * 
     * @PHP-GLFW: This method is specifc to the php extension and not part of the
     * original OpenGL API.
     * 
     * @param int $location 
     * @param \GL\Math\Vec4 $vec 
     * 
     * @return void
     */ 
    function glUniformVec4f(int $location, \GL\Math\Vec4 $vec) : void {};
 
 


    /**
     * Constants
     * ----------------------------------------------------------------------------
     */
//define('a', 'stable');
//define('a', 'stable');
//define('a', 'stable');
//define('a', 'stable');
//define('a', 'stable');
//define('a', 'stable');
//define('a', 'stable');
//define('a', 'stable');
//define('a', 'stable');
//define('a', 'stable');
//define('a', 'stable');
    define('GL_DEPTH_BUFFER_BIT', 0x00000100);
    define('GL_STENCIL_BUFFER_BIT', 0x00000400);
    define('GL_COLOR_BUFFER_BIT', 0x00004000);
    define('GL_CURRENT_BIT', 0x00000001);
    define('GL_POINT_BIT', 0x00000002);
    define('GL_LINE_BIT', 0x00000004);
    define('GL_POLYGON_BIT', 0x00000008);
    define('GL_POLYGON_STIPPLE_BIT', 0x00000010);
    define('GL_PIXEL_MODE_BIT', 0x00000020);
    define('GL_LIGHTING_BIT', 0x00000040);
    define('GL_FOG_BIT', 0x00000080);
    define('GL_ACCUM_BUFFER_BIT', 0x00000200);
    define('GL_VIEWPORT_BIT', 0x00000800);
    define('GL_TRANSFORM_BIT', 0x00001000);
    define('GL_ENABLE_BIT', 0x00002000);
    define('GL_HINT_BIT', 0x00008000);
    define('GL_EVAL_BIT', 0x00010000);
    define('GL_LIST_BIT', 0x00020000);
    define('GL_TEXTURE_BIT', 0x00040000);
    define('GL_SCISSOR_BIT', 0x00080000);
    define('GL_ALL_ATTRIB_BITS', 0xFFFFFFFF);
    define('GL_MULTISAMPLE_BIT', 0x20000000);
    define('GL_FALSE', GL_FALSE);
    define('GL_TRUE', 1);
    define('GL_ZERO', GL_ZERO);
    define('GL_ONE', 1);
    define('GL_NONE', GL_NONE);
    define('GL_NO_ERROR', GL_NO_ERROR);
    define('GL_INVALID_INDEX', 0xFFFFFFFF);
    define('GL_TIMEOUT_IGNORED', 0xFFFFFFFFFFFFFFFF);
    define('GL_POINTS', 0x0000);
    define('GL_LINES', 0x0001);
    define('GL_LINE_LOOP', 0x0002);
    define('GL_LINE_STRIP', 0x0003);
    define('GL_TRIANGLES', 0x0004);
    define('GL_TRIANGLE_STRIP', 0x0005);
    define('GL_TRIANGLE_FAN', 0x0006);
    define('GL_QUADS', 0x0007);
    define('GL_NEVER', 0x0200);
    define('GL_LESS', 0x0201);
    define('GL_EQUAL', 0x0202);
    define('GL_LEQUAL', 0x0203);
    define('GL_GREATER', 0x0204);
    define('GL_NOTEQUAL', 0x0205);
    define('GL_GEQUAL', 0x0206);
    define('GL_ALWAYS', 0x0207);
    define('GL_SRC_COLOR', 0x0300);
    define('GL_ONE_MINUS_SRC_COLOR', 0x0301);
    define('GL_SRC_ALPHA', 0x0302);
    define('GL_ONE_MINUS_SRC_ALPHA', 0x0303);
    define('GL_DST_ALPHA', 0x0304);
    define('GL_ONE_MINUS_DST_ALPHA', 0x0305);
    define('GL_DST_COLOR', 0x0306);
    define('GL_ONE_MINUS_DST_COLOR', 0x0307);
    define('GL_SRC_ALPHA_SATURATE', 0x0308);
    define('GL_FRONT_LEFT', 0x0400);
    define('GL_FRONT_RIGHT', 0x0401);
    define('GL_BACK_LEFT', 0x0402);
    define('GL_BACK_RIGHT', 0x0403);
    define('GL_FRONT', 0x0404);
    define('GL_BACK', 0x0405);
    define('GL_LEFT', 0x0406);
    define('GL_RIGHT', 0x0407);
    define('GL_FRONT_AND_BACK', 0x0408);
    define('GL_INVALID_ENUM', 0x0500);
    define('GL_INVALID_VALUE', 0x0501);
    define('GL_INVALID_OPERATION', 0x0502);
    define('GL_OUT_OF_MEMORY', 0x0505);
    define('GL_CW', 0x0900);
    define('GL_CCW', 0x0901);
    define('GL_POINT_SIZE', 0x0B11);
    define('GL_POINT_SIZE_RANGE', 0x0B12);
    define('GL_POINT_SIZE_GRANULARITY', 0x0B13);
    define('GL_LINE_SMOOTH', 0x0B20);
    define('GL_LINE_WIDTH', 0x0B21);
    define('GL_LINE_WIDTH_RANGE', 0x0B22);
    define('GL_LINE_WIDTH_GRANULARITY', 0x0B23);
    define('GL_POLYGON_MODE', 0x0B40);
    define('GL_POLYGON_SMOOTH', 0x0B41);
    define('GL_CULL_FACE', 0x0B44);
    define('GL_CULL_FACE_MODE', 0x0B45);
    define('GL_FRONT_FACE', 0x0B46);
    define('GL_DEPTH_RANGE', 0x0B70);
    define('GL_DEPTH_TEST', 0x0B71);
    define('GL_DEPTH_WRITEMASK', 0x0B72);
    define('GL_DEPTH_CLEAR_VALUE', 0x0B73);
    define('GL_DEPTH_FUNC', 0x0B74);
    define('GL_STENCIL_TEST', 0x0B90);
    define('GL_STENCIL_CLEAR_VALUE', 0x0B91);
    define('GL_STENCIL_FUNC', 0x0B92);
    define('GL_STENCIL_VALUE_MASK', 0x0B93);
    define('GL_STENCIL_FAIL', 0x0B94);
    define('GL_STENCIL_PASS_DEPTH_FAIL', 0x0B95);
    define('GL_STENCIL_PASS_DEPTH_PASS', 0x0B96);
    define('GL_STENCIL_REF', 0x0B97);
    define('GL_STENCIL_WRITEMASK', 0x0B98);
    define('GL_VIEWPORT', 0x0BA2);
    define('GL_DITHER', 0x0BD0);
    define('GL_BLEND_DST', 0x0BE0);
    define('GL_BLEND_SRC', 0x0BE1);
    define('GL_BLEND', 0x0BE2);
    define('GL_LOGIC_OP_MODE', 0x0BF0);
    define('GL_DRAW_BUFFER', 0x0C01);
    define('GL_READ_BUFFER', 0x0C02);
    define('GL_SCISSOR_BOX', 0x0C10);
    define('GL_SCISSOR_TEST', 0x0C11);
    define('GL_COLOR_CLEAR_VALUE', 0x0C22);
    define('GL_COLOR_WRITEMASK', 0x0C23);
    define('GL_DOUBLEBUFFER', 0x0C32);
    define('GL_STEREO', 0x0C33);
    define('GL_LINE_SMOOTH_HINT', 0x0C52);
    define('GL_POLYGON_SMOOTH_HINT', 0x0C53);
    define('GL_UNPACK_SWAP_BYTES', 0x0CF0);
    define('GL_UNPACK_LSB_FIRST', 0x0CF1);
    define('GL_UNPACK_ROW_LENGTH', 0x0CF2);
    define('GL_UNPACK_SKIP_ROWS', 0x0CF3);
    define('GL_UNPACK_SKIP_PIXELS', 0x0CF4);
    define('GL_UNPACK_ALIGNMENT', 0x0CF5);
    define('GL_PACK_SWAP_BYTES', 0x0D00);
    define('GL_PACK_LSB_FIRST', 0x0D01);
    define('GL_PACK_ROW_LENGTH', 0x0D02);
    define('GL_PACK_SKIP_ROWS', 0x0D03);
    define('GL_PACK_SKIP_PIXELS', 0x0D04);
    define('GL_PACK_ALIGNMENT', 0x0D05);
    define('GL_MAX_TEXTURE_SIZE', 0x0D33);
    define('GL_MAX_VIEWPORT_DIMS', 0x0D3A);
    define('GL_SUBPIXEL_BITS', 0x0D50);
    define('GL_TEXTURE_1D', 0x0DE0);
    define('GL_TEXTURE_2D', 0x0DE1);
    define('GL_TEXTURE_WIDTH', 0x1000);
    define('GL_TEXTURE_HEIGHT', 0x1001);
    define('GL_TEXTURE_BORDER_COLOR', 0x1004);
    define('GL_DONT_CARE', 0x1100);
    define('GL_FASTEST', 0x1101);
    define('GL_NICEST', 0x1102);
    define('GL_BYTE', 0x1400);
    define('GL_UNSIGNED_BYTE', 0x1401);
    define('GL_SHORT', 0x1402);
    define('GL_UNSIGNED_SHORT', 0x1403);
    define('GL_INT', 0x1404);
    define('GL_UNSIGNED_INT', 0x1405);
    define('GL_FLOAT', 0x1406);
    define('GL_STACK_OVERFLOW', 0x0503);
    define('GL_STACK_UNDERFLOW', 0x0504);
    define('GL_CLEAR', 0x1500);
    define('GL_AND', 0x1501);
    define('GL_AND_REVERSE', 0x1502);
    define('GL_COPY', 0x1503);
    define('GL_AND_INVERTED', 0x1504);
    define('GL_NOOP', 0x1505);
    define('GL_XOR', 0x1506);
    define('GL_OR', 0x1507);
    define('GL_NOR', 0x1508);
    define('GL_EQUIV', 0x1509);
    define('GL_INVERT', 0x150A);
    define('GL_OR_REVERSE', 0x150B);
    define('GL_COPY_INVERTED', 0x150C);
    define('GL_OR_INVERTED', 0x150D);
    define('GL_NAND', 0x150E);
    define('GL_SET', 0x150F);
    define('GL_TEXTURE', 0x1702);
    define('GL_COLOR', 0x1800);
    define('GL_DEPTH', 0x1801);
    define('GL_STENCIL', 0x1802);
    define('GL_STENCIL_INDEX', 0x1901);
    define('GL_DEPTH_COMPONENT', 0x1902);
    define('GL_RED', 0x1903);
    define('GL_GREEN', 0x1904);
    define('GL_BLUE', 0x1905);
    define('GL_ALPHA', 0x1906);
    define('GL_RGB', 0x1907);
    define('GL_RGBA', 0x1908);
    define('GL_POINT', 0x1B00);
    define('GL_LINE', 0x1B01);
    define('GL_FILL', 0x1B02);
    define('GL_KEEP', 0x1E00);
    define('GL_REPLACE', 0x1E01);
    define('GL_INCR', 0x1E02);
    define('GL_DECR', 0x1E03);
    define('GL_VENDOR', 0x1F00);
    define('GL_RENDERER', 0x1F01);
    define('GL_VERSION', 0x1F02);
    define('GL_EXTENSIONS', 0x1F03);
    define('GL_NEAREST', 0x2600);
    define('GL_LINEAR', 0x2601);
    define('GL_NEAREST_MIPMAP_NEAREST', 0x2700);
    define('GL_LINEAR_MIPMAP_NEAREST', 0x2701);
    define('GL_NEAREST_MIPMAP_LINEAR', 0x2702);
    define('GL_LINEAR_MIPMAP_LINEAR', 0x2703);
    define('GL_TEXTURE_MAG_FILTER', 0x2800);
    define('GL_TEXTURE_MIN_FILTER', 0x2801);
    define('GL_TEXTURE_WRAP_S', 0x2802);
    define('GL_TEXTURE_WRAP_T', 0x2803);
    define('GL_REPEAT', 0x2901);
    define('GL_QUAD_STRIP', 0x0008);
    define('GL_POLYGON', 0x0009);
    define('GL_ACCUM', 0x0100);
    define('GL_LOAD', 0x0101);
    define('GL_RETURN', 0x0102);
    define('GL_MULT', 0x0103);
    define('GL_ADD', 0x0104);
    define('GL_AUX0', 0x0409);
    define('GL_AUX1', 0x040A);
    define('GL_AUX2', 0x040B);
    define('GL_AUX3', 0x040C);
    define('GL_2D', 0x0600);
    define('GL_3D', 0x0601);
    define('GL_3D_COLOR', 0x0602);
    define('GL_3D_COLOR_TEXTURE', 0x0603);
    define('GL_4D_COLOR_TEXTURE', 0x0604);
    define('GL_PASS_THROUGH_TOKEN', 0x0700);
    define('GL_POINT_TOKEN', 0x0701);
    define('GL_LINE_TOKEN', 0x0702);
    define('GL_POLYGON_TOKEN', 0x0703);
    define('GL_BITMAP_TOKEN', 0x0704);
    define('GL_DRAW_PIXEL_TOKEN', 0x0705);
    define('GL_COPY_PIXEL_TOKEN', 0x0706);
    define('GL_LINE_RESET_TOKEN', 0x0707);
    define('GL_EXP', 0x0800);
    define('GL_EXP2', 0x0801);
    define('GL_COEFF', 0x0A00);
    define('GL_ORDER', 0x0A01);
    define('GL_DOMAIN', 0x0A02);
    define('GL_PIXEL_MAP_I_TO_I', 0x0C70);
    define('GL_PIXEL_MAP_S_TO_S', 0x0C71);
    define('GL_PIXEL_MAP_I_TO_R', 0x0C72);
    define('GL_PIXEL_MAP_I_TO_G', 0x0C73);
    define('GL_PIXEL_MAP_I_TO_B', 0x0C74);
    define('GL_PIXEL_MAP_I_TO_A', 0x0C75);
    define('GL_PIXEL_MAP_R_TO_R', 0x0C76);
    define('GL_PIXEL_MAP_G_TO_G', 0x0C77);
    define('GL_PIXEL_MAP_B_TO_B', 0x0C78);
    define('GL_PIXEL_MAP_A_TO_A', 0x0C79);
    define('GL_CURRENT_COLOR', 0x0B00);
    define('GL_CURRENT_INDEX', 0x0B01);
    define('GL_CURRENT_NORMAL', 0x0B02);
    define('GL_CURRENT_TEXTURE_COORDS', 0x0B03);
    define('GL_CURRENT_RASTER_COLOR', 0x0B04);
    define('GL_CURRENT_RASTER_INDEX', 0x0B05);
    define('GL_CURRENT_RASTER_TEXTURE_COORDS', 0x0B06);
    define('GL_CURRENT_RASTER_POSITION', 0x0B07);
    define('GL_CURRENT_RASTER_POSITION_VALID', 0x0B08);
    define('GL_CURRENT_RASTER_DISTANCE', 0x0B09);
    define('GL_POINT_SMOOTH', 0x0B10);
    define('GL_LINE_STIPPLE', 0x0B24);
    define('GL_LINE_STIPPLE_PATTERN', 0x0B25);
    define('GL_LINE_STIPPLE_REPEAT', 0x0B26);
    define('GL_LIST_MODE', 0x0B30);
    define('GL_MAX_LIST_NESTING', 0x0B31);
    define('GL_LIST_BASE', 0x0B32);
    define('GL_LIST_INDEX', 0x0B33);
    define('GL_POLYGON_STIPPLE', 0x0B42);
    define('GL_EDGE_FLAG', 0x0B43);
    define('GL_LIGHTING', 0x0B50);
    define('GL_LIGHT_MODEL_LOCAL_VIEWER', 0x0B51);
    define('GL_LIGHT_MODEL_TWO_SIDE', 0x0B52);
    define('GL_LIGHT_MODEL_AMBIENT', 0x0B53);
    define('GL_SHADE_MODEL', 0x0B54);
    define('GL_COLOR_MATERIAL_FACE', 0x0B55);
    define('GL_COLOR_MATERIAL_PARAMETER', 0x0B56);
    define('GL_COLOR_MATERIAL', 0x0B57);
    define('GL_FOG', 0x0B60);
    define('GL_FOG_INDEX', 0x0B61);
    define('GL_FOG_DENSITY', 0x0B62);
    define('GL_FOG_START', 0x0B63);
    define('GL_FOG_END', 0x0B64);
    define('GL_FOG_MODE', 0x0B65);
    define('GL_FOG_COLOR', 0x0B66);
    define('GL_ACCUM_CLEAR_VALUE', 0x0B80);
    define('GL_MATRIX_MODE', 0x0BA0);
    define('GL_NORMALIZE', 0x0BA1);
    define('GL_MODELVIEW_STACK_DEPTH', 0x0BA3);
    define('GL_PROJECTION_STACK_DEPTH', 0x0BA4);
    define('GL_TEXTURE_STACK_DEPTH', 0x0BA5);
    define('GL_MODELVIEW_MATRIX', 0x0BA6);
    define('GL_PROJECTION_MATRIX', 0x0BA7);
    define('GL_TEXTURE_MATRIX', 0x0BA8);
    define('GL_ATTRIB_STACK_DEPTH', 0x0BB0);
    define('GL_ALPHA_TEST', 0x0BC0);
    define('GL_ALPHA_TEST_FUNC', 0x0BC1);
    define('GL_ALPHA_TEST_REF', 0x0BC2);
    define('GL_LOGIC_OP', 0x0BF1);
    define('GL_AUX_BUFFERS', 0x0C00);
    define('GL_INDEX_CLEAR_VALUE', 0x0C20);
    define('GL_INDEX_WRITEMASK', 0x0C21);
    define('GL_INDEX_MODE', 0x0C30);
    define('GL_RGBA_MODE', 0x0C31);
    define('GL_RENDER_MODE', 0x0C40);
    define('GL_PERSPECTIVE_CORRECTION_HINT', 0x0C50);
    define('GL_POINT_SMOOTH_HINT', 0x0C51);
    define('GL_FOG_HINT', 0x0C54);
    define('GL_TEXTURE_GEN_S', 0x0C60);
    define('GL_TEXTURE_GEN_T', 0x0C61);
    define('GL_TEXTURE_GEN_R', 0x0C62);
    define('GL_TEXTURE_GEN_Q', 0x0C63);
    define('GL_PIXEL_MAP_I_TO_I_SIZE', 0x0CB0);
    define('GL_PIXEL_MAP_S_TO_S_SIZE', 0x0CB1);
    define('GL_PIXEL_MAP_I_TO_R_SIZE', 0x0CB2);
    define('GL_PIXEL_MAP_I_TO_G_SIZE', 0x0CB3);
    define('GL_PIXEL_MAP_I_TO_B_SIZE', 0x0CB4);
    define('GL_PIXEL_MAP_I_TO_A_SIZE', 0x0CB5);
    define('GL_PIXEL_MAP_R_TO_R_SIZE', 0x0CB6);
    define('GL_PIXEL_MAP_G_TO_G_SIZE', 0x0CB7);
    define('GL_PIXEL_MAP_B_TO_B_SIZE', 0x0CB8);
    define('GL_PIXEL_MAP_A_TO_A_SIZE', 0x0CB9);
    define('GL_MAP_COLOR', 0x0D10);
    define('GL_MAP_STENCIL', 0x0D11);
    define('GL_INDEX_SHIFT', 0x0D12);
    define('GL_INDEX_OFFSET', 0x0D13);
    define('GL_RED_SCALE', 0x0D14);
    define('GL_RED_BIAS', 0x0D15);
    define('GL_ZOOM_X', 0x0D16);
    define('GL_ZOOM_Y', 0x0D17);
    define('GL_GREEN_SCALE', 0x0D18);
    define('GL_GREEN_BIAS', 0x0D19);
    define('GL_BLUE_SCALE', 0x0D1A);
    define('GL_BLUE_BIAS', 0x0D1B);
    define('GL_ALPHA_SCALE', 0x0D1C);
    define('GL_ALPHA_BIAS', 0x0D1D);
    define('GL_DEPTH_SCALE', 0x0D1E);
    define('GL_DEPTH_BIAS', 0x0D1F);
    define('GL_MAX_EVAL_ORDER', 0x0D30);
    define('GL_MAX_LIGHTS', 0x0D31);
    define('GL_MAX_CLIP_PLANES', 0x0D32);
    define('GL_MAX_PIXEL_MAP_TABLE', 0x0D34);
    define('GL_MAX_ATTRIB_STACK_DEPTH', 0x0D35);
    define('GL_MAX_MODELVIEW_STACK_DEPTH', 0x0D36);
    define('GL_MAX_NAME_STACK_DEPTH', 0x0D37);
    define('GL_MAX_PROJECTION_STACK_DEPTH', 0x0D38);
    define('GL_MAX_TEXTURE_STACK_DEPTH', 0x0D39);
    define('GL_INDEX_BITS', 0x0D51);
    define('GL_RED_BITS', 0x0D52);
    define('GL_GREEN_BITS', 0x0D53);
    define('GL_BLUE_BITS', 0x0D54);
    define('GL_ALPHA_BITS', 0x0D55);
    define('GL_DEPTH_BITS', 0x0D56);
    define('GL_STENCIL_BITS', 0x0D57);
    define('GL_ACCUM_RED_BITS', 0x0D58);
    define('GL_ACCUM_GREEN_BITS', 0x0D59);
    define('GL_ACCUM_BLUE_BITS', 0x0D5A);
    define('GL_ACCUM_ALPHA_BITS', 0x0D5B);
    define('GL_NAME_STACK_DEPTH', 0x0D70);
    define('GL_AUTO_NORMAL', 0x0D80);
    define('GL_MAP1_COLOR_4', 0x0D90);
    define('GL_MAP1_INDEX', 0x0D91);
    define('GL_MAP1_NORMAL', 0x0D92);
    define('GL_MAP1_TEXTURE_COORD_1', 0x0D93);
    define('GL_MAP1_TEXTURE_COORD_2', 0x0D94);
    define('GL_MAP1_TEXTURE_COORD_3', 0x0D95);
    define('GL_MAP1_TEXTURE_COORD_4', 0x0D96);
    define('GL_MAP1_VERTEX_3', 0x0D97);
    define('GL_MAP1_VERTEX_4', 0x0D98);
    define('GL_MAP2_COLOR_4', 0x0DB0);
    define('GL_MAP2_INDEX', 0x0DB1);
    define('GL_MAP2_NORMAL', 0x0DB2);
    define('GL_MAP2_TEXTURE_COORD_1', 0x0DB3);
    define('GL_MAP2_TEXTURE_COORD_2', 0x0DB4);
    define('GL_MAP2_TEXTURE_COORD_3', 0x0DB5);
    define('GL_MAP2_TEXTURE_COORD_4', 0x0DB6);
    define('GL_MAP2_VERTEX_3', 0x0DB7);
    define('GL_MAP2_VERTEX_4', 0x0DB8);
    define('GL_MAP1_GRID_DOMAIN', 0x0DD0);
    define('GL_MAP1_GRID_SEGMENTS', 0x0DD1);
    define('GL_MAP2_GRID_DOMAIN', 0x0DD2);
    define('GL_MAP2_GRID_SEGMENTS', 0x0DD3);
    define('GL_TEXTURE_COMPONENTS', 0x1003);
    define('GL_TEXTURE_BORDER', 0x1005);
    define('GL_AMBIENT', 0x1200);
    define('GL_DIFFUSE', 0x1201);
    define('GL_SPECULAR', 0x1202);
    define('GL_POSITION', 0x1203);
    define('GL_SPOT_DIRECTION', 0x1204);
    define('GL_SPOT_EXPONENT', 0x1205);
    define('GL_SPOT_CUTOFF', 0x1206);
    define('GL_CONSTANT_ATTENUATION', 0x1207);
    define('GL_LINEAR_ATTENUATION', 0x1208);
    define('GL_QUADRATIC_ATTENUATION', 0x1209);
    define('GL_COMPILE', 0x1300);
    define('GL_COMPILE_AND_EXECUTE', 0x1301);
    define('GL_2_BYTES', 0x1407);
    define('GL_3_BYTES', 0x1408);
    define('GL_4_BYTES', 0x1409);
    define('GL_EMISSION', 0x1600);
    define('GL_SHININESS', 0x1601);
    define('GL_AMBIENT_AND_DIFFUSE', 0x1602);
    define('GL_COLOR_INDEXES', 0x1603);
    define('GL_MODELVIEW', 0x1700);
    define('GL_PROJECTION', 0x1701);
    define('GL_COLOR_INDEX', 0x1900);
    define('GL_LUMINANCE', 0x1909);
    define('GL_LUMINANCE_ALPHA', 0x190A);
    define('GL_BITMAP', 0x1A00);
    define('GL_RENDER', 0x1C00);
    define('GL_FEEDBACK', 0x1C01);
    define('GL_SELECT', 0x1C02);
    define('GL_FLAT', 0x1D00);
    define('GL_SMOOTH', 0x1D01);
    define('GL_S', 0x2000);
    define('GL_T', 0x2001);
    define('GL_R', 0x2002);
    define('GL_Q', 0x2003);
    define('GL_MODULATE', 0x2100);
    define('GL_DECAL', 0x2101);
    define('GL_TEXTURE_ENV_MODE', 0x2200);
    define('GL_TEXTURE_ENV_COLOR', 0x2201);
    define('GL_TEXTURE_ENV', 0x2300);
    define('GL_EYE_LINEAR', 0x2400);
    define('GL_OBJECT_LINEAR', 0x2401);
    define('GL_SPHERE_MAP', 0x2402);
    define('GL_TEXTURE_GEN_MODE', 0x2500);
    define('GL_OBJECT_PLANE', 0x2501);
    define('GL_EYE_PLANE', 0x2502);
    define('GL_CLAMP', 0x2900);
    define('GL_CLIP_PLANE0', 0x3000);
    define('GL_CLIP_PLANE1', 0x3001);
    define('GL_CLIP_PLANE2', 0x3002);
    define('GL_CLIP_PLANE3', 0x3003);
    define('GL_CLIP_PLANE4', 0x3004);
    define('GL_CLIP_PLANE5', 0x3005);
    define('GL_LIGHT0', 0x4000);
    define('GL_LIGHT1', 0x4001);
    define('GL_LIGHT2', 0x4002);
    define('GL_LIGHT3', 0x4003);
    define('GL_LIGHT4', 0x4004);
    define('GL_LIGHT5', 0x4005);
    define('GL_LIGHT6', 0x4006);
    define('GL_LIGHT7', 0x4007);
    define('GL_COLOR_LOGIC_OP', 0x0BF2);
    define('GL_POLYGON_OFFSET_UNITS', 0x2A00);
    define('GL_POLYGON_OFFSET_POINT', 0x2A01);
    define('GL_POLYGON_OFFSET_LINE', 0x2A02);
    define('GL_TEXTURE_INTERNAL_FORMAT', 0x1003);
    define('GL_DOUBLE', 0x140A);
    define('GL_R3_G3_B2', 0x2A10);
    define('GL_FEEDBACK_BUFFER_POINTER', 0x0DF0);
    define('GL_SELECTION_BUFFER_POINTER', 0x0DF3);
    define('GL_CLIENT_ATTRIB_STACK_DEPTH', 0x0BB1);
    define('GL_INDEX_LOGIC_OP', 0x0BF1);
    define('GL_MAX_CLIENT_ATTRIB_STACK_DEPTH', 0x0D3B);
    define('GL_FEEDBACK_BUFFER_SIZE', 0x0DF1);
    define('GL_FEEDBACK_BUFFER_TYPE', 0x0DF2);
    define('GL_SELECTION_BUFFER_SIZE', 0x0DF4);
    define('GL_V2F', 0x2A20);
    define('GL_V3F', 0x2A21);
    define('GL_C4UB_V2F', 0x2A22);
    define('GL_C4UB_V3F', 0x2A23);
    define('GL_C3F_V3F', 0x2A24);
    define('GL_N3F_V3F', 0x2A25);
    define('GL_C4F_N3F_V3F', 0x2A26);
    define('GL_T2F_V3F', 0x2A27);
    define('GL_T4F_V4F', 0x2A28);
    define('GL_T2F_C4UB_V3F', 0x2A29);
    define('GL_T2F_C3F_V3F', 0x2A2A);
    define('GL_T2F_N3F_V3F', 0x2A2B);
    define('GL_T2F_C4F_N3F_V3F', 0x2A2C);
    define('GL_T4F_C4F_N3F_V4F', 0x2A2D);
    define('GL_SMOOTH_POINT_SIZE_RANGE', 0x0B12);
    define('GL_SMOOTH_POINT_SIZE_GRANULARITY', 0x0B13);
    define('GL_SMOOTH_LINE_WIDTH_RANGE', 0x0B22);
    define('GL_SMOOTH_LINE_WIDTH_GRANULARITY', 0x0B23);
    define('GL_CLIP_DISTANCE0', 0x3000);
    define('GL_CLIP_DISTANCE1', 0x3001);
    define('GL_CLIP_DISTANCE2', 0x3002);
    define('GL_CLIP_DISTANCE3', 0x3003);
    define('GL_CLIP_DISTANCE4', 0x3004);
    define('GL_CLIP_DISTANCE5', 0x3005);
    define('GL_CLIP_DISTANCE6', 0x3006);
    define('GL_CLIP_DISTANCE7', 0x3007);
    define('GL_MAX_CLIP_DISTANCES', 0x0D32);
    define('GL_INVALID_FRAMEBUFFER_OPERATION', 0x0506);
    define('GL_HALF_FLOAT', 0x140B);
    define('GL_LINES_ADJACENCY', 0x000A);
    define('GL_LINE_STRIP_ADJACENCY', 0x000B);
    define('GL_TRIANGLES_ADJACENCY', 0x000C);
    define('GL_TRIANGLE_STRIP_ADJACENCY', 0x000D);
    define('GL_PATCHES', 0x000E);
    define('GL_FIXED', 0x140C);
    define('GL_POLYGON_OFFSET_FILL', 0x8037);
    define('GL_POLYGON_OFFSET_FACTOR', 0x8038);
    define('GL_TEXTURE_BINDING_1D', 0x8068);
    define('GL_TEXTURE_BINDING_2D', 0x8069);
    define('GL_TEXTURE_RED_SIZE', 0x805C);
    define('GL_TEXTURE_GREEN_SIZE', 0x805D);
    define('GL_TEXTURE_BLUE_SIZE', 0x805E);
    define('GL_TEXTURE_ALPHA_SIZE', 0x805F);
    define('GL_PROXY_TEXTURE_1D', 0x8063);
    define('GL_PROXY_TEXTURE_2D', 0x8064);
    define('GL_RGB4', 0x804F);
    define('GL_RGB5', 0x8050);
    define('GL_RGB8', 0x8051);
    define('GL_RGB10', 0x8052);
    define('GL_RGB12', 0x8053);
    define('GL_RGB16', 0x8054);
    define('GL_RGBA2', 0x8055);
    define('GL_RGBA4', 0x8056);
    define('GL_RGB5_A1', 0x8057);
    define('GL_RGBA8', 0x8058);
    define('GL_RGB10_A2', 0x8059);
    define('GL_RGBA12', 0x805A);
    define('GL_RGBA16', 0x805B);
    define('GL_VERTEX_ARRAY_POINTER', 0x808E);
    define('GL_NORMAL_ARRAY_POINTER', 0x808F);
    define('GL_COLOR_ARRAY_POINTER', 0x8090);
    define('GL_INDEX_ARRAY_POINTER', 0x8091);
    define('GL_TEXTURE_COORD_ARRAY_POINTER', 0x8092);
    define('GL_EDGE_FLAG_ARRAY_POINTER', 0x8093);
    define('GL_VERTEX_ARRAY', 0x8074);
    define('GL_NORMAL_ARRAY', 0x8075);
    define('GL_COLOR_ARRAY', 0x8076);
    define('GL_INDEX_ARRAY', 0x8077);
    define('GL_TEXTURE_COORD_ARRAY', 0x8078);
    define('GL_EDGE_FLAG_ARRAY', 0x8079);
    define('GL_VERTEX_ARRAY_SIZE', 0x807A);
    define('GL_VERTEX_ARRAY_TYPE', 0x807B);
    define('GL_VERTEX_ARRAY_STRIDE', 0x807C);
    define('GL_NORMAL_ARRAY_TYPE', 0x807E);
    define('GL_NORMAL_ARRAY_STRIDE', 0x807F);
    define('GL_COLOR_ARRAY_SIZE', 0x8081);
    define('GL_COLOR_ARRAY_TYPE', 0x8082);
    define('GL_COLOR_ARRAY_STRIDE', 0x8083);
    define('GL_INDEX_ARRAY_TYPE', 0x8085);
    define('GL_INDEX_ARRAY_STRIDE', 0x8086);
    define('GL_TEXTURE_COORD_ARRAY_SIZE', 0x8088);
    define('GL_TEXTURE_COORD_ARRAY_TYPE', 0x8089);
    define('GL_TEXTURE_COORD_ARRAY_STRIDE', 0x808A);
    define('GL_EDGE_FLAG_ARRAY_STRIDE', 0x808C);
    define('GL_TEXTURE_LUMINANCE_SIZE', 0x8060);
    define('GL_TEXTURE_INTENSITY_SIZE', 0x8061);
    define('GL_TEXTURE_PRIORITY', 0x8066);
    define('GL_TEXTURE_RESIDENT', 0x8067);
    define('GL_ALPHA4', 0x803B);
    define('GL_ALPHA8', 0x803C);
    define('GL_ALPHA12', 0x803D);
    define('GL_ALPHA16', 0x803E);
    define('GL_LUMINANCE4', 0x803F);
    define('GL_LUMINANCE8', 0x8040);
    define('GL_LUMINANCE12', 0x8041);
    define('GL_LUMINANCE16', 0x8042);
    define('GL_LUMINANCE4_ALPHA4', 0x8043);
    define('GL_LUMINANCE6_ALPHA2', 0x8044);
    define('GL_LUMINANCE8_ALPHA8', 0x8045);
    define('GL_LUMINANCE12_ALPHA4', 0x8046);
    define('GL_LUMINANCE12_ALPHA12', 0x8047);
    define('GL_LUMINANCE16_ALPHA16', 0x8048);
    define('GL_INTENSITY', 0x8049);
    define('GL_INTENSITY4', 0x804A);
    define('GL_INTENSITY8', 0x804B);
    define('GL_INTENSITY12', 0x804C);
    define('GL_INTENSITY16', 0x804D);
    define('GL_UNSIGNED_BYTE_3_3_2', 0x8032);
    define('GL_UNSIGNED_SHORT_4_4_4_4', 0x8033);
    define('GL_UNSIGNED_SHORT_5_5_5_1', 0x8034);
    define('GL_UNSIGNED_INT_8_8_8_8', 0x8035);
    define('GL_UNSIGNED_INT_10_10_10_2', 0x8036);
    define('GL_TEXTURE_BINDING_3D', 0x806A);
    define('GL_PACK_SKIP_IMAGES', 0x806B);
    define('GL_PACK_IMAGE_HEIGHT', 0x806C);
    define('GL_UNPACK_SKIP_IMAGES', 0x806D);
    define('GL_UNPACK_IMAGE_HEIGHT', 0x806E);
    define('GL_TEXTURE_3D', 0x806F);
    define('GL_PROXY_TEXTURE_3D', 0x8070);
    define('GL_TEXTURE_DEPTH', 0x8071);
    define('GL_TEXTURE_WRAP_R', 0x8072);
    define('GL_MAX_3D_TEXTURE_SIZE', 0x8073);
    define('GL_RESCALE_NORMAL', 0x803A);
    define('GL_MULTISAMPLE', 0x809D);
    define('GL_SAMPLE_ALPHA_TO_COVERAGE', 0x809E);
    define('GL_SAMPLE_ALPHA_TO_ONE', 0x809F);
    define('GL_SAMPLE_COVERAGE', 0x80A0);
    define('GL_SAMPLE_BUFFERS', 0x80A8);
    define('GL_SAMPLES', 0x80A9);
    define('GL_SAMPLE_COVERAGE_VALUE', 0x80AA);
    define('GL_SAMPLE_COVERAGE_INVERT', 0x80AB);
    define('GL_BLEND_COLOR', 0x8005);
    define('GL_BLEND_EQUATION', 0x8009);
    define('GL_CONSTANT_COLOR', 0x8001);
    define('GL_ONE_MINUS_CONSTANT_COLOR', 0x8002);
    define('GL_CONSTANT_ALPHA', 0x8003);
    define('GL_ONE_MINUS_CONSTANT_ALPHA', 0x8004);
    define('GL_FUNC_ADD', 0x8006);
    define('GL_FUNC_REVERSE_SUBTRACT', 0x800B);
    define('GL_FUNC_SUBTRACT', 0x800A);
    define('GL_MIN', 0x8007);
    define('GL_MAX', 0x8008);
    define('GL_BLEND_EQUATION_RGB', 0x8009);
    define('GL_CLIENT_PIXEL_STORE_BIT', 0x00000001);
    define('GL_CLIENT_VERTEX_ARRAY_BIT', 0x00000002);
    define('GL_CLIENT_ALL_ATTRIB_BITS', 0xFFFFFFFF);
    define('GL_UNSIGNED_BYTE_2_3_3_REV', 0x8362);
    define('GL_UNSIGNED_SHORT_5_6_5', 0x8363);
    define('GL_UNSIGNED_SHORT_5_6_5_REV', 0x8364);
    define('GL_UNSIGNED_SHORT_4_4_4_4_REV', 0x8365);
    define('GL_UNSIGNED_SHORT_1_5_5_5_REV', 0x8366);
    define('GL_UNSIGNED_INT_8_8_8_8_REV', 0x8367);
    define('GL_UNSIGNED_INT_2_10_10_10_REV', 0x8368);
    define('GL_BGR', 0x80E0);
    define('GL_BGRA', 0x80E1);
    define('GL_MAX_ELEMENTS_VERTICES', 0x80E8);
    define('GL_MAX_ELEMENTS_INDICES', 0x80E9);
    define('GL_CLAMP_TO_EDGE', 0x812F);
    define('GL_TEXTURE_MIN_LOD', 0x813A);
    define('GL_TEXTURE_MAX_LOD', 0x813B);
    define('GL_TEXTURE_BASE_LEVEL', 0x813C);
    define('GL_TEXTURE_MAX_LEVEL', 0x813D);
    define('GL_CLAMP_TO_BORDER', 0x812D);
    define('GL_POINT_FADE_THRESHOLD_SIZE', 0x8128);
    define('GL_POINT_SIZE_MIN', 0x8126);
    define('GL_POINT_SIZE_MAX', 0x8127);
    define('GL_POINT_DISTANCE_ATTENUATION', 0x8129);
    define('GL_ALIASED_LINE_WIDTH_RANGE', 0x846E);
    define('GL_ALIASED_POINT_SIZE_RANGE', 0x846D);
    define('GL_FOG_COORDINATE_SOURCE', 0x8450);
    define('GL_FOG_COORDINATE', 0x8451);
    define('GL_FRAGMENT_DEPTH', 0x8452);
    define('GL_CURRENT_FOG_COORDINATE', 0x8453);
    define('GL_FOG_COORDINATE_ARRAY_TYPE', 0x8454);
    define('GL_FOG_COORDINATE_ARRAY_STRIDE', 0x8455);
    define('GL_FOG_COORDINATE_ARRAY_POINTER', 0x8456);
    define('GL_FOG_COORDINATE_ARRAY', 0x8457);
    define('GL_COLOR_SUM', 0x8458);
    define('GL_CURRENT_SECONDARY_COLOR', 0x8459);
    define('GL_SECONDARY_COLOR_ARRAY_SIZE', 0x845A);
    define('GL_SECONDARY_COLOR_ARRAY_TYPE', 0x845B);
    define('GL_SECONDARY_COLOR_ARRAY_STRIDE', 0x845C);
    define('GL_SECONDARY_COLOR_ARRAY_POINTER', 0x845D);
    define('GL_SECONDARY_COLOR_ARRAY', 0x845E);
    define('GL_FOG_COORD_SRC', 0x8450);
    define('GL_FOG_COORD', 0x8451);
    define('GL_CURRENT_FOG_COORD', 0x8453);
    define('GL_FOG_COORD_ARRAY_TYPE', 0x8454);
    define('GL_FOG_COORD_ARRAY_STRIDE', 0x8455);
    define('GL_FOG_COORD_ARRAY_POINTER', 0x8456);
    define('GL_FOG_COORD_ARRAY', 0x8457);
    define('GL_CURRENT_RASTER_SECONDARY_COLOR', 0x845F);
    define('GL_LIGHT_MODEL_COLOR_CONTROL', 0x81F8);
    define('GL_SINGLE_COLOR', 0x81F9);
    define('GL_SEPARATE_SPECULAR_COLOR', 0x81FA);
    define('GL_TEXTURE0', 0x84C0);
    define('GL_TEXTURE1', 0x84C1);
    define('GL_TEXTURE2', 0x84C2);
    define('GL_TEXTURE3', 0x84C3);
    define('GL_TEXTURE4', 0x84C4);
    define('GL_TEXTURE5', 0x84C5);
    define('GL_TEXTURE6', 0x84C6);
    define('GL_TEXTURE7', 0x84C7);
    define('GL_TEXTURE8', 0x84C8);
    define('GL_TEXTURE9', 0x84C9);
    define('GL_TEXTURE10', 0x84CA);
    define('GL_TEXTURE11', 0x84CB);
    define('GL_TEXTURE12', 0x84CC);
    define('GL_TEXTURE13', 0x84CD);
    define('GL_TEXTURE14', 0x84CE);
    define('GL_TEXTURE15', 0x84CF);
    define('GL_TEXTURE16', 0x84D0);
    define('GL_TEXTURE17', 0x84D1);
    define('GL_TEXTURE18', 0x84D2);
    define('GL_TEXTURE19', 0x84D3);
    define('GL_TEXTURE20', 0x84D4);
    define('GL_TEXTURE21', 0x84D5);
    define('GL_TEXTURE22', 0x84D6);
    define('GL_TEXTURE23', 0x84D7);
    define('GL_TEXTURE24', 0x84D8);
    define('GL_TEXTURE25', 0x84D9);
    define('GL_TEXTURE26', 0x84DA);
    define('GL_TEXTURE27', 0x84DB);
    define('GL_TEXTURE28', 0x84DC);
    define('GL_TEXTURE29', 0x84DD);
    define('GL_TEXTURE30', 0x84DE);
    define('GL_TEXTURE31', 0x84DF);
    define('GL_ACTIVE_TEXTURE', 0x84E0);
    define('GL_COMPRESSED_RGB', 0x84ED);
    define('GL_COMPRESSED_RGBA', 0x84EE);
    define('GL_TEXTURE_COMPRESSION_HINT', 0x84EF);
    define('GL_CLIENT_ACTIVE_TEXTURE', 0x84E1);
    define('GL_MAX_TEXTURE_UNITS', 0x84E2);
    define('GL_TRANSPOSE_MODELVIEW_MATRIX', 0x84E3);
    define('GL_TRANSPOSE_PROJECTION_MATRIX', 0x84E4);
    define('GL_TRANSPOSE_TEXTURE_MATRIX', 0x84E5);
    define('GL_TRANSPOSE_COLOR_MATRIX', 0x84E6);
    define('GL_COMPRESSED_ALPHA', 0x84E9);
    define('GL_COMPRESSED_LUMINANCE', 0x84EA);
    define('GL_COMPRESSED_LUMINANCE_ALPHA', 0x84EB);
    define('GL_COMPRESSED_INTENSITY', 0x84EC);
    define('GL_SUBTRACT', 0x84E7);
    define('GL_MAX_RENDERBUFFER_SIZE', 0x84E8);
    define('GL_TEXTURE_CUBE_MAP', 0x8513);
    define('GL_TEXTURE_BINDING_CUBE_MAP', 0x8514);
    define('GL_TEXTURE_CUBE_MAP_POSITIVE_X', 0x8515);
    define('GL_TEXTURE_CUBE_MAP_NEGATIVE_X', 0x8516);
    define('GL_TEXTURE_CUBE_MAP_POSITIVE_Y', 0x8517);
    define('GL_TEXTURE_CUBE_MAP_NEGATIVE_Y', 0x8518);
    define('GL_TEXTURE_CUBE_MAP_POSITIVE_Z', 0x8519);
    define('GL_TEXTURE_CUBE_MAP_NEGATIVE_Z', 0x851A);
    define('GL_PROXY_TEXTURE_CUBE_MAP', 0x851B);
    define('GL_MAX_CUBE_MAP_TEXTURE_SIZE', 0x851C);
    define('GL_NORMAL_MAP', 0x8511);
    define('GL_REFLECTION_MAP', 0x8512);
    define('GL_MAX_TEXTURE_LOD_BIAS', 0x84FD);
    define('GL_TEXTURE_LOD_BIAS', 0x8501);
    define('GL_INCR_WRAP', 0x8507);
    define('GL_DECR_WRAP', 0x8508);
    define('GL_TEXTURE_FILTER_CONTROL', 0x8500);
    define('GL_DEPTH_STENCIL', 0x84F9);
    define('GL_UNSIGNED_INT_24_8', 0x84FA);
    define('GL_TEXTURE_RECTANGLE', 0x84F5);
    define('GL_TEXTURE_BINDING_RECTANGLE', 0x84F6);
    define('GL_PROXY_TEXTURE_RECTANGLE', 0x84F7);
    define('GL_MAX_RECTANGLE_TEXTURE_SIZE', 0x84F8);
    define('GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER', 0x84F0);
    define('GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER', 0x84F1);
    define('GL_TEXTURE_COMPRESSED_IMAGE_SIZE', 0x86A0);
    define('GL_TEXTURE_COMPRESSED', 0x86A1);
    define('GL_NUM_COMPRESSED_TEXTURE_FORMATS', 0x86A2);
    define('GL_COMPRESSED_TEXTURE_FORMATS', 0x86A3);
    define('GL_DOT3_RGB', 0x86AE);
    define('GL_DOT3_RGBA', 0x86AF);
    define('GL_COMBINE', 0x8570);
    define('GL_COMBINE_RGB', 0x8571);
    define('GL_COMBINE_ALPHA', 0x8572);
    define('GL_SOURCE0_RGB', 0x8580);
    define('GL_SOURCE1_RGB', 0x8581);
    define('GL_SOURCE2_RGB', 0x8582);
    define('GL_SOURCE0_ALPHA', 0x8588);
    define('GL_SOURCE1_ALPHA', 0x8589);
    define('GL_SOURCE2_ALPHA', 0x858A);
    define('GL_OPERAND0_RGB', 0x8590);
    define('GL_OPERAND1_RGB', 0x8591);
    define('GL_OPERAND2_RGB', 0x8592);
    define('GL_OPERAND0_ALPHA', 0x8598);
    define('GL_OPERAND1_ALPHA', 0x8599);
    define('GL_OPERAND2_ALPHA', 0x859A);
    define('GL_RGB_SCALE', 0x8573);
    define('GL_ADD_SIGNED', 0x8574);
    define('GL_INTERPOLATE', 0x8575);
    define('GL_CONSTANT', 0x8576);
    define('GL_PRIMARY_COLOR', 0x8577);
    define('GL_PREVIOUS', 0x8578);
    define('GL_SRC1_ALPHA', 0x8589);
    define('GL_SRC0_RGB', 0x8580);
    define('GL_SRC1_RGB', 0x8581);
    define('GL_SRC2_RGB', 0x8582);
    define('GL_SRC0_ALPHA', 0x8588);
    define('GL_SRC2_ALPHA', 0x858A);
    define('GL_BLEND_DST_RGB', 0x80C8);
    define('GL_BLEND_SRC_RGB', 0x80C9);
    define('GL_BLEND_DST_ALPHA', 0x80CA);
    define('GL_BLEND_SRC_ALPHA', 0x80CB);
    define('GL_DEPTH_COMPONENT16', 0x81A5);
    define('GL_DEPTH_COMPONENT24', 0x81A6);
    define('GL_DEPTH_COMPONENT32', 0x81A7);
    define('GL_GENERATE_MIPMAP', 0x8191);
    define('GL_GENERATE_MIPMAP_HINT', 0x8192);
    define('GL_MIRRORED_REPEAT', 0x8370);
    define('GL_TEXTURE_DEPTH_SIZE', 0x884A);
    define('GL_TEXTURE_COMPARE_MODE', 0x884C);
    define('GL_TEXTURE_COMPARE_FUNC', 0x884D);
    define('GL_DEPTH_TEXTURE_MODE', 0x884B);
    define('GL_COMPARE_R_TO_TEXTURE', 0x884E);
    define('GL_COMPARE_REF_TO_TEXTURE', 0x884E);
    define('GL_TEXTURE_CUBE_MAP_SEAMLESS', 0x884F);
    define('GL_BUFFER_SIZE', 0x8764);
    define('GL_BUFFER_USAGE', 0x8765);
    define('GL_STENCIL_BACK_FUNC', 0x8800);
    define('GL_STENCIL_BACK_FAIL', 0x8801);
    define('GL_STENCIL_BACK_PASS_DEPTH_FAIL', 0x8802);
    define('GL_STENCIL_BACK_PASS_DEPTH_PASS', 0x8803);
    define('GL_MAX_DRAW_BUFFERS', 0x8824);
    define('GL_DRAW_BUFFER0', 0x8825);
    define('GL_DRAW_BUFFER1', 0x8826);
    define('GL_DRAW_BUFFER2', 0x8827);
    define('GL_DRAW_BUFFER3', 0x8828);
    define('GL_DRAW_BUFFER4', 0x8829);
    define('GL_DRAW_BUFFER5', 0x882A);
    define('GL_DRAW_BUFFER6', 0x882B);
    define('GL_DRAW_BUFFER7', 0x882C);
    define('GL_DRAW_BUFFER8', 0x882D);
    define('GL_DRAW_BUFFER9', 0x882E);
    define('GL_DRAW_BUFFER10', 0x882F);
    define('GL_DRAW_BUFFER11', 0x8830);
    define('GL_DRAW_BUFFER12', 0x8831);
    define('GL_DRAW_BUFFER13', 0x8832);
    define('GL_DRAW_BUFFER14', 0x8833);
    define('GL_DRAW_BUFFER15', 0x8834);
    define('GL_BLEND_EQUATION_ALPHA', 0x883D);
    define('GL_RGBA32F', 0x8814);
    define('GL_RGB32F', 0x8815);
    define('GL_RGBA16F', 0x881A);
    define('GL_RGB16F', 0x881B);
    define('GL_NUM_PROGRAM_BINARY_FORMATS', 0x87FE);
    define('GL_PROGRAM_BINARY_FORMATS', 0x87FF);
    define('GL_QUERY_COUNTER_BITS', 0x8864);
    define('GL_CURRENT_QUERY', 0x8865);
    define('GL_QUERY_RESULT', 0x8866);
    define('GL_QUERY_RESULT_AVAILABLE', 0x8867);
    define('GL_ARRAY_BUFFER', 0x8892);
    define('GL_ELEMENT_ARRAY_BUFFER', 0x8893);
    define('GL_ARRAY_BUFFER_BINDING', 0x8894);
    define('GL_ELEMENT_ARRAY_BUFFER_BINDING', 0x8895);
    define('GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING', 0x889F);
    define('GL_READ_ONLY', 0x88B8);
    define('GL_WRITE_ONLY', 0x88B9);
    define('GL_READ_WRITE', 0x88BA);
    define('GL_BUFFER_ACCESS', 0x88BB);
    define('GL_BUFFER_MAPPED', 0x88BC);
    define('GL_BUFFER_MAP_POINTER', 0x88BD);
    define('GL_STREAM_DRAW', 0x88E0);
    define('GL_STREAM_READ', 0x88E1);
    define('GL_STREAM_COPY', 0x88E2);
    define('GL_STATIC_DRAW', 0x88E4);
    define('GL_STATIC_READ', 0x88E5);
    define('GL_STATIC_COPY', 0x88E6);
    define('GL_DYNAMIC_DRAW', 0x88E8);
    define('GL_DYNAMIC_READ', 0x88E9);
    define('GL_DYNAMIC_COPY', 0x88EA);
    define('GL_SAMPLES_PASSED', 0x8914);
    define('GL_VERTEX_ARRAY_BUFFER_BINDING', 0x8896);
    define('GL_NORMAL_ARRAY_BUFFER_BINDING', 0x8897);
    define('GL_COLOR_ARRAY_BUFFER_BINDING', 0x8898);
    define('GL_INDEX_ARRAY_BUFFER_BINDING', 0x8899);
    define('GL_TEXTURE_COORD_ARRAY_BUFFER_BINDING', 0x889A);
    define('GL_EDGE_FLAG_ARRAY_BUFFER_BINDING', 0x889B);
    define('GL_SECONDARY_COLOR_ARRAY_BUFFER_BINDING', 0x889C);
    define('GL_FOG_COORDINATE_ARRAY_BUFFER_BINDING', 0x889D);
    define('GL_WEIGHT_ARRAY_BUFFER_BINDING', 0x889E);
    define('GL_FOG_COORD_ARRAY_BUFFER_BINDING', 0x889D);
    define('GL_MAX_VERTEX_ATTRIBS', 0x8869);
    define('GL_VERTEX_ATTRIB_ARRAY_NORMALIZED', 0x886A);
    define('GL_MAX_TEXTURE_IMAGE_UNITS', 0x8872);
    define('GL_POINT_SPRITE', 0x8861);
    define('GL_COORD_REPLACE', 0x8862);
    define('GL_MAX_TEXTURE_COORDS', 0x8871);
    define('GL_PIXEL_PACK_BUFFER', 0x88EB);
    define('GL_PIXEL_UNPACK_BUFFER', 0x88EC);
    define('GL_PIXEL_PACK_BUFFER_BINDING', 0x88ED);
    define('GL_PIXEL_UNPACK_BUFFER_BINDING', 0x88EF);
    define('GL_VERTEX_ATTRIB_ARRAY_INTEGER', 0x88FD);
    define('GL_MAX_ARRAY_TEXTURE_LAYERS', 0x88FF);
    define('GL_MIN_PROGRAM_TEXEL_OFFSET', 0x8904);
    define('GL_MAX_PROGRAM_TEXEL_OFFSET', 0x8905);
    define('GL_CLAMP_READ_COLOR', 0x891C);
    define('GL_FIXED_ONLY', 0x891D);
    define('GL_DEPTH24_STENCIL8', 0x88F0);
    define('GL_TEXTURE_STENCIL_SIZE', 0x88F1);
    define('GL_CLAMP_VERTEX_COLOR', 0x891A);
    define('GL_CLAMP_FRAGMENT_COLOR', 0x891B);
    define('GL_GEOMETRY_VERTICES_OUT', 0x8916);
    define('GL_GEOMETRY_INPUT_TYPE', 0x8917);
    define('GL_GEOMETRY_OUTPUT_TYPE', 0x8918);
    define('GL_VERTEX_ATTRIB_ARRAY_DIVISOR', 0x88FE);
    define('GL_SRC1_COLOR', 0x88F9);
    define('GL_ONE_MINUS_SRC1_COLOR', 0x88FA);
    define('GL_ONE_MINUS_SRC1_ALPHA', 0x88FB);
    define('GL_MAX_DUAL_SOURCE_DRAW_BUFFERS', 0x88FC);
    define('GL_SAMPLER_BINDING', 0x8919);
    define('GL_TIME_ELAPSED', 0x88BF);
    define('GL_GEOMETRY_SHADER_INVOCATIONS', 0x887F);
    define('GL_MAX_TESS_CONTROL_INPUT_COMPONENTS', 0x886C);
    define('GL_MAX_TESS_EVALUATION_INPUT_COMPONENTS', 0x886D);
    define('GL_VERTEX_ATTRIB_ARRAY_ENABLED', 0x8622);
    define('GL_VERTEX_ATTRIB_ARRAY_SIZE', 0x8623);
    define('GL_VERTEX_ATTRIB_ARRAY_STRIDE', 0x8624);
    define('GL_VERTEX_ATTRIB_ARRAY_TYPE', 0x8625);
    define('GL_CURRENT_VERTEX_ATTRIB', 0x8626);
    define('GL_VERTEX_PROGRAM_POINT_SIZE', 0x8642);
    define('GL_VERTEX_ATTRIB_ARRAY_POINTER', 0x8645);
    define('GL_VERTEX_PROGRAM_TWO_SIDE', 0x8643);
    define('GL_PROGRAM_POINT_SIZE', 0x8642);
    define('GL_DEPTH_CLAMP', 0x864F);
    define('GL_FRAGMENT_SHADER', 0x8B30);
    define('GL_VERTEX_SHADER', 0x8B31);
    define('GL_MAX_FRAGMENT_UNIFORM_COMPONENTS', 0x8B49);
    define('GL_MAX_VERTEX_UNIFORM_COMPONENTS', 0x8B4A);
    define('GL_MAX_VARYING_FLOATS', 0x8B4B);
    define('GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS', 0x8B4C);
    define('GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS', 0x8B4D);
    define('GL_SHADER_TYPE', 0x8B4F);
    define('GL_MAX_VARYING_COMPONENTS', 0x8B4B);
    define('GL_FLOAT_VEC2', 0x8B50);
    define('GL_FLOAT_VEC3', 0x8B51);
    define('GL_FLOAT_VEC4', 0x8B52);
    define('GL_INT_VEC2', 0x8B53);
    define('GL_INT_VEC3', 0x8B54);
    define('GL_INT_VEC4', 0x8B55);
    define('GL_BOOL', 0x8B56);
    define('GL_BOOL_VEC2', 0x8B57);
    define('GL_BOOL_VEC3', 0x8B58);
    define('GL_BOOL_VEC4', 0x8B59);
    define('GL_FLOAT_MAT2', 0x8B5A);
    define('GL_FLOAT_MAT3', 0x8B5B);
    define('GL_FLOAT_MAT4', 0x8B5C);
    define('GL_SAMPLER_1D', 0x8B5D);
    define('GL_SAMPLER_2D', 0x8B5E);
    define('GL_SAMPLER_3D', 0x8B5F);
    define('GL_SAMPLER_CUBE', 0x8B60);
    define('GL_SAMPLER_1D_SHADOW', 0x8B61);
    define('GL_SAMPLER_2D_SHADOW', 0x8B62);
    define('GL_FLOAT_MAT2x3', 0x8B65);
    define('GL_FLOAT_MAT2x4', 0x8B66);
    define('GL_FLOAT_MAT3x2', 0x8B67);
    define('GL_FLOAT_MAT3x4', 0x8B68);
    define('GL_FLOAT_MAT4x2', 0x8B69);
    define('GL_FLOAT_MAT4x3', 0x8B6A);
    define('GL_SAMPLER_2D_RECT', 0x8B63);
    define('GL_SAMPLER_2D_RECT_SHADOW', 0x8B64);
    define('GL_DELETE_STATUS', 0x8B80);
    define('GL_COMPILE_STATUS', 0x8B81);
    define('GL_LINK_STATUS', 0x8B82);
    define('GL_VALIDATE_STATUS', 0x8B83);
    define('GL_INFO_LOG_LENGTH', 0x8B84);
    define('GL_ATTACHED_SHADERS', 0x8B85);
    define('GL_ACTIVE_UNIFORMS', 0x8B86);
    define('GL_ACTIVE_UNIFORM_MAX_LENGTH', 0x8B87);
    define('GL_SHADER_SOURCE_LENGTH', 0x8B88);
    define('GL_ACTIVE_ATTRIBUTES', 0x8B89);
    define('GL_ACTIVE_ATTRIBUTE_MAX_LENGTH', 0x8B8A);
    define('GL_FRAGMENT_SHADER_DERIVATIVE_HINT', 0x8B8B);
    define('GL_SHADING_LANGUAGE_VERSION', 0x8B8C);
    define('GL_CURRENT_PROGRAM', 0x8B8D);
    define('GL_POINT_SPRITE_COORD_ORIGIN', 0x8CA0);
    define('GL_LOWER_LEFT', 0x8CA1);
    define('GL_UPPER_LEFT', 0x8CA2);
    define('GL_STENCIL_BACK_REF', 0x8CA3);
    define('GL_STENCIL_BACK_VALUE_MASK', 0x8CA4);
    define('GL_STENCIL_BACK_WRITEMASK', 0x8CA5);
    define('GL_DEPTH_COMPONENT32F', 0x8CAC);
    define('GL_DEPTH32F_STENCIL8', 0x8CAD);
    define('GL_FRAMEBUFFER_BINDING', 0x8CA6);
    define('GL_DRAW_FRAMEBUFFER_BINDING', 0x8CA6);
    define('GL_RENDERBUFFER_BINDING', 0x8CA7);
    define('GL_READ_FRAMEBUFFER', 0x8CA8);
    define('GL_DRAW_FRAMEBUFFER', 0x8CA9);
    define('GL_READ_FRAMEBUFFER_BINDING', 0x8CAA);
    define('GL_RENDERBUFFER_SAMPLES', 0x8CAB);
    define('GL_SRGB', 0x8C40);
    define('GL_SRGB8', 0x8C41);
    define('GL_SRGB_ALPHA', 0x8C42);
    define('GL_SRGB8_ALPHA8', 0x8C43);
    define('GL_COMPRESSED_SRGB', 0x8C48);
    define('GL_COMPRESSED_SRGB_ALPHA', 0x8C49);
    define('GL_SLUMINANCE_ALPHA', 0x8C44);
    define('GL_SLUMINANCE8_ALPHA8', 0x8C45);
    define('GL_SLUMINANCE', 0x8C46);
    define('GL_SLUMINANCE8', 0x8C47);
    define('GL_COMPRESSED_SLUMINANCE', 0x8C4A);
    define('GL_COMPRESSED_SLUMINANCE_ALPHA', 0x8C4B);
    define('GL_TEXTURE_1D_ARRAY', 0x8C18);
    define('GL_PROXY_TEXTURE_1D_ARRAY', 0x8C19);
    define('GL_TEXTURE_2D_ARRAY', 0x8C1A);
    define('GL_PROXY_TEXTURE_2D_ARRAY', 0x8C1B);
    define('GL_TEXTURE_BINDING_1D_ARRAY', 0x8C1C);
    define('GL_TEXTURE_BINDING_2D_ARRAY', 0x8C1D);
    define('GL_R11F_G11F_B10F', 0x8C3A);
    define('GL_UNSIGNED_INT_10F_11F_11F_REV', 0x8C3B);
    define('GL_RGB9_E5', 0x8C3D);
    define('GL_UNSIGNED_INT_5_9_9_9_REV', 0x8C3E);
    define('GL_TEXTURE_SHARED_SIZE', 0x8C3F);
    define('GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH', 0x8C76);
    define('GL_TRANSFORM_FEEDBACK_BUFFER_MODE', 0x8C7F);
    define('GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS', 0x8C80);
    define('GL_TRANSFORM_FEEDBACK_VARYINGS', 0x8C83);
    define('GL_TRANSFORM_FEEDBACK_BUFFER_START', 0x8C84);
    define('GL_TRANSFORM_FEEDBACK_BUFFER_SIZE', 0x8C85);
    define('GL_PRIMITIVES_GENERATED', 0x8C87);
    define('GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN', 0x8C88);
    define('GL_RASTERIZER_DISCARD', 0x8C89);
    define('GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS', 0x8C8A);
    define('GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS', 0x8C8B);
    define('GL_INTERLEAVED_ATTRIBS', 0x8C8C);
    define('GL_SEPARATE_ATTRIBS', 0x8C8D);
    define('GL_TRANSFORM_FEEDBACK_BUFFER', 0x8C8E);
    define('GL_TRANSFORM_FEEDBACK_BUFFER_BINDING', 0x8C8F);
    define('GL_TEXTURE_RED_TYPE', 0x8C10);
    define('GL_TEXTURE_GREEN_TYPE', 0x8C11);
    define('GL_TEXTURE_BLUE_TYPE', 0x8C12);
    define('GL_TEXTURE_ALPHA_TYPE', 0x8C13);
    define('GL_TEXTURE_DEPTH_TYPE', 0x8C16);
    define('GL_UNSIGNED_NORMALIZED', 0x8C17);
    define('GL_TEXTURE_LUMINANCE_TYPE', 0x8C14);
    define('GL_TEXTURE_INTENSITY_TYPE', 0x8C15);
    define('GL_TEXTURE_BUFFER', 0x8C2A);
    define('GL_MAX_TEXTURE_BUFFER_SIZE', 0x8C2B);
    define('GL_TEXTURE_BINDING_BUFFER', 0x8C2C);
    define('GL_TEXTURE_BUFFER_DATA_STORE_BINDING', 0x8C2D);
    define('GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS', 0x8C29);
    define('GL_ANY_SAMPLES_PASSED', 0x8C2F);
    define('GL_SAMPLE_SHADING', 0x8C36);
    define('GL_MIN_SAMPLE_SHADING_VALUE', 0x8C37);
    define('GL_MAJOR_VERSION', 0x821B);
    define('GL_MINOR_VERSION', 0x821C);
    define('GL_NUM_EXTENSIONS', 0x821D);
    define('GL_CONTEXT_FLAGS', 0x821E);
    define('GL_COMPRESSED_RED', 0x8225);
    define('GL_COMPRESSED_RG', 0x8226);
    define('GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING', 0x8210);
    define('GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE', 0x8211);
    define('GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE', 0x8212);
    define('GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE', 0x8213);
    define('GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE', 0x8214);
    define('GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE', 0x8215);
    define('GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE', 0x8216);
    define('GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE', 0x8217);
    define('GL_FRAMEBUFFER_DEFAULT', 0x8218);
    define('GL_FRAMEBUFFER_UNDEFINED', 0x8219);
    define('GL_DEPTH_STENCIL_ATTACHMENT', 0x821A);
    define('GL_INDEX', 0x8222);
    define('GL_RG', 0x8227);
    define('GL_RG_INTEGER', 0x8228);
    define('GL_R8', 0x8229);
    define('GL_R16', 0x822A);
    define('GL_RG8', 0x822B);
    define('GL_RG16', 0x822C);
    define('GL_R16F', 0x822D);
    define('GL_R32F', 0x822E);
    define('GL_RG16F', 0x822F);
    define('GL_RG32F', 0x8230);
    define('GL_R8I', 0x8231);
    define('GL_R8UI', 0x8232);
    define('GL_R16I', 0x8233);
    define('GL_R16UI', 0x8234);
    define('GL_R32I', 0x8235);
    define('GL_R32UI', 0x8236);
    define('GL_RG8I', 0x8237);
    define('GL_RG8UI', 0x8238);
    define('GL_RG16I', 0x8239);
    define('GL_RG16UI', 0x823A);
    define('GL_RG32I', 0x823B);
    define('GL_RG32UI', 0x823C);
    define('GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT', 0x00000001);
    define('GL_RGBA32UI', 0x8D70);
    define('GL_RGB32UI', 0x8D71);
    define('GL_RGBA16UI', 0x8D76);
    define('GL_RGB16UI', 0x8D77);
    define('GL_RGBA8UI', 0x8D7C);
    define('GL_RGB8UI', 0x8D7D);
    define('GL_RGBA32I', 0x8D82);
    define('GL_RGB32I', 0x8D83);
    define('GL_RGBA16I', 0x8D88);
    define('GL_RGB16I', 0x8D89);
    define('GL_RGBA8I', 0x8D8E);
    define('GL_RGB8I', 0x8D8F);
    define('GL_RED_INTEGER', 0x8D94);
    define('GL_GREEN_INTEGER', 0x8D95);
    define('GL_BLUE_INTEGER', 0x8D96);
    define('GL_RGB_INTEGER', 0x8D98);
    define('GL_RGBA_INTEGER', 0x8D99);
    define('GL_BGR_INTEGER', 0x8D9A);
    define('GL_BGRA_INTEGER', 0x8D9B);
    define('GL_SAMPLER_1D_ARRAY', 0x8DC0);
    define('GL_SAMPLER_2D_ARRAY', 0x8DC1);
    define('GL_SAMPLER_1D_ARRAY_SHADOW', 0x8DC3);
    define('GL_SAMPLER_2D_ARRAY_SHADOW', 0x8DC4);
    define('GL_SAMPLER_CUBE_SHADOW', 0x8DC5);
    define('GL_UNSIGNED_INT_VEC2', 0x8DC6);
    define('GL_UNSIGNED_INT_VEC3', 0x8DC7);
    define('GL_UNSIGNED_INT_VEC4', 0x8DC8);
    define('GL_INT_SAMPLER_1D', 0x8DC9);
    define('GL_INT_SAMPLER_2D', 0x8DCA);
    define('GL_INT_SAMPLER_3D', 0x8DCB);
    define('GL_INT_SAMPLER_CUBE', 0x8DCC);
    define('GL_INT_SAMPLER_1D_ARRAY', 0x8DCE);
    define('GL_INT_SAMPLER_2D_ARRAY', 0x8DCF);
    define('GL_UNSIGNED_INT_SAMPLER_1D', 0x8DD1);
    define('GL_UNSIGNED_INT_SAMPLER_2D', 0x8DD2);
    define('GL_UNSIGNED_INT_SAMPLER_3D', 0x8DD3);
    define('GL_UNSIGNED_INT_SAMPLER_CUBE', 0x8DD4);
    define('GL_UNSIGNED_INT_SAMPLER_1D_ARRAY', 0x8DD6);
    define('GL_UNSIGNED_INT_SAMPLER_2D_ARRAY', 0x8DD7);
    define('GL_FLOAT_32_UNSIGNED_INT_24_8_REV', 0x8DAD);
    define('GL_FRAMEBUFFER_SRGB', 0x8DB9);
    define('GL_COMPRESSED_RED_RGTC1', 0x8DBB);
    define('GL_COMPRESSED_SIGNED_RED_RGTC1', 0x8DBC);
    define('GL_COMPRESSED_RG_RGTC2', 0x8DBD);
    define('GL_COMPRESSED_SIGNED_RG_RGTC2', 0x8DBE);
    define('GL_ALPHA_INTEGER', 0x8D97);
    define('GL_SAMPLER_BUFFER', 0x8DC2);
    define('GL_INT_SAMPLER_2D_RECT', 0x8DCD);
    define('GL_INT_SAMPLER_BUFFER', 0x8DD0);
    define('GL_UNSIGNED_INT_SAMPLER_2D_RECT', 0x8DD5);
    define('GL_UNSIGNED_INT_SAMPLER_BUFFER', 0x8DD8);
    define('GL_FRAMEBUFFER_ATTACHMENT_LAYERED', 0x8DA7);
    define('GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS', 0x8DA8);
    define('GL_GEOMETRY_SHADER', 0x8DD9);
    define('GL_MAX_GEOMETRY_UNIFORM_COMPONENTS', 0x8DDF);
    define('GL_MAX_GEOMETRY_OUTPUT_VERTICES', 0x8DE0);
    define('GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS', 0x8DE1);
    define('GL_INT_2_10_10_10_REV', 0x8D9F);
    define('GL_ACTIVE_SUBROUTINES', 0x8DE5);
    define('GL_ACTIVE_SUBROUTINE_UNIFORMS', 0x8DE6);
    define('GL_MAX_SUBROUTINES', 0x8DE7);
    define('GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS', 0x8DE8);
    define('GL_QUERY_WAIT', 0x8E13);
    define('GL_QUERY_NO_WAIT', 0x8E14);
    define('GL_QUERY_BY_REGION_WAIT', 0x8E15);
    define('GL_QUERY_BY_REGION_NO_WAIT', 0x8E16);
    define('GL_QUADS_FOLLOW_PROVOKING_VERTEX_CONVENTION', 0x8E4C);
    define('GL_FIRST_VERTEX_CONVENTION', 0x8E4D);
    define('GL_LAST_VERTEX_CONVENTION', 0x8E4E);
    define('GL_PROVOKING_VERTEX', 0x8E4F);
    define('GL_SAMPLE_POSITION', 0x8E50);
    define('GL_SAMPLE_MASK', 0x8E51);
    define('GL_SAMPLE_MASK_VALUE', 0x8E52);
    define('GL_MAX_SAMPLE_MASK_WORDS', 0x8E59);
    define('GL_TEXTURE_SWIZZLE_R', 0x8E42);
    define('GL_TEXTURE_SWIZZLE_G', 0x8E43);
    define('GL_TEXTURE_SWIZZLE_B', 0x8E44);
    define('GL_TEXTURE_SWIZZLE_A', 0x8E45);
    define('GL_TEXTURE_SWIZZLE_RGBA', 0x8E46);
    define('GL_TIMESTAMP', 0x8E28);
    define('GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET', 0x8E5E);
    define('GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET', 0x8E5F);
    define('GL_MAX_GEOMETRY_SHADER_INVOCATIONS', 0x8E5A);
    define('GL_MIN_FRAGMENT_INTERPOLATION_OFFSET', 0x8E5B);
    define('GL_MAX_FRAGMENT_INTERPOLATION_OFFSET', 0x8E5C);
    define('GL_FRAGMENT_INTERPOLATION_OFFSET_BITS', 0x8E5D);
    define('GL_MAX_VERTEX_STREAMS', 0x8E71);
    define('GL_ACTIVE_SUBROUTINE_UNIFORM_LOCATIONS', 0x8E47);
    define('GL_ACTIVE_SUBROUTINE_MAX_LENGTH', 0x8E48);
    define('GL_ACTIVE_SUBROUTINE_UNIFORM_MAX_LENGTH', 0x8E49);
    define('GL_NUM_COMPATIBLE_SUBROUTINES', 0x8E4A);
    define('GL_COMPATIBLE_SUBROUTINES', 0x8E4B);
    define('GL_PATCH_VERTICES', 0x8E72);
    define('GL_PATCH_DEFAULT_INNER_LEVEL', 0x8E73);
    define('GL_PATCH_DEFAULT_OUTER_LEVEL', 0x8E74);
    define('GL_TESS_CONTROL_OUTPUT_VERTICES', 0x8E75);
    define('GL_TESS_GEN_MODE', 0x8E76);
    define('GL_TESS_GEN_SPACING', 0x8E77);
    define('GL_TESS_GEN_VERTEX_ORDER', 0x8E78);
    define('GL_TESS_GEN_POINT_MODE', 0x8E79);
    define('GL_ISOLINES', 0x8E7A);
    define('GL_FRACTIONAL_ODD', 0x8E7B);
    define('GL_FRACTIONAL_EVEN', 0x8E7C);
    define('GL_MAX_PATCH_VERTICES', 0x8E7D);
    define('GL_MAX_TESS_GEN_LEVEL', 0x8E7E);
    define('GL_MAX_TESS_CONTROL_UNIFORM_COMPONENTS', 0x8E7F);
    define('GL_MAX_TESS_EVALUATION_UNIFORM_COMPONENTS', 0x8E80);
    define('GL_MAX_TESS_CONTROL_TEXTURE_IMAGE_UNITS', 0x8E81);
    define('GL_MAX_TESS_EVALUATION_TEXTURE_IMAGE_UNITS', 0x8E82);
    define('GL_MAX_TESS_CONTROL_OUTPUT_COMPONENTS', 0x8E83);
    define('GL_MAX_TESS_PATCH_COMPONENTS', 0x8E84);
    define('GL_MAX_TESS_CONTROL_TOTAL_OUTPUT_COMPONENTS', 0x8E85);
    define('GL_MAX_TESS_EVALUATION_OUTPUT_COMPONENTS', 0x8E86);
    define('GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS', 0x8E89);
    define('GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS', 0x8E8A);
    define('GL_MAX_COMBINED_TESS_CONTROL_UNIFORM_COMPONENTS', 0x8E1E);
    define('GL_MAX_COMBINED_TESS_EVALUATION_UNIFORM_COMPONENTS', 0x8E1F);
    define('GL_TESS_EVALUATION_SHADER', 0x8E87);
    define('GL_TESS_CONTROL_SHADER', 0x8E88);
    define('GL_TRANSFORM_FEEDBACK', 0x8E22);
    define('GL_TRANSFORM_FEEDBACK_BUFFER_PAUSED', 0x8E23);
    define('GL_TRANSFORM_FEEDBACK_BUFFER_ACTIVE', 0x8E24);
    define('GL_TRANSFORM_FEEDBACK_BINDING', 0x8E25);
    define('GL_MAX_TRANSFORM_FEEDBACK_BUFFERS', 0x8E70);
    define('GL_BUFFER_ACCESS_FLAGS', 0x911F);
    define('GL_BUFFER_MAP_LENGTH', 0x9120);
    define('GL_BUFFER_MAP_OFFSET', 0x9121);
    define('GL_MAX_VERTEX_OUTPUT_COMPONENTS', 0x9122);
    define('GL_MAX_GEOMETRY_INPUT_COMPONENTS', 0x9123);
    define('GL_MAX_GEOMETRY_OUTPUT_COMPONENTS', 0x9124);
    define('GL_MAX_FRAGMENT_INPUT_COMPONENTS', 0x9125);
    define('GL_CONTEXT_PROFILE_MASK', 0x9126);
    define('GL_MAX_SERVER_WAIT_TIMEOUT', 0x9111);
    define('GL_OBJECT_TYPE', 0x9112);
    define('GL_SYNC_CONDITION', 0x9113);
    define('GL_SYNC_STATUS', 0x9114);
    define('GL_SYNC_FLAGS', 0x9115);
    define('GL_SYNC_FENCE', 0x9116);
    define('GL_SYNC_GPU_COMMANDS_COMPLETE', 0x9117);
    define('GL_UNSIGNALED', 0x9118);
    define('GL_SIGNALED', 0x9119);
    define('GL_ALREADY_SIGNALED', 0x911A);
    define('GL_TIMEOUT_EXPIRED', 0x911B);
    define('GL_CONDITION_SATISFIED', 0x911C);
    define('GL_WAIT_FAILED', 0x911D);
    define('GL_TEXTURE_2D_MULTISAMPLE', 0x9100);
    define('GL_PROXY_TEXTURE_2D_MULTISAMPLE', 0x9101);
    define('GL_TEXTURE_2D_MULTISAMPLE_ARRAY', 0x9102);
    define('GL_PROXY_TEXTURE_2D_MULTISAMPLE_ARRAY', 0x9103);
    define('GL_TEXTURE_BINDING_2D_MULTISAMPLE', 0x9104);
    define('GL_TEXTURE_BINDING_2D_MULTISAMPLE_ARRAY', 0x9105);
    define('GL_TEXTURE_SAMPLES', 0x9106);
    define('GL_TEXTURE_FIXED_SAMPLE_LOCATIONS', 0x9107);
    define('GL_SAMPLER_2D_MULTISAMPLE', 0x9108);
    define('GL_INT_SAMPLER_2D_MULTISAMPLE', 0x9109);
    define('GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE', 0x910A);
    define('GL_SAMPLER_2D_MULTISAMPLE_ARRAY', 0x910B);
    define('GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY', 0x910C);
    define('GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY', 0x910D);
    define('GL_MAX_COLOR_TEXTURE_SAMPLES', 0x910E);
    define('GL_MAX_DEPTH_TEXTURE_SAMPLES', 0x910F);
    define('GL_MAX_INTEGER_SAMPLES', 0x9110);
    define('GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE', 0x8CD0);
    define('GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME', 0x8CD1);
    define('GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL', 0x8CD2);
    define('GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE', 0x8CD3);
    define('GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER', 0x8CD4);
    define('GL_FRAMEBUFFER_COMPLETE', 0x8CD5);
    define('GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT', 0x8CD6);
    define('GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT', 0x8CD7);
    define('GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER', 0x8CDB);
    define('GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER', 0x8CDC);
    define('GL_FRAMEBUFFER_UNSUPPORTED', 0x8CDD);
    define('GL_MAX_COLOR_ATTACHMENTS', 0x8CDF);
    define('GL_COLOR_ATTACHMENT0', 0x8CE0);
    define('GL_COLOR_ATTACHMENT1', 0x8CE1);
    define('GL_COLOR_ATTACHMENT2', 0x8CE2);
    define('GL_COLOR_ATTACHMENT3', 0x8CE3);
    define('GL_COLOR_ATTACHMENT4', 0x8CE4);
    define('GL_COLOR_ATTACHMENT5', 0x8CE5);
    define('GL_COLOR_ATTACHMENT6', 0x8CE6);
    define('GL_COLOR_ATTACHMENT7', 0x8CE7);
    define('GL_COLOR_ATTACHMENT8', 0x8CE8);
    define('GL_COLOR_ATTACHMENT9', 0x8CE9);
    define('GL_COLOR_ATTACHMENT10', 0x8CEA);
    define('GL_COLOR_ATTACHMENT11', 0x8CEB);
    define('GL_COLOR_ATTACHMENT12', 0x8CEC);
    define('GL_COLOR_ATTACHMENT13', 0x8CED);
    define('GL_COLOR_ATTACHMENT14', 0x8CEE);
    define('GL_COLOR_ATTACHMENT15', 0x8CEF);
    define('GL_COLOR_ATTACHMENT16', 0x8CF0);
    define('GL_COLOR_ATTACHMENT17', 0x8CF1);
    define('GL_COLOR_ATTACHMENT18', 0x8CF2);
    define('GL_COLOR_ATTACHMENT19', 0x8CF3);
    define('GL_COLOR_ATTACHMENT20', 0x8CF4);
    define('GL_COLOR_ATTACHMENT21', 0x8CF5);
    define('GL_COLOR_ATTACHMENT22', 0x8CF6);
    define('GL_COLOR_ATTACHMENT23', 0x8CF7);
    define('GL_COLOR_ATTACHMENT24', 0x8CF8);
    define('GL_COLOR_ATTACHMENT25', 0x8CF9);
    define('GL_COLOR_ATTACHMENT26', 0x8CFA);
    define('GL_COLOR_ATTACHMENT27', 0x8CFB);
    define('GL_COLOR_ATTACHMENT28', 0x8CFC);
    define('GL_COLOR_ATTACHMENT29', 0x8CFD);
    define('GL_COLOR_ATTACHMENT30', 0x8CFE);
    define('GL_COLOR_ATTACHMENT31', 0x8CFF);
    define('GL_DEPTH_ATTACHMENT', 0x8D00);
    define('GL_STENCIL_ATTACHMENT', 0x8D20);
    define('GL_FRAMEBUFFER', 0x8D40);
    define('GL_RENDERBUFFER', 0x8D41);
    define('GL_RENDERBUFFER_WIDTH', 0x8D42);
    define('GL_RENDERBUFFER_HEIGHT', 0x8D43);
    define('GL_RENDERBUFFER_INTERNAL_FORMAT', 0x8D44);
    define('GL_STENCIL_INDEX1', 0x8D46);
    define('GL_STENCIL_INDEX4', 0x8D47);
    define('GL_STENCIL_INDEX8', 0x8D48);
    define('GL_STENCIL_INDEX16', 0x8D49);
    define('GL_RENDERBUFFER_RED_SIZE', 0x8D50);
    define('GL_RENDERBUFFER_GREEN_SIZE', 0x8D51);
    define('GL_RENDERBUFFER_BLUE_SIZE', 0x8D52);
    define('GL_RENDERBUFFER_ALPHA_SIZE', 0x8D53);
    define('GL_RENDERBUFFER_DEPTH_SIZE', 0x8D54);
    define('GL_RENDERBUFFER_STENCIL_SIZE', 0x8D55);
    define('GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE', 0x8D56);
    define('GL_MAX_SAMPLES', 0x8D57);
    define('GL_MAP_READ_BIT', 0x0001);
    define('GL_MAP_WRITE_BIT', 0x0002);
    define('GL_MAP_INVALIDATE_RANGE_BIT', 0x0004);
    define('GL_MAP_INVALIDATE_BUFFER_BIT', 0x0008);
    define('GL_MAP_FLUSH_EXPLICIT_BIT', 0x0010);
    define('GL_MAP_UNSYNCHRONIZED_BIT', 0x0020);
    define('GL_VERTEX_ARRAY_BINDING', 0x85B5);
    define('GL_R8_SNORM', 0x8F94);
    define('GL_RG8_SNORM', 0x8F95);
    define('GL_RGB8_SNORM', 0x8F96);
    define('GL_RGBA8_SNORM', 0x8F97);
    define('GL_R16_SNORM', 0x8F98);
    define('GL_RG16_SNORM', 0x8F99);
    define('GL_RGB16_SNORM', 0x8F9A);
    define('GL_RGBA16_SNORM', 0x8F9B);
    define('GL_SIGNED_NORMALIZED', 0x8F9C);
    define('GL_PRIMITIVE_RESTART', 0x8F9D);
    define('GL_PRIMITIVE_RESTART_INDEX', 0x8F9E);
    define('GL_COPY_READ_BUFFER', 0x8F36);
    define('GL_COPY_WRITE_BUFFER', 0x8F37);
    define('GL_DRAW_INDIRECT_BUFFER', 0x8F3F);
    define('GL_DRAW_INDIRECT_BUFFER_BINDING', 0x8F43);
    define('GL_DOUBLE_MAT2', 0x8F46);
    define('GL_DOUBLE_MAT3', 0x8F47);
    define('GL_DOUBLE_MAT4', 0x8F48);
    define('GL_DOUBLE_MAT2x3', 0x8F49);
    define('GL_DOUBLE_MAT2x4', 0x8F4A);
    define('GL_DOUBLE_MAT3x2', 0x8F4B);
    define('GL_DOUBLE_MAT3x4', 0x8F4C);
    define('GL_DOUBLE_MAT4x2', 0x8F4D);
    define('GL_DOUBLE_MAT4x3', 0x8F4E);
    define('GL_UNIFORM_BUFFER', 0x8A11);
    define('GL_UNIFORM_BUFFER_BINDING', 0x8A28);
    define('GL_UNIFORM_BUFFER_START', 0x8A29);
    define('GL_UNIFORM_BUFFER_SIZE', 0x8A2A);
    define('GL_MAX_VERTEX_UNIFORM_BLOCKS', 0x8A2B);
    define('GL_MAX_GEOMETRY_UNIFORM_BLOCKS', 0x8A2C);
    define('GL_MAX_FRAGMENT_UNIFORM_BLOCKS', 0x8A2D);
    define('GL_MAX_COMBINED_UNIFORM_BLOCKS', 0x8A2E);
    define('GL_MAX_UNIFORM_BUFFER_BINDINGS', 0x8A2F);
    define('GL_MAX_UNIFORM_BLOCK_SIZE', 0x8A30);
    define('GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS', 0x8A31);
    define('GL_MAX_COMBINED_GEOMETRY_UNIFORM_COMPONENTS', 0x8A32);
    define('GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS', 0x8A33);
    define('GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT', 0x8A34);
    define('GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH', 0x8A35);
    define('GL_ACTIVE_UNIFORM_BLOCKS', 0x8A36);
    define('GL_UNIFORM_TYPE', 0x8A37);
    define('GL_UNIFORM_SIZE', 0x8A38);
    define('GL_UNIFORM_NAME_LENGTH', 0x8A39);
    define('GL_UNIFORM_BLOCK_INDEX', 0x8A3A);
    define('GL_UNIFORM_OFFSET', 0x8A3B);
    define('GL_UNIFORM_ARRAY_STRIDE', 0x8A3C);
    define('GL_UNIFORM_MATRIX_STRIDE', 0x8A3D);
    define('GL_UNIFORM_IS_ROW_MAJOR', 0x8A3E);
    define('GL_UNIFORM_BLOCK_BINDING', 0x8A3F);
    define('GL_UNIFORM_BLOCK_DATA_SIZE', 0x8A40);
    define('GL_UNIFORM_BLOCK_NAME_LENGTH', 0x8A41);
    define('GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS', 0x8A42);
    define('GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES', 0x8A43);
    define('GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER', 0x8A44);
    define('GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER', 0x8A45);
    define('GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER', 0x8A46);
    define('GL_CONTEXT_CORE_PROFILE_BIT', 0x00000001);
    define('GL_CONTEXT_COMPATIBILITY_PROFILE_BIT', 0x00000002);
    define('GL_SYNC_FLUSH_COMMANDS_BIT', 0x00000001);
    define('GL_RGB10_A2UI', 0x906F);
    define('GL_TEXTURE_CUBE_MAP_ARRAY', 0x9009);
    define('GL_TEXTURE_BINDING_CUBE_MAP_ARRAY', 0x900A);
    define('GL_PROXY_TEXTURE_CUBE_MAP_ARRAY', 0x900B);
    define('GL_SAMPLER_CUBE_MAP_ARRAY', 0x900C);
    define('GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW', 0x900D);
    define('GL_INT_SAMPLER_CUBE_MAP_ARRAY', 0x900E);
    define('GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY', 0x900F);
    define('GL_DOUBLE_VEC2', 0x8FFC);
    define('GL_DOUBLE_VEC3', 0x8FFD);
    define('GL_DOUBLE_VEC4', 0x8FFE);
    define('GL_IMPLEMENTATION_COLOR_READ_TYPE', 0x8B9A);
    define('GL_IMPLEMENTATION_COLOR_READ_FORMAT', 0x8B9B);
    define('GL_LOW_FLOAT', 0x8DF0);
    define('GL_MEDIUM_FLOAT', 0x8DF1);
    define('GL_HIGH_FLOAT', 0x8DF2);
    define('GL_LOW_INT', 0x8DF3);
    define('GL_MEDIUM_INT', 0x8DF4);
    define('GL_HIGH_INT', 0x8DF5);
    define('GL_SHADER_COMPILER', 0x8DFA);
    define('GL_SHADER_BINARY_FORMATS', 0x8DF8);
    define('GL_NUM_SHADER_BINARY_FORMATS', 0x8DF9);
    define('GL_MAX_VERTEX_UNIFORM_VECTORS', 0x8DFB);
    define('GL_MAX_VARYING_VECTORS', 0x8DFC);
    define('GL_MAX_FRAGMENT_UNIFORM_VECTORS', 0x8DFD);
    define('GL_RGB565', 0x8D62);
    define('GL_PROGRAM_BINARY_RETRIEVABLE_HINT', 0x8257);
    define('GL_PROGRAM_SEPARABLE', 0x8258);
    define('GL_ACTIVE_PROGRAM', 0x8259);
    define('GL_PROGRAM_PIPELINE_BINDING', 0x825A);
    define('GL_MAX_VIEWPORTS', 0x825B);
    define('GL_VIEWPORT_SUBPIXEL_BITS', 0x825C);
    define('GL_VIEWPORT_BOUNDS_RANGE', 0x825D);
    define('GL_LAYER_PROVOKING_VERTEX', 0x825E);
    define('GL_VIEWPORT_INDEX_PROVOKING_VERTEX', 0x825F);
    define('GL_UNDEFINED_VERTEX', 0x8260);
    define('GL_PROGRAM_BINARY_LENGTH', 0x8741);
    define('GL_VERTEX_SHADER_BIT', 0x00000001);
    define('GL_FRAGMENT_SHADER_BIT', 0x00000002);
    define('GL_GEOMETRY_SHADER_BIT', 0x00000004);
    define('GL_TESS_CONTROL_SHADER_BIT', 0x00000008);
    define('GL_TESS_EVALUATION_SHADER_BIT', 0x00000010);
    define('GL_ALL_SHADER_BITS', 0xFFFFFFFF);
    define('GLFW_VERSION_MAJOR', 3);
    define('GLFW_VERSION_MINOR', 3);
    define('GLFW_VERSION_REVISION', 5);
    define('GLFW_TRUE', 1);
    define('GLFW_FALSE', GLFW_FALSE);
    define('GLFW_RELEASE', GLFW_RELEASE);
    define('GLFW_PRESS', 1);
    define('GLFW_REPEAT', 2);
    define('GLFW_HAT_CENTERED', GLFW_HAT_CENTERED);
    define('GLFW_HAT_UP', 1);
    define('GLFW_HAT_RIGHT', 2);
    define('GLFW_HAT_DOWN', 4);
    define('GLFW_HAT_LEFT', 8);
    define('GLFW_KEY_SPACE', 32);
    define('GLFW_KEY_APOSTROPHE', 39);
    define('GLFW_KEY_COMMA', 44);
    define('GLFW_KEY_MINUS', 45);
    define('GLFW_KEY_PERIOD', 46);
    define('GLFW_KEY_SLASH', 47);
    define('GLFW_KEY_SEMICOLON', 59);
    define('GLFW_KEY_EQUAL', 61);
    define('GLFW_KEY_A', 65);
    define('GLFW_KEY_B', 66);
    define('GLFW_KEY_C', 67);
    define('GLFW_KEY_D', 68);
    define('GLFW_KEY_E', 69);
    define('GLFW_KEY_F', 70);
    define('GLFW_KEY_G', 71);
    define('GLFW_KEY_H', 72);
    define('GLFW_KEY_I', 73);
    define('GLFW_KEY_J', 74);
    define('GLFW_KEY_K', 75);
    define('GLFW_KEY_L', 76);
    define('GLFW_KEY_M', 77);
    define('GLFW_KEY_N', 78);
    define('GLFW_KEY_O', 79);
    define('GLFW_KEY_P', 80);
    define('GLFW_KEY_Q', 81);
    define('GLFW_KEY_R', 82);
    define('GLFW_KEY_S', 83);
    define('GLFW_KEY_T', 84);
    define('GLFW_KEY_U', 85);
    define('GLFW_KEY_V', 86);
    define('GLFW_KEY_W', 87);
    define('GLFW_KEY_X', 88);
    define('GLFW_KEY_Y', 89);
    define('GLFW_KEY_Z', 90);
    define('GLFW_KEY_LEFT_BRACKET', 91);
    define('GLFW_KEY_BACKSLASH', 92);
    define('GLFW_KEY_RIGHT_BRACKET', 93);
    define('GLFW_KEY_GRAVE_ACCENT', 96);
    define('GLFW_KEY_ESCAPE', 256);
    define('GLFW_KEY_ENTER', 257);
    define('GLFW_KEY_TAB', 258);
    define('GLFW_KEY_BACKSPACE', 259);
    define('GLFW_KEY_INSERT', 260);
    define('GLFW_KEY_DELETE', 261);
    define('GLFW_KEY_RIGHT', 262);
    define('GLFW_KEY_LEFT', 263);
    define('GLFW_KEY_DOWN', 264);
    define('GLFW_KEY_UP', 265);
    define('GLFW_KEY_PAGE_UP', 266);
    define('GLFW_KEY_PAGE_DOWN', 267);
    define('GLFW_KEY_HOME', 268);
    define('GLFW_KEY_END', 269);
    define('GLFW_KEY_CAPS_LOCK', 280);
    define('GLFW_KEY_SCROLL_LOCK', 281);
    define('GLFW_KEY_NUM_LOCK', 282);
    define('GLFW_KEY_PRINT_SCREEN', 283);
    define('GLFW_KEY_PAUSE', 284);
    define('GLFW_KEY_KP_DECIMAL', 330);
    define('GLFW_KEY_KP_DIVIDE', 331);
    define('GLFW_KEY_KP_MULTIPLY', 332);
    define('GLFW_KEY_KP_SUBTRACT', 333);
    define('GLFW_KEY_KP_ADD', 334);
    define('GLFW_KEY_KP_ENTER', 335);
    define('GLFW_KEY_KP_EQUAL', 336);
    define('GLFW_KEY_LEFT_SHIFT', 340);
    define('GLFW_KEY_LEFT_CONTROL', 341);
    define('GLFW_KEY_LEFT_ALT', 342);
    define('GLFW_KEY_LEFT_SUPER', 343);
    define('GLFW_KEY_RIGHT_SHIFT', 344);
    define('GLFW_KEY_RIGHT_CONTROL', 345);
    define('GLFW_KEY_RIGHT_ALT', 346);
    define('GLFW_KEY_RIGHT_SUPER', 347);
    define('GLFW_KEY_MENU', 348);
    define('GLFW_KEY_LAST', GLFW_KEY_MENU);
    define('GLFW_MOD_SHIFT', 0x0001);
    define('GLFW_MOD_CONTROL', 0x0002);
    define('GLFW_MOD_ALT', 0x0004);
    define('GLFW_MOD_SUPER', 0x0008);
    define('GLFW_MOD_CAPS_LOCK', 0x0010);
    define('GLFW_MOD_NUM_LOCK', 0x0020);
    define('GLFW_MOUSE_BUTTON_LAST', GLFW_MOUSE_BUTTON_8);
    define('GLFW_MOUSE_BUTTON_LEFT', GLFW_MOUSE_BUTTON_1);
    define('GLFW_MOUSE_BUTTON_RIGHT', GLFW_MOUSE_BUTTON_2);
    define('GLFW_MOUSE_BUTTON_MIDDLE', GLFW_MOUSE_BUTTON_3);
    define('GLFW_JOYSTICK_LAST', GLFW_JOYSTICK_16);
    define('GLFW_GAMEPAD_BUTTON_A', GLFW_GAMEPAD_BUTTON_A);
    define('GLFW_GAMEPAD_BUTTON_B', 1);
    define('GLFW_GAMEPAD_BUTTON_X', 2);
    define('GLFW_GAMEPAD_BUTTON_Y', 3);
    define('GLFW_GAMEPAD_BUTTON_LEFT_BUMPER', 4);
    define('GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER', 5);
    define('GLFW_GAMEPAD_BUTTON_BACK', 6);
    define('GLFW_GAMEPAD_BUTTON_START', 7);
    define('GLFW_GAMEPAD_BUTTON_GUIDE', 8);
    define('GLFW_GAMEPAD_BUTTON_LEFT_THUMB', 9);
    define('GLFW_GAMEPAD_BUTTON_RIGHT_THUMB', 10);
    define('GLFW_GAMEPAD_BUTTON_DPAD_UP', 11);
    define('GLFW_GAMEPAD_BUTTON_DPAD_RIGHT', 12);
    define('GLFW_GAMEPAD_BUTTON_DPAD_DOWN', 13);
    define('GLFW_GAMEPAD_BUTTON_DPAD_LEFT', 14);
    define('GLFW_GAMEPAD_BUTTON_LAST', GLFW_GAMEPAD_BUTTON_DPAD_LEFT);
    define('GLFW_GAMEPAD_BUTTON_CROSS', GLFW_GAMEPAD_BUTTON_A);
    define('GLFW_GAMEPAD_BUTTON_CIRCLE', GLFW_GAMEPAD_BUTTON_B);
    define('GLFW_GAMEPAD_BUTTON_SQUARE', GLFW_GAMEPAD_BUTTON_X);
    define('GLFW_GAMEPAD_BUTTON_TRIANGLE', GLFW_GAMEPAD_BUTTON_Y);
    define('GLFW_GAMEPAD_AXIS_LEFT_X', GLFW_GAMEPAD_AXIS_LEFT_X);
    define('GLFW_GAMEPAD_AXIS_LEFT_Y', 1);
    define('GLFW_GAMEPAD_AXIS_RIGHT_X', 2);
    define('GLFW_GAMEPAD_AXIS_RIGHT_Y', 3);
    define('GLFW_GAMEPAD_AXIS_LEFT_TRIGGER', 4);
    define('GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER', 5);
    define('GLFW_GAMEPAD_AXIS_LAST', GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER);
    define('GLFW_NO_ERROR', GLFW_NO_ERROR);
    define('GLFW_NOT_INITIALIZED', 0x00010001);
    define('GLFW_NO_CURRENT_CONTEXT', 0x00010002);
    define('GLFW_INVALID_ENUM', 0x00010003);
    define('GLFW_INVALID_VALUE', 0x00010004);
    define('GLFW_OUT_OF_MEMORY', 0x00010005);
    define('GLFW_API_UNAVAILABLE', 0x00010006);
    define('GLFW_VERSION_UNAVAILABLE', 0x00010007);
    define('GLFW_PLATFORM_ERROR', 0x00010008);
    define('GLFW_FORMAT_UNAVAILABLE', 0x00010009);
    define('GLFW_NO_WINDOW_CONTEXT', 0x0001000A);
    define('GLFW_FOCUSED', 0x00020001);
    define('GLFW_ICONIFIED', 0x00020002);
    define('GLFW_RESIZABLE', 0x00020003);
    define('GLFW_VISIBLE', 0x00020004);
    define('GLFW_DECORATED', 0x00020005);
    define('GLFW_AUTO_ICONIFY', 0x00020006);
    define('GLFW_FLOATING', 0x00020007);
    define('GLFW_MAXIMIZED', 0x00020008);
    define('GLFW_CENTER_CURSOR', 0x00020009);
    define('GLFW_TRANSPARENT_FRAMEBUFFER', 0x0002000A);
    define('GLFW_HOVERED', 0x0002000B);
    define('GLFW_FOCUS_ON_SHOW', 0x0002000C);
    define('GLFW_RED_BITS', 0x00021001);
    define('GLFW_GREEN_BITS', 0x00021002);
    define('GLFW_BLUE_BITS', 0x00021003);
    define('GLFW_ALPHA_BITS', 0x00021004);
    define('GLFW_DEPTH_BITS', 0x00021005);
    define('GLFW_STENCIL_BITS', 0x00021006);
    define('GLFW_ACCUM_RED_BITS', 0x00021007);
    define('GLFW_ACCUM_GREEN_BITS', 0x00021008);
    define('GLFW_ACCUM_BLUE_BITS', 0x00021009);
    define('GLFW_ACCUM_ALPHA_BITS', 0x0002100A);
    define('GLFW_AUX_BUFFERS', 0x0002100B);
    define('GLFW_STEREO', 0x0002100C);
    define('GLFW_SAMPLES', 0x0002100D);
    define('GLFW_SRGB_CAPABLE', 0x0002100E);
    define('GLFW_REFRESH_RATE', 0x0002100F);
    define('GLFW_DOUBLEBUFFER', 0x00021010);
    define('GLFW_CLIENT_API', 0x00022001);
    define('GLFW_CONTEXT_VERSION_MAJOR', 0x00022002);
    define('GLFW_CONTEXT_VERSION_MINOR', 0x00022003);
    define('GLFW_CONTEXT_REVISION', 0x00022004);
    define('GLFW_CONTEXT_ROBUSTNESS', 0x00022005);
    define('GLFW_OPENGL_FORWARD_COMPAT', 0x00022006);
    define('GLFW_OPENGL_DEBUG_CONTEXT', 0x00022007);
    define('GLFW_OPENGL_PROFILE', 0x00022008);
    define('GLFW_CONTEXT_RELEASE_BEHAVIOR', 0x00022009);
    define('GLFW_CONTEXT_NO_ERROR', 0x0002200A);
    define('GLFW_CONTEXT_CREATION_API', 0x0002200B);
    define('GLFW_SCALE_TO_MONITOR', 0x0002200C);
    define('GLFW_COCOA_RETINA_FRAMEBUFFER', 0x00023001);
    define('GLFW_COCOA_FRAME_NAME', 0x00023002);
    define('GLFW_COCOA_GRAPHICS_SWITCHING', 0x00023003);
    define('GLFW_NO_API', GLFW_NO_API);
    define('GLFW_OPENGL_API', 0x00030001);
    define('GLFW_OPENGL_ES_API', 0x00030002);
    define('GLFW_NO_ROBUSTNESS', GLFW_NO_ROBUSTNESS);
    define('GLFW_NO_RESET_NOTIFICATION', 0x00031001);
    define('GLFW_LOSE_CONTEXT_ON_RESET', 0x00031002);
    define('GLFW_OPENGL_ANY_PROFILE', GLFW_OPENGL_ANY_PROFILE);
    define('GLFW_OPENGL_CORE_PROFILE', 0x00032001);
    define('GLFW_OPENGL_COMPAT_PROFILE', 0x00032002);
    define('GLFW_CURSOR', 0x00033001);
    define('GLFW_STICKY_KEYS', 0x00033002);
    define('GLFW_STICKY_MOUSE_BUTTONS', 0x00033003);
    define('GLFW_LOCK_KEY_MODS', 0x00033004);
    define('GLFW_RAW_MOUSE_MOTION', 0x00033005);
    define('GLFW_CURSOR_NORMAL', 0x00034001);
    define('GLFW_CURSOR_HIDDEN', 0x00034002);
    define('GLFW_CURSOR_DISABLED', 0x00034003);
    define('GLFW_ANY_RELEASE_BEHAVIOR', GLFW_ANY_RELEASE_BEHAVIOR);
    define('GLFW_RELEASE_BEHAVIOR_FLUSH', 0x00035001);
    define('GLFW_RELEASE_BEHAVIOR_NONE', 0x00035002);
    define('GLFW_NATIVE_CONTEXT_API', 0x00036001);
    define('GLFW_EGL_CONTEXT_API', 0x00036002);
    define('GLFW_OSMESA_CONTEXT_API', 0x00036003);
    define('GLFW_ARROW_CURSOR', 0x00036001);
    define('GLFW_IBEAM_CURSOR', 0x00036002);
    define('GLFW_CROSSHAIR_CURSOR', 0x00036003);
    define('GLFW_HAND_CURSOR', 0x00036004);
    define('GLFW_HRESIZE_CURSOR', 0x00036005);
    define('GLFW_VRESIZE_CURSOR', 0x00036006);
    define('GLFW_CONNECTED', 0x00040001);
    define('GLFW_DISCONNECTED', 0x00040002);
    define('GLFW_JOYSTICK_HAT_BUTTONS', 0x00050001);
    define('GLFW_COCOA_CHDIR_RESOURCES', 0x00051001);
    define('GLFW_COCOA_MENUBAR', 0x00051002);
}
