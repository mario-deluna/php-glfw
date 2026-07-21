# Performance

A fair question about any math library is whether it's fast enough to run inside a render loop, where you might build dozens of matrices and transform thousands of vectors every single frame. The good news: because these classes are implemented in C, with each vector component stored as a plain float, the overhead of using them is minimal, at least by PHP standards.

You don't need to take that on faith. Below are benchmarks comparing PHP-GLFW's C-backed classes against an equivalent pure-PHP implementation.

!!! note

    Benchmarks are always a little controversial and depend heavily on the use case. The pure-PHP implementation used here isn't claimed to be perfectly optimized, but then, neither is the C one. Treat these as a rough sense of the gap, not gospel.

## Vector math

This is the code under test, a couple of `Vec4` multiplications and a normalize:

```php
$v1 = new Vec4(1.0, 2.0, 3.0, 4.0);
$v2 = new Vec4(5.0, 6.0, 7.0, 8.0);
$v3 = $v1 * $v2 * $v1;
$v3->normalize();
```

The pure-PHP comparison uses a userland `Vec4` implementation, [Vec4.php](https://github.com/mario-deluna/php-render/blob/master/src/Math/Vec4.php), doing the same work through static methods:

```php
$v1 = new Vec4PHP(1.0, 2.0, 3.0, 4.0);
$v2 = new Vec4PHP(5.0, 6.0, 7.0, 8.0);
$v3 = Vec4PHP::_multiplyVec4($v1, $v2);
$v3 = Vec4PHP::_multiplyVec4($v3, $v1);
$v3 = Vec4PHP::_normalize($v3);
```

The benchmarks were run with phpbench: each case runs 10,000 times, iterating the code above 1,000 times, for 10,000,000 iterations in total.

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

For this simple test the GL functions come out roughly **400% faster** than the PHP implementation.

## Matrix math

The more complex the operation, the wider the gap grows, because PHP's per-call overhead becomes the bottleneck. Here's a matrix multiply followed by an inverse (`GL\Math\Mat4`):

```php
$m1 = new Mat4;
$m2 = new Mat4;
$m3 = $m1 * $m2;
$m4 = Mat4::inverted($m3);
```

Against the pure-PHP `Mat4`, [Mat4.php](https://github.com/mario-deluna/php-render/blob/master/src/Math/Mat4.php):

```php
$m1 = new Mat4PHP();
$m2 = new Mat4PHP();
$m3 = Mat4PHP::_multiply($m1, $m2);
$m4 = $m3->inverse();
```

As expected, the difference is even more pronounced: PHP-GLFW is around **1,500% faster** here. Again, not an entirely fair comparison, but a telling one.

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

The takeaway is simple: build your matrices and transform your vectors freely inside the render loop. The math library is designed to keep up.
