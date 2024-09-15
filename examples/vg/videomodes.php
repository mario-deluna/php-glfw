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

$videoModes = glfwGetVideoModes(glfwGetPrimaryMonitor());

// group em by resolution
$grouped = [];
foreach($videoModes as $videoMode) {
    $key = $videoMode->width . 'x' . $videoMode->height;
    if (!isset($grouped[$key])) {
        $grouped[$key] = [];
    }

    $grouped[$key][] = $videoMode;
}

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

    $currentVideoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    $currResKey = $currentVideoMode->width . 'x' . $currentVideoMode->height;

    $offset = 50;
    $x = $offset;
    $y = $offset;
    $width = 250;
    $height = 100;
    foreach($grouped as $resKey => $videoModes) {
        $vg->beginPath();
        $vg->fillColor(VGColor::white());
        if ($resKey === $currResKey) {
            $vg->fillColor(VGColor::blue());
        }

        $vg->roundedRect($x, $y, $width, $height, 25);
        $vg->fill();

        $vg->fillColor(VGColor::black());
        $vg->textAlign(VGAlign::LEFT | VGAlign::TOP);
        $vg->text($x + 10, $y + 10, $resKey);
        
        $subX = $x;
        foreach($videoModes as $videoMode) {
            $subX = $vg->text($subX + 10, $y + 30, $videoMode->refreshRate . 'hz');
        }

        $y += $height + $offset;
        if ($y > ExampleHelper::WIN_HEIGHT - ($height + $offset)) {
            $y = $offset;
            $x += $width + $offset;
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