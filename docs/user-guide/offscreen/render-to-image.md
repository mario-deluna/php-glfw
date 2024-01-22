# Rendering to an Image

You can render your OpenGL scene or parts of it to an image using PHP-GLFW.

The [`Texture2D`](./../../API/Texture/Texture2D.md) class can be constructed using a buffer of pixel data. 

```php
// create a buffer to store the pixel data in
// we currently only support extracting unsigned byte data from the framebuffer
$pixelBuffer = new \GL\Buffer\UByteBuffer();

// read the pixels from the current framebuffer into the buffer object `$pixelBuffer`
// glReadPixels(x, y, width, height, format, type, buffer)
glReadPixels(0, 0, 800, 800, GL_RGB, GL_UNSIGNED_BYTE, $pixelBuffer);

// creates a texture object with the pixel data and writes it to a file in JPEG format
Texture2D::fromBuffer(800, 800, $pixelBuffer, Texture2D::CHANNEL_RGB)
    ->writeJPG('frame.jpg');
```

## High DPI Screens

If you are using a high DPI screen, your framebuffer might be larger than the window size. 

This is why you should fetch the framebuffer size first if you plan to export the entire screen.

```php
// get the framebuffer size
glfwGetFramebufferSize($window, $width, $height);

// rest just as before..
glReadPixels(0, 0, $width, $height, GL_RGB, GL_UNSIGNED_BYTE, $pixelBuffer);
Texture2D::fromBuffer($width, $height, $pixelBuffer, Texture2D::CHANNEL_RGB)
    ->writeJPG('frame.jpg');
```

!!! note
    This also depends on other settings like, `GLFW_SCALE_TO_MONITOR` and `GLFW_COCOA_RETINA_FRAMEBUFFER`.


You have multiple formats to choose from when writing the image to disk:

- `writePNG`: PNG format with lossless compression, preserving all image data and supporting transparency. 

- `writeJPG` JPGs are lossy compressed images, by expirience they are best for images with high entropy, like noisy scenes or photographs.

- `writeBMP`: BMP format stores images without compression, ensuring complete fidelity of the original data.

- `writeTGA`: TGA, super simple to write and read, but not very space efficient.

<!-- ## Render to Video (mp4 with ffmpeg)

We can use the same technique to render to a video file, by using the [`ffmpeg`](https://ffmpeg.org/) command line tool.

The simplest way to do this is to write frame by frame to stdout and pipe it to ffmpeg.

```php
// get the framebuffer size
glfwGetFramebufferSize($window, $width, $height);

// rest just as before..
$pixelBuffer = new \GL\Buffer\UByteBuffer();
glReadPixels(0, 0, $width, $height, GL_RGB, GL_UNSIGNED_BYTE, $pixelBuffer);
Texture2D::fromBuffer($width, $height, $pixelBuffer, Texture2D::CHANNEL_RGB)
    ->writeJPG('frame.jpg');
``` -->