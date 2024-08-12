//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#version 430 core

// #includes doesn't work GLSL 
// Insert at compile time "ShaderLayout.h" manually
#include "ShaderLayout.h"

layout (location = ATTRIB_LOCATION_VERT) in vec4 vert;    
layout (location = ATTRIB_LOCATION_NORM) in vec3 norms;
layout (location = ATTRIB_LOCATION_TEXT) in vec2 uv;

layout (location = ATTRIB_LOCATION_WEIGHT) in vec4  weight;
layout (location = ATTRIB_LOCATION_JOINT) in ivec4 joint;

// Uniforms

layout (std430, binding = 0) buffer boneWorld_label
{
	mat4 boneWorld[];
};

	uniform mat4 view_matrix;
	uniform mat4 proj_matrix;
	uniform mat4 pivotWorld;

// Varying
	out VS_OUT
	{
		vec2 textCoordinate;
	} vs_out;


void main(void)
{
    vs_out.textCoordinate = uv;

	// Remember: We use ROW major, but OpenGL GLSL multiplies in reverse order!

	 mat4 skin_matrix = weight.x * boneWorld[joint.x]   +
					    weight.y * boneWorld[joint.y]   +
					    weight.z * boneWorld[joint.z]   +
					    weight.w * boneWorld[joint.w]  ;
	
    gl_Position = proj_matrix * view_matrix * pivotWorld * skin_matrix * vert;    
}

// --- End of File ---
