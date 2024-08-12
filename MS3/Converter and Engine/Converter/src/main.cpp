//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GLTF.h"
#include "json.hpp"

#include "File.h"
#include "ShaderLayout.h"
#include "meshDataConverter.h"

#include "CubeMesh.h"
#include "SphereMesh.h"
#include "PyramidMesh.h"

#include "ConvertTexture.h"

#include "ConvertedDataCopy.h"
#include "ConvertModel.h"
#include "ConvertAnim.h"
#include "ConvertSkeleton.h"
#include "ConvertHierarchy.h"
#include "ConvertSkin.h"

#include "ConvertXML.h"

using namespace Azul;
using namespace tinygltf;
using json = nlohmann::json;

void CreateModel(const char* modelName);

int main()
{
	// Verify that the version of the library that we linked against is
	// compatible with the version of the headers we compiled against.
	GOOGLE_PROTOBUF_VERIFY_VERSION;

	// Premade - Meshes
	ConvertCubeMesh();
	ConvertPyramidMesh();
	ConvertSphereMesh();

	// Textures
	ConvertTextureTGA("Aliens.tga");
	ConvertTextureTGA("HotPink.tga");
	ConvertTextureTGA("Rocks.tga");
	ConvertTextureTGA("Duckweed.tga");
	ConvertTextureTGA("RedBrick.tga");
	ConvertTextureTGA("Stone.tga");
	ConvertTexturePNG("R2D2_BaseColor.png");
	ConvertTexturePNG("FontTexture.png");
	ConvertTexturePNG("Ch14_1001_Diffuse.png");
	ConvertTexturePNG("ChickenbotDiffuse.png");

	// convert to Model, Anim, Skeleton
	ConvertModel("R2-D2");

	//Create  model with textures
	CreateModel("wooden crate");
	CreateModel("space_frigate");

	// Animation
	ConvertAnim("walk_mesh");
	ConvertAnim("run+mesh");
	ConvertAnim("shot_up+mesh");
	ConvertAnim("sidestep_right+mesh");


	// per model
	ConvertSkin("walk_mesh", "ChickenBot");
	ConvertJoint("walk_mesh", "ChickenBot");
	ConvertSkeleton("walk_mesh", "ChickenBot");
	ConvertHierarchy("walk_mesh", "ChickenBot");
	ConvertInvBind("walk_mesh", "ChickenBot");

	// Animation
	ConvertAnim("Joyful Jump");

	// per model
	ConvertSkin("Joyful Jump", "Mouse");
	ConvertJoint("Joyful Jump", "Mouse");
	ConvertSkeleton("Joyful Jump","Mouse");
	ConvertHierarchy("Joyful Jump", "Mouse");
	ConvertInvBind("Joyful Jump", "Mouse");

	ConvertAnim("Mousey_Shuffling");
	ConvertAnim("Mousey_Gangnam_Style");
	ConvertAnim("Mousey_Happy_Walk");
	ConvertAnim("Mousey_Hip_Hop_Dancing");
	ConvertAnim("Mousey_Northern_Soul_Spin2");
	ConvertAnim("Mousey_Rumba_Dancing");
	ConvertAnim("Mousey_Run_Forward");

	// convert XML
	ConvertXML("Metrics");


	// Move Converted data to the Data Directory
	ConvertedDataCopy();

	google::protobuf::ShutdownProtobufLibrary();

	return 0;
}

