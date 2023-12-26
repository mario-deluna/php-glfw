# Fill vs Stroke


In a php-glfw vector graphics context, shapes can be rendered on-screen using two methods: fill and stroke.

* **Fill** Filling a shape colors its entire interior area. When you fill a shape, like a circle, the entire circle is covered with the fill color.

* **Stroke** Stroking a shape outlines it without filling the interior. Stroking a circle, for example, results in just the circle's edge being drawn, using the stroke color. 


<figure markdown>
  ![PHP VectorGraphics Rectangle Stroke Drawing](./../../docs-assets/php-glfw/user_guide/vg/fillvsstroke/fill_vs_stroke.png){ width="700" }
</figure>



=== "Stroke"

    ```php
    $vg->beginPath();
    $vg->rect(200, 100, 400, 200);
    $vg->strokeColor(VGColor::red());
    $vg->strokeWidth(20); // note that we additinally set the stroke width
    $vg->stroke();
    ```

=== "Fill"

    ```php
    $vg->beginPath();
    $vg->rect(200, 100, 400, 200);
    $vg->fillColor(VGColor::red());
    $vg->fill();
    ```


## Fill and Stroke Together

These two methods can be used together to create borders and outlines for shapes.

<figure markdown>
  ![PHP VectorGraphics Rectangle Fill and Stroke Drawing](./../../docs-assets/php-glfw/user_guide/vg/fillvsstroke/fill_plus_stroke.png){ width="700" }
</figure>

```php
$vg->beginPath();
$vg->rect(200, 100, 400, 200);
$vg->fillColor(VGColor::orange());
$vg->strokeColor(VGColor::red());
$vg->strokeWidth(20);
$vg->fill();
$vg->stroke();
```

## Stroke Width

The stroke width is the thickness of the stroke. The default stroke width is 1.0. The stroke width is always centered on the path, meaning that half of the stroke width is drawn on the inside of the path, and half on the outside.

<figure markdown>
  ![PHP VectorGraphics Rectangle Stroke Width Drawing](./../../docs-assets/php-glfw/user_guide/vg/fillvsstroke/stroke_width.gif){ width="100%" }
</figure>


## Stroke Inside and Outside

Again, the stroke width is always centered on the path so if you want to draw a stroke that is entirely inside or outside the path, you need to adjust the path itself.

=== "Stroke Inside"

    To draw a stroke that is entirely inside the path, you need to move the path inwards by half the stroke width.

    <figure markdown>
    ![PHP VectorGraphics Rectangle Stroke Inside Drawing](./../../docs-assets/php-glfw/user_guide/vg/fillvsstroke/stroke_inner.gif){ width="100%" }
    </figure>

    ```php
    $rectX = 200;
    $rectY = 100;
    $rectWidth = 400;
    $rectHeight = 200;
    $strokeWidth = 20;

    $vg->beginPath();
    $vg->rect(
        $rectX + $strokeWidth / 2, 
        $rectY + $strokeWidth / 2, 
        $rectWidth - $strokeWidth, 
        $rectHeight - $strokeWidth
    );
    $vg->strokeColor(VGColor::red());
    $vg->strokeWidth($strokeWidth);
    $vg->stroke();
    ```

=== "Stroke Outside"

    To draw a stroke that is entirely outside the path, you need to move the path outwards by half the stroke width.

    <figure markdown>
    ![PHP VectorGraphics Rectangle Stroke Outside Drawing](./../../docs-assets/php-glfw/user_guide/vg/fillvsstroke/stroke_outer.gif){ width="100%" }
    </figure>

    ```php
    $rectX = 200;
    $rectY = 100;
    $rectWidth = 400;
    $rectHeight = 200;
    $strokeWidth = 20;

    $vg->beginPath();
    $vg->rect(
        $rectX - $strokeWidth / 2, 
        $rectY - $strokeWidth / 2, 
        $rectWidth + $strokeWidth, 
        $rectHeight + $strokeWidth
    );
    $vg->strokeColor(VGColor::red());
    $vg->strokeWidth($strokeWidth);
    $vg->stroke();
    ```


