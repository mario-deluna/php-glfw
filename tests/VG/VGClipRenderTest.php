<?php

namespace GL\Tests\VG;

use GL\Buffer\UByteBuffer;
use GL\Tests\GLFunctions\GLFunctionsTestCase;
use GL\VectorGraphics\SVGImage;
use GL\VectorGraphics\VGColor;
use GL\VectorGraphics\VGContext;

/**
 * Renders into the offscreen framebuffer and reads pixels back to verify that an
 * active nvgClip() region constrains strokes and text, not just fills.
 *
 * @group glfwinit
 */
#[\PHPUnit\Framework\Attributes\Group('glfwinit')]
class VGClipRenderTest extends GLFunctionsTestCase
{
    private int $fbWidth = 0;
    private int $fbHeight = 0;

    /**
     * begins a frame using the real framebuffer size (handles hi-dpi offscreen
     * buffers) and clears colour + stencil to a known black state.
     */
    private function beginClearedFrame(VGContext $vg) : void
    {
        glfwGetFramebufferSize($this->window, $this->fbWidth, $this->fbHeight);

        glViewport(0, 0, $this->fbWidth, $this->fbHeight);
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        $pixelRatio = $this->fbWidth / self::TEST_VIEW_WIDTH;
        $vg->beginFrame(self::TEST_VIEW_WIDTH, self::TEST_VIEW_HEIGHT, $pixelRatio);
    }

    /**
     * reads back the red channel (0..255) of a single framebuffer pixel. x/y are
     * given in NanoVG coordinates (top-left origin) and converted to the
     * bottom-up framebuffer space.
     */
    private function readRed(float $nvgX, float $nvgY) : int
    {
        glFinish();

        $ratio = $this->fbWidth / self::TEST_VIEW_WIDTH;
        $fbX = (int) round($nvgX * $ratio);
        $fbY = $this->fbHeight - 1 - (int) round($nvgY * $ratio);

        $buf = new UByteBuffer();
        glReadPixels($fbX, $fbY, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, $buf);

        return $buf[0];
    }

    /**
     * clips the current path to the left half of the view.
     */
    private function clipLeftHalf(VGContext $vg) : void
    {
        $vg->beginPath();
        $vg->rect(0, 0, self::TEST_VIEW_WIDTH / 2, self::TEST_VIEW_HEIGHT);
        $vg->clip();
    }

    /**
     * draws a thick white horizontal line spanning the full width at mid-height.
     */
    private function drawFullWidthStroke(VGContext $vg) : void
    {
        $midY = self::TEST_VIEW_HEIGHT / 2;
        $vg->beginPath();
        $vg->moveTo(0, $midY);
        $vg->lineTo(self::TEST_VIEW_WIDTH, $midY);
        $vg->strokeColor(new VGColor(1.0, 1.0, 1.0, 1.0));
        $vg->strokeWidth(10.0);
        $vg->stroke();
    }

    public static function strokeFlagProvider() : array
    {
        return [
            'plain strokes'   => [VGContext::ANTIALIAS],
            'stencil strokes' => [VGContext::ANTIALIAS | VGContext::STENCIL_STROKES],
        ];
    }

    /**
     * @dataProvider strokeFlagProvider
     */
    #[\PHPUnit\Framework\Attributes\DataProvider('strokeFlagProvider')]
    public function testStrokeIsClipped(int $flags) : void
    {
        $vg = new VGContext($flags);

        $this->beginClearedFrame($vg);
        $this->clipLeftHalf($vg);
        $this->drawFullWidthStroke($vg);
        $vg->endFrame();

        $midY = self::TEST_VIEW_HEIGHT / 2;

        // inside the clip (left) the stroke must be visible
        $this->assertGreaterThan(200, $this->readRed(self::TEST_VIEW_WIDTH * 0.25, $midY),
            'stroke should be visible inside the clip region');

        // outside the clip (right) the stroke must be cut off - stays black
        $this->assertLessThan(50, $this->readRed(self::TEST_VIEW_WIDTH * 0.75, $midY),
            'stroke must not bleed outside the clip region');
    }

