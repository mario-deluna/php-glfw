<?php

use GL\Buffer\FloatBuffer;
use GL\Geometry\ObjFileParser;
use GL\Texture\Texture2D;
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

    private static function getVGFontHandle(VGContext $vg) : int
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
        $vg->fill();
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
    public static function drawCoordPoint(VGContext $vg, float $x, float $y, string $label = null) : void
    {
        $vg->beginPath();
        $vg->circle($x, $y, 5);
        $vg->fillColori(80, 80, 80, 255);
        $vg->fill();

        if ($label !== null) {
            $vg->fontSize(20);
            $vg->fontFaceId(self::getVGFontHandle($vg));
            $vg->fillColori(80, 80, 80, 255);
            $vg->text($x + 10, $y + 24, $label);
        }
    }

    /**
     * Draws a red point with a label, use this when you want to focus on a specific point.
     */
    public static function drawPoint(VGContext $vg, float $x, float $y, string $label = null) : void
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
}
