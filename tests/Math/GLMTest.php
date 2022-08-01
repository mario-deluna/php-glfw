<?php 

namespace GL\Tests\Math;

use GLM;
use GL\Math\Vec3;

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

    public function testTriangleNormal() : void
    {
        $p1 = new Vec3(0.0, 0.0, 0.0);
        $p2 = new Vec3(1.0, 0.0, 0.0);
        $p3 = new Vec3(0.0, 1.0, 0.0);
        $normal = GLM::triangleNormal($p1, $p2, $p3);
        $this->assertEqualsWithDelta(0.0, $normal->x, 0.005);
        $this->assertEqualsWithDelta(0.0, $normal->y, 0.005);
        $this->assertEqualsWithDelta(1.0, $normal->z, 0.005);
    }
}