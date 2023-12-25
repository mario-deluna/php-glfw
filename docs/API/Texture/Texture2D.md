# Texture2D 

The Texture2D class is part of the PHP-GLFW OpenGL extension. It loads images / textures from common formats like PNG, JPG, GIF, BMP, TGA etc.
and converts the raw bitmap to a `GL\UByteBuffer` instance. The `GL\UByteBuffer` instance can be uploaded to the GPU using the [`glTexImage2D`](/API/OpenGL/glTexImage2D.html) function.

```php 
namespace GL\Texture
{
    class Texture2D {}
}
```

## Usage 

A very basic example of loading a file from disk and printing its metadata. Then creating A GPU texture and uploading the image data to the GPU.

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

Read more about the [`glTexImage2D`](/API/OpenGL/glTexImage2D.html) function to learn about the arguments.

## Methods

### `fromDisk`

Loads a texture / image from a file on disk and returns a Texture2D object.

```php
static function fromDisk(string $path) : \GL\Texture\Texture2D
```

arguments

:    1. `string` `$file` The path to the image file to load.

returns

:    `\GL\Texture\Texture2D` The loaded texture object.

---
     
### `fromBuffer`

Loads a texture / image from a buffer and returns a Texture2D object.

```php
static function fromBuffer(int $width, int $height, \GL\Buffer\UByteBuffer $buffer, int $channels = \GL\Texture\Texture2D::CHANNEL_RGBA) : \GL\Texture\Texture2D
```

The buffer is not copied, the Texture2D object will hold a reference to the buffer given.

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
     
### `buffer`

Returns a reference to the internal `UByteBuffer` instance of the current texture.

```php
function buffer() : \GL\Buffer\UByteBuffer
```

returns

:    `\GL\UByteBuffer` The loaded image data.

---
     
### `writeJPG`

Writes the image data to a file on disk. (JPEG)

```php
function writeJPG(string $path, int $quality = 100) : void
```

arguments

:    1. `string` `$file` The path to the file to write to.
    2. `int` `$quality` The quality of the image. (0 - 100)

returns

:    `void` 

---
     
### `writePNG`

Writes the image data to a file on disk. (PNG)

```php
function writePNG(string $path) : void
```

arguments

:    1. `string` `$file` The path to the file to write to.

---
     
### `writeBMP`

Writes the image data to a file on disk. (BMP)

```php
function writeBMP(string $path) : void
```

arguments

:    1. `string` `$file` The path to the file to write to.

---
     
### `writeTGA`

Writes the image data to a file on disk. (TGA)

```php
function writeTGA(string $path) : void
```

arguments

:    1. `string` `$file` The path to the file to write to.

---
     


