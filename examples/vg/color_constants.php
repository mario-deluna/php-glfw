<?php
/**
 * Color Constants
 * 
 * This example shows all the available color constants.
 *
 * @image      user_guide/vg/colors/color_contants.png
 * @category   Color
 */
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

    $colors = [
        'red',
        'green',
        'blue',
        'white',
        'black',
        'transparent',
        'yellow',
        'cyan',
        'magenta',
        'orange',
        'pink',
        'purple',
        'brown',
        'gray',
        'darkGray',
        'lightGray',
        'random',
        'randomGray',
    ];

    $circleRadius = 45;
    $gutter = 10;
    $x = 50;
    $y = 50;
    foreach($colors as $i => $color) {
        $vg->beginPath();
        $vg->circle($x, $y, $circleRadius);
        $vg->fillColor(VGColor::$color());
        $vg->fill();

        // label
        $vg->fillColor(VGColor::white());
        $vg->fontSize(14);
        $vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);
        $vg->text($x, $y + $circleRadius + 20, $color);

        $x += $circleRadius * 2 + $gutter;
        if($x > ExampleHelper::WIN_WIDTH - 50) {
            $x = 50;
            $y += $circleRadius * 2 + $gutter + 50;
        }
    }

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);