<?php
/**
 * This example will open a window and draw a 3D cube in it.
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/99_example_helpers.php';

use GL\Math\{Vec3, Vec4, Mat4};
use GL\Buffer\FloatBuffer;

$window = ExampleHelper::begin();

// compile a simple shader to project the cube 
// and output the uv colors to the fragment shader
$cubeShader = ExampleHelper::compileShader(<<< 'GLSL'
#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_uv;

out vec2 v_uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    v_uv = a_uv;
	gl_Position = projection * view * model * vec4(a_position, 1.0f);
}
GLSL,
<<< 'GLSL'
#version 330 core
out vec4 fragment_color;

in vec2 v_uv;

void main()
{
    fragment_color = vec4(v_uv.x, v_uv.y, 1.0f, 1.0f);
} 
GLSL);

// create a floating point buffer with the vertex and uv data 
// of a cube with a 1x1x1 size.
$verticies = new FloatBuffer([ 
	-0.5, -0.5, -0.5,  0.0, 0.0,
     0.5, -0.5, -0.5,  1.0, 0.0,
     0.5,  0.5, -0.5,  1.0, 1.0,
     0.5,  0.5, -0.5,  1.0, 1.0,
    -0.5,  0.5, -0.5,  0.0, 1.0,
    -0.5, -0.5, -0.5,  0.0, 0.0,

    -0.5, -0.5,  0.5,  0.0, 0.0,
     0.5, -0.5,  0.5,  1.0, 0.0,
     0.5,  0.5,  0.5,  1.0, 1.0,
     0.5,  0.5,  0.5,  1.0, 1.0,
    -0.5,  0.5,  0.5,  0.0, 1.0,
    -0.5, -0.5,  0.5,  0.0, 0.0,

    -0.5,  0.5,  0.5,  1.0, 0.0,
    -0.5,  0.5, -0.5,  1.0, 1.0,
    -0.5, -0.5, -0.5,  0.0, 1.0,
    -0.5, -0.5, -0.5,  0.0, 1.0,
    -0.5, -0.5,  0.5,  0.0, 0.0,
    -0.5,  0.5,  0.5,  1.0, 0.0,

     0.5,  0.5,  0.5,  1.0, 0.0,
     0.5,  0.5, -0.5,  1.0, 1.0,
     0.5, -0.5, -0.5,  0.0, 1.0,
     0.5, -0.5, -0.5,  0.0, 1.0,
     0.5, -0.5,  0.5,  0.0, 0.0,
     0.5,  0.5,  0.5,  1.0, 0.0,

    -0.5, -0.5, -0.5,  0.0, 1.0,
     0.5, -0.5, -0.5,  1.0, 1.0,
     0.5, -0.5,  0.5,  1.0, 0.0,
     0.5, -0.5,  0.5,  1.0, 0.0,
    -0.5, -0.5,  0.5,  0.0, 0.0,
    -0.5, -0.5, -0.5,  0.0, 1.0,

    -0.5,  0.5, -0.5,  0.0, 1.0,
     0.5,  0.5, -0.5,  1.0, 1.0,
     0.5,  0.5,  0.5,  1.0, 0.0,
     0.5,  0.5,  0.5,  1.0, 0.0,
    -0.5,  0.5,  0.5,  0.0, 0.0,
    -0.5,  0.5, -0.5,  0.0, 1.0
]);

// create a vertex array object and upload the vertices
glGenVertexArrays(1, $VAO);
glGenBuffers(1, $VBO);

glBindVertexArray($VAO);
glBindBuffer(GL_ARRAY_BUFFER, $VBO);
glBufferData(GL_ARRAY_BUFFER, $verticies, GL_STATIC_DRAW);

// declare the vertex attributes
// positions
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 5, 0);
glEnableVertexAttribArray(0);

// uv
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 5, GL_SIZEOF_FLOAT * 3);
glEnableVertexAttribArray(1);

// unbind
glBindBuffer(GL_ARRAY_BUFFER, 0); 
glBindVertexArray(0); 

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
    glUseProgram($cubeShader);

    // define the model matrix aka the cubes postion in the world
    $model = new Mat4;
    // because we want the cube to spin, we rotate the matrix based
    // on the elapsed time.
    $model->rotate(glfwGetTime() * 2, new Vec3(0.0, 1.0, 0.0));
    $model->rotate(glfwGetTime() * 2, new Vec3(0.0, 0.0, 1.0));

    // next the view matrix, this is the camera / eye position and rotation
	$view = new Mat4;
    // you can imagine the camera is beeing moved back by 2 units here.
    $view->translate(new Vec3(0.0, 0.0, -2));

    // and finally the projection matrix, this is the perspective matrix.
	$projection = new Mat4;
	$projection->perspective(glm::radians(70.0), ExampleHelper::WIN_WIDTH / ExampleHelper::WIN_HEIGHT, 0.1, 100.0);

    // now set the uniform variables in the shader.
    // note that we use `glUniformMatrix4f` instead of `glUniformMatrix4fv` to pass a single matrix.
    glUniformMatrix4f(glGetUniformLocation($cubeShader, "model"), GL_FALSE, $model);
    glUniformMatrix4f(glGetUniformLocation($cubeShader, "view"), GL_FALSE, $view);
    glUniformMatrix4f(glGetUniformLocation($cubeShader, "projection"), GL_FALSE, $projection);

    // bind & draw the vertex array
    glBindVertexArray($VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}


// stop & cleanup
glDeleteVertexArrays(1, $VAO);
glDeleteBuffers(1, $VBO);

ExampleHelper::stop($window);