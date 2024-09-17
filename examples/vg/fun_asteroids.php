<?php
/**
 * A simple asteroids game showcasing how to use the vector graphics library.
 * 
 * This is meant to be played with a Gamepad / Controller. (No Keyboard support!)
 * 
 * @category   Input
 */

/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Buffer\FloatBuffer;
use GL\Math\Vec2;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor};

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

// glfw comes with a built in gamepad database, but as the build gets older 
// it is useful to update the mappings on the fly. You can find these here: 
// - https://raw.githubusercontent.com/mdqinc/SDL_GameControllerDB/master/gamecontrollerdb.txt
glfwUpdateGamepadMappings(file_get_contents(__DIR__ . "/../gamecontrollerdb.txt"));


class Player {

    /**
     * Higher values are faster.
     */
    public float $rotationSpeed = 0.03;

    /**
     * Forward / Backward speed.
     */
    public float $mainThrust = 0.05;

    /**
     * Side thrust speed.
     */
    public float $sideThrust = 0.005;

    /**
     * Shooting Cooldown in seconds.
     */
    public float $shootCooldown = 0.1;

    /**
     * Last time the player shot.
     */
    public float $lastShotTime = 0;

    public function __construct(
        public Vec2 $position,
        public Vec2 $velocity,
        public float $rotation,
    )
    {}

    public function applyThrust(float $thrust) {
        $forward = $this->getForwardVector();
        $this->velocity = $this->velocity + $forward * $thrust;
    }

    public function applySideThrust(float $thrust) {
        $this->velocity->x = $this->velocity->x + cos($this->rotation) * $thrust;
        $this->velocity->y = $this->velocity->y + sin($this->rotation) * $thrust;
    }

    public function getForwardVector() {
        return new Vec2(cos($this->rotation + M_PI / 2), sin($this->rotation + M_PI / 2));
    }

    public function shoot() : ?Bullet {
        if (glfwGetTime() - $this->lastShotTime < $this->shootCooldown) {
            return null;
        }

        $this->lastShotTime = glfwGetTime();

        return new Bullet(
            new Vec2($this->position->x, $this->position->y),
            // the bullet gets our velocity plus a little push in the direction we are facing
            $this->velocity + ($this->getForwardVector() * -2),
            $this->rotation
        );
    }
}

class Bullet 
{
    public float $spawnTime;

    public function __construct(
        public Vec2 $position,
        public Vec2 $velocity,
        public float $rotation,
        public float $lifeTime = 5.0 // default lifetime of 5 seconds
    )
    {
        $this->spawnTime = glfwGetTime();
    }
}

class Asteroid 
{
    public static function generate() : Asteroid {

        // basically we generate a n amount of points around a circle and then
        // just randomly slightly displace the points to make it look more natural.
        $points = rand(5, 16);
        $radius = rand(20, 50);
        $variance = 10;

        $vertices = new FloatBuffer();
        $angle = 0;
        $angleStep = M_PI * 2 / $points;

        for ($i = 0; $i < $points; $i++) {
            $angle += $angleStep;
            $radius = $radius + rand(-$variance, $variance);
            $x = cos($angle) * $radius + rand(-2, 2);
            $y = sin($angle) * $radius + rand(-2, 2);

            $vertices->pushVec2(new Vec2($x, $y));
        }

        return new Asteroid(
            new Vec2(0, 0),
            new Vec2(0, 0),
            0,
            $radius + $variance,
            $vertices
        );
    }

    public function __construct(
        public Vec2 $position,
        public Vec2 $velocity,
        public float $rotation,
        public float $radius,
        public FloatBuffer $vertices,
    )
    {}
}

class State 
{
    /**
     * Will draw some texts on the screen if set to true.
     */
    public bool $debugMode = false;

    /**
     * The player object.
     */
    public Player $player;

    /**
     * The camera position.
     */
    public Vec2 $cameraPosition;

    /**
     * The bullets.
     * 
     * @var array<Bullet>
     */
    public array $bullets = [];

    /**
     * The asteroids.
     * 
     * @var array<Asteroid>
     */
    public array $asteroids = [];

    /**
     * The current score.
     */
    public int $score = 0;

    /**
     * Constructor
     */
    public function __construct()
    {
        $this->player = new Player(
            new Vec2(0, 0),
            new Vec2(0, 0),
            0
        );

        $this->cameraPosition = new Vec2(0, 0);
    }
}

