/**
 * Cpp impl of the C wrapper for ogt_vox
 */
#define OGT_VOX_IMPLEMENTATION
#include "ogt_vox.h"
#define OGT_VOXEL_MESHIFY_IMPLEMENTATION
#include "ogt_voxel_meshify.h"
#include "ogt_vox_c_wrapper.h"

#include <cstring>

static inline void phpglfw_copy_palette(ogt_mesh_rgba* dst, const ogt_vox_rgba_c* src)
{
    for (int i = 0; i < 256; ++i) {
        dst[i].r = src[i].r;
        dst[i].g = src[i].g;
        dst[i].b = src[i].b;
        dst[i].a = src[i].a;
    }
}

static inline void phpglfw_pack_transform(ogt_vox_transform_c* dst, const ogt_vox_transform& src)
{
    if (!dst) {
        return;
    }

    dst->m[0] = src.m00;
    dst->m[1] = src.m01;
    dst->m[2] = src.m02;
    dst->m[3] = src.m03;

    dst->m[4] = src.m10;
    dst->m[5] = src.m11;
    dst->m[6] = src.m12;
    dst->m[7] = src.m13;

    dst->m[8] = src.m20;
    dst->m[9] = src.m21;
    dst->m[10] = src.m22;
    dst->m[11] = src.m23;

    dst->m[12] = src.m30;
    dst->m[13] = src.m31;
    dst->m[14] = src.m32;
    dst->m[15] = src.m33;
}

static ogt_mesh_c* phpglfw_convert_cpp_mesh(const ogt_voxel_meshify_context* ctx, ogt_mesh* cpp_mesh)
{
    if (!cpp_mesh) {
        return nullptr;
    }

    ogt_mesh_c* c_mesh = new ogt_mesh_c();
    c_mesh->vertex_count = cpp_mesh->vertex_count;
    c_mesh->index_count = cpp_mesh->index_count;

    c_mesh->vertices = new ogt_mesh_vertex_c[c_mesh->vertex_count];
    for (uint32_t i = 0; i < c_mesh->vertex_count; i++) {
        const ogt_mesh_vertex& vertex = cpp_mesh->vertices[i];
        c_mesh->vertices[i].pos.x = vertex.pos.x;
        c_mesh->vertices[i].pos.y = vertex.pos.y;
        c_mesh->vertices[i].pos.z = vertex.pos.z;

        c_mesh->vertices[i].normal.x = vertex.normal.x;
        c_mesh->vertices[i].normal.y = vertex.normal.y;
        c_mesh->vertices[i].normal.z = vertex.normal.z;

        c_mesh->vertices[i].color.r = vertex.color.r;
        c_mesh->vertices[i].color.g = vertex.color.g;
        c_mesh->vertices[i].color.b = vertex.color.b;
        c_mesh->vertices[i].color.a = vertex.color.a;

        c_mesh->vertices[i].palette_index = vertex.palette_index;
    }

    c_mesh->indices = new uint32_t[c_mesh->index_count];
    std::memcpy(c_mesh->indices, cpp_mesh->indices, sizeof(uint32_t) * c_mesh->index_count);

    ogt_mesh_destroy(ctx, cpp_mesh);

    return c_mesh;
}

