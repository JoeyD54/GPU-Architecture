//----------------------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Verify.h"

namespace Azul
{
	void Verify::GetVertsCopy(unsigned char *&p, unsigned int &numBytes)
	{
		AZUL_UNUSED_VAR(p);
		AZUL_UNUSED_VAR(numBytes);

		// stubbed to shut up tests
		unsigned char *pBuff = new unsigned char[1]();
		p = pBuff;
		numBytes = 1;
	}

	void Verify::GetNormsCopy(unsigned char *&p, unsigned int &numBytes)
	{
		AZUL_UNUSED_VAR(p);
		AZUL_UNUSED_VAR(numBytes);

		// stubbed to shut up tests
		unsigned char *pBuff = new unsigned char[1]();
		p = pBuff;
		numBytes = 1;
	}

	void Verify::GetUVsCopy(unsigned char *&p, unsigned int &numBytes)
	{
		AZUL_UNUSED_VAR(p);
		AZUL_UNUSED_VAR(numBytes);

		// stubbed to shut up tests
		unsigned char *pBuff = new unsigned char[1]();
		p = pBuff;
		numBytes = 1;
	}

	void Verify::GetIndexCopy(unsigned char *&p, unsigned int &numBytes)
	{
		AZUL_UNUSED_VAR(p);
		AZUL_UNUSED_VAR(numBytes);

		// stubbed to shut up tests
		unsigned char *pBuff = new unsigned char[1]();
		p = pBuff;
		numBytes = 1;
	}

	void Verify::GetTextureBufferCopy(unsigned char *&p, unsigned int &numBytes)
	{
		AZUL_UNUSED_VAR(p);
		AZUL_UNUSED_VAR(numBytes);

		// stubbed to shut up tests
		unsigned char *pBuff = new unsigned char[1]();
		p = pBuff;
		numBytes = 1;
	}


	Verify::Model_stats Verify::GetModelStats()
	{
		Model_stats stats;
		stats = {0};

		// fill stats data fields	
		AZUL_UNUSED_VAR(stats);

		return stats;
	}

}
// --- End of File ---