$state = new State();


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

    // move the origin to the center of the window
    $vg->translate(ExampleHelper::WIN_WIDTH / 2, ExampleHelper::WIN_HEIGHT / 2);
    $vg->translate(-$state->cameraPosition->x, -$state->cameraPosition->y);
    ExampleHelper::drawCoordSys($vg);

    $gameIsPaused = true;
    $gamePauseMessage = "Please connect a Gamepad / Controller to play!";
    $gamepadId = -1;

    // check if a gamepad is connected
    for ($jid = GLFW_JOYSTICK_1; $jid < GLFW_JOYSTICK_LAST; $jid++) {
        if (glfwJoystickPresent($jid) && glfwJoystickIsGamepad($jid)) {
            $gamepadId = $jid;
            $gameIsPaused = false;
            break;
        }
    }

    if ($gameIsPaused) {
        $vg->fontSize(32.0);
        $vg->fillColor(VGColor::white());
        $vg->textAlign(VGAlign::CENTER | VGAlign::MIDDLE);
        $vg->text(0, 0, $gamePauseMessage);
    } else 
    {
        // get the gamepad state
        $gamepadAxes = glfwGetGamepadAxes($gamepadId);
        $gamepadButtons = glfwGetGamepadButtons($gamepadId);

        /**
         * Handle the asteroids
         */
        if (count($state->asteroids) < 10) {
            $asteroid = Asteroid::generate();

            // always spawn somewhere around the player but outside of the screen
            $screenRadius = max(ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT) / 2;
            $screenRadius += 100;
            $angle = rand(0, 360) * M_PI / 180;
            $posX = cos($angle) * $screenRadius;
            $posY = sin($angle) * $screenRadius;

            $asteroid->position->x = $state->player->position->x + $posX;
            $asteroid->position->y = $state->player->position->y + $posY;
            $asteroid->velocity->x = rand(-1, 1) * 0.1;
            $asteroid->velocity->y = rand(-1, 1) * 0.1;
            $asteroid->rotation = rand(-1, 1);

            $state->asteroids[] = $asteroid;
        }

        foreach ($state->asteroids as $index => $asteroid) {

            // if an asteroid is to far from the player we remove it
            if (Vec2::distance($state->player->position, $asteroid->position) > 1000) {
                unset($state->asteroids[$index]);
                continue;
            }

            $asteroid->position->x = $asteroid->position->x + $asteroid->velocity->x;
            $asteroid->position->y = $asteroid->position->y + $asteroid->velocity->y;

            $vg->save();
            $vg->translate($asteroid->position->x, $asteroid->position->y);
            $vg->rotate($asteroid->rotation * glfwGetTime());

            $vg->fillColor(VGColor::white());
            $vg->beginPath();
            
            $vertexCount = $asteroid->vertices->size() / 2;
            $vg->moveTo($asteroid->vertices[0], $asteroid->vertices[1]);
            for ($i = 1; $i < $vertexCount; $i++) {
                $vg->lineTo($asteroid->vertices[$i * 2], $asteroid->vertices[$i * 2 + 1]);
            }
            $vg->closePath();
            $vg->fill();
            $vg->restore();
        }


        /**
         * Handle the player
         */

        // roration
        $state->player->rotation += $gamepadAxes[GLFW_GAMEPAD_AXIS_LEFT_X] * $state->player->rotationSpeed;

        // apply thrust
        $thrust = $gamepadAxes[GLFW_GAMEPAD_AXIS_RIGHT_Y] * $state->player->mainThrust;
        $sideThrust = $gamepadAxes[GLFW_GAMEPAD_AXIS_RIGHT_X] * $state->player->sideThrust;  

        $state->player->applyThrust($thrust);
        $state->player->applySideThrust($sideThrust);

        // dampen the velocity
        $state->player->velocity->x = $state->player->velocity->x * 0.99;
        $state->player->velocity->y = $state->player->velocity->y * 0.99;

        // update the player position
        $state->player->position->x = $state->player->position->x + $state->player->velocity->x;
        $state->player->position->y = $state->player->position->y + $state->player->velocity->y;

        // move the camera into the direction of the player
        $state->cameraPosition->x = $state->cameraPosition->x + ($state->player->position->x - $state->cameraPosition->x) * 0.01;
        $state->cameraPosition->y = $state->cameraPosition->y + ($state->player->position->y - $state->cameraPosition->y) * 0.01;

        // draw the player (triangle its a asteroids game after all)
        $vg->save();

        // rotate the player
        $vg->translate($state->player->position->x, $state->player->position->y);
        $vg->rotate($state->player->rotation);

        $vg->fillColor(VGColor::white());
        $vg->beginPath();
        $vg->moveTo(0, -20);
        $vg->lineTo(10, 10);
        $vg->lineTo(-10, 10);
        $vg->closePath();
        $vg->fill();

        $vg->restore();

        /**
         * Handle the shooting
         */
        if ($gamepadAxes[GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER] > 0.5) {
            if ($bullet = $state->player->shoot()) {
                $state->bullets[] = $bullet;
            }
        }

        /**
         * Handle the bullets
         */
        foreach ($state->bullets as $index => $bullet) {
            $bullet->position->x = $bullet->position->x + $bullet->velocity->x;
            $bullet->position->y = $bullet->position->y + $bullet->velocity->y;

            // remove bullets that are too old
            if (glfwGetTime() - $bullet->spawnTime > $bullet->lifeTime) {
                unset($state->bullets[$index]);
                continue;
            }

            // check if a bullet hits an asteroid
            foreach ($state->asteroids as $aIndex => $asteroid) {
                if (Vec2::distance($bullet->position, $asteroid->position) < $asteroid->radius) {
                    unset($state->bullets[$index]);
                    unset($state->asteroids[$aIndex]);
                    $state->score++;
                    break;
                }
            }

            $vg->fillColor(VGColor::white());
            $vg->beginPath();
            $vg->circle($bullet->position->x, $bullet->position->y, 2);
            $vg->fill();
        }

        if ($state->debugMode) {
            $vg->fontSize(14.0);
            $vg->fillColor(VGColor::white());
            $vg->textAlign(VGAlign::LEFT | VGAlign::TOP);
            $vg->text(
                $state->player->position->x + 20, 
                $state->player->position->y + 20, 
                sprintf("Player: p(%.2f, %.2f) v(%.2f, %.2f) r(%.2f)", 
                    $state->player->position->x, 
                    $state->player->position->y, 
                    $state->player->velocity->x, 
                    $state->player->velocity->y, 
                    $state->player->rotation
                )
            );
        }
    }

    // draw the score
    $vg->reset();
    $vg->fontSize(32.0);
    $vg->fillColor(VGColor::white());
    $vg->textAlign(VGAlign::LEFT | VGAlign::TOP);
    $vg->text(20, 20, "Score: " . $state->score);



    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);