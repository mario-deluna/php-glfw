<?php
/**
 * This example renders the Crytek Sponza scene. 
 * 
 * This example is far more complex then the previous ones. 
 * Which is also why it includes mutliple files and is split into multiple functions.
 */
require __DIR__ . '/99_example_helpers.php';

use GL\Math\{GLM, Vec3, Vec4, Mat4, Vec2};
use GL\Buffer\FloatBuffer;

/**
 * Config
 * 
 * ----------------------------------------------------------------------------
 */
// render resolution
$renderResolutionX = ExampleHelper::WIN_WIDTH;
$renderResolutionY = ExampleHelper::WIN_HEIGHT;
$renderResolutionDPI = 1.0;
$renderResolutionX *= $renderResolutionDPI;
$renderResolutionY *= $renderResolutionDPI;

// shadowmap resolution
$shadowMapWidth = 2048;
$shadowMapHeight = 2048;

// its a directional light which always points at 0, 0, 0
$lightPosition = new Vec3(0.0, 1200, 30); 
$lightColor = new Vec3(1.0, 1.0, 1.0);


$window = ExampleHelper::begin();


/**
 * Downloading the sponza scene
 * 
 * ----------------------------------------------------------------------------
 */

// ensure zip extension is loaded
if (!extension_loaded('zip')) {
    throw new \Exception('The zip extension is required to run this example');
}

// ensure the curl extension is loaded
if (!extension_loaded('curl')) {
    throw new \Exception('The curl extension is required to run this example');
}

// download and extract the sponza scene if not downloaded yet
$sponzaDir = __DIR__ . DIRECTORY_SEPARATOR . 'sponza';
$sponzaPath = $sponzaDir . DIRECTORY_SEPARATOR . 'Sponza-master';

if ((!is_dir($sponzaDir)) || (!file_exists($sponzaDir))) {
    echo "Downloading Sponza scene...\n";
    $sponzaZip = __DIR__ . '/sponza.zip';
    file_put_contents($sponzaZip, fopen("https://github.com/jimmiebergmann/Sponza/archive/refs/heads/master.zip", 'rb'));

    echo "Extracting Sponza scene...\n";
    $zip = new ZipArchive();
    $zip->open($sponzaZip);
    $zip->extractTo($sponzaDir);
    $zip->close();

    // remove the zip file
    unlink($sponzaZip);

    // check if download was successfully
    if (!file_exists($sponzaPath . '/sponza.obj')) {
        throw new \Exception('Failed to download Sponza scene');
    }

    // patch the sponza.mtl file to use the correct texture keywords
    // the material currently uses `map_Disp` instead of `map_bump` for the normal map
    // which is not supported by the ObjFileParser class.
    echo "Patching Sponza scene material...\n";
    $mtl = file_get_contents($sponzaPath . '/sponza.mtl');
    $mtl = str_replace('map_Disp', 'map_bump', $mtl);
    file_put_contents($sponzaPath . '/sponza.mtl', $mtl);

    echo "Done!\n";
}

/**
 * Loading the scene files
 * 
 * ----------------------------------------------------------------------------
 */
echo "Loading Sponza scene...\n";
$mesh = new \GL\Geometry\ObjFileParser($sponzaPath . '/sponza.obj');
// $mesh = new \GL\Geometry\ObjFileParser($sponzaPath . '/cube.obj');

// extract the meshes foreach material 
// in this example we only care about the position data, so we pass 'p' as the second argument.
$meshes = $mesh->getMeshes('pnctb');

echo "Uploading Sponza scene to GPU...\n";

