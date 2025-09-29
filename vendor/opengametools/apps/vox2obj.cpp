
/*
    vox2obj - MIT license - Justin Paver, April 2022

    A program that can convert MagicaVoxel .vox files to .obj, with optional support
    for extracting given frames of animation out as either separate .obj or as
    separate objects within the .obj file.

    Please see the MIT license information at the end of this file, and please consider
    sharing any improvements you make.
*/

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
// if min/max are not already defined, windows.h defines them, which breaks std::min/std::max.
// we can safely undefine them after we've included windows.h
#define max
#define min
#include <windows.h>
#undef max
#undef min
#endif

#define OGT_VOX_IMPLEMENTATION
#include "../src/ogt_vox.h"

#define OGT_VOXEL_MESHIFY_IMPLEMENTATION
#include "../src/ogt_voxel_meshify.h"

#if defined(_MSC_VER)
    #include <io.h>
#endif
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>
#include <math.h>

FILE * open_file(const char *filename, const char *mode)
{
#if defined(_MSC_VER) && _MSC_VER >= 1400
    FILE * fp;
    if (0 != fopen_s(&fp, filename, mode))
        fp = 0;
#else
    FILE * fp = fopen(filename, mode);
#endif
    return fp;
}

// a helper function to load a magica voxel scene given a filename.
const ogt_vox_scene* load_vox_scene(const char* filename, uint32_t scene_read_flags = 0)
{
    // open the file
    FILE * fp = open_file(filename, "rb");
    if (!fp)
        return NULL;

    // get the buffer size which matches the size of the file
    fseek(fp, 0, SEEK_END);
    uint32_t buffer_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // load the file into a memory buffer
    uint8_t * buffer = new uint8_t[buffer_size];
    fread(buffer, buffer_size, 1, fp);
    fclose(fp);

    // construct the scene from the buffer
    const ogt_vox_scene * scene = ogt_vox_read_scene_with_flags(buffer, buffer_size, scene_read_flags);

    // the buffer can be safely deleted once the scene is instantiated.
    delete[] buffer;

    return scene;
}

std::string to_string_zeroes(uint32_t value, uint32_t num_digits) {
    std::string str = std::to_string(value);
    while (str.size() < num_digits) {
        str = std::string("0") + str;
    }
    return str;
}

// computes transform * vec4(vec3.xyz, 0.0)
ogt_mesh_vec3 transform_vector(const ogt_vox_transform& transform, const ogt_mesh_vec3& vec) {
    ogt_mesh_vec3 result;
    result.x = (vec.x * transform.m00) + (vec.y * transform.m10) + (vec.z * transform.m20) + (0.0f * transform.m30);
    result.y = (vec.x * transform.m01) + (vec.y * transform.m11) + (vec.z * transform.m21) + (0.0f * transform.m31);
    result.z = (vec.x * transform.m02) + (vec.y * transform.m12) + (vec.z * transform.m22) + (0.0f * transform.m32);
    return result;
}

// computes transform * vec4(vec3.xyz, 1.0)
// assumes (m03, m13, m23, m33) == (0,0,0,1)
ogt_mesh_vec3 transform_point(const ogt_vox_transform& transform, const ogt_mesh_vec3& vec) {
    ogt_mesh_vec3 result;
    result.x = (vec.x * transform.m00) + (vec.y * transform.m10) + (vec.z * transform.m20) + (1.0f * transform.m30);
    result.y = (vec.x * transform.m01) + (vec.y * transform.m11) + (vec.z * transform.m21) + (1.0f * transform.m31);
    result.z = (vec.x * transform.m02) + (vec.y * transform.m12) + (vec.z * transform.m22) + (1.0f * transform.m32);
    return result;
}

