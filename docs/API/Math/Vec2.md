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
     
### `length`

Returns the length of the vector

```php
function length() : float
```

returns

:    `float` 

---
     
### `dot`

Returns the dot product of the left and right vectors

```php
function dot(\GL\Math\Vec2 $left, \GL\Math\Vec2 $right) : float
```

```php
$dot = Vec2::dot($left, $right);
```

arguments

:    1. `\Vec2` `$left` The left vector.
    2. `\Vec2` `$right` The right vector.

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
     
### `normalize`

normalizes the current vector

```php
function normalize() : \GL\Math\Vec2
```

returns

:    `\Vec2` 

---
     
### `abs`

Makes each component x if x >= 0; otherwise, -x

```php
function abs() : \GL\Math\Vec2
```

returns

:    `void` 

---
     
