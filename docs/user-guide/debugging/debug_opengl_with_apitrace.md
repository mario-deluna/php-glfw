# Debug OpenGL calls with apitrace

Every OpenGL developer, at some point, will face the challenge of a black screen or a crash without a clear understanding of what went wrong. In these situations, recording and replaying OpenGL calls in a debugger can be invaluable. Several tools can help you achieve this, but one of the most popular is [apitrace](http://apitrace.github.io/). Apitrace stands out due to its simplicity, ease of use, and cross-platform compatibility, supporting all major operating systems.

## Alternative Debugging Tools

While apitrace is a great choice, other tools might be better suited to your specific needs or preferences. Here are some alternatives:

- [NVIDIA Nsight](https://developer.nvidia.com/nsight-visual-studio-edition): A fantastic tool, but limited to Windows. My personal favorite.
- [RenderDoc](https://renderdoc.org/): A versatile, graphics debugging tool.
- [Intel GPA](https://www.intel.com/content/www/us/en/developer/tools/graphics-performance-analyzers/overview.html): Tailored for Intel chips, it may not work with other chipsets.
- [glintercept](https://github.com/dtrebilco/glintercept): An OpenGL function call interceptor for Windows.
- [vogl](https://github.com/ValveSoftware/vogl): A powerful, open-source debugger created by Valve Software.

## Tracing OpenGL Calls

When working with PHP-GLFW, tracing OpenGL calls is a straightforward process, similar to tracing calls in a C++ OpenGL application. To trace your PHP OpenGL application, use the following command:

```bash
apitrace trace --api gl php my_php_application.php
```

This command launches your application and generates a file named `php.trace` in the current directory. This file records all the OpenGL calls made during the PHP script's execution.

## Analyzing Traced Calls

To examine the recorded calls, use the `qapitrace` command. This command opens a GUI that allows you to easily navigate and analyze the calls:

```bash
qapitrace php.trace
```

Through the `qapitrace` GUI, you can scrutinize the OpenGL calls, view their results, buffers, textures, states etc. This information can help you understand what's happening behind the scenes and improve the stability and performance of your PHP-GLFW applications.

Happy debugging!

