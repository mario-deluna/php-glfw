<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Buffer\FloatBuffer;
use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor};

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

function isPrime(int $number): bool {
    if ($number <= 1) {
        return false;
    }

    if ($number === 2) {
        return true;
    }

    if ($number % 2 === 0) {
        return false;
    }

    for ($i = 3; $i <= sqrt($number); $i += 2) {
        if ($number % $i === 0) {
            return false;
        }
    }

    return true;
}

$fb = 0;
$fbTex = 0;
$fbStencil = 0;
$fbWidth = 0;
$fbHeight = 0;
$fbScaleX = 0;

$number = 1;
$numberOfStepsPerFrame = 1000;

// define the grid in which we render the primes
$viewWidth = 80;
$viewHeight = 60;

$zoom = 1.0;
$offsetX = 0.0;
$offsetY = 0.0;

$shouldRun = true;

glfwSetKeyCallback($window, function($key, $scancode, $action, $mods) use (&$shouldRun, &$number, &$viewWidth, &$viewHeight, &$zoom, &$offsetX, &$offsetY) {
    if ($key == GLFW_KEY_SPACE && $action == GLFW_PRESS) {
        $shouldRun = !$shouldRun;
    }

    // reset
    if ($key == GLFW_KEY_R && $action == GLFW_PRESS) {
        $number = 1;
        buildFramebuffer();
        $zoom = 1.0;
        $offsetX = 0.0;
        $offsetY = 0.0;
    }

    // increase / decrease the view width
    if ($key == GLFW_KEY_Q && ($action == GLFW_PRESS || $action == GLFW_REPEAT)) {
        $viewWidth--;
        $number = 1;
        buildFramebuffer();
        $shouldRun = true;
    }

    if ($key == GLFW_KEY_E && ($action == GLFW_PRESS || $action == GLFW_REPEAT)) {
        $viewWidth++;
        $number = 1;
        buildFramebuffer();
        $shouldRun = true;
    }

    // increase / decrease the view height
    if ($key == GLFW_KEY_A && ($action == GLFW_PRESS || $action == GLFW_REPEAT)) {
        $viewHeight--;
        $number = 1;
        buildFramebuffer();
        $shouldRun = true;
    }

    if ($key == GLFW_KEY_D && ($action == GLFW_PRESS || $action == GLFW_REPEAT)) {
        $viewHeight++;
        $number = 1;
        buildFramebuffer();
        $shouldRun = true;
    }
});

// on scroll we zoom
glfwSetScrollCallback($window, function($xOffset, $yOffset) use (&$zoom) {
    $zoom += $yOffset * 0.1;
    $zoom = max(0.001, $zoom);
});

// allow mouse dragging to move the offset
$mouseDown = false;
$mouseX = 0;
$mouseY = 0;
glfwSetMouseButtonCallback($window, function($button, $action, $mods) use (&$mouseDown, &$mouseX, &$mouseY) {
    if ($button == GLFW_MOUSE_BUTTON_LEFT) {
        $mouseDown = $action == GLFW_PRESS;
    }
});

glfwSetCursorPosCallback($window, function($x, $y) use (&$mouseDown, &$mouseX, &$mouseY, &$offsetX, &$offsetY, &$zoom) {
    if ($mouseDown) {
        $offsetX -= ($x - $mouseX) * $zoom;
        $offsetY += ($y - $mouseY) * $zoom;
    }

    $mouseX = $x;
    $mouseY = $y;
});


