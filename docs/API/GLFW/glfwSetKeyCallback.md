# glfwSetKeyCallback
This function sets the key callback of the specified window, which is called
when a key is pressed, repeated or released.

```php
function glfwSetKeyCallback(\GLFWwindow $window, callable $callback) : void
```

Example:
```php
glfwSetKeyCallback($window, function($key, $scancode, $action, $mods)
use($window) {
	if ($key == GLFW_KEY_ESCAPE && $action == GLFW_PRESS) {
		glfwSetWindowShouldClose($window, GL_TRUE);
	}
});
```

The key functions deal with physical keys, with layout independent key tokens
named after their values in the standard US keyboard layout. If you want to
input text, use the character callback instead.

When a window loses input focus, it will generate synthetic key release
events for all pressed keys. You can tell these events from user-generated
events by the fact that the synthetic ones are generated after the focus loss
event has been processed, i.e. after the window focus callback has been
called.

The scancode of a key is specific to that platform or sometimes even to that
machine. Scancodes are intended to allow users to bind keys that don't have a
GLFW key token. Such keys have key set to GLFW_KEY_UNKNOWN, their state is
not saved and so it cannot be queried with glfwGetKey.

Sometimes GLFW needs to generate synthetic key events, in which case the
scancode may be zero.

arguments

:    1. `\GLFWwindow` `$window` 
    2. `callable` `$callback` 

---
     