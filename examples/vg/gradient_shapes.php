<?php
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

$gradientPos1 = new Vec2(50, 150);
$gradientPos2 = new Vec2(350, 450);
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
    ExampleHelper::drawCoordSys($vg);

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
    $paint = $vg->linearGradient(
        $gradientPos1->x,
        $gradientPos1->y,
        $gradientPos2->x,
        $gradientPos2->y,
        $gradientColor1,
        $gradientColor2
    );

    // fill the screen with the gradient
    $vg->beginPath();

    // // rectangle
    // $vg->beginPath();
    // $vg->fillPaint($paint);
    // $vg->rect(50, 150, 300, 300);
    // $vg->fill();
    
    // // circle
    // $vg->beginPath();
    // $vg->fillPaint($paint);
    // $vg->circle(200, 300, 150);
    // $vg->fill();

    // phplogo 
//     nvgScale(vg, 0, 0); // This actually scales down everything to a point where it won't be visible.
// nvgTranslate(vg, 0, 1);

// // Set stroke style
// nvgStrokeColor(vg, nvgRGBA(0, 0, 0, 0)); // Sets stroke color to transparent.
// nvgStrokeWidth(vg, 1.0); // Default stroke width, adjust if needed.
// nvgLineCap(vg, NVG_PROJECT); // Sets the line cap to 'project'.
// nvgLineJoin(vg, NVG_MITER); // Sets the line join to 'miter'.

// // First Path
// nvgBeginPath(vg);
// nvgMoveTo(vg, 7.579, 10.123);
// nvgLineTo(vg, 21.783, 10.123);
// nvgBezierTo(vg, 25.952, 10.158, 28.973, 11.36, 30.846, 13.727);
// nvgBezierTo(vg, 32.719, 16.094, 33.337, 19.327, 32.701, 23.426);
// nvgBezierTo(vg, 32.454, 25.299, 31.906, 27.136, 31.058, 28.938);
// nvgBezierTo(vg, 30.245, 30.74, 29.115, 32.365, 27.666, 33.814);
// nvgBezierTo(vg, 25.899, 35.651, 24.009, 36.817, 21.995, 37.312);
// nvgBezierTo(vg, 19.981, 37.807, 17.896, 38.054, 15.741, 38.054);
// nvgLineTo(vg, 9.381, 38.054);
// nvgLineTo(vg, 7.367, 48.124);
// nvgLineTo(vg, 0, 48.124);
// nvgClosePath(vg); // Closes the path and connects it back to the starting point.
// nvgStroke(vg); // Apply the stroke.

// // Second Path (repeat pattern for each shape, updating coordinates and bezier controls)
// nvgBeginPath(vg);
// nvgMoveTo(vg, 41.093, 0);
// nvgLineTo(vg, 48.407, 0);
// nvgLineTo(vg, 46.34, 10.123);
// nvgLineTo(vg, 52.912, 10.123);
// nvgBezierTo(vg, 56.516, 10.194, 59.201, 10.936, 60.968, 12.349);
// nvgBezierTo(vg, 62.77, 13.762, 63.3, 16.448, 62.558, 20.405);
// nvgLineTo(vg, 59.007, 38.054);
// nvgLineTo(vg, 51.587, 38.054);
// nvgLineTo(vg, 54.979, 21.2);
// nvgBezierTo(vg, 55.332, 19.433, 55.226, 18.179, 54.661, 17.437);
// nvgBezierTo(vg, 54.096, 16.695, 52.877, 16.324, 51.004, 16.324);
// nvgLineTo(vg, 45.121, 16.271);
// nvgLineTo(vg, 40.775, 38.054);
// nvgLineTo(vg, 33.461, 38.054);
// nvgClosePath(vg);
// nvgStroke(vg);

// // Third Path
// nvgBeginPath(vg);
// nvgMoveTo(vg, 70.412, 10.123);
// // ... include all other commands for this shape following the pattern above
// nvgClosePath(vg);
// nvgStroke(vg);
    $vg->scale(0, 0);
    $vg->translate(0, 1);
    $vg->strokeColor(new VGColor(0, 0, 0, 0));
    $vg->strokeWidth(1.0);
    $vg->lineCap(VGContext::PROJECT);
    $vg->lineJoin(VGContext::MITER);


    ExampleHelper::drawLength($vg, $gradientPos1->x, $gradientPos1->y, $gradientPos2->x, $gradientPos2->y, '');
    ExampleHelper::drawPoint($vg, $gradientPos1->x, $gradientPos1->y, 'p1('. round($gradientPos1->x) .', '. round($gradientPos1->y) .')');
    ExampleHelper::drawPoint($vg, $gradientPos2->x, $gradientPos2->y, 'P2('. round($gradientPos2->x) .', '. round($gradientPos2->y) .')');

    ExampleHelper::drawFuncLabels($vg, 50, 50, [
        "gradient({$gradientPos1->x}, {$gradientPos1->y}, {$gradientPos2->x}, {$gradientPos2->y}, color1, color2)",
        // "rect(50, 150, 300, 300)",
        "circle(200, 300, 150)",
    ]);
    
    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);