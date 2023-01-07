
/** 
 * @generate-function-entries
 * ##generate-class-entries
 */

namespace GL\Geometry
{
    class ObjFileParser
    {   
        public readonly array $materials;

        public readonly array $groups;

        public readonly array $objects;

        /**
         * Obj. file parser constructor.
         * IMPORTANT: This obj. file parser does ONLY support triangulated meshes!
         */
        public function __construct(string $file) {}

        public function getVertices(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : \GL\Buffer\FloatBuffer {}

        public function getIndexedVertices(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : \GL\Geometry\ObjFileParser\Mesh {}

        public function getMeshes(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : array {}

        public function getIndexedMeshes(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : array {}
    }
}

namespace GL\Geometry\ObjFileParser
{
    class Resource {}

    class Mesh {
        public readonly ?Material $material;

        public readonly FloatBuffer $vertices;

        public readonly ?UIntBuffer $indices; 
    }

    class Material
    {
        public readonly string $name;

        public function __construct() {}
    }

    class Group
    {
        public readonly string $name;

        public function __construct() {}
    }

    class Texture
    {
        public function __construct() {}
    }
}

namespace GL\Texture
{
    class Texture2D {
        public static function fromDisk(string $path) : Texture2D {}
        public function buffer() : \GL\Buffer\UByteBuffer {}
        public function width() : int {}
        public function height() : int {}
        public function channels() : int {}
        public function writeJPG(string $path, int $quality = 100) : void {}
    }
}

namespace GL\Math 
{
    class GLM {
        public static function radians(float $degrees) : float {}
        public static function angle(float $radians) : float {}
        public static function triangleNormal(Vec3 $p1, Vec3 $p2, Vec3 $p3) : Vec3 {}
        public static function normalize(Vec2|Vec3|Vec4 $vec) : Vec2|Vec3|Vec4 {}
    }

<?php foreach($mathObjects as $obj) : ?> 
    class <?php echo $obj->name; ?> {
        public function __construct(<?php echo $obj->getPhpArgs(); ?>) {}
        public function copy() : <?php echo $obj->name; ?> {}
<?php if ($obj->isVector()) : ?>
        // static
        public static function normalized(<?php echo $obj->name; ?> $vec) : <?php echo $obj->name; ?> {}
        public static function distance(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : float {}
        public static function distance2(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : float {}
        public static function dot(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : float {}
        // member function
        public function length() : float {}
        public function distanceTo(<?php echo $obj->name; ?> $right) : float {}
        public function distance2To(<?php echo $obj->name; ?> $right) : float {}
        public function normalize() : void {}
        public function abs() : void {}
<?php if ($obj->size === 3) : ?>
        public static function cross(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : <?php echo $obj->name; ?> {}
<?php endif; ?>
<?php elseif($obj->isMatrix()) : ?>
        public static function fromArray(array $values) : <?php echo $obj->name; ?> {}
        public static function inverted(<?php echo $obj->name; ?> $matrix) : <?php echo $obj->name; ?> {}
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
        public function translate(Vec3 $translation) : void {}
        public function rotate(float $angle, Vec3 $axis) : void {}
        public function determinant() : float {}
<?php elseif($obj->isQuat()) : ?>
        public static function fromMat4(Mat4 $matrix) : <?php echo $obj->name; ?> {}
        public static function fromVec4(Vec4 $vec) : <?php echo $obj->name; ?> {}
        public static function inverted(<?php echo $obj->name; ?> $quat) : <?php echo $obj->name; ?> {}
        public static function normalized(<?php echo $obj->name; ?> $quat) : <?php echo $obj->name; ?> {} 
        public function normalize() : void {}
        public function length() : float {}
        public function eulerAngles() : Vec3 {}
        public function rotate(float $angle, Vec3 $axis) : void {}
        public function inverse() : void {}
        public function mat4() : Mat4 {}
<?php endif; ?>
        public function __toString() : string {}
    }
<?php endforeach; ?>
};

namespace GL\Buffer 
{   
    interface BufferInterface {
        public function __construct(?array $initalData = null) {}
        public function clear() : void {}
        public function size() : int {}
        public function capacity() : int {}
        public function reserve(int $size) : void {}
    }
<?php foreach($buffers as $buffer) : ?>

    class <?php echo $buffer->name; ?> implements BufferInterface {
        public function __construct(?array $initalData = null) {}
        public function __toString() : string {}
        public function push(<?php echo $buffer->getValuePHPType(); ?> $value) : void {}
        public function pushArray(array $values) : void {}
<?php if ($buffer->name == 'FloatBuffer') : ?>
        public function pushVec2(GL\Math\Vec2 $vec) : void {}
        public function pushVec3(GL\Math\Vec3 $vec) : void {}
        public function pushVec4(GL\Math\Vec4 $vec) : void {}
        public function pushMat4(GL\Math\Mat4 $matrix) : void {}
<?php endif; ?>
        public function fill(int $count, <?php echo $buffer->getValuePHPType(); ?> $value) : void {}
        public function clear() : void {}
        public function size() : int {}
        public function capacity() : int {}
        public function reserve(int $size) : void {}
    }
<?php endforeach; ?>
};

namespace {
    /**
     * Constants
     * ----------------------------------------------------------------------------
     */
<?php foreach($constants as $const) : //var_dump($const); die; ?>
<?php if ($const->isForwardDefinition) : ?>
    // const <?php echo $const->name; ?> = <?php echo $const->definitionValueString; ?>;
<?php else : ?>
    // const <?php echo $const->name; ?> = <?php echo $const->definitionValueString; ?>;
<?php endif; ?>
<?php endforeach; ?>

    /**
     * Functions
     * ----------------------------------------------------------------------------
     */
<?php foreach($functions as $func) : ?>
    <?php echo $func->getPHPStub(); ?>
<?php endforeach; ?> 
}
