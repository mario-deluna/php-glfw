<?php 

namespace GL\Tests\Math;

use GL\Math\GLM;
use GL\Math\Mat4;
use GL\Math\Vec3;
use GL\Math\Vec4;

require_once __DIR__ . '/MathObjectAssertions.php';

class Mat4Test extends \PHPUnit\Framework\TestCase
{
    use MathObjectAssertions;

    private function createTestMatrix() : Mat4
    {
        $m = new Mat4;
        $m[0] = 1.0;
        $m[1] = 2.0;
        $m[2] = 3.0;
        $m[3] = 4.0;
        $m[4] = 5.0;
        $m[5] = 6.0;
        $m[6] = 7.0;
        $m[7] = 8.0;
        $m[8] = 9.0;
        $m[9] = 10.0;
        $m[10] = 11.0;
        $m[11] = 12.0;
        $m[12] = 13.0;
        $m[13] = 14.0;
        $m[14] = 15.0;
        $m[15] = 16.0;
        return $m;
    }
    
    public function testConstruct() : void
    {
        $this->assertInstanceOf(Mat4::class, new Mat4);

        // ensure identity matrix is correct
        $m = new Mat4;
        $this->assertEqualsMatrix(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
            $m
        );
    }

    public function testReadAndWrite() : void
    {
        $m = new Mat4;
        $m[0] = 1.0;
        $m[1] = 2.0;
        $m[2] = 3.0;
        $m[3] = 4.0;
        $m[4] = 5.0;
        $m[5] = 6.0;
        $m[6] = 7.0;
        $m[7] = 8.0;
        $m[8] = 9.0;
        $m[9] = 10.0;
        $m[10] = 11.0;
        $m[11] = 12.0;
        $m[12] = 13.0;
        $m[13] = 14.0;
        $m[14] = 15.0;
        $m[15] = 16.0;
        
        $this->assertEqualsMatrix(
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16,
            $m
        );
    }

    public function testCopy() : void
    {
        $m = $this->createTestMatrix();
        
        $m2 = $m->copy();
        $this->assertEqualsMatrix(
            1.0, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16,
            $m2
        );

        for($i = 0; $i < 16; $i++) {
            $m[$i] = 0.0;
        }

        $this->assertEqualsMatrix(
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            $m
        );

        $this->assertEqualsMatrix(
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16,
            $m2
        );
    }
    
    public function testRow() : void
    {
        $m = $this->createTestMatrix();
        
        $this->assertEqualsVector4(1, 2, 3, 4, $m->row(0));
        $this->assertEqualsVector4(5, 6, 7, 8, $m->row(1));
        $this->assertEqualsVector4(9, 10, 11, 12, $m->row(2));
        $this->assertEqualsVector4(13, 14, 15, 16, $m->row(3));
    }

    public function testSetRow() : void
    {
        $m = new Mat4;
        $m->setRow(0, new Vec4(1, 2, 3, 4));
        $m->setRow(1, new Vec4(5, 6, 7, 8));
        $m->setRow(2, new Vec4(9, 10, 11, 12));
        $m->setRow(3, new Vec4(13, 14, 15, 16));
        
        $this->assertEqualsMatrix(
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16,
            $m
        );
    }

    public function testCol() : void
    {
        $m = $this->createTestMatrix();
        
        $this->assertEqualsVector4(1, 5, 9, 13, $m->col(0));
        $this->assertEqualsVector4(2, 6, 10, 14, $m->col(1));
        $this->assertEqualsVector4(3, 7, 11, 15, $m->col(2));
        $this->assertEqualsVector4(4, 8, 12, 16, $m->col(3));
    }

    public function testSetCol() : void
    {
        $m = new Mat4;
        $m->setCol(0, new Vec4(1, 5, 9, 13));
        $m->setCol(1, new Vec4(2, 6, 10, 14));
        $m->setCol(2, new Vec4(3, 7, 11, 15));
        $m->setCol(3, new Vec4(4, 8, 12, 16));
        
        $this->assertEqualsMatrix(
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            13, 14, 15, 16,
            $m
        );
    }

