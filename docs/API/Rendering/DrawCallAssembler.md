# DrawCallAssembler

The Draw Call Assembler helps you generate efficient draw call batches for your meshes. You submit per-object draw requests (a mesh handle, a transform, a material, a pass) and the assembler does the heavy lifting in native C: it frustum-culls, selects a level of detail, sorts to minimize state changes, and collapses identical objects into instanced batches. It can then issue the draws for you, or hand back GPU-ready buffers so you can draw them yourself.

```php
namespace GL\Rendering
{
    class DrawCallAssembler {}
}
```

For a guided, example-first introduction, see the [Draw Call Assembler user guide](../../user-guide/rendering/draw-call-assembler.md). This page is the flat API reference.

## Usage

### Registering meshes and submitting instances

```php
use GL\Rendering\DrawCallAssembler;
use GL\Math\{Mat4, Vec3};

$assembler = new DrawCallAssembler();

$shipHandle = $assembler->registerMesh(
    vao: $vao,
    vertexCount: $vertexCount,
    aabbMin: $aabbMin,
    aabbMax: $aabbMax,
);

$assembler->bindTransformBuffer($vao, 2);

// each frame
$assembler->clearInstances();
$assembler->submit($shipHandle, $transform, materialId: 0);
```

### Drawing the scene

Let the assembler issue the draws, running your callback before each one:

```php
$assembler->execute(function (int $meshHandle, int $materialId, int $instanceOffset, int $instanceCount, int $flags) {
    // the VAO is already bound; set uniforms, bind textures, etc.
});
```

Or build the packed buffers and drive the draws yourself:

```php
$commandCount = $assembler->build();
$commands = $assembler->commandBuffer; // read with $commands[$i]
```

## Constants

### Sort modes

