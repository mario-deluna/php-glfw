<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor};

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

// Main Loop
// ---------------------------------------------------------------------------- 
while (!glfwWindowShouldClose($window))
{
    // clear
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // fetch the content scale of the window
    $contentScaleX;
    $contentScaleY;
    glfwGetWindowContentScale($window, $contentScaleX, $contentScaleY);

    // begin a new frame using the window size as the viewport size
    $vg->beginFrame(ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT, $contentScaleX);

    ExampleHelper::drawCoordSys($vg);

    // Render a Hello World Text
    $vg->fontSize(200.0);
    $vg->textLetterSpacing(2.0);
    $vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);

    // shadow text
    $vg->beginPath();
    $vg->fontBlur(4);
    $vg->fillColor(VGColor::rgba(1.0, 1.0, 1.0, 0.5));
    $vg->text(ExampleHelper::WIN_WIDTH / 2, ExampleHelper::WIN_HEIGHT / 2 + 10, "Hello World");
    $vg->closePath();
    
    // actual text
    $vg->beginPath();
    $vg->fontBlur(0.0);
    $vg->fillColor(VGColor::white());
    $vg->text(ExampleHelper::WIN_WIDTH / 2, ExampleHelper::WIN_HEIGHT / 2, "Hello World");


    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);