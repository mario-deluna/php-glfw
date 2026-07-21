<?php
/**
 * This example shows off the DrawCallAssembler with payload attributes.
 *
 * Instead of setting a material color uniform per draw call, we hand the
 * assembler an extra buffer of per-instance data (an RGB color here) with
 * bindPayloadData / bindPayloadBuffer. The assembler streams that payload
 * alongside the instance transforms, so it arrives in the shader as a plain
 * vertex attribute and every instance can carry its own color for free.
 */
require __DIR__ . '/99_example_helpers.php';

use GL\Math\{GLM, Mat4, Vec3};
use GL\Rendering\DrawCallAssembler;
use GL\Buffer\FloatBuffer;
use GL\Buffer\UIntBuffer;

/**
 * Config
 *
 * ----------------------------------------------------------------------------
 */
// how many ships to scatter through the field
const INSTANCE_COUNT = 50000;

// distance at which a ship is swapped for its cheap LOD cube
const LOD_SWITCH_DISTANCE = 1000.0;


$window = ExampleHelper::begin();


/**
 * Setup window & GL state
 *
 * ----------------------------------------------------------------------------
 */
glfwSetWindowTitle($window, 'PHP-GLFW DrawCallAssembler with Payload');
glViewport(0, 0, ExampleHelper::WIN_WIDTH, ExampleHelper::WIN_HEIGHT);

// enable depth testing and back face culling, because we are rendering
// solid 3d objects with overlapping triangles
glEnable(GL_DEPTH_TEST);
glEnable(GL_CULL_FACE);
glCullFace(GL_BACK);


/**
 * Build shader
 *
 * ----------------------------------------------------------------------------
 */
// note how the color arrives as a per-instance vertex attribute (location 6)
// instead of a material uniform. that is the payload the assembler streams for us.
$shader = ExampleHelper::compileShader(<<<'GLSL'
#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

// transform matrix (instanced)
layout (location = 2) in mat4 i_transform;

// per-instance color (instanced payload)
layout (location = 6) in vec3 i_color;

out vec3 v_normal;
out vec3 v_world_pos;
out vec3 v_instance_color;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	mat4 model = i_transform;
	mat3 normal_matrix = mat3(transpose(inverse(model)));
	vec4 world_pos = model * vec4(a_position, 1.0);

	v_normal = normalize(normal_matrix * a_normal);
	v_world_pos = world_pos.xyz;
	v_instance_color = i_color;

	gl_Position = projection * view * world_pos;
}
GLSL,
<<<'GLSL'
#version 330 core
in vec3 v_normal;
in vec3 v_world_pos;
in vec3 v_instance_color;

out vec4 fragment_color;

uniform vec3 light_dir;
uniform vec3 light_color;
uniform vec3 camera_pos;
uniform float ambient_strength = 0.12;

void main()
{
	vec3 normal = normalize(v_normal);
	vec3 lit_dir = normalize(light_dir);
	vec3 view_dir = normalize(camera_pos - v_world_pos);

	float diffuse = max(dot(normal, lit_dir), 0.0);
	float specular = pow(max(dot(normal, normalize(lit_dir + view_dir)), 0.0), 32.0) * 0.2;

	// use the per-instance payload color instead of a material uniform
	vec3 color = v_instance_color * (ambient_strength + diffuse) * light_color + specular;
	fragment_color = vec4(color, 1.0);
}
GLSL);


/**
 * Create meshes
 *
 * ----------------------------------------------------------------------------
 */

// load the ship model and upload it to the GPU. we also track the bounding box
// of the mesh, the assembler needs it later for frustum culling.
$ship = ExampleHelper::getShipObj();
$shipMeshes = $ship->getMeshes('pn');

if (empty($shipMeshes)) {
    throw new RuntimeException('ship model does not contain any meshes');
}

$vertexBuffer = new FloatBuffer();
foreach ($shipMeshes as $mesh) {
    $vertexBuffer->append($mesh->vertices);
}

