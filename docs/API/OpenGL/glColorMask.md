# glColorMask
enable and disable writing of frame buffer color components

```php
function glColorMask(bool $red, bool $green, bool $blue, bool $alpha) : void
```

arguments

:    1. `bool` `$red` Specify whether red, green, blue, and alpha are to be
    written into the frame buffer. The initial values are all
    <constant>GL_TRUE</constant>, indicating that the color components are
    written.
    2. `bool` `$green` 
    3. `bool` `$blue` 
    4. `bool` `$alpha` 

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.