function buildFramebuffer()
{
    global $fb;
    global $fbTex;
    global $fbStencil;
    global $window;
    global $fbWidth;
    global $fbHeight;
    global $fbScaleX;

    // delete old framebuffer
    if ($fb) {
        glDeleteFramebuffers(1, $fb);
        $fb = 0;
    }

    if ($fbTex) {
        glDeleteTextures(1, $fbTex);
        $fbTex = 0;
    }

    if ($fbStencil) {
        glDeleteRenderbuffers(1, $fbStencil);
        $fbStencil = 0;
    }

    glfwGetWindowContentScale($window, $contentScaleX, $contentScaleY);
    glfwGetWindowSize($window, $width, $height);

    $fbWidth = $width;
    $fbHeight = $height;
    $fbScaleX = $contentScaleX;

    glGenFramebuffers(1, $fb);
    glBindFramebuffer(GL_FRAMEBUFFER, $fb);
    
    // create a color attachment texture
    glGenTextures(1, $fbTex);
    glBindTexture(GL_TEXTURE_2D, $fbTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, $fbWidth * $fbScaleX, $fbHeight * $fbScaleX, 0, GL_RGBA, GL_UNSIGNED_BYTE, null);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, $fbStencil);
    glBindRenderbuffer(GL_RENDERBUFFER, $fbStencil);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, $fbWidth * $fbScaleX, $fbHeight * $fbScaleX);
    
    // attach the texture and RBO to the framebuffer
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, $fbTex, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, $fbStencil);
    
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !== GL_FRAMEBUFFER_COMPLETE) {
        throw new Exception('Offscreen Framebuffer is not complete!');
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

$quadShader = ExampleHelper::compileShader(<<< 'GLSL'
#version 330 core
layout (location = 0) in vec2 a_position;
layout (location = 1) in vec2 a_uv;

out vec2 v_uv;

void main()
{
    v_uv = a_uv;
    gl_Position = vec4(a_position, 0.0f, 1.0f);
}
GLSL,
<<< 'GLSL'
#version 330 core

out vec4 fragment_color;

in vec2 v_uv;

uniform sampler2D tex;
uniform vec2 offset;
uniform float zoom;

void main()
{
    vec2 adjusted_uv = (v_uv - 0.5) * zoom + 0.5 + offset;
    fragment_color = vec4(texture(tex, adjusted_uv).rgb, 1.0f);
}
GLSL);

// create a quad
[$quadVAO, $quadVBO] = ExampleHelper::createQuadVBO();

// create a framebuffer
buildFramebuffer();

// Main Loop
// ---------------------------------------------------------------------------- 
while (!glfwWindowShouldClose($window))
{
    glfwGetWindowContentScale($window, $contentScaleX, $contentScaleY);
    glfwGetWindowSize($window, $width, $height);
    glViewport(0, 0, $width * $contentScaleX, $height * $contentScaleY);

    // bind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, $fb);
    glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // begin a new frame using the window size as the viewport size
    $vg->beginFrame($fbWidth, $fbHeight, $fbScaleX);

    // ExampleHelper::drawCoordSys($vg);
    if ($shouldRun && glfwGetTime() > 0.5) {
        for($s=0; $s<$numberOfStepsPerFrame; $s++) {

            $number++;
            $isPrime = isPrime($number);

            $blockWidth = $fbWidth / $viewWidth;
            $blockHeight = $fbHeight / $viewHeight;

            // convert the number into a rect postion x,y one pixel wide
            // $x = $number % $fbWidth;
            // $y = floor($number / $fbWidth);
            $x = $number % $viewWidth;
            $y = floor($number / $viewWidth);

            // check if the number is outside the view
            if ($y * $blockHeight > $fbHeight) {
                var_dump($y * $blockHeight, $fbHeight);
                $shouldRun = false;
                break;
            }

            if ($isPrime) {
                $vg->beginPath();
                $vg->fillColori(22, 159, 255, 255);
                $vg->rect($x * $blockWidth, $y * $blockHeight, $blockWidth, $blockHeight);
                $vg->fill();
            }

            // draw the number into the block
            $vg->beginPath();
            $vg->fontSize(min($blockWidth, $blockHeight) * 0.4);
            $vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);
            $vg->fillColori(255, 255, 255, 255);
            $vg->text($x * $blockWidth + $blockWidth / 2, $y * $blockHeight + $blockHeight / 2, $number);
            $vg->fill();
        }
    }

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // unbind the framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // draw the framebuffer texture
    glClearColor(1, 0, 0, 1);
    glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glfwGetWindowContentScale($window, $contentScaleX, $contentScaleY);
    glfwGetWindowSize($window, $width, $height);
    glViewport(0, 0, $width * $contentScaleX, $height * $contentScaleY);

    // bind the framebuffer texture to the texture unit 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, $fbTex);
    glUseProgram($quadShader);
    glUniform1i(glGetUniformLocation($quadShader, 'tex'), 0);
    // the offset is in pixels so it needs to be scaled to uv space
    $offsetUVX = $offsetX / ($fbWidth);
    $offsetUVY = $offsetY / ($fbHeight);
    glUniform2f(glGetUniformLocation($quadShader, 'offset'), $offsetUVX, $offsetUVY);
    glUniform1f(glGetUniformLocation($quadShader, 'zoom'), $zoom);

    // draw a quad
    glBindVertexArray($quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // draw some metrics
    $vg->beginFrame($width, $height, $contentScaleX);

    ExampleHelper::drawFuncLabels($vg, 50, 50, [
        "view($viewWidth, $viewHeight)",
        "zoom($zoom)",
        "offset($offsetX, $offsetY)",
    ]);

    $vg->endFrame();
    

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);