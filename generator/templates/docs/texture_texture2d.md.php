# Texture2D

The Texture2D class is part of the PHP-GLFW OpenGL extension. It loads images / textures from common formats like PNG, JPG, GIF, BMP, TGA, HDR etc.
and converts the raw bitmap into a native buffer instance you can upload to the GPU with the [`glTexImage2D`](/API/OpenGL/glTexImage2D.html) function.

Standard (LDR) images are loaded into a [`GL\Buffer\UByteBuffer`](/API/Buffer/UByteBuffer.html), while High Dynamic Range (`.hdr`) images are loaded into a [`GL\Buffer\FloatBuffer`](/API/Buffer/FloatBuffer.html). Use `isHDR()` to tell which one `buffer()` returns.

```php
namespace GL\Texture
{
    class Texture2D {}
}
```

!!! tip "Looking for a walkthrough?"
    This page is the exhaustive class reference. For a guided, example-first introduction (loading from disk, uploading to the GPU, procedural and HDR textures, and writing images back out), see the [Textures user guide](/user-guide/rendering/texture2d.html).

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

Read more about the [`glTexImage2D`](/API/OpenGL/glTexImage2D.html) function to learn about the arguments.

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

<?php foreach([
    'fromDisk',
    'fromBuffer',
    'fromBufferHDR',
    'width',
    'height',
    'channels',
    'isHDR',
    'buffer',
    'writeJPG',
    'writePNG',
    'writeBMP',
    'writeTGA',
    'writeHDR',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\Texture\\Texture2D::' . $funcName); ?>
<?php endforeach; ?>


