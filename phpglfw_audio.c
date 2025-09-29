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
#include "phpglfw_buffer.h"
#include "phpglfw_math.h"

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
    zval *options = NULL;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|a", &options) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audioengine_object *intern = phpglfw_audioengine_from_zobj_p(Z_OBJ_P(getThis()));

    // initialize the engine configuration with defaults
    ma_engine_config maengine_conf = ma_engine_config_init();

    // parse the options array if provided
    if (options != NULL && Z_TYPE_P(options) == IS_ARRAY) {
        zval *val;

        // listenerCount
        if ((val = zend_hash_str_find(Z_ARRVAL_P(options), "listenerCount", sizeof("listenerCount") - 1)) != NULL) {
            if (Z_TYPE_P(val) == IS_LONG) {
                ma_uint32 count = (ma_uint32)Z_LVAL_P(val);
                if (count >= 1 && count <= MA_ENGINE_MAX_LISTENERS) {
                    maengine_conf.listenerCount = count;
                } else {
                    zend_throw_error(NULL, "listenerCount must be between 1 and %d", MA_ENGINE_MAX_LISTENERS);
                    RETURN_THROWS();
                }
            }
        }

        // channels
        if ((val = zend_hash_str_find(Z_ARRVAL_P(options), "channels", sizeof("channels") - 1)) != NULL) {
            if (Z_TYPE_P(val) == IS_LONG) {
                maengine_conf.channels = (ma_uint32)Z_LVAL_P(val);
            }
        }

        // sampleRate
        if ((val = zend_hash_str_find(Z_ARRVAL_P(options), "sampleRate", sizeof("sampleRate") - 1)) != NULL) {
            if (Z_TYPE_P(val) == IS_LONG) {
                maengine_conf.sampleRate = (ma_uint32)Z_LVAL_P(val);
            }
        }

        // periodSizeInFrames
        if ((val = zend_hash_str_find(Z_ARRVAL_P(options), "periodSizeInFrames", sizeof("periodSizeInFrames") - 1)) != NULL) {
            if (Z_TYPE_P(val) == IS_LONG) {
                maengine_conf.periodSizeInFrames = (ma_uint32)Z_LVAL_P(val);
            }
        }

        // periodSizeInMilliseconds
        if ((val = zend_hash_str_find(Z_ARRVAL_P(options), "periodSizeInMilliseconds", sizeof("periodSizeInMilliseconds") - 1)) != NULL) {
            if (Z_TYPE_P(val) == IS_LONG) {
                maengine_conf.periodSizeInMilliseconds = (ma_uint32)Z_LVAL_P(val);
            }
        }

        // gainSmoothTimeInFrames
        if ((val = zend_hash_str_find(Z_ARRVAL_P(options), "gainSmoothTimeInFrames", sizeof("gainSmoothTimeInFrames") - 1)) != NULL) {
            if (Z_TYPE_P(val) == IS_LONG) {
                maengine_conf.gainSmoothTimeInFrames = (ma_uint32)Z_LVAL_P(val);
            }
        }

        // gainSmoothTimeInMilliseconds
        if ((val = zend_hash_str_find(Z_ARRVAL_P(options), "gainSmoothTimeInMilliseconds", sizeof("gainSmoothTimeInMilliseconds") - 1)) != NULL) {
            if (Z_TYPE_P(val) == IS_LONG) {
                maengine_conf.gainSmoothTimeInMilliseconds = (ma_uint32)Z_LVAL_P(val);
            }
        }

        // defaultVolumeSmoothTimeInPCMFrames
        if ((val = zend_hash_str_find(Z_ARRVAL_P(options), "defaultVolumeSmoothTimeInPCMFrames", sizeof("defaultVolumeSmoothTimeInPCMFrames") - 1)) != NULL) {
            if (Z_TYPE_P(val) == IS_LONG) {
                maengine_conf.defaultVolumeSmoothTimeInPCMFrames = (ma_uint32)Z_LVAL_P(val);
            }
        }

        // noAutoStart
        if ((val = zend_hash_str_find(Z_ARRVAL_P(options), "noAutoStart", sizeof("noAutoStart") - 1)) != NULL) {
            if (Z_TYPE_P(val) == IS_TRUE) {
                maengine_conf.noAutoStart = MA_TRUE;
            } else if (Z_TYPE_P(val) == IS_FALSE) {
                maengine_conf.noAutoStart = MA_FALSE;
            }
        }

        // monoExpansionMode
        if ((val = zend_hash_str_find(Z_ARRVAL_P(options), "monoExpansionMode", sizeof("monoExpansionMode") - 1)) != NULL) {
            if (Z_TYPE_P(val) == IS_LONG) {
                ma_uint32 mode = (ma_uint32)Z_LVAL_P(val);
                if (mode <= ma_mono_expansion_mode_stereo_only) {
                    maengine_conf.monoExpansionMode = (ma_mono_expansion_mode)mode;
                } else {
                    zend_throw_error(NULL, "Invalid monoExpansionMode value. Use GL_MA_MONO_EXPANSION_MODE_* constants");
                    RETURN_THROWS();
                }
            }
        }
    }

    ma_result result = ma_engine_init(&maengine_conf, intern->maengine);
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

    // update the sounds internal properties for the object (channels, sample rate, length)
    ma_uint32 channels;
    ma_uint32 sample_rate;
    ma_sound_get_data_format(sound_obj->masound, NULL, &channels, &sample_rate, NULL, 0);
    ma_uint64 pcm_length;
    ma_sound_get_length_in_pcm_frames(sound_obj->masound, &pcm_length);

    // we can calculate the length of the sound in seconds using the sample rate
    // miniaudio does the same internally, but this way we do not have to fetch the 
    // pcm length twice
    float length = (ma_int64)pcm_length / (float)sample_rate;

    zend_update_property_long(phpglfw_audiosound_ce, Z_OBJ_P(return_value), "channels", sizeof("channels") - 1, channels);
    zend_update_property_long(phpglfw_audiosound_ce, Z_OBJ_P(return_value), "sampleRate", sizeof("sampleRate") - 1, sample_rate);
    zend_update_property_double(phpglfw_audiosound_ce, Z_OBJ_P(return_value), "length", sizeof("length") - 1, length);
    zend_update_property_long(phpglfw_audiosound_ce, Z_OBJ_P(return_value), "lengthPCM", sizeof("lengthPCM") - 1, pcm_length);
}

