namespace GL\Math 
{
    <?php foreach($mathObjects as $obj) : ?> 
    class <?php echo $obj->name; ?> 
    {
<?php if ($obj->isVector()) : ?>
<?php foreach($obj->getPropIt() as $i => $prop) : ?>
        /**
         * Virtual property for "<?php echo $prop; ?>" (<?php echo $i; ?>)
         */
        public float $<?php echo $prop; ?>;

<?php endforeach; ?>
<?php foreach($obj->getAltPropIt() as $i => $prop) : ?>
        /**
         * Virtual property for "<?php echo $prop; ?>" (<?php echo $i; ?>)
         */
        public float $<?php echo $prop; ?>;

<?php endforeach; ?>
<?php endif; ?>
        
        /**
         * Constructor
         */
        public function __construct(<?php echo $obj->getPhpArgs(); ?>) {}

<?php if ($obj->isVector()) : ?>
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
        public function dot(<?php echo $obj->name; ?> $right) : float {}

        /**
         * Returns the distance between this vector and another
         * 
         * @return float
         */
        public function distance(<?php echo $obj->name; ?> $right) : float {}

        /**
         * Returns squared distance between this vector and another
         * 
         * @return float
         */
        public function distance2(<?php echo $obj->name; ?> $right) : float {}

        /**
         * Returns a normalized version of this vector
         */
        public function normalize() : <?php echo $obj->name; ?> {}

        /**
         * Creates a new <?php echo $obj->name; ?> where each component is x if x >= 0; otherwise, -x
         */
        public function abs() : <?php echo $obj->name; ?> {}
<?php elseif($obj->isMatrix()) : ?>

        /**
         * Constructs and returns a new matrix based on the given array of values
         */
        public static function fromArray(array $values) : <?php echo $obj->name; ?> {}

        /**
         * Creates and returns a copy of the current matrix
         */
        public function copy() : <?php echo $obj->name; ?> {}
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
<?php endif; ?>
        public function __toString() : string {}
    }
<?php endforeach; ?>
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
<?php foreach($buffers as $buffer) : ?>

    class <?php echo $buffer->name; ?> implements BufferInterface {

        /**
         * Constructs a new <?php echo $buffer->name; ?>, internally (<?php echo $buffer->type; ?>)
         * 
         * @param null|array<<?php echo $buffer->getValuePHPType(); ?>> $intialData Inital data to be pushed into the buffer.
         */
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}

        /**
         * pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = <?php echo $buffer->getValuePHPType() === 'int' ? '123' : '3.14'; ?>`.
         *
         * @param <?php echo $buffer->getValuePHPType(); ?> $value The value to be pushed into the buffer.
         *
         * @return void 
         */
        public function push(<?php echo $buffer->getValuePHPType(); ?> $value) : void {}

        /**
         * pushes an array of values into the buffer. This works the same as when you pass inital data to the constructor.
         *
         * @param array<<?php echo $buffer->getValuePHPType(); ?>> $values The values to be pushed into the buffer.
         *
         * @return void
         */
        public function pushArray(array $values) : void {}

<?php if ($buffer->name == 'FloatBuffer') : ?>
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
<?php endif; ?>

        /**
         * Fills the buffer with $count amount of values. The second argument is the value that is filled in.
         *
         * @param int $count The number of elements to fill.
         * @param <?php echo $buffer->getValuePHPType(); ?> $value The value that will be filled in.
         *
         * @return void 
         */
        public function fill(int $count, <?php echo $buffer->getValuePHPType(); ?> $value) : void {}
        
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
<?php endforeach; ?>
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
<?php foreach($functions as $func) : ?>
<?php echo tabulate($func->getFunctionPHPCommentBlock()); ?> 
    <?php echo $func->getPHPStub(); ?> 
<?php endforeach; ?> 


    /**
     * Constants
     * ----------------------------------------------------------------------------
     */
<?php foreach($constants as $const) : ?>
<?php if ($const->isForwardDefinition) : ?>
    define('<?php echo $const->name; ?>', <?php echo $const->definitionValueString; ?>);
<?php else : ?>
//define('a', 'stable');
<?php endif; ?>
<?php endforeach; ?>
}
