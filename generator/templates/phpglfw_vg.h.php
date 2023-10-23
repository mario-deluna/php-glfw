/**
 * PHP-glfw 
 * 
 * Vector Graphics (powered by NanoVG)
 *
 * Copyright (c) 2018-2023 Mario Döring
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef PHP_GLFW_VG_H
#define PHP_GLFW_VG_H 1

#include "phpglfw_constants.h"
#include "nanovg.h"

/**
 * NanoVG object wrappers
 */
typedef struct _phpglfw_vgcontext_object {
    NVGcontext* nvgctx;
    zend_object std;
} phpglfw_vgcontext_object; 

typedef struct _phpglfw_vgpaint_object {
    NVGpaint nvgpaint;
    zend_object std;
} phpglfw_vgpaint_object;

typedef struct _phpglfw_vgimage_object {
    int nvgimage_handle;
    zend_object std;
} phpglfw_vgimage_object;

typedef struct _phpglfw_vgcolor_object {
    NVGcolor nvgcolor;
    zend_object std;
} phpglfw_vgcolor_object;

zend_class_entry *phpglfw_get_vg_vgcontext_ce();
zend_class_entry *phpglfw_get_vg_vgpaint_ce();
zend_class_entry *phpglfw_get_vg_vgimage_ce();
zend_class_entry *phpglfw_get_vg_vgcolor_ce(); 

phpglfw_vgcontext_object* phpglfw_vgcontext_objectptr_from_zobj_p(zend_object* obj);
phpglfw_vgpaint_object* phpglfw_vgpaint_objectptr_from_zobj_p(zend_object* obj);
phpglfw_vgimage_object* phpglfw_vgimage_objectptr_from_zobj_p(zend_object* obj);
phpglfw_vgcolor_object* phpglfw_vgcolor_objectptr_from_zobj_p(zend_object* obj);

void phpglfw_register_vg_module(INIT_FUNC_ARGS);

#endif
