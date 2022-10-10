<?php
/**
 * This example renders the Crytek Sponza scene. 
 */
require __DIR__ . '/99_example_helpers.php';

use GL\Math\{Vec3, Vec4, Mat4, Vec2};
use GL\Buffer\FloatBuffer;


$window = ExampleHelper::begin();


/**
 * Downloading the sponza scene
 * 
 * ----------------------------------------------------------------------------
 */

// ensure zip extension is loaded
if (!extension_loaded('zip')) {
    throw new \Exception('The zip extension is required to run this example');
}

// ensure the curl extension is loaded
if (!extension_loaded('curl')) {
    throw new \Exception('The curl extension is required to run this example');
}

// download and extract the sponza scene if not downloaded yet
$sponzaDir = __DIR__ . '/sponza';
$sponzaPath = $sponzaDir . '/Sponza-master';
if (!is_dir($sponzaDir)) {
    echo "Downloading Sponza scene...\n";
    $sponzaZip = __DIR__ . '/sponza.zip';
    file_put_contents($sponzaZip, fopen("https://github.com/jimmiebergmann/Sponza/archive/refs/heads/master.zip", 'rb'));

    echo "Extracting Sponza scene...\n";
    $zip = new ZipArchive();
    $zip->open($sponzaZip);
    $zip->extractTo($sponzaDir);
    $zip->close();

    // remove the zip file
    unlink($sponzaZip);

    // check if download was successfully
    if (!file_exists($sponzaPath . '/sponza.obj')) {
        throw new \Exception('Failed to download Sponza scene');
    }

    // patch the sponza.mtl file to use the correct texture keywords
    // the material currently uses `map_Disp` instead of `map_bump` for the normal map
    // which is not supported by the ObjFileParser class.
    echo "Patching Sponza scene material...\n";
    $mtl = file_get_contents($sponzaPath . '/sponza.mtl');
    $mtl = str_replace('map_Disp', 'map_bump', $mtl);
    file_put_contents($sponzaPath . '/sponza.mtl', $mtl);

    echo "Done!\n";
}


/**
 * Loading the scene files
 * 
 * ----------------------------------------------------------------------------
 */
echo "Loading Sponza scene...\n";
$mesh = new \GL\Geometry\ObjFileParser($sponzaPath . '/sponza.obj');

// extract the meshes foreach material 
// in this example we only care about the position data, so we pass 'p' as the second argument.
$meshes = $mesh->getMeshes('pnctb');

echo "Uploading Sponza scene to GPU...\n";

// generate a vertex buffer for each mesh
$vertexBuffers = [];
foreach ($meshes as $i => $mesh) {
   
    echo "Uploading mesh #". $i ." with " . $mesh->vertices->size() . " vertices...\n";

    // create a vertex array object and upload the vertices
    glGenVertexArrays(1, $VAO);
    glGenBuffers(1, $VBO);

    glBindVertexArray($VAO);
    glBindBuffer(GL_ARRAY_BUFFER, $VBO);
    glBufferData(GL_ARRAY_BUFFER, $mesh->vertices, GL_STATIC_DRAW);

    // declare the vertex attributes
    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 14, 0);
    glEnableVertexAttribArray(0);

    // normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 14, GL_SIZEOF_FLOAT * 3);
    glEnableVertexAttribArray(1);

    // texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 14, GL_SIZEOF_FLOAT * 6);
    glEnableVertexAttribArray(2);

    // tangent
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 14, GL_SIZEOF_FLOAT * 8);
    glEnableVertexAttribArray(3);

    // bitangent
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 14, GL_SIZEOF_FLOAT * 11);
    glEnableVertexAttribArray(4);

    // load the textures for this mesh
    // and upload them to the GPU aswell
    $diffuseTexture = null;
    if ($mesh->material->diffuseTexture && file_exists($mesh->material->diffuseTexture->path)) {
        echo "loading diffuse texture: " . $mesh->material->diffuseTexture->name . "\n";
        $diffuseTexture = ExampleHelper::loadTexture($mesh->material->diffuseTexture->path);
    }

    $normalTexture = null;
    if ($mesh->material->bumpTexture && file_exists($mesh->material->bumpTexture->path)) {
        echo "loading normal map: " . $mesh->material->bumpTexture->name . "\n";
        $normalTexture = ExampleHelper::loadTexture($mesh->material->bumpTexture->path);
    }

    $alphaTexture = null;
    if ($mesh->material->dissolveTexture && file_exists($mesh->material->dissolveTexture->path)) {
        echo "loading alpha map: " . $mesh->material->dissolveTexture->name . "\n";
        $alphaTexture = ExampleHelper::loadTexture($mesh->material->dissolveTexture->path);
    }

    $vertexBuffers[] = [
        'VAO' => $VAO,
        'VBO' => $VBO,
        'count' => $mesh->vertices->size() / 3,

        'textureDiffuse' => $diffuseTexture,
        'textureNormal' => $normalTexture,
        'textureAlpha' => $alphaTexture,
    ];
}

// unbind
glBindBuffer(GL_ARRAY_BUFFER, 0); 
glBindVertexArray(0); 


/**
 * Build Shaders
 * 
 * ----------------------------------------------------------------------------
 */

// compile a simple shader to project the cube 
// and output the uv colors to the fragment shader
$objectShader = ExampleHelper::compileShader(<<< 'GLSL'
#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcords;
layout (location = 3) in vec3 a_tangent;
layout (location = 4) in vec3 a_bitangent;

out vec3 v_normal;
out vec2 v_texcords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // we need to transform the normal vector to world space
    v_normal = vec3(model * vec4(a_normal, 1.0f));
    v_texcords = a_texcords;
    gl_Position = projection * view * model * vec4(a_position, 1.0f);
}
GLSL,
<<< 'GLSL'
#version 330 core
out vec4 fragment_color;

