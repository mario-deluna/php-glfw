<?php 

namespace GL\Tests\Math;

use GL\Math\GLM;
use GL\Math\Vec2;
use GL\Math\Vec3;
use GL\Math\Vec4;

class GLMTest extends \PHPUnit\Framework\TestCase
{
    public function testRadians() : void
    {
        $this->assertEqualsWithDelta(M_PI * 0.5, GLM::radians(90.0), 0.005);
        $this->assertEqualsWithDelta(M_PI, GLM::radians(180.0), 0.005);
    }

    public function testAngle() : void
    {
        $this->assertEqualsWithDelta(90.0, GLM::angle(M_PI * 0.5), 0.005);
        $this->assertEqualsWithDelta(180.0, GLM::angle(M_PI), 0.005);
    }

    public function testNormalize() : void
    {
        // vec4
        $vec = new Vec4(1.0, 2.0, 3.0, 4.0);
        $normalized = GLM::normalize($vec);
        $this->assertEqualsWithDelta(0.182, $normalized->x, 0.005);
        $this->assertEqualsWithDelta(0.365, $normalized->y, 0.005);
        $this->assertEqualsWithDelta(0.547, $normalized->z, 0.005);
        $this->assertEqualsWithDelta(0.730, $normalized->w, 0.005);

        // ensure source vector is not modified
        $this->assertEquals(1.0, $vec->x);
        $this->assertEquals(2.0, $vec->y);
        $this->assertEquals(3.0, $vec->z);
        $this->assertEquals(4.0, $vec->w);

        // vec3
        $vec = new Vec3(1.0, 2.0, 3.0);
        $normalized = GLM::normalize($vec);
        $this->assertEqualsWithDelta(0.267, $normalized->x, 0.005);
        $this->assertEqualsWithDelta(0.535, $normalized->y, 0.005);
        $this->assertEqualsWithDelta(0.802, $normalized->z, 0.005);

        // ensure source vector is not modified
        $this->assertEquals(1.0, $vec->x);
        $this->assertEquals(2.0, $vec->y);
        $this->assertEquals(3.0, $vec->z);

        // vec2
        $vec = new Vec2(1.0, 2.0);
        $normalized = GLM::normalize($vec);
        $this->assertEqualsWithDelta(0.447, $normalized->x, 0.005);
        $this->assertEqualsWithDelta(0.894, $normalized->y, 0.005);

        // ensure source vector is not modified
        $this->assertEquals(1.0, $vec->x);
        $this->assertEquals(2.0, $vec->y);
    }

    // public function testTriangleNormal() : void
    // {
    //     $p1 = new Vec3(0.0, 0.0, 0.0);
    //     $p2 = new Vec3(1.0, 0.0, 0.0);
    //     $p3 = new Vec3(0.0, 1.0, 0.0);
    //     $normal = GLM::triangleNormal($p1, $p2, $p3);
    //     $this->assertEqualsWithDelta(0.0, $normal->x, 0.005);
    //     $this->assertEqualsWithDelta(0.0, $normal->y, 0.005);
    //     $this->assertEqualsWithDelta(1.0, $normal->z, 0.005);
    // }
}