    public function testOperationAddition() : void
    {
        $m = $this->createTestMatrix();
        $m2 = $this->createTestMatrix();
        
        $m3 = $m + $m2;
        $this->assertEqualsMatrix(
            2, 4, 6, 8,
            10, 12, 14, 16,
            18, 20, 22, 24,
            26, 28, 30, 32,
            $m3
        );
    }

    public function testOperationSubstraction() : void
    {
        $m = $this->createTestMatrix();
        $m2 = $this->createTestMatrix();
        
        $m3 = $m - $m2;
        $this->assertEqualsMatrix(
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            $m3
        );

        $m4 = $m - new Mat4;
        $this->assertEqualsMatrix(
            0, 2, 3, 4,
            5, 5, 7, 8,
            9, 10, 10, 12,
            13, 14, 15, 15,
            $m4
        );
    }

    public function testOperationMultiply() : void
    {
        $m1 = $this->createTestMatrix();
        $m2 = $this->createTestMatrix();
        
        $m3 = $m1 * $m2;

        $this->assertEqualsMatrix(
            90, 100, 110, 120,
            202, 228, 254, 280,
            314, 356, 398, 440,
            426, 484, 542, 600,
            $m3
        );

        // test order
        $m3 = new Mat4;
        $m3[0] = 0.16; 
        $m3[1] = 0.15; 
        $m3[2] = 0.14; 
        $m3[3] = 0.13; 
        $m3[4] = 0.12; 
        $m3[5] = 0.11; 
        $m3[6] = 0.10; 
        $m3[7] = 0.9; 
        $m3[8] = 0.8; 
        $m3[9] = 0.7;
        $m3[10] = 0.6; 
        $m3[11] = 0.5; 
        $m3[12] = 0.4; 
        $m3[13] = 0.3; 
        $m3[14] = 0.2; 
        $m3[15] = 0.1;

        $this->assertEqualsMatrix(
            4.4, 3.67, 2.94, 3.83,
            10.32, 8.71, 7.1, 10.35,
            16.24, 13.75, 11.26, 16.87,
            22.16, 18.79, 15.42, 23.39,
            $m3 * $m1
        );

        $this->assertEqualsMatrix(
            3.86, 4.44, 5.02, 5.6,
            13.27, 14.5, 15.73, 16.96,
            16.2, 18.8, 21.4, 24,
            5, 6, 7, 8,
            $m1 * $m3
        );

        $m2 = new Mat4;
        for($i = 0; $i < 16; $i++) {
            $m2[$i] = (float) 16 - $i;
        }

        // so as it turns out there is a "bug" in the zend engine
        // that is swapping the multiplication operands in some ituations.
        // As there is no matrix lib in php it never mattered if the operands
        // are switched as an optimisation matter until now. 
        // -> https://github.com/php/php-src/issues/9175
        // until there is a fix for this when multiplying 
        // more then one matrix at once we have to set paranthesis to enforce execution order.
        // var_dump((string) ($m1 * $m2));
        // var_dump((string) ($m1 * $m2 * $m3));
        // var_dump((string) ($m1 * ($m2 * $m3)));
        // var_dump((string) (($m1 * $m2) * $m3));
        // die;

        // assert the this matrix mat4x4(( 132.04, 152.56, 173.08, 193.6 ), ( 137.66, 160.84, 184.02, 207.2 ), ( 622.8, 719.2, 815.6, 912 ), ( 274, 316, 358, 400 ))
        $this->assertEqualsMatrix(
            132.04, 152.56, 173.08, 193.6,
            137.66, 160.84, 184.02, 207.2,
            622.8, 719.2, 815.6, 912,
            274, 316, 358, 400,
            $m1 * ($m2 * $m3)
        );
    }

