# glPolygonMode
select a polygon rasterization mode

```php
function glPolygonMode(int $face, int $mode) : void
```

arguments

:    1. `int` `$face` Specifies the polygons that mode applies to. Must be
    <constant>GL_FRONT_AND_BACK</constant> for front- and back-facing polygons.
    2. `int` `$mode` Specifies how polygons will be rasterized. Accepted values
    are <constant>GL_POINT</constant>, <constant>GL_LINE</constant>, and
    <constant>GL_FILL</constant>. The initial value is
    <constant>GL_FILL</constant> for both front- and back-facing polygons.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.