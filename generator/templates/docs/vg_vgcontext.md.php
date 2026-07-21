# VGContext

The `VGContext` is your canvas for 2D vector graphics. It wraps a NanoVG rendering context and gives
you everything you need to draw crisp, resolution-independent shapes, gradients, images and text
directly on top of your OpenGL scene. You build a shape by describing a path, choose how it is
painted with a [`VGColor`](/API/VectorGraphics/VGColor.html) or a
[`VGPaint`](/API/VectorGraphics/VGPaint.html), and then fill or stroke it.

```php
namespace GL\VectorGraphics
{
    class VGContext {}
}
```

!!! tip "Looking for a walkthrough?"
    This page is the exhaustive class reference. If you are just getting started, the
    [Vector Graphics user guide](/user-guide/vector-graphics/creating_a_vgcontext.html) walks you
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

<?php foreach([
    'beginFrame',
    'cancelFrame',
    'endFrame',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGContext::' . $funcName); ?>
<?php endforeach; ?>

## Render State

The context keeps a stack of render states (transform, styles, scissor). Wrap changes in
[`save`](#save) / [`restore`](#restore) to keep them local.

<?php foreach([
    'save',
    'restore',
    'reset',
    'shapeAntiAlias',
    'globalAlpha',
    'globalCompositeOperation',
    'globalCompositeBlendFunc',
    'globalCompositeBlendFuncSeparate',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGContext::' . $funcName); ?>
<?php endforeach; ?>

## Fill & Stroke Style

These decide how the next [`fill`](#fill) or [`stroke`](#stroke) is painted.

<?php foreach([
    'fillColor',
    'strokeColor',
    'fillColori',
    'strokeColori',
    'fillColorVec4',
    'strokeColorVec4',
    'fillPaint',
    'strokePaint',
    'strokeWidth',
    'miterLimit',
    'lineCap',
    'lineJoin',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGContext::' . $funcName); ?>
<?php endforeach; ?>

## Gradients & Paints

Each of these returns a [`VGPaint`](/API/VectorGraphics/VGPaint.html) you hand to
[`fillPaint`](#fillpaint) or [`strokePaint`](#strokepaint).

<?php foreach([
    'linearGradient',
    'boxGradient',
    'radialGradient',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGContext::' . $funcName); ?>
<?php endforeach; ?>

## Images & SVG

Turn a [`Texture2D`](/API/Texture/Texture2D.html) into a
[`VGImage`](/API/VectorGraphics/VGImage.html), or draw a parsed
[`SVGImage`](/API/VectorGraphics/SVGImage.html) straight into the frame.

<?php foreach([
    'imageFromTexture',
    'imageFromHandle',
    'imageSize',
    'deleteImage',
    'drawSVG',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGContext::' . $funcName); ?>
<?php endforeach; ?>

## Transforms

Transforms are applied on top of each other and stored in the render state, so they respect
[`save`](#save) / [`restore`](#restore).

<?php foreach([
    'resetTransform',
    'transform',
    'translate',
    'rotate',
    'skewX',
    'skewY',
    'scale',
    'currentTransform',
    'transformPoint',
    'transformVec2',
    'transformPointCurrent',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGContext::' . $funcName); ?>
<?php endforeach; ?>

## Scissoring

Limit drawing to a rectangular region. Like transforms, scissors are part of the render state.

<?php foreach([
    'scissor',
    'intersectScissor',
    'resetScissor',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGContext::' . $funcName); ?>
<?php endforeach; ?>

## Building Paths

Open a new path with [`beginPath`](#beginpath), then describe it with these commands before you
[`fill`](#fill) or [`stroke`](#stroke) it.

<?php foreach([
    'beginPath',
    'moveTo',
    'lineTo',
    'bezierTo',
    'quadTo',
    'arcTo',
    'closePath',
    'pathWinding',
    'arc',
    'rect',
    'roundedRect',
    'roundedRectVarying',
    'ellipse',
    'circle',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGContext::' . $funcName); ?>
<?php endforeach; ?>

## Rendering Paths

<?php foreach([
    'fill',
    'fillEvenOdd',
    'stroke',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGContext::' . $funcName); ?>
<?php endforeach; ?>

## Clipping

<?php foreach([
    'clip',
    'resetClip',
    'saveClip',
    'restoreClip',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGContext::' . $funcName); ?>
<?php endforeach; ?>

## Fonts & Text

Load a font once with [`createFont`](#createfont), then set the size and alignment
(using the [`VGAlign`](/API/VectorGraphics/VGAlign.html) constants) before drawing with
[`text`](#text) or [`textBox`](#textbox).

<?php foreach([
    'createFont',
    'createFontAtIndex',
    'findFont',
    'addFallbackFontId',
    'addFallbackFont',
    'resetFallbackFontsId',
    'resetFallbackFonts',
    'fontSize',
    'fontBlur',
    'textLetterSpacing',
    'textLineHeight',
    'textAlign',
    'fontFaceId',
    'fontFace',
    'text',
    'textBox',
    'textBounds',
    'textBoxBounds',
    'textMetrics',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\VectorGraphics\\VGContext::' . $funcName); ?>
<?php endforeach; ?>
