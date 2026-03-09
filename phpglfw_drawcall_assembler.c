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
#include "phpglfw_drawcall_assembler.h"
#include "phpglfw_arginfo.h"

#include <math.h>
#include <string.h>
#include "cvector.h"

zend_class_entry *phpglfw_drawcall_assembler_ce;

zend_class_entry *phpglfw_get_drawcall_assembler_ce()
{
    return phpglfw_drawcall_assembler_ce;
}

phpglfw_drawcall_assembler_object *phpglfw_drawcall_assembler_objectptr_from_zobj_p(zend_object *obj)
{
    return (phpglfw_drawcall_assembler_object *)((char *)(obj)-XtOffsetOf(phpglfw_drawcall_assembler_object, std));
}

static zend_object_handlers phpglfw_drawcall_assembler_object_handlers;

static float phpglfw_drawcall_distance_to_camera(phpglfw_math_vec3_object *camera_pos, const mat4x4 transform);
static void phpglfw_drawcall_store_plane(vec4 dest, float a, float b, float c, float d);
static void phpglfw_drawcall_extract_frustum(phpglfw_drawcall_assembler_object *intern);
static uint32_t phpglfw_drawcall_collect_visible_indices(phpglfw_drawcall_assembler_object *intern, uint32_t *visible_indices);
static uint32_t phpglfw_drawcall_select_lod(phpglfw_drawcall_assembler_object *intern, phpglfw_drawcall_instance *instance, float distance);
static void phpglfw_drawcall_update_instance_lod(phpglfw_drawcall_assembler_object *intern, phpglfw_drawcall_instance *instance);
static void phpglfw_drawcall_refresh_instance_lods(phpglfw_drawcall_assembler_object *intern);

static inline void phpglfw_drawcall_release_zval(zval *value)
{
    if (!Z_ISUNDEF(*value))
    {
        zval_ptr_dtor(value);
        ZVAL_UNDEF(value);
    }
}

static zend_object *phpglfw_drawcall_assembler_create_object(zend_class_entry *class_type)
{
    phpglfw_drawcall_assembler_object *intern = zend_object_alloc(sizeof(phpglfw_drawcall_assembler_object), class_type);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);
    intern->std.handlers = &phpglfw_drawcall_assembler_object_handlers;

    // initialize all pointers to null
    intern->command_buffer = NULL;
    intern->instance_transform_buffer = NULL;
    intern->instance_meta_buffer = NULL;
    intern->instance_payload_buffer = NULL;
    intern->meshes = NULL;
    intern->instances = NULL;
    intern->visible_index_buffer = NULL;
    intern->camera_position = NULL;
    intern->view_matrix = NULL;
    intern->projection_matrix = NULL;
    ZVAL_UNDEF(&intern->payload_data_buffer_zv);
    ZVAL_UNDEF(&intern->camera_position_zv);
    ZVAL_UNDEF(&intern->view_matrix_zv);
    ZVAL_UNDEF(&intern->projection_matrix_zv);

    memset(intern->frustum_planes, 0, sizeof(intern->frustum_planes));

    intern->mesh_capacity = 0;
    intern->mesh_count = 0;
    intern->instance_capacity = 0;
    intern->instance_count = 0;
    intern->has_frustum = false;
    intern->sort_mode = PHPGLFW_SORT_NONE;
    intern->auto_instancing = true;
    intern->final_command_count = 0;
    intern->final_instance_count = 0;

    // rendering dispatch
    intern->rendering_transform_buffer_data = NULL;
    intern->rendering_payload_buffer_data = NULL;

    return &intern->std;
}

static void phpglfw_drawcall_assembler_free_handler(zend_object *object)
{
    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(object);

    // release internal-only zvals
    phpglfw_drawcall_release_zval(&intern->payload_data_buffer_zv);
    phpglfw_drawcall_release_zval(&intern->camera_position_zv);
    phpglfw_drawcall_release_zval(&intern->view_matrix_zv);
    phpglfw_drawcall_release_zval(&intern->projection_matrix_zv);

    // free mesh array
    if (intern->meshes) {
        efree(intern->meshes);
    }

    // free instance array
    if (intern->instances) {
        efree(intern->instances);
    }

    if (intern->visible_index_buffer) {
        cvector_free(intern->visible_index_buffer);
    }

    // rendering dispatch
    cvector_free(intern->rendering_transform_buffer_data);
    cvector_free(intern->rendering_payload_buffer_data);

    // we do own the internal VBOs, so make sure to delete them
    if (intern->internal_transform_vbo != 0) {
        glDeleteBuffers(1, &intern->internal_transform_vbo);
    }
    if (intern->internal_payload_vbo != 0) {
        glDeleteBuffers(1, &intern->internal_payload_vbo);
    }

    zend_object_std_dtor(&intern->std);
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, __construct)
{
    zend_long initial_mesh_capacity = 256;
    zend_long initial_instance_capacity = 2048;
    zend_long initial_command_capacity = 512;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|lll",
        &initial_mesh_capacity,
        &initial_instance_capacity,
        &initial_command_capacity
    ) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    // allocate mesh storage
    intern->mesh_capacity = initial_mesh_capacity;
    intern->meshes = ecalloc(intern->mesh_capacity, sizeof(phpglfw_drawcall_mesh));

    // allocate instance storage
    intern->instance_capacity = initial_instance_capacity;
    intern->instances = ecalloc(intern->instance_capacity, sizeof(phpglfw_drawcall_instance));

    // for readonly properties, we must write directly to the properties table
    // zend_update_property doesn't work with readonly properties declared in stubs
    zend_object *this_obj = Z_OBJ_P(ZEND_THIS);
    zval *prop;

    // command buffer
    prop = OBJ_PROP_NUM(this_obj, 0);
    object_init_ex(prop, phpglfw_get_buffer_gluint_ce());
    intern->command_buffer = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(prop));
    cvector_reserve(intern->command_buffer->vec, initial_command_capacity * PHPGLFW_COMMAND_STRIDE);

    // instance transform buffer
    prop = OBJ_PROP_NUM(this_obj, 1);
    object_init_ex(prop, phpglfw_get_buffer_glfloat_ce());
    intern->instance_transform_buffer = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(prop));
    cvector_reserve(intern->instance_transform_buffer->vec, initial_instance_capacity * PHPGLFW_TRANSFORM_STRIDE);

    // instance meta buffer
    prop = OBJ_PROP_NUM(this_obj, 2);
    object_init_ex(prop, phpglfw_get_buffer_gluint_ce());
    intern->instance_meta_buffer = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(prop));
    cvector_reserve(intern->instance_meta_buffer->vec, initial_instance_capacity * PHPGLFW_INSTANCE_META_STRIDE);

    // instance payload buffer
    prop = OBJ_PROP_NUM(this_obj, 3);
    object_init_ex(prop, phpglfw_get_buffer_glfloat_ce());
    intern->instance_payload_buffer = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(prop));

    // stride constants
    prop = OBJ_PROP_NUM(this_obj, 4);
    ZVAL_LONG(prop, PHPGLFW_COMMAND_STRIDE);

    prop = OBJ_PROP_NUM(this_obj, 5);
    ZVAL_LONG(prop, PHPGLFW_TRANSFORM_STRIDE);

    prop = OBJ_PROP_NUM(this_obj, 6);
    ZVAL_LONG(prop, PHPGLFW_INSTANCE_META_STRIDE);

    // initialize internal VBO (will be created on first use)
    intern->internal_transform_vbo = 0;
    intern->internal_payload_vbo = 0;
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, setCameraData)
{
    zval *camera_position = NULL;
    zval *view_matrix = NULL;
    zval *projection_matrix = NULL;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|zzz", &camera_position, &view_matrix, &projection_matrix) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    // store camera data if provided
    if (camera_position && Z_TYPE_P(camera_position) == IS_OBJECT)
    {
        phpglfw_drawcall_release_zval(&intern->camera_position_zv);
        ZVAL_OBJ_COPY(&intern->camera_position_zv, Z_OBJ_P(camera_position));
        intern->camera_position = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ(intern->camera_position_zv));
    }
    else
    {
        phpglfw_drawcall_release_zval(&intern->camera_position_zv);
        intern->camera_position = NULL;
    }

    if (view_matrix && Z_TYPE_P(view_matrix) == IS_OBJECT)
    {
        phpglfw_drawcall_release_zval(&intern->view_matrix_zv);
        ZVAL_OBJ_COPY(&intern->view_matrix_zv, Z_OBJ_P(view_matrix));
        intern->view_matrix = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ(intern->view_matrix_zv));
    }
    else
    {
        phpglfw_drawcall_release_zval(&intern->view_matrix_zv);
        intern->view_matrix = NULL;
    }

    if (projection_matrix && Z_TYPE_P(projection_matrix) == IS_OBJECT)
    {
        phpglfw_drawcall_release_zval(&intern->projection_matrix_zv);
        ZVAL_OBJ_COPY(&intern->projection_matrix_zv, Z_OBJ_P(projection_matrix));
        intern->projection_matrix = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ(intern->projection_matrix_zv));
    }
    else
    {
        phpglfw_drawcall_release_zval(&intern->projection_matrix_zv);
        intern->projection_matrix = NULL;
    }

    if (intern->view_matrix && intern->projection_matrix)
    {
        phpglfw_drawcall_extract_frustum(intern);
    }
    else
    {
        intern->has_frustum = false;
    }
}

