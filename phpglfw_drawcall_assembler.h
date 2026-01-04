/**
 * PHP-glfw 
 * 
 * Extension: DrawCallAssembler
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
#ifndef PHP_GLFW_DRAWCALL_ASSEMBLER_H
#define PHP_GLFW_DRAWCALL_ASSEMBLER_H

#include "php.h"
#include "phpglfw_math.h"
#include "phpglfw_buffer.h"

// sort mode constants
#define PHPGLFW_SORT_NONE 0
#define PHPGLFW_SORT_FRONT_TO_BACK 1
#define PHPGLFW_SORT_BACK_TO_FRONT 2
#define PHPGLFW_SORT_DEPTH_PREPASS 3

// sort key bit packing constants
#define SK_PASS_BITS      2
#define SK_PROG_BITS     12
#define SK_MAT_BITS      14
#define SK_VAO_BITS      12
#define SK_MESH_BITS     14
#define SK_DEPTH_BITS    10

// sort key bit shifts (MSB -> LSB)
#define SK_DEPTH_SHIFT    0
#define SK_MESH_SHIFT    (SK_DEPTH_SHIFT + SK_DEPTH_BITS)          // 10
#define SK_VAO_SHIFT     (SK_MESH_SHIFT  + SK_MESH_BITS)           // 24
#define SK_MAT_SHIFT     (SK_VAO_SHIFT   + SK_VAO_BITS)            // 36
#define SK_PROG_SHIFT    (SK_MAT_SHIFT   + SK_MAT_BITS)            // 50
#define SK_PASS_SHIFT    (SK_PROG_SHIFT  + SK_PROG_BITS)           // 62

// sort key bit masks
#define SK_MASK(bits)     ((1ULL << (bits)) - 1ULL)

// render passes (kept to 2 bits via SK_PASS_BITS)
#define PHPGLFW_PASS_OPAQUE 0
#define PHPGLFW_PASS_TRANSPARENT 1
#define PHPGLFW_PASS_DEPTH 2
#define PHPGLFW_PASS_USER 3

// draw flags
#define PHPGLFW_FLAG_IGNORE_CULLING 2
#define PHPGLFW_FLAG_DISABLE_INSTANCING 4
#define PHPGLFW_FLAG_CUSTOM_SORT_KEY 8

// buffer strides
#define PHPGLFW_COMMAND_STRIDE 8
#define PHPGLFW_TRANSFORM_STRIDE 16
#define PHPGLFW_INSTANCE_META_STRIDE 4

// performance constants
#define PHPGLFW_SMALL_BUFFER_THRESHOLD 256
#define PHPGLFW_LOD_CACHE_EPSILON 0.01f

typedef struct _phpglfw_drawcall_mesh {
    uint32_t vao_id;
    uint32_t vertex_offset;
    uint32_t vertex_count;
    uint32_t index_offset;
    uint32_t index_count;
    phpglfw_math_vec3_object *aabb_min;
    phpglfw_math_vec3_object *aabb_max;
    uint32_t material_hint;
    uint32_t primitive;
    bool has_bounds;
    float bounds_center[3];
    float bounds_radius;
    
    // lod table
    phpglfw_buffer_glfloat_object *lod_distances;
    phpglfw_buffer_gluint_object *lod_handles;
} phpglfw_drawcall_mesh;

typedef struct _phpglfw_drawcall_instance {
    uint32_t base_mesh_handle;
    uint32_t mesh_handle;
    uint32_t material_id;
    uint32_t pass;
    uint32_t program_id;
    uint32_t user_id;
    uint32_t flags;
    mat4x4 transform;
    float sort_distance;
    float sort_bias;
    // lod caching
    float cached_lod_distance;
    uint32_t cached_lod_handle;
    // precomputed sort key for fast sorting
    uint64_t sort_key;
    // precomputed group key for batching
    uint64_t group_key;
} phpglfw_drawcall_instance;

typedef struct _phpglfw_drawcall_assembler_object {
    zend_object std;
    
    // buffers exposed to php
    phpglfw_buffer_gluint_object *command_buffer;
    phpglfw_buffer_glfloat_object *instance_transform_buffer;
    phpglfw_buffer_gluint_object *instance_meta_buffer;
    phpglfw_buffer_glfloat_object *instance_payload_buffer;
    zval command_buffer_zv;
    zval instance_transform_buffer_zv;
    zval instance_meta_buffer_zv;
    zval instance_payload_buffer_zv;

    // payload data buffer (for user-defined per-instance data)
    // this one holds the source data, the instance_payload_buffer is the GPU buffer
    // after culling and reordering
    zval payload_data_buffer_zv;
    uint32_t payload_data_stride; // offset in floats (not bytes, currently only float buffers supported)
    
    // internal state
    phpglfw_drawcall_mesh *meshes;
    uint32_t mesh_capacity;
    uint32_t mesh_count;
    
    phpglfw_drawcall_instance *instances;
    uint32_t instance_capacity;
    uint32_t instance_count;

    // buffer where we store the visible instance indices during culling
    // we reuse this buffer each frame to avoid reallocations
    uint32_t *visible_index_buffer;
    
    // frame state
    phpglfw_math_vec3_object *camera_position;
    phpglfw_math_mat4_object *view_matrix;
    phpglfw_math_mat4_object *projection_matrix;
    zval camera_position_zv;
    zval view_matrix_zv;
    zval projection_matrix_zv;
    
    // frustum planes (left, right, bottom, top, near, far)
    vec4 frustum_planes[6];
    bool has_frustum;
    
    // settings
    int sort_mode;
    bool auto_instancing;

    // rendering dispatch 
    cvector_vector_type(float) rendering_transform_buffer_data;
    cvector_vector_type(float) rendering_payload_buffer_data;
    
    // internal vbo for transform data
    GLuint internal_transform_vbo;
    
    // internal vbo for payload data
    GLuint internal_payload_vbo;
    
    // output stats
    uint32_t final_command_count;
    uint32_t final_instance_count;
} phpglfw_drawcall_assembler_object;

zend_class_entry *phpglfw_get_drawcall_assembler_ce();
phpglfw_drawcall_assembler_object *phpglfw_drawcall_assembler_objectptr_from_zobj_p(zend_object* obj);

void phpglfw_register_drawcall_assembler_module(INIT_FUNC_ARGS);

#endif