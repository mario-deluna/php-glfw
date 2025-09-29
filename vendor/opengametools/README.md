# open game tools

Open game tools is a set of unencumbered, free, lightweight, easy-to-integrate tools for use in game development. 

So far it contains these libraries:
- [ogt_vox.h](https://github.com/jpaver/opengametools/blob/master/src/ogt_vox.h) a MagicaVoxel scene reader, writer and merger
- [ogt_voxel_meshify.h](https://github.com/jpaver/opengametools/blob/master/src/ogt_voxel_meshify.h) a few routines to convert voxel grid data to triangle mesh

... and these applications:
- [vox2fbx.cpp](https://github.com/jpaver/opengametools/blob/master/apps/vox2fbx.cpp) an application to extract models from `.vox` and save them to ascii fbx
- [vox2obj.cpp](https://github.com/jpaver/opengametools/blob/master/apps/vox2obj.cpp) an application to extract full frames from `.vox' and save them to Wavefront OBJ files. This tool also supports writing all frames out to individual single-frame .vox files.
- [voxseparate.cpp](https://github.com/jpaver/opengametools/blob/master/apps/voxseparate.cpp) an application to extract models from `.vox` and save them to separate `.vox` files
- [voxmerge.cpp](https://github.com/jpaver/opengametools/blob/master/apps/voxmerge.cpp) an application to merge multiple `.vox` files into a single `.vox` file

Please consider contributing fixes, extensions, bug reports or feature requests to this project. If you have example scenes that fail to load or save correctly, or have additional issues, feel free to file an issue on github and I'd be happy to investigate and make fixes when I have the time.

See [CONTRIBUTING.md](https://github.com/jpaver/opengametools/blob/master/CONTRIBUTING.md) for more details.

## ogt_vox: MagicaVoxel scene reader, writer and merger

A C++ reader, writer and scene merger for [MagicaVoxel](https://ephtracy.github.io/)'s vox file format.

### Scene reading (.vox) 

With this library, reading a `.vox` file will result in a ogt_vox_scene structure which you use to:
- enumerate all or a subset of instance placements within a `.vox` file
- get the transforms for those instances as a matrix flattened relative to the scene file, or relative to their group hierarchy
- access the voxel model referenced by those placements ie. the 3d color grid
- access the palette colors and materials
- access layer, group and visible/hidden state for instances / groups
- access model-swap keyframes for instances
- access transform keyframes for instances / groups
- access the camera settings

I use this library to deep-reference models in `.vox` files and turn them into triangle meshes in my engine's importer/cooker. I also use it in an in-engine wizard to import all instance/scene data into your own engine scene format. This can allow your artists to use MagicaVoxel as a level editor, or simply a tool for managing a kit, palette of module-set to be used within levels or objects within your own editor. 

### Scene Writing (.vox)

The C++ writer for [MagicaVoxel](https://ephtracy.github.io/)'s vox file format takes a user-constructed `ogt_vox_scene` structure and serializes it to `.vox` file format. When saved out to disk, it'll be loadable in MagicaVoxel.

My own testing involved going through all of my on-disk vox files, and verified they load in MagicaVoxel 0.99.3-alpha. The files are usually smaller than the source `.vox` though because they will not preserve all the chunks within the original `.vox` file.

### Scene Merging (.vox)

You can load multiple `.vox` files simultaneously to obtain multiple `ogt_vox_scene` structures. You can then merge them into a single `ogt_vox_scene` and save it out.

If they have different palettes, the merger will do closest-color matches to try preserve the original colors in the output file.

If you find yourself needing to combine multiple files with very similar but non-identical palettes then this is probably the tool for you. If you need to combine multiple files with completely different palettes that have only a few entries used, then this may also be for you!

It should always work, but it may not give a good color fit if the voxel files you use most of their colors and have their own very different palettes. If you want to simply replace the merged file with a very specific palette, you can provide that to the merge function too.

In the future, I might add a more holistic algorithm that prioritizes allocation to the final palette of colors based on their distance from other colors.

### Usage

See [demo_vox.cpp](https://github.com/jpaver/opengametools/blob/master/demo/demo_vox.cpp) for a simple example.

1. Include `ogt_vox.h` directly from one of your C or CPP files:

   ```c++
        #define OGT_VOX_IMPLEMENTATION
        #include "ogt_vox.h"
   ```

2. Use your own file utilities to load a `.vox` file into a memory buffer. eg.

   ```c++
    FILE* fp = fopen("file.vox", "rb");
    uint32_t buffer_size = _filelength(_fileno(fp));
    uint8_t* buffer = new uint8_t[buffer_size];
    fread(buffer, buffer_size, 1, fp);
    fclose(fp);
   ```

3. Pass the buffer into ogt_vox_read_scene to get a scene object eg.

   ```c++
    const ogt_vox_scene* scene = ogt_vox_read_scene(buffer, buffer_size);
    // the buffer can be safely deleted once the scene is instantiated.
    delete[] buffer;
   ```

4. Now read all the information you need from the scene object and use it to import voxel data/instances.
   eg. Here, I just print some basic information:

   ```c++
    printf("# models: %u\n",  scene->num_models);
    printf("# instances: %u\n", scene->num_instances);
   ```

5. Shut down the scene to release the memory it allocated. eg.

   ```c++
   ogt_vox_destroy_scene(scene);
   ```

### Note

The reader, writer and merge functionaliy supports the most relevant chunks as described here:
- [MagicaVoxel-file-format-vox.txt](https://github.com/ephtracy/voxel-model/blob/master/MagicaVoxel-file-format-vox.txt)
- [MagicaVoxel-file-format-vox-extension.txt](https://github.com/ephtracy/voxel-model/blob/master/MagicaVoxel-file-format-vox-extension.txt)

`MATL`/`MATT` are not yet merged, but it is expected to come in a later change. CAVEAT: loading of `MATL` chunks are most accurate when written by recent Magicavoxel versions (0.99.6.2 and 0.99.6.3 at time of writing). Chunks written by earlier versions may not be decoded accurately.

rOBJ chunks are not supported in any capacity for now. If there is interest, do let us know in the Issues section.

## ogt_voxel_meshify: converts voxel grid data to triangle mesh data

This module contains 3 routines for converting paletted voxel grid data to triangle mesh data.

- **ogt_mesh_from_paletted_voxels_simple**: returns the most naieve mesh possible, which will be tessellated at voxel granularity.
![image](https://user-images.githubusercontent.com/8569715/114662155-13c6c100-9cad-11eb-9274-177ad85a82a4.png)

- **ogt_mesh_from_paletted_voxels_greedy**: uses a greedy box-expansion pass to replce rectangular regions of voxels of the same color with a larger polygon that covers the box. It will generally produce t-junctions which can make rasterization not water-tight based on your camera/project/distances.
![image](https://user-images.githubusercontent.com/8569715/114662173-1b866580-9cad-11eb-8671-4b0cb4d404f9.png)

- **ogt_mesh_from_paletted_voxels_polygon**: will polygonize and triangulate connected voxels that are of the same color. The boundary of the polygon will be tessellated only to the degree that is necessary to there are tessellations at color discontinuities. Generally produces slightly more triangles that greedy meshing but it is mostly water-tight, except for a very small number of cases.
![image](https://user-images.githubusercontent.com/8569715/114662191-20e3b000-9cad-11eb-8cd1-2e6be2a38512.png)


More documentation and a demo will be added soon.

## vox2fbx: Tool for extracting meshifying models from Magicavoxel .vox and saving them to .fbx

This is a command-line tool which will find all named voxel grid models in a vox file, turn them into a mesh using one of 3 algorithms (simple, greedy or polygon) each of which produce different density mesh with varying levels of water-tightness (ie. t-junctions), then save those meshes out to individual fbx files.

It can be used from command-line with these args:
 - `--mesh_algorithm <algo>` : (default: polygon) sets the meshing mode where <algo> is one of: simple, greedy or polygon
 - `--named-models-only`     : (default: disabled) will only generate an fbx for models in the vox file that have named instances
 - `--y-as-up`               : (default: disabled) rotate model on export so that y is up

It can also be used from windows explorer by dragging-and-drop your .vox files onto it, and it will produce an output fbx file for each grid model in each `.vox` file.

## vox2obj: Tool for baking entire scenes in a Magicavoxel .vox into a single mesh and saving them to .obj 
   
This is a command-line tool which will find all named voxel grid models in a vox file, turn them into a single mesh using one of 3 algorithms (simple, greedy or polygon) each of which produce different density mesh with varying levels of water-tightness (ie. t-junctions), then save out all frames or a specific set of animation frames out to a .obj file. Each animation frame can optionally be exported into the same .obj file as separate subobjects.

It can be used from command-line with these args:
 - `--mesh_algorithm <algo>` : (default: polygon) sets the meshing mode where <algo> is one of: simple, greedy or polygon
 - `--all_frames_in_one`     : (default: disabled) specifies that all frames should be written into a single output file
 - `--output_name <name>`    : (default: disabled): name of output files
 - `--scale <value>`         : (default: 1.0): scaling factor to apply to output voxels
 - `--frames <first> <last>` : which frame range to extract. If not specified, will extract all frames between min and max keyframes within the .vox file.

It can also be used from windows explorer by dragging-and-drop your .vox files onto it, and it will produce an output .obj file with the above defaults.
   
## voxseparate: Tool for extracting models from a multi-model Magicavoxel .vox and saving them to individual .vox files

Provide input `.vox` files on the command line, and output files will be written out to the same directory, with autogenerated names based on the names of instances of models within these input `.vox` files.

It can also be used from windows explorer by dragging-and-drop your `.vox` files onto it, and it will produce an output vox file for each model in each `.vox` file.

## voxmerge: Tool for merging multiple Magicavoxel .vox files into a single .vox file.

Provide an output filename, and one-or-more multiple input `.vox` files and the merged scene will be written out. The output file will do a basic best fit of palettes colors across all input `.vox` files and will emit only the used colors from all input vox files into the output file.

## Projects using open game tools

 - UE Voxel plugin [ https://wiki.voxelplugin.com/Main_Page ] ( code: https://github.com/Phyronnaz/VoxelPlugin )
 - Voxelmax [ https://voxelmax.com/ ] by http://www.twitter.com/ndreca_com
 - Avoyd [https://www.enkisoftware.com/] by Doug Binks
 - Vengi engine [ https://github.com/mgerhardy/vengi ] by Martin Gerhardy
 - I am also using it in my own game project. Will share details when I'm ready to decloak.

## Acknowledgements

Thanks to [@ephtracy](https://twitter.com/ephtracy). So much would not have been possible without your generosity in releasing the tool free to the public, releasing information about the file format and patiently answering my DMs on twitter.

Thanks to [@nothings](https://twitter.com/nothings) for sharing your single-headers as well as the philosophy behind them. The latter has been invaluable to my personal growth.

Thanks to [@ndreca_com](https://twitter.com/ndreca_com) for feedback on the ogt_vox library!

Thanks to all contributors so far!
