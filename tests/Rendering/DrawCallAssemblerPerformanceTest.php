<?php

namespace GL\Tests\Rendering;

use GL\Buffer\FloatBuffer;
use GL\Buffer\UIntBuffer;
use GL\Math\Mat4;
use GL\Math\Vec3;
use GL\Math\Vec4;
use GL\Rendering\DrawCallAssembler;
use PHPUnit\Framework\TestCase;

/**
 * Performance baseline for the DrawCallAssembler hot path (build()).
 *
 * These are not correctness tests in the strict sense; they drive build() at
 * scale across the assembler's main workloads (sorting, culling, batching,
 * lod + payload) and print a timing report to STDOUT. The printed numbers form
 * the pre-optimization baseline we compare against when tuning the C hot path.
 *
 * Assertions are deliberately loose (result-count sanity + a generous wall-clock
 * ceiling) so the test guards against gross regressions and hangs without being
 * flaky on shared CI runners.
 */
class DrawCallAssemblerPerformanceTest extends TestCase
{
    // instance count used for the linear-cost scenarios; sized so the whole
    // file runs in a few seconds while still being large enough to be measurable
    private const LARGE = 50000;

    // number of timed repetitions per scenario; we keep the median to shed noise
    private const REPS = 5;

    // generous per-scenario wall-clock ceiling (ms); a pathological regression
    // or hang trips this rather than silently passing
    private const MAX_MS = 5000.0;

    private static bool $headerPrinted = false;

    /**
     * deterministic pseudo-random z distance in [1, 1000] driven by an integer
     * sequence so runs are directly comparable (no dependency on a rng seed).
     */
    private static function pseudoZ(int $i): float
    {
        // simple LCG-style mix, kept in 32-bit range
        $h = ($i * 2654435761) & 0xFFFFFFFF;
        $h ^= ($h >> 15);
        return 1.0 + ($h % 1000);
    }

    /**
     * five pass-through planes (dot = +1) and one far plane keeping z <= 5,
     * mirroring the frustum used in DrawCallAssemblerTest.
     */
    private function applyCullingFrustum(DrawCallAssembler $assembler): void
    {
        $pass = new Vec4(0.0, 0.0, 0.0, 1.0);
        $cullFar = new Vec4(0.0, 0.0, -1.0, 5.0);
        $assembler->setFrustumPlanes($pass, $pass, $pass, $pass, $pass, $cullFar);
    }

    /**
     * runs $buildStep once as a warmup, then REPS timed iterations, keeps the
     * median elapsed time, prints a formatted report line and returns the
     * median elapsed milliseconds so the caller can assert on it.
     */
    private function benchmark(string $label, int $instances, callable $buildStep): float
    {
        // warmup: settle JIT and any first-run buffer growth
        $buildStep();

        $samples = [];
        for ($r = 0; $r < self::REPS; $r++) {
            $start = hrtime(true);
            $buildStep();
            $samples[] = hrtime(true) - $start;
        }

        sort($samples);
        $medianNs = $samples[intdiv(count($samples), 2)];
        $medianMs = $medianNs / 1e6;
        $nsPerInstance = $instances > 0 ? $medianNs / $instances : 0.0;
        $throughput = $medianMs > 0 ? $instances / ($medianMs / 1000.0) : 0.0;

        $this->printReport($label, $instances, $medianMs, $nsPerInstance, $throughput);

        return $medianMs;
    }

    private function printReport(string $label, int $instances, float $ms, float $nsPerInstance, float $throughput): void
    {
        if (!self::$headerPrinted) {
            self::$headerPrinted = true;
            fwrite(STDOUT, "\n");
            fwrite(STDOUT, "  DrawCallAssembler::build() performance baseline (median of " . self::REPS . ")\n");
            fwrite(STDOUT, sprintf(
                "  %-28s %10s %12s %12s %16s\n",
                'scenario', 'instances', 'ms', 'ns/inst', 'inst/sec'
            ));
            fwrite(STDOUT, "  " . str_repeat('-', 80) . "\n");
        }

        fwrite(STDOUT, sprintf(
            "  %-28s %10d %12.3f %12.1f %16s\n",
            $label,
            $instances,
            $ms,
            $nsPerInstance,
            number_format($throughput, 0)
        ));
    }

    public function testSortHeavyTransparentPass(): void
    {
        $assembler = new DrawCallAssembler(4, self::LARGE, 512);
        $meshHandle = $assembler->registerMesh(
            1, 0, 3, 0, 0,
            new Vec3(-1.0, -1.0, -1.0),
            new Vec3(1.0, 1.0, 1.0)
        );

        // camera at the origin; distances derive from the transform translation
        $assembler->setCameraData(new Vec3(0.0, 0.0, 0.0));

        // build the scene once, outside the timed region
        for ($i = 0; $i < self::LARGE; $i++) {
            $transform = new Mat4();
            $transform->translate(new Vec3(0.0, 0.0, self::pseudoZ($i)));
            $assembler->submit($meshHandle, $transform, 0, DrawCallAssembler::PASS_TRANSPARENT, 0, 0, 0.0, $i);
        }

        $commandCount = 0;
        $ms = $this->benchmark('sort-heavy (transparent)', self::LARGE, function () use ($assembler, &$commandCount) {
            $commandCount = $assembler->build();
        });

        // all instances are inside the (default, unbounded) frustum and share
        // mesh/material, so they batch into a single instanced command
        $this->assertSame(self::LARGE, $assembler->builtInstanceCount());
        $this->assertSame(1, $commandCount);
        $this->assertLessThan(self::MAX_MS, $ms);
    }

