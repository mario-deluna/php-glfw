# VGPaint

A `VGPaint` describes how a shape is filled or stroked with something richer than a flat color:
a gradient or an image. It is an opaque handle with no methods or properties of its own. You obtain
one from a factory and then hand it to the context to use it.

```php
namespace GL\VectorGraphics
{
    class VGPaint {}
}
```

You create a `VGPaint` from one of:

- [`VGContext::linearGradient`](/API/VectorGraphics/VGContext.html#lineargradient)
- [`VGContext::boxGradient`](/API/VectorGraphics/VGContext.html#boxgradient)
- [`VGContext::radialGradient`](/API/VectorGraphics/VGContext.html#radialgradient)
- [`VGImage::makePaint`](/API/VectorGraphics/VGImage.html#makepaint) /
  [`makePaintCentered`](/API/VectorGraphics/VGImage.html#makepaintcentered)

And you use it with:

- [`VGContext::fillPaint`](/API/VectorGraphics/VGContext.html#fillpaint)
- [`VGContext::strokePaint`](/API/VectorGraphics/VGContext.html#strokepaint)

!!! tip "Looking for a walkthrough?"
    The [Gradients](/user-guide/vector-graphics/gradients.html) and
    [Images](/user-guide/vector-graphics/images.html) user guides show paints in action.

## Usage

```php
use GL\VectorGraphics\VGColor;

// build a paint from a gradient
$paint = $vg->linearGradient(0, 0, 0, 200, VGColor::red(), VGColor::blue());

// use it as the fill for the next shape
$vg->beginPath();
$vg->rect(0, 0, 200, 200);
$vg->fillPaint($paint);
$vg->fill();
```