in vec3 v_normal;
in vec2 v_texcords;

uniform sampler2D texture_diffuse;

uniform vec3 light_dir;
uniform vec3 light_color;

uniform float ambient = 0.5;

void main()
{
    // simple lighting
    float diffuse = max(dot(v_normal, light_dir), 0.0);
    vec3 color = (ambient + diffuse) * light_color * texture(texture_diffuse, v_texcords).rgb;
    fragment_color = vec4(color, 1.0f);
} 
GLSL);


/**
 * Camera & Controls
 * 
 * ----------------------------------------------------------------------------
 */
// view matrix, this is the camera / eye position and rotation
$view = new Mat4;
$view->translate(new Vec3(0.0, 200.0, -6));

$projection = new Mat4;
$projection->perspective(glm::radians(70.0), ExampleHelper::WIN_WIDTH / ExampleHelper::WIN_HEIGHT, 0.1, 10000.0);

// capture keyboard events to toggle rendering modes
$wireframe = false;
glfwSetKeyCallback($window, function ($key, $scancode, $action, $mods) use ($window, &$wireframe) {
    if ($key == GLFW_KEY_ESCAPE && $action == GLFW_PRESS) {
        glfwSetWindowShouldClose($window, true);
    }

    if ($key == GLFW_KEY_W && $action == GLFW_PRESS) {
        $wireframe = !$wireframe;
    }
});

// capture mouse events to move the camara around
$lastX = ExampleHelper::WIN_WIDTH / 2;
$lastY = ExampleHelper::WIN_HEIGHT / 2;
$firstMouse = true;

// camera rotation
$cameraRotation = new Vec2(0.0, 0.0);

glfwSetCursorPosCallback($window, function ($xpos, $ypos) use ($window, &$cameraRotation, &$lastX, &$lastY, &$firstMouse) {

    // only move the camera if the left mouse button is pressed
    if (glfwGetMouseButton($window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS) {
        glfwSetInputMode($window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        $firstMouse = true;
        return;
    }

    glfwSetInputMode($window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if ($firstMouse) {
        $lastX = $xpos;
        $lastY = $ypos;
        $firstMouse = false;
    }

    $xoffset = $xpos - $lastX;
    $yoffset = $lastY - $ypos;
    $lastX = $xpos;
    $lastY = $ypos; 

    // apply eular rotation
    $cameraRotation->x = $cameraRotation->x + $xoffset * 0.1;
    $cameraRotation->y = $cameraRotation->y - $yoffset * 0.1;
});


/**
 * Render the scene
 * 
 * ----------------------------------------------------------------------------
 */

// print some help to the console
echo str_repeat('-', 80) . PHP_EOL;
echo '-> Use the mouse to rotate the object' . PHP_EOL;
echo '-> Press ESC to close the window' . PHP_EOL;
echo '-> Press W to toggle wireframe mode' . PHP_EOL;
echo str_repeat('-', 80) . PHP_EOL;

// update the viewport
glViewport(0, 0, ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT);

// enable depth testing, because we are rendering a 3d object with overlapping
// triangles
glEnable(GL_DEPTH_TEST);

// Main Loop
// ---------------------------------------------------------------------------- 
while (!glfwWindowShouldClose($window))
{
    glClearColor(0, 0, 0, 1);
    // note how we are clearing both the DEPTH and COLOR buffers.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the shader, will active the given shader program
    // for the coming draw calls.
    glUseProgram($objectShader);

    // define the model matrix aka the object postion in the world
    $model = new Mat4;

    // reverse the view matrix, because we are moving the world
    // instead of the camera
    // copy the view matrix, because we need to modify it
    $eye = $view->copy();
    $eye->rotate(GLM::radians($cameraRotation->x), new Vec3(0.0, 1.0, 0.0));
    $eye->rotate(GLM::radians($cameraRotation->y), new Vec3(1.0, 0.0, 0.0));
    $eye->inverse();

    // now set the uniform variables in the shader.
    // note that we use `glUniformMatrix4f` instead of `glUniformMatrix4fv` to pass a single matrix.
    glUniformMatrix4f(glGetUniformLocation($objectShader, "model"), GL_FALSE, $model);
    glUniformMatrix4f(glGetUniformLocation($objectShader, "view"), GL_FALSE, $eye);
    glUniformMatrix4f(glGetUniformLocation($objectShader, "projection"), GL_FALSE, $projection);

    // set the light direction and color
    glUniform3f(glGetUniformLocation($objectShader, "light_dir"), 0.0, 0.7, 0.3);
    glUniform3f(glGetUniformLocation($objectShader, "light_color"), 1.0, 1.0, 1.0);

    // bind & draw the vertex array
    foreach($vertexBuffers as $vb) {
        // update the diffuse texture
        if ($vb['textureDiffuse']) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, $vb['textureDiffuse']);
            glUniform1i(glGetUniformLocation($objectShader, "texture_diffuse"), 0);
        } else {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        if ($wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        // draw the vertex array
        glBindVertexArray($vb['VAO']);
        glDrawArrays(GL_TRIANGLES, 0, $vb['count']);
    }

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}


// stop & cleanup
foreach($vertexBuffers as $vb) {
    glDeleteBuffers(1, $vb['VBO']);
    glDeleteVertexArrays(1, $vb['VAO']);
}

ExampleHelper::stop($window);