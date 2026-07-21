# Filling & Reading

A buffer is only useful once it holds data, and most of the time you build it up piece by piece rather than knowing every value in advance. This page covers the everyday work of putting values in, reading them back, and keeping things fast when the buffers get large.

Every buffer type shares the exact same set of methods, so the examples here use a [`FloatBuffer`](/API/Buffer/FloatBuffer.html), but they apply equally to a [`UIntBuffer`](/API/Buffer/UIntBuffer.html), a [`ByteBuffer`](/API/Buffer/ByteBuffer.html), or any of the others.

## Adding data

### Pushing a single value

The simplest way to add a value is `push`. It appends to the end of the buffer, growing it automatically:

```php
use GL\Buffer\FloatBuffer;

$vertices = new FloatBuffer();

$vertices->push(0.5);
$vertices->push(-0.5);
$vertices->push(0.0);

echo $vertices->size(); // 3
```

If the array-style syntax feels more natural, you are free to use the `[]` subscript to push instead. The two are exactly equivalent, so pick whichever reads better in the moment:

```php
// this ...
$vertices->push(0.5);

// ... does the same thing as this
$vertices[] = 0.5;
```

### Pushing many values at once

When you already have your values in a PHP array, pushing them one at a time is tedious. `pushArray` takes the whole array and appends every value in order:

```php
$vertices = new FloatBuffer();

$vertices->pushArray([
     0.5, -0.5, 0.0,
    -0.5, -0.5, 0.0,
     0.0,  0.5, 0.0,
]);
```

This is the same operation the constructor performs when you pass it an array, so `new FloatBuffer($data)` and calling `pushArray($data)` on a fresh buffer are interchangeable.

### Joining two buffers

Sometimes you build several buffers separately, say one mesh per model, and later want them in a single buffer for one upload. `append` copies the contents of another buffer of the same type onto the end of this one:

```php
$scene = new FloatBuffer($shipVertices);
$scene->append(new FloatBuffer($asteroidVertices));

// $scene now holds the ship followed by the asteroid
```

The buffer you pass in is left untouched, so you may safely append it to several targets or append it more than once.

!!! warning "Types must match"

    `append` only accepts a buffer of the same class. You cannot append a `FloatBuffer` onto a `UIntBuffer`, because their underlying values have different sizes and meanings.

## Reading and modifying

Reading a value back is exactly what you would expect from an array, using its integer index:

```php
$vertices = new FloatBuffer([0.5, -0.5, 0.0]);

echo $vertices[0]; // 0.5
echo $vertices[2]; // 0.0
```

To change a value in place, assign to an index that already exists:

```php
$vertices[1] = 0.25; // overwrite the second value
```

Two small behaviors are worth knowing so nothing surprises you. Reading an index past the end of the buffer returns `null` rather than raising an error, and buffer keys are always integers, so using a string key like `$vertices['x']` throws an `Error`:

```php
$vertices = new FloatBuffer([0.5]);

var_dump($vertices[5]);   // NULL, the index does not exist
$vertices['x'];           // Error: Only a int offset ...
```

### Iterating

A buffer is iterable, so you may walk its values with a regular `foreach`. The key is the integer index and the value is the element, just like a list:

```php
$vertices = new FloatBuffer([0.5, -0.5, 0.0]);

foreach ($vertices as $index => $value) {
    echo "$index => $value\n";
}
// 0 => 0.5
// 1 => -0.5
// 2 => 0
```

## Preallocating for performance

Like a C++ `std::vector`, a buffer grows itself as you push, reallocating its internal storage whenever it runs out of room. That resizing is cheap for a handful of values, but if you are about to push millions of them in a tight loop, repeatedly reallocating and copying is wasted work.

When you know roughly how many elements are coming, call `reserve` first. It sets aside space up front so the buffer does not have to grow mid-loop:

```php
$matrices = new FloatBuffer();

// we are about to push 50 * 50 * 50 matrices, 16 floats each
$matrices->reserve(50 * 50 * 50 * 16);

foreach ($instances as $transform) {
    $matrices->pushMat4($transform);
}
```

This is the pattern the instancing example uses to build tens of thousands of transforms without a hitch (see [examples/04_instancing.php](https://github.com/mario-deluna/php-glfw/blob/master/examples/04_instancing.php)).

The difference between how much you have pushed and how much has been set aside is the difference between `size` and `capacity`:

- `size()` returns the number of elements actually in the buffer.
- `capacity()` returns how many elements it currently has room for before it must grow again.

!!! warning "Both count elements, not bytes"

    `size()` and `capacity()` are measured in *elements*, not bytes. A `FloatBuffer` with a `size()` of `3` holds three floats, which is 12 bytes of data, but `size()` still reports `3`. Keep this in mind when you compute offsets or strides for the GL API.

If you would rather fill a buffer with a known value instead of leaving reserved space undefined, use `fill`. It appends `$count` copies of a value:

```php
$mask = new FloatBuffer();
$mask->fill(5, 1.0);

echo $mask->size(); // 5, every element is 1.0
```

Note that `fill` only ever adds elements, it never shrinks a buffer. If the buffer already held values, the filled values are appended after them.

When you are truly done with a buffer and want its memory back, `clear` releases everything, resetting both `size` and `capacity` to zero. The buffer stays perfectly usable afterward, so you may start pushing into it again right away.

## Where to go next

- [Vectors, Matrices & Conversions](/user-guide/buffers/vectors-matrices-and-conversions.html) shows the `FloatBuffer` helpers for pushing [math types](/user-guide/math/overview.html), working with strings and raw bytes, and quantizing floats to bytes.
- The [Overview](/user-guide/buffers/overview.html) has the full table of buffer types if you need to pick a different one.
