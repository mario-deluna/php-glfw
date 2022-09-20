# DoubleBuffer
The class `GL\Buffer\DoubleBuffer` comes with the PHP-GLFW extension to more efficiently 
handle large arrays of `GLdouble` values (`float` in php).

**Don't confuse these objects with actual GPU buffers.**

`DoubleBuffer` stores an array of real `GLdouble` values internally, which saves a lot of memory
and makes interaction with the GL API a lot easier. An instance of this object can be used similarly to an array but
comes with obvious limitations. The internal implementation is similar to c++ std::vector, this means you do not have to 
specify the exact size / num of elements when constructing the object.

```php 
namespace GL\Buffer
{
    class DoubleBuffer implements BufferInterface {}
}
```

## Usage

Again the object can be used similarly to an array, but it's not a hash map, 
so all keys have to be of type `int`. They also have to be in order and explicitly created.

```php
use GL\Buffer\DoubleBuffer;

$buffer = new DoubleBuffer;

// values can be pushed into the array using subscript
$buffer[] = 42.69;
$buffer[] = 3.14;

// values can be accessed like an array
echo $buffer[0]; // 42.69 

// values can be modifed like an array
// just make sure the used index actually exists, 
// it will NOT be created implicitly!
$buffer[0] = 1.23;

// dumping the buffer will display the first 127 value
var_dump($buffer);
```

!!! note

    The buffer object resizes itself logarithmically, so if you are planning to insert 10 million elements,
    be sure to call the `reserve` method on the object first. As you might guess, it will reserve the 
    given space, ensuring that the internal buffers are not unnecessarily resized multiple times.


### Construct from PHP Array

For ease of use, the `DoubleBuffer` constructor accepts a PHP array which will be pushed 
value by value into the buffer. The constructor does a sanity check, so you will receive an error when 
your array contains invalid values.

```php
$buffer = new DoubleBuffer([
    42.69, 3.14, 1.23 
]);
```

## Methods

The `DoubleBuffer` class exposes the following methods to userland.

### `push`

pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = 3.14`.

```php
function push(float $value) : void
```

arguments

:    1. `float` `$value` The value to be pushed into the buffer.

returns

:    `void` 

---
    

### `pushArray`

pushes an array of values into the buffer. This works the same as when you pass inital data to the constructor.

```php
function pushArray(array $values) : void
```

arguments

:    1. `float[]` `$values` The values to be pushed into the buffer.

returns

:    `void` 

---
    

### `fill`

Fills the buffer with `$count` amount of values. The second argument is the value that is filled in.

```php
function fill(int $count, float $value) : void
```

arguments

:   1. `int $count` The number of elements to fill.
    2. `float $value` That value that will be filled in.

returns 

:   `void`


Example:

```php
$buffer = new DoubleBuffer;
$buffer->fill(5, 3);
var_dump($buffer); // [3, 3, 3, 3, 3]
```

!!! note

    Fill will never shrink a buffer down, meaing when you aleady pushed 10 values in, 
    and then decide to fill 4 values, the other 6 values will remain at the end.

---

### `reserve`

Reserves the $size amount of space. Values are still undefined.

```php
function reserve(int $size) : void
```

arguments

:    1. `int` `$size` The number of elements to reserve space for.

returns

:    `void` 

---
     
### `clear`

Will clear the Buffer, internally this will release all allocated data. Meaning any reserved space will be freed.

```php
function clear() : void
```

returns

:    `void` 

---
     
### `size`

Returns the actual size / number of elements of the buffer.

```php
function size() : int
```

returns

:    `int` buffer size in element count (not bytes)

---
     
### `capacity`

Returns the current reserved space of the buffer.

```php
function capacity() : int
```

returns

:    `int` buffer space in element count (not bytes)

---
     
