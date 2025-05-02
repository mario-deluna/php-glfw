<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Audio\Sound;
use GL\Buffer\FloatBuffer;
use GL\Buffer\ShortBuffer;
use GL\Buffer\UByteBuffer;
use GL\Geometry\ObjFileParser\Texture;
use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor, VGImage};

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

// init audio engine
$audioEngine = new \GL\Audio\Engine();

// current sound
class Playback {
    public Texture2D $soundTexture;
    public VGImage $soundImage;

    public function __construct(
        public Sound $sound,
        public string $soundFile,
        public float $soundX = 0.0,
        public float $soundY = 0.0,
    ) {
        $this->soundTexture = createSoundTexture($sound, ExampleHelper::WIN_WIDTH - 200, 128);

        // upload the texture to the VG Context
        global $vg;
        $this->soundImage = $vg->imageFromTexture($this->soundTexture);
    }
}

class Player {
    public function __construct(
        public ?Playback $playback = null,
    ) {}
}

$player = new Player();

function createSoundTexture(Sound $sound, int $width, int $height) : Texture2D
{
    // read some frames
    $framesBuffer = new FloatBuffer();
    $sampleRate = $sound->getSampleRate();
    $length = $sound->getLengthPCM();

    echo "Starting to generate sound texture...\n";

    // we want to generate a texture from the frames
    // visualizing the sound
    $textureBuffer = new UByteBuffer();
    $textureBuffer->fill($width * $height * 4, 0); // we want to use RGBA to simplify usage with VG

    while ($sound->getCursorPCM() < $length) {
        $startFrame = $sound->getCursorPCM();
        $sound->readFrames($sampleRate, $framesBuffer);
        echo "Reading " . $startFrame . " to " . $sound->getCursorPCM() . " of " . $length . "\n";

        for ($i = 0; $i < $framesBuffer->size(); $i+=$sound->channels) {
            $x = $startFrame + (int)floor($i / $sound->channels);
            $x = (int) floor(($x / $length) * $width);

            for($j = 0; $j < $sound->channels; $j++) {
                $value = $framesBuffer[$i + $j];
                // y is the value of the sample
                $y = (int) floor(($value + 1) * 0.5 * $height);

                // update the pixel buffer by simply adding 1 to the red channel
                $textureBufferIndex = ($x + $y * $width) * 4;

                // i could have solved this cleaner, but decided not to
                if ($textureBuffer[$textureBufferIndex] < 255) {
                    $textureBuffer[$textureBufferIndex] = $textureBuffer[$textureBufferIndex] + 1;
                } elseif ($textureBuffer[$textureBufferIndex + 1] < 255) {
                    $textureBuffer[$textureBufferIndex + 1] = $textureBuffer[$textureBufferIndex + 1] + 1;
                } elseif ($textureBuffer[$textureBufferIndex + 2] < 255) {
                    $textureBuffer[$textureBufferIndex + 2] = $textureBuffer[$textureBufferIndex + 2] + 1;
                }

                // alpha channel should be 255
                $textureBuffer[$textureBufferIndex + 3] = 255;
            } 
        }
    }

    echo "Finished generating sound texture...\n";

    // reset the cursor
    $sound->seekTo(0);

    // create a texture from the buffer
    $texture = Texture2D::fromBuffer($width, $height, $textureBuffer);

    return $texture;
}

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

    var_dump($player->playback->sound);
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
        $progressBarHeight = 108;
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

        // image is the background of the progress bar
        $imagePaint = $player->playback->soundImage->makePaint($x, $y, $progressBarWidth, $progressBarHeight);
        $vg->strokeColor(VGColor::white());
        $vg->fillPaint($imagePaint);
        $vg->beginPath();
        $vg->rect($x, $y, $progressBarWidth, $progressBarHeight);   
        $vg->strokeWidth(2);
        $vg->stroke();
        $vg->fill();


        // render a red cursor
        $cursorColor = VGColor::red();
        $cursorColor->a = 0.5;
        $vg->strokeColor($cursorColor);
        $vg->beginPath();
        $cursorX = $x + $progressBarWidth * $playbackProgress;
        $vg->moveTo($cursorX, $y - 5);
        $vg->lineTo($cursorX, $y + $progressBarHeight + 5);
        $vg->strokeWidth(5);
        $vg->stroke();

        // here we render a little 2d sound position editor
        $y += $progressBarHeight + 20;

        // create a label 
        $vg->fillColor(VGColor::white());
        $vg->textAlign(VGAlign::LEFT | VGAlign::MIDDLE);
        $vg->text($x, $y, "Sound Position");
        $y += 20;

        $positionBoxSize = 200;
        $vg->beginPath();
        $vg->strokeColor(VGColor::white());
        $vg->strokeWidth(2);
        $vg->rect($x, $y, $positionBoxSize, $positionBoxSize);
        $vg->stroke();

        // update sound position when mouse is down inside of the position box
        if (glfwGetMouseButton($window, GLFW_MOUSE_BUTTON_LEFT) === GLFW_PRESS) {
            $cursorX;
            $cursorY;
            glfwGetCursorPos($window, $cursorX, $cursorY);
            if ($cursorX >= $x && $cursorX <= $x + $positionBoxSize && $cursorY >= $y && $cursorY <= $y + $positionBoxSize) {
                $player->playback->soundX = ($cursorX - $x) / $positionBoxSize - 0.5;
                $player->playback->soundY = ($cursorY - $y) / $positionBoxSize - 0.5;
            }
        }

        // render the sound position as a red dot
        $vg->fillColor(VGColor::red());
        $vg->beginPath();
        $vg->circle($x + $positionBoxSize * ($player->playback->soundX + 0.5), $y + $positionBoxSize * ($player->playback->soundY + 0.5), 5);
        $vg->fill();

        // apply the sound position
        $player->playback->sound->setPosition($player->playback->soundX, $player->playback->soundY, 0);


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