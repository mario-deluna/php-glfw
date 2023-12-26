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

    // draw the progress segment
    $cx = 400;
    $cy = 200;
    $radius = 50;
    $progress = $ani->states['progress'];
    $startAngle = -M_PI * 0.5; 
    $endAngle = $startAngle + (M_PI * 2 * $progress);

    $vg->beginPath();
    $vg->moveTo($cx, $cy);
    $startX = $cx + $radius * cos($startAngle);
    $startY = $cy + $radius * sin($startAngle);
    $vg->lineTo($startX, $startY);
    $vg->arc($cx, $cy, $radius, $startAngle, $endAngle, VGContext::CW);
    $vg->closePath();
    $vg->fillColor(VGColor::green());
    $vg->fill();
    
    ExampleHelper::drawFuncLabel($vg, 350, 320, "progress(" . round($progress * 100) . "%)");

    ExampleHelper::drawFuncLabels($vg, 50, 50, [
        "arc($cx, $cy, $radius, $startAngle, $endAngle, VGContext::CW);",
    ]);

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);