// writes
void write_tga_24bit(const uint8_t* pixels, uint32_t width, uint32_t height, FILE* fout) {
    #pragma pack(push, 1)
    #pragma pack(1)
    struct tga_file_header {
        uint8_t  id_length;
        uint8_t  color_map_type;
        uint8_t  image_type;
        uint16_t first_entry_index;
        uint16_t color_map_length;
        uint8_t  color_map_entry_size;
        uint16_t origin_x;
        uint16_t origin_y;
    };
    struct tga_image_header {
        uint16_t image_width;
        uint16_t image_height;
        uint8_t  pixel_depth;
        uint8_t  pixel_descriptor;
    };
    #pragma pack(pop)
    tga_file_header  file_header = {0, 0, 2, 0, 0, 0, 0, 0 };
    tga_image_header image_header = { (uint16_t)width, (uint16_t)height, 24, 0 };
    fwrite(&file_header, sizeof(file_header), 1, fout);
    fwrite(&image_header, sizeof(image_header), 1, fout);
    // input is R,G,B, but we write in B,G,R order. This is a super slow implementation
    // that writes a byte at a time to the file, but whatever...
    uint32_t image_size = width * height * 3;
    for (uint32_t i = 0; i < image_size; i += 3) {
        fwrite(&pixels[i+2], 1, 1, fout);
        fwrite(&pixels[i+1], 1, 1, fout);
        fwrite(&pixels[i+0], 1, 1, fout);
    }
}

FILE* open_obj_file(const char* filename)
{
    FILE * fout = open_file(filename, "wb");
    if (!fout) {
        printf("could not open file '%s' for write - aborting!", filename);
        return nullptr;
    }
    printf("writing file %s\n", filename);
    // there will only ever be 6 normals, so write them out only once.
    fprintf(fout, "vn 1 0 0\n");
    fprintf(fout, "vn -1 0 0\n");
    fprintf(fout, "vn 0 1 0\n");
    fprintf(fout, "vn 0 -1 0\n");
    fprintf(fout, "vn 0 0 1\n");
    fprintf(fout, "vn 0 0 -1\n");

    // there will only ever be up to 256 texcoords, so write them out only once
    for (uint32_t i = 0; i < 256; i++) {
        float u = (0.5f + (float)i) * (1.0f / 256.0f);
        fprintf(fout, "vt %f 0.5\n", u);
    }
    return fout;
}

// converts input value to a string and pds with zeroes to a given length
// eg. zero_padded_string(5,  3)  => "005"
// eg. zero_padded_string(132,3)  => "132"
// eg. zero_padded_string(1453,2) => "1453"
std::string zero_padded_string(uint32_t value, uint32_t num_zeroes) {
    std::string ret = std::to_string(value);
    // not a particularly good way to do this, but it works.
    while (ret.size() < num_zeroes) {
        ret = std::string("0") + ret;
    }
    return ret;
}

void get_frame_min_max(const ogt_vox_scene* scene, uint32_t& frame_min, uint32_t& frame_max) {
    // if frame_min/frame_max are all -1, we determine the frame range from the keyframes within the specified file.
    if (frame_min == UINT32_MAX && frame_max == UINT32_MAX) {
        frame_max = 0;
        frame_min = UINT32_MAX;
        for (uint32_t instance_index = 0; instance_index < scene->num_instances; instance_index++) {
            const ogt_vox_instance* instance = &scene->instances[instance_index];
            if (instance->model_anim.num_keyframes) {
                frame_max = std::max(frame_max, instance->model_anim.keyframes[instance->model_anim.num_keyframes-1].frame_index);
                frame_min = std::min(frame_max, instance->model_anim.keyframes[0].frame_index);
            }
            if (instance->transform_anim.num_keyframes) {
                frame_max = std::max(frame_max, instance->transform_anim.keyframes[instance->transform_anim.num_keyframes-1].frame_index);
                frame_min = std::min(frame_max, instance->transform_anim.keyframes[0].frame_index);
            }
        }
        if (frame_min > frame_max) {
            frame_min = 0;
            frame_max = 0;
        }
    }
}

bool save_scene(const ogt_vox_scene* scene, const std::string& file_name) {
    // serialize the memory buffer
    uint32_t buffer_size = 0;
    uint8_t* buffer      = ogt_vox_write_scene(scene, &buffer_size);
    if (!buffer || !buffer_size) {
        return false;
    }
    // write to file!
    bool  ret = false;
    FILE* fp  = open_file(file_name.c_str(), "wb");
    if (fp)
    {
        fwrite(buffer, buffer_size, 1, fp);
        fclose(fp);
        ret = true;
    }
    ogt_vox_free(buffer);
    return ret;
}

