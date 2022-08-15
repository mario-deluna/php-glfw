# glFramebufferRenderbuffer
attach a renderbuffer as a logical buffer of a framebuffer object

```php
function glFramebufferRenderbuffer(int $target, int $attachment, int $renderbuffertarget, int $renderbuffer) : void
```



arguments

:    1. `int` `$target` Specifies the target to which the framebuffer is bound for
    glFramebufferRenderbuffer.
    2. `int` `$attachment` Specifies the attachment point of the framebuffer.
    3. `int` `$renderbuffertarget` Specifies the renderbuffer target. Must be
    <constant>GL_RENDERBUFFER</constant>.
    4. `int` `$renderbuffer` Specifies the name of an existing renderbuffer
    object of type renderbuffertarget to attach.



---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.