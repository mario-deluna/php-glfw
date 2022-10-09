---
title: ObjFileParser / Material
---

The Obj File Parser's Material class does not bring any new functionality to the table. It's just a container for the material properties that can be defined in an obj file.

```php 
namespace GL\Geometry\ObjFileParser
{
    class Material {}
}
```

## Properties

### $name

The name of the material. (marked as "newmtl") 
This is the same name you use in a 3D modelling software like Blender or 3DS Max to reference the material.

```php
/*
 * @var string
 */
public readonly string $name;
```

### $ambient

The ambient color of the material. (marked as "Ka")
This usally controls the color of the object in the shadow or when a light is not directly hitting the object.

```php
/*
 * @var \GL\Math\Vec3
 */
public readonly Vec3 $ambient;
```

### $diffuse

The diffuse color of the material. (marked as "Kd")
This usally controls the color of the object when a light is directly hitting the object.
This property is often also used for albedo or base color.

```php
/*
 * @var \GL\Math\Vec3
 */
public readonly Vec3 $diffuse;
```

### $specular

The specular color of the material. (marked as "Ks")
This property is often also used for reflection color, shininess or highlights color.

```php
/*
 * @var \GL\Math\Vec3
 */
public readonly Vec3 $specular;
```

### $emmisive

The emmisive color of the material. (marked as "Ke")
This property is often also used for illumination, self glow or light emission.

```php
/*
 * @var \GL\Math\Vec3
 */
public readonly Vec3 $emmisive;
```

### $transmittance

The transmittance of the material. (marked as "Tf")
This property is often also used for transparency or refraction color.

```php
/*
 * @var \GL\Math\Vec3
 */
public readonly Vec3 $transmittance;
```

### $transmissionFilter

The transmission filter color property of the Material. (marked as "Tf")
This property is often also used for transparency or refraction color.

```php
/*
 * @var \GL\Math\Vec3
 */
public readonly Vec3 $transmissionFilter;
```

### $shininess

The shininess of the material. (marked as "Ns")
This property is often also used for glossiness or specular power.

```php
/*
 * @var float
 */
public readonly float $shininess;
```

### $indexOfRefraction

The index of refraction of the materials. (marked as "Ni")

```php
/*
 * @var float
 */
public readonly float $indexOfRefraction;
```

### $dissolve

The dissolve of the material. (marked as "d")
This property is often also used for opacity or transparency.

```php
/*
 * @var float
 */
public readonly float $dissolve;
```

### $illuminationModel

The illumination model of the material. (marked as "illum")

from the obj file specification:

0. Color on and Ambient off
1. Color on and Ambient on
2. Highlight on
3. Reflection on and Ray trace on
4. Transparency: Glass on, Reflection: Ray trace on
5. Reflection: Fresnel on and Ray trace on
6. Transparency: Refraction on, Reflection: Fresnel off and Ray trace on
7. Transparency: Refraction on, Reflection: Fresnel on and Ray trace on
8. Reflection on and Ray trace off
9. Transparency: Glass on, Reflection: Ray trace off
10. Casts shadows onto invisible surfaces

```php
/*
 * @var int
 */
public readonly int $illuminationModel;
```

### $ambientTexture

The ambient texture of the material. (marked as "map_Ka")

```php
/*
 * @var \GL\Geometry\ObjFileParser\Texture
 */
public readonly Texture $ambientTexture;
```

### $diffuseTexture

The diffuse texture of the material. (marked as "map_Kd")

```php
/*
 * @var \GL\Geometry\ObjFileParser\Texture
 */
public readonly Texture $diffuseTexture;
```

### $specularTexture

The specular texture of the material. (marked as "map_Ks")

```php
/*
 * @var \GL\Geometry\ObjFileParser\Texture
 */
public readonly Texture $specularTexture;
```

### $emissiveTexture

The emissive texture of the material. (marked as "map_Ke")

```php
/*
 * @var \GL\Geometry\ObjFileParser\Texture
 */
public readonly Texture $emissiveTexture;
```

### $transmittanceTexture

The transmittance texture of the material. (marked as "map_Tf")

```php
/*
 * @var \GL\Geometry\ObjFileParser\Texture
 */
public readonly Texture $transmittanceTexture;
```

### $shininessTexture

The shininess texture of the material. (marked as "map_Ns")

```php
/*
 * @var \GL\Geometry\ObjFileParser\Texture
 */
public readonly Texture $shininessTexture;
```

### $indexOfRefractionTexture

The index of refraction texture of the material. (marked as "map_Ni")

```php
/*
 * @var \GL\Geometry\ObjFileParser\Texture
 */
public readonly Texture $indexOfRefractionTexture;
```

### $dissolveTexture

The dissolve texture of the material. (marked as "map_d")

```php
/*
 * @var \GL\Geometry\ObjFileParser\Texture
 */
public readonly Texture $dissolveTexture;
```

### $bumpTexture

The bump texture of the material. (marked as "map_bump")

```php
/*
 * @var \GL\Geometry\ObjFileParser\Texture
 */
public readonly Texture $bumpTexture;
```



