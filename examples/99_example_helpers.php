<?php

use GL\Buffer\FloatBuffer;
use GL\Geometry\ObjFileParser;
use GL\Math\Vec4;
use GL\Texture\Texture2D;
use GL\VectorGraphics\VGAlign;
use GL\VectorGraphics\VGColor;
use GL\VectorGraphics\VGContext;

/**
 * To reduce the amount of boilerplate for each example this file contains
 * a collection of helpers / common code that is used by the examples.
 */
class ExampleHelper
{
    const WIN_WIDTH = 1280;
    const WIN_HEIGHT = 720;

    /**
     * Instance of the current windo
     */
    private static ?GLFWwindow $currentWindow = null;

    /**
     * Initializes GLFW and creates a window.
     */
    public static function begin() : GLFWwindow
    {
        // initalize GLFW
        if (!glfwInit()) {
            throw new Exception('GLFW could not be initialized!');
        }

        // prints the GLFW version for the examples sake
        echo glfwGetVersionString() . PHP_EOL;

        // configure the window
        glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

        // make sure to set the GLFW context version to the same 
        // version the GLFW extension has been compiled with, default 4.1
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // enable forward compatibitly, @see glfw docs for details
        // but mostly this fixes an issue many expirence on MacOS
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        // disable retina fb because there seems to be an issue: https://github.com/glfw/glfw/issues/1334
        // glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GL_FALSE);

        // glfwCreateWindow will initalizes a new window in which you can render,
        // you can have multiple windows of course.
        if (!$window = glfwCreateWindow(self::WIN_WIDTH, self::WIN_HEIGHT, "PHP GLFW Demo")) {
            throw new Exception('OS Window could not be initialized!');
        }

        // calling this method will make the given window object 
        // the one that is bound to the current GL context. In other words
        // all GL commands will be executed in the context of this window
        // Special in PHP-GLFW is that this will also initialize glad.
        glfwMakeContextCurrent($window);

        // setting the swap interval to "1" basically enabled vsync. 
        // more correctly it defines how many screen updates to wait for 
        // after glfwSwapBuffers has been called 
        glfwSwapInterval(1);

        // set the current window
        self::$currentWindow = $window;

        return $window;
    }

    /**
     * Terminates GLFW, destroys the window and frees all resources.
     */
    public static function stop(GLFWwindow $window) : void
    {
        glfwDestroyWindow($window);
        glfwTerminate();
    }

    /**
     * Compiles a basic shader program.
     */
    public static function compileShader(string $vertexShaderSource, string $fragmentShaderSource) : int
    {
        $vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource($vertexShader, $vertexShaderSource);
        glCompileShader($vertexShader);
        glGetShaderiv($vertexShader, GL_COMPILE_STATUS, $success);
        if (!$success) {
            throw new Exception('Vertex shader compilation failed: ' . glGetShaderInfoLog($vertexShader, 4096));
        }

        // create, upload and compile the fragment shader
        $fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource($fragShader, $fragmentShaderSource);
        glCompileShader($fragShader);
        glGetShaderiv($fragShader, GL_COMPILE_STATUS, $success);
        if (!$success) {
            throw new Exception("Fragment shader could not be compiled: " . glGetShaderInfoLog($fragShader, 4096));
        }

        // create a shader programm and link our vertex and framgent shader together
        $shaderProgram = glCreateProgram();
        glAttachShader($shaderProgram, $vertexShader);
        glAttachShader($shaderProgram, $fragShader);
        glLinkProgram($shaderProgram);

        glGetProgramiv($shaderProgram, GL_LINK_STATUS, $linkSuccess);
        if (!$linkSuccess) {
            throw new Exception("Shader program could not be linked.");
        }

        // free the shders
        glDeleteShader($vertexShader);
        glDeleteShader($fragShader);

        return $shaderProgram;
    }

