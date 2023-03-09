# Mat4 - GL Math

PHP-GLFW comes with a built-in math library this is a quick reference for the `Mat4` class.
The `Mat4` represents a matrix 4x4 Matrix with 16 values.

The values hold by the Mat4 object are stored internally as real float values, and can be accessed in an array like fashion:

```php
$mat = new Mat4();
$mat[0] = 42.0;
$mat[15] = 42.0;

echo $mat[0];
echo $mat[15];
```

## Methods

### `__construct`

Constructucts a new Mat4 matrix
Does not take any arguments and always returns an identity matrix.

```php
function __construct()
```

aka:
```
1 0 0 0
0 1 0 0
0 0 1 0
0 0 0 1
```

---
     
### `fromArray`

Constructs and returns a new matrix based on the given array of values

```php
static function fromArray(array $values) : \GL\Math\Mat4
```

```php
$matrix = Mat4::fromArray([
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
]);
```

arguments

:    1. `array` `$values` The values to use for the matrix. (flat)

returns

:    `\Mat4` The new matrix.

---
     
### `inverted`

Constructs and returns an inverse of the given matrix

```php
static function inverted(\GL\Math\Mat4 $matrix) : \GL\Math\Mat4
```

```php
$inverse = Mat4::inverse($matrix);
```

arguments

:    1. `\Mat4` `$matrix` The matrix to invert.

returns

:    `\Mat4` The inverted matrix.

---
     
### `multiplyQuat`

Mat4 * Quat

```php
static function multiplyQuat(\GL\Math\Mat4 $left, \GL\Math\Quat $right) : \GL\Math\Mat4
```

Multiplies the left matrix by the right quaternion

Note: **This method only exists because there is a bug with the order of operation in PHP.**

---
     
### `copy`

Copys the current matrix

```php
function copy() : \GL\Math\Mat4
```

Returns a new instance of the current matrix with the same values. This means that any modifications made to the returned matrix will not affect the current matrix.

```php
$copy = $matrix->copy();
```

returns

:    `\Mat4` The copy of the current matrix.

---
     
### `row`

Returns the row at the given index.

```php
function row(int $index) : \GL\Math\Vec4
```

Example usage:

```php
$matrix = new Mat4([
    [1.0, 2.0, 3.0, 4.0],
    [5.0, 6.0, 7.0, 8.0],
    [9.0, 10.0, 11.0, 12.0],
    [13.0, 14.0, 15.0, 16.0]
]);

// Get the first row
$row = $matrix->row(0);
// Expected result: Vec4(1.0, 2.0, 3.0, 4.0)
```

arguments

:    1. `int` `$index` The index of the row to return.

returns

:    `\Vec4` The row at the given index.

---
     
### `setRow`

Sets the row at the given index to the given row

```php
function setRow(int $index, \GL\Math\Vec4 $row) : void
```

Example usage:
```php
$matrix = new Mat4();
$row = new Vec4(1, 2, 3, 4);
$matrix->setRow(0, $row);
```

arguments

:    1. `int` `$index` The index of the row to set.
    2. `\Vec4` `$row` The row to set.

returns

:    `void` 

---
     
### `col`

Returns the column at the given index.

```php
function col(int $index) : \GL\Math\Vec4
```

This method retrieves a column from the matrix at the specified index and returns it as a Vec4 object.

Example:
```php
$matrix = new Mat4([
    [1.0, 2.0, 3.0, 4.0],
    [5.0, 6.0, 7.0, 8.0],
    [9.0, 10.0, 11.0, 12.0],
    [13.0, 14.0, 15.0, 16.0]
]);

$col = $matrix->col(0);

// Returns Vec4(1.0, 5.0, 9.0, 13.0)
```

arguments

:    1. `int` `$index` The index of the column to return.

returns

:    `\Vec4` The column at the given index.

---
     
### `setCol`

Sets the column at the given index to the given column

```php
function setCol(int $index, \GL\Math\Vec4 $col) : void
```

