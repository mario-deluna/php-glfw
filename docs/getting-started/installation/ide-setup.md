<div class="grid cards" markdown>

-   :fontawesome-brands-linux:{ .lg .middle } __Install on Linux__

    ---

    [:octicons-arrow-right-24: Linux Installation](./install-linux.md)

-   :fontawesome-brands-apple:{ .lg .middle } __Install on MacOS__

    ---

    [:octicons-arrow-right-24: MacOS Installation](./install-macos.md)

-   :fontawesome-brands-windows:{ .lg .middle } __Install on Windows__

    ---

    [:octicons-arrow-right-24: Windows Installation](./install-windows.md)
</div>


# PHP-GLFW IDE Setup

Once the extension is installed, everything works at runtime, but your editor is still in the dark. PHP-GLFW ships as a compiled C extension, so classes like `GL\Math\Vec3`, functions like `glClear`, and constants like `GL_COLOR_BUFFER_BIT` never appear in any `.php` file your IDE can read. Static analysis has nothing to look at, which means no auto-completion, no parameter hints, and no documentation on hover.

The fix is to hand your IDE a set of *stubs*: plain PHP files that declare the whole API with full docblocks, purely so your editor can index them. This page walks you through it.

## Stubs

Since PHP-GLFW is a PHP extension, your editor / IDE may not support auto-completion and doc lookups without some help.
To address this, we have created a composer package that you can include as a dev dependency to have full support:

```bash
composer require --dev phpgl/ide-stubs
```

The package is a single `phpglfw.php` file: thousands of empty class, method, function, and constant declarations that mirror the real extension, each carrying the same docblock you see in the reference docs. Your IDE indexes it like any other source file and lights up completion from there.

!!! note

    The stubs are a **dev-only** dependency. They are never autoloaded and never executed at runtime, they exist solely for your editor. Installing or removing them has no effect on how your program runs.

## Visual Studio Code

VS Code needs a PHP language server to make sense of the stubs. Install either [PHP Intelephense](https://marketplace.visualstudio.com/items?itemName=bmewburn.vscode-intelephense-client) or the official [PHP extension](https://marketplace.visualstudio.com/items?itemName=vscode.php), then run the composer command above.

Because the stubs live under `vendor/`, the language server picks them up automatically once the package is installed, there is nothing to configure. Start typing `GL\Math\` or `glfw` and the completions appear.

!!! tip

    If completion does not show up right away, reload the window (`Cmd/Ctrl + Shift + P` -> **Developer: Reload Window**) so the analyzer re-indexes `vendor/`.

## PhpStorm

PhpStorm indexes your project's `vendor/` directory out of the box, so after running `composer require --dev phpgl/ide-stubs` the completions and hover docs are available immediately.

!!! tip

    If PhpStorm keeps showing "undefined" warnings for GL functions after the install, clear the caches with **File -> Invalidate Caches / Restart -> Invalidate and Restart** to force a fresh re-index.

## Without Composer

Not every project uses Composer, and that is fine. You can point your IDE at the stub file directly:

1. Grab [`stubs/phpglfw.php`](https://github.com/mario-deluna/php-glfw/blob/master/stubs/phpglfw.php) from the repository.
2. Drop it anywhere inside your project, for example a top-level `stubs/` folder.

Both VS Code and PhpStorm index files in your project tree, so the moment the file lands in the workspace you get the same completion and documentation.

!!! warning

    Keep the standalone stub file out of your runtime include path. It only declares empty symbols, so loading it alongside the real extension would clash with the actual definitions. Storing it in a folder your IDE reads but your application never `require`s keeps the two apart.

## Verifying it works

Open any PHP file in your project and start a snippet like this:

```php
$vec = new GL\Math\Vec3(1, 2, 3);
$vec-> // completion should list length(), normalize(), dot(), ...
```

If you see the method list pop up, and hovering a symbol shows its documentation, you are all set. Your program still runs against the real extension exactly as before, the stubs only ever teach your editor.
