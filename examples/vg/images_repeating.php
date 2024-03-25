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

$phpglLogoRepeat = $vg->imageFromTexture($logoTexture, VGImage::REPEAT_XY);
$phpglLogoRepeatX = $vg->imageFromTexture($logoTexture, VGImage::REPEAT_X);
$phpglLogoRepeatY = $vg->imageFromTexture($logoTexture, VGImage::REPEAT_Y);
$phpglLogoRepeatNone = $vg->imageFromTexture($logoTexture, VGImage::REPEAT_NONE);

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

    // split the screen into 4 quadrants
    $quadWidth = ExampleHelper::WIN_WIDTH / 4;

    // fill the first quadrant with a repeating image
    $vg->beginPath();
    $vg->rect(0, 0, $quadWidth, ExampleHelper::WIN_HEIGHT);
    $vg->fillPaint($phpglLogoRepeat->makePaintCentered($quadWidth / 2, ExampleHelper::WIN_HEIGHT / 2, 200, 200));
    $vg->fill();

    // fill the second quadrant with a X repeating image
    $vg->beginPath();
    $vg->rect($quadWidth, 0, $quadWidth, ExampleHelper::WIN_HEIGHT);
    $vg->fillPaint($phpglLogoRepeatY->makePaintCentered($quadWidth + $quadWidth / 2, ExampleHelper::WIN_HEIGHT / 2, 200, 200));
    $vg->fill();

    // fill the third quadrant with a Y repeating image
    $vg->beginPath();
    $vg->rect($quadWidth * 2, 0, $quadWidth, ExampleHelper::WIN_HEIGHT);
    $vg->fillPaint($phpglLogoRepeatX->makePaintCentered($quadWidth * 2 + $quadWidth / 2, ExampleHelper::WIN_HEIGHT / 2, 200, 200));
    $vg->fill();

    // fill the fourth quadrant with a non repeating image
    $vg->beginPath();
    $vg->rect($quadWidth * 3, 0, $quadWidth, ExampleHelper::WIN_HEIGHT);
    $vg->fillPaint($phpglLogoRepeatNone->makePaintCentered($quadWidth * 3 + $quadWidth / 2, ExampleHelper::WIN_HEIGHT / 2, 200, 200));
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
        'REPEAT_XY',
        'REPEAT_X',
        'REPEAT_Y',
        'REPEAT_NONE'
    ];

    $labelPadding = 50;

    for ($i = 0; $i < 4; $i++) {
        $vg->beginPath();
        $vg->fillColor(VGColor::white());
        $vg->roundedRect(
            $quadWidth * $i + $labelPadding,
            ExampleHelper::WIN_HEIGHT - 100,
            $quadWidth - $labelPadding * 2,
            100 - $labelPadding,
            10
        );
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