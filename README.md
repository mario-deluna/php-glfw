# PHP-GLFW

Write fun **3D** games or other **graphical** applications with PHP! This is a C extension adds **GLFW & OpenGL** support to **PHP**. 

## ❓❓❓

<p align="center">
 <img src="https://media.giphy.com/media/lzQHOFIV9Cj5whBcOF/giphy.gif"/>
</p>

> Keep in mind this is a **gif** in reality this runs smoothly at 60fps.

## Notes / Disclaimer

Nobody asked for a library like this, and still, I delivered. Please don't spend a tremendous amount of time writing a "real game" in PHP with this. Just because its possible does not mean it is a good idea. I have no idea how you would ship/distribute such a game. Therefore this library hopefully serves an educational purpose for people who want to get into graphics programming and mainly work with PHP.

I am very far from being an expert with the Zend engine and the PHP internals. So there are pieces in this code that will make you want to pull out your hair from your head. My focus was to make this thing work, bugs, performance and memory leaks or even safe type conversions can be fixed later. (Or probably never because again this is not supposed to create production applications with.) Many methods introduce a hell lot of overhead when it comes to copying (I buy you a beer here in Zürich if you can help me make this somehow efficient.).

Also, keep in mind I did not spend time making this failsafe in any way. When you pass unexpected types, you might end up with a segmentation fault.

I can't point this out enough this library is far from stable, and should **only** be used in _"just for fun"_ or _"because I can"_ and general _experimental_ type of projects. At least in its current state, who knows what the future brings.
 

## Installation

> Note: I only tested this extension on MacOS.

Make sure to install glfw3. 

```
$ brew install glfw3 
```

Clone the repository.

```
$ git clone https://github.com/mario-deluna/php-glfw/ && cd php-glfw
```

Now you should be able to build the extension:

```
$ phpize
$ ./configure --enable-glfw
$ make && make install
```

Don't forget to link the extension, by appending the following lines to your `php.ini`.

```
[glfw]
extension=glfw.so
```

## Example

## Whats inside?

This extension does not only deliver glfw and OpenGL bindings, but it also comes with `stb_image` to make getting started easy.

## API Differences

I have tried to keep the API as similar as possible to the original C API of glfw and OpenGL, but I had to change some things to make this work quickly with PHP. 

### GLFW 

#### glfwMakeContextCurrent

This method will automatically load the **glad** function pointers.

### OpenGL

#### glShaderSource

The last argument the `length` has been removed from the `glShaderSource` function. When you want to add multiple, simply use null termination, or just call the method multiple times.

#### glBufferData

The `glBufferData` method has been disabled and is replaced with multiple type specific buffer methods:
 
 * glBufferDataFloat
 * glBufferDataDouble
 * glBufferDataInt
 * glBufferDataLong

Also, you do not need to pass in the size of your data this is solved by the type-specific methods itself.

```php
glBufferDataFloat(GL_ARRAY_BUFFER, [1.0, 0.5, 0.0], GL_STATIC_DRAW);
``` 

#### glVertexAttribPointer

In phpglfw, the `stride` (byte offset) and `pointer` offset of the vertex attributes is a pure number representing the count and not the size of the data. The size is then determined by the given type.

So this attribute pointer in C:

```c
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
```

Would be written in php be:

```php
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5, 3);
```
