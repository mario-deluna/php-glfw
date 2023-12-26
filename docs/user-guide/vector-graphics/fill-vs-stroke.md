# Fill vs Stroke

There are two ways to draw a shape to the screen. We can either fill the shape or stroke the shape. Filling a shape means that the shape will be filled with the current fill color. Stroking a shape means that the shape will be drawn as a line with the current stroke color.

Creating the same rectangle as above, but this time stroking it instead of filling it, will look like this:

<figure markdown>
  ![PHP VectorGraphics Rectangle Stroke Drawing](./../../docs-assets/php-glfw/user_guide/vg/context_creation/rect_stroke.png){ width="700" }
</figure>

```php
$vg->beginPath();
$vg->rect(10, 10, 100, 100);
$vg->strokeColor(VGColor::red());
$vg->stroke();
```