static void phpglfw_drawcall_store_plane(vec4 dest, float a, float b, float c, float d)
{
    float len = sqrtf((a * a) + (b * b) + (c * c));
    if (len > 0.0f)
    {
        dest[0] = a / len;
        dest[1] = b / len;
        dest[2] = c / len;
        dest[3] = d / len;
    }
    else
    {
        dest[0] = a;
        dest[1] = b;
        dest[2] = c;
        dest[3] = d;
    }
}

static void phpglfw_drawcall_extract_frustum(phpglfw_drawcall_assembler_object *intern)
{
    mat4x4 clip;
    mat4x4_mul(clip, intern->projection_matrix->data, intern->view_matrix->data);

    float m[4][4];
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            m[row][col] = clip[col][row];
        }
    }

    // left
    phpglfw_drawcall_store_plane(
        intern->frustum_planes[0],
        m[3][0] + m[0][0],
        m[3][1] + m[0][1],
        m[3][2] + m[0][2],
        m[3][3] + m[0][3]
    );

    // right
    phpglfw_drawcall_store_plane(
        intern->frustum_planes[1],
        m[3][0] - m[0][0],
        m[3][1] - m[0][1],
        m[3][2] - m[0][2],
        m[3][3] - m[0][3]
    );

    // bottom
    phpglfw_drawcall_store_plane(
        intern->frustum_planes[2],
        m[3][0] + m[1][0],
        m[3][1] + m[1][1],
        m[3][2] + m[1][2],
        m[3][3] + m[1][3]
    );

    // top
    phpglfw_drawcall_store_plane(
        intern->frustum_planes[3],
        m[3][0] - m[1][0],
        m[3][1] - m[1][1],
        m[3][2] - m[1][2],
        m[3][3] - m[1][3]
    );

    // near
    phpglfw_drawcall_store_plane(
        intern->frustum_planes[4],
        m[3][0] + m[2][0],
        m[3][1] + m[2][1],
        m[3][2] + m[2][2],
        m[3][3] + m[2][3]
    );

    // far
    phpglfw_drawcall_store_plane(
        intern->frustum_planes[5],
        m[3][0] - m[2][0],
        m[3][1] - m[2][1],
        m[3][2] - m[2][2],
        m[3][3] - m[2][3]
    );

    intern->has_frustum = true;
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, registerMesh)
{
    zend_long vao_id;
    zend_long vertex_offset = 0, vertex_count = 0;
    zend_long index_offset = 0, index_count = 0;
    zval *aabb_min = NULL, *aabb_max = NULL;
    zend_long material_hint = 0;
    zend_long primitive = 0x0004; // gl_triangles

    if (zend_parse_parameters(ZEND_NUM_ARGS(), 
        "l|llllzzll",
        &vao_id,
        &vertex_offset, &vertex_count,
        &index_offset, &index_count,
        &aabb_min, &aabb_max,
        &material_hint, 
        &primitive
    ) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    // resize mesh array if needed
    if (intern->mesh_count >= intern->mesh_capacity) {
        intern->mesh_capacity *= 2;
        intern->meshes = erealloc(intern->meshes, intern->mesh_capacity * sizeof(phpglfw_drawcall_mesh));
    }

    phpglfw_drawcall_mesh *mesh = &intern->meshes[intern->mesh_count];
    mesh->vao_id = vao_id;
    mesh->vertex_offset = vertex_offset;
    mesh->vertex_count = vertex_count;
    mesh->index_offset = index_offset;
    mesh->index_count = index_count;
    mesh->material_hint = material_hint;
    mesh->primitive = primitive;

    // store bounding box if provided
    if (aabb_min && Z_TYPE_P(aabb_min) == IS_OBJECT) {
        mesh->aabb_min = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(aabb_min));
    } else {
        mesh->aabb_min = NULL;
    }

    if (aabb_max && Z_TYPE_P(aabb_max) == IS_OBJECT) {
        mesh->aabb_max = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(aabb_max));
    } else {
        mesh->aabb_max = NULL;
    }

    if (mesh->aabb_min && mesh->aabb_max)
    {
        mesh->has_bounds = true;
        float half_extents[3];

        for (int axis = 0; axis < 3; axis++)  {
            float min_val = mesh->aabb_min->data[axis];
            float max_val = mesh->aabb_max->data[axis];
            mesh->bounds_center[axis] = (min_val + max_val) * 0.5f;
            half_extents[axis] = (max_val - min_val) * 0.5f;
        }

        mesh->bounds_radius = sqrtf(
            (half_extents[0] * half_extents[0]) +
            (half_extents[1] * half_extents[1]) +
            (half_extents[2] * half_extents[2])
        );
    }
    else
    {
        mesh->has_bounds = false;
        mesh->bounds_radius = 0.0f;
        mesh->bounds_center[0] = 0.0f;
        mesh->bounds_center[1] = 0.0f;
        mesh->bounds_center[2] = 0.0f;
    }

    // initialize lod data
    mesh->lod_distances = NULL;
    mesh->lod_handles = NULL;

    uint32_t handle = intern->mesh_count;
    intern->mesh_count++;

    RETURN_LONG(handle);
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, setLodTable)
{
    zend_long mesh_handle;
    zval *distance_thresholds, *mesh_handles;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lzz", &mesh_handle, &distance_thresholds, &mesh_handles) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    if (mesh_handle >= intern->mesh_count) {
        zend_throw_error(NULL, "invalid mesh handle");
        RETURN_THROWS();
    }

    phpglfw_drawcall_mesh *mesh = &intern->meshes[mesh_handle];

    if (Z_TYPE_P(distance_thresholds) == IS_OBJECT) {
        mesh->lod_distances = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ_P(distance_thresholds));
    }
    else {
        mesh->lod_distances = NULL;
    }

    if (Z_TYPE_P(mesh_handles) == IS_OBJECT) {
        mesh->lod_handles = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ_P(mesh_handles));
    }
    else {
        mesh->lod_handles = NULL;
    }
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, setMeshMaterial)
{
    zend_long mesh_handle, material_id;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &mesh_handle, &material_id) == FAILURE)  {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    if (mesh_handle >= intern->mesh_count) {
        zend_throw_error(NULL, "invalid mesh handle");
        RETURN_THROWS();
    }

    intern->meshes[mesh_handle].material_hint = material_id;
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, setAutoInstancing)
{
    zend_bool enabled;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "b", &enabled) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));
    intern->auto_instancing = enabled;
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, setFrustumPlanes)
{
    zval *left, *right, *bottom, *top, *near, *far;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "zzzzzz", &left, &right, &bottom, &top, &near, &far) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    phpglfw_math_vec4_object *planes[6] = {
        phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(left)),
        phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(right)),
        phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(bottom)),
        phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(top)),
        phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(near)),
        phpglfw_math_vec4_objectptr_from_zobj_p(Z_OBJ_P(far)),
    };

    for (int i = 0; i < 6; i++) {
        memcpy(intern->frustum_planes[i], planes[i]->data, sizeof(vec4));
    }

    intern->has_frustum = true;
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, setSortMode)
{
    zend_long mode;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l", &mode) == FAILURE)
    {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));
    intern->sort_mode = mode;
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, clearInstances)
{
    if (zend_parse_parameters_none() == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));
    intern->instance_count = 0;
    intern->final_command_count = 0;
    intern->final_instance_count = 0;

    cvector_set_size(intern->command_buffer->vec, 0);
    cvector_set_size(intern->instance_transform_buffer->vec, 0);
    cvector_set_size(intern->instance_meta_buffer->vec, 0);
    cvector_set_size(intern->instance_payload_buffer->vec, 0);
}

