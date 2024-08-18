<?php
/**
 * Noise explorer
 * A simple example that demonstrates how to use the noise functions, and how they look like.
 * 
 * @image      user_guide/noise/noise_demo.png
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

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

// a buffer to hold our noise data
$noiseBuffer = new FloatBuffer();
$noiseResolution = 256;
$noiseScale = 4.0;
$noiseAccelX = 0.0;
$noiseAccelY = 0.0;
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

// use arrow keys to move the noise
glfwSetKeyCallback($window, function($key, $scancode, $action, $mods) use (&$noiseAccelX, &$noiseAccelY, $noiseScale) {
    if ($action == GLFW_PRESS || $action == GLFW_REPEAT) {
        switch ($key) {
            case GLFW_KEY_LEFT:
                $noiseAccelX -= 0.01;
                break;
            case GLFW_KEY_RIGHT:
                $noiseAccelX += 0.01;
                break;
            case GLFW_KEY_UP:
                $noiseAccelY -= 0.01;
                break;
            case GLFW_KEY_DOWN:
                $noiseAccelY += 0.01;
                break;
        }
    }
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

    // UI Elements
    ExampleHelper::drawButtonGroup($vg, 100, ExampleHelper::WIN_HEIGHT - 100, [
        'perlin' => 'Perlin',
        'ridge' => 'Ridge',
        'fbm' => 'Fbm',
        'turbulence' => 'Turbulence',
        'island' => 'Island',
    ], $noiseType, function($type) use (&$noiseType, &$noiseScale) {
        $noiseType = $type;

        if ($noiseType == 'island') {
            $noiseScale = 1.0;
        }
    });

    // randomize the seed
    if (in_array($noiseType, ['perlin', 'island'])) {
        ExampleHelper::drawButton($vg, ExampleHelper::WIN_WIDTH - 125, 50, 'Randomize Seed', function() use (&$noiseSeed) {
            $noiseSeed = rand(0, 9999999);
        });
    }


    // update the noise offsets based on the acceleration
    $noiseOffsetX += $noiseAccelX * $noiseScale;
    $noiseOffsetY += $noiseAccelY * $noiseScale;

    // dampen the acceleration
    $noiseAccelX *= 0.9;
    $noiseAccelY *= 0.9;

    // create a noise texture
    if ($noiseType == 'perlin') {
        Noise::perlinFill2D($noiseBuffer, $noiseResolution, $noiseResolution, $noiseScale, $noiseOffsetX, $noiseOffsetY, 0, 0, $noiseSeed);
    } else if ($noiseType == 'ridge') {
        Noise::ridgeFill2D($noiseBuffer, $noiseResolution, $noiseResolution, $noiseScale, $noiseOffsetX, $noiseOffsetY);
    } else if ($noiseType == 'fbm') {
        Noise::fbmFill2D($noiseBuffer, $noiseResolution, $noiseResolution, $noiseScale, $noiseOffsetX, $noiseOffsetY);
    } else if ($noiseType == 'turbulence') {
        Noise::turbulenceFill2D($noiseBuffer, $noiseResolution, $noiseResolution, $noiseScale, $noiseOffsetX, $noiseOffsetY);
    } else if ($noiseType == 'island') {
        Noise::islandFill2D($noiseBuffer, $noiseResolution, $noiseResolution, $noiseSeed, $noiseScale, 1.2);
    }

    // save button
    ExampleHelper::drawButton($vg, ExampleHelper::WIN_WIDTH - 125, 100, 'Save', function() use ($noiseBuffer, $noiseResolution) {
        $texture = Texture2D::fromBuffer($noiseResolution, $noiseResolution, $noiseBuffer->quantizeToUChar(), Texture2D::CHANNEL_R);
        $texture->writePNG('noise.png');
    });

    // upload the texture to the GPU
    glBindTexture(GL_TEXTURE_2D, $noiseGlTex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, $noiseResolution, $noiseResolution, 0, GL_RED, GL_FLOAT, $noiseBuffer);

    // create a vgTexture from the noise texture
    $vgImage = $vg->imageFromHandle($noiseGlTex, $noiseResolution, $noiseResolution);

    $centerX = ExampleHelper::WIN_WIDTH * 0.5;
    $centerY = ExampleHelper::WIN_HEIGHT * 0.5;

    $noiseX = $centerX - $noiseResolution * 0.5;
    $noiseY = $centerY - $noiseResolution * 0.5;

    $paint = $vgImage->makePaint($noiseX, $noiseY, $noiseResolution, $noiseResolution);

    $vg->beginPath();
    $vg->rect($noiseX, $noiseY, $noiseResolution, $noiseResolution);
    $vg->fillPaint($paint);
    $vg->fill();

    ExampleHelper::drawFuncLabels($vg, 50, 50, [
        "$noiseType($noiseResolution, $noiseResolution, $noiseScale, $noiseOffsetX, $noiseOffsetY);",
    ]);

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
}

ExampleHelper::stop($window);