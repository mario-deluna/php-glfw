# Colors

The vector graphics API of PHP-GLFW comes with a set of functions around colors.

You can construct a color as follows:

```php
$color = new VGColor(0.5, 0.5, 0.5, 1.0); // r, g, b, a
```

You can access the color components with using the properties `r`, `g`, `b` and `a`, please not that those values 
are stored internally as 32-bit floats, so they are converted everytime you access them from userland.

```php
echo $color->r; // 0.5
```

## Color Constants

PHP-GLFW provides a set of color constants.

<figure markdown>
![PHP VectorGraphics Color Constants](./../../docs-assets/php-glfw/user_guide/vg/colors/color_contants.png){ width="100%" }
  <figcaption>Run this <code>php examples/vg/color_constants.php</code></figcaption>
</figure>

A color contant can be retrieved with the `VGColor::` prefix. For example, to get the red color constant, use:

```php
$red = VGColor::red();
```

These are the available color constants:


| Colors                | Contrasts                | Random                 |
|-----------------------|--------------------------|------------------------|
| `VGColor::red()`      | `VGColor::gray()`        | `VGColor::random()`    |
| `VGColor::green()`    | `VGColor::darkGray()`    | `VGColor::randomGray()`|
| `VGColor::blue()`     | `VGColor::lightGray()`   |                        |
| `VGColor::yellow()`   | `VGColor::white()`       |                        |
| `VGColor::cyan()`     | `VGColor::black()`       |                        |
| `VGColor::magenta()`  | `VGColor::transparent()` |                        |
| `VGColor::orange()`   |                          |                        |
| `VGColor::pink()`     |                          |                        |
| `VGColor::purple()`   |                          |                        |
| `VGColor::brown()`    |                          |                        |

!!! note
    The `VGColor::random()` and `VGColor::randomGray()` functions return as you might have guessed a random color. 
    This can be useful for debugging purposes, for example when visualizing groups of objects.


## Color Lightness

You can lighten and darken a color with the `lighten()` and `darken()` functions. Both functions take a float value which represents the amount of lightness to add or remove. The value must be between 0 and 1.

Internally the RGB is converted to HSL, the lightness is then modified and the color is converted back to RGB.

<figure markdown>
![PHP VectorGraphics Color Constants](./../../docs-assets/php-glfw/user_guide/vg/colors/color_lightness.png){ width="100%" }
  <figcaption>Run this <code>php examples/vg/color_lightness.php</code></figcaption>
</figure>

```php
// darken
$darkerRed = VGColor::red()->darken(0.3);
// lighten
$ligherRed = VGColor::red()->lighten(0.3);
```

## Color Constrcutors 

There are a few color constructors available:

### From RGB

Constructs a color from RGB values. The values must be between 0 and 1. 

```php
$color = VGColor::rgb(0.5, 0.5, 0.5); // Alpha is set to 1.
$color = VGColor::rgba(0.5, 0.5, 0.5, 0.8);
```

### From HSL

Constructs a color from HSL values. The values must be between 0 and 1.

```php
$color = VGColor::hsl(0.5, 0.5, 0.5); //  Alpha is set to 1.
$color = VGColor::hsla(0.5, 0.5, 0.5, 0.8);
```

### From IRGB

Constructs a color from RGB values. The values must be between 0 and 255.

```php
$white = VGColor::irgb(255, 255, 255); // Alpha is set to 255.
$transparent = VGColor::irgb(255, 255, 255, 50);
```

## Inverting 

You can invert a color with the `invert()` function. This function returns a new color.

```php
$inverted = VGColor::red()->invert();
```

## Conversion between Vectors

You can convert a color to a vector with the `getVec3()` and `getVec4()` functions. You can also construct a color from a vector with the `fromVec3()` and `fromVec4()` functions.

```php
// VGColor(1.0, 0.0, 0.0, 1.0)
$red = VGColor::fromVec3(new Vec3(1.0, 0.0, 0.0));
```

```php
 // Vec3(1.0, 0.0, 0.0)
$vec = VGColor::red()->getVec3();
```

This way you can utilize the vector functions to manipulate colors.

```php
$red = VGColor::red()->getVec3();
$green = VGColor::green()->getVec3();

$mixed = Vec3::mix($red, $green, 0.5);
```