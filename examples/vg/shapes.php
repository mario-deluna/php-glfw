<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor};

// ensure mbstring extensin is loaded, we need it for the text rendering
if (!extension_loaded('mbstring')) {
    throw new \Exception('mbstring extension is required for this example');
}

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

    // draw a rectangle 
    $vg->beginPath();
    $vg->rect(50, 150, 100, 100);
    $vg->fillColor(VGColor::red());
    $vg->fill();

    // draw rounded rectangle
    $vg->beginPath();
    $vg->roundedRect(200, 150, 100, 100, 25);
    $vg->fillColor(VGColor::green());
    $vg->fill();

    // draw ellipse
    $vg->beginPath();
    $vg->ellipse(400, 200, 50, 25);
    $vg->fillColor(VGColor::blue());
    $vg->fill();

    // draw circle
    $vg->beginPath();
    $vg->circle(550, 200, 50);
    $vg->fillColor(VGColor::yellow());
    $vg->fill();

    // draw arc
    $vg->beginPath();
    $vg->arc(700, 200, 50, 0, 3.14, VGContext::CCW);
    $vg->fillColor(VGColor::cyan());
    $vg->fill();

    // ExampleHelper::drawFuncLabels($vg, 50, 50, [
    //     "strokeWidth($strokeWidth);",
    // ]);

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);