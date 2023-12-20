# Creating a VG Context

Before we get to drawing anything, just like with normal OpenGL we need to open a window and create a context in which we can actually draw in. 

Please see [Creating a Window](./window-creation.md) for more information on how to create a window and a context.

_We are not going to discuss the details of creating a window and a context in this tutorial._

!!! question "PHP-GLFW already installed?"

    Follow the **[installation guide](./installation/install-linux.md)** if you **haven't** installed the extension yet!


<figure markdown>
  ![PHP HTML Canvas like API Example](./../docs-assets/php-glfw/getting_started/vg_example.jpg){ width="700" }
</figure>

### Creating the context object

```php
use GL\VectorGraphics\{VGContext};

// code to initalize GLFW and create a window here...

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);
```

As you can see the `VGCotext` constructor takes flags as an argument. In this example we pass `VGContext::ANTIALIAS` to enable (you gussed it) antialiasing.

