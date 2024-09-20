<p align="center">
 <img width="500px" src="https://raw.githubusercontent.com/phpgl/docs-assets/master/php-glfw/logos/logo_with_text.svg">
</p>

<h1 align="center"> PHP-GLFW</h1>

<p align="center">
  <a href="https://github.com/mario-deluna/php-glfw/blob/master/LICENSE" title="license"><img alt="LICENSE" src="https://img.shields.io/badge/license-MIT-428f7e.svg?logo=open%20source%20initiative&logoColor=white&labelColor=555555"></a>
  <a href="#tada-php-support" title="PHP Versions Supported"><img alt="PHP Versions Supported" src="https://img.shields.io/badge/php-8.0%20to%208.3-777bb3.svg?logo=php&logoColor=white&labelColor=555555"></a>
  <a href="https://github.com/mario-deluna/php-glfw/releases/"><img src="https://img.shields.io/github/tag/mario-deluna/php-glfw?include_prereleases=&sort=semver&color=blue" alt="GitHub tag"></a>
  <a href="https://github.com/mario-deluna/php-glfw/issues"><img src="https://img.shields.io/github/issues/mario-deluna/php-glfw" alt="issues - php-glfw"></a>
</p>

<p align="center">
  <a href="https://github.com/mario-deluna/php-glfw/actions/workflows/build.yml" title="PHP-GLFW Tests"><img alt="PHP-GLFW Tests" 
  src="https://github.com/mario-deluna/php-glfw/actions/workflows/build.yml/badge.svg"></a>
  <a href="https://github.com/mario-deluna/php-glfw/actions/workflows/macos_installer.yml" title="MacOS Installer"><img alt="MacOS Installer"
  src="https://github.com/mario-deluna/php-glfw/actions/workflows/macos_installer.yml/badge.svg"></a>
  <a href="https://github.com/mario-deluna/php-glfw/actions/workflows/windows.yml" title="Windows Build"><img alt="Windows Build"
  src="https://github.com/mario-deluna/php-glfw/actions/workflows/windows.yml/badge.svg"></a>
</p>


