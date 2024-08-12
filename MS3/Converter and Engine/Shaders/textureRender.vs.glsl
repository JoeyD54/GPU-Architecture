//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

// TEXTURE RENDER - Vertex Shader
#version 430 core

// #includes doesn't work GLSL 
// Insert at compile time "ShaderLayout.h" manually
#include "ShaderLayout.h"

// Uniforms
uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

// Attributes
layout (location = ATTRIB_LOCATION_VERT) in vec4 position;
layout (location = ATTRIB_LOCATION_TEXT) in vec2 tc;

// Varying
out VS_OUT
{
    vec2 textCoordinate;
} vs_out;

void main(void)
{
    vs_out.textCoordinate = tc;
    gl_Position = proj_matrix * view_matrix * world_matrix * position;
}

// --- End of File ---

