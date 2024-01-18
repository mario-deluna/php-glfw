# Images & Graphics

Till now we only have been using solid colors to fill shapes. But you can also use images / bitmaps as a fill pattern.

<figure markdown>
  <video controls="true" allowfullscreen="true" poster="./../../docs-assets/php-glfw/user_guide/vg/images/images_poster.jpg" style="width: 100%;">
    <source src="./../../docs-assets/php-glfw/user_guide/vg/images/images_cmp.mp4" type="video/mp4">
  </video>
</figure>


There are 3 steps required to do this:

 * Loading the image from disk into memory.
 * Uploading the texture to the GPU.
 * Creating a VGPaint from the texture that can be used as a fill pattern.

## Loading Images

The first step is to load the image from disk into memory. This can be done with the [`Texture2D`](../../API/Texture/Texture2D.md) class.

```php
$texture = Texture2D::fromDisk('/path/to/your/image.png', Texture2D::CHANNEL_RGBA, false)
```

In the Vector Graphics API we only support RGBA (4 channel) images. The last parameter is a boolean that indicates if the image should be flipped vertically. This is required because OpenGL and the Vector Graphics API have different coordinate systems.

## Uploading the Texture

The next step is to upload the texture to the GPU. 

```php
$image = $vg->imageFromTexture($texture);
```

Note that there are two optional arguments that can be passed to this method.

 1. **Repeat Mode**: This can be either `VGImage::REPEAT_XY` or `VGImage::REPEAT_X` or `VGImage::REPEAT_Y` or `VGImage::REPEAT_NONE`. This controls how the image is repeated when the shape is larger than the image. The default is `VGImage::REPEAT_NONE`.

    <figure markdown>
    ![PHP VectorGraphics Image Repeating](./../../docs-assets/php-glfw/user_guide/vg/images/image_repeating.png){ width="100%" }
    </figure>

 2. **Filter Mode**: This can be either `VGImage::FILTER_LINEAR` or `VGImage::FILTER_NEAREST`. This controls how the image is filtered when it is scaled. The default is `VGImage::FILTER_LINEAR`.

    <figure markdown>
    <video controls="true" allowfullscreen="true" poster="./../../docs-assets/php-glfw/user_guide/vg/images/image_filtering.png" style="width: 100%;">
        <source src="./../../docs-assets/php-glfw/user_guide/vg/images/image_filtering.mp4" type="video/mp4">
    </video>
    </figure>

So putting a full function call together would look like this:

```php
$image = $vg->imageFromTexture($texture, VGImage::REPEAT_XY, VGImage::FILTER_LINEAR);
```

## Creating a Paint

The last step is to create a paint from the image. The paint is defined in global space and can be used to fill or stroke any shape.

```php
// makePaint(x, y, width, height, angle, alpha)
$imagePaint = $image->makePaint(0, 0, 500, 500);
```

The `makePaint` method takes 6 arguments:

 1. **x**: The x coordinate of the top left corner of the paint.
 2. **y**: The y coordinate of the top left corner of the paint.
 3. **width**: The width of the paint.
 4. **height**: The height of the paint.
 5. **angle**: The angle of the paint in radians. (The rotation is around the top left corner of the paint)
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

The paint is defined in global space. This means that the paint will not be affected by the shape that it is used to fill. This might be a bit counter intuitive at first.

A simple example to visualize this is to create a paint that covers the entire screen and then draw a rectangle in the middle of the screen with the paint.

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