static float phpglfw_drawcall_distance_to_camera_sq(phpglfw_math_vec3_object *camera_pos, const mat4x4 transform)
{
    const float dx = transform[3][0] - camera_pos->data[0];
    const float dy = transform[3][1] - camera_pos->data[1];
    const float dz = transform[3][2] - camera_pos->data[2];

    return dx * dx + dy * dy + dz * dz;
}

static float phpglfw_drawcall_distance_to_camera(phpglfw_math_vec3_object *camera_pos, const mat4x4 transform)
{
    return sqrtf(phpglfw_drawcall_distance_to_camera_sq(camera_pos, transform));
}

static uint32_t phpglfw_drawcall_collect_visible_indices(phpglfw_drawcall_assembler_object *intern, uint32_t *visible_indices)
{
    const uint32_t total_instances = intern->instance_count;
    const phpglfw_drawcall_instance * const instances = intern->instances;
    const phpglfw_drawcall_mesh * const meshes = intern->meshes;

    // if there is no frustum, we consider all instances to be visible
    if (!intern->has_frustum) {
        for (uint32_t i = 0; i < total_instances; i++) {
            visible_indices[i] = i;
        }

        return total_instances;
    }

    uint32_t write_index = 0;
    
    // get the frustum planes into stack memory (i think this is faster, but to be honest, i did not benchmark it..)
    const float frustum[6][4] = {
        {intern->frustum_planes[0][0], intern->frustum_planes[0][1], intern->frustum_planes[0][2], intern->frustum_planes[0][3]},
        {intern->frustum_planes[1][0], intern->frustum_planes[1][1], intern->frustum_planes[1][2], intern->frustum_planes[1][3]},
        {intern->frustum_planes[2][0], intern->frustum_planes[2][1], intern->frustum_planes[2][2], intern->frustum_planes[2][3]},
        {intern->frustum_planes[3][0], intern->frustum_planes[3][1], intern->frustum_planes[3][2], intern->frustum_planes[3][3]},
        {intern->frustum_planes[4][0], intern->frustum_planes[4][1], intern->frustum_planes[4][2], intern->frustum_planes[4][3]},
        {intern->frustum_planes[5][0], intern->frustum_planes[5][1], intern->frustum_planes[5][2], intern->frustum_planes[5][3]}
    };
    
    for (uint32_t read_index = 0; read_index < total_instances; read_index++)
    {
        const phpglfw_drawcall_instance * const instance = &instances[read_index];
        
        // fast path for ignore culling flag
        if (instance->flags & PHPGLFW_FLAG_IGNORE_CULLING) {
            visible_indices[write_index++] = read_index;
            continue;
        }
        
        const phpglfw_drawcall_mesh * const mesh = &meshes[instance->mesh_handle];
        
        float cx = instance->transform[3][0];
        float cy = instance->transform[3][1];
        float cz = instance->transform[3][2];
        float scaled_radius = mesh->bounds_radius;
        
        if (mesh->has_bounds)
        {
            // transform mesh center to world space
            const float local_x = mesh->bounds_center[0];
            const float local_y = mesh->bounds_center[1];
            const float local_z = mesh->bounds_center[2];
            
            cx = instance->transform[0][0] * local_x + instance->transform[1][0] * local_y + instance->transform[2][0] * local_z + instance->transform[3][0];
            cy = instance->transform[0][1] * local_x + instance->transform[1][1] * local_y + instance->transform[2][1] * local_z + instance->transform[3][1];
            cz = instance->transform[0][2] * local_x + instance->transform[1][2] * local_y + instance->transform[2][2] * local_z + instance->transform[3][2];
            
            // compute uniform scale factor
            const mat4x4 * const t = &instance->transform;
            const float scale_x_sq = (*t)[0][0] * (*t)[0][0] + (*t)[0][1] * (*t)[0][1] + (*t)[0][2] * (*t)[0][2];
            const float scale_y_sq = (*t)[1][0] * (*t)[1][0] + (*t)[1][1] * (*t)[1][1] + (*t)[1][2] * (*t)[1][2];
            const float scale_z_sq = (*t)[2][0] * (*t)[2][0] + (*t)[2][1] * (*t)[2][1] + (*t)[2][2] * (*t)[2][2];
            const float max_scale_sq = fmaxf(scale_x_sq, fmaxf(scale_y_sq, scale_z_sq));
            scaled_radius *= sqrtf(max_scale_sq);
        }
        
        // frustum test
        bool is_visible = true;
        for (int plane = 0; plane < 6 && is_visible; plane++)
        {
            const float distance = frustum[plane][0] * cx + frustum[plane][1] * cy + frustum[plane][2] * cz + frustum[plane][3];
            is_visible = distance >= -scaled_radius;
        }
        
        if (is_visible) {
            visible_indices[write_index++] = read_index;
        }
    }
    
    return write_index;
}

