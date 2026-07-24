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

<?php foreach([
    'generateTriangleMesh',
    'getVoxel'
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\Geometry\\VoxFileParser\\Model::' . $funcName); ?>
<?php endforeach; ?>
