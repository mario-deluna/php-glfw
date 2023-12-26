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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // fetch the content scale of the window
    $contentScaleX;
    $contentScaleY;
    glfwGetWindowContentScale($window, $contentScaleX, $contentScaleY);

    // begin a new frame using the window size as the viewport size
    $vg->beginFrame(ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT, $contentScaleX);

    ExampleHelper::drawCoordSys($vg);

    $rectX = 200;
    $rectY = 100;
    $rectWidth = 400;
    $rectHeight = 200;
    $strokeWidth = (sin(glfwGetTime()) + 1) * 25 + 1; 

    $vg->beginPath();
    $vg->rect(
        $rectX + $strokeWidth / 2, 
        $rectY + $strokeWidth / 2, 
        $rectWidth - $strokeWidth, 
        $rectHeight - $strokeWidth
    );
    $vg->strokeColor(VGColor::red());
    $vg->strokeWidth($strokeWidth);
    $vg->stroke();

    ExampleHelper::drawFuncLabels($vg, 50, 50, [
        "rect(" . 
            ($rectX + $strokeWidth / 2) . ", " . 
            ($rectY + $strokeWidth / 2) . ", " . 
            ($rectWidth - $strokeWidth) . ", " . 
            ($rectHeight - $strokeWidth) .
        ");",
        "strokeWidth($strokeWidth);",
    ]);

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);