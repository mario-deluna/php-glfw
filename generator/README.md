# PHP-GLFW binding generator

Because there are so damn many functions and constants to cover I decided to create a simple generator for this purpose.

The Idea is to use the generator until most of the API is covered and then start optimizing and extending the extension in C itself.

To rebuild the `glfw_gen.c` file simply run the following command:

```
$ ./generator/build
```