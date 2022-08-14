namespace GL\Math 
{
<?php foreach($mathObjects as $obj) : ?> 
    class <?php echo $obj->name; ?> {
        public function __construct(<?php echo $obj->getPhpArgs(); ?>) {}
        public function length() : float {}
        public function dot(<?php echo $obj->name; ?> $right) : float {}
        public function distance(<?php echo $obj->name; ?> $right) : float {}
        public function distance2(<?php echo $obj->name; ?> $right) : float {}
        public function normalize() : <?php echo $obj->name; ?> {}
        public function abs() : <?php echo $obj->name; ?> {}
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