    /**
     * Creates a cube vertex buffer
     * Returns the VBO and VAO
     */
    public static function createCubeVBO()
    {
        $verticies = new FloatBuffer([ 
            -0.5, -0.5, -0.5,  0.0, 0.0,
             0.5, -0.5, -0.5,  1.0, 0.0,
             0.5,  0.5, -0.5,  1.0, 1.0,
             0.5,  0.5, -0.5,  1.0, 1.0,
            -0.5,  0.5, -0.5,  0.0, 1.0,
            -0.5, -0.5, -0.5,  0.0, 0.0,
        
            -0.5, -0.5,  0.5,  0.0, 0.0,
             0.5, -0.5,  0.5,  1.0, 0.0,
             0.5,  0.5,  0.5,  1.0, 1.0,
             0.5,  0.5,  0.5,  1.0, 1.0,
            -0.5,  0.5,  0.5,  0.0, 1.0,
            -0.5, -0.5,  0.5,  0.0, 0.0,
        
            -0.5,  0.5,  0.5,  1.0, 0.0,
            -0.5,  0.5, -0.5,  1.0, 1.0,
            -0.5, -0.5, -0.5,  0.0, 1.0,
            -0.5, -0.5, -0.5,  0.0, 1.0,
            -0.5, -0.5,  0.5,  0.0, 0.0,
            -0.5,  0.5,  0.5,  1.0, 0.0,
        
             0.5,  0.5,  0.5,  1.0, 0.0,
             0.5,  0.5, -0.5,  1.0, 1.0,
             0.5, -0.5, -0.5,  0.0, 1.0,
             0.5, -0.5, -0.5,  0.0, 1.0,
             0.5, -0.5,  0.5,  0.0, 0.0,
             0.5,  0.5,  0.5,  1.0, 0.0,
        
            -0.5, -0.5, -0.5,  0.0, 1.0,
             0.5, -0.5, -0.5,  1.0, 1.0,
             0.5, -0.5,  0.5,  1.0, 0.0,
             0.5, -0.5,  0.5,  1.0, 0.0,
            -0.5, -0.5,  0.5,  0.0, 0.0,
            -0.5, -0.5, -0.5,  0.0, 1.0,
        
            -0.5,  0.5, -0.5,  0.0, 1.0,
             0.5,  0.5, -0.5,  1.0, 1.0,
             0.5,  0.5,  0.5,  1.0, 0.0,
             0.5,  0.5,  0.5,  1.0, 0.0,
            -0.5,  0.5,  0.5,  0.0, 0.0,
            -0.5,  0.5, -0.5,  0.0, 1.0
        ]);
        
        // create a vertex array object and upload the vertices
        glGenVertexArrays(1, $VAO);
        glGenBuffers(1, $VBO);
        
        glBindVertexArray($VAO);
        glBindBuffer(GL_ARRAY_BUFFER, $VBO);
        glBufferData(GL_ARRAY_BUFFER, $verticies, GL_STATIC_DRAW);
        
        // declare the vertex attributes
        // positions
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 5, 0);
        glEnableVertexAttribArray(0);
        
