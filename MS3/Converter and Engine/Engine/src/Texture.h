//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef TEXTURE_H
#define TEXTURE_H

#include "sb7.h"
#include "DLink.h"
namespace Azul
{
	class Texture : public DLink
	{
	public:
		static const unsigned int TEXTURE_ASSET_NAME_SIZE = 64;

	public:
		enum class Name
		{
			HOT_PINK,
			INVADERS,
			STONES,
			RED_BRICK,
			DUCKWEED,
			ROCKS,
			CRATE,
			BONE_2,
			PROTO_LOAD,
			SPACE_FRIGATE,
			R2D2,
			TEXT,
			MOUSEY,
			CHICKEN_BOT,
			NOT_INITIALIZED
		};

	public:
		Texture();
		Texture(const Texture &) = default;
		Texture &operator = (const Texture &) = default;
		virtual ~Texture() override;

		void Set(const char *const _assetName,
			Name _name,
			GLuint _TextureID,
			GLenum minFilter,
			GLenum magFilter,
			GLenum wrapModeS,
			GLenum wrapModeT,
			unsigned int width,
			unsigned int height);


		virtual char *GetName() override;
		virtual bool Compare(DLink *pTarget) override;
		virtual void Dump() override;
		virtual void Wash() override;

	private:
		char assetName[TEXTURE_ASSET_NAME_SIZE];

	public:
		Name name;
		GLuint textureID;
		GLenum minFilter;
		GLenum magFilter;
		GLenum wrapModeS;
		GLenum wrapModeT;
		unsigned int    width;
		unsigned int    height;
	};
}
#endif

// --- End of File ---
