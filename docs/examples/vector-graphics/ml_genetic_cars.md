# Genetic Car Pathfinding

Genetic algorithms are aweomse, to be fair they are quite close to just brute forcing a solution
but they work and most importantly they are fun to watch. Also they are easy to understand and
implement.

<figure markdown>
![Genetic Car Pathfinding Example (PHP-GLFW VG)](./../../docs-assets/php-glfw/examples/vg/ml_genetic_cars.png){ width="600" }
</figure>

<div style="text-align: center;" markdown>
[Check out the Code](https://github.com/mario-deluna/php-glfw/blob/master/examples/vg/ml_genetic_cars.php){ .md-button .md-button--primary }
</div>

Run this example:

```
php examples/vg/ml_genetic_cars.php
```

!!! Note
         It would be an easy fix, but im lazy. Sometimes a obstacle will spawn where the cars spawn and they will die instantly. 
         Just restart the simulation if that happens.

Controls:

- Space: Toggle VSync on or off. The simulation will just run as fast as possible when VSync is off.
- D: Toggle display labels on or off. Labels provide additional information about the cars in the simulation.
- B: Toggle rendering mode between all cars and only the best-performing car.
- P: Dump the instructions of the best-performing car. This outputs the specific instructions that guide the car's behavior.

