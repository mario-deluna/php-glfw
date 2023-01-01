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
     
