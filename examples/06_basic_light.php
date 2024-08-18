<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/99_example_helpers.php';

use GL\Math\{GLM, Vec3, Vec4, Mat4};
use GL\Buffer\FloatBuffer;

$window = ExampleHelper::begin();

// compile a simple shader to project the cube 
// and output the uv colors to the fragment shader
$objectShader = ExampleHelper::compileShader(<<< 'GLSL'
#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

out vec3 v_normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // we need to transform the normal vector to world space
    v_normal = vec3(model * vec4(a_normal, 1.0f));
    gl_Position = projection * view * model * vec4(a_position, 1.0f);
}
GLSL,
<<< 'GLSL'
#version 330 core
out vec4 fragment_color;

in vec3 v_normal;

uniform vec3 mesh_color;
uniform vec3 light_dir;
uniform vec3 light_color;
uniform float ambient = 0.1;

void main()
{
    // simple lighting
    float diffuse = max(dot(v_normal, light_dir), 0.0);
    vec3 color = (ambient + diffuse) * light_color * mesh_color;
    fragment_color = vec4(color, 1.0f);
} 
GLSL);


// load the mesh just as in the example before
$shipObj = ExampleHelper::getShipObj();

// extract the meshes foreach material 
// in this example we also need the object normals to calculate the light direction
$meshes = $shipObj->getMeshes('pn');

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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 6, 0);
    glEnableVertexAttribArray(0);

    // normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 6, GL_SIZEOF_FLOAT * 3);
    glEnableVertexAttribArray(1);

    $vertexBuffers[] = [
        'VAO' => $VAO,
        'VBO' => $VBO,
        'color' => $mesh->material->diffuse,
        'count' => $mesh->vertices->size() / 6,
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

// in this example we let the user move the camera around
// or more accurately, we rotate the object
$rotation = 0.0;
$rotationVelocity = 2.0;
$lastMousePositionX = 0.0;

// print some help to the console
echo str_repeat('-', 80) . PHP_EOL;
echo '-> Use the mouse to rotate the object' . PHP_EOL;
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

    // define the model matrix aka the object postion in the world
    $model = new Mat4;
    
    // update rotation velcotiy based on user input 
    if (glfwGetMouseButton($window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
        glfwGetCursorPos($window, $mousePositionX, $mousePositionY);
        if ($lastMousePositionX != 0.0) {
            $diff = $mousePositionX - $lastMousePositionX;
            $rotationVelocity = $diff * 0.01;
        }
        $lastMousePositionX = $mousePositionX;
    } else {
        $rotationVelocity *= 0.95;
        if (abs($rotationVelocity) < 0.001) {
            $rotationVelocity = 0.0;
        }
    }

    // max rotation speed
    $rotationVelocity = max(-1.0, min(1.0, $rotationVelocity));
    $rotation += $rotationVelocity;

    $model->rotate($rotation, new Vec3(0.0, 1.0, 0.0));

    // next the view matrix, this is the camera / eye position and rotation
    $view = new Mat4;
    // you can imagine the camera is beeing moved back by 2 units here.
    $view->translate(new Vec3(0.0, -3.0, -6));
    // $view->translate(new Vec3(0.0, -1.0, -3));

    // and finally the projection matrix, this is the perspective matrix.
    $projection = new Mat4;
    $projection->perspective(GLM::radians(70.0), ExampleHelper::WIN_WIDTH / ExampleHelper::WIN_HEIGHT, 0.1, 10000.0);

    // now set the uniform variables in the shader.
    // note that we use `glUniformMatrix4f` instead of `glUniformMatrix4fv` to pass a single matrix.
    glUniformMatrix4f(glGetUniformLocation($objectShader, "model"), GL_FALSE, $model);
    glUniformMatrix4f(glGetUniformLocation($objectShader, "view"), GL_FALSE, $view);
    glUniformMatrix4f(glGetUniformLocation($objectShader, "projection"), GL_FALSE, $projection);

    // set the light direction and color
    glUniform3f(glGetUniformLocation($objectShader, "light_dir"), 0.0, 0.7, 0.3);
    glUniform3f(glGetUniformLocation($objectShader, "light_color"), 1.0, 1.0, 1.0);

    // bind & draw the vertex array
    foreach($vertexBuffers as $vb) {
        // update the shader color
        glUniformVec3f(glGetUniformLocation($objectShader, "mesh_color"), $vb['color']);

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