/* -------------------------------------------------------------------------------------------------------------------------------------------------

    MIT License

    Copyright (c) 2021 Justin Paver

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.

------------------------------------------------------------------------------------------------------------------------------------------------- */
#include <stdio.h>
#include <string.h>
#if !_MSC_VER
#define sprintf_s   snprintf
#endif

#define OGT_VOX_IMPLEMENTATION
#include "../src/ogt_vox.h"


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


// a helper function to save a magica voxel scene to disk.
void save_vox_scene(const char* pcFilename, const ogt_vox_scene* scene)
{
    // save the scene back out.
    uint32_t buffersize = 0;
    uint8_t* buffer = ogt_vox_write_scene(scene, &buffersize);
    if (!buffer)
        return;

    // open the file for write
    FILE * fp = open_file(pcFilename, "wb");
    if (!fp) {
        fprintf(stderr, "ERROR: could not open file '%s' for write - aborting!\n", pcFilename);
        ogt_vox_free(buffer);
        return;
    }

    fwrite(buffer, buffersize, 1, fp);
    fclose(fp);
    ogt_vox_free(buffer);
}

void print_help() {
    printf(
        "voxseparate v1.0 by Justin Paver - source code available here: http://github.com/jpaver/opengametools \n"
        "\n"
        "This tool extracts models out of MagicaVoxel .vox files and saves them as individual models within separate .vox files.\n"
        "\n"
        " usage: voxseparate <input_file.vox> <input_file2.vox> ...\n"
        "\n"
        "  It is recommended that you provide names for each instance of your model within the .vox files so\n"
        "  that output filenames make sense, otherwise output filenames will be auto-generated\n"
    );
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
              "-%s.vox",
              model_name);
}

int32_t main(int32_t argc, char** argv) {
    // validate we have at least one input file provided on command-line.
    if (argc <= 1) {
        printf("ERROR: no input files were provided on the command-line\n");
        print_help();
        return 3;
    }

    ogt_vox_layer default_layer = {};
    default_layer.hidden = false;
    default_layer.name = "default";

    ogt_vox_group default_group = {};
    default_group.hidden = false;
    default_group.layer_index = 0;
    default_group.parent_group_index = k_invalid_group_index;
    default_group.transform = ogt_vox_transform_get_identity();

    // process all input files specified
    for (int32_t input_index = 1; input_index < argc; input_index++) {
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
            char tmp_model_name[64] = {};
            if (!model_name) {
                // otherwise, autogenerate a name for the model based on its index in the vox file.
                model_name = tmp_model_name;
                sprintf_s(tmp_model_name, sizeof(tmp_model_name), "model%i", model_index);
            }

            // construct the scene with a single instance referencing this model
            ogt_vox_instance instance = {};
            instance.group_index = 0;   // default_group
            instance.hidden      = false;
            instance.layer_index = 0;   // default_layer
            instance.model_index = 0;
            instance.name        = NULL;
            instance.transform   = ogt_vox_transform_get_identity();

            ogt_vox_scene output_scene = {};
            output_scene.groups        = &default_group;
            output_scene.num_groups    = 1;
            output_scene.instances     = &instance;
            output_scene.num_instances = 1;
            output_scene.instances     = &instance;
            output_scene.num_layers    = 1;
            output_scene.layers        = &default_layer;
            output_scene.num_models    = 1;
            output_scene.models        = &model;
            output_scene.palette       = scene->palette;
            output_scene.materials     = scene->materials;

            // construct the output filename for this model.
            char output_filename[1024];
            make_output_filename(input_filename, model_name, output_filename, sizeof(output_filename));

            save_vox_scene(output_filename, &output_scene);
        }

        ogt_vox_destroy_scene(scene);
    }

    return 0;
}
