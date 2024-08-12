//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CubeMesh.h"
#include "meshData.h"
#include "GLTF.h"
#include "File.h"
#include "ShaderLayout.h"

using namespace tinygltf;

namespace Azul
{
	struct Vert_xyz
	{
		float x;
		float y;
		float z;
	};

	struct Vert_nxnynz
	{
		float nx;
		float ny;
		float nz;
	};

	struct Vert_uv
	{
		float u;
		float v;
	};

	struct Tri_index
	{
		unsigned int v0;
		unsigned int v1;
		unsigned int v2;
	};


	Tri_index cube_triList[] =
	{
		{  1,  0,  2 },
		{  4,  3,  5 },
		{  7,  6,  8 },
		{ 10,  9, 11 },
		{ 13, 12, 14 },
		{ 16, 15, 17 },
		{ 19, 18, 20 },
		{ 22, 21, 23 },
		{ 25, 24, 26 },
		{ 28, 27, 29 },
		{ 31, 30, 32 },
		{ 34, 33, 35 }
	};


	Vert_xyz  cubeData_xyz[] =
	{
		// Triangle 0
		{ -0.25f,  0.25f, -0.25f },
		{ -0.25f, -0.25f, -0.25f },
		{ 0.25f, -0.25f,  -0.25f },

		// Triangle 1
		{ 0.25f,  -0.25f, -0.25f },
		{ 0.25f,   0.25f, -0.25f },
		{ -0.25f,  0.25f, -0.25f },

		// Triangle 2
		{ 0.25f, -0.25f, -0.25f },
		{ 0.25f, -0.25f,  0.25f },
		{ 0.25f,  0.25f, -0.25f },

		// Triangle 3
		{ 0.25f, -0.25f,  0.25f },
		{ 0.25f,  0.25f,  0.25f },
		{ 0.25f,  0.25f, -0.25f },

		// Triangle 4
		{ 0.25f, -0.25f,  0.25f },
		{ -0.25f, -0.25f, 0.25f },
		{ 0.25f,  0.25f,  0.25f },

		// Triangle 5
		{ -0.25f, -0.25f,  0.25f },
		{ -0.25f,  0.25f,  0.25f },
		{ 0.25f,   0.25f,  0.25f },

		// Triangle 6
		{ -0.25f, -0.25f,  0.25f },
		{ -0.25f, -0.25f, -0.25f },
		{ -0.25f,  0.25f,  0.25f },

		// Triangle 7
		{ -0.25f, -0.25f, -0.25f },
		{ -0.25f,  0.25f, -0.25f },
		{ -0.25f,  0.25f,  0.25f },

		// Triangle 8
		{ -0.25f, -0.25f,  0.25f },
		{ 0.25f, -0.25f,   0.25f },
		{ 0.25f, -0.25f,  -0.25f },

		// Triangle 9
		{ 0.25f, -0.25f,  -0.25f },
		{ -0.25f, -0.25f, -0.25f },
		{ -0.25f, -0.25f,  0.25f },

		// Triangle 10
		{ -0.25f,  0.25f, -0.25f },
		{ 0.25f,  0.25f,  -0.25f },
		{ 0.25f,  0.25f,   0.25f },

		// Triangle 11
		{ 0.25f,  0.25f,   0.25f },
		{ -0.25f,  0.25f,  0.25f },
		{ -0.25f,  0.25f, -0.25f }
	};

	Vert_uv  cubeData_uv[] =
	{
		// Triangle 0
		{ 0.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },

		// Triangle 1
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 0.0f },

		// Triangle 2
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
		{ 0.0f, 0.0f },