static zend_always_inline uint32_t phpglfw_drawcall_select_lod(
    phpglfw_drawcall_assembler_object *intern,
    phpglfw_drawcall_instance *instance,
    float distance
) {
    if (!intern->camera_position) {
        return instance->base_mesh_handle;
    }

    // check cache first
    const float distance_diff = fabsf(distance - instance->cached_lod_distance);
    if (distance_diff < PHPGLFW_LOD_CACHE_EPSILON && instance->cached_lod_handle != 0) {
        return instance->cached_lod_handle;
    }

    const uint32_t base_handle = instance->base_mesh_handle;
    if (base_handle >= intern->mesh_count) {
        return base_handle;
    }

    const phpglfw_drawcall_mesh *mesh = &intern->meshes[base_handle];

    if (!mesh->lod_distances || !mesh->lod_handles)
    {
        instance->cached_lod_distance = distance;
        instance->cached_lod_handle = base_handle;
        return base_handle;
    }

    const uint32_t lod_count = (uint32_t)cvector_size(mesh->lod_distances->vec);
    const uint32_t handle_count = (uint32_t)cvector_size(mesh->lod_handles->vec);
    if (lod_count == 0 || handle_count == 0)
    {
        instance->cached_lod_distance = distance;
        instance->cached_lod_handle = base_handle;
        return base_handle;
    }

    const uint32_t limit = lod_count < handle_count ? lod_count : handle_count;
    if (limit == 0)
    {
        instance->cached_lod_distance = distance;
        instance->cached_lod_handle = base_handle;
        return base_handle;
    }

    const float clamped_distance = distance < 0.0f ? 0.0f : distance;
    uint32_t selected_handle = base_handle;
    
    // optimize loop by avoiding bounds checks where possible
    const float *distances = mesh->lod_distances->vec;
    const uint32_t *handles = mesh->lod_handles->vec;
    
    for (uint32_t i = 0; i < limit; i++)
    {
        const float threshold = distances[i];
        const uint32_t alternative = handles[i];

        if (alternative >= intern->mesh_count)
        {
            continue;
        }

        if (clamped_distance >= threshold)
        {
            selected_handle = alternative;
        }
        else
        {
            break;
        }
    }

    // cache result
    instance->cached_lod_distance = distance;
    instance->cached_lod_handle = selected_handle;
    
    return selected_handle;
}

static inline uint64_t make_sort_key_opaque(
    uint32_t pass, uint32_t program_id, uint32_t material_id,
    uint32_t vao_id, uint32_t mesh_id, uint32_t depth_bucket
){
    uint64_t k = 0;
    k |= ((uint64_t)(pass        & SK_MASK(SK_PASS_BITS)))  << SK_PASS_SHIFT;
    k |= ((uint64_t)(program_id  & SK_MASK(SK_PROG_BITS)))  << SK_PROG_SHIFT;
    k |= ((uint64_t)(material_id & SK_MASK(SK_MAT_BITS)))   << SK_MAT_SHIFT;
    k |= ((uint64_t)(vao_id      & SK_MASK(SK_VAO_BITS)))   << SK_VAO_SHIFT;
    k |= ((uint64_t)(mesh_id     & SK_MASK(SK_MESH_BITS)))  << SK_MESH_SHIFT;
    k |= ((uint64_t)(depth_bucket& SK_MASK(SK_DEPTH_BITS))) << SK_DEPTH_SHIFT;
    return k;
}

static inline uint64_t make_sort_key_transparent(
    uint32_t pass, uint32_t program_id, uint32_t material_id,
    uint32_t vao_id, uint32_t mesh_id, uint32_t depth_bucket
){
    uint32_t depth_rev = (SK_MASK(SK_DEPTH_BITS) - (depth_bucket & SK_MASK(SK_DEPTH_BITS)));
    uint64_t k = 0;
    k |= ((uint64_t)(pass        & SK_MASK(SK_PASS_BITS)))  << SK_PASS_SHIFT;
    k |= ((uint64_t)(depth_rev   & SK_MASK(SK_DEPTH_BITS))) << SK_PROG_SHIFT;
    k |= ((uint64_t)(program_id  & SK_MASK(SK_PROG_BITS)))  << SK_MAT_SHIFT;
    k |= ((uint64_t)(material_id & SK_MASK(SK_MAT_BITS)))   << SK_VAO_SHIFT;
    k |= ((uint64_t)(vao_id      & SK_MASK(SK_VAO_BITS)))   << SK_MESH_SHIFT;
    k |= ((uint64_t)(mesh_id     & SK_MASK(SK_MESH_BITS)))  << SK_DEPTH_SHIFT;
    return k;
}

static inline uint64_t phpglfw_drawcall_make_group_key(
    uint32_t pass, uint32_t program_id, uint32_t material_id,
    uint32_t mesh_id, uint32_t flags
){
    uint64_t k = 0;
    k |= ((uint64_t)(pass        & SK_MASK(SK_PASS_BITS)))  << SK_PASS_SHIFT;
    k |= ((uint64_t)(program_id  & SK_MASK(SK_PROG_BITS)))  << SK_PROG_SHIFT;
    k |= ((uint64_t)(material_id & SK_MASK(SK_MAT_BITS)))   << SK_MAT_SHIFT;
    k |= ((uint64_t)(mesh_id     & SK_MASK(SK_MESH_BITS)))  << SK_MESH_SHIFT;
    k |= ((uint64_t)(flags       & SK_MASK(SK_DEPTH_BITS))) << SK_DEPTH_SHIFT;
    return k;
}

