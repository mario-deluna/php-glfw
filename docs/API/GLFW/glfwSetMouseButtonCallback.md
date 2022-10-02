# glfwSetMouseButtonCallback
This function sets the mouse button callback of the specified window, which
is called when a mouse button is pressed or released.

```php
function glfwSetMouseButtonCallback(\GLFWwindow $window, callable $callback) : void
```

Example:
```php
glfwSetMouseButtonCallback($window, function($button, $action, $mods) {
    if ($button == GLFW_MOUSE_BUTTON_LEFT && $action == GLFW_PRESS) {
        echo "Left mouse button pressed" . PHP_EOL;
    }
});
```

When a window loses input focus, it will generate synthetic mouse button
release events for all pressed mouse buttons. You can tell these events from
user-generated events by the fact that the synthetic ones are generated after
the focus loss event has been processed, i.e. after the window focus callback
has been called.

arguments

:    1. `\GLFWwindow` `$window` The window whose callback to set.
    2. `callable` `$callback` 

returns

:    `void` 

---
     

!!! cite "Copyright"

    This documentation page is prased from the `glfw3.h` header file, and only modified to fit 
    the PHP-GFLW extension bindings. The original documentation copyright is as follows:

    ```
    Copyright (c) 2002-2006 Marcus Geelnard
    Copyright (c) 2006-2019 Camilla Löwy
    https://www.glfw.org/license
    ```