<?php
/**
 * Joystick Input
 * Example showcasing how to access a joystick or gamepad / controller using PHP.
 * 
 * @category   Input
 */

/**
 * We utilize the example helpers here to focus on what matter in this specifc example.
 */
require __DIR__ . '/../99_example_helpers.php';

use GL\Texture\Texture2D;
use GL\VectorGraphics\{VGAlign, VGContext, VGColor};

$window = ExampleHelper::begin();

// initalize the a vector graphics context
$vg = new VGContext(VGContext::ANTIALIAS);

// glfw comes with a built in gamepad database, but as the build gets older 
// it is useful to update the mappings on the fly. You can find these here: 
// - https://raw.githubusercontent.com/mdqinc/SDL_GameControllerDB/master/gamecontrollerdb.txt
glfwUpdateGamepadMappings(file_get_contents(__DIR__ . "/../gamecontrollerdb.txt"));


// echo glfwGetJoystickGUID(GLFW_JOYSTICK_1) . PHP_EOL;

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

    $offsetX = 50;
    $offsetY = 50;

    for ($jid = GLFW_JOYSTICK_1; $jid < GLFW_JOYSTICK_LAST; $jid++) {
        if (glfwJoystickPresent($jid)) {
            

            // special handling for gamepads 
            if (glfwJoystickIsGamepad($jid)) 
            {
                $gamepad = glfwGetGamepadName($jid);
                $vg->fontSize(18.0);
                $vg->fillColor(VGColor::white());
                $vg->text($offsetX, $offsetY, "Gamepad: $gamepad");

                $offsetY += 20;

                $state = glfwGetGamepadAxes($jid);
                $vg->fontSize(14.0);
                $vg->fillColor(VGColor::white());
                $axes = [
                    GLFW_GAMEPAD_AXIS_LEFT_X => "Left X",
                    GLFW_GAMEPAD_AXIS_LEFT_Y => "Left Y",
                    GLFW_GAMEPAD_AXIS_RIGHT_X => "Right X",
                    GLFW_GAMEPAD_AXIS_RIGHT_Y => "Right Y",
                    GLFW_GAMEPAD_AXIS_LEFT_TRIGGER => "Left Trigger",
                    GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER => "Right Trigger",
                ];

                foreach ($axes as $axis => $name) {
                    $vg->fillColor(VGColor::white());
                    $vg->text($offsetX, $offsetY, "$name: " . round($state[$axis], 2));

                    // draw a bar to represent the axis value
                    $vg->fillColor(VGColor::red());
                    $vg->beginPath();
                    $vg->circle($offsetX + 200 + ($state[$axis] * 50), $offsetY, 5);
                    $vg->fill();

                    $offsetY += 14;
                }

                $buttons = glfwGetGamepadButtons($jid);
                $vg->fontSize(14.0);
                $vg->text($offsetX, $offsetY, "Buttons: " . count($buttons));

                $offsetY += 20;  
                $buttonMapping = [
                    GLFW_GAMEPAD_BUTTON_A => "A",
                    GLFW_GAMEPAD_BUTTON_B => "B",
                    GLFW_GAMEPAD_BUTTON_X => "X",
                    GLFW_GAMEPAD_BUTTON_Y => "Y",
                    GLFW_GAMEPAD_BUTTON_LEFT_BUMPER => "Left Bumper",
                    GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER => "Right Bumper",
                    GLFW_GAMEPAD_BUTTON_BACK => "Back",
                    GLFW_GAMEPAD_BUTTON_START => "Start",
                    GLFW_GAMEPAD_BUTTON_GUIDE => "Guide",
                    GLFW_GAMEPAD_BUTTON_LEFT_THUMB => "Left Thumb",
                    GLFW_GAMEPAD_BUTTON_RIGHT_THUMB => "Right Thumb",
                    GLFW_GAMEPAD_BUTTON_DPAD_UP => "DPad Up",
                    GLFW_GAMEPAD_BUTTON_DPAD_RIGHT => "DPad Right",
                    GLFW_GAMEPAD_BUTTON_DPAD_DOWN => "DPad Down",
                    GLFW_GAMEPAD_BUTTON_DPAD_LEFT => "DPad Left",
                ];

                foreach ($buttonMapping as $button => $name) {
                    $vg->fillColor(VGColor::white());
                    $vg->text($offsetX, $offsetY, "$name: ");
                    $vg->fillColor($buttons[$button] ? VGColor::green() : VGColor::red());
                    $vg->text($offsetX + 100, $offsetY, $buttons[$button] ? "Pressed" : "Released");
                    $offsetY += 14;
                }
            }
            else 
            {
                $name = glfwGetJoystickName($jid);

                $vg->fontSize(18.0);
                $vg->fillColor(VGColor::white());
                $vg->text($offsetX, $offsetY, $name);
    
                $offsetY += 20;
    
                $axes = glfwGetJoystickAxes($jid);
                $vg->fontSize(14.0);
                $vg->fillColor(VGColor::white());
    
    
                // meta information
                $vg->text($offsetX, $offsetY, "Axes: " . count($axes));
                $offsetY += 14;
                // is gamepad?
                $vg->text($offsetX, $offsetY, "Is Gamepad: " . (glfwJoystickIsGamepad($jid) ? "Yes" : "No"));
                $offsetY += 14;
                // GUID
                $vg->text($offsetX, $offsetY, "GUID: " . glfwGetJoystickGUID($jid));
                $offsetY += 30;
    
                // draw the axes
                for ($i = 0; $i < count($axes); $i++) {
                    $vg->fillColor(VGColor::white());
                    $vg->text($offsetX, $offsetY, "Axis $i: " . round($axes[$i], 2));
    
                    // draw a bar to represent the axis value
                    $vg->fillColor(VGColor::red());
                    $vg->beginPath();
                    $vg->circle($offsetX + 200 + ($axes[$i] * 50), $offsetY, 5);
                    $vg->fill();
    
    
                    $offsetY += 14;
                }
    
                // draw the buttons
                $buttons = glfwGetJoystickButtons($jid);
    
                $vg->fontSize(14.0);
                $vg->text($offsetX, $offsetY, "Buttons: " . count($buttons));
    
                $offsetY += 14;
                for ($i = 0; $i < count($buttons); $i++) {
                    $vg->fillColor(VGColor::white());
                    $vg->text($offsetX, $offsetY, "Button $i: ");
                    $vg->fillColor($buttons[$i] ? VGColor::green() : VGColor::red());
                    $vg->text($offsetX + 100, $offsetY, $buttons[$i] ? "Pressed" : "Released");
                    $offsetY += 14;
                }
            }

            $offsetX += 300;
            $offsetY = 50;
        }
    }

    // end the frame will dispatch all the draw commands to the GPU
    $vg->endFrame();

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}

ExampleHelper::stop($window);