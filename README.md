<p align="center">
 <img width="100px" src="https://raw.githubusercontent.com/mario-deluna/php-glfw/v2/docs/logo_phpglfw_s.png">
</p>

# PHP-GLFW

**[Website](https://example.com) • [User Guide](https://example.com) • [API Docs](https://example.com)**

A fully-featured OpenGL and GLFW extension for PHP. Batteries included _(Math Functions, Texture Loaders...)_

[![PHPglfw](https://github.com/mario-deluna/php-glfw/actions/workflows/build.yml/badge.svg)](https://github.com/mario-deluna/php-glfw/actions/workflows/build.yml)

PHP-GLFW allows you to create _2D_ and _3D_ real-time applications in _PHP_. Bringing a whole different set of tools into the PHP world to develop graphical applications like _games, scientific simulations, user interfaces_ and co. 

  * [What is this extension? Features 🚀](#what-is-this-extension-features-)
  * [Documentation / Gettings Started / Examples 📚](#documentation--gettings-started--examples-)
  * [Installation](#installation)
  * [Things to know when you start 💡](#things-to-know-when-you-start-)
  * [Credits](#credits)
  * [License](#license)

## What is this extension? Features 🚀

Instead of porting function by function manually, PHP-GLFW parses the OpenGL specs to generate most of this C extension. Adjustments are made manually where necessary.

 * Full native support of **OpenGL** (3.3+ core).
    * GPU accelerated rendering in PHP.
    * Targeting OpenGL 4.1, but it can technically be built for newer versions as well.
    * Support for OpenGL extensions (limited).
    * Mostly mirroring the C API, some adjustments where required.
 * Multiplatform Window and real-time input handling using the **[GLFW](https://www.glfw.org)** library. GLFW comes with great features, to name a few:
    * Support for multiple windows and monitors.
    * **Keyboard and Mouse** event handling. 
    * **Joystick** input support.
 * Typed Buffer classes to handle large arrays of data.
    * Low memory footprint and very fast. 
    * Data is stored internally to be directly uploadable to the GPU.
 * built-in **GL math** library with overloaded operators.
    * Allows you to write things like `Vec2(15, -5) * Vec2(42, 7)`
    * Supports the common structures `Vec2`, `Vec3`, `Vec4`, `Mat4` and `Quat`.
    * A bunch of helpers.
 * **Image / Texture** loading and writing.
    * can load common image formats as `jpg`, `png`, `tga`, `bmp`, `gif`. _(gd or Imagick is not required)_
 
## Documentation / Gettings Started / Examples 📚

> 1. [Full Documentation](https://example.com) 
> 2. [Getting Started Guide](https://example.com) 
> 3. [User Guide](https://example.com) 
> 4. [API Docs](https://example.com) 

If you want to check out the code straight away, check out the [examples](./examples#examples) directory.

## Installation 

Please see the complete detailed installation guide here: [Installation](https://example.com)

## Things to know when you start 💡 

PHP-GLFW tries to keep the core OpenGL / GLFW API as close to the original as possible and only do modifications to the API when necessary. This results in some functions being quite wired from a PHP point of view. Naming scheme:

| prefix | module | desc |
|--------|----------|-------------------------------------------------------------------------------------------------------------------------|
| `gl` | OpenGL | Core OpenGL functions.<br> Examples: glClearColor, glEnable, glActiveTexture etc. |
| `glfw` | GLFW | GLFW library functions, everything to interact with the OS window, input.<br> Examples: glfwCreateWindow, glfwGetCursorPos, glfwSwapBuffers |
| `GL\` | PHP-GLFW | Classes and functions in this namespace are custom to the extension, and are not default to OpenGL.<br> Examples: `GL\Buffer\FloatBuffer`, `GL\Math\Vec3` etc.. |


## Credits

- [Mario Döring](https://github.com/mario-deluna)
- [All Contributors](https://github.com/mario-deluna/php-glfw/contributors)

## License

Please see [License File](https://github.com/mario-deluna/php-glfw/blob/master/LICENSE) for more information.

