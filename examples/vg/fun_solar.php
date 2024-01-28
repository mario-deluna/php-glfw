<?php
/**
 * Simple Solar System
 * We will use the vector graphics context to draw a simple solar system. This is massivley simplified
 * but still fun to play around with. Im using real world values but the oribtal mechanics are questionable at best.
 * And I completely ignore the fact that the planets are not on the same plane, this is just a 2D simulation.
 * 
 * @category   Fun
 */
/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Math\Vec2;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor};

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

class OribalObject {

    /**
     * holds the position of the object in screen space
     */
    public Vec2 $viewPos; 

    /**
     * holds the force that is applied to the object in N 
     */
    public Vec2 $force;

    public function __construct(
        public string $name,
        public float $radius, // in km
        public float $mass, // in kg
        public Vec2 $position, // in km
        public Vec2 $velocity, // in m/s
    )
    {
        $this->force = new Vec2(0, 0);   
    }
}

$objects = [];
$au = 149.6e6; // km
$G = 6.6743e-11; // gravitational constant

// sun at the center
$objects[] = new OribalObject(
    name: 'Sun',
    radius: 696340,
    mass: 1.989e30,
    position: new Vec2(0, 0),
    velocity: new Vec2(0, 0),
);

// earth
$objects[] = new OribalObject(
    name: 'Earth',
    radius: 6371,
    mass: 5.972e24,
    position: new Vec2($au, 0),
    velocity: new Vec2(0, 29784.8),
    // velocity: new Vec2(0, 0),
);

// moon
$objects[] = new OribalObject(
    name: 'Moon',
    radius: 1737,
    mass: 7.34767309e22,
    position: new Vec2($au + 384400, 0),
    velocity: new Vec2(0, 29784.8 + 1022),
);

// mars
$objects[] = new OribalObject(
    name: 'Mars',
    radius: 3389,
    mass: 6.39e23,
    position: new Vec2($au * 1.524, 0),
    velocity: new Vec2(0, 24130),
);

// jupiter
$objects[] = new OribalObject(
    name: 'Jupiter',
    radius: 69911,
    mass: 1.898e27,
    position: new Vec2($au * 5.203, 0),
    velocity: new Vec2(0, 13070),
);

$viewZoom = $au * 2;
$viewOffset = new Vec2(0, 0);
$focusedObject = 1;

$timeScale = (1 / 60) * 60 * 60 * 24 * 1; // 1 sec = 1 days

// listen for scroll events to zoom the view
glfwSetScrollCallback($window, function($xOffset, $yOffset) use (&$viewZoom) {
    // zoom in out logarithmically
    $viewZoom *= 1 + $yOffset * 0.1;
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

    // transform the view to center the sun
    $vg->translate(ExampleHelper::WIN_WIDTH / 2, ExampleHelper::WIN_HEIGHT / 2);

    ExampleHelper::drawCoordSys($vg);

    // calculate the force between the objects
    foreach ($objects as $i => $object) {
        $object->force = new Vec2(0, 0);
    
        foreach ($objects as $j => $other) {
            if ($i === $j) continue; // skip self
    
            $distanceVec = ($other->position * 1000) - ($object->position * 1000);
            $distance = $distanceVec->length();
            $forceMagnitude = $G * $object->mass * $other->mass / ($distance ** 2);
            $forceDirection = Vec2::normalized($distanceVec);
            $force = $forceDirection * $forceMagnitude;
            $object->force += $force;
        }
    }

    ExampleHelper::drawFuncLabel($vg, 50, 30, "force(" . $objects[1]->force->x . " N, " . $objects[1]->force->y . " N)");
    ExampleHelper::drawFuncLabel($vg, 50, 50, "velocity(" . $objects[1]->velocity->x . " m/s, " . $objects[1]->velocity->y . " m/s)");

    // apply the velocity to the position
    foreach ($objects as $object) {
        $acceleration = $object->force / $object->mass;
        $object->velocity += $acceleration * $timeScale;
        $object->position += ($object->velocity * $timeScale) / 1000;
    }
    
    // update the screen space positions of the objects
    foreach($objects as $object) {
        $object->viewPos = $object->position / $viewZoom;
        $object->viewPos = $object->viewPos * ExampleHelper::WIN_WIDTH / 2;
    }

    // focus on eath by updating the viewPos of all objects 
    // by the negative position of earth
    $viewOffset = $objects[$focusedObject]->viewPos * -1;
    foreach($objects as $object) {
        $object->viewPos += $viewOffset;
    }

    // if the mouse button is down focus on the closest object
    // the the mouse position
    if (glfwGetMouseButton($window, GLFW_MOUSE_BUTTON_LEFT) === GLFW_PRESS) {
        glfwGetCursorPos($window, $mouseX, $mouseY);

        $mousePos = new Vec2($mouseX, $mouseY);
        $mousePos = $mousePos - new Vec2(ExampleHelper::WIN_WIDTH / 2, ExampleHelper::WIN_HEIGHT / 2);
        $distances = [];
        foreach($objects as $key => $object) {
            $distances[$key] = $object->viewPos->distanceTo($mousePos);
        }

        $closest = array_search(min($distances), $distances);
        $focusedObject = $closest;
        
    }

    // draw the objects
    foreach($objects as $object) {

        $vg->beginPath();
        $vg->circle($object->viewPos->x, $object->viewPos->y, $object->radius / $viewZoom * ExampleHelper::WIN_WIDTH);
        $vg->fillColor(VGColor::white());
        $vg->fill();

        ExampleHelper::drawCoordPoint($vg, $object->viewPos->x, $object->viewPos->y, $object->name);
    }

    static $sel = 0;
    $offset = ExampleHelper::drawButtonGroup($vg, 100, ExampleHelper::WIN_HEIGHT - 100, [
        '1s = 1m',
        '1s = 1h',
        '1s = 1d',
        '1s = 10d',
        '1s = 100d',
    ], $sel, function($selection) use (&$timeScale) {
        match($selection) {
            0 => $timeScale = (1 / 60) * 60,
            1 => $timeScale = (1 / 60) * 60 * 60,
            2 => $timeScale = (1 / 60) * 60 * 60 * 24,
            3 => $timeScale = (1 / 60) * 60 * 60 * 24 * 10,
            4 => $timeScale = (1 / 60) * 60 * 60 * 24 * 100,
        };
    });


    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
}

ExampleHelper::stop($window);