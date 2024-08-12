//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

// TEXTURE RENDER - Fragment Shader

#version 430 core

// Uniform
uniform sampler2D tex_object;

// Varying
in VS_OUT
{
    vec2 textCoordinate;
} fs_in;

out vec4 color;

void main(void)
{
    color = texture(tex_object, fs_in.textCoordinate );
}

// --- End of File ---

