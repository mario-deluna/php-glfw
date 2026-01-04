/**
 * C wrapper for ogt_vox library
 * This file provides a C interface for the C++ ogt_vox library
 */
#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

// forward declarations for opaque types
typedef struct ogt_vox_scene_wrapper ogt_vox_scene_wrapper;
typedef struct ogt_vox_model_wrapper ogt_vox_model_wrapper;
typedef struct ogt_vox_instance_wrapper ogt_vox_instance_wrapper;
typedef struct ogt_vox_layer_wrapper ogt_vox_layer_wrapper;
typedef struct ogt_vox_group_wrapper ogt_vox_group_wrapper;

// RGBA color structure
typedef struct {
    uint8_t r, g, b, a;
} ogt_vox_rgba_c;

// transform structure
typedef struct {
    float m[16];
} ogt_vox_transform_c;

// model structure
typedef struct {
    uint32_t size_x;
    uint32_t size_y;
    uint32_t size_z;
    uint32_t voxel_hash;
    const uint8_t* voxel_data;
} ogt_vox_model_c;

// instance structure
typedef struct {
    const char* name;
    uint32_t model_index;
    uint32_t layer_index;
    uint32_t group_index;
    int hidden;
} ogt_vox_instance_c;

// layer structure
typedef struct {
    const char* name;
    ogt_vox_rgba_c color;
    int hidden;
} ogt_vox_layer_c;

// group structure  
typedef struct {
    const char* name;
    uint32_t parent_group_index;
    uint32_t layer_index;
    int hidden;
} ogt_vox_group_c;

// C interface functions
const ogt_vox_scene_wrapper* ogt_vox_read_scene_c(const uint8_t* buffer, uint32_t buffer_size);
void ogt_vox_destroy_scene_c(const ogt_vox_scene_wrapper* scene);

uint32_t ogt_vox_scene_get_num_models(const ogt_vox_scene_wrapper* scene);
uint32_t ogt_vox_scene_get_num_instances(const ogt_vox_scene_wrapper* scene);
uint32_t ogt_vox_scene_get_num_layers(const ogt_vox_scene_wrapper* scene);
uint32_t ogt_vox_scene_get_num_groups(const ogt_vox_scene_wrapper* scene);

int ogt_vox_scene_get_model(const ogt_vox_scene_wrapper* scene, uint32_t model_index, ogt_vox_model_c* out_model);
int ogt_vox_scene_get_instance(const ogt_vox_scene_wrapper* scene, uint32_t instance_index, ogt_vox_instance_c* out_instance);
int ogt_vox_scene_get_layer(const ogt_vox_scene_wrapper* scene, uint32_t layer_index, ogt_vox_layer_c* out_layer);
int ogt_vox_scene_get_group(const ogt_vox_scene_wrapper* scene, uint32_t group_index, ogt_vox_group_c* out_group);

int ogt_vox_scene_get_instance_transform_global(const ogt_vox_scene_wrapper* scene, uint32_t instance_index, ogt_vox_transform_c* out_transform);
int ogt_vox_scene_get_instance_transform_local(const ogt_vox_scene_wrapper* scene, uint32_t instance_index, ogt_vox_transform_c* out_transform);
int ogt_vox_scene_get_group_transform_global(const ogt_vox_scene_wrapper* scene, uint32_t group_index, ogt_vox_transform_c* out_transform);
int ogt_vox_scene_get_group_transform_local(const ogt_vox_scene_wrapper* scene, uint32_t group_index, ogt_vox_transform_c* out_transform);

ogt_vox_rgba_c ogt_vox_scene_get_palette_color(const ogt_vox_scene_wrapper* scene, uint32_t color_index);

// mesh generation functions
typedef struct {
    float x, y, z;
} ogt_mesh_vec3_c;

typedef struct {
    ogt_mesh_vec3_c pos;
    ogt_mesh_vec3_c normal;
    ogt_vox_rgba_c color;
    uint32_t palette_index;
} ogt_mesh_vertex_c;

typedef struct {
    uint32_t vertex_count;
    uint32_t index_count;
    ogt_mesh_vertex_c* vertices;
    uint32_t* indices;
} ogt_mesh_c;

// generate triangle mesh from voxel model data
ogt_mesh_c* ogt_vox_model_generate_mesh_simple_c(const uint8_t* voxel_data, uint32_t size_x, uint32_t size_y, uint32_t size_z, const ogt_vox_rgba_c* palette);
ogt_mesh_c* ogt_vox_model_generate_mesh_greedy_c(const uint8_t* voxel_data, uint32_t size_x, uint32_t size_y, uint32_t size_z, const ogt_vox_rgba_c* palette);
ogt_mesh_c* ogt_vox_model_generate_mesh_polygon_c(const uint8_t* voxel_data, uint32_t size_x, uint32_t size_y, uint32_t size_z, const ogt_vox_rgba_c* palette);

const ogt_vox_rgba_c* ogt_vox_scene_get_palette_c(const ogt_vox_scene_wrapper* scene);

// destroy generated mesh
void ogt_vox_mesh_destroy_c(ogt_mesh_c* mesh);

#ifdef __cplusplus
}
#endif