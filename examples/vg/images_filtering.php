<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor, VGImage};

// ensure mbstring extensin is loaded, we need it for the text rendering
if (!extension_loaded('mbstring')) {
    throw new \Exception('mbstring extension is required for this example');
}

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

$logoTexture = Texture2D::fromDisk(__DIR__ . '/../phpglfwlogo.png', Texture2D::CHANNEL_RGBA, false);

$phpglLogoNearest = $vg->imageFromTexture($logoTexture, VGImage::REPEAT_XY, VGImage::FILTER_NEAREST);
$phpglLogoLinear = $vg->imageFromTexture($logoTexture, VGImage::REPEAT_XY, VGImage::FILTER_LINEAR);

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

    // split the screen into 2 quadrants
    $quadWidth = ExampleHelper::WIN_WIDTH / 2;

    $zoom = 1.1 + sin(glfwGetTime());
    $textureSize = 3000 * $zoom;
    $xOffset = 650;

    // fill the first quadrant with a repeating image
    $vg->beginPath();
    $vg->rect(0, 0, $quadWidth, ExampleHelper::WIN_HEIGHT);
    $vg->fillPaint($phpglLogoNearest->makePaintCentered(($quadWidth / 2) + $xOffset, ExampleHelper::WIN_HEIGHT / 2, $textureSize, $textureSize));
    $vg->fill();

    // fill the second quadrant with a X repeating image
    $vg->beginPath();
    $vg->rect($quadWidth, 0, $quadWidth, ExampleHelper::WIN_HEIGHT);
    $vg->fillPaint($phpglLogoLinear->makePaintCentered(($quadWidth + $quadWidth / 2) + $xOffset, ExampleHelper::WIN_HEIGHT / 2, $textureSize, $textureSize));
    $vg->fill();

    // now render a simple line to seperate the quadrants
    $vg->beginPath();
    for ($i = 1; $i < 4; $i++) {
        $vg->moveTo($quadWidth * $i, 0);
        $vg->lineTo($quadWidth * $i, ExampleHelper::WIN_HEIGHT);
    }
    $vg->strokeColor(VGColor::black());
    $vg->strokeWidth(30);
    $vg->stroke();

    // and render some labels to explain what is going on
    $lables = [
        'FILTER_NEAREST',
        'FILTER_LINEAR',
    ];

    $labelPadding = 50;

    for ($i = 0; $i < 2; $i++) {
        $vg->beginPath();
        $vg->fillColor(VGColor::white());
        $vg->strokeColor(VGColor::black());
        $vg->roundedRect(
            $quadWidth * $i + $labelPadding,
            ExampleHelper::WIN_HEIGHT - 100,
            $quadWidth - $labelPadding * 2,
            100 - $labelPadding,
            10
        );
        $vg->strokeWidth(5);
        $vg->stroke();
        $vg->fill();

        $vg->beginPath();
        $vg->fillColor(VGColor::black());
        $vg->fontFaceId(ExampleHelper::getVGFontHandle($vg));
        $vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);
        $vg->fontSize(30);
        $vg->text($quadWidth * $i + $quadWidth / 2, ExampleHelper::WIN_HEIGHT - 75, $lables[$i]);
    }

    
    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);