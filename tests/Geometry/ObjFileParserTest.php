<?php 

namespace GL\Tests\Geometry;

use GL\Geometry\ObjFileParser;
use GL\Math\Vec3;

class ObjFileParserTest extends \PHPUnit\Framework\TestCase
{
    private function assertEqualsVector($x, $y, $z, Vec3 $v)
    {
        $this->assertEqualsWithDelta($x, $v->x, 0.005);
        $this->assertEqualsWithDelta($y, $v->y, 0.005);
        $this->assertEqualsWithDelta($z, $v->z, 0.005);
    }

    public function testMaterialParsing() : void
    {
        $mesh = new ObjFileParser(__DIR__ . '/../resources/test.obj');

        $this->assertCount(1, $mesh->materials);

        $this->assertEquals('TestMaterial', $mesh->materials[0]->name);

        // assert the following material
        $this->assertEqualsVector(1.0, 2.0, 3.0, $mesh->materials[0]->ambient);
        $this->assertEqualsVector(4.0, 5.0, 6.0, $mesh->materials[0]->diffuse);
        $this->assertEqualsVector(7.0, 8.0, 9.0, $mesh->materials[0]->specular);
        $this->assertEqualsVector(10.0, 11.0, 12.0, $mesh->materials[0]->emissive);
        $this->assertEqualsVector(13.0, 14.0, 15.0, $mesh->materials[0]->transmittance);
        $this->assertEqualsVector(16.0, 17.0, 18.0, $mesh->materials[0]->transmissionFilter);

        $this->assertEquals(50.0, $mesh->materials[0]->shininess);
        $this->assertEquals(60.0, $mesh->materials[0]->indexOfRefraction);
        $this->assertEquals(70.0, $mesh->materials[0]->dissolve);
        $this->assertEquals(42, $mesh->materials[0]->illuminationModel);
    }
}