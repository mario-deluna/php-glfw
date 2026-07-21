# Quaternions

Sooner or later you'll want to rotate something: spin a cube, aim a camera, tumble a model. You *could* stack up rotations around the x, y, and z axes, but that approach is famous for two headaches. The rotations interfere with each other ("gimbal lock"), and blending smoothly between two orientations is awkward. A quaternion solves both. It's the standard way to represent a rotation in 3D, and PHP-GLFW gives you the [`Quat`](/API/Math/Quat.html) class for it.

Don't worry if quaternions sound intimidating. You rarely need to think about the math inside. In practice you build one, rotate it, and multiply it against a vector or matrix. Let's do exactly that.

## Creating a quaternion

A brand-new quaternion is the **identity** rotation, meaning "no rotation at all":

```php
use GL\Math\Quat;

$rotation = new Quat();
echo $rotation; // quat(1.0, 0.0, 0.0, 0.0)
```

You can access its components through the `$w`, `$x`, `$y`, `$z` properties, but note the ordering: a quaternion is stored **w-first** (`w, x, y, z`), unlike [`Vec4`](/API/Math/Vec4.html), which is `x, y, z, w`. This trips people up, so it's worth stating plainly, and it's why converting from a `Vec4` deliberately reorders the components:

```php
$q = Quat::fromVec4(new Vec4(1, 2, 3, 4)); // quat(4.0, 1.0, 2.0, 3.0)
```

## Rotating

The workhorse method is `rotate()`. It turns the quaternion by an angle (in **radians**) around an axis you give as a `Vec3`. Use [`GLM::radians()`](/API/Math/GLM.html) if you think in degrees:

```php
use GL\Math\{Quat, Vec3, GLM};

// a rotation of 90 degrees around the y (up) axis
$rotation = new Quat();
$rotation->rotate(GLM::radians(90), new Vec3(0, 1, 0));
```

`rotate()` mutates the quaternion in place, and calling it again *accumulates*, so successive calls compose one rotation on top of the last.

## Operators

Where quaternions really shine is multiplication.

Multiplying two quaternions **combines** their rotations into one:

```php
$spin = new Quat();
$spin->rotate(GLM::radians(45), new Vec3(0, 1, 0));

$tilt = new Quat();
$tilt->rotate(GLM::radians(30), new Vec3(1, 0, 0));

$combined = $spin * $tilt; // both rotations, as a single quaternion
```

Multiplying a quaternion by a `Vec3` **applies** the rotation to that vector. This is how you actually turn a direction or a point:

```php
$rotation = new Quat();
$rotation->rotate(GLM::radians(90), new Vec3(0, 1, 0));

$forward = new Vec3(1, 0, 0);      // pointing right (+x)
$rotated = $rotation * $forward;   // now pointing forward (-z)

echo $rotated; // vec3(0.0, 0.0, -1.0)
```

!!! warning "Mind the multiplication order"

    Because quaternion multiplication is not commutative and PHP can swap `*` operands in some expressions (see the [Overview](/user-guide/math/overview.html#operators-just-work)), keep each multiplication in its own parenthesized step. When you want to be completely explicit, use the static helpers instead of the operator:

    ```php
    $combined = Quat::multiply($spin, $tilt);        // Quat * Quat
    $rotated  = Quat::multiplyVec3($rotation, $forward); // Quat * Vec3
    ```

## Common operations

For the full list see the [`Quat` API reference](/API/Math/Quat.html); here are the ones you'll use most.

### Normalize

Rotations accumulate tiny floating-point errors, and a quaternion only represents a clean rotation while it stays unit length. Normalizing fixes that. As elsewhere, the instance method mutates and the static one returns a copy:

```php
$q = new Quat(1, 2, 3, 4);
$q->normalize();
echo $q; // quat(0.182574, 0.365148, 0.547723, 0.730297)

$copy = Quat::normalized(new Quat(1, 2, 3, 4)); // original untouched
```

### Converting to a matrix

To use a rotation inside a full transform, convert it to a [`Mat4`](/API/Math/Mat4.html) with `mat4()`:

```php
$rotation = new Quat();
$rotation->rotate(GLM::radians(90), new Vec3(0, 1, 0));

$matrix = $rotation->mat4(); // a Mat4 you can multiply into your model matrix
```

You can also go the other way with `Quat::fromMat4()`, extracting the rotation from an existing matrix.

### Smooth blending

To ease from one orientation to another, think of a camera gliding to face a new target, interpolate between two quaternions. `slerp()` (spherical linear interpolation) is the one you usually want, since it keeps a constant rotational speed:

```php
$from = new Quat();
$to = new Quat();
$to->rotate(GLM::radians(180), new Vec3(0, 1, 0));

$halfway = Quat::slerp($from, $to, 0.5); // rotated 90 degrees, exactly between them
```

`mix()` and `lerp()` are the cheaper linear cousins, fine for small angles.

### Euler angles

If you need the rotation back as familiar pitch/yaw/roll angles (in radians), `eulerAngles()` returns them as a `Vec3`:

```php
$euler = $rotation->eulerAngles();
```

Now that you can rotate things, the next step is combining rotation with position and scale into a single transform. That's the job of [matrices](/user-guide/math/matrices.html).