        // uv
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 5, GL_SIZEOF_FLOAT * 3);
        glEnableVertexAttribArray(1);
        
        // unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 

        return [$VAO, $VBO];
    }

    public static function createQuadVBO()
    {
        $verticies = new FloatBuffer([ 
            // positions    // texCoords
            -1.0,  1.0, 0.0, 1.0,
            -1.0, -1.0, 0.0, 0.0,
             1.0, -1.0, 1.0, 0.0,

            -1.0,  1.0, 0.0, 1.0,
             1.0, -1.0, 1.0, 0.0,
             1.0,  1.0, 1.0, 1.0
        ]);
        
        // create a vertex array object and upload the vertices
        glGenVertexArrays(1, $VAO);
        glGenBuffers(1, $VBO);
        
        glBindVertexArray($VAO);
        glBindBuffer(GL_ARRAY_BUFFER, $VBO);
        glBufferData(GL_ARRAY_BUFFER, $verticies, GL_STATIC_DRAW);
        
        // declare the vertex attributes
        // positions
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 4, 0);
        glEnableVertexAttribArray(0);
        
        // uv
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 4, GL_SIZEOF_FLOAT * 2);
        glEnableVertexAttribArray(1);
        
        // unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0); 

        return [$VAO, $VBO];
    }

    public static function loadTexture(string $path, int $format = GL_RGB) : int
    {
        // generate a texture, load it from a file and bind it
        glGenTextures(1, $texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, $texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object

        // set the texture wrapping parameters
        // here we basically tell opengl to repeat the texture, so when sampling out of bounds
        // it will still give you a result
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // PHP-GLFW comes with an image loader based on stb_image
        // with it you can easly create a pixel buffer object to upload to opengl
        $textureData = Texture2D::fromDisk($path);
        if ($textureData->channels() == 3) {
            $format = GL_RGB;
        } else if ($textureData->channels() == 4) {
            $format = GL_RGBA;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, $format, $textureData->width(), $textureData->height(), 0, $format, GL_UNSIGNED_BYTE, $textureData->buffer());
        
        // this call generates the mipmaps for the texture
        glGenerateMipmap(GL_TEXTURE_2D);

        return $texture;
    }

    public static function getShipObj() : ObjFileParser
    {
        // ensure zip extension is loaded
        if (!extension_loaded('zip')) {
            throw new \Exception('The zip extension is required to run this example');
        }

        if (!file_exists(__DIR__ . '/ship_light.obj')) {
            $zip = new ZipArchive();
            $zip->open(__DIR__ . '/ship_light.obj.zip');
            $zip->extractTo(__DIR__);
            $zip->close();
        }
        
        // load an object file with the ObjFileParser class, the assest we are loading 
        // is downloaded from kenney.nl, he provides a bunch of low poly free to use assets.
        $mesh = new \GL\Geometry\ObjFileParser(__DIR__ . '/ship_light.obj');

        return $mesh;
    }

    private static ?int $vgFontHandle = null;

    public static function getVGFontHandle(VGContext $vg) : int
    {
        if (self::$vgFontHandle === null) {
            self::$vgFontHandle = $vg->createFont('inconsolata', __DIR__ . '/font/inconsolata/Inconsolata-Regular.ttf');
        }

        return self::$vgFontHandle;
    }

    /**
     * Draws a colored function call text to the screen.
     * This is used to directly visualize what impact what parameter has on the result.
     * 
     * @param VGContext $vg 
     * @param string $functionCall 
     * @return void 
     */
    public static function drawFuncLabel(VGContext $vg, float $x, float $y, string $functionCall) 
    {
        // frist we need to parse the function call into its components
        $matches = [];
        preg_match('/([a-zA-Z0-9]+)\((.*)\)/', $functionCall, $matches);

        [$functionName, $params] = [$matches[1], $matches[2]];
        $params = explode(',', $params);
        $params = array_map('trim', $params);
        
        $vg->save();
        $vg->resetTransform();
        $vg->textAlign(0);
        $vg->fontSize(20);
        $vg->fontFaceId(self::getVGFontHandle($vg));
        $vg->beginPath();

        // first draw the function name
        $vg->fillColori(220, 220, 170, 255);
        $x = $vg->text($x, $y, $functionName);
        
        // open bracket
        $vg->fillColori(22, 159, 255, 255);
        $x = $vg->text($x, $y, '(');

        // now draw the parameters
        $paramCount = count($params);
        foreach($params as $i => $param) {

            // check if the param string is a float
            // if so parse it and format it to 2 decimal places
            if (is_numeric($param)) {
                $vg->fillColori(181, 206, 168, 255);
                if (strpos($param, '.') !== false) {
                    $param = number_format((float) $param, 2);
                } else {
                    $param = number_format((int) $param, 2);
                }
            } else {
                $vg->fillColori(206, 145, 120, 255);
            }

            $x = $vg->text($x, $y, $param);

            if ($i + 1 < $paramCount) {
                $vg->fillColori(212, 212, 212, 255);
                $x = $vg->text($x, $y, ', ');
            }
        }

        // close bracket
        $vg->fillColori(22, 159, 255, 255);
        $x = $vg->text($x, $y, ')');
        $vg->restore();
    }
    
    /**
     * Draws an array of function call labels to the screen.
     * 
     * @param VGContext $vg
     * @param float $x
     * @param float $y
     * @param array<string> $functionCalls
     */
    public static function drawFuncLabels(VGContext $vg, float $x, float $y, array $functionCalls) : void
    {
        foreach($functionCalls as $functionCall) {
            self::drawFuncLabel($vg, $x, $y, $functionCall);
            $y += 30;
        }
    }

    /**
     * Draws a grid representing the coordinate system.
     * 
     * @param VGContext $vg
     * @param float $resolution
     */
    public static function drawGrid(VGContext $vg, float $resolution = 100.0, float $offsetX = 0.0, float $offsetY = 0.0) : void
    {
        $vg->beginPath();

        $maxX = self::WIN_WIDTH;
        $maxY = self::WIN_HEIGHT;

        // $x = 0;
        // while ($x < self::WIN_WIDTH) {
        //     $vg->moveTo($x, 0);
        //     $vg->lineTo($x, self::WIN_HEIGHT);
        //     $x += $resolution;
        // }

        // $y = 0;
        // while ($y < self::WIN_HEIGHT) {
        //     $vg->moveTo(0, $y);
        //     $vg->lineTo(self::WIN_WIDTH, $y);
        //     $y += $resolution;
        // }

        // properly handle offset values
        // because this is a continues grid, pretty much need to just calculate the offset
        // inside the resolution meaning 150 % 100 = 50, so we need to offset by 50 etc.
        $offsetX = (int) $offsetX % $resolution;
        $offsetY = (int) $offsetY % $resolution;

        $x = -$offsetX;
        while ($x < $maxX) {
            $vg->moveTo($x, 0);
            $vg->lineTo($x, $maxY);
            $x += $resolution;
        }

        $y = -$offsetY;
        while ($y < $maxY) {
            $vg->moveTo(0, $y);
            $vg->lineTo($maxX, $y);
            $y += $resolution;
        }
        
        $vg->stroke();
    }

    /**
     * Draws a light point, mainly used to visualize the coordinate system.
     */
    public static function drawCoordPoint(VGContext $vg, float $x, float $y, ?string $label = null) : void
    {
        $vg->beginPath();
        $vg->circle($x, $y, 5);
        $vg->fillColori(80, 80, 80, 255);
        $vg->fill();

        if ($label !== null) {
            $vg->fontSize(20);
            $vg->fontFaceId(self::getVGFontHandle($vg));
            $vg->fillColori(80, 80, 80, 255);
            $vg->textAlign(0);
            $vg->text($x + 10, $y + 24, $label);
        }
    }

    /**
     * Draws a red point with a label, use this when you want to focus on a specific point.
     */
    public static function drawPoint(VGContext $vg, float $x, float $y, ?string $label = null) : void
    {
        // we only want to draw the point at the transformed position
        // so we get the transformed position and then reset the transformation state
        $point = $vg->transformPoint($x, $y);

        $vg->save();
        $vg->resetTransform();

        $vg->beginPath();
        $vg->circle($point->x, $point->y, 5);
        $vg->fillColori(255, 0, 0, 255);
        $vg->fill();

        if ($label !== null) {
            $vg->fontSize(20);
            $vg->fontFaceId(self::getVGFontHandle($vg));
            $vg->fillColori(255, 255, 255, 255);
            $vg->textAlign(VGAlign::LEFT | VGAlign::MIDDLE);
            $vg->text($point->x + 10, $point->y + 10, $label);
        }

        $vg->restore();
    }

    /**
     * Draws a grid representing the coordinate system.
     * 
     * @param VGContext $vg
     * @param float $resolution
     */
    public static function drawCoordSys(VGContext $vg) : void
    {
        // first store the current state
        $vg->save();
        
        $transformData = new FloatBuffer();
        $vg->currentTransform($transformData);

        $vg->resetTransform();

        // high res grid first
        $vg->strokeColori(20, 20, 20, 255);
        $vg->strokeWidth(1.0);
        self::drawGrid($vg, 10.0, -$transformData[4], -$transformData[5]);

        // low res grid
        $vg->strokeColori(50, 50, 50, 255);
        $vg->strokeWidth(2.0);
        self::drawGrid($vg, 100.0, -$transformData[4], -$transformData[5]);

        // render a the transform(0,0) point label
        self::drawCoordPoint($vg, $transformData[4], $transformData[5], '0,0');

        $vg->restore();
    }

    /**
     * Converts radians to a degree string, used to visualize the value
     * 
     * @return void 
     */
    public static function radToDegStr(float $rad) : string
    {
        return round(((int)rad2deg($rad) ) % 360, 0) . '°';
    }

    private static function getLengthIndicatorColor() : VGColor
    {
        return new VGColor(0.8, 0.8, 0.8, 1.0);
    }

    private static function getLengthTextColor() : VGColor
    {
        return new VGColor(0.7, 0.7, 0.7, 1.0);
    }

    /**
     * Draws a small perpendicular mark at a point on the line.
     */
    private static function drawEndMark(VGContext $vg, float $x, float $y, float $otherX, float $otherY) : void
    {
        $markLength = 5; // Length of the end mark
        $angle = atan2($y - $otherY, $x - $otherX) + M_PI / 2;

        // Calculate end points for the mark
        $endX1 = $x + $markLength * cos($angle);
        $endY1 = $y + $markLength * sin($angle);
        $endX2 = $x - $markLength * cos($angle);
        $endY2 = $y - $markLength * sin($angle);

        // Draw the mark
        $vg->beginPath();
        $vg->moveTo($endX1, $endY1);
        $vg->lineTo($endX2, $endY2);
        $vg->stroke();
    }

    /**
     * Draws a short perpendicular line at a given point.
     */
    public static function drawLength(VGContext $vg, float $x1, float $y1, float $x2, float $y2, ?string $label = null, string $labelPos = 'right') : void
    {
        // Main line
        $vg->beginPath();
        $vg->moveTo($x1, $y1);
        $vg->lineTo($x2, $y2);
        $vg->strokeColor(self::getLengthIndicatorColor());
        $vg->strokeWidth(2.0);
        $vg->stroke();

        // Draw end marks
        self::drawEndMark($vg, $x1, $y1, $x2, $y2);
        self::drawEndMark($vg, $x2, $y2, $x1, $y1);

        // Label
        if ($label !== null) {

            // get the center of the line
            $labelX = $x1 + ($x2 - $x1) * 0.5;
            $labelY = $y1 + ($y2 - $y1) * 0.5;

            // left side of the aabb
            if ($labelPos === 'right') {
                $labelX += 20;
                $vg->textAlign(VGAlign::LEFT | VGAlign::MIDDLE);
            } else if ($labelPos === 'left') {
                $labelX -= 20;
                $vg->textAlign(VGAlign::RIGHT | VGAlign::MIDDLE);
            } else if ($labelPos === 'top') {
                $labelY -= 20;
                $vg->textAlign(VGAlign::CENTER | VGAlign::BOTTOM);
            } else if ($labelPos === 'bottom') {
                $labelY += 20;
                $vg->textAlign(VGAlign::CENTER | VGAlign::TOP);
            } else if ($labelPos === 'a') {
                // a means at point 1
                $labelX = $x1;
                $labelY = $y1 - 20;
                $vg->textAlign(VGAlign::LEFT | VGAlign::MIDDLE);
            } else if ($labelPos === 'b') {
                // b means at point 2
                $labelX = $x2;
                $labelY = $y2 + 20;
                $vg->textAlign(VGAlign::LEFT | VGAlign::MIDDLE);
            }

            $vg->fontSize(20);
            $vg->fontFaceId(self::getVGFontHandle($vg));
            $vg->fillColor(self::getLengthTextColor());
            $vg->text($labelX, $labelY, $label);
        }
    }

    /**
     * Draws an interactable slider (horizontal or vertical).
     * Returns the new value if changed, otherwise the current value.
     */
    public static function drawSlider(
        VGContext $vg,
        float $x,
        float $y,
        float $width,
        float $height,
        float $min,
        float $max,
        float &$value,
        string $tooltip = '',
        bool $vertical = false
    ) : void {
        $vg->save();
        $vg->resetTransform();

        // bg
        if ($vertical) {
            $barX = $x;
            $barY = $y;
            $barW = $width;
            $barH = $height;
            $radius = $width / 2;
        } else {
            $barX = $x;
            $barY = $y;
            $barW = $width;
            $barH = $height;
            $radius = $height / 2;
        }
        $vg->beginPath();
        $vg->roundedRect($barX, $barY, $barW, $barH, $radius);
        $vg->fillColori(40, 40, 40, 220);
        $vg->fill();
        $vg->strokeColori(255, 255, 255, 100);
        $vg->strokeWidth(2);
        $vg->stroke();

        // handle pos
        $t = ($value - $min) / ($max - $min);
        if ($vertical) {
            $handleX = $x + $width / 2;
            $handleY = $y + $height - $t * $height;
            $handleRadius = $width * 0.7;
        } else {
            $handleX = $x + $t * $width;
            $handleY = $y + $height / 2;
            $handleRadius = $height * 0.7;
        }

        // draw handle
        $vg->beginPath();
        $vg->circle($handleX, $handleY, $handleRadius);
        $vg->fillColori(76, 66, 233, 255);
        $vg->fill();
        $vg->strokeColori(255, 255, 255, 180);
        $vg->strokeWidth(2);
        $vg->stroke();

        // cursor handling
        glfwGetCursorPos(self::$currentWindow, $mouseX, $mouseY);
        $isInside = $vertical
            ? ($mouseX >= $x && $mouseX <= $x + $width && $mouseY >= $y && $mouseY <= $y + $height)
            : ($mouseX >= $x && $mouseX <= $x + $width && $mouseY >= $y && $mouseY <= $y + $height);
        static $dragging = false;
        static $activeSlider = null;
        $sliderId = sprintf('%d_%d_%s_%s', $x, $y, $tooltip, $vertical ? 'v' : 'h');

        // draw tooltip
        if ($tooltip !== '' && $activeSlider === $sliderId && ($isInside || $dragging)) {
            $vg->fontSize(14);
            $vg->fontFaceId(self::getVGFontHandle($vg));
            $vg->fillColori(255,255,255,255);
            $vg->textAlign(VGAlign::LEFT | VGAlign::MIDDLE);
            if ($vertical) {
                $tooltipX = $handleX + $handleRadius * 2 + 10;
                $tooltipY = $handleY;
                $vg->text($tooltipX, $tooltipY, sprintf($tooltip, $value));
            } else {
                $tooltipX = $x + $t * $width + 10;
                $tooltipY = $y + 10;        
            }
        }


        $mouseDown = glfwGetMouseButton(self::$currentWindow, GLFW_MOUSE_BUTTON_LEFT) === GLFW_PRESS;
        if (($isInside && $mouseDown && !$dragging) || ($activeSlider === $sliderId && $mouseDown)) {
            $dragging = true;
            $activeSlider = $sliderId;
            if ($vertical) {
                $t = 1.0 - (($mouseY - $y) / $height);
            } else {
                $t = ($mouseX - $x) / $width;
            }
            $t = min(max($t, 0.0), 1.0);
            $value = $min + $t * ($max - $min);
        } else if ($activeSlider === $sliderId && !$mouseDown) {
            $dragging = false;
            $activeSlider = null;
        }

        $vg->restore();
    }

    /**
     * Draws a button group with the given options.
     */
    public static function drawButtonGroup(
        VGContext $vg, 
        float $x, 
        float $y, 
        array $options, 
        string &$selectedOption, 
        callable $onSelect
    ) : float 
    {
        $fontHandle = self::getVGFontHandle($vg);
        $fontSize = 20;
        $padding = 30; // distance between the buttons
        $innerOffset = 4; // offset outer rect and the inner button
        $lineHeight = $fontSize * 1.8;

        $vg->save();

        // we rest the transformation state as we render the button group
        // always in screen space, this makes calculating if a click is inside also easier
        $vg->resetTransform();

        $vg->fontSize($fontSize);
        $vg->fontFaceId($fontHandle);
        $vg->textAlign(VGAlign::LEFT | VGAlign::MIDDLE);

        // calculate the width of the button group
        $buttonWidths = [];
        $buttonOffsets = [];
        $offsetc = $padding;
        foreach($options as $key => $option) {
            $buttonWidths[$key] = $vg->textBounds(0, 0, $option);
            $buttonOffsets[$key] = $offsetc;
            $offsetc += $buttonWidths[$key] + $padding * 2;
        }

        $totalWidth = $offsetc - $padding;
        $totalHeight = $lineHeight + $innerOffset * 2;

        // draw the background
        $vg->beginPath();
        $vg->roundedRect($x, $y, $totalWidth, $totalHeight, 10);
        $vg->fillColori(255, 255, 255, 255);
        $vg->strokeColori(254, 254, 254, 255);
        $vg->fill();

        // get the current mouse position
        glfwGetCursorPos(self::$currentWindow, $mouseX, $mouseY);

        static $buttonPressed = [];

        // draw the buttons
        foreach($options as $key => $option) {
            $currentWidth = $buttonWidths[$key];
            $currentOffset = $buttonOffsets[$key];

            $bx = $x + $currentOffset - $padding + $innerOffset;
            $bw = $currentWidth + $padding * 2 - $innerOffset * 2;

            $by = $y + $innerOffset;
            $bh = $totalHeight - $innerOffset * 2;

            if (!isset($buttonPressed[$key])) {
                $buttonPressed[$key] = false;
            }

            // check if the mouse is inside the button
            $isInside = $mouseX >= $bx && $mouseX <= $bx + $bw && $mouseY >= $by && $mouseY <= $by + $bh;
            $isActive = $selectedOption === $key;

            if ($isInside && glfwGetMouseButton(self::$currentWindow, GLFW_MOUSE_BUTTON_LEFT) === GLFW_PRESS) {
                if (!$buttonPressed[$key]) {
                    $buttonPressed[$key] = true; 
                    $onSelect($key);
                }
            } else {
                $buttonPressed[$key] = false; 
            }

            if ($isActive || $isInside) {
                $vg->beginPath();
                $vg->roundedRect($bx, $by, $bw, $bh, 7);
                if ($isInside) {
                    $vg->fillColori(76, 66, 233, 200);
                    $vg->fill();
                } else {
                    $vg->fillColori(76, 66, 233, 255);
                    $vg->fill();
                }

                // set color for label
                $vg->fillColori(255, 255, 255, 255);
            } else {
                $vg->fillColori(0, 0, 0, 255);
            }

            // draw the label
            $vg->text($x + $currentOffset, $y + $totalHeight * 0.5, $option);
        }

        $vg->restore();

        return $totalWidth;
    }

    public static function drawButton(
        VGContext $vg, 
        float $x, 
        float $y, 
        string $label, 
        callable $onClick,
        string $align = 'center'
    ) : float
    {
        $fontHandle = self::getVGFontHandle($vg);
        $fontSize = 20;
        $padding = 30;
        $innerOffset = 4;
        $lineHeight = $fontSize * 1.8;
        $buttonId = sprintf('%s_%d_%d', $label, $x, $y);
        $initalX = $x;
    
        $vg->save();

        // just like the button group we reset the transformation state
        $vg->resetTransform();
    
        $vg->fontSize($fontSize);
        $vg->fontFaceId($fontHandle);
        $vg->textAlign(VGAlign::LEFT | VGAlign::MIDDLE);
    
        // calculate the width of the button
        $buttonWidth = $vg->textBounds(0, 0, $label) + $padding * 2;
        $totalHeight = $lineHeight + $innerOffset * 2;

        // adjust x and y to center the button
        if ($align === 'center') {
            $x -= $buttonWidth * 0.5;
            $y -= $totalHeight * 0.5;
        }
        else if ($align === 'right') {
            $x -= $buttonWidth;
        }
    
        // background always white
        $vg->beginPath();
        $vg->roundedRect($x, $y, $buttonWidth, $totalHeight, 10);
        $vg->fillColori(255, 255, 255, 255);
        $vg->fill();
    
        // Get the current mouse position
        glfwGetCursorPos(self::$currentWindow, $mouseX, $mouseY);
    
        // Check if the mouse is inside the button
        $isInside = $mouseX >= $x && $mouseX <= $x + $buttonWidth &&
                    $mouseY >= $y && $mouseY <= $y + $totalHeight;
    
        static $buttonPressed = [];
        if (!isset($buttonPressed[$buttonId])) {
            $buttonPressed[$buttonId] = false;
        }
    
        if ($isInside && glfwGetMouseButton(self::$currentWindow, GLFW_MOUSE_BUTTON_LEFT) === GLFW_PRESS) {
            if (!$buttonPressed[$buttonId]) {
                $buttonPressed[$buttonId] = true;
                $onClick();
            }
        } else {
            $buttonPressed[$buttonId] = false;
        }

        $highlightColor = VGColor::irgba(76, 66, 233, 200);
    
        // Set button color based on state
        if (!$isInside) {
            $vg->beginPath();
            $vg->fillColor($highlightColor);
            $vg->roundedRect($x + $innerOffset, $y + $innerOffset, $buttonWidth - $innerOffset * 2, $totalHeight - $innerOffset * 2, 7);
            $vg->fill();

            $vg->fillColor(VGColor::white());
        } else {

            // if the button is pressed currently we render some darker gray 
            // just to highlight that the button is currently pressed
            if (glfwGetMouseButton(self::$currentWindow, GLFW_MOUSE_BUTTON_LEFT) === GLFW_PRESS) {
                $vg->beginPath();
                $vg->fillColor(VGColor::lightGray());
                $vg->roundedRect($x + $innerOffset, $y + $innerOffset, $buttonWidth - $innerOffset * 2, $totalHeight - $innerOffset * 2, 7);
                $vg->fill();
            }

            $vg->fillColor($highlightColor);
        }
    
        // Draw the label
        $vg->text($x + $padding, $y + $totalHeight * 0.5, $label);
    
        $vg->restore();

        if ($align === 'left') {
            return $initalX + $buttonWidth;
        }

        return $x + $buttonWidth;
    }

    public static function createAnimation(VGContext $vg) : ExampleAnimation {
        return new ExampleAnimation($vg);
    }
}


