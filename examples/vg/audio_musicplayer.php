<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Audio\Sound;
use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor};

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

// init audio engine
$audioEngine = new \GL\Audio\Engine();

// current sound
class Playback {
    public function __construct(
        public Sound $sound,
        public string $soundFile,
    ) {}
}

class Player {
    public function __construct(
        public ?Playback $playback = null,
    ) {}
}

$player = new Player();

// register a drop callback
glfwSetDropCallback($window, function($count, $paths) use ($audioEngine, &$player) {
    if (!isset($paths[0])) {
        return;
    }

    $effectivePath = $paths[0];

    // check if the file exists
    if (!file_exists($effectivePath)) {
        return;
    }
    
    // try to load the sound
    $player->playback = new Playback(
        $audioEngine->soundFromDisk($effectivePath),
        $effectivePath,
    );
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

    ExampleHelper::drawCoordSys($vg);

    if (!$player->playback) {
        $vg->fontSize(32);
        $vg->fillColor(VGColor::white());
        $vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);
        $vg->text(
            ExampleHelper::WIN_WIDTH * 0.5,
            ExampleHelper::WIN_HEIGHT * 0.5,
            "Drop a sound file (.wav, .mp3) here to play it."
        );
    }
    else {
        ExampleHelper::drawFuncLabels($vg, 100, 50, [
            sprintf("sound(%s, %s)", basename($player->playback->soundFile), $player->playback->sound->isPlaying() ? 'playing' : 'stopped'),
        ]);

        // playback progress
        $x = 100;
        $y = 100;

        $playbackCursor = $player->playback->sound->getCursor();
        $playbackLength = $player->playback->sound->getLength();
        $playbackProgress = $playbackCursor / $playbackLength;

        $vg->fillColor(VGColor::white());
        $vg->textAlign(VGAlign::LEFT | VGAlign::MIDDLE);
        $vg->text($x, $y, sprintf("Progress: %.2f of %.2f (%.2f%%)", $playbackCursor, $playbackLength, $playbackProgress * 100));
        $y += 20;
        $vg->text($x, $y, sprintf("PCM: %d of %d", $player->playback->sound->getCursorPCM(), $player->playback->sound->getLengthPCM()));
        $y += 30;

        // render a little progress bar
        $progressBarHeight = 50;
        $progressBarWidth = ExampleHelper::WIN_WIDTH - ($x * 2);

        // when mouse is down inside of the progress bar we seek to the position
        if (glfwGetMouseButton($window, GLFW_MOUSE_BUTTON_LEFT) === GLFW_PRESS) {
            $cursorX;
            $cursorY;
            glfwGetCursorPos($window, $cursorX, $cursorY);
            if ($cursorX >= $x && $cursorX <= $x + $progressBarWidth && $cursorY >= $y && $cursorY <= $y + $progressBarHeight) {
                $playbackProgress = ($cursorX - $x) / $progressBarWidth;

                // seek to the position
                $player->playback->sound->seekTo($playbackProgress * $playbackLength);
            }
        }

        $vg->strokeColor(VGColor::white());
        $vg->beginPath();
        $vg->rect($x, $y, $progressBarWidth, $progressBarHeight);
        $vg->strokeWidth(2);
        $vg->stroke();

        // render a red cursor
        $vg->strokeColor(VGColor::red());
        $vg->beginPath();
        $cursorX = $x + $progressBarWidth * $playbackProgress;
        $vg->moveTo($cursorX, $y - 5);
        $vg->lineTo($cursorX, $y + $progressBarHeight + 5);
        $vg->strokeWidth(5);
        $vg->stroke();


        // button group at bottom
        $y = ExampleHelper::WIN_HEIGHT - 100;
        $x = 100;

        $x = ExampleHelper::drawButton($vg, $x, $y, 'Play', function() use ($player) {
            $player->playback->sound->play();
        }, 'left');

        $x += 20;

        $x = ExampleHelper::drawButton($vg, $x, $y, 'Pause', function() use ($player) {
            $player->playback->sound->stop();
        }, 'left');

        $x += 20;

        // $x = ExampleHelper::drawButton($vg, $x, $y, 'Stop', function() use ($sound) {
        //     $sound->stop();
        // }, 'left');
    }


    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);