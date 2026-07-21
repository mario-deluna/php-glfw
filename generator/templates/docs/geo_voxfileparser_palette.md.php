# VoxFileParser / Palette

Every voxel stores a palette index rather than a color, and the Palette holds the 256 RGBA entries those indices point at. When you load a scene the parser exposes its palette through `$vox->palette`, and you are free to edit it before generating a mesh to recolor the model. The colors are owned by a 256 * 4 entry [UByteBuffer](/API/Buffer/UByteBuffer.html) under the hood, but the helpers below let you work in the friendlier 0..1 float range.

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

<?php foreach([
    '__construct',
    'getBuffer',
    'getColor',
    'setColor',
    'setColorf',
    'replaceFromBuffer',
    'replaceFromArray',
    'fillDefault'
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\Geometry\\VoxFileParser\\Palette::' . $funcName); ?>
<?php endforeach; ?>
