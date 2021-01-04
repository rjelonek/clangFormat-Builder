#include "ClangFormatPCH1.h"
#pragma hdrstop

#include "FileInfo.h"
#include <windows.h>

namespace ClangFormat
{
	struct LangAndCodePage
	{
		unsigned short language;
		unsigned short codePage;
	};

	FileInfo::FileInfo(String fileName)
	{
		Initialize(fileName);
	}

	void FileInfo::Initialize(String fileName)
	{
		subBlockRoot = "";
		unsigned long verSize = GetFileVersionInfoSize(fileName.c_str(), 0x0);
		if (verSize != 0)
		{
			verData = std::unique_ptr<char[]>(new char[verSize]);
			if (GetFileVersionInfo(fileName.c_str(), 0x0, verSize, verData.get()))
			{
				LangAndCodePage *buffer = 0x0;
				unsigned int bufferSize = 0;
				if (VerQueryValue(verData.get(), L"\\VarFileInfo\\Translation", (void **)&buffer, &bufferSize))
				{
					wchar_t tempLangAndCodePage[9] = {};
					for (unsigned int i = 0; i < (bufferSize / sizeof(struct LangAndCodePage)); ++i)
					{
						swprintf(tempLangAndCodePage, L"%04x%04x", buffer[i].language, buffer[i].codePage);
						subBlockRoot = "\\StringFileInfo\\" + String(tempLangAndCodePage) + "\\";
						break;
					}
				}
			}
			else
				verData.reset();
		}
	}

	String FileInfo::GetStringFileInfo(String subBlockKey)
	{
		String retVal = "";
		if (verData)
		{
			char *buffer = 0x0;
			unsigned int bufferSize = 0;
			if (VerQueryValue(verData.get(), (subBlockRoot + subBlockKey).c_str(), (void **)&buffer, &bufferSize))
				retVal = buffer;
		}

		return retVal;
	}

	String FileInfo::GetProductName()
	{
		return GetStringFileInfo("ProductName");
	}

	String FileInfo::GetProductVersion()
	{
		return GetStringFileInfo("ProductVersion");
	}

	String FileInfo::GetLegalCopyright()
	{
		return GetStringFileInfo("LegalCopyright");
	}

	void FileInfo::GetBareProductVersion(int &release, int &breaking, int &feature, int &fix)
	{
		release = 0;
		breaking = 0;
		feature = 0;
		fix = 0;

		if (verData)
		{
			char *buffer = 0x0;
			unsigned int bufferSize = 0;
			if (VerQueryValue(verData.get(), L"\\", (void **)&buffer, &bufferSize))
			{
				VS_FIXEDFILEINFO *verInfo = (VS_FIXEDFILEINFO *)buffer;
				unsigned long fixedFileInfoSignature = 0xfeef04bd;
				if (verInfo->dwSignature == fixedFileInfoSignature)
				{
					release = (verInfo->dwProductVersionMS >> 16) & 0xFFFF;
					breaking = verInfo->dwProductVersionMS & 0xFFFF;
					feature = (verInfo->dwProductVersionLS >> 16) & 0xFFFF;
					fix = verInfo->dwProductVersionLS & 0xFFFF;
				}
			}
		}
	}
} // namespace ClangFormat
