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
    glClearColor(0, 0, 0, 1);
    // note how we are clearing both the DEPTH and COLOR buffers.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // begin a new frame using the window size as the viewport size
    $vg->beginFrame(ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT, 1);

    $screenCenterX = ExampleHelper::WIN_WIDTH / 2;
    $screenCenterY = ExampleHelper::WIN_HEIGHT / 2;

    // wirst we translate the coordinate system to the center of the screen
    // after this operation 0,0 will be the center of the screen and not the top left corner
    $vg->translate($screenCenterX, $screenCenterY);
    // for this example we will rotate the coordinate system around the center of the screen
    $vg->rotate(glfwGetTime() * 0.3);

    // now we can draw a rectangle, as we are in the center of the screen
    // and we want to draw a rectangle that is 200x200 pixels in size we need to
    // offset the rectangle by -100,-100
    $vg->beginPath();
    $vg->rect(-100, -100, 200, 200);
    
    // now we create a paint from the php logo texture
    // we rotate the texture aswell to showcase why we might want to do this
    $paint = $phpglLogo->makePaintCentered(0, 0, 100, 100, glfwGetTime(), 1.0);
    $vg->fillPaint($paint);
    $vg->fill();

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);