if ($vertexBuffer->size() === 0) {
    throw new RuntimeException('ship mesh did not provide vertex data');
}

// walk the vertex data (6 floats per vertex: xyz + normal) straight from the
// buffer and grow a bounding box to fit every position
$min = [INF, INF, INF];
$max = [-INF, -INF, -INF];
$floatCount = $vertexBuffer->size();
for ($i = 0; $i < $floatCount; $i += 6) {
    $x = $vertexBuffer[$i];
    $y = $vertexBuffer[$i + 1];
    $z = $vertexBuffer[$i + 2];

    if ($x < $min[0]) { $min[0] = $x; }
    if ($y < $min[1]) { $min[1] = $y; }
    if ($z < $min[2]) { $min[2] = $z; }

    if ($x > $max[0]) { $max[0] = $x; }
    if ($y > $max[1]) { $max[1] = $y; }
    if ($z > $max[2]) { $max[2] = $z; }
}

$vertexCount = $vertexBuffer->size() / 6;
$aabbMin = new Vec3($min[0], $min[1], $min[2]);
$aabbMax = new Vec3($max[0], $max[1], $max[2]);

// create a vertex array object and upload the ship vertices
glGenVertexArrays(1, $vao);
glGenBuffers(1, $vbo);

glBindVertexArray($vao);
glBindBuffer(GL_ARRAY_BUFFER, $vbo);
glBufferData(GL_ARRAY_BUFFER, $vertexBuffer, GL_STATIC_DRAW);

// declare the vertex attributes
// positions
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 6, 0);
glEnableVertexAttribArray(0);

// normals
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 6, GL_SIZEOF_FLOAT * 3);
glEnableVertexAttribArray(1);

// unbind
glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);

// build a simple cube that reuses the ship's bounding box as its LOD stand-in.
// far away we can no longer tell a ship from a box, so this is basically free.
$x0 = $aabbMin->x; $x1 = $aabbMax->x;
$y0 = $aabbMin->y; $y1 = $aabbMax->y;
$z0 = $aabbMin->z; $z1 = $aabbMax->z;

$lodData = [
    // front
    $x0, $y0, $z1, 0.0, 0.0, 1.0,
    $x1, $y0, $z1, 0.0, 0.0, 1.0,
    $x1, $y1, $z1, 0.0, 0.0, 1.0,
    $x1, $y1, $z1, 0.0, 0.0, 1.0,
    $x0, $y1, $z1, 0.0, 0.0, 1.0,
    $x0, $y0, $z1, 0.0, 0.0, 1.0,
    // back
    $x0, $y0, $z0, 0.0, 0.0, -1.0,
    $x0, $y1, $z0, 0.0, 0.0, -1.0,
    $x1, $y1, $z0, 0.0, 0.0, -1.0,
    $x1, $y1, $z0, 0.0, 0.0, -1.0,
    $x1, $y0, $z0, 0.0, 0.0, -1.0,
    $x0, $y0, $z0, 0.0, 0.0, -1.0,
    // left
    $x0, $y0, $z0, -1.0, 0.0, 0.0,
    $x0, $y0, $z1, -1.0, 0.0, 0.0,
    $x0, $y1, $z1, -1.0, 0.0, 0.0,
    $x0, $y1, $z1, -1.0, 0.0, 0.0,
    $x0, $y1, $z0, -1.0, 0.0, 0.0,
    $x0, $y0, $z0, -1.0, 0.0, 0.0,
    // right
    $x1, $y0, $z0, 1.0, 0.0, 0.0,
    $x1, $y1, $z0, 1.0, 0.0, 0.0,
    $x1, $y1, $z1, 1.0, 0.0, 0.0,
    $x1, $y1, $z1, 1.0, 0.0, 0.0,
    $x1, $y0, $z1, 1.0, 0.0, 0.0,
    $x1, $y0, $z0, 1.0, 0.0, 0.0,
    // bottom
    $x0, $y0, $z0, 0.0, -1.0, 0.0,
    $x1, $y0, $z0, 0.0, -1.0, 0.0,
    $x1, $y0, $z1, 0.0, -1.0, 0.0,
    $x1, $y0, $z1, 0.0, -1.0, 0.0,
    $x0, $y0, $z1, 0.0, -1.0, 0.0,
    $x0, $y0, $z0, 0.0, -1.0, 0.0,
    // top
    $x0, $y1, $z0, 0.0, 1.0, 0.0,
    $x0, $y1, $z1, 0.0, 1.0, 0.0,
    $x1, $y1, $z1, 0.0, 1.0, 0.0,
    $x1, $y1, $z1, 0.0, 1.0, 0.0,
    $x1, $y1, $z0, 0.0, 1.0, 0.0,
    $x0, $y1, $z0, 0.0, 1.0, 0.0,
];

