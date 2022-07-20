<?php 
namespace PGL\Math 
{
    class Vec3 {
        /**
         * FOo
         */
        public function length() : float {}
        public function normalize() : Vec3 {}
        public function abs() : Vec3 {}
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
};
