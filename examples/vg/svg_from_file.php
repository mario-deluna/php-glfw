<?php
/**
 * Loading and drawing an SVG file with `SVGImage` + `VGContext::drawSVG()`.
 *
 * Unlike `svg.php` (which hardcodes bezier paths that were manually exported from an SVG),
 * this example parses a real `.svg` file at runtime using nanosvg and renders it as crisp,
 * resolution independent vector paths.
 *
 * Here we load the official PHP-GLFW logo (`docs/logo.svg`) and draw it:
 *   - once, large and gently pulsing in the center of the window
 *   - as a row of thumbnails at increasing sizes to show it stays sharp at any scale
 *
 * Note: only solid fills and strokes are rendered. Gradient paints, `<mask>` and
 * `clip-path` are not supported by the parser integration (yet), so complex SVGs may
 * look slightly different from a full SVG renderer. The logo uses solid fills only.
 *
 * We utilize the example helpers here to focus on what matters in this specific example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\VectorGraphics\{VGAlign, VGContext, VGColor, SVGImage};

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

// Parse the SVG file ONCE, outside of the render loop. The resulting SVGImage holds the
// parsed shapes and can be drawn as often as you like without re-parsing.
$logo = SVGImage::fromDisk(__DIR__ . '/../../docs/logo.svg');

echo "Loaded logo.svg with native size: {$logo->width} x {$logo->height}\n";

// the logos aspect ratio, so we can scale it without distortion
$logoAspect = $logo->height / $logo->width;

// Main Loop
// ----------------------------------------------------------------------------
while (!glfwWindowShouldClose($window))
{
    // clear
    glClearColor(0.04, 0.09, 0.15, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // fetch the content scale of the window (for hi-dpi / retina displays)
    $contentScaleX = 1.0;
    $contentScaleY = 1.0;
    glfwGetWindowContentScale($window, $contentScaleX, $contentScaleY);

    // begin a new frame using the window size as the viewport size
    $vg->beginFrame(ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT, $contentScaleX);

    $time = glfwGetTime();

    // make text rendering available
    $vg->fontFaceId(ExampleHelper::getVGFontHandle($vg));

    // Title
    // ------------------------------------------------------------------------
    $vg->fontSize(28);
    $vg->fillColor(VGColor::white());
    $vg->textAlign(VGAlign::LEFT | VGAlign::TOP);
    $vg->text(40, 30, "SVGImage::fromDisk() + VGContext::drawSVG()");

    $vg->fontSize(16);
    $vg->fillColor(VGColor::lightGray());
    $vg->text(40, 66, sprintf("docs/logo.svg  (native %d x %d)  -  drawn as real vector paths, crisp at any size", $logo->width, $logo->height));

    // Big, gently pulsing logo in the center
    // ------------------------------------------------------------------------
    $bigWidth = 360 + sin($time * 1.5) * 30;   // pulse the size to show it stays sharp
    $bigHeight = $bigWidth * $logoAspect;
    $bigX = (ExampleHelper::WIN_WIDTH - $bigWidth) / 2;
    $bigY = 150;

    $vg->drawSVG($logo, $bigX, $bigY, $bigWidth, $bigHeight);

    // A row of thumbnails at increasing sizes
    // ------------------------------------------------------------------------
    $sizes = [32, 48, 64, 96, 128];
    $cursorX = 60;
    $rowY = ExampleHelper::WIN_HEIGHT - 200;

    $vg->fontSize(16);
    $vg->fillColor(VGColor::white());
    $vg->textAlign(VGAlign::LEFT | VGAlign::TOP);
    $vg->text($cursorX, $rowY - 34, "Same SVGImage drawn at different sizes:");

    foreach ($sizes as $size) {
        $w = $size;
        $h = $size * $logoAspect;

        // draw the logo scaled to the thumbnail size
        $vg->drawSVG($logo, $cursorX, $rowY, $w, $h);

        // size label underneath
        $vg->fontSize(13);
        $vg->fillColor(VGColor::lightGray());
        $vg->textAlign(VGAlign::LEFT | VGAlign::TOP);
        $vg->text($cursorX, $rowY + $h + 8, "{$size}px");

        $cursorX += $w + 40;
    }

    // draw the logo once more at its NATIVE size in the bottom right (no w/h given)
    // ------------------------------------------------------------------------
    $vg->fontSize(14);
    $vg->fillColor(VGColor::lightGray());
    $vg->textAlign(VGAlign::RIGHT | VGAlign::TOP);
    $vg->text(ExampleHelper::WIN_WIDTH - 40, $rowY - 34, "native size (no width/height argument) ->");

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);
