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

$ani = ExampleHelper::createAnimation($vg)
    ->defaults([
        'rx' => 100,
        'ry' => 100,
    ])
    ->after(500, function($frame, $vg) {
        $frame->easeInOutTo('rx', 200, 1000);
    })
    ->after(500, function($frame, $vg) {
        $frame->easeInOutTo('rx', 100, 1000);
    })
    ->after(500, function($frame, $vg) {
        $frame->easeInOutTo('ry', 200, 1000);
    })
    ->after(500, function($frame, $vg) {
        $frame->easeInOutTo('ry', 100, 1000);
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

    $radiusX = $ani->states['rx'];
    $radiusY = $ani->states['ry'];

    $vg->beginPath();
    $vg->ellipse(400, 200, $radiusX, $radiusY);
    $vg->fillColori(22, 159, 255, 255);
    $vg->fill();

    // Drawing radii next to the ellipse
    // ExampleHelper::drawLength($vg, 400 - $radiusX, 320, 400 + $radiusX, 320, "radiusX = " . round($radiusX), 'bottom');
    // ExampleHelper::drawLength($vg, 280, 200 - $radiusY, 280, 200 + $radiusY, "radiusY = " . round($radiusY), 'left');

    ExampleHelper::drawLength($vg, 400, 320, 400 + $radiusX, 320, "radiusX = " . round($radiusX), 'bottom');
    ExampleHelper::drawLength($vg, 280, 200, 280, 200 + $radiusY, "radiusY = " . round($radiusY), 'left');

    ExampleHelper::drawPoint($vg, 400, 200, '400, 200');

    ExampleHelper::drawFuncLabels($vg, 50, 50, [
        "ellipse(400, 200, $radiusX, $radiusY);",
    ]);

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);