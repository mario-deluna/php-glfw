# Math & 3D Space

The moment you draw something in more than one dimension, you need math: a point in space, the direction a camera is looking, the spin of a cube, the projection that turns a 3D world into a flat image on your screen. PHP-GLFW ships a small, fast math library so you don't have to reach for a userland package or write it yourself.

Everything lives in the `GL\Math` namespace and is implemented in C, so the objects behave like native PHP values. You can add them with `+`, multiply them with `*`, print them, and store them, all while running far faster than an equivalent PHP implementation. (If you're curious how much faster, the [Performance](../../user-guide/math/performance.md) page has the benchmarks.)

- [Vectors](../../user-guide/math/vectors.md): `Vec2`, `Vec3`, `Vec4` for positions, directions, and colors.
- [Quaternions](../../user-guide/math/quaternions.md): `Quat` for smooth, gimbal-free rotation.
- [Matrices](../../user-guide/math/matrices.md): `Mat4` for transforms, cameras, and projection.
- [Working in 3D Space](../../user-guide/math/working-in-3d-space.md): puts it all together into a real render.

This page covers the handful of conventions that apply to *every* math class. Read it once and the rest of the guide will feel familiar.

## The building blocks

There are five classes, and their names tell you almost everything:

- [`Vec2`](../../API/Math/Vec2.md), [`Vec3`](../../API/Math/Vec3.md), [`Vec4`](../../API/Math/Vec4.md) are vectors with 2, 3, and 4 components.
- [`Quat`](../../API/Math/Quat.md) is a quaternion, used to represent a rotation.
- [`Mat4`](../../API/Math/Mat4.md) is a 4x4 matrix, used to transform points and build cameras.

```php
use GL\Math\Vec3;

$position = new Vec3(1.0, 2.0, 3.0);

echo $position; // prints vec3(1.0, 2.0, 3.0)
```

## Operators just work

The most pleasant thing about these classes is that the arithmetic operators are overloaded. You may add two vectors, multiply a matrix by a vector, or combine two rotations, all with the operators you already know:

```php
use GL\Math\Vec3;

$a = new Vec3(1.0, 2.0, 3.0);
$b = new Vec3(4.0, 5.0, 6.0);

echo $a + $b; // vec3(5.0, 7.0, 9.0)
echo $a * 2.0; // vec3(2.0, 4.0, 6.0)
```

Each class supports a different set of operators (a matrix times a vector means something very different from a vector times a scalar), so the per-class pages spell out exactly what's available.

!!! warning "One gotcha with `*`"

    There is a long-standing issue in the Zend Engine where the operands of a multiplication can be swapped in certain expressions ([php-src #9175](https://github.com/php/php-src/issues/9175)). For most math this is harmless, but matrix and quaternion multiplication is **not** commutative, so `A * B` is not the same as `B * A`, and a swap gives you the wrong result.

    To stay safe, wrap each multiplication in parentheses and assign intermediate results to their own variable:

    ```php
    // do this
    $mvp = $projection * ($view * $model);

    // rather than chaining a long expression
    $mvp = $projection * $view * $model; // risky
    ```

    Every class also offers static `multiply...` helpers (`Quat::multiply()`, `Mat4::multiplyQuat()`, and friends) that sidestep the bug entirely when you'd rather be explicit. You'll see them called out where they matter.

## Reading and writing components

Vectors and quaternions expose their components as **virtual** properties (`$x`, `$y`, `$z`, `$w`) that you can both read and assign:

```php
$position = new Vec3(1.0, 2.0, 3.0);

echo $position->x; // 1.0
$position->y = 5.0;
```

"Virtual" means these aren't real PHP properties stored on the object; they're routed through the C layer. That's what lets the same slot answer to more than one name. Vectors, for instance, alias `$r`, `$g`, `$b`, `$a` onto `$x`, `$y`, `$z`, `$w` so a color reads naturally:

```php
$color = new Vec4(0.2, 0.4, 0.8, 1.0);
$color->r = 1.0;   // same slot as ->x
echo $color->x;    // 1.0
```

You may also reach components by index with the array operator, which is handy in loops:

```php
$position = new Vec3(1.0, 2.0, 3.0);
echo $position[0]; // 1.0
$position[2] = 9.0;
```

Matrices have no named properties. You access their 16 elements purely by index, for reasons the [Matrices](../../user-guide/math/matrices.md) page explains.

## Mutating vs. non-mutating

Many operations come in two flavors, and the naming tells you which is which:

- **Instance methods mutate in place** and return nothing: `$vec->normalize()`, `$matrix->inverse()`.
- **Static methods return a new object** and leave the original untouched: `Vec3::normalized($vec)`, `Mat4::inverted($matrix)`.

```php
use GL\Math\Vec3;

$dir = new Vec3(1.0, 2.0, 3.0);

// non-mutating: $dir is unchanged, $unit is new
$unit = Vec3::normalized($dir);

// mutating: $dir itself is now unit length
$dir->normalize();
```

Reach for the mutating form when you own the object and want to avoid an allocation; reach for the static form when you need to keep the original around. Keep an eye on this distinction, since it's the source of most "why didn't my vector change?" (or "why *did* it change?") surprises.

## Where to go next

Now that you know the shared conventions, pick the piece you need:

- New to this? Start with [Vectors](../../user-guide/math/vectors.md), the foundation everything else builds on.
- Trying to rotate something smoothly? See [Quaternions](../../user-guide/math/quaternions.md).
- Building a camera or transforming a model? See [Matrices](../../user-guide/math/matrices.md).
- Ready to draw a 3D object on screen? Jump straight to [Working in 3D Space](../../user-guide/math/working-in-3d-space.md).
