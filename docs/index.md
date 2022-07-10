# Welcome to PHP-GLFW 

A fully-featured OpenGL and GLFW extension for PHP. Batteries included (Math Functions, Texture Loaders, etc..)

PHP-GLFW allows you to create 2D and 3D desktop applications in PHP. Bringing a whole different set of tools into the PHP world for real-time applications or simple rendering services. 

## 💡 Things to know when you start

PHP-GLFW tries to keep the core OpenGL / GLFW API as close to the original as possible and only do modifications to the API when absolutely necessary. This results in some functions being quite wired from a PHP point of view. In some cases, the extension comes with its own wrapper functions to make the API more simple. To keep things organized tho, all functions are prefixed so you know where they are coming from:

| prefix | module   | desc                                                                                                                                        |
|--------|----------|---------------------------------------------------------------------------------------------------------------------------------------------|
| `gl`     | OpenGL   | Core OpenGL functions the way they are documented.<br> Examples: glClearColor, glEnable, glActiveTexture etc.                               |
| `glfw`   | GLFW     | GLFW library functions, everything to interact with the OS window, input.<br> Examples: glfwCreateWindow, glfwGetCursorPos, glfwSwapBuffers |
| `pgl`    | PHP-GLFW | Functions specific to this extension<br> Examples: pglCreateBuffers, pglBufferFloatData..                                                   |

