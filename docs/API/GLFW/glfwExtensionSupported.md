# glfwExtensionSupported
Returns whether the specified extension is available.

```php
function glfwExtensionSupported(string $extension) : int
```

This function returns whether the specified
`API extension` is supported by the current OpenGL or
OpenGL ES context. It searches both for client API extension and context
creation API extensions.

A context must be current on the calling thread. Calling this function
without a current context will cause a `GLFW_NO_CURRENT_CONTEXT` error.

As this functions retrieves and searches one or more extension strings each
call, it is recommended that you cache its results if it is going to be used
frequently. The extension strings will not change during the lifetime of
a context, so there is no danger in doing this.

This function does not apply to Vulkan. If you are using Vulkan, see @ref
glfwGetRequiredInstanceExtensions, `vkEnumerateInstanceExtensionProperties`
and `vkEnumerateDeviceExtensionProperties` instead.

arguments

:    1. `string` `$extension` The ASCII encoded name of the extension.

returns

:    `int` `GLFW_TRUE` if the extension is available, or `GLFW_FALSE`
otherwise.

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```