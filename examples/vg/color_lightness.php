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


function getHLSLabel(VGColor $color) {
    $hsl = $color->getHSL();
    return sprintf('HLS(%.2f, %.2f, %.2f)', $hsl->x, $hsl->y, $hsl->z);
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

    $colors = [
        'red',
        'green',
        'blue',
    ];

    $numOfLightSteps = 3;
    $stepSize = 0.1;
    $height = ExampleHelper::WIN_HEIGHT / count($colors);
    $y =  $height * 0.5 - 25;
    $gutter = 50;
    $gutterX = 20;
    $radius = $height / 2 - $gutter;

    foreach($colors as $color) {
        $x = ExampleHelper::WIN_WIDTH / 2;
        $vg->beginPath();
        $vg->circle($x, $y, $radius);
        $vg->fillColor(VGColor::$color());
        $vg->fill();

        // render a text under the circle
        $vg->beginPath();
        $vg->fontSize(12);
        $vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);
        $vg->fillColor(VGColor::white());
        $vg->text($x, $y + $radius + 20, $color);
        $vg->text($x, $y + $radius + 40, getHLSLabel(VGColor::$color()));

        // render lighter versions of the color
        for($lightenStep = 1; $lightenStep < $numOfLightSteps + 1; $lightenStep++) {
            $newColor = VGColor::$color()->lighten($stepSize * $lightenStep);

            $vg->beginPath();
            $vg->fillColor($newColor);
            $vg->circle($x + ($lightenStep * $radius * 2) + $gutterX * $lightenStep, $y, $radius);
            $vg->fill();

            // create a lighten label
            $vg->beginPath();
            $vg->fontSize(12);
            $vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);
            $vg->fillColor(VGColor::white());
            $vg->text($x + ($lightenStep * $radius * 2) + $gutterX * $lightenStep, $y + $radius + 20, 'lighten(' . ($stepSize * $lightenStep) . ')');
            $vg->text($x + ($lightenStep * $radius * 2) + $gutterX * $lightenStep, $y + $radius + 40, getHLSLabel($newColor));
        }

        // same for the darken version
        for($darkenStep = 1; $darkenStep < $numOfLightSteps + 1; $darkenStep++) {
            $newColor = VGColor::$color()->darken($stepSize * $darkenStep);

            $vg->beginPath();
            $vg->fillColor($newColor);
            $vg->circle($x - ($darkenStep * $radius * 2) - $gutterX * $darkenStep, $y, $radius);
            $vg->fill();

            // create a darken label
            $vg->beginPath();
            $vg->fontSize(12);
            $vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);
            $vg->fillColor(VGColor::white());
            $vg->text($x - ($darkenStep * $radius * 2) - $gutterX * $darkenStep, $y + $radius + 20, 'darken(' . ($stepSize * $darkenStep) . ')');
            $vg->text($x - ($darkenStep * $radius * 2) - $gutterX * $darkenStep, $y + $radius + 40, getHLSLabel($newColor));
        }

        $y += $height;
    }

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);