# Examples 

 * [1. Hello World](#1-hello-world)
 * [2. 3D Cube](#2-3d-cube)
 * [3. Textured Cube](#3-textured-cube)
 * [4. Instanced Rendering](#4-instanced-rendering)
 * [5. Object file loading](#5-object-file-loading)
 * [6. Simple lighting](#6-simple-lighting)
 * [7. Text Rendering](#7-text-rendering)
 * [8. Input And Events](#8-input-and-events)

## 1. Hello World

This is the most basic example of how to use the GLFW library.
You can think of it as a ""Hello World"" example. In this example, we create a window and render a triangle.

This example does not utilize our helper class to keep it as basic as possible.

> Code: [01_triangle.php](./01_triangle.php)!

<img width="512" alt="s" src="https://user-images.githubusercontent.com/956212/183306669-f085f78a-b0ab-47e1-9a92-cc0b3dc9ca36.png">

## 2. 3D Cube

This example shows how to render a 3D cube using PHP OpenGL.

> Code: [02_3D_cube.php](./02_3D_cube.php)!

https://user-images.githubusercontent.com/956212/183306744-3b345bc8-7010-4e68-94c2-29a335102ce4.mov

## 3. Textured Cube

This example shows how to render a textured cube using PHP OpenGL. It provides an example of how to load a texture from a file and how to use it in a shader using the PHP-GLFW `GL\Texture\Texture2D` class.

> Code: [03_textured_cube.php](./03_textured_cube.php)!

https://user-images.githubusercontent.com/956212/183306784-c85c2b03-ed6f-4070-a416-bdcca8c89783.mov

## 4. Instanced Rendering 

This example shows how to render multiple instances of a single object using PHP OpenGL. It is just a basic example of how to use instanced rendering.

> Code: [04_instancing.php](./04_instancing.php)!

https://user-images.githubusercontent.com/956212/183306836-4b5a06c6-5fdf-40eb-a038-b413af177b77.mov

## 5. Object file loading

This example shows how to load a 3D object from a file using PHP OpenGL. It displays how to utilize the `\GL\Geometry\ObjFileParser` class to load a 3D object from a file and how to render it.

> Code: [05_objloading.php](./05_objloading.php)!

<img width="512" alt="s" src="https://user-images.githubusercontent.com/956212/190877288-a61e4985-7a1b-4570-bf39-f0f95433e5a7.png">

## 6. Simple lighting 

This example shows how to render a 3D object with simple lighting using PHP OpenGL. 

> Code: [06_basic_light.php](./06_basic_light.php)!

<img width="512" alt="s" src="https://user-images.githubusercontent.com/956212/190879015-59616d84-b23e-4319-93b2-9c53c423f6b6.png">

## 7. Text Rendering

This example shows how to render text using PHP OpenGL. It uses a simple bitmap font to render text on the screen.

> Code: [07_text_rendering.php](./07_text_rendering.php)!

<img width="512" alt="s" src="https://user-images.githubusercontent.com/956212/190903240-6f144bf0-77dd-4af9-a293-6e7e8ee5c198.png">

## 8. Input And Events

This example shows how to handle input and events using PHP OpenGL. It implements all available input and window event callbacks and prints them to the console.

> Code: [08_input_and_events.php](./08_input_and_events.php)!

