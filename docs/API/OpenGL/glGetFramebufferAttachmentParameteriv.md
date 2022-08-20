# glGetFramebufferAttachmentParameteriv
retrieve information about attachments of a framebuffer object

```php
function glGetFramebufferAttachmentParameteriv(int $target, int $attachment, int $pname, int &$params) : void
```

arguments

:    1. `int` `$target` Specifies the target to which the framebuffer object is
    bound for glGetFramebufferAttachmentParameteriv.
    2. `int` `$attachment` Specifies the attachment of the framebuffer object to
    query.
    3. `int` `$pname` Specifies the parameter of attachment to query.
    4. `int` `$params` Returns the value of parameter pname for attachment.

returns

:    `void` 

---
     

!!! cite "Copyright © 2010-2014 Khronos Group"

    This material may be distributed subject to the terms and conditions set forth in the Open Publication License, v 1.0, 8 June 1999. https://opencontent.org/openpub/.