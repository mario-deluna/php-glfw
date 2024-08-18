# Noise Functions

PHP-GFLW comes with a number of basic noise functions. Noise is used in games for many procedural generation tasks, such as generating terrain, textures, clouds, and more. Noise can be looked at as a pseudo-random number generator that generates a smooth, continuous, and random-looking output. 

<figure markdown>
![Noise Demo (PHP-GLFW)](./../../docs-assets/php-glfw/user_guide/noise/noise_demo.png){ width="600" }
</figure>

You can run this demo:

```bash
php examples/vg/noise_explorer.php
```

The following noise functions are available:

## Perlin Noise

![Perlin Noise PHP-GLFW](./../../docs-assets/php-glfw/user_guide/noise/noise_perlin.png)

To fetch a single value of Perlin noise, use the `perlin` function:

```php
$noiseValue = GL\Noise::perlin($x, $y, $z);
```

You can also directly fill a 2D buffer with Perlin noise values, this is basically a 2D texture of noise:

```php
$buffer = new GL\Buffer\FloatBuffer();
GL\Noise::perlinFill2D($buffer, 256, 256, 3.0);
```

These are the arguments respectively:

 * `perlin()`:
   * `$x`, `$y`, `$z`: The coordinates of the noise.
   * `$wrapX`, `$wrapY`, `$wrapZ`: The wrapping of the noise.
   * `$seed`: The seed of the noise.
 * `perlinFill2D()`:
   * `$buffer`: The buffer to fill.
   * `$width`, `$height`: The size of the buffer.
   * `$scale`: The scale of the noise.
   * `$offsetX`, `$offsetY`: The offset of the noise.
   * `$wrapX`, `$wrapY`: The wrapping of the noise.
   * `$seed`: The seed of the noise.

## Ridge Noise

![Ridge Noise PHP-GLFW](./../../docs-assets/php-glfw/user_guide/noise/noise_ridge.png)

Ridge noise is a variant of Perlin noise that generates sharp, jagged ridges instead of smooth gradients. This is often used in terrain generation to create mountainous landscapes or other features with steep changes in height.

To fetch a single value of Ridge noise, use the `ridge` function:

```php
$noiseValue = GL\Noise::ridge($x, $y, $z);
```

You can also directly fill a 2D buffer with Ridge noise values:

```php
$buffer = new GL\Buffer\FloatBuffer();
GL\Noise::ridgeFill2D($buffer, 256, 256, 3.0);
```

These are the arguments respectively:

**`ridge()`**

   1. `$x`, `$y`, `$z`: The coordinates of the noise.
   * `$lacunarity`: The frequency multiplier for each octave (default `2.0`).
   * `$gain`: The amplitude reduction factor for each octave (default `0.5`).
   * `$offset`: The offset applied to the noise (default `1.0`).
   * `$octaves`: The number of octaves to sum (default `6`).


**`ridgeFill2D()`**

   * `$buffer`: The buffer to fill.
   * `$width`, `$height`: The size of the buffer.
   * `$scale`: The scale of the noise.
   * `$offsetX`, `$offsetY`: The offset of the noise.
   * `$lacunarity`: The frequency multiplier for each octave.
   * `$gain`: The amplitude reduction factor for each octave.
   * `$offset`: The offset applied to the noise.
   * `$octaves`: The number of octaves to sum.

## Fractal Brownian Motion (fBm) Noise

![fBm Noise PHP-GLFW](./../../docs-assets/php-glfw/user_guide/noise/noise_fbm.png)

Fractal Brownian Motion (fBm) is a method of combining multiple layers (octaves) of noise at different frequencies and amplitudes to create more complex patterns. This is commonly used in generating natural-looking textures like clouds or landscapes.

To fetch a single value of fBm noise, use the `fbm` function:

```php
$noiseValue = GL\Noise::fbm($x, $y, $z);
```

You can also fill a 2D buffer with fBm noise values:

```php
$buffer = new GL\Buffer\FloatBuffer();
GL\Noise::fbmFill2D($buffer, 256, 256, 3.0);
```

These are the arguments respectively:


**`fbm()`**

   * `$x`, `$y`, `$z`: The coordinates of the noise.
   * `$lacunarity`: The frequency multiplier for each octave (default `2.0`).
   * `$gain`: The amplitude reduction factor for each octave (default `0.5`).
   * `$octaves`: The number of octaves to sum (default `6`).

**`fbmFill2D()`**

   * `$buffer`: The buffer to fill.
   * `$width`, `$height`: The size of the buffer.
   * `$scale`: The scale of the noise.
   * `$offsetX`, `$offsetY`: The offset of the noise.
   * `$lacunarity`: The frequency multiplier for each octave.
   * `$gain`: The amplitude reduction factor for each octave.
   * `$octaves`: The number of octaves to sum.

## Turbulence Noise

![Turbulence Noise PHP-GLFW](./../../docs-assets/php-glfw/user_guide/noise/noise_turbulence.png)

Turbulence noise is similar to fBm but applies an absolute value function to the noise, which results in a more chaotic, turbulent pattern. This type of noise is often used for creating textures like marble or water.

To fetch a single value of Turbulence noise, use the `turbulence` function:

```php
$noiseValue = GL\Noise::turbulence($x, $y, $z);
```

You can also fill a 2D buffer with Turbulence noise values:

```php
$buffer = new GL\Buffer\FloatBuffer();
GL\Noise::turbulenceFill2D($buffer, 256, 256, 3.0);
```

These are the arguments respectively:

**`turbulence()`**

   * `$x`, `$y`, `$z`: The coordinates of the noise.
   * `$lacunarity`: The frequency multiplier for each octave (default `2.0`).
   * `$gain`: The amplitude reduction factor for each octave (default `0.5`).
   * `$octaves`: The number of octaves to sum (default `6`).

**`turbulenceFill2D()`**

   * `$buffer`: The buffer to fill.
   * `$width`, `$height`: The size of the buffer.
   * `$scale`: The scale of the noise.
   * `$offsetX`, `$offsetY`: The offset of the noise.
   * `$lacunarity`: The frequency multiplier for each octave.
   * `$gain`: The amplitude reduction factor for each octave.
   * `$octaves`: The number of octaves to sum.

## Island Noise

![Island Noise PHP-GLFW](./../../docs-assets/php-glfw/user_guide/noise/noise_island.png)

Island noise is a specialized noise function designed to generate island-like shapes in 2D. It can be useful for procedural generation of terrain maps where islands are required.

To generate a 2D buffer filled with Island noise values, use the `islandFill2D` function:

```php
$buffer = new GL\Buffer\FloatBuffer();
GL\Noise::islandFill2D($buffer, 256, 256);
```

These are the arguments respectively:

**`islandFill2D()`**

   * `$buffer`: The buffer to fill.
   * `$width`, `$height`: The size of the buffer.
   * `$islandseed`: The seed for island generation (default `42`).
   * `$scale`: The scale of the noise.
   * `$islandmix`: The amount of island shape influence on the final noise (default `0.7`).
   * `$lacunarity`: The frequency multiplier for each octave.
   * `$gain`: The amplitude reduction factor for each octave.
   * `$octaves`: The number of octaves to sum.