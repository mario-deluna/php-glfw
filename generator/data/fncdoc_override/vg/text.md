Draws text at the specified position.

Example:

```php
$vg->fontSize(18.0);
$advance = $vg->text(100, 100, "Hello, World!");
```

---

$x The x-coordinate of the text position.

$y The y-coordinate of the text position.

$string The text string to draw.

@return float The horizontal advance of the text.