// generate a vertex buffer for each mesh
$vertexBuffers = [];
foreach ($meshes as $i => $mesh) {
   
    echo "Uploading mesh #". $i ." with " . $mesh->vertices->size() . " vertices...\n";

    // create a vertex array object and upload the vertices
    glGenVertexArrays(1, $VAO);
    glGenBuffers(1, $VBO);

    glBindVertexArray($VAO);
    glBindBuffer(GL_ARRAY_BUFFER, $VBO);
    glBufferData(GL_ARRAY_BUFFER, $mesh->vertices, GL_STATIC_DRAW);

    // declare the vertex attributes
    // positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 14, 0);
    glEnableVertexAttribArray(0);

    // normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 14, GL_SIZEOF_FLOAT * 3);
    glEnableVertexAttribArray(1);

    // texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 14, GL_SIZEOF_FLOAT * 6);
    glEnableVertexAttribArray(2);

    // tangent
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 14, GL_SIZEOF_FLOAT * 8);
    glEnableVertexAttribArray(3);

    // bitangent
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 14, GL_SIZEOF_FLOAT * 11);
    glEnableVertexAttribArray(4);

    // load the textures for this mesh
    // and upload them to the GPU aswell
    $diffuseTexture = null;
    if ($mesh->material->diffuseTexture && file_exists($mesh->material->diffuseTexture->path)) {
        echo "loading diffuse texture: " . $mesh->material->diffuseTexture->name . "\n";
        $diffuseTexture = ExampleHelper::loadTexture($mesh->material->diffuseTexture->path);
    }

    $normalTexture = null;
    if ($mesh->material->bumpTexture && file_exists($mesh->material->bumpTexture->path)) {
        echo "loading normal map: " . $mesh->material->bumpTexture->name . "\n";
        $normalTexture = ExampleHelper::loadTexture($mesh->material->bumpTexture->path);
    }

    $alphaTexture = null;
    if ($mesh->material->dissolveTexture && file_exists($mesh->material->dissolveTexture->path)) {
        echo "loading alpha map: " . $mesh->material->dissolveTexture->name . "\n";
        $alphaTexture = ExampleHelper::loadTexture($mesh->material->dissolveTexture->path);
    }

    // determine some custom params based on the material
    // ---

    // if foliage disable face culling 
    $cullFace = !in_array($mesh->material->name, [
        'Material__57', // flowers
        'leaf'
    ]);

    $vertexBuffers[] = [
        'VAO' => $VAO,
        'VBO' => $VBO,
        'count' => $mesh->vertices->size() / 3,

        'textureDiffuse' => $diffuseTexture,
        'textureNormal' => $normalTexture,
        'textureAlpha' => $alphaTexture,

        'cullFace' => $cullFace,
    ];
}

// var_dump($vertexBuffers); die;

// unbind
glBindBuffer(GL_ARRAY_BUFFER, 0); 
glBindVertexArray(0); 


/**
 * Build Shaders
 * 
 * ----------------------------------------------------------------------------
 */
$shaders = require_once __DIR__ . '/10_sponza/shaders.php';

// get uniform locations here so we don't have to do it every frame
$uniformsLoc = [
    $shaders['geometry'] => [
        'model' => glGetUniformLocation($shaders['geometry'], 'model'),
        'view' => glGetUniformLocation($shaders['geometry'], 'view'),
        'projection' => glGetUniformLocation($shaders['geometry'], 'projection'),
        'light_space' => glGetUniformLocation($shaders['geometry'], 'light_space'),
        'texture_diffuse' => glGetUniformLocation($shaders['geometry'], 'texture_diffuse'),
        'texture_normal' => glGetUniformLocation($shaders['geometry'], 'texture_normal'),
        'light_dir' => glGetUniformLocation($shaders['geometry'], 'light_dir'),
        'light_color' => glGetUniformLocation($shaders['geometry'], 'light_color'),
        'shadowmap' => glGetUniformLocation($shaders['geometry'], 'shadowmap'),
        'ambient' => glGetUniformLocation($shaders['geometry'], 'ambient'),
        'use_normal_map' => glGetUniformLocation($shaders['geometry'], 'use_normal_map'),
    ],

    $shaders['shadowmap'] => [
        'model' => glGetUniformLocation($shaders['shadowmap'], 'model'),
        'light_space' => glGetUniformLocation($shaders['shadowmap'], 'light_space'),
    ],

    $shaders['quad'] => [
        'u_texture' => glGetUniformLocation($shaders['quad'], 'u_texture'),    
    ],

    $shaders['depth'] => [
        'u_texture' => glGetUniformLocation($shaders['depth'], 'u_texture'),    
    ],
];

/**
 * Build Shadowmap
 * 
 * ----------------------------------------------------------------------------
 */
glGenFramebuffers(1, $shadowFBO);
glBindFramebuffer(GL_FRAMEBUFFER, $shadowFBO);

// also create texture to hold depth map, this is what we will sample later
glGenTextures(1, $shadowTexture);
glBindTexture(GL_TEXTURE_2D, $shadowTexture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, $shadowMapWidth, $shadowMapHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, null);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

// attach depth texture as FBO's depth buffer
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, $shadowTexture, 0);
glDrawBuffer(GL_NONE);
glReadBuffer(GL_NONE);
glBindFramebuffer(GL_FRAMEBUFFER, 0);

