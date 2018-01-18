# PHP-GLFW

Write games with PHP! 

Nobody asked for a library like this and still, I delivered. Please don't spend a tremendous amount of time writing a "real game" in PHP with this. Just because its possible does not mean it is a good idea. I have no idea how you would ship such a game. Therefore this library hopefully serves an educational purpose for people who want to get into graphics programming and mainly work with PHP.

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