    /**
     * sensitivity guard: without a clip the same stroke reaches the right half,
     * proving the clipped test above is meaningful.
     */
    public function testStrokeReachesRightHalfWithoutClip() : void
    {
        $vg = new VGContext(VGContext::ANTIALIAS);

        $this->beginClearedFrame($vg);
        $this->drawFullWidthStroke($vg);
        $vg->endFrame();

        $midY = self::TEST_VIEW_HEIGHT / 2;
        $this->assertGreaterThan(200, $this->readRed(self::TEST_VIEW_WIDTH * 0.75, $midY),
            'without a clip the stroke should cover the right half');
    }

    /**
     * text is drawn via the triangles path - it must respect the clip too.
     */
    public function testTextIsClipped() : void
    {
        $vg = new VGContext(VGContext::ANTIALIAS);

        $font = $vg->createFont('inconsolata', __DIR__ . '/../../examples/font/inconsolata/Inconsolata-Regular.ttf');
        $this->assertGreaterThanOrEqual(0, $font, 'test font must load');

        $this->beginClearedFrame($vg);
        $this->clipLeftHalf($vg);

        $vg->fontFaceId($font);
        $vg->fontSize(120.0);
        $vg->fillColor(new VGColor(1.0, 1.0, 1.0, 1.0));
        // a long run of wide glyphs so text certainly crosses the clip edge
        $vg->text(10, self::TEST_VIEW_HEIGHT / 2 + 40, 'MMMMMMMMMMMMMMMM');

        $vg->endFrame();
        glFinish();

        // scan a vertical band around mid-height, once for the left half and once
        // for the right half, and record the brightest red pixel found in each.
        [$leftMax, $rightMax] = $this->scanHalvesMaxRed();

        $this->assertGreaterThan(200, $leftMax, 'text should be visible inside the clip region');
        $this->assertLessThan(50, $rightMax, 'text must not bleed outside the clip region');
    }

    /**
     * regression: fills were already clipped - keep it that way (also confirms the
     * test harness sets up clips correctly).
     */
    public function testFillIsClipped() : void
    {
        $vg = new VGContext(VGContext::ANTIALIAS);

        $this->beginClearedFrame($vg);
        $this->clipLeftHalf($vg);

        $vg->beginPath();
        $vg->rect(0, 0, self::TEST_VIEW_WIDTH, self::TEST_VIEW_HEIGHT);
        $vg->fillColor(new VGColor(1.0, 1.0, 1.0, 1.0));
        $vg->fill();

        $vg->endFrame();

        $midY = self::TEST_VIEW_HEIGHT / 2;
        $this->assertGreaterThan(200, $this->readRed(self::TEST_VIEW_WIDTH * 0.25, $midY),
            'fill should be visible inside the clip region');
        $this->assertLessThan(50, $this->readRed(self::TEST_VIEW_WIDTH * 0.75, $midY),
            'fill must not bleed outside the clip region');
    }

    /**
     * reads back the full framebuffer once and returns [leftMaxRed, rightMaxRed]
     * across a band of rows around mid-height.
     */
    private function scanHalvesMaxRed() : array
    {
        $buf = new UByteBuffer();
        glReadPixels(0, 0, $this->fbWidth, $this->fbHeight, GL_RGBA, GL_UNSIGNED_BYTE, $buf);

        $ratio = $this->fbWidth / self::TEST_VIEW_WIDTH;
        $midRow = (int) ($this->fbHeight / 2);
        $band = (int) round(50 * $ratio);
        $clipEdge = (int) round((self::TEST_VIEW_WIDTH / 2) * $ratio);

        $leftMax = 0;
        $rightMax = 0;

        for ($y = max(0, $midRow - $band); $y < min($this->fbHeight, $midRow + $band); $y++) {
            for ($x = 0; $x < $this->fbWidth; $x++) {
                $red = $buf[($y * $this->fbWidth + $x) * 4];
                if ($x < $clipEdge) {
                    if ($red > $leftMax) $leftMax = $red;
                } else {
                    if ($red > $rightMax) $rightMax = $red;
                }
            }
        }

        return [$leftMax, $rightMax];
    }