		// Triangle 3
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },
		{ 0.0f, 0.0f },

		// Triangle 4
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 0.0f },

		// Triangle 5
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },

		// Triangle 6
		{ 0.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 0.0f },

		// Triangle 7
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },

		// Triangle 8
		{ 0.0f, 0.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f },

		// Triangle 9
		{ 1.0f, 1.0f },
		{ 0.0f, 1.0f },
		{ 0.0f, 0.0f },

		// Triangle 10
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f },

		// Triangle 11
		{ 1.0f, 0.0f },
		{ 0.0f, 0.0f },
		{ 0.0f, 1.0f }
	};

	Vert_nxnynz  cubeData_nxnynz[] =
	{
		// Triangle 0
		{ -0.6f,  0.6f, -0.6f },
		{ -0.6f, -0.6f, -0.6f },
		{  0.6f,  -0.6f, -0.6f },

		// Triangle 1
		{  0.6f, -0.6f, -0.6f },
		{  0.6f,  0.6f, -0.6f },
		{ -0.6f,  0.6f, -0.6f },

		// Triangle 2
		{  0.6f, -0.6f, -0.6f },
		{  0.6f, -0.6f,  0.6f },
		{  0.6f,  0.6f, -0.6f },

		// Triangle 3
		{  0.6f, -0.6f,  0.6f },
		{  0.6f,  0.6f,  0.6f },
		{  0.6f,  0.6f, -0.6f },

		// Triangle 4
		{  0.6f, -0.6f, 0.6f },
		{ -0.6f, -0.6f, 0.6f },
		{  0.6f,  0.6f, 0.6f },

		// Triangle 5
		{ -0.6f, -0.6f, 0.6f },
		{ -0.6f,  0.6f, 0.6f },
		{  0.6f,  0.6f, 0.6f },

		// Triangle 6
		{ -0.6f, -0.6f,  0.6f },
		{ -0.6f, -0.6f, -0.6f },
		{ -0.6f,  0.6f,  0.6f },

		// Triangle 7
		{ -0.6f, -0.6f, -0.6f },
		{ -0.6f,  0.6f, -0.6f },
		{ -0.6f,  0.6f,  0.6f },

		// Triangle 8
		{ -0.6f, -0.6f,  0.6f },
		{  0.6f, -0.6f,  0.6f },
		{  0.6f, -0.6f, -0.6f },

		// Triangle 9
		{  0.6f, -0.6f, -0.6f },
		{ -0.6f, -0.6f, -0.6f },
		{ -0.6f, -0.6f,  0.6f },

		// Triangle 10
		{ -0.6f, 0.6f, -0.6f },
		{  0.6f, 0.6f, -0.6f },
		{  0.6f, 0.6f,  0.6f },

		// Triangle 11
		{  0.6f, 0.6f,  0.6f },
		{ -0.6f, 0.6f,  0.6f },
		{ -0.6f, 0.6f, -0.6f }
	};

	void ConvertCubeMesh()
	{
		Trace::out("ConvertCubeMesh(): \n");

		// runtime model
		meshData  runModel;

		// Name
		std::string BaseName = "CubeMesh";


		unsigned int numTris = sizeof(cube_triList) / sizeof(cube_triList[0]);
		unsigned int numVerts = sizeof(cubeData_xyz) / sizeof(cubeData_xyz[0]);

		//---------------------------------
		// Model Name
		//---------------------------------
		const char *pMeshName = "CubeMesh";
		memcpy_s(runModel.pMeshName, meshData::FILE_NAME_SIZE, pMeshName, strlen(pMeshName));

		//---------------------------------
		// Set vbo 
		//---------------------------------

		GLTF::SetCustomVBO(ATTRIB_LOCATION_VERT,
			"POSITION",
			runModel.vbo_vert,
			cubeData_xyz,
			numVerts * sizeof(Vert_xyz),
			numVerts,
			vboData::VBO_COMPONENT::FLOAT,
			vboData::VBO_TYPE::VEC3,
			vboData::VBO_TARGET::ARRAY_BUFFER
		);
		//runModel.vbo_vert.Print("vbo_vert");

		GLTF::SetCustomVBO(ATTRIB_LOCATION_NORM,
			"NORMAL",
			runModel.vbo_norm,
			cubeData_nxnynz,
			numVerts * sizeof(Vert_nxnynz),
			numVerts,
			vboData::VBO_COMPONENT::FLOAT,
			vboData::VBO_TYPE::VEC3,
			vboData::VBO_TARGET::ARRAY_BUFFER
		);
		//runModel.vbo_norm.Print("vbo_norm");

		GLTF::SetCustomVBO(ATTRIB_LOCATION_TEXT,
			"TEXCOORD_0",
			runModel.vbo_uv,
			cubeData_uv,
			numVerts * sizeof(Vert_uv),
			numVerts,
			vboData::VBO_COMPONENT::FLOAT,
			vboData::VBO_TYPE::VEC2,
			vboData::VBO_TARGET::ARRAY_BUFFER
		);
		//runModel.vbo_uv.Print("vbo_uv");

		GLTF::SetCustomVBO_index(ATTRIB_LOCATION_INDEX,
			"INDEX",
			runModel.vbo_index,
			cube_triList,
			numTris * sizeof(Tri_index),
			numTris,
			vboData::VBO_COMPONENT::UNSIGNED_INT,
			vboData::VBO_TYPE::SCALAR,
			vboData::VBO_TARGET::ELEMENT_ARRAY_BUFFER
		);
		//runModel.vbo_index.Print("vbo_index");


		//--------------------------------
		// PolyCount
		//--------------------------------
		runModel.triCount = numTris;
		runModel.vertCount = numVerts;


		//Trace::out("--------------\n");
		//Trace::out("--------------\n");
		//Trace::out("--------------\n");

		//runModel.Print("mA");
		meshData_proto mA_proto;
		runModel.Serialize(mA_proto);

		//Trace::out("\n");
		//Trace::out("message size: %d \n", mA_proto.ByteSizeLong());
		//Trace::out("\n");


		// -------------------------------
		//  Write to file
		//--------------------------------

		File::Handle fh;
		File::Error err;

		// Create output name
		const char *pProtoFileType = nullptr;
		bool status = GLTF::GetAzulProtoType(pProtoFileType, runModel);
		assert(status);

		std::string OutputFileName = BaseName + pProtoFileType + ".proto.azul";

		Trace::out("   --> %s\n", OutputFileName.c_str());
		err = File::Open(fh, OutputFileName.c_str(), File::Mode::WRITE);
		assert(err == File::Error::SUCCESS);

		std::string strOut;
		mA_proto.SerializeToString(&strOut);

		File::Write(fh, strOut.data(), strOut.length());
		assert(err == File::Error::SUCCESS);

		err = File::Close(fh);
		assert(err == File::Error::SUCCESS);

		// -------------------------------
		// Read and recreate model data
		// -------------------------------

		err = File::Open(fh, OutputFileName.c_str(), File::Mode::READ);
		assert(err == File::Error::SUCCESS);

		err = File::Seek(fh, File::Position::END, 0);
		assert(err == File::Error::SUCCESS);

		DWORD FileLength;
		err = File::Tell(fh, FileLength);
		assert(err == File::Error::SUCCESS);

		char *poNewBuff = new char[FileLength]();
		assert(poNewBuff);

		err = File::Seek(fh, File::Position::BEGIN, 0);
		assert(err == File::Error::SUCCESS);

		err = File::Read(fh, poNewBuff, FileLength);
		assert(err == File::Error::SUCCESS);

		err = File::Close(fh);
		assert(err == File::Error::SUCCESS);

		//Trace::out("--------------\n");
		//Trace::out("--------------\n");
		//Trace::out("--------------\n");

		std::string strIn(poNewBuff, FileLength);
		meshData_proto mB_proto;

		mB_proto.ParseFromString(strIn);

		meshData mB;
		mB.Deserialize(mB_proto);
		//mB.Print("mB");

		delete[] poNewBuff;

	}
}


// --- End of File ---