static inline void phpglfw_drawcall_compute_sort_key(phpglfw_drawcall_assembler_object *intern, phpglfw_drawcall_instance *instance)
{
    phpglfw_drawcall_mesh *mesh = &intern->meshes[instance->mesh_handle];

    instance->group_key = phpglfw_drawcall_make_group_key(
        instance->pass,
        instance->program_id,
        instance->material_id,
        instance->mesh_handle,
        instance->flags
    );

    // quantize depth to 0-1023 range (clamped at 1000 units) for 10-bit field
    float distance = instance->sort_distance + instance->sort_bias;
    uint32_t depth_bucket = (uint32_t)(fminf(distance / 1000.0f, 1.0f) * 1023.0f);

    const bool is_transparent = (instance->pass == PHPGLFW_PASS_TRANSPARENT);

    if (is_transparent) {
        instance->sort_key = make_sort_key_transparent(
            instance->pass,
            instance->program_id,
            instance->material_id,
            mesh->vao_id,
            instance->mesh_handle,
            depth_bucket
        );
    } else {
        instance->sort_key = make_sort_key_opaque(
            instance->pass,
            instance->program_id,
            instance->material_id,
            mesh->vao_id,
            instance->mesh_handle,
            depth_bucket
        );
    }
}

static inline void phpglfw_drawcall_set_instance_distance(phpglfw_drawcall_assembler_object *intern, phpglfw_drawcall_instance *instance, float distance)
{
    instance->sort_distance = distance;
}

static zend_always_inline void phpglfw_drawcall_update_instance_lod(phpglfw_drawcall_assembler_object *intern, phpglfw_drawcall_instance *instance)
{
    instance->mesh_handle = phpglfw_drawcall_select_lod(intern, instance, instance->sort_distance);

    // rebuild sort key to reflect new mesh handle
    phpglfw_drawcall_compute_sort_key(intern, instance);
}

static void phpglfw_drawcall_refresh_instance_lods(phpglfw_drawcall_assembler_object *intern)
{
    if (intern->instance_count == 0) {
        return;
    }

    for (uint32_t i = 0; i < intern->instance_count; i++) {
        phpglfw_drawcall_update_instance_lod(intern, &intern->instances[i]);
    }
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, submit)
{
    zend_long mesh_handle, material_id;
    zval *transform;
    zend_long pass = PHPGLFW_PASS_OPAQUE;
    zend_long program_id = 0;
    zend_long flags = 0;
    double sort_bias = 0.0;
    zend_long user_id = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lzl|llldl",  &mesh_handle, &transform, &material_id, &pass, &program_id, &flags, &sort_bias, &user_id) == FAILURE){
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    if (mesh_handle >= intern->mesh_count) {
        zend_throw_error(NULL, "invalid mesh handle");
        RETURN_THROWS();
    }

    // resize instance array if needed
    if (intern->instance_count >= intern->instance_capacity)  {
        intern->instance_capacity *= 2;
        intern->instances = erealloc(intern->instances, intern->instance_capacity * sizeof(phpglfw_drawcall_instance));
    }

    phpglfw_drawcall_instance *instance = &intern->instances[intern->instance_count];
    const phpglfw_drawcall_mesh *mesh = &intern->meshes[mesh_handle];
    instance->base_mesh_handle = (uint32_t)mesh_handle;
    instance->mesh_handle = (uint32_t)mesh_handle;
    instance->material_id = material_id;
    instance->pass = (uint32_t)(pass & SK_MASK(SK_PASS_BITS));
    instance->program_id = program_id;
    instance->user_id = user_id;
    instance->flags = flags;
    instance->sort_bias = sort_bias;
    instance->sort_distance = 0.0f;
    
    instance->cached_lod_distance = -1.0f;
    instance->cached_lod_handle = 0;

    phpglfw_math_mat4_object *transform_obj = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(transform));
    mat4x4_dup(instance->transform, transform_obj->data);

    phpglfw_drawcall_compute_sort_key(intern, instance);

    intern->instance_count++;
}

