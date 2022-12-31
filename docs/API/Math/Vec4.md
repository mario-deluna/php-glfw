# Vec4 - GL Math

PHP-GLFW comes with built in fixed size vector classes. `Vec4` represents a vector with 4 components (
`x`, `y`, `z`, `w`, ).

```php 
namespace GL\Math
{
    class Vec4 {
        public float $x;
        public float $y;
        public float $z;
        public float $w;
    }
}
```

The properties of this class are virtual, meaning in this case they are not real PHP properties. But rather values stored internally that 
can be accessed like a property. The same values can be read and written using different names for convience:

```php
$vec = new Vec4;
$vec->x = 42.0;
$vec->y = 42.0;
$vec->z = 42.0;
$vec->w = 42.0;
```

Is exactly the same as:

```php
$vec = new Vec4;
$vec->r = 42.0;
$vec->g = 42.0;
$vec->b = 42.0;
$vec->a = 42.0;
```

## Methods

### `__construct`

Constructor

```php
function __construct(?float $x = null, ?float $y = null, ?float $z = null, ?float $w = null)
```

---
     
### `length`

Returns the length of the vector

```php
function length() : float
```

returns

:    `float` 

---
     
### `dot`

Returns the dot product of this vector and another

```php
function dot(\GL\Math\Vec4 $right) : float
```

returns

:    `float` 

---
     
### `distance`

Returns the distance between the left and right vectors

```php
static function distance(\GL\Math\Vec4 $left, \GL\Math\Vec4 $right) : float
```

```php
$distance = Vec4::distance($left, $right);
```

arguments

:    1. `\Vec4` `$left` The left vector.
    2. `\Vec4` `$right` The right vector.

returns

:    `float` The distance between the left and right vectors.

---
     
### `distance2`

Returns the squared distance between the left and right vectors

```php
static function distance2(\GL\Math\Vec4 $left, \GL\Math\Vec4 $right) : float
```

```php
$distance = Vec4::distance2($left, $right);
```

arguments

:    1. `\Vec4` `$left` The left vector.
    2. `\Vec4` `$right` The right vector.

returns

:    `float` The squared distance between the left and right vectors.

---
     
### `normalize`

normalizes the current vector

```php
function normalize() : \GL\Math\Vec4
```

returns

:    `\Vec4` 

---
     
### `abs`

Makes each component x if x >= 0; otherwise, -x

```php
function abs() : \GL\Math\Vec4
```

returns

:    `void` 

---
     
