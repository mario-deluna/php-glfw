<?php
/**
 * This example will open a window and draw a 3D cube in it.
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/99_example_helpers.php';

use GL\Math\{Vec3, Vec4, Mat4};
use GL\Buffer\FloatBuffer;

// ensure zip extension is loaded
if (!extension_loaded('zip')) {
    throw new \Exception('The zip extension is required to run this example');
}

$window = ExampleHelper::begin();

// compile a simple shader to project the cube 
// and output the uv colors to the fragment shader
$objectShader = ExampleHelper::compileShader(<<< 'GLSL'
#version 330 core
layout (location = 0) in vec3 a_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(a_position, 1.0f);
}
GLSL,
<<< 'GLSL'
#version 330 core
out vec4 fragment_color;

uniform vec3 color;

void main()
{
    fragment_color = vec4(color, 1.0f);
} 
GLSL);

// you can ignore the next few lines till line 49, they simply extract the compressed ship_light file 
// if not extracted yet to save storage space in the repository.
if (!file_exists(__DIR__ . '/ship_light.obj')) {
    $zip = new ZipArchive();
    $zip->open(__DIR__ . '/ship_light.obj.zip');
    $zip->extractTo(__DIR__);
    $zip->close();
}

// load an object file with the ObjFileParser class, the assest we are loading 
// is downloaded from kenney.nl, he provides a bunch of low poly free to use assets.
$mesh = new \GL\Geometry\ObjFileParser(__DIR__ . '/ship_light.obj');

// extract the meshes foreach material 
// in this example we only care about the position data, so we pass 'p' as the second argument.
$meshes = $mesh->getMeshes('p');

// generate a vertex buffer for each mesh
$vertexBuffers = [];
foreach ($meshes as $mesh) {
    
    // create a vertex array object and upload the vertices
    glGenVertexArrays(1, $VAO);
    glGenBuffers(1, $VBO);

    glBindVertexArray($VAO);
    glBindBuffer(GL_ARRAY_BUFFER, $VBO);
    glBufferData(GL_ARRAY_BUFFER, $mesh->vertices, GL_STATIC_DRAW);

    // declare the vertex attributes
    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 3, 0);
    glEnableVertexAttribArray(0);

    $vertexBuffers[] = [
        'VAO' => $VAO,
        'VBO' => $VBO,
        'color' => $mesh->material->diffuse,
        'count' => $mesh->vertices->size() / 3,
    ];
}

// unbind
glBindBuffer(GL_ARRAY_BUFFER, 0); 
glBindVertexArray(0); 

// update the viewport
glViewport(0, 0, ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT);

// enable depth testing, because we are rendering a 3d object with overlapping
// triangles
glEnable(GL_DEPTH_TEST);

// capture keyboard events to toggle rendering modes
$wireframe = false;
glfwSetKeyCallback($window, function ($key, $scancode, $action, $mods) use (&$wireframe, $window) {
    if ($key == GLFW_KEY_ESCAPE && $action == GLFW_PRESS) {
        glfwSetWindowShouldClose($window, true);
    }

    if ($key == GLFW_KEY_W && $action == GLFW_PRESS) {
        $wireframe = !$wireframe;
    }
});

// print some help to the console
echo str_repeat('-', 80) . PHP_EOL;
echo '-> Press ESC to close the window' . PHP_EOL;
echo '-> Press W to toggle wireframe mode' . PHP_EOL;
echo str_repeat('-', 80) . PHP_EOL;

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

    // define the model matrix aka the cubes postion in the world
    $model = new Mat4;
    // because we want the cube to spin, we rotate the matrix based
    // on the elapsed time.
    $model->rotate(glfwGetTime() * 0.5, new Vec3(0.0, 1.0, 0.0));
    // $model->rotate(glfwGetTime() * 2, new Vec3(0.0, 0.0, 1.0));

    // next the view matrix, this is the camera / eye position and rotation
	$view = new Mat4;
    // you can imagine the camera is beeing moved back by 2 units here.
    $view->translate(new Vec3(0.0, -3.0, -6));
    // $view->translate(new Vec3(0.0, -1.0, -3));

    // and finally the projection matrix, this is the perspective matrix.
	$projection = new Mat4;
	$projection->perspective(glm::radians(70.0), ExampleHelper::WIN_WIDTH / ExampleHelper::WIN_HEIGHT, 0.1, 10000.0);

    // now set the uniform variables in the shader.
    // note that we use `glUniformMatrix4f` instead of `glUniformMatrix4fv` to pass a single matrix.
    glUniformMatrix4f(glGetUniformLocation($objectShader, "model"), GL_FALSE, $model);
    glUniformMatrix4f(glGetUniformLocation($objectShader, "view"), GL_FALSE, $view);
    glUniformMatrix4f(glGetUniformLocation($objectShader, "projection"), GL_FALSE, $projection);

    // bind & draw the vertex array
    foreach($vertexBuffers as $vb) {
        // update the shader color
        glUniformVec3f(glGetUniformLocation($objectShader, "color"), $vb['color']);

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