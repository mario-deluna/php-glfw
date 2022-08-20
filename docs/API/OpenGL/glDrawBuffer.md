# glDrawBuffer
specify which color buffers are to be drawn into

```php
function glDrawBuffer(int $buf) : void
```

arguments

:    1. `int` `$buf` For default framebuffer, the argument specifies up to four
    color buffers to be drawn into. Symbolic constants
    <constant>GL_NONE</constant>, <constant>GL_FRONT_LEFT</constant>,
    <constant>GL_FRONT_RIGHT</constant>, <constant>GL_BACK_LEFT</constant>,
    <constant>GL_BACK_RIGHT</constant>, <constant>GL_FRONT</constant>,
    <constant>GL_BACK</constant>, <constant>GL_LEFT</constant>,
    <constant>GL_RIGHT</constant>, and <constant>GL_FRONT_AND_BACK</constant> are
    accepted. The initial value is <constant>GL_FRONT</constant> for
    single-buffered contexts, and <constant>GL_BACK</constant> for
    double-buffered contexts. For framebuffer objects,
    <constant>GL_COLOR_ATTACHMENT$m$</constant> and <constant>GL_NONE</constant>
    enums are accepted, where <constant>$m$</constant> is a value between 0 and
    <constant>GL_MAX_COLOR_ATTACHMENTS</constant>.

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.