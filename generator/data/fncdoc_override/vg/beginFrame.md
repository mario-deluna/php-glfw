Begins drawing a new frame.

Example:

```php
$vg->beginFrame($windowWidth, $windowHeight, $devicePixelRatio);
// draw commands here
$vg->endFrame();
```

---

$windowWidth The width of the window in pixels.

$windowHeight The height of the window in pixels.

$devicePixelRatio The device pixel ratio.

@return void