$lodBuffer = new FloatBuffer($lodData);
$lodVertexCount = count($lodData) / 6;
$lodAabbMin = new Vec3($aabbMin->x, $aabbMin->y, $aabbMin->z);
$lodAabbMax = new Vec3($aabbMax->x, $aabbMax->y, $aabbMax->z);

// upload the LOD cube the same way we did the ship
glGenVertexArrays(1, $lodVao);
glGenBuffers(1, $lodVbo);

glBindVertexArray($lodVao);
glBindBuffer(GL_ARRAY_BUFFER, $lodVbo);
glBufferData(GL_ARRAY_BUFFER, $lodBuffer, GL_STATIC_DRAW);

glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 6, 0);
glEnableVertexAttribArray(0);
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, GL_SIZEOF_FLOAT * 6, GL_SIZEOF_FLOAT * 3);
glEnableVertexAttribArray(1);

glBindBuffer(GL_ARRAY_BUFFER, 0);
glBindVertexArray(0);


/**
 * Register meshes & LOD
 *
 * ----------------------------------------------------------------------------
 */
$assembler = new DrawCallAssembler(
    initialMeshCapacity: 4,
    initialInstanceCapacity: INSTANCE_COUNT + 64,
    initialCommandCapacity: 64
);

// register both meshes with the assembler. it hands back a handle we use to
// submit instances and to wire up the LOD table.
$shipHandle = $assembler->registerMesh(
    vao: $vao,
    vertexOffset: 0,
    vertexCount: $vertexCount,
    indexOffset: 0,
    indexCount: 0,
    aabbMin: $aabbMin,
    aabbMax: $aabbMax,
    materialHint: 0,
    primitive: GL_TRIANGLES
);

$cubeHandle = $assembler->registerMesh(
    vao: $lodVao,
    vertexOffset: 0,
    vertexCount: $lodVertexCount,
    indexOffset: 0,
    indexCount: 0,
    aabbMin: $lodAabbMin,
    aabbMax: $lodAabbMax,
    materialHint: 0,
    primitive: GL_TRIANGLES
);

// tell the assembler to swap the ship for the cube past LOD_SWITCH_DISTANCE
$lodThresholds = new FloatBuffer([LOD_SWITCH_DISTANCE]);
$lodHandles = new UIntBuffer([$cubeHandle]);
$assembler->setLodTable(
    meshHandle: $shipHandle,
    distanceThresholds: $lodThresholds,
    meshHandles: $lodHandles
);

// our own little lookup so the execute() callback can bind the right VAO
// for whichever mesh handle the assembler asks us to draw
$meshRegistry = [
    $shipHandle => [
        'vao' => $vao,
        'vertex_count' => $vertexCount,
        'primitive' => GL_TRIANGLES,
        'base_vertex' => 0,
    ],
    $cubeHandle => [
        'vao' => $lodVao,
        'vertex_count' => $lodVertexCount,
        'primitive' => GL_TRIANGLES,
        'base_vertex' => 0,
    ],
];


/**
 * Scene / instance data
 *
 * ----------------------------------------------------------------------------
 */
// generate the field and, at the same time, fill a payload buffer with one
// RGB color per instance
$payloadBuffer = new FloatBuffer();
$instances = generate_asteroid_field_with_colors($shipHandle, INSTANCE_COUNT, $payloadBuffer);
$wireframe = false;
$animate = true;

