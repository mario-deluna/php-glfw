<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Math\Vec4;
use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor};

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

$firstAmmendment = <<<EOT
Congress shall make no law respecting an establishment of religion, or prohibiting the free exercise thereof; or abridging the freedom of speech, or of the press; or the right of the people peaceably to assemble, and to petition the Government for a redress of grievances.
EOT;

$ani = ExampleHelper::createAnimation($vg)
    ->defaults([
        'width' => ExampleHelper::WIN_WIDTH - 100,
    ])
    ->after(1000, function($frame, $vg) {
        $frame->easeInOutTo('width', ExampleHelper::WIN_WIDTH * 0.5 - 100, 1000);
    })
    ->after(1000, function($frame, $vg) {
        $frame->easeInOutTo('width', ExampleHelper::WIN_WIDTH - 100, 1000);
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

    // Render a TextBox
    $vg->fontSize(32);
    $vg->textAlign(VGAlign::LEFT);
    
    $vg->fillColor(VGColor::white());
    $vg->textBox(50, 50, $ani->states['width'], $firstAmmendment);

    // render a red frame around the text box
    $bounds = new Vec4();
    $vg->textBoxBounds(50, 50, $ani->states['width'], $firstAmmendment, $bounds);

    $vg->strokeColor(VGColor::red());
    $vg->strokeWidth(1.0);
    $vg->beginPath();
    $vg->rect($bounds->x, $bounds->y, $bounds->z - $bounds->x, $bounds->w - $bounds->y);
    $vg->stroke();

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);