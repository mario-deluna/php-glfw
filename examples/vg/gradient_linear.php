<?php
/**
 * Linear Gradient
 * This PHP GLFW Vector Graphics example show how to create a linear gradient and apply it to a rectangle.
 * 
 * @category   Gradients
 */
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Math\GLM;
use GL\Math\Vec2;
use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor, VGImage};

// ensure mbstring extensin is loaded, we need it for the text rendering
if (!extension_loaded('mbstring')) {
    throw new \Exception('mbstring extension is required for this example');
}

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

$gradientPos1 = new Vec2(150, 200);
$gradientPos2 = new Vec2(400, 400);
$gradientColor1 = new VGColor(0.051, 0.682, 0.914, 1.0);
$gradientColor2 = new VGColor(0.169, 0.961, 0.596, 1.0);

$isDraggingP1 = false;
$isDraggingP2 = false;
$currentMousePos = new Vec2(0, 0);

glfwSetMouseButtonCallback($window, function($button, $action, $mods) use($window, &$isDraggingP1, &$isDraggingP2, $gradientPos1, $gradientPos2, $currentMousePos) {
    if ($button == GLFW_MOUSE_BUTTON_LEFT && $action == GLFW_PRESS) {
        if ($currentMousePos->distanceTo($gradientPos1) < 10) {
            $isDraggingP1 = true;
        } else if ($currentMousePos->distanceTo($gradientPos2) < 10) {
            $isDraggingP2 = true;
        }
    } else if ($button == GLFW_MOUSE_BUTTON_LEFT && $action == GLFW_RELEASE) {
        $isDraggingP1 = false;
        $isDraggingP2 = false;
    }
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

    $xpos = 0.0;
    $ypos = 0.0;
    glfwGetCursorPos($window, $xpos, $ypos);
    $currentMousePos->x = $xpos;
    $currentMousePos->y = $ypos;

    if ($isDraggingP1) {
        $gradientPos1->x = $currentMousePos->x;
        $gradientPos1->y = $currentMousePos->y;
    } else if ($isDraggingP2) { 
        $gradientPos2->x = $currentMousePos->x;
        $gradientPos2->y = $currentMousePos->y;
    }

    // created a linear gradient
    $gradientPaint = $vg->linearGradient(
        $gradientPos1->x,
        $gradientPos1->y,
        $gradientPos2->x,
        $gradientPos2->y,
        $gradientColor1,
        $gradientColor2
    );

    // fill the screen with the gradient
    $vg->beginPath();
    $vg->rect(50, 150, ExampleHelper::WIN_WIDTH - 100, ExampleHelper::WIN_HEIGHT - 300);
    $vg->fillPaint($gradientPaint);
    $vg->fill();

    // ExampleHelper::drawCoordSys($vg);
    ExampleHelper::drawLength($vg, $gradientPos1->x, $gradientPos1->y, $gradientPos2->x, $gradientPos2->y, '');
    ExampleHelper::drawPoint($vg, $gradientPos1->x, $gradientPos1->y, 'p1('. round($gradientPos1->x) .', '. round($gradientPos1->y) .')');
    ExampleHelper::drawPoint($vg, $gradientPos2->x, $gradientPos2->y, 'P2('. round($gradientPos2->x) .', '. round($gradientPos2->y) .')');

    ExampleHelper::drawFuncLabels($vg, 50, 50, [
        "gradient({$gradientPos1->x}, {$gradientPos1->y}, {$gradientPos2->x}, {$gradientPos2->y}, color1, color2)",
        "rect(100, 100, ". (ExampleHelper::WIN_WIDTH - 200) .", ". (ExampleHelper::WIN_HEIGHT - 200) .")",
    ]);
    
    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);