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

#include <fast_obj.h>

zend_class_entry *phpglfw_objparser_ce; 
zend_class_entry *phpglfw_objparser_material_ce; 

zend_class_entry *phpglfw_get_geometry_objparser_ce() {
    return phpglfw_objparser_ce;
}

zend_class_entry *phpglfw_get_geometry_objparser_material_ce() {
    return phpglfw_objparser_material_ce;
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

PHP_METHOD(GL_Geometry_ObjFileParser, __construct)
{
    phpglfw_objparser_object *intern = phpglfw_objparser_objectptr_from_zobj_p(Z_OBJ_P(getThis()));
    
    char *file;
    size_t file_len;
    if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &file, &file_len) == FAILURE) {
        RETURN_NULL();
    }

    intern->mesh = fast_obj_read(file);

    zval val;
    ZVAL_EMPTY_ARRAY(&val);

    // get hash table from val
    HashTable *ht = zend_new_array(intern->mesh->material_count);
    ZVAL_ARR(&val, ht);
    zend_update_property(phpglfw_objparser_ce, Z_OBJ_P(getThis()), "materials", sizeof("materials")-1, &val);

    // go over each material construct a php phpglfw_objparser_material_object and add it to the hash table
    for (int i = 0; i < intern->mesh->material_count; i++) {
        zval material_zval;
        object_init_ex(&material_zval, phpglfw_objparser_material_ce);
        phpglfw_objparser_material_object *material_intern = phpglfw_objparser_material_objectptr_from_zobj_p(&material_zval);
        material_intern->material = &intern->mesh->materials[i];

        // set name property
        zend_update_property_string(phpglfw_objparser_material_ce, Z_OBJ_P(&material_zval), "name", sizeof("name")-1, intern->mesh->materials[i].name);
      
        zend_hash_index_update(ht, i, &material_zval);
    }
    
}


PHP_METHOD(GL_Geometry_ObjFileParser_Material, __construct)
{
    zend_throw_error(NULL, "Cannot construct a material directly");
}

void phpglfw_register_objparser_module(INIT_FUNC_ARGS)
{
    zend_class_entry tmp_ce;
    
    // Obj File Parser
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Geometry\\ObjFileParser", class_GL_Geometry_ObjFileParser_methods);
    phpglfw_objparser_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_objparser_ce->create_object = phpglfw_objparser_create_handler;

    memcpy(&phpglfw_objparser_handlers, zend_get_std_object_handlers(), sizeof(phpglfw_objparser_handlers));

    // meterials prop
    zval property_materials_default_value;
	ZVAL_UNDEF(&property_materials_default_value);
	zend_string *property_materials_name = zend_string_init("materials", sizeof("materials") - 1, 1);
	zend_declare_typed_property(phpglfw_objparser_ce, property_materials_name, &property_materials_default_value, ZEND_ACC_PUBLIC | ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_ARRAY));
	zend_string_release(property_materials_name);

    // phpglfw_objparser_handlers.get_debug_info = phpglfw_objparser_debug_info_handler;
    phpglfw_objparser_handlers.free_obj = phpglfw_geometry_objparser_free_handler;

    // Obj File Parser Material
    INIT_CLASS_ENTRY(tmp_ce, "GL\\Geometry\\ObjFileParser\\Material", class_GL_Geometry_ObjFileParser_Material_methods);
    phpglfw_objparser_material_ce = zend_register_internal_class(&tmp_ce);
    phpglfw_objparser_material_ce->create_object = phpglfw_objparser_material_create_handler;

    // material name prop
    zval property_material_name_default_value;
    ZVAL_UNDEF(&property_material_name_default_value);
    zend_string *property_material_name = zend_string_init("name", sizeof("name") - 1, 1);
    zend_declare_typed_property(phpglfw_objparser_material_ce, property_material_name, &property_material_name_default_value, ZEND_ACC_PUBLIC | ZEND_ACC_READONLY, NULL, (zend_type) ZEND_TYPE_INIT_MASK(MAY_BE_STRING));
    zend_string_release(property_material_name);


}