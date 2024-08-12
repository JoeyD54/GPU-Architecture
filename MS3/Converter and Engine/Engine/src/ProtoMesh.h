//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PROTO_MESH_H
#define PROTO_MESH_H

#include "Mesh.h"
#include "Texture.h"

namespace Azul
{
	class ProtoMesh : public Mesh
	{
	public:
		ProtoMesh(const char *const pMeshFileName, Texture::Name name);
		ProtoMesh(const char *const pMeshFileName);

		ProtoMesh() = delete;
		ProtoMesh(const ProtoMesh &) = delete;
		ProtoMesh &operator = (ProtoMesh &) = delete;
		virtual ~ProtoMesh();

	private:
		void privCreateVAO(const char *const pMeshFileName, Texture *&pTexture);

		// Data

	};
}

#endif

// --- End of File ---
