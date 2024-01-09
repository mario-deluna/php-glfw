<?php
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\VectorGraphics\{VGAlign, VGContext, VGColor};

$window = ExampleHelper::begin();

// when pressing space toggle vsync
$vSync = true;
$displayLabels = true;
$onlyRenderBest = false;
glfwSetKeyCallback($window, function($key, $scancode, $action, $mods) use (&$vSync, $window, &$displayLabels, &$onlyRenderBest) {
    if ($key === GLFW_KEY_SPACE && $action === GLFW_PRESS) {
        $vSync = !$vSync;
        glfwSwapInterval((int)$vSync);
    }

    // press d to toggle labels
    if ($key === GLFW_KEY_D && $action === GLFW_PRESS) {
        $displayLabels = !$displayLabels;
    }

    // press b to render only the best car
    if ($key === GLFW_KEY_B && $action === GLFW_PRESS) {
        $onlyRenderBest = !$onlyRenderBest;
    }
});


// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

enum CarStateChange : int {
    case Accelerate = 0;
    case Decelerate = 1;
    case TurnLeft = 2;
    case TurnRight = 3;
}

class CarInstruction {
    public function __construct(
        public CarStateChange $change,
        public float $strength
    )
    {}
}

class Car {
    public float $x = 0.0;
    public float $y = 0.0;
    public float $rotation = 0.0;
    public float $speed = 0.0;
    public float $steering = 0.0; 
    public float $fitness = 0.0;
    public float $penalty = 0.0;
    public bool $isAlive = true;
    public int $numMutations = 0;
    public bool $isBest = false;

    /** @var array<CarInstruction> */
    public array $instructions = [];
    public int $instructionIndex = 0;

    public function tick(float $timeDelta): void 
    {
        if (!$this->isAlive) {
            return;
        }

        // check if there is an instruction to execute
        if (isset($this->instructions[$this->instructionIndex])) {
            $instruction = $this->instructions[$this->instructionIndex];

            switch ($instruction->change) {
                case CarStateChange::Accelerate:
                    $this->speed += $instruction->strength;
                    break;
                case CarStateChange::Decelerate:
                    $this->speed -= $instruction->strength;
                    break;
                case CarStateChange::TurnLeft:
                    $this->steering -= $instruction->strength;
                    break;
                case CarStateChange::TurnRight:
                    $this->steering += $instruction->strength;
                    break;
            }

            $this->instructionIndex++;
        } else {
            // no instruction left, kill the car
            $this->isAlive = false;
        }

        // clamp car limits
        $this->speed = max(-50.0, min(200.0, $this->speed));
        $this->steering = max(-45.0, min(45.0, $this->steering));

        $rotationRadians = deg2rad($this->rotation);

        $this->x += cos($rotationRadians) * $this->speed * $timeDelta;
        $this->y += sin($rotationRadians) * $this->speed * $timeDelta;

        $this->rotation += $this->steering * $timeDelta;
        // $this->rotation += ($this->steering * $this->speed / 200.0) * $timeDelta;

        $this->rotation = fmod($this->rotation, 360.0);
    }

    public function render($vg): void {

        global $onlyRenderBest, $displayLabels;

        if ($onlyRenderBest && !$this->isBest) {
            return;
        }

        $vg->save();

        $vg->translate($this->x, $this->y);
        $vg->rotate(deg2rad($this->rotation));

        // Draw the car as a polygon
        $vg->beginPath();
        $vg->rect(-25, -15, 50, 30);
        if ($this->isBest) {
            $vg->fillColor(VGColor::green());
        } else {
            $vg->fillColor(VGColor::yellow());
        }
        $vg->fill();

        $vg->beginPath();
        $vg->rect(20, -5, 10, 10);

        $vg->fillColor(VGColor::red());
        $vg->fill();

        $vg->restore();

        if ($displayLabels) ExampleHelper::drawPoint($vg, $this->x, $this->y, "  i: {$this->instructionIndex}, fitness: {$this->fitness}, mutations: {$this->numMutations}");
    }
}

class Obsticle {
    public float $x = 0.0;
    public float $y = 0.0;
    public float $radius = 0.0;

    public function __construct(float $x, float $y, float $radius)
    {
        $this->x = $x;
        $this->y = $y;
        $this->radius = $radius;
    }

    public function render($vg): void {
        $vg->beginPath();
        $vg->circle($this->x, $this->y, $this->radius);
        $vg->fillColor(VGColor::red());
        $vg->fill();
    }

