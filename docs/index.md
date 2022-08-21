---
hide:
  - navigation
---

# PHP-GLFW a OpenGL and GLFW extension for PHP

**A fully-featured OpenGL and GLFW extension for PHP. Batteries included 🔋!**

[![PHPglfw](https://github.com/mario-deluna/php-glfw/actions/workflows/build.yml/badge.svg)](https://github.com/mario-deluna/php-glfw/actions/workflows/build.yml)

PHP-GLFW allows you to create _2D_ and _3D_ real-time applications in _PHP_. Bringing a whole different set of tools into the PHP world to develop graphical applications like _games, scientific simulations, user interfaces_ and co. 

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