bool export_scene_anim_as_vox(const ogt_vox_scene* scene, const std::string& out_name, uint32_t frame_min, uint32_t frame_max) {
    bool ret = true;

    get_frame_min_max(scene, frame_min, frame_max);

    ogt_vox_instance* instances = new ogt_vox_instance[scene->num_instances];
    ogt_vox_group*    groups    = new ogt_vox_group[scene->num_groups];

    for (uint32_t frame_index = frame_min; frame_index <= frame_max; frame_index++) {
        // assemble the scene
        for (uint32_t instance_index = 0; instance_index < scene->num_instances; instance_index++) {
            instances[instance_index]                              = scene->instances[instance_index];
            instances[instance_index].transform                    = ogt_vox_sample_instance_transform_local(&scene->instances[instance_index], frame_index);
            instances[instance_index].model_index                  = ogt_vox_sample_instance_model(&scene->instances[instance_index], frame_index);
            instances[instance_index].transform_anim.num_keyframes = 0;
            instances[instance_index].transform_anim.keyframes     = nullptr;
            instances[instance_index].model_anim.num_keyframes     = 0;
            instances[instance_index].model_anim.keyframes         = nullptr;
        }
        for (uint32_t group_index = 0; group_index < scene->num_groups; group_index++) {
            groups[group_index]                              = scene->groups[group_index];
            groups[group_index].transform                    = ogt_vox_sample_group_transform_local(&scene->groups[group_index], frame_index);
            groups[group_index].transform_anim.num_keyframes = 0;
            groups[group_index].transform_anim.keyframes     = nullptr;
        }
        ogt_vox_scene out_scene = *scene;
        out_scene.groups    = groups;
        out_scene.instances = instances;

        // write to disck
        std::string out_vox_name = out_name + "-" + zero_padded_string(frame_index, 3) + ".vox";
        ret &= save_scene(&out_scene, out_vox_name);
    }
    delete[] instances;
    delete[] groups;
    return ret;
}

