<?php 

namespace GL\Tests\Math;

use GL\Math\Mat4;
use GL\Math\Quat;
use GL\Math\Vec2;
use GL\Math\Vec3;
use GL\Math\Vec4;

trait MathObjectAssertions
{
    protected function assertEqualsMatrix($m00, $m01, $m02, $m03, $m10, $m11, $m12, $m13, $m20, $m21, $m22, $m23, $m30, $m31, $m32, $m33, Mat4 $m)
    {
        $this->assertEqualsWithDelta($m00, $m[0], 0.005);
        $this->assertEqualsWithDelta($m01, $m[1], 0.005);
        $this->assertEqualsWithDelta($m02, $m[2], 0.005);
        $this->assertEqualsWithDelta($m03, $m[3], 0.005);
        $this->assertEqualsWithDelta($m10, $m[4], 0.005);
        $this->assertEqualsWithDelta($m11, $m[5], 0.005);
        $this->assertEqualsWithDelta($m12, $m[6], 0.005);
        $this->assertEqualsWithDelta($m13, $m[7], 0.005);
        $this->assertEqualsWithDelta($m20, $m[8], 0.005);
        $this->assertEqualsWithDelta($m21, $m[9], 0.005);
        $this->assertEqualsWithDelta($m22, $m[10], 0.005);
        $this->assertEqualsWithDelta($m23, $m[11], 0.005);
        $this->assertEqualsWithDelta($m30, $m[12], 0.005);
        $this->assertEqualsWithDelta($m31, $m[13], 0.005);
        $this->assertEqualsWithDelta($m32, $m[14], 0.005);
        $this->assertEqualsWithDelta($m33, $m[15], 0.005);
    }

    private function assertEqualsQuat($w, $x, $y, $z, Quat $q)
    {
        $this->assertEqualsWithDelta($w, $q->w, 0.005);
        $this->assertEqualsWithDelta($x, $q->x, 0.005);
        $this->assertEqualsWithDelta($y, $q->y, 0.005);
        $this->assertEqualsWithDelta($z, $q->z, 0.005);
    }

    protected function assertEqualsVector4($x, $y, $z, $w, Vec4 $v)
    {
        $this->assertEqualsWithDelta($x, $v->x, 0.005);
        $this->assertEqualsWithDelta($y, $v->y, 0.005);
        $this->assertEqualsWithDelta($z, $v->z, 0.005);
        $this->assertEqualsWithDelta($w, $v->w, 0.005);
    }

    protected function assertEqualsVector3($x, $y, $z, Vec3 $v)
    {
        $this->assertEqualsWithDelta($x, $v->x, 0.005);
        $this->assertEqualsWithDelta($y, $v->y, 0.005);
        $this->assertEqualsWithDelta($z, $v->z, 0.005);
    }

    protected function assertEqualsVector2($x, $y, Vec2 $v)
    {
        $this->assertEqualsWithDelta($x, $v->x, 0.005);
        $this->assertEqualsWithDelta($y, $v->y, 0.005);
    }
}