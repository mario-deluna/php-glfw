# Plotting primes

Prime numbers are a fascinating! This example will plot the prime numbers in a grid.

<figure markdown>
![Plotting primes Example (PHP-GLFW VG)](./../../docs-assets/php-glfw/examples/vg/fun_primes_1_full.png){ width="600" }
</figure>

<div style="text-align: center;" markdown>
[Check out the Code](https://github.com/mario-deluna/php-glfw/blob/master/examples/vg/fun_primes_1_full.php){ .md-button .md-button--primary }
</div>

Run this example:

```
php examples/vg/fun_primes_1_full.php
```

Controls:

 - Space: Toggle the plotting process on or off.
 - R: Reset the plotting to its initial state, including the prime number sequence, view width, view height, zoom level, and offsets.
 - Q / E: Decrease / Increase the view width. This will rebuild the framebuffer and resume plotting.
 - A / D: Decrease / Increase the view height. This will rebuild the framebuffer and resume plotting.
 - Scroll: Zoom in or out on the plot. Zooming is centered around the current view.
 - Left Mouse Button (Drag): Click and drag to move the plot offset, allowing you to pan around the plotted area.

