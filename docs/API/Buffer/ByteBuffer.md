# ByteBuffer
The class `GL\Buffer\ByteBuffer` comes with the PHP-GLFW extension to more efficiently 
handle large arrays of `GLbyte` values (`int` in php).

**Don't confuse these objects with actual GPU buffers.**

`ByteBuffer` stores an array of real `GLbyte` values internally, which saves a lot of memory
and makes interaction with the GL API a lot easier. An instance of this object can be used similarly to an array but
comes with obvious limitations. The internal implementation is similar to c++ std::vector, this means you do not have to 
specify the exact size / num of elements when constructing the object.

```php 
namespace GL\Buffer
{
    class ByteBuffer implements BufferInterface {}
}
```

## Usage

Again the object can be used similarly to an array, but it's not a hash map, 
so all keys have to be of type `int`. They also have to be in order and explicitly created.

```php
use GL\Buffer\ByteBuffer;

$buffer = new ByteBuffer;

// values can be pushed into the array using subscript
$buffer[] = 42;
$buffer[] = 123;

// values can be accessed like an array
echo $buffer[0]; // 42 

// values can be modifed like an array
// just make sure the used index actually exists, 
// it will NOT be created implicitly!
$buffer[0] = 8;

// dumping the buffer will display the first 127 value
var_dump($buffer);
```

!!! note

    The buffer object resizes itself logarithmically, so if you are planning to insert 10 million elements,
    be sure to call the `reserve` method on the object first. As you might guess, it will reserve the 
    given space, ensuring that the internal buffers are not unnecessarily resized multiple times.


### Construct from PHP Array

For ease of use, the `ByteBuffer` constructor accepts a PHP array which will be pushed 
value by value into the buffer. The constructor does a sanity check, so you will receive an error when 
your array contains invalid values.

```php
$buffer = new ByteBuffer([
    42, 123, 8 
]);
```

## Methods

The `ByteBuffer` class exposes the following methods to userland.


### `push`

pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = 123`.

```php
function push(int $value) : void
```

arguments

:    1. `int` `$value` The value to be pushed into the buffer.

returns

:    `void` 

---
     

### `fill`

Fills the buffer with `$count` amount of values. The second argument is the value that is filled in.

```php
function fill(int $count, int $value) : void
```

arguments

:   1. `int $count` The number of elements to fill.
    2. `int $value` That value that will be filled in.

returns 

:   `void`


Example:

```php
$buffer = new ByteBuffer;
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
     
