
namespace Azul
{
	void ConvertedDataCopy()
	{
		// -----------------------------------------------
	// Getting this directory name programmatically 
	// trying to get: _Version_1.0_
	// HACK city below... need to do cleanly
	// -----------------------------------------------

		size_t len = strlen(SOLUTION_DIR) + 1;
		char *pDir = new char[len]();
		memcpy(pDir, SOLUTION_DIR, len);

		char *pEnd = nullptr;
		char *pStart = nullptr;
		int count = 0;
		// find the start and end ptr of desired string
		for(size_t i = len; i != 0; i--)
		{
			char data = pDir[i];
			if(data == 92 && count == 0)
			{
				count++;
				pEnd = &pDir[i];
				continue;
			}
			if(data == 92 && count == 1)
			{
				count++;
				pEnd = &pDir[i];
				continue;
			}
			if(data == 92 && count == 2)
			{
				count++;
				pStart = &pDir[i];
				pStart += 1;
				break;
			}
		}

		char *pVerName = new char[256]();
		memset(pVerName, 0, 256);
		memcpy_s(pVerName, 256, pStart, (size_t)(pEnd - pStart));

		char *pCopyCmd = new char[256]();
		memset(pCopyCmd, 0, 256);
		sprintf_s(pCopyCmd, 256, "copy *.azul \".\\..\\%s\\Data\"", pVerName);

		system(pCopyCmd);
		system("del *.azul");

		delete pCopyCmd;
		delete pVerName;
		delete pDir;
	}
}

// --- End of File ---
