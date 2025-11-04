!!! warning
    The parser expects fully triangulated meshes. Convert quads or n-gons inside your DCC tool before exporting, otherwise the import will fail.

# Wavefront Object Files

[`GL\Geometry\ObjFileParser`](/API/Geometry/ObjFileParser.html) lets you pull Wavefront `.obj` assets straight into your PHP runtime. This page walks you through loading a model, shaping the vertex layout you need, handling materials, and producing indexed meshes that drop into your renderer.

- Keep your `.mtl` files beside the `.obj`, since materials resolve paths relative to the model.
- Want a quick demo? Run the example:

```bash
php examples/05_objloading.php
```

<figure markdown>
![PHP 3D Boat Wireframe](./../../docs-assets/php-glfw/user_guide/3d_obj/boat_wireframe.png){ width="600" }
</figure>

## Loading Models

Creating the parser is the only setup step. Point it at a file path, and it opens a shared resource that keeps vertex data, indices, and materials in native memory.

```php
use GL\Geometry\ObjFileParser;

$parser = new ObjFileParser(__DIR__ . '/my_asset.obj');

printf("Loaded %d materials\n", count($parser->materials));
printf("Loaded %d groups\n", count($parser->groups));
printf("Loaded %d objects\n", count($parser->objects)); 
```

Will print something like:

```
Loaded 5 materials
Loaded 1 groups
Loaded 19 objects
```

## Vertex Layouts

