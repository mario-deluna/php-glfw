# Text & Fonts

Rendering **text** is a fundamental aspect of many graphics applications, from displaying user interface elements to showing in-game information. However, implementing custom text rendering can be complex and time-consuming, especially when dealing with various font styles and sizes. PHP-GLFW's Vector Graphics API allows you the use of **TrueType Font (TTF)** files.

<figure markdown>
![Example of text rendering using PHP-GLFW Vector Graphics API](./../../docs-assets/php-glfw/user_guide/vg/text/intro.png){ width="100%" }
  <figcaption>Run this <code>php examples/vg/text_intro.php</code></figcaption>
</figure>

## Loading Fonts

First you need to load a font file. You can do this by calling the `createFont()` method on the `VectorGraphics` context object. 

 * The first parameter is the name of the font, which you can use to **reference the font later**. 
 * The second parameter is the path to the font file.

```php
$fontHandle = $vg->createFont('myfont', __DIR__ . '/path/to/my/Font.ttf');
```

The returned integer is the **font handle**. The function will return `-1` if the font could not be loaded.

!!! note
    `0` is a valid handle, so you should check for `-1` specifically.

If your font file contains multiple fonts faces, you can specify which one to load by passing the font face index.

```php
$fontHandle = $vg->createFontAtIndex('myfont', __DIR__ . '/path/to/my/Font.ttf', 0);
```

## Rendering Text

With the font loaded, you can now set it as the current font.

```php
$vg->fontFaceId($fontHandle);
```

Now you to render text:

```php
$vg->beginPath();
$vg->fontSize(20);
$vg->fillColor(VGColor::green());

// text(x, y, string)
$vg->text(50, 50, 'Hello World!');
```

<figure markdown>
![Example of green text rendering using PHP-GLFW Vector Graphics API](./../../docs-assets/php-glfw/user_guide/vg/text/greentext.png){ width="100%" }
</figure>

You do not have to set the font size every time you render text. The Vector Graphics API behaves like a state machine, so the font size will be remembered until you change it again.

## Text Alignment

You can change the text alignment by calling the `textAlign()` method. 

<figure markdown>
![Animated demonstration of text alignment options in PHP-GLFW Vector Graphics API](./../../docs-assets/php-glfw/user_guide/vg/text/text_align.gif){ width="100%" }
  <figcaption>Run this <code>php examples/vg/text_alignment.php</code></figcaption>
</figure>

* Horizontal alignment, which can be one of the following constants:
    * `VGAlign::LEFT`
    * `VGAlign::CENTER`
    * `VGAlign::RIGHT`

* Vertical alignment, which can be one of the following constants:
    * `VGAlign::TOP`
    * `VGAlign::MIDDLE`
    * `VGAlign::BOTTOM`
    * `VGAlign::BASELINE`
    

```php
$vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);
```

## Text Boxes

You can render text inside a box by calling the `textBox()` method. This method will automatically wrap the text to fit inside of a given width.

<figure markdown>
![Example of text box rendering using PHP-GLFW Vector Graphics API](./../../docs-assets/php-glfw/user_guide/vg/text/text_box.gif){ width="100%" }
  <figcaption>Run this <code>php examples/vg/text_boxes.php</code></figcaption>
</figure>

The `textBox()` method works very similar to the `text()` method, except it takes an additional parameter for the width of the box.

```php
// textBox(x, y, width, string)
$vg->textBox(50, 50, 200, 'Hello World!');
```

## Text Metrics

When working with text, you will pretty quickly end up in a situation where you need to know the size of the text you are rendering.

### X Advance

<figure markdown>
![Example of text X advance feature in PHP-GLFW Vector Graphics API](./../../docs-assets/php-glfw/user_guide/vg/text/text_x_advnace.png){ width="100%" }
  <figcaption>Run this <code>php examples/vg/text_color_words.php</code></figcaption>
</figure>

For exmaple, lets say we want to render a sentence where each word is a different color. The `text` function will actually return the **x position + width of the text** it rendered. So we can use this to render the next word at the correct position.

```php
$x = 50;
foreach(['Hey ', 'How ', 'Are ', 'You? '] as $word) {
    $vg->fillColor(VGColor::random());
    $x = $vg->text($x, 50, $word); 
}
```