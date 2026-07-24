# VGColor

`VGColor` is a small, immutable RGBA color value used everywhere in the vector graphics API. Instead
of juggling raw float components you get a friendly object with named colors, hex and HSL
constructors, and handy tweaks like [`darken`](#darken), [`lighten`](#lighten) and
[`withAlpha`](#withalpha). You hand a `VGColor` to
[`VGContext::fillColor`](../../API/VectorGraphics/VGContext.md#fillcolor) or
[`strokeColor`](../../API/VectorGraphics/VGContext.md#strokecolor) to paint your shapes.

```php
namespace GL\VectorGraphics
{
    class VGColor {}
}
```

!!! tip "Looking for a walkthrough?"
    For a gentle, example-first tour of colors (named colors, hex, HSL and adjusting lightness), see
    the [Colors user guide](../../user-guide/vector-graphics/colors.md).

## Usage

Reach for a named color, build one from a hex string, or construct it directly from components in the
`[0.0, 1.0]` range.

```php
use GL\VectorGraphics\VGColor;

$red   = VGColor::red();              // a named color
$brand = VGColor::hex('#2ecc71');     // from a hex string
$warm  = VGColor::irgb(255, 165, 0);  // from 0-255 integer components
$raw   = new VGColor(0.1, 0.2, 0.3, 1.0); // components in [0.0, 1.0]

// derive new colors without mutating the originals
$hover = $brand->lighten(0.1);
$ghost = $brand->withAlpha(0.5);
```

## Properties

A `VGColor` exposes its four components as read/write float properties, each in the `[0.0, 1.0]`
range:

| Property | Meaning |
|----------|---------|
| `$r` | Red component. |
| `$g` | Green component. |
| `$b` | Blue component. |
| `$a` | Alpha component (0.0 fully transparent, 1.0 fully opaque). |

## Constructors

<?php foreach([
    'rgb',
    'rgba',
    'irgb',
    'irgba',
    'hsl',
    'hsla',
    'hex',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGColor::' . $funcName); ?>
<?php endforeach; ?>

## Named Colors

Convenient presets for the common cases. `random` and `randomGray` are handy for quick debugging and
visual tests.

<?php foreach([
    'red',
    'green',
    'blue',
    'white',
    'black',
    'transparent',
    'yellow',
    'cyan',
    'magenta',
    'orange',
    'pink',
    'purple',
    'brown',
    'gray',
    'darkGray',
    'lightGray',
    'random',
    'randomGray',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGColor::' . $funcName); ?>
<?php endforeach; ?>

## Conversions & Adjustments

These return new `VGColor` (or vector) values and leave the original untouched.

<?php foreach([
    'getHSLA',
    'getHSL',
    'getVec4',
    'getVec3',
    'darken',
    'lighten',
    'invert',
    'withAlpha',
    'copy',
    'contrast',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGColor::' . $funcName); ?>
<?php endforeach; ?>