    public function isColliding(Car $car): bool {
        $distance = sqrt(pow($car->x - $this->x, 2) + pow($car->y - $this->y, 2));
        return $distance < $this->radius;
    }
}

$instructionCount = 1000;
$populationSize = 100;
$mutationRate = 0.1;
$cars = [];
for ($i = 0; $i < $populationSize; $i++) {
    $car = new Car();
    $car->x = 50;
    $car->y = 50;
    $cars[] = $car;

    // fill random 100 instructions
    for ($j = 0; $j < $instructionCount; $j++) {
        $car->instructions[] = new CarInstruction(
            change: CarStateChange::from(rand(0, 3)),
            strength: mt_rand(0, 100) / 10,
        );
    }
}

$obsticles = [];
for ($i = 0; $i < 50; $i++) {
    $obsticles[] = new Obsticle(
        x: rand(0, ExampleHelper::WIN_WIDTH),
        y: rand(0, ExampleHelper::WIN_HEIGHT),
        radius: rand(10, 50),
    );
}

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

    // if all cars are dead, reset them
    $allDead = true;
    foreach ($cars as $car) {
        if ($car->isAlive) {
            $allDead = false;
            break;
        }
    }

    if ($allDead) {
        // drop the mutation rate
        $mutationRate *= 0.9;

        // fitness for now is just the distance to the center
        foreach ($cars as $car) {
            $car->fitness = sqrt(pow($car->x - ExampleHelper::WIN_WIDTH / 2, 2) + pow($car->y - ExampleHelper::WIN_HEIGHT / 2, 2));
            $car->fitness += $car->penalty;
        }

        // sort cars by fitness
        usort($cars, function($a, $b) {
            return $a->fitness <=> $b->fitness;
        });

        // take the best 2 cars and breed them
        $bestCars = array_slice($cars, 0, 2);

        var_dump($bestCars[0]->fitness, $bestCars[1]->fitness);

        foreach ($cars as $i => $car) {
            $car->x = 50;
            $car->y = 50;
            $car->rotation = 0.0;
            $car->speed = 0.0;
            $car->steering = 0.0;
            $car->isAlive = true;
            $car->instructionIndex = 0;
            $car->penalty = 0.0;
            $car->numMutations = 0;
            $car->isBest = false;

            // keep the best cars
            if ($i < 2) {
                $car->instructions = $bestCars[$i]->instructions;
                $car->isBest = true;
                continue;
            }

            // create a merged version 
            if ($i === 3) {
                $car->instructions = array_merge(
                    array_slice($bestCars[0]->instructions, 0, $instructionCount / 2),
                    array_slice($bestCars[1]->instructions, $instructionCount / 2),
                );
                continue;
            }

            // update the instructions by randomly picking from the best cars
            $randomCar = $bestCars[array_rand($bestCars)];
            for ($i = 0; $i < $instructionCount; $i++) {
                $car->instructions[$i] = $randomCar->instructions[$i];
            }

            // also mutate 10% of the instructions
            for ($i = 0; $i < $instructionCount; $i++) {
                if (mt_rand(0, 100) / 100 < $mutationRate) {
                    $car->numMutations++;
                    $car->instructions[$i] = new CarInstruction(
                        change: CarStateChange::from(rand(0, 3)),
                        strength: mt_rand(0, 100) / 10,
                    );
                }
            }
        }
    }

    // Draw a car
    foreach ($cars as $i => $car) {
        $car->tick(1.0 / 60.0);

        // check if car is colliding with any obsticles
        foreach ($obsticles as $obsticle) {
            if ($obsticle->isColliding($car)) {
                $car->isAlive = false;
                $car->penalty = 1000.0;
            }
        }

        // check if car is out of bounds
        if ($car->x < 0 || $car->x > ExampleHelper::WIN_WIDTH || $car->y < 0 || $car->y > ExampleHelper::WIN_HEIGHT) {
            $car->isAlive = false;
            $car->penalty = 1000.0;
        }

        $car->render($vg);
    }

    // draw obsticles
    foreach ($obsticles as $obsticle) {
        $obsticle->render($vg);
    }

    // draw a point of the target
    ExampleHelper::drawPoint($vg, ExampleHelper::WIN_WIDTH / 2, ExampleHelper::WIN_HEIGHT / 2, "Target");

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);