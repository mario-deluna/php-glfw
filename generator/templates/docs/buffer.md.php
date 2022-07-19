# <?php echo $buffer->name; ?>

The class `<?php echo $buffer->getFullNamespaceString(); ?>` comes with the PHP-GLFW extension to more efficiently 
handle large arrays of `<?php echo $buffer->type; ?>` values (`<?php echo $buffer->getValuePHPType(); ?>` in php).

`<?php echo $buffer->name; ?>` stores an array of real `<?php echo $buffer->type; ?>` values internally, which saves a lot of memory
and makes interaction with the GL API a lot easier. An instance of this object can be used similarly to an array but
comes with obvious limitations. The internal implementation is similar to c++ std::vector, this means you do not have to 
specify the exact size / num of elements when constructing the object.

```php 
namespace GL\Buffer
{
    class <?php echo $buffer->name; ?> implements BufferInterface {}
}
```

## Usage

Again the object can be used similarly to an array, but it's not a hash map, 
so all keys have to be of type `int`. They also have to be in order and explicitly created.

```php
use <?php echo $buffer->getFullNamespaceString(); ?>;

$buffer = new <?php echo $buffer->name; ?>;

// values can be pushed into the array using subscript
$buffer[] = <?php echo $buffer->getValuePHPType() === 'int' ? '42' : '42.69'; ?>;
$buffer[] = <?php echo $buffer->getValuePHPType() === 'int' ? '123' : '3.14'; ?>;

// values can be accessed like an array
echo $buffer[0]; // <?php echo $buffer->getValuePHPType() === 'int' ? '42' : '42.69'; ?> 

// values can be modifed like an array
// just make sure the used index actually exists, 
// it will NOT be created implicitly!
$buffer[0] = <?php echo $buffer->getValuePHPType() === 'int' ? '8' : '1.23'; ?>;

// dumping the buffer will display the first 127 value
var_dump($buffer);
```

!!! note

    The buffer object resizes itself logarithmically, so if you are planning to insert 10 million elements,
    be sure to call the `reserve` method on the object first. As you might guess, it will reserve the 
    given space, ensuring that the internal buffers are not unnecessarily resized multiple times.


### Construct from PHP Array

For ease of use, the `<?php echo $buffer->name; ?>` constructor accepts a PHP array which will be pushed 
value by value into the buffer. The constructor does a sanity check, so you will receive an error when 
your array contains invalid values.

```php
$buffer = new <?php echo $buffer->name; ?>([
    <?php echo $buffer->getValuePHPType() === 'int' ? '42' : '42.69'; ?>, <?php echo $buffer->getValuePHPType() === 'int' ? '123' : '3.14'; ?>, <?php echo $buffer->getValuePHPType() === 'int' ? '8' : '1.23'; ?> 
]);
```

## Methods

The `<?php echo $buffer->name; ?>` class exposes the following methods to userland.

### `push` 

pushes a value into the buffer, this is exactly the same as when you would write `$buffer[] = <?php echo $buffer->getValuePHPType() === 'int' ? '123' : '3.14'; ?>`.

```php
function push(<?php echo $buffer->getValuePHPType(); ?> $value) : void
```

---

### `fill`

Fills the buffer with `$count` amount of values. The second argument is the value that is filled in.

```php
function fill(int $count, <?php echo $buffer->getValuePHPType(); ?> $value) : void
```

Example:

```php
$buffer = new <?php echo $buffer->name; ?>;
$buffer->fill(5, 3);
var_dump($buffer); // [3, 3, 3, 3, 3]
```

!!! note

    Fill will never shrink a buffer down, meaing when you aleady pushed 10 values in, 
    and then decide to fill 4 values, the other 6 values will remain at the end.

---

### `clear`

```php
function clear() : void
```

### `size`

```php
function size() : int
```

### `capacity`

```php
public function capacity() : int
```

### `reserve`

```php
public function reserve(int $size) : void
```