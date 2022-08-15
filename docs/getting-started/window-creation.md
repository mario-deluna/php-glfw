# Opening a window

Before we get to drawing anything, we need to open a window and create a context in which we can actually draw in. This requires some boilerplate code which we discuss in this guide.

!!! note "Full Source"

    This getting started tutorial is based on the examples provided with PHP-GLFW.<br> You can check out the complete source code here: [01_triangle.php](https://github.com/mario-deluna/php-glfw/blob/master/examples/01_triangle.php)


## Initalizing GLFW 

At the very beginning we want to call [glfwInit](./../API/GLFW/glfwInit.md), which you probably can guess from the name will initialize GLFW. 

GLFW is a multi-platform library for OpenGL that handles window creation, input & context for us.

```php
if (!glfwInit()) {
    throw new Exception('GLFW could not be initialized!');
}
```

## Creating a Window

Using the function [glfwWindowHint](./../API/GLFW/glfwWindowHint.md) we can declare properties / options aka hints for the to be created window.

```php
// allow the window to be resized by the user
glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

// set the OpenGL context version and profile 
glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

// enable forward compatibility, @see glfw docs for details
glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
```

After declaring the window hints we can call the [glfwCreateWindow](./../API/GLFW/glfwCreateWindow.md) to create a window resource. Hints like `GLFW_RESIZABLE` are completely optional.

```php 
if (!$window = glfwCreateWindow(800, 600, "PHP GLFW Demo")) {
    throw new Exception('OS Window could not be initialized!');
}
```

`$window` is now an instance of the `GLFWwindow` class, which holds the internal resource to the actual window.

## Binding GL Context

By calling [glfwMakeContextCurrent](./../API/GLFW/glfwMakeContextCurrent.md) glfw will make the given window object the one that is bound to the current GL context.
In other words, all GL commands will be executed in the context of this window. Special in PHP-GLFW is that this will also initialize [glad](https://github.com/Dav1dde/glad).

```php
glfwMakeContextCurrent($window);
```

Because I don't particularly appreciate it when my notebook sounds like a jet engine, I enable V-Sync next so that frames are not swapped faster
then the displays refresh rate.

```{ .php .annotate }
glfwSwapInterval(1); #(1)
```

1.  Check [glfwSwapInterval](./../API/GLFW/glfwSwapInterval.md) 


## Main Loop

Because we want the application to run as long as the user wishes to, we have to create a "main loop". 
Basically, a subroutine that keeps on running until we want to exit the application.

In our main loop, we got to take care of a few things, a simplified common main loop looks something like this:

```mermaid
graph LR
 A[Start] --> B[Window should close?];
 B -->|No| C[Poll events];
 C --> D[Do things & Render];
 D --> E[Swap Buffer];
 E --> B;
 B ---->|Yes| F[Cleanup & stop];
```

To make this example a bit more interesting, we change the clear color based on the current mouse position.

```php
while (!glfwWindowShouldClose($window))
{
    glfwPollEvents();
    
    // setting the clear color to black and clearing the color buffer
    glfwGetCursorPos($window, $mouseX, $mouseY);
    glClearColor(sin($mouseX / 300), sin($mouseY / 300), cos($mouseY / 300), 1);
    glClear(GL_COLOR_BUFFER_BIT);

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
}
```

For good mesure, let's clean up after the loop.

```php
glfwDestroyWindow($window);
glfwTerminate();
```

## Demo 

Here you go, a colored window! Not the peak of excitement, but we are getting there slowly.

<div class="video-wrapper">
 <iframe width="1280" height="720" src="https://www.youtube-nocookie.com/embed/kjKIdooEUH0" frameborder="0" allowfullscreen></iframe>
</div>

Next up we are going to create our first geometry and render a triangle in our window.


## Additional resources 

 1. https://www.glfw.org/docs/latest/window_guide.html
 2. https://learnopengl.com/Getting-started/Hello-Window