//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Clip.h"
#include "AnimTime.h"
#include "Bone.h"
#include "Mixer.h"
#include "ClipData.h"
#include "File.h"

namespace Azul
{
	Clip::Clip(const char * pName)
		: numBones(0),
		numFrames(0),
		TotalTime(AnimTime::Duration::ZERO),
		poHead(nullptr)
	{

		// -------------------------------
		// Read and recreate model data
		// -------------------------------
		File::Handle fh;
		File::Error err;

		err = File::Open(fh, pName, File::Mode::READ);

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
		ClipData_proto clipB_proto;

		clipB_proto.ParseFromString(strIn);

		ClipData clipB;
		clipB.Deserialize(clipB_proto);

		delete[] poNewBuff;
		//clipB.Print("clipB");

		this->numBones = (int)clipB.numBones;
		this->numFrames = (int)clipB.numKeyFrames;

		this->privSetAnimationData(clipB);
		//this->privSetAnimationData();

		this->TotalTime = this->privFindMaxTime();
		assert(this->numFrames == this->privFindNumFrames());
	}

	Clip::~Clip()
	{
		FrameBucket *pTmp = poHead;

		while(pTmp != nullptr)
		{
			FrameBucket *pDeleteMe = pTmp;
			pTmp = pTmp->nextBucket;
			delete pDeleteMe;
		}
	}

	void Clip::AnimateBones(AnimTime tCurr, Bone *pResult)
	{
		// First one 
		FrameBucket *pTmp = this->poHead;

		// Find which key frames
		while(tCurr >= pTmp->KeyTime && pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		// pTmp is the "B" key frame
		// pTmp->prev is the "A" key frame
		FrameBucket *pA = pTmp->prevBucket;
		FrameBucket *pB = pTmp;

		// find the "S" of the time
		float tS = (tCurr - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);

		Mixer::Blend(pResult, pA->poBone, pB->poBone, tS, this->numBones);

	}


	void Clip::AnimateBones(AnimTime tCurr, Mixer *pMixer)
	{
		assert(pMixer);

		// First one 
		FrameBucket *pTmp = this->poHead;

		// Find which key frames
		while(tCurr >= pTmp->KeyTime && pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		// pTmp is the "B" key frame
		// pTmp->prev is the "A" key frame
		FrameBucket *pA = pTmp->prevBucket;
		FrameBucket *pB = pTmp;

		pMixer->KeyA = pA->sbo;
		pMixer->KeyB = pB->sbo;

		// find the "S" of the time
		pMixer->tS = (tCurr - pA->KeyTime) / (pB->KeyTime - pA->KeyTime);
	}
	
	int Clip::GetNumBones()
	{
		return this->numBones;
	}

	int Clip::privFindNumFrames()
	{
		int count = 0;
		FrameBucket *pTmp = this->poHead;

		while(pTmp != nullptr)
		{
			count++;
			pTmp = pTmp->nextBucket;
		}
		return count;
	}

	AnimTime Clip::privFindMaxTime()
	{
		AnimTime tMax;
		FrameBucket *pTmp = this->poHead;

		while(pTmp->nextBucket != nullptr)
		{
			pTmp = pTmp->nextBucket;
		}

		tMax = pTmp->KeyTime;

		return tMax;
	}

	AnimTime Clip::GetTotalTime()
	{
		return this->TotalTime;
	}


	void Clip::privSetAnimationData(ClipData &ClipA)
	{
		FrameBucket *pTmp = nullptr;

		pTmp = this->privCreateFrameBucket(ClipA, 0);
		pTmp->prevBucket = nullptr;

		this->poHead = pTmp;

		for(unsigned int i = 1; i < ClipA.numKeyFrames; i++)
		{
			assert(ClipA.poFrameBucketEntry[i].keyFrame == i);

			FrameBucket *pFrameBucket = this->privCreateFrameBucket(ClipA, i);

			pFrameBucket->prevBucket = pTmp;
			pTmp->nextBucket = pFrameBucket;

			pTmp = pFrameBucket;
		}

		pTmp->nextBucket = nullptr;

	}

	Clip::FrameBucket * Clip::privCreateFrameBucket(ClipData &ClipA, unsigned int FrameIndex)
	{
		unsigned int i = FrameIndex;

		// create the space for the bone
		Bone *pBone = new Bone[ClipA.numBones]();

		FrameBucket *pFrameBucket = new FrameBucket();
		pFrameBucket->KeyTime = ClipA.poFrameBucketEntry[i].keyTimeIndex * AnimTime(AnimTime::Duration::FILM_24_FRAME);
		pFrameBucket->poBone = pBone;

		// Fill the bone
		for(unsigned int k = 0; k < ClipA.numBones; k++)
		{
			pBone[k].S.set(ClipA.poFrameBucketEntry[i].poBoneEntry[k].S.x,
				ClipA.poFrameBucketEntry[i].poBoneEntry[k].S.y,
				ClipA.poFrameBucketEntry[i].poBoneEntry[k].S.z);

			pBone[k].Q.set(ClipA.poFrameBucketEntry[i].poBoneEntry[k].Q.qx,
				ClipA.poFrameBucketEntry[i].poBoneEntry[k].Q.qy,
				ClipA.poFrameBucketEntry[i].poBoneEntry[k].Q.qz,
				ClipA.poFrameBucketEntry[i].poBoneEntry[k].Q.qw);

			pBone[k].T.set(ClipA.poFrameBucketEntry[i].poBoneEntry[k].T.x,
				ClipA.poFrameBucketEntry[i].poBoneEntry[k].T.y,
				ClipA.poFrameBucketEntry[i].poBoneEntry[k].T.z);
		}

		// transfer the data to the sbo
		pFrameBucket->sbo.Set(ClipA.numBones, sizeof(Bone), pFrameBucket->poBone);

		return pFrameBucket;
	}


	
}

// --- End of File ---