PHP_METHOD(GL_Audio_Engine, setMasterVolume)
{
    double volume;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &volume) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audioengine_object *intern = phpglfw_audioengine_from_zobj_p(Z_OBJ_P(getThis()));

    ma_engine_set_volume(intern->maengine, (float) volume);
}

PHP_METHOD(GL_Audio_Engine, getMasterVolume)
{
    phpglfw_audioengine_object *intern = phpglfw_audioengine_from_zobj_p(Z_OBJ_P(getThis()));

    float volume = ma_engine_get_volume(intern->maengine);
    RETURN_DOUBLE(volume);
}

PHP_METHOD(GL_Audio_Engine, start)
{
    phpglfw_audioengine_object *intern = phpglfw_audioengine_from_zobj_p(Z_OBJ_P(getThis()));

    ma_result result = ma_engine_start(intern->maengine);
    if (result != MA_SUCCESS) {
        zend_throw_error(NULL, "GL\\Audio\\Engine Failed to start audio engine");
        RETURN_THROWS();
    }
}

PHP_METHOD(GL_Audio_Engine, stop)
{
    phpglfw_audioengine_object *intern = phpglfw_audioengine_from_zobj_p(Z_OBJ_P(getThis()));

    ma_result result = ma_engine_stop(intern->maengine);
    if (result != MA_SUCCESS) {
        zend_throw_error(NULL, "GL\\Audio\\Engine Failed to stop audio engine");
        RETURN_THROWS();
    }
}

