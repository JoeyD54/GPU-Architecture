//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CubeMesh.h"
#include "meshData.h"
#include "GLTF.h"
#include "File.h"
#include "MathEngine.h"
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


	Tri_index pyramid_triList[] =
	{
		{  1,  0,  2},
		{  3,  2,  0},
		{  5,  4,  6},
		{  7,  5,  6},
		{  9,  8, 10},
		{ 11,  9, 10},
		{ 13, 12, 14},
		{ 15, 13, 14},
		{ 17, 16, 18},
		{ 19, 18, 16},
		{ 21, 20, 22},
		{ 23, 22, 20}
	};

	Vert_xyz  pyramidData_xyz[] =
	{
		{-0.25f,   0.0f,  -0.25f  },
		{-0.25f,  -0.0f,  -0.25f  },
		{ 0.25f,  -0.0f,  -0.25f  },
		{  0.0f,   1.0f,   -0.0f  },
		{ 0.25f,  -0.0f,  -0.25f  },
		{ 0.25f,  -0.0f,   0.25f  },
		{  0.0f,   1.0f,   -0.0f  },
		{ 0.25f,   0.0f,   0.25f  },
		{ 0.25f,  -0.0f,   0.25f  },
		{-0.25f,  -0.0f,   0.25f  },
		{  0.0f,   1.0f,    0.0f  },
		{ -0.0f,   1.0f,    0.0f  },
		{-0.25f,  -0.0f,   0.25f  },
		{-0.25f,  -0.0f,  -0.25f  },
		{ -0.0f,   1.0f,    0.0f  },
		{ -0.0f,   1.0f,   -0.0f  },
		{-0.25f,  -0.0f,   0.25f  },
		{ 0.25f,  -0.0f,   0.25f  },
		{ 0.25f,  -0.0f,  -0.25f  },
		{-0.25f,  -0.0f,  -0.25f  },
		{ -0.0f,   1.0f,   -0.0f  },
		{  0.0f,   1.0f,   -0.0f  },
		{  0.0f,   1.0f,    0.0f  },
		{ -0.0f,   1.0f,    0.0f  }

	};

	Vert_nxnynz pyramidData_nxnynz[]
	{
		{  -0.6f,   0.6f,  -0.6f  },
		{  -0.6f,  -0.6f,  -0.6f  },
		{   0.6f,  -0.6f,  -0.6f  },
		{   0.6f,   0.6f,  -0.6f  },
		{   0.6f,  -0.6f,  -0.6f  },
		{   0.6f,  -0.6f,   0.6f  },
		{   0.6f,   0.6f,  -0.6f  },
		{   0.6f,   0.6f,   0.6f  },
		{   0.6f,  -0.6f,   0.6f  },
		{  -0.6f,  -0.6f,   0.6f  },
		{   0.6f,   0.6f,   0.6f  },
		{  -0.6f,   0.6f,   0.6f  },
		{  -0.6f,  -0.6f,   0.6f  },
		{  -0.6f,  -0.6f,  -0.6f  },
		{  -0.6f,   0.6f,   0.6f  },
		{  -0.6f,   0.6f,  -0.6f  },
		{  -0.6f,  -0.6f,   0.6f  },
		{   0.6f,  -0.6f,   0.6f  },
		{   0.6f,  -0.6f,  -0.6f  },
		{  -0.6f,  -0.6f,  -0.6f  },
		{  -0.6f,   0.6f,  -0.6f  },
		{   0.6f,   0.6f,  -0.6f  },
		{   0.6f,   0.6f,   0.6f  },
		{  -0.6f,   0.6f,   0.6f  }

	};

	Vert_uv pyramidData_uv[] =
	{
		{  0.0f,  0.0f,  },
		{  0.0f,  1.0f,  },
		{  1.0f,  1.0f,  },
		{  1.0f,  0.0f,  },
		{  0.0f,  1.0f,  },
		{  1.0f,  1.0f,  },
		{  0.0f,  0.0f,  },
		{  1.0f,  0.0f,  },
		{  1.0f,  1.0f,  },
		{  0.0f,  1.0f,  },
		{  1.0f,  0.0f,  },
		{  0.0f,  0.0f,  },
		{  0.0f,  0.0f,  },
		{  0.0f,  1.0f,  },
		{  1.0f,  0.0f,  },
		{  1.0f,  1.0f,  },
		{  0.0f,  0.0f,  },
		{  1.0f,  0.0f,  },
		{  1.0f,  1.0f,  },
		{  0.0f,  1.0f,  },
		{  0.0f,  1.0f,  },
		{  1.0f,  1.0f,  },
		{  1.0f,  0.0f,  },
		{  0.0f,  0.0f,  }
	};


	void ConvertPyramidMesh()
	{
		Trace::out("ConvertPyramidMesh(): \n");
		// runtime model
		meshData  runModel;

		// Name
		std::string BaseName = "PyramidMesh";

		//--------------------------------
		// GameEngine mapping - ge prefix
		// -------------------------------

		unsigned int numTris = sizeof(pyramid_triList) / sizeof(pyramid_triList[0]);
		unsigned int numVerts = sizeof(pyramidData_xyz) / sizeof(pyramidData_xyz[0]);

		//---------------------------------
		// Model Name
		//---------------------------------
		const char *pMeshName = BaseName.c_str();
		memcpy_s(runModel.pMeshName, meshData::FILE_NAME_SIZE, pMeshName, strlen(pMeshName));

		// Correct make Z dominate, correct postion
		Mat4 M(Mat4::Rot1::X, MATH_PI2);
		for(size_t i = 0; i < numVerts; i++)
		{
			Vec3 v(pyramidData_xyz[i].x, pyramidData_xyz[i].y, pyramidData_xyz[i].z);
			v = v * M;
			pyramidData_xyz[i].x = v[x];
			pyramidData_xyz[i].y = v[y];
			pyramidData_xyz[i].z = v[z];

			//Trace::out("%d: %f %f %f \n", i, pyramidData_xyz[i].x, pyramidData_xyz[i].y, pyramidData_xyz[i].z);
		}

		for(size_t i = 0; i < numVerts; i++)
		{
			Vec3 v(pyramidData_nxnynz[i].nx, pyramidData_nxnynz[i].ny, pyramidData_nxnynz[i].nz);
			v = v * M;
			pyramidData_nxnynz[i].nx = v[x];
			pyramidData_nxnynz[i].ny = v[y];
			pyramidData_nxnynz[i].nz = v[z];
		}

		//---------------------------------
		// Set vbo 
		//---------------------------------
		GLTF::SetCustomVBO(ATTRIB_LOCATION_VERT,
			"POSITION",
			runModel.vbo_vert,
			pyramidData_xyz,
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
			pyramidData_nxnynz,
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
			pyramidData_uv,
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
			pyramid_triList,
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
