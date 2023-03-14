# Math Functions

The PHP OpenGL extension, PHP-GLFW, offers a collection of math functions designed to perform common mathematical operations required in computer graphics. These functions are implemented in C and are accessible within the `GL\Math` namespace.

One unique aspect of these objects in PHP is the use of overloaded operators. This allows you to use the `+` operator for adding two vectors together or the `*` operator for multiplying a vector by a scalar.

These functions and classes are also fast. Learn more about their performance [here](#performance).

!!! warning

    There is currently an issue in the Zend Engine where multiplication operands are switched in certain expressions. This can be problematic when multiplying matrices, as the order is critical compared to regular multiplications.

    To work around this, use parentheses to enforce the correct order.

    [https://github.com/php/php-src/issues/9175](https://github.com/php/php-src/issues/9175)

## Vector Usage

There are three vector classes available: [`Vec2`](/API/Math/Vec2.html), [`Vec3`](/API/Math/Vec3.html), and [`Vec4`](/API/Math/Vec4.html).

The number in the class name indicates the number of components the vector has:

 * [`Vec2`](/API/Math/Vec2.html) has 2 components (`$x`, `$y`)
 * [`Vec3`](/API/Math/Vec3.html) has 3 components (`$x`, `$y`, `$z`)
 * [`Vec4`](/API/Math/Vec4.html) has 4 components (`$x`, `$y`, `$z`, `$w`)

```php
use GL\Math\Vec3;

$vec = new Vec3(1.0, 2.0, 3.0);

echo $vec; // prints vec3(1.0, 2.0, 3.0)
```

You can access the components of a vector using the `$x`, `$y`, `$z`, `$w` properties.

```php
echo $vec->x; // prints 1.0
echo $vec->y; // prints 2.0
echo $vec->z; // prints 3.0
```

You can also set the components of a vector using the `$x`, `$y`, `$z`, `$w` properties.

```php
$vec->x = 4.0;
$vec->y = 5.0;
$vec->z = 6.0;
```

Vector properties are **virtual**, meaning they are not stored in the vector object as real PHP properties. This allows multiple keys to map to the same property. For example, the `$x` property is also mapped to `$r`. The following code is valid:

```php
$vec->r = 42.0;
echo $vec->x; // prints 42.0
$vec->y = 100.0;
echo $vec->g; // prints 100.0
// etc..
```

### Operators

Vector classes have overloaded operators, which means you can use the `+` operator to add two vectors together or the `*` operator to multiply a vector with another vector or a scalar.

```php
$vec1 = new Vec3(1.0, 2.0, 3.0);
$vec2 = new Vec3(4.0, 5.0, 6.0);

// addition
echo $vec1 + $vec2; // vec3(5.0, 7.0, 9.0)

// subtraction
echo $vec1 - $vec2; // vec3(-3.0, -3.0, -3.0)

// multiplication
echo $vec1 * $vec2; // vec3(4.0, 10.0, 18.0)

// division
echo $vec1 / $vec2; // vec3(0.25, 0.4, 0.5)
```

You can also apply scalar operations to the vectors.

```php
$vec1 = new Vec3(1.0, 2.0, 3.0);

// addition
echo $vec1 + 2.0; // vec3(3.0, 4.0, 5.0)

// substraction
echo $vec1 - 2.0; // vec3(-1.0, 0.0, 1.0)

// multiplication
echo $vec1 * 2.0; // vec3(2.0, 4.0, 6.0)

// division
echo $vec1 / 2.0; // vec3(0.5, 1.0, 1.5)
```

### Functions

You can read about the functions available in the [`Vec2`](/API/Math/Vec2.html), [`Vec3`](/API/Math/Vec3.html), [`Vec4`](/API/Math/Vec4.html) classes in the API documentation.

#### Normalize

You can normalize a vector using the [`normalize()`](/API/Math/Vec3.html#normalize) function, or the [`normalized()`](/API/Math/Vec3.html#normalized) static function.

The difference between these two functions is that the [`normalize()`](/API/Math/Vec3.html#normalize) function modifies the vector in place, while the [`normalized()`](/API/Math/Vec3.html#normalized) function returns a new vector.

```php
$vec1 = new Vec3(1.0, 2.0, 3.0);
$vec2 =  Vec3::normalized($vec1); 
echo $vec2; // prints vec3(0.2673, 0.5345, 0.8018)
```

Or using normalize to modify the vector in place:

```php
$vec1 = new Vec3(1.0, 2.0, 3.0);
$vec1->normalize();
echo $vec1; // prints vec3(0.2673, 0.5345, 0.8018)
```

#### Length

You can get the length of a vector using the [`length()`](/API/Math/Vec3.html#length) function.

```php
$vec1 = new Vec3(1.0, 2.0, 3.0);
echo $vec1->length(); // prints 3.7416574954987
```

#### Dot Product

You can get the dot product of two vectors using the [`dot()`](/API/Math/Vec3.html#dot) function.

```php
$vec1 = new Vec3(5.0, 12.5, 7.5);
$vec2 = new Vec3(0.5, 2.0, 0.75);

echo Vec3::dot($vec2); // prints 33.125
```

#### Distance 

Or simply the distance between two vectors using the [`distance()`](/API/Math/Vec3.html#distance) function.

```php
$vec1 = new Vec3(5.0, 12.5, 7.5);
$vec2 = new Vec3(0.5, 2.0, 0.75);

echo Vec3::distance($vec1, $vec2); // prints 13.268
```


## Quaternion Usage

There is a [`Quat`](/API/Math/Quat.html) class available for working with quaternions.

You can think of a quaternion as a 4D vector, but it is not a vector in the same sense as a [`Vec4`](/API/Math/Vec4.html) is. A quaternion is usally used to represent a rotation in 3D space. In our implementation a quaternion has its components stored in `$w`, `$x`, `$y`, `$z` properties. This is not the same as the [`Vec4`](/API/Math/Vec4.html) class, where the components are stored in `$x`, `$y`, `$z`, `$w` properties.

```php
use GL\Math\Quat;

$quat = new Quat();

echo $quat; // prints quat(1.0, 0.0, 0.0, 0.0)
```

You can access the components of the quaternion using the `$w`, `$x`, `$y`, `$z` properties.

```php
echo $quat->w; // prints 1.0
echo $quat->x; // prints 0.0
// etc..
```

You can also set the components of the quaternion using the `$w`, `$x`, `$y`, `$z` properties.

```php
$quat->w = 2.0;
// etc..
``` 

### Operators

Just like the Vector classes the quaternion class [`Quat`](/API/Math/Quat.html) has overloaded operators. This means that you can use the `*` operator to multiply two quaternions together, which can be used to combine rotations. This continues to work even if you multiply a quaternion with a vector. The result will be a vector that has been rotated by the quaternion.

```php
// creates a quat that rotates 90 degrees on the y axis
$quat = new Quat;
$quat->rotate(GLM::radians(90), new Vec3(0, 1, 0));

// create a directional vector pointing in the x direction (right)
$vec = new Vec3(1, 0, 0);

// rotate the vector by the quaternion
$rotated = $quat * $vec;

// print the vector witch should now be pointing in the -z direction (forward)
echo $rotated; // prints vec3(0.0, 0.0, -1.0)
```

### Functions

Just like the vector classes there are a number of functions available for working with quaternions. You can read about the functions available in the [`Quat`](/API/Math/Quat.html) class in the API documentation.

To just give a few common examples:

#### Normalize

You can normalize a quaternion using the [`normalize`](/API/Math/Quat.html#normalize) function. This will make the quaternion a unit quaternion.
This modifies the quaternion in place.

```php
$quat = new Quat(1, 2, 3, 4);
$quat->normalize(); 

echo $quat; // prints quat(0.182574, 0.365148, 0.547723, 0.730297)
```

You can also use the [`normalized`](/API/Math/Quat.htmlQuat.html#normalized) function to create a new quaternion that is a normalized version of the original quaternion.

```php
$quat = new Quat(1, 2, 3, 4);
$normalized = Quat::normalized($quat);
```

#### Rotate 

You can rotate a quaternion using the [`rotate`](/API/Math/Quat.html#rotate) function. This will rotate the quaternion by the given angle around the given axis.

```php
$quat = new Quat;
$quat->rotate(GLM::radians(90), new Vec3(0, 1, 0));
```


## Matrix Usage

There is a [`Mat4`](/API/Math/Mat4.html) class available for working with 4x4 matrices. A matrix (in our implementation) has no accessable properties. You can only access the elements of the matrix using the array access operator `[]`. We store the values in a flat 1 dimensional array.

```php
use GL\Math\Mat4;

$mat = new Mat4;

echo $mat[0]; // prints 1.0
echo $mat[1]; // prints 0.0
echo $mat[15]; // prints 1.0
// etc..
```

You can also set the elements of the matrix using the array access operator `[]`.

```php
$mat[0] = 2.0;
// etc..
```

### Operators

Just like the other math classes the matrix class [`Mat4`](/API/Math/Mat4.html) has overloaded operators. This means that you can use the `*` operator to multiply two matrices together. This continues to work even if you multiply a matrix with a vector. The result will be a vector that has been transformed by the matrix.

```php
$mat1 = new Mat4;
$mat2 = new Mat4;

$mat3 = $mat1 * $mat2;
```

Transforming a point in space using a matrix is done by multiplying the matrix with a vector. The vector is treated as a point, and the result is a vector that represents the transformed point.

```php
$mat = new Mat4;
$mat->translate(new Vec3(10, 50, 1));
$mat->scale(new Vec3(2, 2, 2));
$mat->rotate(GLM::radians(90), new Vec3(0, 0, 1));

$point = new Vec3(10, 10, 5);

$transformed = $mat * $point;
```

### Functions

Just like the vector classes there are a number of functions available for working with matrices. You can read about the functions available in the [`Mat4`](/API/Math/Mat4.html) class in the API documentation.

To just give a few common examples:

#### Inverse 

You can invert a matrix using the [`inverse`](/API/Math/Mat4.html#inverse) function or the [`inverted`](/API/Math/Mat4.html#inverted) function. The `inverse` function modifies the matrix in place, while the `inverted` function returns a new matrix that is the inverse of the original matrix.

```php
$mat = new Mat4;
$mat->translate(new Vec3(10, 50, 1));
$mat->inverse();

// or 

$mat = new Mat4;
$mat->translate(new Vec3(10, 50, 1));
$mat2 = $mat = Mat4::inverted($mat);
```

--- 

## Performance 

The math functions are implemented in C, and each component of a vector is stored as a float, so the overhead of using these functions is minimal. (at least for PHP).

Benchmarks are always controversial and depend on the use case, but here are some benchmarks for the `GL\Math\Vec4` class. Once implemented in PHP and once using the extension functions.

This is the code:

```php
$v1 = new Vec4(1.0, 2.0, 3.0, 4.0);
$v2 = new Vec4(5.0, 6.0, 7.0, 8.0);
$v3 = $v1 * $v2 * $v1;
$v3->normalize();
```

I'm using a PHP implementation of Vec4 that can be found here: [Vec4.php](https://github.com/mario-deluna/php-render/blob/master/src/Math/Vec4.php)

```php
$v1 = new Vec4PHP(1.0, 2.0, 3.0, 4.0);
$v2 = new Vec4PHP(5.0, 6.0, 7.0, 8.0);
$v3 = Vec4PHP::_multiplyVec4($v1, $v2);
$v3 = Vec4PHP::_multiplyVec4($v3, $v1);
$v3 = Vec4PHP::_normalize($v3);
```

The benchmarks are executed using phpbench, each test case is run 10'000 times which iterates the above code 1000 times. So it ran 10'000'000 times in total.

#### Results

```
Average iteration times by variant

1.8ms     │   █
1.5ms     │   █
1.3ms     │   █
1.1ms     │   █
881.0μs   │   █
660.7μs   │   █
440.5μs   │ █ █
220.2μs   │ █ █
          └─────
            1 2

+-----------------------+---------+-----------+--------+---------+
| subject               | memory  | mode      | rstdev | stdev   |
+-----------------------+---------+-----------+--------+---------+
| benchVec4PHPMulGL ()  | 1.615mb | 420.948μs | ±0.00% | 0.000μs |
| benchVec4PHPMulPHP () | 1.615mb | 1.762ms   | ±0.00% | 0.000μs |
+-----------------------+---------+-----------+--------+---------+
```

So in this simple test GL functions are about 400% faster than the PHP implementation.

### Matrix Multiplication Performance 

Obviously the more complex the operation the more the performance difference will be. As in this particular situation, the PHP overhead becomes a clear bottleneck. I do not claim my PHP implementation is perfectly optimized, but so aint the C implementation either...

PHP GLFW Code:

```php
$m1 = new Mat4;
$m2 = new Mat4;
$m3 = $m1 * $m2;
$m4 = $m3->inverse();
```

Mat4 PHP implementation code can be found here [Mat4.php](https://github.com/mario-deluna/php-render/blob/master/src/Math/Mat4.php)

```php 
$m1 = new Mat4PHP();
$m2 = new Mat4PHP();
$m3 = Mat4PHP::_multiply($m1, $m2);
$m4 = $m3->inverse();
```

#### Results

As expected the performance difference is even more pronounced here. PHP-GLFW is about 1'500% faster than the PHP implementation. But again this is not really a fair comparison.

```
3.8ms     │       █
3.4ms     │       █
2.9ms     │       █
2.4ms     │   ▆   █
1.9ms     │   █   █
1.4ms     │   █   █
961.7μs   │   █   █
480.9μs   │ ▄ █ ▅ █
          └─────────
            1 2 3 4

+-----------------------+---------+-----------+--------+---------+
| subject               | memory  | mode      | rstdev | stdev   |
+-----------------------+---------+-----------+--------+---------+
| benchMat4PHPMulGL ()  | 1.615mb | 215.356μs | ±0.00% | 0.000μs |
| benchMat4PHPMulPHP () | 1.615mb | 2.240ms   | ±0.00% | 0.000μs |
| benchMat4PHPInvGL ()  | 1.615mb | 249.179μs | ±0.00% | 0.000μs |
| benchMat4PHPInvPHP () | 1.615mb | 3.847ms   | ±0.00% | 0.000μs |
+-----------------------+---------+-----------+--------+---------+
```