```php
// Create a new matrix and set the second column
$matrix = new Mat4();
$col = new Vec4(1, 2, 3, 4);
$matrix->setCol(1, $col);
```

arguments

:    1. `int` `$index` The index of the column to set.
    2. `\Vec4` `$col` The column to set.

returns

:    `void` 

---
     
### `lookAt`

Sets the matrix to a lookAt matrix

```php
function lookAt(\GL\Math\Vec3 $eye, \GL\Math\Vec3 $center, \GL\Math\Vec3 $up) : void
```

The `lookAt()` method sets the matrix to a lookAt matrix based on the camera's position and orientation.
It takes three parameters: `$eye`, `$center`, and `$up`, which are all instances of the `Vec3` class.

The `$eye` parameter indicates the position of the camera, while `$center` indicates the point
in space to look at. The `$up` parameter specifies the up vector, which determines the orientation of the camera.

Example usage:

```php
// Create a new matrix
$matrix = new Mat4();

// Set the matrix to a lookAt matrix
$matrix->lookAt(
   new Vec3(0, 0, 5), // eye
   new Vec3(0, 0, 0), // center
   new Vec3(0, 1, 0)  // up
);
```

This will create a new matrix and set it to a lookAt matrix with the camera positioned at `(0, 0, 5)`,
looking at the origin `(0, 0, 0)`, with the up vector pointing in the positive y direction.

arguments

:    1. `\Vec3` `$eye` The position of the camera.
    2. `\Vec3` `$center` The position to look at.
    3. `\Vec3` `$up` The up vector.

returns

:    `void` 

---
     
### `perspective`

Sets the matrix to a perspective matrix

```php
function perspective(float $fov, float $aspect, float $near, float $far) : void
```

```php
$matrix->perspective($fov, $aspect, $near, $far);
```

arguments

:    1. `float` `$fov` The field of view.
    2. `float` `$aspect` The aspect ratio.
    3. `float` `$near` The near plane.
    4. `float` `$far` The far plane.

returns

:    `void` 

---
     
### `ortho`

Sets the matrix to an orthographic matrix

```php
function ortho(float $left, float $right, float $bottom, float $top, float $near, float $far) : void
```

```php
$matrix->ortho($left, $right, $bottom, $top, $near, $far);
```

arguments

:    1. `float` `$left` The left plane.
    2. `float` `$right` The right plane.
    3. `float` `$bottom` The bottom plane.
    4. `float` `$top` The top plane.
    5. `float` `$near` The near plane.
    6. `float` `$far` The far plane.

returns

:    `void` 

---
     
### `transpose`

Tranposes the matrix

```php
function transpose() : void
```

```php
$matrix->transpose();
```

returns

:    `void` 

---
     
### `inverse`

Inverts the current matrix

```php
function inverse() : void
```

```php
$matrix->inverse();
```

returns

:    `void` 

---
     
### `scale`

Scale the matrix by the given vector

```php
function scale(\GL\Math\Vec3 $scale) : void
```

```php
$matrix->scale(new Vec3(2, 2, 2));
```

---
     
### `translate`

Translates the matrix by the given vector

```php
function translate(\GL\Math\Vec3 $vector) : void
```

```php
$matrix->translate(new Vec3(1, 1, 1));
```

arguments

:    1. `\Vec3` `$vector` The vector to translate by.

returns

:    `void` 

---
     
### `rotate`

Rotates the matrix by the given angle around the given axis

```php
function rotate(float $angle, \GL\Math\Vec3 $axis) : void
```

```php
$matrix->rotate(GLM::radians(90), new Vec3(0, 1, 0));
```

arguments

:    1. `float` `$angle` The angle to rotate by.
    2. `\Vec3` `$axis` The axis to rotate around.

returns

:    `void` 

---
     
### `determinant`

Retruns the determinant of the matrix

```php
function determinant() : float
```

```php
$det = $matrix->determinant();
```

returns

:    `float` The determinant of the matrix.

---
     
