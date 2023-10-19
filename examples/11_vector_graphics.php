<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/99_example_helpers.php';

use GL\Math\{Vec3, Vec4, Mat4};
use GL\Buffer\FloatBuffer;
use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGContext, VGColor};

// ensure mbstring extensin is loaded, we need it for the text rendering
if (!extension_loaded('mbstring')) {
    throw new \Exception('mbstring extension is required for this example');
}

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(0);


// Main Loop
// ---------------------------------------------------------------------------- 
while (!glfwWindowShouldClose($window))
{
    glClearColor(0, 0, 0, 1);
    // note how we are clearing both the DEPTH and COLOR buffers.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // begin a new frame using the window size as the viewport size
    $vg->beginFrame(ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT, 1);

    $w = 10;
    $h = 6;
    $xo = ExampleHelper::WIN_WIDTH / $w;
    $yo = ExampleHelper::WIN_HEIGHT / $h;
    
    for ($x = 0; $x < 10; $x++) {
        for ($y = 0; $y < 6; $y++) {
            $vg->beginPath();
            $vg->fillColor(new VGColor(
                0.5 + sin($x * 0.5) * 0.5,
                0.5 + sin($y * 0.5) * 0.5,
                1.0,
                1.0
            ));
            // circles animated using the current time as a seed
            $vg->circle(
                $xo * 0.5 + $x * $xo, // x
                $yo * 0.5 + $y * $yo, // y
                30 + sin(glfwGetTime() * 2 + $x * 0.5 + $y * 0.3) * 15 // radius
            );

            $vg->fill();
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