# Colors

The vector graphics API of PHP-GLFW provides a set of functions for working with colors.

## Color Construction

Colors can be constructed by calling the `VGColor` constructor and passing the desired red, green, blue, and alpha values to the constructor:

```php
$color = new VGColor(0.5, 0.5, 0.5, 1.0); // r, g, b, a
```

You may access the individual color components via the `r`, `g`, `b`, and `a` properties. Note that these values are stored internally as 32-bit floats, so they are converted to userland floats every time they are accessed:

```php
echo $color->r; // 0.5
```

## Color Constants

PHP-GLFW provides a variety of color constants.

<figure markdown>
![PHP VectorGraphics Color Constants](./../../docs-assets/php-glfw/user_guide/vg/colors/color_contants.png){ width="100%" }
  <figcaption>Run this <code>php examples/vg/color_constants.php</code></figcaption>
</figure>

A color constant may be retrieved using the `VGColor::` prefix. For example, to retrieve the red color constant, you would use:

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
    The `VGColor::random()` and `VGColor::randomGray()` functions return, as you might guess, a random color. 
    This can be useful for debugging purposes, such as when visualizing groups of objects.


## Color Lightness

You may lighten and darken a color using the `lighten()` and `darken()` methods. Both methods accept a float value representing the amount of lightness to add or remove, respectively. The value should be between 0 and 1.

Internally, the RGB color is converted to the HSL color space, the lightness is modified, and then the color is converted back to RGB.

<figure markdown>
![Illustration of lightening and darkening colors using PHP-GLFW VectorGraphics API](./../../docs-assets/php-glfw/user_guide/vg/colors/color_lightness.png){ width="100%" }
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

Constructs a color from RGB values. The values should be between 0 and 1. 

```php
$color = VGColor::rgb(0.5, 0.5, 0.5); // Alpha is set to 1.
$color = VGColor::rgba(0.5, 0.5, 0.5, 0.8);
```

### From HSL

Constructs a color from HSL values. The values should be between 0 and 1.

```php
$color = VGColor::hsl(0.5, 0.5, 0.5); //  Alpha is set to 1.
$color = VGColor::hsla(0.5, 0.5, 0.5, 0.8);
```

### From IRGB

Constructs a color from RGB values. The values should be between 0 and 255.

```php
$white = VGColor::irgb(255, 255, 255); // Alpha is set to 255.
$transparent = VGColor::irgb(255, 255, 255, 50);
```

## Inverting 

You may invert a color using the `invert()` method. This method returns a new color.

```php
$inverted = VGColor::red()->invert();
```

## Conversion between Vectors

You may convert a color to a vector using the `getVec3()` and `getVec4()` methods. You may also construct a color from a vector using the `fromVec3()` and `fromVec4()` methods.



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