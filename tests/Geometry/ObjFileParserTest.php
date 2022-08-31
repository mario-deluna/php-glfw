<?php 

namespace GL\Tests\Geometry;

use GL\Geometry\ObjFileParser;
use GL\Math\Vec3;

class ObjFileParserTest extends \PHPUnit\Framework\TestCase
{
    public function testMaterialParsing() : void
    {
        $mesh = new ObjFileParser(__DIR__ . '/../resources/test.obj');

        $this->assertCount(1, $mesh->materials);

        $this->assertEquals('TestMaterial', $mesh->materials[0]->name);

        // assert the following material
        $this->assertEquals(new Vec3(1.0, 2.0, 3.0), $mesh->materials[0]->ambient);
        $this->assertEquals(new Vec3(4.0, 5.0, 6.0), $mesh->materials[0]->diffuse);
        $this->assertEquals(new Vec3(7.0, 8.0, 9.0), $mesh->materials[0]->specular);
        $this->assertEquals(new Vec3(10.0, 11.0, 12.0), $mesh->materials[0]->emissive);
        $this->assertEquals(new Vec3(13.0, 14.0, 15.0), $mesh->materials[0]->transmittance);
        $this->assertEquals(new Vec3(16.0, 17.0, 18.0), $mesh->materials[0]->transmissionFilter);

        $this->assertEquals(50.0, $mesh->materials[0]->shininess);
        $this->assertEquals(60.0, $mesh->materials[0]->indexOfRefraction);
        $this->assertEquals(70.0, $mesh->materials[0]->dissolve);
        $this->assertEquals(42, $mesh->materials[0]->illuminationModel);
    }
}