class ExampleAnimationFrame {

    public array $animations = [];

    public const FRAME_KEY = 0;
    public const FRAME_TYPE = 1;
    public const FRAME_FROM = 2;
    public const FRAME_TO = 3;
    public const FRAME_DURATION = 4;

    public function __construct(
        public int $offset,
    )
    {
    }

    public function push(string $key, string $type, ?float $from, float $to, int $duration) : void
    {
        $this->animations[] = [$key, $type, $from, $to, $duration];
    }

    public function linear(string $key, float $from, float $to, int $duration) : void
    {
        $this->push($key, 'linear', $from, $to, $duration);
    }

    public function easeIn(string $key, float $from, float $to, int $duration) : void
    {
        $this->push($key, 'easeIn', $from, $to, $duration);
    }

    public function easeOut(string $key, float $from, float $to, int $duration) : void
    {
        $this->push($key, 'easeOut', $from, $to, $duration);
    }

    public function easeInOut(string $key, float $from, float $to, int $duration) : void
    {
        $this->push($key, 'easeInOut', $from, $to, $duration);
    }

    public function easeInOutTo(string $key, float $to, int $duration) : void
    {
        $this->push($key, 'easeInOut', null, $to, $duration);
    }

    public function easeOutBounceTo(string $key, float $to, int $duration) : void
    {
        $this->push($key, 'easeOutBounce', null, $to, $duration);
    }

