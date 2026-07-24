# Texture2D

The Texture2D class is part of the PHP-GLFW OpenGL extension. It loads images / textures from common formats like PNG, JPG, GIF, BMP, TGA, HDR etc.
and converts the raw bitmap into a native buffer instance you can upload to the GPU with the [`glTexImage2D`](../../API/OpenGL/glTexImage2D.md) function.

Standard (LDR) images are loaded into a [`GL\Buffer\UByteBuffer`](../../API/Buffer/UByteBuffer.md), while High Dynamic Range (`.hdr`) images are loaded into a [`GL\Buffer\FloatBuffer`](../../API/Buffer/FloatBuffer.md). Use `isHDR()` to tell which one `buffer()` returns.

```php
namespace GL\Texture
{
    class Texture2D {}
}
```

!!! tip "Looking for a walkthrough?"
    This page is the exhaustive class reference. For a guided, example-first introduction (loading from disk, uploading to the GPU, procedural and HDR textures, and writing images back out), see the [Textures user guide](../../user-guide/rendering/texture2d.md).

## Usage

A very basic example of loading a file from disk and printing its metadata. Then creating a GPU texture and uploading the image data to the GPU.

```php
// loading an image from disk (1024x1024)
$textureData = Texture2D::fromDisk(__DIR__ . '/picture.png');

echo $textureData->width(); // prints: 1024
echo $textureData->height(); // prints: 1024
echo $textureData->channels(); // prints: 4

// create & upload the texture on the GPU
glGenTextures(1, $texture);
glBindTexture(GL_TEXTURE_2D, $texture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, $textureData->width(), $textureData->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, $textureData->buffer());
```

Read more about the [`glTexImage2D`](../../API/OpenGL/glTexImage2D.md) function to learn about the arguments.

## Constants

The channel constants describe how many components a pixel has. They are used both as the `$requestedChannelCount` argument of `fromDisk` and the `$channels` argument of `fromBuffer` / `fromBufferHDR`.

| Constant | Value | Meaning |
|----------|-------|---------|
| `Texture2D::CHANNEL_R` | 1 | Single channel (red / grayscale). |
| `Texture2D::CHANNEL_GRAY` | 1 | Alias of `CHANNEL_R`. |
| `Texture2D::CHANNEL_RG` | 2 | Two channels. |
| `Texture2D::CHANNEL_GRAY_ALPHA` | 2 | Alias of `CHANNEL_RG`. |
| `Texture2D::CHANNEL_RGB` | 3 | Three channels (red, green, blue). |
| `Texture2D::CHANNEL_RGBA` | 4 | Four channels, with alpha. |

For `fromDisk`, the special value `0` (the default) keeps the file's native channel count instead of forcing a conversion.

## Methods

### `fromDisk`

Loads a texture / image from a file on disk and returns a Texture2D object.

```php
static function fromDisk(string $path, int $requestedChannelCount = 0, bool $flipVertically = true) : \GL\Texture\Texture2D
```

This method automatically detects HDR files (.hdr) and loads them into a FloatBuffer.
All other supported formats (PNG, JPG, GIF, BMP, TGA, etc.) are loaded into a UByteBuffer.

arguments

:    1. `string` `$path` The path to the image file to load.
    2. `int` `$requestedChannelCount` The number of channels to force. 0 means use the original channel count.
    3. `bool` `$flipVertically` Whether to flip the image vertically on load (default: true).

returns

:    `\GL\Texture\Texture2D` The loaded texture object.

---

### `fromBuffer`

Loads a texture / image from a UByteBuffer and returns a Texture2D object.

```php
static function fromBuffer(int $width, int $height, \GL\Buffer\UByteBuffer $buffer, int $channels = \GL\Texture\Texture2D::CHANNEL_RGBA) : \GL\Texture\Texture2D
```

The buffer is not copied, the Texture2D object will hold a reference to the buffer given.

arguments

:    1. `int` `$width` The width of the image.
    2. `int` `$height` The height of the image.
    3. `\GL\Buffer\UByteBuffer` `$buffer` The buffer containing the image data.
    4. `int` `$channels` The number of channels in the image data.

returns

:    `\GL\Texture\Texture2D` The created texture object.

---

### `fromBufferHDR`

Loads a HDR texture from a FloatBuffer and returns a Texture2D object.

```php
static function fromBufferHDR(int $width, int $height, \GL\Buffer\FloatBuffer $buffer, int $channels = \GL\Texture\Texture2D::CHANNEL_RGBA) : \GL\Texture\Texture2D
```

The buffer is not copied, the Texture2D object will hold a reference to the buffer given.

arguments

:    1. `int` `$width` The width of the image.
    2. `int` `$height` The height of the image.
    3. `\GL\Buffer\FloatBuffer` `$buffer` The buffer containing the HDR image data.
    4. `int` `$channels` The number of channels in the image data.

returns

:    `\GL\Texture\Texture2D` The created HDR texture object.

---

### `width`

Returns the width of the image.

```php
function width() : int
```

returns

:    `int` The width of the image.

---

### `height`

Returns the height of the image.

```php
function height() : int
```

returns

:    `int` The height of the image.

---

### `channels`

Returns the number of channels of the image.

```php
function channels() : int
```

returns

:    `int` The number of channels of the image.

---

### `isHDR`

Returns whether the texture contains HDR (High Dynamic Range) data.

```php
function isHDR() : bool
```

When true, the buffer() method returns a FloatBuffer.
When false, the buffer() method returns a UByteBuffer.

returns

:    `bool` 

---

### `buffer`

Returns a reference to the internal buffer instance of the current texture.

```php
function buffer() : \GL\Buffer\UByteBuffer|\GL\Buffer\FloatBuffer
```

For LDR images, this returns a `UByteBuffer`. For HDR images, this returns a `FloatBuffer`.
Use `isHDR()` to check which type of buffer is returned.

returns

:    `\GL\Buffer\UByteBuffer|\GL\Buffer\FloatBuffer` The loaded image data.

---

### `writeJPG`

Writes the image data to a file on disk. (JPEG)

```php
function writeJPG(string $path, int $quality = 100) : void
```

Note: This method only works with LDR textures. For HDR textures, use writeHDR().

arguments

:    1. `string` `$path` The path to the file to write to.
    2. `int` `$quality` The quality of the image. (0 - 100)

returns

:    `void` 

---

### `writePNG`

Writes the image data to a file on disk. (PNG)

```php
function writePNG(string $path) : void
```

Note: This method only works with LDR textures. For HDR textures, use writeHDR().

arguments

:    1. `string` `$path` The path to the file to write to.

---

### `writeBMP`

Writes the image data to a file on disk. (BMP)

```php
function writeBMP(string $path) : void
```

Note: This method only works with LDR textures. For HDR textures, use writeHDR().

arguments

:    1. `string` `$path` The path to the file to write to.

---

### `writeTGA`

Writes the image data to a file on disk. (TGA)

```php
function writeTGA(string $path) : void
```

Note: This method only works with LDR textures. For HDR textures, use writeHDR().

arguments

:    1. `string` `$path` The path to the file to write to.

---

### `writeHDR`

Writes the HDR image data to a file on disk. (.hdr format)

```php
function writeHDR(string $path) : void
```

Note: This method only works with HDR textures. For LDR textures, use writePNG(), writeJPG(), etc.

arguments

:    1. `string` `$path` The path to the file to write to.

---



