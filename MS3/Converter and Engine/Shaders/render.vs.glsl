//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#version 430 core

// #includes doesn't work GLSL 
// Insert at compile time "ShaderLayout.h" manually
#include "ShaderLayout.h"

// varying
in vec4 position;

out VS_OUT
{ 
    vec4 color;
} vs_out;

// uniforms
uniform mat4 world_matrix;
uniform mat4 view_matrix;
uniform mat4 proj_matrix;

void main(void)
{              
    gl_Position = proj_matrix * view_matrix * world_matrix * position;      
    vs_out.color = position * 2.0 + vec4(0.5, 0.5, 0.5, 0.0);
}

// --- End of File ---

