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

    $cornerRadius = 50 + sin(glfwGetTime()) * 25;

    $vg->beginPath();
    $vg->roundedRect(100, 100, 200, 200, $cornerRadius);
    $vg->fillColori(22, 159, 255, 255);
    $vg->fill();

    // radius
    ExampleHelper::drawLength($vg, 320, 100, 320, 100 + $cornerRadius, "radius = " . round($cornerRadius));

    // width
    ExampleHelper::drawLength($vg, 100, 320, 300, 320, "width = 200", 'bottom');

    ExampleHelper::drawPoint($vg, 100, 100, '100,100');

    ExampleHelper::drawFuncLabels($vg, 50, 50, [
        "roundedRect(100, 100, 200, 200, $cornerRadius);",
    ]);



    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);