/**
 * Build offscreen render target
 *
 * ----------------------------------------------------------------------------
 */
glGenFramebuffers(1, $offscreenFBO);
glBindFramebuffer(GL_FRAMEBUFFER, $offscreenFBO);

// create a color attachment texture
glGenTextures(1, $offscreenTexture);
glBindTexture(GL_TEXTURE_2D, $offscreenTexture);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, $renderResolutionX, $renderResolutionY, 0, GL_RGB, GL_UNSIGNED_BYTE, null);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
glGenRenderbuffers(1, $offscreenRBO);
glBindRenderbuffer(GL_RENDERBUFFER, $offscreenRBO);
glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, $renderResolutionX, $renderResolutionY);

// attach the texture and RBO to the framebuffer
glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, $offscreenTexture, 0);
glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, $offscreenRBO);

// finally check if framebuffer is complete
if (glCheckFramebufferStatus(GL_FRAMEBUFFER) !== GL_FRAMEBUFFER_COMPLETE) {
    throw new Exception('Offscreen Framebuffer is not complete!');
}

glBindFramebuffer(GL_FRAMEBUFFER, 0);

/**
 * Debug quad
 * To visualize various buffers
 * 
 * ----------------------------------------------------------------------------
 */
$quadVerticies = new \GL\Buffer\FloatBuffer([
    -1.0, -1.0, 0.0, 0.0,
    1.0, -1.0, 1.0, 0.0,
    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0,
    -1.0, 1.0, 0.0, 1.0,
    -1.0, -1.0, 0.0, 0.0
]);
glGenVertexArrays(1, $quadVAO);
glGenBuffers(1, $quadVBO);
glBindVertexArray($quadVAO);
glBindBuffer(GL_ARRAY_BUFFER, $quadVBO);
glBufferData(GL_ARRAY_BUFFER, $quadVerticies, GL_STATIC_DRAW);

// declare the vertex attributes
// positions
glVertexAttribPointer(0, 2, GL_FLOAT, false, GL_SIZEOF_FLOAT * 4, 0);
glEnableVertexAttribArray(0);

// uv
glVertexAttribPointer(1, 2, GL_FLOAT, false, GL_SIZEOF_FLOAT * 4, GL_SIZEOF_FLOAT * 2);
glEnableVertexAttribArray(1);

// unbind
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);


/**
 * Camera & Controls
 * 
 * ----------------------------------------------------------------------------
 */
// view matrix, this is the camera / eye position and rotation
$view = new Mat4;
$view->translate(new Vec3(0.0, 0.0, -2.0));

$projection = new Mat4;
$projection->perspective(glm::radians(70.0), ExampleHelper::WIN_WIDTH / ExampleHelper::WIN_HEIGHT, 0.1, 32000.0);

// capture keyboard events to toggle rendering modes

// wireframe mode
$wireframe = false;

// enable / disable normal mapping
$useNormalMap = 1.0;

glfwSetKeyCallback($window, function ($key, $scancode, $action, $mods) use ($window, &$wireframe, &$useNormalMap) 
{
    // exit app
    if ($key == GLFW_KEY_ESCAPE && $action == GLFW_PRESS) {
        glfwSetWindowShouldClose($window, true);
    }

    // toggle wireframe mode
    if ($key == GLFW_KEY_F && $action == GLFW_PRESS) {
        $wireframe = !$wireframe;
    }

    // toggle normal mapping
    if ($key == GLFW_KEY_N && $action == GLFW_PRESS) {
        $useNormalMap = $useNormalMap ? 0.0 : 1.0;
        echo "use normal map: " . $useNormalMap . "\n";
    }
});

// capture mouse events to move the camara around
$lastX = ExampleHelper::WIN_WIDTH / 2;
$lastY = ExampleHelper::WIN_HEIGHT / 2;
$firstMouse = true;

// camera rotation
$cameraRotation = new Vec2(0.0, 0.0);

