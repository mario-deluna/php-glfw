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
