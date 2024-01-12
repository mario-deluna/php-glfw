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

$sentence = "Hey you! How are you doing today?";
$words = explode(' ', $sentence);
$wordData = [];
foreach ($words as $word) {
    $color = VGColor::random();
    // ensure lightness is at least 0.5
    $hls = $color->getHSL();
    if ($hls->z < 0.5) {
        $hls->z = 0.5;
        $color = VGColor::hsl($hls->x, $hls->y, $hls->z);
    }

    $wordData[] = [
        'word' => $word,
        'color' => $color
    ];
}

// ensure the lightness of

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

    $x = 50;
    $y = ExampleHelper::WIN_HEIGHT / 2;
    foreach($wordData as $word) {
        $vg->fillColor($word['color']);
        $vg->fontSize(40);
        $vg->textAlign(VGAlign::LEFT | VGAlign::MIDDLE);

        $beforeX = $x;
        $x = $vg->text($x, $y, $word['word'] . ' '); 

        $diff = $x - $beforeX;
        
        ExampleHelper::drawLength($vg, $beforeX, $y + 40, $x, $y + 40, $diff, 'bottom');
    }

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);