<p align="center">
 <img width="100px" src="https://raw.githubusercontent.com/mario-deluna/php-glfw/v2/docs/logo_phpglfw_s.png">
</p>

# PHP-GLFW

**[Website](https://phpgl.net) • [Getting Started](https://phpgl.net/getting-started/window-creation.html) • [User Guide](https://phpgl.net/user-guide/index.html) • [API Docs](https://phpgl.net/API/Buffer/ByteBuffer.html)**

**A fully-featured OpenGL and GLFW extension for PHP. Batteries included 🔋!**

[![PHPglfw](https://github.com/mario-deluna/php-glfw/actions/workflows/build.yml/badge.svg)](https://github.com/mario-deluna/php-glfw/actions/workflows/build.yml)

PHP-GLFW allows you to create _2D_ and _3D_ real-time applications in _PHP_. Bringing a whole different set of tools into the PHP world to develop graphical applications like _games, scientific simulations, user interfaces_ and co. 

  * [What is this extension? Features 🚀](#what-is-this-extension-features-)
    + [OpenGL](#opengl)
    + [GLFW](#glfw)
    + [PHPGL - Math](#phpgl---math)
    + [PHPGL - Buffers](#phpgl---buffers)
    + [PHPGL - Textures](#phpgl---textures)
    + [How are the bindings achieved?](#how-are-the-bindings-achieved)
  * [Documentation 📚](#documentation-)
    + [Examples](#examples)
  * [Installation](#installation)
    + [MacOS](#macos)
    + [Linux](#linux)
    + [Stubs (IDE Support)](#stubs-ide-support)
  * [Things to know when you start 💡](#things-to-know-when-you-start-)
  * [Credits](#credits)
  * [License](#license)

## What is this extension? Features 🚀

PHP-GLFW aims to be one extension containing all basics you need to start building graphical applications in PHP. That means that PHP-GLFW **does NOT just
provide GLFW library bindings**. Instead, it also **includes OpenGL bindings** and a bunch of classes and helpers pretty much required for building these types of applications.

### OpenGL 

* Full native support of **OpenGL** (4.1+ core), GPU accelerated rendering in PHP.
* Targeting OpenGL 4.1, but it can also be built for newer versions.
* Support for OpenGL extensions (limited).
* Mostly mirroring the C API, adjustments were made where required or otherwise nonsensical.
* We currently support about ~90% of the full standard, check [GLSUPPORT.md](./GLSUPPORT.md)

### GLFW 

This extension comes obviously with bindings for the amazing **[GLFW](https://www.glfw.org)** library. GLFW comes with great features, to name a few:

* Multiplatform Window creation and handling. (MacOS / Window / Linux)
* Support for multiple windows and monitors.
* Real-time user input handling.
  * **Keyboard and Mouse** event handling. 
  * **Joystick** input support.

### PHPGL - Math

PHPGL is what I call the extras in this extension, aka classes and helpers additionally provided that are pretty much a requirement for these kinds of applications. PHP-GLFW comes with a mathematics library written in C, covering the most common operations required for graphical applications. 

 * Supported structs: `Vec2`, `Vec3`, `Vec4`, `Mat4` and `Quat`.
 * Includes most common matrix operations for the use case like: `lookAt`, `perspective`, `inverse`, `rotate` etc..

Having this integrated into the extension comes with a bunch of advantages:

 * It's fast. 
 * low memory footprint.
 * The math structures have overloaded operators, so you can write things like:
   ```php
   $v3 = Vec2(15, -5) + Vec2(42, 7); // returns Vec2(54, 2)
   ```
 * Some OpenGL functions can directly accept the math structs as arguments. 

### PHPGL - Buffers

This extension also contains a collection of buffer objects that internally hold data in native types. 

 * Can handle large arrays of data.
 * Low memory footprint and very fast. 
 * Data is stored internally to be directly uploadable to the GPU.

### PHPGL - Textures

PHP-GLFW supports the loading of images/textures into buffers without requiring an additional extension:

   * can load common image formats as `jpg`, `png`, `tga`, `bmp`, `gif`. _(gd or Imagick is not required)_
   * can write images/textures back to disk.
   * writes data into a `BufferInterface` object giving full access to the bitmap from userland.

### How are the bindings achieved?

Instead of porting function by function manually, PHP-GLFW parses the OpenGL specs to generate most of this C extension. Adjustments are made manually where necessary.

## Documentation 📚

> 1. [Full Documentation](https://phpgl.net) 
> 2. [Getting Started Guide](https://phpgl.net/getting-started/window-creation.html) 
> 3. [User Guide](https://phpgl.net/user-guide/index.html) 
> 4. [API Docs](https://phpgl.net/API/Buffer/ByteBuffer.html) 

### Examples

![glfw-previews](https://user-images.githubusercontent.com/956212/189208007-74064a7b-0e93-4d7f-b53e-e799a0641e54.png)

If you want to check out the code straight away, check out the [examples](./examples#examples) directory.

## Installation 

**Please see the complete detailed installation guide here: [Installation](https://phpgl.net/getting-started/installation/install-linux.html)**

### MacOS 

#### Installer

There is a simple installer script you can use to install php-gflw:

```
php -r "copy('https://raw.githubusercontent.com/mario-deluna/php-glfw/master/install/macos-installer.php', 'phpglfw-installer.php');" && php phpglfw-installer.php
```

Thats it, if you see the text "Installation finished!" you should be ready to go!

#### Manual installation

If you prefer a manual approach, ensure you have installed the `php-dev`, `git` and `cmake` packages. **They are required!**

```bash
git clone https://github.com/mario-deluna/php-glfw
cd php-glfw
sudo phpize && ./configure --enable-glfw
sudo make install
```

make sure to add `glfw.so` in the `php.ini` file:

```ini
extension="glfw.so"
```

### Linux 

`cmake` is required for the installation. You can skip the first step if it's already installed. 
Also, make sure that you install the `php-dev` package for example, `php8.1-dev`.

```
sudo apt install -y cmake git 
git clone https://github.com/mario-deluna/php-glfw
cd php-glfw
sudo phpize && ./configure --enable-glfw
sudo make install
```

make sure to add `glfw.so` in the `php.ini` file:

```ini
extension="glfw.so"
```

### Stubs (IDE Support)

As this is a PHP extension, your editor / IDE does not support auto-completion and doc lookups without some help.
We created a composer package you can include as a dev dependency to have full support:

```
composer require --dev phpgl/ide-stubs
```

## Things to know when you start 💡 

PHP-GLFW tries to keep the core OpenGL / GLFW API as close to the original as possible and only modifies the API when necessary. This results in some functions being quite wired from a PHP point of view. Naming scheme:

| prefix | module | desc |
|--------|----------|-------------------------------------------------------------------------------------------------------------------------|
| `gl` | OpenGL | Core OpenGL functions.<br> Examples: glClearColor, glEnable, glActiveTexture etc. |
| `glfw` | GLFW | GLFW library functions, everything to interact with the OS window, input.<br> Examples: glfwCreateWindow, glfwGetCursorPos, glfwSwapBuffers |
| `GL\` | PHP-GLFW | Classes and functions in this namespace are custom to the extension and are not default to OpenGL.<br> Examples: `GL\Buffer\FloatBuffer`, `GL\Math\Vec3` etc.. |


## Credits

- [Mario Döring](https://github.com/mario-deluna)
- [All Contributors](https://github.com/mario-deluna/php-glfw/contributors)

## License

Please see [License File](https://github.com/mario-deluna/php-glfw/blob/master/LICENSE) for more information.

