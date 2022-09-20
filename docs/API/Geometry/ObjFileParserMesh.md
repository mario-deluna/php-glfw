---
title: ObjFileParser / Mesh
---

The Obj File Parser's Mesh class does not bring any new functionality to the table. It's just a container for the three objects that can make up a mesh by PHP OpenGLs definition. 

- Vertices ([FloatBuffer](/API/Buffer/FloatBuffer.html)) storing the vertex data, like position, normal, texture coordinates, etc.
- indices ([UIntBuffer](/API/Buffer/UIntBuffer.html)) storing the indices of the vertices that make up the triangles. **optional**
- [Material](/API/Geometry/ObjFileParserMaterial.html) the material of the mesh. **optional**

```php 
namespace GL\Geometry\ObjFileParser
{
    class Mesh {}
}
```

## Properties

### $material

The material of the mesh (can be null)

```php
/*
 * @var \GL\Geometry\ObjFileParser\Material|null
 */
public readonly ?Material $material;
```

### $vertices

A float buffer containing vertex data of the mesh. The layout of the data is not fixed but rather requested by the user.
Read more about the layout [here](/API/Geometry/ObjFileParser.html#getvertices).

```php
/*
 * @var \GL\Buffer\FloatBuffer
 */
public readonly FloatBuffer $vertices;
```

### $indices

A unsigned int buffer containing indices of the mesh. (optional)

```php
/*
 * @var \GL\Buffer\UIntBuffer|null
 */
public readonly ?UIntBuffer $indices;
```
