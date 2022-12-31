<?php 

namespace GL\Tests\Math;

use GL\Math\Vec4;

class Vec4Test extends \PHPUnit\Framework\TestCase
{
    private function assertEqualsVector(float $x, float $y, float $z, float $w, Vec4 $vec) : void
    {
        $this->assertEqualsWithDelta($x, $vec->x, 0.005);
        $this->assertEqualsWithDelta($y, $vec->y, 0.005);
        $this->assertEqualsWithDelta($z, $vec->z, 0.005);
        $this->assertEqualsWithDelta($w, $vec->w, 0.005);
    }

    public function testConstruct() : void
    {
        $this->assertInstanceOf(Vec4::class, new Vec4);

        // vec no constuctor
        $vec = new Vec4;
        $this->assertEqualsVector(0, 0, 0, 0, $vec);

        // vec with constructor
        $vec = new Vec4(1.0, 2.0, 3.0, 4.0);
        $this->assertEqualsVector(1.0, 2.0, 3.0, 4.0, $vec);

        // vec with single val
        $vec = new Vec4(5.0);
        $this->assertEqualsVector(5.0, 5.0, 5.0, 5.0, $vec);
    }

    public function testCopy() : void
    {
        $vec = new Vec4(1.0, 2.0, 3.0, 4.0);
        $vec2 = $vec->copy();
        $this->assertEqualsVector(1.0, 2.0, 3.0, 4.0, $vec2);

        // ensure source vector is not modified
        $vec2->x = 5.0;
        $vec2->y = 6.0;
        $vec2->z = 7.0;
        $vec2->w = 8.0;
        $this->assertEqualsVector(1.0, 2.0, 3.0, 4.0, $vec);
        $this->assertEqualsVector(5.0, 6.0, 7.0, 8.0, $vec2);
    }

    public function testSetAndGet() : void
    {
        $vec = new Vec4;
        $this->assertEqualsVector(0.0, 0.0, 0.0, 0.0, $vec);

        $vec->x = 1.0;
        $vec->y = 2.0;
        $vec->z = 3.0;
        $vec->w = 4.0;
        $this->assertEquals(1.0, $vec->x);
        $this->assertEquals(2.0, $vec->y);
        $this->assertEquals(3.0, $vec->z);
        $this->assertEquals(4.0, $vec->w);

        // ensure RGB are the same values
        $this->assertEquals(1.0, $vec->r);
        $this->assertEquals(2.0, $vec->g);
        $this->assertEquals(3.0, $vec->b);
        $this->assertEquals(4.0, $vec->a);

        $vec->r = 3.0;
        $vec->g = 2.0;
        $vec->b = 1.0;
        $vec->a = 0.0;

        $this->assertEquals(3.0, $vec->r);
        $this->assertEquals(2.0, $vec->g);
        $this->assertEquals(1.0, $vec->b);
        $this->assertEquals(0.0, $vec->a);

        // ensure subscript access works
        $this->assertEquals(3.0, $vec[0]);
        $this->assertEquals(2.0, $vec[1]);
        $this->assertEquals(1.0, $vec[2]);
        $this->assertEquals(0.0, $vec[3]);

        $vec[0] = 1.0;
        $vec[1] = 2.0;
        $vec[2] = 3.0;
        $vec[3] = 4.0;

        $this->assertEquals(1.0, $vec[0]);
        $this->assertEquals(2.0, $vec[1]);
        $this->assertEquals(3.0, $vec[2]);
        $this->assertEquals(4.0, $vec[3]);
    }

    public function testOperations() : void
    {
        $vec1 = new Vec4(5.0, 12.5, 7.5, 1.0);
        $vec2 = new Vec4(0.5, 2.0, 0.75, 1.0);
    
        // add
        $r = $vec1 + $vec2;
        $this->assertEqualsVector(5.5, 14.5, 8.25, 2.0, $r);

        // sub
        $r = $vec1 - $vec2;
        $this->assertEqualsVector(4.5, 10.5, 6.75, 0.0, $r);

        // mul
        $r = $vec1 * $vec2;
        $this->assertEqualsVector(2.5, 25, 5.625, 1.0, $r);

        // div
        $r = $vec1 / $vec2;
        $this->assertEqualsVector(10, 6.25, 10, 1.0, $r);

        // scalar ops
        // add
        $r = $vec1 + 5;
        $this->assertEqualsVector(10, 17.5, 12.5, 6.0, $r);

        // sub
        $r = $vec1 - 5;
        $this->assertEqualsVector(0, 7.5, 2.5, -4.0, $r);

        // mul
        $r = $vec1 * 5;
        $this->assertEqualsVector(25, 62.5, 37.5, 5.0, $r);

        // div
        $r = $vec1 / 5;
        $this->assertEqualsVector(1, 2.5, 1.5, 0.2, $r);

        // scalar ops the other way around
        // add
        $r = 5 + $vec1;
        $this->assertEqualsVector(10, 17.5, 12.5, 6.0, $r);

        // sub
        $r = 5 - $vec1;
        $this->assertEqualsVector(0, 7.5, 2.5, -4.0, $r);

        // mul
        $r = 5 * $vec1;
        $this->assertEqualsVector(25, 62.5, 37.5, 5.0, $r);

        // div
        $r = 5 / $vec1;
        $this->assertEqualsVector(1, 2.5, 1.5, 0.2, $r);
    }

    public function testNormalize() : void
    {
        $vec = new Vec4(5.0, 12.5, 7.5, 1.0);
        $vec->normalize();

        $this->assertEqualsVector(0.324, 0.811, 0.486, 0.064, $vec);
    }

    public function testNormalized() : void
    {
        $vec = new Vec4(5.0, 12.5, 7.5, 1.0);
        $r = Vec4::normalized($vec);

        $this->assertEqualsVector(0.324, 0.811, 0.486, 0.064, $r);
    }

    public function testLength() : void
    {
        $vec = new Vec4(5.0, 12.5, 7.5, 5.0);

        $this->assertEqualsWithDelta(16.20, $vec->length(), 0.05);
    }

    public function testAbs() : void
    {
        $vec = new Vec4(-5.0, 12.5, -7.5, 5.0);
        $vec->abs();

        $this->assertEqualsVector(5.0, 12.5, 7.5, 5.0, $vec);
    }

    public function testDot() : void
    {
        $vec1 = new Vec4(5.0, 12.5, 7.5, 1.0);
        $vec2 = new Vec4(0.5, 2.0, 0.75, 1.0);

        $this->assertEquals(34.125, Vec4::dot($vec1, $vec2));
    }

    public function testDistance() : void
    {
        $vec1 = new Vec4(5.0, 12.5, 7.5, 5.0);
        $vec2 = new Vec4(0.5, 2.0, 0.75, 1.0);

        $this->assertEqualsWithDelta(13.85, $vec1->distanceTo($vec2), 0.05);

        $this->assertEqualsWithDelta(13.85, Vec4::distance($vec1, $vec2), 0.05);
    }

    public function testDistanceSquared() : void
    {
        $vec1 = new Vec4(5.0, 12.5, 7.5, 5.0);
        $vec2 = new Vec4(0.5, 2.0, 0.75, 1.0);

        $this->assertEquals(192.0625, $vec1->distance2To($vec2));

        $this->assertEquals(192.0625, Vec4::distance2($vec1, $vec2));
    }
}   