Passed to [`setSortMode`](#setsortmode).

```php
public const SORT_NONE = 0;          // keep submission order
public const SORT_FRONT_TO_BACK = 1; // nearest first (opaque default)
public const SORT_BACK_TO_FRONT = 2; // farthest first
```

### Render passes

Passed as the `$pass` argument to [`submit`](#submit).

```php
public const PASS_OPAQUE = 0;
public const PASS_TRANSPARENT = 1; // sorted back-to-front automatically
public const PASS_DEPTH = 2;
public const PASS_USER = 3;
```

### Instance flags

Combined as a bitmask in the `$flags` argument to [`submit`](#submit).

```php
public const FLAG_IGNORE_CULLING = 2;     // draw even if outside the frustum
public const FLAG_DISABLE_INSTANCING = 4; // keep as its own draw call
public const FLAG_CUSTOM_SORT_KEY = 8;    // use a custom sort key
```

### Culling strategies

Passed to [`setCullingStrategy`](#setcullingstrategy).

```php
public const CULL_NONE = 0;   // never cull, draw every instance
public const CULL_LINEAR = 1; // per-instance frustum test each frame (default)
public const CULL_OCTREE = 2; // persistent octree, rebuilt only when instances change
```

## Properties

The buffers are filled after a call to [`build`](#build) (and after [`execute`](#execute), which builds internally). They contain only the instances that survived culling, in final draw order.

### $commandBuffer

Packed draw commands, `commandStride` (8) `uint32` values each: `[mesh handle, vao id, index offset, draw count, base vertex, instance offset, instance count, material id]`.

```php
public readonly \GL\Buffer\UIntBuffer $commandBuffer;
```

### $instanceTransformBuffer

One `Mat4` per visible instance, `transformStride` (16) floats each.

```php
public readonly \GL\Buffer\FloatBuffer $instanceTransformBuffer;
```

### $instanceMetaBuffer

Per-instance metadata, `instanceMetaStride` (4) `uint32` values each: `[mesh handle, material id, user id, flags]`.

```php
public readonly \GL\Buffer\UIntBuffer $instanceMetaBuffer;
```

### $instancePayloadBuffer

Optional per-instance float payload (colors, skinning weights, and the like), in sorted order. See [`bindPayloadData`](#bindpayloaddata).

```php
public readonly \GL\Buffer\FloatBuffer $instancePayloadBuffer;
```

### $commandStride

The command buffer stride, in `uint32` components, of one draw command entry (8).

```php
public readonly int $commandStride;
```

### $transformStride

The transform buffer stride, in float components, of one transform entry (16).

```php
public readonly int $transformStride;
```

### $instanceMetaStride

The metadata buffer stride, in `uint32` components, of one metadata entry (4).

```php
public readonly int $instanceMetaStride;
```

## Methods

### `__construct`

Creates a new assembler instance with preallocated capacities.

```php
function __construct(int $initialMeshCapacity = 256, int $initialInstanceCapacity = 2048, int $initialCommandCapacity = 512)
```

arguments

:    1. `int` `$initialMeshCapacity` Number of mesh slots preallocated in the registry.
    2. `int` `$initialInstanceCapacity` Number of instance slots backed by the buffers.
    3. `int` `$initialCommandCapacity` Number of draw command slots.

---

### `registerMesh`

Registers a mesh in the assembler's registry and returns a numeric handle you use to submit instances of it later. You remain the owner of any passed references; the assembler will not modify or delete them.

```php
function registerMesh(int $vao, int $vertexOffset = 0, int $vertexCount = 0, int $indexOffset = 0, int $indexCount = 0, ?\GL\Math\Vec3 $aabbMin = null, ?\GL\Math\Vec3 $aabbMax = null, int $materialHint = 0, int $primitive = 0x0004) : int
```

arguments

:    1. `int` `$vao` OpenGL vertex array object handle that encapsulates buffers and layout.
    2. `int` `$vertexOffset` Starting vertex inside the bound VBO (0 based).
    3. `int` `$vertexCount` Number of vertices to draw when the mesh is rendered without indices.
    4. `int` `$indexOffset` Starting index inside the EBO (set to 0 to draw arrays instead).
    5. `int` `$indexCount` Number of indices used for indexed rendering (0 falls back to `$vertexCount` arrays).
    6. `\GL\Math\Vec3|null` `$aabbMin` Optional minimum point of the mesh bounds (used for frustum culling).
    7. `\GL\Math\Vec3|null` `$aabbMax` Optional maximum point of the mesh bounds.
    8. `int` `$materialHint` Optional default material id applied when `submit()` omits a material.
    9. `int` `$primitive` GL primitive value (defaults to `GL_TRIANGLES` = 0x0004).

returns

:    `int` Numeric handle for the registered mesh.

---

### `setMeshMaterial`

Updates or overrides the default material identifier attached to a mesh.

```php
function setMeshMaterial(int $meshHandle, int $materialId) : void
```

arguments

:    1. `int` `$meshHandle` Mesh handle returned by [`registerMesh`](#registermesh).
    2. `int` `$materialId` The new default material id.

---

### `setLodTable`

Attaches level-of-detail alternatives to a mesh. When you submit the base mesh, the assembler substitutes a cheaper mesh past each distance threshold.

```php
function setLodTable(int $meshHandle, \GL\Buffer\FloatBuffer $distanceThresholds, \GL\Buffer\UIntBuffer $meshHandles) : void
```

arguments

:    1. `int` `$meshHandle` Base mesh handle (the one to be replaced) returned by [`registerMesh`](#registermesh).
    2. `\GL\Buffer\FloatBuffer` `$distanceThresholds` Distances in ascending order.
    3. `\GL\Buffer\UIntBuffer` `$meshHandles` Mesh handle for each LOD level.

---

### `setAutoInstancing`

Enables or disables automatic instancing for meshes submitted multiple times per frame. Enabled by default.

```php
function setAutoInstancing(bool $enabled) : void
```

arguments

:    1. `bool` `$enabled` Whether to collapse compatible instances into batched draws.

---

### `setSortMode`

Selects the ordering applied to opaque draw calls.

```php
function setSortMode(int $mode) : void
```

arguments

:    1. `int` `$mode` One of the `SORT_*` constants.

---

### `setCullingStrategy`

Selects the culling strategy used during [`build`](#build) / [`execute`](#execute). The two optional arguments tune the octree and are ignored by the other strategies; they only take effect when `>= 0`, and passing `-1` leaves the current value untouched. Changing either rebuilds the tree.

```php
function setCullingStrategy(int $strategy, int $octreeMaxDepth = -1, int $octreeMinLeafInstances = -1) : void
```

arguments

:    1. `int` `$strategy` One of the `CULL_*` constants.
    2. `int` `$octreeMaxDepth` Maximum octree subdivision depth. Increase for scenes with a large spatial extent and uneven density.
    3. `int` `$octreeMinLeafInstances` A node stops subdividing once it holds this many instances or fewer.

---

### `setCameraData`

Updates the camera state used for sorting, frustum culling, and LOD evaluation. The position drives LOD selection, while the view and projection matrices drive both sorting and frustum generation.

```php
function setCameraData(?\GL\Math\Vec3 $cameraPosition = null, ?\GL\Math\Mat4 $viewMatrix = null, ?\GL\Math\Mat4 $projectionMatrix = null) : void
```

arguments

:    1. `\GL\Math\Vec3|null` `$cameraPosition` Camera position used for LOD selection.
    2. `\GL\Math\Mat4|null` `$viewMatrix` View matrix used for frustum generation.
    3. `\GL\Math\Mat4|null` `$projectionMatrix` Projection matrix used for frustum generation.

---

### `setFrustumPlanes`

Manually configures the six frustum planes used for culling. Each plane is a [`Vec4`](../../API/Math/Vec4.md) holding the plane equation `ax + by + cz + d = 0`.

```php
function setFrustumPlanes(\GL\Math\Vec4 $left, \GL\Math\Vec4 $right, \GL\Math\Vec4 $bottom, \GL\Math\Vec4 $top, \GL\Math\Vec4 $near, \GL\Math\Vec4 $far) : void
```

arguments

:    1. `\GL\Math\Vec4` `$left` Left plane.
    2. `\GL\Math\Vec4` `$right` Right plane.
    3. `\GL\Math\Vec4` `$bottom` Bottom plane.
    4. `\GL\Math\Vec4` `$top` Top plane.
    5. `\GL\Math\Vec4` `$near` Near plane.
    6. `\GL\Math\Vec4` `$far` Far plane.

---

### `bindTransformBuffer`

Binds and sets up the instance transform buffer on a VAO for instanced rendering. It creates or reuses an internal VBO, sets up the four vec4 attribute locations the transform matrix occupies, and returns the next free attribute location. Must be called before [`execute`](#execute).

```php
function bindTransformBuffer(int $vao, int $offset = 1) : int
```

arguments

:    1. `int` `$vao` The vertex array object to configure.
    2. `int` `$offset` The starting vertex attribute location. For example, `2` puts the matrix at locations 2, 3, 4, 5.

returns

:    `int` The next available attribute location after the transform matrix.

---

### `bindPayloadData`

Registers a `FloatBuffer` of custom per-instance data (colors, skinning weights, and the like) and how many floats make up each instance's payload. The data becomes available in [`$instancePayloadBuffer`](#instancepayloadbuffer) after [`build`](#build). Remember to also call [`bindPayloadBuffer`](#bindpayloadbuffer) to set up the attributes.

```php
function bindPayloadData(\GL\Buffer\FloatBuffer $payloadBuffer, int $stride) : void
```

arguments

:    1. `\GL\Buffer\FloatBuffer` `$payloadBuffer` Buffer containing per-instance payload data.
    2. `int` `$stride` Number of floats per instance in the payload buffer.

---

### `bindPayloadBuffer`

Sets up the vertex attribute pointers for the payload data on a VAO. Must be called after [`bindPayloadData`](#bindpayloaddata).

```php
function bindPayloadBuffer(int $vao, int $offset, int $stride = 0) : int
```

arguments

:    1. `int` `$vao` The vertex array object to configure.
    2. `int` `$offset` The starting vertex attribute location.
    3. `int` `$stride` Number of floats per payload entry (0 uses the stride bound via [`bindPayloadData`](#bindpayloaddata)).

returns

:    `int` The next available attribute location after the payload attributes.

---

### `clearInstances`

Removes all recorded instances without touching the registered meshes. Call this at the top of each frame before submitting.

```php
function clearInstances() : void
```

---

### `submit`

Records a single mesh instance for the current frame.

```php
function submit(int $meshHandle, \GL\Math\Mat4 $transform, int $materialId, int $pass = 0, int $programId = 0, int $flags = 0, float $sortBias = 0.0, int $userId = 0) : void
```

arguments

:    1. `int` `$meshHandle` Mesh handle from [`registerMesh`](#registermesh).
    2. `\GL\Math\Mat4` `$transform` World transform.
    3. `int` `$materialId` Material identifier.
    4. `int` `$pass` Render pass identifier (one of the `PASS_*` constants).
    5. `int` `$programId` Optional program/shader identifier used for batching and sorting.
    6. `int` `$flags` Optional state overrides (`FLAG_*` bitmask).
    7. `float` `$sortBias` Extra distance bias applied when sorting draws.
    8. `int` `$userId` Optional user-supplied id mirrored into the metadata buffer.

---

### `build`

Builds the final draw list, filling [`$commandBuffer`](#commandbuffer), [`$instanceTransformBuffer`](#instancetransformbuffer), [`$instanceMetaBuffer`](#instancemetabuffer), and [`$instancePayloadBuffer`](#instancepayloadbuffer). Use this to handle and execute the draw calls manually; otherwise use [`execute`](#execute).

```php
function build() : int
```

returns

:    `int` The number of draw commands generated for this frame.

---

### `execute`

Builds the draw list and issues the OpenGL draw calls. The callback runs before each draw so you can set up materials and other GL state; the VAO is bound and the draw issued by the assembler internally. You must call [`bindTransformBuffer`](#bindtransformbuffer) before using this method.

```php
function execute(callable $drawCallback) : int
```

The callback receives `(int $meshHandle, int $materialId, int $instanceOffset, int $instanceCount, int $flags)`.

arguments

:    1. `callable` `$drawCallback` A "before draw" callback invoked once per draw command.

returns

:    `int` The number of draw commands executed.

---

### `commandCount`

Returns the number of draw commands generated by the previous [`build`](#build) call.

```php
function commandCount() : int
```

---

### `instanceCount`

Returns the number of instances submitted so far for the current frame.

```php
function instanceCount() : int
```

---

### `builtInstanceCount`

Returns the number of instances that survived culling in the last [`build`](#build) call.

```php
function builtInstanceCount() : int
```

---

### `clearMeshes`

Completely removes all registered meshes and releases their buffers.

```php
function clearMeshes() : void
```

---

### `reset`

Resets both the mesh registry and the current frame state.

```php
function reset() : void
```