[`getVertices`](/API/Geometry/ObjFileParser.html#getvertices) returns a [`FloatBuffer`](/API/Buffer/FloatBuffer.html). You can control the what attributes are included into the buffer by passing a layout string. Each **character** becomes a **vertex attribute** in the order provided.

```php
$vertices = $parser->getVertices('pntbc', $specifcGroup); // <- pass layout
```

| Token | Components | Description |
|-------|------------|-------------|
| `p`   | 3          | Position `(x, y, z)` |
| `n`   | 3          | Normal from the file |
| `N`   | 3          | Generated flat normal |
| `c`   | 2          | Texture coordinates `(u, v)` |
| `t`   | 3          | Generated tangent |
| `b`   | 3          | Generated bitangent |

!!! tip
    Tangents, bitangents and flat normals are **generated on demand**. 

Examples:

 - `pnc` yields `[px, py, pz, nx, ny, nz, u, v, ...]`.
 - `p` yields just positions `[px, py, pz, ...]`.
 - `pN` yields positions and flat normals `[px, py, pz, nfx, nfy, nfz, ...]`.
 - etc..

### Uploading to OpenGL

The returned buffer object can then be uploaded to your GPU, when using VISU we have a convenient class to handle this for us:

=== "VISU"

    ```php
    use VISU\Graphics\BasicVertexArray;

    // fetch all vertices
    $vertices = $parser->getVertices('pnc'); // <- note the 'pnc' layout

    // create a basic vertex array [px, py, pz, nx, ny, nz, u, v] aka [3, 3, 2]
    $vao = new BasicVertexArray($gl, [3, 3, 2]);
    $vao->upload($vertices);
    ```

=== "PHP-GLFW"

    ```php
    // fetch all vertices
    $vertices = $parser->getVertices('pnc');

    // build OpenGL VAO/VBO
    // [position (3), normal (3), texcoord (2)]
    $stride = 3 + 3 + 2; // floats per vertex

    // create & bind buffers
    $vao = glGenVertexArrays(1);
    $buffer = glGenBuffers(1);

    glBindVertexArray($vao);
    glBindBuffer(GL_ARRAY_BUFFER, $buffer);
    glBufferData(GL_ARRAY_BUFFER, $vertices, GL_STATIC_DRAW);

    // setup vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, $stride * GL_SIZEOF_FLOAT, 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, $stride * GL_SIZEOF_FLOAT, 3 * GL_SIZEOF_FLOAT);
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, $stride * GL_SIZEOF_FLOAT, 6 * GL_SIZEOF_FLOAT);
    glEnableVertexAttribArray(2);
    ```

Leave the `$group` argument empty to merge the entire file. Supply a [`Group`](/API/Geometry/ObjFileParserGroup.html) from `$parser->groups` or `$parser->objects` when you only want the geometry for a single section.

## Working With Materials

[`getMeshes()`](/API/Geometry/ObjFileParser.html#getmeshes) slices the model by [Material](/API/Geometry/ObjFileParserMaterial.html) and returns an array of [`Mesh`](/API/Geometry/ObjFileParserMesh.html) objects. Each mesh bundles everything you need to draw: a vertex buffer, an optional index buffer, a material descriptor, and an axis-aligned bounding box.

```php
$meshes = $parser->getMeshes('pnc'); // <- pass layout

foreach ($meshes as $mesh) {
    $material = $mesh->material;
    echo $material->name . "\n";
    echo str_repeat("-", strlen($material->name)) . "\n";

    if ($material) {
        echo "  Diffuse color: " .  $material->diffuse . "\n";
        echo "  Specular color: " .  $material->specular . "\n";
        $vertices = $mesh->vertices; // FloatBuffer
        // etc..
    }
    echo "\n";
}
```

Will print something like:

```
iron
----
  Diffuse color: vec3(0.3765, 0.3765, 0.3765)
  Specular color: vec3(0.25, 0.25, 0.25)

textile
-------
  Diffuse color: vec3(0.8196, 0.7529, 0.6706)
  Specular color: vec3(0.25, 0.25, 0.25)
```


Material properties mirror common MTL fields such as `ambient`, `diffuse`, `specular`, `shininess`, `dissolve`, and `illuminationModel`. Use them to drive your shader uniforms or to build the inputs for a lightweight PBR workflow.

Bounding boxes are available through `aabbMin` and `aabbMax` ([`Vec3`](/API/Math/Vec3.html)). They are perfect for quick frustum checks, simple collisions, or framing a camera before the first draw call.

## Groups and Objects

Wavefront files distinguish between `g` groups and `o` objects. The parser keeps both exposed through `$parser->groups` and `$parser->objects`, each providing `name`, `faceCount`, `faceOffset`, and `indexOffset`.
In php-glfw we consider both as [`Group`](/API/Geometry/ObjFileParserGroup.html) instances since they behave identically from a geometry extraction standpoint.

Groups allow you to partially access the model geometry. This is useful to:

- render only a subsection of a complex asset
- apply distinct transforms or materials per part

```php
// $parser->groups or $parser->objects
foreach ($parser->groups as $group) {
    printf("Group %s spans %d faces\n", $group->name, $group->faceCount);
    $buffer = $parser->getVertices('p', $group);
}
```

## Putting It All Together

The following example is going to use [`VISU`](https://visu.phpgl.net), as making a plain OpenGL example would be too verbose and contain 90% boilerplate code.

!!! hint "VISU Note"

    The examples below expect you to have [`VISU`](https://visu.phpgl.net) available.

    Install VISU via Composer if you haven't already:

    ```bash
    composer require phpgl/visu
    ```

    Create a new PHP file (e.g. `example.php`) and add the following code:

    ```php
    <?php

    use VISU\Quickstart;
    use VISU\Quickstart\{QuickstartApp, QuickstartOptions};
    use VISU\Graphics\RenderTarget;
    use VISU\Graphics\Rendering\RenderContext;

    require __DIR__ . '/vendor/phpgl/visu/bootstrap_inline.php';

    $quickstart = new Quickstart(function(QuickstartOptions $options)
    {
        $options->ready = function(QuickstartApp $app) {
            // initialize
        };

        $options->draw = function(QuickstartApp $app, RenderContext $renderContext, RenderTarget $renderTarget) {
            // draw loop
        };
    });

    $quickstart->run();
    ```

    Running this will open a window with an OpenGL context and a basic render loop.


So first as usual we create a parser instance and load an obj file:

```php
use GL\Geometry\ObjFileParser;

$parser = new ObjFileParser(__DIR__ . '/assets/ship.obj');
```

### Building a Buffer

Next we build a vertex buffer with the positions of our mesh and collect material infos like the diffuse color:

So that we do not have to deal with multiple buffers for each mesh, we create a single large vertex buffer and append each mesh's vertices to it. That way we also don't have to re-bind multiple buffers when rendering.

```php
$vertexBuffer = new FloatBuffer();
$vertexOffset = 0;
$objects = [];
foreach($parser->getMeshes('p') as $mesh) 
{
    // append the mesh vertices to the main buffer
    $vertexBuffer->append($mesh->vertices);

    // every vertex has 3 floats (x, y, z)
    $vertexCount = $mesh->vertices->size() / 3;

    // store the object info
    $objects[] = [
        'vertexOffset' => $vertexOffset,
        'vertexCount' => $vertexCount,
        'color' => $mesh->material->diffuse,
    ];

    // update the vertex offset for the next object
    $vertexOffset += $vertexCount;
}
```

`$vertexBuffer` now contains all vertices of the entire model, while `$objects` holds the necessary info to render each mesh separately. Which we want to do so that we can apply the correct material color.

### Uploading to GPU

Now we need to upload the vertex buffer to the GPU. So that we can render it, for simple buffers VISU provides the `BasicVertexArray` class which wraps a VAO and VBO for us:

```php
$vao = new BasicVertexArray($gl, [3]);
$vao->upload($vertexBuffer);
```

### Rendering the objects

Then in the render loop we bind the VAO and draw each object separately, applying the correct color uniform before each draw call:

```php
// bind the VAO
$vao->bind();

// draw each object
foreach($state->objects as $object)
{
    $shader->setUniformVec3("u_color", $object['color']);
    $vao->draw($object['vertexOffset'], $object['vertexCount']);
}
```

### Full Example

All of the above combined into into a full example looks like this:

```php
<?php

use GL\Buffer\FloatBuffer;
use GL\Math\{Mat4, Vec3};
use VISU\Graphics\{BasicVertexArray, RenderTarget, ShaderProgram, ShaderStage};
use VISU\Graphics\Rendering\RenderContext;
use VISU\Quickstart;
use VISU\Quickstart\{QuickstartApp, QuickstartOptions};

require __DIR__ . '/vendor/phpgl/visu/bootstrap_inline.php';

class ExampleState {
    public ShaderProgram $shader;
    public BasicVertexArray $vao;
    public FloatBuffer $vertexBuffer;
    public array $objects = [];
};

$state = new ExampleState();

$quickstart = new Quickstart(function(QuickstartOptions $options) use($state)
{   
    $options->ready = function(QuickstartApp $app) use($state)
    {
        $parser = new \GL\Geometry\ObjFileParser(__DIR__ . '/ship_light.obj');

        $state->objects = [];
        $state->vertexBuffer = new FloatBuffer();
        $vertexOffset = 0;
        foreach($parser->getMeshes('p') as $mesh) 
        {
            // append the mesh vertices to the main buffer
            $state->vertexBuffer->append($mesh->vertices);

            // every vertex has 3 floats (x, y, z)
            $vertexCount = $mesh->vertices->size() / 3;

            // store the object info
            $state->objects[] = [
                'vertexOffset' => $vertexOffset,
                'vertexCount' => $vertexCount,
                'color' => $mesh->material->diffuse,
            ];

            // update the vertex offset for the next object
            $vertexOffset += $vertexCount;
        }

        // now create the VAO
        $state->vao = new BasicVertexArray($app->gl, [3]);
        $state->vao->upload($state->vertexBuffer);

        // create the shader program
        $state->shader = new ShaderProgram($app->gl);
        $state->shader->attach(ShaderStage::vertex(<<<GLSL
        #version 330 core

        layout(location = 0) in vec3 a_pos;

        uniform mat4 u_proj_matrix;
        uniform mat4 u_view_matrix;
        uniform mat4 u_model_matrix;

        void main()
        {
            gl_Position = u_proj_matrix * u_view_matrix * u_model_matrix * vec4(a_pos, 1.0);
        }
        GLSL
        ));

        $state->shader->attach(ShaderStage::fragment(<<<GLSL
        #version 330 core
        out vec4 fragment_color;
        uniform vec3 u_color;
        void main()
        {
            fragment_color = vec4(u_color, 1.0);
        }
        GLSL
        ));
        $state->shader->link();
    };

    $options->draw = function(QuickstartApp $app, RenderContext $renderContext, RenderTarget $renderTarget) use($state)
    {
        // clear the screen
        $renderTarget->framebuffer()->clear();

        // enable depth testing
        glEnable(GL_DEPTH_TEST);

        // bind the VAO
        $state->vao->bind();
        $state->shader->use();

        // set up the camera matrices
        $aspectRatio = $renderTarget->width() / $renderTarget->height();
        $projMatrix = new Mat4();
        $projMatrix->perspective(45.0, $aspectRatio, 0.1, 100.0);
        $viewMatrix = new Mat4();
        $viewMatrix->translate(new Vec3(0.0, -5.0, -15.0));
        $modelMatrix = new Mat4();
        $modelMatrix->rotate(glfwGetTime() * 0.5, new Vec3(0.0, 1.0, 0.0));

        $state->shader->setUniformMat4("u_proj_matrix", false, $projMatrix);
        $state->shader->setUniformMat4("u_view_matrix", false, $viewMatrix);
        $state->shader->setUniformMat4("u_model_matrix", false, $modelMatrix);

        // draw each object
        foreach($state->objects as $object)
        {
            $state->shader->setUniformVec3("u_color", $object['color']);
            $state->vao->draw($object['vertexOffset'], $object['vertexCount']);
        }
    };
});

$quickstart->run();
```