//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "WorldCompute.h"
#include "File.h"
#include "HierarchyData.h"
#include "InvBindData.h"

namespace Azul
{
	WorldCompute::WorldCompute(Mixer *pMixer, const char *pHierarchyName, const char *pInvBindName)
		: LocalBone(pMixer->Result),
		Hierarchy(),
		WorldMat(),
		InvBind(),
		boneCount(pMixer->numBones),
		hierarchyDepth(0)
	{

		assert(pHierarchyName);
		assert(pInvBindName);

		// -------------------------------
		// Read and recreate model data
		// -------------------------------
		File::Handle fh;
		File::Error err;

		err = File::Open(fh, pHierarchyName, File::Mode::READ);

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

		std::string strIn(poNewBuff, FileLength);
		HierarchyData_proto hA_proto;

		hA_proto.ParseFromString(strIn);

		HierarchyData hB;
		hB.Deserialize(hA_proto);

		delete[] poNewBuff;
		//hB.Print("hB");

		this->hierarchyDepth = (int) hB.maxDepth;


		//------------------------------
		//  Yuck super long to get to this point... 
		// -----------------------------

		// transfer the data to GPU
		this->Hierarchy.Set((hB.maxDepth * hB.numNodes), sizeof(int), hB.poData);

		// ---------------------------
		// world matrix array
		// ----------------------------

		Mat4 *pWorldArray = new Mat4[hB.numNodes]();
		assert(pWorldArray);

		// transfer data to GPU
		this->WorldMat.Set(hB.numNodes, sizeof(Mat4), pWorldArray);

		delete[] pWorldArray;


		// -------------------------------
		// Inv Bind
		// -------------------------------
		err = File::Open(fh, pInvBindName, File::Mode::READ);

		assert(err == File::Error::SUCCESS);

		err = File::Seek(fh, File::Position::END, 0);
		assert(err == File::Error::SUCCESS);

		err = File::Tell(fh, FileLength);
		assert(err == File::Error::SUCCESS);

		poNewBuff = new char[FileLength]();
		assert(poNewBuff);

		err = File::Seek(fh, File::Position::BEGIN, 0);
		assert(err == File::Error::SUCCESS);

		err = File::Read(fh, poNewBuff, FileLength);
		assert(err == File::Error::SUCCESS);

		err = File::Close(fh);
		assert(err == File::Error::SUCCESS);

		std::string strIn2(poNewBuff, FileLength);
		InvBindData_proto IA_proto;

		IA_proto.ParseFromString(strIn2);

		InvBindData IB;
		IB.Deserialize(IA_proto);


		this->InvBind.Set(IB.numMat, sizeof(Mat4), IB.poData);


		delete[] poNewBuff;
		//IB.Print("IB");

	}

}

// --- End of File ---
