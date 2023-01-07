# Vec2 - GL Math

PHP-GLFW comes with built in fixed size vector classes. `Vec2` represents a vector with 2 components (
`x`, `y`, ).

```php 
namespace GL\Math
{
    class Vec2 {
        public float $x;
        public float $y;
    }
}
```

The properties of this class are virtual, meaning in this case they are not real PHP properties. But rather values stored internally that 
can be accessed like a property. The same values can be read and written using different names for convience:

```php
$vec = new Vec2;
$vec->x = 42.0;
$vec->y = 42.0;
```

Is exactly the same as:

```php
$vec = new Vec2;
$vec->r = 42.0;
$vec->g = 42.0;
```

## Methods

### `__construct`

Constructor

```php
function __construct(?float $x = null, ?float $y = null)
```

---
     
### `normalized`

Retruns a normalized version of the given Vec2         *
```php
$normalized = Vec2::normalize(new Vec2($x, $y, $z));
```

```php
static function normalized(\GL\Math\Vec2 $vec) : \GL\Math\Vec2
```

arguments

:    1. `\Vec2` `$vec` The vector to normalize.

returns

:    `\Vec2` The normalized vector.

---
     
### `distance`

Returns the distance between the left and right vectors

```php
static function distance(\GL\Math\Vec2 $left, \GL\Math\Vec2 $right) : float
```

```php
$distance = Vec2::distance($left, $right);
```

arguments

:    1. `\Vec2` `$left` The left vector.
    2. `\Vec2` `$right` The right vector.

returns

:    `float` The distance between the left and right vectors.

---
     
### `distance2`

Returns the squared distance between the left and right vectors

```php
static function distance2(\GL\Math\Vec2 $left, \GL\Math\Vec2 $right) : float
```

```php
$distance = Vec2::distance2($left, $right);
```

arguments

:    1. `\Vec2` `$left` The left vector.
    2. `\Vec2` `$right` The right vector.

returns

:    `float` The squared distance between the left and right vectors.

---
     
### `dot`

Returns the dot product of the left and right vectors

```php
static function dot(\GL\Math\Vec2 $left, \GL\Math\Vec2 $right) : float
```

```php
$dot = Vec2::dot($left, $right);
```

arguments

:    1. `\Vec2` `$left` The left vector.
    2. `\Vec2` `$right` The right vector.

returns

:    `float` The dot product of the left and right vectors.

---
     
### `mix`

Linearly interpolates between the left and right vectors by the given t value.

```php
static function mix(\GL\Math\Vec2 $left, \GL\Math\Vec2 $right, float $t) : \GL\Math\Vec2
```

```php
$mixed = Vec2::mix($left, $right, $t);
```

arguments

:    1. `\Vec2` `$left` The left vector.
    2. `\Vec2` `$right` The right vector.
    3. `float` `$t` The t value (progress / state) 0.0 == left, 1.0 == right.

returns

:    `\Vec2` The mixed vector.

---
     
### `lerp`

Linearly interpolates between the left and right vectors by the given t value.

```php
static function lerp(\GL\Math\Vec2 $left, \GL\Math\Vec2 $right, float $t) : \GL\Math\Vec2
```

This does exactly the same as mix..

```php
$lerped = Vec2::lerp($left, $right, $t);
```

arguments

:    1. `\Vec2` `$left` The left vector.
    2. `\Vec2` `$right` The right vector.
    3. `float` `$t` The t value (progress / state) 0.0 == left, 1.0 == right.

returns

:    `\Vec2` The lerped vector.

---
     
### `slerp`

Spherically interpolates between the left and right vectors by the given t value.

```php
static function slerp(\GL\Math\Vec2 $left, \GL\Math\Vec2 $right, float $t) : \GL\Math\Vec2
```

```php
$slerped = Vec2::slerp($left, $right, $t);
```

arguments

:    1. `\Vec2` `$left` The left vector.
    2. `\Vec2` `$right` The right vector.
    3. `float` `$t` The t value (progress / state) 0.0 == left, 1.0 == right.

returns

:    `\Vec2` The slerped vector.

---
     
### `length`

Returns the length of the vector

```php
function length() : float
```

returns

:    `float` 

---
     
### `distanceTo`

Returns the distance between this vector and another

```php
function distanceTo(\GL\Math\Vec2 $right) : float
```

returns

:    `float` 

---
     
### `distance2To`

Returns squared distance between this vector and another

```php
function distance2To(\GL\Math\Vec2 $right) : float
```

returns

:    `float` 

---
     
### `normalize`

normalizes the current vector

```php
function normalize() : void
```

returns

:    `void` 

---
     
### `abs`

Makes each component x if x >= 0; otherwise, -x

```php
function abs() : void
```

returns

:    `void` 

---
     
