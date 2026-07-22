# MagicaVoxel Files

[MagicaVoxel](https://ephtracy.github.io/) is a free, wildly popular voxel editor, and its `.vox` format is one of the easiest ways to get 3D art into your project without touching a modeling pipeline. [`GL\Geometry\VoxFileParser`](/API/Geometry/VoxFileParser.html) reads those files straight into your PHP runtime: it hands you the scene's models, the way they are placed in the world, the color palette, and a one-call helper that turns a voxel grid into a triangle mesh ready for OpenGL.

This page walks you through loading a scene, understanding the difference between models and instances, generating a mesh to render, recoloring through the palette, and reading individual voxels.

Want to see it running first? There is a complete, lit and shadow-mapped example in the repository:

```bash
php examples/12_voxel_rendering.php
```

## Loading a Scene

Loading is the only setup step. Point the parser at a `.vox` file and it reads the whole scene into native memory: every model, instance, layer, group, and the palette.

```php
use GL\Geometry\VoxFileParser;

$vox = new VoxFileParser(__DIR__ . '/../house.vox');

printf("Loaded %d models\n", $vox->modelCount);
printf("Placed %d instances\n", $vox->instanceCount);
```

Will print something like:

```
Loaded 3 models
Placed 12 instances
```

Everything the file described is now available as plain PHP properties:

- `$vox->models` is an array of [`Model`](/API/Geometry/VoxFileParserModel.html) objects, the actual voxel grids.
- `$vox->instances` is an array of [`Instance`](/API/Geometry/VoxFileParserInstance.html) objects, each one placing a model somewhere in the scene.
- `$vox->layers` and `$vox->groups` carry the [`Layer`](/API/Geometry/VoxFileParserLayer.html) and [`Group`](/API/Geometry/VoxFileParserGroup.html) metadata from the editor.
- `$vox->palette` is the scene's [`Palette`](/API/Geometry/VoxFileParserPalette.html), the 256 colors every voxel refers to.

!!! tip
    If the file cannot be opened or is not a valid MagicaVoxel scene, the constructor throws an exception, so you can wrap the call in a `try`/`catch` when loading user-supplied files.

## Models vs. Instances

This is the one idea worth pausing on, because it is what lets a small `.vox` file describe a large scene.

A **model** is a block of voxel data: a grid of a certain size where each cell holds a palette index. It has no position in the world. An **instance** is a placement: it points at a model by `modelIndex` and carries a `transform` (a [`Mat4`](/API/Math/Mat4.html)) that says where and how that model sits in the scene. One model can be reused by many instances, so a street of ten identical houses is one model and ten instances.

That means the natural way to walk a scene is to loop over instances, resolve the model each one refers to, and use the instance transform when you draw it:

```php
foreach ($vox->instances as $index => $instance) {
    // resolve the model this instance places
    $model = $vox->models[$instance->modelIndex] ?? null;
    if (!$model) {
        continue; // guard against an invalid model reference
    }

    printf(
        "Instance %d places model %d (%dx%dx%d)%s\n",
        $index,
        $instance->modelIndex,
        $model->sizeX, $model->sizeY, $model->sizeZ,
        $instance->name ? " named {$instance->name}" : ''
    );
}
```

When you render, apply `$instance->transform` to your model matrix so each placement lands where the artist put it. Instances also tell you which `layerIndex` and `groupIndex` they belong to, and whether the artist marked them `hidden`, which is handy for skipping geometry you do not want to draw.

```php
$modelMatrix = new Mat4;
if ($instance->transform) {
    $modelMatrix = $modelMatrix * $instance->transform->copy();
}
```

!!! hint "What about layers and groups?"
    [`Layer`](/API/Geometry/VoxFileParserLayer.html) and [`Group`](/API/Geometry/VoxFileParserGroup.html) mirror the organizational structure from the editor: names, visibility, an optional color, and a parent group index. You are free to ignore them for straightforward rendering and reach for them only when you want to respect the artist's layer visibility or group hierarchy.

## Generating a Triangle Mesh

A voxel grid is not something the GPU can draw directly, so the `Model` gives you [`generateTriangleMesh`](/API/Geometry/VoxFileParserModel.html#generatetrianglemesh) to turn it into vertices and indices. You hand it a [`FloatBuffer`](/API/Buffer/FloatBuffer.html) for the vertex attributes and a [`UIntBuffer`](/API/Buffer/UIntBuffer.html) for the triangle indices, and it fills them for you.

```php
use GL\Buffer\FloatBuffer;
use GL\Buffer\UIntBuffer;

$vertices = new FloatBuffer();
$indices  = new UIntBuffer();

$model->generateTriangleMesh($vertices, $indices, null, 'greedy');
```

The third argument is an optional palette override (pass `null` to use the scene's own palette, which is what you usually want). The fourth is the meshing mode:

| Mode | Description |
|------|-------------|
| `simple` | One quad per exposed voxel face. The most faces, but the simplest to reason about. |
| `greedy` | Merges coplanar faces of the same color into larger quads. Far fewer triangles, ideal for rendering. |
| `polygon` | Produces polygonal surfaces for the most compact result. |

By default every vertex carries **9 floats**: position `(x, y, z)`, normal `(x, y, z)`, and an RGB color `(r, g, b)` baked in from the palette. Unlike the OBJ parser, the voxel mesher does not take a layout string, you shape the output through the `$options` array below. The result is still a plain interleaved buffer, so the stride math from the [Vertex Layouts](/user-guide/geometry/vertex-layouts.html) page applies. Uploading it to OpenGL is familiar:

```php
$stride = 9 * GL_SIZEOF_FLOAT;

glBindBuffer(GL_ARRAY_BUFFER, $vbo);
glBufferData(GL_ARRAY_BUFFER, $vertices, GL_STATIC_DRAW);

glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, $ebo);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, $indices, GL_STATIC_DRAW);

// position (location 0)
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, $stride, 0);
glEnableVertexAttribArray(0);

// normal (location 1)
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, $stride, 3 * GL_SIZEOF_FLOAT);
glEnableVertexAttribArray(1);

// color rgb (location 2)
glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, $stride, 6 * GL_SIZEOF_FLOAT);
glEnableVertexAttribArray(2);
```

### Tuning the Output

The fifth argument is an `$options` array that lets you reshape the vertex layout and where the mesh sits. Every key is optional:

- `colors`: how color is written per vertex. `'rgb'` (the default, 3 floats), `'rgba'` (4 floats, adds alpha), or `'none'` (omit color entirely, leaving 6 floats).
- `includePaletteIndex`: when `true`, appends one extra float per vertex holding the raw palette index, useful if you would rather look colors up in a shader.
- `origin`: `'corner'` (the default) keeps the grid's corner at the origin, `'center'` centers the model on its own bounding box, which makes rotating an instance around its middle much easier.
- `originOffset`: an array of three floats added to every position, for nudging the mesh into place.
- `mode`: the same choice as the positional mode argument. Here you may also pass the `Model::MODE_SIMPLE`, `Model::MODE_GREEDY`, or `Model::MODE_POLYGON` constants instead of a string. When present, this overrides the positional argument.

Remember to account for any layout change in your vertex attribute strides. An `rgba` mesh with a palette index, for example, is 11 floats per vertex.

```php
$options = [
    'colors'              => 'rgba',
    'includePaletteIndex' => true,
    'origin'              => 'center',
];

$model->generateTriangleMesh($vertices, $indices, null, 'greedy', $options);

// on success the array receives a `stats` entry describing the result
printf(
    "Built %d vertices, %d indices\n",
    $options['stats']['vertexCount'],
    $options['stats']['indexCount']
);
```

`generateTriangleMesh` returns `true` on success and `false` if the grid held no geometry, so it is worth checking the return value (and that the buffers actually received data) before you upload:

```php
if (!$model->generateTriangleMesh($vertices, $indices) || $vertices->size() === 0) {
    // nothing to draw for this model
}
```

## Working With the Palette

Every voxel stores a palette index rather than a color, and the [`Palette`](/API/Geometry/VoxFileParserPalette.html) holds the 256 RGBA entries those indices point at. The quickest way to read a color is straight off the parser:

```php
$color = $vox->getPaletteColor(42); // a GL\Math\Vec4 in the 0..1 range, or null
```

Because colors are baked into the mesh when you call `generateTriangleMesh`, recoloring is simply a matter of editing the palette first and then generating. You can set entries with float components in the 0..1 range:

```php
$palette = $vox->palette;

// paint palette slot 1 a warm orange
$palette->setColorf(1, 1.0, 0.5, 0.1);

// or from a Vec4
$palette->setColor(2, new Vec4(0.1, 0.8, 0.3, 1.0));

// generate the mesh using the edited palette
$model->generateTriangleMesh($vertices, $indices, $palette, 'greedy');
```

If you have a whole color scheme ready, `replaceFromArray` swaps many entries at once, and `fillDefault` resets everything back to MagicaVoxel's standard table:

```php
$palette->replaceFromArray([
    [1.0, 0.0, 0.0],       // index 0, red
    [0.0, 1.0, 0.0, 0.5],  // index 1, semi-transparent green
]);

$palette->fillDefault(); // start over from the default colors
```

## Reading Individual Voxels

Sometimes you do not want a mesh at all, you want to know what is at a specific cell, for collision, gameplay, or building your own geometry. [`getVoxel`](/API/Geometry/VoxFileParserModel.html#getvoxel) returns the palette index stored at a coordinate, or `null` when the cell is empty or out of bounds.

```php
$index = $model->getVoxel(4, 0, 2);

if ($index !== null) {
    $color = $vox->getPaletteColor($index);
    echo "Solid voxel colored {$color}\n";
}
```

Combined with `sizeX`, `sizeY`, and `sizeZ`, you can walk the whole grid yourself when you need full control.

## Full API Reference

- [`VoxFileParser`](/API/Geometry/VoxFileParser.html) class reference
- [`VoxFileParser\Model`](/API/Geometry/VoxFileParserModel.html) class reference
- [`VoxFileParser\Palette`](/API/Geometry/VoxFileParserPalette.html) class reference
- [`VoxFileParser\Instance`](/API/Geometry/VoxFileParserInstance.html), [`Layer`](/API/Geometry/VoxFileParserLayer.html), and [`Group`](/API/Geometry/VoxFileParserGroup.html) containers