    public function getFrameLenght() : int
    {
        $max = 0;
        foreach($this->animations as $animation) {
            $max = max($max, $animation[self::FRAME_DURATION]);
        }

        return $max;
    }
}

class ExampleAnimation
{
    public array $states = [];
    public array $stateProgress = [];
    public array $activeStates = [];

    private array $frames = [];

    private $lastTick = 0;
    private $tickSizes = [];

    public function __construct(
        private VGContext $vg,
    )
    {
    }

    private function alphaEaseIn(float $progress) : float
    {
        return $progress * $progress;
    }

    private function alphaEaseOut(float $progress) : float
    {
        return 1.0 - (1.0 - $progress) * (1.0 - $progress);
    }

    private function alphaEaseInOut(float $progress) : float
    {
        return $progress < 0.5 ? $this->alphaEaseIn($progress * 2.0) * 0.5 : $this->alphaEaseOut($progress * 2.0 - 1.0) * 0.5 + 0.5;
    }

    private function alphaEaseOutBounce(float $progress) : float
    {
        if ($progress < 1.0 / 2.75) {
            return 7.5625 * $progress * $progress;
        } else if ($progress < 2.0 / 2.75) {
            $progress -= 1.5 / 2.75;
            return 7.5625 * $progress * $progress + 0.75;
        } else if ($progress < 2.5 / 2.75) {
            $progress -= 2.25 / 2.75;
            return 7.5625 * $progress * $progress + 0.9375;
        } else {
            $progress -= 2.625 / 2.75;
            return 7.5625 * $progress * $progress + 0.984375;
        }
    }
    
