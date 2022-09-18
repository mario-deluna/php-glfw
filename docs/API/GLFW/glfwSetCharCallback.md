# glfwSetCharCallback
This function sets the character callback of the specified window, which is
called when a Unicode character is input.

```php
function glfwSetCharCallback(\GLFWwindow $window, callable $callback) : void
```

Example:
```php
glfwSetCharCallback($window, function($codepoint) {
    echo "Character: " . mb_chr($codepoint) . PHP_EOL;
});
```

The character callback is intended for Unicode text input. As it deals with
characters, it is keyboard layout dependent, whereas the key callback is not.
Characters do not map 1:1 to physical keys, as a key may produce zero, one or
more characters. If you want to know whether a specific physical key was
pressed or released, see the key callback instead.

The character callback behaves as system text input normally does and will
not be called if modifier keys are held down that would prevent normal text
input on that platform, for example a Super (Command) key on macOS or Alt key
on Windows.

arguments

:    1. `\GLFWwindow` `$window` 
    2. `callable` `$callback` 

returns

:    `void` 

---
     