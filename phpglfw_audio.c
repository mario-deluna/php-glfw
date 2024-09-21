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
    maengine_conf.periodSizeInFrames = 4096;

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

static HashTable *phpglfw_audiosound_debug_info_handler(zend_object *object, int *is_temp)
{
    phpglfw_audiosound_object *obj_ptr = phpglfw_audiosound_from_zobj_p(object);
    zval zv;
    HashTable *ht;

    ht = zend_new_array(2);
    *is_temp = 1;

    // fetch data from the sound object
    ma_uint32 channels;
    ma_uint32 sample_rate;
    ma_sound_get_data_format(obj_ptr->masound, NULL, &channels, &sample_rate, NULL, 0);

    // add the data to the array
    ZVAL_LONG(&zv, channels);
    zend_hash_str_update(ht, "channels", sizeof("channels") - 1, &zv);

    ZVAL_LONG(&zv, sample_rate);
    zend_hash_str_update(ht, "sample_rate", sizeof("sample_rate") - 1, &zv);

    return ht;
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


PHP_METHOD(GL_Audio_Sound, setPosition)
{
    double x, y, z;
    if (zend_parse_parameters(ZEND_NUM_ARGS() , "ddd", &x, &y, &z) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_audiosound_object *intern = phpglfw_audiosound_from_zobj_p(Z_OBJ_P(getThis()));

    ma_sound_set_position(intern->masound, x, y, z);
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

/**
 * Module registration
 * 
 * ----------------------------------------------------------------------------
 */
void phpglfw_register_audio_module(INIT_FUNC_ARGS)
{
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
    // phpglfw_audiosound_object_handlers.get_debug_info = phpglfw_audiosound_debug_info_handler;

}