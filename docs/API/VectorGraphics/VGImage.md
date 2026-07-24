# VGImage

A `VGImage` is a texture that has been uploaded and prepared for use inside the vector graphics API.
You never construct one directly. Instead you create it from a
[`Texture2D`](../../API/Texture/Texture2D.md) or an existing GPU handle with
[`VGContext::imageFromTexture`](../../API/VectorGraphics/VGContext.md#imagefromtexture) or
[`imageFromHandle`](../../API/VectorGraphics/VGContext.md#imagefromhandle). Once you have an image you
turn it into a [`VGPaint`](../../API/VectorGraphics/VGPaint.md) and use it to fill or stroke shapes,
which lets you texture-map any path you can draw.

```php
namespace GL\VectorGraphics
{
    class VGImage {}
}
```

!!! tip "Looking for a walkthrough?"
    See the [Images user guide](../../user-guide/vector-graphics/images.md) for a hands-on introduction
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
[`VGContext::imageFromTexture`](../../API/VectorGraphics/VGContext.md#imagefromtexture) /
[`imageFromHandle`](../../API/VectorGraphics/VGContext.md#imagefromhandle).

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

### `makePaint`

Creates a paint object of the current image that can be used to fill or stroke shapes.

```php
function makePaint(float $x, float $y, float $w, float $h, float $angle = 0.0, float $alpha = 1.0) : \GL\VectorGraphics\VGPaint
```

arguments

:    1. `float` `$x` The x-coordinate of the top left corner of the paint.
    2. `float` `$y` The y-coordinate of the top left corner of the paint.
    3. `float` `$width` The width of the paint.
    4. `float` `$height` The height of the paint.
    5. `float` `$angle` The angle of the paint in radians. (The rotation is around the top left corner of the paint.)
    6. `float` `$alpha` The alpha value of the paint.

---

### `makePaintCentered`

Creates a paint object of the current image (from center) that can be used to fill or stroke shapes.

```php
function makePaintCentered(float $cx, float $cy, float $w, float $h, float $angle = 0.0, float $alpha = 1.0) : \GL\VectorGraphics\VGPaint
```

The image is centered around the given coordinates and also rotated around the center.

arguments

:    1. `float` `$cx` The x-coordinate of the center of the paint.
    2. `float` `$cy` The y-coordinate of the center of the paint.
    3. `float` `$width` The width of the paint.
    4. `float` `$height` The height of the paint.
    5. `float` `$angle` The angle of the paint in radians. (The rotation is around the center of the paint.)
    6. `float` `$alpha` The alpha value of the paint.

---

