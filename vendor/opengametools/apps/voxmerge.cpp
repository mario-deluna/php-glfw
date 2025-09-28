/*
    voxmerge - MIT license - Justin Paver, Feb 2022

    An application that can take 1 or multiple input Magicavoxel .vox files, merge them into a single .vox file and write it out.
    This is part of the open game tools project: https://github.com/jpaver/opengametools.

    Please see the MIT license information at the end of this file, and please consider
    sharing any improvements you make.
*/

#define OGT_VOX_IMPLEMENTATION
#include "../src/ogt_vox.h"

#if defined(_MSC_VER)
    #include <io.h>
#endif
#include <stdio.h>

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
bool save_vox_scene(const char* pcFilename, const ogt_vox_scene* scene)
{
    // save the scene back out.
    uint32_t buffersize = 0;
    uint8_t* buffer = ogt_vox_write_scene(scene, &buffersize);
    if (!buffer) {
        return false;
    }

    // open the file for write
    FILE * fp = open_file(pcFilename, "wb");
    if (!fp) {
        ogt_vox_free(buffer);
        return false;
    }

    fwrite(buffer, buffersize, 1, fp);
    fclose(fp);
    ogt_vox_free(buffer);
    return true;
}

void print_help()
{
    printf("voxmerge v0.9\n");
    printf("usage:\n");
    printf("  voxmerge <outputfilename.vox> <input0.vox> <input1.vox> ...\n");
}

// demonstrates merging multiple scenes together
bool merge_scenes(const char* output_filename, const char** input_filenames, uint32_t input_count)
{
    bool any_error = false;

    if (input_count == 0) {
        return false;
    }

    // allocate and load all input scenes
    const ogt_vox_scene** scenes = new const ogt_vox_scene*[input_count];
    for (uint32_t i = 0; i < input_count; i++) {
        scenes[i] = load_vox_scene(input_filenames[i]);
        if (!scenes[i]) {
            printf("ERROR: failed to load scene from filename %s\n", input_filenames[i]);
            any_error = true;
        }
    }

    // if we loaded all input scenes, merge them and try save them.
    if (!any_error) {
        ogt_vox_scene* merged_scene = ogt_vox_merge_scenes(scenes, input_count, NULL, 0);
        if (merged_scene) {
            if (!save_vox_scene(output_filename, merged_scene)) {
                printf("ERROR: failed to save merged scene to filename %s\n", output_filename);
                any_error = true;
            }
            ogt_vox_destroy_scene(merged_scene);
        }
    }

    // destroy our source scenes
    for (uint32_t i = 0; i < input_count; i++) {
        if (scenes[i]) {
            ogt_vox_destroy_scene(scenes[i]);
        }
    }
    delete[] scenes;

    return !any_error;
}

int main(int argc, const char** argv)
{
    if (argc <= 2) {
        printf("ERROR: not enough arguments provided\n");
        print_help();
    }
    // argv[0] = voxmerge.exe
    // argv[1] = output_filename
    // argv[2] = input file 0
    // argv[3] = input file 1
    if (merge_scenes(argv[1], &argv[2], argc-2)) {
        return 0;
    }

    // return an error code
    return 99;
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