bool export_scene_anim_as_obj(const ogt_vox_scene* scene, const std::string& out_name, bool out_file_per_frame, float voxel_scale, uint32_t frame_min, uint32_t frame_max, const char* mesh_algorithm) {
    get_frame_min_max(scene, frame_min, frame_max);

    // put the color index into the alpha component of every color in the palette
    ogt_vox_palette palette = scene->palette;
    for (uint32_t i = 0; i < 256; i++) {
        palette.color[i].a = (uint8_t)i;
    }

    // meshify all models.
    ogt_voxel_meshify_context meshify_context = {};
    std::vector<ogt_mesh*> meshes;
    meshes.resize(scene->num_models, nullptr);

    // go through all frames
    std::string out_texture_name = out_name + ".tga";
    std::string out_material_name = out_name + ".mtl";

    // write palette data as tga
    {
        FILE* fout = open_file(out_texture_name.c_str(), "wb");
        if (!fout) {
            printf("could not open file '%s' for write - aborting!", out_texture_name.c_str());
            return false;
        }

        printf("writing file %s\n", out_texture_name.c_str());
        uint8_t tga_data[256*3];
        for (uint32_t j = 0; j < 256; j++) {
            tga_data[j * 3 + 0] = palette.color[j].r;
            tga_data[j * 3 + 1] = palette.color[j].g;
            tga_data[j * 3 + 2] = palette.color[j].b;
        }
        write_tga_24bit(tga_data, 256, 1, fout);
        fclose(fout);
    }

    // write material data
    {
        FILE* fout = open_file(out_material_name.c_str(), "wb");
        if (!fout) {
            printf("could not open file '%s' for write - aborting!", out_material_name.c_str());
            return false;
        }
        printf("writing file %s\n", out_material_name.c_str());
        fprintf(fout, "# opengametools vox2obj - see source code at https://github.com/jpaver/opengametools/tree/master/apps/vox2obj.cpp\r\n"); // TODO(jpaver) proper header
        fprintf(fout, "\r\n");
        fprintf(fout, "newmtl palette\r\n");
        fprintf(fout, "illum 1\r\n");
        fprintf(fout, "Ka 0.000 0.000 0.000\r\n");
        fprintf(fout, "Kd 1.000 1.000 1.000\r\n");
        fprintf(fout, "Ks 0.000 0.000 0.000\r\n");
        fprintf(fout, "map_Kd %s\r\n", out_texture_name.c_str());
        fclose(fout);
    }

    // write geometry data
    bool error = false;
    {
        FILE* fout = nullptr;
        uint32_t base_vertex_index = 0;
        for (uint32_t frame_index = frame_min; frame_index <= frame_max; frame_index++) {
            if (out_file_per_frame) {
                if (fout)
                    fclose(fout);
                std::string out_obj_name = out_name + "-" + zero_padded_string(frame_index, 3) + ".obj";
                fout = open_obj_file(out_obj_name.c_str());
                if (!fout) {
                    printf("could not open file '%s' for write - aborting!", out_obj_name.c_str());
                    error = true;
                    break;
                }
                base_vertex_index = 0;
            }
            else if (!fout) {
                std::string out_obj_name = out_name + ".obj";
                fout = open_obj_file(out_obj_name.c_str());
                if (!fout) {
                    printf("could not open file '%s' for write - aborting!", out_obj_name.c_str());
                    error = true;
                    break;
                }
            }

            fprintf(fout, "o frame_%03u\n", frame_index);
            fprintf(fout, "mtllib %s\n", out_material_name.c_str());
            fprintf(fout, "usemtl palette\n");

            for (uint32_t instance_index = 0; instance_index < scene->num_instances; instance_index++) {
                const ogt_vox_instance* instance = &scene->instances[instance_index];
                // skip this instance if it's hidden in the .vox file
                if (instance->hidden)
                    continue;
                // skip this instance if it's part of a hidden layer in the .vox file
                if (scene->layers[instance->layer_index].hidden)
                    continue;
                // skip this instance if it's part of a hidden group
                if (instance->group_index != k_invalid_group_index && scene->groups[instance->group_index].hidden)
                    continue;

                ogt_vox_transform transform   = ogt_vox_sample_instance_transform_global(instance, frame_index, scene);
                uint32_t          model_index = ogt_vox_sample_instance_model(instance, frame_index);

                // just in time generate the mesh for this model if we haven't already done so.
                const ogt_vox_model* model = scene->models[model_index];
                if (model && !meshes[model_index]) {
                    // generate a mesh for this model using the mesh_algorithm specified
                    printf("  - generating mesh for model of size %u x %u x %u using mesh_algorithm %s\n", model->size_x, model->size_y, model->size_z, mesh_algorithm);
                    ogt_mesh* mesh =
                        (strcmp(mesh_algorithm, "polygon") == 0) ? ogt_mesh_from_paletted_voxels_polygon(&meshify_context, model->voxel_data, model->size_x, model->size_y, model->size_z, (const ogt_mesh_rgba*)&palette.color[0]) :
                        (strcmp(mesh_algorithm, "greedy") == 0) ? ogt_mesh_from_paletted_voxels_greedy(&meshify_context, model->voxel_data, model->size_x, model->size_y, model->size_z, (const ogt_mesh_rgba*)&palette.color[0]) :
                        (strcmp(mesh_algorithm, "simple") == 0) ? ogt_mesh_from_paletted_voxels_simple(&meshify_context, model->voxel_data, model->size_x, model->size_y, model->size_z, (const ogt_mesh_rgba*)&palette.color[0]) :
                        NULL;

                    for (uint32_t i = 0; i < mesh->vertex_count; i++) {
                        // pre-bias the mesh vertices by the model dimensions - resets the center/pivot so it is at (0,0,0)
                        mesh->vertices[i].pos.x -= (float)(model->size_x / 2);
                        mesh->vertices[i].pos.y -= (float)(model->size_y / 2);
                        mesh->vertices[i].pos.z -= (float)(model->size_z / 2);
                        // the normal is always a unit vector aligned on one of the 6 cardinal directions, here we just
                        // precompute which index it was (same order as the 'vn' tags we wrote out when opening the file)
                        // and write it as a uint32_t into the x field. This allows us to avoid do this index conversion
                        // for every vert in a mesh, and not for every vert multiplied by the number of instances.
                        ogt_mesh_vec3& normal = mesh->vertices[i].normal;
                        uint32_t normal_index = normal.x != 0 ? (normal.x > 0.0f ? 0 : 1) :
                                                normal.y != 0 ? (normal.y > 0.0f ? 2 : 3) :
                                                (normal.z > 0.0f ? 4 : 5);
                        *(uint32_t*)&normal.x = normal_index;
                    }
                    // cache this mesh so we don't need to do it multiple times.
                    meshes[model_index] = mesh;
                }

                // some instances can have no geometry, so we just skip em
                const ogt_mesh* mesh = meshes[model_index];
                if (!mesh)
                    continue;

                if (voxel_scale != 1.0f) {
                    // bake voxel scale into the transform to avoid doing the scale per vertex.
                    float* transform_data = &transform.m00;
                    for (size_t i = 0; i < 16; i++) {
                        transform_data[i] *= voxel_scale;
                    }
                    // scaling vertex positions, so we do floating point writes
                    for (size_t i = 0; i < mesh->vertex_count; i++) {
                        ogt_mesh_vec3 pos = transform_point(transform, mesh->vertices[i].pos);
                        fprintf(fout, "v %f %f %f\n", pos.x, pos.y, pos.z);
                    }
                }
                else {
                    // we're not scaling positions, can write them much more compactly (smaller .obj file size) as int.
                    for (size_t i = 0; i < mesh->vertex_count; i++) {
                        ogt_mesh_vec3 pos = transform_point(transform, mesh->vertices[i].pos);
                        fprintf(fout, "v %i %i %i\n", (int32_t)pos.x, (int32_t)pos.y, (int32_t)pos.z);
                    }
                }
                // write faces
                for (size_t i = 0; i < mesh->index_count; i += 3) {
                    uint32_t v_i0 = base_vertex_index + mesh->indices[i + 0] + 1;
                    uint32_t v_i1 = base_vertex_index + mesh->indices[i + 1] + 1;
                    uint32_t v_i2 = base_vertex_index + mesh->indices[i + 2] + 1;
                    uint32_t t_i0 = mesh->vertices[mesh->indices[i+0]].color.a + 1;
                    uint32_t t_i1 = mesh->vertices[mesh->indices[i+1]].color.a + 1;
                    uint32_t t_i2 = mesh->vertices[mesh->indices[i+2]].color.a + 1;
                    uint32_t n_i0 = *((uint32_t*)&mesh->vertices[mesh->indices[i+0]].normal.x) + 1;
                    uint32_t n_i1 = *((uint32_t*)&mesh->vertices[mesh->indices[i+1]].normal.x) + 1;
                    uint32_t n_i2 = *((uint32_t*)&mesh->vertices[mesh->indices[i+2]].normal.x) + 1;
                    fprintf(fout, "f %u/%u/%u %u/%u/%u %u/%u/%u\n", v_i0, t_i0, n_i0, v_i1, t_i1, n_i1, v_i2, t_i2, n_i2);
                }
                base_vertex_index += mesh->vertex_count;
            }
        }

        if (fout) {
            fclose(fout);
        }
    }
    return !error;
}

