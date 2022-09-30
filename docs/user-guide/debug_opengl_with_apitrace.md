# Debug OpenGL calls with apitrace

Every OpenGL developer will sooner or later end up in a situation where they only see a black screen or a crash and they have no idea what is going wrong.  In this case it is often VERY useful to record the OpenGL calls and replay them in a debugger. There are a bunch of tools that can do this, but the one I like the most is [apitrace](http://apitrace.github.io/). Mostly because it is pretty straight forward to use and it is available for **all major platforms**.

**Other tools**

 * [NVIDIA Nsight](https://developer.nvidia.com/nsight-visual-studio-edition)<br>
   My absolute favorite, but it is only available for Windows. 
 * [RenderDoc](https://renderdoc.org/)
 * [Intel GPA](https://www.intel.com/content/www/us/en/developer/tools/graphics-performance-analyzers/overview.html)<br>
    I have not used this one, I think it only works with intel chips, please correct me if I am wrong.
 * [glintercept](https://github.com/dtrebilco/glintercept)
 * [vogl](https://github.com/ValveSoftware/vogl)

 ## Trace calls

Tracing a PHP OpenGL application is no different than tracing a C++ OpenGL application. 

```bash
apitrace trace --api gl php my_php_application.php
```

This will launch your application and create a file called `php.trace` in the current directory. This file contains all the OpenGL calls that were made during the execution of the PHP script.

## Inspect calls

To inspect the calls you can use the `qapitrace` command. This will open a GUI that allows you to inspect the calls. 

```bash
qapitrace php.trace
```

