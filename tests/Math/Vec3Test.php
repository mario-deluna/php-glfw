<?php 

namespace GL\Tests\Math;

use GL\Math\Vec3;

class Vec3Test extends \PHPUnit\Framework\TestCase
{
    private function assertEqualsVector($x, $y, $z, Vec3 $v)
    {
        $this->assertEqualsWithDelta($x, $v->x, 0.005);
        $this->assertEqualsWithDelta($y, $v->y, 0.005);
        $this->assertEqualsWithDelta($z, $v->z, 0.005);
    }

    public function testConstruct() : void
    {
        $this->assertInstanceOf(Vec3::class, new Vec3);

        // vec no constuctor
        $v = new Vec3;
        $this->assertEqualsVector(0, 0, 0, $v);

        // vec with single val
        $v = new Vec3(5);
        $this->assertEqualsVector(5, 5, 5, $v);

        // vec with all args
        $v = new Vec3(1, 2, 3);
        $this->assertEqualsVector(1, 2, 3, $v);
    }

    public function testCopy() : void
    {
        $v = new Vec3(1, 2, 3);
        $v2 = $v->copy();
        $this->assertEqualsVector(1, 2, 3, $v2);

        // ensure source vector is not modified
        $v2->x = 4;
        $v2->y = 5;
        $v2->z = 6;
        $this->assertEqualsVector(1, 2, 3, $v);
        $this->assertEqualsVector(4, 5, 6, $v2);
    }

    public function testSetAndGet() : void
    {
        $vec = new Vec3;
        $this->assertEqualsVector(0.0, 0.0, 0.0, $vec);

        $vec->x = 1.0;
        $vec->y = 2.0;
        $vec->z = 3.0;
        $this->assertEquals(1.0, $vec->x);
        $this->assertEquals(2.0, $vec->y);
        $this->assertEquals(3.0, $vec->z);

        // ensure RGB are the same values
        $this->assertEquals(1.0, $vec->r);
        $this->assertEquals(2.0, $vec->g);
        $this->assertEquals(3.0, $vec->b);

        $vec->r = 3.0;
        $vec->g = 2.0;
        $vec->b = 1.0;

        $this->assertEquals(3.0, $vec->r);
        $this->assertEquals(2.0, $vec->g);
        $this->assertEquals(1.0, $vec->b);

        // ensure subscript access works
        $this->assertEquals(3.0, $vec[0]);
        $this->assertEquals(2.0, $vec[1]);
        $this->assertEquals(1.0, $vec[2]);

        $vec[0] = 1.0;
        $vec[1] = 2.0;
        $vec[2] = 3.0;

        $this->assertEquals(1.0, $vec[0]);
        $this->assertEquals(2.0, $vec[1]);
        $this->assertEquals(3.0, $vec[2]);
    }

    public function testOperations() : void
    {
        $vec1 = new Vec3(5.0, 12.5, 7.5);
        $vec2 = new Vec3(0.5, 2.0, 0.75);
    
        // add
        $r = $vec1 + $vec2;
        $this->assertEqualsVector(5.5, 14.5, 8.25, $r);

        // sub
        $r = $vec1 - $vec2;
        $this->assertEqualsVector(4.5, 10.5, 6.75, $r);

        // mul
        $r = $vec1 * $vec2;
        $this->assertEqualsVector(2.5, 25, 5.625, $r);

        // div
        $r = $vec1 / $vec2;
        $this->assertEqualsVector(10, 6.25, 10, $r);

        // scalar ops
        // add
        $r = $vec1 + 5;
        $this->assertEqualsVector(10, 17.5, 12.5, $r);

        // sub
        $r = $vec1 - 5;
        $this->assertEqualsVector(0, 7.5, 2.5, $r);

        // mul
        $r = $vec1 * 5;
        $this->assertEqualsVector(25, 62.5, 37.5, $r);

        // div
        $r = $vec1 / 5;
        $this->assertEqualsVector(1, 2.5, 1.5, $r);

        // scalar ops the other way around
        // add
        $r = 5 + $vec1;
        $this->assertEqualsVector(10, 17.5, 12.5, $r);

        // sub
        $r = 5 - $vec1;
        $this->assertEqualsVector(0, 7.5, 2.5, $r);

        // mul
        $r = 5 * $vec1;
        $this->assertEqualsVector(25, 62.5, 37.5, $r);

        // div
        $r = 5 / $vec1;
        $this->assertEqualsVector(1, 2.5, 1.5, $r);

    }

    public function testNormalize() : void
    {
        $vec = new Vec3(5.0, 12.5, 7.5);
        $vec->normalize();
        
        $this->assertEqualsVector(0.324, 0.811, 0.486, $vec);
    }

    public function testNormalized() : void
    {
        $vec = new Vec3(5.0, 12.5, 7.5);
        $r = Vec3::normalized($vec);
        
        $this->assertEqualsVector(0.324, 0.811, 0.486, $r);
    }

    public function testLength() : void
    {
        $vec = new Vec3(5.0, 12.5, 7.5);
        
        $this->assertEqualsWithDelta(15.411, $vec->length(), 0.05);
    }

    public function testAbs() : void
    {
        $vec = new Vec3(5.0, -12.5, -7.5);
        $r = $vec->abs();
        
        $this->assertEqualsVector(5, 12.5, 7.5, $r);
    }

    public function testDot() : void
    {
        $vec1 = new Vec3(5.0, 12.5, 7.5);
        $vec2 = new Vec3(0.5, 2.0, 0.75);
        
        $this->assertEqualsWithDelta(33.125, $vec1->dot($vec2), 0.05);
    }

    public function testDistance() : void
    {
        $vec1 = new Vec3(5.0, 12.5, 7.5);
        $vec2 = new Vec3(0.5, 2.0, 0.75);
        
        $this->assertEqualsWithDelta(13.268, $vec1->distance($vec2), 0.05);
    }

    public function testDistanceSquared() : void
    {
        $vec1 = new Vec3(5.0, 12.5, 7.5);
        $vec2 = new Vec3(0.5, 2.0, 0.75);
        
        $this->assertEqualsWithDelta(176.062, $vec1->distance2($vec2), 0.05);
    }

    public function testToString() : void
    {
        $vec = new Vec3(5.0, 12.5, 7.5);
        $this->assertMatchesRegularExpression("/vec3\(5.0+, 12.5([0]+)?, 7.5([0]+)?\)/", (string) $vec);
    }

    public function testCross() : void
    {
        $vec1 = new Vec3(5.0, 12.5, 7.5);
        $vec2 = new Vec3(0.5, 2.0, 0.75);
        $r = $vec1->cross($vec2);
        
        $this->assertEqualsVector(-5.625, 0, 3.75, $r);
    }
}