<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor};
use phpDocumentor\Reflection\DocBlock\Tags\Example;

// ensure mbstring extensin is loaded, we need it for the text rendering
if (!extension_loaded('mbstring')) {
    throw new \Exception('mbstring extension is required for this example');
}

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

$ani = ExampleHelper::createAnimation($vg)
    ->defaults([
        'x' => 100,
        'y' => 150,
        'width' => 100,
        'height' => 100
    ])
    ->after(500, function($frame, $vg) {
        $frame->easeInOutTo('x', 200, 1000);
    })
    ->after(500, function($frame, $vg) {
        $frame->easeInOutTo('width', 200, 1000);
        $frame->easeInOutTo('height', 200, 1000);
    })
    ->after(500, function($frame, $vg) {
        $frame->easeInOutTo('width', 100, 1000);
        $frame->easeInOutTo('height', 100, 1000);
    })
    ->after(500, function($frame, $vg) {
        $frame->easeInOutTo('x', 100, 1000);
    });


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

    $ani->build(glfwGetTime());

    $vg->beginPath();
    $vg->rect($ani->states['x'], 150, $ani->states['width'], $ani->states['height']);
    $vg->fillColor(VGColor::red());
    $vg->fill();

    ExampleHelper::drawFuncLabels($vg, 50, 50, [
        "rect({$ani->states['x']}, 150, {$ani->states['width']}, {$ani->states['height']});"
    ]);

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);