PHP_METHOD(GL_Audio_Engine, setListenerPosition)
{
    zval *position_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &position_zval, phpglfw_get_math_vec3_ce()) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audioengine_object *intern = phpglfw_audioengine_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_math_vec3_object *position_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(position_zval));

    ma_engine_listener_set_position(intern->maengine, 0, position_ptr->data[0], position_ptr->data[1], position_ptr->data[2]);
}

PHP_METHOD(GL_Audio_Engine, setListenerDirection)
{
    zval *direction_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &direction_zval, phpglfw_get_math_vec3_ce()) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audioengine_object *intern = phpglfw_audioengine_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_math_vec3_object *direction_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(direction_zval));

    ma_engine_listener_set_direction(intern->maengine, 0, direction_ptr->data[0], direction_ptr->data[1], direction_ptr->data[2]);
}

PHP_METHOD(GL_Audio_Engine, setListenerWorldUp)
{
    zval *worldUp_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &worldUp_zval, phpglfw_get_math_vec3_ce()) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audioengine_object *intern = phpglfw_audioengine_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_math_vec3_object *worldUp_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(worldUp_zval));

    ma_engine_listener_set_world_up(intern->maengine, 0, worldUp_ptr->data[0], worldUp_ptr->data[1], worldUp_ptr->data[2]);
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

#define PHPGLFW_AUDIO_SOUND_PROP_GETTER(name, getter) \
    PHP_METHOD(GL_Audio_Sound, getter) \
    { \
        phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis())); \
        zval rv; \
        zval *value = zend_read_property(phpglfw_audiosound_ce, Z_OBJ_P(getThis()), #name, sizeof(#name) - 1, 0, &rv); \
        RETURN_ZVAL(value, 0, 0); \
    }

PHPGLFW_AUDIO_SOUND_PROP_GETTER(channels, getChannels)
PHPGLFW_AUDIO_SOUND_PROP_GETTER(sampleRate, getSampleRate)
PHPGLFW_AUDIO_SOUND_PROP_GETTER(length, getLength)
PHPGLFW_AUDIO_SOUND_PROP_GETTER(lengthPCM, getLengthPCM)

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

PHP_METHOD(GL_Audio_Sound, stop)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_sound_stop(intern->masound);
}

PHP_METHOD(GL_Audio_Sound, setStartMs)
{
    zend_long start;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &start) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_sound_set_start_time_in_milliseconds(intern->masound, (ma_uint64) start);
}

PHP_METHOD(GL_Audio_Sound, setStopMs)
{
    zend_long stop;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &stop) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_sound_set_stop_time_in_milliseconds(intern->masound, (ma_uint64) stop);
}

PHP_METHOD(GL_Audio_Sound, isPlaying)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    RETURN_BOOL(ma_sound_is_playing(intern->masound));
}

PHP_METHOD(GL_Audio_Sound, getCursor)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    float cursor;
    ma_sound_get_cursor_in_seconds(intern->masound, &cursor);
    RETURN_DOUBLE(cursor);
}


PHP_METHOD(GL_Audio_Sound, getCursorPCM)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_uint64 cursor;
    ma_sound_get_cursor_in_pcm_frames(intern->masound, &cursor);
    RETURN_LONG(cursor);
}

PHP_METHOD(GL_Audio_Sound, seekTo)
{
    double cursor;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &cursor) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    // we cannot actually seek to a given position in seconds, only in pcm frames
    // means we estimate the pcm frame from the given seconds
    ma_uint32 sample_rate;
    ma_sound_get_data_format(intern->masound, NULL, NULL, &sample_rate, NULL, 0);
    ma_uint64 frame = (ma_uint64)(cursor * sample_rate);
    ma_uint64 length;
    ma_sound_get_length_in_pcm_frames(intern->masound, &length);

    // sanity check the frame is within the bounds
    if (frame > length) {
        frame = length;
    }

    // seek to the frame
    ma_result result = ma_sound_seek_to_pcm_frame(intern->masound, frame);

    RETURN_BOOL(result == MA_SUCCESS);
}

