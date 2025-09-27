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
    class GLFWvidmode {
        public readonly int $width;
        public readonly int $height;
        public readonly int $redBits;
        public readonly int $greenBits;
        public readonly int $blueBits;
        public readonly int $refreshRate;
    }

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
    class GLM 
    {
        /**
         * Returns the given degrees in radians.
         *
         * @param float $degrees The degrees to convert to radians.
         * @return float radians.
         */
        public static function radians(float $degrees) : float {}

        /**
         * Returns the given radians in degrees.
         *
         * @param float $radians The radians to convert to degrees.
         * @return float degrees.
         */
        public static function angle(float $radians) : float {}

        public static function triangleNormal(GL\Math\Vec3 $p1, \GL\Math\Vec3 $p2, \GL\Math\Vec3 $p3) : \GL\Math\Vec3 {}

        /**
         * Returns a normalized vector from the given vector. (Vec2, Vec3, Vec4)
         *
         * @param GL\Math\Vec2|GL\Math\Vec3|GL\Math\Vec4 $vec The vector to normalize.
         * @return GL\Math\Vec2|GL\Math\Vec3|GL\Math\Vec4 The normalized vector.
         */
        public static function normalize(GL\Math\Vec2|GL\Math\Vec3|GL\Math\Vec4 $vec) : GL\Math\Vec2|GL\Math\Vec3|GL\Math\Vec4 {}
    }

    <?php foreach($mathObjects as $obj) : ?> 
    class <?php echo $obj->name; ?> 
    {
<?php if ($obj->isVector() || $obj->isQuat()) : ?>
<?php foreach($obj->getPropIt() as $i => $prop) : ?>
        /**
         * Virtual property for "<?php echo $prop; ?>" (<?php echo $i; ?>)
         */
        public float $<?php echo $prop; ?>;

<?php endforeach; ?>
<?php endif; ?>
<?php if ($obj->isVector()) : ?>
<?php foreach($obj->getAltPropIt() as $i => $prop) : ?>
        /**
         * Virtual property for "<?php echo $prop; ?>" (<?php echo $i; ?>)
         */
        public float $<?php echo $prop; ?>;

<?php endforeach; ?>
<?php endif; ?>
        

<?php if ($obj->isVector()) : ?>
        /**
         * Constructor
         */
        public function __construct(<?php echo $obj->getPhpArgs(); ?>) {}

        /**
         * Creates and returns a copy of the current <?php echo $obj->name; ?>.
         */
        public function copy() : <?php echo $obj->name; ?> {}

        /**
         * Returns the distance between the left and right vectors
         * 
         * ```php    
         * $distance = <?php echo $obj->name; ?>::distance($left, $right);
         * ```
         *
         * @param <?php echo $obj->name; ?> $left The left vector.
         * @param <?php echo $obj->name; ?> $right The right vector.
         * @return float The distance between the left and right vectors.
         */
        public static function distance(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : float {}
        
        /**
         * Returns the squared distance between the left and right vectors
         *
         * ```php
         * $distance = <?php echo $obj->name; ?>::distance2($left, $right);
         * ```
         *
         * @param <?php echo $obj->name; ?> $left The left vector.
         * @param <?php echo $obj->name; ?> $right The right vector.
         * @return float The squared distance between the left and right vectors.
         */
        public static function distance2(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : float {}

        /**
         * Retruns a normalized version of the given <?php echo $obj->name; ?>
         * 
         * ```php
         * $normalized = <?php echo $obj->name; ?>::normalize(new <?php echo $obj->name; ?>($x, $y, $z));
         * ```
         * 
         * @param <?php echo $obj->name; ?> $vec The vector to normalize.
         * @return <?php echo $obj->name; ?> The normalized vector.
         */
        public static function normalized(<?php echo $obj->name; ?> $vec) : <?php echo $obj->name; ?> {}
        
        /**
         * Returns the dot product of the left and right vectors
         * 
         * ```php
         * $dot = <?php echo $obj->name; ?>::dot($left, $right);
         * ```
         * 
         * @param <?php echo $obj->name; ?> $left The left vector.
         * @param <?php echo $obj->name; ?> $right The right vector.
         * @return float The dot product of the left and right vectors.
         */
        public static function dot(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : float {}

        /**
         * Linearly interpolates between the left and right vectors by the given t value.
         *
         * ```php
         * $mixed = <?php echo $obj->name; ?>::mix($left, $right, $t);
         * ```
         *
         * @param <?php echo $obj->name; ?> $left The left vector.
         * @param <?php echo $obj->name; ?> $right The right vector.
         * @param float $t The t value (progress / state) 0.0 == left, 1.0 == right.
         * @return <?php echo $obj->name; ?> The mixed vector.
         */
        public static function mix(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right, float $t) : <?php echo $obj->name; ?> {}

        /**
         * Linearly interpolates between the left and right vectors by the given t value.
         * This does exactly the same as mix..
         * 
         * ```php
         * $lerped = <?php echo $obj->name; ?>::lerp($left, $right, $t);
         * ```
         *
         * @param <?php echo $obj->name; ?> $left The left vector.
         * @param <?php echo $obj->name; ?> $right The right vector.
         * @param float $t The t value (progress / state) 0.0 == left, 1.0 == right.
         * @return <?php echo $obj->name; ?> The lerped vector.
         */
        public static function lerp(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right, float $t) : <?php echo $obj->name; ?> {}

        /**
         * Spherically interpolates between the left and right vectors by the given t value.
         * 
         * ```php
         * $slerped = <?php echo $obj->name; ?>::slerp($left, $right, $t);
         * ```
         * 
         * @param <?php echo $obj->name; ?> $left The left vector.
         * @param <?php echo $obj->name; ?> $right The right vector.
         * @param float $t The t value (progress / state) 0.0 == left, 1.0 == right.
         * @return <?php echo $obj->name; ?> The slerped vector.
         */
        public static function slerp(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right, float $t) : <?php echo $obj->name; ?> {}

        /**
         * Returns the length of the vector
         * 
         * @return float
         */
        public function length() : float {}

        /**
         * Returns the distance between this vector and another
         * 
         * @return float
         */
        public function distanceTo(<?php echo $obj->name; ?> $right) : float {}

        /**
         * Returns squared distance between this vector and another
         * 
         * @return float
         */
        public function distance2To(<?php echo $obj->name; ?> $right) : float {}

        /**
         * normalizes the current vector
         * 
         * @return void
         */
        public function normalize() : void {}

        /**
         * Makes each component x if x >= 0; otherwise, -x
         * 
         * @return void
         */
        public function abs() : void {}
        
<?php if ($obj->size === 3) : ?>
        /**
         * Returns the cross product of this vector and another
         * 
         * ```php
         * $cross = <?php echo $obj->name; ?>::cross($left, $right);
         * ```
         *  
         * @param <?php echo $obj->name; ?> $left The left vector.   
         * @param <?php echo $obj->name; ?> $right The right vector.     
         * @return <?php echo $obj->name; ?> The cross product of the left and right vectors.
         */
        public static function cross(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : <?php echo $obj->name; ?> {}

        /**
         * Vec3 * Quat
         * Multiplies the left vector by the right quaternion
         * Note: **This method only exists because there is a bug with the order of operation in PHP.**
         */
        public static function multiplyQuat(<?php echo $obj->name; ?> $left, Quat $right) : <?php echo $obj->name; ?> {}
<?php endif; ?>
<?php elseif($obj->isMatrix()) : ?>

        /**
         * Constructucts a new <?php echo $obj->name; ?> matrix
         * Does not take any arguments and always returns an identity matrix.
         * aka: 
         * ```
         * 1 0 0 0
         * 0 1 0 0
         * 0 0 1 0
         * 0 0 0 1         
         * ```
         */
        public function __construct(<?php echo $obj->getPhpArgs(); ?>) {}

        /**
         * Copys the current matrix
         *
         * Returns a new instance of the current matrix with the same values. This means that any modifications made to the returned matrix will not affect the current matrix. 
         * 
         * ```php
         * $copy = $matrix->copy();
         * ```
         *
         * @return <?php echo $obj->name; ?> The copy of the current matrix.
         */
        public function copy() : <?php echo $obj->name; ?> {}

        /**
         * Constructs and returns a new matrix based on the given array of values
         * 
         * ```php
         * $matrix = <?php echo $obj->name; ?>::fromArray([
         *     1, 0, 0, 0,
         *     0, 1, 0, 0,
         *     0, 0, 1, 0,
         *     0, 0, 0, 1
         * ]);
         * ```
         *
         * @param array $values The values to use for the matrix. (flat)
         * @return <?php echo $obj->name; ?> The new matrix.
         */
        public static function fromArray(array $values) : <?php echo $obj->name; ?> {}

        /**
         * Constructs and returns an inverse of the given matrix
         * 
         * ```php
         * $inverse = <?php echo $obj->name; ?>::inverse($matrix);
         * ```
         *
         * @param <?php echo $obj->name; ?> $matrix The matrix to invert.
         * @return <?php echo $obj->name; ?> The inverted matrix.
         */
        public static function inverted(<?php echo $obj->name; ?> $matrix) : <?php echo $obj->name; ?> {}

        /**
         * Mat4 * Quat
         * 
         * Multiplies the left matrix by the right quaternion
         *
         * Note: **This method only exists because there is a bug with the order of operation in PHP.**
         */
        public static function multiplyQuat(<?php echo $obj->name; ?> $left, Quat $right) : <?php echo $obj->name; ?> {}
        
        /**
         * Returns the row at the given index.
         *
         * Example usage:
         *
         * ```php
         * $matrix = Mat4::fromArray([
         *     [1.0, 2.0, 3.0, 4.0],
         *     [5.0, 6.0, 7.0, 8.0],
         *     [9.0, 10.0, 11.0, 12.0],
         *     [13.0, 14.0, 15.0, 16.0]
         * ]);
         *
         * // Get the first row
         * $row = $matrix->row(0);
         * // Expected result: Vec4(1.0, 2.0, 3.0, 4.0)
         * ```
         *
         * @param int $index The index of the row to return.
         * @return Vec4 The row at the given index.
         */
        public function row(int $index) : Vec4 {}

        /**
         * Sets the row at the given index to the given row
         *
         * Example usage:
         * ```php
         * $matrix = new Mat4();
         * $row = new Vec4(1, 2, 3, 4);
         * $matrix->setRow(0, $row);
         * ```
         *
         * @param int $index The index of the row to set.
         * @param Vec4 $row The row to set.
         * @return void
         */
        public function setRow(int $index, Vec4 $row) : void {}

        /**
         * Returns the column at the given index.
         *
         * This method retrieves a column from the matrix at the specified index and returns it as a Vec4 object.
         * 
         * Example:
         * ```php
         * $matrix = Mat4::fromArray([
         *     [1.0, 2.0, 3.0, 4.0],
         *     [5.0, 6.0, 7.0, 8.0],
         *     [9.0, 10.0, 11.0, 12.0],
         *     [13.0, 14.0, 15.0, 16.0]
         * ]);
         * 
         * $col = $matrix->col(0);
         * 
         * // Returns Vec4(1.0, 5.0, 9.0, 13.0)
         * ```
         *
         * @param int $index The index of the column to return.
         * @return Vec4 The column at the given index.
         */
        public function col(int $index) : Vec4 {}

        /**
         * Sets the column at the given index to the given column
         *
         * ```php
         * // Create a new matrix and set the second column
         * $matrix = new Mat4();
         * $col = new Vec4(1, 2, 3, 4);
         * $matrix->setCol(1, $col);
         * ```
         *
         * @param int $index The index of the column to set.
         * @param Vec4 $col The column to set.
         * @return void
         */
        public function setCol(int $index, Vec4 $col) : void {}

        /**
         * Sets the matrix to a lookAt matrix
         * 
         * The `lookAt()` method sets the matrix to a lookAt matrix based on the camera's position and orientation. 
         * It takes three parameters: `$eye`, `$center`, and `$up`, which are all instances of the `Vec3` class. 
         * 
         * The `$eye` parameter indicates the position of the camera, while `$center` indicates the point 
         * in space to look at. The `$up` parameter specifies the up vector, which determines the orientation of the camera.
         *
         * Example usage:
         *
         * ```php
         * // Create a new matrix
         * $matrix = new Mat4();
         *
         * // Set the matrix to a lookAt matrix
         * $matrix->lookAt(
         *    new Vec3(0, 0, 5), // eye
         *    new Vec3(0, 0, 0), // center
         *    new Vec3(0, 1, 0)  // up
         * );
         * ``` 
         *
         * This will create a new matrix and set it to a lookAt matrix with the camera positioned at `(0, 0, 5)`, 
         * looking at the origin `(0, 0, 0)`, with the up vector pointing in the positive y direction.
         *
         * @param Vec3 $eye The position of the camera.
         * @param Vec3 $center The position to look at.
         * @param Vec3 $up The up vector.
         * @return void
         */
        public function lookAt(Vec3 $eye, Vec3 $center, Vec3 $up) : void {}

        /**
         * Sets the matrix to a perspective matrix
         *
         * ```php
         * $matrix->perspective($fov, $aspect, $near, $far);
         * ```
         *
         * @param float $fov The field of view.
         * @param float $aspect The aspect ratio.
         * @param float $near The near plane.
         * @param float $far The far plane.
         * @return void
         */
        public function perspective(float $fov, float $aspect, float $near, float $far) : void {}

        /**
         * Sets the matrix to an orthographic matrix
         *
         * ```php
         * $matrix->ortho($left, $right, $bottom, $top, $near, $far);
         * ```
         *
         * @param float $left The left plane.
         * @param float $right The right plane.
         * @param float $bottom The bottom plane.
         * @param float $top The top plane.
         * @param float $near The near plane.
         * @param float $far The far plane.
         * @return void
         */
        public function ortho(float $left, float $right, float $bottom, float $top, float $near, float $far) : void {}

        /**
         * Tranposes the matrix
         * 
         * ```php
         * $matrix->transpose();
         * ```
         *
         * @return void
         */
        public function transpose() : void {}

        /**
         * Inverts the current matrix
         *
         * ```php
         * $matrix->inverse();
         * ```
         *
         * @return void
         */
        public function inverse() : void {}

        /**
         * Scale the matrix by the given vector
         * 
         * ```php
         * $matrix->scale(new Vec3(2, 2, 2));
         * ```
         */
        public function scale(Vec3 $scale) : void {}

        /**
         * Translates the matrix by the given vector
         *
         * ```php
         * $matrix->translate(new Vec3(1, 1, 1));
         * ```
         *
         * @param Vec3 $vector The vector to translate by.
         * @return void
         */
        public function translate(Vec3 $vector) : void {}

        /**
         * Rotates the matrix by the given angle around the given axis
         *
         * ```php
         * $matrix->rotate(GLM::radians(90), new Vec3(0, 1, 0));
         * ```
         *
         * @param float $angle The angle to rotate by.
         * @param Vec3 $axis The axis to rotate around.
         * @return void
         */
        public function rotate(float $angle, Vec3 $axis) : void {}

        /**
         * Retruns the determinant of the matrix
         *
         * ```php
         * $det = $matrix->determinant();
         * ```
         *
         * @return float The determinant of the matrix.
         */
        public function determinant() : float {}

<?php elseif($obj->isQuat()) : ?>

        /**
         * Constructor
         */
        public function __construct(<?php echo $obj->getPhpArgs(); ?>) {}

        /**
         * Creates and returns a copy of the current quaternion
         */
        public function copy() : <?php echo $obj->name; ?> {}

        /**
         * Constructs and returns a new quaternion based on the given Mat4 matrix
         *
         * ```php
         * $quat = <?php echo $obj->name; ?>::fromMat4($matrix);
         * ```
         *
         * @param Mat4 $matrix The matrix to construct the quaternion from.
         * @return <?php echo $obj->name; ?> The constructed quaternion.
         */
        public static function fromMat4(Mat4 $matrix) : <?php echo $obj->name; ?> {}

        /**
         * Constructs and returns a new quaternion based on the given Vec4 vector.
         * The quaternion is arragned as (w, x, y, z), while the vector is arranged as (x, y, z, w).
         * This method will swap the x and w components.
         *
         * ```php
         * $quat = <?php echo $obj->name; ?>::fromVec4($vector);
         * ```
         *
         * @param Vec4 $vector The vector to construct the quaternion from.
         * @return <?php echo $obj->name; ?> The constructed quaternion.
         */
        public static function fromVec4(Vec4 $vec) : <?php echo $obj->name; ?> {}

        /**
         * Constructs and return a inverted quaternion based on the given one
         * 
         * ```php
         * $inverted = <?php echo $obj->name; ?>::inverted($quat);
         * ```
         *
         * @param <?php echo $obj->name; ?> $quat The quaternion to invert.
         * @return <?php echo $obj->name; ?> The inverted quaternion.
         */
        public static function inverted(<?php echo $obj->name; ?> $quat) : <?php echo $obj->name; ?> {}

        /**
        * Constructs and returns a normalized quaternion based on the given one
        *
        * ```php
        * $normalized = <?php echo $obj->name; ?>::normalized($quat);
        * ```
        *
        * @param <?php echo $obj->name; ?> $quat The quaternion to normalize.
        * @return <?php echo $obj->name; ?> The normalized quaternion.
        */
        public static function normalized(<?php echo $obj->name; ?> $quat) : <?php echo $obj->name; ?> {} 

        /**
         * Performs a linear interpolation between two quaternions and returns the resulting quaternion.
         *
         * ```php
         * $result = <?php echo $obj->name; ?>::mix($left, $right, $t);
         * ```
         *
         * @param <?php echo $obj->name; ?> $left The left quaternion.
         * @param <?php echo $obj->name; ?> $right The right quaternion.
         * @param float $t The interpolation factor.
         * @return <?php echo $obj->name; ?> The interpolated quaternion.
         */
        public static function mix(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right, float $t) : <?php echo $obj->name; ?> {}

        /**
         * Performs a linear interpolation between two quaternions and returns the resulting quaternion.
         * This function is identical to `mix`.
         * 
         * ```php
         * $result = <?php echo $obj->name; ?>::lerp($left, $right, $t);
         * ```
         *
         * @param <?php echo $obj->name; ?> $left The left quaternion.
         * @param <?php echo $obj->name; ?> $right The right quaternion.
         * @param float $t The interpolation factor.
         * @return <?php echo $obj->name; ?> The interpolated quaternion.
         */
        public static function lerp(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right, float $t) : <?php echo $obj->name; ?> {}

        /**
         * Performs a spherical linear interpolation between two quaternions and returns the resulting quaternion.
         *
         * ```php
         * $result = <?php echo $obj->name; ?>::slerp($left, $right, $t);
         * ```
         * 
         * @param <?php echo $obj->name; ?> $left The left quaternion.
         * @param <?php echo $obj->name; ?> $right The right quaternion.
         * @param float $t The interpolation factor.
         * @return <?php echo $obj->name; ?> The interpolated quaternion.
         */
        public static function slerp(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right, float $t) : <?php echo $obj->name; ?> {}

        /**
         * Returns the dot product of two quaternions.
         * 
         * ```php
         * $dot = <?php echo $obj->name; ?>::dot($left, $right);
         * ```
         * 
         * @param <?php echo $obj->name; ?> $left The left quaternion.
         * @param <?php echo $obj->name; ?> $right The right quaternion.
         * @return float The dot product.
         */
        public static function dot(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : float {}

        /**
         * Quat * Quat
         * Multiplies two quaternions and returns the result.
         * Note: **This method only exists because there is a bug with the order of operation in PHP.**
         */
        public static function multiply(<?php echo $obj->name; ?> $left, <?php echo $obj->name; ?> $right) : <?php echo $obj->name; ?> {}

        /**
         * Quat * Vec3
         * Multiplies a quaternion and a vector and returns the result.
         * Note: **This method only exists because there is a bug with the order of operation in PHP.**
         */
        public static function multiplyVec3(<?php echo $obj->name; ?> $quat, Vec3 $vec) : Vec3 {}

        /**
         * Quat * Mat4
         * Multiplies a quaternion and a matrix and returns the result.
         * Note: **This method only exists because there is a bug with the order of operation in PHP.**
         */
        public static function multiplyMat4(<?php echo $obj->name; ?> $quat, Mat4 $mat) : Mat4 {}

        /**
         * The same as `normalized()`, but modifies the current quaternion instead of creating a new one.
         *
         * ```php
         * $quat->normalize();
         * ```
         */
        public function normalize() : void {}

        /**
         * Returns the length of the quaternion
         * 
         * ```php
         * $length = $quat->length();
         * ```
         */
        public function length() : float {}

        /**
         * Returns the quaternion represented as euler angles (in radians)
         * 
         * ```php
         * $euler = $quat->eulerAngles();
         * ```
         *
         * @return Vec3 The euler angles.
         */
        public function eulerAngles() : Vec3 {}

        /**
         * Rotates the quaternion by the given angle (in radians) around the given axis
         * 
         * ```php
         * $quat->rotate(GLM::radians(45.0), new Vec3(0, 1, 0));
         * ```
         * 
         * @param float $angle The angle to rotate by (in radians)
         * @param Vec3 $axis The axis to rotate around
         */
        public function rotate(float $angle, Vec3 $axis) : void {}

        /**
         * Invseres the current quaternion, this is basically the same as `inverted()` but 
         * modifies the current quaternion instead of creating a new one.
         *
         * ```php
         * $quat->inverse();
         * ```
         */
        public function inverse() : void {}

        /**
         * Constructs a Mat4 matrix based on the current quaternion
         *
         * ```php
         * $matrix = $quat->mat4();
         * ```
         *
         * @return Mat4 The matrix representation of the quaternion.
         */
        public function mat4() : Mat4 {}
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

<?php if ($buffer->name == 'UByteBuffer') : ?>
        /**
         * Pushes a string into the buffer
         */
        public function pushString(string $string) : void {}

<?php elseif ($buffer->name == 'FloatBuffer') : ?>
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

        /**
         * Returns the internal data of the buffer as a binary string.
         * 
         * @return string The binary string of the buffer.
         */
        public function dump() : string {}
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

        /**
         * The min of the axis aligned bounding box of the mesh.
         * 
         * @var \GL\Buffer\Vec3|null
         */
        public readonly ?\GL\Buffer\Vec3 $aabbMin;

        /**
         * The max of the axis aligned bounding box of the mesh.
         * 
         * @var \GL\Buffer\Vec3|null
         */
        public readonly ?\GL\Buffer\Vec3 $aabbMax;
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
         * The ambient texture of the material
         *
         * @var \GL\Geometry\ObjFileParser\Texture|null $ambientTexture
         */
        public readonly ?Texture $ambientTexture;

        /**
         * The diffuse texture of the material
         *
         * @var \GL\Geometry\ObjFileParser\Texture|null $diffuseTexture
         */
        public readonly ?Texture $diffuseTexture;

        /**
         * The specular texture of the material
         *
         * @var \GL\Geometry\ObjFileParser\Texture|null $specularTexture
         */
        public readonly ?Texture $specularTexture;

        /**
         * The emissive texture of the material
         *
         * @var \GL\Geometry\ObjFileParser\Texture|null $emissiveTexture
         */
        public readonly ?Texture $emissiveTexture;

        /**
         * The transmittance texture of the material
         *
         * @var \GL\Geometry\ObjFileParser\Texture|null $transmittanceTexture
         */
        public readonly ?Texture $transmittanceTexture;

        /**
         * The shininess texture of the material
         *
         * @var \GL\Geometry\ObjFileParser\Texture|null $shininessTexture
         */
        public readonly ?Texture $shininessTexture;

        /**
         * The index of refraction texture of the material
         *
         * @var \GL\Geometry\ObjFileParser\Texture|null $indexOfRefractionTexture
         */
        public readonly ?Texture $indexOfRefractionTexture;

        /**
         * The dissolve texture of the material
         *
         * @var \GL\Geometry\ObjFileParser\Texture|null $dissolveTexture
         */
        public readonly ?Texture $dissolveTexture;

        /**
         * The bump texture of the material
         *
         * @var \GL\Geometry\ObjFileParser\Texture|null $bumpTexture
         */
        public readonly ?Texture $bumpTexture;

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
        /**
         * The name of the texture file
         * 
         * @var string $name|null
         */
        public readonly ?string $name;

        /**
         * The path to the texture file on the filesystem (absolute)
         * 
         * @var string $path|null
         */
        public readonly ?string $path;

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

        /**
         * Almost the same as getVertices but returns an Mesh object instead.
         * The mesh object is a wrapper around the vertex data buffer and the index buffer.
         * 
         * Please see the `getVertices` docs for more information about the layout string.
         *  
         * !!! note
         *     Even you your object file is already indexed, this method will reindex the data.
         *     This is required to generate the normals and tangents. As a result this method 
         *     is a lot slower than getVertices.
         * 
         * @param string $layout The layout of the buffer.
         * @param \GL\Geometry\ObjFileParser\Group|null $group The group to get the vertex data for.
         * 
         * @return \GL\Geometry\Mesh The generated mesh object
         */
        public function getIndexedVertices(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : \GL\Geometry\ObjFileParser\Mesh {}

        /**
         * Returns an array of Mesh objects grouped by material. 
         * In many situations your object / model is split into multiple submeshes, each with its own material.
         * with every material there are usally different material properties associated. This usally requires
         * a uniform to be updated, a different shader to be used or a different texture to be bound.
         * This is where `getMeshes` comes in handy. It will return an array of Mesh objects, each with its own material.
         * 
         * Please see the `getVertices` docs for more information about the layout string.
         * 
         * @param string $layout The layout of the buffer.
         * @param \GL\Geometry\ObjFileParser\Group|null $group The group to get the vertex data for.
         * 
         * @return array<\GL\Geometry\ObjFileParser\Mesh>
         */
        public function getMeshes(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : array {}

        public function getIndexedMeshes(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : array {}
    }
}

namespace GL\Texture
{
    /**
     * The Texture2D class is part of the PHP-GLFW OpenGL extension.
     * It loads images / textures from common formats like PNG, JPG, GIF, BMP, TGA etc. and converts the raw bitmap to a `GL\UByteBuffer` instance.
     */
    class Texture2D 
    {
        public const CHANNEL_R = 1;
        public const CHANNEL_GRAY = 1;
        public const CHANNEL_RG = 2;
        public const CHANNEL_GRAY_ALPHA = 2;
        public const CHANNEL_RGB = 3;
        public const CHANNEL_RGBA = 4;

        /**
         * Loads a texture / image from a file on disk and returns a Texture2D object.
         *
         * @param string $file The path to the image file to load.
         * @return \GL\Texture\Texture2D The loaded texture object.
         */
        public static function fromDisk(string $path) : Texture2D {}

        /**
         * Loads a texture / image from a buffer and returns a Texture2D object.
         * 
         * The buffer is not copied, the Texture2D object will hold a reference to the buffer given.
         */
        public static function fromBuffer(int $width, int $height, \GL\Buffer\UByteBuffer $buffer, int $channels = Texture2D::CHANNEL_RGBA) : Texture2D {}

        /**
         * Returns a reference to the internal `UByteBuffer` instance of the current texture.
         * 
         * @return \GL\UByteBuffer The loaded image data.
         */
        public function buffer() : \GL\Buffer\UByteBuffer {}

        /**
         * Returns the width of the image.
         *
         * @return int The width of the image.
         */
        public function width() : int {}

        /**
         * Returns the height of the image.
         *
         * @return int The height of the image.
         */
        public function height() : int {}

        /**
         * Returns the number of channels of the image.
         *
         * @return int The number of channels of the image.
         */
        public function channels() : int {}

        /**
         * Writes the image data to a file on disk. (JPEG)
         * 
         * @param string $file The path to the file to write to.
         * @param int $quality The quality of the image. (0 - 100)
         *
         * @return void
         */
        public function writeJPG(string $path, int $quality = 100) : void {}

        /**
         * Writes the image data to a file on disk. (PNG)
         *
         * @param string $file The path to the file to write to.
         */
        public function writePNG(string $path) : void {}

        /**
         * Writes the image data to a file on disk. (BMP)
         *
         * @param string $file The path to the file to write to.
         */
        public function writeBMP(string $path) : void {}

        /**
         * Writes the image data to a file on disk. (TGA)
         *
         * @param string $file The path to the file to write to.
         */
        public function writeTGA(string $path) : void {}
    }
}

namespace GL
{
    class Noise 
    {
        /**
         * Samples a Perlin noise value.
         *
         * The `wrap` parameters allow you to generate wraparound noise, which repeats at powers of two.
         * A value of 0 indicates "no wrapping." Due to the implementation details, the noise always wraps
         * every 256 units, regardless of the specified wrap value.
         * 
         * The implementation is based on "stb_perlin.h" by Sean Barrett, Jack Mott, Jordan Peck.
         *
         * @param float $x      The x-coordinate.
         * @param float $y      The y-coordinate.
         * @param float $z      The z-coordinate.
         * @param int   $wrapX  The wrap value for the x-axis.
         * @param int   $wrapY  The wrap value for the y-axis.
         * @param int   $wrapZ  The wrap value for the z-axis.
         * @param int   $seed   The seed that determines the variation of the noise function.
         *                      Only the lowest 8 bits of the seed are used.
         */
        public static function perlin(float $x, float $y, float $z, int $wrapX = 0, int $wrapY = 0, int $wrapZ = 0, int $seed = 0) : float {}
        
        /**
         * Samples a "ridged" fractal perlin value
         * 
         * @param float $x The x coordinate
         * @param float $y The y coordinate
         * @param float $z The z coordinate
         * @param float $lacunarity the spacing between successive octaves (default `2.0`).
         * @param float $gain the relative weighting applied to each successive octave (default `0.5`).
         * @param float $offset the offset used to invert the ridges (default `1.0`).
         * @param int $octaves the number of octaves to sum (default `6`).
         *                     This determines the number of noise3() calls and directly affects runtime performance.
         *
         * @return float The ridged noise value.
         * 
         * @see stb_perlin_ridge_noise3
         *
         * The implementation is based on "stb_perlin.h" by Sean Barrett, Jack Mott, Jordan Peck.
         */
        public static function ridge(float $x, float $y, float $z, float $lacunarity = 2.0, float $gain = 0.5, float $offset = 1.0, int $octaves = 6) : float {}
        
        /**
         * Samples a "fractal Brownian motion" perlin value
         *
         * @param float $x The x coordinate
         * @param float $y The y coordinate
         * @param float $z The z coordinate
         * @param float $lacunarity the spacing between successive octaves (default `2.0`).
         * @param float $gain the relative weighting applied to each successive octave (default `0.5`).
         * @param int $octaves the number of octaves to sum (default `6`).
         *                    This determines the number of noise3() calls and directly affects runtime performance.
         *
         * @return float The fractal Brownian motion noise value.
         *
         * @see stb_perlin_fbm_noise3
         * 
         * The implementation is based on "stb_perlin.h" by Sean Barrett, Jack Mott, Jordan Peck.
         */
        public static function fbm(float $x, float $y, float $z, float $lacunarity = 2.0, float $gain = 0.5, int $octaves = 6) : float {}
        
        /**
         * Samples a "turbulence" perlin value
         * 
         * @param float $x The x coordinate
         * @param float $y The y coordinate
         * @param float $z The z coordinate
         * @param float $lacunarity the spacing between successive octaves (default `2.0`).
         * @param float $gain the relative weighting applied to each successive octave (default `0.5`).
         * @param int $octaves the number of octaves to sum (default `6`).
         *                   This determines the number of noise3() calls and directly affects runtime performance.
         *
         * @return float The turbulence noise value.
         *
         * @see stb_perlin_turbulence_noise3
         *
         * The implementation is based on "stb_perlin.h" by Sean Barrett, Jack Mott, Jordan Peck.
         */
        public static function turbulence(float $x, float $y, float $z, float $lacunarity = 2.0, float $gain = 0.5, int $octaves = 6) : float {}

        /**
         * Fill a FloatBuffer with a 2D perlin noise pattern.
         * 
         * With `offsetX` and `offsetY` you can move the noise pattern around.
         * Think of the scale as the zoom level of the noise pattern.
         * The `wrapX` and `wrapY` parameters allow you to generate wraparound noise, which repeats at powers of two.
         *
         * @param \GL\Buffer\FloatBuffer $buffer The buffer to fill.
         * @param int $width The width of the map.
         * @param int $height The height of the map.
         * @param float $scale The scale of the noise pattern.
         * @param float $offsetX The x offset of the noise pattern.
         * @param float $offsetY The y offset of the noise pattern.
         * @param int $wrapX The wrap value for the x-axis.
         * @param int $wrapY The wrap value for the y-axis.
         * @param int $seed The seed that determines the variation of the noise function.
         */
        public static function perlinFill2D(\GL\Buffer\FloatBuffer $buffer, int $width, int $height, float $scale, float $offsetX = 0, float $offsetY = 0, int $wrapX = 0, int $wrapY = 0, int $seed = 0) : void {}
        
        /**
         * Fill a FloatBuffer with a 2D ridged noise pattern.
         *
         * With `offsetX` and `offsetY` you can move the noise pattern around.
         * Think of the `scale` as the zoom level of the noise pattern.
         * The `wrapX` and `wrapY` parameters allow you to generate wraparound noise, which repeats at powers of two.
         *  
         * @param \GL\Buffer\FloatBuffer $buffer The buffer to fill.
         * @param int $width The width of the map.
         * @param int $height The height of the map.
         * @param float $scale The scale of the noise pattern.
         * @param float $offsetX The x offset of the noise pattern.
         * @param float $offsetY The y offset of the noise pattern.
         * @param float $lacunarity the spacing between successive octaves (default `2.0`).
         * @param float $gain the relative weighting applied to each successive octave (default `0.5`).
         * @param float $offset the offset used to invert the ridges (default `1.0`).
         * @param int $octaves the number of octaves to sum (default `6`).
         *                     This determines the number of noise3() calls and directly affects runtime performance.
         */
        public static function ridgeFill2D(\GL\Buffer\FloatBuffer $buffer, int $width, int $height, float $scale, float $offsetX = 0, float $offsetY = 0, float $lacunarity = 2.0, float $gain = 0.5, float $offset = 1.0, int $octaves = 6) : void {}
        
        /**
         * Fill a FloatBuffer with a 2D fractal Brownian motion (fBm) noise pattern.
         *
         * With `offsetX` and `offsetY` you can move the noise pattern around.
         * Think of the `scale` as the zoom level of the noise pattern.
         * The `lacunarity` determines the frequency multiplier between successive octaves, 
         * and `gain` controls the amplitude scaling. The `octaves` parameter determines
         * the number of noise layers to sum, affecting both the detail and runtime performance.
         *
         * @param \GL\Buffer\FloatBuffer $buffer The buffer to fill.
         * @param int $width The width of the map.
         * @param int $height The height of the map. 
         * @param float $scale The scale of the noise pattern.
         * @param float $offsetX The x offset of the noise pattern.
         * @param float $offsetY The y offset of the noise pattern.
         * @param float $lacunarity The frequency multiplier between successive octaves (default `2.0`).
         * @param float $gain The amplitude scaling factor for successive octaves (default `0.5`).
         * @param int $octaves The number of octaves to sum (default `6`).
         */
        public static function fbmFill2D(\GL\Buffer\FloatBuffer $buffer, int $width, int $height, float $scale, float $offsetX = 0, float $offsetY = 0, float $lacunarity = 2.0, float $gain = 0.5, int $octaves = 6) : void {}
        
        /**
         * Fill a FloatBuffer with a 2D turbulence noise pattern.
         *
         * With `offsetX` and `offsetY` you can move the noise pattern around.
         * Think of the `scale` as the zoom level of the noise pattern.
         * The `lacunarity` determines the frequency multiplier between successive octaves, 
         * and `gain` controls the amplitude scaling. The `octaves` parameter determines
         * the number of noise layers to sum, affecting both the detail and runtime performance.
         *
         * @param \GL\Buffer\FloatBuffer $buffer The buffer to fill.
         * @param int $width The width of the map.
         * @param int $height The height of the map.
         * @param float $scale The scale of the noise pattern.
         * @param float $offsetX The x offset of the noise pattern.
         * @param float $offsetY The y offset of the noise pattern.
         * @param float $lacunarity The frequency multiplier between successive octaves (default `2.0`).
         * @param float $gain The amplitude scaling factor for successive octaves (default `0.5`).
         * @param int $octaves The number of octaves to sum (default `6`).
         */
        public static function turbulenceFill2D(\GL\Buffer\FloatBuffer $buffer, int $width, int $height, float $scale, float $offsetX = 0, float $offsetY = 0, float $lacunarity = 2.0, float $gain = 0.5, int $octaves = 6) : void {}
        
        /**
         * Fill a FloatBuffer with a 2D island-shaped noise pattern.
         *
         * This function generates a noise pattern that simulates islands by combining a noise pattern 
         * with a radial gradient. The `islandseed` controls the variation of the island shapes,
         * `scale` adjusts the overall size, and `islandmix` blends the noise pattern with the island shape.
         * The `lacunarity`, `gain`, and `octaves` parameters further control the noise detail and characteristics.
         *
         * @param \GL\Buffer\FloatBuffer $buffer The buffer to fill.
         * @param int $width The width of the map.
         * @param int $height The height of the map.
         * @param int $islandseed The seed for island shape variation (default `42`).
         * @param float $scale The scale of the noise pattern (default `1.0`).
         * @param float $islandmix The blend factor between the noise pattern and island shape (default `0.7`).
         * @param float $lacunarity The frequency multiplier between successive octaves (default `2.0`).
         * @param float $gain The amplitude scaling factor for successive octaves (default `0.5`).
         * @param int $octaves The number of octaves to sum (default `6`).
         */
        public static function islandFill2D(\GL\Buffer\FloatBuffer $buffer, int $width, int $height, int $islandseed = 42, float $scale = 1.0, float $islandmix = 0.7, float $lacunarity = 2.0, float $gain = 0.5, int $octaves = 6) : void {}
    }
}

namespace GL\Audio
{
    /**
     * The Engine class is the main audio engine that manages all audio playback.
     * It provides methods for loading sounds, controlling master volume, and 3D audio positioning.
     */
    class Engine
    {
        /**
         * Creates a new audio engine instance.
         * 
         * @param array $options Optional configuration array with the following keys:
         *   - listenerCount: int - Number of listeners (1 to 4, default is system dependent)
         *   - channels: int - Number of output channels (0 = use device default)
         *   - sampleRate: int - Sample rate in Hz (0 = use device default)
         *   - periodSizeInFrames: int - Period size in frames for low-latency (0 = use default)
         *   - periodSizeInMilliseconds: int - Period size in milliseconds (used if periodSizeInFrames is 0)
         *   - gainSmoothTimeInFrames: int - Smoothing time for gain changes in frames
         *   - gainSmoothTimeInMilliseconds: int - Smoothing time for gain changes in ms
         *   - defaultVolumeSmoothTimeInPCMFrames: int - Default volume smoothing time
         *   - noAutoStart: bool - Don't start the engine automatically (false by default)
         *   - monoExpansionMode: int - How to expand mono to multi-channel (use GL_MA_MONO_EXPANSION_MODE_* constants)
         */
        public function __construct(array $options = []) {}

        /**
         * Starts the audio engine.
         * 
         * @return void
         * @throws Error if the engine fails to start
         */
        public function start() : void {}

        /**
         * Stops the audio engine.
         * 
         * @return void
         * @throws Error if the engine fails to stop
         */
        public function stop() : void {}

        /**
         * Loads a sound from a file path.
         * 
         * @param string $filePath The path to the audio file to load.
         * @return Sound The loaded sound object.
         */
        public function load(string $filePath) : Sound {}
        
        /**
         * Loads a sound from a file path.
         * Alias for load() method.
         * 
         * @param string $filePath The path to the audio file to load.
         * @return Sound The loaded sound object.
         */
        public function soundFromDisk(string $filePath) : Sound {}

        /**
         * Sets the master volume for all sounds.
         * 
         * @param float $volume The master volume level (0.0 to 1.0).
         * @return void
         */
        public function setMasterVolume(float $volume) : void {}

        /**
         * Gets the current master volume.
         * 
         * @return float The current master volume level.
         */
        public function getMasterVolume() : float {}

        /**
         * Sets the listener position for 3D audio.
         * 
         * @param Vec3 $position The position vector of the listener.
         * @return void
         */
        public function setListenerPosition(\GL\Math\Vec3 $position) : void {}

        /**
         * Sets the listener direction for 3D audio.
         * 
         * @param Vec3 $direction The direction vector the listener is facing.
         * @return void
         */
        public function setListenerDirection(\GL\Math\Vec3 $direction) : void {}

        /**
         * Sets the listener world up vector for 3D audio.
         * 
         * @param Vec3 $worldUp The up vector defining the listener's orientation.
         * @return void
         */
        public function setListenerWorldUp(\GL\Math\Vec3 $worldUp) : void {}
    }

    /**
     * The Sound class represents an individual audio sound that can be played, paused, and controlled.
     */
    class Sound
    {
        /**
         * Plays the sound.
         * 
         * @return void
         */
        public function play() : void {}

        /**
         * Stops the sound and resets it to the beginning.
         * 
         * @return void
         */
        public function stop() : void {}

        /**
         * Sets the volume of the sound.
         * 
         * @param float $volume The volume level (0.0 to 1.0).
         * @return void
         */
        public function setVolume(float $volume) : void {}

        /**
         * Gets the current volume of the sound.
         * 
         * @return float The current volume level.
         */
        public function getVolume() : float {}

        /**
         * Sets the pitch of the sound.
         * 
         * @param float $pitch The pitch multiplier (1.0 = normal pitch).
         * @return void
         */
        public function setPitch(float $pitch) : void {}

        /**
         * Gets the current pitch of the sound.
         * 
         * @return float The current pitch multiplier.
         */
        public function getPitch() : float {}

        /**
         * Sets whether the sound should loop.
         * 
         * @param bool $loop Whether to loop the sound.
         * @return void
         */
        public function setLoop(bool $loop) : void {}

        /**
         * Gets whether the sound is set to loop.
         * 
         * @return bool Whether the sound is set to loop.
         */
        public function getLoop() : bool {}

        /**
         * Sets the pan (stereo positioning) of the sound.
         * 
         * @param float $pan The pan value (-1.0 = left, 0.0 = center, 1.0 = right).
         * @return void
         */
        public function setPan(float $pan) : void {}

        /**
         * Gets the current pan of the sound.
         * 
         * @return float The current pan value.
         */
        public function getPan() : float {}

        /**
         * Sets the 3D position of the sound in world space.
         * 
         * @param Vec3 $position The position vector (x, y, z).
         * @return void
         */
        public function setPosition(\GL\Math\Vec3 $position) : void {}

        /**
         * Gets the current 3D position of the sound.
         * 
         * @return Vec3 The current position vector.
         */
        public function getPosition() : \GL\Math\Vec3 {}

        /**
         * Sets the minimum distance for 3D audio attenuation.
         * 
         * @param float $distance The minimum distance.
         * @return void
         */
        public function setMinDistance(float $distance) : void {}

        /**
         * Gets the minimum distance for 3D audio attenuation.
         * 
         * @return float The minimum distance.
         */
        public function getMinDistance() : float {}

        /**
         * Sets the maximum distance for 3D audio rolloff.
         * 
         * @param float $distance The maximum distance.
         * @return void
         */
        public function setMaxDistance(float $distance) : void {}

        /**
         * Gets the maximum distance for 3D audio rolloff.
         * 
         * @return float The maximum distance.
         */
        public function getMaxDistance() : float {}

        /**
         * Sets the direction of the sound for directional audio effects.
         * 
         * @param Vec3 $direction The direction vector.
         * @return void
         */
        public function setDirection(\GL\Math\Vec3 $direction) : void {}

        /**
         * Gets the direction of the sound.
         * 
         * @return Vec3 The direction vector.
         */
        public function getDirection() : \GL\Math\Vec3 {}

        /**
         * Sets the velocity of the sound for Doppler effects.
         * 
         * @param Vec3 $velocity The velocity vector.
         * @return void
         */
        public function setVelocity(\GL\Math\Vec3 $velocity) : void {}

        /**
         * Gets the velocity of the sound.
         * 
         * @return Vec3 The velocity vector.
         */
        public function getVelocity() : \GL\Math\Vec3 {}

        /**
         * Fades the sound in from 0 to full volume over the specified duration.
         * 
         * @param float $duration The fade duration in seconds.
         * @return void
         */
        public function fadeIn(float $duration) : void {}

        /**
         * Fades the sound out from current volume to 0 over the specified duration.
         * 
         * @param float $duration The fade duration in seconds.
         * @return void
         */
        public function fadeOut(float $duration) : void {}

        /**
         * Sets a custom fade from one volume to another over the specified duration.
         * 
         * @param float $fromVolume The starting volume (0.0 to 1.0).
         * @param float $toVolume The target volume (0.0 to 1.0).
         * @param float $duration The fade duration in seconds.
         * @return void
         */
        public function setFade(float $fromVolume, float $toVolume, float $duration) : void {}

        /**
         * Gets the current fade volume.
         * 
         * @return float The current fade volume.
         */
        public function getCurrentFadeVolume() : float {}
    }
}

namespace GL\VectorGraphics
{
    class VGColor {
        public static function rgb(float $r, float $g, float $b) : VGColor {}
        public static function rgba(float $r, float $g, float $b, float $a) : VGColor {}
        /**
         * HSL color constructor
         * All values are in the range [0.0, 1.0]
         *
         * @param float $h Hue
         * @param float $s Saturation
         * @param float $l Lightness
         */
        public static function hsl(float $h, float $s, float $l) : VGColor {}

        /**
         * HSL with alpha color constructor
         * All values are in the range [0.0, 1.0]
         *
         * @param float $h Hue
         * @param float $s Saturation
         * @param float $l Lightness
         */
        public static function hsla(float $h, float $s, float $l, float $a) : VGColor {}

        /**
         * RGB color constructor from integer values
         * All values are in the range [0, 255]
         *
         * @param int $r Red
         * @param int $g Green
         * @param int $b Blue
         */
        public static function irgb(int $r, int $g, int $b) : VGColor {}

        /**
         * RGBA color constructor from integer values
         * All values are in the range [0, 255]
         *
         * @param int $r Red
         * @param int $g Green
         * @param int $b Blue
         * @param int $a Alpha
         */
        public static function irgba(int $r, int $g, int $b, int $a) : VGColor {}
        //public static function fromVec4(\GL\Math\Vec4 $vec) : VGColor {}
        //public static function fromVec3(\GL\Math\Vec3 $vec) : VGColor {}

        /**
         * Hex color constructor
         * You can pass a hex string with or without the `#` prefix. (e.g. `#FF0000` or `FF0000`)
         * 
         * Example:
         *     $color = VGColor::hex('#FF0000');
         *     $color = VGColor::hex('FF0000');
         *     $color = VGColor::hex('#000');
         * 
         * @param string $hex The hex string to convert to a color.
         */
        public static function hex(string $hex) : VGColor {}

        public static function red() : VGColor {}
        public static function green() : VGColor {}
        public static function blue() : VGColor {}
        public static function white() : VGColor {}
        public static function black() : VGColor {}
        public static function transparent() : VGColor {}
        public static function yellow() : VGColor {}
        public static function cyan() : VGColor {}
        public static function magenta() : VGColor {}
        public static function orange() : VGColor {}
        public static function pink() : VGColor {}
        public static function purple() : VGColor {}
        public static function brown() : VGColor {}
        public static function gray() : VGColor {}
        public static function darkGray() : VGColor {}
        public static function lightGray() : VGColor {}
        public static function random() : VGColor {}
        public static function randomGray() : VGColor {} 

        /**
         * Virtual property for the red component of the color
         */
        public float $r;

        /**
         * Virtual property for the green component of the color
         */
        public float $g;

        /**
         * Virtual property for the blue component of the color
         */
        public float $b;

        /**
         * Virtual property for the alpha component of the color
         */
        public float $a;

        public function __construct(float $r, float $g, float $b, float $a) {}

        /**
         * Returns the color as a Vec4 where each component represents Hue, Saturation, Lightness and Alpha respectively.
         */
        public function getHSLA() : \GL\Math\Vec4 {}

        /**
         * Returns the color as a Vec3 where each component represents Hue, Saturation and Lightness respectively.
         */
        public function getHSL() : \GL\Math\Vec3 {}

        /**
         * Returns the color as a Vec4 where each component represents Red, Green, Blue and Alpha respectively.
         */
        public function getVec4() : \GL\Math\Vec4 {}

        /**
         * Returns the color as a Vec3 where each component represents Red, Green and Blue respectively.
         */
        public function getVec3() : \GL\Math\Vec3 {}

        /**
         * Darkens the color by the specified amount.
         *
         * @param float $amount The amount to darken the color by.
         * @return VGColor The darkened color.
         */
        public function darken(float $amount) : VGColor {}

        /**
         * Lightens the color by the specified amount.
         *
         * @param float $amount The amount to lighten the color by.
         * @return VGColor The lightened color.
         */
        public function lighten(float $amount) : VGColor {}

        /**
         * Inverts the color.
         *
         * @return VGColor The inverted color.
         */
        public function invert() : VGColor {}
    }
    
    class VGPaint {
    }

    class VGImage {
        /**
         * No repeat pattern.
         */
        public const REPEAT_NONE = 0;

        /**
         * Repeat pattern in the X direction.
         */
        public const REPEAT_X = 1;

        /**
         * Repeat pattern in the Y direction.
         */
        public const REPEAT_Y = 2;

        /**
         * Repeat pattern in both X and Y directions.
         */
        public const REPEAT_XY = 3;

        /**
         * Linear filtering.
         */
        public const FILTER_LINEAR = 0;

        /**
         * Nearest-neighbor filtering.
         */
        public const FILTER_NEAREST = 1;
        
        /**
         * Creates a paint object of the current image that can be used to fill or stroke shapes.
         *
         * @param float $x The x-coordinate of the top left corner of the paint.
         * @param float $y The y-coordinate of the top left corner of the paint.
         * @param float $width The width of the paint.
         * @param float $height The height of the paint.
         * @param float $angle The angle of the paint in radians. (The rotation is around the top left corner of the paint.)
         * @param float $alpha The alpha value of the paint.
         */
        public function makePaint(float $x, float $y, float $w, float $h, float $angle = 0.0, float $alpha = 1.0) : VGPaint {}

        /**
         * Creates a paint object of the current image (from center) that can be used to fill or stroke shapes.
         * The image is centered around the given coordinates and also rotated around the center.
         *
         * @param float $cx The x-coordinate of the center of the paint.
         * @param float $cy The y-coordinate of the center of the paint.
         * @param float $width The width of the paint.
         * @param float $height The height of the paint.
         * @param float $angle The angle of the paint in radians. (The rotation is around the center of the paint.)
         * @param float $alpha The alpha value of the paint.
         */
        public function makePaintCentered(float $cx, float $cy, float $w, float $h, float $angle = 0.0, float $alpha = 1.0) : VGPaint {}
    }

    class VGAlign {
        /**
         * Align to the left.
         */
        public const LEFT = 1;

        /**
         * Align to the center horizontally.
         */
        public const CENTER = 2;

        /**
         * Align to the right.
         */
        public const RIGHT = 4;

        /**
         * Align to the top.
         */
        public const TOP = 8;

        /**
         * Align to the middle vertically.
         */
        public const MIDDLE = 16;

        /**
         * Align to the bottom.
         */
        public const BOTTOM = 32;

        /**
         * Align to the baseline.
         */
        public const BASELINE = 64;
    }

    class VGContext {
        /**
         * Enable antialiasing.
         * Provides smoother edges for shapes and text.
         */
        public const ANTIALIAS = 1;

        /**
         * Enable stencil strokes.
         * Allows for more accurate stroke rendering for overlapping shapes.
         */
        public const STENCIL_STROKES = 2;

        /**
         * Enable debug mode.
         * Adds additional error checks.
         */
        public const DEBUG = 4;

        /**
         * Counter-clockwise winding.
         * Used for defining solid shapes.
         */
        public const CCW = 1;

        /**
         * Clockwise winding.
         * Used for defining hole shapes.
         */
        public const CW = 2;

        /**
         * Solid fill. (Same as VGContext::CCW)
         * Used for filling paths.
         */
        public const SOLID = 1;

        /**
         * Hole fill. (Same as VGContext::CW)
         * Used for creating holes in paths.
         */
        public const HOLE = 2;

        /**
         * Butt line cap.
         */
        public const LINECAP_BUTT = 0;

        /**
         * Round line cap.
         */
        public const LINECAP_ROUND = 1;

        /**
         * Square line cap.
         */
        public const LINECAP_SQUARE = 2;

        /**
         * Bevel line join.
         */
        public const LINEJOIN_BEVEL = 3;

        /**
        * Miter line join.
        */
        public const LINEJOIN_MITER = 4;

        /**
         * VGContext Constructor 
         *
         * example: 
         * ```php
         * $context = new VGContext(VGContext::ANTIALIAS);
         * ```
         * 
         * @param int $flags The flags to use for the context.
         */
        public function __construct(int $flags = 0) {}

        /**
         * Sets the fill color using integer values.
         *
         * @param int $r The red component (0-255).
         * @param int $g The green component (0-255).
         * @param int $b The blue component (0-255).
         * @param int $a The alpha component (0-255), where 255 is fully opaque.
         */
        public function fillColori(int $r, int $g, int $b, int $a) : void {}

        /**
         * Sets the stroke color using integer values.
         *
         * @param int $r The red component (0-255).
         * @param int $g The green component (0-255).
         * @param int $b The blue component (0-255).
         * @param int $a The alpha component (0-255), where 255 is fully opaque.
         */
        public function strokeColori(int $r, int $g, int $b, int $a) : void {}

        /**
         * Sets the fill color using a Vec4 object.
         *
         * @param \GL\Math\Vec4 $vec A vector containing the RGBA components of the color.
         */
        public function fillColorVec4(\GL\Math\Vec4 $vec) : void {}

        /**
         * Sets the stroke color using a Vec4 object.
         *
         * @param \GL\Math\Vec4 $vec A vector containing the RGBA components of the color.
         */
        public function strokeColorVec4(\GL\Math\Vec4 $vec) : void {}

        /**
         * Transforms a point using the current transformation matrix.
         *
         * @param float $x The x-coordinate of the point.
         * @param float $y The y-coordinate of the point.
         * @return \GL\Math\Vec2 The transformed point as a Vec2 object.
         */
        public function transformPoint(float $x, float $y) : \GL\Math\Vec2 {}

        /**
         * Transforms a vector using the current transformation matrix.
         *
         * @param \GL\Math\Vec2 $vec The vector to transform.
         * @return \GL\Math\Vec2 The transformed vector.
         */
        public function transformVec2(\GL\Math\Vec2 $vec) : \GL\Math\Vec2 {}

        /**
         * Creates a VGImage object from a given texture. 
         * This will upload the texture to the GPU.
         *
         * ```php
         * $image = $vg->imageFromTexture($texture, VGImage::REPEAT_XY, VGImage::FILTER_LINEAR);
         * ```
         *
         * @param \GL\Texture\Texture2D $texture The texture to create the image from.
         * @param int $repeatMode This can be either VGImage::REPEAT_XY, VGImage::REPEAT_X, VGImage::REPEAT_Y, or VGImage::REPEAT_NONE.
         *                        This controls how the image is repeated when the shape is larger than the image. 
         *                        The default is VGImage::REPEAT_NONE.
         * @param int $filterMode This can be either VGImage::FILTER_LINEAR or VGImage::FILTER_NEAREST.
         *                        This controls how the image is filtered when it is scaled. 
         *                        The default is VGImage::FILTER_LINEAR.
         */
        public function imageFromTexture(
            \GL\Texture\Texture2D $texture,
            int $repeatMode = VGImage::REPEAT_NONE,
            int $filterMode = VGImage::FILTER_LINEAR
        ) : VGImage {}

        /**
         * Creates a VGImage object from a given texture handle. 
         * This will reference the texture already uploaded to the GPU.
         *
         * ```php
         * $image = $vg->imageFromHandle($handle, $width, $height, VGImage::REPEAT_XY, VGImage::FILTER_LINEAR);
         * ```
         *
         * @param int $handle The GPU handle of the texture.
         * @param int $width The width of the texture.
         * @param int $height The height of the texture.
         * @param int $repeatMode This can be either VGImage::REPEAT_XY, VGImage::REPEAT_X, VGImage::REPEAT_Y, or VGImage::REPEAT_NONE.
         *                        This controls how the image is repeated when the shape is larger than the image. 
         *                        The default is VGImage::REPEAT_NONE.
         * @param int $filterMode This can be either VGImage::FILTER_LINEAR or VGImage::FILTER_NEAREST.
         *                        This controls how the image is filtered when it is scaled. 
         *                        The default is VGImage::FILTER_LINEAR.
         */
        public function imageFromHandle(
            int $handle,
            int $width,
            int $height,
            int $repeatMode = VGImage::REPEAT_NONE,
            int $filterMode = VGImage::FILTER_LINEAR
        ) : VGImage {}
        
        /**
         * Creates a linear gradient paint object.
         * The gradient is defined by the start and end points, as well as the colors at these points.
         *
         * ```php
         * $x1 = 50;    
         * $y1 = 150;
         * $x2 = 350;
         * $y2 = 450;
         * $color1 = new VGColor(0.051, 0.682, 0.914, 1.0);
         * $color2 = new VGColor(0.169, 0.961, 0.596, 1.0);
         *
         * $paint = $vg->linearGradient($x1, $y1, $x2, $y2, $color1, $color2);
         * ```
         *
         * @param float $sx The x-coordinate of the start point of the gradient.
         * @param float $sy The y-coordinate of the start point of the gradient.
         * @param float $ex The x-coordinate of the end point of the gradient.
         * @param float $ey The y-coordinate of the end point of the gradient.
         * @param VGColor $icol The color at the start point of the gradient.
         * @param VGColor $ocol The color at the end point of the gradient.
         */
        public function linearGradient(float $sx, float $sy, float $ex, float $ey, VGColor $icol, VGColor $ocol) : VGPaint {}
        
        /**
         * Creates a box gradient paint object.
         *
         * ```php
         * $x = 100;
         * $y = 100;
         * $width = 200;
         * $height = 100;
         * $radius = 10;
         * $feather = 20;
         * $color1 = new VGColor(0.051, 0.682, 0.914, 1.0);
         * $color2 = new VGColor(0.169, 0.961, 0.596, 1.0);
         *
         * $paint = $vg->boxGradient($x, $y, $width, $height, $radius, $feather, $color1, $color2);
         * ```
         *
         * @param float $x The x-coordinate of the top left corner of the box.
         * @param float $y The y-coordinate of the top left corner of the box.
         * @param float $w The width of the box.
         * @param float $h The height of the box.
         * @param float $r The corner radius of the box.
         * @param float $f The feathering amount (how much the gradient fades).
         * @param VGColor $icol The color inside the box.
         * @param VGColor $ocol The color outside the box.
         */
        public function boxGradient(float $x, float $y, float $w, float $h, float $r, float $f, VGColor $icol, VGColor $ocol) : VGPaint {}
        
        /**
         * Creates a radial gradient paint object.
         * The gradient is defined by the center point and two radii, with the color transitioning from the inner to the outer radius.
         *
         * ```php
         * $cx = 150;
         * $cy = 150;
         * $innerRadius = 50;
         * $outerRadius = 100;
         * $color1 = new VGColor(0.914, 0.051, 0.682, 1.0);
         * $color2 = new VGColor(0.961, 0.596, 0.169, 1.0);
         *
         * $paint = $vg->radialGradient($cx, $cy, $innerRadius, $outerRadius, $color1, $color2);
         * ```
         *
         * @param float $cx The x-coordinate of the center of the gradient.
         * @param float $cy The y-coordinate of the center of the gradient.
         * @param float $inr The inner radius of the gradient.
         * @param float $outr The outer radius of the gradient.
         * @param VGColor $icol The color at the inner radius.
         * @param VGColor $ocol The color at the outer radius.
         */
        public function radialGradient(float $cx, float $cy, float $inr, float $outr, VGColor $icol, VGColor $ocol) : VGPaint {}
        //public function imagePattern(float $cx, float $cy, float $w, float $h, float $angle, float $alpha) : VGPaint {}

<?php foreach($vgContextFunctions as $func) : ?>
        public <?php echo $func->getPHPStub(); ?>
<?php endforeach; ?> 
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
    define('<?php echo $const->name; ?>', <?php echo $const->definitionValueString; ?>);
<?php endforeach; ?>
}
