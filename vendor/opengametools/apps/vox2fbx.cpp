/* -------------------------------------------------------------------------------------------------------------------------------------------------

    MIT License

    Copyright (c) 2020 Justin Paver

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.

------------------------------------------------------------------------------------------------------------------------------------------------- */
#include <string.h>
#if !_MSC_VER
#define sprintf_s   snprintf
#endif

#define OGT_VOX_IMPLEMENTATION
#include "../src/ogt_vox.h"
#define OGT_VOXEL_MESHIFY_IMPLEMENTATION
#include "../src/ogt_voxel_meshify.h"

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

void print_help() {
    printf(
        "vox2fbx v1.0 by Justin Paver - source code available here: http://github.com/jpaver/opengametools \n"
        "\n"
        "This tool extracts models out of MagicaVoxel .vox files and saves them as meshes within individual ascii .fbx files.\n"
        "\n"
        " usage: vox2fbx [optional args] <input_file.vox> <input_file2.vox> ... \n"
        "\n"
        " [optional args] can be one or multiple of:\n"
        " --mesh_algorithm <algo> : (default: polygon) sets the meshing mode where <algo> is one of: simple, greedy or polygon\n"
        " --named-models-only     : (default: disabled) will only generate an fbx for models in the vox file that have named instances\n"
        " --y-as-up               : (default: disabled) rotate model on export so that y is up"
        "\n"
        "examples:\n"
        "  vox2fbx --mesh_algorithm greedy --named-models-only test_scene.vox\n"
        "  vox2fbx --mesh_algorithm simple --y-as-up test_scene1.vox test_scene2.vox test_scene3.vox\n"
        "\n"
        "In windows, you can drag and drop a selection of files onto the executable.\n"
        ""
        "NOTES:\n"
        "  This tool generates tessellated meshes based on which mesh_algorithm is selected. The current algorithms\n"
        "  tessellate differently, with simple algorithm providing the most dense mesh at 2 triangles per visible voxel\n"
        "  face, polygon algorithm is mostly water tight (there is one edge case), and greedy algorithm is usually lowest\n"
        "  in polygon count, but is very far from watertight.\n"
        "  All 3 algorithms currently represent color by using the vertex color channel for the mesh in the fbx file.\n"
        "\n"
        "  At time of writing, both Microsoft Windows 10 3d Viewer and Adobe FBX Review tools do load these models,\n"
        "  however neither of them is capable of viewing vertex colors on the mesh for some reason so they show up\n"
        "  as grey. The one tool that I was able to load them on (sketchfab.com) does have this capability, and I \n"
        "  suspect other tools (such as Unity3D or UE4 game engine importers for FBX) do as well.\n"
        "\n"
        "  It is recommended that you provide names for each instance of your model within the .vox files so\n"
        "  that output filenames make sense.\n"
    );
}

