//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "InvBindData.h"

namespace Azul
{
	InvBindData::~InvBindData()
	{
		delete[] this->poData;
		this->poData = nullptr;
	}

	InvBindData::InvBindData()
		:numMat(0),
		poData(nullptr)
	{

	}

	InvBindData::InvBindData(unsigned int _numMat)
		:numMat(_numMat),
		poData(nullptr)
	{
		
		this->poData = new float[numMat*16]();
		assert(this->poData);
	}

	InvBindData &InvBindData::operator = (const InvBindData &r)
	{
		if(this != &r)
		{
			// Nuke orginal
			this->numMat = 0;
			delete[] this->poData;

			// copy the new
			this->numMat = r.numMat;
			this->poData = new float[numMat*16]();

			for(size_t i = 0; i < (numMat*16); i++)
			{
				this->poData[i] = r.poData[i];
			}
		}

		return *this;
	}

	void InvBindData::Serialize(InvBindData_proto &out) const
	{
		AZUL_UNUSED_VAR(out);

		out.set_nummat(this->numMat);
	
		for(unsigned int i = 0; i < (numMat*16); i++)
		{
			// add it to the message(package)
			out.add_podata(this->poData[i]);
		}
	}

	void InvBindData::Deserialize(const InvBindData_proto &in)
	{
		AZUL_UNUSED_VAR(in);
		// Safety
		delete[] this->poData;
		this->poData = nullptr;

		this->numMat = in.nummat();

		this->poData = new float[numMat*16]();
		assert(this->poData);

		for(unsigned int i = 0; i < (numMat * 16); i++)
		{
			poData[i] = in.podata(i);
		}
	}

	void InvBindData::Print(const char *const pName) const
	{
		AZUL_UNUSED_VAR(pName);
		Trace::out("%s: \n", pName);

		Trace::out("numMat: %d\n",this->numMat);

	
		for(size_t i = 0; i < (numMat*16); i++)
		{
			Trace::out("%2d: InvMat----\n", i/16);
			Trace::out("%f %f %f %f\n", poData[i], poData[i+1],poData[i+2],poData[i+3]);
			Trace::out("%f %f %f %f\n", poData[i+4], poData[i + 5], poData[i + 6], poData[i + 7]);
			Trace::out("%f %f %f %f\n", poData[i+8], poData[i + 9], poData[i + 10], poData[i + 11]);
			Trace::out("%f %f %f %f\n", poData[i+12], poData[i + 13], poData[i + 14], poData[i + 15]);

			i += 15;
		}

		Trace::out("\n");
	}
}

// --- End of File ---