PHP_METHOD(GL_Audio_Sound, seekToPCM)
{
    zend_long cursor;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "l", &cursor) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));
    ma_result result = ma_sound_seek_to_pcm_frame(intern->masound, (ma_uint64) cursor);

    RETURN_BOOL(result == MA_SUCCESS);
}

PHP_METHOD(GL_Audio_Sound, setVolume)
{
    double volume;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &volume) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_sound_set_volume(intern->masound, (float) volume);
}

PHP_METHOD(GL_Audio_Sound, setPitch)
{
    double pitch;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &pitch) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_sound_set_pitch(intern->masound, (float) pitch);
}

PHP_METHOD(GL_Audio_Sound, setLoop)
{
    zend_bool loop;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "b", &loop) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_sound_set_looping(intern->masound, loop);
}

PHP_METHOD(GL_Audio_Sound, setPosition)
{
    zval *position_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &position_zval, phpglfw_get_math_vec3_ce()) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_math_vec3_object *position_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(position_zval));

    ma_sound_set_position(intern->masound, position_ptr->data[0], position_ptr->data[1], position_ptr->data[2]);
}

PHP_METHOD(GL_Audio_Sound, getVolume)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    float volume = ma_sound_get_volume(intern->masound);
    RETURN_DOUBLE(volume);
}

PHP_METHOD(GL_Audio_Sound, getPitch)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    float pitch = ma_sound_get_pitch(intern->masound);
    RETURN_DOUBLE(pitch);
}

PHP_METHOD(GL_Audio_Sound, getLoop)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_bool32 loop = ma_sound_is_looping(intern->masound);
    RETURN_BOOL(loop);
}

PHP_METHOD(GL_Audio_Sound, setPan)
{
    double pan;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &pan) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_sound_set_pan(intern->masound, (float) pan);
}

PHP_METHOD(GL_Audio_Sound, getPan)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    float pan = ma_sound_get_pan(intern->masound);
    RETURN_DOUBLE(pan);
}

