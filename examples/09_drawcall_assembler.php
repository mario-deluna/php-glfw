<?php
/**
 * This example shows off the DrawCallAssembler.
 *
 * We build a massive asteroid field of millions of instances and let the
 * assembler do the heavy lifting: frustum culling, LOD selection and batching
 * the survivors into as few draw calls as possible. Because the scene is static
 * and only the camera moves, this is a great place to compare the different
 * culling strategies against each other.
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
const INSTANCE_COUNT = 10_000_000;

// distance at which a ship is swapped for its cheap LOD cube
const LOD_SWITCH_DISTANCE = 1000.0;

// packed instance parameter layout (floats per instance)
const INSTANCE_PARAM_STRIDE = 11;
// [0..2] position xyz, [3] scale, [4..6] rotation axis xyz,
// [7] rotation speed, [8] bob speed, [9] bob strength, [10] material id (as float)


$window = ExampleHelper::begin();


/**
 * Setup window & GL state
 *
 * ----------------------------------------------------------------------------
 */
glfwSetWindowTitle($window, 'PHP-GLFW DrawCallAssembler');
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
// the per-instance model matrix arrives as a vertex attribute (location 2),
// so every instance can share the same shader program and draw call
$shader = ExampleHelper::compileShader(<<<'GLSL'
#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;

layout (location = 2) in mat4 i_transform;

out vec3 v_normal;
out vec3 v_world_pos;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	mat4 model = i_transform;
	mat3 normal_matrix = mat3(transpose(inverse(model)));
	vec4 world_pos = model * vec4(a_position, 1.0);

	v_normal = normalize(normal_matrix * a_normal);
	v_world_pos = world_pos.xyz;

	gl_Position = projection * view * world_pos;
}
GLSL,
<<<'GLSL'
#version 330 core
in vec3 v_normal;
in vec3 v_world_pos;

out vec4 fragment_color;

uniform vec3 light_dir;
uniform vec3 light_color;
uniform vec3 camera_pos;
uniform vec3 material_color;
uniform float ambient_strength = 0.12;