extern "C" {

struct ogt_vox_scene_wrapper {
    const ogt_vox_scene* scene;
};

const ogt_vox_scene_wrapper* ogt_vox_read_scene_c(const uint8_t* buffer, uint32_t buffer_size) {
    const ogt_vox_scene* scene = ogt_vox_read_scene(buffer, buffer_size);
    if (!scene) {
        return nullptr;
    }
    
    ogt_vox_scene_wrapper* wrapper = new ogt_vox_scene_wrapper();
    wrapper->scene = scene;
    return wrapper;
}

void ogt_vox_destroy_scene_c(const ogt_vox_scene_wrapper* scene) {
    if (scene) {
        ogt_vox_destroy_scene(scene->scene);
        delete scene;
    }
}

uint32_t ogt_vox_scene_get_num_models(const ogt_vox_scene_wrapper* scene) {
    return scene ? scene->scene->num_models : 0;
}

uint32_t ogt_vox_scene_get_num_instances(const ogt_vox_scene_wrapper* scene) {
    return scene ? scene->scene->num_instances : 0;
}

uint32_t ogt_vox_scene_get_num_layers(const ogt_vox_scene_wrapper* scene) {
    return scene ? scene->scene->num_layers : 0;
}

uint32_t ogt_vox_scene_get_num_groups(const ogt_vox_scene_wrapper* scene) {
    return scene ? scene->scene->num_groups : 0;
}

int ogt_vox_scene_get_model(const ogt_vox_scene_wrapper* scene, uint32_t model_index, ogt_vox_model_c* out_model) {
    if (!scene || !out_model || model_index >= scene->scene->num_models) {
        return 0;
    }
    
    const ogt_vox_model* model = scene->scene->models[model_index];
    out_model->size_x = model->size_x;
    out_model->size_y = model->size_y;
    out_model->size_z = model->size_z;
    out_model->voxel_hash = model->voxel_hash;
    out_model->voxel_data = model->voxel_data;
    
    return 1;
}

int ogt_vox_scene_get_instance(const ogt_vox_scene_wrapper* scene, uint32_t instance_index, ogt_vox_instance_c* out_instance) {
    if (!scene || !out_instance || instance_index >= scene->scene->num_instances) {
        return 0;
    }
    
    const ogt_vox_instance* instance = &scene->scene->instances[instance_index];
    out_instance->name = instance->name;
    out_instance->model_index = instance->model_index;
    out_instance->layer_index = instance->layer_index;
    out_instance->group_index = instance->group_index;
    out_instance->hidden = instance->hidden ? 1 : 0;
    
    return 1;
}

int ogt_vox_scene_get_layer(const ogt_vox_scene_wrapper* scene, uint32_t layer_index, ogt_vox_layer_c* out_layer) {
    if (!scene || !out_layer || layer_index >= scene->scene->num_layers) {
        return 0;
    }
    
    const ogt_vox_layer* layer = &scene->scene->layers[layer_index];
    out_layer->name = layer->name;
    out_layer->color.r = layer->color.r;
    out_layer->color.g = layer->color.g;
    out_layer->color.b = layer->color.b;
    out_layer->color.a = layer->color.a;
    out_layer->hidden = layer->hidden ? 1 : 0;
    
    return 1;
}

int ogt_vox_scene_get_group(const ogt_vox_scene_wrapper* scene, uint32_t group_index, ogt_vox_group_c* out_group) {
    if (!scene || !out_group || group_index >= scene->scene->num_groups) {
        return 0;
    }
    
    const ogt_vox_group* group = &scene->scene->groups[group_index];
    out_group->name = group->name;
    out_group->parent_group_index = group->parent_group_index;
    out_group->layer_index = group->layer_index;
    out_group->hidden = group->hidden ? 1 : 0;
    
    return 1;
}

ogt_vox_rgba_c ogt_vox_scene_get_palette_color(const ogt_vox_scene_wrapper* scene, uint32_t color_index) {
    ogt_vox_rgba_c color = {0, 0, 0, 0};
    
    if (scene && color_index < 256) {
        const ogt_vox_rgba& palette_color = scene->scene->palette.color[color_index];
        color.r = palette_color.r;
        color.g = palette_color.g;
        color.b = palette_color.b;
        color.a = palette_color.a;
    }
    
    return color;
}

const ogt_vox_rgba_c* ogt_vox_scene_get_palette_c(const ogt_vox_scene_wrapper* scene) {
    if (!scene) {
        return nullptr;
    }

    return reinterpret_cast<const ogt_vox_rgba_c*>(scene->scene->palette.color);
}

int ogt_vox_scene_get_instance_transform_global(const ogt_vox_scene_wrapper* scene, uint32_t instance_index, ogt_vox_transform_c* out_transform) {
    if (!scene || !out_transform || instance_index >= scene->scene->num_instances) {
        return 0;
    }

    const ogt_vox_instance* instance = &scene->scene->instances[instance_index];
    ogt_vox_transform transform = ogt_vox_sample_instance_transform_global(instance, 0, scene->scene);
    phpglfw_pack_transform(out_transform, transform);
    return 1;
}

int ogt_vox_scene_get_instance_transform_local(const ogt_vox_scene_wrapper* scene, uint32_t instance_index, ogt_vox_transform_c* out_transform) {
    if (!scene || !out_transform || instance_index >= scene->scene->num_instances) {
        return 0;
    }

    const ogt_vox_instance* instance = &scene->scene->instances[instance_index];
    ogt_vox_transform transform = ogt_vox_sample_instance_transform_local(instance, 0);
    phpglfw_pack_transform(out_transform, transform);
    return 1;
}

int ogt_vox_scene_get_group_transform_global(const ogt_vox_scene_wrapper* scene, uint32_t group_index, ogt_vox_transform_c* out_transform) {
    if (!scene || !out_transform || group_index >= scene->scene->num_groups) {
        return 0;
    }

    const ogt_vox_group* group = &scene->scene->groups[group_index];
    ogt_vox_transform transform = ogt_vox_sample_group_transform_global(group, 0, scene->scene);
    phpglfw_pack_transform(out_transform, transform);
    return 1;
}

int ogt_vox_scene_get_group_transform_local(const ogt_vox_scene_wrapper* scene, uint32_t group_index, ogt_vox_transform_c* out_transform) {
    if (!scene || !out_transform || group_index >= scene->scene->num_groups) {
        return 0;
    }

    const ogt_vox_group* group = &scene->scene->groups[group_index];
    ogt_vox_transform transform = ogt_vox_sample_group_transform_local(group, 0);
    phpglfw_pack_transform(out_transform, transform);
    return 1;
}

// mesh generation functions
ogt_mesh_c* ogt_vox_model_generate_mesh_simple_c(const uint8_t* voxel_data, uint32_t size_x, uint32_t size_y, uint32_t size_z, const ogt_vox_rgba_c* palette) {
    if (!voxel_data || !palette) {
        return nullptr;
    }

    ogt_mesh_rgba cpp_palette[256];
    phpglfw_copy_palette(cpp_palette, palette);

    ogt_voxel_meshify_context ctx = {};
    ogt_mesh* cpp_mesh = ogt_mesh_from_paletted_voxels_simple(&ctx, voxel_data, size_x, size_y, size_z, cpp_palette);

    return phpglfw_convert_cpp_mesh(&ctx, cpp_mesh);
}

ogt_mesh_c* ogt_vox_model_generate_mesh_greedy_c(const uint8_t* voxel_data, uint32_t size_x, uint32_t size_y, uint32_t size_z, const ogt_vox_rgba_c* palette) {
    if (!voxel_data || !palette) {
        return nullptr;
    }

    ogt_mesh_rgba cpp_palette[256];
    phpglfw_copy_palette(cpp_palette, palette);

    ogt_voxel_meshify_context ctx = {};
    ogt_mesh* cpp_mesh = ogt_mesh_from_paletted_voxels_greedy(&ctx, voxel_data, size_x, size_y, size_z, cpp_palette);

    return phpglfw_convert_cpp_mesh(&ctx, cpp_mesh);
}

ogt_mesh_c* ogt_vox_model_generate_mesh_polygon_c(const uint8_t* voxel_data, uint32_t size_x, uint32_t size_y, uint32_t size_z, const ogt_vox_rgba_c* palette) {
    if (!voxel_data || !palette) {
        return nullptr;
    }

    ogt_mesh_rgba cpp_palette[256];
    phpglfw_copy_palette(cpp_palette, palette);

    ogt_voxel_meshify_context ctx = {};
    ogt_mesh* cpp_mesh = ogt_mesh_from_paletted_voxels_polygon(&ctx, voxel_data, size_x, size_y, size_z, cpp_palette);

    return phpglfw_convert_cpp_mesh(&ctx, cpp_mesh);
}

void ogt_vox_mesh_destroy_c(ogt_mesh_c* mesh) {
    if (mesh) {
        delete[] mesh->vertices;
        delete[] mesh->indices;
        delete mesh;
    }
}

} // extern "C"