**[Website](https://phpgl.net) • [Getting Started](https://phpgl.net/getting-started/getting-started-with-php-and-opengl.html) • [API Docs](https://phpgl.net/API/Buffer/ByteBuffer.html) • [Examples](https://phpgl.net/examples/00-about-examples.html)**

**A fully-featured OpenGL and GLFW extension for PHP. Batteries included 🔋!**

<!-- [![PHP-GLFW Tests](https://github.com/mario-deluna/php-glfw/actions/workflows/build.yml/badge.svg)](https://github.com/mario-deluna/php-glfw/actions/workflows/build.yml)
[![MacOS Installer](https://github.com/mario-deluna/php-glfw/actions/workflows/macos_installer.yml/badge.svg)](https://github.com/mario-deluna/php-glfw/actions/workflows/macos_installer.yml)
[![Windows Build](https://github.com/mario-deluna/php-glfw/actions/workflows/windows.yml/badge.svg)](https://github.com/mario-deluna/php-glfw/actions/workflows/windows.yml) -->

PHP-GLFW allows you to create _2D_ and _3D_ real-time applications in _PHP_. It introduces a whole new set of tools for PHP developers to build graphical applications like _games, scientific simulations, user interfaces_, and much more.

<p align="center">
 <img width="720px" src="https://user-images.githubusercontent.com/956212/196137371-74546845-4101-4e22-8d1c-4550f0ba2adf.gif" alt="3D Rendering in PHP">
</p>

_Currently supports **PHP8.x**_

- [What is this extension? Discover the features 🚀](#what-is-this-extension-features-)
  + [OpenGL](#opengl)
  + [GLFW](#glfw)
  + [PHPGL - Math](#phpgl---math)
  + [PHPGL - Buffers](#phpgl---buffers)
  + [PHPGL - Textures](#phpgl---textures)
  + [PHPGL - Geometry](#phpgl---geometry)
  + [How are the bindings achieved?](#how-are-the-bindings-achieved)
- [Documentation 📚](#documentation-)
- [Examples](#examples)
  + [Game - PHP Towerdefense](#php-towerdense-game)
  + [Game - FlappyPHPant](#flappyphpant)
- [Installation](#installation)
  + [MacOS](#macos)
  + [Linux](#linux)
  + [Stubs (IDE Support)](#stubs-ide-support)
- [Credits](#credits)
- [License](#license)

## What is this extension? Features 🚀

PHP-GLFW aims to be a complete solution containing everything you need to start building graphical applications in PHP. It doesn't just provide **GLFW library bindings**, but also includes **OpenGL bindings** and a set of essential classes and helpers.

### OpenGL

* Full native support for **OpenGL** (4.1+ core), bringing GPU-accelerated rendering to PHP.
* Targets OpenGL 4.1, but can be built for newer versions as well.
* Support for OpenGL extensions (limited).
* Mirrors the C API as closely as possible, with adjustments made where required or otherwise nonsensical.
* Supports ~90% of the full standard; see [GLSUPPORT.md](./GLSUPPORT.md) for details.

### GLFW

This extension includes bindings for the powerful **[GLFW](https://www.glfw.org)** library, offering a range of amazing features, such as:

* Multiplatform Window creation and handling (MacOS / Windows / Linux)
* Support for multiple windows and monitors
* Real-time user input handling
  * **Keyboard and Mouse** event handling
  * **Joystick** input support
  * **Gamepad** Support

### Vector Graphics API

PHP-GLFW includes a vector graphics API that allows you to draw in a HTML canvas-like manner in PHP. Its uses the same OpenGL context internally allowing you to build complex rendering pipelines utilizing both the vector graphics API and the more low-level OpenGL API.

<p align="left">
 <img alt="PHP Vector Graphics Rendering Library" src="https://github.com/user-attachments/assets/be534c0e-f0c3-4201-bd98-d7725e3b62ed" align="center" width="600" >
</p>

- Allows for quick and intuitive rendering of primitives.
- Includes numerous helpers for colors.
- Supports gradients and images.
- Easily renders text with any font.
- Ideal for quickly creating GUIs.

1. [Read more about the Vector Graphics API](https://phpgl.net/user-guide/vector-graphics/creating_a_vgcontext.html)

### PHPGL - Math

PHP-GLFW comes with a built-in mathematics library, written in C and optimized for graphical applications.

<p align="left">
 <img alt="PHP Vector Math Library" src="https://github.com/user-attachments/assets/99b19edc-6679-46c7-82a9-7b0969fce96a" align="center" width="600" >
</p>

* Supported structs: `Vec2`, `Vec3`, `Vec4`, `Mat4`, and `Quat`
* Includes most common matrix operations, like: `lookAt`, `perspective`, `inverse`, `rotate`, and more

Integration into the extension offers several advantages:

* High performance
* Low memory footprint
* Overloaded operators for math structs, enabling intuitive operations like:
  ```php
  use GL\Math\Vec2;
  $v3 = Vec2(15, -5) + Vec2(42, 7); // returns Vec2(57, 2)
  ```
* Some OpenGL functions directly accept math structs as arguments

1. [Read more about math functions](https://phpgl.net/user-guide/math/math_functions.html)

### PHPGL - Buffers

This extension also includes a set of buffer objects that internally hold data in native types.

* Can handle large arrays of data
* Low memory footprint and very fast
* Data is stored internally to be directly uploadable to the GPU

1. [Read more about the buffers](https://phpgl.net/API/Buffer/FloatBuffer.html)

### PHPGL - Textures

PHP-GLFW supports the loading of images/textures into buffers without requiring an additional extension:

* Can load common image formats, like `jpg`, `png`, `tga`, `bmp`, and `gif` _(gd or Imagick is not required)_
* Can write images/textures back to disk
* Writes data into a `BufferInterface` object, providing full access to the bitmap

1. [Read more about texture loading](https://phpgl.net/API/Texture/Texture2D.html)

### PHPGL - Geometry

PHP-GLFW comes with a `.obj` wavefront file loader, allowing you to load and parse `.obj` files. It also provides helpers to generate tangent and bitangent vectors for the loaded geometry. Currently, only triangulated geometry is supported, with no support for quads.

* Can parse `.obj` and `.mtl` files
* Can generate normal, tangent, and bitangent vectors for the loaded geometry on the fly
* Allows extraction of separate meshes and groups from the loaded geometry
* Can group vertices by their material
* Can reindex extracted meshes to reduce the number of vertices

1. [Read more about geometry loading](https://phpgl.net/API/Geometry/ObjFileParser.html)

### How are the bindings achieved?

PHP-GLFW parses the OpenGL specs to generate most of the C extension, instead of porting functions manually. Manual adjustments are made where necessary.

## Documentation 📚

> 1. [Full Documentation](https://phpgl.net)
> 2. [Getting Started Guide](https://phpgl.net/getting-started/window-creation.html)
> 3. [User Guide](https://phpgl.net/user-guide/vector-graphics/creating_a_vgcontext.html)
> 4. [API Docs](https://phpgl.net/API/Buffer/ByteBuffer.html)

## Examples

[![glfw-previews](https://user-images.githubusercontent.com/956212/189208007-74064a7b-0e93-4d7f-b53e-e799a0641e54.png)](./examples#examples)

Explore the [examples](./examples#examples) directory to dive into the code.

### FlappyPHPant

A very simple Flappy Bird-like game written in PHP.

<p align="center">
   <img width="640" src="https://github.com/phpgl/flappyphpant/assets/956212/9d32a533-73cb-40e6-b940-7976b765d658" alt="FlappyPHPant 2D PHP Game">
</p>

https://github.com/phpgl/flappyphpant


### php-chip8

Yet another CHIP-8 emulator, but in PHP!

<p align="center">
   <img width="640" src="https://github.com/mario-deluna/php-chip8/assets/956212/ae03baa0-8a00-4872-8131-39ca420a6310" alt="A CHIP-8 Game Emulator written in PHP">
</p>

https://github.com/mario-deluna/php-chip8


### PHP-Towerdense Game

We are currently developing a 3D game entirely built with PHP, leveraging the power of PHP-GLFW. The game, named PHP-TowerDefense, is open-source and serves as a showcase for the capabilities of PHP-GLFW. Although the game is in active development, it is not yet ready for release.

<p align="center">
 <img width="80%" alt="PHP-TowerDefense Screenshot" src="https://user-images.githubusercontent.com/956212/222989984-e1b2d431-26de-47f4-a17d-7800e5afb052.jpg">
</p>
Check out the game's repository on GitHub for more information and to follow its progress: https://github.com/phpgl/php-towerdefense

### php-pong

Classic Pong game programmed with pure OpenGL wrapped in OOP code.

<p align="center">
   <img width="640" src="https://raw.githubusercontent.com/medilies/php-pong/main/screened.gif" alt="Classic Pong Game written in PHP">
</p>

https://github.com/medilies/php-pong

## Installation 

**Please refer to the comprehensive installation guide here: [Installation](https://phpgl.net/getting-started/installation/install-linux.html)**

> **PHP Version:** `>= 8.0`
> While I would love to support older PHP builds, it was just not feasible for this extension.

### MacOS 

#### Installer

You can use a simple installer script to install PHP-GLFW:

```
php -r "copy('https://raw.githubusercontent.com/mario-deluna/php-glfw/master/install/macos-installer.php', 'phpglfw-installer.php');" && php phpglfw-installer.php
```

Once you see "Installation finished!", you're ready to go!

#### Manual installation

For a manual approach, ensure you have installed the `php-dev`, `git`, and `cmake` packages. **They are required!**

```bash
git clone https://github.com/mario-deluna/php-glfw
cd php-glfw
sudo phpize && ./configure --enable-glfw
sudo make install
```

Don't forget to add `glfw.so` in the `php.ini` file:

```ini
extension="glfw.so"
```

### Linux 

`cmake` is required for the installation. You can skip the first step if it's already installed.
Also, make sure that you install the `php-dev` package, for example, `php8.1-dev`.

```
sudo apt install -y cmake git 
git clone https://github.com/mario-deluna/php-glfw
cd php-glfw
sudo phpize && ./configure --enable-glfw
sudo make install
```

Make sure to add `glfw.so` in the `php.ini` file:

```ini
extension="glfw.so"
```

### Stubs (IDE Support)

As this is a PHP extension, your editor / IDE does not support auto-completion and doc lookups without some help.
We created a composer package you can include as a dev dependency to have full support:

```
composer require --dev phpgl/ide-stubs
```

## Credits

- [Mario Döring](https://github.com/mario-deluna)
- [All Contributors](https://github.com/mario-deluna/php-glfw/contributors)

## License

Please see [License File](https://github.com/mario-deluna/php-glfw/blob/master/LICENSE) for more information.
