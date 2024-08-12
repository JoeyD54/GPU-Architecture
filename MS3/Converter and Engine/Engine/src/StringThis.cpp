//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "StringThis.h"


namespace Azul
{
	StringThis::StringThis(Texture::Name status)
	{
		switch(status)
		{
		case Texture::Name::HOT_PINK:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::HOT_PINK));
			break;

		case Texture::Name::INVADERS:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::INVADERS));
			break;

		case Texture::Name::STONES:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::STONES));
			break;

		case Texture::Name::RED_BRICK:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::RED_BRICK));
			break;

		case Texture::Name::DUCKWEED:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::DUCKWEED));
			break;

		case Texture::Name::ROCKS:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::ROCKS));
			break;

		case Texture::Name::CRATE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::CRATE));
			break;

		case Texture::Name::BONE_2:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::BONE_2));
			break;

		case Texture::Name::PROTO_LOAD:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::PROTO_LOAD));
			break;
		case Texture::Name::TEXT:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::TEXT));
			break;
		case Texture::Name::SPACE_FRIGATE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::SPACE_FRIGATE));
			break;
		case Texture::Name::R2D2:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::R2D2));
			break;

		case Texture::Name::CHICKEN_BOT:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::CHICKEN_BOT));
			break;

		case Texture::Name::MOUSEY:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::MOUSEY));
			break;

		case Texture::Name::NOT_INITIALIZED:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Texture::NOT_INITIALIZED));
			break;

		default:
			assert(false);
		}
	}


	StringThis::StringThis(Mesh::Name status)
	{
		switch(status)
		{
		case Mesh::Name::CUBE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CUBE));
			break;

		case Mesh::Name::CRATE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CRATE));
			break;

		case Mesh::Name::BONE_2:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::BONE_2));
			break;

		case Mesh::Name::SPHERE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::SPHERE));
			break;

		case Mesh::Name::PYRAMID:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::PYRAMID));
			break;

		case Mesh::Name::CAMERA:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CAMERA));
			break;

		case Mesh::Name::SPRITE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::SPRITE));
			break;

		case Mesh::Name::SPACE_FRIGATE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::SPACE_FRIGATE));
			break;
		case Mesh::Name::R2D2:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::R2D2));
			break;

		case Mesh::Name::CHICKEN_SKIN:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::CHICKEN_SKIN));
			break;

		case Mesh::Name::MOUSEY_SKIN:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::MOUSEY_SKIN));
			break;

		case Mesh::Name::Bone:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone));
			break;

		case Mesh::Name::Bone_001:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_001));
			break;

		case Mesh::Name::Bone_L:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_L));
			break;

		case Mesh::Name::Bone_L_001:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_L_001));
			break;

		case Mesh::Name::Bone_L_002:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_L_002));
			break;

		case Mesh::Name::Bone_R:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_R));
			break;

		case Mesh::Name::Bone_R_001:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_R_001));
			break;

		case Mesh::Name::Bone_R_002:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::Bone_R_002));
			break;

		case Mesh::Name::NOT_INITIALIZED:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::NOT_INITIALIZED));
			break;

		case Mesh::Name::NULL_MESH:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(Mesh::NULL_MESH));
			break;

		default:
			assert(false);
		}
	}



	StringThis::StringThis(ShaderObject::Name status)
	{
		switch(status)
		{
		case ShaderObject::Name::NULL_SHADER:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::NULL_SHADER));
			break;

		case ShaderObject::Name::SPRITE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::SPRITE));
			break;

		case ShaderObject::Name::COLOR_POSITION:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::COLOR_POSITION));
			break;

		case ShaderObject::Name::SKIN_TEXTURE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::SKIN_TEXTURE));
			break;

		case ShaderObject::Name::TEXTURE_SIMPLE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::TEXTURE_SIMPLE));
			break;

		case ShaderObject::Name::TEXTURE_POINT_LIGHT:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::TEXTURE_POINT_LIGHT));
			break;

		case ShaderObject::Name::CONST_COLOR:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::CONST_COLOR));
			break;

		case ShaderObject::Name::COLOR_SINGLE:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::COLOR_SINGLE));
			break;

		case ShaderObject::Name::COMPUTE_TEST:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::COMPUTE_TEST));
			break;

		case ShaderObject::Name::COMPUTE_MIXER:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::COMPUTE_MIXER));
			break;

		case ShaderObject::Name::COMPUTE_WORLD:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::COMPUTE_WORLD));
			break;

		case ShaderObject::Name::UNINITIALIZED:
			strcpy_s(this->buffer, BUFFER_SIZE, STRING_ME(ShaderObject::UNINITIALIZED));
			break;

		default:
			assert(false);
		}
	}


	StringThis::operator char *()
	{
		return this->buffer;
	}

}

// --- End of File ---