    public function testOperationAdditionAssignment() : void
    {
        $m = $this->createTestMatrix();
        $m2 = $this->createTestMatrix();
        
        $m += $m2;
        $this->assertEqualsMatrix(
            2, 4, 6, 8,
            10, 12, 14, 16,
            18, 20, 22, 24,
            26, 28, 30, 32,
            $m
        );
    }

    public function testOperationSubstractionAssignment() : void
    {
        $m = $this->createTestMatrix();
        $m2 = $this->createTestMatrix();
        
        $m -= $m2;
        $this->assertEqualsMatrix(
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            $m
        );
    }

    public function testOperationMultiplyVector3() : void
    {
        $v = new Vec3(0.5, 1, 5);
        $m = new Mat4;

        $m->translate(new Vec3(10, 0, 0));
        $m->scale(new Vec3(5, 5, 5));
        
        $v2 = $m * $v;

        $this->assertEqualsVector3(12.5, 5, 25, $v2);

        // now with the stupid test matrix
        $m = $this->createTestMatrix();
        $v = new Vec3(1, 2, 3);

        $v2 = $m * $v;

        $this->assertEqualsVector3(51, 58, 65, $v2);

        // test a rotation 
        $m = new Mat4;
        $m->rotate(GLM::radians(45), new Vec3(0, 0, 1));
        $v = new Vec3(0.5, 1, 5);

        $v2 = $m * $v;

        $this->assertEqualsVector3(-0.353553, 1.06066, 5, $v2);
    }

    public function testOperationMultiplyVector4() : void
    {
        $v = new Vec4(0.5, 1, 5, 1);
        $m = new Mat4;

        $m->translate(new Vec3(10, 0, 0));
        $m->scale(new Vec3(5, 5, 5));
        
        $v2 = $m * $v;

        $this->assertEqualsVector4(12.5, 5, 25, 1, $v2);
    }

    public function testPerspective() : void
    {
        $m = new Mat4;
        $m->perspective(90.0, 4.0 / 3.0, .1, 100.0);
        
        $this->assertEqualsMatrix(
            0.463027, 0, 0, 0,
            0, 0.61737, 0, 0,
            0, 0, -1.002, -1,
            0, 0, -0.2002, 0,
            $m
        );
    }

    public function testOrtho() : void
    {
        $m = new Mat4;
        $m->ortho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
        
        $this->assertEqualsMatrix(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, -1, 0,
            0, 0, 0, 1,
            $m
        );

        $m->ortho(0, 1920, 0, 1080, -0.1, 100.0);

        $this->assertEqualsMatrix(
            0.001, 0, 0, 0,
            0, 0.001, 0, 0,
            0, 0, -0.019, 0,
            -1, -1, -0.998, 1,
            $m
        );
    }

    public function testLookAt() : void
    {
        $m = new Mat4;
        $m->lookAt(new Vec3(10, 10, 10), new Vec3(50, -50, 50), new Vec3(0, 1, 0));
        $this->assertEqualsMatrix(
            -0.707,  0.514, -0.485, 0,
             0.000,  0.685,  0.727, 0,
             0.707,  0.514, -0.485, 0,
            -0.000, -17.149, 2.425, 1,
            $m
        );

        $m->lookAt(new Vec3(0, 1000, 0), new Vec3(1, 1, 1), new Vec3(0.0, 1.0, 0.0));
        $this->assertEqualsMatrix(
            -0.707107, 0.707106, -0.001001, 0,
            0, 0.00141563, 0.999999, 0,
            0.707107, 0.707106, -0.001001, 0,
            -0, -1.41563, -999.999, 1,
            $m
        );
    }

    public function testTranspose() : void
    {
        $m = $this->createTestMatrix();
        $m->transpose();

        $this->assertEqualsMatrix(
            1, 5, 9, 13,
            2, 6, 10, 14,
            3, 7, 11, 15,
            4, 8, 12, 16,
            $m
        );
    }

