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

Returns the dot product of this vector and another

```php
function dot(\GL\Math\Vec2 $right) : float
```

returns

:    `float` 

---
     
### `distance`

Returns the distance between this vector and another

```php
function distance(\GL\Math\Vec2 $right) : float
```

returns

:    `float` 

---
     
### `distance2`

Returns squared distance between this vector and another

```php
function distance2(\GL\Math\Vec2 $right) : float
```

returns

:    `float` 

---
     
### `normalize`

Returns a normalized version of this vector

```php
function normalize() : \GL\Math\Vec2
```

---
     
### `abs`

Creates a new Vec2 where each component is x if x >= 0; otherwise, -x

```php
function abs() : \GL\Math\Vec2
```

---
     