PHP_METHOD(GL_Audio_Sound, readFrames)
{
    zend_long frames;
    zval *frames_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "lO", &frames, &frames_zval, phpglfw_get_buffer_interface_ce()) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_format format;
    ma_uint32 channels;
    ma_uint32 sample_rate;
    ma_sound_get_data_format(intern->masound, &format, &channels, &sample_rate, NULL, 0);

    // fetching the length, depending on the decoder seems to require a full read
    // of the sound, which we already did when we loaded the sound
    // so we just fetch the length from the object, i guess this could cause issues as the length is a 64uint
    // and the php long is a 64bit signed int, ping me if something breaks and you end up here
    zval val;
    zval *length_zval = zend_read_property(phpglfw_audiosound_ce, Z_OBJ_P(getThis()), "lengthPCM", sizeof("lengthPCM") - 1, 0, &val);

    if (Z_TYPE_P(length_zval) != IS_LONG) {
        zend_throw_error(NULL, "How in the world did you manage to even get here?");
        RETURN_LONG(0);
    }

    ma_uint64 length = (ma_uint64) Z_LVAL_P(length_zval);

    zend_class_entry *required_ce = NULL;
    if (format == ma_format_f32) {
        required_ce = phpglfw_get_buffer_glfloat_ce();
    } else if (format == ma_format_s16) {
        required_ce = phpglfw_get_buffer_glshort_ce();
    } else if (format == ma_format_u8) {
        required_ce = phpglfw_get_buffer_glubyte_ce();
    } else {
        zend_throw_error(NULL, "The format of the sound is not supported");
        RETURN_LONG(0);
    }

    if (Z_OBJCE_P(frames_zval) != required_ce) {
        zend_throw_error(NULL, "The buffer must be of type %s", ZSTR_VAL(required_ce->name));
        RETURN_LONG(0);
    }

    // get the datasource
    ma_uint64 frames_read = 0;
    ma_data_source *source = intern->masound->pDataSource;
    ma_result result = MA_ERROR;

    if (required_ce == phpglfw_get_buffer_glfloat_ce()) {
        phpglfw_buffer_glfloat_object *obj_ptr = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(frames_zval));
        cvector_reserve(obj_ptr->vec, frames * channels);
        result = ma_data_source_read_pcm_frames(source, obj_ptr->vec, frames, &frames_read);
        cvector_set_size(obj_ptr->vec, frames_read * channels);
    } else if (required_ce == phpglfw_get_buffer_glshort_ce()) {
        phpglfw_buffer_glshort_object *obj_ptr = phpglfw_buffer_glshort_objectptr_from_zobj_p(Z_OBJ_P(frames_zval));
        cvector_reserve(obj_ptr->vec, frames * channels);
        result = ma_data_source_read_pcm_frames(source, obj_ptr->vec, frames, &frames_read);
        cvector_set_size(obj_ptr->vec, frames_read * channels);
    } else if (required_ce == phpglfw_get_buffer_glubyte_ce()) {
        phpglfw_buffer_glubyte_object *obj_ptr = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(frames_zval));
        cvector_reserve(obj_ptr->vec, frames * channels);
        result = ma_data_source_read_pcm_frames(source, obj_ptr->vec, frames, &frames_read);
        cvector_set_size(obj_ptr->vec, frames_read * channels);
    }

    if (result != MA_SUCCESS) {
        zend_throw_error(NULL, "Failed to read frames from sound");
        RETURN_LONG(0);
    }

    RETURN_LONG(frames_read);
}

PHP_METHOD(GL_Audio_Sound, getPosition)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_vec3f position = ma_sound_get_position(intern->masound);
    
    object_init_ex(return_value, phpglfw_get_math_vec3_ce());
    phpglfw_math_vec3_object *result_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    result_ptr->data[0] = position.x;
    result_ptr->data[1] = position.y;
    result_ptr->data[2] = position.z;
}

PHP_METHOD(GL_Audio_Sound, setMinDistance)
{
    double min_distance;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &min_distance) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));
    ma_sound_set_min_distance(intern->masound, (float) min_distance);
}

PHP_METHOD(GL_Audio_Sound, getMinDistance)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));
    float min_distance = ma_sound_get_min_distance(intern->masound);
    RETURN_DOUBLE(min_distance);
}

PHP_METHOD(GL_Audio_Sound, setMaxDistance)
{
    double max_distance;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &max_distance) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));
    ma_sound_set_max_distance(intern->masound, (float) max_distance);
}

PHP_METHOD(GL_Audio_Sound, getMaxDistance)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));
    float max_distance = ma_sound_get_max_distance(intern->masound);
    RETURN_DOUBLE(max_distance);
}

PHP_METHOD(GL_Audio_Sound, setDirection)
{
    zval *direction_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &direction_zval, phpglfw_get_math_vec3_ce()) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_math_vec3_object *direction_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(direction_zval));

    ma_sound_set_direction(intern->masound, direction_ptr->data[0], direction_ptr->data[1], direction_ptr->data[2]);
}

PHP_METHOD(GL_Audio_Sound, getDirection)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_vec3f direction = ma_sound_get_direction(intern->masound);
    
    object_init_ex(return_value, phpglfw_get_math_vec3_ce());
    phpglfw_math_vec3_object *result_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    result_ptr->data[0] = direction.x;
    result_ptr->data[1] = direction.y;
    result_ptr->data[2] = direction.z;
}

