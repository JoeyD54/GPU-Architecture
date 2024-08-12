//--------------------------------------------------------------
// Copyright 2022, Ed Keenan, all rights reserved.
//--------------------------------------------------------------

#include "File.h"

namespace Azul
{

	bool File::IsHandleValid(File::Handle fh) noexcept
	{
		DWORD flags;

		bool result = GetHandleInformation(fh, &flags);

		return result;
	}

	File::Error File::Open(File::Handle& fh, const char* const fileName, File::Mode mode) noexcept
	{
		File::Error  ferror = File::Error::SUCCESS;


		if (mode == File::Mode::WRITE)
		{
			fh = CreateFileA(fileName, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		}
		else if (mode == File::Mode::READ)
		{
			fh = CreateFileA(fileName, GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		}
		else if (mode == File::Mode::READ_WRITE)
		{
			fh = CreateFileA(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		}


		if (fh == INVALID_HANDLE_VALUE)
		{
			ferror = File::Error::OPEN_FAIL;
		}
		return     ferror;
	}

	File::Error File::Close(File::Handle &fh) noexcept
	{
		File::Error  ferror = File::Error::CLOSE_FAIL;
		if (IsHandleValid(fh))
		{
			if (CloseHandle(fh) != 0)
			{
				ferror = File::Error::SUCCESS;
			}
		}
		return ferror;
	}

	File::Error File::Write(File::Handle fh, const void* const buffer, const DWORD inSize) noexcept
	{
		File::Error  ferror = File::Error::SUCCESS;

		//If any of this is bad, fail
		if (!IsHandleValid(fh) || buffer == nullptr || (int) inSize < 0)
		{
			return File::Error::WRITE_FAIL;
		}

		DWORD dwBytesWritten = 0;
		WriteFile(fh, buffer, inSize, &dwBytesWritten, NULL);
		


		if (dwBytesWritten > 0 && dwBytesWritten != inSize)
		{
			ferror = File::Error::WRITE_FAIL;
		}


		return ferror;
	}

	File::Error File::Read(File::Handle fh, void* const buffer, const DWORD inSize) noexcept
	{
		if (!IsHandleValid(fh) || buffer == nullptr || (int)inSize < 0)
		{
			return File::Error::READ_FAIL;
		}

		DWORD dwBytesWritten = 0;
		ReadFile(fh, buffer, inSize, &dwBytesWritten, NULL);

		if (dwBytesWritten > 0 && dwBytesWritten != inSize)
		{
			return File::Error::READ_FAIL;
		}

		return File::Error::SUCCESS;
	}

	File::Error File::Seek(File::Handle fh, File::Position location, int offset) noexcept
	{
		DWORD tmp;
		if (location == File::Position::END)
		{
			tmp = FILE_END;
		}
		else if (location == File::Position::CURRENT)
		{
			tmp = FILE_CURRENT;
		}
		else
		{
			tmp = FILE_BEGIN;
		}


		if (!IsHandleValid(fh) || SetFilePointer(fh, offset, NULL, tmp) == INVALID_SET_FILE_POINTER)
		{
			return File::Error::SEEK_FAIL;
		}
		return File::Error::SUCCESS;
	}

	File::Error File::Tell(File::Handle fh, DWORD& offset) noexcept
	{
		offset = SetFilePointer(fh, 0, NULL, FILE_CURRENT);

		if (!IsHandleValid(fh) || offset == INVALID_SET_FILE_POINTER)
		{
			return File::Error::TELL_FAIL;
		}

		return File::Error::SUCCESS;
	}

	File::Error File::Flush(File::Handle fh) noexcept
	{
		if (!IsHandleValid(fh))
		{
			return File::Error::FLUSH_FAIL;
		}

		FlushFileBuffers(fh);
		return File::Error::SUCCESS;
	}

}

// --- End of File ---
