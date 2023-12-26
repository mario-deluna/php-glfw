# Shapes (Circle, Rectangle, Polygon, etc.)

There are a number of basic shapes for which a helper function is provided.

<figure markdown>
![PHP VectorGraphics Shapes](./../../docs-assets/php-glfw/user_guide/vg/shapes/shapes.png){ width="100%" }
<figcaption markdown>
 `rect()`, `roundedRect()`, `ellipse()`, `circle()`, `arc()`
</figcaption>
</figure>


## Rectangles

The `rect()` function draws a rectangle with the top-left corner at `(x, y)` and the specified `width` and `height`.

```php
// rect(x, y, width, height)
$vg->rect(10, 10, 100, 100);
```

<figure markdown>
![PHP VectorGraphics Rectangle Drawing](./../../docs-assets/php-glfw/user_guide/vg/shapes/rect_demo.gif){ width="100%" }
</figure>

## Rounded Rectangles

The `roundedRect()` function draws a rectangle with rounded corners. The `radius` parameter specifies the radius of the corners.

```php
// roundedRect(x, y, width, height, radius)
$vg->roundedRect(10, 10, 100, 100, 10);
```

<figure markdown>
![PHP VectorGraphics Rounded Rectangle Drawing](./../../docs-assets/php-glfw/user_guide/vg/shapes/rounded_rect_demo.gif){ width="100%" }
</figure>

## Circles

The `circle()` function draws a circle with the center at `(x, y)` and the specified `radius`.

```php
// circle(x, y, radius)
$vg->circle(400, 200, 50);
```

<figure markdown>
![PHP VectorGraphics Circle Drawing](./../../docs-assets/php-glfw/user_guide/vg/shapes/circle_demo.gif){ width="100%" }
</figure>

## Ellipses

The `ellipse()` function draws an ellipse with the center at `(x, y)` and the specified `radiusX` and `radiusY`.

```php
// ellipse(x, y, radiusX, radiusY)
$vg->ellipse(400, 200, 50, 100);
```

<figure markdown>
![PHP VectorGraphics Ellipse Drawing](./../../docs-assets/php-glfw/user_guide/vg/shapes/ellipse_demo.gif){ width="100%" }
</figure>

## Arcs

I've honestly only used arcs to draw pie charts, so thats what im going to focus on in this example. 

```php
// arc(cx, cy, radius, startAngle, endAngle, direction)
// CCW = Counter Clockwise
$vg->arc(700, 200, 50, 0, 3.14, VGContext::CCW);
```

Again this can be utilized to draw pies! Here is an example of how to draw a circular progress indicator.

```php
$cx = 400;
$cy = 200;
$radius = 50;
$progress = 0.5; // 50%
$startAngle = -M_PI * 0.5; 
$endAngle = $startAngle + (M_PI * 2 * $progress);

$vg->beginPath();
$vg->moveTo($cx, $cy);
$startX = $cx + $radius * cos($startAngle);
$startY = $cy + $radius * sin($startAngle);
$vg->lineTo($startX, $startY);
$vg->arc($cx, $cy, $radius, $startAngle, $endAngle, VGContext::CW);
$vg->closePath();
$vg->fillColor(VGColor::green());
$vg->fill();
```

<figure markdown>
![PHP VectorGraphics Arc Drawing](./../../docs-assets/php-glfw/user_guide/vg/shapes/arc_progress_pie.gif){ width="100%" }
</figure>

## Polygons

If you want to draw a custom shape you can simply issue a series of `moveTo()` and `lineTo()` commands to draw a polygon.

This will allow you to draw basically any shape you want. Here is an example of how to draw a star.

<figure markdown>
![PHP VectorGraphics Polygon Drawing](./../../docs-assets/php-glfw/user_guide/vg/shapes/poly_custom_star.png){ width="100%" }
</figure>

```php
$vg->beginPath();
$vg->moveTo(400, 100);
$vg->lineTo(450, 200);
$vg->lineTo(550, 200);
$vg->lineTo(475, 250);
$vg->lineTo(500, 350);
$vg->lineTo(400, 300);
$vg->lineTo(300, 350);
$vg->lineTo(325, 250);
$vg->lineTo(250, 200);
$vg->lineTo(350, 200);
$vg->closePath();
$vg->fillColor(VGColor::yellow());
$vg->fill();

// draw some eyes
$vg->beginPath();
$vg->circle(400 - 30, 230, 10);
$vg->circle(400 + 30, 230, 10);
$vg->fillColor(VGColor::black());
$vg->fill();
```