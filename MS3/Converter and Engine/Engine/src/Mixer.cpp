//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Mixer.h"
#include "MathApp.h"
#include "SSBO.h"
#include "ShaderMan.h"
#include "Anim.h"

namespace Azul
{

	Mixer::Mixer(Anim *pAnim)
		: KeyA(),
		KeyB(),
		tS(0.0f)
	{
		this->Result = pAnim->sboResult;
		this->numBones = pAnim->numBones;
	}

	void Mixer::Blend(Bone *pResult,
		const Bone *pA,
		const Bone *pB,
		const float tS,
		int numBones)
	{
		assert(pA);
		assert(pB);

		//const Bone *pBoneOrigA = pA;
		//const Bone *pBoneOrigB = pB;
		//Bone *pBoneOrigResult = pResult;

		// Interpolate to tS time, for all bones
		for(int i = 0; i < numBones; i++)
		{
			// interpolate ahoy!
			Vec3App::Lerp(pResult->T, pA->T, pB->T, tS);
			QuatApp::Slerp(pResult->Q, pA->Q, pB->Q, tS);
			Vec3App::Lerp(pResult->S, pA->S, pB->S, tS);

			// advance the pointer
			pA++;
			pB++;
			pResult++;
		}



		// Let's try the shader to prove out the mixer
		//unsigned int uNumBones = (unsigned int)numBones;

		//// ------------------------------------
		//// Load SSBO into the shader - 
		////    note: this is only for test
		////          shouldn't be here at all...
		//// -----------------------------------
		//Bone *pBoneResult = new Bone[uNumBones]();
		//Bone *pBoneA = new Bone[uNumBones]();
		//Bone *pBoneB = new Bone[uNumBones]();

		//// Fill in BoneA & BoneB array
		//for(unsigned int i = 0; i < uNumBones; i++)
		//{
		//	pBoneA[i] = pBoneOrigA[i];
		//	pBoneB[i] = pBoneOrigB[i];
		//}

		//for (unsigned int i = 0; i < uNumBones; i++)
		//{

		//	Trace::out("\n");
		//	Trace::out("[%2d]\n", i);
		//	Trace::out("  T: %+ 5.3f %+ 5.3f %+ 5.3f            %+ 5.3f %+ 5.3f %+ 5.3f  \n",
		//		pBoneA->T[x], pBoneA->T[y], pBoneA->T[z],
		//		pBoneB->T[x], pBoneB->T[y], pBoneB->T[z]);
		//	Trace::out("  Q: %+ 5.3f %+ 5.3f %+ 5.3f %+ 5.3f     %+ 5.3f %+ 5.3f %+ 5.3f %+ 5.3f \n",
		//		pBoneA->Q[x], pBoneA->Q[y], pBoneA->Q[z], pBoneA->Q[w],
		//		pBoneB->Q[x], pBoneB->Q[y], pBoneB->Q[z], pBoneB->Q[w]);
		//	Trace::out("  S: %+ 5.3f %+ 5.3f %+ 5.3f            %+ 5.3f %+ 5.3f %+ 5.3f  \n",
		//		pBoneA->S[x], pBoneA->S[y], pBoneA->S[z],
		//		pBoneB->S[x], pBoneB->S[y], pBoneB->S[z]);
		//}

		//// Place them into a Shader Buffer Object
		//SSBO *pSSBO_A = new SSBO();
		//pSSBO_A->Set(uNumBones, sizeof(Bone), pBoneA);

		//SSBO *pSSBO_B = new SSBO();
		//pSSBO_B->Set(uNumBones, sizeof(Bone), pBoneB);

		//SSBO *pSSBO_Result = new SSBO();
		//pSSBO_Result->Set(uNumBones, sizeof(Bone), pBoneResult);

		//delete[] pBoneA;
		//delete[] pBoneB;
		//delete[] pBoneResult;

		//// Lock and load the shader...
		//ShaderObject *pComputeShader = ShaderMan::Find(ShaderObject::Name::COMPUTE_MIXER);

		//pComputeShader->SetActive();

		//pSSBO_A->Bind(0);
		//pSSBO_B->Bind(1);
		//pSSBO_Result->Bind(2);

		//glUniform1f(pComputeShader->GetLocation("ts"), tS);
		//glUniform1i(pComputeShader->GetLocation("boneCount"), numBones);

		//// Dispatch
		//pComputeShader->Dispatch((unsigned int)(numBones / 8), 1, 1);

		//// Block Waiting for stages to complete
		//glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);

		//Bone *pTmp = (Bone *)pSSBO_Result->Map(SSBO::Access::READ_ONLY);

		//Trace::out("\n\n");
		//Trace::out("----------------------------------\n");
		//for(unsigned int i = 0; i < uNumBones; i++)
		//{
		//	Bone *pCompute = &pTmp[i];
		//	Bone *pCpp = &pBoneOrigResult[i];

		//	Trace::out("\n");
		//	Trace::out("[%2d]\n", i);
		//	Trace::out("  T: %+ 5.3f %+ 5.3f %+ 5.3f            %+ 5.3f %+ 5.3f %+ 5.3f   \n",
		//		pCompute->T[x], pCompute->T[y], pCompute->T[z],
		//		    pCpp->T[x],     pCpp->T[y],     pCpp->T[z]);
		//	Trace::out("  Q: %+ 5.3f %+ 5.3f %+ 5.3f %+ 5.3f     %+ 5.3f %+ 5.3f %+ 5.3f %+ 5.3f \n",
		//		pCompute->Q[x], pCompute->Q[y], pCompute->Q[z], pCompute->Q[w],
		//		pCpp->Q[x], pCpp->Q[y], pCpp->Q[z], pCpp->Q[w]);
		//	Trace::out("  S: %+ 5.3f %+ 5.3f %+ 5.3f            %+ 5.3f %+ 5.3f %+ 5.3f  \n",
		//		pCompute->S[x], pCompute->S[y], pCompute->S[z],
		//		    pCpp->S[x],     pCpp->S[y],     pCpp->S[z]);
		//}

		//pSSBO_Result->Unmap();

		//delete pSSBO_A;
		//delete pSSBO_B;
		//delete pSSBO_Result;
	}

}

// --- End of File ---
