Calculates the bounding box of the specified text and returns the horizontal advance.

Example: 

```php
$vg->fontSize(18.0);
$bounds = new Vec4();
$advance = $vg->textBounds(100, 100, "Hello, World!", $bounds);
echo "Text bounds: " . $bounds . "\n";
echo "Text advance: " . $advance . "\n";
```

---

$x The x of the text position.

$y The y of the text position.

$string The text string to measure.

$bounds Vec4 object in which the calculated bounds are stored [xmin, ymin, xmax, ymax].

@return The horizontal advance of the text.