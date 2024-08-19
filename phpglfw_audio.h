/**
 * PHP-glfw 
 * 
 * Auido bindings for PHP-GLFW (miniaudio)
 *
 * Copyright (c) 2018-2024 Mario Döring
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
#ifndef PHP_GLFW_AUDIO_H
#define PHP_GLFW_AUDIO_H 1

#include "phpglfw_constants.h"

#include "miniaudio.h"

typedef struct _phpglfw_audioengine_object {
    ma_engine *maengine;
    zend_object std;
} phpglfw_audioengine_object; 

typedef struct _phpglfw_audiosound_object {
    ma_sound *masound;
    zend_object std;
} phpglfw_audiosound_object;

zend_class_entry *phpglfw_get_audioengine_ce();
zend_class_entry *phpglfw_get_audiosound_ce();

phpglfw_audioengine_object *phpglfw_audioengine_from_zobj_p(zend_object *obj);
phpglfw_audiosound_object *phpglfw_audiosound_from_zobj_p(zend_object *obj);

void phpglfw_register_audio_module(INIT_FUNC_ARGS);

#endif