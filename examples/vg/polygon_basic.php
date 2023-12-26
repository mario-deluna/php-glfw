<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor};
use phpDocumentor\Reflection\DocBlock\Tags\Example;

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

$ani = ExampleHelper::createAnimation($vg)
    ->defaults([
        'progress' => 0.0,
    ])
    ->after(500, function($frame, $vg) {
        $frame->easeInOutTo('progress', 0.3, 1000);
    })
    ->after(100, function($frame, $vg) {
        $frame->easeInOutTo('progress', 0.7, 1500);
    })
    ->after(300, function($frame, $vg) {
        $frame->easeInOutTo('progress', 0.8, 200);
    })
    ->after(500, function($frame, $vg) {
        $frame->easeInOutTo('progress', 1.0, 800);
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
    $vg->moveTo(400, 100);
    $vg->lineTo(450, 200);
    $vg->lineTo(550, 200);
    $vg->lineTo(475, 250);
    $vg->lineTo(500, 350);
    $vg->lineTo(400, 300);
    $vg->lineTo(300, 350);
    $vg->lineTo(325, 250);
    $vg->lineTo(250, 200);
    $vg->lineTo(350, 200);
    $vg->closePath();
    $vg->fillColor(VGColor::yellow());
    $vg->fill();

    // draw some eyes
    $vg->beginPath();
    $vg->circle(400 - 30, 230, 10);
    $vg->circle(400 + 30, 230, 10);
    $vg->fillColor(VGColor::black());
    $vg->fill();

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);