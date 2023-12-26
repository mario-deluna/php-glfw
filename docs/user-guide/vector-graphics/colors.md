# Colors

The vector graphics API of PHP-GLFW comes with a set of functions around colors.

You can construct a color as follows:

```php
$color = new VGColor(0.5, 0.5, 0.5, 1.0); // r, g, b, a
```

**Colors are immutable**, so you can't change the values of a color after it has been constructed.

## Color Constants

PHP-GLFW provides a set of color constants.

<figure markdown>
![PHP VectorGraphics Color Constants](./../../docs-assets/php-glfw/user_guide/vg/colors/color_contants.png){ width="100%" }
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