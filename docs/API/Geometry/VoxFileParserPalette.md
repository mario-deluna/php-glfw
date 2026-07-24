# VoxFileParser / Palette

Every voxel stores a palette index rather than a color, and the Palette holds the 256 RGBA entries those indices point at. When you load a scene the parser exposes its palette through `$vox->palette`, and you are free to edit it before generating a mesh to recolor the model. The colors are owned by a 256 * 4 entry [UByteBuffer](../../API/Buffer/UByteBuffer.md) under the hood, but the helpers below let you work in the friendlier 0..1 float range.

```php
namespace GL\Geometry\VoxFileParser
{
    class Palette {}
}
```

## Usage

### Recoloring the scene

```php
$palette = $vox->palette;

// paint a couple of entries
$palette->setColorf(1, 1.0, 0.5, 0.1);      // warm orange
$palette->setColor(2, new \GL\Math\Vec4(0.1, 0.8, 0.3, 1.0));

// then generate a mesh using the edited palette
$model->generateTriangleMesh($vertices, $indices, $palette, 'greedy');
```

### Starting from a color scheme

```php
$palette->replaceFromArray([
    [1.0, 0.0, 0.0],       // index 0, red
    [0.0, 1.0, 0.0, 0.5],  // index 1, semi-transparent green
]);

$palette->fillDefault(); // reset to the default MagicaVoxel colors
```

## Methods

### `__construct`

```php
function __construct(?\GL\Buffer\UByteBuffer $buffer = null)
```

arguments

:    1. `?\GL\Buffer\UByteBuffer` `$buffer` Optional existing buffer to wrap. When omitted a default palette is created.

---

### `getBuffer`

Retrieve the underlying RGBA byte buffer (256 * 4 entries).

```php
function getBuffer() : \GL\Buffer\UByteBuffer
```

returns

:    `\GL\Buffer\UByteBuffer` The 256 * 4 byte RGBA palette buffer.

---

### `getColor`

Fetch a color at the given palette index as a Vec4 object in the 0..1 range.

```php
function getColor(int $index) : \GL\Math\Vec4
```

arguments

:    1. `int` `$index` The palette index to read (0..255).

returns

:    `\GL\Math\Vec4` The color at the given index in the 0..1 range.

---

### `setColor`

Assign a color at the given palette index using a Vec4 color.

```php
function setColor(int $index, \GL\Math\Vec4 $color) : void
```

arguments

:    1. `int` `$index` The palette index to write (0..255).
    2. `\GL\Math\Vec4` `$color` The color in the 0..1 range.

returns

:    `void` 

---

### `setColorf`

Assign a color at the given palette index using individual float components.

```php
function setColorf(int $index, float $r, float $g, float $b, float $a = 1.0) : void
```

Components are expected in the 0..1 range.

arguments

:    1. `int` `$index` The palette index to write (0..255).
    2. `float` `$r` The red component (0..1).
    3. `float` `$g` The green component (0..1).
    4. `float` `$b` The blue component (0..1).
    5. `float` `$a` The alpha component (0..1), defaults to 1.0.

returns

:    `void` 

---

### `replaceFromBuffer`

Replace the palette contents from another buffer. Accepts RGBA byte or float layouts.

```php
function replaceFromBuffer(\GL\Buffer\UByteBuffer|\GL\Buffer\FloatBuffer $buffer) : void
```

arguments

:    1. `\GL\Buffer\UByteBuffer|\GL\Buffer\FloatBuffer` `$buffer` A buffer holding RGBA color data.

returns

:    `void` 

---

### `replaceFromArray`

Replace palette entries from an array of colors. Each color may be [r, g, b] or [r, g, b, a] in 0..1 range.

```php
function replaceFromArray(array $colors) : void
```

arguments

:    1. `array<int,array{0: float, 1: float, 2: float, 3?: float}>` `$colors` The colors to write, starting at index 0.

returns

:    `void` 

---

### `fillDefault`

Reset the palette to the default MagicaVoxel color table.

```php
function fillDefault() : void
```

returns

:    `void` 

---

