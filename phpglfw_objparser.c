/**
 * PHP-glfw 
 * 
 * Extension: GL Textures
 *
 * Copyright (c) 2018-2022 Mario Döring
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
#include "phpglfw_objparser.h"
#include "phpglfw_arginfo.h"
#include "phpglfw_buffer.h"
#include "phpglfw_math.h"

#include <fast_obj.h>

zend_class_entry *phpglfw_objparser_ce; 
zend_class_entry *phpglfw_objparser_material_ce; 
zend_class_entry *phpglfw_objparser_group_ce;
zend_class_entry *phpglfw_objparser_texture_ce;

zend_class_entry *phpglfw_get_geometry_objparser_ce() {
    return phpglfw_objparser_ce;
}

zend_class_entry *phpglfw_get_geometry_objparser_material_ce() {
    return phpglfw_objparser_material_ce;
}

zend_class_entry *phpglfw_get_geometry_objparser_group_ce() {
    return phpglfw_objparser_group_ce;
}

zend_class_entry *phpglfw_get_geometry_objparser_texture_ce() {
    return phpglfw_objparser_texture_ce;
}

static zend_object_handlers phpglfw_objparser_handlers;

zend_object *phpglfw_objparser_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_objparser_object) + zend_object_properties_size(class_type);
    phpglfw_objparser_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    intern->mesh = NULL;

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = &phpglfw_objparser_handlers;

    return &intern->std;
}

zend_object *phpglfw_objparser_material_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_objparser_material_object) + zend_object_properties_size(class_type);
    phpglfw_objparser_material_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = zend_get_std_object_handlers();
    
    return &intern->std;
}

zend_object *phpglfw_objparser_group_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_objparser_group_object) + zend_object_properties_size(class_type);
    phpglfw_objparser_group_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = zend_get_std_object_handlers();
    
    return &intern->std;
}

zend_object *phpglfw_objparser_texture_create_handler(zend_class_entry *class_type)
{
    size_t block_len = sizeof(phpglfw_objparser_texture_object) + zend_object_properties_size(class_type);
    phpglfw_objparser_texture_object *intern = emalloc(block_len);
    memset(intern, 0, block_len);

    zend_object_std_init(&intern->std, class_type);
    object_properties_init(&intern->std, class_type);

    intern->std.handlers = zend_get_std_object_handlers();
    
    return &intern->std;
}

static void phpglfw_geometry_objparser_free_handler(zend_object *object)
{
    phpglfw_objparser_object *intern = phpglfw_objparser_objectptr_from_zobj_p(object);

    if (intern->mesh != NULL) {
        fast_obj_destroy(intern->mesh);
        intern->mesh = NULL;
    }

    zend_object_std_dtor(&intern->std);
}


// static HashTable *phpglfw_objparser_debug_info_handler(zend_object *object, int *is_temp)
// {
//     phpglfw_objparser_object *intern = phpglfw_objparser_objectptr_from_zobj_p(object);
//     zval zv;
//     HashTable *ht;

//     ht = zend_new_array(3);
//     *is_temp = 1;

//     return ht;
// }

void create_meshgroup_phparray(zval *array_zval, fastObjGroup *group_ptr, unsigned int group_size)
{
    ZVAL_EMPTY_ARRAY(array_zval);
    HashTable *ht = zend_new_array(group_size);
    ZVAL_ARR(array_zval, ht);

    for (unsigned int i = 0; i < group_size; i++) {
        zval group_obj_zval;
        object_init_ex(&group_obj_zval, phpglfw_objparser_group_ce);
        phpglfw_objparser_group_object *group_obj = phpglfw_objparser_group_objectptr_from_zobj_p(Z_OBJ_P(&group_obj_zval));
        group_obj->group = &group_ptr[i];

        php_printf("%s\n", group_obj->group->name);

        // set name property
        if (group_obj->group->name != NULL) {
            zend_update_property_string(phpglfw_objparser_group_ce, Z_OBJ_P(&group_obj_zval), "name", sizeof("name") - 1, group_obj->group->name);
        }

        // set the face count prop
        zend_update_property_long(phpglfw_objparser_group_ce, Z_OBJ_P(&group_obj_zval), "faceCount", sizeof("faceCount") - 1, group_obj->group->face_count);

        // add the array el
        zend_hash_index_update(ht, i, &group_obj_zval);
    }
}

PHP_METHOD(GL_Geometry_ObjFileParser, __construct)
{
    zend_object *curr_obj = Z_OBJ_P(getThis());
    phpglfw_objparser_object *intern = phpglfw_objparser_objectptr_from_zobj_p(curr_obj);
    
    char *file;
    size_t file_len;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &file, &file_len) == FAILURE) {
        RETURN_NULL();
    }

    intern->mesh = fast_obj_read(file);

    // handle groups
    // ----------------
    zval groups_array_zval;
    create_meshgroup_phparray(&groups_array_zval, intern->mesh->groups, intern->mesh->group_count);
    zend_update_property(phpglfw_objparser_ce, curr_obj, "groups", sizeof("groups")-1, &groups_array_zval);

    // handle objects
    // ----------------
    zval objects_array_zval;
    create_meshgroup_phparray(&objects_array_zval, intern->mesh->objects, intern->mesh->object_count);
    zend_update_property(phpglfw_objparser_ce, curr_obj, "objects", sizeof("objects")-1, &objects_array_zval);

    // handle materials
    // ----------------
    zval materials_array_zval;
    ZVAL_EMPTY_ARRAY(&materials_array_zval);

    // get hash table from val
    HashTable *ht = zend_new_array(intern->mesh->material_count);
    ZVAL_ARR(&materials_array_zval, ht);
    zend_update_property(phpglfw_objparser_ce, Z_OBJ_P(getThis()), "materials", sizeof("materials")-1, &materials_array_zval);

    // go over each material construct a php phpglfw_objparser_material_object and add it to the hash table
    for (int i = 0; i < intern->mesh->material_count; i++) {
        zval material_zval;
        object_init_ex(&material_zval, phpglfw_objparser_material_ce);
        phpglfw_objparser_material_object *material_intern = phpglfw_objparser_material_objectptr_from_zobj_p(Z_OBJ_P(&material_zval));
        material_intern->material = &intern->mesh->materials[i];

        // set name property
        zend_update_property_string(phpglfw_objparser_material_ce, Z_OBJ_P(&material_zval), "name", sizeof("name")-1, intern->mesh->materials[i].name);

        // set the ambient property
        zval ambient_zval;
        ZVAL_UNDEF(&ambient_zval);
        object_init_ex(&ambient_zval, phpglfw_get_math_vec3_ce());
        phpglfw_math_vec3_object *ambient_intern = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(&ambient_zval));
        ambient_intern->data[0] = intern->mesh->materials[i].Ka[0];
        ambient_intern->data[1] = intern->mesh->materials[i].Ka[1];
        ambient_intern->data[2] = intern->mesh->materials[i].Ka[2];
        zend_update_property(phpglfw_objparser_material_ce, Z_OBJ_P(&material_zval), "ambient", sizeof("ambient")-1, &ambient_zval);

        // set the diffuse property
        zval diffuse_zval;
        ZVAL_UNDEF(&diffuse_zval);
        object_init_ex(&diffuse_zval, phpglfw_get_math_vec3_ce());
        phpglfw_math_vec3_object *diffuse_intern = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(&diffuse_zval));
        diffuse_intern->data[0] = intern->mesh->materials[i].Kd[0];
        diffuse_intern->data[1] = intern->mesh->materials[i].Kd[1];
        diffuse_intern->data[2] = intern->mesh->materials[i].Kd[2];
        zend_update_property(phpglfw_objparser_material_ce, Z_OBJ_P(&material_zval), "diffuse", sizeof("diffuse")-1, &diffuse_zval);

        // set the specular property
        zval specular_zval;
        ZVAL_UNDEF(&specular_zval);
        object_init_ex(&specular_zval, phpglfw_get_math_vec3_ce());
        phpglfw_math_vec3_object *specular_intern = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(&specular_zval));
        specular_intern->data[0] = intern->mesh->materials[i].Ks[0];
        specular_intern->data[1] = intern->mesh->materials[i].Ks[1];
        specular_intern->data[2] = intern->mesh->materials[i].Ks[2];
        zend_update_property(phpglfw_objparser_material_ce, Z_OBJ_P(&material_zval), "specular", sizeof("specular")-1, &specular_zval);

        // set the emissive property
        zval emissive_zval;
        ZVAL_UNDEF(&emissive_zval);
        object_init_ex(&emissive_zval, phpglfw_get_math_vec3_ce());
        phpglfw_math_vec3_object *emissive_intern = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(&emissive_zval));
        emissive_intern->data[0] = intern->mesh->materials[i].Ke[0];
        emissive_intern->data[1] = intern->mesh->materials[i].Ke[1];
        emissive_intern->data[2] = intern->mesh->materials[i].Ke[2];
        zend_update_property(phpglfw_objparser_material_ce, Z_OBJ_P(&material_zval), "emissive", sizeof("emissive")-1, &emissive_zval);

        // set the transmittance property
        zval transmittance_zval;
        ZVAL_UNDEF(&transmittance_zval);
        object_init_ex(&transmittance_zval, phpglfw_get_math_vec3_ce());
        phpglfw_math_vec3_object *transmittance_intern = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(&transmittance_zval));
        transmittance_intern->data[0] = intern->mesh->materials[i].Kt[0];
        transmittance_intern->data[1] = intern->mesh->materials[i].Kt[1];
        transmittance_intern->data[2] = intern->mesh->materials[i].Kt[2];
        zend_update_property(phpglfw_objparser_material_ce, Z_OBJ_P(&material_zval), "transmittance", sizeof("transmittance")-1, &transmittance_zval);
        
        // set the transmission filter property
        zval transmission_filter_zval;
        ZVAL_UNDEF(&transmission_filter_zval);
        object_init_ex(&transmission_filter_zval, phpglfw_get_math_vec3_ce());
        phpglfw_math_vec3_object *transmission_filter_intern = phpglfw_math_vec3_objectptr_from_zobj_p(Z_OBJ_P(&transmission_filter_zval));
        transmission_filter_intern->data[0] = intern->mesh->materials[i].Tf[0];
        transmission_filter_intern->data[1] = intern->mesh->materials[i].Tf[1];
        transmission_filter_intern->data[2] = intern->mesh->materials[i].Tf[2];
        zend_update_property(phpglfw_objparser_material_ce, Z_OBJ_P(&material_zval), "transmissionFilter", sizeof("transmissionFilter")-1, &transmission_filter_zval);

        // set the shininess property
        zend_update_property_double(phpglfw_objparser_material_ce, Z_OBJ_P(&material_zval), "shininess", sizeof("shininess")-1, intern->mesh->materials[i].Ns);

        // set the index of refraction property
        zend_update_property_double(phpglfw_objparser_material_ce, Z_OBJ_P(&material_zval), "indexOfRefraction", sizeof("indexOfRefraction")-1, intern->mesh->materials[i].Ni);
        
        // set the dissolve property
        zend_update_property_double(phpglfw_objparser_material_ce, Z_OBJ_P(&material_zval), "dissolve", sizeof("dissolve")-1, intern->mesh->materials[i].d);

        // set the illumination model property
        zend_update_property_long(phpglfw_objparser_material_ce, Z_OBJ_P(&material_zval), "illuminationModel", sizeof("illuminationModel")-1, intern->mesh->materials[i].illum);

        // add the material to the array
        zend_hash_index_update(ht, i, &material_zval);
    }   
}

PHP_METHOD(GL_Geometry_ObjFileParser_Material, __construct)
{
    zend_throw_error(NULL, "Cannot construct a material directly");
}

PHP_METHOD(GL_Geometry_ObjFileParser_Group, __construct)
{
    zend_throw_error(NULL, "Cannot construct a group directly");
}

PHP_METHOD(GL_Geometry_ObjFileParser_Texture, __construct)
{
    zend_throw_error(NULL, "Cannot construct a texture directly");
}

void phpglfw_register_objparser_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;
    
    // Obj File Parser
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Geometry\\ObjFileParser", class_GL_Geometry_ObjFileParser_methods);
    phpglfw_objparser_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_objparser_ce->create_object = phpglfw_objparser_create_handler;

    memcpy(&phpglfw_objparser_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_objparser_handlers));

#if PHP_VERSION_ID >= 80100 && 0
    int prop_access_flags = ZEND_ACC_PUBLIC | ZEND_ACC_READONLY;
#else
    int prop_access_flags = ZEND_ACC_PUBLIC;
#endif

    // meterials prop
    zval property_materials_default_value;
	ZVAL_UNDEF(&property_materials_default_value);
	zend_string *property_materials_name = zend_string_init("materials", sizeof("materials") - 1, 1);
	zend_declare_typed_property(phpglfw_objparser_ce, property_materials_name, &property_materials_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_materials_name);

    // groups prop
    zval property_groups_default_value;
    ZVAL_UNDEF(&property_groups_default_value);
    zend_string *property_groups_name = zend_string_init("groups", sizeof("groups") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_ce, property_groups_name, &property_groups_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
    zend_string_release(property_groups_name);

    // objects prop
    zval property_objects_default_value;
    ZVAL_UNDEF(&property_objects_default_value);
    zend_string *property_objects_name = zend_string_init("objects", sizeof("objects") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_ce, property_objects_name, &property_objects_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
    zend_string_release(property_objects_name);

    // phpglfw_objparser_handlers.get_debug_info = phpglfw_objparser_debug_info_handler;
    phpglfw_objparser_handlers.free_obj = phpglfw_geometry_objparser_free_handler;

    // Obj File Parser Material
    // ------------------------------
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Geometry\\ObjFileParser\\Material", class_GL_Geometry_ObjFileParser_Material_methods);
    phpglfw_objparser_material_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_objparser_material_ce->create_object = phpglfw_objparser_material_create_handler;

    // material name prop (public readonly string $name)
    zval property_material_name_default_value;
    ZVAL_UNDEF(&property_material_name_default_value);
    zend_string *property_material_name = zend_string_init("name", sizeof("name") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_material_ce, property_material_name, &property_material_name_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
    zend_string_release(property_material_name);

    // material ambient prop (public readonly Vec3 $ambient)
	zend_string *property_material_ambient_class_Vec3 = zend_string_init("GL\\Math\\Vec3", sizeof("GL\\Math\\Vec3")-1, 1);
    zval property_material_ambient_default_value;
    ZVAL_NULL(&property_material_ambient_default_value);
    zend_string *property_material_ambient = zend_string_init("ambient", sizeof("ambient") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_material_ce, property_material_ambient, &property_material_ambient_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_material_ambient_class_Vec3, 0, MAY_BE_NULL));
    zend_string_release(property_material_ambient);

    // material diffuse prop (public readonly Vec3 $diffuse)
    zend_string *property_material_diffuse_class_Vec3 = zend_string_init("GL\\Math\\Vec3", sizeof("GL\\Math\\Vec3")-1, 1);
    zval property_material_diffuse_default_value;
    ZVAL_NULL(&property_material_diffuse_default_value);
    zend_string *property_material_diffuse = zend_string_init("diffuse", sizeof("diffuse") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_material_ce, property_material_diffuse, &property_material_diffuse_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_material_diffuse_class_Vec3, 0, MAY_BE_NULL));
    zend_string_release(property_material_diffuse);

    // material specular prop (public readonly Vec3 $sepcular)
    zend_string *property_material_specular_class_Vec3 = zend_string_init("GL\\Math\\Vec3", sizeof("GL\\Math\\Vec3")-1, 1);
    zval property_material_specular_default_value;
    ZVAL_NULL(&property_material_specular_default_value);
    zend_string *property_material_specular = zend_string_init("specular", sizeof("specular") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_material_ce, property_material_specular, &property_material_specular_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_material_specular_class_Vec3, 0, MAY_BE_NULL));
    zend_string_release(property_material_specular);

    // material emissive prop (public readonly Vec3 $emissive)
    zend_string *property_material_emissive_class_Vec3 = zend_string_init("GL\\Math\\Vec3", sizeof("GL\\Math\\Vec3")-1, 1);
    zval property_material_emissive_default_value;
    ZVAL_NULL(&property_material_emissive_default_value);
    zend_string *property_material_emissive = zend_string_init("emissive", sizeof("emissive") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_material_ce, property_material_emissive, &property_material_emissive_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_material_emissive_class_Vec3, 0, MAY_BE_NULL));
    zend_string_release(property_material_emissive);

    // material transmittance prop (public readonly Vec3 $transmittance)
    zend_string *property_material_transmittance_class_Vec3 = zend_string_init("GL\\Math\\Vec3", sizeof("GL\\Math\\Vec3")-1, 1);
    zval property_material_transmittance_default_value;
    ZVAL_NULL(&property_material_transmittance_default_value);
    zend_string *property_material_transmittance = zend_string_init("transmittance", sizeof("transmittance") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_material_ce, property_material_transmittance, &property_material_transmittance_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_material_transmittance_class_Vec3, 0, MAY_BE_NULL));
    zend_string_release(property_material_transmittance);

    // material transmission filter prop (public readonly Vec3 $transmissionFilter)
    zend_string *property_material_transmissionFilter_class_float = zend_string_init("GL\\Math\\Vec3", sizeof("GL\\Math\\Vec3")-1, 1);
    zval property_material_transmissionFilter_default_value;
    ZVAL_DOUBLE(&property_material_transmissionFilter_default_value, 1.0);
    zend_string *property_material_transmissionFilter = zend_string_init("transmissionFilter", sizeof("transmissionFilter") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_material_ce, property_material_transmissionFilter, &property_material_transmissionFilter_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_CLASS(property_material_transmissionFilter_class_float, 0, MAY_BE_NULL));
    zend_string_release(property_material_transmissionFilter);

    // material shininess prop (public readonly float $shininess)
    zval property_material_shininess_default_value;
    ZVAL_DOUBLE(&property_material_shininess_default_value, 1.0);
    zend_string *property_material_shininess = zend_string_init("shininess", sizeof("shininess") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_material_ce, property_material_shininess, &property_material_shininess_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
    zend_string_release(property_material_shininess);

    // material index of refraction prop (public readonly float $indexOfRefraction)
    zval property_material_indexOfRefraction_default_value;
    ZVAL_DOUBLE(&property_material_indexOfRefraction_default_value, 1.0);
    zend_string *property_material_indexOfRefraction = zend_string_init("indexOfRefraction", sizeof("indexOfRefraction") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_material_ce, property_material_indexOfRefraction, &property_material_indexOfRefraction_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
    zend_string_release(property_material_indexOfRefraction);

    // material dissolve prop (public readonly float $dissolve)
    zval property_material_dissolve_default_value;
    ZVAL_DOUBLE(&property_material_dissolve_default_value, 1.0);
    zend_string *property_material_dissolve = zend_string_init("dissolve", sizeof("dissolve") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_material_ce, property_material_dissolve, &property_material_dissolve_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_DOUBLE));
    zend_string_release(property_material_dissolve);

    // material illumination model prop (public readonly int $illuminationModel)
    zval property_material_illuminationModel_default_value;
    ZVAL_LONG(&property_material_illuminationModel_default_value, 0);
    zend_string *property_material_illuminationModel = zend_string_init("illuminationModel", sizeof("illuminationModel") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_material_ce, property_material_illuminationModel, &property_material_illuminationModel_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
    zend_string_release(property_material_illuminationModel);

    // Obj File Parser Group
    // ------------------------------
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Geometry\\ObjFileParser\\Group", class_GL_Geometry_ObjFileParser_Group_methods);
    phpglfw_objparser_group_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_objparser_group_ce->create_object = phpglfw_objparser_material_create_handler;

    // group name prop (public readonly string $name)
    zval property_group_name_default_value;
    ZVAL_NULL(&property_group_name_default_value);
    zend_string *property_group_name = zend_string_init("name", sizeof("name") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_group_ce, property_group_name, &property_group_name_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
    zend_string_release(property_group_name);

    // group face count prop (public readonly int $faceCount)
    zval property_group_face_count_default_value;
    ZVAL_LONG(&property_group_face_count_default_value, 0);
    zend_string *property_group_face_count = zend_string_init("faceCount", sizeof("faceCount") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_group_ce, property_group_face_count, &property_group_face_count_default_value, prop_access_flags, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_LONG));
    zend_string_release(property_group_face_count);


}