void print_help()
{
    printf(
        "vox2obj v2.0 by Justin Paver - source code available here: http://github.com/jpaver/opengametools \n"
        "\n"
        "This tool can extract frames out of a given MagicaVoxel.vox and save them either as separate .obj files,\n"
        " or as a single .obj file with separate internal objects for each frame.\n"
        "\n"
        " usage: vox2obj [optional args] <input_file.vox>\n"
        "\n"
        " [optional args] can be one or multiple of:\n"
        " --mesh_algorithm <algo> : (default: polygon) sets the meshing mode where <algo> is one of: simple, greedy or polygon\n"
        " --all_frames_in_one     : (default: disabled) specifies that all frames should be written into a single output file\n"
        " --output_name <name>    : (default: disabled): name of output files\n"
        " --scale <value>         : (default: 1.0): scaling factor to apply to output voxels\n"
        " --frames <first> <last> : which frame range to extract. If not specified, will extract all keyframes within the .vox file.\n"
        " --output_vox            : (default: disabled): if specified will output .vox files for each frame instead of .obj"
        "\n"
        "example:\n"
        "  vox2obj --mesh_algorithm polygon --output_name test --frames 0 119 --scale scene.vox\n"
        "\n"
        "The above example uses polygon tessellation. will generate test.mtl/test.tga and the test.obj will contain 120 objects,\n"
        "with each object representing a mesh of the entire frame within scene.vox\n"
    );
}

