<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/99_example_helpers.php';

use GL\Math\{Vec3, Vec4, Mat4};
use GL\Buffer\FloatBuffer;
use GL\Texture\Texture2D;

// ensure mbstring extensin is loaded, we need it for the text rendering
if (!extension_loaded('mbstring')) {
    throw new \Exception('mbstring extension is required for this example');
}

$window = ExampleHelper::begin();

// in the font/ directory you find a bitmap version of the font cozette 
// to use it we need to load it into a texture and create a font atlas
glGenTextures(1, $fontTexture);
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, $fontTexture);
// texture wrapping
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
// set texture filtering parameters
// because we have a pixel font we want to use nearest neighbor filtering
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
$textureData = Texture2D::fromDisk(__DIR__ . '/font/cozette.png');
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, $textureData->width(), $textureData->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, $textureData->buffer());

// next we need to parse the xml file that contains the font atlas
$atlasXml = simplexml_load_file(__DIR__ . '/font/cozette.xml');
$atlas = [];
$atlasWidth = (int) $atlasXml->common->attributes()->scaleW;
$atlasHeight = (int) $atlasXml->common->attributes()->scaleH;

foreach($atlasXml->chars->char as $char) {
    $atlas[(int) $char['id']] = [
        'x' => (int) $char['x'],
        'y' => (int) $char['y'],
        'width' => (int) $char['width'],
        'height' => (int) $char['height'],
        'xoffset' => (int) $char['xoffset'],
        'yoffset' => (int) $char['yoffset'],
        'xadvance' => (int) $char['xadvance'],
    ];
}

function getAtlasChar(string $char) : ?array {
    global $atlas;
    return $atlas[mb_ord($char)] ?? null;
}

// create a vertex buffer for the text
// we will use a single vertex buffer for all text 
// and just update the vertex data each frame
// (this is not ideal for performance, but it is simple and works for this example)
glGenVertexArrays(1, $textVAO);
glGenBuffers(1, $textVBO);

glBindVertexArray($textVAO);
glBindBuffer(GL_ARRAY_BUFFER, $textVBO);

// vertex attributes for the text
// position
glEnableVertexAttribArray(0);
glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 4, 0);

// uv
glEnableVertexAttribArray(1);
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 4, GL_SIZEOF_FLOAT * 2);

glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);

// compile a simple text shader to project the text
$textShader = ExampleHelper::compileShader(<<< 'GLSL'
#version 330 core
layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_uv;

out vec2 v_uv;

uniform mat4 projection;

void main()
{
    v_uv = vec2(a_uv.x, 1.0f - a_uv.y);
    gl_Position = projection * vec4(a_position, 0.0f, 1.0f);
}

GLSL,
<<< 'GLSL'
#version 330 core
out vec4 fragment_color;

in vec2 v_uv;

uniform sampler2D font;

void main()
{
    fragment_color = vec4(vec3(texture(font, v_uv).a), 1.0f);
}
GLSL);

// update the viewport
glViewport(0, 0, ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT);

// declare the text buffer
$textCorpus = "Hello PHP-GLFW, press arrow key up and down to change the text size.\nYou can also type here: ";
$scale = 1.0;

// register the char callback and extend the text corpus with use input
glfwSetCharCallback($window, function($char) use (&$textCorpus) {
    $textCorpus .= mb_chr($char);
});

// register the key callback and remove the last char from the text corpus
glfwSetKeyCallback($window, function($key, $scancode, $action, $mods) use (&$textCorpus) {
    if ($action === GLFW_PRESS && $key === GLFW_KEY_BACKSPACE) {
        $textCorpus = mb_substr($textCorpus, 0, -1);
    }
    // also register linebreaks
    if ($action === GLFW_PRESS && $key === GLFW_KEY_ENTER) {
        $textCorpus .= "\n";
    }

    // arrow up and down to change the text size
    if ($action === GLFW_PRESS && $key === GLFW_KEY_UP) {
        global $scale;
        $scale *= 1.1;
    }

    if ($action === GLFW_PRESS && $key === GLFW_KEY_DOWN) {
        global $scale;
        $scale *= 0.9;
    }
});

// Main Loop
// ---------------------------------------------------------------------------- 
while (!glfwWindowShouldClose($window))
{
    glfwPollEvents();
    
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the shader, will active the given shader program
    // for the coming draw calls.
    glUseProgram($textShader);

    // for text rendering we need to use a orthographic projection
    $projection = new Mat4;
    $projection->ortho(0, ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT, 0, -1, 1);

    // set the projection matrix
    glUniformMatrix4f(glGetUniformLocation($textShader, 'projection'), GL_FALSE, $projection);

    // bind the font texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, $fontTexture);
    glUniform1i(glGetUniformLocation($textShader, 'font'), 0);

    // bind the vertex array object
    glBindVertexArray($textVAO);
    glBindBuffer(GL_ARRAY_BUFFER, $textVBO);

    // build final text 
    $text = $textCorpus;

    // add a blinking curosor
    if (((int)(glfwGetTime() * 2) % 2) === 0) {
        $text .= '_';
    }

    // draw the text
    $x = 10;
    $y = 10;
    $lineHeight = 20;

    $vertices = new FloatBuffer();
    $textLen = mb_strlen($text);

    // the vertex count has to be counted 
    // in the loop because some chars are not in the atlas
    $vertexCount = 0;
    
    // reserve the memory for the vertices
    $vertices->reserve($textLen * 6 * 4);
    
    // for every character in the text
    for($i = 0; $i < $textLen; $i++) 
    {
        $char = mb_substr($text, $i, 1);
        $charData = getAtlasChar($char);

        // on linebreak
        if ($char === "\n") {
            $x = 10;
            $y += $lineHeight * $scale;
            continue;
        }
        
        // skip unknown characters
        if ($charData === null) {
            continue;
        }

        // create 2 triangles for the character
        // precalucalte the correct uv coordinates for the character
        $xpos = $x + $charData['xoffset'] * $scale;
        $ypos = $y + $charData['yoffset'] * $scale;
        $w = $charData['width'] * $scale;
        $h = $charData['height'] * $scale;
        $uvX = (float) $charData['x'] / $atlasWidth;
        $uvY = (float) $charData['y'] / $atlasHeight;
        $uvW = (float) $charData['width'] / $atlasWidth;
        $uvH = (float) $charData['height'] / $atlasHeight;

        $vertices->pushArray([
            $xpos, $ypos, $uvX, $uvY,
            $xpos + $w, $ypos, $uvX + $uvW, $uvY,
            $xpos, $ypos + $h, $uvX, $uvY + $uvH,
            $xpos + $w, $ypos, $uvX + $uvW, $uvY,
            $xpos, $ypos + $h, $uvX, $uvY + $uvH,
            $xpos + $w, $ypos + $h, $uvX + $uvW, $uvY + $uvH,
        ]);

        $vertexCount += 6;

        // advance the cursor
        $x += $charData['xadvance'] * $scale;
        if ($x > ExampleHelper::WIN_WIDTH - 10) {
            $x = 10;
            $y += $lineHeight * $scale;
        }
    }

    // buffer the vertices
    glBufferData(GL_ARRAY_BUFFER, $vertices, GL_DYNAMIC_DRAW);

    // render the characters
    glDrawArrays(GL_TRIANGLES, 0, $vertexCount);

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
}


// stop & cleanup vbo & vao
glDeleteVertexArrays(1, $textVAO);
glDeleteBuffers(1, $textVBO);

ExampleHelper::stop($window);