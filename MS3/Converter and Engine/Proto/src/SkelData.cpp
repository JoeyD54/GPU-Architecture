//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "SkelData.h"

namespace Azul
{
	SkelData::~SkelData()
	{
		delete[] this->poSkelEntry;
		this->poSkelEntry = nullptr;
	}

	SkelData::SkelData()
	{
		this->numBones = 0;
		this->poSkelEntry = nullptr;
	}
	
	SkelData::SkelData(unsigned int _numBones)
	{
		this->numBones = _numBones;

		this->poSkelEntry = new SkelEntry[_numBones]();
		assert(this->poSkelEntry);
	}

	void SkelData::Serialize(SkelData_proto &out) const
	{
		AZUL_UNUSED_VAR(out);

		// Add the number of bones
		out.set_numbones(this->numBones);

		// Add the SkelEntry
		SkelEntry_proto tmpSkelEntry_proto;

		for(unsigned int i = 0; i < this->numBones; i++)
		{
			// create one proto
			this->poSkelEntry[i].Serialize(tmpSkelEntry_proto);

			// add it to the message(package)
			SkelEntry_proto *p = out.add_poskelentry();
			assert(p);
			*p = tmpSkelEntry_proto;
		}

		assert(out.numbones() == this->numBones);
	}

	void SkelData::Deserialize(const SkelData_proto &in)
	{
		AZUL_UNUSED_VAR(in);
		// safety
		delete[] this->poSkelEntry;
		this->poSkelEntry = nullptr;

		this->numBones = in.numbones();

		this->poSkelEntry = new SkelEntry[this->numBones]();
		assert(this->poSkelEntry);

		for(unsigned int i = 0; i < this->numBones; i++)
		{
			poSkelEntry[i].Deserialize(in.poskelentry((int)i));
		}
	}

	void SkelData::Print(const char *const pName) const
	{
		AZUL_UNUSED_VAR(pName);
		Trace::out("%s: \n", pName);

		for(size_t i = 0; i < this->numBones; i++)
		{
			this->poSkelEntry[i].Print(pName);
		}

		Trace::out("\n");


	}
}

// --- End of File ---


