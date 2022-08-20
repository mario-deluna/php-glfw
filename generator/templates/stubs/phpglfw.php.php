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
