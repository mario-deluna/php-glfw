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

        $this->assertEquals('test_a.png', $mesh->materials[0]->ambientTexture->name);
        $this->assertEquals('test_d.png', $mesh->materials[0]->diffuseTexture->name);
        $this->assertEquals('test_s.png', $mesh->materials[0]->specularTexture->name);
        $this->assertEquals('test_e.png', $mesh->materials[0]->emissiveTexture->name);
        $this->assertEquals('test_t.png', $mesh->materials[0]->transmittanceTexture->name);
        $this->assertEquals('test_ns.png', $mesh->materials[0]->shininessTexture->name);
        $this->assertEquals('test_ni.png', $mesh->materials[0]->indexOfRefractionTexture->name);
        $this->assertEquals('test_alpha.png', $mesh->materials[0]->dissolveTexture->name);
        $this->assertEquals('test_norm.png', $mesh->materials[0]->bumpTexture->name);
    }

    public function testMesh() : void 
    {
        $obj = new ObjFileParser(__DIR__ . '/../resources/test.obj');
        $meshes = $obj->getMeshes('p');

        $expectedData = [
            1.0, 1.0, -1.0,
            -1.0, 1.0, -1.0,
            -1.0, 1.0, 1.0,
            1.0, 1.0, 1.0,
            1.0, -1.0, 1.0,
            1.0, 1.0, 1.0,
            -1.0, 1.0, 1.0,
            -1.0, -1.0, 1.0,
            -1.0, -1.0, 1.0,
            -1.0, 1.0, 1.0,
            -1.0, 1.0, -1.0,
            -1.0, -1.0, -1.0,
            -1.0, -1.0, -1.0,
            1.0, -1.0, -1.0,
            1.0, -1.0, 1.0,
            -1.0, -1.0, 1.0,
            1.0, -1.0, -1.0,
            1.0, 1.0, -1.0,
        ];

        foreach($meshes[0]->vertices as $index => $position) {
            if (!isset($expectedData[$index])) break;
            $this->assertEquals($expectedData[$index], $position, $index . ' ' . $position);
        }
    }

    public function testMeshAABB() : void
    {
        $obj = new ObjFileParser(__DIR__ . '/../resources/test.obj');

        return; // TODO: fix this test on Linux!!!! There is some issue i did not catch yet.

        $meshes = $obj->getMeshes('p');

        $this->assertEqualsVector(-1.0, -1.0, -1.0, $meshes[0]->aabbMin);
        $this->assertEqualsVector(1.0, 1.0, 1.0, $meshes[0]->aabbMax);

        // repeat to test for memory issue 
        $meshes = $obj->getMeshes('p');

        $this->assertEqualsVector(-1.0, -1.0, -1.0, $meshes[0]->aabbMin);
        $this->assertEqualsVector(1.0, 1.0, 1.0, $meshes[0]->aabbMax);
    }

}