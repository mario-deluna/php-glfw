# PHP Audio Engine

PHP-GLFW ships with high level audio playback that is powered by [miniaudio](https://miniaud.io/).  The `GL\Audio` namespace gives you a lightweight engine that can stream compressed files, control per sound playback, and leverage spatial audio by combining the audio module with the math utilities that already ship with the extension.

This guide walks through the main building blocks:

- Creating and configuring the audio engine
- Loading sounds from disk
- Basic playback, looping, and volume controls
- Seeking, fading, and querying playback state
- Spatial audio features (listener, positions, min/max distance)
- Reading PCM frames for visualisation or DSP

You can try everything live by running the music player example:

```bash
php examples/vg/audio_musicplayer.php
```

## Engine setup

Create a new `GL\Audio\Engine` instance once in your application.  By default it initialises the output device immediately, but you can opt out and start the engine later.

```{.php .annotate}
use GL\Audio\Engine;
use GL\Math\Vec3;

$audio = new Engine(); # (1)!

$audio->setMasterVolume(0.8);

// configure the listener so spatial audio matches your world
$audio->setListenerPosition(new Vec3(0.0, 1.6, 0.0));
$audio->setListenerDirection(new Vec3(0.0, 0.0, -1.0));
$audio->setListenerWorldUp(new Vec3(0.0, 1.0, 0.0));
```

1. You can pass an optional config array to the constructor to tweak engine and device settings (see below).
    
   ```php
   $audio = new Engine([
    'channels' => 2,
    'sampleRate' => 48000,
    // etc..
   ]);
   ```

The constructor accepts an optional array of configuration options:

| Option | Type | Description |
|--------|------|-------------|
| `listenerCount` | `int` | Number of active 3D listeners (1 default, max 4). |
| `channels` | `int` | Override output channels (default taken from the device). |
| `sampleRate` | `int` | Request a specific device sample rate. |
| `periodSizeInFrames` | `int` | Custom device period size in frames. |
| `periodSizeInMilliseconds` | `int` | Alternative way to define the device period size. |
| `gainSmoothTimeInFrames` | `int` | Number of frames used when smoothing master volume changes. |
| `gainSmoothTimeInMilliseconds` | `int` | Same as above but in milliseconds. |
| `defaultVolumeSmoothTimeInPCMFrames` | `int` | Fade duration for per sound volume automation. |
| `noAutoStart` | `bool` | Skip automatic engine start. Call `$engine->start()` manually. |
| `monoExpansionMode` | `int` | Choose how mono sources expand to stereo. Use `GL_MA_MONO_EXPANSION_MODE_*` constants. |

!!! tip
    The engine automatically shuts down in the object destructor, so you rarely have to call `$engine->stop()` manually unless you manage devices explicitly.

## Loading sounds from disk

Use `soundFromDisk()` to create a `GL\Audio\Sound` instance.  The method returns a fully initialised sound that keeps track of format, channel count, sample rate, and length information on the PHP side.

```php
$sound = $audio->soundFromDisk(__DIR__ . '/assets/music_loop.ogg');

echo $sound->getChannels();      // e.g. 2
echo $sound->getSampleRate();    // e.g. 48000
echo $sound->getLength();        // seconds
```

MiniAudio supports a wide range of formats (WAV, MP3, FLAC, Ogg/Vorbis, and more).  The decoder is streaming-based, so memory usage stays reasonable even for long files.

## Basic playback controls

Every sound shares the same engine but exposes independent playback state.  The most common actions are straightforward:

```php
$sound->play();
$sound->setLoop(true);
$sound->setVolume(0.65);
$sound->setPitch(1.1);
$sound->setPan(-0.25); // -1.0 left, 1.0 right

// and play it!
$sound->play();
```

Use `$sound->stop()` to halt playback without rewinding.  Query playback position via `getCursor()` (seconds) or `getCursorPCM()` (frames).  When looping is enabled the cursor wraps automatically.

## Seeking, trimming, and fading

You can seek and constrain playback ranges without reloading the asset:

```php
$sound->setStartMs(500);   // begin 0.5 seconds into the file
$sound->setStopMs(3500);   // stop after 3.5 seconds

$sound->seekTo(42.0);      // jump to 42 seconds (returns bool)
$sound->seekToPCM(22050);  // or directly in PCM frames
```

Fades are expressed in seconds and run on the miniaudio mixer thread:

```php
$sound->fadeIn(2.0);                 // ramp current volume to 1.0 in 2 seconds
$sound->fadeOut(1.5);                // ramp down to silence
$sound->setFade(0.2, 0.8, 3.0);      // custom fade from 0.2 -> 0.8
$current = $sound->getCurrentFadeVolume();
```

## Spatial audio

Combine the audio engine with `GL\Math\Vec3` to position sounds in 3D.  The listener properties typically follow your camera, while sound positions follow moving entities.

```php
use GL\Math\Vec3;

$engine->setListenerPosition($camera->position);
$engine->setListenerDirection($camera->forward);
$engine->setListenerWorldUp(new Vec3(0.0, 1.0, 0.0));

$gunShot = $engine->soundFromDisk(__DIR__ . '/assets/gun_shot.wav');
$gunShot->setLoop(true);
$gunShot->setPosition(new Vec3(-3.0, 0.0, 1.5));
$gunShot->setMinDistance(1.0);   // distance where full volume is kept
$gunShot->setMaxDistance(25.0);  // distance where attenuation stops
$gunShot->setVelocity(new Vec3(0.0, 0.0, 2.0));
$gunShot->play();
```

Call `getPosition()`, `getDirection()`, and `getVelocity()` to fetch the current values if you need to debug spatial settings.

## Reading PCM data

`readFrames()` lets you stream raw audio frames into one of the native buffer types.  Choose the buffer that matches the sound format (float, signed 16-bit, or unsigned 8-bit) and reuse it between calls.

```php
use GL\Buffer\FloatBuffer;

$frames = new FloatBuffer();
$requested = 2048;
$readFrames = $sound->readFrames($requested, $frames);

printf("Read %d frames (%.2f ms)\n", $readFrames, $readFrames / $sound->getSampleRate() * 1000);
```

The method returns the number of frames read and resizes the buffer automatically. You can feed these samples into FFT analysis, visualisers, or streaming uploads similar to the `audio_musicplayer` example.

## Example: Music Player

The `examples/vg/audio_musicplayer.php` example demonstrates how all of these pieces fit together. It streams dropped files, renders a waveform texture, and exposes UI controls for volume, pitch, looping, and spatial position. Use it as a starting point for your own tools.