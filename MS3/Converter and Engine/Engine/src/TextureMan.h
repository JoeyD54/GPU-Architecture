//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef TEXTURE_MAN_H
#define TEXTURE_MAN_H 

#include "ManBase.h"
#include "Texture.h"
#include "meshData.h"

namespace Azul
{
	class TextureMan : public ManBase
	{
		//----------------------------------------------------------------------
		// Static Methods
		//----------------------------------------------------------------------
	public:
		static void Create(int reserveNum = 0, int reserveGrow = 1);
		static void Destroy();

		static void Add(Texture::Name name, Texture *pTexture);

		static Texture *Add(const char *const pFileName, Texture::Name name);

		static Texture *Add(meshData &mB);
		static Texture *Find(Texture::Name name);
		static GLuint FindID(Texture::Name name);
		static void Remove(Texture *pNode);
		static void Dump();

		//----------------------------------------------------------------------
		// Private methods
		//----------------------------------------------------------------------
	private:
		static TextureMan *privGetInstance();

		~TextureMan();
		TextureMan(const TextureMan &) = delete;
		TextureMan &operator = (const TextureMan &) = delete;
		TextureMan(int reserveNum, int reserveGrow);

		void privLoadTexture(meshData &mB, GLuint *&textureID);
		bool privLoadRawTexture(meshData &mB);

		GLenum privGetOpenGLValue(textureData::TEXTURE_EFORMAT eFormat) const;
		GLint privGetOpenGLValue(textureData::TEXTURE_NCOMPONENT nComponent) const;

		//----------------------------------------------------------------------
		// Override Abstract methods
		//----------------------------------------------------------------------
	protected:
		DLink *derivedCreateNode() override;


		//----------------------------------------------------------------------
		// Data: unique data for this manager 
		//----------------------------------------------------------------------
	private:
		Texture *poNodeCompare;
		static TextureMan *posInstance;

	};
}

#endif

// --- End of File ---