glfwSetCursorPosCallback($window, function ($xpos, $ypos) use ($window, &$cameraRotation, &$lastX, &$lastY, &$firstMouse) {

    // only move the camera if the left mouse button is pressed
    if (glfwGetMouseButton($window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS) {
        glfwSetInputMode($window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        $firstMouse = true;
        return;
    }

    glfwSetInputMode($window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if ($firstMouse) {
        $lastX = $xpos;
        $lastY = $ypos;
        $firstMouse = false;
    }

    $xoffset = $xpos - $lastX;
    $yoffset = $lastY - $ypos;
    $lastX = $xpos;
    $lastY = $ypos; 

    // apply eular rotation
    $cameraRotation->x = $cameraRotation->x - $xoffset * 0.3;
    $cameraRotation->y = $cameraRotation->y + $yoffset * 0.3;
});


/**
 * Render the scene
 * 
 * ----------------------------------------------------------------------------
 */

// print some help to the console
echo str_repeat('-', 80) . PHP_EOL;
echo '-> Use the mouse to rotate the object' . PHP_EOL;
echo '-> Press ESC to close the window' . PHP_EOL;
echo '-> Press F to toggle wireframe mode' . PHP_EOL;
echo '-> Press N to toggle normal mapping' . PHP_EOL;
echo str_repeat('-', 80) . PHP_EOL;

// update the viewport
glViewport(0, 0, ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT);

// enable depth testing, because we are rendering a 3d object with overlapping
// triangles
glEnable(GL_DEPTH_TEST);
glEnable(GL_CULL_FACE);
glDisable(GL_BLEND);

// define the model matrix aka the object postion in the world
// we use the same for every mesh as we render only one model that is already translated
$model = new Mat4;
$model->scale(new Vec3(0.5));

// Main Loop
// ---------------------------------------------------------------------------- 
while (!glfwWindowShouldClose($window))
{
    // continuesly rotate the light 0
    $lightPosition->x = cos((20 + glfwGetTime()) * 0.1) * 1000;
    $lightPosition->z = cos((20 + glfwGetTime()) * 0.04) * 1500;
    
    // calculate the light direction. (It points to 0,0,0)
    $lightDir = glm::normalize($lightPosition);

    /**
     * Shadow Pass
     * 
     * ----------------------------------------------------------------------------
     */
    // extract light position from view matrix
    // $lightPos = new Vec3($view[12], $view[13], $view[14]);
    $shadowSize = 600;


    $lightProjection = new Mat4;
    $lightProjection->ortho(-$shadowSize, $shadowSize, -$shadowSize, $shadowSize, 1.0, 5000);
    $lightView = new Mat4;
    $lightView->translate($lightPosition);
    // $lightView->lookAt($lightPos, $lightPos + ($lightDir * 1000), new Vec3(0.0, 1.0, 0.0));
    $lightView->lookAt($lightPosition, new Vec3(0, 0, 0), new Vec3(0.0, 0.0, 1.0));
    $lightSpace = $lightProjection * $lightView;

    // render our scene for the shadow map
    glViewport(0, 0, $shadowMapWidth, $shadowMapHeight);
    glBindFramebuffer(GL_FRAMEBUFFER, $shadowFBO);
    glClear(GL_DEPTH_BUFFER_BIT);
    glCullFace(GL_FRONT);
    glUseProgram($shaders['shadowmap']);
    glUniformMatrix4f($uniformsLoc[$shaders['shadowmap']]['light_space'], GL_FALSE, $lightSpace);
    glUniformMatrix4f($uniformsLoc[$shaders['shadowmap']]["model"], GL_FALSE, $model);
     
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // bind & draw the vertex array
    foreach($vertexBuffers as $vb) 
    {
        glBindVertexArray($vb['VAO']);
        glDrawArrays(GL_TRIANGLES, 0, $vb['count']);
    }
    

    /**
     * Forward Pass
     * 
     * ----------------------------------------------------------------------------
     */
    
    // bind the render target
    glBindFramebuffer(GL_FRAMEBUFFER, $offscreenFBO);
    glViewport(0, 0, $renderResolutionX, $renderResolutionY);

    // use some blueish color to imitate a skybox
    glClearColor(0.52, 0.80, 0.92, 1.0);
    // note how we are clearing both the DEPTH and COLOR buffers.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // reset culling
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);

    // use the shader, will active the given shader program
    // for the coming draw calls.
    glUseProgram($shaders['geometry']);

    // reverse the view matrix, because we are moving the world
    // instead of the camera
    // copy the view matrix, because we need to modify it
    $eye = $view->copy();
    $eye->rotate(GLM::radians($cameraRotation->x), new Vec3(0.0, 1.0, 0.0));
    $eye->rotate(GLM::radians($cameraRotation->y), new Vec3(1.0, 0.0, 0.0));
    $eye->inverse();

    // extract the forward vector from the view matrix
    $col = $eye->col(2);
    $forward = new Vec3($col->x, $col->y, $col->z);

    // using W,A,S,D to move the camera around
    if (glfwGetKey($window, GLFW_KEY_W) == GLFW_PRESS) {
        $view->translate($forward * -1);
    }
    else if (glfwGetKey($window, GLFW_KEY_S) == GLFW_PRESS) {
        $view->translate($forward);
    }

    if (glfwGetKey($window, GLFW_KEY_A) == GLFW_PRESS) {
        $view->translate($forward->cross(new Vec3(0.0, 1.0, 0.0)));
    }
    else if (glfwGetKey($window, GLFW_KEY_D) == GLFW_PRESS) {
        $view->translate($forward->cross(new Vec3(0.0, 1.0, 0.0)) * -1);
    }

    // now set the uniform variables in the shader.
    // note that we use `glUniformMatrix4f` instead of `glUniformMatrix4fv` to pass a single matrix.
    glUniformMatrix4f($uniformsLoc[$shaders['geometry']]["model"], GL_FALSE, $model);
    glUniformMatrix4f($uniformsLoc[$shaders['geometry']]["view"], GL_FALSE, $eye);
    glUniformMatrix4f($uniformsLoc[$shaders['geometry']]["projection"], GL_FALSE, $projection);
    $lv = $lightView->copy();
    // $lv->inverse();
    // glUniformMatrix4f($uniformsLoc[$shaders['geometry']]["view"], GL_FALSE, $lv);
    // glUniformMatrix4f($uniformsLoc[$shaders['geometry']]["projection"], GL_FALSE, $lightProjection);

    // set the light direction and color
    glUniformVec3f($uniformsLoc[$shaders['geometry']]["light_dir"], $lightDir);
    glUniformVec3f($uniformsLoc[$shaders['geometry']]["light_color"], $lightColor);

    // set shadowmap
    glActiveTexture(GL_TEXTURE10);
    glBindTexture(GL_TEXTURE_2D, $shadowTexture);
    glUniform1i($uniformsLoc[$shaders['geometry']]["shadowmap"], 10);
    glUniformMatrix4f($uniformsLoc[$shaders['geometry']]["light_space"], GL_FALSE, $lightSpace);

    // other settings
    glUniform1f($uniformsLoc[$shaders['geometry']]["use_normal_map"], $useNormalMap);

    // bind & draw the vertex array
    foreach($vertexBuffers as $vb) 
    {
        // enable disable face culling
        if ($wireframe || $vb['cullFace'] === false) {
            glDisable(GL_CULL_FACE);
        } else {
            glEnable(GL_CULL_FACE);
        }

        // update the diffuse texture
        if ($vb['textureDiffuse']) {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, $vb['textureDiffuse']);
            glUniform1i($uniformsLoc[$shaders['geometry']]["texture_diffuse"], 0);
        } else {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        // update the normal texture
        if ($vb['textureNormal']) {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, $vb['textureNormal']);
            glUniform1i($uniformsLoc[$shaders['geometry']]["texture_normal"], 1);
        } else {
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, 0);
        }

        if ($wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        // draw the vertex array
        glBindVertexArray($vb['VAO']);
        glDrawArrays(GL_TRIANGLES, 0, $vb['count']);
    }


    /**
     * Bind the main FB
     * 
     * ----------------------------------------------------------------------------
     */
    
    // get framebuffer size
    glfwGetFramebufferSize($window, $fx, $fy);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, $fx, $fy);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /**
     * Debug Out
     * 
     * ----------------------------------------------------------------------------
     */
    if (0) 
    {
        $debugTexture = $shadowTexture;

        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glUseProgram($shaders['depth']);
        glUniform1i($uniformsLoc[$shaders['depth']]["u_texture"], 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, $debugTexture);
        glBindVertexArray($quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, $quadVBO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    else 
    {
        // draw the render texture to the screen
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glUseProgram($shaders['quad']);
        glUniform1i($uniformsLoc[$shaders['quad']]["u_texture"], 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, $offscreenTexture);
        glBindVertexArray($quadVAO);
        glBindBuffer(GL_ARRAY_BUFFER, $quadVBO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    // swap the windows framebuffer and
    // poll queued window events.
    glfwSwapBuffers($window);
    glfwPollEvents();
}


// stop & cleanup
foreach($vertexBuffers as $vb) {
    glDeleteBuffers(1, $vb['VBO']);
    glDeleteVertexArrays(1, $vb['VAO']);
}

ExampleHelper::stop($window);
