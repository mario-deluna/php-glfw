# glScissor
define the scissor box

```php
function glScissor(int $x, int $y, int $width, int $height) : void
```

arguments

:    1. `int` `$x` Specify the lower left corner of the scissor box. Initially (0,
    0).
    2. `int` `$y` 
    3. `int` `$width` Specify the width and height of the scissor box. When a GL
    context is first attached to a window, width and height are set to the
    dimensions of that window.
    4. `int` `$height` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.