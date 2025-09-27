---
applyTo: '**'
---

## Most Important!!!

 - !!!!Always begin single line comments with a lowercase letter!!!!
 - Never change arginfo.h directly, always use the generator tool to update it!
 - arginfo is being built via the stubs in `generator/templates/phpglfw.stub.php.php`
 - There are two stub files, one for the generation of the c code, the other for the php ide stubs.
   - `generator/templates/phpglfw.stub.php.php` (C code, plain func declarations, no docblocks etc.)
   - `generator/templates/stubs/phpglfw.php.php` (PHP stubs, contain docblock documentation and comments etc.)

## Architecture Overview

PHP-GLFW is a PHP extension that provides comprehensive bindings for GLFW (windowing) and OpenGL, plus additional graphics utilities. The extension is structured as multiple C modules that expose PHP classes and functions.

Most of these C files are generated via the `generator/` tool.

## Very Very Important!!!:

So always double check if there is a template file under `generator/templates/` before modifing a .c file directly!

## Component Guidelines

When modifying core components, follow these guidelines to ensure consistency and proper code generation:

### Generated Components (edit PHP templates, then regenerate)

 - **GLFW & OpenGL Bindings**: 
    - Edit `generator/templates/phpglfw_functions.c.php` 
    - Edit `generator/templates/phpglfw_functions.h.php`
    - Edit `generator/templates/phpglfw_constants.c.php` 
    - Edit `generator/templates/phpglfw_constants.h.php`
 - **Buffer Objects**: 
    - Edit `generator/templates/phpglfw_buffer.c.php` 
    - Edit `generator/templates/phpglfw_buffer.h.php`
 - **Math Library**:
    - Edit `generator/templates/phpglfw_math.c.php` 
    - Edit `generator/templates/phpglfw_math.h.php`
 - **NanoVG Bindings**:
    - Edit `generator/templates/phpglfw_nanovg.c.php` 
    - Edit `generator/templates/phpglfw_nanovg.h.php`
 - **PHP Extension Stubs**:
    - Edit `generator/templates/phpglfw.stub.php.php` for C code generation (arginfo, etc..)
 - **PHP IDE Stubs**:
    - Edit `generator/templates/stubs/phpglfw.php.php` for IDE support (docblocks, comments, etc..)

### Direct Edit Components (edit C files directly)

- **Texture Loading**: 
    - Edit `phpglfw_texture.c` directly, 
    - update both stubs template files. 
- **Geometry Parser**: 
    - Edit `phpglfw_objparser.c` directly
    - update both stubs template files.
- **Audio System**:
    - Edit `phpglfw_audio.c` directly
    - update both stubs template files.

### Special Cases
- **Glad** (`vendor/glad/`): Generated via glad library - do not edit manually

**Important**: Always update the corresponding PHP stubs in `generator/templates/stubs/phpglfw.php.php` for IDE support when adding new functions or classes and `generator/templates/phpglfw.stub.php.php` for arginfo generation.

**Regenerate bindings:**
```bash
php generator/build
```

### Build System

The extension uses GNU autotools with a complex `configure.ac` that:
- Detects platform (Linux/MacOS) and builds appropriate GLFW backends
- Bundles GLFW as a submodule if not found system-wide
- Links multiple C libraries (GLFW, glad, nanovg, stb, fastobj, miniaudio)
- Generates platform-specific compilation flags

**Build commands:**
```bash
sudo phpize && sudo ./configure --enable-glfw && make && sudo make install
```

## Development Workflow

### Testing

- **Unit Tests**: PHPUnit in `tests/` directory with subdirs for each module
- **Integration Tests**: Examples in `examples/` serve as integration tests
- **CI Matrix**: GitHub Actions tests across PHP 8.1-8.4 on Ubuntu/macOS/Windows

**Run tests:**
```bash
composer install
./vendor/bin/phpunit
```

### Example Patterns

All examples follow consistent patterns using `ExampleHelper` class:

```php
use GL\Buffer\FloatBuffer;
use GL\Math\Vec3;

// Initialize GLFW window
$window = ExampleHelper::begin();

// Create vertex buffers
$vertices = new FloatBuffer([/* vertex data */]);
glGenVertexArrays(1, $VAO);
glBindVertexArray($VAO);
// ... buffer setup ...

// Main render loop
while (!glfwWindowShouldClose($window)) {
    glClear(GL_COLOR_BUFFER_BIT);
    // ... render code ...
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);
```

### Common Gotchas

- **Context Management**: Always call `glfwMakeContextCurrent($window)` before GL operations
- **Buffer Objects**: Use `FloatBuffer`/`IntBuffer` for GPU data - they're more efficient than PHP arrays
- **Math Operations**: Vec3/Mat4 support operator overloading: `$result = $vec1 + $vec2`
- **Platform Differences**: MacOS requires `GLFW_OPENGL_FORWARD_COMPAT` and specific context hints
- **Extension Loading**: Add `extension="glfw.so"` to `php.ini` after installation

### Debugging

- **OpenGL Errors**: Check `glGetError()` after GL calls
- **Build Issues**: Ensure GLFW headers/libs are available or let configure build them
- **Memory Leaks**: Buffer objects are managed - don't manually free them
- **Shader Debugging**: Use `glGetShaderInfoLog()` for compilation errors

### File Organization

- `phpglfw_*.c`: Individual module implementations
- `vendor/`: Bundled C libraries (GLFW, glad, stb, nanovg, etc.)
- `examples/`: Working demos showcasing features
- `tests/`: PHPUnit test suites for each module
- `stubs/`: PHP interface definitions for IDE support
- `generator/`: OpenGL & extension binding code generator

### Contribution Guidelines

- **New Features**: Add to appropriate `phpglfw_*.c` file and update stubs
- **OpenGL Functions**: Use generator tool, don't manually add bindings
- **Examples**: Follow `ExampleHelper` pattern, add to `examples/` with descriptive names
- **Tests**: Add PHPUnit tests in corresponding `tests/` subdirectories
- **Documentation**: Update `docs/` and ensure examples are well-commented</content>
<parameter name="filePath">/Users/mariodoring/Developer/Labs/php-glfw/.github/copilot-instructions.md