bool write_mesh_to_fbx(const char* output_filename, const ogt_mesh* mesh, const char* mesh_name)
{
    FILE* fout = open_file(output_filename, "wb");
    if (!fout) {
        return false;
    }

    fprintf(fout,
        "; FBX 6.1.0 project file\n"
        "; ----------------------------------------------------\n"
        "\n"
        "FBXHeaderExtension:  {\n"
        "\tFBXHeaderVersion: 1003\n"
        "\tFBXVersion: 6100\n"
        "\tCreator: \"http://github.com/jpaver/opengametools vox2fbx\"\n"
        "}\n"
        "\n"
        "; Object definitions\n"
        "; ------------------------------------------------------------------\n"
        "\n"
        "Definitions:  {\n"
        "\tVersion: 100\n"
        "\tCount: 1\n"
        "\tObjectType: \"Model\" {\n"
        "\t\tCount: 1\n"
        "\t}\n"
        "}\n"
        "\n"
        "; Object properties\n"
        "; ------------------------------------------------------------------\n"
        "\n"
        "Objects:  {\n"
    );

    // start the model.
    fprintf(fout,
        "\tModel: \"%s\", \"Mesh\" {\n"
        "\t\tVersion: 232\n",
        mesh_name);

    // write the vertices
    {
        fprintf(fout,
            "\t\tVertices:");
        for (uint32_t i = 0; i < mesh->vertex_count; i++) {
            fprintf(fout, "%s%f,%f,%f", ((i > 0) ? "," : ""), mesh->vertices[i].pos.x, mesh->vertices[i].pos.y, mesh->vertices[i].pos.z);
        }
        fprintf(fout, "\n");
    }

    // write the vertex indices
    {
        fprintf(fout,
            "\t\tPolygonVertexIndex: ");
        for (uint32_t i = 0; i < mesh->index_count; i += 3) {
            uint32_t i0 = mesh->indices[i + 2];
            uint32_t i1 = mesh->indices[i + 1];
            uint32_t i2 = mesh->indices[i + 0];
            fprintf(fout, "%s%u,%u,-%u", ((i > 0) ? "," : ""), i0, i1, (i2 + 1));
        }
        fprintf(fout, "\n");
    }
    fprintf(fout,
        "\t\tGeometryVersion: 124\n"
    );

    // write the vertex normals layer element
    {
        fprintf(fout,
            "\t\tLayerElementNormal: 0 {\n"
            "\t\t\tVersion: 101\n"
            "\t\t\tName: \"\"\n"
            "\t\t\tMappingInformationType: \"ByVertice\"\n"
            "\t\t\tReferenceInformationType: \"Direct\"\n"
        );
        // write colors array
        fprintf(fout,
            "\t\t\tNormals: "
        );
        for (uint32_t i = 0; i < mesh->vertex_count; i++) {
            float x = mesh->vertices[i].normal.x;
            float y = mesh->vertices[i].normal.y;
            float z = mesh->vertices[i].normal.z;
            // palette color
            fprintf(fout, "%s%f,%f,%f", ((i > 0) ? "," : ""), x, y, z);
        }
        fprintf(fout, "\n");
        fprintf(fout,
            "\t\t}\n");
    }

    // write the vertex colors layer element
    {
        fprintf(fout,
            "\t\tLayerElementColor: 0 {\n"
            "\t\t\tVersion: 101\n"
            "\t\t\tName: \"colorSet1\"\n"
            "\t\t\tMappingInformationType: \"ByPolygonVertex\"\n"
            "\t\t\tReferenceInformationType: \"Direct\"\n"
        );
        // write colors array
        fprintf(fout,
            "\t\t\tColors: "
        );
        for (uint32_t i = 0; i < mesh->index_count; i++) {
            uint32_t index = mesh->indices[i];
            float r = (mesh->vertices[index].color.r / 255.0f);
            float g = (mesh->vertices[index].color.g / 255.0f);
            float b = (mesh->vertices[index].color.b / 255.0f);
            float a = 1.0f;
            // palette color
            fprintf(fout, "%s%f,%f,%f,%f", ((i > 0) ? "," : ""), r, g, b, a);
        }
        fprintf(fout, "\n");

        fprintf(fout,
            "\t\t}\n");
    }
    // write the layers
    fprintf(fout,
        "\t\tLayer: 0 {\n"
        "\t\t\tVersion: 100\n"
        "\t\t\tLayerElement: {\n"
        "\t\t\t\tType: \"LayerElementNormal\"\n"
        "\t\t\t\tTypedIndex: 0\n"
        "\t\t\t}\n"
        "\t\t\tLayerElement: {\n"
        "\t\t\t\tType: \"LayerElementColor\"\n"
        "\t\t\t\tTypedIndex: 0\n"
        "\t\t\t}\n"
        "\t\t}\n"
    );

    // write the tail of the model
    fprintf(fout,
        "\t}\n"
        "}\n"
        "\n");

    // write the connections
    fprintf(fout,
        "; Object connections\n"
        "; ------------------------------------------------------------------\n"
        "Connections:  {\n"
        "\tConnect: \"OO\", \"%s\", \"Model::Scene\"\n"
        "}\n",
        mesh_name);

    fclose(fout);
    return true;
}

