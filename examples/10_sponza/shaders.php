<?php
/**
 * Shaders for the Sponza example.
 * 
 * ----------------------------------------------------------------------------
 */
$shaders = []; 

/**
 * Basic geometry shader
 * 
 * ----------------------------------------------------------------------------
 */
$shaders['geometry'] = ExampleHelper::compileShader(<<< 'GLSL'
#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_texcords;
layout (location = 3) in vec3 a_tangent;
layout (location = 4) in vec3 a_bitangent;

out vec2 v_texcords;
out vec3 v_normal;
out mat3 v_tbn;
out vec3 v_position;
out vec4 v_lightspace_position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 light_space;

void main()
{
    vec4 world_pos = model * vec4(a_position, 1.0);
    v_lightspace_position = light_space * world_pos;
    v_position = world_pos.xyz;

    // we need to transform the directional vectors to world space
    vec3 n = normalize(mat3(model) * a_normal);
    vec3 t = normalize(mat3(model) * a_tangent);
    vec3 b = normalize(mat3(model) * a_bitangent);
    
    v_tbn = mat3(t, b, n);
    v_normal = n;

    // flip the uvs
    v_texcords = vec2(a_texcords.x, a_texcords.y);

    // final pos
    gl_Position = projection * view * world_pos;
}
GLSL,
<<< 'GLSL'
#version 330 core
out vec4 fragment_color;

in vec2 v_texcords;
in vec3 v_normal;
in mat3 v_tbn;
in vec3 v_position;
in vec4 v_lightspace_position;

uniform sampler2D texture_diffuse;
uniform sampler2D texture_normal;   

// light
uniform vec3 light_dir;
uniform vec3 light_color;

// shadows
uniform sampler2D shadowmap;
uniform mat4 light_space;
uniform float minimum_shadow_bias = 0.005f;

uniform float ambient = 0.45;

// some settings for debugging 
uniform float use_normal_map = 1.0;

float shadow_coef(vec2 uv)
{
    return texture(shadowmap, uv).r;
} 

float fragment_in_shadow(vec3 normal)
{
    vec3 proj_coords = v_lightspace_position.xyz / v_lightspace_position.w;
    proj_coords = proj_coords * 0.5 + 0.5;

    float shadow_depth = shadow_coef(proj_coords.xy); 
    float current_depth = proj_coords.z;

    float bias = max(minimum_shadow_bias * (1.0 - dot(normal, light_dir)), minimum_shadow_bias);

    // PCF
    float shadow = 0.0;
    vec2 texel_size = 1.0 / textureSize(shadowmap, 0);
    for(int x = -1; x <= 1; ++x) {
        for(int y = -1; y <= 1; ++y) {
            float pcf_depth = texture(shadowmap, proj_coords.xy + vec2(x, y) * texel_size).r; 
            shadow += current_depth - bias > pcf_depth  ? 1.0 : 0.0;        
        }    
    }

    shadow /= 9.0;
    
    if(proj_coords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}

void main()
{
    vec4 diffusetex = texture(texture_diffuse, v_texcords);

    // discard alpha tested fragments
    if (diffusetex.a < 0.5) {
        discard;
    }

    // normals
    vec3 normal_rgb = normalize(texture(texture_normal, v_texcords).rgb * 2.0 - 1.0); 
    vec3 normal = normalize(v_tbn * normal_rgb);

    // determine the final normal
    vec3 final_normal = mix(v_normal, normal, use_normal_map);

    // simple lighting
    float diffuse = max(dot(final_normal, light_dir), 0.0);

    // calculate shadow
    float shadow = fragment_in_shadow(final_normal);    
         
    vec3 color = (ambient + (1.0 - shadow) * (diffuse)) * light_color * diffusetex.rgb;
    
    fragment_color = vec4(color, 1.0f);
    // fragment_color = vec4(final_normal, 1.0);
} 
GLSL);


/**
 * Shadow map shader
 * just projects the vertices to the light space, no fragments are generated
 * ----------------------------------------------------------------------------
 */
$shaders['shadowmap'] = ExampleHelper::compileShader(<<< 'GLSL'
#version 330 core

layout (location = 0) in vec3 a_position;

uniform mat4 model;
uniform mat4 light_space;

void main()
{
    gl_Position = light_space * model * vec4(a_position, 1.0);
}
GLSL,
<<< 'GLSL'
#version 330 core

void main()
{
}
GLSL);


/**
 * Just draw a texture quad to the screen
 * ----------------------------------------------------------------------------
 */
$shaders['quad'] = ExampleHelper::compileShader(<<< 'GLSL'
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;
out vec2 v_uv;
void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    v_uv = uv;
}
GLSL,
<<< 'GLSL'
#version 330 core
out vec4 fragment_color;
in vec2 v_uv;
uniform sampler2D u_texture;
void main()
{
    fragment_color = texture(u_texture, v_uv);
} 
GLSL);

/**
 * Just draw depth map to the screen
 * ----------------------------------------------------------------------------
 */
$shaders['depth'] = ExampleHelper::compileShader(<<< 'GLSL'
#version 330 core
layout (location = 0) in vec2 position;
layout (location = 1) in vec2 uv;
out vec2 v_uv;
void main()
{
    gl_Position = vec4(position, 0.0, 1.0);
    v_uv = uv;
}
GLSL,
<<< 'GLSL'
#version 330 core
out vec4 fragment_color;
in vec2 v_uv;
uniform sampler2D u_texture;


void main()
{
    float depth = texture(u_texture, v_uv).r;
    fragment_color = vec4(vec3(depth), 1.0);
}
GLSL);

// return the shader array
return $shaders;