void main()
{
	vec3 normal = normalize(v_normal);
	vec3 lit_dir = normalize(light_dir);
	vec3 view_dir = normalize(camera_pos - v_world_pos);

	float diffuse = max(dot(normal, lit_dir), 0.0);
	float specular = pow(max(dot(normal, normalize(lit_dir + view_dir)), 0.0), 32.0) * 0.2;

	vec3 color = material_color * (ambient_strength + diffuse) * light_color + specular;
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
// build a palette of random material colors, one is picked per instance
$materialPalette = [];
for ($i = 0; $i < 50; $i++) {
    $materialPalette[] = [
        mt_rand(20, 100) / 100.0,
        mt_rand(20, 100) / 100.0,
        mt_rand(20, 100) / 100.0,
    ];
}

// generate the packed per-instance parameters for the whole field
$instanceParams = generate_asteroid_field(count($materialPalette), INSTANCE_COUNT);
$wireframe = false;
$animate = true;


/**
 * Culling strategy
 *
 * ----------------------------------------------------------------------------
 */
// the asteroid field is static (instances are submitted once, only the camera
// moves), so the octree strategy is a great fit: the tree is built once and
// reused across frames, and only whole subtrees are tested against the frustum.
// press C to cycle between the culling strategies and compare the cull rate.
//
// this field spans a huge radius but clusters densely near the origin, so the
// octree needs a deep subdivision cap to break that cluster into small leaves
// instead of a few giant ones (which would make per-leaf sphere tests dominate).
// a smaller leaf size trims the per-leaf work further at the cost of a bigger,
// slower-to-build tree. tune these two numbers to your scene.
$cullingStrategy = DrawCallAssembler::CULL_OCTREE;
$assembler->setCullingStrategy($cullingStrategy, octreeMaxDepth: 31, octreeMinLeafInstances: 16);

// get uniform locations here so we don't have to do it every frame
$uniforms = [
    'view' => glGetUniformLocation($shader, 'view'),
    'projection' => glGetUniformLocation($shader, 'projection'),
    'camera_pos' => glGetUniformLocation($shader, 'camera_pos'),
    'light_dir' => glGetUniformLocation($shader, 'light_dir'),
    'light_color' => glGetUniformLocation($shader, 'light_color'),
    'ambient' => glGetUniformLocation($shader, 'ambient_strength'),
    'material_color' => glGetUniformLocation($shader, 'material_color'),
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
// capture keyboard events to toggle rendering modes and cycle the culling
glfwSetKeyCallback($window, function ($key, $scancode, $action, $mods) use (&$wireframe, &$animate, &$instanceParams, &$cullingStrategy, $shipHandle, $materialPalette, $window, $assembler)
{
    if ($action !== GLFW_PRESS) {
        return;
    }

    // exit app
    if ($key === GLFW_KEY_ESCAPE) {
        glfwSetWindowShouldClose($window, true);
        return;
    }

    // toggle animation
    if ($key === GLFW_KEY_SPACE) {
        $animate = !$animate;
        return;
    }

    // toggle wireframe mode
    if ($key === GLFW_KEY_F) {
        $wireframe = !$wireframe;
        return;
    }

    // cycle NONE -> LINEAR -> OCTREE -> NONE ...
    if ($key === GLFW_KEY_C) {
        $cullingStrategy = ($cullingStrategy + 1) % 3;
        $assembler->setCullingStrategy($cullingStrategy, octreeMaxDepth: 31, octreeMinLeafInstances: 16);
        printf("culling strategy: %s" . PHP_EOL, culling_strategy_name($cullingStrategy));
        return;
    }

    // rebuild the whole field with fresh random parameters
    if ($key === GLFW_KEY_R) {
        $instanceParams = generate_asteroid_field(count($materialPalette), INSTANCE_COUNT);
        build_instances($assembler, $instanceParams, $shipHandle, glfwGetTime(), $animate);
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
echo "DrawCallAssembler demo" . PHP_EOL;
echo "  * Hold LMB: look around" . PHP_EOL;
echo "  * WASD: move horizontally" . PHP_EOL;
echo "  * Q/E: move up or down" . PHP_EOL;
echo "  * SHIFT: temporary speed boost" . PHP_EOL;
echo "  * SPACE: freeze the culling frustum (stop updating camera data)" . PHP_EOL;
echo "  * F: toggle wireframe" . PHP_EOL;
echo "  * C: cycle culling strategy (none / linear / octree)" . PHP_EOL;
echo "  * R: rebuild random scene" . PHP_EOL;
echo "  * ESC: close the window" . PHP_EOL;
echo "culling strategy: " . culling_strategy_name($cullingStrategy) . PHP_EOL;
echo str_repeat('-', 80) . PHP_EOL;

$lastTime = glfwGetTime();
$frameCounter = 0;
$buildCpuTimes = [];
$frameTimes = [];

// use bindTransformBuffer to set up instance attributes automatically
// (the transform VBO is owned and updated internally by the assembler)
$assembler->bindTransformBuffer($vao, 2);
$assembler->bindTransformBuffer($lodVao, 2);

// submit the field to the assembler once, it stays valid until we rebuild it
build_instances($assembler, $instanceParams, $shipHandle, glfwGetTime(), $animate);

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
    // everything inside the callback runs once per draw command, not per instance.
    $buildStartTime = microtime(true);
    $commandCount = $assembler->execute(function(int $meshHandle, int $materialId, int $instanceOffset, int $instanceCount, int $flags) use ($meshRegistry, $materialPalette, $uniforms, $wireframe)
    {
        // bind the appropriate mesh VAO
        $mesh = $meshRegistry[$meshHandle];
        glBindVertexArray($mesh['vao']);

        // set the material color for this batch
        $color = $materialPalette[$materialId % count($materialPalette)];
        glUniform3f($uniforms['material_color'], $color[0], $color[1], $color[2]);

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
            "[frame %d] %s | submitted %d, visible %d (%.1f%% culled), draw calls: %d, execute time: %.3fms, avg execute: %.3fms, frame: %.3fms, avg frame: %.3fms (%.1f FPS)" . PHP_EOL,
            $frameCounter,
            culling_strategy_name($cullingStrategy),
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

// returns the human readable name of a culling strategy, for the console output
function culling_strategy_name(int $strategy) : string
{
    return match ($strategy) {
        DrawCallAssembler::CULL_NONE => 'none',
        DrawCallAssembler::CULL_LINEAR => 'linear',
        DrawCallAssembler::CULL_OCTREE => 'octree',
        default => 'unknown',
    };
}

// draws a single-line console progress bar, updated in place via a carriage
// return. only meant for the long one-off load phases (generate / submit) at
// large instance counts.
function print_progress(string $label, int $current, int $total) : void
{
    $width = 30;
    $ratio = $total > 0 ? $current / $total : 1.0;
    $filled = (int) round($ratio * $width);
    $bar = str_repeat('#', $filled) . str_repeat('-', $width - $filled);
    printf("\r  %-12s [%s] %5.1f%% (%d/%d)", $label, $bar, $ratio * 100.0, $current, $total);
    if ($current >= $total) {
        echo PHP_EOL;
    }
}

// walks the packed parameter buffer and submits one instance per entry to the
// assembler, building its transform matrix on the way. called both at startup
// and whenever the scene is rebuilt with the R key.
function build_instances(DrawCallAssembler $assembler, FloatBuffer $params, int $meshHandle, float $time, bool $animate) : void
{
    $assembler->clearInstances();

    $count = intdiv($params->size(), INSTANCE_PARAM_STRIDE);
    $progressStep = max(1, intdiv($count, 100));
    for ($index = 0; $index < $count; $index++)
    {
        $b = $index * INSTANCE_PARAM_STRIDE;

        if ($index % $progressStep === 0) {
            print_progress('submitting', $index, $count);
        }

        $transform = new Mat4;

        // bob the instance up and down over time
        $bob = sin($time * $params[$b + 8] + $index) * $params[$b + 9];
        $transform->translate(new Vec3(
            $params[$b + 0],
            $params[$b + 1] + $bob,
            $params[$b + 2]
        ));

        // spin it around its own axis, unless animation is paused
        $rotationSpeed = $params[$b + 7];
        if ($animate && abs($rotationSpeed) > 0.0) {
            $transform->rotate(
                $time * $rotationSpeed,
                new Vec3($params[$b + 4], $params[$b + 5], $params[$b + 6])
            );
        }

        $scale = $params[$b + 3];
        $transform->scale(new Vec3($scale, $scale, $scale));

        $assembler->submit(
            meshHandle: $meshHandle,
            transform: $transform,
            materialId: (int) $params[$b + 10],
            flags: 0,
            sortBias: 0.0,
            userId: $index
        );
    }

    print_progress('submitting', $count, $count);
}

// generates the whole asteroid field into a packed native buffer.
//
// we pack the per-instance generation parameters into a native buffer instead
// of a PHP array. at millions of instances a PHP array of nested arrays costs
// gigabytes of heap, while this packed buffer is INSTANCE_PARAM_STRIDE floats
// per instance (see the layout comment near the top of the file).
function generate_asteroid_field(int $materialCount, int $count) : FloatBuffer
{
    $buffer = new FloatBuffer();
    $buffer->reserve($count * INSTANCE_PARAM_STRIDE);

    $progressStep = max(1, intdiv($count, 100));
    for ($i = 0; $i < $count; $i++)
    {
        if ($i % $progressStep === 0) {
            print_progress('generating', $i, $count);
        }

        $radius = random_float(20.0, INSTANCE_COUNT);
        $angle = random_float(0.0, 2 * M_PI);
        $height = random_float(-8.0, 25.0);
        $scale = random_float(0.4, 2.5);

        $axis = Vec3::normalized(new Vec3(
            random_float(-1.0, 1.0),
            random_float(-1.0, 1.0),
            random_float(-1.0, 1.0)
        ));

        $buffer->push(cos($angle) * $radius);
        $buffer->push($height);
        $buffer->push(sin($angle) * $radius);
        $buffer->push($scale);
        $buffer->push($axis->x);
        $buffer->push($axis->y);
        $buffer->push($axis->z);
        $buffer->push(random_float(-0.9, 1.1));
        $buffer->push(random_float(0.5, 2.2));
        $buffer->push(random_float(0.0, 1.5));
        $buffer->push((float) random_int(0, max(0, $materialCount - 1)));
    }

    print_progress('generating', $count, $count);

    return $buffer;
}

// returns a random float in the given range
function random_float(float $min, float $max) : float
{
    return $min + ($max - $min) * (mt_rand() / mt_getrandmax());
}
