# Math Functions 

The PHP OpenGL extension PHP-GLFW provides a set of math functions that can be used to perform common mathematical operations required in computer graphics.
The functions are implemented in C and are available in the `GL\Math` namespace. 

Something you might not have seen in PHP before is that these objects have overloaded operators. This means that you can use the `+` operator to add two vectors together, or the `*` operator to multiply a vector by a scalar.

Also, these functions and classes are fast*, check out [Performance](#performance)

!!! warning

    There currently is a "bug" in the zend engine where multiplication operands are switched in 
    some expressions. This is a problem when multiplying matrices as the order / sequence there is cricitcal 
    compared to normal multiplications...
    
    To workaround this you have to set paranthesis to enforce the correct order.

    [https://github.com/php/php-src/issues/9175](https://github.com/php/php-src/issues/9175)

## Usage

### Vectors

There are 3 vector classes available, [`Vec2`](/API/Math/Vec2.html), [`Vec3`](/API/Math/Vec3.html), [`Vec4`](/API/Math/Vec4.html).

The number in the class name indicates the number of components the vector has. 

 * [`Vec2`](/API/Math/Vec2.html) has 2 components. (`$x`, `$y`)
 * [`Vec3`](/API/Math/Vec3.html) has 3 components. (`$x`, `$y`, `$z`)
 * [`Vec4`](/API/Math/Vec4.html) has 4 components. (`$x`, `$y`, `$z`, `$w`)

```php 
use GL\Math\Vec3;

$vec = new Vec3(1.0, 2.0, 3.0);

echo $vec; // prints vec3(1.0, 2.0, 3.0)
```

You can access the components of the vector using the `$x`, `$y`, `$z`, `$w` properties.

```php
echo $vec->x; // prints 1.0
echo $vec->y; // prints 2.0
echo $vec->z; // prints 3.0
```

You can also set the components of the vector using the `$x`, `$y`, `$z`, `$w` properties.

```php
$vec->x = 4.0;
$vec->y = 5.0;
$vec->z = 6.0;
```

Note the vector properties are **virtual**, meaning that they are not stored in the vector object as real php properties. This allows us to map them to multiple keys. For example, the `$x` property is mapped `$r` aswell. This means the following code is valid:

```php
$vec->r = 42.0;
echo $vec->x; // prints 42.0
$vec->y = 100.0;
echo $vec->g; // prints 100.0
// etc..
```

#### Operators

As notes above the vector classes have overloaded operators. This means that you can use the `+` operator to add two vectors together, or the `*` operator to multiply a vector with another vector or a scalar.

```php
$vec1 = new Vec3(1.0, 2.0, 3.0);
$vec2 = new Vec3(4.0, 5.0, 6.0);

// addition
echo $vec1 + $vec2; // vec3(5.0, 7.0, 9.0)

// substration
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

#### Functions

You can read about the functions available in the [`Vec2`](/API/Math/Vec2.html), [`Vec3`](/API/Math/Vec3.html), [`Vec4`](/API/Math/Vec4.html) classes in the API documentation.

To just give a quick exmaple:

```php
$vec1 = new Vec3(1.0, 2.0, 3.0);
echo $vec1->length(); // prints 3.7416574954987
echo $vec1->normalize(); // prints vec3(0.2673, 0.5345, 0.8018)
```

## Performance 

The math functions are implemented in C, each component of a vector is stored as a float, so the overhead of using these functions is minimal. (at least for PHP).

Benchmarks are always controversial and depend on the use case, but here are some benchmarks for the `GL\Math\Vec4` class. Once implemented in PHP and once using the extension functions.

This is the code:

```php
$v1 = new Vec4(1.0, 2.0, 3.0, 4.0);
$v2 = new Vec4(5.0, 6.0, 7.0, 8.0);
$v3 = $v1 * $v2 * $v1;
$v4 = $v3->normalize();
```

Im using a php implementation of Vec4 that can be found here: [Vec4.php](https://github.com/mario-deluna/php-render/blob/master/src/Math/Vec4.php)

```php
$v1 = new Vec4PHP(1.0, 2.0, 3.0, 4.0);
$v2 = new Vec4PHP(5.0, 6.0, 7.0, 8.0);
$v3 = Vec4PHP::_multiplyVec4($v1, $v2);
$v3 = Vec4PHP::_multiplyVec4($v3, $v1);
$v4 = Vec4PHP::_normalize($v3);
```

The benchmarks are executed using phpbench, each test case is run 10'000 times which iterates the above code 1000 times. So its run 10'000'000 times in total.

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

So in this simple test GL function are about 400% faster than the PHP implementation.

### Matrix Multiplication Performance 

Obviously the complexer the operation the more the performance difference will be. As in this particular sitation the PHP overhead becomes a clear bottleneck. I do not claim my PHP implementation is perfectly optimized, but so aint the C implementation either...

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

#### Results

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