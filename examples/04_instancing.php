<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/99_example_helpers.php';

use GL\Buffer\FloatBuffer;
use GL\Math\{GLM, Vec3, Mat4};

$window = ExampleHelper::begin();

// compile a simple shader to project the cube 
// and output the uv colors to the fragment shader
$cubeShader = ExampleHelper::compileShader(<<< 'GLSL'
#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_uv;
layout (location = 2) in mat4 a_model;

out vec2 v_uv;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    v_uv = a_uv;
	gl_Position = projection * view * a_model * vec4(a_position, 1.0f);
}
GLSL,
<<< 'GLSL'
#version 330 core
out vec4 fragment_color;

in vec2 v_uv;
uniform sampler2D logo;

void main()
{
    fragment_color = vec4(texture(logo, v_uv).rgb, 1.0f) * vec4(v_uv, 1.0f, 1.0f);
}
GLSL);

// just like before we create a cube 
// but we don't have to go over the same things again.
list($VAO, $VBO) = ExampleHelper::createCubeVBO();

// additionally create the elements buffer
$matrices = new FloatBuffer;
$c3size = 50;
$matrices->reserve($c3size * $c3size * $c3size * 16);
for ($y = 0; $y < $c3size; $y++) {
    for ($x = 0; $x < $c3size; $x++) {
        for ($z = 0; $z < $c3size; $z++) {
            $m = new Mat4;
            $p = new Vec3($x, $y, $z);
            $m->translate(($p - ($c3size / 2)) * 2.5);
            $matrices->pushMat4($m);
        }
    }
}

glGenBuffers(1, $EBO);
glBindBuffer(GL_ARRAY_BUFFER, $EBO);
glBufferData(GL_ARRAY_BUFFER, $matrices, GL_STATIC_DRAW);

// define additional vertex attributes for the instancing
glBindVertexArray($VAO);
glEnableVertexAttribArray(2);
glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 16, 0);
glEnableVertexAttribArray(3);
glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 16, (GL_SIZEOF_FLOAT * 4) * 1);
glEnableVertexAttribArray(4);
glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 16, (GL_SIZEOF_FLOAT * 4) * 2);
glEnableVertexAttribArray(5);
glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 16, (GL_SIZEOF_FLOAT * 4) * 3);

glVertexAttribDivisor(2, 1);
glVertexAttribDivisor(3, 1);
glVertexAttribDivisor(4, 1);
glVertexAttribDivisor(5, 1);

glBindVertexArray(0);

$texture = ExampleHelper::loadTexture(__DIR__ . '/phpglfwlogo.png');

// set the shader uniform to point 
// the texture unit to our texture
glUseProgram($cubeShader);
glUniform1i(glGetUniformLocation($cubeShader, 'logo'), 0);

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

    // time 
    $t = glfwGetTime() * 0.1;
    $dist = ($c3size * 2.5) + (cos(($t + 2) * 0.5) * 250);

    // next the view matrix, this is the camera / eye position and rotation
	$view = new Mat4;
    // we rotate the camera around the y axis and always look at the origin
    // also we zoom in and out for nice effect
    $view->lookAt(new Vec3(sin($t) * $dist, 0.0, cos($t) * $dist), new Vec3(0.0, 0.0, 1.0), new Vec3(0.0, 1.0, 0.0));

    // and finally the projection matrix, this is the perspective matrix.
	$projection = new Mat4;
	$projection->perspective(GLM::radians(45.0), ExampleHelper::WIN_WIDTH / ExampleHelper::WIN_HEIGHT, 1.0, 10000.0);

    // now set the uniform variables in the shader.
    // note that we use `glUniformMatrix4f` instead of `glUniformMatrix4fv` to pass a single matrix.
    glUniformMatrix4f(glGetUniformLocation($cubeShader, "view"), GL_FALSE, $view);
    glUniformMatrix4f(glGetUniformLocation($cubeShader, "projection"), GL_FALSE, $projection);

    // bind & draw the vertex array
    glBindVertexArray($VAO);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, $matrices->size() / 16);
    glBindVertexArray(0);
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