<?php
/**
 * Noise Grid
 * Just a simple & fun visual effect that can be achieved with noise functions.
 * 
 * @category   Noise
 */
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Buffer\FloatBuffer;
use GL\Geometry\ObjFileParser\Texture;
use GL\Math\GLM;
use GL\Math\Vec2;
use GL\Noise;
use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor, VGImage};
use phpDocumentor\Reflection\DocBlock\Tags\Var_;

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

// a buffer to hold our noise data
$noiseBuffer = new FloatBuffer();
$noiseBuffer2 = new FloatBuffer();
$noiseResolution = 128;
$noiseScale = 4.0;
$noiseOffsetX = 0.0;
$noiseOffsetY = 0.0;
$noiseSeed = 42;

// noise type for demo
$noiseType = 'perlin';

// make a noise GPU texture
$noiseGlTex = 0;
glGenTextures(1, $noiseGlTex);
glBindTexture(GL_TEXTURE_2D, $noiseGlTex);
// no repeating
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// listen for scroll events to change the scale of noise
glfwSetScrollCallback($window, function($xOffset, $yOffset) use (&$noiseScale) {
    // zoom in out logarithmically
    $noiseScale *= 1 + $yOffset * 0.1;
    $noiseScale = min(max($noiseScale, 0.01), 100);
});


// Main Loop
// ---------------------------------------------------------------------------- 
while (!glfwWindowShouldClose($window))
{
    // clear
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glfwPollEvents();

    // fetch the content scale of the window
    $contentScaleX;
    $contentScaleY;
    glfwGetWindowContentScale($window, $contentScaleX, $contentScaleY);

    // begin a new frame using the window size as the viewport size
    $vg->beginFrame(ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT, $contentScaleX);

    ExampleHelper::drawCoordSys($vg);

    $noiseOffsetX += 0.005;
    $noiseOffsetY += 0.005;

    Noise::ridgeFill2D($noiseBuffer, $noiseResolution, $noiseResolution, $noiseScale, $noiseOffsetX, $noiseOffsetY);
    Noise::perlinFill2D($noiseBuffer2, $noiseResolution, $noiseResolution, $noiseScale, -$noiseOffsetX, -$noiseOffsetY);

    // we render one dot per 20 pixels
    $dotSize = 20;
    $xDots = (int) (ExampleHelper::WIN_WIDTH / $dotSize);
    $yDots = (int) (ExampleHelper::WIN_HEIGHT / $dotSize);

    for ($x = 0; $x < $xDots; $x++) {
        for ($y = 0; $y < $yDots; $y++) {

            // calulcate the relative x and y position inside of the screen
            $xRel = $x / $xDots;
            $yRel = $y / $yDots;

            // sample the noise buffer at the relative position
            $noiseYIndex = (int) ($yRel * $noiseResolution);
            $noiseXIndex = (int) ($xRel * $noiseResolution);
            $value = $noiseBuffer[$noiseYIndex * $noiseResolution + $noiseXIndex];
            $value2 = $noiseBuffer2[$noiseYIndex * $noiseResolution + $noiseXIndex];

            $finalValue = ($value + $value2) / 2;

            $vg->beginPath();
            $vg->fillColor((new VGColor($value, $value2, $value, 1.0))->lighten(0.5));
            $vg->circle(ExampleHelper::WIN_WIDTH * $xRel, ExampleHelper::WIN_HEIGHT * $yRel, $dotSize * $finalValue);
            $vg->fill();
        }
    }

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
}

ExampleHelper::stop($window);