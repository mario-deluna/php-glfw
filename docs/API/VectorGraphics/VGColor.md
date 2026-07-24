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

### `rgb`

RGB color constructor.

```php
static function rgb(float $r, float $g, float $b) : \GL\VectorGraphics\VGColor
```

All values are in the range [0.0, 1.0], alpha defaults to fully opaque.

arguments

:    1. `float` `$r` Red
    2. `float` `$g` Green
    3. `float` `$b` Blue

returns

:    `\VGColor` The resulting color.

---

### `rgba`

RGBA color constructor.

```php
static function rgba(float $r, float $g, float $b, float $a) : \GL\VectorGraphics\VGColor
```

All values are in the range [0.0, 1.0].

arguments

:    1. `float` `$r` Red
    2. `float` `$g` Green
    3. `float` `$b` Blue
    4. `float` `$a` Alpha

returns

:    `\VGColor` The resulting color.

---

### `irgb`

RGB color constructor from integer values
All values are in the range [0, 255]

```php
static function irgb(int $r, int $g, int $b) : \GL\VectorGraphics\VGColor
```

arguments

:    1. `int` `$r` Red
    2. `int` `$g` Green
    3. `int` `$b` Blue

---

### `irgba`

RGBA color constructor from integer values
All values are in the range [0, 255]

```php
static function irgba(int $r, int $g, int $b, int $a) : \GL\VectorGraphics\VGColor
```

arguments

:    1. `int` `$r` Red
    2. `int` `$g` Green
    3. `int` `$b` Blue
    4. `int` `$a` Alpha

---

### `hsl`

HSL color constructor
All values are in the range [0.0, 1.0]

```php
static function hsl(float $h, float $s, float $l) : \GL\VectorGraphics\VGColor
```

arguments

:    1. `float` `$h` Hue
    2. `float` `$s` Saturation
    3. `float` `$l` Lightness

---

### `hsla`

HSL with alpha color constructor
All values are in the range [0.0, 1.0]

```php
static function hsla(float $h, float $s, float $l, float $a) : \GL\VectorGraphics\VGColor
```

arguments

:    1. `float` `$h` Hue
    2. `float` `$s` Saturation
    3. `float` `$l` Lightness

---

### `hex`

Hex color constructor
You can pass a hex string with or without the `#` prefix. (e.g. `#FF0000` or `FF0000`)

```php
static function hex(string $hex) : \GL\VectorGraphics\VGColor
```

Example:
$color = VGColor::hex('#FF0000');
$color = VGColor::hex('FF0000');
$color = VGColor::hex('#000');

arguments

:    1. `string` `$hex` The hex string to convert to a color.

---


## Named Colors

Convenient presets for the common cases. `random` and `randomGray` are handy for quick debugging and
visual tests.

### `red`

The named color red.

```php
static function red() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `green`

The named color green.

```php
static function green() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `blue`

The named color blue.

```php
static function blue() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `white`

The named color white.

```php
static function white() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `black`

The named color black.

```php
static function black() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `transparent`

A fully transparent color.

```php
static function transparent() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `yellow`

The named color yellow.

```php
static function yellow() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `cyan`

The named color cyan.

```php
static function cyan() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `magenta`

The named color magenta.

```php
static function magenta() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `orange`

The named color orange.

```php
static function orange() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `pink`

The named color pink.

```php
static function pink() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `purple`

The named color purple.

```php
static function purple() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `brown`

The named color brown.

```php
static function brown() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `gray`

The named color gray.

```php
static function gray() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `darkGray`

A darker shade of gray.

```php
static function darkGray() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `lightGray`

A lighter shade of gray.

```php
static function lightGray() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `random`

A random opaque color, handy for quick debugging.

```php
static function random() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---

### `randomGray`

A random shade of gray, handy for quick debugging.

```php
static function randomGray() : \GL\VectorGraphics\VGColor
```

 @return VGColor

---


## Conversions & Adjustments

These return new `VGColor` (or vector) values and leave the original untouched.

### `getHSLA`

Returns the color as a Vec4 where each component represents Hue, Saturation, Lightness and Alpha respectively.

```php
function getHSLA() : \GL\Math\Vec4
```

---

### `getHSL`

Returns the color as a Vec3 where each component represents Hue, Saturation and Lightness respectively.

```php
function getHSL() : \GL\Math\Vec3
```

---

### `getVec4`

Returns the color as a Vec4 where each component represents Red, Green, Blue and Alpha respectively.

```php
function getVec4() : \GL\Math\Vec4
```

---

### `getVec3`

Returns the color as a Vec3 where each component represents Red, Green and Blue respectively.

```php
function getVec3() : \GL\Math\Vec3
```

---

### `darken`

Darkens the color by the specified amount.

```php
function darken(float $amount) : \GL\VectorGraphics\VGColor
```

arguments

:    1. `float` `$amount` The amount to darken the color by.

returns

:    `\VGColor` The darkened color.

---

### `lighten`

Lightens the color by the specified amount.

```php
function lighten(float $amount) : \GL\VectorGraphics\VGColor
```

arguments

:    1. `float` `$amount` The amount to lighten the color by.

returns

:    `\VGColor` The lightened color.

---

### `invert`

Inverts the color.

```php
function invert() : \GL\VectorGraphics\VGColor
```

returns

:    `\VGColor` The inverted color.

---

### `withAlpha`

Returns a new color with modified alpha.

```php
function withAlpha(float $alpha) : \GL\VectorGraphics\VGColor
```

arguments

:    1. `float` `$alpha` The new alpha value (0.0 to 1.0).

returns

:    `\VGColor` A new color with the specified alpha.

---

### `copy`

Returns a copy of the color object.

```php
function copy() : \GL\VectorGraphics\VGColor
```

returns

:    `\VGColor` A copy of this color.

---

### `contrast`

Returns either black or white depending on what provides better contrast for this color.

```php
function contrast() : \GL\VectorGraphics\VGColor
```

Uses perceived luminance to determine which color (black or white) would be more readable
when displayed on top of this color.

returns

:    `\VGColor` Either black or white color for optimal contrast.

---

