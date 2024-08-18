<?php
/**
 * Radial Gradient
 * This example demonstrates how to draw a radial gradient using the PHP GLFW Vector Graphics API.
 * 
 * @category   Gradients
 */
/**
 * We utilize the example helpers here to focus on what matter in this specific example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Math\GLM;
use GL\Math\Vec2;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor, VGImage};

// ensure mbstring extension is loaded, we need it for the text rendering
if (!extension_loaded('mbstring')) {
    throw new \Exception('mbstring extension is required for this example');
}

$window = ExampleHelper::begin();

// initialize a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

$gradientCenter = new Vec2(300, 300);
$gradientRadius = 150.0;
$gradientColor1 = new VGColor(0.051, 0.682, 0.914, 1.0);
$gradientColor2 = new VGColor(0.169, 0.961, 0.596, 1.0);

$isDraggingCenter = false;
$currentMousePos = new Vec2(0, 0);

glfwSetMouseButtonCallback($window, function($button, $action, $mods) use($window, &$isDraggingCenter, $gradientCenter, $currentMousePos) {
    if ($button == GLFW_MOUSE_BUTTON_LEFT && $action == GLFW_PRESS) {
        if ($currentMousePos->distanceTo($gradientCenter) < 10) {
            $isDraggingCenter = true;
        }
    } else if ($button == GLFW_MOUSE_BUTTON_LEFT && $action == GLFW_RELEASE) {
        $isDraggingCenter = false;
    }
});

glfwSetScrollCallback($window, function($xOffset, $yOffset) use (&$gradientRadius) {
    // increase or decrease the radius of the gradient
    $gradientRadius *= 1 + $yOffset * 0.1;
    $gradientRadius = min(max($gradientRadius, 10), 1000);
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

    if ($isDraggingCenter) {
        $gradientCenter->x = $currentMousePos->x;
        $gradientCenter->y = $currentMousePos->y;
    }

    // create a radial gradient
    $gradientPaint = $vg->radialGradient(
        $gradientCenter->x,
        $gradientCenter->y,
        0, // inner radius
        $gradientRadius, // outer radius
        $gradientColor1,
        $gradientColor2
    );

    // fill the screen with the gradient
    $vg->beginPath();
    $vg->rect(50, 150, ExampleHelper::WIN_WIDTH - 100, ExampleHelper::WIN_HEIGHT - 300);
    $vg->fillPaint($gradientPaint);
    $vg->fill();

    ExampleHelper::drawPoint($vg, $gradientCenter->x, $gradientCenter->y, 'Center('. round($gradientCenter->x) .', '. round($gradientCenter->y) .')');

    ExampleHelper::drawFuncLabels($vg, 50, 50, [
        "radialGradient({$gradientCenter->x}, {$gradientCenter->y}, 0, {$gradientRadius}, color1, color2)",
        "rect(50, 150, ". (ExampleHelper::WIN_WIDTH - 100) .", ". (ExampleHelper::WIN_HEIGHT - 300) .")",
    ]);
    
    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the window's framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);
