---
title: ObjFileParser / Group
---

The Obj File Parser's Group class does not bring any new functionality to the table. It's just a container for index offsets that make up a group 
in an obj file.

```php 
namespace GL\Geometry\ObjFileParser
{
    class Group {}
}
```

## Properties

### $name

The name of the group or object

```php
/*
 * @var string|null
 */
public readonly ?string $name;
```

### $faceCount

The number of faces in the group

```php
/*
 * @var int
 */
public readonly int $faceCount;
```

### $faceOffset

The offset of the first face in the resource object

```php
/*
 * @var int
 */
public readonly int $faceOffset;
```

### $indexOffset

The offset of the first index in the resource object

```php
/*
 * @var int
 */
public readonly int $indexOffset;
```

