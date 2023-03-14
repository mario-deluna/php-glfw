# Gettings Started with PHP & OpenGL 

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

## What is OpenGL?

Creating realistic, three-dimensional models or designing immersive virtual landscapes in games requires the use of powerful graphics APIs like OpenGL, Vulkan, or DirectX. Among these tools, OpenGL, (Open Graphics Library), is a popular cross-platform API for rendering 2D and 3D graphics. It has been employed in various applications, ranging from gaming and computer-aided design (CAD) to scientific visualizations. Although rendering APIs such as Vulkan and DirectX have also gained prominence for their particular strengths, OpenGL's simplicity and capabilities maintain its relevance in the field of graphics rendering.

### State Machine

An important aspect of OpenGL is its architecture as a state machine. This implies that OpenGL relies on a collection of global states to determine its graphics rendering behavior. Programmers can modify and configure these states to achieve their desired visual effects. While this concept might appear unconventional, especially for those familiar with object-oriented programming (OOP), understanding its intricacies can lead to a powerful and adaptable approach to graphics rendering.

### Navigating the Learning Curve

Adapting to OpenGL's state machine architecture can be challenging, especially for those with an OOP background. It may lead to unexpected and frustrating bugs during the learning process. However, don't let this discourage you! As you become more familiar with the API, you'll discover the potential it holds for creating stunning visual experiences.

To help you get started, here are some tips for working with OpenGL:

1. **Take it slow:** Familiarize yourself with the fundamentals of OpenGL and its state machine design. Start with simple 2D graphics before diving into more complex 3D scenes.
2. **Be patient:** Learning OpenGL can be an iterative process, so don't be afraid to experiment and make mistakes. The more you practice, the better you'll become.
3. **Utilize resources:** There are numerous tutorials, forums, and documentation available to help you learn OpenGL. Engage with the community and ask questions if you're stuck.
   I can really recommend [https://gamedev.net](https://gamedev.net)
4. **Understand shaders:** Shaders play a crucial role in OpenGL, so it's important to learn how to write and use them effectively to control the rendering pipeline.


## Additional resources 

I took a lot of inspiration from multiple sources to write this tutorial. Especially the [LearnOpenGL](https://learnopengl.com/) website was a great help and went into much more detail than I could for PHP-GLFW. I highly recommend you check it out, as most things are directly applicable to PHP-GLFW.

 1. [https://learnopengl.com](https://learnopengl.com/)
 2. [http://www.opengl-tutorial.org](http://www.opengl-tutorial.org)
 3. [https://nicolbolas.github.io/oldtut/index.html](https://nicolbolas.github.io/oldtut/index.html)
 2. [https://www.khronos.org/opengl/wiki/Getting_Started](https://www.khronos.org/opengl/wiki/Getting_Started)
