# Images & Graphics

Until now, we have only been using solid colors to fill shapes. However, you can also use images or bitmaps as a fill pattern.

<figure markdown>
  <video controls="true" allowfullscreen="true" poster="./../../docs-assets/php-glfw/user_guide/vg/images/images_poster.jpg" style="width: 100%;">
    <source src="./../../docs-assets/php-glfw/user_guide/vg/images/images_cmp.mp4" type="video/mp4">
  </video>
</figure>

There are three steps required to achieve this:

1. Loading the image from disk into memory.
2. Uploading the texture to the GPU.
3. Creating a `VGPaint` from the texture that can be used as a fill pattern.

## Loading Images

The first step is to load the image from disk into memory. This can be done with the [`Texture2D`](../../API/Texture/Texture2D.md) class.

```php
$texture = Texture2D::fromDisk('/path/to/your/image.png', Texture2D::CHANNEL_RGBA, false);
```

In the Vector Graphics API, only RGBA (4-channel) images are supported. The last parameter is a boolean that indicates whether the image should be flipped vertically. This is required because OpenGL and the Vector Graphics API use different coordinate systems.

## Uploading the Texture

The next step is to upload the texture to the GPU. 

```php
$image = $vg->imageFromTexture($texture);
```

Note that there are two optional arguments that can be passed to this method:

1. **Repeat Mode**: This can be either `VGImage::REPEAT_XY`, `VGImage::REPEAT_X`, `VGImage::REPEAT_Y`, or `VGImage::REPEAT_NONE`. This controls how the image is repeated when the shape is larger than the image. The default is `VGImage::REPEAT_NONE`.

    <figure markdown>
    ![PHP VectorGraphics Image Repeating](./../../docs-assets/php-glfw/user_guide/vg/images/image_repeating.png){ width="100%" }
    </figure>

2. **Filter Mode**: This can be either `VGImage::FILTER_LINEAR` or `VGImage::FILTER_NEAREST`. This controls how the image is filtered when it is scaled. The default is `VGImage::FILTER_LINEAR`.

    <figure markdown>
    <video controls="true" allowfullscreen="true" poster="./../../docs-assets/php-glfw/user_guide/vg/images/image_filtering.png" style="width: 100%;">
        <source src="./../../docs-assets/php-glfw/user_guide/vg/images/image_filtering.mp4" type="video/mp4">
    </video>
    </figure>

A complete function call would look like this:

```php
$image = $vg->imageFromTexture($texture, VGImage::REPEAT_XY, VGImage::FILTER_LINEAR);
```

## Creating a Paint

The final step is to create a paint from the image. The paint is defined in global space and can be used to fill or stroke any shape.

```php
// makePaint(x, y, width, height, angle, alpha)
$imagePaint = $image->makePaint(0, 0, 500, 500);
```

The `makePaint` method takes six arguments:

1. **x**: The x-coordinate of the top left corner of the paint.
2. **y**: The y-coordinate of the top left corner of the paint.
3. **width**: The width of the paint.
4. **height**: The height of the paint.
5. **angle**: The angle of the paint in radians. (The rotation is around the top left corner of the paint.)
6. **alpha**: The alpha value of the paint.

## Using the Paint

The paint can now be used to fill or stroke any shape.

```php
$vg->beginPath();
$vg->rect(0, 0, 500, 500);
$vg->fillPaint($imagePaint);
$vg->fill();
```

<figure markdown>
![PHP VectorGraphics Image Fill](./../../docs-assets/php-glfw/user_guide/vg/images/image_rect.png){ width="100%" }
</figure>

### In Global Space?

The paint is defined in global space, meaning it will **NOT** be affected by the shape it is used to fill. This might seem counterintuitive at first.

A simple example to visualize this is to create a paint that covers the entire screen and then draw a rectangle in the middle of the screen with that paint.

<figure markdown>
![PHP VectorGraphics Image Fill](./../../docs-assets/php-glfw/user_guide/vg/images/images_globalspace.gif){ width="70%" }
</figure>

```php
$paint = $myImage->makePaint(0, 0, 512, 512);
$vg->beginPath();
$vg->rect(100, 100, 200, 200);
$vg->fillPaint($paint);
$vg->fill();
```

### Scaling a Paint

If you are now confused about how to set the size of an image, this is controlled by the parameters passed to `makePaint`. The `width` and `height` parameters define the size of the paint in global space.

![PHP-GLFW VectorGraphics Image Scaling](./../../docs-assets/php-glfw/user_guide/vg/images/image_scaling_vg_phpglfw.png)

A quick example:

```php
$vg->beginPath();
$vg->rect(100, 100, 200, 200);
$paint = $myImage->makePaint(100, 100, 200, 200);
$vg->fillPaint($paint);
$vg->fill();

// slightly smaller
$vg->beginPath();
$vg->rect(350, 100, 100, 100);
$paint = $myImage->makePaint(350, 100, 100, 100);
$vg->fillPaint($paint);
$vg->fill();

// even smaller
$vg->beginPath();
$vg->rect(500, 100, 50, 50);
$paint = $myImage->makePaint(500, 100, 50, 50);
$vg->fillPaint($paint);
$vg->fill();
```

## Preexisting Images (Context Sharing)

If you have a texture that is already uploaded to the GPU, you can create an image from it that can be used as a paint.

```php
$glTexture; // the GL texture handle

$vgImage = $vg->imageFromHandle($glTexture, $textureWidth, $textureHeight);
$paint = $vgImage->makePaint(0, 0, $textureWidth, $textureHeight);
```