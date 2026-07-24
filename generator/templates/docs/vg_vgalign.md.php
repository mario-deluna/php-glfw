# VGAlign

`VGAlign` is a small collection of constants that tell
[`VGContext::textAlign`](../../API/VectorGraphics/VGContext.md#textalign) where to anchor text relative
to the coordinate you pass to [`text`](../../API/VectorGraphics/VGContext.md#text). You combine exactly
one horizontal option with one vertical option using the bitwise OR operator (`|`).

```php
namespace GL\VectorGraphics
{
    class VGAlign {}
}
```

!!! tip "Looking for a walkthrough?"
    The [Text & Fonts user guide](../../user-guide/vector-graphics/text.md) shows alignment in a
    complete example.

## Usage

```php
use GL\VectorGraphics\VGAlign;

// anchor text at its left edge, vertically centered on the y coordinate
$vg->textAlign(VGAlign::LEFT | VGAlign::MIDDLE);
$vg->text(20, 100, "Hello world");
```

## Constants

### Horizontal alignment

| Constant | Value | Meaning |
|----------|-------|---------|
| `VGAlign::LEFT` | 1 | Anchor at the left edge (the default). |
| `VGAlign::CENTER` | 2 | Anchor at the horizontal center. |
| `VGAlign::RIGHT` | 4 | Anchor at the right edge. |

### Vertical alignment

| Constant | Value | Meaning |
|----------|-------|---------|
| `VGAlign::TOP` | 8 | Anchor at the top of the text. |
| `VGAlign::MIDDLE` | 16 | Anchor at the vertical center. |
| `VGAlign::BOTTOM` | 32 | Anchor at the bottom. |
| `VGAlign::BASELINE` | 64 | Anchor at the text baseline (the default). |
