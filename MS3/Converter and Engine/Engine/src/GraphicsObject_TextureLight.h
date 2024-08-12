//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GRAPHICS_OBJECT_TEXTURE_LIGHT_H
#define GRAPHICS_OBJECT_TEXTURE_LIGHT_H

#include "GraphicsObject.h"
#include "Texture.h"
#include "MathEngine.h"

namespace Azul
{
	class GraphicsObject_TextureLight : public GraphicsObject
	{
	public:
		GraphicsObject_TextureLight(Mesh *_pMesh, ShaderObject *_pShaderObj, Texture::Name  _name, Vec4 &LightColor, Vec3 &LightPos);

		GraphicsObject_TextureLight() = delete;
		GraphicsObject_TextureLight(const GraphicsObject_TextureLight &) = delete;
		GraphicsObject_TextureLight &operator = (const GraphicsObject_TextureLight &) = delete;
		virtual ~GraphicsObject_TextureLight();

		// Rendermaterial contract
		virtual void SetState() override;
		virtual void SetDataGPU() override;
		virtual void Draw() override;
		virtual void RestoreState() override;

		// data:  place uniform instancing here

		Texture::Name  textName;
		Vec4 *poLightColor;
		Vec3 *poLightPos;
	};

}

#endif

// ---  End of File ---