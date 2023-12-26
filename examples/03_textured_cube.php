<?php
/**
 * This example will open a window and draw a 3D cube in it.
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/99_example_helpers.php';

use GL\Math\{GLM, Vec3, Mat4};
use GL\Texture\Texture2D;

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
uniform sampler2D logo;

void main()
{
    fragment_color = vec4(texture(logo, v_uv).rgb, 1.0f);
} 
GLSL);

// just like before we create a cube 
// but we don't have to go over the same things again.
list($VAO, $VBO) = ExampleHelper::createCubeVBO();


// generate a texture, load it from a file and bind it
glGenTextures(1, $texture);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, $texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

// set the texture wrapping parameters
// here we basically tell opengl to repeat the texture, so when sampling out of bounds
// it will still give you a result
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

// set texture filtering parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// PHP-GLFW comes with an image loader based on stb_image
// with it you can easly create a pixel buffer object to upload to opengl
$textureData = Texture2D::fromDisk(__DIR__ . '/phpglfwlogo.png', Texture2D::CHANNEL_RGB);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, $textureData->width(), $textureData->height(), 0, GL_RGB, GL_UNSIGNED_BYTE, $textureData->buffer());

// this call generates the mipmaps for the texture
glGenerateMipmap(GL_TEXTURE_2D);

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

    // define the model matrix aka the cubes postion in the world
    $model = new Mat4;
    // because we want the cube to spin, we rotate the matrix based
    // on the elapsed time.
    $model->rotate(glfwGetTime() * 0.5, new Vec3(0.0, 1.0, 0.0));
    $model->rotate(glfwGetTime() * 0.5, new Vec3(0.0, 0.0, 1.0));

    // next the view matrix, this is the camera / eye position and rotation
	$view = new Mat4;
    // you can imagine the camera is beeing moved back by 2 units here.
    $view->translate(new Vec3(0.0, 0.0, -2));

    // and finally the projection matrix, this is the perspective matrix.
	$projection = new Mat4;
	$projection->perspective(GLM::radians(70.0), ExampleHelper::WIN_WIDTH / ExampleHelper::WIN_HEIGHT, 0.1, 100.0);

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