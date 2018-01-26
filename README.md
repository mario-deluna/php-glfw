# PHP-GLFW

Write games with PHP! 



## Notes / Disclaimer

Nobody asked for a library like this and still, I delivered. Please don't spend a tremendous amount of time writing a "real game" in PHP with this. Just because its possible does not mean it is a good idea. I have no idea how you would ship / distribute such a game. Therefore this library hopefully serves an educational purpose for people who want to get into graphics programming and mainly work with PHP.

I'm very far from being an expert with the Zend engine and the PHP internals. So there are pieces in this code that will make you want to pull out your hair. My focus was to make this thing run, bugs, performance and memory leaks can be fixed later. Or probably never because again this is not supposed to create production applications with.

## Installation

Make sure to install glfw3 

```
$ brew install glfw3 
```

Now you should be able to build the extension:

```
$ phpize
$ ./configure --enable-glfw
$ make && make install
```

## API Differences

I've tried to keep the API as similar as possible to the original C API of glfw and OpenGL, but I had to change some things to make this work easily with PHP.

### GLFW 

#### glfwMakeContextCurrent

This method will automatically load the **glad** function pointers.

### OpenGL

#### glBufferData