    public function defaults(array $defaults) : self
    {
        foreach($defaults as $key => $value) {
            if (isset($this->states[$key])) {
                throw new \Exception('Default value for "' . $key . '" has already been set, you need to set the default value before you set the animation.');
            }
            $this->states[$key] = $value;
        }

        return $this;
    }

    public function after(int $offset, callable $callback) : self
    {
        $currentOffset = $offset;
        // get the last frames offset
        if (count($this->frames) > 0) {
            $lastFrame = $this->frames[count($this->frames) - 1];
            $currentOffset += $lastFrame->offset + $lastFrame->getFrameLenght();
        }

        $frame = new ExampleAnimationFrame($currentOffset);

        $callback($frame, $this->vg);

        $this->frames[] = $frame;

        return $this;
    }

    private function buildAnimationPreconditions()
    {
        $states = [];

        // in here we basically just determine the "from" values for each animation
        foreach($this->frames as $frame) {
            foreach($frame->animations as &$animation)  {
                if (!isset($states[$animation[ExampleAnimationFrame::FRAME_KEY]])) {
                    $states[$animation[ExampleAnimationFrame::FRAME_KEY]] = $animation[ExampleAnimationFrame::FRAME_FROM] ?? $this->states[$animation[ExampleAnimationFrame::FRAME_KEY]] ?? 0;
                }

                if ($animation[ExampleAnimationFrame::FRAME_FROM] === null) {
                    $animation[ExampleAnimationFrame::FRAME_FROM] = $states[$animation[ExampleAnimationFrame::FRAME_KEY]];
                }

                // set the new from value
                $states[$animation[ExampleAnimationFrame::FRAME_KEY]] = $animation[ExampleAnimationFrame::FRAME_TO];
            }
        }
    }

