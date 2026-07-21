# VoxFileParser

The Vox File Parser reads [MagicaVoxel](https://ephtracy.github.io/) `.vox` scenes into your PHP runtime. It ships with PHP-GLFW and is built on top of the _opengametools_ voxel library written in C. A single call loads the whole scene: the voxel models, the instances that place them in the world, the layers and groups from the editor, and the color palette.

```php
namespace GL\Geometry
{
    class VoxFileParser {}
}
```

If you are new to the voxel workflow, the [MagicaVoxel Files](/user-guide/geometry/magicavoxel-files.html) guide walks through loading, meshing, and recoloring a scene end to end.

## Usage

### Loading a scene

```php
use GL\Geometry\VoxFileParser;

$vox = new VoxFileParser(__DIR__ . '/house.vox');

printf("Loaded %d models\n", $vox->modelCount);
printf("Placed %d instances\n", $vox->instanceCount);
```

### Walking the scene

A [Model](/API/Geometry/VoxFileParserModel.html) is voxel grid data with no position of its own, while an [Instance](/API/Geometry/VoxFileParserInstance.html) places a model in the world through its `modelIndex` and `transform`. To render a scene you typically loop over the instances and resolve the model each one refers to.

```php
foreach ($vox->instances as $instance) {
    $model = $vox->models[$instance->modelIndex] ?? null;
    if (!$model) {
        continue;
    }

    // generate a mesh, apply $instance->transform, draw ...
}
```

## Properties

### $models

An array of all voxel [Model](/API/Geometry/VoxFileParserModel.html) objects contained in the scene.

```php
/*
 * @var array<\GL\Geometry\VoxFileParser\Model>
 */
public readonly array $models;
```

### $instances

An array of [Instance](/API/Geometry/VoxFileParserInstance.html) objects, each placing a model into the scene.

```php
/*
 * @var array<\GL\Geometry\VoxFileParser\Instance>
 */
public readonly array $instances;
```

### $layers

An array of [Layer](/API/Geometry/VoxFileParserLayer.html) objects describing the editor layers.

```php
/*
 * @var array<\GL\Geometry\VoxFileParser\Layer>
 */
public readonly array $layers;
```

### $groups

An array of [Group](/API/Geometry/VoxFileParserGroup.html) objects describing the group hierarchy.

```php
/*
 * @var array<\GL\Geometry\VoxFileParser\Group>
 */
public readonly array $groups;
```

### $palette

The scene [Palette](/API/Geometry/VoxFileParserPalette.html), holding the 256 RGBA colors every voxel refers to.

```php
/*
 * @var \GL\Geometry\VoxFileParser\Palette|null
 */
public readonly ?\GL\Geometry\VoxFileParser\Palette $palette;
```

### $modelCount, $instanceCount, $layerCount, $groupCount

Convenience counts mirroring the size of the arrays above.

```php
public readonly int $modelCount;
public readonly int $instanceCount;
public readonly int $layerCount;
public readonly int $groupCount;
```

## Methods

### `__construct`

Parse a MagicaVoxel scene from a file on disk.

```php
function __construct(string $file)
```

arguments

:    1. `string` `$file` The path to the .vox file to load.

---

### `getModel`

Retrieve a single voxel model by its index.

```php
function getModel(int $modelIndex) : ?\GL\Geometry\VoxFileParser\Model
```

arguments

:    1. `int` `$modelIndex` The index of the model inside the scene.

returns

:    `\VoxFileParser\Model|null` The model, or null when the index is out of range.

---

### `getPaletteColor`

Look up a color from the scene palette by its index.

```php
function getPaletteColor(int $colorIndex) : ?\GL\Math\Vec4
```

arguments

:    1. `int` `$colorIndex` The palette index to read (0..255).

returns

:    `\GL\Math\Vec4|null` The color in the 0..1 range, or null when the index is out of range.

---

