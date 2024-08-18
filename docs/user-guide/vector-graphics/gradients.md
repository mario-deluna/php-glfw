# Color Gradients

Gradients allow you to fill shapes with colors that smoothly transition from one to another. You can use gradients to paint any path (unfortunately, text is not yet supported), and we support two types: linear and radial.

One important thing to note: when you use gradients in PHP-GLFW's Vector Graphics API, the position and size of your shape don't change the gradient itself. Instead, they affect how the gradient maps onto your shape. It's a bit like stretching out a large sheet of gift wrap and then using your shape to cut out a piece of it.

Images follow a similar concept; check out [Images & Graphics](./images.md).

## Linear Gradients

A linear gradient requires just two points to work: where it starts and where it ends.

<figure markdown>
  <video controls="true" allowfullscreen="true" poster="./../../docs-assets/php-glfw/user_guide/vg/gradients/linear_ex.png" style="width: 100%;">
    <source src="./../../docs-assets/php-glfw/user_guide/vg/gradients/gradient.mp4" type="video/mp4">
  </video>
  <figcaption>Run this <code>php examples/vg/gradient_linear.php</code></figcaption>
</figure>

Gradients, just like images/textures, are applied using a `VGPaint` object. 

To create a linear paint:

```php
$x1 = 50;    
$y1 = 150;
$x2 = 350;
$y2 = 450;
$color1 = new VGColor(0.051, 0.682, 0.914, 1.0);
$color2 = new VGColor(0.169, 0.961, 0.596, 1.0);

$paint = $vg->linearGradient($x1, $y1, $x2, $y2, $color1, $color2);
```

This paint can then be applied to all kinds of shapes.

### Rectangles


<figure markdown>
![PHP-GLFW VectorGraphics Gradient on Rectangle](./../../docs-assets/php-glfw/user_guide/vg/gradients/gradient_rect.png){ width="100%" }
</figure>


```php
$vg->beginPath();
$vg->fillPaint($paint);
$vg->rect(50, 150, 300, 300);
$vg->fill();
```

### Circles


<figure markdown>
![PHP-GLFW VectorGraphics Gradient on Circle](./../../docs-assets/php-glfw/user_guide/vg/gradients/gradient_circle.png){ width="100%" }
</figure>

```php
$vg->beginPath();
$vg->fillPaint($paint);
$vg->circle(200, 300, 150);
$vg->fill();
```

Rember the Vector Graphics API is a state machine, so you can reuse the paint object for multiple shapes.


<figure markdown>
![PHP-GLFW VectorGraphics Gradient on Wave](./../../docs-assets/php-glfw/user_guide/vg/gradients/gradient_wave.gif)
  <figcaption>Run this <code>php examples/vg/gradient_wave.php</code></figcaption>
</figure>

```php  
$waveY = ExampleHelper::WIN_HEIGHT / 2;
$dotSize = 10;
$dotDistance = 20;
$waveLength = 0.1;

$vg->fillPaint($paint);

for($x = 0; $x < ExampleHelper::WIN_WIDTH; $x += $dotDistance) {
    $value = sin($x * $waveLength / 20 + glfwGetTime());
    $vg->beginPath();
    $vg->circle($x, $waveY + $value * 100, $dotSize);
    $vg->fill();
}
```

## Radial Gradients

A radial gradient is created by defining a central point and a radius, resulting in a smooth transition of colors that radiates outward in a circular pattern from the center to the outer edge.

<figure markdown>
![PHP-GLFW VectorGraphics Gradient on Wave](./../../docs-assets/php-glfw/user_guide/vg/gradients/gradient_radial.png)
  <figcaption>Run this <code>php examples/vg/gradient_radial.php</code></figcaption>
</figure>

to create a radial paint:

```php
$centerX = 300;
$centerY = 300;
$innerRadius = 0;
$outerRadius = 150;
$color1 = new VGColor(0.051, 0.682, 0.914, 1.0);
$color2 = new VGColor(0.169, 0.961, 0.596, 1.0);

$paint = $vg->radialGradient($centerX, $centerY, $innerRadius, $outerRadius, $color1, $color2);
```