    /**
     * an SVG whose single shape references a mask, so drawSVG exercises the
     * internal nvgClip()/nvgRestoreClip() mask path.
     */
    private function makeMaskedSvg() : SVGImage
    {
        return SVGImage::fromString(
            '<svg width="100" height="100" xmlns="http://www.w3.org/2000/svg">'
            . '<mask id="m"><rect x="0" y="0" width="50" height="100" fill="#ffffff"/></mask>'
            . '<rect x="0" y="0" width="100" height="100" fill="#00ff00" mask="url(#m)"/>'
            . '</svg>'
        );
    }

    /**
     * confirms the mask fixture actually clips (the shape's right half is masked
     * out). This guarantees the drawSVG mask path — and therefore the clip
     * save/restore under test below — is genuinely exercised, not skipped because
     * the mask went unrecognised.
     */
    public function testDrawSVGMaskClipsShape() : void
    {
        $vg = new VGContext(VGContext::ANTIALIAS);
        $svg = $this->makeMaskedSvg();

        $this->beginClearedFrame($vg);
        // green shape masked to its own left 50px, drawn scaled to the full view
        $vg->drawSVG($svg, 0, 0, self::TEST_VIEW_WIDTH, self::TEST_VIEW_HEIGHT);
        $vg->endFrame();

        $buf = new UByteBuffer();
        glFinish();
        glReadPixels(0, 0, $this->fbWidth, $this->fbHeight, GL_RGBA, GL_UNSIGNED_BYTE, $buf);
        // green channel: left half of the shape is kept, right half masked away
        $midRow = (int) ($this->fbHeight / 2);
        $ratio = $this->fbWidth / self::TEST_VIEW_WIDTH;
        $leftG  = $buf[($midRow * $this->fbWidth + (int) round(self::TEST_VIEW_WIDTH * 0.25 * $ratio)) * 4 + 1];
        $rightG = $buf[($midRow * $this->fbWidth + (int) round(self::TEST_VIEW_WIDTH * 0.75 * $ratio)) * 4 + 1];

        $this->assertGreaterThan(200, $leftG, 'masked shape should be visible in its unmasked (left) half');
        $this->assertLessThan(50, $rightG, 'masked shape must be clipped away in its masked (right) half');
    }

    /**
     * regression: drawSVG used to destroy the caller's clip via nvgResetClip when a
     * shape carried a mask. It must now snapshot/restore the clip so drawing after
     * drawSVG stays clipped. Draw a masked SVG inside a left-half clip, then a
     * full-width fill: the right half must stay black.
     */
    public function testDrawSVGPreservesCallerClip() : void
    {
        $vg = new VGContext(VGContext::ANTIALIAS);
        $svg = $this->makeMaskedSvg();

        $this->beginClearedFrame($vg);
        $this->clipLeftHalf($vg);

        // this masked draw previously cleared the clip outright
        $vg->drawSVG($svg);

        // a full-width fill drawn afterwards must still respect the caller's clip
        $vg->beginPath();
        $vg->rect(0, 0, self::TEST_VIEW_WIDTH, self::TEST_VIEW_HEIGHT);
        $vg->fillColor(new VGColor(1.0, 0.0, 0.0, 1.0));
        $vg->fill();

        $vg->endFrame();

        $midY = self::TEST_VIEW_HEIGHT / 2;
        $this->assertGreaterThan(200, $this->readRed(self::TEST_VIEW_WIDTH * 0.25, $midY),
            'fill after drawSVG should be visible inside the clip region');
        $this->assertLessThan(50, $this->readRed(self::TEST_VIEW_WIDTH * 0.75, $midY),
            'fill after drawSVG must not bleed outside the caller clip that drawSVG was supposed to preserve');
    }
}