static const phpglfw_drawcall_instance *instances_global;
static int phpglfw_index_compare_by_sort_key(const void *a, const void *b)
{
    const uint32_t idx_a = *(const uint32_t *)a;
    const uint32_t idx_b = *(const uint32_t *)b;
    const uint64_t key_a = instances_global[idx_a].sort_key;
    const uint64_t key_b = instances_global[idx_b].sort_key;
    return (key_a < key_b) ? -1 : ((key_a > key_b) ? 1 : 0);
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, build)
{
    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    // clear output buffers
    cvector_set_size(intern->command_buffer->vec, 0);
    cvector_set_size(intern->instance_transform_buffer->vec, 0);
    cvector_set_size(intern->instance_meta_buffer->vec, 0);

    uint32_t command_count = 0;
    uint32_t instance_offset = 0;
    uint32_t visible_count = intern->instance_count;
    uint32_t *visible_indices = NULL;
    uint32_t stack_buffer[PHPGLFW_SMALL_BUFFER_THRESHOLD];
    const bool use_frustum_culling = intern->has_frustum && visible_count > 0;
    const bool use_stack_allocation = visible_count <= PHPGLFW_SMALL_BUFFER_THRESHOLD;

    if (use_stack_allocation) {
        visible_indices = stack_buffer;
    }
    else
    {
        // ensure the index buffer is allocated and large enough
        if (!intern->visible_index_buffer) {
            cvector_reserve(intern->visible_index_buffer, visible_count);
        }
        else if (cvector_capacity(intern->visible_index_buffer) < visible_count) {
            cvector_reserve(intern->visible_index_buffer, visible_count);
        }
        visible_indices = intern->visible_index_buffer;
    }

    // collect the visible instance indices
    // aka do frustum culling
    visible_count = phpglfw_drawcall_collect_visible_indices(intern, visible_indices);

    // nothing visible = nothing to do
    if (visible_count == 0)  {
        intern->final_command_count = 0;
        intern->final_instance_count = 0;
        RETURN_LONG(0);
    }

    const size_t total_transform_floats = (size_t)visible_count * PHPGLFW_TRANSFORM_STRIDE;
    const size_t total_meta_uints = (size_t)visible_count * PHPGLFW_INSTANCE_META_STRIDE;
    cvector_ensure(intern->instance_transform_buffer->vec, total_transform_floats);
    cvector_ensure(intern->instance_meta_buffer->vec, total_meta_uints);
    
    // setup payload buffer if bound
    float *payload_write_ptr = NULL;
    size_t payload_cursor = 0;
    if (!Z_ISUNDEF(intern->payload_data_buffer_zv)) {
        const size_t total_payload_floats = (size_t)visible_count * intern->payload_data_stride;
        cvector_ensure(intern->instance_payload_buffer->vec, total_payload_floats);
        payload_write_ptr = intern->instance_payload_buffer->vec;
    }
    
    float *transform_write_ptr = intern->instance_transform_buffer->vec;
    uint32_t *meta_write_ptr = intern->instance_meta_buffer->vec;
    size_t transform_cursor = 0;
    size_t meta_cursor = 0;

    const phpglfw_drawcall_instance * const instances = intern->instances;
    const phpglfw_drawcall_mesh * const meshes = intern->meshes;

    // compute the distance to camera for each visible instance
    if (intern->camera_position)
    {
        for (uint32_t i = 0; i < visible_count; i++)
        {
            const uint32_t instance_index = visible_indices[i];
            phpglfw_drawcall_instance *instance = &instances[instance_index];
            
            // calculate distance to camera and apply it to the instance
            float distance_sq = phpglfw_drawcall_distance_to_camera_sq(intern->camera_position, instance->transform);
            phpglfw_drawcall_set_instance_distance(intern, instance, sqrtf(distance_sq));
            phpglfw_drawcall_compute_sort_key(intern, instance);
        }
    }

    // eval LOD selection
    phpglfw_drawcall_refresh_instance_lods(intern);

    // sort the visible indices by precomputed sort keys
    if (visible_count > 1) {
        instances_global = instances;
        qsort(visible_indices, visible_count, sizeof(uint32_t), phpglfw_index_compare_by_sort_key);
    }
    
    // build draw call commands
    for (uint32_t base_pos = 0; base_pos < visible_count;)
    {
        uint32_t base_index = visible_indices[base_pos];
        const phpglfw_drawcall_instance *base_instance = &instances[base_index];
        const phpglfw_drawcall_mesh *mesh = &meshes[base_instance->mesh_handle];
        uint32_t command_flags = base_instance->flags;
        const uint32_t batch_flags = command_flags;
        const uint64_t batch_group_key = base_instance->group_key;
        bool can_auto_instance = intern->auto_instancing && !(command_flags & PHPGLFW_FLAG_DISABLE_INSTANCING);
        uint32_t batch_pos = base_pos + 1;

        if (can_auto_instance)
        {
            while (batch_pos < visible_count)
            {
                const phpglfw_drawcall_instance *candidate = &instances[visible_indices[batch_pos]];
                if (candidate->group_key != batch_group_key) {
                    break;
                }
                batch_pos++;
            }
        }

        const uint32_t batch_size = batch_pos - base_pos;
        const uint32_t draw_count = mesh->index_count > 0 ? mesh->index_count : mesh->vertex_count;

        cvector_push_back(intern->command_buffer->vec, base_instance->mesh_handle);
        cvector_push_back(intern->command_buffer->vec, mesh->vao_id);
        cvector_push_back(intern->command_buffer->vec, mesh->index_offset);
        cvector_push_back(intern->command_buffer->vec, draw_count);
        cvector_push_back(intern->command_buffer->vec, mesh->vertex_offset);
        cvector_push_back(intern->command_buffer->vec, instance_offset);
        cvector_push_back(intern->command_buffer->vec, batch_size);
        cvector_push_back(intern->command_buffer->vec, base_instance->material_id);

        for (uint32_t cursor = base_pos; cursor < batch_pos; cursor++)
        {
            const phpglfw_drawcall_instance * const instance = &instances[visible_indices[cursor]];
            const mat4x4 * const transform = &instance->transform;
            float *transform_dst = transform_write_ptr + transform_cursor;

            // unroll matrix copy
            transform_dst[0] = (*transform)[0][0];
            transform_dst[1] = (*transform)[0][1];
            transform_dst[2] = (*transform)[0][2];
            transform_dst[3] = (*transform)[0][3];
            transform_dst[4] = (*transform)[1][0];
            transform_dst[5] = (*transform)[1][1];
            transform_dst[6] = (*transform)[1][2];
            transform_dst[7] = (*transform)[1][3];
            transform_dst[8] = (*transform)[2][0];
            transform_dst[9] = (*transform)[2][1];
            transform_dst[10] = (*transform)[2][2];
            transform_dst[11] = (*transform)[2][3];
            transform_dst[12] = (*transform)[3][0];
            transform_dst[13] = (*transform)[3][1];
            transform_dst[14] = (*transform)[3][2];
            transform_dst[15] = (*transform)[3][3];

            uint32_t *meta_dst = meta_write_ptr + meta_cursor;
            meta_dst[0] = instance->mesh_handle;
            meta_dst[1] = instance->material_id;
            meta_dst[2] = instance->user_id;
            meta_dst[3] = batch_flags;

            transform_cursor += PHPGLFW_TRANSFORM_STRIDE;
            meta_cursor += PHPGLFW_INSTANCE_META_STRIDE;
        }

        // copy payload data if available
        if (payload_write_ptr && !Z_ISUNDEF(intern->payload_data_buffer_zv)) 
        {
            phpglfw_buffer_glfloat_object *payload_source = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ(intern->payload_data_buffer_zv));

            for (uint32_t cursor = base_pos; cursor < batch_pos; cursor++)
            {
                uint32_t source_offset = visible_indices[cursor] * intern->payload_data_stride;
                
                // ensure we don't read beyond the source buffer
                if (source_offset + intern->payload_data_stride <= cvector_size(payload_source->vec)) {
                    float *payload_dst = payload_write_ptr + payload_cursor;
                    for (uint32_t p = 0; p < intern->payload_data_stride; p++) {
                        payload_dst[p] = payload_source->vec[source_offset + p];
                    }
                }
                payload_cursor += intern->payload_data_stride;
            }
        }

        instance_offset += batch_size;
        command_count++;
        base_pos = batch_pos;
    }

    // only store back visible_indices if we used heap allocation
    if (use_frustum_culling && !use_stack_allocation) {
        intern->visible_index_buffer = visible_indices;
    }

    intern->final_command_count = command_count;
    intern->final_instance_count = instance_offset;

    RETURN_LONG(command_count);
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, bindTransformBuffer)
{
    zend_long vao, offset = 1;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l|l", &vao, &offset) == FAILURE) {
        RETURN_THROWS();
    }

    // ensure given vao and vbo are valid
    if (vao == 0) {
        zend_throw_error(NULL, "invalid VAO handle given.");
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    // // check if the VBO was already set, we don't really support that, because
    // // it might lead to confusion. The VBO will be constantly updated during execute().
    // // with the expectation that it is the same VBO for every draw call.
    // // The VAO on the other hand can be different per draw call as long as it shares the same VBO binding.
    // if (intern->internal_transform_vbo != 0 && intern->internal_transform_vbo != (GLuint)vbo) {
    //     zend_throw_error(NULL, "transform VBO is already bound, you can pass multiple VAOs but they must share the same VBO.");
    //     RETURN_THROWS();
    // }

    // the top is there is just for reference, i've decided that the VBO is owned by the DrawCallAssembler
    // and will be updated automatically during execute().
    if (intern->internal_transform_vbo == 0) {
        glGenBuffers(1, &intern->internal_transform_vbo);
    }

    // bind the VAO and VBO
    glBindVertexArray((GLuint)vao);
    glBindBuffer(GL_ARRAY_BUFFER, intern->internal_transform_vbo);

    // transform matrix attribute pointers (4x Vec4 for Mat4)
    GLsizei stride = PHPGLFW_TRANSFORM_STRIDE * sizeof(GLfloat);
    
    for (int i = 0; i < 4; i++) {
        GLuint location = (GLuint)offset + i;
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(location, 4, GL_FLOAT, GL_FALSE, stride, (void*)(i * 4 * sizeof(GLfloat)));
        glVertexAttribDivisor(location, 1); // this is an instanced attribute
    }

    // return next available attribute location
    RETURN_LONG(offset + 4);
}