#include <iostream>

int main(int argc, char** argv) {
    // print help if no args are provided
    if (argc == 1) {
        print_help();
        // wait for keyboard input
        printf("\n\nPress enter to continue!");
        std::cin.get();

        return 0;
    }

    // default parameter values
    const char* input_file        = nullptr;
    const char* mesh_algorithm    = "polygon";
    const char* output_name       = nullptr;
    bool        all_frames_in_one = false;
    bool        output_as_vox     = false;
    uint32_t    frame_min         = UINT32_MAX; // auto!
    uint32_t    frame_max         = UINT32_MAX; // auto!
    float       scale             = 1.0f;

    // parse arguments and override default parameter values
    for (int i = 1; i < argc; ) {
        if (strcmp(argv[i], "--mesh_algorithm")==0) {
            mesh_algorithm = argv[i+1];
            i += 2;
        }
        else if (strcmp(argv[i], "--all_frames_in_one") == 0) {
            all_frames_in_one = true;
            i++;
        }
        else if (strcmp(argv[i], "--frames") == 0) {
            frame_min = atoi(argv[i+1]);
            frame_max = atoi(argv[i+2]);
            i += 3;
        }
        else if (strcmp(argv[i], "--output_name") == 0) {
            output_name = argv[i+1];
            i += 2;
        }
        else if (strcmp(argv[i], "--scale") == 0) {
            scale = (float)atof(argv[i+1]);
            i += 2;
        }
        else if (strcmp(argv[i], "--output_vox") == 0) {
            output_as_vox = true;
            i++;
        }
        else if (strncmp(argv[i], "--", 2) == 0) {
            printf("ERROR: unrecognized parameter '%s'\n", argv[i]);
            return 1;
        }
        else {
            input_file = argv[i];
            break;
        }
    }

    // validate that an input file was specified.
    if (!input_file) {
        printf("ERROR: expected last argument to be input file\n");
        print_help();
        return 1;
    }

    uint32_t read_scene_flags = k_read_scene_flags_keyframes | k_read_scene_flags_groups | k_read_scene_flags_keep_empty_models_instances | k_read_scene_flags_keep_duplicate_models;

    const ogt_vox_scene* scene = load_vox_scene(input_file, read_scene_flags);
    if (!scene) {
        printf("ERROR: could not load input file: %s", input_file);
        return 3;
    }

    // either use the output prefix specified, or generate one from the input filename.
    std::string output_prefix;
    if (!output_name) {
        output_prefix = std::string(input_file);
        output_prefix = output_prefix.substr(0, output_prefix.find_first_of('.'));
    }
    else {
        output_prefix = std::string(output_name);
    }

    bool ret = false;
    if (output_as_vox) {
        ret = export_scene_anim_as_vox(scene, output_prefix, frame_min, frame_max);
    }
    else {
        bool output_file_per_frame = !all_frames_in_one;
        // validate specified mesh_algorithm is one of "polygon", "greedy" or "simple"
        if (strcmp(mesh_algorithm, "polygon") != 0 &&
            strcmp(mesh_algorithm, "greedy") != 0 &&
            strcmp(mesh_algorithm, "simple") != 0)
        {
            printf("ERROR: invalid mesh algorithm specified: %s", mesh_algorithm);
            print_help();
            return 2;
        }
        ret = export_scene_anim_as_obj(scene, output_prefix, output_file_per_frame, scale, frame_min, frame_max, mesh_algorithm);
    }
    ogt_vox_destroy_scene(scene);

    return ret ? 4 : 0;
}

/* -------------------------------------------------------------------------------------------------------------------------------------------------

    MIT License

    Copyright (c) 2022 Justin Paver

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.

------------------------------------------------------------------------------------------------------------------------------------------------- */
