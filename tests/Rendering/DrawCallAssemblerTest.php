<?php

namespace GL\Tests\Rendering;

use GL\Buffer\FloatBuffer;
use GL\Buffer\UIntBuffer;
use GL\Math\GLM;
use GL\Math\Mat4;
use GL\Math\Vec3;
use GL\Math\Vec4;
use GL\Rendering\DrawCallAssembler;
use PHPUnit\Framework\TestCase;

class DrawCallAssemblerTest extends TestCase
{
    public function testBuildBatchesInstancesAndStoresMetaData()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $meshHandle = $assembler->registerMesh(1, 0, 3, 0, 0);

        $firstTransform = new Mat4();
        $firstTransform->translate(new Vec3(1.0, 2.0, 3.0));
        $secondTransform = new Mat4();
        $secondTransform->translate(new Vec3(4.0, 5.0, 6.0));

        $assembler->submit($meshHandle, $firstTransform, 11, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 101);
        $assembler->submit($meshHandle, $secondTransform, 11, DrawCallAssembler::PASS_OPAQUE, 0, 0, 1.0, 202);

        $commandCount = $assembler->build();

        $this->assertSame(1, $commandCount);
        $this->assertSame(1, $assembler->commandCount());
        $this->assertSame(2, $assembler->builtInstanceCount());

        $commandBuffer = $assembler->commandBuffer;
        $this->assertSame($assembler->commandStride, $commandBuffer->size());
        $this->assertSame($meshHandle, $commandBuffer[0]);
        $this->assertSame(1, $commandBuffer[1]);
        $this->assertSame(0, $commandBuffer[2]);
        $this->assertSame(3, $commandBuffer[3]);
        $this->assertSame(0, $commandBuffer[4]);
        $this->assertSame(0, $commandBuffer[5]);
        $this->assertSame(2, $commandBuffer[6]);
        $this->assertSame(11, $commandBuffer[7]);

        $metaBuffer = $assembler->instanceMetaBuffer;
        $this->assertSame(2 * $assembler->instanceMetaStride, $metaBuffer->size());
        $expectedMeta = [
            $meshHandle, 11, 101, 0,
            $meshHandle, 11, 202, 0,
        ];

        for ($i = 0; $i < count($expectedMeta); $i++) {
            $this->assertSame($expectedMeta[$i], $metaBuffer[$i]);
        }

