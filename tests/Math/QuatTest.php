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

    public function testNormalize() : void
    {
        $q = new Quat(1, 2, 3, 4);
        $q->normalize();
        $this->assertEqualsQuat(0.182574, 0.365148, 0.547723, 0.730297, $q);
    }

    public function testNormalized() : void
    {
        $q = new Quat(1, 2, 3, 4);
        $q = Quat::normalized($q);
        $this->assertEqualsQuat(0.182574, 0.365148, 0.547723, 0.730297, $q);
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

    public function testMat4() : void
    {
        $q = new Quat();
        $m = $q->mat4();

        $this->assertEqualsMatrix(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
            $m
        );

        // rotate on x axis
        $q = new Quat();
        $q->rotate(GLM::radians(45), new Vec3(1, 0, 0));
        $m = $q->mat4();

        $this->assertEqualsMatrix(
            1, 0, 0, 0,
            0, 0.7071067811865475, 0.7071067811865475, 0,
            0, -0.7071067811865475, 0.7071067811865475, 0,
            0, 0, 0, 1,
            $m
        );

        // rotate on y axis
        $q->rotate(GLM::radians(45), new Vec3(0, 1, 0));
        $m = $q->mat4();

        $this->assertEqualsMatrix(
            0.7071067811865475, 0.5, -0.5, 0,
            0, 0.7071067811865475, 0.7071067811865475, 0,
            0.7071067811865475, -0.5, 0.5, 0,
            0, 0, 0, 1,
            $m
        );

        // rotate on z axis
        $q->rotate(GLM::radians(45), new Vec3(0, 0, 1));
        $m = $q->mat4();

        $this->assertEqualsMatrix(
            0.5, 0.853553, 0.146447, 0,
            -0.5, 0.146446, 0.853553, 0,
            0.707107, -0.5, 0.5, 0,
            0, 0, 0, 1,
            $m
        );
    }

    public function testConstructFromMat4()
    {
        $m = new Mat4;
        $q = Quat::fromMat4($m);

        $this->assertEqualsQuat(1, 0, 0, 0, $q);

        // rotate on x axis
        $m = new Mat4;
        $m->rotate(GLM::radians(45), new Vec3(1, 0, 0));

        $q = Quat::fromMat4($m);
        $this->assertEqualsQuat(0.92388, 0.382683, 0, 0, $q);

        // rotate on y axis
        $m = new Mat4;
        $m->rotate(GLM::radians(45), new Vec3(0, 1, 0));

        $q = Quat::fromMat4($m);
        $this->assertEqualsQuat(0.92388, 0, 0.382683, 0, $q);

        // now consecutive rotations
        $m = new Mat4;
        $m->rotate(GLM::radians(45), new Vec3(1, 0, 0));
        $m->rotate(GLM::radians(45), new Vec3(0, 1, 0));
        $m->rotate(GLM::radians(45), new Vec3(0, 0, 1));

        $q = Quat::fromMat4($m);
        $this->assertEqualsQuat(0.732538, 0.46194, 0.191342, 0.46194, $q);
    }

    public function testConstructFromVec4()
    {
        $v = new Vec4(1, 2, 3, 4);
        $q = Quat::fromVec4($v);

        $this->assertEqualsQuat(4, 1, 2, 3, $q);
    }

    public function testOperationAddition()
    {
        $q1 = new Quat(1, 2, 3, 4);
        $q2 = new Quat(5, 6, 7, 8);

        $q3 = $q1 + $q2;
        $this->assertEqualsQuat(6, 8, 10, 12, $q3);

        // test with switched operands
        $q3 = $q2 + $q1;
        $this->assertEqualsQuat(6, 8, 10, 12, $q3);
    }

    public function testOperationSubtraction()
    {
        $q1 = new Quat(1, 2, 3, 4);
        $q2 = new Quat(5, 6, 7, 8);

        $q3 = $q1 - $q2;
        $this->assertEqualsQuat(-4, -4, -4, -4, $q3);

        // test with switched operands
        $q3 = $q2 - $q1;
        $this->assertEqualsQuat(4, 4, 4, 4, $q3);
    }

    public function testOperationMultiplication()
    {
        $q1 = new Quat(1, 2, 3, 4);
        $q2 = new Quat(5, 6, 7, 8);

        $q3 = $q1 * $q2;
        $this->assertEqualsQuat(-60, 12, 30, 24, $q3);

        // test with switched operands
        $q3 = $q2 * $q1;
        $this->assertEqualsQuat(-60, 20, 14, 32, $q3);
    }

    public function testOperationScalarMultiplication()
    {
        $q = new Quat(1, 2, 3, 4);

        $q2 = $q * 2;
        $this->assertEqualsQuat(2, 4, 6, 8, $q2);

        // test with switched operands
        $q2 = 2 * $q;
        $this->assertEqualsQuat(2, 4, 6, 8, $q2);
    }

    public function testOperationScalarDivision()
    {
        $q = new Quat(1, 2, 3, 4);

        $q2 = $q / 2;
        $this->assertEqualsQuat(0.5, 1, 1.5, 2, $q2);
    }
    
    public function testOperationVec3Multiplication()
    {
        $q = new Quat(1, 2, 3, 4);
        $q->normalize();
        $v = new Vec3(5, 6, 7);

        $v2 = $q * $v;

        $this->assertEqualsVector3(2.6, 6, 8.2, $v2);

        // test with switched operands
        $v2 = $v * $q;
    
        $this->assertEqualsVector3(3, 5.2, 8.6, $v2);


        // test a rotation for human
        // we create a quat that rotates 90 degrees on y axis
        $q = new Quat;
        $q->rotate(GLM::radians(90), new Vec3(0, 1, 0));

        // we create a vector that points to the right
        $v = new Vec3(1, 0, 0);

        // we rotate the vector
        $v2 = $q * $v;

        // we expect the vector to point to the front
        $this->assertEqualsVector3(0, 0, -1, $v2);
    }
}