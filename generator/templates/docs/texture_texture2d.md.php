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

<?php foreach([
    'fromDisk', 
    'width',
    'height',
    'channels',
    'buffer',
    'writeJPG',
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\Texture\\Texture2D::' . $funcName); ?> 
<?php endforeach; ?>


