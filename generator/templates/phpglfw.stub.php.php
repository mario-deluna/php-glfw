
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
        public readonly ?\GL\Buffer\Vec3 $aabbMin;
        public readonly ?\GL\Buffer\Vec3 $aabbMax;
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
        public static function fromDisk(string $path, int $requestedChannelCount = 0, bool $flipVertically = true) : Texture2D {}
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
        public static function mix(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right, float $t) : <?php echo $obj->name; ?> {}
        public static function lerp(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right, float $t) : <?php echo $obj->name; ?> {}
        public static function slerp(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right, float $t) : <?php echo $obj->name; ?> {}

        // member function
        public function length() : float {}
        public function distanceTo(<?php echo $obj->name; ?> $right) : float {}
        public function distance2To(<?php echo $obj->name; ?> $right) : float {}
        public function normalize() : void {}
        public function abs() : void {}
<?php if ($obj->size === 3) : ?>
        public static function cross(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : <?php echo $obj->name; ?> {}
        public static function multiplyQuat(<?php echo $obj->name; ?> $left, Quat $right) : <?php echo $obj->name; ?> {}
<?php endif; ?>
<?php elseif($obj->isMatrix()) : ?>
        public static function fromArray(array $values) : <?php echo $obj->name; ?> {}
        public static function inverted(<?php echo $obj->name; ?> $matrix) : <?php echo $obj->name; ?> {}
        public static function multiplyQuat(<?php echo $obj->name; ?> $left, Quat $right) : <?php echo $obj->name; ?> {}
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
        public static function mix(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right, float $t) : <?php echo $obj->name; ?> {}
        public static function lerp(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right, float $t) : <?php echo $obj->name; ?> {}
        public static function slerp(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right, float $t) : <?php echo $obj->name; ?> {}
        public static function dot(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : float {}
        public static function multiply(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : <?php echo $obj->name; ?> {}
        public static function multiplyVec3(<?php echo $obj->name; ?> $quat, Vec3 $vec) : Vec3 {}
        public static function multiplyMat4(<?php echo $obj->name; ?> $quat, Mat4 $mat) : Mat4 {}
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

namespace GL\VectorGraphics
{
    class VGColor {
        //public static function rgb(float $r, float $g, float $b) : VGColor {}
        //public static function rgba(float $r, float $g, float $b, float $a) : VGColor {}
        //public static function irgb(int $r, int $g, int $b) : VGColor {}
        //public static function irgba(int $r, int $g, int $b, int $a) : VGColor {}
        //public static function fromVec4(\GL\Math\Vec4 $vec) : VGColor {}
        //public static function fromVec3(\GL\Math\Vec3 $vec) : VGColor {}

        public function __construct(float $r, float $g, float $b, float $a) {}
    }
    
    class VGPaint {
        //public static function fromImage(VGImage $image, float $cx, float $cy, float $w, float $h, float $angle, float $alpha = 1.0) : VGPaint {}
    }

    class VGImage {
        // public const REPEAT_NONE = 0;
        // public const REPEAT_X = 1;
        // public const REPEAT_Y = 2;
        // public const REPEAT_XY = 3;

        // public const FILTER_LINEAR = 0;
        // public const FILTER_NEAREST = 1;

        public function makePaint(float $cx, float $cy, float $w, float $h, float $angle = 0.0, float $alpha = 1.0) : VGPaint {}
    }

    class VGContext {
        // public const ANTIALIAS = 1;
        // public const STENCIL_STROKES = 2;
        // public const DEBUG = 4;

        public function __construct(int $flags = 0) {}
        public function fillColori(int $r, int $g, int $b, int $a) : void {}
        public function strokeColori(int $r, int $g, int $b, int $a) : void {}
        public function fillColorVec4(\GL\Math\Vec4 $vec) : void {}
        public function strokeColorVec4(\GL\Math\Vec4 $vec) : void {}

        public function imageFromTexture(
            \GL\Texture\Texture2D $texture,
            int $repeatMode = VGImage::REPEAT_NONE,
            int $filterMode = VGImage::FILTER_LINEAR
        ) : VGImage {}

        public function linearGradient(float $sx, float $sy, float $ex, float $ey, VGColor $icol, VGColor $ocol) : VGPaint {}
        public function boxGradient(float $x, float $y, float $w, float $h, float $r, float $f, VGColor $icol, VGColor $ocol) : VGPaint {}
        public function radialGradient(float $cx, float $cy, float $inr, float $outr, VGColor $icol, VGColor $ocol) : VGPaint {}
        //public function imagePattern(float $cx, float $cy, float $w, float $h, float $angle, float $alpha) : VGPaint {}

<?php foreach($vgContextFunctions as $func) : ?>
        public <?php echo $func->getPHPStub(); ?>
<?php endforeach; ?> 
    }
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