    public function build(float $time) : void 
    {
        if (empty($this->stateProgress)) {
            $this->buildAnimationPreconditions();
        }

        $this->tickSizes[] = $time - $this->lastTick;
        $this->lastTick = $time;
        // take max 8 samples
        if (count($this->tickSizes) > 16) {
            array_shift($this->tickSizes);
        }

        $tickSize = (array_sum($this->tickSizes) / count($this->tickSizes) * 1000);

        // collect all aviailable keys and their base values
        foreach($this->frames as $frame) {
            foreach($frame->animations as $animation)  {
                if (!isset($this->states[$animation[ExampleAnimationFrame::FRAME_KEY]])) {
                    $this->states[$animation[ExampleAnimationFrame::FRAME_KEY]] = $animation[ExampleAnimationFrame::FRAME_FROM];
                    $this->stateProgress[$animation[ExampleAnimationFrame::FRAME_KEY]] = 0.0;
                }
            }
        }

        // flatten the animations
        $animations = [];
        $lastTick = 0;
        foreach($this->frames as $frame) {
            foreach($frame->animations as $animation)  {
                $animations[] = [
                    'start' => $frame->offset,
                    'end' => $frame->offset + $animation[ExampleAnimationFrame::FRAME_DURATION],  
                    'ani' => $animation,
                ];

                $lastTick = max($lastTick, $frame->offset + $animation[ExampleAnimationFrame::FRAME_DURATION]);
            }
        }

        // convert time to tick 
        $tick = (int) round($time * 1000);
        // loop tick around the last tick
        $tick = $tick % $lastTick;

        // find all animations that are active at the current tick
        $activeAnimations = [];
        foreach($animations as $animation) {
            if ($tick >= $animation['start'] && $tick <= $animation['end'] + $tickSize) {
                $activeAnimations[] = $animation;
            }
        }

        // apply the animations
        foreach($activeAnimations as $animation) {
            [$key, $type, $from, $to, $duration] = $animation['ani'];
            $progress = ($tick - $animation['start']) / $duration;

            // clamp progress
            $progress = min(1.0, max(0.0, $progress));

            // apply easing function
            switch($type) {
                case 'linear':
                    break;
                case 'easeIn':
                    $progress = $this->alphaEaseIn($progress);
                    break;
                case 'easeOut':
                    $progress = $this->alphaEaseOut($progress);
                    break;
                case 'easeInOut':
                    $progress = $this->alphaEaseInOut($progress);
                    break;
                case 'easeOutBounce':
                    $progress = $this->alphaEaseOutBounce($progress);
                    break;
            }

            $value = $from + ($to - $from) * $progress;
            
            $this->states[$key] = $value;
            $this->stateProgress[$key] = $progress;
        }
    }
}