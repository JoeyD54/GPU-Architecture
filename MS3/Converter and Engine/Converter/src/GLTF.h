//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef GLTF_H
#define GLTF_H

#include "tiny_gltf.h"
#include "MathEngine.h"
#include "meshData.h"

using namespace tinygltf;

namespace Azul
{

	struct fVect2
	{
		fVect2() = default;
		~fVect2() = default;

		float u;
		float v;
	};

	struct fVect3
	{
		fVect3() = default;
		~fVect3() = default;

		fVect3(float _x, float _y, float _z)
			:x(_x), y(_y), z(_z)
		{}

		float x;
		float y;
		float z;
	};

	struct fVect4
	{
		fVect4() = default;
		~fVect4() = default;

		fVect4(float _x, float _y, float _z, float _w)
			:x(_x), y(_y), z(_z), w(_w)
		{

		}

		float x;
		float y;
		float z;
		float w;
	};

	struct iuVect3
	{
		iuVect3() = default;
		~iuVect3() = default;

		iuVect3(unsigned int _v0, unsigned int _v1, unsigned int _v2)
			: v0(_v0), v1(_v1), v2(_v2)
		{

		}

		unsigned int v0;
		unsigned int v1;
		unsigned int v2;
	};

	struct isVect3
	{
		isVect3() = default;
		~isVect3() = default;

		isVect3(unsigned short _x, unsigned short _y, unsigned short _z)
			:x(_x), y(_y), z(_z)
		{

		}
		unsigned short x;
		unsigned short y;
		unsigned short z;

	};

	struct isVect4
	{
		isVect4() = default;
		~isVect4() = default;

		isVect4(unsigned short _x, unsigned short _y, unsigned short _z, unsigned short _w)
			:x(_x), y(_y), z(_z), w(_w)
		{

		}
		unsigned short x;
		unsigned short y;
		unsigned short z;
		unsigned short w;
	};

	struct iuVect4
	{
		iuVect4() = default;
		~iuVect4() = default;

		iuVect4(unsigned int _x, unsigned int _y, unsigned int _z, unsigned int _w)
			:x(_x), y(_y), z(_z), w(_w)
		{

		}
		unsigned int x;
		unsigned int y;
		unsigned int z;
		unsigned int w;
	};

	struct fMat4
	{
		float m0;
		float m1;
		float m2;
		float m3;
		float m4;
		float m5;
		float m6;
		float m7;
		float m8;
		float m9;
		float m10;
		float m11;
		float m12;
		float m13;
		float m14;
		float m15;
	};

	struct skin_weight_joint_index
	{
		skin_weight_joint_index() = default;
		~skin_weight_joint_index() = default;
		size_t	index;
		fVect4	skinWeight;
		isVect4	jointIndex;
	};

	struct LocalToGlobalIndex
	{
		LocalToGlobalIndex(size_t _local, size_t _global, size_t _joint)
			: localIndex(_local), globalIndex(_global), JointIndex(_joint)
		{}

		size_t localIndex;   // new model
		size_t globalIndex;  // original model	
		size_t JointIndex;   // Here for verification...should be same value for every index
	};

	struct BoneMesh
	{
		std::string boneName;
		size_t      vertCount;
		size_t      jointIndex;
		Mat4        inverseMatrix;  // single - Inverse Matrix based on JointIndex
		bool        corrected;      // pos/norms corrected
		std::vector< LocalToGlobalIndex > l2gIndex;   // x
		std::vector< fVect3 > pos;
		std::vector< fVect3 > norms;
		std::vector< fVect2 > text_coord;
		std::vector< iuVect3 > index;                 // x
	};

	struct SkinMesh
	{
		std::string skinName;
		size_t      vertCount;
		size_t      polyCount;

		std::vector< int > jointTable;

		// Skin data...
		std::vector< Mat4 > invBone;
		std::vector< iuVect4 > joints;  // orig unsigned short--> unsigned int
		std::vector< fVect4 > weights;
		std::vector< fVect4 > color;  // rgba

		// Mesh data...
		std::vector< fVect3 > pos;
		std::vector< fVect3 > norms;
		std::vector< fVect2 > text_coord;

		// Trilist indexing
		std::vector< iuVect3 > index;  // orig unsigned short--> unsigned int
	};


	struct GLB_header
	{
		uint32_t magic;
		uint32_t version;
		uint32_t length;
	};

	struct CHUNK_header
	{
		uint32_t chunkLength;
		uint32_t chunkType;
		unsigned char chunkData[];
	};

	class GLTF
	{
	public:

		static bool LoadBinary(Model &model, const char *const pFileName);
		static bool LoadASCII(Model &model, const char *const pFileName);

		static bool GetGLBRawBuffer(char *&pBuff, unsigned int &BuffSize, const char *const pFileName);
		static bool GetGLBHeader(GLB_header &header, const char *const pBuff, unsigned int BuffSize);
		static bool GetRawJSON(char *&pJSON, unsigned int &JsonSize, const char *const pBuff, unsigned int BuffSize);
		static bool GetBinaryBuffPtr(char *&pBinaryBuff, unsigned int &BinaryBuffSize, const char *const pBuff, unsigned int BuffSize);

		static bool SetCustomVBO(unsigned int AttribIndex,
			const char *pKey,
			vboData &vbo,
			void *data,
			unsigned int sizeInBytes,
			unsigned int count,
			vboData::VBO_COMPONENT componentType,
			vboData::VBO_TYPE type,
			vboData::VBO_TARGET target);

		static bool SetCustomVBO_index(unsigned int AttribIndex,
			const char *pKey,
			vboData &vbo,
			void *data,
			unsigned int sizeInBytes,
			unsigned int count,
			vboData::VBO_COMPONENT componentType,
			vboData::VBO_TYPE type,
			vboData::VBO_TARGET target);

		static bool SetVBO(Model &gltfModel,
			unsigned int AttribIndex,
			const char *pKey,
			vboData &vbo,
			char *pBinaryBuff);

		static bool SetVBO_index(Model &gltfModel, unsigned int AttribIndex, vboData &vbo, char *pBinaryBuff);

		static bool SetVBO_BONE(Model &gltfModel,
			unsigned int _AttribIndex,
			const char *pKey,
			vboData &vbo,
			char *pBuffStart,
			unsigned int byteLength,
			unsigned int count);

		static bool SetVBO_BONE_index(Model &gltfModel,
			unsigned int _AttribIndex,
			vboData &vbo,
			char *pBuffStart,
			unsigned int byteLength,
			unsigned int count);

		static bool SetTexture(Model &gltfModel, unsigned int index, textureData &text, char *pBinaryBuff);

		static void PrintData(char *pBinaryBuff, size_t byteOffset, size_t count, vboData::VBO_COMPONENT componentType, vboData::VBO_TYPE vboType);

		static bool GetAzulProtoType(const char *&pProtoFileType, meshData &_meshData);
	};
}

#endif

// --- End of File ---