PHP_METHOD(GL_Rendering_DrawCallAssembler, bindPayloadData)
{
    zval *payload_buffer;
    zend_long stride;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "Ol", &payload_buffer, phpglfw_get_buffer_glfloat_ce(), &stride) == FAILURE) {
        RETURN_THROWS();
    }

    // validate stride
    if (stride <= 0) {
        zend_throw_error(NULL, "stride must be greater than 0");
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    // store reference to the buffer object and stride
    ZVAL_COPY(&intern->payload_data_buffer_zv, payload_buffer);
    intern->payload_data_stride = (uint32_t)stride;
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, bindPayloadBuffer)
{
    zend_long vao, offset, stride = 0;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll|l", &vao, &offset, &stride) == FAILURE) {
        RETURN_THROWS();
    }

    // validate VAO
    if (vao == 0) {
        zend_throw_error(NULL, "invalid VAO handle given.");
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    // check if payload data was bound
    if (Z_ISUNDEF(intern->payload_data_buffer_zv)) {
        zend_throw_error(NULL, "bindPayloadData must be called before bindPayloadBuffer.");
        RETURN_THROWS();
    }

    // use bound stride if not provided
    uint32_t payload_stride = stride > 0 ? (uint32_t)stride : intern->payload_data_stride;
    
    if (payload_stride == 0) {
        zend_throw_error(NULL, "payload stride cannot be 0");
        RETURN_THROWS();
    }

    // create internal payload VBO if needed
    if (intern->internal_payload_vbo == 0) {
        glGenBuffers(1, &intern->internal_payload_vbo);
    }

    // bind VAO and VBO
    glBindVertexArray((GLuint)vao);
    glBindBuffer(GL_ARRAY_BUFFER, intern->internal_payload_vbo);

    // set up vertex attributes for payload data
    // each attribute can hold up to 4 floats (Vec4), so we need to split larger strides
    uint32_t remaining_components = payload_stride;
    uint32_t current_offset_bytes = 0;
    uint32_t attribute_index = 0;
    GLsizei stride_bytes = payload_stride * sizeof(GLfloat);

    while (remaining_components > 0) {
        uint32_t components_in_this_attr = remaining_components > 4 ? 4 : remaining_components;
        GLuint location = (GLuint)offset + attribute_index;
        
        glEnableVertexAttribArray(location);
        glVertexAttribPointer(
            location, 
            components_in_this_attr, 
            GL_FLOAT, 
            GL_FALSE, 
            stride_bytes, 
            (void*)(current_offset_bytes)
        );
        glVertexAttribDivisor(location, 1); // instanced attribute
        
        remaining_components -= components_in_this_attr;
        current_offset_bytes += components_in_this_attr * sizeof(GLfloat);
        attribute_index++;
    }

    // return next available attribute location
    RETURN_LONG(offset + attribute_index);
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, execute)
{
    zend_fcall_info fci;
    zend_fcall_info_cache fci_cache;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "f", &fci, &fci_cache) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    uint32_t command_count = 0;
    uint32_t instance_offset = 0;
    uint32_t visible_count = intern->instance_count;
    uint32_t *visible_indices = NULL;
    uint32_t stack_buffer[PHPGLFW_SMALL_BUFFER_THRESHOLD];
    const bool use_frustum_culling = intern->has_frustum && visible_count > 0;
    const bool use_stack_allocation = visible_count <= PHPGLFW_SMALL_BUFFER_THRESHOLD;

    if (use_stack_allocation) {
        visible_indices = stack_buffer;
    }
    else
    {
        // ensure the index buffer is allocated and large enough
        if (!intern->visible_index_buffer) {
            cvector_reserve(intern->visible_index_buffer, visible_count);
        }
        else if (cvector_capacity(intern->visible_index_buffer) < visible_count) {
            cvector_reserve(intern->visible_index_buffer, visible_count);
        }
        visible_indices = intern->visible_index_buffer;
    }

    // collect the visible instance indices
    // aka do frustum culling
    visible_count = phpglfw_drawcall_collect_visible_indices(intern, visible_indices);

    // nothing visible = nothing to do
    if (visible_count == 0)  {
        intern->final_command_count = 0;
        intern->final_instance_count = 0;
        RETURN_LONG(0);
    }

    phpglfw_drawcall_instance * const instances = intern->instances;
    const phpglfw_drawcall_mesh * const meshes = intern->meshes;

    // compute the distance to camera for each visible instance
    if (intern->camera_position)
    {
        for (uint32_t i = 0; i < visible_count; i++)
        {
            const uint32_t instance_index = visible_indices[i];
            phpglfw_drawcall_instance *instance = &instances[instance_index];
            
            // calculate distance to camera and apply it to the instance
            float distance_sq = phpglfw_drawcall_distance_to_camera_sq(intern->camera_position, instance->transform);
            phpglfw_drawcall_set_instance_distance(intern, instance, sqrtf(distance_sq));
            phpglfw_drawcall_compute_sort_key(intern, instance);
        }
    }

    // eval LOD selection
    phpglfw_drawcall_refresh_instance_lods(intern);

    // sort the visible indices by precomputed sort keys
    if (visible_count > 1) {
        instances_global = instances;
        qsort(visible_indices, visible_count, sizeof(uint32_t), phpglfw_index_compare_by_sort_key);
    }

    // prepare transform buffer data
    const size_t total_transform_floats = (size_t)visible_count * PHPGLFW_TRANSFORM_STRIDE;
    cvector_ensure(intern->rendering_transform_buffer_data, total_transform_floats);
    float *transform_write_ptr = intern->rendering_transform_buffer_data;
    size_t transform_cursor = 0;

    // prepare payload buffer data if bound
    float *payload_write_ptr = NULL;
    size_t payload_cursor = 0;
    bool has_payload = !Z_ISUNDEF(intern->payload_data_buffer_zv);
    
    if (has_payload) {
        const size_t total_payload_floats = (size_t)visible_count * intern->payload_data_stride;
        cvector_ensure(intern->rendering_payload_buffer_data, total_payload_floats);
        payload_write_ptr = intern->rendering_payload_buffer_data;
        
        // build payload data for visible instances
        phpglfw_buffer_glfloat_object *payload_source = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ(intern->payload_data_buffer_zv));
        for (uint32_t i = 0; i < visible_count; i++) {
            uint32_t source_offset = visible_indices[i] * intern->payload_data_stride;
            
            // ensure we don't read beyond the source buffer
            if (source_offset + intern->payload_data_stride <= cvector_size(payload_source->vec)) {
                for (uint32_t p = 0; p < intern->payload_data_stride; p++) {
                    payload_write_ptr[payload_cursor + p] = payload_source->vec[source_offset + p];
                }
            }
            payload_cursor += intern->payload_data_stride;
        }
        payload_cursor = 0; // reset for batch processing
    }

    uint32_t current_vao = 0;

    // build draw call commands and execute them directly
    for (uint32_t base_pos = 0; base_pos < visible_count;)
    {
        uint32_t base_index = visible_indices[base_pos];
        const phpglfw_drawcall_instance *base_instance = &instances[base_index];
        const phpglfw_drawcall_mesh *mesh = &meshes[base_instance->mesh_handle];
        uint32_t command_flags = base_instance->flags;
        const uint64_t batch_group_key = base_instance->group_key;
        bool can_auto_instance = intern->auto_instancing && !(command_flags & PHPGLFW_FLAG_DISABLE_INSTANCING);
        uint32_t batch_pos = base_pos + 1;

        if (can_auto_instance)
        {
            while (batch_pos < visible_count)
            {
                const phpglfw_drawcall_instance *candidate = &instances[visible_indices[batch_pos]];
                if (candidate->group_key != batch_group_key) {
                    break;
                }
                batch_pos++;
            }
        }

        const uint32_t batch_size = batch_pos - base_pos;
        const uint32_t draw_count = mesh->index_count > 0 ? mesh->index_count : mesh->vertex_count;

        if (mesh->vao_id != current_vao) {
            glBindVertexArray(mesh->vao_id);
            current_vao = mesh->vao_id;
        }

        // populate transform buffer for this batch
        for (uint32_t cursor = base_pos; cursor < batch_pos; cursor++)
        {
            const phpglfw_drawcall_instance * const instance = &instances[visible_indices[cursor]];
            const mat4x4 * const transform = &instance->transform;
            float *transform_dst = transform_write_ptr + transform_cursor;

            // unroll matrix copy 
            transform_dst[0] = (*transform)[0][0];
            transform_dst[1] = (*transform)[0][1];
            transform_dst[2] = (*transform)[0][2];
            transform_dst[3] = (*transform)[0][3];
            transform_dst[4] = (*transform)[1][0];
            transform_dst[5] = (*transform)[1][1];
            transform_dst[6] = (*transform)[1][2];
            transform_dst[7] = (*transform)[1][3];
            transform_dst[8] = (*transform)[2][0];
            transform_dst[9] = (*transform)[2][1];
            transform_dst[10] = (*transform)[2][2];
            transform_dst[11] = (*transform)[2][3];
            transform_dst[12] = (*transform)[3][0];
            transform_dst[13] = (*transform)[3][1];
            transform_dst[14] = (*transform)[3][2];
            transform_dst[15] = (*transform)[3][3];

            transform_cursor += PHPGLFW_TRANSFORM_STRIDE;
        }

        // upload transform data to GPU using internal VBO
        if (intern->internal_transform_vbo == 0) {
            zend_throw_error(NULL, "bindTransformBuffer must be called before execute, seeing this error means you probably forgot to bind your VAO to the DrawCallAssembler.");
            RETURN_THROWS();
        }
        glBindBuffer(GL_ARRAY_BUFFER, intern->internal_transform_vbo);
        glBufferData(GL_ARRAY_BUFFER, batch_size * PHPGLFW_TRANSFORM_STRIDE * sizeof(float), transform_write_ptr + (instance_offset * PHPGLFW_TRANSFORM_STRIDE), GL_DYNAMIC_DRAW);

        // upload payload data to GPU if bound
        if (has_payload && intern->internal_payload_vbo != 0) {
            uint32_t payload_data_size = batch_size * intern->payload_data_stride * sizeof(float);
            uint32_t payload_offset = instance_offset * intern->payload_data_stride;
            
            glBindBuffer(GL_ARRAY_BUFFER, intern->internal_payload_vbo);
            glBufferData(GL_ARRAY_BUFFER, payload_data_size, payload_write_ptr + payload_offset, GL_DYNAMIC_DRAW);
        }

        // prepare callback arguments: mesh_handle, material_id, instance_offset, instance_count, flags
        zval args[5];
        ZVAL_LONG(&args[0], base_instance->mesh_handle);
        ZVAL_LONG(&args[1], base_instance->material_id);
        ZVAL_LONG(&args[2], instance_offset);
        ZVAL_LONG(&args[3], batch_size);
        ZVAL_LONG(&args[4], command_flags);

        fci.param_count = 5;
        fci.params = args;

        zval retval;
        fci.retval = &retval;

        // call the user callback
        if (zend_call_function(&fci, &fci_cache) == FAILURE)
        {
            zval_ptr_dtor(&retval);
            RETURN_THROWS();
        }

        zval_ptr_dtor(&retval);

        // issue the actual draw call
        if (mesh->index_count > 0)
        {
            // indexed draw
            glDrawElementsInstancedBaseVertex(
                mesh->primitive,
                draw_count,
                GL_UNSIGNED_INT,
                (void*)(mesh->index_offset * sizeof(uint32_t)),
                batch_size,
                mesh->vertex_offset
            );
        }
        else
        {
            // array draw
            glDrawArraysInstanced(
                mesh->primitive,
                mesh->vertex_offset,
                draw_count,
                batch_size
            );
        }

        instance_offset += batch_size;
        command_count++;
        base_pos = batch_pos;
    }

    // only store back visible_indices if we used heap allocation
    if (use_frustum_culling && !use_stack_allocation) {
        intern->visible_index_buffer = visible_indices;
    }

    intern->final_command_count = command_count;
    intern->final_instance_count = instance_offset;

    RETURN_LONG(command_count);
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, commandCount)
{
    if (zend_parse_parameters_none() == FAILURE)
    {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));
    RETURN_LONG(intern->final_command_count);
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, instanceCount)
{
    if (zend_parse_parameters_none() == FAILURE)
    {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));
    RETURN_LONG(intern->instance_count);
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, builtInstanceCount)
{
    if (zend_parse_parameters_none() == FAILURE)
    {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));
    RETURN_LONG(intern->final_instance_count);
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, clearMeshes)
{
    if (zend_parse_parameters_none() == FAILURE)
    {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));
    intern->mesh_count = 0;
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, reset)
{
    if (zend_parse_parameters_none() == FAILURE)
    {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    intern->mesh_count = 0;
    intern->instance_count = 0;
    intern->final_command_count = 0;
    intern->final_instance_count = 0;
    if (intern->visible_index_buffer) {
        cvector_set_size(intern->visible_index_buffer, 0);
    }

    cvector_set_size(intern->command_buffer->vec, 0);
    cvector_set_size(intern->instance_transform_buffer->vec, 0);
    cvector_set_size(intern->instance_meta_buffer->vec, 0);
    cvector_set_size(intern->instance_payload_buffer->vec, 0);
}

void phpglfw_register_drawcall_assembler_module(INIT_FUNC_ARGS)
{
    // register class using stub-generated function
    phpglfw_drawcall_assembler_ce = register_class_GL_Rendering_DrawCallAssembler();
    phpglfw_drawcall_assembler_ce->create_object = phpglfw_drawcall_assembler_create_object;

    // setup object handlers
    memcpy(&phpglfw_drawcall_assembler_object_handlers, zend_get_std_object_handlers(), sizeof(zend_object_handlers));
    phpglfw_drawcall_assembler_object_handlers.offset = XtOffsetOf(phpglfw_drawcall_assembler_object, std);
    phpglfw_drawcall_assembler_object_handlers.free_obj = phpglfw_drawcall_assembler_free_handler;
}