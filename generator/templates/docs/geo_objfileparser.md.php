# ObjFileParser

The Obj File Parser is a simple parser for the Wavefront .obj file format that ships with PHP-GLFW.
Loading some sort of geometry is essential for any 3D OpenGL application. This PHP OpenGL extension
comes with a simple parser based on the _fast_obj_ library written in C. The parser is able to load
large .obj files in a matter of seconds. I also added some additional features to the parser, like
the generation of tangents and bitangents for normal mapping.

```php 
namespace GL\Geometry
{
    class ObjFileParser {}
}
```

## Usage 

### Loading a .obj file 

```php
use GL\Geometry\ObjFileParser;

$model = new \GL\Geometry\ObjFileParser('path/to/your/3dmodel.obj');
```

### Extracting all vertices 

If you don't care about materials and just want to extract all vertices from the .obj file, you can using the `getVertices` method.

```php
$vertices = $model->getVertices('p');
```

Noticed the `p` argument? This is the vertex attribute you want to extract. 
In this example we only want to extract the position data, which is what `p` stands for.

Check out the [getVertices](#getvertices) method for more information about the available vertex attributes.

`$vertices` is now a [FloatBuffer](/API/Buffer/FloatBuffer.html) object that contains the positions of all vertices in the .obj file.

```php
var_dump($vertices); // [
    1.0, 2.0, 3.0, // vertex 1
    4.0, 5.0, 6.0, // vertex 2
    7.0, 8.0, 9.0, // vertex 3
    // ...
// ]
```

### Extracting Meshes

If your model is made up of multiple materials and you want to extract the vertices for each material, you can use the `getMeshes` method.
This method is going to be slower than the `getVertices` method, because it has to group the vertices by material. But it's still pretty fast,
and for sure faster then if you would implement the grouping in PHP.

One main difference between the `getVertices` and `getMeshes` method is that the `getMeshes` method returns an array of [Mesh](/API/Geometry/ObjFileParserMesh.html) objects.

```php
// extract `pnc` [position, normal, texture coords]
$meshes = $model->getMeshes('pnc');

foreach ($meshes as $mesh) {
    // do something with the mesh
}
```

!!! tip "Example"

    A simple example to extract the diffuse color of a typical low poly model would be can be seen [here](https://github.com/mario-deluna/php-glfw/blob/master/examples/05_objloading.php#L60)

## Properties

The ObjFileParser has a few public properties:

### $materials 

An array of material objects is parsed from the file.

```php
/*
 * @var array<\GL\Geometry\ObjFileParser\Material>
 */
public readonly array $materials;
```

### $groups

An array of groups parsed from the file. (marked as "g")

```php
/*
 * @var array<\GL\Geometry\ObjFileParser\Group>
 */
public readonly array $groups;
```

### $objects

An array of objects parsed from the file. (marked as "o")

```php
/*
 * @var array<\GL\Geometry\ObjFileParser\Group>
 */
public readonly array $objects;
```

!!! note "What is the difference between groups and objects?"
    One explanation I found said: Groups are used to group faces together. Objects are used to group groups together. 
    This is a bit confusing, but it is the way the .obj file format works.

    Now I could not confirm this as it seems that every 3D exporter does kinda what he wants with .obj files, so check your 
    .obj file and the settings of your 3D editor. 
 

## Methods

<?php foreach([
    '__construct', 
    'getVertices',
    'getIndexedVertices',
    'getMeshes'
] as $funcName) : ?>
<?php echo $docParser->getAPIRefMarkdown('GL\\Geometry\\ObjFileParser::' . $funcName); ?> 
<?php endforeach; ?>


