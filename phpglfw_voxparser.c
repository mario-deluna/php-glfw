/**
 * PHP-glfw 
 * 
 * Extension: Vox File Parser
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
#include "phpglfw_voxparser.h"
#include "phpglfw_arginfo.h"
#include "phpglfw_buffer.h"
#include "phpglfw_math.h"
#include "php_streams.h"

#include <stdbool.h>
#include <string.h>

#define PHPGLFW_VOX_PALETTE_LENGTH 256u
#define PHPGLFW_VOX_PALETTE_COMPONENTS (PHPGLFW_VOX_PALETTE_LENGTH * 4u)
#define PHPGLFW_VOX_PALETTE_BYTES (PHPGLFW_VOX_PALETTE_COMPONENTS * sizeof(uint8_t))

static const zend_function_entry phpglfw_empty_function_entries[] = { ZEND_FE_END };

phpglfw_voxparser_resource_object* phpglfw_voxparser_res_objectptr_from_zobj_p(zend_object* obj);
phpglfw_voxparser_model_object* phpglfw_voxparser_model_objectptr_from_zobj_p(zend_object* obj);
phpglfw_voxparser_instance_object* phpglfw_voxparser_instance_objectptr_from_zobj_p(zend_object* obj);
phpglfw_voxparser_layer_object* phpglfw_voxparser_layer_objectptr_from_zobj_p(zend_object* obj);
phpglfw_voxparser_group_object* phpglfw_voxparser_group_objectptr_from_zobj_p(zend_object* obj);
phpglfw_voxparser_palette_object* phpglfw_voxparser_palette_objectptr_from_zobj_p(zend_object* obj);

void phpglfw_voxparser_transform_to_mat4(zval *mat4_zval, const ogt_vox_transform_c *transform);
phpglfw_buffer_glubyte_object *phpglfw_voxparser_palette_ensure_buffer(phpglfw_voxparser_palette_object *palette_intern);
void phpglfw_voxparser_palette_prepare_buffer(phpglfw_buffer_glubyte_object *buffer_intern);
void phpglfw_voxparser_palette_copy_from_rgba(phpglfw_buffer_glubyte_object *buffer_intern, const ogt_vox_rgba_c *rgba);
zend_bool phpglfw_voxparser_palette_extract_color(zval *color_zval, uint8_t *rgba_out);
uint8_t phpglfw_vox_float_to_byte(double value);

zend_class_entry *phpglfw_voxparser_res_ce;
zend_class_entry *phpglfw_voxparser_ce;
zend_class_entry *phpglfw_voxparser_palette_ce;
zend_class_entry *phpglfw_voxparser_model_ce;
zend_class_entry *phpglfw_voxparser_instance_ce;
zend_class_entry *phpglfw_voxparser_layer_ce;
zend_class_entry *phpglfw_voxparser_group_ce;

static zend_object_handlers phpglfw_voxparser_res_handlers;
static zend_object_handlers phpglfw_voxparser_palette_handlers;
static zend_object_handlers phpglfw_voxparser_model_handlers;
static zend_object_handlers phpglfw_voxparser_instance_handlers;
static zend_object_handlers phpglfw_voxparser_layer_handlers;
static zend_object_handlers phpglfw_voxparser_group_handlers;

typedef enum {
    PHPGLFW_VOX_MESH_MODE_SIMPLE = 0,
    PHPGLFW_VOX_MESH_MODE_GREEDY = 1,
    PHPGLFW_VOX_MESH_MODE_POLYGON = 2
} phpglfw_vox_mesh_mode;

uint8_t phpglfw_vox_float_to_byte(double value)
{
    if (value < 0.0) return 0;
    if (value > 1.0) return 255;
    return (uint8_t)(value * 255.0 + 0.5);
}

static const ogt_vox_rgba_c* phpglfw_vox_default_palette(void)
{
    static ogt_vox_rgba_c palette[256];
    static bool initialized = false;

    if (!initialized) {
        for (int i = 0; i < 256; i++) {
            palette[i].r = (uint8_t) i;
            palette[i].g = (uint8_t) i;
            palette[i].b = (uint8_t) i;
            palette[i].a = 255;
        }
        initialized = true;
    }

    return palette;
}

static zend_bool phpglfw_vox_mesh_mode_from_zval(zval *mode_zval, phpglfw_vox_mesh_mode *out_mode)
{
    if (!mode_zval || !out_mode) {
        return 0;
    }

    switch (Z_TYPE_P(mode_zval)) {
        case IS_LONG:
            if (Z_LVAL_P(mode_zval) == PHPGLFW_VOX_MESH_MODE_SIMPLE) {
                *out_mode = PHPGLFW_VOX_MESH_MODE_SIMPLE;
                return 1;
            }
            if (Z_LVAL_P(mode_zval) == PHPGLFW_VOX_MESH_MODE_GREEDY) {
                *out_mode = PHPGLFW_VOX_MESH_MODE_GREEDY;
                return 1;
            }
            if (Z_LVAL_P(mode_zval) == PHPGLFW_VOX_MESH_MODE_POLYGON) {
                *out_mode = PHPGLFW_VOX_MESH_MODE_POLYGON;
                return 1;
            }
            return 0;
        case IS_STRING:
            if (zend_string_equals_literal_ci(Z_STR_P(mode_zval), "simple")) {
                *out_mode = PHPGLFW_VOX_MESH_MODE_SIMPLE;
                return 1;
            }
            if (zend_string_equals_literal_ci(Z_STR_P(mode_zval), "greedy")) {
                *out_mode = PHPGLFW_VOX_MESH_MODE_GREEDY;
                return 1;
            }
            if (zend_string_equals_literal_ci(Z_STR_P(mode_zval), "polygon") || zend_string_equals_literal_ci(Z_STR_P(mode_zval), "polygons")) {
                *out_mode = PHPGLFW_VOX_MESH_MODE_POLYGON;
                return 1;
            }
            return 0;
        default:
            break;
    }

    return 0;
}

static zend_object *phpglfw_voxparser_layer_create_handler(zend_class_entry *class_type)
{
    phpglfw_voxparser_layer_object *intern = zend_object_alloc(sizeof(phpglfw_voxparser_layer_object), class_type);
    intern->resource = NULL;
    ZVAL_UNDEF(&intern->resource_zval);
    memset(&intern->layer, 0, sizeof(ogt_vox_layer_c));
    intern->index = 0;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_voxparser_layer_handlers;

    return &intern->std;
}

static void phpglfw_voxparser_layer_free_handler(zend_object *object)
{
    phpglfw_voxparser_layer_object *intern = phpglfw_voxparser_layer_objectptr_from_zobj_p(object);

    if (!Z_ISUNDEF(intern->resource_zval)) {
        zval_ptr_dtor(&intern->resource_zval);
        ZVAL_UNDEF(&intern->resource_zval);
    }

    zend_object_std_dtor(&intern->std);
}

static zend_object *phpglfw_voxparser_group_create_handler(zend_class_entry *class_type)
{
    phpglfw_voxparser_group_object *intern = zend_object_alloc(sizeof(phpglfw_voxparser_group_object), class_type);
    intern->resource = NULL;
    ZVAL_UNDEF(&intern->resource_zval);
    memset(&intern->group, 0, sizeof(ogt_vox_group_c));
    memset(&intern->transform_global, 0, sizeof(ogt_vox_transform_c));
    memset(&intern->transform_local, 0, sizeof(ogt_vox_transform_c));
    intern->has_transforms = 0;
    intern->index = 0;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_voxparser_group_handlers;

    return &intern->std;
}

static void phpglfw_voxparser_group_free_handler(zend_object *object)
{
    phpglfw_voxparser_group_object *intern = phpglfw_voxparser_group_objectptr_from_zobj_p(object);

    if (!Z_ISUNDEF(intern->resource_zval)) {
        zval_ptr_dtor(&intern->resource_zval);
        ZVAL_UNDEF(&intern->resource_zval);
    }

    zend_object_std_dtor(&intern->std);
}

static zend_object *phpglfw_voxparser_palette_create_handler(zend_class_entry *class_type)
{
    phpglfw_voxparser_palette_object *intern = zend_object_alloc(sizeof(phpglfw_voxparser_palette_object), class_type);
    intern->buffer = NULL;
    ZVAL_UNDEF(&intern->buffer_zval);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_voxparser_palette_handlers;

    return &intern->std;
}

static void phpglfw_voxparser_palette_free_handler(zend_object *object)
{
    phpglfw_voxparser_palette_object *intern = phpglfw_voxparser_palette_objectptr_from_zobj_p(object);

    if (!Z_ISUNDEF(intern->buffer_zval)) {
        zval_ptr_dtor(&intern->buffer_zval);
        ZVAL_UNDEF(&intern->buffer_zval);
    }

    intern->buffer = NULL;

    zend_object_std_dtor(&intern->std);
}

static zend_object *phpglfw_voxparser_res_create_handler(zend_class_entry *class_type)
{
    phpglfw_voxparser_resource_object *intern = zend_object_alloc(sizeof(phpglfw_voxparser_resource_object), class_type);
    intern->scene = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_voxparser_res_handlers;

    return &intern->std;
}

static void phpglfw_geometry_voxparser_res_free_handler(zend_object *object)
{
    phpglfw_voxparser_resource_object *intern = phpglfw_voxparser_res_objectptr_from_zobj_p(object);

    if (intern->scene) {
        ogt_vox_destroy_scene_c(intern->scene);
        intern->scene = NULL;
    }

    zend_object_std_dtor(&intern->std);
}

static zend_object *phpglfw_voxparser_model_create_handler(zend_class_entry *class_type)
{
    phpglfw_voxparser_model_object *intern = zend_object_alloc(sizeof(phpglfw_voxparser_model_object), class_type);
    intern->resource = NULL;
    ZVAL_UNDEF(&intern->resource_zval);
    memset(&intern->model, 0, sizeof(ogt_vox_model_c));
    intern->index = 0;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_voxparser_model_handlers;

    return &intern->std;
}

static void phpglfw_voxparser_model_free_handler(zend_object *object)
{
    phpglfw_voxparser_model_object *intern = phpglfw_voxparser_model_objectptr_from_zobj_p(object);

    if (!Z_ISUNDEF(intern->resource_zval)) {
        zval_ptr_dtor(&intern->resource_zval);
        ZVAL_UNDEF(&intern->resource_zval);
    }

    zend_object_std_dtor(&intern->std);
}

static zend_object *phpglfw_voxparser_instance_create_handler(zend_class_entry *class_type)
{
    phpglfw_voxparser_instance_object *intern = zend_object_alloc(sizeof(phpglfw_voxparser_instance_object), class_type);
    intern->resource = NULL;
    ZVAL_UNDEF(&intern->resource_zval);
    memset(&intern->instance, 0, sizeof(ogt_vox_instance_c));
    memset(&intern->transform_global, 0, sizeof(ogt_vox_transform_c));
    memset(&intern->transform_local, 0, sizeof(ogt_vox_transform_c));
    intern->has_transforms = 0;
    intern->index = 0;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_voxparser_instance_handlers;

    return &intern->std;
}

static void phpglfw_voxparser_instance_free_handler(zend_object *object)
{
    phpglfw_voxparser_instance_object *intern = phpglfw_voxparser_instance_objectptr_from_zobj_p(object);

    if (!Z_ISUNDEF(intern->resource_zval)) {
        zval_ptr_dtor(&intern->resource_zval);
        ZVAL_UNDEF(&intern->resource_zval);
    }

    zend_object_std_dtor(&intern->std);
}

void create_models_phparray(zval *array_zval, const ogt_vox_scene_wrapper* scene, unsigned int model_count, zval *resource_zval)
{
    phpglfw_voxparser_resource_object *resource_obj = NULL;
    if (resource_zval && Z_TYPE_P(resource_zval) == IS_OBJECT && instanceof_function(Z_OBJCE_P(resource_zval), phpglfw_voxparser_res_ce)) {
        resource_obj = phpglfw_voxparser_res_objectptr_from_zobj_p(Z_OBJ_P(resource_zval));
    }

    ZVAL_EMPTY_ARRAY(array_zval);
    HashTable *ht = zend_new_array(model_count);
    ZVAL_ARR(array_zval, ht);

    for (unsigned int i = 0; i < model_count; i++) {
        ogt_vox_model_c model;
        if (!ogt_vox_scene_get_model(scene, i, &model)) {
            continue;
        }

        zval model_obj_zval;
        object_init_ex(&model_obj_zval, phpglfw_voxparser_model_ce);

        phpglfw_voxparser_model_object *model_intern = phpglfw_voxparser_model_objectptr_from_zobj_p(Z_OBJ(model_obj_zval));
        model_intern->model = model;
        model_intern->index = i;

        if (resource_obj != NULL) {
            model_intern->resource = resource_obj;
            ZVAL_OBJ_COPY(&model_intern->resource_zval, Z_OBJ_P(resource_zval));
        }

        zend_update_property_long(phpglfw_voxparser_model_ce, Z_OBJ(model_obj_zval), "index", sizeof("index") - 1, (zend_long) i);
        zend_update_property_long(phpglfw_voxparser_model_ce, Z_OBJ(model_obj_zval), "sizeX", sizeof("sizeX") - 1, model.size_x);
        zend_update_property_long(phpglfw_voxparser_model_ce, Z_OBJ(model_obj_zval), "sizeY", sizeof("sizeY") - 1, model.size_y);
        zend_update_property_long(phpglfw_voxparser_model_ce, Z_OBJ(model_obj_zval), "sizeZ", sizeof("sizeZ") - 1, model.size_z);
        zend_update_property_long(phpglfw_voxparser_model_ce, Z_OBJ(model_obj_zval), "voxelHash", sizeof("voxelHash") - 1, model.voxel_hash);

        size_t total_voxels = (size_t) model.size_x * (size_t) model.size_y * (size_t) model.size_z;
        zend_update_property_long(phpglfw_voxparser_model_ce, Z_OBJ(model_obj_zval), "voxelCount", sizeof("voxelCount") - 1, (zend_long) total_voxels);

        zval voxel_data_zval;
        object_init_ex(&voxel_data_zval, phpglfw_get_buffer_glubyte_ce());
        phpglfw_buffer_glubyte_object *buffer_intern = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ(voxel_data_zval));

        if (total_voxels > 0) {
            if (cvector_capacity(buffer_intern->vec) < total_voxels) {
                cvector_reserve(buffer_intern->vec, total_voxels);
            }
            cvector_set_size(buffer_intern->vec, total_voxels);
            memcpy(buffer_intern->vec, model.voxel_data, total_voxels);
        }

        zend_update_property(phpglfw_voxparser_model_ce, Z_OBJ(model_obj_zval), "voxelData", sizeof("voxelData") - 1, &voxel_data_zval);
        zval_ptr_dtor(&voxel_data_zval);

        if (resource_zval && Z_TYPE_P(resource_zval) == IS_OBJECT) {
            zval resource_copy;
            ZVAL_OBJ_COPY(&resource_copy, Z_OBJ_P(resource_zval));
            zend_update_property(phpglfw_voxparser_model_ce, Z_OBJ(model_obj_zval), "resource", sizeof("resource") - 1, &resource_copy);
            zval_ptr_dtor(&resource_copy);
        } else {
            zend_update_property_null(phpglfw_voxparser_model_ce, Z_OBJ(model_obj_zval), "resource", sizeof("resource") - 1);
        }

        zend_hash_index_update(ht, i, &model_obj_zval);
    }
}

void create_instances_phparray(zval *array_zval, const ogt_vox_scene_wrapper* scene, unsigned int instance_count, zval *resource_zval)
{
    phpglfw_voxparser_resource_object *resource_obj = NULL;
    if (resource_zval && Z_TYPE_P(resource_zval) == IS_OBJECT && instanceof_function(Z_OBJCE_P(resource_zval), phpglfw_voxparser_res_ce)) {
        resource_obj = phpglfw_voxparser_res_objectptr_from_zobj_p(Z_OBJ_P(resource_zval));
    }

    ZVAL_EMPTY_ARRAY(array_zval);
    HashTable *ht = zend_new_array(instance_count);
    ZVAL_ARR(array_zval, ht);

    for (unsigned int i = 0; i < instance_count; i++) {
        ogt_vox_instance_c instance;
        if (!ogt_vox_scene_get_instance(scene, i, &instance)) {
            continue;
        }

        zval instance_obj_zval;
        object_init_ex(&instance_obj_zval, phpglfw_voxparser_instance_ce);

        phpglfw_voxparser_instance_object *instance_intern = phpglfw_voxparser_instance_objectptr_from_zobj_p(Z_OBJ(instance_obj_zval));
        instance_intern->instance = instance;
        instance_intern->index = i;

        if (resource_obj != NULL) {
            instance_intern->resource = resource_obj;
            ZVAL_OBJ_COPY(&instance_intern->resource_zval, Z_OBJ_P(resource_zval));
        }

        zend_update_property_long(phpglfw_voxparser_instance_ce, Z_OBJ(instance_obj_zval), "index", sizeof("index") - 1, (zend_long) i);

        if (instance.name != NULL) {
            zend_update_property_string(phpglfw_voxparser_instance_ce, Z_OBJ(instance_obj_zval), "name", sizeof("name") - 1, instance.name);
        } else {
            zend_update_property_null(phpglfw_voxparser_instance_ce, Z_OBJ(instance_obj_zval), "name", sizeof("name") - 1);
        }

        zend_update_property_long(phpglfw_voxparser_instance_ce, Z_OBJ(instance_obj_zval), "modelIndex", sizeof("modelIndex") - 1, instance.model_index);
        zend_update_property_long(phpglfw_voxparser_instance_ce, Z_OBJ(instance_obj_zval), "layerIndex", sizeof("layerIndex") - 1, instance.layer_index);
        zend_update_property_long(phpglfw_voxparser_instance_ce, Z_OBJ(instance_obj_zval), "groupIndex", sizeof("groupIndex") - 1, instance.group_index);
        zend_update_property_bool(phpglfw_voxparser_instance_ce, Z_OBJ(instance_obj_zval), "hidden", sizeof("hidden") - 1, instance.hidden);

        ogt_vox_transform_c transform_global;
        ogt_vox_transform_c transform_local;
        zend_bool have_global = ogt_vox_scene_get_instance_transform_global(scene, i, &transform_global);
        zend_bool have_local = ogt_vox_scene_get_instance_transform_local(scene, i, &transform_local);

        instance_intern->has_transforms = have_global || have_local;
        if (have_global) {
            instance_intern->transform_global = transform_global;
            zval transform_zval;
            phpglfw_voxparser_transform_to_mat4(&transform_zval, &transform_global);
            zend_update_property(phpglfw_voxparser_instance_ce, Z_OBJ(instance_obj_zval), "transform", sizeof("transform") - 1, &transform_zval);
            zval_ptr_dtor(&transform_zval);
        } else {
            zend_update_property_null(phpglfw_voxparser_instance_ce, Z_OBJ(instance_obj_zval), "transform", sizeof("transform") - 1);
        }

        if (have_local) {
            instance_intern->transform_local = transform_local;
            zval transform_local_zval;
            phpglfw_voxparser_transform_to_mat4(&transform_local_zval, &transform_local);
            zend_update_property(phpglfw_voxparser_instance_ce, Z_OBJ(instance_obj_zval), "localTransform", sizeof("localTransform") - 1, &transform_local_zval);
            zval_ptr_dtor(&transform_local_zval);
        } else {
            zend_update_property_null(phpglfw_voxparser_instance_ce, Z_OBJ(instance_obj_zval), "localTransform", sizeof("localTransform") - 1);
        }

        zend_hash_index_update(ht, i, &instance_obj_zval);
    }
}

void create_layers_phparray(zval *array_zval, const ogt_vox_scene_wrapper* scene, unsigned int layer_count, zval *resource_zval)
{
    phpglfw_voxparser_resource_object *resource_obj = NULL;
    if (resource_zval && Z_TYPE_P(resource_zval) == IS_OBJECT && instanceof_function(Z_OBJCE_P(resource_zval), phpglfw_voxparser_res_ce)) {
        resource_obj = phpglfw_voxparser_res_objectptr_from_zobj_p(Z_OBJ_P(resource_zval));
    }

    ZVAL_EMPTY_ARRAY(array_zval);
    HashTable *ht = zend_new_array(layer_count);
    ZVAL_ARR(array_zval, ht);

    for (unsigned int i = 0; i < layer_count; i++) {
        ogt_vox_layer_c layer;
        if (!ogt_vox_scene_get_layer(scene, i, &layer)) {
            continue;
        }

        zval layer_obj_zval;
        object_init_ex(&layer_obj_zval, phpglfw_voxparser_layer_ce);

        phpglfw_voxparser_layer_object *layer_intern = phpglfw_voxparser_layer_objectptr_from_zobj_p(Z_OBJ(layer_obj_zval));
        layer_intern->layer = layer;
        layer_intern->index = i;

        if (resource_obj != NULL) {
            layer_intern->resource = resource_obj;
            ZVAL_OBJ_COPY(&layer_intern->resource_zval, Z_OBJ_P(resource_zval));
        }

        zend_update_property_long(phpglfw_voxparser_layer_ce, Z_OBJ(layer_obj_zval), "index", sizeof("index") - 1, (zend_long) i);

        if (layer.name != NULL) {
            zend_update_property_string(phpglfw_voxparser_layer_ce, Z_OBJ(layer_obj_zval), "name", sizeof("name") - 1, layer.name);
        } else {
            zend_update_property_null(phpglfw_voxparser_layer_ce, Z_OBJ(layer_obj_zval), "name", sizeof("name") - 1);
        }

        zval color_zval;
        object_init_ex(&color_zval, phpglfw_get_math_vec4_ce());
        phpglfw_math_vec4_object *color_intern = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ(color_zval));
        color_intern->data[0] = layer.color.r / 255.0f;
        color_intern->data[1] = layer.color.g / 255.0f;
        color_intern->data[2] = layer.color.b / 255.0f;
        color_intern->data[3] = layer.color.a / 255.0f;
        zend_update_property(phpglfw_voxparser_layer_ce, Z_OBJ(layer_obj_zval), "color", sizeof("color") - 1, &color_zval);
        zval_ptr_dtor(&color_zval);

        zend_update_property_bool(phpglfw_voxparser_layer_ce, Z_OBJ(layer_obj_zval), "hidden", sizeof("hidden") - 1, layer.hidden);

        zend_hash_index_update(ht, i, &layer_obj_zval);
    }
}

void create_groups_phparray(zval *array_zval, const ogt_vox_scene_wrapper* scene, unsigned int group_count, zval *resource_zval)
{
    phpglfw_voxparser_resource_object *resource_obj = NULL;
    if (resource_zval && Z_TYPE_P(resource_zval) == IS_OBJECT && instanceof_function(Z_OBJCE_P(resource_zval), phpglfw_voxparser_res_ce)) {
        resource_obj = phpglfw_voxparser_res_objectptr_from_zobj_p(Z_OBJ_P(resource_zval));
    }

    ZVAL_EMPTY_ARRAY(array_zval);
    HashTable *ht = zend_new_array(group_count);
    ZVAL_ARR(array_zval, ht);

    for (unsigned int i = 0; i < group_count; i++) {
        ogt_vox_group_c group;
        if (!ogt_vox_scene_get_group(scene, i, &group)) {
            continue;
        }

        zval group_obj_zval;
        object_init_ex(&group_obj_zval, phpglfw_voxparser_group_ce);

        phpglfw_voxparser_group_object *group_intern = phpglfw_voxparser_group_objectptr_from_zobj_p(Z_OBJ(group_obj_zval));
        group_intern->group = group;
        group_intern->index = i;

        if (resource_obj != NULL) {
            group_intern->resource = resource_obj;
            ZVAL_OBJ_COPY(&group_intern->resource_zval, Z_OBJ_P(resource_zval));
        }

        zend_update_property_long(phpglfw_voxparser_group_ce, Z_OBJ(group_obj_zval), "index", sizeof("index") - 1, (zend_long) i);

        if (group.name != NULL) {
            zend_update_property_string(phpglfw_voxparser_group_ce, Z_OBJ(group_obj_zval), "name", sizeof("name") - 1, group.name);
        } else {
            zend_update_property_null(phpglfw_voxparser_group_ce, Z_OBJ(group_obj_zval), "name", sizeof("name") - 1);
        }

        zend_update_property_long(phpglfw_voxparser_group_ce, Z_OBJ(group_obj_zval), "parentGroupIndex", sizeof("parentGroupIndex") - 1, group.parent_group_index);
        zend_update_property_long(phpglfw_voxparser_group_ce, Z_OBJ(group_obj_zval), "layerIndex", sizeof("layerIndex") - 1, group.layer_index);
        zend_update_property_bool(phpglfw_voxparser_group_ce, Z_OBJ(group_obj_zval), "hidden", sizeof("hidden") - 1, group.hidden);

        ogt_vox_transform_c transform_global;
        ogt_vox_transform_c transform_local;
        zend_bool have_global = ogt_vox_scene_get_group_transform_global(scene, i, &transform_global);
        zend_bool have_local = ogt_vox_scene_get_group_transform_local(scene, i, &transform_local);

        group_intern->has_transforms = have_global || have_local;

        if (have_global) {
            group_intern->transform_global = transform_global;
            zval transform_zval;
            phpglfw_voxparser_transform_to_mat4(&transform_zval, &transform_global);
            zend_update_property(phpglfw_voxparser_group_ce, Z_OBJ(group_obj_zval), "transform", sizeof("transform") - 1, &transform_zval);
            zval_ptr_dtor(&transform_zval);
        } else {
            zend_update_property_null(phpglfw_voxparser_group_ce, Z_OBJ(group_obj_zval), "transform", sizeof("transform") - 1);
        }

        if (have_local) {
            group_intern->transform_local = transform_local;
            zval transform_local_zval;
            phpglfw_voxparser_transform_to_mat4(&transform_local_zval, &transform_local);
            zend_update_property(phpglfw_voxparser_group_ce, Z_OBJ(group_obj_zval), "localTransform", sizeof("localTransform") - 1, &transform_local_zval);
            zval_ptr_dtor(&transform_local_zval);
        } else {
            zend_update_property_null(phpglfw_voxparser_group_ce, Z_OBJ(group_obj_zval), "localTransform", sizeof("localTransform") - 1);
        }

        zend_hash_index_update(ht, i, &group_obj_zval);
    }
}

PHP_METHOD(GL_Geometry_VoxFileParser, __construct)
{
    zend_object *curr_obj = Z_OBJ_P(getThis());

    zval res_obj_zval;
    object_init_ex(&res_obj_zval, phpglfw_voxparser_res_ce);
    zend_update_property(phpglfw_voxparser_ce, curr_obj, "resource", sizeof("resource") - 1, &res_obj_zval);

    phpglfw_voxparser_resource_object *intern = phpglfw_voxparser_res_objectptr_from_zobj_p(Z_OBJ(res_obj_zval));
    intern->scene = NULL;

    char *file_path;
    size_t file_path_len;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "p", &file_path, &file_path_len) == FAILURE) {
        zval_ptr_dtor(&res_obj_zval);
        RETURN_NULL();
    }

    zend_string *file_buffer = NULL;
    php_stream *stream = php_stream_open_wrapper_ex(file_path, "rb", REPORT_ERRORS, NULL, NULL);
    if (!stream) {
        zend_throw_error(NULL, "Could not open vox file: %s", file_path);
        goto cleanup;
    }

    file_buffer = php_stream_copy_to_mem(stream, PHP_STREAM_COPY_ALL, 0);
    php_stream_close(stream);
    stream = NULL;

    if (!file_buffer) {
        zend_throw_error(NULL, "Could not read vox file: %s", file_path);
        goto cleanup;
    }

    intern->scene = ogt_vox_read_scene_c((const uint8_t *) ZSTR_VAL(file_buffer), (uint32_t) ZSTR_LEN(file_buffer));
    if (!intern->scene) {
        zend_throw_error(NULL, "Could not parse vox file: %s", file_path);
        goto cleanup;
    }

    uint32_t num_models = ogt_vox_scene_get_num_models(intern->scene);
    uint32_t num_instances = ogt_vox_scene_get_num_instances(intern->scene);
    uint32_t num_layers = ogt_vox_scene_get_num_layers(intern->scene);
    uint32_t num_groups = ogt_vox_scene_get_num_groups(intern->scene);

    zend_update_property_long(phpglfw_voxparser_ce, curr_obj, "modelCount", sizeof("modelCount") - 1, (zend_long) num_models);
    zend_update_property_long(phpglfw_voxparser_ce, curr_obj, "instanceCount", sizeof("instanceCount") - 1, (zend_long) num_instances);
    zend_update_property_long(phpglfw_voxparser_ce, curr_obj, "layerCount", sizeof("layerCount") - 1, (zend_long) num_layers);
    zend_update_property_long(phpglfw_voxparser_ce, curr_obj, "groupCount", sizeof("groupCount") - 1, (zend_long) num_groups);

    zval models_array_zval;
    create_models_phparray(&models_array_zval, intern->scene, num_models, &res_obj_zval);
    zend_update_property(phpglfw_voxparser_ce, curr_obj, "models", sizeof("models") - 1, &models_array_zval);
    zval_ptr_dtor(&models_array_zval);

    zval instances_array_zval;
    create_instances_phparray(&instances_array_zval, intern->scene, num_instances, &res_obj_zval);
    zend_update_property(phpglfw_voxparser_ce, curr_obj, "instances", sizeof("instances") - 1, &instances_array_zval);
    zval_ptr_dtor(&instances_array_zval);

    zval layers_array_zval;
    create_layers_phparray(&layers_array_zval, intern->scene, num_layers, &res_obj_zval);
    zend_update_property(phpglfw_voxparser_ce, curr_obj, "layers", sizeof("layers") - 1, &layers_array_zval);
    zval_ptr_dtor(&layers_array_zval);

    zval groups_array_zval;
    create_groups_phparray(&groups_array_zval, intern->scene, num_groups, &res_obj_zval);
    zend_update_property(phpglfw_voxparser_ce, curr_obj, "groups", sizeof("groups") - 1, &groups_array_zval);
    zval_ptr_dtor(&groups_array_zval);

    const ogt_vox_rgba_c *palette_ptr = ogt_vox_scene_get_palette_c(intern->scene);
    zval palette_object_zval;
    object_init_ex(&palette_object_zval, phpglfw_voxparser_palette_ce);

    phpglfw_voxparser_palette_object *palette_intern = phpglfw_voxparser_palette_objectptr_from_zobj_p(Z_OBJ(palette_object_zval));
    phpglfw_buffer_glubyte_object *palette_buffer = phpglfw_voxparser_palette_ensure_buffer(palette_intern);

    if (palette_ptr) {
        memcpy(palette_buffer->vec, palette_ptr, PHPGLFW_VOX_PALETTE_BYTES);
    } else {
        phpglfw_voxparser_palette_copy_from_rgba(palette_buffer, phpglfw_vox_default_palette());
    }

    zend_update_property(phpglfw_voxparser_ce, curr_obj, "palette", sizeof("palette") - 1, &palette_object_zval);
    zval_ptr_dtor(&palette_object_zval);

cleanup:
    if (file_buffer) {
        zend_string_release(file_buffer);
    }
    zval_ptr_dtor(&res_obj_zval);
    return;
}

PHP_METHOD(GL_Geometry_VoxFileParser, getModel)
{
    long model_index;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &model_index) == FAILURE) {
        return;
    }

    // get the resource zval from local prop
    zval rv;
    zval *resource_zval = zend_read_property(phpglfw_voxparser_ce, Z_OBJ_P(getThis()), "resource", sizeof("resource")-1, 0, &rv);

    // fetch the internal obj from resource_zval
    phpglfw_voxparser_resource_object *intern = phpglfw_voxparser_res_objectptr_from_zobj_p(Z_OBJ_P(resource_zval));
    
    uint32_t num_models = ogt_vox_scene_get_num_models(intern->scene);
    if (!intern->scene || model_index < 0 || model_index >= num_models) {
        RETURN_NULL();
    }

    ogt_vox_model_c model;
    if (!ogt_vox_scene_get_model(intern->scene, model_index, &model)) {
        RETURN_NULL();
    }
    
    object_init_ex(return_value, phpglfw_voxparser_model_ce);

    phpglfw_voxparser_model_object *model_intern = phpglfw_voxparser_model_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    model_intern->model = model;
    model_intern->index = model_index;

    if (resource_zval && Z_TYPE_P(resource_zval) == IS_OBJECT) {
        model_intern->resource = intern;
        ZVAL_OBJ_COPY(&model_intern->resource_zval, Z_OBJ_P(resource_zval));
    }

    zend_update_property_long(phpglfw_voxparser_model_ce, Z_OBJ_P(return_value), "sizeX", sizeof("sizeX") - 1, model.size_x);
    zend_update_property_long(phpglfw_voxparser_model_ce, Z_OBJ_P(return_value), "sizeY", sizeof("sizeY") - 1, model.size_y);
    zend_update_property_long(phpglfw_voxparser_model_ce, Z_OBJ_P(return_value), "sizeZ", sizeof("sizeZ") - 1, model.size_z);
    zend_update_property_long(phpglfw_voxparser_model_ce, Z_OBJ_P(return_value), "voxelHash", sizeof("voxelHash") - 1, model.voxel_hash);

    size_t total_voxels = (size_t) model.size_x * (size_t) model.size_y * (size_t) model.size_z;
    zend_update_property_long(phpglfw_voxparser_model_ce, Z_OBJ_P(return_value), "index", sizeof("index") - 1, (zend_long) model_index);
    zend_update_property_long(phpglfw_voxparser_model_ce, Z_OBJ_P(return_value), "voxelCount", sizeof("voxelCount") - 1, (zend_long) total_voxels);

    zval voxel_data;
    object_init_ex(&voxel_data, phpglfw_get_buffer_glubyte_ce());
    phpglfw_buffer_glubyte_object *buffer_intern = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(&voxel_data));
    
    if (total_voxels > 0) {
        if (cvector_capacity(buffer_intern->vec) < total_voxels) {
            cvector_reserve(buffer_intern->vec, total_voxels);
        }
        cvector_set_size(buffer_intern->vec, total_voxels);
        memcpy(buffer_intern->vec, model.voxel_data, total_voxels);
    }
    
    zend_update_property(phpglfw_voxparser_model_ce, Z_OBJ_P(return_value), "voxelData", sizeof("voxelData") - 1, &voxel_data);
    zval_ptr_dtor(&voxel_data);

    if (resource_zval && Z_TYPE_P(resource_zval) == IS_OBJECT) {
        zval resource_copy;
        ZVAL_OBJ_COPY(&resource_copy, Z_OBJ_P(resource_zval));
        zend_update_property(phpglfw_voxparser_model_ce, Z_OBJ_P(return_value), "resource", sizeof("resource") - 1, &resource_copy);
        zval_ptr_dtor(&resource_copy);
    } else {
        zend_update_property_null(phpglfw_voxparser_model_ce, Z_OBJ_P(return_value), "resource", sizeof("resource") - 1);
    }
}

PHP_METHOD(GL_Geometry_VoxFileParser, getPaletteColor)
{
    long color_index;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &color_index) == FAILURE) {
        return;
    }

    // get the resource zval from local prop
    zval rv;
    zval *resource_zval = zend_read_property(phpglfw_voxparser_ce, Z_OBJ_P(getThis()), "resource", sizeof("resource")-1, 0, &rv);

    // fetch the internal obj from resource_zval
    phpglfw_voxparser_resource_object *intern = phpglfw_voxparser_res_objectptr_from_zobj_p(Z_OBJ_P(resource_zval));
    
    if (!intern->scene || color_index < 0 || color_index >= 256) {
        RETURN_NULL();
    }

    ogt_vox_rgba_c color = ogt_vox_scene_get_palette_color(intern->scene, color_index);
    
    object_init_ex(return_value, phpglfw_get_math_vec4_ce());
    phpglfw_math_vec4_object *color_intern = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    color_intern->data[0] = color.r / 255.0f;
    color_intern->data[1] = color.g / 255.0f;
    color_intern->data[2] = color.b / 255.0f;
    color_intern->data[3] = color.a / 255.0f;
}

// Constructors for sub-classes that should not be directly instantiated
PHP_METHOD(GL_Geometry_VoxFileParser_Model, __construct)
{
    zend_throw_error(NULL, "Cannot construct a model directly");
}

PHP_METHOD(GL_Geometry_VoxFileParser_Palette, __construct)
{
    zval *buffer_zval = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|O!", &buffer_zval, phpglfw_get_buffer_glubyte_ce()) == FAILURE) {
        return;
    }

    phpglfw_voxparser_palette_object *intern = phpglfw_voxparser_palette_objectptr_from_zobj_p(Z_OBJ_P(getThis()));

    if (buffer_zval && Z_TYPE_P(buffer_zval) == IS_OBJECT) {
        phpglfw_buffer_glubyte_object *buffer_intern = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(buffer_zval));
        size_t current_size = cvector_size(buffer_intern->vec);

        if (current_size < PHPGLFW_VOX_PALETTE_COMPONENTS) {
            size_t old_size = current_size;
            if (cvector_capacity(buffer_intern->vec) < PHPGLFW_VOX_PALETTE_COMPONENTS) {
                cvector_reserve(buffer_intern->vec, PHPGLFW_VOX_PALETTE_COMPONENTS);
            }
            cvector_set_size(buffer_intern->vec, PHPGLFW_VOX_PALETTE_COMPONENTS);
            uint8_t *target = buffer_intern->vec;
            const uint8_t *defaults = (const uint8_t *) phpglfw_vox_default_palette();
            memcpy(target + old_size, defaults + old_size, PHPGLFW_VOX_PALETTE_COMPONENTS - old_size);
        } else if (current_size > PHPGLFW_VOX_PALETTE_COMPONENTS) {
            cvector_set_size(buffer_intern->vec, PHPGLFW_VOX_PALETTE_COMPONENTS);
        }

        phpglfw_voxparser_palette_prepare_buffer(buffer_intern);

        if (!Z_ISUNDEF(intern->buffer_zval)) {
            zval_ptr_dtor(&intern->buffer_zval);
        }

        ZVAL_OBJ_COPY(&intern->buffer_zval, Z_OBJ_P(buffer_zval));
        intern->buffer = buffer_intern;
    } else {
        phpglfw_buffer_glubyte_object *buffer_intern = phpglfw_voxparser_palette_ensure_buffer(intern);
        phpglfw_voxparser_palette_copy_from_rgba(buffer_intern, phpglfw_vox_default_palette());
    }
}

PHP_METHOD(GL_Geometry_VoxFileParser_Palette, getBuffer)
{
    ZEND_PARSE_PARAMETERS_NONE();

    phpglfw_voxparser_palette_object *intern = phpglfw_voxparser_palette_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_voxparser_palette_ensure_buffer(intern);

    RETURN_OBJ_COPY(Z_OBJ(intern->buffer_zval));
}

PHP_METHOD(GL_Geometry_VoxFileParser_Palette, setColor)
{
    zend_long index;
    zval *vec_zval;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lO", &index, &vec_zval, phpglfw_get_math_vec4_ce()) == FAILURE) {
        return;
    }

    if (index < 0 || index >= (zend_long) PHPGLFW_VOX_PALETTE_LENGTH) {
        zend_throw_error(NULL, "Palette index must be between 0 and 255");
        RETURN_THROWS();
    }

    phpglfw_voxparser_palette_object *intern = phpglfw_voxparser_palette_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_buffer_glubyte_object *buffer_intern = phpglfw_voxparser_palette_ensure_buffer(intern);
    phpglfw_math_vec4_object *vec_intern = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(vec_zval));

    uint32_t offset = ((uint32_t) index) * 4u;
    buffer_intern->vec[offset + 0] = phpglfw_vox_float_to_byte(vec_intern->data[0]);
    buffer_intern->vec[offset + 1] = phpglfw_vox_float_to_byte(vec_intern->data[1]);
    buffer_intern->vec[offset + 2] = phpglfw_vox_float_to_byte(vec_intern->data[2]);
    buffer_intern->vec[offset + 3] = phpglfw_vox_float_to_byte(vec_intern->data[3]);
}

PHP_METHOD(GL_Geometry_VoxFileParser_Palette, setColorf)
{
    zend_long index;
    double r;
    double g;
    double b;
    double a = 1.0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lddd|d", &index, &r, &g, &b, &a) == FAILURE) {
        return;
    }

    if (index < 0 || index >= (zend_long) PHPGLFW_VOX_PALETTE_LENGTH) {
        zend_throw_error(NULL, "Palette index must be between 0 and 255");
        RETURN_THROWS();
    }

    phpglfw_voxparser_palette_object *intern = phpglfw_voxparser_palette_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_buffer_glubyte_object *buffer_intern = phpglfw_voxparser_palette_ensure_buffer(intern);

    uint32_t offset = ((uint32_t) index) * 4u;
    buffer_intern->vec[offset + 0] = phpglfw_vox_float_to_byte((float) r);
    buffer_intern->vec[offset + 1] = phpglfw_vox_float_to_byte((float) g);
    buffer_intern->vec[offset + 2] = phpglfw_vox_float_to_byte((float) b);
    buffer_intern->vec[offset + 3] = phpglfw_vox_float_to_byte((float) a);
}

PHP_METHOD(GL_Geometry_VoxFileParser_Palette, getColor)
{
    zend_long index;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &index) == FAILURE) {
        return;
    }

    if (index < 0 || index >= (zend_long) PHPGLFW_VOX_PALETTE_LENGTH) {
        zend_throw_error(NULL, "Palette index must be between 0 and 255");
        RETURN_THROWS();
    }

    phpglfw_voxparser_palette_object *intern = phpglfw_voxparser_palette_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_buffer_glubyte_object *buffer_intern = phpglfw_voxparser_palette_ensure_buffer(intern);

    uint32_t offset = ((uint32_t) index) * 4u;

    // create vec4 object and set its values
    object_init_ex(return_value, phpglfw_get_math_vec4_ce());
    phpglfw_math_vec4_object *vec_intern = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(return_value));
    
    vec_intern->data[0] = buffer_intern->vec[offset + 0] / 255.0f;
    vec_intern->data[1] = buffer_intern->vec[offset + 1] / 255.0f;
    vec_intern->data[2] = buffer_intern->vec[offset + 2] / 255.0f;
    vec_intern->data[3] = buffer_intern->vec[offset + 3] / 255.0f;
}

PHP_METHOD(GL_Geometry_VoxFileParser_Palette, replaceFromBuffer)
{
    zval *source_zval;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "O", &source_zval) == FAILURE) {
        return;
    }

    zend_class_entry *source_ce = Z_OBJCE_P(source_zval);
    phpglfw_voxparser_palette_object *intern = phpglfw_voxparser_palette_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_buffer_glubyte_object *target_buffer = phpglfw_voxparser_palette_ensure_buffer(intern);

    if (instanceof_function(source_ce, phpglfw_get_geometry_voxparser_palette_ce())) {
        phpglfw_voxparser_palette_object *source_palette = phpglfw_voxparser_palette_objectptr_from_zobj_p(Z_OBJ_P(source_zval));
        phpglfw_buffer_glubyte_object *source_buffer = phpglfw_voxparser_palette_ensure_buffer(source_palette);
        memcpy(target_buffer->vec, source_buffer->vec, PHPGLFW_VOX_PALETTE_BYTES);
        return;
    }

    if (instanceof_function(source_ce, phpglfw_get_buffer_glubyte_ce())) {
        phpglfw_buffer_glubyte_object *buffer_intern = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(source_zval));
        size_t size = cvector_size(buffer_intern->vec);
        if (size < PHPGLFW_VOX_PALETTE_COMPONENTS) {
            zend_throw_error(NULL, "Palette buffer must contain at least %u RGBA components", (unsigned) PHPGLFW_VOX_PALETTE_COMPONENTS);
            RETURN_THROWS();
        }
        memcpy(target_buffer->vec, buffer_intern->vec, PHPGLFW_VOX_PALETTE_BYTES);
        return;
    }

    if (instanceof_function(source_ce, phpglfw_get_buffer_glfloat_ce())) {
        phpglfw_buffer_glfloat_object *float_buffer = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(source_zval));
        size_t component_count = cvector_size(float_buffer->vec);
        if (component_count < PHPGLFW_VOX_PALETTE_COMPONENTS) {
            zend_throw_error(NULL, "Float palette buffer must contain at least %u RGBA components", (unsigned) PHPGLFW_VOX_PALETTE_COMPONENTS);
            RETURN_THROWS();
        }

        for (uint32_t i = 0; i < PHPGLFW_VOX_PALETTE_LENGTH; i++) {
            target_buffer->vec[i * 4 + 0] = phpglfw_vox_float_to_byte(float_buffer->vec[i * 4 + 0]);
            target_buffer->vec[i * 4 + 1] = phpglfw_vox_float_to_byte(float_buffer->vec[i * 4 + 1]);
            target_buffer->vec[i * 4 + 2] = phpglfw_vox_float_to_byte(float_buffer->vec[i * 4 + 2]);
            target_buffer->vec[i * 4 + 3] = phpglfw_vox_float_to_byte(float_buffer->vec[i * 4 + 3]);
        }
        return;
    }

    zend_throw_error(NULL, "Unsupported palette buffer type. Expected UByteBuffer, FloatBuffer or Palette instance");
    RETURN_THROWS();
}

PHP_METHOD(GL_Geometry_VoxFileParser_Palette, replaceFromArray)
{
    zval *colors_zval;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "a", &colors_zval) == FAILURE) {
        return;
    }

    phpglfw_voxparser_palette_object *intern = phpglfw_voxparser_palette_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_buffer_glubyte_object *buffer_intern = phpglfw_voxparser_palette_ensure_buffer(intern);

    HashTable *ht = Z_ARRVAL_P(colors_zval);
    zend_bool updated = 0;
    zval *color_entry;
    zend_ulong index_key;

    ZEND_HASH_FOREACH_NUM_KEY_VAL(ht, index_key, color_entry) {
        if (index_key >= PHPGLFW_VOX_PALETTE_LENGTH) {
            zend_throw_error(NULL, "Palette index %u is out of range", (unsigned) index_key);
            RETURN_THROWS();
        }

        uint8_t rgba[4];
        if (!phpglfw_voxparser_palette_extract_color(color_entry, rgba)) {
            zend_throw_error(NULL, "Invalid color definition at palette index %u", (unsigned) index_key);
            RETURN_THROWS();
        }

        uint32_t offset = ((uint32_t) index_key) * 4u;
        buffer_intern->vec[offset + 0] = rgba[0];
        buffer_intern->vec[offset + 1] = rgba[1];
        buffer_intern->vec[offset + 2] = rgba[2];
        buffer_intern->vec[offset + 3] = rgba[3];
        updated = 1;
    } ZEND_HASH_FOREACH_END();

    if (!updated) {
        zend_throw_error(NULL, "Color definition array must contain at least one entry");
        RETURN_THROWS();
    }
}

PHP_METHOD(GL_Geometry_VoxFileParser_Palette, fillDefault)
{
    ZEND_PARSE_PARAMETERS_NONE();

    phpglfw_voxparser_palette_object *intern = phpglfw_voxparser_palette_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    phpglfw_buffer_glubyte_object *buffer_intern = phpglfw_voxparser_palette_ensure_buffer(intern);
    phpglfw_voxparser_palette_copy_from_rgba(buffer_intern, phpglfw_vox_default_palette());
}

PHP_METHOD(GL_Geometry_VoxFileParser_Model, generateTriangleMesh)
{
    zval *vertices_buffer_zval;
    zval *indices_buffer_zval;
    zval *palette_object_zval = NULL;
    zend_string *mode_string = NULL;
    zval *options_spec = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OO|O!S!a!", &vertices_buffer_zval, phpglfw_get_buffer_glfloat_ce(), &indices_buffer_zval, phpglfw_get_buffer_gluint_ce(), &palette_object_zval, phpglfw_get_geometry_voxparser_palette_ce(), &mode_string, &options_spec) == FAILURE) {
        return;
    }

    phpglfw_buffer_glfloat_object *vertices_buffer_intern = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(vertices_buffer_zval));
    phpglfw_buffer_gluint_object *indices_buffer_intern = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(indices_buffer_zval));

    zval *size_x_prop = zend_read_property(phpglfw_voxparser_model_ce, Z_OBJ_P(getThis()), "sizeX", sizeof("sizeX") - 1, 0, NULL);
    zval *size_y_prop = zend_read_property(phpglfw_voxparser_model_ce, Z_OBJ_P(getThis()), "sizeY", sizeof("sizeY") - 1, 0, NULL);
    zval *size_z_prop = zend_read_property(phpglfw_voxparser_model_ce, Z_OBJ_P(getThis()), "sizeZ", sizeof("sizeZ") - 1, 0, NULL);
    zval *voxel_data_prop = zend_read_property(phpglfw_voxparser_model_ce, Z_OBJ_P(getThis()), "voxelData", sizeof("voxelData") - 1, 0, NULL);

    if (!size_x_prop || !size_y_prop || !size_z_prop || !voxel_data_prop || Z_TYPE_P(voxel_data_prop) != IS_OBJECT) {
        zend_throw_error(NULL, "Model data is not available");
        RETURN_FALSE;
    }

    uint32_t size_x = Z_LVAL_P(size_x_prop);
    uint32_t size_y = Z_LVAL_P(size_y_prop);
    uint32_t size_z = Z_LVAL_P(size_z_prop);

    phpglfw_buffer_glubyte_object *voxel_data_intern = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ_P(voxel_data_prop));

    zval *resource_prop = zend_read_property(phpglfw_voxparser_model_ce, Z_OBJ_P(getThis()), "resource", sizeof("resource") - 1, 0, NULL);
    phpglfw_voxparser_resource_object *resource_intern = NULL;
    if (resource_prop && Z_TYPE_P(resource_prop) == IS_OBJECT && instanceof_function(Z_OBJCE_P(resource_prop), phpglfw_voxparser_res_ce)) {
        resource_intern = phpglfw_voxparser_res_objectptr_from_zobj_p(Z_OBJ_P(resource_prop));
    }

    phpglfw_vox_mesh_mode mesh_mode = PHPGLFW_VOX_MESH_MODE_SIMPLE;
    if (mode_string) {
        if (zend_string_equals_literal_ci(mode_string, "simple")) {
            mesh_mode = PHPGLFW_VOX_MESH_MODE_SIMPLE;
        } else if (zend_string_equals_literal_ci(mode_string, "greedy")) {
            mesh_mode = PHPGLFW_VOX_MESH_MODE_GREEDY;
        } else if (zend_string_equals_literal_ci(mode_string, "polygon") || zend_string_equals_literal_ci(mode_string, "polygons")) {
            mesh_mode = PHPGLFW_VOX_MESH_MODE_POLYGON;
        } else {
            zend_throw_error(NULL, "Invalid mesh generation mode, expected 'simple', 'greedy' or 'polygon'");
            RETURN_FALSE;
        }
    }

    enum {
        PHPGLFW_VOX_COLOR_LAYOUT_RGB,
        PHPGLFW_VOX_COLOR_LAYOUT_RGBA,
        PHPGLFW_VOX_COLOR_LAYOUT_NONE
    } color_mode = PHPGLFW_VOX_COLOR_LAYOUT_RGB;

    zend_bool include_palette_index = 0;
    enum {
        PHPGLFW_VOX_ORIGIN_CORNER,
        PHPGLFW_VOX_ORIGIN_CENTER
    } origin_mode = PHPGLFW_VOX_ORIGIN_CORNER;
    float custom_origin_offset[3] = {0.0f, 0.0f, 0.0f};

    if (options_spec && Z_TYPE_P(options_spec) == IS_ARRAY) {
        HashTable *opts_ht = Z_ARRVAL_P(options_spec);

        zval *mode_value = zend_hash_str_find(opts_ht, "mode", sizeof("mode") - 1);
        if (mode_value && Z_TYPE_P(mode_value) != IS_NULL && Z_TYPE_P(mode_value) != IS_UNDEF) {
            if (!phpglfw_vox_mesh_mode_from_zval(mode_value, &mesh_mode)) {
                zend_throw_error(NULL, "Invalid mesh mode provided in options");
                RETURN_FALSE;
            }
        }

        zval *color_layout = zend_hash_str_find(opts_ht, "colors", sizeof("colors") - 1);
        if (!color_layout) {
            color_layout = zend_hash_str_find(opts_ht, "colorLayout", sizeof("colorLayout") - 1);
        }
        if (color_layout && Z_TYPE_P(color_layout) == IS_STRING) {
            if (zend_string_equals_literal_ci(Z_STR_P(color_layout), "rgba")) {
                color_mode = PHPGLFW_VOX_COLOR_LAYOUT_RGBA;
            } else if (zend_string_equals_literal_ci(Z_STR_P(color_layout), "none")) {
                color_mode = PHPGLFW_VOX_COLOR_LAYOUT_NONE;
            } else if (zend_string_equals_literal_ci(Z_STR_P(color_layout), "rgb")) {
                color_mode = PHPGLFW_VOX_COLOR_LAYOUT_RGB;
            } else {
                zend_throw_error(NULL, "Unsupported color layout. Expected 'rgb', 'rgba' or 'none'");
                RETURN_FALSE;
            }
        }

        zval *palette_index_flag = zend_hash_str_find(opts_ht, "includePaletteIndex", sizeof("includePaletteIndex") - 1);
        if (palette_index_flag) {
            include_palette_index = zend_is_true(palette_index_flag);
        }

        zval *origin_value = zend_hash_str_find(opts_ht, "origin", sizeof("origin") - 1);
        if (origin_value && Z_TYPE_P(origin_value) == IS_STRING) {
            if (zend_string_equals_literal_ci(Z_STR_P(origin_value), "center") || zend_string_equals_literal_ci(Z_STR_P(origin_value), "centered")) {
                origin_mode = PHPGLFW_VOX_ORIGIN_CENTER;
            } else if (zend_string_equals_literal_ci(Z_STR_P(origin_value), "corner")) {
                origin_mode = PHPGLFW_VOX_ORIGIN_CORNER;
            } else {
                zend_throw_error(NULL, "Unknown origin mode. Expected 'corner' or 'center'");
                RETURN_FALSE;
            }
        }

        zval *origin_offset = zend_hash_str_find(opts_ht, "originOffset", sizeof("originOffset") - 1);
        if (origin_offset && Z_TYPE_P(origin_offset) == IS_ARRAY) {
            for (int i = 0; i < 3; i++) {
                zval *component = zend_hash_index_find(Z_ARRVAL_P(origin_offset), i);
                if (component && Z_TYPE_P(component) != IS_NULL && Z_TYPE_P(component) != IS_UNDEF) {
                    custom_origin_offset[i] = (float) zval_get_double(component);
                }
            }
        }
    }

    const ogt_vox_rgba_c *palette_ptr = NULL;
    ogt_vox_rgba_c palette_storage[PHPGLFW_VOX_PALETTE_LENGTH];

    if (palette_object_zval && Z_TYPE_P(palette_object_zval) == IS_OBJECT) {
        phpglfw_voxparser_palette_object *palette_object = phpglfw_voxparser_palette_objectptr_from_zobj_p(Z_OBJ_P(palette_object_zval));
        phpglfw_buffer_glubyte_object *palette_buffer = phpglfw_voxparser_palette_ensure_buffer(palette_object);
        palette_ptr = (const ogt_vox_rgba_c *) palette_buffer->vec;
    }

    if (!palette_ptr) {
        if (resource_intern && resource_intern->scene) {
            palette_ptr = ogt_vox_scene_get_palette_c(resource_intern->scene);
        }
        if (!palette_ptr) {
            palette_ptr = phpglfw_vox_default_palette();
        }
    } else {
        memcpy(palette_storage, palette_ptr, sizeof(palette_storage));
        palette_ptr = palette_storage;
    }

    ogt_mesh_c *mesh = NULL;
    switch (mesh_mode) {
        case PHPGLFW_VOX_MESH_MODE_GREEDY:
            mesh = ogt_vox_model_generate_mesh_greedy_c(
                voxel_data_intern->vec,
                size_x,
                size_y,
                size_z,
                palette_ptr
            );
            break;
        case PHPGLFW_VOX_MESH_MODE_POLYGON:
            mesh = ogt_vox_model_generate_mesh_polygon_c(
                voxel_data_intern->vec,
                size_x,
                size_y,
                size_z,
                palette_ptr
            );
            break;
        case PHPGLFW_VOX_MESH_MODE_SIMPLE:
        default:
            mesh = ogt_vox_model_generate_mesh_simple_c(
                voxel_data_intern->vec,
                size_x,
                size_y,
                size_z,
                palette_ptr
            );
            break;
    }

    if (!mesh) {
        zend_throw_error(NULL, "Failed to generate mesh from voxel data");
        RETURN_FALSE;
    }

    size_t floats_per_vertex = 6;
    switch (color_mode) {
        case PHPGLFW_VOX_COLOR_LAYOUT_RGBA:
            floats_per_vertex += 4;
            break;
        case PHPGLFW_VOX_COLOR_LAYOUT_RGB:
            floats_per_vertex += 3;
            break;
        case PHPGLFW_VOX_COLOR_LAYOUT_NONE:
        default:
            break;
    }

    if (include_palette_index) {
        floats_per_vertex += 1;
    }

    size_t vertices_needed = mesh->vertex_count * floats_per_vertex;
    size_t indices_needed = mesh->index_count;

    if (cvector_size(vertices_buffer_intern->vec) < vertices_needed) {
        cvector_reserve(vertices_buffer_intern->vec, vertices_needed);
    }
    cvector_set_size(vertices_buffer_intern->vec, vertices_needed);

    if (cvector_size(indices_buffer_intern->vec) < indices_needed) {
        cvector_reserve(indices_buffer_intern->vec, indices_needed);
    }
    cvector_set_size(indices_buffer_intern->vec, indices_needed);

    float origin_offset[3] = {custom_origin_offset[0], custom_origin_offset[1], custom_origin_offset[2]};
    if (origin_mode == PHPGLFW_VOX_ORIGIN_CENTER) {
        origin_offset[0] -= (float) size_x * 0.5f;
        origin_offset[1] -= (float) size_y * 0.5f;
        origin_offset[2] -= (float) size_z * 0.5f;
    }

    for (uint32_t i = 0; i < mesh->vertex_count; i++) {
        uint32_t base_idx = i * floats_per_vertex;
        uint32_t cursor = base_idx;

        vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].pos.x + origin_offset[0];
        vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].pos.y + origin_offset[1];
        vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].pos.z + origin_offset[2];

        vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].normal.x;
        vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].normal.y;
        vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].normal.z;

        if (color_mode == PHPGLFW_VOX_COLOR_LAYOUT_RGB) {
            vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].color.r / 255.0f;
            vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].color.g / 255.0f;
            vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].color.b / 255.0f;
        } else if (color_mode == PHPGLFW_VOX_COLOR_LAYOUT_RGBA) {
            vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].color.r / 255.0f;
            vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].color.g / 255.0f;
            vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].color.b / 255.0f;
            vertices_buffer_intern->vec[cursor++] = mesh->vertices[i].color.a / 255.0f;
        }

        if (include_palette_index) {
            vertices_buffer_intern->vec[cursor++] = (float) mesh->vertices[i].palette_index;
        }
    }

    for (uint32_t i = 0; i < mesh->index_count; i++) {
        indices_buffer_intern->vec[i] = mesh->indices[i];
    }

    uint32_t vertex_count = mesh->vertex_count;
    uint32_t index_count = mesh->index_count;

    ogt_vox_mesh_destroy_c(mesh);

    if (options_spec && Z_TYPE_P(options_spec) == IS_ARRAY) {
        HashTable *opts_ht = Z_ARRVAL_P(options_spec);
        zval stats_arr;
        array_init(&stats_arr);
        add_assoc_long(&stats_arr, "vertexCount", vertex_count);
        add_assoc_long(&stats_arr, "indexCount", index_count);
        if (!zend_hash_str_update(opts_ht, "stats", sizeof("stats") - 1, &stats_arr)) {
            zval_ptr_dtor(&stats_arr);
        }
    }

    RETURN_TRUE;
}

PHP_METHOD(GL_Geometry_VoxFileParser_Model, getVoxel)
{
    zend_long x;
    zend_long y;
    zend_long z;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lll", &x, &y, &z) == FAILURE) {
        return;
    }

    phpglfw_voxparser_model_object *model_intern = phpglfw_voxparser_model_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    if (!model_intern || !model_intern->model.voxel_data) {
        RETURN_NULL();
    }

    if (x < 0 || y < 0 || z < 0) {
        RETURN_NULL();
    }

    uint32_t ux = (uint32_t) x;
    uint32_t uy = (uint32_t) y;
    uint32_t uz = (uint32_t) z;

    if (ux >= model_intern->model.size_x || uy >= model_intern->model.size_y || uz >= model_intern->model.size_z) {
        RETURN_NULL();
    }

    size_t index = (size_t) ux + (size_t) model_intern->model.size_x * ((size_t) uy + (size_t) model_intern->model.size_y * (size_t) uz);
    uint8_t value = model_intern->model.voxel_data[index];
    RETURN_LONG(value);
}

PHP_METHOD(GL_Geometry_VoxFileParser_Instance, __construct)
{
    zend_throw_error(NULL, "Cannot construct an instance directly");
}

PHP_METHOD(GL_Geometry_VoxFileParser_Layer, __construct)
{
    zend_throw_error(NULL, "Cannot construct a layer directly");
}

PHP_METHOD(GL_Geometry_VoxFileParser_Group, __construct)
{
    zend_throw_error(NULL, "Cannot construct a group directly");
}

phpglfw_voxparser_resource_object* phpglfw_voxparser_res_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_voxparser_resource_object*)((char*)(obj) - XtOffsetOf(phpglfw_voxparser_resource_object, std));
}

phpglfw_voxparser_model_object* phpglfw_voxparser_model_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_voxparser_model_object*)((char*)(obj) - XtOffsetOf(phpglfw_voxparser_model_object, std));
}

phpglfw_voxparser_instance_object* phpglfw_voxparser_instance_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_voxparser_instance_object*)((char*)(obj) - XtOffsetOf(phpglfw_voxparser_instance_object, std));
}

phpglfw_voxparser_layer_object* phpglfw_voxparser_layer_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_voxparser_layer_object*)((char*)(obj) - XtOffsetOf(phpglfw_voxparser_layer_object, std));
}

phpglfw_voxparser_group_object* phpglfw_voxparser_group_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_voxparser_group_object*)((char*)(obj) - XtOffsetOf(phpglfw_voxparser_group_object, std));
}

phpglfw_voxparser_palette_object* phpglfw_voxparser_palette_objectptr_from_zobj_p(zend_object* obj)
{
    return (phpglfw_voxparser_palette_object*)((char*)(obj) - XtOffsetOf(phpglfw_voxparser_palette_object, std));
}

void phpglfw_voxparser_transform_to_mat4(zval *mat4_zval, const ogt_vox_transform_c *transform)
{
    object_init_ex(mat4_zval, phpglfw_get_math_mat4_ce());
    phpglfw_math_mat4_object *mat4_intern = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(mat4_zval));

    // Convert the transform to a 4x4 matrix
    // Assuming the transform has m[16] array
    memcpy(&mat4_intern->data[0][0], transform->m, sizeof(float) * 16);
}

phpglfw_buffer_glubyte_object *phpglfw_voxparser_palette_ensure_buffer(phpglfw_voxparser_palette_object *palette_intern)
{
    if (!Z_ISUNDEF(palette_intern->buffer_zval)) {
        return palette_intern->buffer;
    }

    object_init_ex(&palette_intern->buffer_zval, phpglfw_get_buffer_glubyte_ce());
    palette_intern->buffer = phpglfw_buffer_glubyte_objectptr_from_zobj_p(Z_OBJ(palette_intern->buffer_zval));

    if (cvector_size(palette_intern->buffer->vec) < PHPGLFW_VOX_PALETTE_COMPONENTS) {
        cvector_reserve(palette_intern->buffer->vec, PHPGLFW_VOX_PALETTE_COMPONENTS);
        cvector_set_size(palette_intern->buffer->vec, PHPGLFW_VOX_PALETTE_COMPONENTS);
    }

    return palette_intern->buffer;
}

void phpglfw_voxparser_palette_prepare_buffer(phpglfw_buffer_glubyte_object *buffer_intern)
{
    if (cvector_size(buffer_intern->vec) < PHPGLFW_VOX_PALETTE_COMPONENTS) {
        cvector_reserve(buffer_intern->vec, PHPGLFW_VOX_PALETTE_COMPONENTS);
        cvector_set_size(buffer_intern->vec, PHPGLFW_VOX_PALETTE_COMPONENTS);
    }
}

void phpglfw_voxparser_palette_copy_from_rgba(phpglfw_buffer_glubyte_object *buffer_intern, const ogt_vox_rgba_c *rgba)
{
    memcpy(buffer_intern->vec, rgba, PHPGLFW_VOX_PALETTE_BYTES);
}

zend_bool phpglfw_voxparser_palette_extract_color(zval *color_zval, uint8_t *rgba_out)
{
    if (Z_TYPE_P(color_zval) == IS_ARRAY) {
        HashTable *ht = Z_ARRVAL_P(color_zval);
        zval *r_val = zend_hash_str_find(ht, "r", sizeof("r") - 1);
        zval *g_val = zend_hash_str_find(ht, "g", sizeof("g") - 1);
        zval *b_val = zend_hash_str_find(ht, "b", sizeof("b") - 1);
        zval *a_val = zend_hash_str_find(ht, "a", sizeof("a") - 1);

        if (r_val && g_val && b_val) {
            rgba_out[0] = phpglfw_vox_float_to_byte(zval_get_double(r_val));
            rgba_out[1] = phpglfw_vox_float_to_byte(zval_get_double(g_val));
            rgba_out[2] = phpglfw_vox_float_to_byte(zval_get_double(b_val));
            rgba_out[3] = a_val ? phpglfw_vox_float_to_byte(zval_get_double(a_val)) : 255;
            return 1;
        }
    } else if (Z_TYPE_P(color_zval) == IS_OBJECT && instanceof_function(Z_OBJCE_P(color_zval), phpglfw_get_math_vec4_ce())) {
        phpglfw_math_vec4_object *vec4 = phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(color_zval));
        rgba_out[0] = phpglfw_vox_float_to_byte(vec4->data[0]);
        rgba_out[1] = phpglfw_vox_float_to_byte(vec4->data[1]);
        rgba_out[2] = phpglfw_vox_float_to_byte(vec4->data[2]);
        rgba_out[3] = phpglfw_vox_float_to_byte(vec4->data[3]);
        return 1;
    }

    return 0;
}

void phpglfw_register_voxparser_module(INIT_FUNC_ARGS)
{
    // Vox File Parser Resource
    // ------------------------------
    phpglfw_voxparser_res_ce = register_class_GL_Geometry_VoxFileParser_Resource();
    phpglfw_voxparser_res_ce->create_object = phpglfw_voxparser_res_create_handler;

    memcpy(&phpglfw_voxparser_res_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_voxparser_res_handlers));

    phpglfw_voxparser_res_handlers.offset = XtOffsetOf(phpglfw_voxparser_resource_object, std);
    phpglfw_voxparser_res_handlers.free_obj = phpglfw_geometry_voxparser_res_free_handler;

    // Vox File Parser
    // ------------------------------
    phpglfw_voxparser_ce = register_class_GL_Geometry_VoxFileParser();

    // Vox File Parser Palette
    phpglfw_voxparser_palette_ce = register_class_GL_Geometry_VoxFileParser_Palette();
    phpglfw_voxparser_palette_ce->create_object = phpglfw_voxparser_palette_create_handler;

    memcpy(&phpglfw_voxparser_palette_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_voxparser_palette_handlers));
    phpglfw_voxparser_palette_handlers.offset = XtOffsetOf(phpglfw_voxparser_palette_object, std);
    phpglfw_voxparser_palette_handlers.free_obj = phpglfw_voxparser_palette_free_handler;

    // Vox File Parser Model
    // ------------------------------
    phpglfw_voxparser_model_ce = register_class_GL_Geometry_VoxFileParser_Model();
    phpglfw_voxparser_model_ce->create_object = phpglfw_voxparser_model_create_handler;

    memcpy(&phpglfw_voxparser_model_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_voxparser_model_handlers));
    phpglfw_voxparser_model_handlers.offset = XtOffsetOf(phpglfw_voxparser_model_object, std);
    phpglfw_voxparser_model_handlers.free_obj = phpglfw_voxparser_model_free_handler;

    // Vox File Parser Instance
    // ------------------------------
    phpglfw_voxparser_instance_ce = register_class_GL_Geometry_VoxFileParser_Instance();
    phpglfw_voxparser_instance_ce->create_object = phpglfw_voxparser_instance_create_handler;

    memcpy(&phpglfw_voxparser_instance_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_voxparser_instance_handlers));
    phpglfw_voxparser_instance_handlers.offset = XtOffsetOf(phpglfw_voxparser_instance_object, std);
    phpglfw_voxparser_instance_handlers.free_obj = phpglfw_voxparser_instance_free_handler;

    // Vox File Parser Layer
    // ------------------------------
    phpglfw_voxparser_layer_ce = register_class_GL_Geometry_VoxFileParser_Layer();
    phpglfw_voxparser_layer_ce->create_object = phpglfw_voxparser_layer_create_handler;

    memcpy(&phpglfw_voxparser_layer_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_voxparser_layer_handlers));
    phpglfw_voxparser_layer_handlers.offset = XtOffsetOf(phpglfw_voxparser_layer_object, std);
    phpglfw_voxparser_layer_handlers.free_obj = phpglfw_voxparser_layer_free_handler;

    // Vox File Parser Group
    // ------------------------------
    phpglfw_voxparser_group_ce = register_class_GL_Geometry_VoxFileParser_Group();
    phpglfw_voxparser_group_ce->create_object = phpglfw_voxparser_group_create_handler;

    memcpy(&phpglfw_voxparser_group_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_voxparser_group_handlers));
    phpglfw_voxparser_group_handlers.offset = XtOffsetOf(phpglfw_voxparser_group_object, std);
    phpglfw_voxparser_group_handlers.free_obj = phpglfw_voxparser_group_free_handler;
}

zend_class_entry *phpglfw_get_geometry_voxparser_ce() {
    return phpglfw_voxparser_ce;
}

zend_class_entry *phpglfw_get_geometry_voxparser_res_ce() {
    return phpglfw_voxparser_res_ce;
}

zend_class_entry *phpglfw_get_geometry_voxparser_model_ce() {
    return phpglfw_voxparser_model_ce;
}

zend_class_entry *phpglfw_get_geometry_voxparser_instance_ce() {
    return phpglfw_voxparser_instance_ce;
}

zend_class_entry *phpglfw_get_geometry_voxparser_layer_ce() {
    return phpglfw_voxparser_layer_ce;
}

zend_class_entry *phpglfw_get_geometry_voxparser_group_ce() {
    return phpglfw_voxparser_group_ce;
}

zend_class_entry *phpglfw_get_geometry_voxparser_material_ce() {
    return NULL; // not implemented
}

zend_class_entry *phpglfw_get_geometry_voxparser_palette_ce() {
    return phpglfw_voxparser_palette_ce;
}