// bind payload data: 3 floats per instance (RGB color)
$assembler->bindPayloadData($payloadBuffer, 3);

// get uniform locations here so we don't have to do it every frame
$uniforms = [
    'view' => glGetUniformLocation($shader, 'view'),
    'projection' => glGetUniformLocation($shader, 'projection'),
    'camera_pos' => glGetUniformLocation($shader, 'camera_pos'),
    'light_dir' => glGetUniformLocation($shader, 'light_dir'),
    'light_color' => glGetUniformLocation($shader, 'light_color'),
    'ambient' => glGetUniformLocation($shader, 'ambient_strength'),
];

// set the light and ambient uniforms once, they never change
glUseProgram($shader);
glUniform3f($uniforms['light_dir'], 0.35, 0.7, 0.2);
glUniform3f($uniforms['light_color'], 1.0, 0.95, 0.85);
glUniform1f($uniforms['ambient'], 0.12);


/**
 * Camera & controls
 *
 * ----------------------------------------------------------------------------
 */
// capture keyboard events to toggle rendering modes and rebuild the scene
glfwSetKeyCallback($window, function ($key, $scancode, $action, $mods) use (&$wireframe, &$animate, &$instances, $shipHandle, $window, $assembler, &$payloadBuffer)
{
    if ($action !== GLFW_PRESS) {
        return;
    }

    // exit app
    if ($key === GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose($window, true);
        return;
    }

    // toggle rotation
    if ($key === GLFW_KEY_SPACE) {
        $animate = !$animate;
        return;
    }

    // toggle wireframe mode
    if ($key === GLFW_KEY_F) {
        $wireframe = !$wireframe;
        return;
    }

    // rebuild the field with fresh random colors, then rebind the new payload
    if ($key === GLFW_KEY_R) {
        $payloadBuffer->clear();
        $instances = generate_asteroid_field_with_colors($shipHandle, INSTANCE_COUNT, $payloadBuffer);
        $assembler->bindPayloadData($payloadBuffer, 3);
    }
});

// the camera is a free flying camera driven by yaw / pitch euler angles
$cameraPos = new Vec3(0.0, 45.0, 140.0);
$cameraYaw = -90.0;
$cameraPitch = -12.5;
$mouseInput = [
    'lastX' => ExampleHelper::WIN_WIDTH / 2,
    'lastY' => ExampleHelper::WIN_HEIGHT / 2,
    'firstMouse' => true,
];

