# ObjFileParser

The Obj File Parser is a simple parser for the Wavefront .obj file format that ships with PHP-GLFW.
Loading of some sort of geometry is essetial for any 3D OpenGL application. This PHP OpenGL extension
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


## Properties

The ObjFileParser has a few public properties:

### $materials 

An array of material objects parsed from the file.

```php
/*
 * @var array<\GL\Geometry\ObjFileParser\Material>
 */
public readonly array $materials;
```

### $groups

An array groups parsed from the file. (marked as "g")

```php
/*
 * @var array<\GL\Geometry\ObjFileParser\Group>
 */
public readonly array $groups;
```

### $objects

An array objects parsed from the file. (marked as "o")

```php
/*
 * @var array<\GL\Geometry\ObjFileParser\Group>
 */
public readonly array $objects;
```

!!! note "What is the difference between groups and objects?"
    One explanation i found said: Groups are used to group faces together. Objects are used to group groups together. 
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


