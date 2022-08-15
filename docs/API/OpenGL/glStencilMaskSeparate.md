# glStencilMaskSeparate
control the front and/or back writing of individual bits in the stencil
planes

```php
function glStencilMaskSeparate(int $face, int $mask) : void
```



arguments

:    1. `int` `$face` Specifies whether the front and/or back stencil writemask is
    updated. Three symbolic constants are valid: <constant>GL_FRONT</constant>,
    <constant>GL_BACK</constant>, and <constant>GL_FRONT_AND_BACK</constant>.
    2. `int` `$mask` Specifies a bit mask to enable and disable writing of
    individual bits in the stencil planes. Initially, the mask is all 1's.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.