<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGContext, VGColor};

// ensure mbstring extensin is loaded, we need it for the text rendering
if (!extension_loaded('mbstring')) {
    throw new \Exception('mbstring extension is required for this example');
}

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

$phpglLogo = $vg->imageFromTexture(
    Texture2D::fromDisk(__DIR__ . '/../phpglfwlogo.png', Texture2D::CHANNEL_RGBA, false)
);

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

    $screenCenterX = ExampleHelper::WIN_WIDTH / 2;
    $screenCenterY = ExampleHelper::WIN_HEIGHT / 2;

    $vg->beginPath();
    $vg->rect(100, 100, 200, 200);
    $paint = $phpglLogo->makePaint(100, 100, 200, 200);
    $vg->fillPaint($paint);
    $vg->fill();

    ExampleHelper::drawLength($vg, 100, 100 - 20, 300, 100 - 20, "200x200", 'top');

    // slight smaller
    $vg->beginPath();
    $vg->rect(350, 100, 100, 100);
    $paint = $phpglLogo->makePaint(350, 100, 100, 100);
    $vg->fillPaint($paint);
    $vg->fill();

    ExampleHelper::drawLength($vg, 350, 100 - 20, 450, 100 - 20, "100x100", 'top');

    // even smaller
    $vg->beginPath();
    $vg->rect(500, 100, 50, 50);
    $paint = $phpglLogo->makePaint(500, 100, 50, 50);
    $vg->fillPaint($paint);
    $vg->fill();

    ExampleHelper::drawLength($vg, 500, 100 - 20, 550, 100 - 20, "50x50", 'top');

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);