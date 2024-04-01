# Color Gradients

Gradients allow you to fill shapes with colors that smoothly transition from one to another. You can use gradients to paint any path (text is unfortunatly not yet supported), and we support two types: linear and radial.

Something important to note: when you use gradients in PHP-GLFW's Vector Graphics API, the position and size of your shape don't change the gradient itself. Instead, they affect how the gradient maps onto your shape. It's a bit like stretching out a large foil of gift wrap and then using your shape to cut out a piece of it.

Images follow a similar concept; check out [Images & Graphics](./images.md).

## Linear Gradients

A linear gradient requires just two points to work: where it starts and where it ends.

<figure markdown>
  <video controls="true" allowfullscreen="true" poster="./../../docs-assets/php-glfw/user_guide/vg/gradients/linear_ex.png" style="width: 100%;">
    <source src="./../../docs-assets/php-glfw/user_guide/vg/gradients/gradient.mp4" type="video/mp4">
  </video>
  <figcaption>Run this <code>php examples/vg/gradient_linear.php</code></figcaption>
</figure>

Gradients just like images/textures are applied using a `VGPaint` object. 

To create such a linear paint:

```php
$x1 = 50;    
$y2 = 150;
$x2 = 350;
$y2 = 450;
$color1 = new VGColor(0.051, 0.682, 0.914, 1.0);
$color2 = new VGColor(0.169, 0.961, 0.596, 1.0);

$paint = $vg->linearGradient($x1, $y1, $x2, $y2, $color1, $color2);
```

This paint can then be applied to all kinds of shapes.

### Rectangles

```php
$vg->beginPath();
$vg->fillPaint($paint);
$vg->rect(50, 150, 300, 300);
$vg->fill();
```

<figure markdown>
![PHP-GLFW VectorGraphics Gradient on Rectangle](./../../docs-assets/php-glfw/user_guide/vg/gradients/gradient_rect.png){ width="100%" }
</figure>

### Circles

```php
$vg->beginPath();
$vg->fillPaint($paint);
$vg->circle(200, 300, 150);
$vg->fill();
```

<figure markdown>
![PHP-GLFW VectorGraphics Gradient on Circle](./../../docs-assets/php-glfw/user_guide/vg/gradients/gradient_circle.png){ width="100%" }
</figure>