void CreateModel(const char* modelName)
{

	bool status;
	tinygltf::Model gltfModel;

	// runtime model
	meshData  runModel;

	const char* pGLB_extension = ".glb";
	const char* pProto_extension = ".proto.azul";

	size_t FileNameSize = strlen(modelName) + strlen(pGLB_extension) + 1;

	char* poFileName = new char[FileNameSize]();
	strcat_s(poFileName, FileNameSize, modelName);
	strcat_s(poFileName, FileNameSize, pGLB_extension);

	size_t ProtoFileNameSize = strlen(modelName) + strlen(pProto_extension) + 1;

	char* poProtoFileName = new char[ProtoFileNameSize]();
	strcat_s(poProtoFileName, ProtoFileNameSize, modelName);
	strcat_s(poProtoFileName, ProtoFileNameSize, pProto_extension);

	// Load the gltfModel
	status = GLTF::LoadBinary(gltfModel, poFileName);
	assert(status);

	// Read glb into memory (raw buffer)
	char* poBuff = nullptr;
	unsigned int BuffSize(0);

	status = GLTF::GetGLBRawBuffer(poBuff, BuffSize, poFileName);
	assert(status);

	// Get GLB_Header
	GLB_header glbHeader;
	status = GLTF::GetGLBHeader(glbHeader, poBuff, BuffSize);
	assert(status);

	// Get Raw JSON
	char* poJSON = nullptr;
	unsigned int JsonSize(0);
	status = GLTF::GetRawJSON(poJSON, JsonSize, poBuff, BuffSize);
	assert(status);

	// Get the Binary Buffer Address
	char* pBinaryBuff = nullptr;
	unsigned int BinaryBuffSize = 0;
	status = GLTF::GetBinaryBuffPtr(pBinaryBuff, BinaryBuffSize, poBuff, BuffSize);
	assert(status);


	//---------------------------------
	// Model Name
	//---------------------------------

	memcpy_s(runModel.pMeshName, meshData::FILE_NAME_SIZE, gltfModel.nodes[0].name.c_str(), gltfModel.nodes[0].name.length());


	//---------------------------------
	// Set vbo 
	//---------------------------------
	GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_VERT, "POSITION", runModel.vbo_vert, pBinaryBuff);
	runModel.vbo_vert.Print("vbo_vert");

	GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_NORM, "NORMAL", runModel.vbo_norm, pBinaryBuff);
	runModel.vbo_norm.Print("vbo_norm");

	GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_TEXT, "TEXCOORD_0", runModel.vbo_uv, pBinaryBuff);
	runModel.vbo_uv.Print("vbo_uv");

	GLTF::SetVBO(gltfModel, ATTRIB_LOCATION_COLOR, "COLOR_0", runModel.vbo_color, pBinaryBuff);
	runModel.vbo_color.Print("vbo_color");

	GLTF::SetVBO_index(gltfModel, ATTRIB_LOCATION_INDEX, runModel.vbo_index, pBinaryBuff);
	runModel.vbo_index.Print("vbo_index");


	//--------------------------------
	// PolyCount
	//--------------------------------
	runModel.triCount = runModel.vbo_index.count / 3;
	runModel.vertCount = runModel.vbo_vert.count;

	//--------------------------------
	// BoundingSphere
	//--------------------------------

	//runModel.

	//Vec3* pVerts = new Vec3[(unsigned int)runModel.vertCount];
	//for (int i = 0; i < runModel.vertCount; i++)
	//{
		//pVerts[i].set(cubeData_xyz[i].x, cubeData_xyz[i].y, cubeData_xyz[i].z);
		//Trace::out("%d:  %f %f %f\n", i, pVerts[i][x], pVerts[i][y], pVerts[i][z]);
	//}


	//--------------------------------
	// RenderMode
	//--------------------------------
	runModel.mode = meshDataConverter::GetMode(gltfModel.meshes[0].primitives[0].mode);
	assert(runModel.mode == meshData::RENDER_MODE::MODE_TRIANGLES);

	// Set texture from Image vector

	// Find index to color
	if (gltfModel.images.size() > 0)
	{
		unsigned int colorIndex = 0;
		colorIndex = (unsigned int)gltfModel.materials[0].pbrMetallicRoughness.baseColorTexture.index;

		GLTF::SetTexture(gltfModel, colorIndex, runModel.text_color, pBinaryBuff);
		runModel.text_color.Print("text_color");
	}

	delete[] poBuff;

	Trace::out("--------------\n");
	Trace::out("--------------\n");
	Trace::out("--------------\n");

	runModel.Print("mA");
	meshData_proto mA_proto;
	runModel.Serialize(mA_proto);

	Trace::out("\n");
	Trace::out("message size: %d \n", mA_proto.ByteSizeLong());
	Trace::out("\n");


	// -------------------------------
	//  Write to file
	//--------------------------------

	File::Handle fh;
	File::Error err;

	const char* pProtoFileType = nullptr;
	status = GLTF::GetAzulProtoType(pProtoFileType, runModel);
	assert(status);

	// Create output name
	std::string BaseName(modelName);
	std::string OutputFileName = BaseName + pProtoFileType + ".proto.azul";

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

	char* poNewBuff = new char[FileLength]();
	assert(poNewBuff);

	err = File::Seek(fh, File::Position::BEGIN, 0);
	assert(err == File::Error::SUCCESS);

	err = File::Read(fh, poNewBuff, FileLength);
	assert(err == File::Error::SUCCESS);

	err = File::Close(fh);
	assert(err == File::Error::SUCCESS);

	Trace::out("--------------\n");
	Trace::out("--------------\n");
	Trace::out("--------------\n");

	std::string strIn(poNewBuff, FileLength);
	meshData_proto mB_proto;

	mB_proto.ParseFromString(strIn);

	meshData mB;
	mB.Deserialize(mB_proto);
	mB.Print("mB");

	delete[] poProtoFileName;
	delete[] poFileName;
	delete[] poJSON;
	delete[] poNewBuff;
}
// ---  End of File ---
