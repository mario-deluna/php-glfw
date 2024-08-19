/**
 * PHP-glfw 
 * 
 * Extension: Audio
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
#include "phpglfw_audio.h"
#include "phpglfw_arginfo.h"

#include "php.h"
#include "Zend/zend_smart_str.h"
#include "ext/standard/info.h"
#include "ext/standard/php_var.h"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

zend_class_entry *phpglfw_audioengine_ce;
zend_class_entry *phpglfw_audiosound_ce;

zend_class_entry *phpglfw_get_audioengine_ce()
{
    return phpglfw_audioengine_ce;
}

zend_class_entry *phpglfw_get_audiosound_ce()
{
    return phpglfw_audiosound_ce;
}

zend_always_inline phpglfw_audioengine_object *phpglfw_audioengine_from_zobj_p(zend_object *obj)
{
    return (phpglfw_audioengine_object*)((char*)(obj) - XtOffsetOf(phpglfw_audioengine_object, std));
}

zend_always_inline phpglfw_audiosound_object *phpglfw_audiosound_from_zobj_p(zend_object *obj)
{
    return (phpglfw_audiosound_object*)((char*)(obj) - XtOffsetOf(phpglfw_audiosound_object, std));
}

static zend_object_handlers phpglfw_audioengine_object_handlers;
static zend_object_handlers phpglfw_audiosound_object_handlers;

/**
 * Audio\Engine
 * 
 * ----------------------------------------------------------------------------
 */
zend_object *phpglfw_audioengine_create_object(zend_class_entry *class_type)
{
    phpglfw_audioengine_object *intern;
    intern = zend_object_alloc(sizeof(phpglfw_audioengine_object), class_type);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &phpglfw_audioengine_object_handlers;
    intern->maengine = malloc(sizeof(*intern->maengine));

    return &intern->std;
}

static void phpglfw_audioengine_free_handler(zend_object *object)
{
    phpglfw_audioengine_object *intern = phpglfw_audioengine_from_zobj_p(object);

    if (intern->maengine != NULL) {
        ma_engine_uninit(intern->maengine);
        free(intern->maengine);
    }

    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(GL_Audio_Engine, __construct)
{
    phpglfw_audioengine_object *intern = phpglfw_audioengine_from_zobj_p(Z_OBJ_P(getThis()));

    ma_engine_config maengine_conf;

    ma_result result = ma_engine_init(NULL, intern->maengine);
    if (result != MA_SUCCESS) {
        zend_throw_error(NULL, "GL\\Audio\\Engine Failed to initialize audio engine");
        RETURN_THROWS();
    }
}

PHP_METHOD(GL_Audio_Engine, soundFromDisk)
{
    const char *path;
    size_t path_len;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "s", &path, &path_len) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audioengine_object *intern = phpglfw_audioengine_from_zobj_p(Z_OBJ_P(getThis()));

    object_init_ex(return_value, phpglfw_get_audiosound_ce());
    phpglfw_audiosound_object *sound_obj = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(return_value));

    ma_result result = ma_sound_init_from_file(intern->maengine, path, 0, NULL, NULL, sound_obj->masound);
    if (result != MA_SUCCESS) {
        zend_throw_error(NULL, "GL\\Audio\\Engine Failed to load sound '%s' from disk", path);
        RETURN_THROWS();
    }
}

/**
 * Audio\Sound
 * 
 * ----------------------------------------------------------------------------
 */
zend_object *phpglfw_audiosound_create_object(zend_class_entry *class_type)
{
    phpglfw_audiosound_object *intern;
    intern = zend_object_alloc(sizeof(phpglfw_audiosound_object), class_type);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &phpglfw_audiosound_object_handlers;
    intern->masound = malloc(sizeof(*intern->masound));

    return &intern->std;
}

static void phpglfw_audiosound_free_handler(zend_object *object)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(object);

    if (intern->masound != NULL) {
        ma_sound_uninit(intern->masound);
        free(intern->masound);
    }

    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(GL_Audio_Sound, __construct)
{
    zend_throw_error(NULL, "GL\\Audio\\Sound is not constructable, please use GL\\Audio\\Engine::soundFromDisk");
    RETURN_THROWS();
}

PHP_METHOD(GL_Audio_Sound, play)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_sound_start(intern->masound);
}

PHP_METHOD(GL_Audio_Sound, setPosition)
{
    double x, y, z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddd", &x, &y, &z) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_sound_set_position(intern->masound, x, y, z);
}

/**
 * Module registration
 * 
 * ----------------------------------------------------------------------------
 */
void phpglfw_register_audio_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;

    // init & register the audio engine class
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Audio\\Engine", class_GL_Audio_Engine_methods);
    phpglfw_audioengine_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_audioengine_ce->create_object = phpglfw_audioengine_create_object;

    memcpy(&phpglfw_audioengine_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    phpglfw_audioengine_object_handlers.offset = XtOffsetOf(phpglfw_audioengine_object, std);
    phpglfw_audioengine_object_handlers.free_obj = phpglfw_audioengine_free_handler;

    // sound class
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Audio\\Sound", class_GL_Audio_Sound_methods);
    phpglfw_audiosound_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_audiosound_ce->create_object = phpglfw_audiosound_create_object;

    memcpy(&phpglfw_audiosound_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    phpglfw_audiosound_object_handlers.offset = XtOffsetOf(phpglfw_audiosound_object, std);
    phpglfw_audiosound_object_handlers.free_obj = phpglfw_audiosound_free_handler;

}