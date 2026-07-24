# SVGImage

`SVGImage` holds a parsed SVG document ready to be drawn as real vector paths. You parse the file
once (it is relatively expensive), keep the resulting `SVGImage` around, and then render it as often
as you like with [`VGContext::drawSVG`](../../API/VectorGraphics/VGContext.md#drawsvg). Because it is
drawn as paths rather than a bitmap, it stays crisp at any size.

```php
namespace GL\VectorGraphics
{
    class SVGImage {}
}
```

!!! note "What is supported"
    Solid fills and strokes are rendered. Gradient paints are skipped for now, and alpha masks
    (`mask="url(#id)"`) are honored as a 1-bit (hard edged) clip.

## Usage

Parse once outside your render loop, then draw it, optionally scaled to a target size.

```php
use GL\VectorGraphics\SVGImage;

// parse once, reuse every frame
$logo = SVGImage::fromDisk(__DIR__ . '/logo.svg');

echo "Native size: {$logo->width} x {$logo->height}\n";

// ... inside the frame:
$vg->drawSVG($logo, 40, 40);            // at native size
$vg->drawSVG($logo, 40, 240, 128, 128); // scaled to fit 128x128
```

## Properties

| Property | Meaning |
|----------|---------|
| `$width` | The native width of the parsed document in pixels (read-only). |
| `$height` | The native height of the parsed document in pixels (read-only). |

## Methods

<?php foreach([
    'fromDisk',
    'fromString',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\SVGImage::' . $funcName); ?>
<?php endforeach; ?>
