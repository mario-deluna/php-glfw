<?php
/**
 * Text Alignment
 * 
 * This interactive example shows how to align text horizontally and vertically.
 * 
 * @category   Text
 * @image      user_guide/vg/text/text_align.gif
 * @thumbnail  examples/vg/{example}.png
 */

/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor};

// ensure mbstring extensin is loaded, we need it for the text rendering
if (!extension_loaded('mbstring')) {
    throw new \Exception('mbstring extension is required for this example');
}

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);
$fontHandle = $vg->createFont('inconsolata', __DIR__ . '/../font/inconsolata/Inconsolata-Regular.ttf');

// draw a button group to show the different alignments
$horizontalAlignment = 'LEFT';
$verticalAlignment = 'TOP';
$currentText = 'Hello Ronon!';

glfwSetKeyCallback($window, function($key, $scancode, $action, $mods) use (&$currentText) {
    if ($action === GLFW_PRESS) {
        if ($key === GLFW_KEY_BACKSPACE) {
            $currentText = mb_substr($currentText, 0, -1);
        } else if ($key === GLFW_KEY_ENTER) {
            $currentText .= "\n";
        }
    }
});

glfwSetCharCallback($window, function($char) use (&$currentText) {
    $currentText .= mb_chr($char);
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

    $screenCenterX = ExampleHelper::WIN_WIDTH / 2;
    $screenCenterY = ExampleHelper::WIN_HEIGHT / 2;

    // we translate the coordinate system to the center of the screen
    $vg->translate($screenCenterX, $screenCenterY);

    ExampleHelper::drawCoordSys($vg);
    $offset = ExampleHelper::drawButtonGroup($vg, 100, ExampleHelper::WIN_HEIGHT - 100, [
        'LEFT' => 'Left',
        'CENTER' => 'Center',
        'RIGHT' => 'Right',
    ], $horizontalAlignment, function($alignment) use (&$horizontalAlignment) {
        $horizontalAlignment = $alignment;
    });

    ExampleHelper::drawButtonGroup($vg, 200 + $offset, ExampleHelper::WIN_HEIGHT - 100, [
        'TOP' => 'Top',
        'MIDDLE' => 'Middle',
        'BASELINE' => 'Baseline',
        'BOTTOM' => 'Bottom',
    ], $verticalAlignment, function($alignment) use (&$verticalAlignment) {
        $verticalAlignment = $alignment;
    });

    $vg->fontSize(32);
    $h = constant(VGAlign::class . '::' . $horizontalAlignment);
    $v = constant(VGAlign::class . '::' . $verticalAlignment);
    $vg->textAlign($h | $v);

    // blinking cursor suffix every 0.5 seconds
    $suffix = '';
    if (floor(glfwGetTime() * 2) % 2 === 0) {
        $suffix = '_';
    }

    $offset = $vg->text(0, 0, $currentText);
    $vg->text($offset, 0, $suffix);

    // draw a label of the actual values
    ExampleHelper::drawFuncLabels($vg, 50, 50, [
        "translate($screenCenterX, $screenCenterY)",
        "textAlign(VGAlign::$horizontalAlignment | VGAlign::$verticalAlignment)",
    ]);

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);