    public function testInverse() : void
    {
        $m = new Mat4;
        $m->inverse();

        $this->assertEqualsMatrix(
            1, -0, 0, -0,
            -0, 1, -0, 0,
            0, -0, 1, -0,
            -0, 0, -0, 1,
            $m
        );

        $m->lookAt(new Vec3(10, 10, 10), new Vec3(50, -50, 50), new Vec3(0, 1, 0));
        $m->inverse();

        $this->assertEqualsMatrix(
            -0.707107, -0, 0.707107, -0,
            0.514496, 0.685994, 0.514496, 0,
            -0.485071, 0.727607, -0.485071, 0,
            10, 10, 10, 1,
            $m
        );
    }

    public function testInverted()
    {
        $m = new Mat4;
        $m->lookAt(new Vec3(10, 10, 10), new Vec3(50, -50, 50), new Vec3(0, 1, 0));
        $m2 = Mat4::inverted($m);

        $this->assertEqualsMatrix(
            -0.707107, -0, 0.707107, -0,
            0.514496, 0.685994, 0.514496, 0,
            -0.485071, 0.727607, -0.485071, 0,
            10, 10, 10, 1,
            $m2
        );
    }

    public function testTranslate() : void
    {
        $m = $this->createTestMatrix();
        $m->translate(new Vec3(10, 15, 20));

        $this->assertEqualsMatrix(
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            278, 324, 370, 416,
            $m
        );

        // translate further
        $m->translate(new Vec3(10, 15, 20));
        $this->assertEqualsMatrix(
            1, 2, 3, 4,
            5, 6, 7, 8,
            9, 10, 11, 12,
            543, 634, 725, 816,
            $m
        );
    }

    public function testScale() : void
    {
        $m = new Mat4;
        $m->scale(new Vec3(2, 3, 4));
        $this->assertEqualsMatrix(
            2, 0, 0, 0,
            0, 3, 0, 0,
            0, 0, 4, 0,
            0, 0, 0, 1,
            $m
        );

        $m = $this->createTestMatrix();
        $m->scale(new Vec3(2, 3, 4));
        $this->assertEqualsMatrix(
            2, 4, 6, 8,
            15, 18, 21, 24,
            36, 40, 44, 48,
            13, 14, 15, 16,
            $m
        );
    }

    public function testRotate() : void
    {
        $m = new Mat4;
        $m->rotate(GLM::radians(90), new Vec3(0, 0, 1));

        $this->assertEqualsMatrix(
            -4.37114e-08, 1, 0, 0,
            -1, -4.37114e-08, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
            $m
        );

        // rotate further
        $m->rotate(GLM::radians(90), new Vec3(0, 0, 1));

        $this->assertEqualsMatrix(
            -1, -8.74228e-08, 0, 0,
            8.74228e-08, -1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1,
            $m
        );
        
        // and further on all axis for good mesure
        $m->rotate(GLM::radians(45), new Vec3(1, 1, 1));

        $this->assertEqualsMatrix(
            -0.804738, -0.505879, -0.310617, 0,
            0.310617, -0.804738, 0.505879, 0,
            -0.505879, 0.310617, 0.804738, 0,
            0, 0, 0, 1,
            $m
        );
    }

    public function testDeterminant() : void
    {
        $m = new Mat4;
        $this->assertEquals(1, $m->determinant());
        
        $m[0] = 1.0;
        $m[1] = 2.0;
        $m[2] = 3.0;
        $m[3] = 4.0;
        $m[4] = 5.0;
        $m[5] = 6.0;
        $m[6] = 7.0;
        $m[7] = 8.0;
        $m[8] = 9.0;
        $m[9] = 10.0;
        $m[10] = 11.0;
        $m[11] = 12.0;
        $m[12] = 13.0;
        $m[13] = 14.0;
        $m[14] = 15.0;
        $m[15] = 16.0;
        
        $this->assertEquals(0.0, $m->determinant());

        $m[0] = -10.0;
        $m[10] = -10.0;

        $this->assertEquals(-3696.0, $m->determinant());
    }
}