static void make_output_filename(const char* input_filename, const char* model_name, char* output_filename, size_t size) {
    // Copy input_filename
    sprintf_s(output_filename, size, "%s", input_filename);
    output_filename[size - 1] = '\0'; // ensure null-termination

    // Strip the extension
    char* ext = strchr(output_filename, '.');
    if (ext) {
        *ext = '\0';
    }

    // Append "-", model_name, ".vox" using snprintf
    sprintf_s(output_filename + strlen(output_filename),
              size - strlen(output_filename),
              "-%s.fbx",
              model_name);
}

int32_t main(int32_t argc, char** argv) {
    // just print help if no args are provided
    if (argc == 1) {
        print_help();
        return 0;
    }

    // default parameter values
    const char* mesh_algorithm = "polygon";
    bool named_models_only     = false;
    bool y_as_up               = false;

    // parse arguments and override default parameter values.
    int32_t start_input_index = INT32_MAX;
    for (int32_t i = 1; i < argc; ) {
        if (strcmp(argv[i], "--mesh_algorithm") == 0) {
            mesh_algorithm = argv[i+1];
            i += 2;
        }
        else if (strcmp(argv[i], "--named-models-only") == 0) {
            named_models_only = true;
            i++;
        }
        else if (strcmp(argv[i], "--y-as-up") == 0) {
            y_as_up = true;
            i++;
        }
        else if (strncmp(argv[i], "--", 2) == 0) {
            printf("ERROR: unrecognized parameter '%s'", argv[i]);
            return 1;
        }
        else {
            // first argument that doesn't start with '--' is an input file.
            start_input_index = i;
            break;
        }
    }

    // validate specified mesh_algorithm is one of "polygon", "greedy" or "simple"
    if (strcmp(mesh_algorithm, "polygon") != 0 &&
        strcmp(mesh_algorithm, "greedy") != 0 &&
        strcmp(mesh_algorithm, "simple") != 0)
    {
        printf("ERROR: invalid mesh algorithm specified: %s", mesh_algorithm);
        print_help();
        return 2;
    }

    // validate we have at least one input file provided on command-line.
    if (start_input_index >= argc) {
        printf("ERROR: no input files were provided on the command-line\n");
        print_help();
        return 3;
    }

    // process all input files specified
    for (int32_t input_index = start_input_index; input_index < argc; input_index++) {
        const char* input_filename = argv[input_index];
        if (!strstr(input_filename, ".vox")) {
            printf("ERROR: input '%s' specified does not have .vox extension.\n", input_filename);
            return 4;
        }
        printf("processing input %s\n", input_filename);

        // load scene
        const ogt_vox_scene* scene = load_vox_scene(input_filename);
        if (!scene) {
            printf("ERROR: could not load scene with name '%s'\n", input_filename);
            return 5;
        }

        // determine which models we're going to write to the FBX file.
        for (uint32_t model_index = 0; model_index < scene->num_models; model_index++) {
            const ogt_vox_model* model = scene->models[model_index];

            // find the model name by finding a named instance that references it.
            const char* model_name = NULL;
            for (uint32_t instance_index = 0; instance_index < scene->num_instances; instance_index++) {
                if (scene->instances[instance_index].name && scene->instances[instance_index].model_index == model_index) {
                    if (!model_name) {
                        model_name = scene->instances[instance_index].name;
                    }
                    else {
                        // warn if there are multiple instances of the same model with different names causing ambiguity (a .vox author could do this without knowing).
                        printf("WARNING: model %i has been given name %s but there is also an instance of this model with name %s.", model_index, model_name, scene->instances[instance_index].name);
                    }
                }
            }

            // if there is no model name, we either skip the export of this model (if --named-models-only was specified ) or give it an autogenerated name
            char tmp_model_name[64];
            if (!model_name) {
                if (named_models_only) {
                    printf("   skipped model %i because it does not have a name\n", model_index);
                    continue;   // skip this model as it has no name and caller only wants to extract named models
                }

                // otherwise, autogenerate a name for the model based on its index in the vox file.
                model_name = tmp_model_name;
                sprintf_s(tmp_model_name, sizeof(tmp_model_name), "model%i", model_index);
            }

            // construct the output filename for this model.
            char output_filename[1024];
            make_output_filename(input_filename, model_name, output_filename, sizeof(output_filename));

            // generate a mesh for this model using the mesh_algorithm specified
            ogt_voxel_meshify_context ctx;
            memset(&ctx, 0, sizeof(ctx));
            ogt_mesh* mesh =
                (strcmp(mesh_algorithm, "polygon") == 0) ? ogt_mesh_from_paletted_voxels_polygon(&ctx, model->voxel_data, model->size_x, model->size_y, model->size_z, (const ogt_mesh_rgba*)& scene->palette.color[0]) :
                (strcmp(mesh_algorithm, "greedy") == 0) ? ogt_mesh_from_paletted_voxels_greedy(&ctx, model->voxel_data, model->size_x, model->size_y, model->size_z, (const ogt_mesh_rgba*)& scene->palette.color[0]) :
                (strcmp(mesh_algorithm, "simple") == 0) ? ogt_mesh_from_paletted_voxels_simple(&ctx, model->voxel_data, model->size_x, model->size_y, model->size_z, (const ogt_mesh_rgba*)& scene->palette.color[0]) :
                NULL;
            if (!mesh) {
                printf("ERROR: could not create mesh using mesh_algorithm '%s' aborting!\n", mesh_algorithm);
                return 6;
            }

            // It's possible for algorithms above to emit some duplicate verts on shared faces. Remove those now.
            ogt_mesh_remove_duplicate_vertices(&ctx, mesh);

            // offset mesh vertices so that the centre of the mesh (centre of the voxel grid) is at (0,0,0)
            {
                float origin_x = (float)(model->size_x >> 1);
                float origin_y = (float)(model->size_y >> 1);
                float origin_z = (float)(model->size_z >> 1);
                for (uint32_t i = 0; i < mesh->vertex_count; i++) {
                    mesh->vertices[i].pos.x -= origin_x;
                    mesh->vertices[i].pos.y -= origin_y;
                    mesh->vertices[i].pos.z -= origin_z;
                }
            }

            // if --y-as-up was specified, apply rotation to the positions and normals for all models
            if (y_as_up)
            {
                for (uint32_t i = 0; i < mesh->vertex_count; i++) {
                    ogt_mesh_vec3 old_pos = mesh->vertices[i].pos;
                    mesh->vertices[i].pos.x = -old_pos.x;
                    mesh->vertices[i].pos.y = old_pos.z;
                    mesh->vertices[i].pos.z = old_pos.y;
                    ogt_mesh_vec3 old_normal = mesh->vertices[i].normal;
                    mesh->vertices[i].normal.x = -old_normal.x;
                    mesh->vertices[i].normal.y = old_normal.z;
                    mesh->vertices[i].normal.z = old_normal.y;
                }
            }

            if (!write_mesh_to_fbx(output_filename, mesh, model_name)) {
                printf("ERROR: could not open file '%s' for write - aborting!", output_filename);
                return 6;
            }
            printf("   wrote model %i to output file %s (mesh has %u triangles, %u vertices)\n", model_index, output_filename, mesh->index_count / 3, mesh->vertex_count);

            ogt_mesh_destroy(&ctx, mesh);
        }

        ogt_vox_destroy_scene(scene);
    }

    return 0;
}
