# VGImage

A `VGImage` is a texture that has been uploaded and prepared for use inside the vector graphics API.
You never construct one directly. Instead you create it from a
[`Texture2D`](/API/Texture/Texture2D.html) or an existing GPU handle with
[`VGContext::imageFromTexture`](/API/VectorGraphics/VGContext.html#imagefromtexture) or
[`imageFromHandle`](/API/VectorGraphics/VGContext.html#imagefromhandle). Once you have an image you
turn it into a [`VGPaint`](/API/VectorGraphics/VGPaint.html) and use it to fill or stroke shapes,
which lets you texture-map any path you can draw.

```php
namespace GL\VectorGraphics
{
    class VGImage {}
}
```

!!! tip "Looking for a walkthrough?"
    See the [Images user guide](/user-guide/vector-graphics/images.html) for a hands-on introduction
    to loading, scaling, filtering and repeating images.

## Usage

Create an image from a texture, build a paint for the region you want to cover, then fill a path with
it.

```php
use GL\VectorGraphics\{VGImage, VGColor};
use GL\Texture\Texture2D;

$texture = Texture2D::fromDisk(__DIR__ . '/ship.png');
$image   = $vg->imageFromTexture($texture, VGImage::REPEAT_NONE, VGImage::FILTER_LINEAR);

$paint = $image->makePaint(100, 100, 256, 256);

$vg->beginPath();
$vg->rect(100, 100, 256, 256);
$vg->fillPaint($paint);
$vg->fill();
```

## Constants

### Repeat modes

How the image tiles when the painted area is larger than the image. Passed to
[`VGContext::imageFromTexture`](/API/VectorGraphics/VGContext.html#imagefromtexture) /
[`imageFromHandle`](/API/VectorGraphics/VGContext.html#imagefromhandle).

| Constant | Value | Meaning |
|----------|-------|---------|
| `VGImage::REPEAT_NONE` | 0 | Do not repeat. |
| `VGImage::REPEAT_X` | 1 | Repeat horizontally. |
| `VGImage::REPEAT_Y` | 2 | Repeat vertically. |
| `VGImage::REPEAT_XY` | 3 | Repeat in both directions. |

### Filter modes

How the image is sampled when scaled.

| Constant | Value | Meaning |
|----------|-------|---------|
| `VGImage::FILTER_LINEAR` | 0 | Smooth bilinear filtering. |
| `VGImage::FILTER_NEAREST` | 1 | Nearest-neighbor (crisp pixels). |

## Methods

<?php foreach([
    'makePaint',
    'makePaintCentered',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGImage::' . $funcName); ?>
<?php endforeach; ?>
