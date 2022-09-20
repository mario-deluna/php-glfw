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

One main difference between the `getVertices` and `getMeshes` method is that the `getMeshes` method returns an array of [Mesh](/API/Geometry/Mesh.html) objects.

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

### `__construct`

Parses on `.obj` (Wavefront object) file and makes the parsed data available.

```php
function __construct(string $file)
```

IMPORTANT: This obj. file parser does ONLY support triangulated meshes!

arguments

:    1. `string` `$file` The path to the obj file to parse.

---
     
### `getVertices`

Returns a FloatBuffer object containing the requested vertex data for the given group.

```php
function getVertices(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : \GL\Buffer\FloatBuffer
```

If no group is given the entire object is returned.

The layout of the buffer is specifed as a string, where each character represents a vertex attribute.
The following characters are supported:

 * `p` - position
 * `n` - normal
 * `N` - generated normal (estimated for each face)
 * `c` - texture coordinate
 * `t` - tangent (estimated for each face)
 * `b` - bitangent (estimated for each face)

You can use combine those characters to specify the layout of the buffer.

Example:
Layout: `pnc`
Will generate the following buffer layout:
```
[position.x, position.y, position.z, normal.x, normal.y, normal.z, textureCoordinate.x, textureCoordinate.y, ...]
```

arguments

:    1. `string` `$layout` The layout of the buffer.
    2. `\GL\Geometry\ObjFileParser\Group|null` `$group` The group to get the vertex data for.

returns

:    `\GL\Math\FloatBuffer` The generated vertex data buffer

---
     
### `getIndexedVertices`

Almost the same as getVertices but returns an Mesh object instead.

```php
function getIndexedVertices(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : \GL\Geometry\ObjFileParser\Mesh
```

The mesh object is a wrapper around the vertex data buffer and the index buffer.

Please see the `getVertices` docs for more information about the layout string.

!!! note
    Even you your object file is already indexed, this method will reindex the data.
    This is required to generate the normals and tangents. As a result this method
    is a lot slower than getVertices.

arguments

:    1. `string` `$layout` The layout of the buffer.
    2. `\GL\Geometry\ObjFileParser\Group|null` `$group` The group to get the vertex data for.

returns

:    `\GL\Geometry\Mesh` The generated mesh object

---
     
### `getMeshes`

Returns an array of Mesh objects grouped by material.

```php
function getMeshes(string $layout, ?\GL\Geometry\ObjFileParser\Group $group = null) : array
```

In many situations your object / model is split into multiple submeshes, each with its own material.
with every material there are usally different material properties associated. This usally requires
a uniform to be updated, a different shader to be used or a different texture to be bound.
This is where `getMeshes` comes in handy. It will return an array of Mesh objects, each with its own material.

Please see the `getVertices` docs for more information about the layout string.

arguments

:    1. `string` `$layout` The layout of the buffer.
    2. `\GL\Geometry\ObjFileParser\Group|null` `$group` The group to get the vertex data for.

returns

:    `\GL\Geometry\ObjFileParser\Mesh[]` 

---
     


