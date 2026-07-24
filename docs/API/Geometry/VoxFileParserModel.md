# VoxFileParser / Model

A Model holds the voxel data for one grid inside a MagicaVoxel scene: its dimensions and a palette index for every filled cell. A model has no position in the world, an `Instance` is what places it. The most common thing you will do with a model is turn it into a renderable triangle mesh with `generateTriangleMesh`.

```php
namespace GL\Geometry\VoxFileParser
{
    class Model {}
}
```

## Usage

### Generating a mesh

```php
use GL\Buffer\FloatBuffer;
use GL\Buffer\UIntBuffer;

$vertices = new FloatBuffer();
$indices  = new UIntBuffer();

$model->generateTriangleMesh($vertices, $indices, null, 'greedy');
```

By default every vertex is 9 floats: position (3), normal (3), and an RGB color (3) baked from the palette. See the [MagicaVoxel Files](../../user-guide/geometry/magicavoxel-files.md) guide for the full list of `$options` that reshape this layout.

### Reading a single voxel

```php
$paletteIndex = $model->getVoxel(4, 0, 2); // int, or null when empty
```

## Constants

The meshing modes are also available as integer constants. You may pass them through the `mode` key of the `$options` array. The positional `$mode` argument of `generateTriangleMesh` expects the equivalent string (`'simple'`, `'greedy'`, `'polygon'`).

```php
public const MODE_SIMPLE = 0;   // 'simple'  - one quad per exposed voxel face
public const MODE_GREEDY = 1;   // 'greedy'  - merge coplanar same-color faces
public const MODE_POLYGON = 2;  // 'polygon' - compact polygonal surfaces
```

## Properties

### $index

The sequential index of this model inside the scene.

```php
/*
 * @var int
 */
public readonly int $index;
```

### $sizeX, $sizeY, $sizeZ

The dimensions of the voxel grid.

```php
public readonly int $sizeX;
public readonly int $sizeY;
public readonly int $sizeZ;
```

### $voxelCount

The number of filled voxels in the grid.

```php
/*
 * @var int
 */
public readonly int $voxelCount;
```

### $voxelHash

A hash identifying the voxel contents, useful for spotting models that share identical geometry.

```php
/*
 * @var int
 */
public readonly int $voxelHash;
```

### $voxelData

The raw palette indices for the grid, exposed as a byte buffer.

```php
/*
 * @var \GL\Buffer\UByteBuffer|null
 */
public readonly ?\GL\Buffer\UByteBuffer $voxelData;
```

## Methods

### `generateTriangleMesh`

Generate a triangle mesh for this voxel grid.

```php
function generateTriangleMesh(\GL\Buffer\FloatBuffer $vertices, \GL\Buffer\UIntBuffer $indices, ?\GL\Geometry\VoxFileParser\Palette $palette = null, string $mode = 'simple', ?array $options = null) : bool
```

arguments

:    1. `\GL\Buffer\FloatBuffer` `$vertices` Destination buffer for vertex attributes (position, normal, colors).
    2. `\GL\Buffer\UIntBuffer` `$indices` Destination buffer for triangle indices.
    3. `\GL\Geometry\VoxFileParser\Palette|null` `$palette` Optional palette override or editor instance.
    4. `string` `$mode` Mesh generation mode name (simple, greedy, polygon).
    5. `array{colors?: "rgb"|"rgba"|"none", includePaletteIndex?: bool, origin?: "corner"|"center", originOffset?: array<int,float>, stats?: array{vertexCount: int, indexCount: int}|null}|null` `$options` Additional mesh generation controls. When provided, this array receives a `stats` entry on success.

returns

:    `bool` True on success, false otherwise.

---

### `getVoxel`

Retrieve the palette index stored at the given voxel coordinate.

```php
function getVoxel(int $x, int $y, int $z) : ?int
```

arguments

:    1. `int` `$x` The voxel x coordinate.
    2. `int` `$y` The voxel y coordinate.
    3. `int` `$z` The voxel z coordinate.

returns

:    `int|null` The palette index at the coordinate, or null when the cell is empty or out of bounds.

---