    public function testCullingHeavy(): void
    {
        $assembler = new DrawCallAssembler(4, self::LARGE, 512);
        $meshHandle = $assembler->registerMesh(
            1, 0, 3, 0, 0,
            new Vec3(-1.0, -1.0, -1.0),
            new Vec3(1.0, 1.0, 1.0)
        );

        $this->applyCullingFrustum($assembler);
        $assembler->setCameraData(new Vec3(0.0, 0.0, 0.0));

        // spread instances across z; the far plane keeps only z <= 5 (plus the
        // sphere radius), so roughly half are culled
        $kept = 0;
        for ($i = 0; $i < self::LARGE; $i++) {
            $z = ($i % 2 === 0) ? 1.0 : 100.0;
            if ($z <= 5.0 + 2.0) {
                $kept++;
            }
            $transform = new Mat4();
            $transform->translate(new Vec3(0.0, 0.0, $z));
            $assembler->submit($meshHandle, $transform, 0, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, $i);
        }

        $commandCount = 0;
        $ms = $this->benchmark('culling-heavy', self::LARGE, function () use ($assembler, &$commandCount) {
            $commandCount = $assembler->build();
        });

        // all survivors share one mesh/material, so a correct sort batches them
        // into a single command; a mis-sort would fragment this (guards the
        // low-cardinality quicksort path at scale)
        $this->assertSame(1, $commandCount);

        $built = $assembler->builtInstanceCount();
        fwrite(STDOUT, sprintf(
            "  %-28s culled %d / %d (%.0f%% survived)\n",
            '',
            self::LARGE - $built,
            self::LARGE,
            100.0 * $built / self::LARGE
        ));

        // a meaningful fraction must be removed by culling
        $this->assertSame($kept, $built);
        $this->assertLessThan(self::LARGE, $built);
        $this->assertLessThan(self::MAX_MS, $ms);
    }

    public function testBatchingManyMaterials(): void
    {
        $materials = 256;

        $assembler = new DrawCallAssembler(4, self::LARGE, 1024);
        $meshHandle = $assembler->registerMesh(1, 0, 3, 0, 0);

        // cycle through many distinct materials so batching produces many groups
        for ($i = 0; $i < self::LARGE; $i++) {
            $transform = new Mat4();
            $assembler->submit($meshHandle, $transform, $i % $materials, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, $i);
        }

        $commandCount = 0;
        $ms = $this->benchmark('batching (256 materials)', self::LARGE, function () use ($assembler, &$commandCount) {
            $commandCount = $assembler->build();
        });

        fwrite(STDOUT, sprintf("  %-28s commands: %d\n", '', $commandCount));

        // one instanced command per distinct material group
        $this->assertSame($materials, $commandCount);
        $this->assertSame(self::LARGE, $assembler->builtInstanceCount());
        $this->assertLessThan(self::MAX_MS, $ms);
    }

    public function testLodAndPayload(): void
    {
        $count = self::LARGE;
        $payloadStride = 4;

        $assembler = new DrawCallAssembler(4, $count, 512);
        $baseMesh = $assembler->registerMesh(10, 0, 3, 0, 0);
        $lodMesh = $assembler->registerMesh(20, 0, 6, 0, 0);

        // switch to the lod mesh once an instance is >= 50 units away
        $assembler->setLodTable($baseMesh, new FloatBuffer([50.0]), new UIntBuffer([$lodMesh]));
        $assembler->setCameraData(new Vec3(0.0, 0.0, 0.0));

        // per-instance payload sized to the workload
        $payload = new FloatBuffer();
        $payload->reserve($count * $payloadStride);
        for ($i = 0; $i < $count; $i++) {
            $payload->push((float) $i);
            $payload->push((float) ($i + 1));
            $payload->push((float) ($i + 2));
            $payload->push((float) ($i + 3));
        }
        $assembler->bindPayloadData($payload, $payloadStride);

        // alternate instances across the lod threshold so both meshes are used
        for ($i = 0; $i < $count; $i++) {
            $z = ($i % 2 === 0) ? 10.0 : 60.0;
            $transform = new Mat4();
            $transform->translate(new Vec3(0.0, 0.0, $z));
            $assembler->submit($baseMesh, $transform, 0, DrawCallAssembler::PASS_OPAQUE, 0, 0, 0.0, $i);
        }

        $commandCount = 0;
        $ms = $this->benchmark('lod + payload', $count, function () use ($assembler, &$commandCount) {
            $commandCount = $assembler->build();
        });

        fwrite(STDOUT, sprintf("  %-28s commands: %d\n", '', $commandCount));

        // both lod levels are used and each is one mesh/material group, so a
        // correct sort produces exactly two commands; a mis-sort would
        // interleave the levels and fragment them (guards the low-cardinality
        // quicksort path at scale)
        $this->assertSame($count, $assembler->builtInstanceCount());
        $this->assertSame(2, $commandCount);
        $this->assertSame($count * $payloadStride, $assembler->instancePayloadBuffer->size());
        $this->assertLessThan(self::MAX_MS, $ms);
    }
}
