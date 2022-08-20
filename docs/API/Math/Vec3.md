# Vec3 - GL Math

PHP-GLFW comes with built in fixed size vector classes. `Vec3` represents a vector with 3 components (
`x`, `y`, `z`, ).

```php 
namespace GL\Math
{
    class Vec3 {
        public float $x;
        public float $y;
        public float $z;
    }
}
```

The properties of this class are virtual, meaning in this case they are not real PHP properties. But rather values stored internally that 
can be accessed like a property. The same values can be read and written using different names for convience:

```php
$vec = new Vec3;
$vec->x = 42.0;
$vec->y = 42.0;
$vec->z = 42.0;
```

Is exactly the same as:

```php
$vec = new Vec3;
$vec->r = 42.0;
$vec->g = 42.0;
$vec->b = 42.0;
```

## Methods

### `__construct`

Constructor

```php
function __construct(?float $x = null, ?float $y = null, ?float $z = null)
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
function dot(\GL\Math\Vec3 $right) : float
```

returns

:    `float` 

---
     
### `distance`

Returns the distance between this vector and another

```php
function distance(\GL\Math\Vec3 $right) : float
```

returns

:    `float` 

---
     
### `distance2`

Returns squared distance between this vector and another

```php
function distance2(\GL\Math\Vec3 $right) : float
```

returns

:    `float` 

---
     
### `normalize`

Returns a normalized version of this vector

```php
function normalize() : \GL\Math\Vec3
```

---
     
### `abs`

Creates a new Vec3 where each component is x if x >= 0; otherwise, -x

```php
function abs() : \GL\Math\Vec3
```

---
     
