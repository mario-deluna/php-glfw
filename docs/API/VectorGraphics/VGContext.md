# VGContext

The `VGContext` is your canvas for 2D vector graphics. It wraps a NanoVG rendering context and gives
you everything you need to draw crisp, resolution-independent shapes, gradients, images and text
directly on top of your OpenGL scene. You build a shape by describing a path, choose how it is
painted with a [`VGColor`](../../API/VectorGraphics/VGColor.md) or a
[`VGPaint`](../../API/VectorGraphics/VGPaint.md), and then fill or stroke it.

```php
namespace GL\VectorGraphics
{
    class VGContext {}
}
```

!!! tip "Looking for a walkthrough?"
    This page is the exhaustive class reference. If you are just getting started, the
    [Vector Graphics user guide](../../user-guide/vector-graphics/creating_a_vgcontext.md) walks you
    through creating a context, drawing your first shapes, colors, gradients, images and text with
    small runnable examples.

## Usage

Everything you draw happens between a `beginFrame` and an `endFrame` call. Inside that frame you open
a path, describe your geometry, pick a color and then fill it.

```php
use GL\VectorGraphics\{VGContext, VGColor};

// create a context once, antialiasing enabled
$vg = new VGContext(VGContext::ANTIALIAS);

// ... inside your render loop, after clearing the screen:
$vg->beginFrame($windowWidth, $windowHeight, $devicePixelRatio);

$vg->beginPath();
$vg->rect(100, 100, 200, 120);
$vg->fillColor(VGColor::red());
$vg->fill();

// dispatch all queued draw commands to the GPU
$vg->endFrame();
```

## Constants

### Context flags

Pass these to the constructor, combined with the bitwise OR operator (`|`).

| Constant | Value | Meaning |
|----------|-------|---------|
| `VGContext::ANTIALIAS` | 1 | Smooth the edges of shapes and text. |
| `VGContext::STENCIL_STROKES` | 2 | More accurate stroke rendering for overlapping shapes. |
| `VGContext::DEBUG` | 4 | Enable extra error checks while developing. |

### Path winding

