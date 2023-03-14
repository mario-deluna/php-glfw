---
hide:
  - navigation
---

# PHP-GLFW a OpenGL and GLFW extension for PHP

**A fully-featured OpenGL and GLFW extension for PHP. Batteries included 🔋!**

[![PHPglfw](https://github.com/mario-deluna/php-glfw/actions/workflows/build.yml/badge.svg)](https://github.com/mario-deluna/php-glfw/actions/workflows/build.yml)

PHP-GLFW allows you to create _2D_ and _3D_ real-time applications in _PHP_. Bringing a whole different set of tools into the PHP world to develop graphical applications like _games, scientific simulations, user interfaces_ and co. 

<div class="grid cards" markdown>

-   :material-clock-fast:{ .lg .middle } __Install in 5 minutes__

    ---

    If you haven't installed PHP-GLFW yet, follow the installation guide for your platform.

    [:octicons-arrow-right-24: Installation **Linux**](./getting-started/installation/install-linux.md)

    [:octicons-arrow-right-24: Installation **MacOS**](./getting-started/installation/install-macos.md)
    
    [:octicons-arrow-right-24: Installation **Windows**](./getting-started/installation/install-windows.md)

-   :material-lightbulb:{ .lg .middle } __PHP OpenGL Tutorial__

    ---

    ![PHP-GLFW](./../docs-assets/php-glfw/getting_started/basic_pipeline.png){ width="100%"}

    Everything ready to get started? Jump right into the first chapter of the tutorial.

    [:octicons-arrow-right-24: Getting Started (Create Window)](./getting-started/window-creation.md)

-   :material-book:{ .lg .middle } __API Docs__

    ---

    Checkout the API documentation for all the functions and classes available in PHP-GLFW.

    [:octicons-arrow-right-24: GLFW](./API/GLFW/glfwCreateWindow.md)
    
    [:octicons-arrow-right-24: OpenGL](./API/OpenGL/glBufferData.md)

    [:octicons-arrow-right-24: Buffers](./API/Buffer/ByteBuffer.md)

    [:octicons-arrow-right-24: Math](./API/Math/Vec4.md)

    [:octicons-arrow-right-24: Geometry](./API/Geometry/ObjFileParser.md)

-   :material-play-circle:{ .lg .middle } __Examples__

    ---

    ![PHP-GLFW](./../docs-assets/php-glfw/examples/preview_sponza.jpg){ width="100%"}

    Want to directly dig into example code? Check out the examples folder.

    [:octicons-arrow-right-24: Examples](./examples/00-about-examples.md)
</div>


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

### PHPGL - Math

PHP-GLFW comes with a built-in mathematics library, written in C and optimized for graphical applications.

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
