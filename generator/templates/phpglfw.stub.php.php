
/** @generate-function-entries */
/** @generate-class-entries */
/**
 * Classes
 */
namespace GL\Math 
{
<?php foreach($mathObjects as $obj) : ?> 
    class <?php echo $obj->name; ?> {
        public function __construct(<?php echo $obj->getPhpArgs(); ?>) {}
<?php if ($obj->isVector()) : ?>
        public function length() : float {}
        public function dot(<?php echo $obj->name; ?> $right) : float {}
        public function distance(<?php echo $obj->name; ?> $right) : float {}
        public function distance2(<?php echo $obj->name; ?> $right) : float {}
        public function normalize() : <?php echo $obj->name; ?> {}
        public function abs() : <?php echo $obj->name; ?> {}
<?php elseif($obj->isMatrix()) : ?>
        public function copy() : <?php echo $obj->name; ?> {}
        public function row(int $index) : Vec4 {}
        public function setRow(int $index, Vec4 $row) : void {}
        public function col(int $index) : Vec4 {}
        public function setCol(int $index, Vec4 $col) : void {}
        public function lookAt(Vec3 $eye, Vec3 $center, Vec3 $up) : void {}
        public function perspective(float $fov, float $aspect, float $near, float $far) : void {}
        public function ortho(float $left, float $right, float $bottom, float $top, float $near, float $far) : void {}
        public function scale(Vec3 $scale) : void {}
        public function determinant() : float {}
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
    //define('a', 'stable');
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
