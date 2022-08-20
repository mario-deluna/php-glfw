# glFramebufferTexture
attach a level of a texture object as a logical buffer of a framebuffer
object

```php
function glFramebufferTexture(int $target, int $attachment, int $texture, int $level) : void
```

arguments

:    1. `int` `$target` Specifies the target to which the framebuffer is bound for
    all commands except glNamedFramebufferTexture.
    2. `int` `$attachment` Specifies the attachment point of the framebuffer.
    3. `int` `$texture` Specifies the name of an existing texture object to
    attach.
    4. `int` `$level` Specifies the mipmap level of the texture object to attach.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.