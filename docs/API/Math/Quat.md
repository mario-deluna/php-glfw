# Quat - GL Math

PHP-GLFW comes with a built-in math library this is a quick reference for the `Quat` class.
The `Quat` represents a vector with 4 components (`w`, `x`, `y`, `z`, ),
which can be and is generally used to represent rotations.

```php 
namespace GL\Math
{
    class Quat {
        public float $w;
        public float $x;
        public float $y;
        public float $z;
    }
}
```

The properties of this class are virtual, meaning in this case they are not real PHP properties. But rather values stored internally that 
can be accessed like a property. The same values can be read and written using different names:

```php
$quat = new Quat;
$quat->w = 42.0;
$quat->x = 42.0;
$quat->y = 42.0;
$quat->z = 42.0;
```

Is exactly the same as:

```php
$quat = new Quat;
$quat[0] = 42.0;
$quat[1] = 42.0;
$quat[2] = 42.0;
$quat[3] = 42.0;
```

## Methods

### `__construct`

Constructor

```php
function __construct(?float $w = null, ?float $x = null, ?float $y = null, ?float $z = null)
```

---
     
### `fromVec4`

Constructs and returns a new quaternion based on the given Vec4 vector.

```php
static function fromVec4(\GL\Math\Vec4 $vec) : \GL\Math\Quat
```

The quaternion is arragned as (w, x, y, z), while the vector is arranged as (x, y, z, w).
This method will swap the x and w components.

```php
$quat = Quat::fromVec4($vector);
```

arguments

:    1. `\Vec4` `$vector` The vector to construct the quaternion from.

returns

:    `\Quat` The constructed quaternion.

---
     
### `fromMat4`

Constructs and returns a new quaternion based on the given Mat4 matrix

```php
static function fromMat4(\GL\Math\Mat4 $matrix) : \GL\Math\Quat
```

```php
$quat = Quat::fromMat4($matrix);
```

arguments

:    1. `\Mat4` `$matrix` The matrix to construct the quaternion from.

returns

:    `\Quat` The constructed quaternion.

---
     
### `normalized`

Constructs and returns a normalized quaternion based on the given one

```php
static function normalized(\GL\Math\Quat $quat) : \GL\Math\Quat
```

```php
$normalized = Quat::normalized($quat);
```

arguments

:    1. `\Quat` `$quat` The quaternion to normalize.

returns

:    `\Quat` The normalized quaternion.

---
     
### `normalize`

The same as `normalized()`, but modifies the current quaternion instead of creating a new one.

```php
function normalize() : void
```

```php
$quat->normalize();
```

---
     
### `inverse`

Invseres the current quaternion, this is basically the same as `inverted()` but
modifies the current quaternion instead of creating a new one.

```php
function inverse() : void
```

```php
$quat->inverse();
```

---
     
### `inverted`

Constructs and return a inverted quaternion based on the given one

```php
static function inverted(\GL\Math\Quat $quat) : \GL\Math\Quat
```

```php
$inverted = Quat::inverted($quat);
```

arguments

:    1. `\Quat` `$quat` The quaternion to invert.

returns

:    `\Quat` The inverted quaternion.

---
     
### `length`

Returns the length of the quaternion

```php
function length() : float
```

```php
$length = $quat->length();
```

---
     
### `eulerAngles`

Returns the quaternion represented as euler angles (in radians)

```php
function eulerAngles() : \GL\Math\Vec3
```

```php
$euler = $quat->eulerAngles();
```

returns

:    `\Vec3` The euler angles.

---
     
### `rotate`

Rotates the quaternion by the given angle (in radians) around the given axis

```php
function rotate(float $angle, \GL\Math\Vec3 $axis) : void
```

```php
$quat->rotate(GLM::radians(45.0), new Vec3(0, 1, 0));
```

arguments

:    1. `float` `$angle` The angle to rotate by (in radians)
    2. `\Vec3` `$axis` The axis to rotate around

---
     
### `mat4`

Constructs a Mat4 matrix based on the current quaternion

```php
function mat4() : \GL\Math\Mat4
```

```php
$matrix = $quat->mat4();
```

returns

:    `\Mat4` The matrix representation of the quaternion.

---
     
