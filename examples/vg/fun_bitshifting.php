<?php
/**
 * Visaulizing Bitshifting
 * 
 * The first time you saw ">>" or "<<" in a programming language, you probably wondered WTF is this? 
 * Or at least I did. The concept is actually quite simple, but it's hard to grasp at first. 
 * Visaualizing it helps and allowing to play around with it helps a lot.
 * 
 * Controls:
 * 
 *  - Click on a bit to toggle it
 *  - Click on the << and >> buttons to shift the bits
 *  - Click on the button on the top to set the number to a constant
 *
 * @category   Fun
 */
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Math\Vec2;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor};

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

// store if the mouse was pressed in the current frame
$didClick = false;
glfwSetMouseButtonCallback($window, function($button, $action, $mods) use (&$didClick) {
    if ($button == GLFW_MOUSE_BUTTON_LEFT && $action == GLFW_PRESS) {
        $didClick = true;
    }
});


$number = 42;

// Main Loop
// ---------------------------------------------------------------------------- 
while (!glfwWindowShouldClose($window))
{
    // clear
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    $didClick = false;
    glfwPollEvents();

    // fetch the content scale of the window
    $contentScaleX;
    $contentScaleY;
    glfwGetWindowContentScale($window, $contentScaleX, $contentScaleY);

    // begin a new frame using the window size as the viewport size
    $vg->beginFrame(ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT, $contentScaleX);

    ExampleHelper::drawCoordSys($vg);

    // extract the first 8 bits of the number
    // and draw them as 8 circles
    $bits = 8;
    $bitSize = 50;
    $bitGutter = 10;
    $bitsLen = $bits * $bitSize + ($bits - 1) * $bitGutter;
    $startPos = ExampleHelper::WIN_WIDTH / 2 + $bitsLen / 2 - $bitSize / 2;
    $y = ExampleHelper::WIN_HEIGHT / 2;

    $vg->fillColor(VGColor::white());
    for($i = 0; $i < 8; $i++) {
        $bit = ($number >> $i) & 1;
        $bitDec = pow(2, $i);

        $vg->beginPath();
        $vg->circle($startPos, $y, $bitSize / 2);
        $vg->fillColor($bit ? VGColor::white() : VGColor::gray());

        // simple bounding circle check to see if the mouse is over the bit
        glfwGetCursorPos($window, $mouseX, $mouseY);
        $mouseVec = new Vec2($mouseX, $mouseY);
        $bitVec = new Vec2($startPos, $y);
        if (Vec2::distance($mouseVec, $bitVec) < $bitSize / 2) {
            $vg->fillColor(VGColor::lightGray());

            // if mouse is pressed, toggle the bit
            if ($didClick) {
                $number ^= $bitDec;
            }
        }

        // fill the bit circle
        $vg->fill();

        // label to show what decimal value the bit represents
        $vg->fillColor(VGColor::gray());
        $vg->fontSize(20);
        $vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);
        $vg->text($startPos, $y + $bitSize / 2 + 20, (string)$bitDec);

        $startPos -= $bitSize + $bitGutter;
    }

    // large decimal number on top 
    $vg->fillColor(VGColor::white());
    $vg->fontSize(64);
    $vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);
    $vg->text(ExampleHelper::WIN_WIDTH / 2, $y - 100, (string)$number);

    // large hex number on bottom
    $vg->fillColor(VGColor::gray());
    $vg->fontSize(48);
    $vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);
    $vg->text(ExampleHelper::WIN_WIDTH / 2, $y + 100, '0x' . dechex($number));


    // create bits shift buttons to the left and right
    $rightEnd = ExampleHelper::WIN_WIDTH / 2 + $bitsLen / 2;
    $leftEnd = ExampleHelper::WIN_WIDTH / 2 - $bitsLen / 2;

    ExampleHelper::drawButton($vg, $rightEnd + 100, $y, '>>', function() use (&$number) {
        $number >>= 1;
    });

    ExampleHelper::drawButton($vg, $leftEnd - 100, $y, '<<', function() use (&$number) {
        $number <<= 1;
    });

    // reset button 
    $x = 100;
    $x = 30 + ExampleHelper::drawButton($vg, $x, 50, 'Reset', function() use (&$number) {
        $number = 42;
    }, 'left');
    $x = 30 + ExampleHelper::drawButton($vg, $x, 50, '0', function() use (&$number) {
        $number = 0;
    }, 'left');
    $x = 30 + ExampleHelper::drawButton($vg, $x, 50, '128', function() use (&$number) {
        $number = 128;
    }, 'left');
    $x = 30 + ExampleHelper::drawButton($vg, $x, 50, '255', function() use (&$number) {
        $number = 255;
    }, 'left');


    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
}

ExampleHelper::stop($window);