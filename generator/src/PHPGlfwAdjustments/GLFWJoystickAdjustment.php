<?php 

namespace PHPGlfwAdjustments;

use ExtArgument;
use ExtFunction;
use ExtGenerator;
use ExtType;

class GLFWJoystickAdjustment implements AdjustmentInterface
{
    private function joystickAxes(ExtGenerator $gen) : void
    {
        $joystickAxesFunc = new class('glfwGetJoystickAxes') extends ExtFunction 
        {    
            public function getFunctionImplementationBody() : string
            {
                return <<<EOD
                zend_long joystick;
                if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &joystick) == FAILURE) {
                    return;
                }
                
                int count;
                const float* axes = glfwGetJoystickAxes(joystick, &count);
                
                array_init(return_value);
                
                for (int i = 0; i < count; i++) {
                    add_next_index_double(return_value, axes[i]);
                }
                EOD;
            }
        };
        
        // copy base function into our new one and replace it in the extension
        $joystickAxesFunc->copyFrom($gen->getFunctionByName('glfwGetJoystickAxes'));
        $joystickAxesFunc->incomplete = false;
        $joystickAxesFunc->returnType = ExtFunction::RETURN_ARRAY;

        // drop the count argument
        unset($joystickAxesFunc->arguments[1]);
        
        $gen->replaceFunctionByName($joystickAxesFunc);
    }

    private function joystickButtons(ExtGenerator $gen) : void
    {
        $joystickButtonsFunc = new class('glfwGetJoystickButtons') extends ExtFunction 
        {    
            public function getFunctionImplementationBody() : string
            {
                return <<<EOD
                zend_long joystick;
                if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &joystick) == FAILURE) {
                    return;
                }
                
                int count;
                const unsigned char* buttons = glfwGetJoystickButtons(joystick, &count);
                
                array_init(return_value);
                
                for (int i = 0; i < count; i++) {
                    add_next_index_bool(return_value, buttons[i]);
                }
                EOD;
            }
        };
        
        // copy base function into our new one and replace it in the extension
        $joystickButtonsFunc->copyFrom($gen->getFunctionByName('glfwGetJoystickButtons'));
        $joystickButtonsFunc->incomplete = false;
        $joystickButtonsFunc->returnType = ExtFunction::RETURN_ARRAY;

        // drop the count argument
        unset($joystickButtonsFunc->arguments[1]);
        
        $gen->replaceFunctionByName($joystickButtonsFunc);
    }

    private function gamepadAxes(ExtGenerator $gen) : void
    {
        $getGamepadAxesFunc = new class('glfwGetGamepadAxes') extends ExtFunction 
        {    
            public function getFunctionImplementationBody() : string
            {
                return <<<EOD
                zend_long joystick;
                if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &joystick) == FAILURE) {
                    return;
                }

                array_init(return_value);
                
                GLFWgamepadstate state;
                if (!glfwGetGamepadState(joystick, &state)) {
                    return;
                }

                // gamepad state has 6 axes
                for (int i = 0; i < 6; i++) {
                    add_next_index_double(return_value, state.axes[i]);
                }
                EOD;
            }
        };

        // this function doesnt exist in the base extension, so we need to add it
        $getGamepadAxesFunc->incomplete = false;
        $getGamepadAxesFunc->returnType = ExtFunction::RETURN_ARRAY;
        $getGamepadAxesFunc->arguments = [
            ExtArgument::make('joystick', ExtType::T_LONG),
        ];

        $getGamepadAxesFunc->arguments[0]->comment = 'The joystick to query.';

        $getGamepadAxesFunc->comment = <<<EOD
        Returns the state of the specified gamepad's axes.

        If the gamepad is not present, or the given joystick is not a gamepad, this function will return an empty array.

        The returned array is indexed by the GLFW gamepad axis constants:
         - `GLFW_GAMEPAD_AXIS_LEFT_X`
         - `GLFW_GAMEPAD_AXIS_LEFT_Y`
         - `GLFW_GAMEPAD_AXIS_RIGHT_X`
         - `GLFW_GAMEPAD_AXIS_RIGHT_Y`
         - `GLFW_GAMEPAD_AXIS_LEFT_TRIGGER`
         - `GLFW_GAMEPAD_AXIS_RIGHT_TRIGGER`
        EOD;
           
        $gen->addFunction($getGamepadAxesFunc);
    }

    private function gamepadButtons(ExtGenerator $gen) : void
    {
        $getGamepadButtonsFunc = new class('glfwGetGamepadButtons') extends ExtFunction 
        {    
            public function getFunctionImplementationBody() : string
            {
                return <<<EOD
                zend_long joystick;
                if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &joystick) == FAILURE) {
                    return;
                }

                array_init(return_value);
                
                GLFWgamepadstate state;
                if (!glfwGetGamepadState(joystick, &state)) {
                    return;
                }

                // gamepad state has 15 buttons
                for (int i = 0; i < 15; i++) {
                    add_next_index_bool(return_value, state.buttons[i]);
                }
                EOD;
            }
        };

        // this function doesnt exist in the base extension, so we need to add it
        $getGamepadButtonsFunc->incomplete = false;
        $getGamepadButtonsFunc->returnType = ExtFunction::RETURN_ARRAY;
        $getGamepadButtonsFunc->arguments = [
            ExtArgument::make('joystick', ExtType::T_LONG),
        ];

        $getGamepadButtonsFunc->arguments[0]->comment = 'The joystick to query.';

        $getGamepadButtonsFunc->comment = <<<EOD
        Returns the state of the specified gamepad's buttons.

        If the gamepad is not present, or the given joystick is not a gamepad, this function will return an empty array.

        The returned array is indexed by the GLFW gamepad button constants:
         - `GLFW_GAMEPAD_BUTTON_A`
         - `GLFW_GAMEPAD_BUTTON_B`
         - `GLFW_GAMEPAD_BUTTON_X`
         - `GLFW_GAMEPAD_BUTTON_Y`
         - `GLFW_GAMEPAD_BUTTON_LEFT_BUMPER`
         - `GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER`
         - `GLFW_GAMEPAD_BUTTON_BACK`
         - `GLFW_GAMEPAD_BUTTON_START`
         - `GLFW_GAMEPAD_BUTTON_GUIDE`
         - `GLFW_GAMEPAD_BUTTON_LEFT_THUMB`
         - `GLFW_GAMEPAD_BUTTON_RIGHT_THUMB`
         - `GLFW_GAMEPAD_BUTTON_DPAD_UP`
         - `GLFW_GAMEPAD_BUTTON_DPAD_RIGHT`
         - `GLFW_GAMEPAD_BUTTON_DPAD_DOWN`
         - `GLFW_GAMEPAD_BUTTON_DPAD_LEFT`
        EOD;
           
        $gen->addFunction($getGamepadButtonsFunc);
    }

    public function handle(ExtGenerator $gen) : void
    {
        $this->joystickAxes($gen);
        $this->joystickButtons($gen);
        $this->gamepadAxes($gen);
        $this->gamepadButtons($gen);
    }
}
