//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#ifndef MESH_DATA_H
#define MESH_DATA_H

#include "MeshData.pb.h"
#include "vboData.h"
#include "textureData.h"

namespace Azul
{

	class meshData
	{
	public:
		static const unsigned int FILE_NAME_SIZE = 64;

		static constexpr const char *PROTO_VERSION = "1.1.0"; // Major.Version.Rev
		static const unsigned int VERSION_NUM_BYTES = 8;

	public:
		enum class RENDER_MODE
		{
			MODE_POINTS = 0,
			MODE_LINE = 1,
			MODE_LINE_LOOP = 2,
			MODE_LINE_STRIP = 3,
			MODE_TRIANGLES = 4,
			MODE_TRIANGLE_STRIP = 5,
			MODE_TRIANGLE_FAN = 6,
			DEFAULT = MODE_TRIANGLES
		};

	public:
		meshData();
		meshData(const meshData &) = delete;
		meshData &operator = (const meshData &) = delete;
		~meshData();

		// Serialization 
		void Serialize(meshData_proto &out) const;
		void Deserialize(const meshData_proto &in);

		void Print(const char *const pName) const;

	public:
		char             pVersion[VERSION_NUM_BYTES];

		char             pMeshName[FILE_NAME_SIZE];
		RENDER_MODE      mode;
		unsigned int     triCount;
		unsigned int     vertCount;

		// All models can have this data
		vboData          vbo_vert;   // Engine Attribute: 0
		vboData          vbo_norm;   // Engine Attribute: 1
		vboData          vbo_uv;     // Engine Attribute: 2 
		vboData          vbo_color;  // Engine Attribute: 3   
		vboData          vbo_index;  // Engine Attribute: 4

		// remove this... loading texture separately
		textureData      text_color;

		// Skinned data
		vboData          vbo_weights;  // Engine Attribute: 5
		vboData          vbo_joints;   // Engine Attribute: 6
		vboData          vbo_invBind;  // Engine Attribute: 7

	};

}

#endif

// --- End of File ---
