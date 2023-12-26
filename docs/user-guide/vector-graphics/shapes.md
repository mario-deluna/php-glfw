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