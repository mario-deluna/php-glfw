/**
 * PHP-glfw 
 * 
 * Extension Vox file parser
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
#ifndef PHP_GLFW_VOXPARSER_H
#define PHP_GLFW_VOXPARSER_H 1


#include <stdbool.h>

#include "phpglfw_constants.h"

#include "ogt_vox_c_wrapper.h"

struct _phpglfw_buffer_glubyte_object;

/**
 * Resource object containing the ogt_vox_scene data.
 */
typedef struct _phpglfw_voxparser_resource_object {
    const ogt_vox_scene_wrapper* scene;
    zend_object std;
} phpglfw_voxparser_resource_object; 

typedef struct _phpglfw_voxparser_model_object {
    phpglfw_voxparser_resource_object* resource;
    zval resource_zval;
    ogt_vox_model_c model;
    uint32_t index;
    zend_object std;
} phpglfw_voxparser_model_object;

typedef struct _phpglfw_voxparser_instance_object {
    phpglfw_voxparser_resource_object* resource;
    zval resource_zval;
    ogt_vox_instance_c instance;
    ogt_vox_transform_c transform_global;
    ogt_vox_transform_c transform_local;
    bool has_transforms;
    uint32_t index;
    zend_object std;
} phpglfw_voxparser_instance_object;

typedef struct _phpglfw_voxparser_layer_object {
    phpglfw_voxparser_resource_object* resource;
    zval resource_zval;
    ogt_vox_layer_c layer;
    uint32_t index;
    zend_object std;
} phpglfw_voxparser_layer_object;

typedef struct _phpglfw_voxparser_group_object {
    phpglfw_voxparser_resource_object* resource;
    zval resource_zval;
    ogt_vox_group_c group;
    ogt_vox_transform_c transform_global;
    ogt_vox_transform_c transform_local;
    bool has_transforms;
    uint32_t index;
    zend_object std;
} phpglfw_voxparser_group_object;

typedef struct _phpglfw_voxparser_palette_object {
    zval buffer_zval;
    struct _phpglfw_buffer_glubyte_object* buffer;
    zend_object std;
} phpglfw_voxparser_palette_object;

zend_class_entry *phpglfw_get_geometry_voxparser_ce(); 
zend_class_entry *phpglfw_get_geometry_voxparser_res_ce(); 
zend_class_entry *phpglfw_get_geometry_voxparser_model_ce(); 
zend_class_entry *phpglfw_get_geometry_voxparser_instance_ce(); 
zend_class_entry *phpglfw_get_geometry_voxparser_layer_ce();
zend_class_entry *phpglfw_get_geometry_voxparser_group_ce();
zend_class_entry *phpglfw_get_geometry_voxparser_material_ce();
zend_class_entry *phpglfw_get_geometry_voxparser_palette_ce();

phpglfw_voxparser_resource_object* phpglfw_voxparser_res_objectptr_from_zobj_p(zend_object* obj);
phpglfw_voxparser_model_object* phpglfw_voxparser_model_objectptr_from_zobj_p(zend_object* obj);
phpglfw_voxparser_instance_object* phpglfw_voxparser_instance_objectptr_from_zobj_p(zend_object* obj);
phpglfw_voxparser_layer_object* phpglfw_voxparser_layer_objectptr_from_zobj_p(zend_object* obj);
phpglfw_voxparser_group_object* phpglfw_voxparser_group_objectptr_from_zobj_p(zend_object* obj);
phpglfw_voxparser_palette_object* phpglfw_voxparser_palette_objectptr_from_zobj_p(zend_object* obj);

void phpglfw_register_voxparser_module(INIT_FUNC_ARGS);

#endif