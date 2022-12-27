<?php 

namespace GL\Tests\Math;

use GL\Math\GLM;
use GL\Math\Mat4;
use GL\Math\Quat;
use GL\Math\Vec3;
use GL\Math\Vec4;

require_once __DIR__ . '/MathObjectAssertions.php';

class QuatTest extends \PHPUnit\Framework\TestCase
{
    use MathObjectAssertions;

    public function testConstruct() : void
    {
        $this->assertInstanceOf(Quat::class, new Quat);

        // ensure identity quat is correct
        $q = new Quat;
        $this->assertEqualsQuat(1, 0, 0, 0, $q);
    }

    public function testSubscriptAccess() : void
    {
        $q = new Quat;
        $q[0] = 1.0;
        $q[1] = 2.0;
        $q[2] = 3.0;
        $q[3] = 4.0;

        // assert props
        $this->assertEqualsQuat(1, 2, 3, 4, $q);

        // set over props and assert via subscript
        $q->w = 5.0;
        $q->x = 6.0;
        $q->y = 7.0;
        $q->z = 8.0;

        $this->assertEquals(5, $q[0]);
        $this->assertEquals(6, $q[1]);
        $this->assertEquals(7, $q[2]);
        $this->assertEquals(8, $q[3]);
    }

    public function testQuatLength() : void
    {
        $q = new Quat(1, 2, 3, 4);
        $this->assertEqualsWithDelta(5.4772257804870605, $q->length(), 0.005);
    }

    public function testRotate() : void 
    {
        // test rotate on x axis
        $q = new Quat;
        $q->rotate(GLM::radians(45), new Vec3(1, 0, 0));
        $this->assertEqualsQuat(0.92388, 0.382683, 0, 0, $q);

        // test rotate on y axis
        $q = new Quat;
        $q->rotate(GLM::radians(45), new Vec3(0, 1, 0));
        $this->assertEqualsQuat(0.92388, 0, 0.382683, 0, $q);

        // test rotate on z axis
        $q = new Quat;
        $q->rotate(GLM::radians(45), new Vec3(0, 0, 1));
        $this->assertEqualsQuat(0.92388, 0, 0, 0.382683, $q);

        // now test multiple consecutive rotations
        $q = new Quat;
        $q->rotate(GLM::radians(45), new Vec3(1, 0, 0));
        $this->assertEqualsQuat(0.92388, 0.382683, 0, 0, $q);
        $q->rotate(GLM::radians(45), new Vec3(0, 1, 0));
        $this->assertEqualsQuat(0.853553, 0.353553, 0.353553, 0.146447, $q);
        $q->rotate(GLM::radians(45), new Vec3(0, 0, 1));
        $this->assertEqualsQuat(0.732538, 0.46194, 0.191342, 0.46194, $q);
    }
}