// capture mouse events to look around while the left button is held
glfwSetCursorPosCallback($window, function ($xpos, $ypos) use ($window, &$mouseInput, &$cameraYaw, &$cameraPitch)
{
    // only look around if the left mouse button is pressed
    if (glfwGetMouseButton($window, GLFW_MOUSE_BUTTON_LEFT) !== GLFW_PRESS) {
        glfwSetInputMode($window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        $mouseInput['firstMouse'] = true;
        return;
    }

    glfwSetInputMode($window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if ($mouseInput['firstMouse']) {
        $mouseInput['lastX'] = $xpos;
        $mouseInput['lastY'] = $ypos;
        $mouseInput['firstMouse'] = false;
        return;
    }

    $xoffset = $xpos - $mouseInput['lastX'];
    $yoffset = $mouseInput['lastY'] - $ypos;
    $mouseInput['lastX'] = $xpos;
    $mouseInput['lastY'] = $ypos;

    // apply euler rotation, clamping the pitch so we can't flip over
    $sensitivity = 0.15;
    $cameraYaw += $xoffset * $sensitivity;
    $cameraPitch += $yoffset * $sensitivity;
    $cameraPitch = max(-89.0, min(89.0, $cameraPitch));
});


/**
 * Render the scene
 *
 * ----------------------------------------------------------------------------
 */

// print some help to the console
echo str_repeat('-', 80) . PHP_EOL;
echo "DrawCallAssembler with Payload demo" . PHP_EOL;
echo "  * Hold LMB: look around" . PHP_EOL;
echo "  * WASD: move horizontally" . PHP_EOL;
echo "  * Q/E: move up or down" . PHP_EOL;
echo "  * SHIFT: temporary speed boost" . PHP_EOL;
echo "  * SPACE: pause rotation" . PHP_EOL;
echo "  * F: toggle wireframe" . PHP_EOL;
echo "  * R: rebuild random scene with new colors" . PHP_EOL;
echo "  * ESC: close the window" . PHP_EOL;
echo str_repeat('-', 80) . PHP_EOL;

$lastTime = glfwGetTime();
$frameCounter = 0;
$buildCpuTimes = [];
$frameTimes = [];

// use bindTransformBuffer to set up instance transform attributes automatically.
// the transform matrix uses locations 2-5, so the payload starts at location 6.
$nextLocation = $assembler->bindTransformBuffer($vao, 2);
$nextLocation = $assembler->bindTransformBuffer($lodVao, 2);

// bind the payload buffer to set up the color attribute.
// this uses location 6 for the RGB color (3 floats).
$assembler->bindPayloadBuffer($vao, 6);
$assembler->bindPayloadBuffer($lodVao, 6);

// submit the field to the assembler once, it stays valid until we rebuild it
build_instances_with_payload($assembler, $instances, glfwGetTime(), $animate);

// Main Loop
// ----------------------------------------------------------------------------
while (!glfwWindowShouldClose($window))
{
    $frameStartTime = microtime(true);
    $time = glfwGetTime();
    $deltaTime = $time - $lastTime;
    $lastTime = $time;

    // build a camera basis from the yaw / pitch angles. front points where we
    // are looking, right and up are derived from it.
    $cameraFront = Vec3::normalized(new Vec3(
        cos(GLM::radians($cameraYaw)) * cos(GLM::radians($cameraPitch)),
        sin(GLM::radians($cameraPitch)),
        sin(GLM::radians($cameraYaw)) * cos(GLM::radians($cameraPitch))
    ));
    $cameraRight = Vec3::normalized(Vec3::cross($cameraFront, new Vec3(0.0, 1.0, 0.0)));
    $cameraUp = Vec3::normalized(Vec3::cross($cameraRight, $cameraFront));

    // move the camera with W,A,S,D on the ground plane and Q,E up / down.
    // holding shift gives a temporary speed boost.
    $speed = 35.0;
    if (glfwGetKey($window, GLFW_KEY_LEFT_SHIFT) === GLFW_PRESS || glfwGetKey($window, GLFW_KEY_RIGHT_SHIFT) === GLFW_PRESS) {
        $speed *= 2.2;
    }
    $velocity = $speed * $deltaTime;

    // flatten front and right onto the ground plane so movement stays level
    // no matter where we are looking
    $frontLen = sqrt(($cameraFront->x * $cameraFront->x) + ($cameraFront->z * $cameraFront->z));
    $forward = $frontLen > 0.0001 ? new Vec3($cameraFront->x / $frontLen, 0.0, $cameraFront->z / $frontLen) : new Vec3(0.0, 0.0, 0.0);
    $rightLen = sqrt(($cameraRight->x * $cameraRight->x) + ($cameraRight->z * $cameraRight->z));
    $right = $rightLen > 0.0001 ? new Vec3($cameraRight->x / $rightLen, 0.0, $cameraRight->z / $rightLen) : new Vec3(0.0, 0.0, 0.0);

    if (glfwGetKey($window, GLFW_KEY_W) === GLFW_PRESS) {
        $cameraPos = new Vec3($cameraPos->x + $forward->x * $velocity, $cameraPos->y + $forward->y * $velocity, $cameraPos->z + $forward->z * $velocity);
    }
    if (glfwGetKey($window, GLFW_KEY_S) === GLFW_PRESS) {
        $cameraPos = new Vec3($cameraPos->x - $forward->x * $velocity, $cameraPos->y - $forward->y * $velocity, $cameraPos->z - $forward->z * $velocity);
    }
    if (glfwGetKey($window, GLFW_KEY_A) === GLFW_PRESS) {
        $cameraPos = new Vec3($cameraPos->x - $right->x * $velocity, $cameraPos->y - $right->y * $velocity, $cameraPos->z - $right->z * $velocity);
    }
    if (glfwGetKey($window, GLFW_KEY_D) === GLFW_PRESS) {
        $cameraPos = new Vec3($cameraPos->x + $right->x * $velocity, $cameraPos->y + $right->y * $velocity, $cameraPos->z + $right->z * $velocity);
    }
    if (glfwGetKey($window, GLFW_KEY_E) === GLFW_PRESS) {
        $cameraPos = new Vec3($cameraPos->x, $cameraPos->y + $velocity, $cameraPos->z);
    }
    if (glfwGetKey($window, GLFW_KEY_Q) === GLFW_PRESS) {
        $cameraPos = new Vec3($cameraPos->x, $cameraPos->y - $velocity, $cameraPos->z);
    }

    // build the view and projection matrices from the camera
    $view = new Mat4;
    $viewTarget = new Vec3(
        $cameraPos->x + $cameraFront->x,
        $cameraPos->y + $cameraFront->y,
        $cameraPos->z + $cameraFront->z
    );
    $view->lookAt($cameraPos, $viewTarget, $cameraUp);

    $projection = new Mat4;
    $projection->perspective(GLM::radians(60.0), ExampleHelper::WIN_WIDTH / ExampleHelper::WIN_HEIGHT, 0.1, 64000.0);

    // only update camera data when space is not held, so we can freeze the
    // culling frustum in place and fly out of it to see the effect
    if (glfwGetKey($window, GLFW_KEY_SPACE) !== GLFW_PRESS) {
        $assembler->setCameraData($cameraPos, $view, $projection);
    }

    // use some dark space color to clear the screen
    glClearColor(0.03, 0.03, 0.05, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // now set the per-frame uniforms in the shader
    glUseProgram($shader);
    glUniformMatrix4f($uniforms['view'], GL_FALSE, $view);
    glUniformMatrix4f($uniforms['projection'], GL_FALSE, $projection);
    glUniform3f($uniforms['camera_pos'], $cameraPos->x, $cameraPos->y, $cameraPos->z);

    // let the assembler cull, sort and batch, then hand us one call per batch.
    // no need to set material colors anymore, the color rides along as payload.
    $buildStartTime = microtime(true);
    $commandCount = $assembler->execute(function(int $meshHandle, int $materialId, int $instanceOffset, int $instanceCount, int $flags) use ($meshRegistry, $wireframe)
    {
        // bind the appropriate mesh VAO
        $mesh = $meshRegistry[$meshHandle];
        glBindVertexArray($mesh['vao']);

        // apply wireframe mode if requested
        if ($wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }
    });
    $buildEndTime = microtime(true);
    $buildCpuTime = ($buildEndTime - $buildStartTime) * 1000; // in milliseconds
    $buildCpuTimes[] = $buildCpuTime;

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(0);

    // swap the windows framebuffer and poll queued window events
    glfwSwapBuffers($window);
    glfwPollEvents();

    $frameEndTime = microtime(true);
    $frameTime = ($frameEndTime - $frameStartTime) * 1000; // in milliseconds
    $frameTimes[] = $frameTime;

    // every 60 frames print a line of stats so we can watch the cull rate
    $frameCounter++;
    if ($frameCounter % 60 === 0)
    {
        $submittedInstances = $assembler->instanceCount();
        $builtInstances = $assembler->builtInstanceCount();
        $finalCommands = $commandCount;
        $avgBuildTime = count($buildCpuTimes) > 0 ? array_sum($buildCpuTimes) / count($buildCpuTimes) : 0.0;
        $avgFrameTime = count($frameTimes) > 0 ? array_sum($frameTimes) / count($frameTimes) : 0.0;
        $cullPercent = $submittedInstances > 0 ? (100.0 * ($submittedInstances - $builtInstances) / $submittedInstances) : 0.0;
        printf(
            "[frame %d] submitted %d, visible %d (%.1f%% culled), draw calls: %d, execute time: %.3fms, avg execute: %.3fms, frame: %.3fms, avg frame: %.3fms (%.1f FPS)" . PHP_EOL,
            $frameCounter,
            $submittedInstances,
            $builtInstances,
            $cullPercent,
            $finalCommands,
            $buildCpuTime,
            $avgBuildTime,
            $frameTime,
            $avgFrameTime,
            1000.0 / $avgFrameTime
        );
    }
}


/**
 * Cleanup
 *
 * ----------------------------------------------------------------------------
 */
glDeleteBuffers(1, $vbo);
glDeleteBuffers(1, $lodVbo);
glDeleteVertexArrays(1, $vao);
glDeleteVertexArrays(1, $lodVao);

ExampleHelper::stop($window);


/**
 * helper functions
 *
 * ----------------------------------------------------------------------------
 */

// walks the instance list and submits one instance per entry to the assembler,
// building its transform matrix on the way. called both at startup and whenever
// the scene is rebuilt with the R key.
function build_instances_with_payload(DrawCallAssembler $assembler, array $instances, float $time, bool $animate) : void
{
    $assembler->clearInstances();

    foreach ($instances as $index => $instance)
    {
        $transform = new Mat4;

        // bob the instance up and down over time
        $bob = sin($time * $instance['bob_speed'] + $index) * $instance['bob_strength'];
        $transform->translate(new Vec3(
            $instance['position'][0],
            $instance['position'][1] + $bob,
            $instance['position'][2]
        ));

        // spin it around its own axis, unless animation is paused
        if ($animate && abs($instance['rotation_speed']) > 0.0) {
            $transform->rotate(
                $time * $instance['rotation_speed'],
                new Vec3($instance['axis'][0], $instance['axis'][1], $instance['axis'][2])
            );
        }

        $transform->scale(new Vec3(
            $instance['scale'],
            $instance['scale'],
            $instance['scale']
        ));

        $assembler->submit(
            meshHandle: $instance['mesh'],
            transform: $transform,
            materialId: 0, // not used, the color comes from the payload instead
            flags: 0,
            sortBias: 0.0,
            userId: $index
        );
    }
}

// generates the asteroid field and fills the payload buffer with one RGB color
// per instance, so each instance can be drawn in its own color
function generate_asteroid_field_with_colors(int $meshHandle, int $count, FloatBuffer $payloadBuffer) : array
{
    $instances = [];

    for ($i = 0; $i < $count; $i++)
    {
        $radius = random_float(20.0, $count);
        $angle = random_float(0.0, 2 * M_PI);
        $height = random_float(-8.0, 25.0);
        $scale = random_float(0.4, 2.5);

        $axis = Vec3::normalized(new Vec3(
            random_float(-1.0, 1.0),
            random_float(-1.0, 1.0),
            random_float(-1.0, 1.0)
        ));

        // pick a random color for this instance
        $color = [
            random_float(0.2, 1.0), // red
            random_float(0.2, 1.0), // green
            random_float(0.2, 1.0), // blue
        ];

        // add the color to the payload buffer, in the same order we submit
        // the instances so the assembler can line them up
        $payloadBuffer->pushArray($color);

        $instances[] = [
            'mesh' => $meshHandle,
            'position' => [
                cos($angle) * $radius,
                $height,
                sin($angle) * $radius,
            ],
            'scale' => $scale,
            'axis' => [$axis->x, $axis->y, $axis->z],
            'rotation_speed' => random_float(-0.9, 1.1),
            'bob_speed' => random_float(0.5, 2.2),
            'bob_strength' => random_float(0.0, 1.5),
            'color' => $color,
        ];
    }

    return $instances;
}

// returns a random float in the given range
function random_float(float $min, float $max) : float
{
    return $min + ($max - $min) * (mt_rand() / mt_getrandmax());
}