Used with [`pathWinding`](#pathwinding) and [`arc`](#arc) to control solid versus hole subpaths.

| Constant | Value | Meaning |
|----------|-------|---------|
| `VGContext::CCW` | 1 | Counter-clockwise winding (solid shapes). |
| `VGContext::CW` | 2 | Clockwise winding (holes). |
| `VGContext::SOLID` | 1 | Alias of `CCW`, reads better when filling. |
| `VGContext::HOLE` | 2 | Alias of `CW`, reads better when cutting holes. |

### Line caps and joins

Used with [`lineCap`](#linecap) and [`lineJoin`](#linejoin).

| Constant | Value | Meaning |
|----------|-------|---------|
| `VGContext::LINECAP_BUTT` | 0 | Flat cap flush with the line end. |
| `VGContext::LINECAP_ROUND` | 1 | Rounded cap. |
| `VGContext::LINECAP_SQUARE` | 2 | Square cap extending past the line end. |
| `VGContext::LINEJOIN_BEVEL` | 3 | Beveled corner. |
| `VGContext::LINEJOIN_MITER` | 4 | Sharp mitered corner. |

## Frame Lifecycle

### `beginFrame`

Begins drawing a new frame.

```php
function beginFrame(float $windowWidth, float $windowHeight, float $devicePixelRatio) : void
```

Example:

```php
$vg->beginFrame($windowWidth, $windowHeight, $devicePixelRatio);
// draw commands here
$vg->endFrame();
```

arguments

:    1. `float` `$windowWidth` The width of the window in pixels.
    2. `float` `$windowHeight` The height of the window in pixels.
    3. `float` `$devicePixelRatio` The device pixel ratio.

returns

:    `void` 

---

### `cancelFrame`

cancelFrame

```php
function cancelFrame() : void
```

returns

:    `void` 

---

### `endFrame`

Ends drawing the current frame.

```php
function endFrame() : void
```

Example:

```php
$vg->beginFrame($windowWidth, $windowHeight, $devicePixelRatio);
// draw commands here
$vg->endFrame();
```

returns

:    `void` 

---


## Render State

The context keeps a stack of render states (transform, styles, scissor). Wrap changes in
[`save`](#save) / [`restore`](#restore) to keep them local.

### `save`

Saves the current render state onto a state stack.

```php
function save() : void
```

Example:

```php
$vg->save();
// modify state here
$vg->restore();
```

returns

:    `void` 

---

### `restore`

Restores the render state from the state stack.

```php
function restore() : void
```

Example:

```php
$vg->save();
// modify state here
$vg->restore();
```

returns

:    `void` 

---

### `reset`

Resets the current render state to default values.

```php
function reset() : void
```

returns

:    `void` 

---

### `shapeAntiAlias`

shapeAntiAlias

```php
function shapeAntiAlias(int $enabled) : void
```

arguments

:    1. `int` `$enabled` 

returns

:    `void` 

---

### `globalAlpha`

globalAlpha

```php
function globalAlpha(float $alpha) : void
```

arguments

:    1. `float` `$alpha` 

returns

:    `void` 

---

### `globalCompositeOperation`

globalCompositeOperation

```php
function globalCompositeOperation(int $op) : void
```

arguments

:    1. `int` `$op` 

returns

:    `void` 

---

### `globalCompositeBlendFunc`

globalCompositeBlendFunc

```php
function globalCompositeBlendFunc(int $sfactor, int $dfactor) : void
```

arguments

:    1. `int` `$sfactor` 
    2. `int` `$dfactor` 

returns

:    `void` 

---

### `globalCompositeBlendFuncSeparate`

globalCompositeBlendFuncSeparate

```php
function globalCompositeBlendFuncSeparate(int $srcRGB, int $dstRGB, int $srcAlpha, int $dstAlpha) : void
```

arguments

:    1. `int` `$srcRGB` 
    2. `int` `$dstRGB` 
    3. `int` `$srcAlpha` 
    4. `int` `$dstAlpha` 

returns

:    `void` 

---


## Fill & Stroke Style

These decide how the next [`fill`](#fill) or [`stroke`](#stroke) is painted.

### `fillColor`

Sets the fill color.

```php
function fillColor(\GL\VectorGraphics\VGColor $color) : void
```

Example:

```php
$color = new VGColor(1.0, 0.0, 0.0, 1.0);
$vg->fillColor($color);
```

arguments

:    1. `\GL\VectorGraphics\VGColor` `$color` The fill color.

returns

:    `void` 

---

### `strokeColor`

Sets the stroke color.

```php
function strokeColor(\GL\VectorGraphics\VGColor $color) : void
```

Example:

```php
$color = new VGColor(0.0, 0.0, 0.0, 1.0);
$vg->strokeColor($color);
```

arguments

:    1. `\GL\VectorGraphics\VGColor` `$color` The stroke color.

returns

:    `void` 

---

### `fillColori`

Sets the fill color using integer values.

```php
function fillColori(int $r, int $g, int $b, int $a) : void
```

arguments

:    1. `int` `$r` The red component (0-255).
    2. `int` `$g` The green component (0-255).
    3. `int` `$b` The blue component (0-255).
    4. `int` `$a` The alpha component (0-255), where 255 is fully opaque.

---

### `strokeColori`

Sets the stroke color using integer values.

```php
function strokeColori(int $r, int $g, int $b, int $a) : void
```

arguments

:    1. `int` `$r` The red component (0-255).
    2. `int` `$g` The green component (0-255).
    3. `int` `$b` The blue component (0-255).
    4. `int` `$a` The alpha component (0-255), where 255 is fully opaque.

---

### `fillColorVec4`

Sets the fill color using a Vec4 object.

```php
function fillColorVec4(\GL\Math\Vec4 $vec) : void
```

arguments

:    1. `\GL\Math\Vec4` `$vec` A vector containing the RGBA components of the color.

---

### `strokeColorVec4`

Sets the stroke color using a Vec4 object.

```php
function strokeColorVec4(\GL\Math\Vec4 $vec) : void
```

arguments

:    1. `\GL\Math\Vec4` `$vec` A vector containing the RGBA components of the color.

---

### `fillPaint`

fillPaint

```php
function fillPaint(\GL\VectorGraphics\VGPaint $paint) : void
```

arguments

:    1. `\GL\VectorGraphics\VGPaint` `$paint` 

returns

:    `void` 

---

### `strokePaint`

strokePaint

```php
function strokePaint(\GL\VectorGraphics\VGPaint $paint) : void
```

arguments

:    1. `\GL\VectorGraphics\VGPaint` `$paint` 

returns

:    `void` 

---

### `strokeWidth`

Sets the stroke width.

```php
function strokeWidth(float $size) : void
```

Example:

```php
$vg->strokeWidth(2.0);
```

arguments

:    1. `float` `$size` The stroke width.

returns

:    `void` 

---

### `miterLimit`

miterLimit

```php
function miterLimit(float $limit) : void
```

arguments

:    1. `float` `$limit` 

returns

:    `void` 

---

### `lineCap`

lineCap

```php
function lineCap(int $cap) : void
```

arguments

:    1. `int` `$cap` 

returns

:    `void` 

---

### `lineJoin`

lineJoin

```php
function lineJoin(int $join) : void
```

arguments

:    1. `int` `$join` 

returns

:    `void` 

---


## Gradients & Paints

Each of these returns a [`VGPaint`](../../API/VectorGraphics/VGPaint.md) you hand to
[`fillPaint`](#fillpaint) or [`strokePaint`](#strokepaint).

### `linearGradient`

Creates a linear gradient paint object.

```php
function linearGradient(float $sx, float $sy, float $ex, float $ey, \GL\VectorGraphics\VGColor $icol, \GL\VectorGraphics\VGColor $ocol) : \GL\VectorGraphics\VGPaint
```

The gradient is defined by the start and end points, as well as the colors at these points.

```php
$x1 = 50;
$y1 = 150;
$x2 = 350;
$y2 = 450;
$color1 = new VGColor(0.051, 0.682, 0.914, 1.0);
$color2 = new VGColor(0.169, 0.961, 0.596, 1.0);

$paint = $vg->linearGradient($x1, $y1, $x2, $y2, $color1, $color2);
```

arguments

:    1. `float` `$sx` The x-coordinate of the start point of the gradient.
    2. `float` `$sy` The y-coordinate of the start point of the gradient.
    3. `float` `$ex` The x-coordinate of the end point of the gradient.
    4. `float` `$ey` The y-coordinate of the end point of the gradient.
    5. `\VGColor` `$icol` The color at the start point of the gradient.
    6. `\VGColor` `$ocol` The color at the end point of the gradient.

---

### `boxGradient`

Creates a box gradient paint object.

```php
function boxGradient(float $x, float $y, float $w, float $h, float $r, float $f, \GL\VectorGraphics\VGColor $icol, \GL\VectorGraphics\VGColor $ocol) : \GL\VectorGraphics\VGPaint
```

```php
$x = 100;
$y = 100;
$width = 200;
$height = 100;
$radius = 10;
$feather = 20;
$color1 = new VGColor(0.051, 0.682, 0.914, 1.0);
$color2 = new VGColor(0.169, 0.961, 0.596, 1.0);

$paint = $vg->boxGradient($x, $y, $width, $height, $radius, $feather, $color1, $color2);
```

arguments

:    1. `float` `$x` The x-coordinate of the top left corner of the box.
    2. `float` `$y` The y-coordinate of the top left corner of the box.
    3. `float` `$w` The width of the box.
    4. `float` `$h` The height of the box.
    5. `float` `$r` The corner radius of the box.
    6. `float` `$f` The feathering amount (how much the gradient fades).
    7. `\VGColor` `$icol` The color inside the box.
    8. `\VGColor` `$ocol` The color outside the box.

---

### `radialGradient`

Creates a radial gradient paint object.

```php
function radialGradient(float $cx, float $cy, float $inr, float $outr, \GL\VectorGraphics\VGColor $icol, \GL\VectorGraphics\VGColor $ocol) : \GL\VectorGraphics\VGPaint
```

The gradient is defined by the center point and two radii, with the color transitioning from the inner to the outer radius.

```php
$cx = 150;
$cy = 150;
$innerRadius = 50;
$outerRadius = 100;
$color1 = new VGColor(0.914, 0.051, 0.682, 1.0);
$color2 = new VGColor(0.961, 0.596, 0.169, 1.0);

$paint = $vg->radialGradient($cx, $cy, $innerRadius, $outerRadius, $color1, $color2);
```

arguments

:    1. `float` `$cx` The x-coordinate of the center of the gradient.
    2. `float` `$cy` The y-coordinate of the center of the gradient.
    3. `float` `$inr` The inner radius of the gradient.
    4. `float` `$outr` The outer radius of the gradient.
    5. `\VGColor` `$icol` The color at the inner radius.
    6. `\VGColor` `$ocol` The color at the outer radius.

---


## Images & SVG

Turn a [`Texture2D`](../../API/Texture/Texture2D.md) into a
[`VGImage`](../../API/VectorGraphics/VGImage.md), or draw a parsed
[`SVGImage`](../../API/VectorGraphics/SVGImage.md) straight into the frame.

### `imageFromTexture`

Creates a VGImage object from a given texture.

```php
function imageFromTexture(\GL\Texture\Texture2D $texture, int $repeatMode = \GL\VectorGraphics\VGImage::REPEAT_NONE, int $filterMode = \GL\VectorGraphics\VGImage::FILTER_LINEAR) : \GL\VectorGraphics\VGImage
```

This will upload the texture to the GPU.

```php
$image = $vg->imageFromTexture($texture, VGImage::REPEAT_XY, VGImage::FILTER_LINEAR);
```

arguments

:    1. `\GL\Texture\Texture2D` `$texture` The texture to create the image from.
    2. `int` `$repeatMode` This can be either VGImage::REPEAT_XY, VGImage::REPEAT_X, VGImage::REPEAT_Y, or VGImage::REPEAT_NONE.
    This controls how the image is repeated when the shape is larger than the image.
    The default is VGImage::REPEAT_NONE.
    3. `int` `$filterMode` This can be either VGImage::FILTER_LINEAR or VGImage::FILTER_NEAREST.
    This controls how the image is filtered when it is scaled.
    The default is VGImage::FILTER_LINEAR.

---

### `imageFromHandle`

Creates a VGImage object from a given texture handle.

```php
function imageFromHandle(int $handle, int $width, int $height, int $repeatMode = \GL\VectorGraphics\VGImage::REPEAT_NONE, int $filterMode = \GL\VectorGraphics\VGImage::FILTER_LINEAR) : \GL\VectorGraphics\VGImage
```

This will reference the texture already uploaded to the GPU.

```php
$image = $vg->imageFromHandle($handle, $width, $height, VGImage::REPEAT_XY, VGImage::FILTER_LINEAR);
```

arguments

:    1. `int` `$handle` The GPU handle of the texture.
    2. `int` `$width` The width of the texture.
    3. `int` `$height` The height of the texture.
    4. `int` `$repeatMode` This can be either VGImage::REPEAT_XY, VGImage::REPEAT_X, VGImage::REPEAT_Y, or VGImage::REPEAT_NONE.
    This controls how the image is repeated when the shape is larger than the image.
    The default is VGImage::REPEAT_NONE.
    5. `int` `$filterMode` This can be either VGImage::FILTER_LINEAR or VGImage::FILTER_NEAREST.
    This controls how the image is filtered when it is scaled.
    The default is VGImage::FILTER_LINEAR.

---

### `imageSize`

imageSize

```php
function imageSize(int $image, int &$w, int &$h) : void
```

arguments

:    1. `int` `$image` 
    2. `int` `$w` 
    3. `int` `$h` 

returns

:    `void` 

---

### `deleteImage`

deleteImage

```php
function deleteImage(int $image) : void
```

arguments

:    1. `int` `$image` 

returns

:    `void` 

---

### `drawSVG`

Renders a parsed SVGImage as vector paths into the current frame.

```php
function drawSVG(\GL\VectorGraphics\SVGImage $svg, float $x = 0.0, float $y = 0.0, ?float $w = null, ?float $h = null) : void
```

When $w and $h are omitted the SVG is drawn at its native size,
otherwise it is scaled to fit the given width/height.

Only solid fills/strokes are rendered; gradient paints are skipped for now.
Alpha masks (mask="url(#id)") are honoured as a 1-bit (hard edged) clip.

arguments

:    1. `\SVGImage` `$svg` The parsed SVG image to draw.
    2. `float` `$x` The x-coordinate of the top left corner.
    3. `float` `$y` The y-coordinate of the top left corner.
    4. `float|null` `$w` Target width; null draws at native width.
    5. `float|null` `$h` Target height; null draws at native height.

---


## Transforms

Transforms are applied on top of each other and stored in the render state, so they respect
[`save`](#save) / [`restore`](#restore).

### `resetTransform`

resetTransform

```php
function resetTransform() : void
```

returns

:    `void` 

---

### `transform`

transform

```php
function transform(float $a, float $b, float $c, float $d, float $e, float $f) : void
```

arguments

:    1. `float` `$a` 
    2. `float` `$b` 
    3. `float` `$c` 
    4. `float` `$d` 
    5. `float` `$e` 
    6. `float` `$f` 

returns

:    `void` 

---

### `translate`

translate

```php
function translate(float $x, float $y) : void
```

arguments

:    1. `float` `$x` 
    2. `float` `$y` 

returns

:    `void` 

---

### `rotate`

rotate

```php
function rotate(float $angle) : void
```

arguments

:    1. `float` `$angle` 

returns

:    `void` 

---

### `skewX`

skewX

```php
function skewX(float $angle) : void
```

arguments

:    1. `float` `$angle` 

returns

:    `void` 

---

### `skewY`

skewY

```php
function skewY(float $angle) : void
```

arguments

:    1. `float` `$angle` 

returns

:    `void` 

---

### `scale`

scale

```php
function scale(float $x, float $y) : void
```

arguments

:    1. `float` `$x` 
    2. `float` `$y` 

returns

:    `void` 

---

### `currentTransform`

currentTransform

```php
function currentTransform(\GL\Buffer\FloatBuffer $buffer) : void
```

arguments

:    1. `\GL\Buffer\FloatBuffer` `$buffer` 

returns

:    `void` 

---

### `transformPoint`

Transforms a point using the current transformation matrix.

```php
function transformPoint(float $x, float $y) : \GL\Math\Vec2
```

arguments

:    1. `float` `$x` The x-coordinate of the point.
    2. `float` `$y` The y-coordinate of the point.

returns

:    `\GL\Math\Vec2` The transformed point as a Vec2 object.

---

### `transformVec2`

Transforms a vector using the current transformation matrix.

```php
function transformVec2(\GL\Math\Vec2 $vec) : \GL\Math\Vec2
```

arguments

:    1. `\GL\Math\Vec2` `$vec` The vector to transform.

returns

:    `\GL\Math\Vec2` The transformed vector.

---

### `transformPointCurrent`

transformPointCurrent

```php
function transformPointCurrent(float &$dstx, float &$dsty, float $srcx, float $srcy) : void
```

arguments

:    1. `float` `$dstx` 
    2. `float` `$dsty` 
    3. `float` `$srcx` 
    4. `float` `$srcy` 

returns

:    `void` 

---


## Scissoring

Limit drawing to a rectangular region. Like transforms, scissors are part of the render state.

### `scissor`

scissor

```php
function scissor(float $x, float $y, float $w, float $h) : void
```

arguments

:    1. `float` `$x` 
    2. `float` `$y` 
    3. `float` `$w` 
    4. `float` `$h` 

returns

:    `void` 

---

### `intersectScissor`

intersectScissor

```php
function intersectScissor(float $x, float $y, float $w, float $h) : void
```

arguments

:    1. `float` `$x` 
    2. `float` `$y` 
    3. `float` `$w` 
    4. `float` `$h` 

returns

:    `void` 

---

### `resetScissor`

resetScissor

```php
function resetScissor() : void
```

returns

:    `void` 

---


## Building Paths

Open a new path with [`beginPath`](#beginpath), then describe it with these commands before you
[`fill`](#fill) or [`stroke`](#stroke) it.

### `beginPath`

Begins a new path.

```php
function beginPath() : void
```

Example:

```php
$vg->beginPath();
$vg->rect(100, 100, 200, 100);
$vg->fill();
```

returns

:    `void` 

---

### `moveTo`

moveTo

```php
function moveTo(float $x, float $y) : void
```

arguments

:    1. `float` `$x` 
    2. `float` `$y` 

returns

:    `void` 

---

### `lineTo`

lineTo

```php
function lineTo(float $x, float $y) : void
```

arguments

:    1. `float` `$x` 
    2. `float` `$y` 

returns

:    `void` 

---

### `bezierTo`

bezierTo

```php
function bezierTo(float $c1x, float $c1y, float $c2x, float $c2y, float $x, float $y) : void
```

arguments

:    1. `float` `$c1x` 
    2. `float` `$c1y` 
    3. `float` `$c2x` 
    4. `float` `$c2y` 
    5. `float` `$x` 
    6. `float` `$y` 

returns

:    `void` 

---

### `quadTo`

quadTo

```php
function quadTo(float $cx, float $cy, float $x, float $y) : void
```

arguments

:    1. `float` `$cx` 
    2. `float` `$cy` 
    3. `float` `$x` 
    4. `float` `$y` 

returns

:    `void` 

---

### `arcTo`

arcTo

```php
function arcTo(float $x1, float $y1, float $x2, float $y2, float $radius) : void
```

arguments

:    1. `float` `$x1` 
    2. `float` `$y1` 
    3. `float` `$x2` 
    4. `float` `$y2` 
    5. `float` `$radius` 

returns

:    `void` 

---

### `closePath`

closePath

```php
function closePath() : void
```

returns

:    `void` 

---

### `pathWinding`

pathWinding

```php
function pathWinding(int $dir) : void
```

arguments

:    1. `int` `$dir` 

returns

:    `void` 

---

### `arc`

arc

```php
function arc(float $cx, float $cy, float $r, float $a0, float $a1, int $dir) : void
```

arguments

:    1. `float` `$cx` 
    2. `float` `$cy` 
    3. `float` `$r` 
    4. `float` `$a0` 
    5. `float` `$a1` 
    6. `int` `$dir` 

returns

:    `void` 

---

### `rect`

Creates a rectangle path.

```php
function rect(float $x, float $y, float $w, float $h) : void
```

Example:

```php
$vg->beginPath();
$vg->rect(100, 100, 200, 100);
$vg->fill();
```

arguments

:    1. `float` `$x` The x-coordinate of the top-left corner.
    2. `float` `$y` The y-coordinate of the top-left corner.
    3. `float` `$w` The width of the rectangle.
    4. `float` `$h` The height of the rectangle.

returns

:    `void` 

---

### `roundedRect`

roundedRect

```php
function roundedRect(float $x, float $y, float $w, float $h, float $r) : void
```

arguments

:    1. `float` `$x` 
    2. `float` `$y` 
    3. `float` `$w` 
    4. `float` `$h` 
    5. `float` `$r` 

returns

:    `void` 

---

### `roundedRectVarying`

roundedRectVarying

```php
function roundedRectVarying(float $x, float $y, float $w, float $h, float $radTopLeft, float $radTopRight, float $radBottomRight, float $radBottomLeft) : void
```

arguments

:    1. `float` `$x` 
    2. `float` `$y` 
    3. `float` `$w` 
    4. `float` `$h` 
    5. `float` `$radTopLeft` 
    6. `float` `$radTopRight` 
    7. `float` `$radBottomRight` 
    8. `float` `$radBottomLeft` 

returns

:    `void` 

---

### `ellipse`

ellipse

```php
function ellipse(float $cx, float $cy, float $rx, float $ry) : void
```

arguments

:    1. `float` `$cx` 
    2. `float` `$cy` 
    3. `float` `$rx` 
    4. `float` `$ry` 

returns

:    `void` 

---

### `circle`

Creates a circle path.

```php
function circle(float $cx, float $cy, float $r) : void
```

Example:

```php
$vg->beginPath();
$vg->circle(150, 150, 50);
$vg->fill();
```

arguments

:    1. `float` `$cx` The x-coordinate of the center.
    2. `float` `$cy` The y-coordinate of the center.
    3. `float` `$r` The radius of the circle.

returns

:    `void` 

---


## Rendering Paths

### `fill`

Fills the current path with the current fill color or paint.

```php
function fill() : void
```

Example:

```php
$vg->beginPath();
$vg->rect(100, 100, 200, 100);
$vg->fill();
```

returns

:    `void` 

---

### `fillEvenOdd`

fillEvenOdd

```php
function fillEvenOdd() : void
```

returns

:    `void` 

---

### `stroke`

Strokes the current path with the current stroke color or paint.

```php
function stroke() : void
```

Example:

```php
$vg->beginPath();
$vg->rect(100, 100, 200, 100);
$vg->stroke();
```

returns

:    `void` 

---


## Clipping

### `clip`

clip

```php
function clip() : void
```

returns

:    `void` 

---

### `resetClip`

resetClip

```php
function resetClip() : void
```

returns

:    `void` 

---

### `saveClip`

saveClip

```php
function saveClip() : void
```

returns

:    `void` 

---

### `restoreClip`

restoreClip

```php
function restoreClip() : void
```

returns

:    `void` 

---


## Fonts & Text

Load a font once with [`createFont`](#createfont), then set the size and alignment
(using the [`VGAlign`](../../API/VectorGraphics/VGAlign.md) constants) before drawing with
[`text`](#text) or [`textBox`](#textbox).

### `createFont`

createFont

```php
function createFont(string $name, string $filename) : int
```

arguments

:    1. `string` `$name` 
    2. `string` `$filename` 

returns

:    `int` 

---

### `createFontAtIndex`

createFontAtIndex

```php
function createFontAtIndex(string $name, string $filename, int $fontIndex) : int
```

arguments

:    1. `string` `$name` 
    2. `string` `$filename` 
    3. `int` `$fontIndex` 

returns

:    `int` 

---

### `findFont`

findFont

```php
function findFont(string $name) : int
```

arguments

:    1. `string` `$name` 

returns

:    `int` 

---

### `addFallbackFontId`

addFallbackFontId

```php
function addFallbackFontId(int $baseFont, int $fallbackFont) : int
```

arguments

:    1. `int` `$baseFont` 
    2. `int` `$fallbackFont` 

returns

:    `int` 

---

### `addFallbackFont`

addFallbackFont

```php
function addFallbackFont(string $baseFont, string $fallbackFont) : int
```

arguments

:    1. `string` `$baseFont` 
    2. `string` `$fallbackFont` 

returns

:    `int` 

---

### `resetFallbackFontsId`

resetFallbackFontsId

```php
function resetFallbackFontsId(int $baseFont) : void
```

arguments

:    1. `int` `$baseFont` 

returns

:    `void` 

---

### `resetFallbackFonts`

resetFallbackFonts

```php
function resetFallbackFonts(string $baseFont) : void
```

arguments

:    1. `string` `$baseFont` 

returns

:    `void` 

---

### `fontSize`

fontSize

```php
function fontSize(float $size) : void
```

arguments

:    1. `float` `$size` 

returns

:    `void` 

---

### `fontBlur`

fontBlur

```php
function fontBlur(float $blur) : void
```

arguments

:    1. `float` `$blur` 

returns

:    `void` 

---

### `textLetterSpacing`

textLetterSpacing

```php
function textLetterSpacing(float $spacing) : void
```

arguments

:    1. `float` `$spacing` 

returns

:    `void` 

---

### `textLineHeight`

textLineHeight

```php
function textLineHeight(float $lineHeight) : void
```

arguments

:    1. `float` `$lineHeight` 

returns

:    `void` 

---

### `textAlign`

textAlign

```php
function textAlign(int $align) : void
```

arguments

:    1. `int` `$align` 

returns

:    `void` 

---

### `fontFaceId`

fontFaceId

```php
function fontFaceId(int $font) : void
```

arguments

:    1. `int` `$font` 

returns

:    `void` 

---

### `fontFace`

fontFace

```php
function fontFace(string $font) : void
```

arguments

:    1. `string` `$font` 

returns

:    `void` 

---

### `text`

Draws text at the specified position.

```php
function text(float $x, float $y, string $string) : float
```

Example:

```php
$vg->fontSize(18.0);
$advance = $vg->text(100, 100, "Hello, World!");
```

arguments

:    1. `float` `$x` The x-coordinate of the text position.
    2. `float` `$y` The y-coordinate of the text position.
    3. `string` `$string` The text string to draw.

returns

:    `float` float The horizontal advance of the text.

---

### `textBox`

textBox

```php
function textBox(float $x, float $y, float $breakRowWidth, string $string) : void
```

arguments

:    1. `float` `$x` 
    2. `float` `$y` 
    3. `float` `$breakRowWidth` 
    4. `string` `$string` 

returns

:    `void` 

---

### `textBounds`

Calculates the bounding box of the specified text and returns the horizontal
advance.

```php
function textBounds(float $x, float $y, string $string, ?\GL\Math\Vec4 &$bounds = NULL) : float
```

Example:

```php
$vg->fontSize(18.0);
$bounds = new Vec4();
$advance = $vg->textBounds(100, 100, "Hello, World!", $bounds);
echo "Text bounds: " . $bounds . "\n";
echo "Text advance: " . $advance . "\n";
```

arguments

:    1. `float` `$x` The x of the text position.
    2. `float` `$y` The y of the text position.
    3. `string` `$string` The text string to measure.
    4. `?\GL\Math\Vec4` `$bounds` Vec4 object in which the calculated bounds are
    stored [xmin, ymin, xmax, ymax].

returns

:    `float` The horizontal advance of the text.

---

### `textBoxBounds`

textBoxBounds

```php
function textBoxBounds(float $x, float $y, float $breakRowWidth, string $string, ?\GL\Math\Vec4 &$bounds = NULL) : void
```

arguments

:    1. `float` `$x` 
    2. `float` `$y` 
    3. `float` `$breakRowWidth` 
    4. `string` `$string` 
    5. `?\GL\Math\Vec4` `$bounds` 

returns

:    `void` 

---

### `textMetrics`

textMetrics

```php
function textMetrics(float &$ascender, float &$descender, float &$lineh) : void
```

arguments

:    1. `float` `$ascender` 
    2. `float` `$descender` 
    3. `float` `$lineh` 

returns

:    `void` 

---