PHP_METHOD(GL_Audio_Sound, setVelocity)
{
    zval *velocity_zval;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "O", &velocity_zval, phpglfw_get_math_vec3_ce()) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_math_vec3_object *velocity_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(velocity_zval));

    ma_sound_set_velocity(intern->masound, velocity_ptr->data[0], velocity_ptr->data[1], velocity_ptr->data[2]);
}

PHP_METHOD(GL_Audio_Sound, getVelocity)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_vec3f velocity = ma_sound_get_velocity(intern->masound);
    
    object_init_ex(return_value, phpglfw_get_math_vec3_ce());
    phpglfw_math_vec3_object *result_ptr = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    result_ptr->data[0] = velocity.x;
    result_ptr->data[1] = velocity.y;
    result_ptr->data[2] = velocity.z;
}

PHP_METHOD(GL_Audio_Sound, fadeIn)
{
    double duration;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &duration) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));
    
    float currentvol = ma_sound_get_current_fade_volume(intern->masound);
    
    // for simplicity sake we use a float from php userland, so we convert seconds to milliseconds here
    ma_uint64 duration_ms = (ma_uint64)(duration * 1000.0);
    ma_sound_set_fade_in_milliseconds(intern->masound, currentvol, 1.0f, duration_ms);
}

PHP_METHOD(GL_Audio_Sound, fadeOut)
{
    double duration;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "d", &duration) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));
    
    float currentvol = ma_sound_get_current_fade_volume(intern->masound);
    
    // same here, convert seconds to milliseconds
    ma_uint64 duration_ms = (ma_uint64)(duration * 1000.0);
    ma_sound_set_fade_in_milliseconds(intern->masound, currentvol, 0.0f, duration_ms);
}

PHP_METHOD(GL_Audio_Sound, setFade)
{
    double fromVolume, toVolume, duration;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddd", &fromVolume, &toVolume, &duration) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));
    
    ma_uint64 duration_ms = (ma_uint64)(duration * 1000.0);
    ma_sound_set_fade_in_milliseconds(intern->masound, (float)fromVolume, (float)toVolume, duration_ms);
}

PHP_METHOD(GL_Audio_Sound, getCurrentFadeVolume)
{
    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));
    float fadeVolume = ma_sound_get_current_fade_volume(intern->masound);
    RETURN_DOUBLE(fadeVolume);
}

/**
 * Module registration
 * 
 * ----------------------------------------------------------------------------
 */
void phpglfw_register_audio_module(INIT_FUNC_ARGS)
{
    // register mono expansion mode constants
    REGISTER_LONG_CONSTANT("GL_MA_MONO_EXPANSION_MODE_DUPLICATE", ma_mono_expansion_mode_duplicate, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("GL_MA_MONO_EXPANSION_MODE_AVERAGE", ma_mono_expansion_mode_average, CONST_CS|CONST_PERSISTENT);
    REGISTER_LONG_CONSTANT("GL_MA_MONO_EXPANSION_MODE_STEREO_ONLY", ma_mono_expansion_mode_stereo_only, CONST_CS|CONST_PERSISTENT);

    // init & register the audio engine class
    phpglfw_audioengine_ce = register_class_GL_Audio_Engine();
    phpglfw_audioengine_ce->create_object = phpglfw_audioengine_create_object;

    memcpy(&phpglfw_audioengine_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    phpglfw_audioengine_object_handlers.offset = XtOffsetOf(phpglfw_audioengine_object, std);
    phpglfw_audioengine_object_handlers.free_obj = phpglfw_audioengine_free_handler;

    // sound class
    phpglfw_audiosound_ce = register_class_GL_Audio_Sound();
    phpglfw_audiosound_ce->create_object = phpglfw_audiosound_create_object;

    memcpy(&phpglfw_audiosound_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    phpglfw_audiosound_object_handlers.offset = XtOffsetOf(phpglfw_audiosound_object, std);
    phpglfw_audiosound_object_handlers.free_obj = phpglfw_audiosound_free_handler;

}