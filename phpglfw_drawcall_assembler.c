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
#include <float.h>
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

static void phpglfw_drawcall_store_plane(vec4 dest, float a, float b, float c, float d);
static void phpglfw_drawcall_extract_frustum(phpglfw_drawcall_assembler_object *intern);
static uint32_t phpglfw_drawcall_collect_visible_indices(phpglfw_drawcall_assembler_object *intern, uint32_t *visible_indices);
static uint32_t phpglfw_drawcall_select_lod(phpglfw_drawcall_assembler_object *intern, phpglfw_drawcall_instance *instance, float distance);
static void phpglfw_drawcall_update_instance_lod(phpglfw_drawcall_assembler_object *intern, phpglfw_drawcall_instance *instance);
static void phpglfw_drawcall_refresh_instance_lods(phpglfw_drawcall_assembler_object *intern, const uint32_t *visible_indices, uint32_t visible_count);

static inline void phpglfw_drawcall_release_zval(zval *value)
{
    if (!Z_ISUNDEF(*value))
    {
        zval_ptr_dtor(value);
        ZVAL_UNDEF(value);
    }
}

// release every PHP object a mesh holds a reference to and clear the raw
// typed pointers so they can never be read after the object is gone.
static void phpglfw_drawcall_release_mesh_refs(phpglfw_drawcall_mesh *mesh)
{
    phpglfw_drawcall_release_zval(&mesh->aabb_min_zv);
    phpglfw_drawcall_release_zval(&mesh->aabb_max_zv);
    phpglfw_drawcall_release_zval(&mesh->lod_distances_zv);
    phpglfw_drawcall_release_zval(&mesh->lod_handles_zv);
    mesh->aabb_min = NULL;
    mesh->aabb_max = NULL;
    mesh->lod_distances = NULL;
    mesh->lod_handles = NULL;
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
    intern->sort_keys_a = NULL;
    intern->sort_keys_b = NULL;
    intern->sort_indices_b = NULL;
    intern->sort_scratch_capacity = 0;
    intern->oct_nodes = NULL;
    intern->oct_node_capacity = 0;
    intern->oct_node_count = 0;
    intern->oct_instance_indices = NULL;
    intern->oct_instance_scratch = NULL;
    intern->oct_centers = NULL;
    intern->oct_radii = NULL;
    intern->oct_ignored_indices = NULL;
    intern->oct_ignored_count = 0;
    intern->oct_scratch_capacity = 0;
    intern->oct_dirty = true;
    intern->oct_max_depth = PHPGLFW_OCT_MAX_DEPTH;
    intern->oct_min_leaf = PHPGLFW_OCT_MIN_LEAF_INSTANCES;
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
    intern->frustum_from_matrices = false;
    intern->sort_mode = PHPGLFW_SORT_NONE;
    intern->cull_strategy = PHPGLFW_CULL_LINEAR;
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

    // free mesh array, releasing every reference each mesh holds first.
    // we iterate the full capacity because clearMeshes()/reset() only lower
    // mesh_count, and every slot is either a live mesh or zero-initialized
    // (all-UNDEF) memory, so releasing is always safe.
    if (intern->meshes) {
        for (uint32_t i = 0; i < intern->mesh_capacity; i++) {
            phpglfw_drawcall_release_mesh_refs(&intern->meshes[i]);
        }
        efree(intern->meshes);
    }

    // free instance array
    if (intern->instances) {
        efree(intern->instances);
    }

    if (intern->visible_index_buffer) {
        cvector_free(intern->visible_index_buffer);
    }

    // radix sort scratch buffers
    if (intern->sort_keys_a) {
        efree(intern->sort_keys_a);
    }
    if (intern->sort_keys_b) {
        efree(intern->sort_keys_b);
    }
    if (intern->sort_indices_b) {
        efree(intern->sort_indices_b);
    }

    // octree scratch buffers
    if (intern->oct_nodes) {
        efree(intern->oct_nodes);
    }
    if (intern->oct_instance_indices) {
        efree(intern->oct_instance_indices);
    }
    if (intern->oct_instance_scratch) {
        efree(intern->oct_instance_scratch);
    }
    if (intern->oct_centers) {
        efree(intern->oct_centers);
    }
    if (intern->oct_radii) {
        efree(intern->oct_radii);
    }
    if (intern->oct_ignored_indices) {
        efree(intern->oct_ignored_indices);
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

    // a zero or negative seed would corrupt the heap: ecalloc(0, ...) allocates
    // nothing and the capacity *= 2 growth path never grows 0, so the first
    // write lands out of bounds. negatives also wrap to huge uint32_t values.
    if (initial_mesh_capacity < 1 || initial_instance_capacity < 1 || initial_command_capacity < 1) {
        zend_value_error("DrawCallAssembler capacities must be >= 1");
        RETURN_THROWS();
    }
    if (initial_mesh_capacity > PHPGLFW_MAX_CAPACITY ||
        initial_instance_capacity > PHPGLFW_MAX_CAPACITY ||
        initial_command_capacity > PHPGLFW_MAX_CAPACITY) {
        zend_value_error("DrawCallAssembler capacities exceed the maximum");
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

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "|O!O!O!",
        &camera_position,   phpglfw_get_math_vec3_ce(),
        &view_matrix,       phpglfw_get_math_mat4_ce(),
        &projection_matrix, phpglfw_get_math_mat4_ce()) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    // store camera data if provided. the "O!O!O!" parameter spec already
    // guarantees each argument is either NULL or an object of the required
    // class, so a non-NULL zval is always the expected object type.
    phpglfw_drawcall_release_zval(&intern->camera_position_zv);
    if (camera_position)
    {
        ZVAL_OBJ_COPY(&intern->camera_position_zv, Z_OBJ_P(camera_position));
        intern->camera_position = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ(intern->camera_position_zv));
    }
    else
    {
        intern->camera_position = NULL;
    }

    phpglfw_drawcall_release_zval(&intern->view_matrix_zv);
    if (view_matrix)
    {
        ZVAL_OBJ_COPY(&intern->view_matrix_zv, Z_OBJ_P(view_matrix));
        intern->view_matrix = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ(intern->view_matrix_zv));
    }
    else
    {
        intern->view_matrix = NULL;
    }

    phpglfw_drawcall_release_zval(&intern->projection_matrix_zv);
    if (projection_matrix)
    {
        ZVAL_OBJ_COPY(&intern->projection_matrix_zv, Z_OBJ_P(projection_matrix));
        intern->projection_matrix = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ(intern->projection_matrix_zv));
    }
    else
    {
        intern->projection_matrix = NULL;
    }

    if (intern->view_matrix && intern->projection_matrix)
    {
        phpglfw_drawcall_extract_frustum(intern); // sets frustum_from_matrices = true
    }
    else if (intern->frustum_from_matrices)
    {
        // we no longer have both matrices to derive a frustum from (incomplete
        // matrix update, or a position-only update). a previously matrix-derived
        // frustum is now stale, so disable culling (safe default). a manually set
        // frustum (setFrustumPlanes) is left intact.
        intern->has_frustum = false;
        intern->frustum_from_matrices = false;
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
    intern->frustum_from_matrices = true;
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
        "l|llllO!O!ll",
        &vao_id,
        &vertex_offset, &vertex_count,
        &index_offset, &index_count,
        &aabb_min, phpglfw_get_math_vec3_ce(),
        &aabb_max, phpglfw_get_math_vec3_ce(),
        &material_hint,
        &primitive
    ) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    // resize mesh array if needed
    if (intern->mesh_count >= intern->mesh_capacity) {
        uint32_t old_capacity = intern->mesh_capacity;
        intern->mesh_capacity *= 2;
        intern->meshes = erealloc(intern->meshes, intern->mesh_capacity * sizeof(phpglfw_drawcall_mesh));
        // erealloc does not zero the grown region; do it ourselves so the new
        // slots have UNDEF zvals (releasing/overwriting them stays safe).
        memset(&intern->meshes[old_capacity], 0, (intern->mesh_capacity - old_capacity) * sizeof(phpglfw_drawcall_mesh));
    }

    phpglfw_drawcall_mesh *mesh = &intern->meshes[intern->mesh_count];
    // release anything a reused slot may still hold (after clearMeshes/reset)
    phpglfw_drawcall_release_mesh_refs(mesh);
    mesh->vao_id = vao_id;
    mesh->vertex_offset = vertex_offset;
    mesh->vertex_count = vertex_count;
    mesh->index_offset = index_offset;
    mesh->index_count = index_count;
    mesh->material_hint = material_hint;
    mesh->primitive = primitive;

    // store bounding box if provided (holding a reference so it can't dangle).
    // the "O!" spec guarantees a non-NULL arg is already a Vec3 object.
    if (aabb_min) {
        ZVAL_OBJ_COPY(&mesh->aabb_min_zv, Z_OBJ_P(aabb_min));
        mesh->aabb_min = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ(mesh->aabb_min_zv));
    } else {
        mesh->aabb_min = NULL;
    }

    if (aabb_max) {
        ZVAL_OBJ_COPY(&mesh->aabb_max_zv, Z_OBJ_P(aabb_max));
        mesh->aabb_max = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ(mesh->aabb_max_zv));
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

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "lOO",
        &mesh_handle,
        &distance_thresholds, phpglfw_get_buffer_glfloat_ce(),
        &mesh_handles,        phpglfw_get_buffer_gluint_ce()) == FAILURE) {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    if (mesh_handle < 0 || (uint32_t)mesh_handle >= intern->mesh_count) {
        zend_throw_error(NULL, "invalid mesh handle");
        RETURN_THROWS();
    }

    phpglfw_drawcall_mesh *mesh = &intern->meshes[mesh_handle];

    // release any previously bound lod buffers before rebinding
    phpglfw_drawcall_release_zval(&mesh->lod_distances_zv);
    mesh->lod_distances = NULL;
    phpglfw_drawcall_release_zval(&mesh->lod_handles_zv);
    mesh->lod_handles = NULL;

    // "O" guarantees objects of the expected buffer classes
    ZVAL_OBJ_COPY(&mesh->lod_distances_zv, Z_OBJ_P(distance_thresholds));
    mesh->lod_distances = phpglfw_buffer_glfloat_objectptr_from_zobj_p(Z_OBJ(mesh->lod_distances_zv));

    ZVAL_OBJ_COPY(&mesh->lod_handles_zv, Z_OBJ_P(mesh_handles));
    mesh->lod_handles = phpglfw_buffer_gluint_objectptr_from_zobj_p(Z_OBJ(mesh->lod_handles_zv));
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, setMeshMaterial)
{
    zend_long mesh_handle, material_id;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "ll", &mesh_handle, &material_id) == FAILURE)  {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    if (mesh_handle < 0 || (uint32_t)mesh_handle >= intern->mesh_count) {
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

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "OOOOOO",
        &left,   phpglfw_get_math_vec4_ce(),
        &right,  phpglfw_get_math_vec4_ce(),
        &bottom, phpglfw_get_math_vec4_ce(),
        &top,    phpglfw_get_math_vec4_ce(),
        &near,   phpglfw_get_math_vec4_ce(),
        &far,    phpglfw_get_math_vec4_ce()) == FAILURE) {
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
    intern->frustum_from_matrices = false; // manually set, not matrix-derived
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

PHP_METHOD(GL_Rendering_DrawCallAssembler, setCullingStrategy)
{
    zend_long strategy;
    // -1 sentinels: "leave the current octree tuning unchanged"
    zend_long octree_max_depth = -1;
    zend_long octree_min_leaf = -1;

    if (zend_parse_parameters(ZEND_NUM_ARGS(), "l|ll", &strategy, &octree_max_depth, &octree_min_leaf) == FAILURE)
    {
        RETURN_THROWS();
    }

    if (strategy < PHPGLFW_CULL_NONE || strategy > PHPGLFW_CULL_OCTREE) {
        zend_value_error("invalid culling strategy, expected one of DrawCallAssembler::CULL_*");
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));
    intern->cull_strategy = (int)strategy;

    // apply optional octree tuning; changing it invalidates any cached tree
    if (octree_max_depth >= 0) {
        if (octree_max_depth < 1 || octree_max_depth > PHPGLFW_OCT_MAX_DEPTH_LIMIT) {
            zend_value_error("octree max depth must be between 1 and %d", PHPGLFW_OCT_MAX_DEPTH_LIMIT);
            RETURN_THROWS();
        }
        intern->oct_max_depth = (int)octree_max_depth;
        intern->oct_dirty = true;
    }
    if (octree_min_leaf >= 0) {
        if (octree_min_leaf < 1) {
            zend_value_error("octree min leaf instance count must be >= 1");
            RETURN_THROWS();
        }
        intern->oct_min_leaf = (uint32_t)octree_min_leaf;
        intern->oct_dirty = true;
    }
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
    intern->oct_dirty = true;

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

// compute the world-space bounding sphere (center + radius) of an instance.
// this is the exact model both the linear and octree culling paths test: the
// mesh bounds center transformed to world space and the radius scaled by the
// largest axis scale of the transform. instances without mesh bounds fall back
// to the translation column and the (unscaled) mesh radius.
static void phpglfw_drawcall_instance_world_sphere(
    const phpglfw_drawcall_instance *instance,
    const phpglfw_drawcall_mesh *mesh,
    float out_center[3],
    float *out_radius
) {
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

    out_center[0] = cx;
    out_center[1] = cy;
    out_center[2] = cz;
    *out_radius = scaled_radius;
}

// test a bounding sphere against the 6 frustum planes. a sphere is visible when
// its signed distance to every plane is >= -radius; we early-out on the first
// plane that rejects it.
static zend_always_inline bool phpglfw_drawcall_sphere_in_frustum(
    const float frustum[6][4], float cx, float cy, float cz, float radius
) {
    for (int plane = 0; plane < 6; plane++)
    {
        const float distance = frustum[plane][0] * cx + frustum[plane][1] * cy + frustum[plane][2] * cz + frustum[plane][3];
        if (distance < -radius) {
            return false;
        }
    }

    return true;
}

// classify an axis-aligned box against the frustum: 0 = fully outside,
// 1 = intersecting, 2 = fully inside. uses the p-vertex / n-vertex test: for
// each plane the box corner farthest along the plane normal (p-vertex) decides
// "fully outside", the nearest corner (n-vertex) decides "not fully inside".
static int phpglfw_drawcall_aabb_frustum_class(const float frustum[6][4], const float mn[3], const float mx[3])
{
    bool intersecting = false;

    for (int plane = 0; plane < 6; plane++)
    {
        const float a = frustum[plane][0];
        const float b = frustum[plane][1];
        const float c = frustum[plane][2];
        const float d = frustum[plane][3];

        const float px = (a >= 0.0f) ? mx[0] : mn[0];
        const float py = (b >= 0.0f) ? mx[1] : mn[1];
        const float pz = (c >= 0.0f) ? mx[2] : mn[2];
        if (a * px + b * py + c * pz + d < 0.0f) {
            return 0; // p-vertex behind the plane => whole box outside
        }

        const float nx = (a >= 0.0f) ? mn[0] : mx[0];
        const float ny = (b >= 0.0f) ? mn[1] : mx[1];
        const float nz = (c >= 0.0f) ? mn[2] : mx[2];
        if (a * nx + b * ny + c * nz + d < 0.0f) {
            intersecting = true; // n-vertex behind the plane => box straddles it
        }
    }

    return intersecting ? 1 : 2;
}

// grow the per-instance octree scratch arrays to hold at least `count` entries.
static void phpglfw_drawcall_oct_reserve_instances(phpglfw_drawcall_assembler_object *intern, uint32_t count)
{
    if (intern->oct_scratch_capacity >= count) {
        return;
    }

    uint32_t new_cap = intern->oct_scratch_capacity ? intern->oct_scratch_capacity : 256;
    while (new_cap < count) {
        new_cap *= 2;
    }

    intern->oct_instance_indices = erealloc(intern->oct_instance_indices, new_cap * sizeof(uint32_t));
    intern->oct_instance_scratch = erealloc(intern->oct_instance_scratch, new_cap * sizeof(uint32_t));
    intern->oct_ignored_indices = erealloc(intern->oct_ignored_indices, new_cap * sizeof(uint32_t));
    intern->oct_centers = erealloc(intern->oct_centers, new_cap * 3 * sizeof(float));
    intern->oct_radii = erealloc(intern->oct_radii, new_cap * sizeof(float));
    intern->oct_scratch_capacity = new_cap;
}

// grow the octree node pool to hold at least `needed` nodes.
static void phpglfw_drawcall_oct_reserve_nodes(phpglfw_drawcall_assembler_object *intern, uint32_t needed)
{
    if (intern->oct_node_capacity >= needed) {
        return;
    }

    uint32_t new_cap = intern->oct_node_capacity ? intern->oct_node_capacity : 64;
    while (new_cap < needed) {
        new_cap *= 2;
    }

    intern->oct_nodes = erealloc(intern->oct_nodes, new_cap * sizeof(phpglfw_drawcall_octnode));
    intern->oct_node_capacity = new_cap;
}

// compute a node's bounds as the union of the world-space sphere AABBs of the
// instances in its slice. spheres are indexed by instance id via oct_centers/
// oct_radii; the slice itself is a range of the oct_instance_indices permutation.
static void phpglfw_drawcall_oct_node_bounds(phpglfw_drawcall_assembler_object *intern, phpglfw_drawcall_octnode *node)
{
    if (node->instance_count == 0) {
        node->aabb_min[0] = node->aabb_min[1] = node->aabb_min[2] = 0.0f;
        node->aabb_max[0] = node->aabb_max[1] = node->aabb_max[2] = 0.0f;
        return;
    }

    float mn[3] = { FLT_MAX, FLT_MAX, FLT_MAX };
    float mx[3] = { -FLT_MAX, -FLT_MAX, -FLT_MAX };

    const uint32_t end = node->first_instance + node->instance_count;
    for (uint32_t i = node->first_instance; i < end; i++)
    {
        const uint32_t idx = intern->oct_instance_indices[i];
        const float *c = &intern->oct_centers[idx * 3];
        const float r = intern->oct_radii[idx];

        for (int axis = 0; axis < 3; axis++) {
            const float lo = c[axis] - r;
            const float hi = c[axis] + r;
            if (lo < mn[axis]) mn[axis] = lo;
            if (hi > mx[axis]) mx[axis] = hi;
        }
    }

    node->aabb_min[0] = mn[0]; node->aabb_min[1] = mn[1]; node->aabb_min[2] = mn[2];
    node->aabb_max[0] = mx[0]; node->aabb_max[1] = mx[1]; node->aabb_max[2] = mx[2];
}

// recursively subdivide a node into 8 octants. recursion depth is bounded by
// PHPGLFW_OCT_MAX_DEPTH, so the stack usage is trivially bounded.
static void phpglfw_drawcall_oct_subdivide(phpglfw_drawcall_assembler_object *intern, uint32_t node_index, int depth)
{
    const uint32_t first = intern->oct_nodes[node_index].first_instance;
    const uint32_t count = intern->oct_nodes[node_index].instance_count;

    if (count <= intern->oct_min_leaf || depth >= intern->oct_max_depth) {
        intern->oct_nodes[node_index].is_leaf = true;
        intern->oct_nodes[node_index].child_base = 0;
        return;
    }

    // split at the center of the node bounds
    const float sx = 0.5f * (intern->oct_nodes[node_index].aabb_min[0] + intern->oct_nodes[node_index].aabb_max[0]);
    const float sy = 0.5f * (intern->oct_nodes[node_index].aabb_min[1] + intern->oct_nodes[node_index].aabb_max[1]);
    const float sz = 0.5f * (intern->oct_nodes[node_index].aabb_min[2] + intern->oct_nodes[node_index].aabb_max[2]);

    const uint32_t end = first + count;

    // count how many instances fall into each octant (by sphere center)
    uint32_t counts[8] = {0};
    for (uint32_t i = first; i < end; i++)
    {
        const uint32_t idx = intern->oct_instance_indices[i];
        const float *c = &intern->oct_centers[idx * 3];
        const int oct = (c[0] >= sx ? 1 : 0) | (c[1] >= sy ? 2 : 0) | (c[2] >= sz ? 4 : 0);
        counts[oct]++;
    }

    // if every instance lands in the same octant, splitting makes no progress
    // (e.g. coincident centers), so keep this node as a leaf.
    for (int oct = 0; oct < 8; oct++) {
        if (counts[oct] == count) {
            intern->oct_nodes[node_index].is_leaf = true;
            intern->oct_nodes[node_index].child_base = 0;
            return;
        }
    }

    // stable-ish scatter of the slice into 8 contiguous octant buckets
    uint32_t cursor[8];
    uint32_t offset = first;
    for (int oct = 0; oct < 8; oct++) {
        cursor[oct] = offset;
        offset += counts[oct];
    }
    for (uint32_t i = first; i < end; i++)
    {
        const uint32_t idx = intern->oct_instance_indices[i];
        const float *c = &intern->oct_centers[idx * 3];
        const int oct = (c[0] >= sx ? 1 : 0) | (c[1] >= sy ? 2 : 0) | (c[2] >= sz ? 4 : 0);
        intern->oct_instance_scratch[cursor[oct]++] = idx;
    }
    memcpy(&intern->oct_instance_indices[first], &intern->oct_instance_scratch[first], count * sizeof(uint32_t));

    // allocate 8 children; this may move the node pool, so we read/write the
    // parent purely by index and re-fetch pointers after the reserve.
    const uint32_t child_base = intern->oct_node_count;
    phpglfw_drawcall_oct_reserve_nodes(intern, child_base + 8);
    intern->oct_node_count += 8;

    intern->oct_nodes[node_index].is_leaf = false;
    intern->oct_nodes[node_index].child_base = child_base;

    uint32_t child_first = first;
    for (int oct = 0; oct < 8; oct++)
    {
        phpglfw_drawcall_octnode *child = &intern->oct_nodes[child_base + oct];
        child->first_instance = child_first;
        child->instance_count = counts[oct];
        child->child_base = 0;
        child->is_leaf = true;
        child_first += counts[oct];
        phpglfw_drawcall_oct_node_bounds(intern, child);
    }

    for (int oct = 0; oct < 8; oct++) {
        if (counts[oct] > 0) {
            phpglfw_drawcall_oct_subdivide(intern, child_base + oct, depth + 1);
        }
    }
}

// (re)build the persistent octree from the current instance set. runs only when
// the tree is dirty; the resulting tree is camera-independent and reused across
// frames until the instance set changes.
static void phpglfw_drawcall_build_octree(phpglfw_drawcall_assembler_object *intern)
{
    const uint32_t total_instances = intern->instance_count;
    const phpglfw_drawcall_instance * const instances = intern->instances;
    const phpglfw_drawcall_mesh * const meshes = intern->meshes;

    intern->oct_node_count = 0;
    intern->oct_ignored_count = 0;

    if (total_instances > 0) {
        phpglfw_drawcall_oct_reserve_instances(intern, total_instances);
    }

    // partition instances: IGNORE_CULLING ones are emitted verbatim every frame
    // and kept out of the tree; the rest go into the permutation and get their
    // world spheres cached (indexed by instance id).
    uint32_t culled_count = 0;
    for (uint32_t i = 0; i < total_instances; i++)
    {
        const phpglfw_drawcall_instance * const instance = &instances[i];

        if (instance->flags & PHPGLFW_FLAG_IGNORE_CULLING) {
            intern->oct_ignored_indices[intern->oct_ignored_count++] = i;
            continue;
        }

        const phpglfw_drawcall_mesh * const mesh = &meshes[instance->mesh_handle];
        float center[3];
        float radius;
        phpglfw_drawcall_instance_world_sphere(instance, mesh, center, &radius);

        intern->oct_centers[i * 3 + 0] = center[0];
        intern->oct_centers[i * 3 + 1] = center[1];
        intern->oct_centers[i * 3 + 2] = center[2];
        intern->oct_radii[i] = radius;
        intern->oct_instance_indices[culled_count++] = i;
    }

    intern->oct_dirty = false;

    if (culled_count == 0) {
        return; // nothing to place in the tree (all instances ignored, or none)
    }

    // root node covering the whole culled set
    phpglfw_drawcall_oct_reserve_nodes(intern, 1);
    intern->oct_node_count = 1;
    intern->oct_nodes[0].first_instance = 0;
    intern->oct_nodes[0].instance_count = culled_count;
    intern->oct_nodes[0].child_base = 0;
    intern->oct_nodes[0].is_leaf = true;
    phpglfw_drawcall_oct_node_bounds(intern, &intern->oct_nodes[0]);

    phpglfw_drawcall_oct_subdivide(intern, 0, 0);
}

// recursively collect the visible instances of a subtree into visible_indices,
// starting at write_index. nodes fully outside the frustum are pruned; nodes
// fully inside accept their whole slice without any per-instance test; nodes
// that straddle the frustum recurse (or, at a leaf, do a per-instance sphere test).
static uint32_t phpglfw_drawcall_oct_collect_node(
    phpglfw_drawcall_assembler_object *intern,
    const float frustum[6][4],
    uint32_t node_index,
    uint32_t *visible_indices,
    uint32_t write_index
) {
    const phpglfw_drawcall_octnode *node = &intern->oct_nodes[node_index];
    if (node->instance_count == 0) {
        return write_index;
    }

    const int cls = phpglfw_drawcall_aabb_frustum_class(frustum, node->aabb_min, node->aabb_max);
    if (cls == 0) {
        return write_index; // fully outside, prune
    }

    if (cls == 2) {
        // fully inside: every contained sphere is inside, accept the whole slice
        memcpy(&visible_indices[write_index], &intern->oct_instance_indices[node->first_instance], node->instance_count * sizeof(uint32_t));
        return write_index + node->instance_count;
    }

    // straddles the frustum
    if (node->is_leaf) {
        const uint32_t end = node->first_instance + node->instance_count;
        for (uint32_t i = node->first_instance; i < end; i++)
        {
            const uint32_t idx = intern->oct_instance_indices[i];
            const float *c = &intern->oct_centers[idx * 3];
            if (phpglfw_drawcall_sphere_in_frustum(frustum, c[0], c[1], c[2], intern->oct_radii[idx])) {
                visible_indices[write_index++] = idx;
            }
        }
        return write_index;
    }

    const uint32_t child_base = node->child_base;
    for (int oct = 0; oct < 8; oct++) {
        write_index = phpglfw_drawcall_oct_collect_node(intern, frustum, child_base + oct, visible_indices, write_index);
    }

    return write_index;
}

static uint32_t phpglfw_drawcall_octree_collect(
    phpglfw_drawcall_assembler_object *intern,
    const float frustum[6][4],
    uint32_t *visible_indices
) {
    uint32_t write_index = 0;

    // IGNORE_CULLING instances are always visible
    for (uint32_t i = 0; i < intern->oct_ignored_count; i++) {
        visible_indices[write_index++] = intern->oct_ignored_indices[i];
    }

    if (intern->oct_node_count == 0) {
        return write_index;
    }

    return phpglfw_drawcall_oct_collect_node(intern, frustum, 0, visible_indices, write_index);
}

static uint32_t phpglfw_drawcall_collect_visible_indices(phpglfw_drawcall_assembler_object *intern, uint32_t *visible_indices)
{
    const uint32_t total_instances = intern->instance_count;
    const phpglfw_drawcall_instance * const instances = intern->instances;
    const phpglfw_drawcall_mesh * const meshes = intern->meshes;

    // no frustum, or culling explicitly disabled: everything is visible
    if (!intern->has_frustum || intern->cull_strategy == PHPGLFW_CULL_NONE) {
        for (uint32_t i = 0; i < total_instances; i++) {
            visible_indices[i] = i;
        }

        return total_instances;
    }

    // get the frustum planes into stack memory (i think this is faster, but to be honest, i did not benchmark it..)
    const float frustum[6][4] = {
        {intern->frustum_planes[0][0], intern->frustum_planes[0][1], intern->frustum_planes[0][2], intern->frustum_planes[0][3]},
        {intern->frustum_planes[1][0], intern->frustum_planes[1][1], intern->frustum_planes[1][2], intern->frustum_planes[1][3]},
        {intern->frustum_planes[2][0], intern->frustum_planes[2][1], intern->frustum_planes[2][2], intern->frustum_planes[2][3]},
        {intern->frustum_planes[3][0], intern->frustum_planes[3][1], intern->frustum_planes[3][2], intern->frustum_planes[3][3]},
        {intern->frustum_planes[4][0], intern->frustum_planes[4][1], intern->frustum_planes[4][2], intern->frustum_planes[4][3]},
        {intern->frustum_planes[5][0], intern->frustum_planes[5][1], intern->frustum_planes[5][2], intern->frustum_planes[5][3]}
    };

    // octree strategy: (re)build the persistent tree if needed, then traverse it
    if (intern->cull_strategy == PHPGLFW_CULL_OCTREE) {
        if (intern->oct_dirty) {
            phpglfw_drawcall_build_octree(intern);
        }

        return phpglfw_drawcall_octree_collect(intern, frustum, visible_indices);
    }

    // linear strategy: test every instance's bounding sphere against the frustum
    uint32_t write_index = 0;
    for (uint32_t read_index = 0; read_index < total_instances; read_index++)
    {
        const phpglfw_drawcall_instance * const instance = &instances[read_index];

        // fast path for ignore culling flag
        if (instance->flags & PHPGLFW_FLAG_IGNORE_CULLING) {
            visible_indices[write_index++] = read_index;
            continue;
        }

        const phpglfw_drawcall_mesh * const mesh = &meshes[instance->mesh_handle];

        float center[3];
        float scaled_radius;
        phpglfw_drawcall_instance_world_sphere(instance, mesh, center, &scaled_radius);

        if (phpglfw_drawcall_sphere_in_frustum(frustum, center[0], center[1], center[2], scaled_radius)) {
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

    // check cache first (handle 0 is a valid mesh, so use an explicit valid flag
    // rather than a "handle != 0" sentinel)
    const float distance_diff = fabsf(distance - instance->cached_lod_distance);
    if (instance->lod_cache_valid && distance_diff < PHPGLFW_LOD_CACHE_EPSILON) {
        return instance->cached_lod_handle;
    }

    const uint32_t base_handle = instance->base_mesh_handle;
    if (base_handle >= intern->mesh_count) {
        return base_handle;
    }

    const phpglfw_drawcall_mesh *mesh = &intern->meshes[base_handle];

    // fall back to the base handle when there are no usable LODs. lod_count and
    // handle_count are both non-zero past this guard, so limit is too.
    const uint32_t lod_count = mesh->lod_distances ? (uint32_t)cvector_size(mesh->lod_distances->vec) : 0;
    const uint32_t handle_count = mesh->lod_handles ? (uint32_t)cvector_size(mesh->lod_handles->vec) : 0;
    if (lod_count == 0 || handle_count == 0)
    {
        instance->lod_cache_valid = true;
        instance->cached_lod_distance = distance;
        instance->cached_lod_handle = base_handle;
        return base_handle;
    }

    const uint32_t limit = lod_count < handle_count ? lod_count : handle_count;

    // distance is the SQUARED distance to the camera, so compare against
    // squared thresholds (monotonic, so LOD selection is unchanged).
    const float clamped_distance_sq = distance < 0.0f ? 0.0f : distance;
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

        if (clamped_distance_sq >= threshold * threshold)
        {
            selected_handle = alternative;
        }
        else
        {
            break;
        }
    }

    // cache result
    instance->lod_cache_valid = true;
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
    // depth-major layout so transparent draws sort back-to-front. uses the
    // dedicated SKT_* shifts whose field widths match the reordered fields.
    k |= ((uint64_t)(pass        & SK_MASK(SK_PASS_BITS)))  << SKT_PASS_SHIFT;
    k |= ((uint64_t)(depth_rev   & SK_MASK(SK_DEPTH_BITS))) << SKT_DEPTH_SHIFT;
    k |= ((uint64_t)(program_id  & SK_MASK(SK_PROG_BITS)))  << SKT_PROG_SHIFT;
    k |= ((uint64_t)(material_id & SK_MASK(SK_MAT_BITS)))   << SKT_MAT_SHIFT;
    k |= ((uint64_t)(vao_id      & SK_MASK(SK_VAO_BITS)))   << SKT_VAO_SHIFT;
    k |= ((uint64_t)(mesh_id     & SK_MASK(SK_MESH_BITS)))  << SKT_MESH_SHIFT;
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

    // pick the sort direction first; it also decides how we quantize depth.
    // SORT_NONE keeps the per-pass default (transparent = back-to-front,
    // everything else front-to-back); the explicit modes force a global
    // direction regardless of pass.
    bool back_to_front;
    switch (intern->sort_mode) {
        case PHPGLFW_SORT_FRONT_TO_BACK: back_to_front = false; break;
        case PHPGLFW_SORT_BACK_TO_FRONT: back_to_front = true; break;
        default:                         back_to_front = (instance->pass == PHPGLFW_PASS_TRANSPARENT); break;
    }

    // quantize depth to the 0-1023 range (10-bit field). sort_distance holds
    // the SQUARED distance to the camera. back-to-front (transparent) draws use
    // depth as the *most*-significant sort field with only 10 bits, so they
    // need real-distance resolution in the near field -> take the sqrt here.
    // front-to-back (opaque) draws use depth as the *least*-significant field,
    // so quantizing straight from the squared distance is enough (monotonic)
    // and keeps the hot path sqrt-free. clamp to >= 0 first: a negative float
    // cast to uint32_t is undefined and would jumble the bucket.
    uint32_t depth_bucket;
    if (back_to_front) {
        // sort_bias is applied in linear distance space, matching submit()'s
        // linear bias semantics.
        float distance = sqrtf(instance->sort_distance) + instance->sort_bias;
        if (distance < 0.0f) {
            distance = 0.0f;
        }
        depth_bucket = (uint32_t)(fminf(distance / 1000.0f, 1.0f) * 1023.0f);

        instance->sort_key = make_sort_key_transparent(
            instance->pass,
            instance->program_id,
            instance->material_id,
            mesh->vao_id,
            instance->mesh_handle,
            depth_bucket
        );
    } else {
        // clamp against 1000^2 so the mapping lines up with the linear
        // 1000-unit clamp used on the transparent path. sort_bias has no
        // meaningful effect on this coarse least-significant bucket and is
        // intentionally omitted to avoid a sqrt.
        float distance_sq = instance->sort_distance;
        if (distance_sq < 0.0f) {
            distance_sq = 0.0f;
        }
        depth_bucket = (uint32_t)(fminf(distance_sq / (1000.0f * 1000.0f), 1.0f) * 1023.0f);

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

// refresh LOD selection and sort keys only for the visible set. culled
// instances are never sorted or rendered this frame and their distance is not
// recomputed, so refreshing them would be wasted work on stale data.
static void phpglfw_drawcall_refresh_instance_lods(phpglfw_drawcall_assembler_object *intern, const uint32_t *visible_indices, uint32_t visible_count)
{
    phpglfw_drawcall_instance * const instances = intern->instances;

    for (uint32_t i = 0; i < visible_count; i++) {
        phpglfw_drawcall_update_instance_lod(intern, &instances[visible_indices[i]]);
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

    if (mesh_handle < 0 || (uint32_t)mesh_handle >= intern->mesh_count) {
        zend_throw_error(NULL, "invalid mesh handle");
        RETURN_THROWS();
    }

    // resize instance array if needed
    if (intern->instance_count >= intern->instance_capacity)  {
        intern->instance_capacity *= 2;
        intern->instances = erealloc(intern->instances, intern->instance_capacity * sizeof(phpglfw_drawcall_instance));
    }

    phpglfw_drawcall_instance *instance = &intern->instances[intern->instance_count];
    instance->base_mesh_handle = (uint32_t)mesh_handle;
    instance->mesh_handle = (uint32_t)mesh_handle;
    instance->material_id = material_id;
    instance->pass = (uint32_t)(pass & SK_MASK(SK_PASS_BITS));
    instance->program_id = program_id;
    instance->user_id = user_id;
    instance->flags = flags;
    instance->sort_bias = sort_bias;
    instance->sort_distance = 0.0f;
    
    instance->lod_cache_valid = false;
    instance->cached_lod_distance = -1.0f;
    instance->cached_lod_handle = 0;

    phpglfw_math_mat4_object *transform_obj = phpglfw_math_mat4_objectptr_from_zobj_p(Z_OBJ_P(transform));
    mat4x4_dup(instance->transform, transform_obj->data);

    phpglfw_drawcall_compute_sort_key(intern, instance);

    intern->instance_count++;

    // the instance set changed, so any cached octree is now stale
    intern->oct_dirty = true;
}

// below this count neither the radix setup nor a quicksort partition pays off,
// so we use a plain stable insertion sort (it also guarantees the stable order
// the unit tests rely on).
#define PHPGLFW_SMALL_SORT_THRESHOLD 64

// stable LSD radix sort of visible_indices by the precomputed 64-bit sort_key.
//
// the keys are extracted once into a scratch array so the byte passes never
// touch the scattered 128-byte instance struct, and the scratch buffers are
// reused across calls. this wins when the keys are diverse: it replaces a
// comparison sort's O(n log n) key-chasing comparisons with a fixed number of
// linear, cache-friendly passes.
static void phpglfw_drawcall_radix_sort(phpglfw_drawcall_assembler_object *intern, uint32_t *visible_indices, uint32_t count)
{
    const phpglfw_drawcall_instance * const instances = intern->instances;

    // grow the scratch buffers if needed (geometric, like the instance array)
    if (intern->sort_scratch_capacity < count)
    {
        uint32_t new_cap = intern->sort_scratch_capacity ? intern->sort_scratch_capacity : 256;
        while (new_cap < count) {
            new_cap *= 2;
        }
        intern->sort_keys_a = erealloc(intern->sort_keys_a, new_cap * sizeof(uint64_t));
        intern->sort_keys_b = erealloc(intern->sort_keys_b, new_cap * sizeof(uint64_t));
        intern->sort_indices_b = erealloc(intern->sort_indices_b, new_cap * sizeof(uint32_t));
        intern->sort_scratch_capacity = new_cap;
    }

    uint64_t *keys_src = intern->sort_keys_a;
    uint64_t *keys_dst = intern->sort_keys_b;
    uint32_t *idx_src = visible_indices;
    uint32_t *idx_dst = intern->sort_indices_b;

    // extract the keys once so the passes below stay cache-friendly
    for (uint32_t i = 0; i < count; i++) {
        keys_src[i] = instances[idx_src[i]].sort_key;
    }

    // LSD radix over the 8 bytes of the 64-bit key
    for (uint32_t shift = 0; shift < 64; shift += 8)
    {
        uint32_t counts[256] = {0};
        for (uint32_t i = 0; i < count; i++) {
            counts[(keys_src[i] >> shift) & 0xFF]++;
        }

        // skip the pass entirely if every key shares this byte (small keys)
        if (counts[(keys_src[0] >> shift) & 0xFF] == count) {
            continue;
        }

        // exclusive prefix sum -> bucket start offsets
        uint32_t sum = 0;
        for (uint32_t b = 0; b < 256; b++) {
            const uint32_t c = counts[b];
            counts[b] = sum;
            sum += c;
        }

        // stable scatter
        for (uint32_t i = 0; i < count; i++) {
            const uint32_t pos = counts[(keys_src[i] >> shift) & 0xFF]++;
            keys_dst[pos] = keys_src[i];
            idx_dst[pos] = idx_src[i];
        }

        uint64_t *tk = keys_src; keys_src = keys_dst; keys_dst = tk;
        uint32_t *ti = idx_src; idx_src = idx_dst; idx_dst = ti;
    }

    // if the result ended up in the scratch index buffer, copy it back
    if (idx_src != visible_indices) {
        memcpy(visible_indices, idx_src, (size_t)count * sizeof(uint32_t));
    }
}

// in-place 3-way (Dutch-flag) quicksort of visible_indices by sort_key, reading
// the keys on demand. this wins when the keys are highly repetitive: equal keys
// collapse into the middle partition so the sort finishes in a couple of passes
// instead of paying the radix extract + per-byte passes. iterative with an
// explicit stack (recurse the smaller side, loop the larger) to bound depth,
// median-of-3 pivot to avoid quadratic behaviour on sorted input, and an
// insertion-sort cutoff for small partitions.
static void phpglfw_drawcall_quicksort3(const phpglfw_drawcall_instance *instances, uint32_t *a, uint32_t count)
{
    // signed bounds keep the lt-1 / gt+1 boundary math free of unsigned wrap.
    // depth is bounded to ~2*log2(count) because we only push the smaller side.
    int64_t stack[128];
    int sp = 0;
    stack[sp++] = 0;
    stack[sp++] = (int64_t)count - 1;

    while (sp > 0)
    {
        int64_t hi = stack[--sp];
        int64_t lo = stack[--sp];

        while (lo < hi)
        {
            if (hi - lo < 24)
            {
                for (int64_t i = lo + 1; i <= hi; i++) {
                    const uint32_t v = a[i];
                    const uint64_t k = instances[v].sort_key;
                    int64_t j = i;
                    while (j > lo && instances[a[j - 1]].sort_key > k) {
                        a[j] = a[j - 1];
                        j--;
                    }
                    a[j] = v;
                }
                break;
            }

            // median-of-3 pivot key from lo, mid, hi
            const int64_t mid = lo + (hi - lo) / 2;
            const uint64_t ka = instances[a[lo]].sort_key;
            const uint64_t kb = instances[a[mid]].sort_key;
            const uint64_t kc = instances[a[hi]].sort_key;
            uint64_t pivot;
            if (ka < kb) {
                pivot = (kb < kc) ? kb : ((ka < kc) ? kc : ka);
            } else {
                pivot = (ka < kc) ? ka : ((kb < kc) ? kc : kb);
            }

            // 3-way partition: [lo,lt-1] < pivot, [lt,gt] == pivot, [gt+1,hi] > pivot
            int64_t lt = lo, gt = hi, i = lo;
            while (i <= gt)
            {
                const uint64_t ki = instances[a[i]].sort_key;
                if (ki < pivot) {
                    const uint32_t t = a[lt]; a[lt] = a[i]; a[i] = t;
                    lt++; i++;
                } else if (ki > pivot) {
                    const uint32_t t = a[i]; a[i] = a[gt]; a[gt] = t;
                    gt--;
                } else {
                    i++;
                }
            }

            // recurse the smaller side, loop on the larger (bounds stack depth)
            const int64_t left_lo = lo, left_hi = lt - 1;
            const int64_t right_lo = gt + 1, right_hi = hi;
            if ((left_hi - left_lo) > (right_hi - right_lo)) {
                if (right_lo < right_hi) { stack[sp++] = right_lo; stack[sp++] = right_hi; }
                hi = left_hi;
            } else {
                if (left_lo < left_hi) { stack[sp++] = left_lo; stack[sp++] = left_hi; }
                lo = right_lo;
            }
        }
    }
}

// sorts visible_indices in place by the precomputed 64-bit instance sort_key.
//
// picks the algorithm from a cheap cardinality estimate of an evenly spaced key
// sample: diverse keys go to the radix sort (its fixed extract + pass cost
// amortizes over the many comparisons a comparison sort would otherwise do),
// while highly repetitive keys go to the 3-way quicksort (which collapses equal
// keys and finishes without radix's overhead). small batches use a stable
// insertion sort, which also guarantees the stable order the unit tests expect.
static void phpglfw_drawcall_sort_visible(phpglfw_drawcall_assembler_object *intern, uint32_t *visible_indices, uint32_t count)
{
    if (count < 2) {
        return;
    }

    const phpglfw_drawcall_instance * const instances = intern->instances;

    if (count < PHPGLFW_SMALL_SORT_THRESHOLD)
    {
        for (uint32_t i = 1; i < count; i++)
        {
            const uint32_t idx = visible_indices[i];
            const uint64_t key = instances[idx].sort_key;
            uint32_t j = i;
            while (j > 0 && instances[visible_indices[j - 1]].sort_key > key) {
                visible_indices[j] = visible_indices[j - 1];
                j--;
            }
            visible_indices[j] = idx;
        }
        return;
    }

    // estimate key cardinality from an evenly spaced sample
    enum { SAMPLE = 64 };
    uint64_t sample[SAMPLE];
    uint32_t step = count / SAMPLE;
    if (step == 0) {
        step = 1;
    }
    uint32_t sn = 0;
    for (uint32_t i = 0; sn < SAMPLE && i < count; i += step) {
        sample[sn++] = instances[visible_indices[i]].sort_key;
    }
    for (uint32_t i = 1; i < sn; i++) {
        const uint64_t v = sample[i];
        uint32_t j = i;
        while (j > 0 && sample[j - 1] > v) {
            sample[j] = sample[j - 1];
            j--;
        }
        sample[j] = v;
    }
    uint32_t distinct = sn ? 1 : 0;
    for (uint32_t i = 1; i < sn; i++) {
        if (sample[i] != sample[i - 1]) {
            distinct++;
        }
    }

    // diverse sample (>= half distinct) -> radix; repetitive -> 3-way quicksort
    if (distinct * 2 >= sn) {
        phpglfw_drawcall_radix_sort(intern, visible_indices, count);
    } else {
        phpglfw_drawcall_quicksort3(instances, visible_indices, count);
    }
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, build)
{
    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    // clear output buffers (including payload, so a frame with no payload bound
    // does not leave stale data exposed on the readonly property)
    cvector_set_size(intern->command_buffer->vec, 0);
    cvector_set_size(intern->instance_transform_buffer->vec, 0);
    cvector_set_size(intern->instance_meta_buffer->vec, 0);
    cvector_set_size(intern->instance_payload_buffer->vec, 0);

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
        // ensure the index buffer is allocated and large enough. cvector_reserve
        // is a no-op when capacity already suffices and allocates from NULL.
        cvector_reserve(intern->visible_index_buffer, visible_count);
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

    // non-const: the distance loop below mutates instances in place
    phpglfw_drawcall_instance * const instances = intern->instances;
    const phpglfw_drawcall_mesh * const meshes = intern->meshes;

    // compute the distance to camera for each visible instance
    if (intern->camera_position)
    {
        for (uint32_t i = 0; i < visible_count; i++)
        {
            const uint32_t instance_index = visible_indices[i];
            phpglfw_drawcall_instance *instance = &instances[instance_index];

            // store the SQUARED distance to the camera and skip the per-instance
            // sqrt here. LOD selection compares against squared thresholds and
            // the opaque depth bucket quantizes from the squared distance; the
            // transparent path takes the sqrt on demand in compute_sort_key.
            // the sort key is (re)computed by refresh_instance_lods below once
            // the final LOD mesh handle is known, so we don't compute it here.
            float distance_sq = phpglfw_drawcall_distance_to_camera_sq(intern->camera_position, instance->transform);
            phpglfw_drawcall_set_instance_distance(intern, instance, distance_sq);
        }
    }

    // eval LOD selection
    phpglfw_drawcall_refresh_instance_lods(intern, visible_indices, visible_count);

    // sort the visible indices by precomputed sort keys
    phpglfw_drawcall_sort_visible(intern, visible_indices, visible_count);

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

        // copy payload data if available. payload_write_ptr is non-NULL only
        // when a payload buffer is bound, so no need to re-check the zval.
        if (payload_write_ptr)
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
    // release any previously bound payload buffer first to avoid leaking it
    phpglfw_drawcall_release_zval(&intern->payload_data_buffer_zv);
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

    // nothing was submitted -> nothing to draw. return before the transform
    // buffer precondition so an empty assembler (e.g. a render pass whose
    // geometry has no instances this frame) is a harmless no-op rather than an
    // error. bindTransformBuffer only runs when a mesh is registered, so an
    // assembler that never received any instances legitimately has no VBO yet.
    if (intern->instance_count == 0) {
        intern->final_command_count = 0;
        intern->final_instance_count = 0;
        RETURN_LONG(0);
    }

    // precondition: a transform VBO must have been created via bindTransformBuffer.
    // check once up front rather than mid-loop so we never leave GL state half-bound.
    if (intern->internal_transform_vbo == 0) {
        zend_throw_error(NULL, "bindTransformBuffer must be called before execute, seeing this error means you probably forgot to bind your VAO to the DrawCallAssembler.");
        RETURN_THROWS();
    }

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
        // ensure the index buffer is allocated and large enough. cvector_reserve
        // is a no-op when capacity already suffices and allocates from NULL.
        cvector_reserve(intern->visible_index_buffer, visible_count);
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
            
            // store the SQUARED distance to the camera and skip the per-instance
            // sqrt here. LOD selection compares against squared thresholds and
            // the opaque depth bucket quantizes from the squared distance; the
            // transparent path takes the sqrt on demand in compute_sort_key.
            // the sort key is (re)computed by refresh_instance_lods below once
            // the final LOD mesh handle is known, so we don't compute it here.
            float distance_sq = phpglfw_drawcall_distance_to_camera_sq(intern->camera_position, instance->transform);
            phpglfw_drawcall_set_instance_distance(intern, instance, distance_sq);
        }
    }

    // eval LOD selection
    phpglfw_drawcall_refresh_instance_lods(intern, visible_indices, visible_count);

    // sort the visible indices by precomputed sort keys
    phpglfw_drawcall_sort_visible(intern, visible_indices, visible_count);

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

        // upload transform data to GPU using internal VBO (existence checked up front)
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
    for (uint32_t i = 0; i < intern->mesh_count; i++) {
        phpglfw_drawcall_release_mesh_refs(&intern->meshes[i]);
    }
    intern->mesh_count = 0;
}

PHP_METHOD(GL_Rendering_DrawCallAssembler, reset)
{
    if (zend_parse_parameters_none() == FAILURE)
    {
        RETURN_THROWS();
    }

    phpglfw_drawcall_assembler_object *intern = phpglfw_drawcall_assembler_objectptr_from_zobj_p(Z_OBJ_P(ZEND_THIS));

    for (uint32_t i = 0; i < intern->mesh_count; i++) {
        phpglfw_drawcall_release_mesh_refs(&intern->meshes[i]);
    }
    intern->mesh_count = 0;
    intern->instance_count = 0;
    intern->final_command_count = 0;
    intern->final_instance_count = 0;
    intern->oct_dirty = true;
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