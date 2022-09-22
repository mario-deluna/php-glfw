# glfwVulkanSupported
Returns whether the Vulkan loader and an ICD have been found.

```php
function glfwVulkanSupported() : int
```

This function returns whether the Vulkan loader and any minimally functional
ICD have been found.

The availability of a Vulkan loader and even an ICD does not by itself
guarantee that
surface creation or even instance creation is possible. Call @ref
glfwGetRequiredInstanceExtensions to check whether the extensions necessary
for Vulkan
surface creation are available and
[`glfwGetPhysicalDevicePresentationSupport`](/API/GLFW/glfwGetPhysicalDevicePresentationSupport.html)
to
check whether a queue family of a physical device supports image
presentation.

returns

:    `int` `GLFW_TRUE` if Vulkan is minimally available, or `GLFW_FALSE`
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