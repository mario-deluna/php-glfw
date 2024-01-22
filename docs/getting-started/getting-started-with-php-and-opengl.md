# Getting Started with PHP & OpenGL

This getting started guide is not specifically just about PHP-GLFW. I also try to explain some basics about OpenGL and how to use it with PHP.
So see this more as a Tutorial to learn OpenGL with PHP. Or an OpenGL crash course in PHP.

<div class="grid cards" markdown>

-   :material-clock-fast:{ .lg .middle } __Install in 5 minutes__

    ---

    If you haven't installed PHP-GLFW yet, follow the installation guide for your platform.

    [:octicons-arrow-right-24: Installation **Linux**](./installation/install-linux.md)

    [:octicons-arrow-right-24: Installation **MacOS**](./installation/install-macos.md)
    
    [:octicons-arrow-right-24: Installation **Windows**](./installation/install-windows.md)

-   :material-lightbulb:{ .lg .middle } __PHP OpenGL Tutorial__

    ---

    ![PHP-GLFW](./../docs-assets/php-glfw/getting_started/basic_pipeline.png){ width="100%"}

    Everything ready to get started? Jump right into the first chapter of the tutorial.

    [:octicons-arrow-right-24: Getting Started (Create Window)](./window-creation.md)
</div>

## PHP Vector Graphics API

Are you looking for the **HTML Canvas** inspired API for PHP? Check out the PHP Vector Graphics API.

<div class="grid cards" markdown>

-   :material-clock-fast:{ .lg .middle } __Getting Started with VG__

    ---

    ![PHP Vector Graphics API](./../docs-assets/php-glfw/getting_started/vg_example.jpg){ width="100%"}

    Want to learn how to use the vector graphics API? Check out our getting started guide.

    [:octicons-arrow-right-24: Getting Started](./../user-guide/vector-graphics/creating_a_vgcontext.md)


-   :material-lightbulb:{ .lg .middle } __Fun PHP VG Examples__

    ---

    ![PHP-GLFW](./../docs-assets/php-glfw/examples/vg/fun_bitshifting_thumb.png){ width="100%"}

    We craftet a ton of interactive examples to play around with. Check them out!

    [:octicons-arrow-right-24: Vector Graphics Examples](./../examples/00-about-examples.md#vector-graphics-examples)
</div>

## What is OpenGL?

Imagine you want to build a chair. Where would you begin?

You could start by planting a tree, waiting for it to grow, and then using a rock to chop it down. From there, you could carve wooden tools out of the tree stump then... _ok, you get where im getting at._

We could also **not start from zero**. _(Ignoring the fact that you could take this game much further...)_  

Realistically, you would likely use some pre-made tools, equipment, and perhaps some pre-cut wooden planks to build a simple chair.

The same concept applies here. Think of **OpenGL as a set of basic tools** that allow you to work with your material, which in this case is the **GPU**.

### Why OpenGL?

There are other very popular graphics APIs, such as Vulkan, Metal, and DirectX. 

 * OpenGL is incredibly simple, has a wealth of resources available to learn from, is cross-platform, and has been used to build games for literally decades.
 * Vulkan is awesome, but its very low-level nature would make it an absolute pain to use with PHP while essentially losing all the benefits such a low-level API would give you.
 * Metal is only available on Apple devices and DirectX is only available on Windows, making OpenGL the clear choice here.

### State Machine

As a PHP developer, you are likely familiar with object-oriented programming (OOP) or the old school PHP Spaghetti®.

To my knowledge, there aren't any popular state machine APIs in PHP userland. 

**However, OpenGL is one.**

If you've never worked with a state machine API before, it may feel a bit strange at first. Especially if you're used to classic OOP, this will _feel wrong_ and you won't stop thinking about the _potential bugs_ with so much _global state_ that everybody can and will change!

In real-time rendering, **performance plays a massive role**, so reducing unnecessary operations is key. Clever algorithms are obviously indispensable as well. **Try to suppress your OOP instincts and embrace the state machine.**

_(If you are already thinking of creating a superclass `Drawable` with a `draw()` method which all of your objects will inherit from, don't...)_

## Vector Graphics API

PHP-GLFW also includes a Vector Graphics (VG) API, which is inspired by the HTML Canvas API. This API provides a convenient way to draw graphics on the screen and rapidly prototype ideas and concepts.

The VG API is based on a modified version of [NanoVG](https://github.com/memononen/nanovg) and, like the rest of PHP-GLFW, is a state machine.

Personally, I find it useful to visualize concepts, and the VG API is perfect for that. You can quickly put ideas on the screen and see how they look and feel.

Additionally, you can freely combine the VG API with a custom OpenGL rendering pipeline. For example, you can use the VG API to draw a user interface (UI) and then use OpenGL to render a 3D scene underneath it.

## Additional Resources 

I took a lot of inspiration from multiple sources to write this tutorial. Especially the [LearnOpenGL](https://learnopengl.com/) website was a great help and went into much more detail than I could for PHP-GLFW. I highly recommend you check it out, as most things are directly applicable to PHP-GLFW.

 1. [https://learnopengl.com](https://learnopengl.com/)
 2. [http://www.opengl-tutorial.org](http://www.opengl-tutorial.org)
 3. [https://nicolbolas.github.io/oldtut/index.html](https://nicolbolas.github.io/oldtut/index.html)
 2. [https://www.khronos.org/opengl/wiki/Getting_Started](https://www.khronos.org/opengl/wiki/Getting_Started)