        $transformBuffer = $assembler->instanceTransformBuffer;
        $this->assertSame(2 * $assembler->transformStride, $transformBuffer->size());
    }

    public function testBuildSeparatesCommandsByMaterial()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $meshHandle = $assembler->registerMesh(2, 0, 6, 0, 0);

        $transform = new Mat4();

        $assembler->submit($meshHandle, $transform, 3, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 10);
        $assembler->submit($meshHandle, $transform, 7, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 11);
        $assembler->submit($meshHandle, $transform, 7, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 12);

        $commandCount = $assembler->build();

        $this->assertSame(2, $commandCount);
        $this->assertSame(2, $assembler->commandCount());
        $this->assertSame(3, $assembler->builtInstanceCount());

        $commandBuffer = $assembler->commandBuffer;
        $this->assertSame(2 * $assembler->commandStride, $commandBuffer->size());
        $commandValues = [];
        foreach ($commandBuffer as $value) {
            $commandValues[] = $value;
        }

        $firstCommand = array_slice($commandValues, 0, $assembler->commandStride);
        $secondCommand = array_slice($commandValues, $assembler->commandStride, $assembler->commandStride);

        $this->assertSame([
            $meshHandle, 2, 0, 6, 0, 0, 1, 3,
        ], $firstCommand);

        $this->assertSame([
            $meshHandle, 2, 0, 6, 0, 1, 2, 7,
        ], $secondCommand);

        $metaBuffer = $assembler->instanceMetaBuffer;
        $this->assertSame(3 * $assembler->instanceMetaStride, $metaBuffer->size());
        $expectedMeta = [
            $meshHandle, 3, 10, 0,
            $meshHandle, 7, 11, 0,
            $meshHandle, 7, 12, 0,
        ];

        for ($i = 0; $i < count($expectedMeta); $i++) {
            $this->assertSame($expectedMeta[$i], $metaBuffer[$i]);
        }
    }

    public function testSubmitRejectsNegativeMeshHandle()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $assembler->registerMesh(1, 0, 3, 0, 0);

        $this->expectException(\Error::class);
        $assembler->submit(-1, new Mat4(), 0);
    }

    public function testSubmitRejectsOutOfRangeMeshHandle()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $assembler->registerMesh(1, 0, 3, 0, 0);

        $this->expectException(\Error::class);
        $assembler->submit(5, new Mat4(), 0);
    }

    public function testTransparentPassSortsBackToFront()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $meshHandle = $assembler->registerMesh(1, 0, 3, 0, 0);

        // camera at the origin; distances are derived from the transform translation
        $assembler->setCameraData(new Vec3(0.0, 0.0, 0.0));

        $near = new Mat4();
        $near->translate(new Vec3(0.0, 0.0, 5.0));
        $mid = new Mat4();
        $mid->translate(new Vec3(0.0, 0.0, 10.0));
        $far = new Mat4();
        $far->translate(new Vec3(0.0, 0.0, 20.0));

        // submit near -> mid -> far; back-to-front sorting must reorder them far -> near.
        // user ids track the original submission so we can read back the sorted order.
        $assembler->submit($meshHandle, $near, 0, DrawCallAssembler::PASS_TRANSPARENT, 0, 0, 0.0, 1);
        $assembler->submit($meshHandle, $mid, 0, DrawCallAssembler::PASS_TRANSPARENT, 0, 0, 0.0, 2);
        $assembler->submit($meshHandle, $far, 0, DrawCallAssembler::PASS_TRANSPARENT, 0, 0, 0.0, 3);

        $assembler->build();

        $metaBuffer = $assembler->instanceMetaBuffer;
        $stride = $assembler->instanceMetaStride;

        // user id is stored at offset 2 within each instance's meta record
        $sortedUserIds = [
            $metaBuffer[0 * $stride + 2],
            $metaBuffer[1 * $stride + 2],
            $metaBuffer[2 * $stride + 2],
        ];

        $this->assertSame([3, 2, 1], $sortedUserIds);
    }

    public function testSortModeBackToFrontOverridesOpaqueDefault()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $meshHandle = $assembler->registerMesh(1, 0, 3, 0, 0);
        $assembler->setCameraData(new Vec3(0.0, 0.0, 0.0));

        $near = new Mat4();
        $near->translate(new Vec3(0.0, 0.0, 5.0));
        $far = new Mat4();
        $far->translate(new Vec3(0.0, 0.0, 50.0));

        // opaque instances, user ids track submission order (near=1, far=2)
        $assembler->submit($meshHandle, $near, 0, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 1);
        $assembler->submit($meshHandle, $far, 0, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 2);

        $stride = $assembler->instanceMetaStride;

        // default (SORT_NONE): opaque sorts front-to-back -> near first
        $assembler->build();
        $meta = $assembler->instanceMetaBuffer;
        $this->assertSame([1, 2], [$meta[0 * $stride + 2], $meta[1 * $stride + 2]]);

        // forcing back-to-front must reverse the order -> far first
        $assembler->setSortMode(DrawCallAssembler::SORT_BACK_TO_FRONT);
        $assembler->build();
        $meta = $assembler->instanceMetaBuffer;
        $this->assertSame([2, 1], [$meta[0 * $stride + 2], $meta[1 * $stride + 2]]);
    }

    public function testDisableInstancingProducesSeparateCommands()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $meshHandle = $assembler->registerMesh(1, 0, 3, 0, 0);

        $transform = new Mat4();

        // two identical instances would normally batch into a single command;
        // the DISABLE_INSTANCING flag must keep them as separate draw commands
        $assembler->submit($meshHandle, $transform, 0, DrawCallAssembler::PASS_OPAQUE, 0, DrawCallAssembler::FLAG_DISABLE_INSTANCING, 0.0, 0);
        $assembler->submit($meshHandle, $transform, 0, DrawCallAssembler::PASS_OPAQUE, 0, DrawCallAssembler::FLAG_DISABLE_INSTANCING, 0.0, 0);

        $commandCount = $assembler->build();

        $this->assertSame(2, $commandCount);
        $this->assertSame(2, $assembler->builtInstanceCount());
    }

    public function testFrustumCullingRemovesInstancesOutsidePlanes()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $meshHandle = $assembler->registerMesh(1, 0, 3, 0, 0);

        // five permissive planes (dot is always +1) and one that only keeps z <= 5
        $this->applyCullingFrustum($assembler);

        $near = new Mat4();
        $near->translate(new Vec3(0.0, 0.0, 0.0));
        $far = new Mat4();
        $far->translate(new Vec3(0.0, 0.0, 100.0));

        $assembler->submit($meshHandle, $near, 0, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 1);
        $assembler->submit($meshHandle, $far, 0, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 2);

        $commandCount = $assembler->build();

        $this->assertSame(1, $commandCount);
        $this->assertSame(1, $assembler->builtInstanceCount());

        // only the near instance (user id 1) survived
        $meta = $assembler->instanceMetaBuffer;
        $this->assertSame(1, $meta[2]);
    }

    public function testIgnoreCullingFlagKeepsInstance()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $meshHandle = $assembler->registerMesh(1, 0, 3, 0, 0);

        $this->applyCullingFrustum($assembler);

        $near = new Mat4();
        $near->translate(new Vec3(0.0, 0.0, 0.0));
        $far = new Mat4();
        $far->translate(new Vec3(0.0, 0.0, 100.0));

        // the far instance would be culled, but IGNORE_CULLING keeps it
        $assembler->submit($meshHandle, $near, 0, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 1);
        $assembler->submit($meshHandle, $far, 0, DrawCallAssembler::PASS_OPAQUE, 0, DrawCallAssembler::FLAG_IGNORE_CULLING, 0.0, 2);

        $assembler->build();

        $this->assertSame(2, $assembler->builtInstanceCount());
    }

    public function testLodSelectionPicksMeshByDistance()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $baseMesh = $assembler->registerMesh(10, 0, 3, 0, 0); // handle 0, vao 10
        $lodMesh = $assembler->registerMesh(20, 0, 6, 0, 0);  // handle 1, vao 20

        // switch to the lod mesh once the instance is >= 50 units away
        $assembler->setLodTable($baseMesh, new FloatBuffer([50.0]), new UIntBuffer([$lodMesh]));
        $assembler->setCameraData(new Vec3(0.0, 0.0, 0.0));

        $close = new Mat4();
        $close->translate(new Vec3(0.0, 0.0, 10.0)); // distance 10 -> base mesh
        $distant = new Mat4();
        $distant->translate(new Vec3(0.0, 0.0, 60.0)); // distance 60 -> lod mesh

        $assembler->submit($baseMesh, $close, 0);
        $assembler->submit($baseMesh, $distant, 0);

        $commandCount = $assembler->build();
        $this->assertSame(2, $commandCount);

        // commands are sorted by vao/mesh, so the base mesh (vao 10) comes first
        $command = $assembler->commandBuffer;
        $stride = $assembler->commandStride;

        // first command: base mesh
        $this->assertSame($baseMesh, $command[0 * $stride + 0]);
        $this->assertSame(10, $command[0 * $stride + 1]);
        // second command: lod mesh selected by distance
        $this->assertSame($lodMesh, $command[1 * $stride + 0]);
        $this->assertSame(20, $command[1 * $stride + 1]);
    }

    public function testLodSelectionFallsBackToBaseMeshWithoutLodTable()
    {
        // a mesh that never had setLodTable() called keeps NULL lod tables, so
        // select_lod must fall back to the base handle at any distance. this
        // exercises the guard that returns base_handle when no LODs exist.
        $assembler = new DrawCallAssembler(4, 4, 4);
        $baseMesh = $assembler->registerMesh(10, 0, 3, 0, 0);
        $assembler->setCameraData(new Vec3(0.0, 0.0, 0.0));

        $far = new Mat4();
        $far->translate(new Vec3(0.0, 0.0, 500.0)); // very distant

        $assembler->submit($baseMesh, $far, 0);

        $this->assertSame(1, $assembler->build());

        $command = $assembler->commandBuffer;
        $stride = $assembler->commandStride;

        // no LOD table -> the base mesh (vao 10) is used regardless of distance
        $this->assertSame($baseMesh, $command[0 * $stride + 0]);
        $this->assertSame(10, $command[0 * $stride + 1]);
    }

    public function testLodSelectionFallsBackToBaseMeshWithEmptyLodTable()
    {
        // an empty LOD table (zero-length distance/handle buffers) must also
        // fall back to the base handle, covering the lod_count/handle_count == 0
        // guard in select_lod.
        $assembler = new DrawCallAssembler(4, 4, 4);
        $baseMesh = $assembler->registerMesh(10, 0, 3, 0, 0);
        $assembler->setLodTable($baseMesh, new FloatBuffer([]), new UIntBuffer([]));
        $assembler->setCameraData(new Vec3(0.0, 0.0, 0.0));

        $far = new Mat4();
        $far->translate(new Vec3(0.0, 0.0, 500.0));

        $assembler->submit($baseMesh, $far, 0);

        $this->assertSame(1, $assembler->build());

        $command = $assembler->commandBuffer;
        $stride = $assembler->commandStride;

        $this->assertSame($baseMesh, $command[0 * $stride + 0]);
        $this->assertSame(10, $command[0 * $stride + 1]);
    }

    public function testPayloadDataFollowsSortedOrder()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $meshHandle = $assembler->registerMesh(1, 0, 3, 0, 0);
        $assembler->setCameraData(new Vec3(0.0, 0.0, 0.0));

        // per-instance payload, stride 2, indexed by submission order:
        // instance 0 -> [1, 10], instance 1 -> [2, 20]
        $assembler->bindPayloadData(new FloatBuffer([1.0, 10.0, 2.0, 20.0]), 2);

        $near = new Mat4();
        $near->translate(new Vec3(0.0, 0.0, 5.0));
        $far = new Mat4();
        $far->translate(new Vec3(0.0, 0.0, 50.0));

        // transparent -> back-to-front, so the far instance (payload [2, 20]) comes first
        $assembler->submit($meshHandle, $near, 0, DrawCallAssembler::PASS_TRANSPARENT, 0, 0, 0.0, 1);
        $assembler->submit($meshHandle, $far, 0, DrawCallAssembler::PASS_TRANSPARENT, 0, 0, 0.0, 2);

        $assembler->build();

        $payload = $assembler->instancePayloadBuffer;
        $this->assertSame(4, $payload->size());
        $this->assertSame([2.0, 20.0, 1.0, 10.0], [$payload[0], $payload[1], $payload[2], $payload[3]]);
    }

    public function testClearInstancesResetsState()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $meshHandle = $assembler->registerMesh(1, 0, 3, 0, 0);

        $assembler->submit($meshHandle, new Mat4(), 0);
        $assembler->build();
        $this->assertSame(1, $assembler->instanceCount());

        $assembler->clearInstances();

        $this->assertSame(0, $assembler->instanceCount());
        $this->assertSame(0, $assembler->commandBuffer->size());
        $this->assertSame(0, $assembler->instanceMetaBuffer->size());

        // meshes survive clearInstances, so we can submit again
        $assembler->submit($meshHandle, new Mat4(), 0);
        $this->assertSame(1, $assembler->build());
    }

    public function testConstructorRejectsZeroCapacity()
    {
        $this->expectException(\ValueError::class);
        new DrawCallAssembler(0);
    }

    public function testConstructorRejectsNegativeCapacity()
    {
        $this->expectException(\ValueError::class);
        new DrawCallAssembler(4, -1, 4);
    }

    public function testPositionOnlyCameraUpdateInvalidatesMatrixFrustum()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $meshHandle = $assembler->registerMesh(1, 0, 3, 0, 0);

        // camera at the origin looking down -Z
        $view = new Mat4();
        $view->lookAt(new Vec3(0.0, 0.0, 0.0), new Vec3(0.0, 0.0, -1.0), new Vec3(0.0, 1.0, 0.0));
        $proj = new Mat4();
        $proj->perspective(GLM::radians(60.0), 1.0, 0.1, 50.0);
        $assembler->setCameraData(new Vec3(0.0, 0.0, 0.0), $view, $proj);

        $front = new Mat4();
        $front->translate(new Vec3(0.0, 0.0, -10.0)); // in front of the camera -> visible
        $behind = new Mat4();
        $behind->translate(new Vec3(0.0, 0.0, 10.0)); // behind the camera -> culled

        $assembler->submit($meshHandle, $front, 0, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 1);
        $assembler->submit($meshHandle, $behind, 0, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 2);

        // the matrix-derived frustum culls the instance behind the camera
        $assembler->build();
        $this->assertSame(1, $assembler->builtInstanceCount());

        // a position-only update can no longer derive a frustum; the stale matrix
        // frustum must be invalidated (culling off) rather than frozen, so both
        // instances survive instead of being silently culled against the old pose
        $assembler->setCameraData(new Vec3(0.0, 0.0, 0.0));
        $assembler->build();
        $this->assertSame(2, $assembler->builtInstanceCount());
    }

    public function testPositionOnlyCameraUpdatePreservesManualFrustum()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $meshHandle = $assembler->registerMesh(1, 0, 3, 0, 0);

        // a manually set frustum is not matrix-derived and must survive a
        // subsequent position-only camera update
        $this->applyCullingFrustum($assembler);
        $assembler->setCameraData(new Vec3(0.0, 0.0, 0.0));

        $near = new Mat4();
        $near->translate(new Vec3(0.0, 0.0, 0.0));
        $far = new Mat4();
        $far->translate(new Vec3(0.0, 0.0, 100.0));

        $assembler->submit($meshHandle, $near, 0, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 1);
        $assembler->submit($meshHandle, $far, 0, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, 2);

        $assembler->build();

        // the manual frustum still culls the far instance
        $this->assertSame(1, $assembler->builtInstanceCount());
        $meta = $assembler->instanceMetaBuffer;
        $this->assertSame(1, $meta[2]);
    }

    /**
     * Sets six frustum planes: five that always pass (dot product = +1) and one
     * that only keeps points with z <= 5 (plane -z + 5 >= 0).
     */
    private function applyCullingFrustum(DrawCallAssembler $assembler): void
    {
        $pass = new Vec4(0.0, 0.0, 0.0, 1.0);
        $cullFar = new Vec4(0.0, 0.0, -1.0, 5.0);
        $assembler->setFrustumPlanes($pass, $pass, $pass, $pass, $pass, $cullFar);
    }

    public function testSetLodTableRejectsWrongObjectType()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $meshHandle = $assembler->registerMesh(1, 0, 3, 0, 0);

        $this->expectException(\TypeError::class);
        $assembler->setLodTable($meshHandle, new \stdClass(), new \stdClass());
    }

    public function testRegisterMeshRejectsWrongBoundsObjectType()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);

        $this->expectException(\TypeError::class);
        $assembler->registerMesh(1, 0, 3, 0, 0, new \stdClass(), new \stdClass());
    }

    public function testSetFrustumPlanesRejectsWrongObjectType()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);
        $bad = new \stdClass();

        $this->expectException(\TypeError::class);
        $assembler->setFrustumPlanes($bad, $bad, $bad, $bad, $bad, $bad);
    }

    public function testSetCameraDataRejectsWrongObjectType()
    {
        $assembler = new DrawCallAssembler(4, 4, 4);

        $this->expectException(\TypeError::class);
        $assembler->setCameraData(new \stdClass());
    }
}
